//---------------------------------------------------------------------------
//
// Name:        wxSwUpdate.cpp
// Author:      Gabriel Ferri
// Created:     31/07/2009
// Description: wxSwUpdate class implementation
//
//---------------------------------------------------------------------------

#include "wxSwUpdate.h"
#include "wxZipFiles.h"
#include <wx/utils.h>

#define VERSION_FILE		wxT("app.ver")

#ifdef __WXMSW__
	#define UPDATER_FILE	wxT("updater.exe")
#else
	#define UPDATER_FILE	wxT("updater")
#endif


wxSwUpdate::wxSwUpdate( const wxString &fileName, const wxString &targetDir )
{
	zipFileName = fileName;
	zipTargetDir = targetDir;
}

wxSwUpdate::~wxSwUpdate()
{
}

//----------------------------------------------------------------------------------
// Check
// Compare the version of the 'update file' with the passed one and check if the 
// 'update file' contains the updater executable
// Return: 0 = OK, -1 = Error (view errorMsg), 1 = obsolete version
//----------------------------------------------------------------------------------
int wxSwUpdate::Check( unsigned short int version, unsigned short int revision )
{
	wxMemoryOutputStream memoryBuffer;

	if( wxReadZipFile( zipFileName, VERSION_FILE, memoryBuffer ) == 0 )
	{
		char *buffer = new char[memoryBuffer.GetSize() + 1];
		memoryBuffer.CopyTo( buffer, memoryBuffer.GetSize() );
		buffer[memoryBuffer.GetSize()] = '\0';
		wxString zipVersion( buffer );
		delete [] buffer;

		// retrieve file version ( version.revision )
		long fileVer, fileRev;
		if( zipVersion.Find( '.' ) == wxNOT_FOUND )
		{
			errorMsg = _T("File corrupted ! ('") + zipFileName + _T("').");
			return -1;
		}
		zipVersion.ToLong( &fileVer );
		zipVersion.Mid( zipVersion.Find( '.' ) + 1 ).ToLong( &fileRev );

		// check version
		if( fileVer > version || ( fileVer == version && fileRev > revision ) )
		{
			// look for updater app
			if( wxCheckZipFile( zipFileName, UPDATER_FILE, zipUpdater ) == 0 )
				return 0;
			else
			{
				errorMsg = _T("File corrupted ! ('") + zipFileName + _T("').");
				return -1;
			}
		}
		else
			return 1;
	}

	errorMsg = wxZipError;
	return -1;
}

//----------------------------------------------------------------------------------
// Download
// Extract the 'update file' into zipTargetDir
//----------------------------------------------------------------------------------
int wxSwUpdate::Download()
{
	if( wxExtractZipFiles( zipFileName, zipTargetDir ) == 0 )
		return 0;

	errorMsg = wxZipError;
	return -1;
}

//----------------------------------------------------------------------------------
// RunUpdater
// Execute the updater
//----------------------------------------------------------------------------------
long wxSwUpdate::RunUpdater()
{
	#ifndef __WXMSW__
		wxString changeMode = wxT("chmod 777 ") + zipTargetDir + zipUpdater;
		changeMode.Replace( wxT("//"), wxT("/") );
		wxExecute( changeMode );
	#endif
	wxString updaterStr = zipTargetDir + zipUpdater + wxString::Format(" %d", wxGetProcessId());
	#ifndef __WXMSW__
		updaterStr.Replace( wxT("//"), wxT("/") );
	#endif
	return wxExecute( updaterStr );
}

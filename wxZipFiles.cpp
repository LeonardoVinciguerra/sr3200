//---------------------------------------------------------------------------
//
// Name:        wxZipFiles.cpp
// Author:      Gabriel Ferri
// Created:     31/07/2009
// Description: wxZipFiles functions implementation
//
//---------------------------------------------------------------------------

#include "wxZipFiles.h"
#include <wx/filesys.h>
#include <wx/wfstream.h>
#include <wx/zipstrm.h>
#include <memory>

wxString wxZipError;


//----------------------------------------------------------------------------------
// wxExtractZipFiles
// Extract archive aZipFile in directory aTargetDir
//----------------------------------------------------------------------------------
int wxExtractZipFiles( const wxString &aZipFile, const wxString &aTargetDir )
{
	wxFileSystem fs;
	std::auto_ptr<wxZipEntry> entry(new wxZipEntry);

	wxFileInputStream in( aZipFile );
	if( !in )
	{
		wxZipError = _T("Can not open file '") + aZipFile + _T("'.");
		return -1;
	}

	wxZipInputStream zip_dir( in );
	while( entry.reset(zip_dir.GetNextEntry()), entry.get() != NULL )
	{
		// read 'zip' to access the dir entry's data
		if( entry->IsDir() )
		{
			// access meta-data
			wxString name = entry->GetName();
			name = aTargetDir + name;

			int perm = entry->GetMode();
			wxFileName::Mkdir(name, perm, wxPATH_MKDIR_FULL);
		}
	}

	wxZipInputStream zip_file( in );
	while( entry.reset(zip_file.GetNextEntry()), entry.get() != NULL )
	{
		// read 'zip' to access the files entry's data
		if( !entry->IsDir() )
		{
			// access meta-data
			wxString name = entry->GetName();
			name = aTargetDir + name;

			zip_file.OpenEntry( *entry.get() );
			if( !zip_file.CanRead() )
			{
				wxZipError = _T("Can not read zip entry '") + entry->GetName() + _T("'.");
				return -1;
			}
			wxFileOutputStream file( name );
			if( !file )
			{
				wxZipError = _T("Can not create file '") + name + _T("'.");
				return -1;
			}
			zip_file.Read( file );
		}
	}

	return 0;
}

//----------------------------------------------------------------------------------
// wxReadZipFile
// Find the first occurrence of aFileName in archive aZipFile (without path) and
// store it in aBuffer
//----------------------------------------------------------------------------------
int wxReadZipFile( const wxString &aZipFile, const wxString &aFileName, const wxMemoryOutputStream &aBuffer )
{
	wxFileSystem fs;
	std::auto_ptr<wxZipEntry> entry(new wxZipEntry);

	wxFileInputStream in( aZipFile );
	if( !in )
	{
		wxZipError = _T("Can not open file '") + aZipFile + _T("'.");
		return -1;
	}

	wxZipInputStream zip_file( in );
	while( entry.reset(zip_file.GetNextEntry()), entry.get() != NULL )
	{
		// read 'zip' to access the files entry's data
		if( !entry->IsDir() )
		{
			// access meta-data
			wxFileName name( entry->GetName() );

			if( aFileName.Cmp( name.GetFullName() ) == 0 )
			{
				zip_file.OpenEntry( *entry.get() );
				if( !zip_file.CanRead() )
				{
					wxZipError = _T("Cannot read zip entry '") + entry->GetName() + _T("'.");
					return -1;
				}

				zip_file.Read( (wxOutputStream &)aBuffer );
				return 0;
			}
		}
	}

	wxZipError = _T("File '") + aFileName + _T("' not found !");
	return -1;
}


//----------------------------------------------------------------------------------
// wxCheckZipFile
// Check if file aFileName is in archive aZipFile (without path)
//----------------------------------------------------------------------------------
int wxCheckZipFile( const wxString &aZipFile, const wxString &aFileName )
{
	wxFileSystem fs;
	std::auto_ptr<wxZipEntry> entry(new wxZipEntry);

	wxFileInputStream in( aZipFile );
	if( !in )
	{
		wxZipError = _T("Can not open file '") + aZipFile + _T("'.");
		return -1;
	}

	wxZipInputStream zip_file( in );
	while( entry.reset(zip_file.GetNextEntry()), entry.get() != NULL )
	{
		// read 'zip' to access the files entry's data
		if( !entry->IsDir() )
		{
			// access meta-data
			wxFileName name( entry->GetName() );

			if( aFileName.Cmp( name.GetFullName() ) == 0 )
				return 0;
		}
	}

	wxZipError = _T("File '") + aFileName + _T("' not found !");
	return -1;
}


//----------------------------------------------------------------------------------
// wxCheckZipFile
// Check if file aFileName is in archive aZipFile (without path) and store in
// aFileNamePath its path
//----------------------------------------------------------------------------------
int wxCheckZipFile( const wxString &aZipFile, const wxString &aFileName, wxString &aFileNamePath )
{
	wxFileSystem fs;
	std::auto_ptr<wxZipEntry> entry(new wxZipEntry);

	wxFileInputStream in( aZipFile );
	if( !in )
	{
		wxZipError = _T("Can not open file '") + aZipFile + _T("'.");
		return -1;
	}

	wxZipInputStream zip_file( in );
	while( entry.reset(zip_file.GetNextEntry()), entry.get() != NULL )
	{
		// read 'zip' to access the files entry's data
		if( !entry->IsDir() )
		{
			// access meta-data
			wxFileName name( entry->GetName() );

			if( aFileName.Cmp( name.GetFullName() ) == 0 )
			{
				aFileNamePath = entry->GetName();
				return 0;
			}
		}
	}

	wxZipError = _T("File '") + aFileName + _T("' not found !");
	return -1;
}

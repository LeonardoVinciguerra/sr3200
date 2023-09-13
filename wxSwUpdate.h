//---------------------------------------------------------------------------
//
// Name:        wxSwUpdate.h
// Author:      Gabriel Ferri
// Created:     31/07/2009
// Description: wxSwUpdate class declaration
//
//---------------------------------------------------------------------------

#ifndef __WXSWUPDATE_H
#define __WXSWUPDATE_H

#include <wx/string.h>

class wxSwUpdate
{
public:

    wxSwUpdate( const wxString &fileName, const wxString &targetDir );
    ~wxSwUpdate();

	int Check( unsigned short int version, unsigned short int revision );
	int Download();
	long RunUpdater();

	wxString GetErrorMessage() { return errorMsg; };

private:
	wxString errorMsg;

	wxString zipFileName;
	wxString zipUpdater;
	wxString zipTargetDir;
};

#endif

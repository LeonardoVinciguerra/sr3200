//---------------------------------------------------------------------------
//
// Name:        wxMyEntryDialog.h
// Author:      Gabriel Ferri
// Created:     10/06/2008
// Description: wxMyEntryDialog class declaration
//
//---------------------------------------------------------------------------

#ifndef __WXMYENTRYDIALOG_H
#define __WXMYENTRYDIALOG_H

#include <wx/textdlg.h>

class wxMyEntryDialog : public wxTextEntryDialog
{
public:
	wxMyEntryDialog( wxWindow* parent, const wxString& message, const wxString& caption = "Please enter text", const wxString& defaultValue = "", long style = wxOK | wxCANCEL | wxCENTRE, const wxPoint& pos = wxDefaultPosition );

	void SetMyValidator( const wxValidator &validator );
};

#endif

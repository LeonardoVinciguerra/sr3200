//---------------------------------------------------------------------------
//
// Name:        wxMyEntryDialog.cpp
// Author:      Gabriel Ferri
// Created:     10/06/2008
// Description: wxMyEntryDialog class implementation
//
//---------------------------------------------------------------------------

#include "wxMyEntryDialog.h"


//----------------------------------------------------------------------------------
// wxMyEntryDialog
// 
//----------------------------------------------------------------------------------
wxMyEntryDialog::wxMyEntryDialog( wxWindow* parent, const wxString& message, const wxString& caption, const wxString& defaultValue, long style, const wxPoint& pos )
	: wxTextEntryDialog( parent, message, caption, defaultValue, style, pos )
{
}

//----------------------------------------------------------------------------------
// SetMyValidator
// 
//----------------------------------------------------------------------------------
void wxMyEntryDialog::SetMyValidator( const wxValidator &validator )
{
	m_textctrl->SetValidator( validator );
}

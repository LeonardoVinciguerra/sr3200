//---------------------------------------------------------------------------
//
// Name:        wxMySpinValidator.cpp
// Author:      Gabriel Ferri
// Created:     09/06/2009 10.52.01
// Description: wxMySpinValidator class implementation
//
//---------------------------------------------------------------------------

#include "wxMySpinValidator.h"
#include <wx/spinctrl.h>

//----------------------------------------------------------------------------------
// wxMyValidator
// Costruttore
//----------------------------------------------------------------------------------
wxMySpinValidator::wxMySpinValidator( int *value )
: wxValidator()
{
	m_intValue = value;

	Initialize();
}

wxMySpinValidator::wxMySpinValidator( const wxMySpinValidator & val )
: wxValidator()
{
    Copy( val );
}

//----------------------------------------------------------------------------------
// Initialize
// 
//----------------------------------------------------------------------------------
void wxMySpinValidator::Initialize()
{
	//
}

//----------------------------------------------------------------------------------
// Clone
// Make a clone of this validator (or return NULL) - currently necessary if you're
// passing a reference to a validator.
// Another possibility is to always pass a pointer to a new validator (so the
// calling code can use a copy constructor of the relevant class).
//----------------------------------------------------------------------------------
wxObject* wxMySpinValidator::Clone() const
{
    return new wxMySpinValidator(*this);
}

//----------------------------------------------------------------------------------
// Copy
// 
//----------------------------------------------------------------------------------
bool wxMySpinValidator::Copy( const wxMySpinValidator& val )
{
    wxValidator::Copy( val );

	m_intValue = val.m_intValue;

	return true;
}

//----------------------------------------------------------------------------------
// TransferFromWindow
// Called to transfer data from the window
//----------------------------------------------------------------------------------
bool wxMySpinValidator::TransferFromWindow()
{
	*m_intValue = (int)((wxSpinCtrl *)m_validatorWindow)->GetValue();

	return true;
}

//----------------------------------------------------------------------------------
// TransferToWindow
// Called to transfer data to the window
//----------------------------------------------------------------------------------
bool wxMySpinValidator::TransferToWindow()
{
	((wxSpinCtrl *)m_validatorWindow)->SetValue( wxString::Format("%d", *m_intValue) );

	return true;
}

//----------------------------------------------------------------------------------
// Validate
// Called when the value in the window must be validated
// This function can pop up an error message
//----------------------------------------------------------------------------------
bool wxMySpinValidator::Validate( wxWindow* parent )
{
    return true;
}

//---------------------------------------------------------------------------
//
// Name:        wxMyComboValidator.cpp
// Author:      Gabriel Ferri
// Created:     18/04/2008 12.06.21
// Description: wxMyComboValidator class implementation
//
//---------------------------------------------------------------------------

#include "wxMyComboValidator.h"
#include <wx/combobox.h>

//----------------------------------------------------------------------------------
// wxMyValidator
// Costruttore
//----------------------------------------------------------------------------------
wxMyComboValidator::wxMyComboValidator( int *value, bool isSelection )
: wxValidator()
{
	m_type = myComboINT;

	m_intValue = value;
	m_isSelection = isSelection;

	Initialize();
}

wxMyComboValidator::wxMyComboValidator( wxString *value )
: wxValidator()
{
	m_type = myComboSTRING;

	m_stringValue = value;
	m_isSelection = true;

	Initialize();
}

wxMyComboValidator::wxMyComboValidator( const wxMyComboValidator & val )
: wxValidator()
{
    Copy( val );
}

//----------------------------------------------------------------------------------
// Initialize
// 
//----------------------------------------------------------------------------------
void wxMyComboValidator::Initialize()
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
wxObject* wxMyComboValidator::Clone() const
{
    return new wxMyComboValidator(*this);
}

//----------------------------------------------------------------------------------
// Copy
// 
//----------------------------------------------------------------------------------
bool wxMyComboValidator::Copy( const wxMyComboValidator& val )
{
    wxValidator::Copy( val );

	m_type			= val.m_type;

	m_intValue		= val.m_intValue;
	m_stringValue	= val.m_stringValue;

	m_isSelection	= val.m_isSelection;

    return true;
}

//----------------------------------------------------------------------------------
// TransferFromWindow
// Called to transfer data from the window
//----------------------------------------------------------------------------------
bool wxMyComboValidator::TransferFromWindow()
{
	if( m_type == myComboINT )
	{
		if( m_isSelection )
		{
			*m_intValue = ((wxComboBox *)m_validatorWindow)->GetSelection();
		}
		else
		{
			long longVal;
			((wxComboBox *)m_validatorWindow)->GetValue().ToLong( &longVal );
			*m_intValue = (int)longVal;
		}
	}
	else if( m_type == myComboSTRING )
	{
		*m_stringValue = ((wxComboBox *)m_validatorWindow)->GetValue();
	}

	return true;
}

//----------------------------------------------------------------------------------
// TransferToWindow
// Called to transfer data to the window
//----------------------------------------------------------------------------------
bool wxMyComboValidator::TransferToWindow()
{
	if( m_type == myComboINT )
	{
		if( m_isSelection )
		{
			((wxComboBox *)m_validatorWindow)->SetSelection( *m_intValue );
		}
		else
		{
			((wxComboBox *)m_validatorWindow)->SetValue( wxString::Format("%d", *m_intValue) );
		}
	}
	else if( m_type == myComboSTRING )
	{
		((wxComboBox *)m_validatorWindow)->SetValue( *m_stringValue );
	}

	return true;
}

//----------------------------------------------------------------------------------
// Validate
// Called when the value in the window must be validated
// This function can pop up an error message
//----------------------------------------------------------------------------------
bool wxMyComboValidator::Validate( wxWindow* parent )
{
	/*
    wxString val(((wxTextCtrl*)m_validatorWindow)->GetValue());

    // valid the length
    size_t len = val.Len();
    if ( len < m_minLen || (m_maxLen > 0 && len > m_maxLen))
            return false;

    // valid the value
    for ( size_t i = 0; i < val.Len(); ++i) {
            if ( !wxIsxdigit(val[i])) return false;
    }
	*/
    return true;
}

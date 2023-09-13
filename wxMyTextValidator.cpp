//---------------------------------------------------------------------------
//
// Name:        wxMyTextValidator.cpp
// Author:      Gabriel Ferri
// Created:     17/04/2008 10.41.44
// Description: wxMyTextValidator class implementation
//
//---------------------------------------------------------------------------

#include "wxMyTextValidator.h"
#include <wx/textctrl.h>

//----------------------------------------------------------------------------------
// wxMyValidator
// Costruttore
//----------------------------------------------------------------------------------
wxMyTextValidator::wxMyTextValidator( bool isNegative, bool isReal )
: wxValidator()
{
	m_type = myTextNULL;
	m_isNegative = isNegative;
	m_isReal = isReal;
	m_decimal = 3;

	Initialize();
}

wxMyTextValidator::wxMyTextValidator( int *value, bool isNegative )
: wxValidator()
{
	m_type = myTextINT;
	m_intValue = value;
	m_isNegative = isNegative;
	m_isReal = false;
	m_decimal = 0;

	Initialize();
}

wxMyTextValidator::wxMyTextValidator( long *value, bool isNegative )
: wxValidator()
{
	m_type = myTextLONG;
	m_longValue = value;
	m_isNegative = isNegative;
	m_isReal = false;
	m_decimal = 0;

	Initialize();
}

wxMyTextValidator::wxMyTextValidator( float *value, bool isNegative, int decimal )
: wxValidator()
{
	m_type = myTextFLOAT;
	m_floatValue = value;
	m_isNegative = isNegative;
	m_isReal = true;
	m_decimal = decimal;

	Initialize();
}

wxMyTextValidator::wxMyTextValidator( double *value, bool isNegative, int decimal )
: wxValidator()
{
	m_type = myTextDOUBLE;
	m_doubleValue = value;
	m_isNegative = isNegative;
	m_isReal = true;
	m_decimal = decimal;

	Initialize();
}

wxMyTextValidator::wxMyTextValidator( wxString *value )
: wxValidator()
{
	m_type = myTextSTRING;
	m_stringValue = value;

	Initialize();
}

wxMyTextValidator::wxMyTextValidator( const wxMyTextValidator & val )
: wxValidator()
{
    Copy( val );
}

//----------------------------------------------------------------------------------
// Initialize
// 
//----------------------------------------------------------------------------------
void wxMyTextValidator::Initialize()
{
	this->Connect( wxEVT_CHAR, wxKeyEventHandler(wxMyTextValidator::OnChar) );

	// nasty trick to retrieve current decimal separator
	wxString tmp = wxString::Format( "%1.1f", 1.0 );
	if( tmp.Find( '.' ) != wxNOT_FOUND )
	{
		m_localeSeparator = wxT(".");
	}
	else
	{
		m_localeSeparator = wxT(",");
	}
}

//----------------------------------------------------------------------------------
// Clone
// Make a clone of this validator (or return NULL) - currently necessary if you're
// passing a reference to a validator.
// Another possibility is to always pass a pointer to a new validator (so the
// calling code can use a copy constructor of the relevant class).
//----------------------------------------------------------------------------------
wxObject* wxMyTextValidator::Clone() const
{
    return new wxMyTextValidator(*this);
}

//----------------------------------------------------------------------------------
// Copy
// 
//----------------------------------------------------------------------------------
bool wxMyTextValidator::Copy( const wxMyTextValidator& val )
{
    wxValidator::Copy( val );
	m_localeSeparator	= val.m_localeSeparator;

	m_type				= val.m_type;
	m_intValue			= val.m_intValue;
	m_longValue			= val.m_longValue;
	m_floatValue		= val.m_floatValue;
	m_doubleValue		= val.m_doubleValue;
	m_stringValue		= val.m_stringValue;

	m_isNegative		= val.m_isNegative;
	m_isReal			= val.m_isReal;
	m_decimal			= val.m_decimal;

	this->Connect( wxEVT_CHAR, wxKeyEventHandler(wxMyTextValidator::OnChar) );

    return true;
}

//----------------------------------------------------------------------------------
// TransferFromWindow
// Called to transfer data from the window
//----------------------------------------------------------------------------------
bool wxMyTextValidator::TransferFromWindow()
{
	if( m_type == myTextINT )
	{
		long longVal;
		((wxTextCtrl *)m_validatorWindow)->GetValue().ToLong( &longVal );
		*m_intValue = (int)longVal;
	}
	else if( m_type == myTextLONG )
	{
		long longVal;
		((wxTextCtrl *)m_validatorWindow)->GetValue().ToLong( &longVal );
		*m_longValue = longVal;
	}
	else if( m_type == myTextFLOAT )
	{
		double floatVal;
		((wxTextCtrl *)m_validatorWindow)->GetValue().ToDouble( &floatVal );
		*m_floatValue = (float)floatVal;
	}
	else if( m_type == myTextDOUBLE )
	{
		double doubleVal;
		((wxTextCtrl *)m_validatorWindow)->GetValue().ToDouble( &doubleVal );
		*m_doubleValue = doubleVal;
	}
	else if( m_type == myTextSTRING )
	{
		*m_stringValue = ((wxTextCtrl *)m_validatorWindow)->GetValue();
	}

	return true;
}

//----------------------------------------------------------------------------------
// TransferToWindow
// Called to transfer data to the window
//----------------------------------------------------------------------------------
bool wxMyTextValidator::TransferToWindow()
{
	if( m_type == myTextINT )
	{
		((wxTextCtrl *)m_validatorWindow)->ChangeValue( wxString::Format( "%d", *m_intValue ) );
	}
	else if( m_type == myTextLONG )
	{
		((wxTextCtrl *)m_validatorWindow)->ChangeValue( wxString::Format( "%d", (int)*m_longValue ) );
	}
	else if( m_type == myTextFLOAT )
	{
		((wxTextCtrl *)m_validatorWindow)->ChangeValue( wxString::Format( wxString::Format( "%%.%df", m_decimal ), *m_floatValue ) );
	}
	else if( m_type == myTextDOUBLE )
	{
		((wxTextCtrl *)m_validatorWindow)->ChangeValue( wxString::Format( wxString::Format( "%%.%df", m_decimal ), *m_doubleValue ) );
	}
	else if( m_type == myTextSTRING )
	{
		((wxTextCtrl *)m_validatorWindow)->ChangeValue( *m_stringValue );
	}

	return true;
}

//----------------------------------------------------------------------------------
// Validate
// Called when the value in the window must be validated
// This function can pop up an error message
//----------------------------------------------------------------------------------
bool wxMyTextValidator::Validate( wxWindow* parent )
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

//----------------------------------------------------------------------------------
// OnChar
// 
//----------------------------------------------------------------------------------
void wxMyTextValidator::OnChar( wxKeyEvent& event )
{
	if( m_validatorWindow )
	{
		// don't filter if myTextSTRING
		if( m_type == myTextSTRING )
		{
			event.Skip();
			return;
		}

		int keyCode = event.GetKeyCode();

		// don't filter special keys and Delete
		if( keyCode < WXK_SPACE || keyCode == WXK_DELETE || keyCode > WXK_START )
		{
			event.Skip();
			return;
		}

		wxTextCtrl *ctrl = (wxTextCtrl *)m_validatorWindow;
		long pos = ctrl->GetInsertionPoint();

		// filter digits
		if( wxIsdigit(keyCode) )
		{
			if( pos == 0 )
			{
				if( ctrl->GetStringSelection().Len() != 0 )
				{
					event.Skip();
				}
				else if( ctrl->GetValue().Find( '-' ) == wxNOT_FOUND )
				{
					event.Skip();
				}
			}
			else
			{
				event.Skip();
			}

			return;
		}

		// filter '-'
		if( m_isNegative && keyCode == '-' && pos == 0 )
		{
			if( ctrl->GetStringSelection().Len() != 0 )
			{
				event.Skip();
			}
			else if( ctrl->GetValue().Find( '-' ) == wxNOT_FOUND )
			{
				event.Skip();
			}

			return;
		}

		// filter decimal separator
		if( m_isReal && (keyCode == '.' ||  keyCode == ',') )
		{
			if( pos == 0 )
			{
				if( ctrl->GetStringSelection().Find( m_localeSeparator ) != wxNOT_FOUND )
				{
					ctrl->WriteText( m_localeSeparator );
				}
				else if( ctrl->GetValue().Find( m_localeSeparator ) == wxNOT_FOUND )
				{
					if( ctrl->GetValue().Find( '-' ) == wxNOT_FOUND )
					{
						ctrl->WriteText( m_localeSeparator );
					}
				}
			}
			else
			{
				if( ctrl->GetStringSelection().Find( m_localeSeparator ) != wxNOT_FOUND )
				{
					ctrl->WriteText( m_localeSeparator );
				}
				else if( ctrl->GetValue().Find( m_localeSeparator ) == wxNOT_FOUND )
				{
					ctrl->WriteText( m_localeSeparator );
				}
			}

			return;
		}
	}
}

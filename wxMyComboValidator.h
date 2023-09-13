//---------------------------------------------------------------------------
//
// Name:        wxMyComboValidator.h
// Author:      Gabriel Ferri
// Created:     18/04/2008 12.06.21
// Description: wxMyComboValidator class declaration
//
//---------------------------------------------------------------------------

#ifndef __WXMYCOMBOVALIDATOR_H
#define __WXMYCOMBOVALIDATOR_H

#include <wx/validate.h>

enum myComboValidatorType
{
	myComboNULL,
	myComboINT,
	myComboSTRING
};

class wxMyComboValidator : public wxValidator
{
	public:
		wxMyComboValidator( int *value, bool isSelection = true );
		wxMyComboValidator( wxString *value );
		wxMyComboValidator( const wxMyComboValidator & val );

		wxObject* Clone() const;
		bool Copy( const wxMyComboValidator& val );

		bool TransferFromWindow();
		bool TransferToWindow();
		bool Validate( wxWindow* parent );

	protected:
		void Initialize();

		myComboValidatorType m_type;

		int *m_intValue;
		wxString *m_stringValue;

		bool m_isSelection;
};

#endif

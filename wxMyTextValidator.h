//---------------------------------------------------------------------------
//
// Name:        wxMyTextValidator.h
// Author:      Gabriel Ferri
// Created:     17/04/2008 10.41.44
// Description: wxMyTextValidator class declaration
//
//---------------------------------------------------------------------------

#ifndef __WXMYTEXTVALIDATOR_H
#define __WXMYTEXTVALIDATOR_H

#include <wx/validate.h>

enum myTextValidatorType
{
	myTextNULL,
	myTextINT,
	myTextLONG,
	myTextFLOAT,
	myTextDOUBLE,
	myTextSTRING
};

class wxMyTextValidator : public wxValidator
{
	public:
		wxMyTextValidator( bool isNegative = true, bool isReal = true );
		wxMyTextValidator( int *value, bool isNegative = true );
		wxMyTextValidator( long *value, bool isNegative = true );
		wxMyTextValidator( float *value, bool isNegative = true, int decimal = 3 );
		wxMyTextValidator( double *value, bool isNegative = true, int decimal = 3 );
		wxMyTextValidator( wxString *value );
		wxMyTextValidator( const wxMyTextValidator & val );

		wxObject* Clone() const;
		bool Copy( const wxMyTextValidator& val );

		bool TransferFromWindow();
		bool TransferToWindow();
		bool Validate( wxWindow* parent );
		void OnChar( wxKeyEvent& event );

	protected:
		void Initialize();

		wxString m_localeSeparator;

		myTextValidatorType m_type;
		int *m_intValue;
		long *m_longValue;
		float *m_floatValue;
		double *m_doubleValue;
		wxString *m_stringValue;

		bool m_isNegative;
		bool m_isReal;
		int m_decimal;
};

#endif

//---------------------------------------------------------------------------
//
// Name:        wxMySpinValidator.h
// Author:      Gabriel Ferri
// Created:     09/06/2009 10.52.01
// Description: wxMySpinValidator class declaration
//
//---------------------------------------------------------------------------

#ifndef __WXMYSPINVALIDATOR_H
#define __WXMYSPINVALIDATOR_H

#include <wx/validate.h>

class wxMySpinValidator : public wxValidator
{
	public:
		wxMySpinValidator( int *value );
		wxMySpinValidator( const wxMySpinValidator & val );

		wxObject* Clone() const;
		bool Copy( const wxMySpinValidator& val );

		bool TransferFromWindow();
		bool TransferToWindow();
		bool Validate( wxWindow* parent );

	protected:
		void Initialize();

		int *m_intValue;
};

#endif

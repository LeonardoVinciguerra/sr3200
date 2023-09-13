/***************************************************************
 * Name:      wxSR3200App.h
 * Purpose:   Defines Application Class
 * Author:    Gabriel Ferri ()
 * Created:   2008-21-01
 * Copyright: Gabriel Ferri ()
 * License:
 **************************************************************/

#ifndef WXSR3200APP_H
#define WXSR3200APP_H

#include <wx/app.h>
#include <wx/snglinst.h>
#include "wxTranslationHelper.h"


class wxSR3200App : public wxApp
{
	public:
		bool OnInit();
		int OnExit();

		void SetShutdown( bool state ) { shutdown = state; };

		void GetInstalledLanguages( wxArrayString & names );
		wxString GetCurrentLanguage();
		bool SelectLanguage( const wxString & name );

	protected:
		wxTranslationHelper *translationHelper;
		wxArrayLong langIdentifiers;
		wxArrayString langNames;
		//wxSingleInstanceChecker* m_checker;

		bool shutdown;
};

DECLARE_APP( wxSR3200App );

#endif // WXSR3200APP_H

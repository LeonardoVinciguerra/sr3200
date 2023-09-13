/***************************************************************
 * Name:      wxSR3200App.cpp
 * Purpose:   Code for Application Class
 * Author:    Gabriel Ferri ()
 * Created:   2008-21-01
 * Copyright: Gabriel Ferri ()
 * License:
 **************************************************************/

#include "wxSR3200App.h"
#include <wx/log.h>
#include "wxMainWin.h"

IMPLEMENT_APP( wxSR3200App )

bool wxSR3200App::OnInit()
{
	shutdown = false;

	// Check if there is another instance running
	/*
	const wxString name = wxString::Format("wxsr3200-%s", wxGetUserId().c_str());
	m_checker = new wxSingleInstanceChecker( name );
	if( m_checker->IsAnotherRunning() )
	{
		wxLogError( wxT("Another program instance is already running!!!") );
		return false;
	}
	*/
	//se schioppa il test, vai nella home, abilita file nascosti e cancella quello wx3200
	// Load language
	translationHelper = new wxTranslationHelper( *this, DIR_LANGUAGES );
	if( !translationHelper->IsLanguageSelected() )
		return false;

	// add PNG handler
	wxImage::AddHandler(new wxPNGHandler);

	// Create the main window
	wxMainWin* dialog = new wxMainWin( NULL );
	SetTopWindow( dialog );

	// Show the main window
	dialog->Show( true );
	dialog->Raise(); // bring to front
	dialog->Update();

	return true;
}

int wxSR3200App::OnExit()
{
	//wxDELETE( m_checker );
	wxDELETE( translationHelper );

	if( shutdown )
	{
		#ifdef __WXMSW__
			wxShutdown( wxSHUTDOWN_POWEROFF );
		#else
			system( "shutdown -h now" );
		#endif
	}

	return 0;
}

void wxSR3200App::GetInstalledLanguages( wxArrayString & names )
{
	translationHelper->GetInstalledLanguages( langNames, langIdentifiers );
	names.Clear();
	names = langNames;
}

wxString wxSR3200App::GetCurrentLanguage()
{
	wxLocale * locale = translationHelper->GetLocale();
	return locale->GetLocale();
}

bool wxSR3200App::SelectLanguage( const wxString & name )
{
	for( size_t i = 0; i < langNames.Count(); i++ )
	{
		if( langNames[i].Cmp( name ) == 0 )
			return translationHelper->SetLanguage( langNames, langIdentifiers, i );
	}
	return true;
}

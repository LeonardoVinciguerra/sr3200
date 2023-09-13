//---------------------------------------------------------------------------
//
// Name:        wxTranslationHelper.h
// Author:      Gabriel Ferri
// Created:     5/09/2008
// Description: wxTranslationHelper class declaration
//
//---------------------------------------------------------------------------
#ifndef WXTRANSLATIONHELPER_H
#define WXTRANSLATIONHELPER_H

#include <wx/app.h>

class wxTranslationHelper
{
    wxApp & m_App;
    wxLocale * m_Locale;
	wxString m_CatalogDir;

	bool isLanguageSelected;

public:
    wxTranslationHelper( wxApp &app, const wxString &catalogDir );
    ~wxTranslationHelper();

    wxLocale * GetLocale();
    void GetInstalledLanguages( wxArrayString & names, wxArrayLong & identifiers );
	bool SetLanguage( const wxArrayString & names, const wxArrayLong & identifiers, size_t index );
    bool AskUserForLanguage( const wxArrayString & names, const wxArrayLong & identifiers );
    bool Load();
    void Save( bool bReset = false );
	bool IsLanguageSelected() { return isLanguageSelected; };
};

#endif

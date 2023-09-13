//---------------------------------------------------------------------------
//
// Name:        wxTranslationHelper.cpp
// Author:      GAbriel Ferri
// Created:     5/09/2008
// Description: wxTranslationHelper class implementation
//
//---------------------------------------------------------------------------
#include "wxTranslationHelper.h"
#include <wx/config.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/choicdlg.h>


wxTranslationHelper::wxTranslationHelper( wxApp & app, const wxString &catalogDir )
: m_App(app), m_Locale(NULL), m_CatalogDir(catalogDir)
{
	isLanguageSelected = Load();
}

wxTranslationHelper::~wxTranslationHelper()
{
	Save();
	wxDELETE(m_Locale);
}

wxLocale * wxTranslationHelper::GetLocale()
{
	return m_Locale;
}

bool wxTranslationHelper::Load()
{
	wxConfig config( m_App.GetAppName() );
	long language;
	if( !config.Read( wxT("wxSR3200_Language"), &language, wxLANGUAGE_UNKNOWN ) )
	{
		language = wxLANGUAGE_UNKNOWN;
	}

	wxArrayString names;
	wxArrayLong identifiers;
	GetInstalledLanguages( names, identifiers );

	if( language == wxLANGUAGE_UNKNOWN )
		return AskUserForLanguage( names, identifiers );

	for( size_t i = 0; i < identifiers.Count(); i++ )
	{
		if( identifiers[i] == language )
		{
			wxDELETE( m_Locale );
			m_Locale = new wxLocale;
			m_Locale->Init( identifiers[i] );
			m_Locale->AddCatalogLookupPathPrefix( m_CatalogDir );
			m_Locale->AddCatalog( m_App.GetAppName() );
			return true;
		}
	}
	return false;
}

void wxTranslationHelper::Save( bool bReset )
{
	wxConfig config( m_App.GetAppName() );
	long language = wxLANGUAGE_UNKNOWN;
	if( !bReset )
	{
		if( m_Locale )
		{
			language = m_Locale->GetLanguage();
		}
	}
	config.Write( wxT("wxSR3200_Language"), language );
	config.Flush();
}

void wxTranslationHelper::GetInstalledLanguages( wxArrayString & names, wxArrayLong & identifiers )
{
	names.Clear();
	identifiers.Clear();
	wxDir dir( m_CatalogDir );
	wxString filename;	
	const wxLanguageInfo * langinfo;
	wxString name = wxLocale::GetLanguageName( wxLANGUAGE_DEFAULT );
	if( !name.IsEmpty() )
	{
		names.Add( wxT("Default") );
		identifiers.Add( wxLANGUAGE_DEFAULT );
	}

	for( bool cont = dir.GetFirst(&filename); cont; cont = dir.GetNext(&filename) )
	{
		if( wxDirExists( dir.GetName()+wxFileName::GetPathSeparator()+filename ) )
		{
			langinfo = wxLocale::FindLanguageInfo( filename );
			if( langinfo != NULL )
			{
				if( wxFileExists(dir.GetName()+wxFileName::GetPathSeparator()+filename+wxFileName::GetPathSeparator()+m_App.GetAppName()+wxT(".mo")))
				{
					names.Add( langinfo->Description );
					identifiers.Add( langinfo->Language );
				}
			}
		}
	}
}

bool wxTranslationHelper::SetLanguage( const wxArrayString & names, const wxArrayLong & identifiers, size_t index )
{
	if( index >= identifiers.Count() )
		return false;

	wxDELETE( m_Locale );
	m_Locale = new wxLocale;
	m_Locale->Init( identifiers[index] );
	m_Locale->AddCatalogLookupPathPrefix( m_CatalogDir );
	m_Locale->AddCatalog( m_App.GetAppName() );
	return true;
}

bool wxTranslationHelper::AskUserForLanguage( const wxArrayString & names, const wxArrayLong & identifiers )
{
	long index = wxGetSingleChoiceIndex( wxT("Select the language"), wxT("Language"), names );
	if( index == -1 )
		return false;

	wxDELETE( m_Locale );
	m_Locale = new wxLocale;
	m_Locale->Init( identifiers[index] );
	m_Locale->AddCatalogLookupPathPrefix( m_CatalogDir );
	m_Locale->AddCatalog( m_App.GetAppName() );
	return true;
}

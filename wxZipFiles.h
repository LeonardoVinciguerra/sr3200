//---------------------------------------------------------------------------
//
// Name:        wxZipFiles.h
// Author:      Gabriel Ferri
// Created:     31/07/2009
// Description: wxZipFiles functions declaration
//
//---------------------------------------------------------------------------

#ifndef __WXZIPFILES_H
#define __WXZIPFILES_H

#include <wx/string.h>
#include <wx/mstream.h>

int wxExtractZipFiles( const wxString &aZipFile, const wxString &aTargetDir );
int wxReadZipFile( const wxString &aZipFile, const wxString &aFileName, const wxMemoryOutputStream &aBuffer );
int wxCheckZipFile( const wxString &aZipFile, const wxString &aFileName );
int wxCheckZipFile( const wxString &aZipFile, const wxString &aFileName, wxString &aFileNamePath );

extern wxString wxZipError;

#endif

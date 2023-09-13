//---------------------------------------------------------------------------
//
// Name:        wxPictureBox.h
// Author:      Gabriel Ferri
// Created:     13/05/2008
// Description: wxPictureBox class declaration
//
//---------------------------------------------------------------------------

#ifndef __WXPICTUREBOX_H
#define __WXPICTUREBOX_H

#include <wx/panel.h>
#include <wx/bitmap.h>

//TEMP - sono qui perche' altrimenti non funzione il link
#include <wx/dcmemory.h>
#include <wx/dcbuffer.h>

class wxPictureBox : public wxPanel
{
public:
	wxPictureBox( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize );

	void SetImage( const wxBitmap& img );
	wxPoint ScreenToImage( const wxPoint& pt );

	void SetImageDisplacement( int pixels ) { displacement = pixels; };
	int GetImageDisplacement() { return displacement; };

	int GetControlBorder() { return border_sunken_width; };

	void ConnectMouseEvent( int eventType, wxMouseEventFunction func, wxEvtHandler* eventSink ) { Connect( GetId(), eventType, (wxObjectEventFunction)(wxEventFunction)func, NULL, eventSink ); };
	bool DisconnectMouseEvent( int eventType, wxMouseEventFunction func, wxEvtHandler* eventSink ) { return Disconnect( GetId(), eventType, (wxObjectEventFunction)(wxEventFunction)func, NULL, eventSink ); };

	void ConnectKeyEvent( int eventType, wxCharEventFunction func, wxEvtHandler* eventSink ) { Connect( GetId(), eventType, (wxObjectEventFunction)(wxEventFunction)func, NULL, eventSink ); };
	bool DisconnectKeyEvent( int eventType, wxCharEventFunction func, wxEvtHandler* eventSink ) { return Disconnect( GetId(), eventType, (wxObjectEventFunction)(wxEventFunction)func, NULL, eventSink ); };

	int GetWidth() { return image.GetWidth(); };
	int GetHeight() { return image.GetHeight(); };

	wxColour GetPixelColour(int x, int y);

private:
	void OnPaint( wxPaintEvent& e );
	void OnSize( wxSizeEvent& e );

	wxBitmap image;
	int border_sunken_width;
	int displacement;
};

#endif

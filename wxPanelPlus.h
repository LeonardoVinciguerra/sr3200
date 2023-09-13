//---------------------------------------------------------------------------
//
// Name:        wxPanelPlus.h
// Author:      Gabriel Ferri
// Created:     17/11/2010
// Description: wxPanelPlus class declaration
//
//---------------------------------------------------------------------------

#ifndef __WXPANELPLUS_H
#define __WXPANELPLUS_H

#include <wx/panel.h>

class wxPanelPlus : public wxPanel
{
public:
	wxPanelPlus( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize );

	void SetLabel( const wxString& value ) { text = value; };
	void SetBackgroundBorderColour( wxColor color ) { bgBorderColor = color; isBorderColorSet = true; };
	void SetBackgroundDisableColour( wxColor color ) { bgDisableColor = color; };
	void SetForegroundDisableColour( wxColor color ) { fgDisableColor = color; };

	void ConnectMouseEvent( int eventType, wxMouseEventFunction func, wxEvtHandler* eventSink ) { Connect( GetId(), eventType, (wxObjectEventFunction)(wxEventFunction)func, NULL, eventSink ); };
	bool DisconnectMouseEvent( int eventType, wxMouseEventFunction func, wxEvtHandler* eventSink ) { return Disconnect( GetId(), eventType, (wxObjectEventFunction)(wxEventFunction)func, NULL, eventSink ); };

	void ConnectKeyEvent( int eventType, wxCharEventFunction func, wxEvtHandler* eventSink ) { Connect( GetId(), eventType, (wxObjectEventFunction)(wxEventFunction)func, NULL, eventSink ); };
	bool DisconnectKeyEvent( int eventType, wxCharEventFunction func, wxEvtHandler* eventSink ) { return Disconnect( GetId(), eventType, (wxObjectEventFunction)(wxEventFunction)func, NULL, eventSink ); };

private:
	void OnPaint( wxPaintEvent& e );
	void OnEraseBackground( wxEraseEvent& event );
	void OnSize( wxSizeEvent& e );

	wxString text;

	wxColor bgBorderColor;
	bool isBorderColorSet;

	wxColor bgDisableColor;
	wxColor fgDisableColor;
};

#endif //__WXPANELPLUS_H

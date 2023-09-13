//---------------------------------------------------------------------------
//
// Name:        wxPanelPlus.cpp
// Author:      Gabriel Ferri
// Created:     17/11/2010
// Description: wxPanelPlus class implementation
//
//---------------------------------------------------------------------------

#include "wxPanelPlus.h"
#include <wx/settings.h>
#include <wx/dcbuffer.h>

#define BORDER_VALUE		0.6f


//----------------------------------------------------------------------------------
// wxPanelPlus
// 
//----------------------------------------------------------------------------------
wxPanelPlus::wxPanelPlus( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size )
	: wxPanel( parent, id, pos, size )
{
	SetBackgroundStyle( wxBG_STYLE_CUSTOM );

	Connect( GetId(), wxEVT_PAINT, wxPaintEventHandler( wxPanelPlus::OnPaint ), NULL, this );
	Connect( GetId(), wxEVT_ERASE_BACKGROUND,wxEraseEventHandler( wxPanelPlus::OnEraseBackground ), NULL, this );
	Connect( GetId(), wxEVT_SIZE, wxSizeEventHandler( wxPanelPlus::OnSize ), NULL, this );

	bgBorderColor = wxColor( 0, 0, 0 ); // BLACK
	isBorderColorSet = false;

	bgDisableColor = GetBackgroundColour();
	fgDisableColor = GetForegroundColour();
}

//----------------------------------------------------------------------------------
// OnPaint
//----------------------------------------------------------------------------------
void wxPanelPlus::OnPaint( wxPaintEvent& e )
{
	wxAutoBufferedPaintDC dc( this );
	// background color
	dc.SetBrush( IsEnabled() ? GetBackgroundColour() : bgDisableColor );
	// border color
	if( isBorderColorSet )
		dc.SetPen( wxPen( bgBorderColor ) );
	else
		dc.SetPen( wxPen( wxColor( dc.GetBrush().GetColour().Red() * BORDER_VALUE, dc.GetBrush().GetColour().Green() * BORDER_VALUE, dc.GetBrush().GetColour().Blue() * BORDER_VALUE ) ) );
	// draw control
	dc.DrawRectangle( 0, 0, GetClientSize().x, GetClientSize().y );

	if( !text.IsEmpty() )
	{
		dc.SetTextForeground( IsEnabled() ? GetForegroundColour() : fgDisableColor );
		dc.SetFont( GetFont() );

		int w, h;
		dc.GetTextExtent( text, &w, &h );

		int posX = (GetClientSize().x - w) / 2;
		int posY = (GetClientSize().y - h) / 2;
		dc.DrawText( text, posX, posY );
	}
}

//----------------------------------------------------------------------------------
// OnEraseBackground
//----------------------------------------------------------------------------------
void wxPanelPlus::OnEraseBackground( wxEraseEvent& event )
{
}

//----------------------------------------------------------------------------------
// OnSize
//----------------------------------------------------------------------------------
void wxPanelPlus::OnSize( wxSizeEvent& e )
{
	Refresh();
}

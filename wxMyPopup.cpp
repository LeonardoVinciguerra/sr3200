//---------------------------------------------------------------------------
//
// Name:        wxMyPopup.cpp
// Author:      Gabriel Ferri
// Created:     15/12/2010
// Description: wxMyPopup class implementation
//
//---------------------------------------------------------------------------

#include "wxMyPopup.h"
#include <wx/frame.h>
#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/stattext.h>


// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(wxMyPopup, wxDialog)
	EVT_LEFT_DOWN(wxMyPopup::OnLeftDown)
	EVT_LEFT_UP(wxMyPopup::OnLeftUp)
	EVT_MOTION(wxMyPopup::OnMouseMove)
	EVT_PAINT(wxMyPopup::OnPaint)
	EVT_SIZE(wxMyPopup::OnSize)

#ifdef __WXGTK__
	EVT_WINDOW_CREATE(wxMyPopup::OnWindowCreate)
#endif
END_EVENT_TABLE()


// frame constructor
wxMyPopup::wxMyPopup( wxWindow* parent, wxWindowID id )
: wxDialog( parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 | wxFRAME_SHAPED | wxSIMPLE_BORDER | wxFRAME_NO_TASKBAR | wxSTAY_ON_TOP )
{
	double_buffer = new wxBitmap( GetClientSize().x, GetClientSize().y );
	isDragEnable = false;

	arrow_height = 10;
	arrow_position = wxDefaultPosition;

	wxBoxSizer* sizerMain = new wxBoxSizer(wxHORIZONTAL);
	sizerClient = new wxBoxSizer(wxHORIZONTAL);
	sizerMain->Add( sizerClient, 0, wxTOP, arrow_height );

	SetSizer( sizerMain );
	sizerMain->Fit( this );
	sizerMain->SetSizeHints( this );

	arrow_pos_x = GetClientSize().x - ARROW_DELTAX;

	SetPosition( wxPoint( arrow_position.x - GetClientSize().x / 2 - 1, arrow_position.y ) );

#ifndef __WXGTK__
	// On wxGTK we can't do this yet because the window hasn't been created
	// yet so we wait until the EVT_WINDOW_CREATE event happens.  On wxMSW and
	// wxMac the window has been created at this point so we go ahead and set
	// the shape now.
	SetWindowShape();
#endif
}

wxMyPopup::~wxMyPopup()
{
	delete double_buffer;
}

void wxMyPopup::SetArrowPosition( const wxPoint& position )
{
	arrow_position = position;
	SetPosition( wxPoint( arrow_position.x - arrow_pos_x - GetClientSize().x, arrow_position.y ) );
}

void wxMyPopup::SetChild( wxWindow* child )
{
	sizerClient->Add( child, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	sizerClient->Layout();

	wxSizer* sizer = GetSizer();
	sizer->Layout();
	sizer->Fit( this );
	sizer->SetSizeHints( this );

	SetPosition( wxPoint( arrow_position.x - GetClientSize().x / 2 - 1, arrow_position.y ) );
}

void wxMyPopup::SetWindowShape()
{
	wxRegion region( *double_buffer, *wxRED );
	SetShape(region);
}


	//------------//
	//   Events   //
	//------------//

void wxMyPopup::OnLeftDown(wxMouseEvent& evt)
{
	if( isDragEnable )
	{
		CaptureMouse();
		wxPoint pos = ClientToScreen(evt.GetPosition());
		wxPoint origin = GetPosition();
		int dx =  pos.x - origin.x;
		int dy = pos.y - origin.y;
		m_delta = wxPoint(dx, dy);
	}
}

void wxMyPopup::OnLeftUp(wxMouseEvent& WXUNUSED(evt))
{
	if( HasCapture() )
	{
		ReleaseMouse();
	}
}

void wxMyPopup::OnMouseMove(wxMouseEvent& evt)
{
	if( isDragEnable )
	{
		if( evt.Dragging() && evt.LeftIsDown() )
		{
			wxPoint pos = ClientToScreen( evt.GetPosition() );
			Move(wxPoint(pos.x - m_delta.x, pos.y - m_delta.y));
		}
	}
}

void wxMyPopup::OnPaint( wxPaintEvent& WXUNUSED(evt))
{
	wxPaintDC dc( this );
	dc.SetBackground( *wxTRANSPARENT_BRUSH );
	dc.Clear();
	dc.DrawBitmap( *double_buffer, 0, 0, true );
}

void wxMyPopup::OnSize( wxSizeEvent& WXUNUSED(evt) )
{
	if( GetClientSize().x != double_buffer->GetWidth() || GetClientSize().y != double_buffer->GetHeight() )
	{
		if( GetClientSize().x > 0 && GetClientSize().y > 0 )
		{
			delete double_buffer;
			double_buffer = new wxBitmap( GetClientSize().x, GetClientSize().y );

			wxMemoryDC dc;
			dc.SelectObject( *double_buffer );
			dc.SetBackground( *wxRED );
			dc.Clear();
			dc.SetBrush( *wxWHITE );
			dc.SetPen( *wxBLACK );
			// draw rounded rectangle
			dc.DrawRoundedRectangle( 0, arrow_height, GetClientSize().x, GetClientSize().y - arrow_height, 8 );
			// draw arrow
			if( arrow_height > 3 )
			{
				arrow_pos_x = GetClientSize().x - ARROW_DELTAX;
				dc.DrawLine( arrow_pos_x, 0, arrow_pos_x - arrow_height, arrow_height );
				dc.DrawLine( arrow_pos_x, 0, arrow_pos_x + arrow_height, arrow_height );
				dc.SetPen( *wxWHITE );
				dc.DrawLine( arrow_pos_x - arrow_height + 1, arrow_height, arrow_pos_x + arrow_height, arrow_height );
				dc.FloodFill( arrow_pos_x, arrow_height - 1, *wxRED );
			}
			dc.SelectObject( wxNullBitmap );

			SetWindowShape();
		}
		Refresh();
	}
}

void wxMyPopup::OnWindowCreate(wxWindowCreateEvent& WXUNUSED(evt))
{
	SetWindowShape();
}


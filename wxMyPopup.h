//---------------------------------------------------------------------------
//
// Name:        wxMyPopup.h
// Author:      Gabriel Ferri
// Created:     15/12/2010
// Description: wxMyPopup class declaration
//
//---------------------------------------------------------------------------
#ifndef __WXMYPOPUP_H
#define __WXMYPOPUP_H

#include <wx/dialog.h>
#include <wx/bitmap.h>
#include <wx/sizer.h>

#define		ARROW_DELTAX	140

// Define a new frame type: this is going to be our main frame
class wxMyPopup : public wxDialog
{
public:
	// ctor(s)
	wxMyPopup( wxWindow* parent, wxWindowID id );
	~wxMyPopup();

	void SetArrowPosition( const wxPoint& position );
	void SetChild( wxWindow* child );

	// event handlers (these functions should _not_ be virtual)
	void OnLeftDown( wxMouseEvent& evt );
	void OnLeftUp( wxMouseEvent& evt );
	void OnMouseMove( wxMouseEvent& evt );
	void OnPaint( wxPaintEvent& evt );
	void OnSize( wxSizeEvent& evt );
	void OnWindowCreate( wxWindowCreateEvent& evt );

private:
	wxBitmap* double_buffer;
	unsigned short arrow_height;
	wxPoint arrow_position;

	wxBoxSizer* sizerClient;

	bool isDragEnable;
	wxPoint m_delta;

	int arrow_pos_x;

	void SetWindowShape();

	DECLARE_EVENT_TABLE()
};


#endif // __WXMYPOPUP_H

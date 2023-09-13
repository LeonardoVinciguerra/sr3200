//---------------------------------------------------------------------------
//
// Name:        wxPictureBox.cpp
// Author:      Gabriel Ferri
// Created:     13/05/2008
// Description: wxPictureBox class implementation
//
//---------------------------------------------------------------------------

#include "wxPictureBox.h"
#include <wx/rawbmp.h>
#include <iostream>

//----------------------------------------------------------------------------------
// wxPictureBox
// 
//----------------------------------------------------------------------------------
wxPictureBox::wxPictureBox( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size )
	: wxPanel( parent, id, pos, size, wxBORDER_SUNKEN | wxWANTS_CHARS )
{
	SetBackgroundStyle( wxBG_STYLE_CUSTOM );

	image = wxNullBitmap;

	Connect( GetId(), wxEVT_PAINT, wxPaintEventHandler( wxPictureBox::OnPaint ), NULL, this );
	Connect( GetId(), wxEVT_SIZE, wxSizeEventHandler( wxPictureBox::OnSize ), NULL, this );

	border_sunken_width = ( GetSize().x - GetClientSize().x ) / 2;
	displacement = 0;
}

//----------------------------------------------------------------------------------
// OnPaint
// 
//----------------------------------------------------------------------------------
void wxPictureBox::OnPaint( wxPaintEvent& e )
{
	wxAutoBufferedPaintDC doublebufDC( this );
	doublebufDC.DrawBitmap( image, -(border_sunken_width + displacement), -(border_sunken_width + displacement) );
}

//----------------------------------------------------------------------------------
// OnSize
// 
//----------------------------------------------------------------------------------
void wxPictureBox::OnSize( wxSizeEvent& e )
{
	Refresh();
}

//----------------------------------------------------------------------------------
// SetImage
// Show the image on the control
//----------------------------------------------------------------------------------
void wxPictureBox::SetImage( const wxBitmap& img )
{
	image = img;
	Refresh();
}

//----------------------------------------------------------------------------------
// ScreenToImage
// Converts from screen to image coordinates
//----------------------------------------------------------------------------------
wxPoint wxPictureBox::ScreenToImage( const wxPoint& pt )
{
	return ScreenToClient( pt ) + wxPoint( border_sunken_width + displacement, border_sunken_width + displacement );
}

wxColour wxPictureBox::GetPixelColour(int x, int y)
{
	wxBitmap temp;
   wxColour c;
   std::cout<<"coord received at :"<<x<< "  "<<y <<std::endl;
   temp = image.GetSubBitmap(wxRect(x, y, 1, 1));

   wxImage img;
   img = temp.ConvertToImage();

   c.Set(img.GetRed(0,0), img.GetGreen(0,0), img.GetBlue(0,0), img.GetAlpha(0,0));
   //std::cout<<(int)c.Red()<< "  "<< (int)c.Green() << " "<< (int)c.Blue()<<std::endl;
   return c;
}


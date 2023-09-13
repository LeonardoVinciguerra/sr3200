#include "wxAuxVideo.h"

//(*InternalHeaders(wxAuxVideo)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxAuxVideo)
const long wxAuxVideo::ID_CUSTOM1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxAuxVideo,wxPanel)
	//(*EventTable(wxAuxVideo)
	//*)
END_EVENT_TABLE()

wxAuxVideo::wxAuxVideo(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxAuxVideo)
	wxBoxSizer* BoxSizer1;
	
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	SetBackgroundColour(wxColour(192,192,192));
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	videoAux = new wxPictureBox(this,ID_CUSTOM1,wxDefaultPosition,wxSize(480,360));
	BoxSizer1->Add(videoAux, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	//*)
}

wxAuxVideo::~wxAuxVideo()
{
	//(*Destroy(wxAuxVideo)
	//*)
}

//----------------------------------------------------------------------------------
// SetImage
// Show the image on the control
//----------------------------------------------------------------------------------
void wxAuxVideo::SetImage( const wxBitmap& img )
{
	videoAux->SetImage( img );
}

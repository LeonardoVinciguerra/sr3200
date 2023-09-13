#include "images/png_images.h"

#include "wxMainVideo.h"

//(*InternalHeaders(wxMainVideo)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/msgdlg.h>
#include "Messages.h"

#define DIRTY_BORDER				5

//(*IdInit(wxMainVideo)
const long wxMainVideo::ID_CUSTOM1 = wxNewId();
const long wxMainVideo::ID_STATICTEXT8 = wxNewId();
const long wxMainVideo::ID_SliderBrightness = wxNewId();
const long wxMainVideo::ID_STATICTEXT9 = wxNewId();
const long wxMainVideo::ID_STATICTEXT10 = wxNewId();
const long wxMainVideo::ID_STATICLINE2 = wxNewId();
const long wxMainVideo::ID_STATICTEXT11 = wxNewId();
const long wxMainVideo::ID_SliderContrast = wxNewId();
const long wxMainVideo::ID_STATICTEXT12 = wxNewId();
const long wxMainVideo::ID_STATICTEXT13 = wxNewId();
const long wxMainVideo::ID_PANEL2 = wxNewId();
const long wxMainVideo::ID_BITMAPBUTTON1 = wxNewId();
const long wxMainVideo::ID_STATICLINE1 = wxNewId();
const long wxMainVideo::ID_STATICTEXT7 = wxNewId();
const long wxMainVideo::ID_TEXTCTRL1 = wxNewId();
const long wxMainVideo::ID_TEXTCTRL2 = wxNewId();
//*)

const long wxMainVideo::ID_EVENT = wxNewId();
const long wxMainVideo::CHANGE_SPI_PREVIEW = wxNewId();

BEGIN_EVENT_TABLE(wxMainVideo,wxPanel)
	//(*EventTable(wxMainVideo)
	//*)
END_EVENT_TABLE()

wxMainVideo::wxMainVideo(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxMainVideo)
	wxBoxSizer* BoxSizer10;
	wxBoxSizer* BoxSizer8;
	wxBoxSizer* BoxSizer13;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer11;
	wxBoxSizer* BoxSizer12;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer9;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	SetBackgroundColour(wxColour(192,192,192));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	videoMain = new wxPictureBox(this,ID_CUSTOM1,wxDefaultPosition,wxSize(630,470));
	BoxSizer1->Add(videoMain, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	videoControlSizer = new wxBoxSizer(wxHORIZONTAL);
	Panel2 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	Panel2->SetBackgroundColour(wxColour(128,128,128));
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
	StaticText8 = new wxStaticText(Panel2, ID_STATICTEXT8, _("0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	BoxSizer11->Add(StaticText8, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	brightnessSlider = new wxSlider(Panel2, ID_SliderBrightness, 0, 0, 100, wxDefaultPosition, wxSize(150,21), wxSL_HORIZONTAL|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SliderBrightness"));
	BoxSizer11->Add(brightnessSlider, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	StaticText9 = new wxStaticText(Panel2, ID_STATICTEXT9, _("100"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	BoxSizer11->Add(StaticText9, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer10->Add(BoxSizer11, 0, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	StaticText10 = new wxStaticText(Panel2, ID_STATICTEXT10, _("Brightness"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	BoxSizer10->Add(StaticText10, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer2->Add(BoxSizer10, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine2 = new wxStaticLine(Panel2, ID_STATICLINE2, wxDefaultPosition, wxSize(-1,-1), wxLI_VERTICAL, _T("ID_STATICLINE2"));
	BoxSizer2->Add(StaticLine2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
	StaticText11 = new wxStaticText(Panel2, ID_STATICTEXT11, _("0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	BoxSizer13->Add(StaticText11, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	contrastSlider = new wxSlider(Panel2, ID_SliderContrast, 0, 0, 100, wxDefaultPosition, wxSize(150,21), wxSL_HORIZONTAL|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SliderContrast"));
	BoxSizer13->Add(contrastSlider, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	StaticText12 = new wxStaticText(Panel2, ID_STATICTEXT12, _("100"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	BoxSizer13->Add(StaticText12, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer12->Add(BoxSizer13, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	StaticText13 = new wxStaticText(Panel2, ID_STATICTEXT13, _("Contrast"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	BoxSizer12->Add(StaticText13, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer2->Add(BoxSizer12, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2->SetSizer(BoxSizer2);
	BoxSizer2->Fit(Panel2);
	BoxSizer2->SetSizeHints(Panel2);
	videoControlSizer->Add(Panel2, 0, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	videoControlSizer->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	auxVideoBtn = new wxBitmapButton(this, ID_BITMAPBUTTON1, wxNullBitmap, wxDefaultPosition, wxSize(34,34), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	auxVideoBtn->SetDefault();
	videoControlSizer->Add(auxVideoBtn, 0, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(videoControlSizer, 0, wxTOP|wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	BoxSizer1->Add(StaticLine1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer8 = new wxBoxSizer(wxVERTICAL);
	BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Current production"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	BoxSizer9->Add(StaticText7, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	productionNameEdit = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(200,19), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer9->Add(productionNameEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer8->Add(BoxSizer9, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	infoEdit = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	infoEdit->Hide();
	BoxSizer8->Add(infoEdit, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer8, 0, wxTOP|wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_SliderBrightness,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxMainVideo::OnbrightnessSliderCmdScroll);
	Connect(ID_SliderBrightness,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxMainVideo::OnbrightnessSliderCmdScroll);
	Connect(ID_SliderBrightness,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxMainVideo::OnbrightnessSliderCmdScroll);
	Connect(ID_SliderBrightness,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxMainVideo::OnbrightnessSliderCmdScroll);
	Connect(ID_SliderBrightness,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxMainVideo::OnbrightnessSliderCmdScroll);
	Connect(ID_SliderBrightness,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxMainVideo::OnbrightnessSliderCmdScroll);
	Connect(ID_SliderBrightness,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxMainVideo::OnbrightnessSliderCmdScroll);
	Connect(ID_SliderBrightness,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxMainVideo::OnbrightnessSliderCmdScroll);
	Connect(ID_SliderBrightness,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&wxMainVideo::OnbrightnessSliderCmdScroll);
	Connect(ID_SliderContrast,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&wxMainVideo::OncontrastSliderCmdScroll);
	Connect(ID_SliderContrast,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxMainVideo::OncontrastSliderCmdScroll);
	Connect(ID_SliderContrast,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxMainVideo::OncontrastSliderCmdScroll);
	Connect(ID_SliderContrast,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxMainVideo::OncontrastSliderCmdScroll);
	Connect(ID_SliderContrast,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxMainVideo::OncontrastSliderCmdScroll);
	Connect(ID_SliderContrast,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxMainVideo::OncontrastSliderCmdScroll);
	Connect(ID_SliderContrast,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxMainVideo::OncontrastSliderCmdScroll);
	Connect(ID_SliderContrast,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxMainVideo::OncontrastSliderCmdScroll);
	Connect(ID_SliderContrast,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxMainVideo::OncontrastSliderCmdScroll);
	Connect(ID_SliderContrast,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&wxMainVideo::OncontrastSliderCmdScroll);
	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainVideo::OnauxVideoBtnClick);
	//*)

	// init buttons image
	auxVideoBtn->SetBitmapDisabled( wxMEMORY_BITMAP( aux_small ) );
	auxVideoBtn->SetBitmapLabel( wxMEMORY_BITMAP( aux_small_on ) );

	// Setup controls and vars
	auxVideoBtn->SetToolTip( TOO_AUXVIDEO );
}

wxMainVideo::~wxMainVideo()
{
	//(*Destroy(wxMainVideo)
	//*)
}


//----------------------------------------------------------------------------------
// Init
// Inizializza il controllo
//----------------------------------------------------------------------------------
int wxMainVideo::Init( SRMachine* SRRef, wxAuxVideo *auxVideoRef, wxCameraControl *cameraRef )
{
	SR = SRRef;
	videoAux = auxVideoRef;
	camera = cameraRef;

	videoMain->SetImageDisplacement( DIRTY_BORDER );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// ShowControl
//
//----------------------------------------------------------------------------------
int wxMainVideo::ShowControl()
{
	UpdateControl();

	return SR_OK;
}

//----------------------------------------------------------------------------------
// HideControl
//
//----------------------------------------------------------------------------------
int wxMainVideo::HideControl()
{
	// save camera brightness and contrast
	SR->DB->SaveProductionData();

	return SR_OK;
}

//----------------------------------------------------------------------------------
// UpdateControl
//
//----------------------------------------------------------------------------------
int wxMainVideo::UpdateControl()
{
	#ifndef __WXMSW__
		// set camera brightness and contrast
		camera->SetBrightness( SR->DB->pCurrentFiducial->CameraBrightness * 65535 );
		camera->SetContrast( SR->DB->pCurrentFiducial->CameraContrast * 65535 );

		brightnessSlider->SetValue( SR->DB->pCurrentFiducial->CameraBrightness * 100 );
		contrastSlider->SetValue( SR->DB->pCurrentFiducial->CameraContrast * 100 );
	#endif

	return SR_OK;
}

void wxMainVideo::OnbrightnessSliderCmdScroll(wxScrollEvent& event)
{
	#ifndef __WXMSW__
		SR->DB->pCurrentFiducial->CameraBrightness = event.GetPosition() / 100.0;
		SR->DB->CameraZeroParamsS.CameraBrightness = event.GetPosition() / 100.0;

		camera->SetBrightness( event.GetPosition() / 100.0 * 65535 );
	#endif
}

void wxMainVideo::OncontrastSliderCmdScroll(wxScrollEvent& event)
{
	#ifndef __WXMSW__
		SR->DB->pCurrentFiducial->CameraContrast = event.GetPosition() / 100.0;
		SR->DB->CameraZeroParamsS.CameraContrast = event.GetPosition() / 100.0;

		camera->SetContrast( event.GetPosition() / 100.0 * 65535 );
	#endif
}

void wxMainVideo::OnauxVideoBtnClick(wxCommandEvent& event)
{
	AuxVideoModeEnum mode = camera->GetAuxMode();
	camera->SetAuxMode( mode == AUX_CAMPOSITION ? AUX_SMOOTH_EDGE : AUX_CAMPOSITION );

	//wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
	//e.SetId( ID_EVENT );
	//e.SetInt( CHANGE_SPI_PREVIEW );
	//GetParent()->GetEventHandler()->AddPendingEvent( e );
}

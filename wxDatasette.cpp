#include "images/png_images.h"

#include "wxDatasette.h"

//(*InternalHeaders(wxDatasette)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "GlobalDefs.h"

const long wxDatasette::ID_START_BUTTON = wxNewId();
const long wxDatasette::ID_STOP_BUTTON = wxNewId();
const long wxDatasette::ID_NEXT_BUTTON = wxNewId();
const long wxDatasette::ID_PREV_BUTTON = wxNewId();
const long wxDatasette::ID_PAUSE_BUTTON = wxNewId();

//(*IdInit(wxDatasette)
const long wxDatasette::ID_BITMAPBUTTON1 = wxNewId();
const long wxDatasette::ID_BITMAPBUTTON2 = wxNewId();
const long wxDatasette::ID_BITMAPBUTTON3 = wxNewId();
const long wxDatasette::ID_BITMAPBUTTON5 = wxNewId();
const long wxDatasette::ID_BITMAPBUTTON4 = wxNewId();
const long wxDatasette::ID_STATICTEXT6 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxDatasette,wxPanel)
	//(*EventTable(wxDatasette)
	//*)
END_EVENT_TABLE()

wxDatasette::wxDatasette(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxDatasette)
	wxBoxSizer* BoxSizer1;
	
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	SetBackgroundColour(wxColour(192,192,192));
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	prevBtn = new wxBitmapButton(this, ID_BITMAPBUTTON1, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	prevBtn->SetDefault();
	BoxSizer1->Add(prevBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	startBtn = new wxBitmapButton(this, ID_BITMAPBUTTON2, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
	startBtn->SetDefault();
	BoxSizer1->Add(startBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	stopBtn = new wxBitmapButton(this, ID_BITMAPBUTTON3, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
	stopBtn->SetDefault();
	BoxSizer1->Add(stopBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	pauseBtn = new wxBitmapButton(this, ID_BITMAPBUTTON5, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON5"));
	pauseBtn->SetDefault();
	pauseBtn->Disable();
	BoxSizer1->Add(pauseBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	nextBtn = new wxBitmapButton(this, ID_BITMAPBUTTON4, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON4"));
	nextBtn->SetDefault();
	BoxSizer1->Add(nextBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	BoxSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	funcName = new wxStaticText(this, ID_STATICTEXT6, _("SR3200"), wxDefaultPosition, wxSize(-1,-1), 0, _T("ID_STATICTEXT6"));
	wxFont funcNameFont(14,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Franklin Gothic Medium"),wxFONTENCODING_DEFAULT);
	funcName->SetFont(funcNameFont);
	BoxSizer1->Add(funcName, 0, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	
	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxDatasette::OnprevBtnClick);
	Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxDatasette::OnstartBtnClick);
	Connect(ID_BITMAPBUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxDatasette::OnstopBtnClick);
	Connect(ID_BITMAPBUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxDatasette::OnpauseBtnClick);
	Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxDatasette::OnnextBtnClick);
	//*)


	// init buttons image
	prevBtn->SetBitmapDisabled( wxMEMORY_BITMAP( rwd ) );
	prevBtn->SetBitmapLabel( wxMEMORY_BITMAP( rwd_on ) );
	startBtn->SetBitmapDisabled( wxMEMORY_BITMAP( play ) );
	startBtn->SetBitmapLabel( wxMEMORY_BITMAP( play_on ) );
	stopBtn->SetBitmapDisabled( wxMEMORY_BITMAP( stop ) );
	stopBtn->SetBitmapLabel( wxMEMORY_BITMAP( stop_on ) );
	pauseBtn->SetBitmapDisabled( wxMEMORY_BITMAP( pause_off ) );
	pauseBtn->SetBitmapLabel( wxMEMORY_BITMAP( pause_on ) );
	nextBtn->SetBitmapDisabled( wxMEMORY_BITMAP( ffw ) );
	nextBtn->SetBitmapLabel( wxMEMORY_BITMAP( ffw_on ) );
}

wxDatasette::~wxDatasette()
{
	//(*Destroy(wxDatasette)
	//*)
}


//----------------------------------------------------------------------------------
// Init
// Inizializza il controllo
//----------------------------------------------------------------------------------
int wxDatasette::Init()
{
	return SR_OK;
}

void wxDatasette::OnstartBtnClick(wxCommandEvent& event)
{
	wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
	e.SetId( ID_START_BUTTON );
	GetParent()->GetEventHandler()->AddPendingEvent( e );
}

void wxDatasette::OnprevBtnClick(wxCommandEvent& event)
{
	wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
	e.SetId( ID_PREV_BUTTON );
	GetParent()->GetEventHandler()->AddPendingEvent( e );
}

void wxDatasette::OnnextBtnClick(wxCommandEvent& event)
{
	wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
	e.SetId( ID_NEXT_BUTTON );
	GetParent()->GetEventHandler()->AddPendingEvent( e );
}

void wxDatasette::OnstopBtnClick(wxCommandEvent& event)
{
	wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
	e.SetId( ID_STOP_BUTTON );
	GetParent()->GetEventHandler()->AddPendingEvent( e );
}

void wxDatasette::OnpauseBtnClick(wxCommandEvent& event)
{
	wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
	e.SetId( ID_PAUSE_BUTTON );
	GetParent()->GetEventHandler()->AddPendingEvent( e );
}

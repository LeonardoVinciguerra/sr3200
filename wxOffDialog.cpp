#include "images/png_images.h"

#include "wxOffDialog.h"

//(*InternalHeaders(wxOffDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "Messages.h"

//(*IdInit(wxOffDialog)
const long wxOffDialog::ID_STATICTEXT3 = wxNewId();
const long wxOffDialog::ID_PANEL1 = wxNewId();
const long wxOffDialog::ID_PANEL2 = wxNewId();
const long wxOffDialog::ID_PANEL3 = wxNewId();
const long wxOffDialog::ID_BITMAPBUTTON1 = wxNewId();
const long wxOffDialog::ID_STATICTEXT1 = wxNewId();
const long wxOffDialog::ID_BITMAPBUTTON2 = wxNewId();
const long wxOffDialog::ID_STATICTEXT2 = wxNewId();
const long wxOffDialog::ID_BUTTON1 = wxNewId();
const long wxOffDialog::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxOffDialog,wxDialog)
	//(*EventTable(wxOffDialog)
	//*)
END_EVENT_TABLE()

wxOffDialog::wxOffDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxOffDialog)
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer6;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;
	
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(20,41), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	Panel1->SetBackgroundColour(wxColour(0,255,0));
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("SR3200"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	StaticText3->SetForegroundColour(wxColour(255,255,255));
	wxFont StaticText3Font(16,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Franklin Gothic Medium"),wxFONTENCODING_DEFAULT);
	StaticText3->SetFont(StaticText3Font);
	BoxSizer7->Add(StaticText3, 0, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 20);
	Panel1->SetSizer(BoxSizer7);
	BoxSizer7->SetSizeHints(Panel1);
	BoxSizer2->Add(Panel1, 100, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	Panel2 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxSize(100,41), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	Panel2->SetBackgroundColour(wxColour(255,255,255));
	BoxSizer2->Add(Panel2, 50, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	Panel3 = new wxPanel(this, ID_PANEL3, wxDefaultPosition, wxSize(20,41), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	Panel3->SetBackgroundColour(wxColour(255,0,0));
	BoxSizer2->Add(Panel3, 25, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer1->Add(BoxSizer2, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer3->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer5 = new wxBoxSizer(wxVERTICAL);
	standbyBtn = new wxBitmapButton(this, ID_BITMAPBUTTON1, wxNullBitmap, wxDefaultPosition, wxSize(64,64), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	standbyBtn->SetDefault();
	BoxSizer5->Add(standbyBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Standby"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(10,wxSWISS,wxFONTSTYLE_ITALIC,wxBOLD,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	BoxSizer5->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(BoxSizer5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer6 = new wxBoxSizer(wxVERTICAL);
	shutdownBtn = new wxBitmapButton(this, ID_BITMAPBUTTON2, wxNullBitmap, wxDefaultPosition, wxSize(64,64), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
	shutdownBtn->SetDefault();
	BoxSizer6->Add(shutdownBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Shutdown"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	wxFont StaticText2Font(10,wxSWISS,wxFONTSTYLE_ITALIC,wxBOLD,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	BoxSizer6->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(BoxSizer6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 15);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	exitBtn = new wxButton(this, ID_BUTTON1, _("Exit"), wxDefaultPosition, wxSize(75,25), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer4->Add(exitBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cancelBtn = new wxButton(this, ID_BUTTON2, _("Cancel"), wxDefaultPosition, wxSize(75,25), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer4->Add(cancelBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer4, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	
	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxOffDialog::OnstandbyBtnClick);
	Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxOffDialog::OnshutdownBtnClick);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxOffDialog::OnexitBtnClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxOffDialog::OncancelBtnClick);
	//*)

	// init buttons image
	shutdownBtn->SetBitmapLabel( wxMEMORY_BITMAP( off_big ) );
	standbyBtn->SetBitmapLabel( wxMEMORY_BITMAP( standby_big ) );
	standbyBtn->SetBitmapDisabled( wxMEMORY_BITMAP( standby_big_off ) );

	// Tooltips
	standbyBtn->SetToolTip( TOO_STANDBY );
	shutdownBtn->SetToolTip( TOO_SHUTDOWN );
	Center();
}

wxOffDialog::~wxOffDialog()
{
	//(*Destroy(wxOffDialog)
	//*)
}

void wxOffDialog::OnexitBtnClick(wxCommandEvent& event)
{
	EndModal( OFFDIALOG_EXIT );
}

void wxOffDialog::OncancelBtnClick(wxCommandEvent& event)
{
	EndModal( OFFDIALOG_CANCEL );
}

void wxOffDialog::OnstandbyBtnClick(wxCommandEvent& event)
{
	EndModal( OFFDIALOG_STANDBY );
}

void wxOffDialog::OnshutdownBtnClick(wxCommandEvent& event)
{
	EndModal( OFFDIALOG_SHUTDOWN );
}

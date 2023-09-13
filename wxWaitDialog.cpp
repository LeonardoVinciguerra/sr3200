#include "wxWaitDialog.h"

//(*InternalHeaders(wxWaitDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxWaitDialog)
const long wxWaitDialog::ID_STATICTEXT3 = wxNewId();
const long wxWaitDialog::ID_PANEL1 = wxNewId();
const long wxWaitDialog::ID_PANEL2 = wxNewId();
const long wxWaitDialog::ID_PANEL3 = wxNewId();
const long wxWaitDialog::ID_STATICTEXT1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxWaitDialog,wxDialog)
	//(*EventTable(wxWaitDialog)
	//*)
END_EVENT_TABLE()

wxWaitDialog::wxWaitDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxWaitDialog)
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;
	
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
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
	BoxSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	messageText = new wxStaticText(this, ID_STATICTEXT1, _("Waiting for..."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont messageTextFont(11,wxSWISS,wxFONTSTYLE_ITALIC,wxBOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	messageText->SetFont(messageTextFont);
	BoxSizer3->Add(messageText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	//*)
}

wxWaitDialog::~wxWaitDialog()
{
	//(*Destroy(wxWaitDialog)
	//*)
}


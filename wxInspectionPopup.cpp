#include "images/png_images.h"

#include "wxInspectionPopup.h"

//(*InternalHeaders(wxInspectionPopup)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/dialog.h>

//(*IdInit(wxInspectionPopup)
const long wxInspectionPopup::ID_STATICTEXT3 = wxNewId();
const long wxInspectionPopup::ID_BITMAPBUTTON12 = wxNewId();
const long wxInspectionPopup::ID_BITMAPBUTTON4 = wxNewId();
const long wxInspectionPopup::ID_BITMAPBUTTON1 = wxNewId();
const long wxInspectionPopup::ID_STATICTEXT2 = wxNewId();
const long wxInspectionPopup::ID_STATICTEXT1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxInspectionPopup,wxPanel)
	//(*EventTable(wxInspectionPopup)
	//*)
END_EVENT_TABLE()

wxInspectionPopup::wxInspectionPopup(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxInspectionPopup)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	SetBackgroundColour(wxColour(255,255,255));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer2->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Inspection"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	wxFont StaticText3Font(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText3->SetFont(StaticText3Font);
	BoxSizer2->Add(StaticText3, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxVERTICAL);
	cancelBtn = new wxBitmapButton(this, ID_BITMAPBUTTON12, wxNullBitmap, wxDefaultPosition, wxSize(24,24), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON12"));
	cancelBtn->SetDefault();
	BoxSizer3->Add(cancelBtn, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(BoxSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	BitmapButton1 = new wxBitmapButton(this, ID_BITMAPBUTTON4, wxNullBitmap, wxDefaultPosition, wxSize(220,160), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON4"));
	FlexGridSizer1->Add(BitmapButton1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BitmapButton2 = new wxBitmapButton(this, ID_BITMAPBUTTON1, wxNullBitmap, wxDefaultPosition, wxSize(220,160), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	FlexGridSizer1->Add(BitmapButton2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT2, _("View Records"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	wxFont StaticText1Font(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	FlexGridSizer1->Add(StaticText1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT1, _("Verify"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText2Font(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	FlexGridSizer1->Add(StaticText2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(FlexGridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BITMAPBUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPopup::OncancelBtnClick);
	Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPopup::OnBitmapButton1Click);
	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPopup::OnBitmapButton2Click);
	//*)

	// init buttons image
	cancelBtn->SetBitmapLabel( wxMEMORY_BITMAP( delete_xsmall_on ) );
	BitmapButton1->SetBitmapLabel( wxMEMORY_BITMAP( results ) );
	BitmapButton2->SetBitmapLabel( wxMEMORY_BITMAP( verify ) );
}

wxInspectionPopup::~wxInspectionPopup()
{
	//(*Destroy(wxInspectionPopup)
	//*)
	/*
	SetSizer(BoxSizer1);
		BoxSizer1->Fit(this);
		BoxSizer1->SetSizeHints(this);*/
}

void wxInspectionPopup::OncancelBtnClick(wxCommandEvent& event)
{
	((wxDialog*)GetParent())->EndModal( wxCANCEL );
}

void wxInspectionPopup::OnBitmapButton1Click(wxCommandEvent& event)
{
	((wxDialog*)GetParent())->EndModal( INSPECTIONPOPUP_TEACHING );
}

void wxInspectionPopup::OnBitmapButton2Click(wxCommandEvent& event)
{
	((wxDialog*)GetParent())->EndModal( INSPECTIONPOPUP_VERIFY );
}
  

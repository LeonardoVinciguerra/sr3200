#include "images/png_images.h"

#include "wxAlignmentTypeDialog.h"

//(*InternalHeaders(wxAlignmentTypeDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "GlobalDefs.h"

//(*IdInit(wxAlignmentTypeDialog)
const long wxAlignmentTypeDialog::ID_STATICTEXT1 = wxNewId();
const long wxAlignmentTypeDialog::ID_BITMAPBUTTON1 = wxNewId();
const long wxAlignmentTypeDialog::ID_BITMAPBUTTON2 = wxNewId();
const long wxAlignmentTypeDialog::ID_STATICTEXT3 = wxNewId();
const long wxAlignmentTypeDialog::ID_STATICTEXT4 = wxNewId();
const long wxAlignmentTypeDialog::ID_PANEL1 = wxNewId();
const long wxAlignmentTypeDialog::ID_STATICTEXT2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxAlignmentTypeDialog,wxDialog)
	//(*EventTable(wxAlignmentTypeDialog)
	//*)
END_EVENT_TABLE()

wxAlignmentTypeDialog::wxAlignmentTypeDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxAlignmentTypeDialog)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Choose the method to use on board alignment:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer1->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	Panel1->SetBackgroundColour(wxColour(192,192,192));
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	templateBtn = new wxBitmapButton(Panel1, ID_BITMAPBUTTON1, wxNullBitmap, wxDefaultPosition, wxSize(110,110), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	FlexGridSizer1->Add(templateBtn, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	vectorialBtn = new wxBitmapButton(Panel1, ID_BITMAPBUTTON2, wxNullBitmap, wxDefaultPosition, wxSize(110,110), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
	vectorialBtn->SetDefault();
	FlexGridSizer1->Add(vectorialBtn, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("Template Matching"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer1->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(Panel1, ID_STATICTEXT4, _("Vectorial"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer1->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(FlexGridSizer1, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel1->SetSizer(BoxSizer2);
	BoxSizer2->Fit(Panel1);
	BoxSizer2->SetSizeHints(Panel1);
	BoxSizer1->Add(Panel1, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	lastUsedLbl = new wxStaticText(this, ID_STATICTEXT2, _("Last time you used:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer1->Add(lastUsedLbl, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	
	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxAlignmentTypeDialog::OntemplateBtnClick);
	Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxAlignmentTypeDialog::OnvectorialBtnClick);
	//*)

	// init buttons image
	templateBtn->SetBitmapLabel( wxMEMORY_BITMAP( template_matching ) );
	vectorialBtn->SetBitmapLabel( wxMEMORY_BITMAP( vectorial_search ) );

	//
	lastUsedLbl->SetLabel( _("Last time you used:") + wxString::Format( " ---" ) );
	vectorialBtn->SetFocus();

	SetTitle( MACHINE_NAME );
	Center();
}

wxAlignmentTypeDialog::~wxAlignmentTypeDialog()
{
	//(*Destroy(wxAlignmentTypeDialog)
	//*)
}

void wxAlignmentTypeDialog::SetLastUsedMethod( int method )
{
	if( method == ALIGNMENTTYPE_VECTORIAL )
	{
		lastUsedLbl->SetLabel( _("Last time you used:") + wxString::Format( " " ) + _("Vectorial") );
		vectorialBtn->SetFocus();
	}
	else
	{
		lastUsedLbl->SetLabel( _("Last time you used:") + wxString::Format( " " ) + _("Template Matching") );
		templateBtn->SetFocus();
	}
	Layout();
}

void wxAlignmentTypeDialog::OntemplateBtnClick(wxCommandEvent& event)
{
	EndModal( ALIGNMENTTYPE_TEMPLATE );
}

void wxAlignmentTypeDialog::OnvectorialBtnClick(wxCommandEvent& event)
{
	EndModal( ALIGNMENTTYPE_VECTORIAL );
}

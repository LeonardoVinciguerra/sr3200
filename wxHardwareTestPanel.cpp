#include "images/png_images.h"

#include "wxHardwareTestPanel.h"

//(*InternalHeaders(wxHardwareTestPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/msgdlg.h>
#include "wxMyTextValidator.h"
#include "GlobalUtils.h"
#include "Messages.h"

const long wxHardwareTestPanel::ID_INPUT_TIMER = wxNewId();

//(*IdInit(wxHardwareTestPanel)
const long wxHardwareTestPanel::ID_BUTTON1 = wxNewId();
const long wxHardwareTestPanel::ID_CHECKBOX1 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT1 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP1 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT2 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP2 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT15 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP15 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT3 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP3 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT4 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP4 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT14 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP14 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT5 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP5 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT6 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP6 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT17 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP17 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT7 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP7 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT8 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP8 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT12 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP12 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT9 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP9 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT11 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP11 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT18 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP18 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT10 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP10 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT19 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP19 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT16 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP16 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT13 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP13 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT20 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP20 = wxNewId();
const long wxHardwareTestPanel::ID_STATICTEXT23 = wxNewId();
const long wxHardwareTestPanel::ID_STATICBITMAP21 = wxNewId();
const long wxHardwareTestPanel::ID_CHECKBOX2 = wxNewId();
const long wxHardwareTestPanel::ID_CHECKBOX3 = wxNewId();
const long wxHardwareTestPanel::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxHardwareTestPanel,wxPanel)
	//(*EventTable(wxHardwareTestPanel)
	//*)
END_EVENT_TABLE()

wxHardwareTestPanel::wxHardwareTestPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxHardwareTestPanel)
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer6;
	wxBoxSizer* BoxSizer15;
	wxBoxSizer* BoxSizer19;
	wxBoxSizer* BoxSizer20;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer10;
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* BoxSizer8;
	wxBoxSizer* BoxSizer21;
	wxBoxSizer* BoxSizer13;
	wxBoxSizer* BoxSizer23;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer11;
	wxBoxSizer* BoxSizer16;
	wxBoxSizer* BoxSizer18;
	wxBoxSizer* BoxSizer12;
	wxBoxSizer* BoxSizer14;
	wxGridSizer* GridSizer1;
	wxBoxSizer* BoxSizer17;
	wxBoxSizer* BoxSizer24;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer9;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxBoxSizer* BoxSizer22;
	wxBoxSizer* BoxSizer3;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer23 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer23->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	table1OnFocus = new wxButton(this, ID_BUTTON1, _("Table On Focus"), wxDefaultPosition, wxSize(150,25), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer23->Add(table1OnFocus, 0, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer23, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	readInputsCheck = new wxCheckBox(this, ID_CHECKBOX1, _("Read Inputs"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	readInputsCheck->SetValue(false);
	BoxSizer1->Add(readInputsCheck, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Inputs"));
	GridSizer1 = new wxGridSizer(0, 3, 0, 0);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Plate zero"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer3->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap1 = new wxStaticBitmap(this, ID_STATICBITMAP1, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP1"));
	BoxSizer3->Add(StaticBitmap1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer3, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Cam. Y up end"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer4->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap2 = new wxStaticBitmap(this, ID_STATICBITMAP2, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP2"));
	BoxSizer4->Add(StaticBitmap2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer4, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer17 = new wxBoxSizer(wxHORIZONTAL);
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _("Loader up/down end"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	BoxSizer17->Add(StaticText15, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap15 = new wxStaticBitmap(this, ID_STATICBITMAP15, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP15"));
	BoxSizer17->Add(StaticBitmap15, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer17, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Loader zero"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	BoxSizer5->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap3 = new wxStaticBitmap(this, ID_STATICBITMAP3, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP3"));
	BoxSizer5->Add(StaticBitmap3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer5, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Cam. Y down end"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	BoxSizer6->Add(StaticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap4 = new wxStaticBitmap(this, ID_STATICBITMAP4, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP4"));
	BoxSizer6->Add(StaticBitmap4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer6, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer16 = new wxBoxSizer(wxHORIZONTAL);
	StaticText14 = new wxStaticText(this, ID_STATICTEXT14, _("Ejetor Zero"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	BoxSizer16->Add(StaticText14, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap14 = new wxStaticBitmap(this, ID_STATICBITMAP14, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP14"));
	BoxSizer16->Add(StaticBitmap14, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer16, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Cam. X axis zero"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	BoxSizer7->Add(StaticText5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap5 = new wxStaticBitmap(this, ID_STATICBITMAP5, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP5"));
	BoxSizer7->Add(StaticBitmap5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer7, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Squeegees up end"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	BoxSizer8->Add(StaticText6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap6 = new wxStaticBitmap(this, ID_STATICBITMAP6, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP6"));
	BoxSizer8->Add(StaticBitmap6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer8, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer19 = new wxBoxSizer(wxHORIZONTAL);
	StaticText17 = new wxStaticText(this, ID_STATICTEXT17, _("Center Conveyor end"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	BoxSizer19->Add(StaticText17, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap17 = new wxStaticBitmap(this, ID_STATICBITMAP17, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP17"));
	BoxSizer19->Add(StaticBitmap17, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer19, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Cam. Y axis zero"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	BoxSizer9->Add(StaticText7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap7 = new wxStaticBitmap(this, ID_STATICBITMAP7, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP7"));
	BoxSizer9->Add(StaticBitmap7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer9, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Squeegees down end"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	BoxSizer10->Add(StaticText8, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap8 = new wxStaticBitmap(this, ID_STATICBITMAP8, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP8"));
	BoxSizer10->Add(StaticBitmap8, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer10, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Input Sensor Ext"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	BoxSizer14->Add(StaticText12, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap12 = new wxStaticBitmap(this, ID_STATICBITMAP12, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP12"));
	BoxSizer14->Add(StaticBitmap12, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer14, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Squeegees zero"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	BoxSizer11->Add(StaticText9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap9 = new wxStaticBitmap(this, ID_STATICBITMAP9, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP9"));
	BoxSizer11->Add(StaticBitmap9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer11, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("Plate up/down end"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	BoxSizer13->Add(StaticText11, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap11 = new wxStaticBitmap(this, ID_STATICBITMAP11, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP11"));
	BoxSizer13->Add(StaticBitmap11, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer13, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer20 = new wxBoxSizer(wxHORIZONTAL);
	StaticText18 = new wxStaticText(this, ID_STATICTEXT18, _("Cover security"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
	BoxSizer20->Add(StaticText18, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap18 = new wxStaticBitmap(this, ID_STATICBITMAP18, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP18"));
	BoxSizer20->Add(StaticBitmap18, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer20, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Left Conveyor zero"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	BoxSizer12->Add(StaticText10, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap10 = new wxStaticBitmap(this, ID_STATICBITMAP10, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP10"));
	BoxSizer12->Add(StaticBitmap10, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer12, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer21 = new wxBoxSizer(wxHORIZONTAL);
	StaticText19 = new wxStaticText(this, ID_STATICTEXT19, _("Cam. X right end"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
	BoxSizer21->Add(StaticText19, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap19 = new wxStaticBitmap(this, ID_STATICBITMAP19, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP19"));
	BoxSizer21->Add(StaticBitmap19, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer21, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer18 = new wxBoxSizer(wxHORIZONTAL);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT16, _("Air pressure"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	BoxSizer18->Add(StaticText16, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap16 = new wxStaticBitmap(this, ID_STATICBITMAP16, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP16"));
	BoxSizer18->Add(StaticBitmap16, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer18, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer15 = new wxBoxSizer(wxHORIZONTAL);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("Center Conveyor zero"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	BoxSizer15->Add(StaticText13, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap13 = new wxStaticBitmap(this, ID_STATICBITMAP13, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP13"));
	BoxSizer15->Add(StaticBitmap13, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer15, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer22 = new wxBoxSizer(wxHORIZONTAL);
	StaticText20 = new wxStaticText(this, ID_STATICTEXT20, _("Cam. X left end"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
	BoxSizer22->Add(StaticText20, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap20 = new wxStaticBitmap(this, ID_STATICBITMAP20, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP20"));
	BoxSizer22->Add(StaticBitmap20, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer22, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer24 = new wxBoxSizer(wxHORIZONTAL);
	StaticText21 = new wxStaticText(this, ID_STATICTEXT23, _("Input Sensor Int"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
	BoxSizer24->Add(StaticText21, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBitmap21 = new wxStaticBitmap(this, ID_STATICBITMAP21, wxNullBitmap, wxDefaultPosition, wxSize(16,16), wxSIMPLE_BORDER, _T("ID_STATICBITMAP21"));
	BoxSizer24->Add(StaticBitmap21, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer24, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(GridSizer1, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	disableLimitsCheck = new wxCheckBox(this, ID_CHECKBOX2, _("Disable Limits"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	disableLimitsCheck->SetValue(false);
	BoxSizer2->Add(disableLimitsCheck, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	safeModeCheck = new wxCheckBox(this, ID_CHECKBOX3, _("Safe Mode"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, wxDefaultValidator, _T("ID_CHECKBOX3"));
	safeModeCheck->SetValue(false);
	BoxSizer2->Add(safeModeCheck, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	inputsTimer.SetOwner(this, ID_TIMER1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxHardwareTestPanel::Ontable1OnFocusClick);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxHardwareTestPanel::OnreadInputsCheckClick);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxHardwareTestPanel::OndisableLimitsCheckClick);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxHardwareTestPanel::OnsafeModeCheckClick);
	Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&wxHardwareTestPanel::OninputsTimerTrigger);
	Connect(wxEVT_PAINT,(wxObjectEventFunction)&wxHardwareTestPanel::OnPaint);
	//*)
}

wxHardwareTestPanel::~wxHardwareTestPanel()
{
	//(*Destroy(wxHardwareTestPanel)
	//*)
}

//----------------------------------------------------------------------------------
// Init
// Inizializza il controllo
//----------------------------------------------------------------------------------
int wxHardwareTestPanel::Init( SRMachine* SRRef, SmartLog* smartLoggerRef, wxControlPanel *controlPanelRef )
{
	SR = SRRef;
	smartLogger = smartLoggerRef;
	controlPanel = controlPanelRef;

	isTimerBusy = false;
	isFirstTime = true;

	StaticBitmap1->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	StaticBitmap2->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	StaticBitmap3->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	StaticBitmap4->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	StaticBitmap5->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	StaticBitmap6->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	StaticBitmap7->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	StaticBitmap8->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	StaticBitmap9->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	//StaticBitmap10->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	StaticBitmap11->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	StaticBitmap12->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	//StaticBitmap13->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	StaticBitmap15->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	StaticBitmap16->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	//StaticBitmap17->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	StaticBitmap18->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	StaticBitmap19->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	StaticBitmap20->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	StaticBitmap21->SetBitmap( wxMEMORY_BITMAP( led_gray ) );

	memset( inputs, 0, sizeof(int)*(NUM_MOTORS+1)*6 );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// ShowControl
//
//----------------------------------------------------------------------------------
int wxHardwareTestPanel::ShowControl()
{
	SR->DB->SetFiducialParams( FIDUCIAL_VISION_TEST );

	readInputsCheck->SetValue( false );
	ResetInputs();

	limitsState = SR->GetLimitsState();
	disableLimitsCheck->SetValue( !limitsState );
	disableLimitsCheck->Enable( limitsState );

	safeModeCheck->Enable( !SR->GetSafeModeState() );
	safeModeCheck->SetValue( SR->GetSafeModeState() );

	controlPanel->axisCombo->Select(0);

	if( isFirstTime )
	{
		isFirstTime = false;
		wxMessageBox( MSG_HWTALERT, MACHINE_NAME, wxOK | wxICON_INFORMATION, GetParent() );
	}

	TransferDataToWindow();

	return SR_OK;
}

//----------------------------------------------------------------------------------
// HideControl
//
//----------------------------------------------------------------------------------
int wxHardwareTestPanel::HideControl()
{
	inputsTimer.Stop();

	SR->ActivateSWLimits( limitsState );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// ResetInputs
//
//----------------------------------------------------------------------------------
void wxHardwareTestPanel::ResetInputs()
{
	memset( inputs, 0, sizeof(int)*(NUM_MOTORS+1)*6 );

	wxPaintEvent e( ID_INPUT_TIMER );
	wxPostEvent( this, e );
}

//----------------------------------------------------------------------------------
// SelectInput
//
//----------------------------------------------------------------------------------
inline int wxHardwareTestPanel::SelectInput( int inputId )
{
	cout<<"Leggo input ID: "<<inputId<<" Value: "<<inputs[SR->DB->IOParamsS[inputId].DriverId-1][SR->DB->IOParamsS[inputId].DriverPort]<< endl;
	return inputs[SR->DB->IOParamsS[inputId].DriverId-1][SR->DB->IOParamsS[inputId].DriverPort];
}

void wxHardwareTestPanel::OnreadInputsCheckClick(wxCommandEvent& event)
{
	if( event.IsChecked() )
		inputsTimer.Start( INPUTTIMERHWT, true );
	else
	{
		inputsTimer.Stop();
		ResetInputs();
	}
}

void wxHardwareTestPanel::OndisableLimitsCheckClick(wxCommandEvent& event)
{
	SR->ActivateSWLimits( !event.IsChecked() );
}

void wxHardwareTestPanel::OnsafeModeCheckClick(wxCommandEvent& event)
{
	if( event.IsChecked() )
	{
		SR->ActivateSafeMode( true );
		safeModeCheck->Enable( false );
	}
}

void wxHardwareTestPanel::OninputsTimerTrigger(wxTimerEvent& event)
{
	if( SR->GetMachineState() == false )
		return;

	if( isTimerBusy )
		return;

	isTimerBusy = true;

	// Lettura di tutti gli ingressi della macchina
	bool isError = false;

	if( SR->GetAllInput( MOTOR_TABLE1_ID, inputs[MOTOR_TABLE1_ID][0], inputs[MOTOR_TABLE1_ID][1], inputs[MOTOR_TABLE1_ID][2] ) == SR_ERROR )
		isError = true;
	if( SR->GetAllInput( MOTOR_PLATE_ID, inputs[MOTOR_PLATE_ID][0], inputs[MOTOR_PLATE_ID][1], inputs[MOTOR_PLATE_ID][2] ) == SR_ERROR )
		isError = true;
	if( SR->GetAllInput( MOTOR_SQUEEGEES_ID, inputs[MOTOR_SQUEEGEES_ID][0], inputs[MOTOR_SQUEEGEES_ID][1], inputs[MOTOR_SQUEEGEES_ID][2] ) == SR_ERROR )
		isError = true;
	if( SR->GetAllInput( MOTOR_CAMERAX_ID, inputs[MOTOR_CAMERAX_ID][0], inputs[MOTOR_CAMERAX_ID][1], inputs[MOTOR_CAMERAX_ID][2] ) == SR_ERROR )
		isError = true;
	if( SR->GetAllInput( MOTOR_CAMERAY_ID, inputs[MOTOR_CAMERAY_ID][0], inputs[MOTOR_CAMERAY_ID][1], inputs[MOTOR_CAMERAY_ID][2] ) == SR_ERROR )
		isError = true;
	if( SR->DB->MachineParamsS.LoaderInstalled )
	{
		if( SR->GetAllInput( MOTOR_LOADER_ID, inputs[MOTOR_LOADER_ID][0], inputs[MOTOR_LOADER_ID][1], inputs[MOTOR_LOADER_ID][2] ) == SR_ERROR )
			isError = true;
	}
	if( SR->GetAllInput( MOTOR_LCONV_WIDTH_ID, inputs[MOTOR_LCONV_WIDTH_ID][0], inputs[MOTOR_LCONV_WIDTH_ID][1], inputs[MOTOR_LCONV_WIDTH_ID][2] ) == SR_ERROR )
		isError = true;
	if( SR->GetAllInput( MOTOR_CCONV_WIDTH_ID, inputs[MOTOR_CCONV_WIDTH_ID][0], inputs[MOTOR_CCONV_WIDTH_ID][1], inputs[MOTOR_CCONV_WIDTH_ID][2] ) == SR_ERROR )
		isError = true;
	if(SR->DB->MachineParamsS.CleaningInstalled){
		if( SR->GetAllInput( MOTOR_CLEANING_ID, inputs[MOTOR_CLEANING_ID][0], inputs[MOTOR_CLEANING_ID][1], inputs[MOTOR_CLEANING_ID][2] ) == SR_ERROR )
			isError = true;
	}

	MACHINE_CONFIG(CONV_PUSH_MOTOR)
		if( SR->GetAllInput( MOTOR_LCONV_PUSH_ID, inputs[MOTOR_LCONV_PUSH_ID][0], inputs[MOTOR_LCONV_PUSH_ID][1], inputs[MOTOR_LCONV_PUSH_ID][2] ) == SR_ERROR )
			isError = true;
	MACHINE_CONFIG_END

	if( isError == true )
		smartLogger->Write( MSG_INPUTSERROR, MSG_ERROR );

	isTimerBusy = false;

	if( readInputsCheck->IsChecked() )
	{
		wxPaintEvent e( ID_INPUT_TIMER );
		wxPostEvent( this, e );

		inputsTimer.Start( INPUTTIMERHWT, true );
	}
	else
		ResetInputs();
}

void wxHardwareTestPanel::OnPaint(wxPaintEvent& event)
{
	// Check if event is raised by inputsTimer
	if( event.GetId() == ID_INPUT_TIMER )
	{
		Freeze();
		StaticBitmap1->SetBitmap( SelectInput( INPUT_PLATEZERO ) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap2->SetBitmap( SelectInput( INPUT_CAMYCCWLIM ) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap3->SetBitmap( SelectInput( INPUT_LOADERZERO ) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap4->SetBitmap( SelectInput( INPUT_CAMYCWLIM ) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap5->SetBitmap( SelectInput( INPUT_CAMXZERO ) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap6->SetBitmap( SelectInput( INPUT_SQUEEGEESCWLIM ) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap7->SetBitmap( SelectInput( INPUT_CAMYZERO ) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap8->SetBitmap( SelectInput( INPUT_SQUEEGEESCCWLIM ) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap9->SetBitmap( SelectInput( INPUT_SQUEEGEESZERO ) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap10->SetBitmap( SelectInput( INPUT_LCONVWZERO ) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap11->SetBitmap( (SelectInput( INPUT_PLATECWLIM )||SelectInput( INPUT_PLATECCWLIM )) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap12->SetBitmap( SelectInput( INPUT_SENSOR_EXT ) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap13->SetBitmap( SelectInput( INPUT_CCONVWZERO ) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap14->SetBitmap( (SelectInput( INPUT_LCONVWCWLIM )||SelectInput( INPUT_LCONVWCCWLIM )) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap15->SetBitmap( (SelectInput( INPUT_LOADERCWLIM )||SelectInput( INPUT_LOADERCCWLIM )) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap16->SetBitmap( SelectInput( INPUT_AIR ) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap17->SetBitmap( (SelectInput( INPUT_CCONVWCWLIM )||SelectInput( INPUT_CCONVWCCWLIM )) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap18->SetBitmap( SelectInput( INPUT_COVER ) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap19->SetBitmap( SelectInput( INPUT_CAMXCWLIM ) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap20->SetBitmap( SelectInput( INPUT_CAMXCCWLIM ) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		//StaticBitmap21->SetBitmap( SelectInput( INPUT_PEDALSTART ) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		StaticBitmap21->SetBitmap( SelectInput( INPUT_SENSOR_INT ) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		//cout<<"Stato del sensore interno: "<<SelectInput( INPUT_SENSOR_INT )<< endl;
		Thaw();
	}
	event.Skip();
}

void wxHardwareTestPanel::Ontable1OnFocusClick(wxCommandEvent& event)
{
	// Check for motors position
	if( SR->CheckMotorsPos() == SR_ERROR )
	{
		if( SR->ResetMotors( MODE_START_POSITION ) == SR_ERROR )
		{
			SR->ErrorManagement();
			return;
		}
	}
	// Move the board to reaches the camera focus
	if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
	{
		smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
		SR->ErrorManagement();
		return;
	}
}

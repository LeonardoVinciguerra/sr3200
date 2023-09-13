#include "images/png_images.h"

#include "wxProductionDataPanel.h"

//(*InternalHeaders(wxProductionDataPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/textdlg.h>
#include <wx/msgdlg.h>
#include "wxMyTextValidator.h"
#include "wxMyComboValidator.h"
#include "GlobalUtils.h"
#include "Messages.h"
#include "wxWaitDialog.h"

#include "wxGerberDialog.h"

enum ProductionDataStateEnum
{
	PRODUCTIONDATA_STATE_SQUEEGEESZERO,
	PRODUCTIONDATA_STATE_SQUEEGEESMOVE
};

//(*IdInit(wxProductionDataPanel)
const long wxProductionDataPanel::ID_STATICTEXT1 = wxNewId();
const long wxProductionDataPanel::ID_COMBOBOX1 = wxNewId();
const long wxProductionDataPanel::ID_BITMAPBUTTON1 = wxNewId();
const long wxProductionDataPanel::ID_BITMAPBUTTON2 = wxNewId();
const long wxProductionDataPanel::ID_BITMAPBUTTON3 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT2 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL1 = wxNewId();
const long wxProductionDataPanel::ID_BUTTON1 = wxNewId();
const long wxProductionDataPanel::ID_BITMAPBUTTON17 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT3 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL2 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT4 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL4 = wxNewId();
const long wxProductionDataPanel::ID_BITMAPBUTTON11 = wxNewId();
const long wxProductionDataPanel::ID_PANEL5 = wxNewId();
const long wxProductionDataPanel::ID_CHECKBOX1 = wxNewId();
const long wxProductionDataPanel::ID_BUTTON3 = wxNewId();
const long wxProductionDataPanel::ID_PANEL3 = wxNewId();
const long wxProductionDataPanel::ID_CUSTOM1 = wxNewId();
const long wxProductionDataPanel::ID_CHECKBOX2 = wxNewId();
const long wxProductionDataPanel::ID_BUTTON5 = wxNewId();
const long wxProductionDataPanel::ID_PANEL7 = wxNewId();
const long wxProductionDataPanel::ID_CUSTOM2 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT5 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL3 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT25 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT8 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL7 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT9 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL8 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT7 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL6 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT40 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL5 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT30 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT29 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT31 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL16 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL15 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL14 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT10 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL9 = wxNewId();
const long wxProductionDataPanel::ID_BITMAPBUTTON4 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT11 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL10 = wxNewId();
const long wxProductionDataPanel::ID_BITMAPBUTTON5 = wxNewId();
const long wxProductionDataPanel::ID_PANEL1 = wxNewId();
const long wxProductionDataPanel::ID_BITMAPBUTTON6 = wxNewId();
const long wxProductionDataPanel::ID_BITMAPBUTTON7 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL12 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT14 = wxNewId();
const long wxProductionDataPanel::ID_BUTTON9 = wxNewId();
const long wxProductionDataPanel::ID_BUTTON8 = wxNewId();
const long wxProductionDataPanel::ID_BITMAPBUTTON8 = wxNewId();
const long wxProductionDataPanel::ID_BITMAPBUTTON9 = wxNewId();
const long wxProductionDataPanel::ID_PANEL2 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT32 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL17 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT34 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT33 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL18 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT35 = wxNewId();
const long wxProductionDataPanel::ID_BUTTON2 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT19 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL20 = wxNewId();
const long wxProductionDataPanel::ID_BITMAPBUTTON16 = wxNewId();
const long wxProductionDataPanel::ID_BITMAPBUTTON10 = wxNewId();
const long wxProductionDataPanel::ID_PANEL6 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT37 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL21 = wxNewId();
const long wxProductionDataPanel::ID_BITMAPBUTTON12 = wxNewId();
const long wxProductionDataPanel::ID_BITMAPBUTTON13 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL22 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT38 = wxNewId();
const long wxProductionDataPanel::ID_BITMAPBUTTON14 = wxNewId();
const long wxProductionDataPanel::ID_BITMAPBUTTON15 = wxNewId();
const long wxProductionDataPanel::ID_PANEL4 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT15 = wxNewId();
const long wxProductionDataPanel::ID_COMBOBOX4 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT16 = wxNewId();
const long wxProductionDataPanel::ID_COMBOBOX5 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT17 = wxNewId();
const long wxProductionDataPanel::ID_COMBOBOX6 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT20 = wxNewId();
const long wxProductionDataPanel::ID_COMBOBOX9 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT21 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL19 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT36 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT22 = wxNewId();
const long wxProductionDataPanel::ID_COMBOBOX11 = wxNewId();
const long wxProductionDataPanel::ID_BUTTON4 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT23 = wxNewId();
const long wxProductionDataPanel::ID_COMBOBOX3 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT24 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL13 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT27 = wxNewId();
const long wxProductionDataPanel::ID_CHECKBOX3 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT28 = wxNewId();
const long wxProductionDataPanel::ID_COMBOBOX12 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT12 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL11 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT26 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT6 = wxNewId();
const long wxProductionDataPanel::ID_COMBOBOX8 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT18 = wxNewId();
const long wxProductionDataPanel::ID_COMBOBOX7 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT41 = wxNewId();
const long wxProductionDataPanel::ID_COMBOBOX10 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT39 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL23 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT42 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT13 = wxNewId();
const long wxProductionDataPanel::ID_COMBOBOX2 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT43 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT44 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL24 = wxNewId();
const long wxProductionDataPanel::ID_STATICTEXT45 = wxNewId();
const long wxProductionDataPanel::ID_TEXTCTRL25 = wxNewId();

//Antireflects WorkingModes
const long wxProductionDataPanel::ID_STATICTEXT_ANTIREFLECTS = wxNewId();
const long wxProductionDataPanel::ID_COMBOBOX_ANTIREFLECTS = wxNewId();

//*)

BEGIN_EVENT_TABLE(wxProductionDataPanel,wxPanel)
	//(*EventTable(wxProductionDataPanel)
	//*)
END_EVENT_TABLE()

wxProductionDataPanel::wxProductionDataPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxProductionDataPanel)
	wxBoxSizer* BoxSizer4;
	wxStaticBoxSizer* StaticBoxSizer2;
	wxBoxSizer* BoxSizer6;
	wxGridSizer* GridSizer4;
	wxBoxSizer* BoxSizer29;
	wxBoxSizer* BoxSizer15;
	wxBoxSizer* BoxSizer19;
	wxBoxSizer* BoxSizer20;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer10;
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* BoxSizer39;
	wxBoxSizer* BoxSizer8;
	wxBoxSizer* BoxSizer21;
	wxBoxSizer* BoxSizer13;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxBoxSizer* BoxSizer36;
	wxBoxSizer* BoxSizer37;
	wxFlexGridSizer* FlexGridSizer2;
	wxBoxSizer* BoxSizer23;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer11;
	wxBoxSizer* BoxSizer16;
	wxStaticBoxSizer* StaticBoxSizer7;
	wxBoxSizer* BoxSizer30;
	wxBoxSizer* BoxSizer18;
	wxBoxSizer* BoxSizer12;
	wxBoxSizer* BoxSizer28;
	wxBoxSizer* BoxSizer38;
	wxBoxSizer* BoxSizer14;
	wxStaticBoxSizer* wxSizerWorkingModes;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxGridSizer* GridSizer1;
	wxStaticBoxSizer* StaticBoxSizer6;
	wxBoxSizer* BoxSizer27;
	wxGridSizer* GridSizer3;
	wxBoxSizer* BoxSizer31;
	wxBoxSizer* BoxSizer17;
	wxBoxSizer* BoxSizer24;
	wxBoxSizer* BoxSizer26;
	wxBoxSizer* BoxSizer32;
	wxBoxSizer* BoxSizer4wxSizerT121;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer9;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxBoxSizer* BoxSizer22;
	wxBoxSizer* BoxSizer34;
	wxBoxSizer* BoxSizer33;
	wxFlexGridSizer* FlexGridSizer1;
	wxBoxSizer* BoxSizer35;
	wxBoxSizer* wxSizerT11;
	wxBoxSizer* BoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer5;
	wxGridSizer* GridSizer2;
	wxBoxSizer* BoxSizer25;
	wxBoxSizer* BoxSizer40;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	SetExtraStyle( GetExtraStyle() | wxWS_EX_VALIDATE_RECURSIVELY );
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Production Name"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer2->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	productionNameCombo = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxSize(200,25), 0, 0, wxCB_READONLY|wxCB_DROPDOWN, wxDefaultValidator, _T("ID_COMBOBOX1"));
	BoxSizer2->Add(productionNameCombo, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	newBtn = new wxBitmapButton(this, ID_BITMAPBUTTON1, wxNullBitmap, wxDefaultPosition, wxSize(34,34), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	newBtn->SetDefault();
	BoxSizer2->Add(newBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	editBtn = new wxBitmapButton(this, ID_BITMAPBUTTON2, wxNullBitmap, wxDefaultPosition, wxSize(34,34), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
	editBtn->SetDefault();
	BoxSizer2->Add(editBtn, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	deleteBtn = new wxBitmapButton(this, ID_BITMAPBUTTON3, wxNullBitmap, wxDefaultPosition, wxSize(34,34), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
	deleteBtn->SetDefault();
	BoxSizer2->Add(deleteBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Counter"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer2->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	counterEdit = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(80,19), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer2->Add(counterEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	counterResetBtn = new wxButton(this, ID_BUTTON1, _("Reset"), wxDefaultPosition, wxSize(75,25), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer2->Add(counterResetBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 0, wxTOP|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer35 = new wxBoxSizer(wxVERTICAL);
	BoxSizer5 = new wxBoxSizer(wxVERTICAL);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("PCB Size"));
	Panel5 = new wxPanel(this, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
	BoxSizer17 = new wxBoxSizer(wxHORIZONTAL);
	GridSizer1 = new wxGridSizer(0, 1, 0, 0);
	BoxSizer33 = new wxBoxSizer(wxHORIZONTAL);
	importFromGerberBtn = new wxBitmapButton(Panel5, ID_BITMAPBUTTON17, wxNullBitmap, wxDefaultPosition, wxSize(34,34), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON17"));
	importFromGerberBtn->SetDefault();
	BoxSizer33->Add(importFromGerberBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer7->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(Panel5, ID_STATICTEXT3, _("X (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	BoxSizer7->Add(StaticText3, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	pcbXEdit = new wxTextCtrl(Panel5, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(80,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer7->Add(pcbXEdit, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer33->Add(BoxSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
	StaticText4 = new wxStaticText(Panel5, ID_STATICTEXT4, _("Y (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	BoxSizer8->Add(StaticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	pcbYEdit = new wxTextCtrl(Panel5, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxSize(80,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	BoxSizer8->Add(pcbYEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer33->Add(BoxSizer8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer33, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer17->Add(GridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer36 = new wxBoxSizer(wxHORIZONTAL);
	conveyorAdjustBtn = new wxBitmapButton(Panel5, ID_BITMAPBUTTON11, wxNullBitmap, wxDefaultPosition, wxSize(34,34), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON11"));
	conveyorAdjustBtn->SetDefault();
	BoxSizer36->Add(conveyorAdjustBtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer17->Add(BoxSizer36, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel5->SetSizer(BoxSizer17);
	BoxSizer17->Fit(Panel5);
	BoxSizer17->SetSizeHints(Panel5);
	StaticBoxSizer1->Add(Panel5, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer5->Add(StaticBoxSizer1, 0, wxTOP|wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer7 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Gerbers"));
	FlexGridSizer3 = new wxFlexGridSizer(0, 7, 0, 0);
	FlexGridSizer3->Add(-1,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel3 = new wxPanel(this, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	BoxSizer38 = new wxBoxSizer(wxVERTICAL);
	topGerber_Check = new wxCheckBox(Panel3, ID_CHECKBOX1, _("Printing\nSide"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	topGerber_Check->SetValue(false);
	BoxSizer38->Add(topGerber_Check, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	topGerberBtn = new wxButton(Panel3, ID_BUTTON3, _("..."), wxDefaultPosition, wxSize(50,20), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	BoxSizer38->Add(topGerberBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel3->SetSizer(BoxSizer38);
	BoxSizer38->Fit(Panel3);
	BoxSizer38->SetSizeHints(Panel3);
	FlexGridSizer3->Add(Panel3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	gTopImage = new wxPictureBox(this,ID_CUSTOM1,wxDefaultPosition,wxSize(100,100));
	FlexGridSizer3->Add(gTopImage, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(80,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel7 = new wxPanel(this, ID_PANEL7, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
	BoxSizer39 = new wxBoxSizer(wxVERTICAL);
	botGerber_Check = new wxCheckBox(Panel7, ID_CHECKBOX2, _("Lower\nSide"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	botGerber_Check->SetValue(false);
	BoxSizer39->Add(botGerber_Check, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	botGerberBtn = new wxButton(Panel7, ID_BUTTON5, _("..."), wxDefaultPosition, wxSize(50,20), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	BoxSizer39->Add(botGerberBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel7->SetSizer(BoxSizer39);
	BoxSizer39->Fit(Panel7);
	BoxSizer39->SetSizeHints(Panel7);
	FlexGridSizer3->Add(Panel7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	gBotImage = new wxPictureBox(this,ID_CUSTOM2,wxDefaultPosition,wxSize(100,100));
	FlexGridSizer3->Add(gBotImage, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(-1,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer7->Add(FlexGridSizer3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer5->Add(StaticBoxSizer7, 0, wxTOP|wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Workplate"));
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Interference (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	BoxSizer6->Add(StaticText5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	plateDeltaEdit = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxSize(80,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	BoxSizer6->Add(plateDeltaEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	interferenceLimitsLabel = new wxStaticText(this, ID_STATICTEXT25, _("[ -0.0 : 0.0 ]"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
	BoxSizer6->Add(interferenceLimitsLabel, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(BoxSizer6, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer5->Add(StaticBoxSizer2, 0, wxTOP|wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("PCB Corrections"));
	GridSizer2 = new wxGridSizer(0, 1, 0, 0);
	BoxSizer34 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Translation X (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	BoxSizer11->Add(StaticText8, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	correctionXEdit = new wxTextCtrl(this, ID_TEXTCTRL7, wxEmptyString, wxDefaultPosition, wxSize(80,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
	BoxSizer11->Add(correctionXEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer34->Add(BoxSizer11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Translation Y (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	BoxSizer12->Add(StaticText9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	correctionYEdit = new wxTextCtrl(this, ID_TEXTCTRL8, wxEmptyString, wxDefaultPosition, wxSize(80,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
	BoxSizer12->Add(correctionYEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer34->Add(BoxSizer12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer2->Add(BoxSizer34, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer10->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Rotation (deg)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	BoxSizer10->Add(StaticText7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	correctionREdit = new wxTextCtrl(this, ID_TEXTCTRL6, wxEmptyString, wxDefaultPosition, wxSize(80,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
	BoxSizer10->Add(correctionREdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer9->Add(BoxSizer10, 0, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer29 = new wxBoxSizer(wxHORIZONTAL);
	StaticText33 = new wxStaticText(this, ID_STATICTEXT40, _("Delta Y front/rear"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT40"));
	BoxSizer29->Add(StaticText33, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	DeltaYfrontRear = new wxTextCtrl(this, ID_TEXTCTRL5, wxEmptyString, wxDefaultPosition, wxSize(80,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	BoxSizer29->Add(DeltaYfrontRear, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer9->Add(BoxSizer29, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 20);
	GridSizer2->Add(BoxSizer9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(GridSizer2, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer5->Add(StaticBoxSizer3, 0, wxTOP|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer35->Add(BoxSizer5, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Notes"));
	BoxSizer18 = new wxBoxSizer(wxVERTICAL);
	StaticText26 = new wxStaticText(this, ID_STATICTEXT30, _("Squeegees"), wxDefaultPosition, wxSize(-1,19), 0, _T("ID_STATICTEXT30"));
	BoxSizer18->Add(StaticText26, 0, wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText28 = new wxStaticText(this, ID_STATICTEXT29, _("Solder paste"), wxDefaultPosition, wxSize(-1,19), 0, _T("ID_STATICTEXT29"));
	BoxSizer18->Add(StaticText28, 0, wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText27 = new wxStaticText(this, ID_STATICTEXT31, _("Other"), wxDefaultPosition, wxSize(-1,19), 0, _T("ID_STATICTEXT31"));
	BoxSizer18->Add(StaticText27, 0, wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(BoxSizer18, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer19 = new wxBoxSizer(wxVERTICAL);
	notes1Edit = new wxTextCtrl(this, ID_TEXTCTRL16, wxEmptyString, wxDefaultPosition, wxSize(-1,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL16"));
	BoxSizer19->Add(notes1Edit, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	notes2Edit = new wxTextCtrl(this, ID_TEXTCTRL15, wxEmptyString, wxDefaultPosition, wxSize(-1,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL15"));
	BoxSizer19->Add(notes2Edit, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	notesEdit = new wxTextCtrl(this, ID_TEXTCTRL14, wxEmptyString, wxDefaultPosition, wxSize(-1,76), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL14"));
	BoxSizer19->Add(notesEdit, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(BoxSizer19, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer35->Add(StaticBoxSizer5, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	BoxSizer3->Add(BoxSizer35, 0, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	BoxSizer31 = new wxBoxSizer(wxVERTICAL);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxVERTICAL, this, _("Squeegees"));
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	GridSizer3 = new wxGridSizer(0, 2, 0, 0);
	BoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
	StaticText10 = new wxStaticText(Panel1, ID_STATICTEXT10, _("Zero position (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	BoxSizer13->Add(StaticText10, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	squeegeesZeroMoveEdit = new wxTextCtrl(Panel1, ID_TEXTCTRL9, wxEmptyString, wxDefaultPosition, wxSize(60,19), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL9"));
	BoxSizer13->Add(squeegeesZeroMoveEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	squeegeesZeroMoveBtn = new wxBitmapButton(Panel1, ID_BITMAPBUTTON4, wxNullBitmap, wxDefaultPosition, wxSize(34,34), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON4"));
	squeegeesZeroMoveBtn->SetDefault();
	BoxSizer13->Add(squeegeesZeroMoveBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer3->Add(BoxSizer13, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
	StaticText11 = new wxStaticText(Panel1, ID_STATICTEXT11, _("Movement (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	BoxSizer14->Add(StaticText11, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	squeegeesMoveEdit = new wxTextCtrl(Panel1, ID_TEXTCTRL10, wxEmptyString, wxDefaultPosition, wxSize(60,19), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL10"));
	BoxSizer14->Add(squeegeesMoveEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	squeegeesMoveBtn = new wxBitmapButton(Panel1, ID_BITMAPBUTTON5, wxNullBitmap, wxDefaultPosition, wxSize(34,34), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON5"));
	squeegeesMoveBtn->SetDefault();
	BoxSizer14->Add(squeegeesMoveBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer3->Add(BoxSizer14, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel1->SetSizer(GridSizer3);
	GridSizer3->Fit(Panel1);
	GridSizer3->SetSizeHints(Panel1);
	StaticBoxSizer4->Add(Panel1, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerControlPanel = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Control Panel"));
	wxSizerT11 = new wxBoxSizer(wxVERTICAL);
	moveUpBtn = new wxBitmapButton(this, ID_BITMAPBUTTON6, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON6"));
	moveUpBtn->SetDefault();
	wxSizerT11->Add(moveUpBtn, 0, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	moveDownBtn = new wxBitmapButton(this, ID_BITMAPBUTTON7, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON7"));
	moveDownBtn->SetDefault();
	wxSizerT11->Add(moveDownBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerControlPanel->Add(wxSizerT11, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4wxSizerT121 = new wxBoxSizer(wxHORIZONTAL);
	moveUserEdit = new wxTextCtrl(this, ID_TEXTCTRL12, wxEmptyString, wxDefaultPosition, wxSize(50,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL12"));
	BoxSizer4wxSizerT121->Add(moveUserEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	moveMMLabel = new wxStaticText(this, ID_STATICTEXT14, _("mm"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	BoxSizer4wxSizerT121->Add(moveMMLabel, 0, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerControlPanel->Add(BoxSizer4wxSizerT121, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer15 = new wxBoxSizer(wxVERTICAL);
	squeegeesFrontBtn = new wxButton(this, ID_BUTTON9, _("Front Squeegees"), wxDefaultPosition, wxSize(150,23), 0, wxDefaultValidator, _T("ID_BUTTON9"));
	BoxSizer15->Add(squeegeesFrontBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	squeegeesRearBtn = new wxButton(this, ID_BUTTON8, _("Rear Squeegees"), wxDefaultPosition, wxSize(150,23), 0, wxDefaultValidator, _T("ID_BUTTON8"));
	BoxSizer15->Add(squeegeesRearBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerControlPanel->Add(BoxSizer15, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	wxSizerControlPanel->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	BoxSizer23 = new wxBoxSizer(wxHORIZONTAL);
	okBtn = new wxBitmapButton(Panel2, ID_BITMAPBUTTON8, wxNullBitmap, wxDefaultPosition, wxSize(34,34), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON8"));
	okBtn->SetDefault();
	BoxSizer23->Add(okBtn, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cancelBtn = new wxBitmapButton(Panel2, ID_BITMAPBUTTON9, wxNullBitmap, wxDefaultPosition, wxSize(34,34), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON9"));
	cancelBtn->SetDefault();
	BoxSizer23->Add(cancelBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2->SetSizer(BoxSizer23);
	BoxSizer23->Fit(Panel2);
	BoxSizer23->SetSizeHints(Panel2);
	wxSizerControlPanel->Add(Panel2, 0, wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticBoxSizer4->Add(wxSizerControlPanel, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Escape Distance"));
	GridSizer4 = new wxGridSizer(0, 2, 0, 0);
	BoxSizer21 = new wxBoxSizer(wxHORIZONTAL);
	StaticText25 = new wxStaticText(this, ID_STATICTEXT32, _("Front (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT32"));
	BoxSizer21->Add(StaticText25, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	squeegeesRecoveryFrontEdit = new wxTextCtrl(this, ID_TEXTCTRL17, wxEmptyString, wxDefaultPosition, wxSize(50,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL17"));
	BoxSizer21->Add(squeegeesRecoveryFrontEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	recoveryFLimitsLabel = new wxStaticText(this, ID_STATICTEXT34, _("[ -0.0 : 0.0 ]"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT34"));
	BoxSizer21->Add(recoveryFLimitsLabel, 1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer4->Add(BoxSizer21, 0, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer22 = new wxBoxSizer(wxHORIZONTAL);
	StaticText29 = new wxStaticText(this, ID_STATICTEXT33, _("Rear (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT33"));
	BoxSizer22->Add(StaticText29, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	squeegeesRecoveryRearEdit = new wxTextCtrl(this, ID_TEXTCTRL18, wxEmptyString, wxDefaultPosition, wxSize(50,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL18"));
	BoxSizer22->Add(squeegeesRecoveryRearEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	recoveryRLimitsLabel = new wxStaticText(this, ID_STATICTEXT35, _("[ -0.0 : 0.0 ]"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT35"));
	BoxSizer22->Add(recoveryRLimitsLabel, 1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer4->Add(BoxSizer22, 0, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer6->Add(GridSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(StaticBoxSizer6, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer31->Add(StaticBoxSizer4, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerLoader = new wxStaticBoxSizer(wxVERTICAL, this, _("Loader"));
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	BoxSizer37 = new wxBoxSizer(wxVERTICAL);
	loaderAdjPosition = new wxButton(this, ID_BUTTON2, _("Move to Loading Position"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer37->Add(loaderAdjPosition, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel6 = new wxPanel(this, ID_PANEL6, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL6"));
	BoxSizer25 = new wxBoxSizer(wxHORIZONTAL);
	StaticText19 = new wxStaticText(Panel6, ID_STATICTEXT19, _("Start position (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
	BoxSizer25->Add(StaticText19, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	loaderStartPosEdit = new wxTextCtrl(Panel6, ID_TEXTCTRL20, wxEmptyString, wxDefaultPosition, wxSize(60,19), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL20"));
	BoxSizer25->Add(loaderStartPosEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	loaderStartMoveBtn = new wxBitmapButton(Panel6, ID_BITMAPBUTTON16, wxNullBitmap, wxDefaultPosition, wxSize(34,34), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON16"));
	loaderStartMoveBtn->SetDefault();
	BoxSizer25->Add(loaderStartMoveBtn, 1, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	loaderStartTeachBtn = new wxBitmapButton(Panel6, ID_BITMAPBUTTON10, wxNullBitmap, wxDefaultPosition, wxSize(34,34), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON10"));
	loaderStartTeachBtn->SetDefault();
	BoxSizer25->Add(loaderStartTeachBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel6->SetSizer(BoxSizer25);
	BoxSizer25->Fit(Panel6);
	BoxSizer25->SetSizeHints(Panel6);
	BoxSizer37->Add(Panel6, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(BoxSizer37, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer32 = new wxBoxSizer(wxVERTICAL);
	BoxSizer26 = new wxBoxSizer(wxHORIZONTAL);
	StaticText30 = new wxStaticText(this, ID_STATICTEXT37, _("Pitch (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT37"));
	BoxSizer26->Add(StaticText30, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	loaderTrayPitchEdit = new wxTextCtrl(this, ID_TEXTCTRL21, wxEmptyString, wxDefaultPosition, wxSize(60,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL21"));
	BoxSizer26->Add(loaderTrayPitchEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer32->Add(BoxSizer26, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(BoxSizer32, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerLoader->Add(FlexGridSizer2, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerControlPanelLoader = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Control Panel"));
	BoxSizer27 = new wxBoxSizer(wxVERTICAL);
	moveUpLoaderBtn = new wxBitmapButton(this, ID_BITMAPBUTTON12, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON12"));
	moveUpLoaderBtn->SetDefault();
	BoxSizer27->Add(moveUpLoaderBtn, 0, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	moveDownLoaderBtn = new wxBitmapButton(this, ID_BITMAPBUTTON13, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON13"));
	moveDownLoaderBtn->SetDefault();
	BoxSizer27->Add(moveDownLoaderBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerControlPanelLoader->Add(BoxSizer27, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer28 = new wxBoxSizer(wxHORIZONTAL);
	moveLoaderEdit = new wxTextCtrl(this, ID_TEXTCTRL22, wxEmptyString, wxDefaultPosition, wxSize(50,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL22"));
	BoxSizer28->Add(moveLoaderEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText31 = new wxStaticText(this, ID_STATICTEXT38, _("mm"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT38"));
	BoxSizer28->Add(StaticText31, 0, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerControlPanelLoader->Add(BoxSizer28, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerControlPanelLoader->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel4 = new wxPanel(this, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	BoxSizer30 = new wxBoxSizer(wxHORIZONTAL);
	okLoaderBtn = new wxBitmapButton(Panel4, ID_BITMAPBUTTON14, wxNullBitmap, wxDefaultPosition, wxSize(34,34), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON14"));
	okLoaderBtn->SetDefault();
	BoxSizer30->Add(okLoaderBtn, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cancelLoaderBtn = new wxBitmapButton(Panel4, ID_BITMAPBUTTON15, wxNullBitmap, wxDefaultPosition, wxSize(34,34), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON15"));
	cancelLoaderBtn->SetDefault();
	BoxSizer30->Add(cancelLoaderBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel4->SetSizer(BoxSizer30);
	BoxSizer30->Fit(Panel4);
	BoxSizer30->SetSizeHints(Panel4);
	wxSizerControlPanelLoader->Add(Panel4, 0, wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	wxSizerLoader->Add(wxSizerControlPanelLoader, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer31->Add(wxSizerLoader, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(BoxSizer31, 0, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	wxSizerWorkingModes = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Working Modes"));

	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _("Printing fiducial search"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	FlexGridSizer1->Add(StaticText15, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	fiducialSearchCombo = new wxComboBox(this, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxSize(120,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX4"));
	FlexGridSizer1->Add(fiducialSearchCombo, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT16, _("Printing fiducial on frame"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	FlexGridSizer1->Add(StaticText16, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	fiducialOnFrameCombo = new wxComboBox(this, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxSize(120,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX5"));
	FlexGridSizer1->Add(fiducialOnFrameCombo, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText17 = new wxStaticText(this, ID_STATICTEXT17, _("Debug mode"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	FlexGridSizer1->Add(StaticText17, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	debugModeCombo = new wxComboBox(this, ID_COMBOBOX6, wxEmptyString, wxDefaultPosition, wxSize(120,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX6"));
	FlexGridSizer1->Add(debugModeCombo, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText20 = new wxStaticText(this, ID_STATICTEXT20, _("Squeegees double cycle"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
	FlexGridSizer1->Add(StaticText20, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	doubleSqueegeesCombo = new wxComboBox(this, ID_COMBOBOX9, wxEmptyString, wxDefaultPosition, wxSize(120,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX9"));
	FlexGridSizer1->Add(doubleSqueegeesCombo, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText21 = new wxStaticText(this, ID_STATICTEXT21, _("Squeegees speed (mm/sec)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
	FlexGridSizer1->Add(StaticText21, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer24 = new wxBoxSizer(wxHORIZONTAL);
	squeegeesSpeedEdit = new wxTextCtrl(this, ID_TEXTCTRL19, wxEmptyString, wxDefaultPosition, wxSize(55,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL19"));
	BoxSizer24->Add(squeegeesSpeedEdit, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	squeegeesSpeedLimitsLabel = new wxStaticText(this, ID_STATICTEXT36, _("[ -0.0 : 0.0 ]"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT36"));
	BoxSizer24->Add(squeegeesSpeedLimitsLabel, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer24, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText22 = new wxStaticText(this, ID_STATICTEXT22, _("Verify points"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
	FlexGridSizer1->Add(StaticText22, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer20 = new wxBoxSizer(wxHORIZONTAL);
	printingVerifyCombo = new wxComboBox(this, ID_COMBOBOX11, wxEmptyString, wxDefaultPosition, wxSize(65,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX11"));
	BoxSizer20->Add(printingVerifyCombo, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	verifyResetBtn = new wxButton(this, ID_BUTTON4, _("Reset"), wxDefaultPosition, wxSize(50,25), 0, wxDefaultValidator, _T("ID_BUTTON4"));
	BoxSizer20->Add(verifyResetBtn, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer20, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText14 = new wxStaticText(this, ID_STATICTEXT23, _("Verify mode on printing"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
	FlexGridSizer1->Add(StaticText14, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	printingVerifyAutoCombo = new wxComboBox(this, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxSize(120,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX3"));
	FlexGridSizer1->Add(printingVerifyAutoCombo, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText23 = new wxStaticText(this, ID_STATICTEXT24, _("Verify delay on printing (sec)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
	FlexGridSizer1->Add(StaticText23, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer16 = new wxBoxSizer(wxHORIZONTAL);
	printingVerifyTimeEdit = new wxTextCtrl(this, ID_TEXTCTRL13, wxEmptyString, wxDefaultPosition, wxSize(55,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL13"));
	BoxSizer16->Add(printingVerifyTimeEdit, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	printingVerifyTimeLimitsLabel = new wxStaticText(this, ID_STATICTEXT27, _("[ -0.0 : 0.0 ]"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
	BoxSizer16->Add(printingVerifyTimeLimitsLabel, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer16, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxStopSPIWhenError = new wxCheckBox(this, ID_CHECKBOX3, _("Stop SPI execution"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	CheckBoxStopSPIWhenError->SetValue(false);
	FlexGridSizer1->Add(CheckBoxStopSPIWhenError, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText24 = new wxStaticText(this, ID_STATICTEXT28, _("Differential disengage"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT28"));
	FlexGridSizer1->Add(StaticText24, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	differentialDisengageCombo = new wxComboBox(this, ID_COMBOBOX12, wxEmptyString, wxDefaultPosition, wxSize(120,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX12"));
	FlexGridSizer1->Add(differentialDisengageCombo, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Disengage speed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer1->Add(StaticText12, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	disengageMovementEdit = new wxTextCtrl(this, ID_TEXTCTRL11, wxEmptyString, wxDefaultPosition, wxSize(55,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL11"));
	BoxSizer4->Add(disengageMovementEdit, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	disengageMovementLimitsLabel = new wxStaticText(this, ID_STATICTEXT26, _("[ 0.0 : 0.0 ]"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT26"));
	BoxSizer4->Add(disengageMovementLimitsLabel, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Verify after printing"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer1->Add(StaticText6, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	VerifyAfterprintingCombo = new wxComboBox(this, ID_COMBOBOX8, wxEmptyString, wxDefaultPosition, wxSize(120,25), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX8"));
	FlexGridSizer1->Add(VerifyAfterprintingCombo, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText18 = new wxStaticText(this, ID_STATICTEXT18, _("Loader enabled"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
	FlexGridSizer1->Add(StaticText18, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	loaderEnCombo = new wxComboBox(this, ID_COMBOBOX7, wxEmptyString, wxDefaultPosition, wxSize(120,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX7"));
	FlexGridSizer1->Add(loaderEnCombo, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText34 = new wxStaticText(this, ID_STATICTEXT41, _("Stencil cleaning enabled"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT41"));
	FlexGridSizer1->Add(StaticText34, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	cleaningEnCombo = new wxComboBox(this, ID_COMBOBOX10, wxEmptyString, wxDefaultPosition, wxSize(120,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX10"));
	FlexGridSizer1->Add(cleaningEnCombo, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText32 = new wxStaticText(this, ID_STATICTEXT39, _("Cleaning engage"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT39"));
	FlexGridSizer1->Add(StaticText32, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer40 = new wxBoxSizer(wxHORIZONTAL);
	CleaningEngageBox = new wxTextCtrl(this, ID_TEXTCTRL23, wxEmptyString, wxDefaultPosition, wxSize(55,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL23"));
	BoxSizer40->Add(CleaningEngageBox, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText35 = new wxStaticText(this, ID_STATICTEXT42, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT42"));
	BoxSizer40->Add(StaticText35, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer40, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("Beeper enabled"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	StaticText13->Hide();
	FlexGridSizer1->Add(StaticText13, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BeeperEnCombo = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxSize(120,25), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	BeeperEnCombo->Hide();
	FlexGridSizer1->Add(BeeperEnCombo, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText36 = new wxStaticText(this, ID_STATICTEXT43, _("Piston Offsets"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT43"));
	FlexGridSizer1->Add(StaticText36, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer41 = new wxBoxSizer(wxHORIZONTAL);
	StaticText37 = new wxStaticText(this, ID_STATICTEXT44, _("X"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT44"));
	StaticText37->SetMinSize(wxSize(-1,-1));
	StaticText37->SetMaxSize(wxSize(-1,-1));
	BoxSizer41->Add(StaticText37, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	xPistonOffsetTextEdit = new wxTextCtrl(this, ID_TEXTCTRL24, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL24"));
	xPistonOffsetTextEdit->SetMinSize(wxSize(50,20));
	BoxSizer41->Add(xPistonOffsetTextEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText38 = new wxStaticText(this, ID_STATICTEXT45, _("Y"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT45"));
	BoxSizer41->Add(StaticText38, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	yPistonoffsetTextEdit = new wxTextCtrl(this, ID_TEXTCTRL25, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL25"));
	yPistonoffsetTextEdit->SetMinSize(wxSize(50,20));
	BoxSizer41->Add(yPistonoffsetTextEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer41, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerWorkingModes->Add(FlexGridSizer1, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(wxSizerWorkingModes, 0, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	BoxSizer1->Add(BoxSizer3, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

	StaticTextAntireflects = new wxStaticText(this, ID_STATICTEXT_ANTIREFLECTS, _("Antireflects "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXTANTIREFLECTS"));
	FlexGridSizer1->Add(StaticTextAntireflects, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	antiReflectsCombo = new wxComboBox(this, ID_COMBOBOX_ANTIREFLECTS, wxEmptyString, wxDefaultPosition, wxSize(120,25), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX_ANTIREFLECTS"));
	FlexGridSizer1->Add(antiReflectsCombo, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);



	Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&wxProductionDataPanel::OnproductionNameComboSelect);
	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnnewBtnClick);
	Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OneditBtnClick);
	Connect(ID_BITMAPBUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OndeleteBtnClick);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OncounterResetBtnClick);
	Connect(ID_BITMAPBUTTON17,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnimportFromGerberBtnClick);
	Connect(ID_BITMAPBUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnconveyorAdjustBtnClick);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OntopGerber_CheckClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OntopGerberBtnClick);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnbotGerber_CheckClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnbotGerberBtnClick);
	Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnsqueegeesZeroMoveBtnClick);
	Connect(ID_BITMAPBUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnsqueegeesMoveBtnClick);
	Connect(ID_BITMAPBUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnmoveUpBtnClick);
	Connect(ID_BITMAPBUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnmoveDownBtnClick);
	Connect(ID_TEXTCTRL12,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&wxProductionDataPanel::OnmoveUserEditText);
	Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnsqueegeesFrontBtnClick);
	Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnsqueegeesRearBtnClick);
	Connect(ID_BITMAPBUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnokBtnClick);
	Connect(ID_BITMAPBUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OncancelBtnClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnloaderAdjPositionClick);
	Connect(ID_BITMAPBUTTON16,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnloaderStartMoveBtnClick);
	Connect(ID_BITMAPBUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnloaderStartTeachBtnClick);
	Connect(ID_BITMAPBUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnMoveUpLoaderBtnClick);
	Connect(ID_BITMAPBUTTON13,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnmoveDownLoaderBtnClick);
	Connect(ID_TEXTCTRL22,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&wxProductionDataPanel::OnmoveLoaderEditText);
	Connect(ID_BITMAPBUTTON14,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnokLoaderBtnClick);
	Connect(ID_BITMAPBUTTON15,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OncancelLoaderBtnClick);
	Connect(ID_COMBOBOX4,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&wxProductionDataPanel::OnWorkingModesComboSelect);
	Connect(ID_COMBOBOX11,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&wxProductionDataPanel::OnWorkingModesComboSelect);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnverifyResetBtnClick);
	Connect(ID_COMBOBOX3,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&wxProductionDataPanel::OnWorkingModesComboSelect);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxProductionDataPanel::OnCheckBoxStopSPIWhenErrorClick);
	Connect(ID_COMBOBOX12,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&wxProductionDataPanel::OnWorkingModesComboSelect);
	Connect(ID_COMBOBOX7,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&wxProductionDataPanel::OnWorkingModesComboSelect);
	Connect(ID_COMBOBOX10,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&wxProductionDataPanel::OnWorkingModesComboSelect);
	Connect(ID_COMBOBOX2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&wxProductionDataPanel::OnWorkingModesComboSelect);
	Connect(ID_COMBOBOX_ANTIREFLECTS,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&wxProductionDataPanel::OnWorkingModesComboSelect);
	//*)

	// init buttons image
	newBtn->SetBitmapDisabled( wxMEMORY_BITMAP( add_small ) );
	newBtn->SetBitmapLabel( wxMEMORY_BITMAP( add_small_on ) );
	deleteBtn->SetBitmapDisabled( wxMEMORY_BITMAP( delete_small ) );
	deleteBtn->SetBitmapLabel( wxMEMORY_BITMAP( delete_small_on ) );
	editBtn->SetBitmapDisabled( wxMEMORY_BITMAP( edit_small ) );
	editBtn->SetBitmapLabel( wxMEMORY_BITMAP( edit_small_on ) );
	squeegeesZeroMoveBtn->SetBitmapDisabled( wxMEMORY_BITMAP( teach_small_off ) );
	squeegeesZeroMoveBtn->SetBitmapLabel( wxMEMORY_BITMAP( teach_small_on ) );
	squeegeesMoveBtn->SetBitmapDisabled( wxMEMORY_BITMAP( teach_small_off ) );
	squeegeesMoveBtn->SetBitmapLabel( wxMEMORY_BITMAP( teach_small_on ) );
	moveUpBtn->SetBitmapDisabled( wxMEMORY_BITMAP( up ) );
	moveUpBtn->SetBitmapLabel( wxMEMORY_BITMAP( up_on ) );
	moveDownBtn->SetBitmapDisabled( wxMEMORY_BITMAP( down ) );
	moveDownBtn->SetBitmapLabel( wxMEMORY_BITMAP( down_on ) );
	okBtn->SetBitmapLabel( wxMEMORY_BITMAP( ok_small_on ) );
	okBtn->SetBitmapDisabled( wxMEMORY_BITMAP( ok_small ) );
	cancelBtn->SetBitmapLabel( wxMEMORY_BITMAP( cancel_small_on ) );
	cancelBtn->SetBitmapDisabled( wxMEMORY_BITMAP( cancel_small ) );
	loaderStartMoveBtn->SetBitmapDisabled( wxMEMORY_BITMAP( play_small ) );
	loaderStartMoveBtn->SetBitmapLabel( wxMEMORY_BITMAP( play_small_on ) );
	loaderStartTeachBtn->SetBitmapDisabled( wxMEMORY_BITMAP( teach_small_off ) );
	loaderStartTeachBtn->SetBitmapLabel( wxMEMORY_BITMAP( teach_small_on ) );
	moveUpLoaderBtn->SetBitmapDisabled( wxMEMORY_BITMAP( up ) );
	moveUpLoaderBtn->SetBitmapLabel( wxMEMORY_BITMAP( up_on ) );
	moveDownLoaderBtn->SetBitmapDisabled( wxMEMORY_BITMAP( down ) );
	moveDownLoaderBtn->SetBitmapLabel( wxMEMORY_BITMAP( down_on ) );
	okLoaderBtn->SetBitmapLabel( wxMEMORY_BITMAP( ok_small_on ) );
	okLoaderBtn->SetBitmapDisabled( wxMEMORY_BITMAP( ok_small ) );
	cancelLoaderBtn->SetBitmapLabel( wxMEMORY_BITMAP( cancel_small_on ) );
	cancelLoaderBtn->SetBitmapDisabled( wxMEMORY_BITMAP( cancel_small ) );
	conveyorAdjustBtn->SetBitmapDisabled( wxMEMORY_BITMAP( play_small ) );
	conveyorAdjustBtn->SetBitmapLabel( wxMEMORY_BITMAP( play_small_on ) );
	importFromGerberBtn->SetBitmapDisabled( wxMEMORY_BITMAP( teach_small_off ) );
	importFromGerberBtn->SetBitmapLabel( wxMEMORY_BITMAP( teach_small_on ) );
	/* //TEMP - per il futuro
	squeegeesFrontBtn->SetBitmapDisabled( wxMEMORY_BITMAP( frontsqueegees ) );
	squeegeesFrontBtn->SetBitmapLabel( wxMEMORY_BITMAP( frontsqueegees_on ) );
	squeegeesRearBtn->SetBitmapDisabled( wxMEMORY_BITMAP( rearsqueegees ) );
	squeegeesRearBtn->SetBitmapLabel( wxMEMORY_BITMAP( rearsqueegees_on ) );
	*/

	// set buttons tooltip
	newBtn->SetToolTip( TOO_NEWPRODUCTION );
	editBtn->SetToolTip( TOO_EDITPRODUCTION );
	deleteBtn->SetToolTip( TOO_DELETEPRODUCTION );
	squeegeesZeroMoveBtn->SetToolTip( TOO_TEACHSQUEEGEESZERO );
	squeegeesMoveBtn->SetToolTip( TOO_TEACHSQUEEGEESMOVE );
	counterResetBtn->SetToolTip( TOO_COUNTERRESET );
	okBtn->SetToolTip( TOO_OK );
	cancelBtn->SetToolTip( TOO_CANCEL );
	loaderStartMoveBtn->SetToolTip( TOO_MOVELOADERZERO );
	loaderStartTeachBtn->SetToolTip( TOO_TEACHLOADERZERO );
	okLoaderBtn->SetToolTip( TOO_OK );
	cancelLoaderBtn->SetToolTip( TOO_CANCEL );
	conveyorAdjustBtn->SetToolTip( TOO_CONVEYORADJUST );
	topGerberBtn->SetToolTip( TOO_TOPGERBERSEL );
	botGerberBtn->SetToolTip( TOO_BOTGERBERSEL );
	importFromGerberBtn->SetToolTip( TOO_GERBERDIM );
	/* //TEMP - per il futuro
	squeegeesFrontBtn->SetToolTip( TOO_FRONTSQUEEGEES );
	squeegeesRearBtn->SetToolTip( TOO_REARSQUEEGEES );
	*/
}

wxProductionDataPanel::~wxProductionDataPanel()
{
	//(*Destroy(wxProductionDataPanel)
	//*)
}

//----------------------------------------------------------------------------------
// Init
// Inizializza il controllo
//----------------------------------------------------------------------------------
int wxProductionDataPanel::Init( SRMachine *SRRef, SmartLog* smartLoggerRef, wxPanel *toolBoxRef, wxBitmapButton* menuBtnRef )
{
	SR = SRRef;
	smartLogger = smartLoggerRef;
	toolBox = toolBoxRef;
	menuBtn = menuBtnRef;

	move = 10.0;
	moveLoader = 10.0;
	isBusy = false;

	EnableSizerChilds( wxSizerControlPanel, false );
	EnableSizerChilds( wxSizerControlPanelLoader, false );

	// init combo labels
	wxArrayString comboLabels;
	comboLabels.Add(_("No"));
	comboLabels.Add(_("Yes"));
	differentialDisengageCombo->Append( comboLabels );
	fiducialOnFrameCombo->Append( comboLabels );
	debugModeCombo->Append( comboLabels );
	doubleSqueegeesCombo->Append( comboLabels );
	loaderEnCombo->Append( comboLabels );
	cleaningEnCombo->Append( comboLabels );
	antiReflectsCombo->Append( comboLabels);
	//BeeperEnCombo->Append(comboLabels);
	//aggiunto
	VerifyAfterprintingCombo->Append(comboLabels);

	comboLabels.Clear();
	comboLabels.Add(_("Auto"));
	comboLabels.Add(_("Manual"));
	fiducialSearchCombo->Append( comboLabels );
	printingVerifyAutoCombo->Append( comboLabels );


	comboLabels.Clear();
	//comboLabels.Add(_("No"));
	comboLabels.Add(wxT("1"));
	comboLabels.Add(wxT("2"));
	comboLabels.Add(wxT("3"));
	comboLabels.Add(wxT("4"));
	comboLabels.Add(wxT("5"));
	comboLabels.Add(wxT("6"));
	comboLabels.Add(wxT("7"));
	comboLabels.Add(wxT("8"));
	comboLabels.Add(wxT("9"));
	comboLabels.Add(wxT("10"));
	printingVerifyCombo->Append( comboLabels );

	//
	productionNameCombo->Clear();
	productionNameCombo->Append( SR->DB->ProductionNames );
	productionNameCombo->SetValue( SR->DB->ProductionDataS.ProductionName );

	// Avoid the deletion of the "SR3200" production
	editBtn->Enable( SR->DB->ProductionDataS.IdProd == 0 ? false : true );
	deleteBtn->Enable( SR->DB->ProductionDataS.IdProd == 0 ? false : true );

	counterEdit->SetValidator(					wxMyTextValidator( &SR->DB->ProductionDataS.Counter ) );
	pcbXEdit->SetValidator(						wxMyTextValidator( &SR->DB->ProductionDataS.PCBX, false, 2 ) );
	pcbYEdit->SetValidator(						wxMyTextValidator( &SR->DB->ProductionDataS.PCBY, false, 2 ) );
	squeegeesMoveEdit->SetValidator(			wxMyTextValidator( &SR->DB->ProductionDataS.SqueegeesMove, true, 2 ) );
	squeegeesZeroMoveEdit->SetValidator(		wxMyTextValidator( &SR->DB->ProductionDataS.SqueegeesZeroMove, true, 2 ) );
	squeegeesRecoveryFrontEdit->SetValidator(	wxMyTextValidator( &SR->DB->ProductionDataS.SqueegeesRecoveryFront, true, 2 ) );
	squeegeesRecoveryRearEdit->SetValidator(	wxMyTextValidator( &SR->DB->ProductionDataS.SqueegeesRecoveryRear, true, 2 ) );
	correctionXEdit->SetValidator(				wxMyTextValidator( &SR->DB->ProductionDataS.CorrectionX ) );
	correctionYEdit->SetValidator(				wxMyTextValidator( &SR->DB->ProductionDataS.CorrectionY ) );
	DeltaYfrontRear->SetValidator(				wxMyTextValidator( &SR->DB->ProductionDataS.DeltaYFrontRear ) );
	correctionREdit->SetValidator(				wxMyTextValidator( &SR->DB->ProductionDataS.CorrectionTheta ) );
	plateDeltaEdit->SetValidator(				wxMyTextValidator( &SR->DB->ProductionDataS.PlateMovementDelta ) );
	loaderStartPosEdit->SetValidator(			wxMyTextValidator( &SR->DB->ProductionDataS.LoaderStartPos, true, 2 ) );
	loaderTrayPitchEdit->SetValidator(			wxMyTextValidator( &SR->DB->ProductionDataS.LoaderTrayPitch, true, 2 ) );
	fiducialSearchCombo->SetValidator(			wxMyComboValidator( &SR->DB->WorkingModesS.FiducialSearch ) );
	fiducialOnFrameCombo->SetValidator(			wxMyComboValidator( &SR->DB->WorkingModesS.FiducialOnFrame ) );
	debugModeCombo->SetValidator(				wxMyComboValidator( &SR->DB->WorkingModesS.DebugMode ) );
	doubleSqueegeesCombo->SetValidator(			wxMyComboValidator( &SR->DB->WorkingModesS.DoubleSqueegees ) );
	printingVerifyCombo->SetValidator(			wxMyComboValidator( &SR->DB->WorkingModesS.PrintingVerify ) );
	differentialDisengageCombo->SetValidator(	wxMyComboValidator( &SR->DB->WorkingModesS.DifferentialDisengage ) );
	disengageMovementEdit->SetValidator(		wxMyTextValidator( &SR->DB->WorkingModesS.DisengageSpeed, false ) );
	squeegeesSpeedEdit->SetValidator(			wxMyTextValidator( &SR->DB->WorkingModesS.SqueegeesSpeedValue, false ) );
	printingVerifyAutoCombo->SetValidator(		wxMyComboValidator( &SR->DB->WorkingModesS.PrintingVerifyAuto ) );
	printingVerifyTimeEdit->SetValidator(		wxMyTextValidator( &SR->DB->WorkingModesS.PrintingVerifyTime, false ) );
	loaderEnCombo->SetValidator(				wxMyComboValidator( &SR->DB->WorkingModesS.LoaderEn ) );
	antiReflectsCombo->SetValidator(			wxMyComboValidator( &SR->DB->WorkingModesS.AntiReflectsEn ) );
	moveUserEdit->SetValidator(					wxMyTextValidator( &move ) );
	moveLoaderEdit->SetValidator(				wxMyTextValidator( &moveLoader ) );
	notesEdit->SetValidator(					wxMyTextValidator( &SR->DB->ProductionDataS.Notes ) );
	notes1Edit->SetValidator(					wxMyTextValidator( &SR->DB->ProductionDataS.Notes1 ) );
	notes2Edit->SetValidator(					wxMyTextValidator( &SR->DB->ProductionDataS.Notes2 ) );
	cleaningEnCombo->SetValidator(				wxMyComboValidator( &SR->DB->WorkingModesS.CleaningEn ) );
	CleaningEngageBox->SetValidator(			wxMyTextValidator( &SR->DB->WorkingModesS.CleaningEngageDistance, true , 1 ) );
	VerifyAfterprintingCombo->SetValidator( 	wxMyComboValidator( &SR->DB->WorkingModesS.VerifyON ) );
	xPistonOffsetTextEdit->SetValidator(		wxMyTextValidator( &SR->DB->WorkingModesS.PistonLoadingDeltaX, true , 1 ) );
	yPistonoffsetTextEdit->SetValidator(		wxMyTextValidator( &SR->DB->WorkingModesS.PistonLoadingDeltaY, true , 1 ) );

	//CheckBoxStopSPIWhenError->SetValidator(wxMyComboValidator( &SR->DB->WorkingModesS.SPIStopsWhenFaulty ));

	interferenceLimitsLabel->SetLabel( wxString::Format( wxT("[%.1f : %.1f]"), PLATE_MOVEMENT_DELTA_MIN, PLATE_MOVEMENT_DELTA_MAX ) );
	disengageMovementLimitsLabel->SetLabel( wxString::Format( wxT("[%.1f : %.1f]"), PLATE_DISENGAGE_MIN, PLATE_DISENGAGE_MAX ) );
	printingVerifyTimeLimitsLabel->SetLabel( wxString::Format( wxT("[%d : %d]"), VERIFY_DELAY_MIN, VERIFY_DELAY_MAX ) );
	recoveryFLimitsLabel->SetLabel( wxString::Format( wxT("[%.0f : %.0f]"), RECOVERY_F_MIN, RECOVERY_F_MAX ) );
	recoveryRLimitsLabel->SetLabel( wxString::Format( wxT("[%.0f : %.0f]"), RECOVERY_R_MIN, RECOVERY_R_MAX ) );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// ShowControl
// Mostra il controllo a video
//----------------------------------------------------------------------------------
int wxProductionDataPanel::ShowControl()
{
	int squeegees_speed_min = SR->DB->SpeedTableS[SPEED_SQUEEGEES_ID].Speed[0];
	int squeegees_speed_max = SR->DB->SpeedTableS[SPEED_SQUEEGEES_ID].Speed[2];
	squeegeesSpeedLimitsLabel->SetLabel( wxString::Format( wxT("[%d : %d]"), squeegees_speed_min, squeegees_speed_max ) );

	TransferDataToWindow();
	UpdateWorkingModesCombos();
	UpdateGerberData();
	return SR_OK;
}

//----------------------------------------------------------------------------------
// HideControl
// Nasconde il controllo
//----------------------------------------------------------------------------------
int wxProductionDataPanel::HideControl()
{
	TransferDataFromWindow();

	CheckLimitedVars();

	SR->DB->SaveProductionData();
	SR->DB->SaveWorkingModes();
	return SR_OK;
}

//----------------------------------------------------------------------------------
// UpdateProductionNames
// Aggiorna la lista delle produzioni
//----------------------------------------------------------------------------------
int wxProductionDataPanel::UpdateProductionNames()
{
	productionNameCombo->Clear();
	productionNameCombo->Append( SR->DB->ProductionNames );
	productionNameCombo->SetValue( SR->DB->ProductionDataS.ProductionName );

	// Avoid the deletion of the "SR3200" production
	editBtn->Enable( SR->DB->ProductionDataS.IdProd == 0 ? false : true );
	deleteBtn->Enable( SR->DB->ProductionDataS.IdProd == 0 ? false : true );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// LoadProduction
// Carica una produzione da DB
//----------------------------------------------------------------------------------
int wxProductionDataPanel::LoadProduction( const wxString &prodName )
{
	SR->DB->LoadProductionStructsFromDB( prodName );
	SR->DB->ActualProductionS.IdProd = SR->DB->ProductionDataS.IdProd;
	SR->DB->SaveActualProduction();
	TransferDataToWindow();

	UpdateWorkingModesCombos();
	UpdateGerberData();

	// Avoid the deletion of the "SR3200" production
	editBtn->Enable( SR->DB->ProductionDataS.IdProd == 0 ? false : true );
	deleteBtn->Enable( SR->DB->ProductionDataS.IdProd == 0 ? false : true );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// UpdateWorkingModesCombos
// Aggiorna la visualizzazione di WorkingModes
//----------------------------------------------------------------------------------
void wxProductionDataPanel::UpdateWorkingModesCombos()
{
	fiducialOnFrameCombo->Enable( SR->DB->WorkingModesS.FiducialSearch == FIDUCIAL_MANUAL ? false : true );
	printingVerifyAutoCombo->Enable( SR->DB->WorkingModesS.PrintingVerify == 0 ? false : true );
	printingVerifyTimeEdit->Enable( !printingVerifyAutoCombo->IsEnabled() || SR->DB->WorkingModesS.PrintingVerifyAuto == 1 ? false : true );
	CheckBoxStopSPIWhenError->Enable(!printingVerifyAutoCombo->IsEnabled() || SR->DB->WorkingModesS.PrintingVerifyAuto == 1 ? false : true );
	CheckBoxStopSPIWhenError->SetValue(SR->DB->WorkingModesS.SPIStopsWhenFaulty);
	disengageMovementEdit->Enable( SR->DB->WorkingModesS.DifferentialDisengage == 0 ? false : true );
	loaderEnCombo->Enable( SR->DB->MachineParamsS.LoaderInstalled == 0 ? false : true );
	cleaningEnCombo->Enable( SR->DB->MachineParamsS.CleaningInstalled == 0 ? false : true );
	CleaningEngageBox->Enable(SR->DB->MachineParamsS.CleaningInstalled == 0 ? false : true);
	//xPistonOffsetTextEdit->SetValue(wxString::Format(wxT("%f"), SR->DB->WorkingModesS.PistonLoadingDeltaX));
	//yPistonoffsetTextEdit->SetValue(wxString::Format(wxT("%f"), SR->DB->WorkingModesS.PistonLoadingDeltaY));
	EnableSizerChilds( wxSizerLoader, (SR->DB->MachineParamsS.LoaderInstalled == 0 || SR->DB->WorkingModesS.LoaderEn == 0) ? false : true );
	EnableSizerChilds( wxSizerControlPanelLoader, false );


}

//----------------------------------------------------------------------------------
// UpdateGerberData
// Aggiorna la visualizzazione dei gerber
//----------------------------------------------------------------------------------
void wxProductionDataPanel::UpdateGerberData()
{
	if( SR->DB->ProductionDataS.TopGerberOn )
	{
		topGerber_Check->SetValue(true);
		GerberPreviewImage(TOP_LAYER, true);
	}
	else
	{
		topGerber_Check->SetValue(false);
		GerberPreviewImage(TOP_LAYER, false);
	}

	if( SR->DB->ProductionDataS.BotGerberOn )
	{
		botGerber_Check->SetValue(true);
		GerberPreviewImage(BOTTOM_LAYER, true);
	}
	else
	{
		botGerber_Check->SetValue(false);
		GerberPreviewImage(BOTTOM_LAYER, false);
	}
}

//----------------------------------------------------------------------------------
// CheckLimitedVars
// Controlla le variabili da limitare entro un certo range
//----------------------------------------------------------------------------------
void wxProductionDataPanel::CheckLimitedVars()
{
	SR->DB->ProductionDataS.PlateMovementDelta = MID( PLATE_MOVEMENT_DELTA_MIN, SR->DB->ProductionDataS.PlateMovementDelta, PLATE_MOVEMENT_DELTA_MAX );
	SR->DB->WorkingModesS.DisengageSpeed = MID( PLATE_DISENGAGE_MIN, SR->DB->WorkingModesS.DisengageSpeed, PLATE_DISENGAGE_MAX );
	SR->DB->WorkingModesS.PrintingVerifyTime = MID( VERIFY_DELAY_MIN, SR->DB->WorkingModesS.PrintingVerifyTime, VERIFY_DELAY_MAX );
	SR->DB->ProductionDataS.SqueegeesRecoveryFront = MID( RECOVERY_F_MIN, SR->DB->ProductionDataS.SqueegeesRecoveryFront, RECOVERY_F_MAX );
	SR->DB->ProductionDataS.SqueegeesRecoveryRear = MID( RECOVERY_R_MIN, SR->DB->ProductionDataS.SqueegeesRecoveryRear, RECOVERY_R_MAX );

	// squeegees speed
	int squeegees_speed_min = SR->DB->SpeedTableS[SPEED_SQUEEGEES_ID].Speed[0];
	int squeegees_speed_max = SR->DB->SpeedTableS[SPEED_SQUEEGEES_ID].Speed[2];
	SR->DB->WorkingModesS.SqueegeesSpeedValue = MID( squeegees_speed_min, SR->DB->WorkingModesS.SqueegeesSpeedValue, squeegees_speed_max );
	SR->DB->SpeedTableS[SPEED_SQUEEGEES_ID].Speed[1] = MID( SR->DB->SpeedTableS[SPEED_SQUEEGEES_ID].Speed[0], SR->DB->WorkingModesS.SqueegeesSpeedValue, SR->DB->SpeedTableS[SPEED_SQUEEGEES_ID].Speed[2] );
}

//----------------------------------------------------------------------------------
// OnWorkingModesComboSelect
// Gestisce modifiche nelle opzione di WorkingModes
//----------------------------------------------------------------------------------
void wxProductionDataPanel::OnWorkingModesComboSelect( wxCommandEvent& event )
{
	TransferDataFromWindow();
	UpdateWorkingModesCombos();
}

void wxProductionDataPanel::OnproductionNameComboSelect(wxCommandEvent& event)
{
	// skip if the same production is selected
	if( !event.GetString().Cmp( SR->DB->ProductionDataS.ProductionName ) )
		return;

	// save old production
	TransferDataFromWindow();

	CheckLimitedVars();

	SR->DB->SaveProductionData();
	SR->DB->SaveWorkingModes();

	// load new production
	LoadProduction( event.GetString() );

	// Check if origins are correctly setted
	if( SR->CheckOrigin() )
	{
		// Ask for conveyors to move to selected production position
		if( wxMessageBox( MSG_CONVEYORSTOSTART, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, GetParent() ) == wxYES )
		{
			double convMove = SR->DB->ProductionDataS.PCBY - SR->DB->MachineParamsS.LConvMovement - SR->DB->MachineParamsS.LConvZeroMovement + CONVEYOR_WIDTH_DELTA;
			if(convMove < CONVPISTON_MIN_Y){
				wxMessageBox( MSG_CONVWIDTHMIN, MACHINE_NAME, wxOK | wxICON_ERROR, this);
				return;
			}
			wxWaitDialog wait(this);
			wait.SetMessage( MSG_CONVEYORWAIT );
			wait.Show();

			// Move the conveyors to Y dimension
			if( SR->LConvWidthMotor.Move( SR->DB->ProductionDataS.PCBY - SR->DB->MachineParamsS.LConvMovement - SR->DB->MachineParamsS.LConvZeroMovement + CONVEYOR_WIDTH_DELTA, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CONVWIDTHERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			if( SR->CConvWidthMotor.Move( SR->DB->ProductionDataS.PCBY - SR->DB->MachineParamsS.CConvMovement - SR->DB->MachineParamsS.CConvZeroMovement + CONVEYOR_WIDTH_DELTA, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CONVWIDTHERROR, MSG_ERROR );
				SR->ErrorManagement();
			}

			if( SR->LConvWidthMotor.Wait() == SR_ERROR )
			{
				smartLogger->Write( MSG_CONVWIDTHERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			if( SR->CConvWidthMotor.Wait() == SR_ERROR )
			{
				smartLogger->Write( MSG_CONVWIDTHERROR, MSG_ERROR );
				SR->ErrorManagement();
			}

			wait.Close();

			smartLogger->Write( MSG_CONVEYOROK, MSG_SUCCESS );
		}
	}
}

void wxProductionDataPanel::OnnewBtnClick(wxCommandEvent& event)
{
	// save current production
	TransferDataFromWindow();

	CheckLimitedVars();

	SR->DB->SaveProductionData();
	SR->DB->SaveWorkingModes();

	// Insert new production name
	wxTextEntryDialog *entryDlg = new wxTextEntryDialog( GetParent(), MSG_NEWPRODUCTIONNAME, MACHINE_NAME, wxT(""), wxOK | wxCANCEL | wxCENTRE );
	if( entryDlg->ShowModal() == wxID_CANCEL || entryDlg->GetValue().IsEmpty() )
		return;

	// Check if name already exist
	if( SR->DB->ProductionNames.Index( entryDlg->GetValue().Upper() ) != wxNOT_FOUND )
	{
		wxMessageBox( MSG_EXSISTINGNAME, MACHINE_NAME, wxOK | wxICON_QUESTION, GetParent() );
		return;
	}

	// Insert new production
	SR->DB->InsertProduction( entryDlg->GetValue().Upper(), SR->DB->MachineParamsS.SqueegeesDefZeroMove );

	// Add and select
	SR->DB->ProductionNames.Add( entryDlg->GetValue().Upper() );
	SR->DB->ProductionNames.Sort();
	productionNameCombo->Clear();
	productionNameCombo->Append( SR->DB->ProductionNames );
	productionNameCombo->SetValue( entryDlg->GetValue().Upper() );

	LoadProduction( entryDlg->GetValue().Upper() );
}

void wxProductionDataPanel::OneditBtnClick(wxCommandEvent& event)
{
	char oldName[MAXNPATH];
	char newName[MAXNPATH];

	// Insert new production name
	wxTextEntryDialog *entryDlg = new wxTextEntryDialog( GetParent(), MSG_NEWPRODUCTIONNAME, MACHINE_NAME, SR->DB->ProductionDataS.ProductionName, wxOK | wxCANCEL | wxCENTRE );
	if( entryDlg->ShowModal() == wxID_CANCEL || entryDlg->GetValue().IsEmpty() )
		return;

	// Remove and select
	SR->DB->ProductionNames.Remove( SR->DB->ProductionDataS.ProductionName );
	SR->DB->ProductionNames.Add( entryDlg->GetValue().Upper() );
	SR->DB->ProductionNames.Sort();
	productionNameCombo->Clear();
	productionNameCombo->Append( SR->DB->ProductionNames );
	productionNameCombo->SetValue( entryDlg->GetValue().Upper() );

	// rename gerbers files (if exist)
    strcpy(oldName,SR->DB->ProductionDataS.ProductionName);
    strcat(oldName,"-t");
    strcpy(newName,entryDlg->GetValue().Upper());
    strcat(newName,"-t");
	RenameFiles( DIR_GERBER, oldName, newName );
    strcpy(oldName,SR->DB->ProductionDataS.ProductionName);
    strcat(oldName,"-b");
    strcpy(newName,entryDlg->GetValue().Upper());
    strcat(newName,"-b");
	RenameFiles( DIR_GERBER, oldName, newName );

	SR->DB->ProductionDataS.ProductionName = entryDlg->GetValue().Upper();
	SR->DB->SaveProductionData();
}

void wxProductionDataPanel::OndeleteBtnClick(wxCommandEvent& event)
{
	char nameProd[MAXNPATH];

	if( wxMessageBox( MSG_ASKPRODUCTIONDELETE, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, GetParent() ) != wxYES )
		return;

	// Delete selected production
	if( wxMessageBox( MSG_ASKSAVERECORDS, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, GetParent() ) == wxYES )
	{
		SR->DB->DeleteProduction( SR->DB->ProductionDataS.IdProd, false ); //second argument is keepRecords
	}
	else{
		SR->DB->DeleteProduction( SR->DB->ProductionDataS.IdProd, true );
	}

	// Remove and select
	SR->DB->ProductionNames.Remove( SR->DB->ProductionDataS.ProductionName );
	SR->DB->ProductionNames.Sort();
	productionNameCombo->Clear();
	productionNameCombo->Append( SR->DB->ProductionNames );
	productionNameCombo->SetValue( SR->DB->ProductionNames[0] );

	// remove gerbers files (if exist)
    strcpy(nameProd,SR->DB->ProductionDataS.ProductionName);
    strcat(nameProd,"*");
	DeleteFiles( DIR_GERBER, nameProd );

	LoadProduction( SR->DB->ProductionNames[0] );
}

void wxProductionDataPanel::OncounterResetBtnClick(wxCommandEvent& event)
{
	if( wxMessageBox( MSG_ASKCOUNTERRESET, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, GetParent() ) != wxYES )
		return;

	counterEdit->ChangeValue( "0" );
}

void wxProductionDataPanel::OnsqueegeesZeroMoveBtnClick(wxCommandEvent& event)
{
	// Check if origins are correctly setted
	if( !SR->CheckOrigin() )
	{
		SR->ErrorManagement();
		return;
	}

	// SRMachine errors reset
	SR->ResetErrors();

	toolBox->Enable( false );
	menuBtn->Enable( false );
	EnableSizerChilds( GetSizer(), false );
	EnableSizerChilds( wxSizerControlPanel, true );
	Layout();

	currentState = PRODUCTIONDATA_STATE_SQUEEGEESZERO;
	smartLogger->Write( MSG_SQUEEGEESZERO );
}

void wxProductionDataPanel::OnsqueegeesMoveBtnClick(wxCommandEvent& event)
{
	// Check if origins are correctly setted
	if( !SR->CheckOrigin() )
	{
		SR->ErrorManagement();
		return;
	}

	// SRMachine errors reset
	SR->ResetErrors();

	toolBox->Enable( false );
	menuBtn->Enable( false );
	EnableSizerChilds( GetSizer(), false );
	EnableSizerChilds( wxSizerControlPanel, true );
	Layout();

	currentState = PRODUCTIONDATA_STATE_SQUEEGEESMOVE;
	smartLogger->Write( MSG_SQUEEGEESMOVE );
}

void wxProductionDataPanel::OnokBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;

	// Deactivate squeegees
	if( SR->SetOutput( OUTPUT_SQUEEGEESFRONT, false ) == SR_ERROR )
	{
		smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	if( SR->SetOutput( OUTPUT_SQUEEGEESREAR, false ) == SR_ERROR )
	{
		smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
		SR->ErrorManagement();
	}

	switch( currentState )
	{
		case PRODUCTIONDATA_STATE_SQUEEGEESZERO:
			SR->DB->ProductionDataS.SqueegeesZeroMove = SR->SqueegeesMotor.GetPosition();

			smartLogger->Write( MSG_SQUEEGEESZEROENDED, MSG_SUCCESS );
			break;

		case PRODUCTIONDATA_STATE_SQUEEGEESMOVE:
			SR->DB->ProductionDataS.SqueegeesMove = SR->SqueegeesMotor.GetPosition() - SR->DB->ProductionDataS.SqueegeesZeroMove;

			smartLogger->Write( MSG_SQUEEGEESMOVEENDED, MSG_SUCCESS );

			// Move the squeegees back to start position
			if( SR->SqueegeesMotor.MoveAndWait( SR->DB->ProductionDataS.SqueegeesZeroMove, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_SQUEEGEESERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			SR->SetSqueegeesCycle( false );
			break;
	}

	// save to DB
	SR->DB->SaveProductionData();

	TransferDataToWindow();

	toolBox->Enable( true );
	menuBtn->Enable( true );
	EnableSizerChilds( GetSizer(), true );
	EnableSizerChilds( wxSizerControlPanel, false );
	EnableSizerChilds( wxSizerLoader, SR->DB->WorkingModesS.LoaderEn == 0 ? false : true );
	EnableSizerChilds( wxSizerControlPanelLoader, false );
	// Avoid the deletion of the "SR3200" production
	editBtn->Enable( SR->DB->ProductionDataS.IdProd == 0 ? false : true );
	deleteBtn->Enable( SR->DB->ProductionDataS.IdProd == 0 ? false : true );
	Layout();

	isBusy = false;
}

void wxProductionDataPanel::OncancelBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;

	switch( currentState )
	{
		case PRODUCTIONDATA_STATE_SQUEEGEESZERO:
			smartLogger->Write( MSG_SQUEEGEESZEROABORTED, MSG_ERROR );
			break;

		case PRODUCTIONDATA_STATE_SQUEEGEESMOVE:
			smartLogger->Write( MSG_SQUEEGEESMOVEABORTED, MSG_ERROR );
			break;
	}

	// Deactivate squeegees
	if( SR->SetOutput( OUTPUT_SQUEEGEESFRONT, false ) == SR_ERROR )
	{
		smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	if( SR->SetOutput( OUTPUT_SQUEEGEESREAR, false ) == SR_ERROR )
	{
		smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	// Move the squeegees back to start position
	if( SR->SqueegeesMotor.MoveAndWait( SR->DB->ProductionDataS.SqueegeesZeroMove, ABS_MOVE ) == SR_ERROR )
	{
		smartLogger->Write( MSG_SQUEEGEESERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	SR->SetSqueegeesCycle( false );

	toolBox->Enable( true );
	menuBtn->Enable( true );
	EnableSizerChilds( GetSizer(), true );
	EnableSizerChilds( wxSizerControlPanel, false );
	EnableSizerChilds( wxSizerLoader, SR->DB->WorkingModesS.LoaderEn == 0 ? false : true );
	EnableSizerChilds( wxSizerControlPanelLoader, false );
	// Avoid the deletion of the "SR3200" production
	editBtn->Enable( SR->DB->ProductionDataS.IdProd == 0 ? false : true );
	deleteBtn->Enable( SR->DB->ProductionDataS.IdProd == 0 ? false : true );
	Layout();

	isBusy = false;
}

void wxProductionDataPanel::OnmoveUpBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->SqueegeesMotor.MoveAndWait( -move, REL_MOVE ) == SR_ERROR )
	{
		smartLogger->Write( MSG_SQUEEGEESERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxProductionDataPanel::OnmoveDownBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->SqueegeesMotor.MoveAndWait( move, REL_MOVE ) == SR_ERROR )
	{
		smartLogger->Write( MSG_SQUEEGEESERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxProductionDataPanel::OnsqueegeesFrontBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->SetOutput( OUTPUT_SQUEEGEESFRONT, !SR->isSqueegeesFrontOn ) == SR_ERROR )
	{
		smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxProductionDataPanel::OnsqueegeesRearBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->SetOutput( OUTPUT_SQUEEGEESREAR, !SR->isSqueegeesRearOn ) == SR_ERROR )
	{
		smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxProductionDataPanel::OnmoveUserEditText(wxCommandEvent& event)
{
	TransferDataFromWindow();
}

void wxProductionDataPanel::OnverifyResetBtnClick(wxCommandEvent& event)
{
	SR->DB->ResetVerifyPoints();

	TransferDataFromWindow();
	SR->DB->WorkingModesS.PrintingVerify = 0;
	TransferDataToWindow();
	UpdateWorkingModesCombos();
}

void wxProductionDataPanel::OnloaderAdjPositionClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;

	wxWaitDialog wait(this);
	wait.SetMessage( MSG_LOADERWAIT );
	wait.Show();

	// Move the loader to start position
	if( SR->LoaderMotor.MoveAndWait( SR->DB->MachineParamsS.LoaderAdjPosition, ABS_MOVE ) == SR_ERROR )
	{
		smartLogger->Write( MSG_LOADERERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	//040418
	SR->isReckinLoadPosition = true;
	wait.Close();

	isBusy = false;
}

void wxProductionDataPanel::OnloaderStartMoveBtnClick(wxCommandEvent& event)
{
	moveLoaderToProductionPosition();

}
void wxProductionDataPanel::moveLoaderToProductionPosition(){
	if( isBusy )
			return;

		isBusy = true;

		wxWaitDialog wait(this);
		wait.SetMessage( MSG_LOADERWAIT );
		wait.Show();

		// Move the loader to start position
		if( SR->LoaderMotor.MoveAndWait( SR->DB->MachineParamsS.LoaderZeroMovement + SR->DB->ProductionDataS.LoaderStartPos, ABS_MOVE ) == SR_ERROR )
		{
			smartLogger->Write( MSG_LOADERERROR, MSG_ERROR );
			SR->ErrorManagement();
		}
		SR->isReckinLoadPosition = false;
		SR->SetRackPos( 1 );

		wait.Close();

		isBusy = false;
}

void wxProductionDataPanel::OnloaderStartTeachBtnClick(wxCommandEvent& event)
{
	// Check if origins are correctly setted
	if( !SR->CheckOrigin() )
	{
		SR->ErrorManagement();
		return;
	}

	// SRMachine errors reset
	SR->ResetErrors();

	toolBox->Enable( false );
	menuBtn->Enable( false );
	EnableSizerChilds( GetSizer(), false );
	EnableSizerChilds( wxSizerControlPanelLoader, true );
	Layout();

	smartLogger->Write( MSG_LOADERZERO );
}

void wxProductionDataPanel::OnMoveUpLoaderBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->LoaderMotor.MoveAndWait( moveLoader, REL_MOVE ) == SR_ERROR )
	{
		smartLogger->Write( MSG_LOADERERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxProductionDataPanel::OnmoveDownLoaderBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->LoaderMotor.MoveAndWait( -moveLoader, REL_MOVE ) == SR_ERROR )
	{
		smartLogger->Write( MSG_LOADERERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxProductionDataPanel::OnokLoaderBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;

	SR->DB->ProductionDataS.LoaderStartPos = SR->LoaderMotor.GetPosition() - SR->DB->MachineParamsS.LoaderZeroMovement;

	smartLogger->Write( MSG_LOADERZEROENDED, MSG_SUCCESS );

	// save to DB
	SR->DB->SaveProductionData();

	TransferDataToWindow();

	toolBox->Enable( true );
	menuBtn->Enable( true );
	EnableSizerChilds( GetSizer(), true );
	EnableSizerChilds( wxSizerControlPanel, false );
	EnableSizerChilds( wxSizerControlPanelLoader, false );
	// Avoid the deletion of the "SR3200" production
	editBtn->Enable( SR->DB->ProductionDataS.IdProd == 0 ? false : true );
	deleteBtn->Enable( SR->DB->ProductionDataS.IdProd == 0 ? false : true );
	Layout();

	isBusy = false;
}

void wxProductionDataPanel::OncancelLoaderBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;

	smartLogger->Write( MSG_LOADERZEROABORTED, MSG_ERROR );

	int retVal = wxMessageBox( MSG_LOADERZEROPOS, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, this );
	if( retVal == wxYES )
	{
		wxWaitDialog wait(this);
		wait.SetMessage( MSG_LOADERWAIT );
		wait.Show();

		// Move the loader back to start position
		if( SR->LoaderMotor.MoveAndWait( SR->DB->ProductionDataS.LoaderStartPos, ABS_MOVE ) == SR_ERROR )
		{
			smartLogger->Write( MSG_LOADERERROR, MSG_ERROR );
			SR->ErrorManagement();
		}

		wait.Close();
	}

	toolBox->Enable( true );
	menuBtn->Enable( true );
	EnableSizerChilds( GetSizer(), true );
	EnableSizerChilds( wxSizerControlPanel, false );
	EnableSizerChilds( wxSizerControlPanelLoader, false );
	// Avoid the deletion of the "SR3200" production
	editBtn->Enable( SR->DB->ProductionDataS.IdProd == 0 ? false : true );
	deleteBtn->Enable( SR->DB->ProductionDataS.IdProd == 0 ? false : true );
	Layout();

	isBusy = false;
}

void wxProductionDataPanel::OnmoveLoaderEditText(wxCommandEvent& event)
{
	TransferDataFromWindow();
}

void wxProductionDataPanel::OnconveyorAdjustBtnClick(wxCommandEvent& event)
{
	TransferDataFromWindow();

	//check if the board is inside 040418
	if(SR->isBoardLoaded){
		wxMessageBox( MSG_BOARDPRESENT, MACHINE_NAME, wxICON_WARNING, this );
		return;
	}

	if(SR->DB->MachineParamsS.CleaningInstalled){
		//Obtain the engage position for the cleaner
		SR->DB->WorkingModesS.CleaningEngageDistance = floor(SR->DB->ProductionDataS.PCBY - SR->DB->MachineParamsS.CConvMovement - SR->DB->MachineParamsS.CConvZeroMovement + CLEANING_CONVEYOR_OFFSET - SR->DB->MachineParamsS.CleaningCameraDelta);
		CleaningEngageBox->SetValue(wxString::Format(wxT("%d"), (int)floor(SR->DB->WorkingModesS.CleaningEngageDistance)));
	}

	double convMove = SR->DB->ProductionDataS.PCBY - SR->DB->MachineParamsS.LConvMovement - SR->DB->MachineParamsS.LConvZeroMovement + CONVEYOR_WIDTH_DELTA;
	if(convMove < CONVPISTON_MIN_Y){
		wxMessageBox( MSG_CONVWIDTHMIN, MACHINE_NAME, wxOK | wxICON_ERROR, this);
		return;
	}

	wxWaitDialog wait(this);
	wait.SetMessage( MSG_CONVEYORWAIT );
	wait.Show();

	// Move the conveyors to Y dimension
	if( SR->LConvWidthMotor.Move( SR->DB->ProductionDataS.PCBY - SR->DB->MachineParamsS.LConvMovement - SR->DB->MachineParamsS.LConvZeroMovement + CONVEYOR_WIDTH_DELTA, ABS_MOVE ) == SR_ERROR )
	{
		smartLogger->Write( MSG_CONVWIDTHERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	if( SR->CConvWidthMotor.Move( SR->DB->ProductionDataS.PCBY - SR->DB->MachineParamsS.CConvMovement - SR->DB->MachineParamsS.CConvZeroMovement + CONVEYOR_WIDTH_DELTA, ABS_MOVE ) == SR_ERROR )
	{
		smartLogger->Write( MSG_CONVWIDTHERROR, MSG_ERROR );
		SR->ErrorManagement();
	}

	if( SR->LConvWidthMotor.Wait() == SR_ERROR )
	{
		smartLogger->Write( MSG_CONVWIDTHERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	if( SR->CConvWidthMotor.Wait() == SR_ERROR )
	{
		smartLogger->Write( MSG_CONVWIDTHERROR, MSG_ERROR );
		SR->ErrorManagement();
	}

	wait.Close();

	smartLogger->Write( MSG_CONVEYOROK, MSG_SUCCESS );
}

void wxProductionDataPanel::GerberPreviewImage(int layerId, bool visible)
{
	char path[MAXNPATH];

	wxBitmap blankBmp( 100, 100 );
	wxMemoryDC dc;
	dc.SelectObject( blankBmp );
	dc.SetBackground( this->GetBackgroundColour() );
	dc.Clear();

	if( visible )
	{
	    strcpy(path,DIR_GERBER);
	    strcat(path,"/");
	    strcat(path,SR->DB->ProductionDataS.ProductionName);
	    if( layerId == TOP_LAYER )
	        strcat(path,"-t.png");
	    else
	        strcat(path,"-b.png");

		// Blit final image to the screen.
		wxBitmap m_bitmap(wxImage(path, wxBITMAP_TYPE_PNG));

		dc.DrawBitmap(m_bitmap, 0, 0, true);
	}

	if( layerId == TOP_LAYER )
		gTopImage->SetImage( blankBmp );
	else
		gBotImage->SetImage( blankBmp );
}

void wxProductionDataPanel::OntopGerberBtnClick(wxCommandEvent& event)
{
	wxGerberDialog gerber(this);
	gerber.Init( SR );
	gerber.SetCurrentLayer( TOP_LAYER );

	if( gerber.ShowModal() == GERBERDIALOG_OK )
	{
		topGerber_Check->SetValue(true);
		GerberPreviewImage(TOP_LAYER, true);
		SR->DB->ProductionDataS.TopGerberOn = 1;
		SR->DB->ProductionDataS.TopGerberRot = gerber.GetLayerRot();
		SR->DB->ProductionDataS.TopGerberFlip = gerber.GetLayerFlip();
	}
}

void wxProductionDataPanel::OnbotGerberBtnClick(wxCommandEvent& event)
{
	wxGerberDialog gerber(this);
	gerber.Init( SR );
	gerber.SetCurrentLayer( BOTTOM_LAYER );

	if( gerber.ShowModal() == GERBERDIALOG_OK )
	{
		botGerber_Check->SetValue(true);
		GerberPreviewImage(BOTTOM_LAYER, true);
		SR->DB->ProductionDataS.BotGerberOn = 1;
		SR->DB->ProductionDataS.BotGerberRot = gerber.GetLayerRot();
		SR->DB->ProductionDataS.BotGerberFlip = gerber.GetLayerFlip();
	}
}

void wxProductionDataPanel::OntopGerber_CheckClick(wxCommandEvent& event)
{
	char path[MAXNPATH];

	if( !topGerber_Check->GetValue() )
	{
		GerberPreviewImage(TOP_LAYER, false);
		SR->DB->ProductionDataS.TopGerberOn = 0;
	}
	else
	{
	    strcpy(path,DIR_GERBER);
	    strcat(path,"/");
	    strcat(path,SR->DB->ProductionDataS.ProductionName);
		strcat(path,"-t.png");

		if( CheckFile(path) )
		{
			GerberPreviewImage(TOP_LAYER, true);
			SR->DB->ProductionDataS.TopGerberOn = 1;
		}
		else
		{
			wxMessageBox( MSG_ERRORLOADGERBER, MACHINE_NAME, wxOK | wxICON_ERROR, this );
			topGerber_Check->SetValue(false);
			SR->DB->ProductionDataS.TopGerberOn = 0;
		}
	}
}

void wxProductionDataPanel::OnbotGerber_CheckClick(wxCommandEvent& event)
{
	char path[MAXNPATH];

	if( !botGerber_Check->GetValue() )
	{
		GerberPreviewImage(BOTTOM_LAYER, false);
		SR->DB->ProductionDataS.BotGerberOn = 0;
	}
	else
	{
	    strcpy(path,DIR_GERBER);
	    strcat(path,"/");
	    strcat(path,SR->DB->ProductionDataS.ProductionName);
		strcat(path,"-b.png");

		if( CheckFile(path) )
		{
			GerberPreviewImage(BOTTOM_LAYER, true);
			SR->DB->ProductionDataS.BotGerberOn = 1;
		}
		else
		{
			wxMessageBox( MSG_ERRORLOADGERBER, MACHINE_NAME, wxOK | wxICON_ERROR, this );
			botGerber_Check->SetValue(false);
			SR->DB->ProductionDataS.BotGerberOn = 0;
		}
	}
}

void wxProductionDataPanel::OnimportFromGerberBtnClick(wxCommandEvent& event)
{
	char pathBase[MAXNPATH];
	char layerName[MAXNPATH];
	char fileNumber[2];
	gerbv_project_t *mainProject;

	if( !topGerber_Check->GetValue() && !botGerber_Check->GetValue() )
	{
		wxMessageBox( MSG_ERRORSELGERBER, MACHINE_NAME, wxOK | wxICON_ERROR, this );
		return;
	}

	mainProject = gerbv_create_project();

	strcpy(pathBase,DIR_GERBER);
    strcat(pathBase,"/");
    strcat(pathBase,SR->DB->ProductionDataS.ProductionName);

    // Se c'e' un gerber caricato come top, uso quello per le dimensioni,
    // altrimenti prendo quelle dal bottom
    if( topGerber_Check->GetValue() )
    	strcat(pathBase,"-t.l");
    else
    	strcat(pathBase,"-b.l");

	// Add active layers to project
	if( SR->DB->ProductionDataS.BotGerberSolder != 0 )
	{
		strcpy(layerName,pathBase);
    	sprintf(fileNumber,"%d",SR->DB->ProductionDataS.BotGerberSolder-1);
		strcat(layerName, fileNumber);
		gerbv_open_layer_from_filename( mainProject, layerName );
	}
	if( SR->DB->ProductionDataS.BotGerberMech != 0 )
	{
		strcpy(layerName,pathBase);
    	sprintf(fileNumber,"%d",SR->DB->ProductionDataS.BotGerberMech-1);
		strcat(layerName, fileNumber);
		gerbv_open_layer_from_filename( mainProject, layerName );
	}

	// Get gerber outside dimensions
	gerbv_render_size_t boundingbox;
	gerbv_render_get_boundingbox(mainProject, &boundingbox);
	double xdim, ydim;
	xdim = INCH_TO_MM*fabs(boundingbox.right-boundingbox.left);
	ydim = INCH_TO_MM*fabs(boundingbox.top-boundingbox.bottom);
	double Cx = fabs( xdim * cos(SR->DB->ProductionDataS.BotGerberRot) + ydim * sin(SR->DB->ProductionDataS.BotGerberRot) );
	double Cy = fabs( -xdim * sin(SR->DB->ProductionDataS.BotGerberRot) + ydim * cos(SR->DB->ProductionDataS.BotGerberRot) );

	SR->DB->ProductionDataS.PCBX = Cx;
	SR->DB->ProductionDataS.PCBY = Cy;

	if(SR->DB->MachineParamsS.CleaningInstalled){
		//Obtain the engage position for the cleaner
		SR->DB->WorkingModesS.CleaningEngageDistance = floor(SR->DB->ProductionDataS.PCBY - SR->DB->MachineParamsS.CConvMovement - SR->DB->MachineParamsS.CConvZeroMovement + CLEANING_CONVEYOR_OFFSET - SR->DB->MachineParamsS.CleaningCameraDelta);
		CleaningEngageBox->SetValue(wxString::Format(wxT("%d"), (int)floor(SR->DB->WorkingModesS.CleaningEngageDistance)));
	}

	// save to DB
	SR->DB->SaveProductionData();

	TransferDataToWindow();

	// destroy the project, which will in turn destroy all child images
	gerbv_destroy_project (mainProject);


}

void wxProductionDataPanel::OnCheckBoxStopSPIWhenErrorClick(wxCommandEvent& event)
{
	 SR->DB->WorkingModesS.SPIStopsWhenFaulty = CheckBoxStopSPIWhenError->GetValue();

}

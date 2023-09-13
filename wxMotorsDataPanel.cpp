#include "wxMotorsDataPanel.h"

//(*InternalHeaders(wxMotorsDataPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/file.h>
#include "GlobalEnum.h"
#include "wxMyTextValidator.h"
#include "wxMyComboValidator.h"
#include "wxMySpinValidator.h"
#include "GlobalUtils.h"
#include "Messages.h"

//(*IdInit(wxMotorsDataPanel)
const long wxMotorsDataPanel::ID_LISTBOX1 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT1 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT2 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT3 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT4 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT5 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT6 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT7 = wxNewId();
const long wxMotorsDataPanel::ID_SPINCTRL1 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL1 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL2 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL3 = wxNewId();
const long wxMotorsDataPanel::ID_COMBOBOX2 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL4 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL5 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT40 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT41 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL35 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL36 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT14 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT15 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT39 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT16 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT18 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT27 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT28 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT29 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT30 = wxNewId();
const long wxMotorsDataPanel::ID_SPINCTRL2 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL9 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL34 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL10 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL11 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL12 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL13 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL14 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL24 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT31 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT32 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT33 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT34 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT35 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT36 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT37 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT17 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT38 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL25 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL26 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL27 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL28 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL29 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL30 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL31 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL32 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL33 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT42 = wxNewId();
const long wxMotorsDataPanel::ID_SPINCTRL3 = wxNewId();
const long wxMotorsDataPanel::ID_CHECKBOX1 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT25 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL6 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT26 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL7 = wxNewId();
const long wxMotorsDataPanel::ID_STATICLINE1 = wxNewId();
const long wxMotorsDataPanel::ID_LISTBOX2 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT19 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT20 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT21 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT22 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL15 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL16 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL17 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT23 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL18 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL19 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL20 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT24 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL21 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL22 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL23 = wxNewId();
const long wxMotorsDataPanel::ID_STATICLINE2 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT8 = wxNewId();
const long wxMotorsDataPanel::ID_COMBOBOX1 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT9 = wxNewId();
const long wxMotorsDataPanel::ID_COMBOBOX4 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT10 = wxNewId();
const long wxMotorsDataPanel::ID_COMBOBOX5 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT11 = wxNewId();
const long wxMotorsDataPanel::ID_COMBOBOX6 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT12 = wxNewId();
const long wxMotorsDataPanel::ID_TEXTCTRL8 = wxNewId();
const long wxMotorsDataPanel::ID_BUTTON1 = wxNewId();
const long wxMotorsDataPanel::ID_STATICTEXT13 = wxNewId();
const long wxMotorsDataPanel::ID_COMBOBOX7 = wxNewId();
const long wxMotorsDataPanel::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxMotorsDataPanel,wxPanel)
	//(*EventTable(wxMotorsDataPanel)
	//*)
END_EVENT_TABLE()

wxMotorsDataPanel::wxMotorsDataPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxMotorsDataPanel)
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* BoxSizer8;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxBoxSizer* BoxSizer2;
	wxStaticBoxSizer* StaticBoxSizer8;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer6;
	wxGridSizer* GridSizer3;
	wxBoxSizer* BoxSizer1;
	wxStaticBoxSizer* StaticBoxSizer5;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	SetMaxSize(wxSize(-1,600));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	StaticBoxSizer8 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Motor params"));
	motorsList = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxSize(-1,120), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
	StaticBoxSizer8->Add(motorsList, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	GridSizerStepper = new wxGridSizer(0, 7, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Address"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	GridSizerStepper->Add(StaticText1, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Min current"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	GridSizerStepper->Add(StaticText2, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Acc current"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	GridSizerStepper->Add(StaticText3, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Max current"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	GridSizerStepper->Add(StaticText4, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Microstep"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	GridSizerStepper->Add(StaticText5, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Pulley"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	GridSizerStepper->Add(StaticText6, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Reduction"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	GridSizerStepper->Add(StaticText7, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	addressSpin = new wxSpinCtrl(this, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxSize(70,25), 0, 1, 31, 0, _T("ID_SPINCTRL1"));
	addressSpin->SetValue(_T("0"));
	GridSizerStepper->Add(addressSpin, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	minCurEdit = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	GridSizerStepper->Add(minCurEdit, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	accCurEdit = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	GridSizerStepper->Add(accCurEdit, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	maxCurEdit = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	GridSizerStepper->Add(maxCurEdit, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	stepCombo = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxSize(70,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX2"));
	GridSizerStepper->Add(stepCombo, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	pulleyEdit = new wxTextCtrl(this, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	GridSizerStepper->Add(pulleyEdit, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	reductionEdit = new wxTextCtrl(this, ID_TEXTCTRL5, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	GridSizerStepper->Add(reductionEdit, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText40 = new wxStaticText(this, ID_STATICTEXT40, _("Home Fast"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT40"));
	GridSizerStepper->Add(StaticText40, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText41 = new wxStaticText(this, ID_STATICTEXT41, _("Home Slow"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT41"));
	GridSizerStepper->Add(StaticText41, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizerStepper->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizerStepper->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizerStepper->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizerStepper->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizerStepper->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	homeFastSEdit = new wxTextCtrl(this, ID_TEXTCTRL35, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL35"));
	GridSizerStepper->Add(homeFastSEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	homeSlowSEdit = new wxTextCtrl(this, ID_TEXTCTRL36, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL36"));
	GridSizerStepper->Add(homeSlowSEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizerStepper->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizerStepper->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizerStepper->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizerStepper->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizerStepper->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(GridSizerStepper, 0, wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizerBrushless = new wxGridSizer(0, 9, 0, 0);
	StaticText14 = new wxStaticText(this, ID_STATICTEXT14, _("Address"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	GridSizerBrushless->Add(StaticText14, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _("Max current"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	GridSizerBrushless->Add(StaticText15, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText39 = new wxStaticText(this, ID_STATICTEXT39, _("Red current"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT39"));
	GridSizerBrushless->Add(StaticText39, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT16, _("Line Enc"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	GridSizerBrushless->Add(StaticText16, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText18 = new wxStaticText(this, ID_STATICTEXT18, _("PulsesToMm"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
	GridSizerBrushless->Add(StaticText18, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText27 = new wxStaticText(this, ID_STATICTEXT27, _("PPR"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
	GridSizerBrushless->Add(StaticText27, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText28 = new wxStaticText(this, ID_STATICTEXT28, _("KP Speed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT28"));
	GridSizerBrushless->Add(StaticText28, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText29 = new wxStaticText(this, ID_STATICTEXT29, _("KI Speed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT29"));
	GridSizerBrushless->Add(StaticText29, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText30 = new wxStaticText(this, ID_STATICTEXT30, _("KP Pos"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT30"));
	GridSizerBrushless->Add(StaticText30, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	addressBSpin = new wxSpinCtrl(this, ID_SPINCTRL2, _T("0"), wxDefaultPosition, wxSize(70,25), 0, 1, 31, 0, _T("ID_SPINCTRL2"));
	addressBSpin->SetValue(_T("0"));
	GridSizerBrushless->Add(addressBSpin, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	curEdit = new wxTextCtrl(this, ID_TEXTCTRL9, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL9"));
	GridSizerBrushless->Add(curEdit, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	redCurEdit = new wxTextCtrl(this, ID_TEXTCTRL34, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL34"));
	GridSizerBrushless->Add(redCurEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lineEncEdit = new wxTextCtrl(this, ID_TEXTCTRL10, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL10"));
	GridSizerBrushless->Add(lineEncEdit, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PTMEdit = new wxTextCtrl(this, ID_TEXTCTRL11, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL11"));
	GridSizerBrushless->Add(PTMEdit, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PPREdit = new wxTextCtrl(this, ID_TEXTCTRL12, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL12"));
	GridSizerBrushless->Add(PPREdit, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	KPSEdit = new wxTextCtrl(this, ID_TEXTCTRL13, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL13"));
	GridSizerBrushless->Add(KPSEdit, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	KISEdit = new wxTextCtrl(this, ID_TEXTCTRL14, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL14"));
	GridSizerBrushless->Add(KISEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	KPPEdit = new wxTextCtrl(this, ID_TEXTCTRL24, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL24"));
	GridSizerBrushless->Add(KPPEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText31 = new wxStaticText(this, ID_STATICTEXT31, _("Poles"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT31"));
	GridSizerBrushless->Add(StaticText31, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText32 = new wxStaticText(this, ID_STATICTEXT32, _("Jerk"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT32"));
	GridSizerBrushless->Add(StaticText32, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText33 = new wxStaticText(this, ID_STATICTEXT33, _("KA"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT33"));
	GridSizerBrushless->Add(StaticText33, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText34 = new wxStaticText(this, ID_STATICTEXT34, _("KS"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT34"));
	GridSizerBrushless->Add(StaticText34, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText35 = new wxStaticText(this, ID_STATICTEXT35, _("KC"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT35"));
	GridSizerBrushless->Add(StaticText35, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText36 = new wxStaticText(this, ID_STATICTEXT36, _("Home Fast"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT36"));
	GridSizerBrushless->Add(StaticText36, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText37 = new wxStaticText(this, ID_STATICTEXT37, _("Home Slow"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT37"));
	GridSizerBrushless->Add(StaticText37, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText17 = new wxStaticText(this, ID_STATICTEXT17, _("End Move D."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	GridSizerBrushless->Add(StaticText17, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText38 = new wxStaticText(this, ID_STATICTEXT38, _("Spyke Delta"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT38"));
	GridSizerBrushless->Add(StaticText38, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	polesEdit = new wxTextCtrl(this, ID_TEXTCTRL25, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL25"));
	GridSizerBrushless->Add(polesEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	jerkEdit = new wxTextCtrl(this, ID_TEXTCTRL26, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL26"));
	GridSizerBrushless->Add(jerkEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	KAEdit = new wxTextCtrl(this, ID_TEXTCTRL27, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL27"));
	GridSizerBrushless->Add(KAEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	KSEdit = new wxTextCtrl(this, ID_TEXTCTRL28, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL28"));
	GridSizerBrushless->Add(KSEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	KCEdit = new wxTextCtrl(this, ID_TEXTCTRL29, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL29"));
	GridSizerBrushless->Add(KCEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	homeFastEdit = new wxTextCtrl(this, ID_TEXTCTRL30, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL30"));
	GridSizerBrushless->Add(homeFastEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	homeSlowEdit = new wxTextCtrl(this, ID_TEXTCTRL31, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL31"));
	GridSizerBrushless->Add(homeSlowEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	EndMoveDeltaEdit = new wxTextCtrl(this, ID_TEXTCTRL32, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL32"));
	GridSizerBrushless->Add(EndMoveDeltaEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SpykeDeltaEdit = new wxTextCtrl(this, ID_TEXTCTRL33, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL33"));
	GridSizerBrushless->Add(SpykeDeltaEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(GridSizerBrushless, 1, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizerBrush = new wxGridSizer(0, 3, 0, 0);
	StaticText42 = new wxStaticText(this, ID_STATICTEXT42, _("Address"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT42"));
	GridSizerBrush->Add(StaticText42, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizerBrush->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizerBrush->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	AddressBrushSpin = new wxSpinCtrl(this, ID_SPINCTRL3, _T("0"), wxDefaultPosition, wxSize(70,25), 0, 1, 31, 0, _T("ID_SPINCTRL3"));
	AddressBrushSpin->SetValue(_T("0"));
	GridSizerBrush->Add(AddressBrushSpin, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	DirectionCheck = new wxCheckBox(this, ID_CHECKBOX1, _("Direction (CW/CCW)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	DirectionCheck->SetValue(false);
	GridSizerBrush->Add(DirectionCheck, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizerBrush->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(GridSizerBrush, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxLimits = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Motor limits"));
	StaticText25 = new wxStaticText(this, ID_STATICTEXT25, _("Min"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
	StaticBoxLimits->Add(StaticText25, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	minLimitEdit = new wxTextCtrl(this, ID_TEXTCTRL6, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
	StaticBoxLimits->Add(minLimitEdit, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxLimits->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText26 = new wxStaticText(this, ID_STATICTEXT26, _("Max"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT26"));
	StaticBoxLimits->Add(StaticText26, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	maxLimitEdit = new wxTextCtrl(this, ID_TEXTCTRL7, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
	StaticBoxLimits->Add(maxLimitEdit, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(StaticBoxLimits, 0, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer8->Add(BoxSizer2, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer8, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	BoxSizer1->Add(StaticLine1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Speed table"));
	speedList = new wxListBox(this, ID_LISTBOX2, wxDefaultPosition, wxSize(-1,90), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX2"));
	StaticBoxSizer5->Add(speedList, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer3 = new wxGridSizer(0, 4, 0, 0);
	GridSizer3->Add(-1,-1,0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText19 = new wxStaticText(this, ID_STATICTEXT19, _("Speed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
	GridSizer3->Add(StaticText19, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText20 = new wxStaticText(this, ID_STATICTEXT20, _("Acceleration"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
	GridSizer3->Add(StaticText20, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText21 = new wxStaticText(this, ID_STATICTEXT21, _("Deceleration"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
	GridSizer3->Add(StaticText21, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText22 = new wxStaticText(this, ID_STATICTEXT22, _("Low"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
	GridSizer3->Add(StaticText22, 0, wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 10);
	speedLEdit = new wxTextCtrl(this, ID_TEXTCTRL15, wxEmptyString, wxDefaultPosition, wxSize(120,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL15"));
	GridSizer3->Add(speedLEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	accLEdit = new wxTextCtrl(this, ID_TEXTCTRL16, wxEmptyString, wxDefaultPosition, wxSize(120,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL16"));
	GridSizer3->Add(accLEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	decLEdit = new wxTextCtrl(this, ID_TEXTCTRL17, wxEmptyString, wxDefaultPosition, wxSize(120,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL17"));
	GridSizer3->Add(decLEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText23 = new wxStaticText(this, ID_STATICTEXT23, _("Normal"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
	GridSizer3->Add(StaticText23, 0, wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 10);
	speedNEdit = new wxTextCtrl(this, ID_TEXTCTRL18, wxEmptyString, wxDefaultPosition, wxSize(120,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL18"));
	GridSizer3->Add(speedNEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	accNEdit = new wxTextCtrl(this, ID_TEXTCTRL19, wxEmptyString, wxDefaultPosition, wxSize(120,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL19"));
	GridSizer3->Add(accNEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	decNEdit = new wxTextCtrl(this, ID_TEXTCTRL20, wxEmptyString, wxDefaultPosition, wxSize(120,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL20"));
	GridSizer3->Add(decNEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText24 = new wxStaticText(this, ID_STATICTEXT24, _("High"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
	GridSizer3->Add(StaticText24, 0, wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 10);
	speedHEdit = new wxTextCtrl(this, ID_TEXTCTRL21, wxEmptyString, wxDefaultPosition, wxSize(120,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL21"));
	GridSizer3->Add(speedHEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	accHEdit = new wxTextCtrl(this, ID_TEXTCTRL22, wxEmptyString, wxDefaultPosition, wxSize(120,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL22"));
	GridSizer3->Add(accHEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	decHEdit = new wxTextCtrl(this, ID_TEXTCTRL23, wxEmptyString, wxDefaultPosition, wxSize(120,19), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL23"));
	GridSizer3->Add(decHEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(GridSizer3, 0, wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer5, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine2 = new wxStaticLine(this, ID_STATICLINE2, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
	BoxSizer1->Add(StaticLine2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("Serial params"));
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Stepper Motors"));
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Port"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	StaticBoxSizer4->Add(StaticText8, 0, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	stepperPortCombo = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxSize(200,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX1"));
	StaticBoxSizer4->Add(stepperPortCombo, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Baud rate"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	StaticBoxSizer4->Add(StaticText9, 0, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 20);
	stepperBaudCombo = new wxComboBox(this, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxSize(110,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX4"));
	StaticBoxSizer4->Add(stepperBaudCombo, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(StaticBoxSizer4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Brushless Motors"));
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Port"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	StaticBoxSizer6->Add(StaticText10, 0, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	brushlessPortCombo = new wxComboBox(this, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxSize(200,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX5"));
	StaticBoxSizer6->Add(brushlessPortCombo, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("Baud rate"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	StaticBoxSizer6->Add(StaticText11, 0, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 20);
	brushlessBaudCombo = new wxComboBox(this, ID_COMBOBOX6, wxEmptyString, wxDefaultPosition, wxSize(110,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX6"));
	StaticBoxSizer6->Add(brushlessBaudCombo, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(StaticBoxSizer6, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4->Add(StaticBoxSizer3, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer_Upload = new wxStaticBoxSizer(wxVERTICAL, this, _("Upload firmware"));
	BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("File name"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	BoxSizer8->Add(StaticText12, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	openFileText = new wxTextCtrl(this, ID_TEXTCTRL8, wxEmptyString, wxDefaultPosition, wxSize(270,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL8"));
	BoxSizer8->Add(openFileText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	openFileBtn = new wxButton(this, ID_BUTTON1, _("..."), wxDefaultPosition, wxSize(27,21), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer8->Add(openFileBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer_Upload->Add(BoxSizer8, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("Driver"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	BoxSizer7->Add(StaticText13, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	driverIdCombo = new wxComboBox(this, ID_COMBOBOX7, wxEmptyString, wxDefaultPosition, wxSize(110,25), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX7"));
	BoxSizer7->Add(driverIdCombo, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	uploadBtn = new wxButton(this, ID_BUTTON2, _("Upload Firmware"), wxDefaultPosition, wxSize(75,33), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer7->Add(uploadBtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer_Upload->Add(BoxSizer7, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4->Add(StaticBoxSizer_Upload, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer4, 0, wxTOP|wxBOTTOM|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	openFileDialog = new wxFileDialog(this, _("Choose a file"), wxEmptyString, wxEmptyString, _("*.enc"), wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&wxMotorsDataPanel::OnmotorsListSelect);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxMotorsDataPanel::OnDirectionCheckClick);
	Connect(ID_LISTBOX2,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&wxMotorsDataPanel::OnspeedListSelect);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMotorsDataPanel::OnopenFileBtnClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMotorsDataPanel::OnuploadBtnClick);
	//*)

	/*
	StaticBoxSizer_Upload->Show( false );
	Layout();
	*/
}

wxMotorsDataPanel::~wxMotorsDataPanel()
{
	//(*Destroy(wxMotorsDataPanel)
	//*)
}


//----------------------------------------------------------------------------------
// Init
// Inizializza il controllo
//----------------------------------------------------------------------------------
int wxMotorsDataPanel::Init( SRMachine* SRRef, SmartLog* smartLoggerRef )
{
	SR = SRRef;
	smartLogger = smartLoggerRef;

	wxArrayString comboLabels;

	// motor
	//---------------------------------------
	comboLabels.Clear();
	comboLabels.Add(_T("TABLE"));
	comboLabels.Add(_T("CAMERA_X"));
	comboLabels.Add(_T("CAMERA_Y"));
	comboLabels.Add(_T("PLATE"));
	comboLabels.Add(_T("SQUEEGEES"));
	comboLabels.Add(_T("LCONV"));
	comboLabels.Add(_T("CCONV"));
	comboLabels.Add(_T("LOADER"));
	comboLabels.Add(_T("CLEANING"));
	driverIdCombo->Append( comboLabels );

	comboLabels.Clear();
	comboLabels.Add(_T("TABLE_1"));
	comboLabels.Add(_T("TABLE_2"));
	comboLabels.Add(_T("TABLE_3"));
	comboLabels.Add(_T("CAMERA_X"));
	comboLabels.Add(_T("CAMERA_Y"));
	comboLabels.Add(_T("PLATE"));
	comboLabels.Add(_T("SQUEEGEES"));
	comboLabels.Add(_T("LCONV_W"));
	comboLabels.Add(_T("LCONV_F"));
	comboLabels.Add(_T("CCONV_W"));
	comboLabels.Add(_T("CCONV_F"));
	comboLabels.Add(_T("LOADER"));
	comboLabels.Add(_T("CLEANING"));
	MACHINE_CONFIG(CONV_PUSH_MOTOR)
		comboLabels.Add(_T("EJECTOR"));
	MACHINE_CONFIG_END
	motorsList->Append( comboLabels );

	comboLabels.Clear();
	comboLabels.Add(_T("1"));
	comboLabels.Add(_T("2"));
	comboLabels.Add(_T("4"));
	comboLabels.Add(_T("8"));
	comboLabels.Add(_T("16"));
	comboLabels.Add(_T("32"));
	comboLabels.Add(_T("64"));
	comboLabels.Add(_T("128"));
	stepCombo->Append( comboLabels );

	GridSizerStepper->Show( true );
	GridSizerBrushless->Show( false );
	GridSizerBrush->Show( false );
	Layout();
	// set initial motor
	motorsList->Select( 0 );
	addressSpin->SetValidator( wxMySpinValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].Address ) );
	minCurEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].MinCurrent, false ) );
	accCurEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].AccCurrent, false ) );
	maxCurEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].MaxCurrent, false ) );
	stepCombo->SetValidator( wxMyComboValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].Microstepping, false ) );
	pulleyEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].Pulley, false ) );
	reductionEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].Reduction, false ) );
	homeFastSEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].HomeFast, false, 0 ) );
	homeSlowSEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].HomeSlow, false, 0 ) );
	minLimitEdit->SetValidator( wxMyTextValidator( &SR->DB->LimitsS[MOTOR_TABLE1_ID].MinLimit, true ) );
	maxLimitEdit->SetValidator( wxMyTextValidator( &SR->DB->LimitsS[MOTOR_TABLE1_ID].MaxLimit, false ) );

	addressBSpin->SetValidator( wxMySpinValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].Address ) );
	curEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].Current, false ) );
	KPSEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].KP_speed, false ) );
	KISEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].KI_speed, false, 4 ) );
	KPPEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].KP_pos, false ) );
	lineEncEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].LineEnc, false ) );
	PTMEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].PulsesToMm, false ) );
	polesEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].Poles, false ) );
	jerkEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].Jerk, false ) );
	KAEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].KA, false ) );
	KSEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].KS, false ) );
	KCEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].KC, false ) );
	homeFastEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].HomeFast, false ) );
	homeSlowEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].HomeSlow, false ) );
	PPREdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].PPR, false ) );
	EndMoveDeltaEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].EndMovementDelta, false ) );
	SpykeDeltaEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].SpykeDelta, false ) );
	redCurEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[MOTOR_TABLE1_ID].RedCurrent, false ) );

	DirectionCheck->SetValue( SR->DB->MotorParamsS[MOTOR_TABLE1_ID].Direction == 0 ? false : true );


	// speed
	//---------------------------------------
	comboLabels.Clear();
	comboLabels.Add(_("Table"));
	comboLabels.Add(_("Camera"));
	comboLabels.Add(_("Plate up"));
	comboLabels.Add(_("Plate down"));
	comboLabels.Add(_("Squeegees"));
	comboLabels.Add(_("Differential disengage"));
	comboLabels.Add(_("Conveyor width"));
	comboLabels.Add(_("Conveyor feed"));
	comboLabels.Add(_("Loader"));
	MACHINE_CONFIG(CONV_PUSH_MOTOR)
			comboLabels.Add(_("Ejector"));
		MACHINE_CONFIG_END
	speedList->Append( comboLabels );

	// set initial speed
	speedList->Select( 0 );
	speedLEdit->SetValidator( wxMyTextValidator( &SR->DB->SpeedTableS[SPEED_TABLE_ID].Speed[0], false ) );
	speedNEdit->SetValidator( wxMyTextValidator( &SR->DB->SpeedTableS[SPEED_TABLE_ID].Speed[1], false ) );
	speedHEdit->SetValidator( wxMyTextValidator( &SR->DB->SpeedTableS[SPEED_TABLE_ID].Speed[2], false ) );
	accLEdit->SetValidator( wxMyTextValidator( &SR->DB->SpeedTableS[SPEED_TABLE_ID].Acc[0], false ) );
	accNEdit->SetValidator( wxMyTextValidator( &SR->DB->SpeedTableS[SPEED_TABLE_ID].Acc[1], false ) );
	accHEdit->SetValidator( wxMyTextValidator( &SR->DB->SpeedTableS[SPEED_TABLE_ID].Acc[2], false ) );
	decLEdit->SetValidator( wxMyTextValidator( &SR->DB->SpeedTableS[SPEED_TABLE_ID].Dec[0], false ) );
	decNEdit->SetValidator( wxMyTextValidator( &SR->DB->SpeedTableS[SPEED_TABLE_ID].Dec[1], false ) );
	decHEdit->SetValidator( wxMyTextValidator( &SR->DB->SpeedTableS[SPEED_TABLE_ID].Dec[2], false ) );


	// serial
	//---------------------------------------

	comboLabels.Clear();

#ifdef __WXMSW__
	for( int i = 1; i <= 15; i++ )
		comboLabels.Add( wxString::Format( _T("COM%d"), i ) );
#else
	struct stat sb;
	wxString devName;

	for( int i = 0; i < 15; i++ )
	{
		devName = wxString::Format( wxT("//dev//ttyUSB%d"), i );
		if( stat( devName.ToAscii(), &sb ) == 0 )
		{
			comboLabels.Add( devName );
		}
	}
#endif

	stepperPortCombo->Append( comboLabels );
	brushlessPortCombo->Append( comboLabels );

	// Baud rate
	comboLabels.Clear();
	comboLabels.Add(_T("9600"));
	comboLabels.Add(_T("19200"));
	comboLabels.Add(_T("38400"));
	comboLabels.Add(_T("57600"));
	comboLabels.Add(_T("115200"));
	comboLabels.Add(_T("230400"));
	comboLabels.Add(_T("460800"));
	stepperBaudCombo->Append( comboLabels );
	brushlessBaudCombo->Append( comboLabels );

	// Set validators
	stepperPortCombo->SetValidator( wxMyComboValidator( &SR->DB->SerialParamsS[DRIVER_STEPPER_ID].SerialPort ) );
	stepperBaudCombo->SetValidator( wxMyComboValidator( &SR->DB->SerialParamsS[DRIVER_STEPPER_ID].SerialSpeed, false ) );
	brushlessPortCombo->SetValidator( wxMyComboValidator( &SR->DB->SerialParamsS[DRIVER_BRUSHLESS_ID].SerialPort ) );
	brushlessBaudCombo->SetValidator( wxMyComboValidator( &SR->DB->SerialParamsS[DRIVER_BRUSHLESS_ID].SerialSpeed, false ) );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// ShowControl
// Mostra il controllo a video
//----------------------------------------------------------------------------------
int wxMotorsDataPanel::ShowControl( )
{
	TransferDataToWindow();
	return SR_OK;
}

//----------------------------------------------------------------------------------
// HideControl
// Nasconde il controllo
//----------------------------------------------------------------------------------
int wxMotorsDataPanel::HideControl( )
{
	TransferDataFromWindow();
	SR->DB->SaveMotorParams();
	SR->DB->SaveLimits();
	SR->DB->SaveSpeedTable();
	SR->DB->SaveSerialParams();
	return SR_OK;
}

void wxMotorsDataPanel::OnmotorsListSelect(wxCommandEvent& event)
{
	TransferDataFromWindow();

	int motor_id = -1;

	switch( event.GetSelection() )
	{
	case 0 :motor_id = MOTOR_TABLE1_ID;			break;
	case 1 :motor_id = MOTOR_TABLE2_ID;			break;
	case 2 :motor_id = MOTOR_TABLE3_ID;			break;
	case 3 :motor_id = MOTOR_CAMERAX_ID;		break;
	case 4 :motor_id = MOTOR_CAMERAY_ID;		break;
	case 5 :motor_id = MOTOR_PLATE_ID;			break;
	case 6 :motor_id = MOTOR_SQUEEGEES_ID;		break;
	case 7 :motor_id = MOTOR_LCONV_WIDTH_ID;	break;
	case 8 :motor_id = MOTOR_LCONV_FEED_ID;		break;
	case 9 :motor_id = MOTOR_CCONV_WIDTH_ID;	break;
	case 10:motor_id = MOTOR_CCONV_FEED_ID;		break;
	case 11:motor_id = MOTOR_LOADER_ID;			break;
	case 12:motor_id = MOTOR_CLEANING_ID;		break;
	case 13:motor_id = MOTOR_LCONV_PUSH_ID;		break;
	default: return;
	}

	if( SR->DB->MotorParamsS[motor_id].Driver == DRIVER_STEPPER_ID )
	{
		GridSizerStepper->Show( true );
		GridSizerBrushless->Show( false );
		GridSizerBrush->Show( false );
		StaticBoxLimits->Show( true );

		addressSpin->SetValidator( wxMySpinValidator( &SR->DB->MotorParamsS[motor_id].Address ) );
		minCurEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].MinCurrent, false ) );
		accCurEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].AccCurrent, false ) );
		maxCurEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].MaxCurrent, false ) );
		stepCombo->SetValidator( wxMyComboValidator( &SR->DB->MotorParamsS[motor_id].Microstepping, false ) );
		pulleyEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].Pulley, false ) );
		reductionEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].Reduction, false ) );
		homeFastSEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].HomeFast, false, 0 ) );
		homeSlowSEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].HomeSlow, false, 0 ) );
	}
	else if( SR->DB->MotorParamsS[motor_id].Driver == DRIVER_BRUSHLESS_ID )
	{
		GridSizerStepper->Show( false );
		GridSizerBrushless->Show( true );
		GridSizerBrush->Show( false );
		StaticBoxLimits->Show( true );

		addressBSpin->SetValidator( wxMySpinValidator( &SR->DB->MotorParamsS[motor_id].Address ) );
		curEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].Current, false ) );
		KPSEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].KP_speed, false ) );
		KISEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].KI_speed, false, 4 ) );
		KPPEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].KP_pos, false ) );
		lineEncEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].LineEnc, false ) );
		PTMEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].PulsesToMm, false ) );
		polesEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].Poles, false ) );
		jerkEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].Jerk, false ) );
		KAEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].KA, false ) );
		KSEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].KS, false ) );
		KCEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].KC, false ) );
		homeFastEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].HomeFast, false ) );
		homeSlowEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].HomeSlow, false ) );
		PPREdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].PPR, false ) );
		EndMoveDeltaEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].EndMovementDelta, false ) );
		SpykeDeltaEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].SpykeDelta, false ) );
		redCurEdit->SetValidator( wxMyTextValidator( &SR->DB->MotorParamsS[motor_id].RedCurrent, false ) );
	}
	else
	{
		GridSizerStepper->Show( false );
		GridSizerBrushless->Show( false );
		GridSizerBrush->Show( true );
		StaticBoxLimits->Show( false );

		AddressBrushSpin->SetValidator( wxMySpinValidator( &SR->DB->MotorParamsS[motor_id].Address ) );
		DirectionCheck->SetValue( SR->DB->MotorParamsS[motor_id].Direction == 0 ? false : true );
	}
	Layout();
	this->Refresh();

	minCurEdit->Enable( true );
	accCurEdit->Enable( true );
	maxCurEdit->Enable( true );
	stepCombo->Enable( true );
	pulleyEdit->Enable( true );
	reductionEdit->Enable( true );
	minLimitEdit->Enable( true );
	maxLimitEdit->Enable( true );
	homeFastSEdit->Enable( true );
	homeSlowSEdit->Enable( true );

	minLimitEdit->SetValidator( wxMyTextValidator( &SR->DB->LimitsS[motor_id].MinLimit, true ) );
	maxLimitEdit->SetValidator( wxMyTextValidator( &SR->DB->LimitsS[motor_id].MaxLimit, false ) );

	TransferDataToWindow();
}

void wxMotorsDataPanel::OnspeedListSelect(wxCommandEvent& event)
{
	TransferDataFromWindow();

	int speed_id = -1;

	switch( event.GetSelection() )
	{
		case 0:	speed_id = SPEED_TABLE_ID;		break;
		case 1:	speed_id = SPEED_CAMERA_ID;		break;
		case 2:	speed_id = SPEED_PLATE_UP_ID;	break;
		case 3:	speed_id = SPEED_PLATE_DOWN_ID;	break;
		case 4:	speed_id = SPEED_SQUEEGEES_ID;	break;
		case 5:	speed_id = SPEED_DISENGAGE_ID;	break;
		case 6:	speed_id = SPEED_CONV_WIDTH_ID;	break;
		case 7:	speed_id = SPEED_CONV_FEED_ID;	break;
		case 8:	speed_id = SPEED_LOADER_ID;		break;
		case 9:	speed_id = SPEED_CONV_PUSH_ID;  break;
		default: return;
	}

	speedLEdit->SetValidator( wxMyTextValidator( &SR->DB->SpeedTableS[speed_id].Speed[0], false ) );
	speedNEdit->SetValidator( wxMyTextValidator( &SR->DB->SpeedTableS[speed_id].Speed[1], false ) );
	speedHEdit->SetValidator( wxMyTextValidator( &SR->DB->SpeedTableS[speed_id].Speed[2], false ) );
	accLEdit->SetValidator( wxMyTextValidator( &SR->DB->SpeedTableS[speed_id].Acc[0], false ) );
	accNEdit->SetValidator( wxMyTextValidator( &SR->DB->SpeedTableS[speed_id].Acc[1], false ) );
	accHEdit->SetValidator( wxMyTextValidator( &SR->DB->SpeedTableS[speed_id].Acc[2], false ) );
	decLEdit->SetValidator( wxMyTextValidator( &SR->DB->SpeedTableS[speed_id].Dec[0], false ) );
	decNEdit->SetValidator( wxMyTextValidator( &SR->DB->SpeedTableS[speed_id].Dec[1], false ) );
	decHEdit->SetValidator( wxMyTextValidator( &SR->DB->SpeedTableS[speed_id].Dec[2], false ) );

	TransferDataToWindow();
}

void wxMotorsDataPanel::OnopenFileBtnClick(wxCommandEvent& event)
{
	if( driverIdCombo->GetSelection() == -1 )
	{
        smartLogger->Write( MSG_DRIVERSELECT );
        return;
	}

	// Retrieve driverId
	int motor_id = -1;
	switch( driverIdCombo->GetSelection() )
	{
		case 0 :motor_id = MOTOR_TABLE1_ID;			break;
		case 1 :motor_id = MOTOR_CAMERAX_ID;		break;
		case 2 :motor_id = MOTOR_CAMERAY_ID;		break;
		case 3 :motor_id = MOTOR_PLATE_ID;			break;
		case 4 :motor_id = MOTOR_SQUEEGEES_ID;		break;
		case 5 :motor_id = MOTOR_LCONV_WIDTH_ID;	break;
		case 6 :motor_id = MOTOR_CCONV_WIDTH_ID;	break;
		case 7 :motor_id = MOTOR_LOADER_ID;			break;
		case 8 :motor_id = MOTOR_CLEANING_ID;		break;
		default: return;
	}

	if( SR->DB->MotorParamsS[motor_id].Driver == DRIVER_STEPPER_ID )
		openFileDialog->SetWildcard( "*.stx" );
	else
		openFileDialog->SetWildcard( "*.brx" );

	if( openFileDialog->ShowModal() )
        openFileText->SetValue( openFileDialog->GetPath() );
}

void wxMotorsDataPanel::OnuploadBtnClick(wxCommandEvent& event)
{
	if( SR->GetMachineState() )
	{
		smartLogger->Write( MSG_DEACTIVATETOUPDATE, MSG_ERROR );
		return;
	}

	if( openFileText->IsEmpty() )
    {
        smartLogger->Write( MSG_FIRMWARESELECT );
        return;
    }

	// open file
    wxFile *inFile = new wxFile( openFileText->GetValue(), wxFile::read );

    if( !inFile->IsOpened() )
	{
        // clear
		delete inFile;

		smartLogger->Write( MSG_FILEOPENERROR, MSG_ERROR );
		return;
	}

	// Open serial port
	if( SR->OpenSerialCom() == SR_ERROR )
	{
		// Clear
		inFile->Close();
		delete inFile;

		SR->ErrorManagement();
		return;
	}

	// Retrieve driverId
	int motor_id = -1;
	switch( driverIdCombo->GetSelection() )
	{
		case 0 :motor_id = MOTOR_TABLE1_ID;			break;
		case 1 :motor_id = MOTOR_CAMERAX_ID;		break;
		case 2 :motor_id = MOTOR_CAMERAY_ID;		break;
		case 3 :motor_id = MOTOR_PLATE_ID;			break;
		case 4 :motor_id = MOTOR_SQUEEGEES_ID;		break;
		case 5 :motor_id = MOTOR_LCONV_WIDTH_ID;	break;
		case 6 :motor_id = MOTOR_CCONV_WIDTH_ID;	break;
		case 7 :motor_id = MOTOR_LOADER_ID;			break;
		case 8 :motor_id = MOTOR_CLEANING_ID;		break;
		default: return;
	}

	// Upload
	SR->UpdateDriver( motor_id, inFile );

	// Clear
	inFile->Close();
	delete inFile;

	// Close serial port
	if( SR->CloseSerialCom() == SR_ERROR )
	{
		SR->ErrorManagement();
	}
}

void wxMotorsDataPanel::OnDirectionCheckClick(wxCommandEvent& event)
{
	// Retrieve driverId
	int motor_id = -1;
	switch( motorsList->GetSelection() )
	{
		case 0 :motor_id = MOTOR_TABLE1_ID;			break;
		case 1 :motor_id = MOTOR_TABLE2_ID;			break;
		case 2 :motor_id = MOTOR_TABLE3_ID;			break;
		case 3 :motor_id = MOTOR_CAMERAX_ID;		break;
		case 4 :motor_id = MOTOR_CAMERAY_ID;		break;
		case 5 :motor_id = MOTOR_PLATE_ID;			break;
		case 6 :motor_id = MOTOR_SQUEEGEES_ID;		break;
		case 7 :motor_id = MOTOR_LCONV_WIDTH_ID;	break;
		case 8 :motor_id = MOTOR_LCONV_FEED_ID;		break;
		case 9 :motor_id = MOTOR_CCONV_WIDTH_ID;	break;
		case 10:motor_id = MOTOR_CCONV_FEED_ID;		break;
		case 11:motor_id = MOTOR_LOADER_ID;			break;
		case 12:motor_id = MOTOR_CLEANING_ID;		break;
		case 13:motor_id = MOTOR_LCONV_PUSH_ID;		break;
		default: return;
	}

	SR->DB->MotorParamsS[motor_id].Direction = event.GetInt() ? 1 : 0;
}

#include "wxAdvancedParamsPanel.h"

//(*InternalHeaders(wxAdvancedParamsPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "wxMyTextValidator.h"
#include "wxMyComboValidator.h"

//(*IdInit(wxAdvancedParamsPanel)
const long wxAdvancedParamsPanel::ID_STATICTEXT6 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL4 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT7 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL5 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT4 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL23 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT5 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL24 = wxNewId();
const long wxAdvancedParamsPanel::ID_BUTTON2 = wxNewId();
const long wxAdvancedParamsPanel::ID_BUTTON1 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT12 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL9 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT13 = wxNewId();
const long wxAdvancedParamsPanel::ID_CHECKBOX1 = wxNewId();
const long wxAdvancedParamsPanel::ID_CHECKBOX2 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT3 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL2 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL3 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT16 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL11 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT17 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL12 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT19 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL13 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT20 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL14 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT18 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL10 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT24 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL17 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT25 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL18 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT26 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL19 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT1 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL1 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT2 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL6 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT9 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL7 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT10 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL8 = wxNewId();
const long wxAdvancedParamsPanel::ID_CHECKBOX3 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT11 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL22 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT22 = wxNewId();
const long wxAdvancedParamsPanel::ID_COMBOBOX5 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT28 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL20 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT23 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL15 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT29 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL21 = wxNewId();
const long wxAdvancedParamsPanel::ID_STATICTEXT27 = wxNewId();
const long wxAdvancedParamsPanel::ID_TEXTCTRL16 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxAdvancedParamsPanel,wxPanel)
	//(*EventTable(wxAdvancedParamsPanel)
	//*)
END_EVENT_TABLE()

wxAdvancedParamsPanel::wxAdvancedParamsPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxAdvancedParamsPanel)
	wxBoxSizer* BoxSizer4;
	wxStaticBoxSizer* StaticBoxSizer2;
	wxGridSizer* GridSizer4;
	wxGridSizer* GridSizer15;
	wxGridSizer* GridSizer10;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxGridSizer* GridSizer13;
	wxGridSizer* GridSizer11;
	wxGridSizer* GridSizer18;
	wxGridSizer* GridSizer5;
	wxGridSizer* GridSizer7;
	wxGridSizer* GridSizer8;
	wxStaticBoxSizer* StaticBoxSizer9;
	wxBoxSizer* BoxSizer2;
	wxStaticBoxSizer* StaticBoxSizer7;
	wxStaticBoxSizer* StaticBoxSizer10;
	wxGridSizer* GridSizer16;
	wxGridSizer* GridSizer9;
	wxGridSizer* GridSizer6;
	wxGridSizer* GridSizer19;
	wxStaticBoxSizer* StaticBoxSizer8;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxGridSizer* GridSizer1;
	wxStaticBoxSizer* StaticBoxSizer6;
	wxGridSizer* GridSizer3;
	wxStaticBoxSizer* StaticBoxSizer11;
	wxBoxSizer* BoxSizer1;
	wxGridSizer* GridSizer14;
	wxGridSizer* GridSizer17;
	wxGridSizer* GridSizer12;
	wxStaticBoxSizer* StaticBoxSizer5;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Plate"));
	GridSizer3 = new wxGridSizer(0, 4, 0, 0);
	GridSizer4 = new wxGridSizer(0, 2, 0, 0);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Movement (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	GridSizer4->Add(StaticText6, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	plateMovementEdit = new wxTextCtrl(this, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	GridSizer4->Add(plateMovementEdit, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Zero Movement (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	GridSizer4->Add(StaticText7, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	plateZeroMovementEdit = new wxTextCtrl(this, ID_TEXTCTRL5, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	GridSizer4->Add(plateZeroMovementEdit, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer3->Add(GridSizer4, 0, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	GridSizer1 = new wxGridSizer(0, 2, 0, 0);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Global Offset X"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	GridSizer1->Add(StaticText4, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GlobalOffsetXInput = new wxTextCtrl(this, ID_TEXTCTRL23, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL23"));
	GridSizer1->Add(GlobalOffsetXInput, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Global Offset Y"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	GridSizer1->Add(StaticText5, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GlobalOffsetYInput = new wxTextCtrl(this, ID_TEXTCTRL24, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL24"));
	GridSizer1->Add(GlobalOffsetYInput, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer3->Add(GridSizer1, 0, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	setGlobaloffsetButton = new wxButton(this, ID_BUTTON2, _("Reset Prod Offset"), wxPoint(0,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	GridSizer3->Add(setGlobaloffsetButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button1 = new wxButton(this, ID_BUTTON1, _("Correct Offset Map"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	GridSizer3->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(GridSizer3, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("Camera"));
	GridSizer6 = new wxGridSizer(0, 2, 0, 0);
	GridSizer7 = new wxGridSizer(0, 2, 0, 0);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Focal height (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	GridSizer7->Add(StaticText12, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	focalHeightEdit = new wxTextCtrl(this, ID_TEXTCTRL9, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL9"));
	GridSizer7->Add(focalHeightEdit, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("Flip"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	GridSizer7->Add(StaticText13, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	flipXCheck = new wxCheckBox(this, ID_CHECKBOX1, _("X"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	flipXCheck->SetValue(false);
	BoxSizer4->Add(flipXCheck, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	flipYCheck = new wxCheckBox(this, ID_CHECKBOX2, _("Y"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	flipYCheck->SetValue(false);
	BoxSizer4->Add(flipYCheck, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer7->Add(BoxSizer4, 0, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Conveyor edge (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	GridSizer7->Add(StaticText3, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	convEdgeXEdit = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer2->Add(convEdgeXEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	convEdgeYEdit = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	BoxSizer2->Add(convEdgeYEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer7->Add(BoxSizer2, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer6->Add(GridSizer7, 0, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticBoxSizer7 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Constants mm/pixels"));
	GridSizer5 = new wxGridSizer(0, 4, 0, 0);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT16, _("X Up"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	GridSizer5->Add(StaticText16, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	upXEdit = new wxTextCtrl(this, ID_TEXTCTRL11, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL11"));
	GridSizer5->Add(upXEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText17 = new wxStaticText(this, ID_STATICTEXT17, _("Y Up"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	GridSizer5->Add(StaticText17, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	upYEdit = new wxTextCtrl(this, ID_TEXTCTRL12, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL12"));
	GridSizer5->Add(upYEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText19 = new wxStaticText(this, ID_STATICTEXT19, _("X Down"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
	GridSizer5->Add(StaticText19, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	downXEdit = new wxTextCtrl(this, ID_TEXTCTRL13, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL13"));
	GridSizer5->Add(downXEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText20 = new wxStaticText(this, ID_STATICTEXT20, _("Y Down"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
	GridSizer5->Add(StaticText20, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	downYEdit = new wxTextCtrl(this, ID_TEXTCTRL14, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL14"));
	GridSizer5->Add(downYEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer7->Add(GridSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer6->Add(StaticBoxSizer7, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(GridSizer6, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxVERTICAL, this, _("Squeegees"));
	GridSizer9 = new wxGridSizer(0, 2, 0, 0);
	GridSizer10 = new wxGridSizer(0, 2, 0, 0);
	StaticText18 = new wxStaticText(this, ID_STATICTEXT18, _("Default Zero Movement (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
	GridSizer10->Add(StaticText18, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	squeegeesDefZeroEdit = new wxTextCtrl(this, ID_TEXTCTRL10, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL10"));
	GridSizer10->Add(squeegeesDefZeroEdit, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer9->Add(GridSizer10, 0, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticBoxSizer4->Add(GridSizer9, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer4, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxVERTICAL, this, _("Table"));
	GridSizer8 = new wxGridSizer(0, 2, 0, 0);
	GridSizer12 = new wxGridSizer(0, 2, 0, 0);
	StaticText24 = new wxStaticText(this, ID_STATICTEXT24, _("Zero Movement 1 (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
	GridSizer12->Add(StaticText24, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	tableZeroMovement1Edit = new wxTextCtrl(this, ID_TEXTCTRL17, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL17"));
	GridSizer12->Add(tableZeroMovement1Edit, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText25 = new wxStaticText(this, ID_STATICTEXT25, _("Zero Movement 2 (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
	GridSizer12->Add(StaticText25, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	tableZeroMovement2Edit = new wxTextCtrl(this, ID_TEXTCTRL18, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL18"));
	GridSizer12->Add(tableZeroMovement2Edit, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText26 = new wxStaticText(this, ID_STATICTEXT26, _("Zero Movement 3 (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT26"));
	GridSizer12->Add(StaticText26, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	tableZeroMovement3Edit = new wxTextCtrl(this, ID_TEXTCTRL19, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL19"));
	GridSizer12->Add(tableZeroMovement3Edit, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer8->Add(GridSizer12, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(GridSizer8, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer5, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer8 = new wxStaticBoxSizer(wxVERTICAL, this, _("Conveyors"));
	GridSizer11 = new wxGridSizer(0, 2, 0, 0);
	StaticBoxSizer10 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Left Conveyor"));
	GridSizer16 = new wxGridSizer(0, 2, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Movement (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	GridSizer16->Add(StaticText1, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lConvMovementEdit = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	GridSizer16->Add(lConvMovementEdit, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Zero Movement (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	GridSizer16->Add(StaticText2, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lConvZeroMovementEdit = new wxTextCtrl(this, ID_TEXTCTRL6, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
	GridSizer16->Add(lConvZeroMovementEdit, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer10->Add(GridSizer16, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer11->Add(StaticBoxSizer10, 0, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticBoxSizer11 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Center Conveyor"));
	GridSizer17 = new wxGridSizer(0, 2, 0, 0);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Movement (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	GridSizer17->Add(StaticText9, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	cConvMovementEdit = new wxTextCtrl(this, ID_TEXTCTRL7, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
	GridSizer17->Add(cConvMovementEdit, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Zero Movement (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	GridSizer17->Add(StaticText10, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	cConvZeroMovementEdit = new wxTextCtrl(this, ID_TEXTCTRL8, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
	GridSizer17->Add(cConvZeroMovementEdit, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer11->Add(GridSizer17, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	InputSensorCheckBox = new wxCheckBox(this, ID_CHECKBOX3, _("Input Sensor"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	InputSensorCheckBox->SetValue(true);
	StaticBoxSizer11->Add(InputSensorCheckBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer11->Add(StaticBoxSizer11, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticBoxSizer8->Add(GridSizer11, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer8, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer9 = new wxStaticBoxSizer(wxVERTICAL, this, _("Loader"));
	GridSizer18 = new wxGridSizer(0, 2, 0, 0);
	GridSizer19 = new wxGridSizer(0, 2, 0, 0);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("Loading Position (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	GridSizer19->Add(StaticText11, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	loaderAdjPositionEdit = new wxTextCtrl(this, ID_TEXTCTRL22, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL22"));
	GridSizer19->Add(loaderAdjPositionEdit, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer18->Add(GridSizer19, 0, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticBoxSizer9->Add(GridSizer18, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer9, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer6 = new wxStaticBoxSizer(wxVERTICAL, this, _("Vision"));
	GridSizer13 = new wxGridSizer(0, 2, 0, 0);
	GridSizer14 = new wxGridSizer(0, 2, 0, 0);
	StaticText22 = new wxStaticText(this, ID_STATICTEXT22, _("Smooth Method"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
	GridSizer14->Add(StaticText22, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	smoothMethodCombo = new wxComboBox(this, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxSize(120,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX5"));
	GridSizer14->Add(smoothMethodCombo, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText28 = new wxStaticText(this, ID_STATICTEXT28, _("FPS"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT28"));
	GridSizer14->Add(StaticText28, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	fpsEdit = new wxTextCtrl(this, ID_TEXTCTRL20, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL20"));
	GridSizer14->Add(fpsEdit, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer13->Add(GridSizer14, 0, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	GridSizer15 = new wxGridSizer(0, 2, 0, 0);
	StaticText23 = new wxStaticText(this, ID_STATICTEXT23, _("Circle Accumulator"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
	GridSizer15->Add(StaticText23, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	circleAccumEdit = new wxTextCtrl(this, ID_TEXTCTRL15, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL15"));
	GridSizer15->Add(circleAccumEdit, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText29 = new wxStaticText(this, ID_STATICTEXT29, _("Rectangle Accumulator"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT29"));
	GridSizer15->Add(StaticText29, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	rectangleAccumEdit = new wxTextCtrl(this, ID_TEXTCTRL21, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL21"));
	GridSizer15->Add(rectangleAccumEdit, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText27 = new wxStaticText(this, ID_STATICTEXT27, _("Search Area Mul."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
	GridSizer15->Add(StaticText27, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	searchAreaEdit = new wxTextCtrl(this, ID_TEXTCTRL16, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL16"));
	GridSizer15->Add(searchAreaEdit, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer13->Add(GridSizer15, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer6->Add(GridSizer13, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer6, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_TEXTCTRL24,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&wxAdvancedParamsPanel::OnTextCtrl2Text);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxAdvancedParamsPanel::OnsetGlobaloffsetButtonClick);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxAdvancedParamsPanel::OnCorrectOffssetmapButtonClick);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxAdvancedParamsPanel::OnflipXCheckClick);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxAdvancedParamsPanel::OnflipYCheckClick);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxAdvancedParamsPanel::OnInputSensorCheckedChanged);
	//*)
}

wxAdvancedParamsPanel::~wxAdvancedParamsPanel()
{
	//(*Destroy(wxAdvancedParamsPanel)
	//*)
}

//----------------------------------------------------------------------------------
// Init
// Inizializza il controllo
//----------------------------------------------------------------------------------
int wxAdvancedParamsPanel::Init( SRDatabase* DBRef, SmartLog* smartLoggerRef )
{
	DB = DBRef;
	smartLogger = smartLoggerRef;

	// init combo labels
	wxArrayString comboLabels;

	comboLabels.Add(wxT("BLUR"));
	comboLabels.Add(wxT("GAUSSIAN"));

	smoothMethodCombo->Append( comboLabels );

	// set validators
	plateZeroMovementEdit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.PlateZeroMovement ) );
	focalHeightEdit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.CameraFocus, false ) );
	upXEdit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.UpXPixMm, false, 6 ) );
	upYEdit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.UpYPixMm, false, 6 ) );
	downXEdit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.DnXPixMm, false, 6 ) );
	downYEdit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.DnYPixMm, false, 6 ) );
	tableZeroMovement1Edit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.TableZeroMovement1 ) );
	tableZeroMovement2Edit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.TableZeroMovement2 ) );
	tableZeroMovement3Edit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.TableZeroMovement3 ) );
	plateMovementEdit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.PlateMovement ) );
	squeegeesDefZeroEdit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.SqueegeesDefZeroMove ) );
	smoothMethodCombo->SetValidator( wxMyComboValidator( &DB->pCurrentFiducial->FilterSmoothType ) );
	fpsEdit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.FPS, false ) );
	circleAccumEdit->SetValidator( wxMyTextValidator( &DB->pCurrentFiducial->CircleAccum, false ) );
	rectangleAccumEdit->SetValidator( wxMyTextValidator( &DB->pCurrentFiducial->RectangleAccum, false ) );
	searchAreaEdit->SetValidator( wxMyTextValidator( &DB->pCurrentFiducial->SearchAreaMul, false ) );
	lConvZeroMovementEdit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.LConvZeroMovement ) );
	lConvMovementEdit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.LConvMovement ) );
	cConvZeroMovementEdit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.CConvZeroMovement ) );
	cConvMovementEdit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.CConvMovement ) );
	loaderAdjPositionEdit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.LoaderAdjPosition ) );
	convEdgeXEdit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.ConvEdgeX ) );
	convEdgeYEdit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.ConvEdgeY ) );

	GlobalOffsetXInput->SetValidator(wxMyTextValidator( &DB->GlobalOffset.X));
	GlobalOffsetYInput->SetValidator(wxMyTextValidator( &DB->GlobalOffset.Y));

	// init flip checks
	flipXCheck->SetValue( DB->MachineParamsS.ImageFlip & 0x002 ? true : false );
	flipYCheck->SetValue( DB->MachineParamsS.ImageFlip & 0x001 ? true : false );


	return SR_OK;
}

//----------------------------------------------------------------------------------
// ShowControl
// Mostra il controllo a video
//----------------------------------------------------------------------------------
int wxAdvancedParamsPanel::ShowControl( )
{
	TransferDataToWindow();
	return SR_OK;
}

//----------------------------------------------------------------------------------
// HideControl
// Nasconde il controllo
//----------------------------------------------------------------------------------
int wxAdvancedParamsPanel::HideControl( )
{
	TransferDataFromWindow();

	// sets the same value for all fiducials
	for( int i = 0; i < NUM_FIDUCIALS; i++ )
	{
		DB->FiducialParamsS[i].FilterSmoothType	= DB->pCurrentFiducial->FilterSmoothType;
		DB->FiducialParamsS[i].CircleAccum		= DB->pCurrentFiducial->CircleAccum;
		DB->FiducialParamsS[i].RectangleAccum	= DB->pCurrentFiducial->RectangleAccum;
		DB->FiducialParamsS[i].SearchAreaMul	= DB->pCurrentFiducial->SearchAreaMul;
	}

	DB->SaveFiducialParams();
	DB->SaveMachineParams();
	DB->SaveCurrentGlobalOffsetValues();
	return SR_OK;
}

void wxAdvancedParamsPanel::OnflipXCheckClick(wxCommandEvent& event)
{
	if( event.IsChecked() )
		DB->MachineParamsS.ImageFlip = DB->MachineParamsS.ImageFlip | 0x0002;
	else
		DB->MachineParamsS.ImageFlip = DB->MachineParamsS.ImageFlip & 0xFFFD;
}

void wxAdvancedParamsPanel::OnflipYCheckClick(wxCommandEvent& event)
{
	if( event.IsChecked() )
		DB->MachineParamsS.ImageFlip = DB->MachineParamsS.ImageFlip | 0x0001;
	else
		DB->MachineParamsS.ImageFlip = DB->MachineParamsS.ImageFlip & 0xFFFE;
}

void wxAdvancedParamsPanel::OnCheckBox1Click(wxCommandEvent& event)
{
}

void wxAdvancedParamsPanel::OnInputSensorCheckedChanged(wxCommandEvent& event)
{
	if( event.IsChecked() ){
		DB->WorkingModesS.InputSensorEnabled = true;
	}
	else{
		if( wxMessageBox( MSG_DISABLESECURITYSERROR, MACHINE_NAME, wxYES_NO | wxICON_QUESTION ) == wxYES ){
			DB->WorkingModesS.InputSensorEnabled = false;
		}else{
			DB->WorkingModesS.InputSensorEnabled = true;
			InputSensorCheckBox->SetValue(true);
		}

	}

}

void wxAdvancedParamsPanel::OnCorrectOffssetmapButtonClick(wxCommandEvent& event)
{
	if( wxMessageBox( MSG_CORRECTOFFSETMAP, MACHINE_NAME, wxYES_NO | wxICON_QUESTION ) == wxYES ){
		DB->CorrectOffsetPoints();
	}
}

void wxAdvancedParamsPanel::OnTextCtrl2Text(wxCommandEvent& event)
{
}

void wxAdvancedParamsPanel::OnsetGlobaloffsetButtonClick(wxCommandEvent& event)
{
	DB->ResetProductionOffsetValues();
}

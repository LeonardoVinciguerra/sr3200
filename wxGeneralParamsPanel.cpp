#include "wxSR3200App.h"
#include "wxGeneralParamsPanel.h"

//(*InternalHeaders(wxGeneralParamsPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/msgdlg.h>
#include "wxMyTextValidator.h"
#include "wxMyComboValidator.h"
#include "Messages.h"
#include "GlobalEnum.h"

//(*IdInit(wxGeneralParamsPanel)
const long wxGeneralParamsPanel::ID_STATICTEXT1 = wxNewId();
const long wxGeneralParamsPanel::ID_TEXTCTRL1 = wxNewId();
const long wxGeneralParamsPanel::ID_STATICTEXT5 = wxNewId();
const long wxGeneralParamsPanel::ID_COMBOBOX2 = wxNewId();
const long wxGeneralParamsPanel::ID_STATICTEXT8 = wxNewId();
const long wxGeneralParamsPanel::ID_COMBOBOX6 = wxNewId();
const long wxGeneralParamsPanel::ID_STATICTEXT11 = wxNewId();
const long wxGeneralParamsPanel::ID_COMBOBOX3 = wxNewId();
const long wxGeneralParamsPanel::ID_CHECKBOX3 = wxNewId();
const long wxGeneralParamsPanel::ID_STATICTEXT21 = wxNewId();
const long wxGeneralParamsPanel::ID_COMBOBOX4 = wxNewId();
const long wxGeneralParamsPanel::ID_STATICTEXT6 = wxNewId();
const long wxGeneralParamsPanel::ID_COMBOBOX8 = wxNewId();
const long wxGeneralParamsPanel::ID_STATICTEXT7 = wxNewId();
const long wxGeneralParamsPanel::ID_COMBOBOX9 = wxNewId();
const long wxGeneralParamsPanel::ID_CHECKBOX2 = wxNewId();
const long wxGeneralParamsPanel::ID_STATICTEXT4 = wxNewId();
const long wxGeneralParamsPanel::ID_COMBOBOX7 = wxNewId();
const long wxGeneralParamsPanel::ID_STATICTEXT2 = wxNewId();
const long wxGeneralParamsPanel::ID_TEXTCTRL6 = wxNewId();
const long wxGeneralParamsPanel::ID_STATICTEXT9 = wxNewId();
const long wxGeneralParamsPanel::ID_TEXTCTRL2 = wxNewId();
const long wxGeneralParamsPanel::ID_CHECKBOX1 = wxNewId();
const long wxGeneralParamsPanel::ID_STATICTEXT10 = wxNewId();
const long wxGeneralParamsPanel::ID_TEXTCTRL5 = wxNewId();
const long wxGeneralParamsPanel::ID_STATICTEXT16 = wxNewId();
const long wxGeneralParamsPanel::ID_TEXTCTRL4 = wxNewId();
const long wxGeneralParamsPanel::ID_CHECKBOX4 = wxNewId();
const long wxGeneralParamsPanel::ID_CHECKBOX5 = wxNewId();
const long wxGeneralParamsPanel::ID_STATICTEXT3 = wxNewId();
const long wxGeneralParamsPanel::ID_COMBOBOX5 = wxNewId();
const long wxGeneralParamsPanel::ID_STATICTEXT12 = wxNewId();
const long wxGeneralParamsPanel::ID_COLOURPICKERCTRL1 = wxNewId();
const long wxGeneralParamsPanel::ID_STATICTEXT13 = wxNewId();
const long wxGeneralParamsPanel::ID_COLOURPICKERCTRL2 = wxNewId();
const long wxGeneralParamsPanel::ID_STATICTEXT14 = wxNewId();
const long wxGeneralParamsPanel::ID_COLOURPICKERCTRL3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxGeneralParamsPanel,wxPanel)
	//(*EventTable(wxGeneralParamsPanel)
	//*)
END_EVENT_TABLE()

wxGeneralParamsPanel::wxGeneralParamsPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxGeneralParamsPanel)
	wxBoxSizer* BoxSizer4;
	wxStaticBoxSizer* StaticBoxSizer2;
	wxBoxSizer* BoxSizer6;
	wxGridSizer* GridSizer4;
	wxBoxSizer* BoxSizer15;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer10;
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* BoxSizer8;
	wxBoxSizer* BoxSizer13;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxGridSizer* GridSizer8;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer11;
	wxBoxSizer* BoxSizer16;
	wxBoxSizer* BoxSizer12;
	wxBoxSizer* BoxSizer14;
	wxGridSizer* GridSizer6;
	wxStaticBoxSizer* StaticBoxSizer8;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxGridSizer* GridSizer1;
	wxStaticBoxSizer* StaticBoxSizer6;
	wxGridSizer* GridSizer3;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer9;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxBoxSizer* BoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer5;
	wxGridSizer* GridSizer2;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Total machine cycles"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer2->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	counterEdit = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(75,19), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer2->Add(counterEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Plate"));
	GridSizer2 = new wxGridSizer(0, 4, 0, 0);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Speed up"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	GridSizer2->Add(StaticText5, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	plateSpeedUpCombo = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxSize(120,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX2"));
	GridSizer2->Add(plateSpeedUpCombo, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Speed down"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	GridSizer2->Add(StaticText8, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	plateSpeedDownCombo = new wxComboBox(this, ID_COMBOBOX6, wxEmptyString, wxDefaultPosition, wxSize(120,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX6"));
	GridSizer2->Add(plateSpeedDownCombo, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(GridSizer2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("Camera"));
	GridSizer6 = new wxGridSizer(0, 4, 0, 0);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("Speed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	GridSizer6->Add(StaticText11, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	cameraSpeedCombo = new wxComboBox(this, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxSize(120,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX3"));
	GridSizer6->Add(cameraSpeedCombo, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer10 = new wxBoxSizer(wxVERTICAL);
	lowLightCheck = new wxCheckBox(this, ID_CHECKBOX3, _("Reduced Camera Light"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	lowLightCheck->SetValue(false);
	BoxSizer10->Add(lowLightCheck, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer6->Add(BoxSizer10, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(GridSizer6, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxVERTICAL, this, _("Table"));
	GridSizer8 = new wxGridSizer(0, 4, 0, 0);
	StaticText21 = new wxStaticText(this, ID_STATICTEXT21, _("Speed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
	GridSizer8->Add(StaticText21, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	tableSpeedCombo = new wxComboBox(this, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxSize(120,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX4"));
	GridSizer8->Add(tableSpeedCombo, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(GridSizer8, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer5, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer8 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Conveyor"));
	GridSizer4 = new wxGridSizer(0, 4, 0, 0);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Speed width"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	GridSizer4->Add(StaticText6, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	convSpeedWidthCombo = new wxComboBox(this, ID_COMBOBOX8, wxEmptyString, wxDefaultPosition, wxSize(120,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX8"));
	GridSizer4->Add(convSpeedWidthCombo, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Speed feed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	GridSizer4->Add(StaticText7, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	convSpeedFeedCombo = new wxComboBox(this, ID_COMBOBOX9, wxEmptyString, wxDefaultPosition, wxSize(120,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX9"));
	GridSizer4->Add(convSpeedFeedCombo, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer8->Add(GridSizer4, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer8, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer6 = new wxStaticBoxSizer(wxVERTICAL, this, _("Loader"));
	GridSizer3 = new wxGridSizer(0, 3, 0, 0);
	BoxSizer8 = new wxBoxSizer(wxVERTICAL);
	loaderInstalledCheck = new wxCheckBox(this, ID_CHECKBOX2, _("Use Loader"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	loaderInstalledCheck->SetValue(false);
	BoxSizer8->Add(loaderInstalledCheck, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer3->Add(BoxSizer8, 0, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	BoxSizer14 = new wxBoxSizer(wxVERTICAL);
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Speed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	BoxSizer6->Add(StaticText4, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	loaderSpeedCombo = new wxComboBox(this, ID_COMBOBOX7, wxEmptyString, wxDefaultPosition, wxSize(120,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX7"));
	BoxSizer6->Add(loaderSpeedCombo, 0, wxALL|wxEXPAND|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer14->Add(BoxSizer6, 0, wxALL|wxALIGN_RIGHT|wxALIGN_TOP, 0);
	GridSizer3->Add(BoxSizer14, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	BoxSizer4 = new wxBoxSizer(wxVERTICAL);
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Zero Movement (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer7->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	loaderZeroMovementEdit = new wxTextCtrl(this, ID_TEXTCTRL6, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
	BoxSizer7->Add(loaderZeroMovementEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4->Add(BoxSizer7, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Default Pitch (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	BoxSizer9->Add(StaticText9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	loaderDefPitchEdit = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer9->Add(loaderDefPitchEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4->Add(BoxSizer9, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 3);
	GridSizer3->Add(BoxSizer4, 0, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticBoxSizer6->Add(GridSizer3, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Cleaning System"));
	GridSizer1 = new wxGridSizer(0, 3, 0, 0);
	BoxSizer5 = new wxBoxSizer(wxVERTICAL);
	cleaningInstalledCheck = new wxCheckBox(this, ID_CHECKBOX1, _("Use Cleaning System"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	cleaningInstalledCheck->SetValue(false);
	BoxSizer5->Add(cleaningInstalledCheck, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer5, 0, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	BoxSizer15 = new wxBoxSizer(wxVERTICAL);
	BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Activation (ms)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	BoxSizer11->Add(StaticText10, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cleaningActivationTime = new wxTextCtrl(this, ID_TEXTCTRL5, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	BoxSizer11->Add(cleaningActivationTime, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer15->Add(BoxSizer11, 1, wxALL|wxALIGN_RIGHT|wxALIGN_TOP, 5);
	BoxSizer16 = new wxBoxSizer(wxHORIZONTAL);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT16, _("Camera/wipe Delta"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	BoxSizer16->Add(StaticText16, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CameraWipeDeltaEdit = new wxTextCtrl(this, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxSize(75,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	BoxSizer16->Add(CameraWipeDeltaEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer15->Add(BoxSizer16, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer15, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer12 = new wxBoxSizer(wxVERTICAL);
	cleaningDoubleCheck = new wxCheckBox(this, ID_CHECKBOX4, _("Double Cleaning Feeding"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	cleaningDoubleCheck->SetValue(false);
	BoxSizer12->Add(cleaningDoubleCheck, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	CleaningVacuum = new wxCheckBox(this, ID_CHECKBOX5, _("Cleaning Vaccum Activation"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	CleaningVacuum->SetValue(false);
	BoxSizer12->Add(CleaningVacuum, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(GridSizer1, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Language"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	BoxSizer3->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	languageCombo = new wxComboBox(this, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxSize(150,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX5"));
	BoxSizer3->Add(languageCombo, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer3, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("SPI Colours"));
	BoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Alarm Colour:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	BoxSizer13->Add(StaticText12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ColourPickerAlarm = new wxColourPickerCtrl(this, ID_COLOURPICKERCTRL1, wxColour(255,0,0), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_COLOURPICKERCTRL1"));
	BoxSizer13->Add(ColourPickerAlarm, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("Warning Colour:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	BoxSizer13->Add(StaticText13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ColourPickerWarning = new wxColourPickerCtrl(this, ID_COLOURPICKERCTRL2, wxColour(255,128,0), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_COLOURPICKERCTRL2"));
	BoxSizer13->Add(ColourPickerWarning, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText14 = new wxStaticText(this, ID_STATICTEXT14, _("Short Colour:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	BoxSizer13->Add(StaticText14, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ColourPickerShort = new wxColourPickerCtrl(this, ID_COLOURPICKERCTRL3, wxColour(255,255,0), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_COLOURPICKERCTRL3"));
	BoxSizer13->Add(ColourPickerShort, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(BoxSizer13, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxGeneralParamsPanel::OnlowLightCheckClick);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxGeneralParamsPanel::OnloaderInstalledCheckClick);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxGeneralParamsPanel::OncleaningInstalledCheckClick);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxGeneralParamsPanel::OncleaningDoubleCheckClick);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxGeneralParamsPanel::OnCleaningVacuumClick);
	Connect(ID_COMBOBOX5,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&wxGeneralParamsPanel::OnlanguageComboSelect);
	Connect(ID_COLOURPICKERCTRL1,wxEVT_COMMAND_COLOURPICKER_CHANGED,(wxObjectEventFunction)&wxGeneralParamsPanel::OnColourPickerAlarmColourChanged);
	Connect(ID_COLOURPICKERCTRL2,wxEVT_COMMAND_COLOURPICKER_CHANGED,(wxObjectEventFunction)&wxGeneralParamsPanel::OnColourPickerWarningColourChanged);
	Connect(ID_COLOURPICKERCTRL3,wxEVT_COMMAND_COLOURPICKER_CHANGED,(wxObjectEventFunction)&wxGeneralParamsPanel::OnColourPickerShortColourChanged);
	//*)
}

wxGeneralParamsPanel::~wxGeneralParamsPanel()
{
	//(*Destroy(wxGeneralParamsPanel)
	//*)
}


//----------------------------------------------------------------------------------
// Init
// Inizializza il controllo
//----------------------------------------------------------------------------------
int wxGeneralParamsPanel::Init( SRMachine* SRRef, SmartLog* smartLoggerRef )
{
	SR = SRRef;
	smartLogger = smartLoggerRef;

	// init combo labels
	wxArrayString comboLabels;
	comboLabels.Add(_("Low"));
	comboLabels.Add(_("Normal"));
	comboLabels.Add(_("High"));
	plateSpeedUpCombo->Append( comboLabels );
	plateSpeedDownCombo->Append( comboLabels );
	cameraSpeedCombo->Append( comboLabels );
	tableSpeedCombo->Append( comboLabels );
	convSpeedWidthCombo->Append( comboLabels );
	convSpeedFeedCombo->Append( comboLabels );
	loaderSpeedCombo->Append( comboLabels );

	// set validators
	plateSpeedUpCombo->SetValidator( wxMyComboValidator( &SR->DB->MachineParamsS.PlateUpSpeed ) );
	plateSpeedDownCombo->SetValidator( wxMyComboValidator( &SR->DB->MachineParamsS.PlateDownSpeed ) );
	cameraSpeedCombo->SetValidator( wxMyComboValidator( &SR->DB->MachineParamsS.CameraSpeed ) );
	tableSpeedCombo->SetValidator( wxMyComboValidator( &SR->DB->MachineParamsS.TableSpeed ) );
	convSpeedWidthCombo->SetValidator( wxMyComboValidator( &SR->DB->MachineParamsS.ConvWidthSpeed ) );
	convSpeedFeedCombo->SetValidator( wxMyComboValidator( &SR->DB->MachineParamsS.ConvFeedSpeed ) );
	loaderSpeedCombo->SetValidator( wxMyComboValidator( &SR->DB->MachineParamsS.LoaderSpeed ) );
	counterEdit->SetValidator( wxMyTextValidator( &SR->DB->MachineParamsS.Counter ) );
	loaderZeroMovementEdit->SetValidator( wxMyTextValidator( &SR->DB->MachineParamsS.LoaderZeroMovement ) );
	loaderDefPitchEdit->SetValidator( wxMyTextValidator( &SR->DB->MachineParamsS.LoaderDefPitch ) );
	cleaningActivationTime->SetValidator( wxMyTextValidator( &SR->DB->MachineParamsS.CleaningActivationTime ) );
	CameraWipeDeltaEdit ->SetValidator(wxMyTextValidator( &SR->DB->MachineParamsS.CleaningCameraDelta ));


	comboLabels.clear();
	comboLabels.Add(_("No"));
	comboLabels.Add(_("Yes"));
	//BeeperEnabledCombo->Append( comboLabels );
	//BeeperEnabledCombo->SetValidator(				wxMyComboValidator( &SR->DB->MachineParamsS.BeeperEn ) );
	//TODO prossima versione
	//BeeperEnabledCombo->Show(false);
	//BeeperEnablelabel->Show(false);

	// init loader activation mode
	loaderInstalledCheck->SetValue( SR->DB->MachineParamsS.LoaderInstalled == 0 ? false : true );

	// init camera led light mode
	lowLightCheck->SetValue( SR->DB->MachineParamsS.LedLightReduced == 0 ? false : true );

	// init cleaning system activation mode
	cleaningInstalledCheck->SetValue( SR->DB->MachineParamsS.CleaningInstalled == 0 ? false : true );

	// init cleaning system double feeding mode
	cleaningDoubleCheck->SetValue( SR->DB->MachineParamsS.CleaningDoubleFeed == 0 ? false : true );

	// init cleaning system vacuum activation
	CleaningVacuum->SetValue( SR->DB->MachineParamsS.CleaningVacuumOn == 0 ? false : true );

	// setup languages
	wxArrayString languages;
	wxGetApp().GetInstalledLanguages( languages );
	languageCombo->Clear();
	languageCombo->Append( languages );
	languageCombo->SetValue( wxGetApp().GetCurrentLanguage() );

	ColourPickerAlarm->SetColour(wxColour(SR->DB->ALARM_COLOR.val[0],SR->DB->ALARM_COLOR.val[1],SR->DB->ALARM_COLOR.val[2]));
	ColourPickerShort->SetColour(wxColour(SR->DB->SHORT_COLOR.val[0],SR->DB->SHORT_COLOR.val[1],SR->DB->SHORT_COLOR.val[2]));
	ColourPickerWarning->SetColour(wxColour(SR->DB->WARNING_COLOR.val[0],SR->DB->WARNING_COLOR.val[1],SR->DB->WARNING_COLOR.val[2]));

	return SR_OK;
}

//----------------------------------------------------------------------------------
// ShowControl
// Mostra il controllo a video
//----------------------------------------------------------------------------------
int wxGeneralParamsPanel::ShowControl( )
{
	TransferDataToWindow();
	return SR_OK;
}

//----------------------------------------------------------------------------------
// HideControl
// Nasconde il controllo
//----------------------------------------------------------------------------------
int wxGeneralParamsPanel::HideControl( )
{
	TransferDataFromWindow();
	SR->DB->SaveMachineParams();
	return SR_OK;
}

void wxGeneralParamsPanel::OnlanguageComboSelect(wxCommandEvent& event)
{
	if( wxGetApp().SelectLanguage( event.GetString() ) == true )
		wxMessageBox( MSG_LANGREBOOT, MACHINE_NAME, wxOK | wxICON_INFORMATION, this );
	else
		wxMessageBox( MSG_LANGERROR, MACHINE_NAME, wxOK | wxICON_ERROR, this );
}

void wxGeneralParamsPanel::OnloaderInstalledCheckClick(wxCommandEvent& event)
{
	SR->DB->MachineParamsS.LoaderInstalled = event.GetInt() ? 1 : 0;
}

void wxGeneralParamsPanel::OnlowLightCheckClick(wxCommandEvent& event)
{
	SR->DB->MachineParamsS.LedLightReduced = event.GetInt() ? 1 : 0;
	if( SR->DB->MachineParamsS.LedLightReduced )
	{
		SR->SetCameraLight( LED_LOW );
	}
	else
	{
		SR->SetCameraLight( LED_HIGH );
	}
}

void wxGeneralParamsPanel::OncleaningInstalledCheckClick(wxCommandEvent& event)
{
	SR->DB->MachineParamsS.CleaningInstalled = event.GetInt() ? 1 : 0;
}

void wxGeneralParamsPanel::OncleaningDoubleCheckClick(wxCommandEvent& event)
{
	SR->DB->MachineParamsS.CleaningDoubleFeed = event.GetInt() ? 1 : 0;
}

void wxGeneralParamsPanel::OnCleaningVacuumClick(wxCommandEvent& event)
{
	SR->DB->MachineParamsS.CleaningVacuumOn = event.GetInt() ? 1 : 0;
}

void wxGeneralParamsPanel::OnColourPickerAlarmColourChanged(wxColourPickerEvent& event)
{
	SR->DB->ALARM_COLOR = cv::Scalar( ColourPickerAlarm->GetColour().Red(), ColourPickerAlarm->GetColour().Green(), ColourPickerAlarm->GetColour().Blue());
	SR->DB->MachineParamsS.SPIAlarmColor = wxString::Format("%d;%d;%d;", (int)SR->DB->ALARM_COLOR.val[0],(int)SR->DB->ALARM_COLOR.val[1],(int)SR->DB->ALARM_COLOR.val[2]);
}

void wxGeneralParamsPanel::OnColourPickerWarningColourChanged(wxColourPickerEvent& event)
{
	SR->DB->WARNING_COLOR = cv::Scalar( ColourPickerWarning->GetColour().Red(), ColourPickerWarning->GetColour().Green(), ColourPickerWarning->GetColour().Blue());
	SR->DB->MachineParamsS.SPIWarningColor = wxString::Format("%d;%d;%d;", (int)SR->DB->WARNING_COLOR.val[0],(int)SR->DB->WARNING_COLOR.val[1],(int)SR->DB->WARNING_COLOR.val[2]);
}

void wxGeneralParamsPanel::OnColourPickerShortColourChanged(wxColourPickerEvent& event)
{
	SR->DB->SHORT_COLOR = cv::Scalar( ColourPickerShort->GetColour().Red(), ColourPickerShort->GetColour().Green(), ColourPickerShort->GetColour().Blue());
	SR->DB->MachineParamsS.SPIShortColor = wxString::Format("%d;%d;%d;", (int)SR->DB->SHORT_COLOR.val[0],(int)SR->DB->SHORT_COLOR.val[1],(int)SR->DB->SHORT_COLOR.val[2]);
}

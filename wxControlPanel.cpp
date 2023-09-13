#include "images/png_images.h"

#include "wxControlPanel.h"

//(*InternalHeaders(wxControlPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "wxMyTextValidator.h"
#include "GlobalUtils.h"
#include "Messages.h"

const long wxControlPanel::ID_LIGHTS_TIMER = wxNewId();


enum ControlPanelStateEnum
{
	PANEL_DISABLE,
	PANEL_LOADER,
	PANEL_PLATE,
	PANEL_CAMERA,
	PANEL_SQUEEGEES,
	PANEL_TABLE,
	PANEL_LCONVW,
	PANEL_LCONVF,
	PANEL_CCONVW,
	PANEL_CCONVF,
	PANEL_LCONVP
};

//(*IdInit(wxControlPanel)
const long wxControlPanel::ID_BITMAPBUTTON1 = wxNewId();
const long wxControlPanel::ID_BITMAPBUTTON4 = wxNewId();
const long wxControlPanel::ID_BITMAPBUTTON3 = wxNewId();
const long wxControlPanel::ID_BITMAPBUTTON2 = wxNewId();
const long wxControlPanel::ID_RADIOBUTTON2 = wxNewId();
const long wxControlPanel::ID_RADIOBUTTON3 = wxNewId();
const long wxControlPanel::ID_RADIOBUTTON1 = wxNewId();
const long wxControlPanel::ID_RADIOBUTTON4 = wxNewId();
const long wxControlPanel::ID_TEXTCTRL1 = wxNewId();
const long wxControlPanel::ID_BITMAPBUTTON6 = wxNewId();
const long wxControlPanel::ID_BITMAPBUTTON5 = wxNewId();
const long wxControlPanel::ID_RADIOBUTTON5 = wxNewId();
const long wxControlPanel::ID_RADIOBUTTON6 = wxNewId();
const long wxControlPanel::ID_RADIOBUTTON7 = wxNewId();
const long wxControlPanel::ID_RADIOBUTTON8 = wxNewId();
const long wxControlPanel::ID_TEXTCTRL2 = wxNewId();
const long wxControlPanel::ID_STATICLINE1 = wxNewId();
const long wxControlPanel::ID_COMBOBOX1 = wxNewId();
const long wxControlPanel::ID_STATICTEXT4 = wxNewId();
const long wxControlPanel::ID_TEXTCTRL3 = wxNewId();
const long wxControlPanel::ID_TEXTCTRL4 = wxNewId();
const long wxControlPanel::ID_TEXTCTRL5 = wxNewId();
const long wxControlPanel::ID_PANEL1 = wxNewId();
const long wxControlPanel::ID_BUTTON11 = wxNewId();
const long wxControlPanel::ID_BUTTON12 = wxNewId();
const long wxControlPanel::ID_BUTTON10 = wxNewId();
const long wxControlPanel::ID_BUTTON9 = wxNewId();
const long wxControlPanel::ID_BUTTON8 = wxNewId();
const long wxControlPanel::ID_BUTTON2 = wxNewId();
const long wxControlPanel::ID_BUTTON1 = wxNewId();
const long wxControlPanel::ID_BUTTON5 = wxNewId();
const long wxControlPanel::ID_BUTTON18 = wxNewId();
const long wxControlPanel::ID_BUTTON4 = wxNewId();
const long wxControlPanel::ID_BUTTON3 = wxNewId();
const long wxControlPanel::ID_BUTTON6 = wxNewId();
const long wxControlPanel::ID_BUTTON13 = wxNewId();
const long wxControlPanel::ID_BUTTON14 = wxNewId();
const long wxControlPanel::ID_BUTTON15 = wxNewId();
const long wxControlPanel::ID_BUTTON7 = wxNewId();
const long wxControlPanel::ID_BUTTON19 = wxNewId();
const long wxControlPanel::ID_BUTTON16 = wxNewId();
const long wxControlPanel::ID_BUTTON17 = wxNewId();
const long wxControlPanel::ID_BUTTON20 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxControlPanel,wxPanel)
	//(*EventTable(wxControlPanel)
	//*)
END_EVENT_TABLE()

wxControlPanel::wxControlPanel(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(wxControlPanel)
	wxBoxSizer* wxSizerRotation;
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer6;
	wxBoxSizer* wxSizerMovement;
	wxBoxSizer* wxSizerT1;
	wxBoxSizer* wxSizerR11;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* wxSizerR1;
	wxBoxSizer* wxSizerIO;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* wxSizerTraslation;
	wxBoxSizer* BoxSizer4wxSizerT121;
	wxBoxSizer* BoxSizer1;
	wxStaticBoxSizer* wxSizerMain;
	wxBoxSizer* wxSizerR12;
	wxBoxSizer* wxSizerT11;
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* wxSizerT12;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	SetMaxSize(wxSize(-1,720));
	wxSizerMain = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Control Panel"));
	wxSizerMovement = new wxBoxSizer(wxVERTICAL);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	wxSizerTraslation = new wxBoxSizer(wxHORIZONTAL);
	wxSizerT1 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	moveLeftBtn = new wxBitmapButton(this, ID_BITMAPBUTTON1, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	moveLeftBtn->SetDefault();
	BoxSizer5->Add(moveLeftBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerT11 = new wxBoxSizer(wxVERTICAL);
	moveUpBtn = new wxBitmapButton(this, ID_BITMAPBUTTON4, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON4"));
	moveUpBtn->SetDefault();
	wxSizerT11->Add(moveUpBtn, 0, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	moveDownBtn = new wxBitmapButton(this, ID_BITMAPBUTTON3, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
	moveDownBtn->SetDefault();
	wxSizerT11->Add(moveDownBtn, 0, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer5->Add(wxSizerT11, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	moveRightBtn = new wxBitmapButton(this, ID_BITMAPBUTTON2, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
	moveRightBtn->SetDefault();
	BoxSizer5->Add(moveRightBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerT1->Add(BoxSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerT12 = new wxBoxSizer(wxVERTICAL);
	moveRadio1 = new wxRadioButton(this, ID_RADIOBUTTON2, wxEmptyString, wxDefaultPosition, wxSize(75,17), wxRB_GROUP, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
	moveRadio1->SetValue(true);
	wxSizerT12->Add(moveRadio1, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	moveRadio2 = new wxRadioButton(this, ID_RADIOBUTTON3, wxEmptyString, wxDefaultPosition, wxSize(75,17), 0, wxDefaultValidator, _T("ID_RADIOBUTTON3"));
	wxSizerT12->Add(moveRadio2, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	moveRadio3 = new wxRadioButton(this, ID_RADIOBUTTON1, wxEmptyString, wxDefaultPosition, wxSize(75,17), 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
	wxSizerT12->Add(moveRadio3, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4wxSizerT121 = new wxBoxSizer(wxHORIZONTAL);
	moveRadio4 = new wxRadioButton(this, ID_RADIOBUTTON4, wxEmptyString, wxDefaultPosition, wxSize(17,17), 0, wxDefaultValidator, _T("ID_RADIOBUTTON4"));
	BoxSizer4wxSizerT121->Add(moveRadio4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	moveUserEdit = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(50,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer4wxSizerT121->Add(moveUserEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerT12->Add(BoxSizer4wxSizerT121, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerT1->Add(wxSizerT12, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerTraslation->Add(wxSizerT1, 0, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	BoxSizer1->Add(wxSizerTraslation, 0, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerRotation = new wxBoxSizer(wxHORIZONTAL);
	wxSizerR1 = new wxBoxSizer(wxHORIZONTAL);
	wxSizerR11 = new wxBoxSizer(wxVERTICAL);
	rotCCWBtn = new wxBitmapButton(this, ID_BITMAPBUTTON6, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON6"));
	rotCCWBtn->SetDefault();
	wxSizerR11->Add(rotCCWBtn, 0, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	rotCWBtn = new wxBitmapButton(this, ID_BITMAPBUTTON5, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON5"));
	rotCWBtn->SetDefault();
	wxSizerR11->Add(rotCWBtn, 0, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	wxSizerR1->Add(wxSizerR11, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerR12 = new wxBoxSizer(wxVERTICAL);
	rotateRadio1 = new wxRadioButton(this, ID_RADIOBUTTON5, wxEmptyString, wxDefaultPosition, wxSize(113,17), wxRB_GROUP, wxDefaultValidator, _T("ID_RADIOBUTTON5"));
	rotateRadio1->SetValue(true);
	wxSizerR12->Add(rotateRadio1, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	rotateRadio2 = new wxRadioButton(this, ID_RADIOBUTTON6, wxEmptyString, wxDefaultPosition, wxSize(113,17), 0, wxDefaultValidator, _T("ID_RADIOBUTTON6"));
	wxSizerR12->Add(rotateRadio2, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	rotateRadio3 = new wxRadioButton(this, ID_RADIOBUTTON7, wxEmptyString, wxDefaultPosition, wxSize(113,17), 0, wxDefaultValidator, _T("ID_RADIOBUTTON7"));
	wxSizerR12->Add(rotateRadio3, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	rotateRadio4 = new wxRadioButton(this, ID_RADIOBUTTON8, wxEmptyString, wxDefaultPosition, wxSize(17,17), 0, wxDefaultValidator, _T("ID_RADIOBUTTON8"));
	BoxSizer6->Add(rotateRadio4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	rotateUserEdit = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(50,19), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer6->Add(rotateUserEdit, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerR12->Add(BoxSizer6, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerR1->Add(wxSizerR12, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerRotation->Add(wxSizerR1, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	BoxSizer1->Add(wxSizerRotation, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerMovement->Add(BoxSizer1, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerMovement->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer3 = new wxBoxSizer(wxVERTICAL);
	wxAxisPanel = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	wxAxisPanel->SetBackgroundColour(wxColour(192,192,192));
	BoxSizer4 = new wxBoxSizer(wxVERTICAL);
	StaticLine1 = new wxStaticLine(wxAxisPanel, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	BoxSizer4->Add(StaticLine1, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	axisCombo = new wxComboBox(wxAxisPanel, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxSize(200,25), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	BoxSizer4->Add(axisCombo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizerPos = new wxBoxSizer(wxVERTICAL);
	positionLabel = new wxStaticText(wxAxisPanel, ID_STATICTEXT4, _("Position (mm):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	BoxSizerPos->Add(positionLabel, 0, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	pos1Edit = new wxTextCtrl(wxAxisPanel, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxSize(50,19), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	BoxSizer7->Add(pos1Edit, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	pos2Edit = new wxTextCtrl(wxAxisPanel, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxSize(50,19), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	BoxSizer7->Add(pos2Edit, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	pos3Edit = new wxTextCtrl(wxAxisPanel, ID_TEXTCTRL5, wxEmptyString, wxDefaultPosition, wxSize(50,19), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	BoxSizer7->Add(pos3Edit, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizerPos->Add(BoxSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4->Add(BoxSizerPos, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	wxAxisPanel->SetSizer(BoxSizer4);
	BoxSizer4->Fit(wxAxisPanel);
	BoxSizer4->SetSizeHints(wxAxisPanel);
	BoxSizer3->Add(wxAxisPanel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	homeBtn = new wxButton(this, ID_BUTTON11, _("Home"), wxDefaultPosition, wxSize(75,25), 0, wxDefaultValidator, _T("ID_BUTTON11"));
	BoxSizer2->Add(homeBtn, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	endBtn = new wxButton(this, ID_BUTTON12, _("End"), wxDefaultPosition, wxSize(75,25), 0, wxDefaultValidator, _T("ID_BUTTON12"));
	BoxSizer2->Add(endBtn, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	BoxSizer3->Add(BoxSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	wxSizerIO = new wxBoxSizer(wxVERTICAL);
	frameLockBtn = new wxButton(this, ID_BUTTON10, _("Frame Lock"), wxDefaultPosition, wxSize(150,23), 0, wxDefaultValidator, _T("ID_BUTTON10"));
	wxSizerIO->Add(frameLockBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	squeegeesFrontBtn = new wxButton(this, ID_BUTTON9, _("Front Squeegees"), wxDefaultPosition, wxSize(150,23), 0, wxDefaultValidator, _T("ID_BUTTON9"));
	wxSizerIO->Add(squeegeesFrontBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	squeegeesRearBtn = new wxButton(this, ID_BUTTON8, _("Rear Squeegees"), wxDefaultPosition, wxSize(150,23), 0, wxDefaultValidator, _T("ID_BUTTON8"));
	wxSizerIO->Add(squeegeesRearBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ledUpBtn = new wxButton(this, ID_BUTTON2, _("Camera Led Up"), wxDefaultPosition, wxSize(150,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	wxSizerIO->Add(ledUpBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ledDownBtn = new wxButton(this, ID_BUTTON1, _("Camera Led Down"), wxDefaultPosition, wxSize(150,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	wxSizerIO->Add(ledDownBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	alarmLightGreenBtn = new wxButton(this, ID_BUTTON5, _("Alarm Light Green"), wxDefaultPosition, wxSize(150,23), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	wxSizerIO->Add(alarmLightGreenBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	alarmLightYellowBtn = new wxButton(this, ID_BUTTON18, _("Alarm Light Yellow"), wxDefaultPosition, wxSize(150,23), 0, wxDefaultValidator, _T("ID_BUTTON18"));
	wxSizerIO->Add(alarmLightYellowBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	alarmLightRedBtn = new wxButton(this, ID_BUTTON4, _("Alarm Light Red"), wxDefaultPosition, wxSize(150,23), 0, wxDefaultValidator, _T("ID_BUTTON4"));
	wxSizerIO->Add(alarmLightRedBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	buzzerBtn = new wxButton(this, ID_BUTTON3, _("Buzzer"), wxDefaultPosition, wxSize(150,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	buzzerBtn->Hide();
	wxSizerIO->Add(buzzerBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	boardLockBtn = new wxButton(this, ID_BUTTON6, _("Board Lock"), wxDefaultPosition, wxSize(150,23), 0, wxDefaultValidator, _T("ID_BUTTON6"));
	wxSizerIO->Add(boardLockBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	convPistonBtn = new wxButton(this, ID_BUTTON13, _("Conveyor Ejector"), wxDefaultPosition, wxSize(150,23), 0, wxDefaultValidator, _T("ID_BUTTON13"));
	wxSizerIO->Add(convPistonBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cameraPistonBtn = new wxButton(this, ID_BUTTON14, _("Camera Piston"), wxDefaultPosition, wxSize(150,23), 0, wxDefaultValidator, _T("ID_BUTTON14"));
	wxSizerIO->Add(cameraPistonBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	loaderPistonBtn = new wxButton(this, ID_BUTTON15, _("Loader Piston"), wxDefaultPosition, wxSize(150,23), 0, wxDefaultValidator, _T("ID_BUTTON15"));
	wxSizerIO->Add(loaderPistonBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cleaningLockBtn = new wxButton(this, ID_BUTTON7, _("Cleaning Lock"), wxDefaultPosition, wxSize(150,23), 0, wxDefaultValidator, _T("ID_BUTTON7"));
	wxSizerIO->Add(cleaningLockBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CleaningActBtn = new wxButton(this, ID_BUTTON19, _("Cleaning Activate"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON19"));
	CleaningActBtn->SetMinSize(wxSize(150,23));
	wxSizerIO->Add(CleaningActBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cleaningVacuumBtn = new wxButton(this, ID_BUTTON16, _("Cleaning Vacuum"), wxDefaultPosition, wxSize(150,23), 0, wxDefaultValidator, _T("ID_BUTTON16"));
	wxSizerIO->Add(cleaningVacuumBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cleaningFeedingBtn = new wxButton(this, ID_BUTTON17, _("Wipe Feeding"), wxDefaultPosition, wxSize(150,23), 0, wxDefaultValidator, _T("ID_BUTTON17"));
	wxSizerIO->Add(cleaningFeedingBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SwitchLightsBtn = new wxButton(this, ID_BUTTON20, _("Switch Lights"), wxDefaultPosition, wxSize(150,23), 0, wxDefaultValidator, _T("ID_BUTTON20"));
	wxSizerIO->Add(SwitchLightsBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer3->Add(wxSizerIO, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerMovement->Add(BoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerMain->Add(wxSizerMovement, 0, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	SetSizer(wxSizerMain);
	wxSizerMain->Fit(this);
	wxSizerMain->SetSizeHints(this);

	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnmoveLeftBtnClick);
	Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnmoveUpBtnClick);
	Connect(ID_BITMAPBUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnmoveDownBtnClick);
	Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnmoveRightBtnClick);
	Connect(ID_RADIOBUTTON2,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&wxControlPanel::OnmoveRadioSelect);
	Connect(ID_RADIOBUTTON3,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&wxControlPanel::OnmoveRadioSelect);
	Connect(ID_RADIOBUTTON1,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&wxControlPanel::OnmoveRadioSelect);
	Connect(ID_RADIOBUTTON4,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&wxControlPanel::OnmoveRadioSelect);
	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&wxControlPanel::OnmoveUserEditText);
	Connect(ID_BITMAPBUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnrotCCWBtnClick);
	Connect(ID_BITMAPBUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnrotCWBtnClick);
	Connect(ID_RADIOBUTTON5,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&wxControlPanel::OnrotateRadioSelect);
	Connect(ID_RADIOBUTTON6,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&wxControlPanel::OnrotateRadioSelect);
	Connect(ID_RADIOBUTTON7,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&wxControlPanel::OnrotateRadioSelect);
	Connect(ID_RADIOBUTTON8,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&wxControlPanel::OnrotateRadioSelect);
	Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&wxControlPanel::OnrotateUserEditText);
	Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&wxControlPanel::OnaxisComboSelect);
	Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnhomeBtnClick);
	Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnendBtnClick);
	Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnframeLockBtnClick);
	Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnsqueegeesFrontBtnClick);
	Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnsqueegeesRearBtnClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnledUpBtnClick);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnledDownBtnClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnalarmLightGreenBtnClick);
	Connect(ID_BUTTON18,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnalarmLightYellowBtnClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnalarmLightRedBtnClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnbuzzerBtnClick);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnboardLockBtnClick);
	Connect(ID_BUTTON13,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnconvPistonBtnClick);
	Connect(ID_BUTTON14,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OncameraPistonBtnClick);
	Connect(ID_BUTTON15,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnloaderPistonBtnClick);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OncleaningLockBtnClick);
	Connect(ID_BUTTON19,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnCleaningActBtnClick);
	Connect(ID_BUTTON16,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OncleaningVacuumBtnClick);
	Connect(ID_BUTTON17,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OncleaningFeedingBtnClick);
	Connect(ID_BUTTON20,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxControlPanel::OnSwitchLightsBtnClick);
	//*)

	//Connect( wxEVT_CHAR_HOOK,(wxObjectEventFunction)&wxControlPanel::OnCharPressed, NULL, this);

	// init buttons image
	moveLeftBtn->SetBitmapDisabled( wxMEMORY_BITMAP( left_off ) );
	moveLeftBtn->SetBitmapLabel( wxMEMORY_BITMAP( left_on ) );
	moveRightBtn->SetBitmapDisabled( wxMEMORY_BITMAP( right_off ) );
	moveRightBtn->SetBitmapLabel( wxMEMORY_BITMAP( right_on ) );
	moveUpBtn->SetBitmapDisabled( wxMEMORY_BITMAP( up ) );
	moveUpBtn->SetBitmapLabel( wxMEMORY_BITMAP( up_on ) );
	moveDownBtn->SetBitmapDisabled( wxMEMORY_BITMAP( down ) );
	moveDownBtn->SetBitmapLabel( wxMEMORY_BITMAP( down_on ) );
	rotCCWBtn->SetBitmapDisabled( wxMEMORY_BITMAP( turn_left ) );
	rotCCWBtn->SetBitmapLabel( wxMEMORY_BITMAP( turn_left_on ) );
	rotCWBtn->SetBitmapDisabled( wxMEMORY_BITMAP( turn_right ) );
	rotCWBtn->SetBitmapLabel( wxMEMORY_BITMAP( turn_right_on ) );
	/* //TEMP - per il futuro
	alarmLightGreenBtn->SetBitmapDisabled( wxMEMORY_BITMAP( light_off ) );
	alarmLightGreenBtn->SetBitmapLabel( wxMEMORY_BITMAP( light_green ) );
	alarmLightRedBtn->SetBitmapDisabled( wxMEMORY_BITMAP( light_off ) );
	alarmLightRedBtn->SetBitmapLabel( wxMEMORY_BITMAP( light_red ) );
	buzzerBtn->SetBitmapDisabled( wxMEMORY_BITMAP( buzzer ) );
	buzzerBtn->SetBitmapLabel( wxMEMORY_BITMAP( buzzer_on ) );
	ledUpBtn->SetBitmapDisabled( wxMEMORY_BITMAP( camledup ) );
	ledUpBtn->SetBitmapLabel( wxMEMORY_BITMAP( camledup_on ) );
	ledDownBtn->SetBitmapDisabled( wxMEMORY_BITMAP( camleddown ) );
	ledDownBtn->SetBitmapLabel( wxMEMORY_BITMAP( camleddown_on ) );
	frameLockBtn->SetBitmapDisabled( wxMEMORY_BITMAP( lockframe ) );
	frameLockBtn->SetBitmapLabel( wxMEMORY_BITMAP( lockframe_on ) );
	squeegeesFrontBtn->SetBitmapDisabled( wxMEMORY_BITMAP( frontsqueegees ) );
	squeegeesFrontBtn->SetBitmapLabel( wxMEMORY_BITMAP( frontsqueegees_on ) );
	squeegeesRearBtn->SetBitmapDisabled( wxMEMORY_BITMAP( rearsqueegees ) );
	squeegeesRearBtn->SetBitmapLabel( wxMEMORY_BITMAP( rearsqueegees_on ) );
	homeBtn->SetBitmapDisabled( wxMEMORY_BITMAP( home_small ) );
	homeBtn->SetBitmapLabel( wxMEMORY_BITMAP( home_small_on ) );
	endBtn->SetBitmapDisabled( wxMEMORY_BITMAP( end_small ) );
	endBtn->SetBitmapLabel( wxMEMORY_BITMAP( end_small_on ) );
	*/

	SR = NULL;
	smartLogger = NULL;

	moveState = 0;
	axisSelected = 0;
	isBusy = false;

	moveValidatorValue = 0;
	rotateValidatorValue = 0;

	// Linear movements
	// PANEL_DISABLE
	moveValues[PANEL_DISABLE][0] = 0;
	moveValues[PANEL_DISABLE][1] = 0;
	moveValues[PANEL_DISABLE][2] = 0;
	moveValues[PANEL_DISABLE][3] = 0;
	// PANEL_PLATE
	moveValues[PANEL_PLATE][0] = 1;
	moveValues[PANEL_PLATE][1] = 5;
	moveValues[PANEL_PLATE][2] = 10;
	moveValues[PANEL_PLATE][3] = 0;
	// PANEL_CAMERA
	moveValues[PANEL_CAMERA][0] = (float)0.1;
	moveValues[PANEL_CAMERA][1] = 1;
	moveValues[PANEL_CAMERA][2] = 10;
	moveValues[PANEL_CAMERA][3] = 0;
	// PANEL_SQUEEGEES
	moveValues[PANEL_SQUEEGEES][0] = 1;
	moveValues[PANEL_SQUEEGEES][1] = 5;
	moveValues[PANEL_SQUEEGEES][2] = 10;
	moveValues[PANEL_SQUEEGEES][3] = 0;
	// PANEL_TABLE
	moveValues[PANEL_TABLE][0] = (float)0.02;
	moveValues[PANEL_TABLE][1] = (float)0.1;
	moveValues[PANEL_TABLE][2] = 1;
	moveValues[PANEL_TABLE][3] = 0;
	// PANEL_LCONVW
	moveValues[PANEL_LCONVW][0] = (float)0.1;
	moveValues[PANEL_LCONVW][1] = 1;
	moveValues[PANEL_LCONVW][2] = 10;
	moveValues[PANEL_LCONVW][3] = 0;
	// PANEL_LCONVF
	moveValues[PANEL_LCONVF][0] = 10;
	moveValues[PANEL_LCONVF][1] = 50;
	moveValues[PANEL_LCONVF][2] = 100;
	moveValues[PANEL_LCONVF][3] = 0;
	// PANEL_CCONVW
	moveValues[PANEL_CCONVW][0] = (float)0.1;
	moveValues[PANEL_CCONVW][1] = 1;
	moveValues[PANEL_CCONVW][2] = 10;
	moveValues[PANEL_CCONVW][3] = 0;
	// PANEL_CCONVF
	moveValues[PANEL_CCONVF][0] = 10;
	moveValues[PANEL_CCONVF][1] = 50;
	moveValues[PANEL_CCONVF][2] = 100;
	moveValues[PANEL_CCONVF][3] = 0;
	// PANEL_LOADER
	moveValues[PANEL_LOADER][0] = (float)0.1;
	moveValues[PANEL_LOADER][1] = 1;
	moveValues[PANEL_LOADER][2] = 10;
	moveValues[PANEL_LOADER][3] = 0;
	// PANEL_LCONVF
	moveValues[PANEL_LCONVP][0] = (float)0.1;
	moveValues[PANEL_LCONVP][1] = 1;
	moveValues[PANEL_LCONVP][2] = 10;
	moveValues[PANEL_LCONVP][3] = 0;

	// Rotations
	// PANEL_TABLE
	rotateValues[0] = (float)0.1;
	rotateValues[1] = (float)0.5;
	rotateValues[2] = 1;
	rotateValues[3] = 0;

	// Set slow movements
	moveIndex = 0;
	rotateIndex = 0;

	SwitchLightsBtn->Show(false);
	LightsTimer = new wxTimer( this, ID_LIGHTS_TIMER );



}

wxControlPanel::~wxControlPanel()
{
	//(*Destroy(wxControlPanel)
	//*)
}

//----------------------------------------------------------------------------------
// Init
// Inizializza il controllo
//----------------------------------------------------------------------------------
int wxControlPanel::Init( SRMachine* SRRef, SmartLog* smartLoggerRef )
{
	SR = SRRef;

	Connect( ID_LIGHTS_TIMER, wxEVT_TIMER, wxTimerEventHandler( SRMachine::OnSwitchLightTimer ), NULL, SR );
	MACHINE_CONFIG_NOT(PASSWORD_ENABLE)
		SwitchLightsBtn->Show(true);
	MACHINE_CONFIG_END
	smartLogger = smartLoggerRef;

	moveUserEdit->SetValidator( wxMyTextValidator( &moveValidatorValue, false, 2 ) );
	rotateUserEdit->SetValidator( wxMyTextValidator( &rotateValidatorValue, false, 2 ) );

	moveRadio1->SetLabel( wxString::Format(wxT("%.2f mm"), moveValues[0][0]) );
	moveRadio2->SetLabel( wxString::Format(wxT("%.2f mm"), moveValues[0][1]) );
	moveRadio3->SetLabel( wxString::Format(wxT("%.2f mm"), moveValues[0][2]) );

	rotateRadio1->SetLabel( wxString::Format(wxT("%.2f deg"), rotateValues[0]) );
	rotateRadio2->SetLabel( wxString::Format(wxT("%.2f deg"), rotateValues[1]) );
	rotateRadio3->SetLabel( wxString::Format(wxT("%.2f deg"), rotateValues[2]) );

	wxArrayString comboLabels;
	comboLabels.Clear();
	comboLabels.Add(_T("Table"));
	comboLabels.Add(_T("Camera"));
	comboLabels.Add(_T("Squeegees"));
	comboLabels.Add(_T("Plate"));
	comboLabels.Add(_T("Left Conveyor Width"));
	comboLabels.Add(_T("Left Conveyor Feed"));
	comboLabels.Add(_T("Center Conveyor Width"));
	comboLabels.Add(_T("Center Conveyor Feed"));
	comboLabels.Add(_T("Loader"));
	MACHINE_CONFIG(CONV_PUSH_MOTOR)
		comboLabels.Add(_T("Left Conveyor Push"));
	MACHINE_CONFIG_END
	axisCombo->Append( comboLabels );

	axisCombo->Select(0);

	// init control
	SetState( PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE );

	TransferDataToWindow();

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SetMovement
// Abilita/disabilita i controlli di movimento
//----------------------------------------------------------------------------------
void wxControlPanel::SetMovement( bool enableUD, bool enableLR, int state )
{
	axisSelected = state;

	moveUpBtn->Enable( enableUD );
	moveDownBtn->Enable( enableUD );
	moveLeftBtn->Enable( enableLR );
	moveRightBtn->Enable( enableLR );

	if( enableUD == false && enableLR == false )
	{
		moveRadio1->Enable( false );
		moveRadio2->Enable( false );
		moveRadio3->Enable( false );
		moveRadio4->Enable( false );
		moveUserEdit->Enable( false );
		//moveMMLabel->Enable( false );

		homeBtn->Enable( false );
		endBtn->Enable( false );
	}
	else
	{
		moveRadio1->Enable( true );
		moveRadio2->Enable( true );
		moveRadio3->Enable( true );
		moveRadio4->Enable( true );
		moveUserEdit->Enable( true );
		//moveMMLabel->Enable( true );

		moveRadio1->SetLabel( wxString::Format("%.2f mm", moveValues[state][0]) );
		moveRadio2->SetLabel( wxString::Format("%.2f mm", moveValues[state][1]) );
		moveRadio3->SetLabel( wxString::Format("%.2f mm", moveValues[state][2]) );
		moveValidatorValue = moveValues[state][3];
		TransferDataToWindow();

		homeBtn->Enable( true );
		endBtn->Enable( true );
	}
}

//----------------------------------------------------------------------------------
// SetRotation
// Abilita/disabilita i controlli di rotazione
//----------------------------------------------------------------------------------
void wxControlPanel::SetRotation( bool enable )
{
	rotCCWBtn->Enable( enable );
	rotCWBtn->Enable( enable );

	rotateRadio1->Enable( enable );
	rotateRadio2->Enable( enable );
	rotateRadio3->Enable( enable );
	rotateRadio4->Enable( enable );
	rotateUserEdit->Enable( enable );
	//rotateMMLabel->Enable( enable );
}

//----------------------------------------------------------------------------------
// SetIO
// Abilita/disabilita i pulsanti di IO
//----------------------------------------------------------------------------------
void wxControlPanel::SetIO( bool enable )
{
	frameLockBtn->Enable( enable );
	squeegeesFrontBtn->Enable( enable );
	squeegeesRearBtn->Enable( enable );
	alarmLightGreenBtn->Enable( enable );
	alarmLightYellowBtn->Enable( enable );
	alarmLightRedBtn->Enable( enable );
	buzzerBtn->Enable( enable );
	ledUpBtn->Enable( enable );
	ledDownBtn->Enable( enable );
}

//----------------------------------------------------------------------------------
// SetState
// Setta lo stato del controllo
//----------------------------------------------------------------------------------
int wxControlPanel::SetState( int movementState, long outputState )
{
	int stateCounter = 0;

	moveState = movementState;

	// set movement panel
	if( moveState == PANEL_MOVE_DISABLE )
	{
		SetMovement( false, false, PANEL_DISABLE );
		SetRotation( false );
	}

	if( moveState & PANEL_MOVE_PLATE )
	{
		SetMovement( true, false, PANEL_PLATE );
		SetRotation( false );
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->PlateMotor.GetPosition() ) );
		stateCounter++;
	}
	else

	if( moveState & PANEL_MOVE_CAMERA )
	{
		SetMovement( true, true, PANEL_CAMERA );
		SetRotation( false );
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->CamXMotor.GetPosition() ) );
		pos2Edit->SetValue( wxString::Format( "%0.2f", SR->CamYMotor.GetPosition() ) );
		stateCounter++;
	}

	if( moveState & PANEL_MOVE_SQUEEGEES )
	{
		SetMovement( true, false, PANEL_SQUEEGEES );
		SetRotation( false );
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->SqueegeesMotor.GetPosition() ) );
		stateCounter++;
	}

	if( moveState & PANEL_MOVE_TABLE )
	{
		SetMovement( true, true, PANEL_TABLE );
		SetRotation( true );
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->Table1Motor.GetPosition() ) );
		pos2Edit->SetValue( wxString::Format( "%0.2f", SR->Table2Motor.GetPosition() ) );
		pos3Edit->SetValue( wxString::Format( "%0.2f", SR->Table3Motor.GetPosition() ) );
		stateCounter++;
	}

	if( moveState & PANEL_MOVE_LOADER )
	{
		SetMovement( true, false, PANEL_LOADER );
		SetRotation( false );
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LoaderMotor.GetPosition() ) );
		stateCounter++;
	}

	if( moveState & PANEL_MOVE_LCONVW )
	{
		SetMovement( true, false, PANEL_LCONVW );
		SetRotation( false );
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LConvWidthMotor.GetPosition() ) );
		stateCounter++;
	}

	if( moveState & PANEL_MOVE_LCONVF )
	{
		SetMovement( false, true, PANEL_LCONVF );
		SetRotation( false );
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LConvFeedMotor.GetPosition() ) );
		stateCounter++;
	}

	if( moveState & PANEL_MOVE_CCONVW )
	{
		SetMovement( true, false, PANEL_CCONVW );
		SetRotation( false );
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->CConvWidthMotor.GetPosition() ) );
		stateCounter++;
	}

	if( moveState & PANEL_MOVE_CCONVF )
	{
		SetMovement( false, true, PANEL_CCONVF );
		SetRotation( false );
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->CConvFeedMotor.GetPosition() ) );
		stateCounter++;
	}

	if( moveState & PANEL_MOVE_LCONVP )
	{
		SetMovement( false, true, PANEL_LCONVP );
		SetRotation( false );
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LConvPushMotor.GetPosition() ) );
		stateCounter++;
	}

	// set positions box
	pos1Edit->Show( true );
	pos2Edit->Show( moveState & PANEL_MOVE_TABLE || moveState & PANEL_MOVE_CAMERA ? true : false );
	pos3Edit->Show( moveState & PANEL_MOVE_TABLE ? true : false );

	// set output buttons
	if( !(outputState & PANEL_OUTPUT_SAME) )
	{
		frameLockBtn->Enable(		outputState & PANEL_OUTPUT_LOCK			? true : false );
		squeegeesFrontBtn->Enable(	outputState & PANEL_OUTPUT_FRONT_S		? true : false );
		squeegeesRearBtn->Enable(	outputState & PANEL_OUTPUT_REAR_S		? true : false );
		alarmLightGreenBtn->Enable(	outputState & PANEL_OUTPUT_ALARM_G		? true : false );
		alarmLightYellowBtn->Enable(outputState & PANEL_OUTPUT_ALARM_Y		? true : false );
		alarmLightRedBtn->Enable(	outputState & PANEL_OUTPUT_ALARM_R		? true : false );
		buzzerBtn->Enable(			outputState & PANEL_OUTPUT_BUZZER		? true : false );
		ledUpBtn->Enable(			outputState & PANEL_OUTPUT_LED_UP		? true : false );
		ledDownBtn->Enable(			outputState & PANEL_OUTPUT_LED_DOWN		? true : false );
		boardLockBtn->Enable(		outputState & PANEL_OUTPUT_BOARD_LOCK	? true : false );
		convPistonBtn->Enable(		outputState & PANEL_OUTPUT_CONV_PIST	? true : false );
		cameraPistonBtn->Enable(	outputState & PANEL_OUTPUT_CAM_PIST		? true : false );
		loaderPistonBtn->Enable(	outputState & PANEL_OUTPUT_LOAD_PIST	? true : false );
		cleaningLockBtn->Enable(	outputState & PANEL_OUTPUT_CLEAN_LOCK	? true : false );
		cleaningVacuumBtn->Enable(	outputState & PANEL_OUTPUT_CLEAN_VAC	? true : false );
		cleaningFeedingBtn->Enable(	outputState & PANEL_OUTPUT_CLEAN_FEED	? true : false );
		CleaningActBtn->Enable(		outputState & PANEL_OUTPUT_CLEAN_ACT	? true : false );
	}

	// show/hide wxAxisPanel
	wxAxisPanel->Show( stateCounter > 1 ? true : false );

	Layout();
	return SR_OK;
}

//----------------------------------------------------------------------------------
// MoveUD
// Muove l'asse UP o DOWN
//----------------------------------------------------------------------------------
void wxControlPanel::MoveUD( int direction )
{
	if( isBusy )
		return;

	isBusy = true;

	float Resolution;

	switch( axisSelected )
	{
	case PANEL_PLATE:
		if( SR->PlateMotor.MoveAndWait( direction * moveValues[PANEL_PLATE][moveIndex], REL_MOVE, SR->GetLimitsState() ) == SR_ERROR )
		{
			smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
			SR->ErrorManagement();
		}
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->PlateMotor.GetPosition() ) );
		break;

	case PANEL_CAMERA:
		if( moveIndex == 0 )
		{
			Resolution = ( PI * SR->DB->MotorParamsS[MOTOR_CAMERAY_ID].Pulley * SR->DB->MotorParamsS[MOTOR_CAMERAY_ID].Reduction ) / ( MOTOR_SPR * SR->DB->MotorParamsS[MOTOR_CAMERAY_ID].Microstepping );
			if( SR->MoveCameraAndWait( 0, direction * Resolution, REL_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
		}
		else
		{
			if( SR->MoveCameraAndWait( 0, direction * moveValues[PANEL_CAMERA][moveIndex], REL_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
		}
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->CamXMotor.GetPosition() ) );
		pos2Edit->SetValue( wxString::Format( "%0.2f", SR->CamYMotor.GetPosition() ) );
		break;

	case PANEL_SQUEEGEES:
		if( SR->SqueegeesMotor.MoveAndWait( -direction * moveValues[PANEL_SQUEEGEES][moveIndex], REL_MOVE, SR->GetLimitsState() ) == SR_ERROR )
		{
			smartLogger->Write( MSG_SQUEEGEESERROR, MSG_ERROR );
			SR->ErrorManagement();
		}
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->SqueegeesMotor.GetPosition() ) );
		break;

	case PANEL_TABLE:
		if( SR->MoveXYTableAndWait( 0, direction * moveValues[PANEL_TABLE][moveIndex], SR->GetLimitsState() ) == SR_ERROR )
		{
			smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
			SR->ErrorManagement();
		}
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->Table1Motor.GetPosition() ) );
		pos2Edit->SetValue( wxString::Format( "%0.2f", SR->Table2Motor.GetPosition() ) );
		pos3Edit->SetValue( wxString::Format( "%0.2f", SR->Table3Motor.GetPosition() ) );
		break;

	case PANEL_LOADER:
		if( SR->LoaderMotor.MoveAndWait( direction * moveValues[PANEL_LOADER][moveIndex], REL_MOVE, SR->GetLimitsState() ) == SR_ERROR )
		{
			smartLogger->Write( MSG_LOADERERROR, MSG_ERROR );
			SR->ErrorManagement();
		}
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LoaderMotor.GetPosition() ) );
		break;

	case PANEL_LCONVW:
		if( SR->LConvWidthMotor.MoveAndWait( direction * moveValues[PANEL_LCONVW][moveIndex], REL_MOVE, SR->GetLimitsState() ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CONVWIDTHERROR, MSG_ERROR );
			SR->ErrorManagement();
		}
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LConvWidthMotor.GetPosition() ) );
		break;

	case PANEL_CCONVW:
		if( SR->CConvWidthMotor.MoveAndWait( direction * moveValues[PANEL_CCONVW][moveIndex], REL_MOVE, SR->GetLimitsState() ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CONVWIDTHERROR, MSG_ERROR );
			SR->ErrorManagement();
		}
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->CConvWidthMotor.GetPosition() ) );
		break;

	default:
		break;
	}

	isBusy = false;
}

//----------------------------------------------------------------------------------
// MoveLR
// Muove l'asse LEFT o RIGHT
//----------------------------------------------------------------------------------
void wxControlPanel::MoveLR( int direction )
{
	if( isBusy )
		return;

	isBusy = true;

	float Resolution;

	switch( axisSelected )
	{
	case PANEL_CAMERA:
		if( moveIndex == 0 )
		{
			Resolution = ( PI * SR->DB->MotorParamsS[MOTOR_CAMERAX_ID].Pulley * SR->DB->MotorParamsS[MOTOR_CAMERAX_ID].Reduction ) / ( MOTOR_SPR * SR->DB->MotorParamsS[MOTOR_CAMERAX_ID].Microstepping );
			if( SR->MoveCameraAndWait( direction * Resolution, 0, REL_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
		}
		else
		{
			if( SR->MoveCameraAndWait( direction * moveValues[PANEL_CAMERA][moveIndex], 0, REL_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
		}
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->CamXMotor.GetPosition() ) );
		pos2Edit->SetValue( wxString::Format( "%0.2f", SR->CamYMotor.GetPosition() ) );
		break;

	case PANEL_TABLE:
		if( SR->MoveXYTableAndWait( direction * moveValues[PANEL_TABLE][moveIndex], 0, SR->GetLimitsState() ) == SR_ERROR )
		{
			smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
			SR->ErrorManagement();
		}
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->Table1Motor.GetPosition() ) );
		pos2Edit->SetValue( wxString::Format( "%0.2f", SR->Table2Motor.GetPosition() ) );
		pos3Edit->SetValue( wxString::Format( "%0.2f", SR->Table3Motor.GetPosition() ) );
		break;

	case PANEL_LCONVF:
		if( SR->LConvFeedMotor.MoveAndWait( direction * moveValues[PANEL_LCONVF][moveIndex], REL_MOVE, SR->GetLimitsState() ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CONVFEEDERROR, MSG_ERROR );
			SR->ErrorManagement();
		}
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LConvFeedMotor.GetPosition() ) );
		break;

	case PANEL_CCONVF:
		if( SR->CConvFeedMotor.MoveAndWait( direction * moveValues[PANEL_CCONVF][moveIndex], REL_MOVE, SR->GetLimitsState() ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CONVFEEDERROR, MSG_ERROR );
			SR->ErrorManagement();
		}
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->CConvFeedMotor.GetPosition() ) );
		break;
	case PANEL_LCONVP:
		if( SR->LConvPushMotor.MoveAndWait( SR->DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].Direction * direction * moveValues[PANEL_LCONVP][moveIndex], REL_MOVE, SR->GetLimitsState() ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CONVPUSHERROR, MSG_ERROR );
			SR->ErrorManagement();
		}
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LConvPushMotor.GetPosition() ) );
		break;

	default:
		break;
	}

	isBusy = false;
}

//----------------------------------------------------------------------------------
// Rotate
// Ruota la tavola CCW o CW
//----------------------------------------------------------------------------------
void wxControlPanel::Rotate( int direction )
{
	if( isBusy )
		return;

	isBusy = true;

	switch( axisSelected )
	{
	case PANEL_TABLE:
		if( SR->RotateTableAndWait( direction * rotateValues[rotateIndex], SR->GetLimitsState() ) == SR_ERROR )
		{
			smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
			SR->ErrorManagement();
		}
		pos1Edit->SetValue( wxString::Format( "%0.2f", SR->Table1Motor.GetPosition() ) );
		pos2Edit->SetValue( wxString::Format( "%0.2f", SR->Table2Motor.GetPosition() ) );
		pos3Edit->SetValue( wxString::Format( "%0.2f", SR->Table3Motor.GetPosition() ) );
		break;

	default:
		break;
	}

	isBusy = false;
}

void wxControlPanel::OnmoveUpBtnClick(wxCommandEvent& event)
{
	MoveUD( 1 );
}

void wxControlPanel::OnmoveDownBtnClick(wxCommandEvent& event)
{
	MoveUD( -1 );
}

void wxControlPanel::OnmoveLeftBtnClick(wxCommandEvent& event)
{
	MoveLR( -1 );
}

void wxControlPanel::OnmoveRightBtnClick(wxCommandEvent& event)
{
	MoveLR( 1 );
}

void wxControlPanel::OnrotCCWBtnClick(wxCommandEvent& event)
{
	Rotate( 1 );
}

void wxControlPanel::OnrotCWBtnClick(wxCommandEvent& event)
{
	Rotate( -1 );
}

void wxControlPanel::OnhomeBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;

	switch( axisSelected )
	{
		case PANEL_PLATE:
			if( SR->PlateMotor.MoveAndWait( 0, ABS_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->PlateMotor.GetPosition() ) );
			break;

		case PANEL_CAMERA:
			if( SR->MoveCameraAndWait( SR->DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit, SR->DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit, ABS_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->CamXMotor.GetPosition() ) );
			pos2Edit->SetValue( wxString::Format( "%0.2f", SR->CamYMotor.GetPosition() ) );
			break;

		case PANEL_SQUEEGEES:
			if( SR->SqueegeesMotor.MoveAndWait( 0, ABS_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_SQUEEGEESERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->SqueegeesMotor.GetPosition() ) );
			break;

		case PANEL_TABLE:
			if( SR->ResetTable() == SR_ERROR )
			{
				smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
				SR->ErrorManagement();
				break;
			}
			if( SR->WaitTable() == SR_ERROR )
			{
				smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
				SR->ErrorManagement();
				break;
			}
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->Table1Motor.GetPosition() ) );
			pos2Edit->SetValue( wxString::Format( "%0.2f", SR->Table2Motor.GetPosition() ) );
			pos3Edit->SetValue( wxString::Format( "%0.2f", SR->Table3Motor.GetPosition() ) );
			break;

		case PANEL_LOADER:
			if( SR->LoaderMotor.MoveAndWait( 0, ABS_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_LOADERERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LoaderMotor.GetPosition() ) );
			break;

		case PANEL_LCONVW:
			if( SR->LConvWidthMotor.MoveAndWait( 0, ABS_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CONVWIDTHERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LConvWidthMotor.GetPosition() ) );
			break;

		case PANEL_LCONVF:
			if( SR->LConvFeedMotor.MoveAndWait( 0, ABS_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CONVFEEDERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LConvFeedMotor.GetPosition() ) );
			break;

		case PANEL_CCONVW:
			if( SR->CConvWidthMotor.MoveAndWait( 0, ABS_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CONVWIDTHERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->CConvWidthMotor.GetPosition() ) );
			break;

		case PANEL_CCONVF:
			if( SR->CConvFeedMotor.MoveAndWait( 0, ABS_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CONVFEEDERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->CConvFeedMotor.GetPosition() ) );
			break;
		case PANEL_LCONVP:
			if( SR->LConvPushMotor.MoveAndWait( 0, ABS_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CONVPUSHERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LConvPushMotor.GetPosition() ) );
			break;

		default:
			break;
	}

	isBusy = false;
}

void wxControlPanel::OnendBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;

	switch( axisSelected )
	{
		case PANEL_PLATE:
			if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.PlateMovement + SR->DB->ProductionDataS.PlateMovementDelta, ABS_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->PlateMotor.GetPosition() ) );
			break;

		case PANEL_CAMERA:
			if( SR->MoveCameraAndWait( SR->DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit, SR->DB->LimitsS[MOTOR_CAMERAY_ID].MinLimit, ABS_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->CamXMotor.GetPosition() ) );
			pos2Edit->SetValue( wxString::Format( "%0.2f", SR->CamYMotor.GetPosition() ) );
			break;

		case PANEL_SQUEEGEES:
			if( SR->SqueegeesMotor.MoveAndWait( SR->DB->ProductionDataS.SqueegeesZeroMove, ABS_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_SQUEEGEESERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->SqueegeesMotor.GetPosition() ) );
			break;

		case PANEL_TABLE:
			break;

		case PANEL_LOADER:
			if( SR->LoaderMotor.MoveAndWait( SR->DB->LimitsS[MOTOR_LOADER_ID].MaxLimit, ABS_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_LOADERERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LoaderMotor.GetPosition() ) );
			break;

		case PANEL_LCONVW:
			if( SR->LConvWidthMotor.MoveAndWait( SR->DB->LimitsS[MOTOR_LCONV_WIDTH_ID].MinLimit, ABS_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CONVWIDTHERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LConvWidthMotor.GetPosition() ) );
			break;

		case PANEL_LCONVF:
			if( SR->LConvFeedMotor.MoveAndWait( SR->DB->LimitsS[MOTOR_LCONV_FEED_ID].MaxLimit, ABS_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CONVFEEDERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LConvFeedMotor.GetPosition() ) );
			break;

		case PANEL_CCONVW:
			if( SR->CConvWidthMotor.MoveAndWait( SR->DB->LimitsS[MOTOR_CCONV_WIDTH_ID].MinLimit, ABS_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CONVWIDTHERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->CConvWidthMotor.GetPosition() ) );
			break;

		case PANEL_CCONVF:
			if( SR->CConvFeedMotor.MoveAndWait( SR->DB->LimitsS[MOTOR_CCONV_FEED_ID].MaxLimit, ABS_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CONVFEEDERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->CConvFeedMotor.GetPosition() ) );
			break;
		case PANEL_LCONVP:
			if( SR->LConvPushMotor.MoveAndWait( SR->DB->LimitsS[MOTOR_LCONV_PUSH_ID].MaxLimit, ABS_MOVE, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CONVPUSHERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LConvPushMotor.GetPosition() ) );
			break;

		default:
			break;
	}

	isBusy = false;
}

void wxControlPanel::OnmoveUserEditText(wxCommandEvent& event)
{
	TransferDataFromWindow();
	moveValues[axisSelected][3] = moveValidatorValue;
}

void wxControlPanel::OnrotateUserEditText(wxCommandEvent& event)
{
	TransferDataFromWindow();
	rotateValues[3] = rotateValidatorValue;
}

void wxControlPanel::OnframeLockBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->SetOutput( OUTPUT_FRAMEUNLOCK, !SR->isFrameUnlocked ) == SR_ERROR )
	{
		smartLogger->Write( MSG_FRAMELOCKERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxControlPanel::OnsqueegeesFrontBtnClick(wxCommandEvent& event)
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

void wxControlPanel::OnsqueegeesRearBtnClick(wxCommandEvent& event)
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

void wxControlPanel::OnalarmLightGreenBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->SetAlarmLight( SR->isSemaphoreGreen ? ALARMLIGHT_OFF : ALARMLIGHT_GREEN ) == SR_ERROR )
	{
		smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxControlPanel::OnalarmLightYellowBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->SetAlarmLight( SR->isSemaphoreYellow ? ALARMLIGHT_OFF : ALARMLIGHT_YELLOW ) == SR_ERROR )
	{
		smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxControlPanel::OnalarmLightRedBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->SetAlarmLight( SR->isSemaphoreRed ? ALARMLIGHT_OFF : ALARMLIGHT_RED ) == SR_ERROR )
	{
		smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxControlPanel::OnbuzzerBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->SetOutput( OUTPUT_BUZZER, !SR->isBuzzerOn ) == SR_ERROR )
	{
		smartLogger->Write( MSG_BUZZERERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxControlPanel::OnledUpBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->SetOutput( OUTPUT_LEDUP, !SR->isLedUpOn ) == SR_ERROR )
	{
		smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxControlPanel::OnledDownBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->SetOutput( OUTPUT_LEDDOWN, !SR->isLedDownOn ) == SR_ERROR )
	{
		smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxControlPanel::OnboardLockBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->SetOutput( OUTPUT_BOARDLOCK, !SR->isBoardLocked ) == SR_ERROR )
	{
		smartLogger->Write( MSG_BOARDLOCKERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxControlPanel::OnconvPistonBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->convPusherEnabled(!SR->isConveyorPistonOn) == SR_ERROR ){
		smartLogger->Write( MSG_CONVPISTONERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxControlPanel::OncameraPistonBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->SetOutput( OUTPUT_CAMERA_PISTON, !SR->isCameraPistonOn ) == SR_ERROR )
	{
		smartLogger->Write( MSG_CAMPISTONERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxControlPanel::OnloaderPistonBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->SetOutput( OUTPUT_LOADER_PISTON, !SR->isLoaderPistonOn ) == SR_ERROR )
	{
		smartLogger->Write( MSG_LOADERPISTONERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxControlPanel::OnmoveRadioSelect(wxCommandEvent& event)
{
	if( moveRadio1->GetValue() )
		moveIndex = 0;
	else if( moveRadio2->GetValue() )
		moveIndex = 1;
	else if( moveRadio3->GetValue() )
		moveIndex = 2;
	else
		moveIndex = 3;
}

void wxControlPanel::OnrotateRadioSelect(wxCommandEvent& event)
{
	if( rotateRadio1->GetValue() )
		rotateIndex = 0;
	else if( rotateRadio2->GetValue() )
		rotateIndex = 1;
	else if( rotateRadio3->GetValue() )
		rotateIndex = 2;
	else
		rotateIndex = 3;
}

void wxControlPanel::OnaxisComboSelect(wxCommandEvent& event)
{
	switch( axisCombo->GetSelection() )
	{
		case 0:
			SetMovement( true, true, PANEL_TABLE );
			SetRotation( true );
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->Table1Motor.GetPosition() ) );
			pos2Edit->SetValue( wxString::Format( "%0.2f", SR->Table2Motor.GetPosition() ) );
			pos3Edit->SetValue( wxString::Format( "%0.2f", SR->Table3Motor.GetPosition() ) );
			break;
		case 1:
			SetMovement( true, true, PANEL_CAMERA );
			SetRotation( false );
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->CamXMotor.GetPosition() ) );
			pos2Edit->SetValue( wxString::Format( "%0.2f", SR->CamYMotor.GetPosition() ) );
			break;
		case 2:
			SetMovement( true, false, PANEL_SQUEEGEES );
			SetRotation( false );
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->SqueegeesMotor.GetPosition() ) );
			break;
		case 3:
			SetMovement( true, false, PANEL_PLATE );
			SetRotation( false );
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->PlateMotor.GetPosition() ) );
			break;
		case 4:
			SetMovement( true, false, PANEL_LCONVW );
			SetRotation( false );
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LConvWidthMotor.GetPosition() ) );
			break;
		case 5:
			SetMovement( false, true, PANEL_LCONVF );
			SetRotation( false );
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LConvFeedMotor.GetPosition() ) );
			break;
		case 6:
			SetMovement( true, false, PANEL_CCONVW );
			SetRotation( false );
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->CConvWidthMotor.GetPosition() ) );
			break;
		case 7:
			SetMovement( false, true, PANEL_CCONVF );
			SetRotation( false );
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->CConvFeedMotor.GetPosition() ) );
			break;
		case 8:
			SetMovement( true, false, PANEL_LOADER );
			SetRotation( false );
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LoaderMotor.GetPosition() ) );
			break;
		case 9:
			SetMovement( false, true, PANEL_LCONVP );
			SetRotation( false );
			pos1Edit->SetValue( wxString::Format( "%0.2f", SR->LConvPushMotor.GetPosition() ) );
			break;
		default:
			return;
	}

	// set positions box
	pos1Edit->Show( true );
	pos2Edit->Show( axisCombo->GetSelection()==0 || axisCombo->GetSelection()==1 ? true : false );
	pos3Edit->Show( axisCombo->GetSelection()==0 ? true : false );
	BoxSizerPos->Layout();
}

void wxControlPanel::OncleaningLockBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->SetOutput( OUTPUT_CLEANINGLOCK, !SR->isCleaningLockOn ) == SR_ERROR )
	{
		smartLogger->Write( MSG_CLEANPISTONERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxControlPanel::OncleaningVacuumBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->SetOutput( OUTPUT_CLEANINGVACUUM, !SR->isCleaningVacuumOn ) == SR_ERROR )
	{
		smartLogger->Write( MSG_CLEANVACUUMERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxControlPanel::OncleaningFeedingBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	// Advance cleaning wipe
	if( SR->CleanerMotor.MoveAndWait( SR->DB->MachineParamsS.CleaningActivationTime ) == SR_ERROR )
	{
		smartLogger->Write( MSG_CLEANERERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}


void wxControlPanel::OnCleaningActBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;
	if( SR->SetOutput( OUTPUT_CLEANINGACTIVATE, !SR->isCleaningActive ) == SR_ERROR )
	{
		smartLogger->Write( MSG_CLEANPISTONERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	isBusy = false;
}

void wxControlPanel::OnSwitchLightsBtnClick(wxCommandEvent& event)
{
	if(LightsTimer->IsRunning()){
		LightsTimer->Stop();
	}else{
		LightsTimer->Start( 1000, false );
	}
}

/*void wxControlPanel::OnCharPressed(wxKeyEvent& event){
	cout<<"Funzione chamata dal panel "<<endl;
	if(event.GetKeyCode() == WXK_ESCAPE){
		SR->SetBuzzerState(false);
	}
}*/


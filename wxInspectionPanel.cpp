#include "images/png_images.h"

#include "wxInspectionPanel.h"

//(*InternalHeaders(wxInspectionPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "wxAreaPanel.h"
#include "wxMyTextValidator.h"
#include "wxMyComboValidator.h"
#include "GlobalUtils.h"
#include "GlobalEnum.h"
#include "Messages.h"
#include "FileFunctions.h"

#include "SRDatabase.h"


#define TABLE_FG_DIS_COLOR		wxColor( 176, 176, 176 )
#define TABLE_BG_DIS_COLOR		GetBackgroundColour()
#define MAX_SITE_NAME_LENGHT	30
#define TABLE_FG_COLOR			wxColor( 255, 255, 0 )
#define TABLE_BG_COLOR			wxColor( 128, 128, 128 )


const long wxInspectionPanel::ID_EVENT = wxNewId();
const int wxInspectionPanel::EVT_TEACH = 1;
const int wxInspectionPanel::EVT_OK = 2;
const int wxInspectionPanel::EVT_CANCEL = 3;
const int wxInspectionPanel::EVT_THRESHOLD = 4;
const int wxInspectionPanel::EVT_SET_THRESHOLD = 5;
const int wxInspectionPanel::EVT_NEED_REFRESH = 6;
const int wxInspectionPanel::EVT_NEED_REFRESH_IMAGE = 7;
const int wxInspectionPanel::EVT_NEED_UPDATE = 8;
const int wxInspectionPanel::EVT_MOVMENT = 10;




//(*IdInit(wxInspectionPanel)
const long wxInspectionPanel::ID_STATICTEXT2 = wxNewId();
const long wxInspectionPanel::ID_COMBOBOX1 = wxNewId();
const long wxInspectionPanel::ID_STATICTEXT8 = wxNewId();
const long wxInspectionPanel::ID_CHECKLISTBOX1 = wxNewId();
const long wxInspectionPanel::ID_BITMAPBUTTON9 = wxNewId();
const long wxInspectionPanel::ID_BITMAPBUTTON10 = wxNewId();
const long wxInspectionPanel::ID_STATICLINE3 = wxNewId();
const long wxInspectionPanel::ID_STATICTEXT4 = wxNewId();
const long wxInspectionPanel::ID_TEXTCTRL1 = wxNewId();
const long wxInspectionPanel::ID_STATICTEXT5 = wxNewId();
const long wxInspectionPanel::ID_CUSTOM13 = wxNewId();
const long wxInspectionPanel::ID_STATICLINE2 = wxNewId();
const long wxInspectionPanel::ID_CUSTOM10 = wxNewId();
const long wxInspectionPanel::ID_BITMAPBUTTON16 = wxNewId();
const long wxInspectionPanel::ID_CUSTOM4 = wxNewId();
const long wxInspectionPanel::ID_BITMAPBUTTON17 = wxNewId();
const long wxInspectionPanel::ID_BITMAPBUTTON18 = wxNewId();
const long wxInspectionPanel::ID_BITMAPBUTTON1 = wxNewId();
const long wxInspectionPanel::ID_BITMAPBUTTON4 = wxNewId();
const long wxInspectionPanel::ID_BITMAPBUTTON3 = wxNewId();
const long wxInspectionPanel::ID_BITMAPBUTTON2 = wxNewId();
const long wxInspectionPanel::ID_BITMAPBUTTON6 = wxNewId();
const long wxInspectionPanel::ID_BITMAPBUTTON5 = wxNewId();
const long wxInspectionPanel::ID_STATICTEXT3 = wxNewId();
const long wxInspectionPanel::ID_SPINCTRL1 = wxNewId();
const long wxInspectionPanel::ID_STATICTEXT6 = wxNewId();
const long wxInspectionPanel::ID_SPINCTRL2 = wxNewId();
const long wxInspectionPanel::ID_STATICLINE4 = wxNewId();
const long wxInspectionPanel::ID_PANEL3 = wxNewId();
const long wxInspectionPanel::ID_PANEL5 = wxNewId();
const long wxInspectionPanel::ID_BITMAPBUTTON15 = wxNewId();
const long wxInspectionPanel::ID_STATICTEXT1 = wxNewId();
const long wxInspectionPanel::ID_BITMAPBUTTON11 = wxNewId();
const long wxInspectionPanel::ID_BITMAPBUTTON12 = wxNewId();
const long wxInspectionPanel::ID_PANEL2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxInspectionPanel,wxPanel)
	//(*EventTable(wxInspectionPanel)
	//*)
END_EVENT_TABLE()

wxInspectionPanel::wxInspectionPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxInspectionPanel)
	wxBoxSizer* spiDataSizer;
	wxBoxSizer* BoxSizer6;
	wxBoxSizer* wxSizerT1;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* siteSizer;
	wxBoxSizer* BoxSizer10;
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* BoxSizer11;
	wxBoxSizer* BoxSizer12;
	wxFlexGridSizer* FlexGridSizer1;
	wxBoxSizer* wxSizerT11;
	wxBoxSizer* wxSizerT12;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	SetBackgroundColour(wxColour(208,208,208));
	SetExtraStyle( GetExtraStyle() | wxWS_EX_VALIDATE_RECURSIVELY );
	mainSizer = new wxBoxSizer(wxVERTICAL);
	modeSizer = new wxBoxSizer(wxHORIZONTAL);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT2, _("Verify mode"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	modeSizer->Add(StaticText3, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	inspectionTypeCombo = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxSize(140,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX1"));
	modeSizer->Add(inspectionTypeCombo, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	mainSizer->Add(modeSizer, 0, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	sitesPanel = new wxPanel(this, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
	sitesPanel->SetBackgroundColour(wxColour(192,192,192));
	BoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
	sitesListSizer = new wxBoxSizer(wxVERTICAL);
	StaticText7 = new wxStaticText(sitesPanel, ID_STATICTEXT8, _("Inspection points"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	sitesListSizer->Add(StaticText7, 0, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	sitesCheckList = new wxCheckListBox(sitesPanel, ID_CHECKLISTBOX1, wxDefaultPosition, wxSize(109,150), 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX1"));
	sitesListSizer->Add(sitesCheckList, 1, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
	addSiteBtn = new wxBitmapButton(sitesPanel, ID_BITMAPBUTTON9, wxNullBitmap, wxDefaultPosition, wxSize(26,26), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON9"));
	addSiteBtn->SetDefault();
	BoxSizer10->Add(addSiteBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	removeSiteBtn = new wxBitmapButton(sitesPanel, ID_BITMAPBUTTON10, wxNullBitmap, wxDefaultPosition, wxSize(26,26), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON10"));
	removeSiteBtn->SetDefault();
	BoxSizer10->Add(removeSiteBtn, 0, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	sitesListSizer->Add(BoxSizer10, 0, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer12->Add(sitesListSizer, 0, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticLine3 = new wxStaticLine(sitesPanel, ID_STATICLINE3, wxDefaultPosition, wxSize(2,-1), wxLI_VERTICAL, _T("ID_STATICLINE3"));
	BoxSizer12->Add(StaticLine3, 0, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	siteSizer = new wxBoxSizer(wxVERTICAL);
	namePosSizer = new wxFlexGridSizer(0, 2, 1, 5);
	StaticText4 = new wxStaticText(sitesPanel, ID_STATICTEXT4, _("Name"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	namePosSizer->Add(StaticText4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	nameValueText = new wxTextCtrl(sitesPanel, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(140,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	namePosSizer->Add(nameValueText, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(sitesPanel, ID_STATICTEXT5, _("Position (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	namePosSizer->Add(StaticText5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	positionValuePP = new wxPanelPlus(sitesPanel,ID_CUSTOM13,wxDefaultPosition,wxSize(140,21));
	namePosSizer->Add(positionValuePP, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	siteSizer->Add(namePosSizer, 0, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	spiPanel = new wxPanel(sitesPanel, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	spiPanel->SetBackgroundColour(wxColour(192,192,192));
	spiDataSizer = new wxBoxSizer(wxVERTICAL);
	StaticLine2 = new wxStaticLine(spiPanel, ID_STATICLINE2, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
	spiDataSizer->Add(StaticLine2, 0, wxTOP|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	thrSizer = new wxBoxSizer(wxHORIZONTAL);
	thresholdPP = new wxPanelPlus(spiPanel,ID_CUSTOM10,wxDefaultPosition,wxSize(140,21));
	thrSizer->Add(thresholdPP, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
	thrMinusBtn = new wxBitmapButton(spiPanel, ID_BITMAPBUTTON16, wxNullBitmap, wxDefaultPosition, wxSize(23,23), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON16"));
	BoxSizer11->Add(thrMinusBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	thresholdValuePP = new wxPanelPlus(spiPanel,ID_CUSTOM4,wxDefaultPosition,wxSize(-1,21));
	BoxSizer11->Add(thresholdValuePP, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	thrPlusBtn = new wxBitmapButton(spiPanel, ID_BITMAPBUTTON17, wxNullBitmap, wxDefaultPosition, wxSize(23,23), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON17"));
	BoxSizer11->Add(thrPlusBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	thrGetBtn = new wxBitmapButton(spiPanel, ID_BITMAPBUTTON18, wxNullBitmap, wxDefaultPosition, wxSize(23,23), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON18"));
	thrGetBtn->SetDefault();
	BoxSizer11->Add(thrGetBtn, 0, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	thrSizer->Add(BoxSizer11, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	spiDataSizer->Add(thrSizer, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerT1 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	moveLeftBtn = new wxBitmapButton(spiPanel, ID_BITMAPBUTTON1, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	moveLeftBtn->SetDefault();
	BoxSizer5->Add(moveLeftBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerT11 = new wxBoxSizer(wxVERTICAL);
	moveUpBtn = new wxBitmapButton(spiPanel, ID_BITMAPBUTTON4, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON4"));
	moveUpBtn->SetDefault();
	wxSizerT11->Add(moveUpBtn, 0, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	moveDownBtn = new wxBitmapButton(spiPanel, ID_BITMAPBUTTON3, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
	moveDownBtn->SetDefault();
	wxSizerT11->Add(moveDownBtn, 0, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer5->Add(wxSizerT11, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	moveRightBtn = new wxBitmapButton(spiPanel, ID_BITMAPBUTTON2, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
	moveRightBtn->SetDefault();
	BoxSizer5->Add(moveRightBtn, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerT1->Add(BoxSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerT12 = new wxBoxSizer(wxVERTICAL);
	Expand_button = new wxBitmapButton(spiPanel, ID_BITMAPBUTTON6, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON6"));
	wxSizerT12->Add(Expand_button, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Reduce_button = new wxBitmapButton(spiPanel, ID_BITMAPBUTTON5, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON5"));
	wxSizerT12->Add(Reduce_button, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerT1->Add(wxSizerT12, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1 = new wxFlexGridSizer(4, 1, -10, 0);
	StaticText1 = new wxStaticText(spiPanel, ID_STATICTEXT3, _("Alarm"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SpinAlarm = new wxSpinCtrl(spiPanel, ID_SPINCTRL1, _T("80"), wxDefaultPosition, wxDefaultSize, 0, 10, 100, 80, _T("ID_SPINCTRL1"));
	SpinAlarm->SetValue(_T("80"));
	FlexGridSizer1->Add(SpinAlarm, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(spiPanel, ID_STATICTEXT6, _("Warning"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer1->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	SpinWarning = new wxSpinCtrl(spiPanel, ID_SPINCTRL2, _T("90"), wxDefaultPosition, wxDefaultSize, 0, 10, 100, 90, _T("ID_SPINCTRL2"));
	SpinWarning->SetValue(_T("90"));
	FlexGridSizer1->Add(SpinWarning, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerT1->Add(FlexGridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	spiDataSizer->Add(wxSizerT1, 0, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticLine4 = new wxStaticLine(spiPanel, ID_STATICLINE4, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE4"));
	spiDataSizer->Add(StaticLine4, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	spiPanel->SetSizer(spiDataSizer);
	spiDataSizer->Fit(spiPanel);
	spiDataSizer->SetSizeHints(spiPanel);
	siteSizer->Add(spiPanel, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer12->Add(siteSizer, 1, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	sitesPanel->SetSizer(BoxSizer12);
	BoxSizer12->Fit(sitesPanel);
	BoxSizer12->SetSizeHints(sitesPanel);
	mainSizer->Add(sitesPanel, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	teachSizer = new wxBoxSizer(wxHORIZONTAL);
	teachSizer->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	teachBtn = new wxBitmapButton(this, ID_BITMAPBUTTON15, wxNullBitmap, wxDefaultPosition, wxSize(56,56), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON15"));
	teachBtn->SetDefault();
	teachSizer->Add(teachBtn, 0, wxRIGHT|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	teachPanel = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	teachPanel->SetBackgroundColour(wxColour(192,192,192));
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	StaticText2 = new wxStaticText(teachPanel, ID_STATICTEXT1, _("Save changes\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer7->Add(StaticText2, 1, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	okBtn = new wxBitmapButton(teachPanel, ID_BITMAPBUTTON11, wxNullBitmap, wxDefaultPosition, wxSize(34,34), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON11"));
	okBtn->SetDefault();
	BoxSizer7->Add(okBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cancelBtn = new wxBitmapButton(teachPanel, ID_BITMAPBUTTON12, wxNullBitmap, wxDefaultPosition, wxSize(34,34), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON12"));
	cancelBtn->SetDefault();
	BoxSizer7->Add(cancelBtn, 0, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer6->Add(BoxSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	teachPanel->SetSizer(BoxSizer6);
	BoxSizer6->Fit(teachPanel);
	BoxSizer6->SetSizeHints(teachPanel);
	teachSizer->Add(teachPanel, 0, wxRIGHT|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	mainSizer->Add(teachSizer, 0, wxTOP|wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(mainSizer);
	mainSizer->Fit(this);
	mainSizer->SetSizeHints(this);

	Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&wxInspectionPanel::OninspectionTypeComboSelect);
	Connect(ID_CHECKLISTBOX1,wxEVT_COMMAND_CHECKLISTBOX_TOGGLED,(wxObjectEventFunction)&wxInspectionPanel::OnsitesCheckListToggled);
	Connect(ID_CHECKLISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&wxInspectionPanel::OnsitesCheckListSelect);
	Connect(ID_BITMAPBUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OnaddSiteBtnClick);
	Connect(ID_BITMAPBUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OnremoveSiteBtnClick);
	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&wxInspectionPanel::OnnameValueTextText);
	Connect(ID_BITMAPBUTTON16,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OnthrMinusBtnClick);
	Connect(ID_BITMAPBUTTON17,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OnthrPlusBtnClick);
	Connect(ID_BITMAPBUTTON18,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OnthrGetBtnClick);
	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OnMoveLeftBtnClick);
	Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OnMoveUpBtnClick);
	Connect(ID_BITMAPBUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OnMoveDownBtnClick);
	Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OnMoveRightBtnClick);
	Connect(ID_BITMAPBUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OnEnlargeBtnClick);
	Connect(ID_BITMAPBUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OnReduceBtnClick);
	Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&wxInspectionPanel::OnSpinAlarmChange);
	Connect(ID_SPINCTRL2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&wxInspectionPanel::OnSpinWarningChange);
	Connect(ID_BITMAPBUTTON15,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OnteachBtnClick);
	Connect(ID_BITMAPBUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OnokBtnClick);
	Connect(ID_BITMAPBUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OncancelBtnClick);
	//*)

	// init buttons image
	addSiteBtn->SetBitmapDisabled( wxMEMORY_BITMAP( add_xsmall ) );
	addSiteBtn->SetBitmapLabel( wxMEMORY_BITMAP( add_xsmall_on ) );
	removeSiteBtn->SetBitmapDisabled( wxMEMORY_BITMAP( delete_xsmall ) );
	removeSiteBtn->SetBitmapLabel( wxMEMORY_BITMAP( delete_xsmall_on ) );
	okBtn->SetBitmapLabel( wxMEMORY_BITMAP( ok_small_on ) );
	okBtn->SetBitmapDisabled( wxMEMORY_BITMAP( ok_small ) );
	cancelBtn->SetBitmapLabel( wxMEMORY_BITMAP( cancel_small_on ) );
	cancelBtn->SetBitmapDisabled( wxMEMORY_BITMAP( cancel_small ) );
	teachBtn->SetBitmapDisabled( wxMEMORY_BITMAP( teach_off ) );
	teachBtn->SetBitmapLabel( wxMEMORY_BITMAP( teach_on ) );
	thrMinusBtn->SetBitmapDisabled( wxMEMORY_BITMAP( minus_round ) );
	thrMinusBtn->SetBitmapLabel( wxMEMORY_BITMAP( minus_round_on ) );
	thrPlusBtn->SetBitmapDisabled( wxMEMORY_BITMAP( plus_round ) );
	thrPlusBtn->SetBitmapLabel( wxMEMORY_BITMAP( plus_round_on ) );
	thrGetBtn->SetBitmapDisabled( wxMEMORY_BITMAP( graph_off ) );
	thrGetBtn->SetBitmapLabel( wxMEMORY_BITMAP( graph_on ) );


	moveLeftBtn->SetBitmapDisabled( wxMEMORY_BITMAP( left_off ) );
	moveLeftBtn->SetBitmapLabel( wxMEMORY_BITMAP( left_on ) );
	moveRightBtn->SetBitmapDisabled( wxMEMORY_BITMAP( right_off ) );
	moveRightBtn->SetBitmapLabel( wxMEMORY_BITMAP( right_on ) );
	moveUpBtn->SetBitmapDisabled( wxMEMORY_BITMAP( up ) );
	moveUpBtn->SetBitmapLabel( wxMEMORY_BITMAP( up_on ) );
	moveDownBtn->SetBitmapDisabled( wxMEMORY_BITMAP( down ) );
	moveDownBtn->SetBitmapLabel( wxMEMORY_BITMAP( down_on ) );

	//those 2 buttons are used to scale the original picture

	Expand_button->SetBitmapLabel( wxMEMORY_BITMAP( expand32 ) );

	Reduce_button->SetBitmapLabel( wxMEMORY_BITMAP( reduce32 ) );


	// init buttons tooltip
	addSiteBtn->SetToolTip( TOO_ADDSITE );
	removeSiteBtn->SetToolTip( TOO_REMOVESITE );
	thrGetBtn->SetToolTip( TOO_SELECTTHR );
	teachBtn->SetToolTip( TOO_TEACHSPI );
	okBtn->SetToolTip( TOO_OK );
	cancelBtn->SetToolTip( TOO_CANCEL );

	// connect extra events
	Connect( wxEVT_COMMAND_BUTTON_CLICKED ,(wxObjectEventFunction)&wxInspectionPanel::OnGUIEvents );
}

wxInspectionPanel::~wxInspectionPanel()
{
	//(*Destroy(wxInspectionPanel)
	//*)
}

//----------------------------------------------------------------------------------
// Init
// Inizializza il controllo
//----------------------------------------------------------------------------------
bool wxInspectionPanel::Init( SRDatabase* DBRef )
{

	/*Connect(ID_BITMAPBUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OnMoveDownBtnClick);
	Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OnMoveUpBtnClick);
	Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OnMoveRightBtnClick);
	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OnMoveLeftBtnClick);

	Connect(ID_BITMAPBUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OnEnlargeBtnClick);
	Connect(ID_BITMAPBUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionPanel::OnReduceBtnClick);*/
	DB = DBRef;

	vetoEvents = true;
	_ballDiameter = 0.f;

	// set label
	thresholdPP->SetLabel( _("Threshold") );

	// init combo labels
	wxArrayString comboLabels;
	comboLabels.Add(_("Operator"));
	if( DB->MachineParamsS.CleaningInstalled ){
		comboLabels.Add(_("Software SPI"));
	}
	inspectionTypeCombo->Append( comboLabels );

	// set validator
	inspectionTypeCombo->SetValidator( wxMyComboValidator( &DB->WorkingModesS.InspectionType ) );
	//ballDiameterEdit->SetValidator( wxMyTextValidator( &_ballDiameter, false, 2 ) );

	// set foreground disable color
	thresholdPP->SetForegroundDisableColour( TABLE_FG_DIS_COLOR );
	positionValuePP->SetForegroundDisableColour( TABLE_FG_DIS_COLOR );
	thresholdValuePP->SetForegroundDisableColour( TABLE_FG_DIS_COLOR );

	// set foreground color
	thresholdPP->SetForegroundColour( TABLE_FG_COLOR );

	// set background disable color
	thresholdPP->SetBackgroundDisableColour( TABLE_BG_DIS_COLOR );

	// set background color
	thresholdPP->SetBackgroundColour( TABLE_BG_COLOR );

	nameValueText->SetMaxLength(MAX_SITE_NAME_LENGHT);

	return true;
}

//----------------------------------------------------------------------------------
// ShowControl
//----------------------------------------------------------------------------------
bool wxInspectionPanel::ShowControl()
{
	DrawControl( IP_OFFLINE );

	return true;
}

//----------------------------------------------------------------------------------
// HideControl
//----------------------------------------------------------------------------------
bool wxInspectionPanel::HideControl()
{
	if( DB->SiteCount() )
	{
		// needs to save any changes on the "name" field
		//DB->SaveInspectionSite( DB->SiteGetSelected() );
		DB->UpdateName( DB->SiteGetSelected() );
	}
	return true;
}

//----------------------------------------------------------------------------------
// DrawControl
//
//----------------------------------------------------------------------------------
void wxInspectionPanel::DrawControl( InspectionEnum mode )
{
	bool needLayout = false;

	if( mode != IP_UPDATE )
		currentMode = mode;

	//Freeze();

	// update navigation toolbar and site data
	if( currentMode == IP_OFFLINE )
	{
		EnableSizerChilds( modeSizer, true );
		UpdateListSizer( 1 ); // enable
		UpdateSiteData( 2 ); // enable and editable + en_check enable
	}
	else if( currentMode == IP_OFFLINE_NO_IMG )
	{
		EnableSizerChilds( modeSizer, true );
		UpdateListSizer( 1 ); // enable
		UpdateSiteData( 1 ); // enable and editable + en_check disable
	}
	else if( currentMode == IP_ONLINE_MOVE )
	{
		EnableSizerChilds( modeSizer, false );
		UpdateListSizer( 1 ); // enable
		UpdateSiteData( 1 ); // enable and editable + en_check disable
	}
	else if( currentMode == IP_TEACH )
	{
		EnableSizerChilds( modeSizer, false );
		UpdateListSizer( 0 ); // all disable
		UpdateSiteData( 1 ); // enable and editable + en_check disable
	}
	else if(currentMode ==IP_TEACH_OFFLINE){
		EnableSizerChilds( modeSizer, false );
		UpdateListSizer( 0 ); // all disable
		UpdateSiteData( 1 ); // enable and editable + en_check disable
	}
	else if( currentMode == IP_TEACH_THR )
	{
		EnableSizerChilds( modeSizer, false );
		UpdateListSizer( 0 ); // all disable
		UpdateSiteData( 0 ); // all disable
	}

	// show hide SPI data
	if( DB->WorkingModesS.InspectionType == INSPECTION_SPI )
	{
		if( !spiPanel->IsShown() )
		{
			spiPanel->Show( true );
			needLayout = true;
		}

		// update SPI data
		if( currentMode == IP_OFFLINE )
		{
			UpdateThreshold( 2 ); // enable but not editable + thr off
			UpdateAreas( 2 ); // enable but not editable
			UpdateAlarmAndWarning();
			spiPanel->Disable();
			nameValueText->Enable(false);
			addSiteBtn->Enable(true);
			removeSiteBtn->Enable(true);
		}
		else if( currentMode == IP_OFFLINE_NO_IMG )
		{
			UpdateThreshold( 0 ); // all disable
			UpdateAreas( 0 ); // all disable
		}
		else if( currentMode == IP_ONLINE_MOVE )
		{
			UpdateThreshold( 0 ); // all disable
			UpdateAreas( 0 ); // all disable
			UpdateAlarmAndWarning();
			addSiteBtn->Enable(false);
			removeSiteBtn->Enable(false);
			spiPanel->Enable(false);
			nameValueText->Enable(false);
		}
		else if( currentMode == IP_TEACH )
		{
			spiPanel->Enable();
			nameValueText->Enable(true);
			UpdateThreshold( 1 ); // enable and editable + thr on
			UpdateAreas( 1 ); // enable and editable
			UpdateAlarmAndWarning();
		}
		else if( currentMode == IP_TEACH_OFFLINE ){
			spiPanel->Enable();
			nameValueText->Enable(true);
			UpdateThreshold( 4 ); // enable and editable + thr on, no draw
			UpdateAreas( 1 ); // enable and editable
			UpdateAlarmAndWarning();
		}
		else if( currentMode == IP_TEACH_THR )
		{
			spiPanel->Enable();
			nameValueText->Enable(true);
			UpdateThreshold( 3 ); // disable + thr on
			UpdateAreas( 0 ); // all disable
			UpdateAlarmAndWarning();
		}
		else if( currentMode== TEACH_OFFLINE){
			spiPanel->Enable();
			nameValueText->Enable(true);
			UpdateThreshold( 4 ); // enable and editable + thr on
			UpdateAreas( 1 ); // enable and editable
			UpdateAlarmAndWarning();
		}
	}
	else
	{
		if( spiPanel->IsShown() )
		{
			spiPanel->Show( false );
			nameValueText->Enable(false);
			needLayout = true;
		}
	}

	// update teach tools
	if( currentMode == IP_OFFLINE )
	{
		// should not be possible if INSPECTION_OPERATOR
		UpdateTeach( 1 ); // show teach (enable) + hide ok/cancel
	}
	else if( currentMode == IP_OFFLINE_NO_IMG )
	{
		UpdateTeach( 0 ); // show teach (disable) + hide ok/cancel
	}
	else if( currentMode == IP_ONLINE_MOVE )
	{
		UpdateTeach( 1 ); // show teach (enable) + hide ok/cancel
	}
	else if( currentMode == IP_TEACH )
	{
		// should not be possible if INSPECTION_OPERATOR
		UpdateTeach( 2 ); // hide teach + show ok/cancel (enable)
	}
	else if( currentMode == IP_TEACH_OFFLINE )
	{
		// should not be possible if INSPECTION_OPERATOR
		UpdateTeach( 2 ); // hide teach + show ok/cancel (enable)
	}
	else if( currentMode == IP_TEACH_THR )
	{
		// should not be possible if INSPECTION_OPERATOR
		UpdateTeach( 3 ); // hide teach + hide ok/cancel (disable)
	}

	if( needLayout )
	{
		mainSizer->SetSizeHints(this);
		GetParent()->Layout();
	}

	TransferDataToWindow();

	Thaw();
	Refresh();
}

//----------------------------------------------------------------------------------
// FireEvent
//----------------------------------------------------------------------------------
void wxInspectionPanel::FireEvent( int eventType )
{
	wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
	e.SetId( ID_EVENT );
	e.SetInt( eventType );
	GetParent()->GetEventHandler()->AddPendingEvent( e );
}

//----------------------------------------------------------------------------------
// UpdateListSizer
//   mode: 1 - enable
//         other - all disable
//----------------------------------------------------------------------------------
void wxInspectionPanel::UpdateListSizer( char mode )
{
	vetoEvents = true;

	sitesCheckList->Clear();
	//cout<<DB->SiteCount()<<endl;
	for( int i = 0; i < DB->SiteCount(); i++ )
	{
		sitesCheckList->AppendString( wxString::Format( "%d. %s", i+1, DB->AUTOInspectionSiteStruct[i].Name.ToAscii() ) );
		sitesCheckList->Check( i, DB->AUTOInspectionSiteStruct[i].Enable ? true : false );
	}
	if( DB->SiteCount() > 0 )
		sitesCheckList->Select( DB->SiteGetSelected() );

	switch( mode )
	{
	case 1: // enable
		EnableSizerChilds( sitesListSizer, true );
		break;

	default: // all disable
		EnableSizerChilds( sitesListSizer, false );
		break;
	}

	vetoEvents = false;
}

//----------------------------------------------------------------------------------
// UpdateSiteData
//   mode: 1 - enable and editable + en_check disable
//         2 - enable and editable + en_check enable
//         other - all disable
//----------------------------------------------------------------------------------
void wxInspectionPanel::UpdateSiteData( char mode )
{
	if( DB->SiteCount() )
	{

		nameValueText->ChangeValue( DB->pAUTOInspectionCurrentSiteStruct->Name );
		//nameValueText->ChangeValue( "schifo" );
		positionValuePP->SetLabel( wxString::Format( "X: %.1f  Y: %.1f", DB->pAUTOInspectionCurrentSiteStruct->X, DB->pAUTOInspectionCurrentSiteStruct->Y ) );

		if( DB->WorkingModesS.InspectionType == INSPECTION_SPI )
		{
			switch( mode )
			{
			case 1: // enable and editable + en_check disable
				EnableSizerChilds( namePosSizer, true );
				break;

			case 2: // enable and editable + en_check enable
				EnableSizerChilds( namePosSizer, true );
				break;

			default: // all disable
				EnableSizerChilds( namePosSizer, false );
				break;
			}
		}
	}
	else
	{
		nameValueText->ChangeValue( wxT("") );
		positionValuePP->SetLabel( wxT("") );
		EnableSizerChilds( namePosSizer, false );
	}
}

//----------------------------------------------------------------------------------
// UpdateThreshold
//   mode: 1 - enable and editable + thr on
//         2 - enable but not editable + thr off
//         3 - disable + thr on
//         other - all disable
//----------------------------------------------------------------------------------
void wxInspectionPanel::UpdateThreshold( char mode )
{
	if( DB->SiteCount() )
	{
		thresholdValuePP->SetLabel( wxString::Format( "%d", DB->pAUTOInspectionCurrentSiteStruct->BinarizationThr ) );

		switch( mode )
		{
		case 1: // enable and editable + thr on
			EnableSizerChilds( thrSizer, true );
			break;

		case 2: // enable but not editable + thr off
			EnableSizerChilds( thrSizer, true );
			thrMinusBtn->Enable( false );
			thrPlusBtn->Enable( false );
			thrGetBtn->Enable( false );
			break;

		case 3: // disable + thr on
			EnableSizerChilds( thrSizer, true );
			thresholdPP->Enable( false );
			thrMinusBtn->Enable( false );
			thresholdValuePP->Enable( false );
			thrPlusBtn->Enable( false );
			break;
		case 4:
			EnableSizerChilds( thrSizer, true );
			thresholdPP->Enable( true );
			thrMinusBtn->Enable( true );
			thresholdValuePP->Enable( true );
			thrPlusBtn->Enable( true );
			thrGetBtn->Enable(false);
			//thrGetBtn->Disable();
			break;

		default: // all disable
			EnableSizerChilds( thrSizer, false );
			break;
		}
	}
	else
	{
		thresholdValuePP->SetLabel( wxT("") );
		EnableSizerChilds( thrSizer, false );
	}
}

//----------------------------------------------------------------------------------
// UpdateAlarmAndWarning
//----------------------------------------------------------------------------------
void wxInspectionPanel::UpdateAlarmAndWarning( )
{
	if( DB->SiteCount() )
	{
		SpinAlarm->SetValue(DB->pAUTOInspectionCurrentSiteStruct->Alarm);
		SpinWarning->SetValue(DB->pAUTOInspectionCurrentSiteStruct->Warning);
	}
	else{
		SpinAlarm->SetValue(0);
		SpinWarning->SetValue(0);
	}
}



//----------------------------------------------------------------------------------
// UpdateAreas
//   mode: 1 - enable and editable
//         2 - enable but not editable
//         other - all disable
//----------------------------------------------------------------------------------
void wxInspectionPanel::UpdateAreas( char mode )
{
	vetoEvents = true;

	if( DB->SiteAreaCount() )
	{
		// setup notebook
		switch( mode )
		{
		case 1: // enable and editable
			//areasNotebook->SetWindowStyleFlag( wxAUI_NB_CLOSE_BUTTON | wxNO_BORDER );
			//areasNotebook->Enable( true );
			manageAreasFlag = true;
			break;

		case 2: // enable but not editable
			//areasNotebook->SetWindowStyleFlag( wxNO_BORDER );
			//areasNotebook->Enable( true );
			manageAreasFlag = false;
			break;

		default: // all disable
		//	areasNotebook->SetWindowStyleFlag( wxNO_BORDER );
			//areasNotebook->Enable( false );
			manageAreasFlag = false;
			break;
		}


		// add/remove pages
		int numPages = DB->SiteAreaCount();
		if( numPages < NUM_INSPECTION_AREAS && manageAreasFlag )
			numPages++; // add the "ADD" page

		if( /*areasNotebook->GetPageCount() <= numPages*/ false)
		{
			// add pages
			//for( int i = areasNotebook->GetPageCount(); i < numPages; i++ )
			//{
			//	wxAreaPanel* page = new wxAreaPanel( areasNotebook );
			//	areasNotebook->AddPage( page, wxT("") );
			//}
		}
		else
		{
			// remove pages
			//for( int i = areasNotebook->GetPageCount(); i > numPages; i-- )
			//{
			//	areasNotebook->DeletePage( areasNotebook->GetPageCount() - 1 );
			//}
		}

		// setup pages
		for( int i = 0; i < numPages; i++ )
		{
			//wxAreaPanel* page = (wxAreaPanel*)areasNotebook->GetPage( i );
			//page->SetSearchArea( &DB->InspectionAreasS[i].SearchArea );
			//page->SetAlarm( &DB->InspectionAreasS[i].Alarm );

			if( i+1 == numPages && numPages > DB->SiteAreaCount() && manageAreasFlag )
			{
				// this is the last page: "ADD" page
				//areasNotebook->SetPageText( DB->SiteAreaCount(), "+" );

				//if( areasNotebook->GetSelection() == i )
					//areasNotebook->SetSelection( i-1 );
			}
			else
				//areasNotebook->SetPageText( i, wxString::Format( _("Area %d"), i+1 ) );

			switch( mode )
			{
			case 1: // enable and editable
				//page->EnableAdjustButtons( true );
				break;

			case 2: // enable but not editable
				//page->EnableAdjustButtons( false );
				break;

			default: // all disable
				//page->EnableAdjustButtons( false );
				break;
			}
		}
	}
	else
	{
		//while( areasNotebook->GetPageCount() )
			//areasNotebook->DeletePage( 0 );

		//areasNotebook->Enable( false );
	}

	vetoEvents = false;

	//areasNotebook->Layout();
}

//----------------------------------------------------------------------------------
// UpdateTeach
//   mode: 1 - show teach (enable) + hide ok/cancel
//         2 - hide teach + show ok/cancel (enable)
//         3 - hide teach + show ok/cancel (disable)
//         other - show teach (disable) + hide ok/cancel
//----------------------------------------------------------------------------------
void wxInspectionPanel::UpdateTeach( char mode )
{
	switch( mode )
	{
	case 1: // show teach (enable) + hide ok/cancel
		teachBtn->Show( true );
		teachBtn->Enable( true );
		teachPanel->Show( false );
		break;

	case 2: // hide teach + show ok/cancel (enable)
		teachBtn->Show( false );
		teachPanel->Show( true );
		teachPanel->Enable( true );
		break;

	case 3: // hide teach + show ok/cancel (disable)
		teachBtn->Show( false );
		teachPanel->Show( true );
		teachPanel->Enable( false );
		break;

	default: // show teach (disable) + hide ok/cancel
		teachBtn->Show( true );
		teachBtn->Enable( false );
		teachPanel->Show( false );
		break;
	}

	teachSizer->Layout();
}

//----------------------------------------------------------------------------------
// OnGUIEvents
//----------------------------------------------------------------------------------
void wxInspectionPanel::OnGUIEvents( wxCommandEvent& event )
{
	// event fired by wxAreaPanel
	//------------------------------------------------------------------------------
	if( event.GetId() == wxAreaPanel::ID_EVENT )
	{
		if( event.GetInt() == wxAreaPanel::EVT_SEARCH_AREA )
			FireEvent( EVT_NEED_REFRESH_IMAGE );
		return;
	}

	event.Skip();
}



	//------------//
	//   Events   //
	//------------//

void wxInspectionPanel::OnaddSiteBtnClick(wxCommandEvent& event)
{
	if( DB->InsertInspectionSite() == SR_ERROR )
	{
		wxMessageBox( MSG_MAXSITEREACHED, MACHINE_NAME, wxOK | wxICON_INFORMATION, GetParent() );
		return;
	}
	DB->SiteLast();
	FireEvent( EVT_NEED_UPDATE );
}

void wxInspectionPanel::OnremoveSiteBtnClick(wxCommandEvent& event)
{
	if( DB->SiteCount() )
	{
		if( wxMessageBox( MSG_ASKREMOVESITE, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, GetParent() ) != wxYES )
			return;

		// remove images
		cout<<"verra rimosso un file: "<<FILE_PRODUCTION_FOLDER<<DB->ProductionDataS.ProductionName.ToAscii()<< FILE_SITE<< DB->ProductionDataS.ProductionName.ToAscii()<< DB->pAUTOInspectionCurrentSiteStruct->IdSite <<endl;
		cout<<"l'indice del sito e: "<<DB->SiteGetSelected()<<endl;
		ffRemoveFile( wxString::Format(FILE_PRODUCTION_FOLDER, DB->ProductionDataS.ProductionName.ToAscii() ), wxString::Format( FILE_SITE, DB->ProductionDataS.ProductionName.ToAscii(), DB->pAUTOInspectionCurrentSiteStruct->IdSite ).ToAscii() );
		ffRemoveFile( wxString::Format(FILE_PRODUCTION_FOLDER, DB->ProductionDataS.ProductionName.ToAscii() ), wxString::Format( FILE_SITEREF, DB->ProductionDataS.ProductionName.ToAscii(), DB->pAUTOInspectionCurrentSiteStruct->IdSite ).ToAscii() );
		// remove from DB
		DB->DeleteInspectionSite( DB->SiteGetSelected() );

		FireEvent( EVT_NEED_UPDATE );
	}
}

void wxInspectionPanel::OnteachBtnClick(wxCommandEvent& event)
{
	teachBtn->Enable( false );
	FireEvent( EVT_TEACH );
}

void wxInspectionPanel::OnokBtnClick(wxCommandEvent& event)
{
	FireEvent( EVT_OK );
}

void wxInspectionPanel::OncancelBtnClick(wxCommandEvent& event)
{
	FireEvent( EVT_CANCEL );
}

void wxInspectionPanel::OnnameValueTextText(wxCommandEvent& event)
{
	DB->pAUTOInspectionCurrentSiteStruct->Name = event.GetString();
}

void wxInspectionPanel::OnthrMinusBtnClick(wxCommandEvent& event)
{
	if(DB->pAUTOInspectionCurrentSiteStruct->BinarizationThr>1){
		DB->pAUTOInspectionCurrentSiteStruct->BinarizationThr--;
		FireEvent( EVT_THRESHOLD );
	}


}

void wxInspectionPanel::OnthrPlusBtnClick(wxCommandEvent& event)
{

	if(DB->pAUTOInspectionCurrentSiteStruct->BinarizationThr<255){
			DB->pAUTOInspectionCurrentSiteStruct->BinarizationThr++;
			FireEvent( EVT_THRESHOLD );
	}
}

void wxInspectionPanel::OnthrGetBtnClick(wxCommandEvent& event)
{
	FireEvent( EVT_SET_THRESHOLD );
}

void wxInspectionPanel::OninspectionTypeComboSelect(wxCommandEvent& event)
{
	TransferDataFromWindow();
	FireEvent( EVT_NEED_UPDATE );
}

void wxInspectionPanel::OnsitesCheckListSelect(wxCommandEvent& event)
{
	if( vetoEvents )
		return;

	TransferDataFromWindow();
	DB->SiteSelect( event.GetInt() );

	FireEvent( EVT_NEED_UPDATE );
}

void wxInspectionPanel::OnsitesCheckListToggled(wxCommandEvent& event)
{
	if( vetoEvents )
		return;

	DB->SiteSelect( event.GetInt() );
	DB->pAUTOInspectionCurrentSiteStruct->Enable = sitesCheckList->IsChecked( event.GetInt() ) ? 1 : 0;
	FireEvent( EVT_NEED_UPDATE );
}

/*void wxInspectionPanel::OnMoveLeftBtnClick (wxCommandEvent& event){

	for (int i=0; i <DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask.size(); i++){
	DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[i].x--;
		for (int j=0; j< DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i].size(); j++){

			DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i][j].x--;
		}
	}
	FireEvent( EVT_NEED_REFRESH_IMAGE );
}
void wxInspectionPanel::OnMoveRightBtnClick (wxCommandEvent& event){

	for (int i=0; i <DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask.size(); i++){
		DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[i].x++;
			for (int j=0; j< DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i].size(); j++){

				DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i][j].x++;
			}
		}

	FireEvent( EVT_NEED_REFRESH_IMAGE );

}
void wxInspectionPanel::OnMoveUpBtnClick (wxCommandEvent& event){

	for (int i=0; i <DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask.size(); i++){
		DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[i].y--;
			for (int j=0; j< DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i].size(); j++){

				DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i][j].y--;
			}
		}
	FireEvent( EVT_NEED_REFRESH_IMAGE );

}
void wxInspectionPanel::OnMoveDownBtnClick (wxCommandEvent& event){

	for (int i=0; i <DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask.size(); i++){
		DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[i].y++;
			for (int j=0; j< DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i].size(); j++){

				DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i][j].y++;
			}
		}

	FireEvent( EVT_NEED_REFRESH_IMAGE );
}*/

void wxInspectionPanel::OnReduceBtnClick (wxCommandEvent& event){
	DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor--;
	FireEvent( EVT_THRESHOLD );
}

void wxInspectionPanel::OnEnlargeBtnClick (wxCommandEvent& event){
	DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor++;
	FireEvent( EVT_THRESHOLD );
}


void wxInspectionPanel::OnMoveUpBtnClick(wxCommandEvent& event)
{
	for (int i=0; i <DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask.size(); i++){
			DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[i].y--;
				for (int j=0; j< DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i].size(); j++){

					DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i][j].y--;
				}
			}
		FireEvent( EVT_NEED_REFRESH_IMAGE );
}

void wxInspectionPanel::OnMoveDownBtnClick(wxCommandEvent& event)
{
	for (int i=0; i <DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask.size(); i++){
			DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[i].y++;
				for (int j=0; j< DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i].size(); j++){

					DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i][j].y++;
				}
			}

		FireEvent( EVT_NEED_REFRESH_IMAGE );
}

void wxInspectionPanel::OnMoveLeftBtnClick(wxCommandEvent& event)
{

	for (int i=0; i <DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask.size(); i++){
	DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[i].x--;
		for (int j=0; j< DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i].size(); j++){

			DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i][j].x--;
		}
	}
	FireEvent( EVT_NEED_REFRESH_IMAGE );
}

void wxInspectionPanel::OnMoveRightBtnClick(wxCommandEvent& event)
{
	for (int i=0; i <DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask.size(); i++){
			DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[i].x++;
				for (int j=0; j< DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i].size(); j++){

					DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i][j].x++;
				}
			}

		FireEvent( EVT_NEED_REFRESH_IMAGE );
}

//void wxInspectionPanel::OnEnlargeBtnClick(wxCommandEvent& event)
//{
//}

//void wxInspectionPanel::OnReduceBtnClick(wxCommandEvent& event)
//{
//}

void wxInspectionPanel::OnSpinAlarmChange(wxSpinEvent& event)
{
	DB->pAUTOInspectionCurrentSiteStruct->Alarm = SpinAlarm->GetValue();
}

void wxInspectionPanel::OnSpinWarningChange(wxSpinEvent& event)
{
	DB->pAUTOInspectionCurrentSiteStruct->Warning = SpinWarning->GetValue();
}

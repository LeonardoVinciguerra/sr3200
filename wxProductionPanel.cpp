#include "images/png_images.h"

#include "wxProductionPanel.h"

//(*InternalHeaders(wxProductionPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "wxMyTextValidator.h"
#include "wxMyComboValidator.h"
#include "Messages.h"
#include "GlobalUtils.h"
#include "wxPinsDialog.h"
#include "wxWaitDialog.h"

//added from 3100, simplify columns orders
enum ResultsGridColLabels
{
	COL_AREA,
	COL_RESULT,
	COL_SHORT
};

#define PP_FG_DIS_COLOR			wxColor( 176, 176, 176 ) // GRAY
#define FID_SEARCH_DISABLE		wxColor( 255, 0, 0 ) // RED
#define SPI_HIGH_BG_COLOR		wxColor( 120, 200, 15 ) // GREEN
#define SPI_LOW_BG_COLOR		wxColor( 255, 0, 0 ) // RED

//aggiunto dalla 3100, chiama il refreshquando si cambia sito
const int wxProductionPanel::EVT_NEED_UPDATE = 8;

const int wxProductionPanel::EVT_GRID_SELECTED = 10;

const long wxProductionPanel::ID_SQUEEGEES_BUTTON = wxNewId();

const long wxProductionPanel::ID_EVENT = wxNewId();

const long wxProductionPanel::EVT_PARAMETERS_CHANGED =  wxNewId();
const long wxProductionPanel::EVT_ACCEPT_CHANGES =  wxNewId();
const long wxProductionPanel::EVT_REQUEST_NEW_THRESHOLDS =  wxNewId();

//(*IdInit(wxProductionPanel)
const long wxProductionPanel::ID_CHECKBOX1 = wxNewId();
const long wxProductionPanel::ID_BITMAPBUTTON2 = wxNewId();
const long wxProductionPanel::ID_BITMAPBUTTON4 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT3 = wxNewId();
const long wxProductionPanel::ID_COMBOBOX1 = wxNewId();
const long wxProductionPanel::ID_SLIDER1 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT1 = wxNewId();
const long wxProductionPanel::ID_SLIDER5 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT7 = wxNewId();
const long wxProductionPanel::ID_SLIDER6 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT6 = wxNewId();
const long wxProductionPanel::ID_SLIDER2 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT2 = wxNewId();
const long wxProductionPanel::ID_SLIDER9 = wxNewId();
const long wxProductionPanel::ID_SLIDER7 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT10 = wxNewId();
const long wxProductionPanel::ID_SliderHUE = wxNewId();
const long wxProductionPanel::ID_STATICTEXT4 = wxNewId();
const long wxProductionPanel::ID_SliderPasteThr = wxNewId();
const long wxProductionPanel::ID_STATICTEXT5 = wxNewId();
const long wxProductionPanel::ID_RADIOBUTTON3 = wxNewId();
const long wxProductionPanel::ID_RADIOBUTTON4 = wxNewId();
const long wxProductionPanel::ID_BITMAPBUTTON3 = wxNewId();
const long wxProductionPanel::ID_BITMAPBUTTON1 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT17 = wxNewId();
const long wxProductionPanel::ID_TEXTCTRL4 = wxNewId();
const long wxProductionPanel::ID_BITMAPBUTTON5 = wxNewId();
const long wxProductionPanel::ID_BITMAPBUTTON6 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT8 = wxNewId();
const long wxProductionPanel::ID_TEXTCTRL1 = wxNewId();
const long wxProductionPanel::ID_BITMAPBUTTON7 = wxNewId();
const long wxProductionPanel::ID_PANEL2 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT39 = wxNewId();
const long wxProductionPanel::ID_TEXTCTRL23 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT11 = wxNewId();
const long wxProductionPanel::ID_TEXTCTRL2 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT12 = wxNewId();
const long wxProductionPanel::ID_TEXTCTRL3 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT18 = wxNewId();
const long wxProductionPanel::ID_TEXTCTRL5 = wxNewId();
const long wxProductionPanel::ID_CHECKBOX2 = wxNewId();
const long wxProductionPanel::ID_CUSTOM1 = wxNewId();
const long wxProductionPanel::ID_SLIDER8 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT9 = wxNewId();
const long wxProductionPanel::ID_PANEL1 = wxNewId();
const long wxProductionPanel::ID_RadioBoxBestChannel = wxNewId();
const long wxProductionPanel::ID_BITMAPBUTTON12 = wxNewId();
const long wxProductionPanel::ID_BITMAPBUTTON13 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT16 = wxNewId();
const long wxProductionPanel::ID_SLIDER15 = wxNewId();
const long wxProductionPanel::ID_BITMAPBUTTON11 = wxNewId();
const long wxProductionPanel::ID_BITMAPBUTTON10 = wxNewId();
const long wxProductionPanel::ID_RADIOBUTTON1 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT13 = wxNewId();
const long wxProductionPanel::ID_RADIOBOX1 = wxNewId();
const long wxProductionPanel::ID_SPINCTRL1 = wxNewId();
const long wxProductionPanel::ID_RADIOBUTTON2 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT14 = wxNewId();
const long wxProductionPanel::ID_SPINCTRL2 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT15 = wxNewId();
const long wxProductionPanel::ID_SPINCTRL3 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT19 = wxNewId();
const long wxProductionPanel::ID_CHECKLISTBOX2 = wxNewId();
const long wxProductionPanel::ID_STATICLINE1 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT23 = wxNewId();
const long wxProductionPanel::ID_TEXTCTRL6 = wxNewId();
const long wxProductionPanel::ID_STATICTEXT24 = wxNewId();
const long wxProductionPanel::ID_CUSTOM2 = wxNewId();
const long wxProductionPanel::ID_GRID2 = wxNewId();
const long wxProductionPanel::RequestSpiChangeBtn = wxNewId();
const long wxProductionPanel::ID_PANEL5 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxProductionPanel,wxPanel)
	//(*EventTable(wxProductionPanel)
	//*)
END_EVENT_TABLE()

wxProductionPanel::wxProductionPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxProductionPanel)
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer6;
	wxBoxSizer* BoxSizer29;
	wxBoxSizer* BoxSizer19;
	wxBoxSizer* BoxSizer15;
	wxBoxSizer* BoxSizer20;
	wxStaticBoxSizer* wxSizerFiducial;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer10;
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* BoxSizer8;
	wxBoxSizer* BoxSizer21;
	wxBoxSizer* BoxSizer23;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer11;
	wxBoxSizer* BoxSizer16;
	wxBoxSizer* BoxSizer18;
	wxBoxSizer* BoxSizer12;
	wxBoxSizer* BoxSizer27;
	wxStaticBoxSizer* wxSizerVision;
	wxBoxSizer* BoxSizer17;
	wxBoxSizer* BoxSizer24;
	wxBoxSizer* BoxSizer26;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer9;
	wxBoxSizer* BoxSizer22;
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* BoxSizer25;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	SetMaxSize(wxSize(-1,290));
	mainSizer = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer4->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer10 = new wxBoxSizer(wxVERTICAL);
	manualCheck = new wxCheckBox(this, ID_CHECKBOX1, _("Manual teach"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, wxDefaultValidator, _T("ID_CHECKBOX1"));
	manualCheck->SetValue(false);
	BoxSizer10->Add(manualCheck, 0, wxTOP|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	fiducialBtn = new wxBitmapButton(this, ID_BITMAPBUTTON2, wxNullBitmap, wxDefaultPosition, wxSize(74,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
	fiducialBtn->SetDefault();
	BoxSizer10->Add(fiducialBtn, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	gerberBtn = new wxBitmapButton(this, ID_BITMAPBUTTON4, wxNullBitmap, wxDefaultPosition, wxSize(110,95), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON4"));
	gerberBtn->SetDefault();
	BoxSizer10->Add(gerberBtn, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4->Add(BoxSizer10, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(BoxSizer4, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	mainSizer->Add(BoxSizer2, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerAlignment = new wxBoxSizer(wxHORIZONTAL);
	wxSizerFiducial = new wxStaticBoxSizer(wxVERTICAL, this, _("Fiducial Params"));
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Shape"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT3"));
	BoxSizer3->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	shapeCombo = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxSize(90,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX1"));
	shapeCombo->SetSelection( shapeCombo->Append(_("CIRCLE")) );
	shapeCombo->Append(_("RECTANGLE"));
	BoxSizer3->Add(shapeCombo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerFiducial->Add(BoxSizer3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	diameterSlider = new wxSlider(this, ID_SLIDER1, 0, 4, 120, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SLIDER1"));
	wxSizerFiducial->Add(diameterSlider, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	diameterLabel = new wxStaticText(this, ID_STATICTEXT1, _("Diameter %0.2f (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxSizerFiducial->Add(diameterLabel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 20);
	sideXSlider = new wxSlider(this, ID_SLIDER5, 0, 4, 120, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SLIDER5"));
	wxSizerFiducial->Add(sideXSlider, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	sideXLabel = new wxStaticText(this, ID_STATICTEXT7, _("Side X %0.2f (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	wxSizerFiducial->Add(sideXLabel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 20);
	sideYSlider = new wxSlider(this, ID_SLIDER6, 0, 4, 120, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SLIDER6"));
	wxSizerFiducial->Add(sideYSlider, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	sideYLabel = new wxStaticText(this, ID_STATICTEXT6, _("Side Y %0.2f (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	wxSizerFiducial->Add(sideYLabel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 20);
	toleranceSlider = new wxSlider(this, ID_SLIDER2, 0, 1, 6, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SLIDER2"));
	wxSizerFiducial->Add(toleranceSlider, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	toleranceLabel = new wxStaticText(this, ID_STATICTEXT2, _("Tolerance %0.2f (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	wxSizerFiducial->Add(toleranceLabel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	rAccumVisionSlider = new wxSlider(this, ID_SLIDER9, 0, 10, 40, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SLIDER9"));
	wxSizerFiducial->Add(rAccumVisionSlider, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cAccumVisionSlider = new wxSlider(this, ID_SLIDER7, 0, 10, 40, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SLIDER7"));
	wxSizerFiducial->Add(cAccumVisionSlider, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	accumLabel = new wxStaticText(this, ID_STATICTEXT10, _("Accumulator"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	wxSizerFiducial->Add(accumLabel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerAlignment->Add(wxSizerFiducial, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	BoxSizer5 = new wxBoxSizer(wxVERTICAL);
	wxSizerVision = new wxStaticBoxSizer(wxVERTICAL, this, _("Vision Processing Params"));
	filterSlider = new wxSlider(this, ID_SliderHUE, 0, 3, 15, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SliderHUE"));
	wxSizerVision->Add(filterSlider, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	filterLabel = new wxStaticText(this, ID_STATICTEXT4, _("Filter"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	wxSizerVision->Add(filterLabel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	houghThrSlider = new wxSlider(this, ID_SliderPasteThr, 0, 10, 60, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SliderPasteThr"));
	wxSizerVision->Add(houghThrSlider, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	thresholdLabel = new wxStaticText(this, ID_STATICTEXT5, _("Threshold"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	wxSizerVision->Add(thresholdLabel, 0, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer5->Add(wxSizerVision, 0, wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerAlignment->Add(BoxSizer5, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	mainSizer->Add(wxSizerAlignment, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerPrinting = new wxBoxSizer(wxHORIZONTAL);
	wxSizerMoveSqueegees = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Squeegees"));
	BoxSizer8 = new wxBoxSizer(wxVERTICAL);
	squeegees1Radio = new wxRadioButton(this, ID_RADIOBUTTON3, _("Front side"), wxDefaultPosition, wxSize(140,17), wxRB_GROUP, wxDefaultValidator, _T("ID_RADIOBUTTON3"));
	squeegees1Radio->SetValue(true);
	BoxSizer8->Add(squeegees1Radio, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	squeegees2Radio = new wxRadioButton(this, ID_RADIOBUTTON4, _("Back side"), wxDefaultPosition, wxSize(140,17), 0, wxDefaultValidator, _T("ID_RADIOBUTTON4"));
	BoxSizer8->Add(squeegees2Radio, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerMoveSqueegees->Add(BoxSizer8, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerMoveSqueegees->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	squeegeesMoveBtn = new wxBitmapButton(this, ID_BITMAPBUTTON3, wxNullBitmap, wxDefaultPosition, wxSize(34,34), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
	squeegeesMoveBtn->SetDefault();
	wxSizerMoveSqueegees->Add(squeegeesMoveBtn, 0, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	wxSizerPrinting->Add(wxSizerMoveSqueegees, 1, wxLEFT|wxRIGHT|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	BoxSizer9 = new wxBoxSizer(wxVERTICAL);
	BoxSizer9->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	immediateStopBtn = new wxBitmapButton(this, ID_BITMAPBUTTON1, wxNullBitmap, wxDefaultPosition, wxSize(70,70), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	immediateStopBtn->SetDefault();
	BoxSizer9->Add(immediateStopBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	sizerConditioningNum = new wxBoxSizer(wxHORIZONTAL);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT17, _("Iterations"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	sizerConditioningNum->Add(StaticText11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CondIterNumber = new wxTextCtrl(this, ID_TEXTCTRL4, _("3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	sizerConditioningNum->Add(CondIterNumber, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer9->Add(sizerConditioningNum, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	wxSizerPrinting->Add(BoxSizer9, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	mainSizer->Add(wxSizerPrinting, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerRackMove = new wxBoxSizer(wxVERTICAL);
	Panel1 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	Panel1->SetForegroundColour(wxColour(96,96,96));
	Panel1->SetBackgroundColour(wxColour(192,192,192));
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer7->Add(-1,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	rackUpBtn = new wxBitmapButton(Panel1, ID_BITMAPBUTTON5, wxNullBitmap, wxDefaultPosition, wxSize(100,100), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON5"));
	rackUpBtn->SetDefault();
	BoxSizer7->Add(rackUpBtn, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	BoxSizer6 = new wxBoxSizer(wxVERTICAL);
	rackPosBtn = new wxBitmapButton(Panel1, ID_BITMAPBUTTON6, wxNullBitmap, wxDefaultPosition, wxSize(100,100), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON6"));
	rackPosBtn->SetDefault();
	BoxSizer6->Add(rackPosBtn, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT8, _("Rack Pos:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	BoxSizer13->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	rackPosEdit = new wxTextCtrl(Panel1, ID_TEXTCTRL1, _("1"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer13->Add(rackPosEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer6->Add(BoxSizer13, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer7->Add(BoxSizer6, 1, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	rackDnBtn = new wxBitmapButton(Panel1, ID_BITMAPBUTTON7, wxNullBitmap, wxDefaultPosition, wxSize(100,100), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON7"));
	rackDnBtn->SetDefault();
	BoxSizer7->Add(rackDnBtn, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	BoxSizer7->Add(-1,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel1->SetSizer(BoxSizer7);
	BoxSizer7->Fit(Panel1);
	BoxSizer7->SetSizeHints(Panel1);
	wxSizerRackMove->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer29 = new wxBoxSizer(wxHORIZONTAL);
	StaticText32 = new wxStaticText(this, ID_STATICTEXT39, _("Boards to produce:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT39"));
	BoxSizer29->Add(StaticText32, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	loaderBoardNumberEdit = new wxTextCtrl(this, ID_TEXTCTRL23, wxEmptyString, wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL23"));
	BoxSizer29->Add(loaderBoardNumberEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer14->Add(BoxSizer29, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer15 = new wxBoxSizer(wxHORIZONTAL);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT11, _("Last printed rack pos:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	BoxSizer15->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lastRackPosEdit = new wxTextCtrl(this, ID_TEXTCTRL2, _("1"), wxDefaultPosition, wxSize(40,-1), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer15->Add(lastRackPosEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer14->Add(BoxSizer15, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerRackMove->Add(BoxSizer14, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	mainSizer->Add(wxSizerRackMove, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer16 = new wxBoxSizer(wxHORIZONTAL);
	wxSizerVerifyEvery = new wxBoxSizer(wxHORIZONTAL);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT12, _("Verify every:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	wxSizerVerifyEvery->Add(StaticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	verifyEveryEdit = new wxTextCtrl(this, ID_TEXTCTRL3, _("1"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	wxSizerVerifyEvery->Add(verifyEveryEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer16->Add(wxSizerVerifyEvery, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizerCleanEvery = new wxBoxSizer(wxHORIZONTAL);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT18, _("Clean every:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
	BoxSizerCleanEvery->Add(StaticText9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cleanEveryEdit = new wxTextCtrl(this, ID_TEXTCTRL5, _("1"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	BoxSizerCleanEvery->Add(cleanEveryEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizerCleanEvery->Add(-1,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SuggestCorrectionCheckbox = new wxCheckBox(this, ID_CHECKBOX2, _("Suggest corrections"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	SuggestCorrectionCheckbox->SetValue(false);
	BoxSizerCleanEvery->Add(SuggestCorrectionCheckbox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer16->Add(BoxSizerCleanEvery, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	mainSizer->Add(BoxSizer16, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	templatePanel = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(-1,5), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	templateImage = new wxPictureBox(templatePanel,ID_CUSTOM1,wxDefaultPosition,wxSize(250,250));
	BoxSizer1->Add(templateImage, 0, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 20);
	BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer11->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer12 = new wxBoxSizer(wxVERTICAL);
	templateSlider = new wxSlider(templatePanel, ID_SLIDER8, 0, 1, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SLIDER8"));
	BoxSizer12->Add(templateSlider, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	templateLabel = new wxStaticText(templatePanel, ID_STATICTEXT9, _("Threshold"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	BoxSizer12->Add(templateLabel, 0, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer11->Add(BoxSizer12, 2, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer11->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer11, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	templatePanel->SetSizer(BoxSizer1);
	BoxSizer1->SetSizeHints(templatePanel);
	mainSizer->Add(templatePanel, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizerPhase1Settings = new wxBoxSizer(wxVERTICAL);
	BoxSizer22 = new wxBoxSizer(wxHORIZONTAL);
	wxString __wxRadioBoxChoices_1[4] =
	{
		_("Red"),
		_("Green"),
		_(" Blue"),
		_("Composite")
	};
	RadioBoxBestChannel = new wxRadioBox(this, ID_RadioBoxBestChannel, _("Channel"), wxDefaultPosition, wxDefaultSize, 4, __wxRadioBoxChoices_1, 1, 0, wxDefaultValidator, _T("ID_RadioBoxBestChannel"));
	BoxSizer22->Add(RadioBoxBestChannel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer24 = new wxBoxSizer(wxVERTICAL);
	AcceptChangesPhase1 = new wxBitmapButton(this, ID_BITMAPBUTTON12, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON12"));
	BoxSizer24->Add(AcceptChangesPhase1, 1, wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	CancelChangesPhase1 = new wxBitmapButton(this, ID_BITMAPBUTTON13, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON13"));
	BoxSizer24->Add(CancelChangesPhase1, 1, wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer22->Add(BoxSizer24, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizerPhase1Settings->Add(BoxSizer22, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer25 = new wxBoxSizer(wxHORIZONTAL);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT16, _("Paste Threshold"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	BoxSizer25->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SliderPasteThr = new wxSlider(this, ID_SLIDER15, 180, 0, 255, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER15"));
	BoxSizer25->Add(SliderPasteThr, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizerPhase1Settings->Add(BoxSizer25, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	mainSizer->Add(BoxSizerPhase1Settings, 1, wxALL|wxEXPAND|wxFIXED_MINSIZE|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizerPhase2Settings = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer23 = new wxBoxSizer(wxVERTICAL);
	CancelChangesPhase2 = new wxBitmapButton(this, ID_BITMAPBUTTON11, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON11"));
	BoxSizer23->Add(CancelChangesPhase2, 1, wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	AcceptChangesPhase2 = new wxBitmapButton(this, ID_BITMAPBUTTON10, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON10"));
	BoxSizer23->Add(AcceptChangesPhase2, 1, wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizerPhase2Settings->Add(BoxSizer23, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer18 = new wxBoxSizer(wxVERTICAL);
	BoxSizer26 = new wxBoxSizer(wxHORIZONTAL);
	ColorPadCriteria = new wxRadioButton(this, ID_RADIOBUTTON1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
	BoxSizer26->Add(ColorPadCriteria, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT13, _("Color:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	BoxSizer26->Add(StaticText5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_2[3] =
	{
		_("Red"),
		_("Green"),
		_("Blue")
	};
	ChannelRadioBox = new wxRadioBox(this, ID_RADIOBOX1, _("Channel"), wxDefaultPosition, wxDefaultSize, 3, __wxRadioBoxChoices_2, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX1"));
	BoxSizer26->Add(ChannelRadioBox, 1, wxALL|wxSHAPED|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ColorPadsWidthSpin = new wxSpinCtrl(this, ID_SPINCTRL1, _T("15"), wxDefaultPosition, wxDefaultSize, 0, 0, 40, 15, _T("ID_SPINCTRL1"));
	ColorPadsWidthSpin->SetValue(_T("15"));
	BoxSizer26->Add(ColorPadsWidthSpin, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer18->Add(BoxSizer26, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer27 = new wxBoxSizer(wxHORIZONTAL);
	HuePadCriteria = new wxRadioButton(this, ID_RADIOBUTTON2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
	BoxSizer27->Add(HuePadCriteria, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT14, _("Hue center:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	BoxSizer27->Add(StaticText6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	HueCenterSpin = new wxSpinCtrl(this, ID_SPINCTRL2, _T("50"), wxDefaultPosition, wxDefaultSize, 0, 0, 230, 50, _T("ID_SPINCTRL2"));
	HueCenterSpin->SetValue(_T("50"));
	BoxSizer27->Add(HueCenterSpin, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT15, _("Hue width:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	BoxSizer27->Add(StaticText7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	HueWidthSpin = new wxSpinCtrl(this, ID_SPINCTRL3, _T("15"), wxDefaultPosition, wxDefaultSize, 0, 0, 40, 15, _T("ID_SPINCTRL3"));
	HueWidthSpin->SetValue(_T("15"));
	BoxSizer27->Add(HueWidthSpin, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer18->Add(BoxSizer27, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizerPhase2Settings->Add(BoxSizer18, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	mainSizer->Add(BoxSizerPhase2Settings, 0, wxALL|wxEXPAND|wxFIXED_MINSIZE|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizerInspection = new wxBoxSizer(wxVERTICAL);
	sitesPanel = new wxPanel(this, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
	sitesPanel->SetBackgroundColour(wxColour(192,192,192));
	BoxSizer17 = new wxBoxSizer(wxVERTICAL);
	BoxSizer19 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer20 = new wxBoxSizer(wxVERTICAL);
	StaticText10 = new wxStaticText(sitesPanel, ID_STATICTEXT19, _("Inspection points"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
	BoxSizer20->Add(StaticText10, 0, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	sitesCheckList = new wxCheckListBox(sitesPanel, ID_CHECKLISTBOX2, wxDefaultPosition, wxSize(130,150), 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX2"));
	BoxSizer20->Add(sitesCheckList, 1, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	BoxSizer19->Add(BoxSizer20, 0, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticLine1 = new wxStaticLine(sitesPanel, ID_STATICLINE1, wxDefaultPosition, wxSize(2,-1), wxLI_VERTICAL, _T("ID_STATICLINE1"));
	BoxSizer19->Add(StaticLine1, 0, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer21 = new wxBoxSizer(wxVERTICAL);
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 1, 5);
	StaticText14 = new wxStaticText(sitesPanel, ID_STATICTEXT23, _("Name"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
	FlexGridSizer1->Add(StaticText14, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	nameValueText = new wxTextCtrl(sitesPanel, ID_TEXTCTRL6, wxEmptyString, wxDefaultPosition, wxSize(140,-1), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL6"));
	FlexGridSizer1->Add(nameValueText, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText15 = new wxStaticText(sitesPanel, ID_STATICTEXT24, _("Position (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
	FlexGridSizer1->Add(StaticText15, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	positionValuePP = new wxPanelPlus(sitesPanel,ID_CUSTOM2,wxDefaultPosition,wxSize(140,21));
	FlexGridSizer1->Add(positionValuePP, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer21->Add(FlexGridSizer1, 0, wxBOTTOM|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	resultsGrid = new wxGrid(sitesPanel, ID_GRID2, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, _T("ID_GRID2"));
	resultsGrid->CreateGrid(1,3);
	resultsGrid->SetRowLabelSize( 0 );
	resultsGrid->EnableEditing(true);
	resultsGrid->EnableGridLines(true);
	resultsGrid->SetColLabelSize(21);
	resultsGrid->SetColLabelValue(0, _("Area"));
	resultsGrid->SetColLabelValue(1, _("Result"));
	resultsGrid->SetColLabelValue(2, _("Short"));
	resultsGrid->SetDefaultCellFont( resultsGrid->GetFont() );
	resultsGrid->SetDefaultCellTextColour( resultsGrid->GetForegroundColour() );
	BoxSizer21->Add(resultsGrid, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer19->Add(BoxSizer21, 9, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ModifySpiParam = new wxBitmapButton(sitesPanel, RequestSpiChangeBtn, wxNullBitmap, wxDefaultPosition, wxSize(30,30), wxBU_AUTODRAW, wxDefaultValidator, _T("RequestSpiChangeBtn"));
	ModifySpiParam->SetToolTip(_("Change prameters"));
	BoxSizer19->Add(ModifySpiParam, 1, wxALL|wxALIGN_LEFT|wxALIGN_BOTTOM, 0);
	BoxSizer17->Add(BoxSizer19, 5, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	sitesPanel->SetSizer(BoxSizer17);
	BoxSizer17->Fit(sitesPanel);
	BoxSizer17->SetSizeHints(sitesPanel);
	BoxSizerInspection->Add(sitesPanel, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	mainSizer->Add(BoxSizerInspection, 2, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	SetSizer(mainSizer);
	mainSizer->Fit(this);
	mainSizer->SetSizeHints(this);

	Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionPanel::OnfiducialBtnClick);
	Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionPanel::OngerberBtnClick);
	Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&wxProductionPanel::OnshapeComboSelect);
	Connect(ID_SLIDER1,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxProductionPanel::OnradiusSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxProductionPanel::OnradiusSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxProductionPanel::OnradiusSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxProductionPanel::OnradiusSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxProductionPanel::OnradiusSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxProductionPanel::OnradiusSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxProductionPanel::OnradiusSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxProductionPanel::OnradiusSliderCmdScroll);
	Connect(ID_SLIDER5,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxProductionPanel::OnsideXSliderCmdScroll);
	Connect(ID_SLIDER5,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxProductionPanel::OnsideXSliderCmdScroll);
	Connect(ID_SLIDER5,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxProductionPanel::OnsideXSliderCmdScroll);
	Connect(ID_SLIDER5,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxProductionPanel::OnsideXSliderCmdScroll);
	Connect(ID_SLIDER5,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxProductionPanel::OnsideXSliderCmdScroll);
	Connect(ID_SLIDER5,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxProductionPanel::OnsideXSliderCmdScroll);
	Connect(ID_SLIDER5,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxProductionPanel::OnsideXSliderCmdScroll);
	Connect(ID_SLIDER5,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxProductionPanel::OnsideXSliderCmdScroll);
	Connect(ID_SLIDER6,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxProductionPanel::OnsideYSliderCmdScroll);
	Connect(ID_SLIDER6,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxProductionPanel::OnsideYSliderCmdScroll);
	Connect(ID_SLIDER6,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxProductionPanel::OnsideYSliderCmdScroll);
	Connect(ID_SLIDER6,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxProductionPanel::OnsideYSliderCmdScroll);
	Connect(ID_SLIDER6,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxProductionPanel::OnsideYSliderCmdScroll);
	Connect(ID_SLIDER6,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxProductionPanel::OnsideYSliderCmdScroll);
	Connect(ID_SLIDER6,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxProductionPanel::OnsideYSliderCmdScroll);
	Connect(ID_SLIDER6,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxProductionPanel::OnsideYSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxProductionPanel::OntoleranceSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxProductionPanel::OntoleranceSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxProductionPanel::OntoleranceSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxProductionPanel::OntoleranceSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxProductionPanel::OntoleranceSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxProductionPanel::OntoleranceSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxProductionPanel::OntoleranceSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxProductionPanel::OntoleranceSliderCmdScroll);
	Connect(ID_SLIDER9,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&wxProductionPanel::OnrAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER9,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxProductionPanel::OnrAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER9,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxProductionPanel::OnrAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER9,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxProductionPanel::OnrAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER9,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxProductionPanel::OnrAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER9,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxProductionPanel::OnrAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER9,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxProductionPanel::OnrAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER9,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxProductionPanel::OnrAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER9,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxProductionPanel::OnrAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&wxProductionPanel::OncAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxProductionPanel::OncAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxProductionPanel::OncAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxProductionPanel::OncAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxProductionPanel::OncAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxProductionPanel::OncAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxProductionPanel::OncAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxProductionPanel::OncAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxProductionPanel::OncAccumVisionSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxProductionPanel::OnfilterSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxProductionPanel::OnfilterSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxProductionPanel::OnfilterSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxProductionPanel::OnfilterSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxProductionPanel::OnfilterSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxProductionPanel::OnfilterSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxProductionPanel::OnfilterSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxProductionPanel::OnfilterSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxProductionPanel::OnhoughThrSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxProductionPanel::OnhoughThrSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxProductionPanel::OnhoughThrSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxProductionPanel::OnhoughThrSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxProductionPanel::OnhoughThrSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxProductionPanel::OnhoughThrSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxProductionPanel::OnhoughThrSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxProductionPanel::OnhoughThrSliderCmdScroll);
	Connect(ID_BITMAPBUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionPanel::OnsqueegeesMoveBtnClick);
	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionPanel::OnimmediateStopBtnClick);
	Connect(ID_BITMAPBUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionPanel::OnrackUpBtnClick);
	Connect(ID_BITMAPBUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionPanel::OnrackPosBtnClick);
	Connect(ID_BITMAPBUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionPanel::OnrackDnBtnClick);
	Connect(ID_SLIDER8,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxProductionPanel::OntemplateSliderCmdScroll);
	Connect(ID_SLIDER8,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxProductionPanel::OntemplateSliderCmdScroll);
	Connect(ID_SLIDER8,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxProductionPanel::OntemplateSliderCmdScroll);
	Connect(ID_SLIDER8,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxProductionPanel::OntemplateSliderCmdScroll);
	Connect(ID_SLIDER8,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxProductionPanel::OntemplateSliderCmdScroll);
	Connect(ID_SLIDER8,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxProductionPanel::OntemplateSliderCmdScroll);
	Connect(ID_SLIDER8,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxProductionPanel::OntemplateSliderCmdScroll);
	Connect(ID_SLIDER8,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxProductionPanel::OntemplateSliderCmdScroll);
	Connect(ID_RadioBoxBestChannel,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&wxProductionPanel::OnChannelChanged);
	Connect(ID_BITMAPBUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionPanel::OnAcceptChangesClick);
	Connect(ID_BITMAPBUTTON13,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionPanel::OnCancelChangesClick);
	Connect(ID_SLIDER15,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&wxProductionPanel::OnPadThrSliderCmdScroll);
	Connect(ID_SLIDER15,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxProductionPanel::OnPadThrSliderCmdScroll);
	Connect(ID_SLIDER15,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxProductionPanel::OnPadThrSliderCmdScroll);
	Connect(ID_SLIDER15,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxProductionPanel::OnPadThrSliderCmdScroll);
	Connect(ID_SLIDER15,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxProductionPanel::OnPadThrSliderCmdScroll);
	Connect(ID_SLIDER15,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxProductionPanel::OnPadThrSliderCmdScroll);
	Connect(ID_SLIDER15,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxProductionPanel::OnPadThrSliderCmdScroll);
	Connect(ID_SLIDER15,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxProductionPanel::OnPadThrSliderCmdScroll);
	Connect(ID_SLIDER15,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxProductionPanel::OnPadThrSliderCmdScroll);
	Connect(ID_BITMAPBUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionPanel::onCancelChangesPhase2);
	Connect(ID_BITMAPBUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionPanel::OnAcceptChangesClick);
	Connect(ID_RADIOBUTTON1,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&wxProductionPanel::OnColorPadCriteriaSelect);
	Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&wxProductionPanel::OnChannelRadioBoxSelect);
	Connect(ID_RADIOBUTTON2,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&wxProductionPanel::OnHuePadCriteriaSelect);
	Connect(ID_SPINCTRL2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&wxProductionPanel::OnHueCenterSpinChange);
	Connect(ID_SPINCTRL3,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&wxProductionPanel::OnHueWidthSpinChange);
	Connect(ID_CHECKLISTBOX2,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&wxProductionPanel::OnsitesCheckListSelect);
	Connect(ID_GRID2,wxEVT_GRID_CELL_LEFT_CLICK,(wxObjectEventFunction)&wxProductionPanel::OnGridElementSelected);
	Connect(RequestSpiChangeBtn,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProductionPanel::OnModifySpiParamClick);
	//*)


	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxProductionPanel::OnSuggestCorrectionCheckboxClick);

	// init buttons image
	immediateStopBtn->SetBitmapLabel( wxMEMORY_BITMAP( stop_hand ) );
	fiducialBtn->SetBitmapDisabled( wxMEMORY_BITMAP( fiducial ) );
	fiducialBtn->SetBitmapLabel( wxMEMORY_BITMAP( fiducial_on ) );
	squeegeesMoveBtn->SetBitmapDisabled( wxMEMORY_BITMAP( play_small ) );
	squeegeesMoveBtn->SetBitmapLabel( wxMEMORY_BITMAP( play_small_on ) );
	gerberBtn->SetBitmapLabel( wxMEMORY_BITMAP( gerber ) );
	rackUpBtn->SetBitmapLabel( wxMEMORY_BITMAP( rack_up ) );
	rackDnBtn->SetBitmapLabel( wxMEMORY_BITMAP( rack_dn ) );
	rackPosBtn->SetBitmapLabel( wxMEMORY_BITMAP( rack_updn ) );

	AcceptChangesPhase1->SetBitmapLabel( wxMEMORY_BITMAP( ok_small_on ) );
	AcceptChangesPhase2->SetBitmapLabel( wxMEMORY_BITMAP( ok_small_on ) );
	CancelChangesPhase1->SetBitmapLabel( wxMEMORY_BITMAP( cancel_small_on ));
	CancelChangesPhase2->SetBitmapLabel( wxMEMORY_BITMAP( cancel_small_on ));
	ModifySpiParam-> SetBitmapLabel( wxMEMORY_BITMAP( teach_small_on ) );
	// init buttons tooltip
	fiducialBtn->SetToolTip( TOO_FIDUCIALMODIFY );
	gerberBtn->SetToolTip( TOO_PINSSELECT );
	rackUpBtn->SetToolTip( TOO_RACKMOVEUP );
	rackDnBtn->SetToolTip( TOO_RACKMOVEDN );
	rackPosBtn->SetToolTip( TOO_RACKMOVEPOS );



	// hide template panel
	ShowTemplatePanel( false );

	smartLogger = NULL;

	mainSizer->Fit( this );
	mainSizer->SetSizeHints( this );
}

wxProductionPanel::~wxProductionPanel()
{
	//(*Destroy(wxProductionPanel)
	//*)
	/*
	BoxSizer1->SetSizeHints(templatePanel);
		//SetSizer(BoxSizer1);
		//Layout(); */     //da sostituire!
}

//----------------------------------------------------------------------------------
// Init
// Inizializza il controllo
//----------------------------------------------------------------------------------
int wxProductionPanel::Init( SRMachine* SRRef, SmartLog* smartLoggerRef )
{
	SR = SRRef;
	smartLogger = smartLoggerRef;

	isFiducialBtnOn = false;
	isBusy = false;

	diameterSlider->SetMin( CIRCLE_DIAMETER_MIN_MM * CIRCLE_SCALE );
	diameterSlider->SetMax( CIRCLE_DIAMETER_MAX_MM * CIRCLE_SCALE );
	sideXSlider->SetMin( RECT_X_MIN_MM * RECTANGLE_SCALE );
	sideXSlider->SetMax( RECT_X_MAX_MM * RECTANGLE_SCALE );
	sideYSlider->SetMin( RECT_Y_MIN_MM * RECTANGLE_SCALE );
	sideYSlider->SetMax( RECT_Y_MAX_MM * RECTANGLE_SCALE );
	toleranceSlider->SetMin( TOLERANCE_MIN_MM * TOLERANCE_SCALE );
	toleranceSlider->SetMax( TOLERANCE_MAX_MM * TOLERANCE_SCALE );
	//SuggestCorrectionCheckbox->SetValue(false);
	SR->suggestCorrections=false;

	//PasteThrSlider->SetMax(MAX_UINT_VALUE);
	//PadThrSlider->SetMax(MAX_UINT_VALUE);

	loaderBoardNumberEdit->SetValidator( wxMyTextValidator( &SR->DB->ProductionDataS.LoaderBoardNumber ) );
	verifyEveryEdit->SetValidator( wxMyTextValidator( &SR->verifyEvery ) );
	cleanEveryEdit->SetValidator( wxMyTextValidator( &SR->cleanEvery ) );
	CondIterNumber->SetValidator( wxMyTextValidator( &SR->pasteConditionIters ) );

	resultsGrid->SetRowLabelSize(0); //to eliminate the index column

	HueCenterSpin->Disable(); //suggest the color approach
	HueWidthSpin->Disable();
	ColorPadCriteria->SetValue(true);

	int width = resultsGrid->GetSize().x;
	for (int i=0; i< resultsGrid->GetCols(); i++){
		resultsGrid->SetColumnWidth(i, width/resultsGrid->GetCols()-3 );
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// ShowControl
//
//----------------------------------------------------------------------------------
int wxProductionPanel::ShowControl()
{
	SR->DB->SetFiducialParams( FIDUCIAL_ROT1 );
	rackPosEdit->SetValue(wxString::Format( "%d", SR->GetRackPos() ));
	lastRackPosEdit->SetValue(wxString::Format( "%d", SR->GetLastPrintedRackPos() ));

	TransferDataToWindow();

	SetFiducialButton( false );

	UpdatePanel();
	return SR_OK;
}

//----------------------------------------------------------------------------------
// HideControl
//
//----------------------------------------------------------------------------------
int wxProductionPanel::HideControl()
{
	TransferDataFromWindow();
	return SR_OK;
}

//----------------------------------------------------------------------------------
// DrawControl
//
//----------------------------------------------------------------------------------
int wxProductionPanel::DrawControl( ProductionEnum mode )
{

	EnableAlignmentPanel( false );
	manualCheck->Show( false );
	wxSizerAlignment->Show( false );

	wxSizerPrinting->Show( (mode == PP_PRINTING)||(mode == PP_PASTE) ? true : false );
	wxSizerMoveSqueegees->Show( mode == PP_PRINTING ? true : false );

	wxSizerRackMove->Show( (mode == PP_PRINTING)||(mode == PP_VERIFY) ? true : false );
	EnableSizerChilds( wxSizerRackMove, SR->DB->MachineParamsS.LoaderInstalled && SR->DB->WorkingModesS.LoaderEn && !SR->isBoardLoaded );

	wxSizerVerifyEvery->Show( mode == PP_PRINTING ? true : false );
	EnableSizerChilds(wxSizerVerifyEvery, SR->DB->WorkingModesS.VerifyON);
	//EnableSizerChilds( wxSizerVerifyEvery,  SR->DB->MachineParamsS.LoaderInstalled && SR->DB->WorkingModesS.LoaderEn);
	BoxSizerCleanEvery->Show( mode == PP_PRINTING ? true : false );
	//EnableSizerChilds( BoxSizerCleanEvery, true);
	SuggestCorrectionCheckbox->Show( false );
	//SuggestCorrectionCheckbox->Show( mode == PP_PRINTING ? true : false );
	//SuggestCorrectionCheckbox->Enable(SR->DB->WorkingModesS.VerifyON && SR->DB->MachineParamsS.CleaningInstalled && (SR->DB->WorkingModesS.InspectionType == INSPECTION_SPI) );
	sizerConditioningNum->Show( mode == PP_PASTE ? true : false );



	//cleanEveryEdit->Enable(SR->DB->MachineParamsS.CleaningInstalled && SR->DB->WorkingModesS.CleaningEn && SR->DB->MachineParamsS.LoaderInstalled && SR->DB->WorkingModesS.LoaderEn);

	//EnableSizerChilds( BoxSizerCleanEvery, SR->DB->MachineParamsS.CleaningInstalled && SR->DB->WorkingModesS.CleaningEn && SR->DB->MachineParamsS.LoaderInstalled && SR->DB->WorkingModesS.LoaderEn );

	BoxSizerInspection->Show( false );
	sitesPanel->Show( false );
	BoxSizerPhase1Settings->Show(false);
	BoxSizerPhase2Settings->Show(false);
	ModifySpiParam->Enable(false);

	if( mode == PP_SPI )
		{
			BoxSizerInspection->Show( true );
			sitesPanel->Show( true );
			EnableSizerChilds( BoxSizerInspection, true );
			sitesCheckList->Enable( true );
			ModifySpiParam->Enable(true);

		}
	if (mode==PP_PHASE1){
		BoxSizerInspection->Show(false);
		BoxSizerPhase1Settings->Show(true);

	}
	if (mode==PP_PHASE2){
		BoxSizerPhase2Settings->Show(true);
		BoxSizerInspection->Show(false);

	}

	//BoxSizerInspection->Show( mode == PP_SPI ? true : false);
	//fine

	fiducialBtn->Show( mode == PP_ALIGNMENT ? true : false );
	fiducialBtn->Enable( SR->DB->WorkingModesS.FiducialSearch == FIDUCIAL_AUTO ? true : false );

	gerberBtn->Show( mode == PP_PINS ? true : false );
	gerberBtn->Enable( SR->DB->ProductionDataS.BotGerberOn ? true : false );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// ShowAlignmentPanel
// Mostra/nasconde i controlli
//----------------------------------------------------------------------------------
void wxProductionPanel::ShowAlignmentPanel( bool state )
{
	wxSizerAlignment->Show( state );

	if( state )
		ConfigureAlignmentPanel( SR->DB->pCurrentFiducial->SearchMode );

	Layout();
}

//----------------------------------------------------------------------------------
// ShowManualCheck
// Mostra/nasconde i controlli
//----------------------------------------------------------------------------------
void wxProductionPanel::ShowManualCheck( bool state )
{
	manualCheck->Show( state );
	Layout();
}

//----------------------------------------------------------------------------------
// CheckLimitedVars
// Controlla le variabili da limitare entro un certo range
//----------------------------------------------------------------------------------
void wxProductionPanel::CheckLimitedVars()
{
	int maxBoard = (int)((SR->DB->LimitsS[MOTOR_LOADER_ID].MaxLimit - SR->DB->ProductionDataS.LoaderStartPos - SR->DB->MachineParamsS.LoaderZeroMovement) / SR->DB->ProductionDataS.LoaderTrayPitch);
	if( maxBoard < SR->DB->ProductionDataS.LoaderBoardNumber )
		wxMessageBox( MSG_TOOMANYBOARDS, MACHINE_NAME, wxOK | wxICON_WARNING, this );
	SR->DB->ProductionDataS.LoaderBoardNumber = MID( 0, SR->DB->ProductionDataS.LoaderBoardNumber, maxBoard );
	SR->verifyEvery = MID( 1, SR->verifyEvery, 20 );
	SR->cleanEvery = MID( 0, SR->cleanEvery, 20 );
}

//----------------------------------------------------------------------------------
// EnableAlignmentPanel
// Abilita/disabilita i controlli
//----------------------------------------------------------------------------------
void wxProductionPanel::EnableAlignmentPanel( bool state )
{
	EnableSizerChilds( wxSizerAlignment, state );
}

//----------------------------------------------------------------------------------
// EnablePrintingPanel
// Abilita/disabilita i controlli
//----------------------------------------------------------------------------------
void wxProductionPanel::EnablePrintingPanel( bool state )
{
	EnableSizerChilds( wxSizerMoveSqueegees, state );
	//EnableSizerChilds( wxSizerRackMove, state && ( SR->DB->MachineParamsS.LoaderInstalled && SR->DB->WorkingModesS.LoaderEn ) );
	EnableSizerChilds( wxSizerRackMove, state && ( SR->DB->MachineParamsS.LoaderInstalled && SR->DB->WorkingModesS.LoaderEn && !SR->isBoardLoaded ) );
	EnableSizerChilds( wxSizerVerifyEvery, state && ( SR->DB->MachineParamsS.LoaderInstalled && SR->DB->WorkingModesS.LoaderEn && SR->DB->WorkingModesS.VerifyON ) );
	//EnableSizerChilds( BoxSizerCleanEvery, state && SR->DB->MachineParamsS.CleaningInstalled);
	EnableSizerChilds( BoxSizerCleanEvery, state); //040418
	//SuggestCorrectionCheckbox->Enable(SR->DB->WorkingModesS.VerifyON && SR->DB->MachineParamsS.CleaningInstalled && (SR->DB->WorkingModesS.InspectionType == INSPECTION_SPI) );
	//cout<<"lo stato vale: "<< state<<endl;
}

//----------------------------------------------------------------------------------
// UpdatePrintingPanel
// Aggiorna i controlli
//----------------------------------------------------------------------------------
void wxProductionPanel::UpdatePrintingPanel()
{
	rackPosEdit->SetValue(wxString::Format( "%d", SR->GetRackPos() ));
	lastRackPosEdit->SetValue(wxString::Format( "%d", SR->GetLastPrintedRackPos() ));
	TransferDataToWindow();
}

//----------------------------------------------------------------------------------
// UpdatePrintingData
// Aggiorna i dati dal pannello
//----------------------------------------------------------------------------------
void wxProductionPanel::UpdatePrintingData()
{
	TransferDataFromWindow();
	CheckLimitedVars();
	TransferDataToWindow();
}

//----------------------------------------------------------------------------------
// ConfigureAlignmentPanel
// Configura i controlli
//----------------------------------------------------------------------------------
void wxProductionPanel::ConfigureAlignmentPanel( int searchMode )
{
	if( searchMode == SEARCH_MODE_CIRCLE )
	{
		diameterSlider->Show( true );
		diameterLabel->Show( true );
		sideXSlider->Show( false );
		sideXLabel->Show( false );
		sideYSlider->Show( false );
		sideYLabel->Show( false );
		cAccumVisionSlider->Show( true );
		rAccumVisionSlider->Show( false );
	}
	else if( searchMode == SEARCH_MODE_RECTANGLE )
	{
		diameterSlider->Show( false );
		diameterLabel->Show( false );
		sideXSlider->Show( true );
		sideXLabel->Show( true );
		sideYSlider->Show( true );
		sideYLabel->Show( true );
		cAccumVisionSlider->Show( false );
		rAccumVisionSlider->Show( true );
	}
	Layout();
}

//----------------------------------------------------------------------------------
// UpdatePanel
//
//----------------------------------------------------------------------------------
void wxProductionPanel::UpdatePanel()
{
	if( SR->DB->pCurrentFiducial->SearchMode == SEARCH_MODE_CIRCLE || SR->DB->pCurrentFiducial->SearchMode == SEARCH_MODE_RECTANGLE )
	{
		filterSlider->SetValue( SR->DB->pCurrentFiducial->FilterSmoothDim );
		houghThrSlider->SetValue( SR->DB->pCurrentFiducial->FilterEdgeThr );

		float diameter = (SR->DB->pCurrentFiducial->CircleDiameter) * MM_X_PIXEL;
		diameter = MID( diameterSlider->GetMin(), myLRound( diameter * CIRCLE_SCALE ), diameterSlider->GetMax() );
		diameterSlider->SetValue( int( diameter ) );
		diameterLabel->SetLabel( wxString::Format(_("Diameter %0.2f (mm)"), diameter / CIRCLE_SCALE ) );
		//
		float tempVal = ( int( diameter ) / CIRCLE_SCALE ) / MM_X_PIXEL;
		SR->DB->pCurrentFiducial->CircleDiameter = myLRound( tempVal );

		float sideX = (SR->DB->pCurrentFiducial->RectangleSideX) * MM_X_PIXEL;
		sideX = MID( sideXSlider->GetMin(), myLRound( sideX * RECTANGLE_SCALE ), sideXSlider->GetMax() );
		sideXSlider->SetValue( int( sideX ) );
		sideXLabel->SetLabel( wxString::Format(_("Side X %0.2f (mm)"), sideX / RECTANGLE_SCALE ) );
		//
		tempVal = ( int( sideX ) / RECTANGLE_SCALE ) / MM_X_PIXEL;
		SR->DB->pCurrentFiducial->RectangleSideX = myLRound( tempVal );

		float sideY = (SR->DB->pCurrentFiducial->RectangleSideY) * MM_X_PIXEL;
		sideY = MID( sideYSlider->GetMin(), myLRound( sideY * RECTANGLE_SCALE ), sideYSlider->GetMax() );
		sideYSlider->SetValue( int( sideY ) );
		sideYLabel->SetLabel( wxString::Format(_("Side Y %0.2f (mm)"), sideY / RECTANGLE_SCALE ) );
		//
		tempVal = ( int( sideY ) / RECTANGLE_SCALE ) / MM_X_PIXEL;
		SR->DB->pCurrentFiducial->RectangleSideY = myLRound( tempVal );

		float tolerance = (SR->DB->pCurrentFiducial->Tolerance) * MM_X_PIXEL;
		tolerance = MID( toleranceSlider->GetMin(), myLRound( tolerance * TOLERANCE_SCALE ), toleranceSlider->GetMax() );
		toleranceSlider->SetValue( int( tolerance ) );
		toleranceLabel->SetLabel( wxString::Format(_("Tolerance %0.2f (mm)"), tolerance / TOLERANCE_SCALE ) );
		//
		tempVal = ( int( tolerance ) / TOLERANCE_SCALE ) / MM_X_PIXEL;
		SR->DB->pCurrentFiducial->Tolerance = myLRound( tempVal );

		cAccumVisionSlider->SetValue( SR->DB->pCurrentFiducial->CircleAccum );
		rAccumVisionSlider->SetValue( SR->DB->pCurrentFiducial->RectangleAccum );

		ConfigureAlignmentPanel( SR->DB->pCurrentFiducial->SearchMode );
		shapeCombo->Select( SR->DB->pCurrentFiducial->SearchMode );
	}
	else // TEMPLATE
	{
		templateSlider->SetValue( int( SR->DB->pCurrentFiducial->TemplateThr ) );
		templateLabel->SetLabel( _("Threshold") + wxString::Format(wxT(" %d %%"), int( SR->DB->pCurrentFiducial->TemplateThr ) ) );
	}
}

void wxProductionPanel::UpdatePanelCameraZero(){
	//more or less the same of void wxProductionPanel::UpdatePanel(), but with anothere structure
	filterSlider->SetValue( SR->DB->CameraZeroParamsS.FilterSmoothDim );
	houghThrSlider->SetValue( SR->DB->CameraZeroParamsS.FilterEdgeThr );

	float diameter = (SR->DB->CameraZeroParamsS.CircleDiameter) * MM_X_PIXEL;
	diameter = MID( diameterSlider->GetMin(), myLRound( diameter * CIRCLE_SCALE ), diameterSlider->GetMax() );
	diameterSlider->SetValue( int( diameter ) );
	diameterLabel->SetLabel( wxString::Format(_("Diameter %0.2f (mm)"), diameter / CIRCLE_SCALE ) );
	//
	float tempVal = ( int( diameter ) / CIRCLE_SCALE ) / MM_X_PIXEL;
	SR->DB->CameraZeroParamsS.CircleDiameter = myLRound( tempVal );



	float tolerance = (SR->DB->CameraZeroParamsS.Tolerance) * MM_X_PIXEL;
	tolerance = MID( toleranceSlider->GetMin(), myLRound( tolerance * TOLERANCE_SCALE ), toleranceSlider->GetMax() );
	toleranceSlider->SetValue( int( tolerance ) );
	toleranceLabel->SetLabel( wxString::Format(_("Tolerance %0.2f (mm)"), tolerance / TOLERANCE_SCALE ) );
	//
	tempVal = ( int( tolerance ) / TOLERANCE_SCALE ) / MM_X_PIXEL;
	SR->DB->CameraZeroParamsS.Tolerance = myLRound( tempVal );

	cAccumVisionSlider->SetValue( SR->DB->CameraZeroParamsS.CircleAccum );

	ConfigureAlignmentPanel( SR->DB->CameraZeroParamsS.SearchMode );
	shapeCombo->Select( SR->DB->CameraZeroParamsS.SearchMode );
}

//----------------------------------------------------------------------------------
// UpdateCircleDiameter
//
//----------------------------------------------------------------------------------
void wxProductionPanel::UpdateCircleDiameter()
{
	float diameter = (SR->DB->pCurrentFiducial->CircleDiameter) * MM_X_PIXEL;
	diameter = MID( diameterSlider->GetMin(), myLRound( diameter * CIRCLE_SCALE ), diameterSlider->GetMax() );
	diameterSlider->SetValue( int( diameter ) );
	diameterLabel->SetLabel( wxString::Format(_("Diameter %0.2f (mm)"), diameter / CIRCLE_SCALE ) );
}

//----------------------------------------------------------------------------------
// UpdateRectangleSides
//
//----------------------------------------------------------------------------------
void wxProductionPanel::UpdateRectangleSides()
{
	float sideX = (SR->DB->pCurrentFiducial->RectangleSideX) * MM_X_PIXEL;
	sideX = MID( sideXSlider->GetMin(), myLRound( sideX * RECTANGLE_SCALE ), sideXSlider->GetMax() );
	sideXSlider->SetValue( int( sideX ) );
	sideXLabel->SetLabel( wxString::Format(_("Side X %0.2f (mm)"), sideX / RECTANGLE_SCALE ) );

	float sideY = (SR->DB->pCurrentFiducial->RectangleSideY) * MM_X_PIXEL;
	sideY = MID( sideYSlider->GetMin(), myLRound( sideY * RECTANGLE_SCALE ), sideYSlider->GetMax() );
	sideYSlider->SetValue( int( sideY ) );
	sideYLabel->SetLabel( wxString::Format(_("Side Y %0.2f (mm)"), sideY / RECTANGLE_SCALE ) );
}

//----------------------------------------------------------------------------------
// EnableShapeCombo
//
//----------------------------------------------------------------------------------
void wxProductionPanel::EnableShapeCombo( bool state )
{
	shapeCombo->Enable( state );
}

//----------------------------------------------------------------------------------
// SetFiducialButton
//
//----------------------------------------------------------------------------------
void wxProductionPanel::SetFiducialButton( bool state )
{
	isFiducialBtnOn = state;

	fiducialBtn->SetBitmapDisabled( isFiducialBtnOn ? wxMEMORY_BITMAP( fiducial_mark ) : wxMEMORY_BITMAP( fiducial ) );
	fiducialBtn->SetBitmapLabel( isFiducialBtnOn ? wxMEMORY_BITMAP( fiducial_mark_on ) : wxMEMORY_BITMAP( fiducial_on ) );
}

//----------------------------------------------------------------------------------
// ShowTemplatePanel
//
//----------------------------------------------------------------------------------
void wxProductionPanel::ShowTemplatePanel( bool state )
{
	if( state )
	{
		templatePanel->SetSize( wxSize( 490, 320 ) );
		templatePanel->SetMinSize( wxSize( 490, 320 ) );
		templatePanel->SetMaxSize( wxSize( 490, 320 ) );
	}
	else
	{
		templatePanel->SetSize( wxSize( 490, 1 ) );
		templatePanel->SetMinSize( wxSize( 490, 1 ) );
		templatePanel->SetMaxSize( wxSize( 490, 1 ) );
	}
	templatePanel->Show( state );
	mainSizer->Layout();
	Layout();
}

//----------------------------------------------------------------------------------
// ShowTemplateImage
//
//----------------------------------------------------------------------------------
void wxProductionPanel::ShowTemplateImage( const wxBitmap& bmp )
{
	wxBitmap bmp_bg( 250, 250 );

	wxMemoryDC dc;
	dc.SelectObject( bmp_bg );

	dc.Clear();
	int x = ( bmp_bg.GetWidth() - bmp.GetWidth() ) / 2;
	int y = ( bmp_bg.GetHeight() - bmp.GetHeight() ) / 2;
	dc.DrawBitmap( bmp, x, y, false );

	dc.SelectObject( wxNullBitmap );
	templateImage->SetImage( bmp_bg );
}

void wxProductionPanel::OnradiusSliderCmdScroll(wxScrollEvent& event)
{
	float diametersPixels = ( diameterSlider->GetValue() / CIRCLE_SCALE ) / MM_X_PIXEL;
	SR->DB->pCurrentFiducial->CircleDiameter = myLRound( diametersPixels );
	SR->DB->CameraZeroParamsS.CircleDiameter = myLRound( diametersPixels );
	diameterLabel->SetLabel( wxString::Format(_("Diameter %0.2f (mm)"), float(event.GetPosition() / CIRCLE_SCALE) ) );
}

void wxProductionPanel::OntoleranceSliderCmdScroll(wxScrollEvent& event)
{
	float tolerancePixels = ( toleranceSlider->GetValue() / TOLERANCE_SCALE ) / MM_X_PIXEL;
	SR->DB->pCurrentFiducial->Tolerance = myLRound( tolerancePixels );
	SR->DB->CameraZeroParamsS.Tolerance = myLRound( tolerancePixels );
	toleranceLabel->SetLabel( wxString::Format(_("Tolerance %0.2f (mm)"), float(event.GetPosition() / TOLERANCE_SCALE) ) );
}

void wxProductionPanel::OnfilterSliderCmdScroll(wxScrollEvent& event)
{
	SR->DB->pCurrentFiducial->FilterSmoothDim = event.GetPosition();
	SR->DB->CameraZeroParamsS.FilterSmoothDim = event.GetPosition();
}

void wxProductionPanel::OnhoughThrSliderCmdScroll(wxScrollEvent& event)
{
	SR->DB->pCurrentFiducial->FilterEdgeThr = event.GetPosition();
	SR->DB->CameraZeroParamsS.FilterEdgeThr = event.GetPosition();
}

void wxProductionPanel::OnshapeComboSelect(wxCommandEvent& event)
{
	SR->DB->pCurrentFiducial->SearchMode = event.GetInt();
	ConfigureAlignmentPanel( event.GetInt() );
	Layout();
}

void wxProductionPanel::OnimmediateStopBtnClick(wxCommandEvent& event)
{
	SR->SetStop( true );
}

void wxProductionPanel::OnsideXSliderCmdScroll(wxScrollEvent& event)
{
	float sidePixels = ( sideXSlider->GetValue() / RECTANGLE_SCALE ) / MM_X_PIXEL;
	SR->DB->pCurrentFiducial->RectangleSideX = myLRound( sidePixels );
	sideXLabel->SetLabel( wxString::Format(_("Side X %0.2f (mm)"), float(event.GetPosition() / RECTANGLE_SCALE) ) );
}

void wxProductionPanel::OnsideYSliderCmdScroll(wxScrollEvent& event)
{
	float sidePixels = ( sideYSlider->GetValue() / RECTANGLE_SCALE ) / MM_X_PIXEL;
	SR->DB->pCurrentFiducial->RectangleSideY = myLRound( sidePixels );
	sideYLabel->SetLabel( wxString::Format(_("Side Y %0.2f (mm)"), float(event.GetPosition() / RECTANGLE_SCALE) ) );
}

void wxProductionPanel::OnfiducialBtnClick(wxCommandEvent& event)
{
	SetFiducialButton( !isFiducialBtnOn );
}

void wxProductionPanel::OnsqueegeesMoveBtnClick(wxCommandEvent& event)
{
	wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
	e.SetId( ID_SQUEEGEES_BUTTON );
	e.SetInt( squeegees1Radio->GetValue() );
	GetParent()->GetEventHandler()->AddPendingEvent( e );
}

void wxProductionPanel::OntemplateSliderCmdScroll(wxScrollEvent& event)
{
	SR->DB->pCurrentFiducial->TemplateThr = event.GetPosition();
	templateLabel->SetLabel( _("Threshold") + wxString::Format(wxT(" %d %%"), event.GetPosition() ) );
}

void wxProductionPanel::OnrAccumVisionSliderCmdScroll(wxScrollEvent& event)
{
	SR->DB->pCurrentFiducial->RectangleAccum = event.GetPosition();
}

void wxProductionPanel::OncAccumVisionSliderCmdScroll(wxScrollEvent& event)
{
	SR->DB->pCurrentFiducial->CircleAccum = event.GetPosition();
	SR->DB->CameraZeroParamsS.CircleAccum = event.GetPosition();
}

void wxProductionPanel::OngerberBtnClick(wxCommandEvent& event)
{
	wxPinsDialog pinsDialog(this);
	pinsDialog.Init( SR );

	if( pinsDialog.ShowModal() == PINSDIALOG_OK )
	{
		SR->DB->SavePinsPoints();
	}
}

void wxProductionPanel::OnrackUpBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;

	wxWaitDialog wait(this);
	wait.SetMessage( MSG_LOADERWAIT );
	wait.Show();

	// Move the loader to start position
	if( SR->LoaderMove( SR->GetRackPos()+1 ) == SR_ERROR )
	{
		smartLogger->Write( MSG_LOADERERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	//040418
	SR->isReckinLoadPosition = false;
	wait.Close();

	rackPosEdit->SetValue(wxString::Format( "%d", SR->GetRackPos() ));

	isBusy = false;
}

void wxProductionPanel::OnrackPosBtnClick(wxCommandEvent& event)
{
	rackPosEdit->GetValue().ToLong(&rackPos);
	rackPos = MID( MIN_RACK_POS, rackPos, MAX_RACK_POS );

	if( isBusy )
		return;

	isBusy = true;

	wxWaitDialog wait(this);
	wait.SetMessage( MSG_LOADERWAIT );
	wait.Show();

	// Move the loader to start position
	if( SR->LoaderMove( rackPos ) == SR_ERROR )
	{
		smartLogger->Write( MSG_LOADERERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	//040418
	SR->isReckinLoadPosition = false;
	wait.Close();

	rackPosEdit->SetValue(wxString::Format( "%d", SR->GetRackPos() ));

	isBusy = false;
}

void wxProductionPanel::OnrackDnBtnClick(wxCommandEvent& event)
{
	if( isBusy )
		return;

	isBusy = true;

	wxWaitDialog wait(this);
	wait.SetMessage( MSG_LOADERWAIT );
	wait.Show();

	// Move the loader to start position
	if( SR->LoaderMove( SR->GetRackPos()-1 ) == SR_ERROR )
	{
		smartLogger->Write( MSG_LOADERERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	//040418
	//SR->isReckinLoadPosition = false;
	wait.Close();

	rackPosEdit->SetValue(wxString::Format( "%d", SR->GetRackPos() ));

	isBusy = false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//importati dalla 3100
void wxProductionPanel::OnsitesCheckListSelect(wxCommandEvent& event)
{
	if( vetoEvents )
		return;

	TransferDataFromWindow();
	SR->DB->SiteSelect( event.GetInt() );
	FireEvent( EVT_NEED_UPDATE );
}
//aggiunto

void wxProductionPanel::OnGridElementSelected(wxGridEvent& event){
	TransferDataFromWindow();
	 //create an event to deliver to wxMain
	 SR->DB->Selected_row = event.GetRow();

	 resultsGrid->SelectRow(SR->DB->Selected_row);

	 FireEvent(EVT_GRID_SELECTED);

}
//end
void wxProductionPanel::FireEvent( int eventType )
{
	wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
	e.SetId( ID_EVENT );
	e.SetInt( eventType );
	GetParent()->GetEventHandler()->AddPendingEvent( e );
}

void wxProductionPanel::UpdateListSizer( char mode )
{
	vetoEvents = true;

	sitesCheckList->Clear();
	for( int i = 0; i < SR->DB->SiteCount(); i++ )
	{
		sitesCheckList->AppendString( wxString::Format( "%d. %s", i+1, SR->DB->AUTOInspectionSiteStruct[i].Name.ToAscii() ) );
		sitesCheckList->Check( i, SR->DB->AUTOInspectionSiteStruct[i].Enable ? true : false );
	}
	if( SR->DB->SiteCount() > 0 )
		sitesCheckList->Select( SR->DB->SiteGetSelected() );

	switch( mode )
	{
	case 1: // enable
		EnableSizerChilds( BoxSizerInspection, true );
		break;

	default: // all disable
		EnableSizerChilds(  BoxSizerInspection, false );
		break;
	}

	vetoEvents = false;
}


void wxProductionPanel::UpdateSiteData( int point )
{
	if( SR->DB->SiteCount() )
	{
		nameValueText->ChangeValue( SR->DB->pAUTOInspectionCurrentSiteStruct->Name );
		positionValuePP->SetLabel( wxString::Format( "X: %.1f  Y: %.1f", SR->DB->pAUTOInspectionCurrentSiteStruct->X, SR->DB->pAUTOInspectionCurrentSiteStruct->Y ) );

		// results grid
		UpdateInspectionResults( point );

		// select site
		vetoEvents = true;
		sitesCheckList->Select( SR->DB->SiteGetSelected() );
		vetoEvents = false;
	}
	else
	{
		nameValueText->ChangeValue( wxT("") );
		positionValuePP->SetLabel( wxT("") );

		// results grid
		resultsGrid->DeleteRows( 0, resultsGrid->GetNumberRows() );
	}
}


//----------------------------------------------------------------------------------
// UpdateInspectionResults
//----------------------------------------------------------------------------------
void wxProductionPanel::UpdateInspectionResults( int NumSite )
{
	resultsGrid->BeginBatch();

	if( SR->DB->ResultsCount() != resultsGrid->GetNumberRows() )
	{
		if( SR->DB->ResultsCount() > resultsGrid->GetNumberRows() )
			//resultsGrid->AppendRows( SR->DB->ResultsCount() - resultsGrid->GetNumberRows()  );
			resultsGrid->AppendRows( SR->DB->ResultsCount() - resultsGrid->GetNumberRows() + 1 );
		else
		{
			if( SR->DB->ResultsCount() == 0 )
				resultsGrid->DeleteRows( 0, resultsGrid->GetNumberRows() );
			else
				//resultsGrid->DeleteRows( SR->DB->ResultsCount() - 1, resultsGrid->GetNumberRows() - SR->DB->ResultsCount()  );
				resultsGrid->DeleteRows( SR->DB->ResultsCount() , resultsGrid->GetNumberRows() - SR->DB->ResultsCount()  );
		}
	}
	//cout<<resultsGrid->GetNumberRows()<<endl;
	//cout<<SR->DB->ResultsCount()<<endl;
	for( int i = 0; i < SR->DB->ResultsCount(); i++ )
	{
		resultsGrid->SetCellValue( i, COL_AREA, wxString::Format( "%d", i+1 ) );


		if( SR->DB->AUTOInspectionResults[i].Percentage_covered == -1 )
		{
			resultsGrid->SetCellValue( i, COL_RESULT, wxT("-") );
			resultsGrid->SetCellBackgroundColour( i, COL_RESULT, resultsGrid->GetBackgroundColour() );
		}
		else
		{
			resultsGrid->SetCellValue( i, COL_RESULT, wxString::Format( "%.1f %%", 100-SR->DB->AUTOInspectionResults[i].Percentage_covered ) );
			resultsGrid->SetCellBackgroundColour( i, COL_RESULT, (100-SR->DB->AUTOInspectionResults[i].Percentage_covered) >= SR->DB->pAUTOInspectionCurrentSiteStruct->Alarm ? SPI_HIGH_BG_COLOR : wxColor(SR->DB->ALARM_COLOR.val[0], SR->DB->ALARM_COLOR.val[1], SR->DB->ALARM_COLOR.val[2]) );
		}

		if( SR->DB->AUTOInspectionResults[i].Connected == 0 )
		{
			resultsGrid->SetCellValue( i , COL_SHORT, wxT("No") );
			resultsGrid->SetCellBackgroundColour( i, COL_SHORT, wxColor( 255, 255, 255 )  );
		}
		else
		{
			resultsGrid->SetCellBackgroundColour( i, COL_SHORT, wxColor(SR->DB->SHORT_COLOR.val[0], SR->DB->SHORT_COLOR.val[1], SR->DB->SHORT_COLOR.val[2]) );
			resultsGrid->SetCellValue( i , COL_SHORT, wxT("Short") );
		}

	}
	resultsGrid->EndBatch();
}


void wxProductionPanel::OnSuggestCorrectionCheckboxClick(wxCommandEvent& event)
{
	//cout<<"suggerisco correzioni? "<< SuggestCorrectionCheckbox->IsChecked()<<endl;
	SR->suggestCorrections = SuggestCorrectionCheckbox->IsChecked();
}


void wxProductionPanel::OnPadThrSliderCmdScroll(wxScrollEvent& event)
{
	SR->DB->pAUTOInspectionCurrentSiteStruct->PadThreshold = event.GetPosition();
	FireEvent( EVT_PARAMETERS_CHANGED );
}


void wxProductionPanel::OnAcceptChangesClick(wxCommandEvent& event)
{
	SR->DB-> WriteSPIparams();
	FireEvent(EVT_ACCEPT_CHANGES);
}

void wxProductionPanel::OnCancelChangesClick(wxCommandEvent& event)
{
	//this restore all parameters
	SR->DB-> RestoreSPIparams();
	this->UpdateSPISliders();
	FireEvent( EVT_PARAMETERS_CHANGED );
}

void wxProductionPanel::OnModifySpiParamClick(wxCommandEvent& event)
{
	//SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannel=-1; //this value enables the manual params check
	//SR->DB->pAUTOInspectionCurrentSiteStruct->BestHue=-1;
	//SR->DB->pAUTOInspectionCurrentSiteStruct->PadThreshold=-1;
	//SR->DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE=-1;
	FireEvent( EVT_REQUEST_NEW_THRESHOLDS );

}

void wxProductionPanel::OnHUESliderCmdScroll(wxScrollEvent& event)
{
	//usare con cautela
	SR->DB->pAUTOInspectionCurrentSiteStruct->BestHue = event.GetPosition()/HUE_SLIDER_DENOM_FACTOR;
	FireEvent( EVT_PARAMETERS_CHANGED );
}

void wxProductionPanel::OnChannelChanged(wxCommandEvent& event)
{
	//usare con cautela
	SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannel = event.GetInt();
	FireEvent( EVT_PARAMETERS_CHANGED );
}

void wxProductionPanel::onCancelChangesPhase2(wxCommandEvent& event)
{
	SR->DB-> RestoreSPIparamsPhase2();
	this->UpdateSPISliders();
	FireEvent( EVT_PARAMETERS_CHANGED );
}


void wxProductionPanel::UpdateSPISliders(){

	RadioBoxBestChannel->SetSelection(SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannel);
	//SliderHUE->SetValue(SR->DB->pAUTOInspectionCurrentSiteStruct->BestHue*HUE_SLIDER_DENOM_FACTOR);
	SliderPasteThr->SetValue(SR->DB->pAUTOInspectionCurrentSiteStruct->PadThreshold);

	//HUE spins
	HueCenterSpin->SetValue(SR->DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE);
	HueWidthSpin->SetValue(SR->DB->pAUTOInspectionCurrentSiteStruct->PasteHUEWidth);

	//COLORS spins
	ChannelRadioBox->SetSelection(SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads);
	ColorPadsWidthSpin->SetValue(SR->DB->pAUTOInspectionCurrentSiteStruct->PadsColorWidth);

}

void wxProductionPanel::OnHueCenterSpinChange(wxSpinEvent& event)
{
	SR->DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE = event.GetPosition();
	FireEvent( EVT_PARAMETERS_CHANGED );
}

void wxProductionPanel::OnHueWidthSpinChange(wxSpinEvent& event)
{
	SR->DB->pAUTOInspectionCurrentSiteStruct->PasteHUEWidth= event.GetPosition();
	FireEvent( EVT_PARAMETERS_CHANGED );
}

void wxProductionPanel::OnColorPadCriteriaSelect(wxCommandEvent& event)
{
	HuePadCriteria->SetValue(false);
	HueCenterSpin->Disable();
	HueWidthSpin->Disable();

	ChannelRadioBox->Enable();
	ColorPadsWidthSpin->Enable();

	SR->DB->pAUTOInspectionCurrentSiteStruct->PadsColorWidth = ColorPadsWidthSpin->GetValue();
	switch (ChannelRadioBox->GetSelection()){
		case COLOR_RED:
			SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads = COLOR_RED;
			break;
		case COLOR_GREEN:
			SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads = COLOR_GREEN;
			break;
		case COLOR_BLUE:
			SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads = COLOR_BLUE;
			break;
	}
	SR->DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE = -1;
	SR->DB->pAUTOInspectionCurrentSiteStruct->PasteHUEWidth = -1;

	FireEvent( EVT_PARAMETERS_CHANGED );
}

void wxProductionPanel::OnHuePadCriteriaSelect(wxCommandEvent& event)
{
	ColorPadCriteria->SetValue(false);
	ChannelRadioBox->Disable();
	ColorPadsWidthSpin->Disable();

	HueCenterSpin->Enable();
	HueWidthSpin->Enable();

	SR->DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE = HueCenterSpin->GetValue();
	SR->DB->pAUTOInspectionCurrentSiteStruct->PasteHUEWidth = HueWidthSpin->GetValue();


	SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads = -1;
	SR->DB->pAUTOInspectionCurrentSiteStruct->PadsColorWidth = -1;

	FireEvent( EVT_PARAMETERS_CHANGED );
}

bool wxProductionPanel::UpdatePadThresholds(int red, int green, int blue){

	/*
	float minimum = min(min(red, green), blue);
	float maximum = max(max(red, green), blue);

	 float hue = 0;
	    if (maximum == red) {
	        hue = (green - blue) / (maximum - minimum);

	    } else if (maximum == green) {
	        hue = 2.0 + (blue - red) / (maximum - minimum);

	    } else {
	        hue = 4.0 + (red - green) / (maximum - minimum);
	    }

	    hue = hue * 60;
	    if (hue < 0) hue = hue + 360;

	    //normalize in range 0-255
	    //hue = (hue/360)*255;

	 */
	cv::Mat ColorPixel(1,1,CV_8UC3);
	ColorPixel.at<cv::Vec3b>(0,0)=cv::Vec3b(red, green, blue);
	cv::cvtColor(ColorPixel,ColorPixel, CV_BGR2HSV);
	vector<cv::Mat> HSV;
	cv::split(ColorPixel, HSV);
	int hue = (int)HSV[0].at<uchar>(0,0);


	    //update the graphical part
	    HueCenterSpin->SetValue(round(hue));

	    if ( ColorPadCriteria->GetValue() ) {
	    	switch (ChannelRadioBox->GetSelection()){
	    		case COLOR_RED:
	    			SR->DB->pAUTOInspectionCurrentSiteStruct-> CentralPadsColor=red;
	    			SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads = COLOR_RED;
	    			break;
	    		case COLOR_GREEN:
	    			SR->DB->pAUTOInspectionCurrentSiteStruct-> CentralPadsColor=green;
	    			SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads = COLOR_GREEN;
	    			break;
	    		case COLOR_BLUE:
	    			SR->DB->pAUTOInspectionCurrentSiteStruct-> CentralPadsColor=blue;
	    			SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads = COLOR_BLUE;
	    			break;
	    	}
	    	SR->DB->pAUTOInspectionCurrentSiteStruct->PadsColorWidth = ColorPadsWidthSpin->GetValue();
	    	SR->DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE = -1;
	    	SR->DB->pAUTOInspectionCurrentSiteStruct->PasteHUEWidth = -1;

	    }
	    else{
	    	SR->DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE = round(hue);
	    	SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads = -1;
	    }

	FireEvent( EVT_PARAMETERS_CHANGED );

	return true;
}

void wxProductionPanel::OnChannelRadioBoxSelect(wxCommandEvent& event)
{
	switch (ChannelRadioBox->GetSelection()){
		case COLOR_RED:
			SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads = COLOR_RED;
			break;
		case COLOR_GREEN:
			SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads = COLOR_GREEN;
			break;
		case COLOR_BLUE:
			SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads = COLOR_BLUE;
			break;
	}
	SR->DB->pAUTOInspectionCurrentSiteStruct->PadsColorWidth = ColorPadsWidthSpin->GetValue();
	FireEvent( EVT_PARAMETERS_CHANGED );
}

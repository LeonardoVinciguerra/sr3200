#include "wxCalibrationPanel.h"

//(*InternalHeaders(wxCalibrationPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/msgdlg.h>
#include "wxMyTextValidator.h"
#include "wxOffsetMapsDialog.h"
#include "GlobalEnum.h"
#include "GlobalUtils.h"
#include "Messages.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//(*IdInit(wxCalibrationPanel)
const long wxCalibrationPanel::ID_RADIOBUTTON1 = wxNewId();
const long wxCalibrationPanel::ID_RADIOBUTTON2 = wxNewId();
const long wxCalibrationPanel::ID_STATICTEXT3 = wxNewId();
const long wxCalibrationPanel::ID_TEXTCTRL2 = wxNewId();
const long wxCalibrationPanel::ID_STATICTEXT5 = wxNewId();
const long wxCalibrationPanel::ID_TEXTCTRL3 = wxNewId();
const long wxCalibrationPanel::ID_STATICTEXT4 = wxNewId();
const long wxCalibrationPanel::ID_TEXTCTRL4 = wxNewId();
const long wxCalibrationPanel::ID_STATICTEXT6 = wxNewId();
const long wxCalibrationPanel::ID_TEXTCTRL5 = wxNewId();
const long wxCalibrationPanel::ID_SLIDER1 = wxNewId();
const long wxCalibrationPanel::ID_STATICTEXT7 = wxNewId();
const long wxCalibrationPanel::ID_SliderPasteThr = wxNewId();
const long wxCalibrationPanel::ID_STATICTEXT10 = wxNewId();
const long wxCalibrationPanel::ID_SLIDER2 = wxNewId();
const long wxCalibrationPanel::ID_STATICTEXT8 = wxNewId();
const long wxCalibrationPanel::ID_SliderHUE = wxNewId();
const long wxCalibrationPanel::ID_STATICTEXT9 = wxNewId();
const long wxCalibrationPanel::ID_STATICTEXT1 = wxNewId();
const long wxCalibrationPanel::ID_TEXTCTRL1 = wxNewId();
const long wxCalibrationPanel::ID_STATICTEXT2 = wxNewId();
const long wxCalibrationPanel::ID_TEXTCTRL6 = wxNewId();
const long wxCalibrationPanel::ID_STATICTEXT11 = wxNewId();
const long wxCalibrationPanel::ID_TEXTCTRL7 = wxNewId();
const long wxCalibrationPanel::ID_BUTTON6 = wxNewId();
const long wxCalibrationPanel::ID_BUTTON1 = wxNewId();
const long wxCalibrationPanel::ID_BUTTON2 = wxNewId();
const long wxCalibrationPanel::ID_BUTTON4 = wxNewId();
const long wxCalibrationPanel::ID_BUTTON3 = wxNewId();
const long wxCalibrationPanel::ID_BUTTON5 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxCalibrationPanel,wxPanel)
	//(*EventTable(wxCalibrationPanel)
	//*)
END_EVENT_TABLE()

wxCalibrationPanel::wxCalibrationPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxCalibrationPanel)
	wxStaticBoxSizer* wxSizerConstants;
	wxStaticBoxSizer* wxSizerCameras;
	wxStaticBoxSizer* wxSizerOffset2;
	wxStaticBoxSizer* wxSizerOffset1;
	wxGridSizer* GridSizer1;
	wxBoxSizer* BoxSizer1;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxBoxSizer* BoxSizer3;
	wxGridSizer* GridSizer2;
	
	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	SetMaxSize(wxSize(-1,290));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	wxSizerScale = new wxBoxSizer(wxHORIZONTAL);
	wxSizerCameras = new wxStaticBoxSizer(wxVERTICAL, this, _("Camera Selection"));
	cameraUpRadio = new wxRadioButton(this, ID_RADIOBUTTON1, _("Up"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
	cameraUpRadio->SetValue(true);
	wxSizerCameras->Add(cameraUpRadio, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cameraDownRadio = new wxRadioButton(this, ID_RADIOBUTTON2, _("Down"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
	wxSizerCameras->Add(cameraDownRadio, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerScale->Add(wxSizerCameras, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	wxSizerConstants = new wxStaticBoxSizer(wxVERTICAL, this, _("Constants mm/pixels"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	xUpLabel = new wxStaticText(this, ID_STATICTEXT3, _("X Up"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer1->Add(xUpLabel, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	xUpEdit = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer1->Add(xUpEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	xDownLabel = new wxStaticText(this, ID_STATICTEXT5, _("Y Up"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer1->Add(xDownLabel, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	yUpEdit = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	FlexGridSizer1->Add(yUpEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	yUpLabel = new wxStaticText(this, ID_STATICTEXT4, _("X Down"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer1->Add(yUpLabel, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	xDownEdit = new wxTextCtrl(this, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	FlexGridSizer1->Add(xDownEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	yDownLabel = new wxStaticText(this, ID_STATICTEXT6, _("Y Down"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer1->Add(yDownLabel, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	yDownEdit = new wxTextCtrl(this, ID_TEXTCTRL5, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	FlexGridSizer1->Add(yDownEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	wxSizerConstants->Add(FlexGridSizer1, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerScale->Add(wxSizerConstants, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(wxSizerScale, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerOffset = new wxBoxSizer(wxVERTICAL);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	wxSizerOffset1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Pattern Params"));
	toleranceOffsetSlider = new wxSlider(this, ID_SLIDER1, 0, 1, 6, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SLIDER1"));
	wxSizerOffset1->Add(toleranceOffsetSlider, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	toleranceLabel = new wxStaticText(this, ID_STATICTEXT7, _("Tolerance %0.2f (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	wxSizerOffset1->Add(toleranceLabel, 0, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	accumOffsetSlider = new wxSlider(this, ID_SliderPasteThr, 0, 10, 80, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SliderPasteThr"));
	wxSizerOffset1->Add(accumOffsetSlider, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	accumLabel = new wxStaticText(this, ID_STATICTEXT10, _("Accumulator"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	wxSizerOffset1->Add(accumLabel, 0, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(wxSizerOffset1, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	wxSizerOffset2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Vision Processing Params"));
	filterOffsetSlider = new wxSlider(this, ID_SLIDER2, 0, 3, 15, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SLIDER2"));
	wxSizerOffset2->Add(filterOffsetSlider, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	filterLabel = new wxStaticText(this, ID_STATICTEXT8, _("Filter"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	wxSizerOffset2->Add(filterLabel, 0, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	houghThrOffsetSlider = new wxSlider(this, ID_SliderHUE, 0, 10, 60, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SliderHUE"));
	wxSizerOffset2->Add(houghThrOffsetSlider, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	thresholdLabel = new wxStaticText(this, ID_STATICTEXT9, _("Threshold"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	wxSizerOffset2->Add(thresholdLabel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(wxSizerOffset2, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	wxSizerOffset->Add(BoxSizer3, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Offset Map Parameters"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Num X"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticBoxSizer1->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	numXEdit = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(40,25), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	StaticBoxSizer1->Add(numXEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(-1,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Num Y"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticBoxSizer1->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	numYEdit = new wxTextCtrl(this, ID_TEXTCTRL6, wxEmptyString, wxDefaultPosition, wxSize(40,25), 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
	StaticBoxSizer1->Add(numYEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(-1,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT11, _("Dist"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	StaticBoxSizer1->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	distEdit = new wxTextCtrl(this, ID_TEXTCTRL7, wxEmptyString, wxDefaultPosition, wxSize(60,25), 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
	StaticBoxSizer1->Add(distEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	defaultOffsetBtn = new wxButton(this, ID_BUTTON6, _("Default"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
	StaticBoxSizer1->Add(defaultOffsetBtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerOffset->Add(StaticBoxSizer1, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1 = new wxGridSizer(0, 3, 0, 0);
	offsetMapsBtn = new wxButton(this, ID_BUTTON1, _("View Offset Maps"), wxDefaultPosition, wxSize(150,25), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	GridSizer1->Add(offsetMapsBtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	checkMapsBtn = new wxButton(this, ID_BUTTON2, _("View Check Maps"), wxDefaultPosition, wxSize(150,25), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	GridSizer1->Add(checkMapsBtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	deltaMapsBtn = new wxButton(this, ID_BUTTON4, _("View Maps Delta"), wxDefaultPosition, wxSize(150,25), 0, wxDefaultValidator, _T("ID_BUTTON4"));
	GridSizer1->Add(deltaMapsBtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerOffset->Add(GridSizer1, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer2 = new wxGridSizer(0, 2, 0, 0);
	offsetToCheckBtn = new wxButton(this, ID_BUTTON3, _("Offset Maps <--> Check Maps"), wxDefaultPosition, wxSize(220,25), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	GridSizer2->Add(offsetToCheckBtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	resetCheckMapsBtn = new wxButton(this, ID_BUTTON5, _("Reset Check Maps"), wxDefaultPosition, wxSize(220,25), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	GridSizer2->Add(resetCheckMapsBtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerOffset->Add(GridSizer2, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(wxSizerOffset, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	
	Connect(ID_SLIDER1,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxCalibrationPanel::OntoleranceOffsetSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxCalibrationPanel::OntoleranceOffsetSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxCalibrationPanel::OntoleranceOffsetSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxCalibrationPanel::OntoleranceOffsetSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxCalibrationPanel::OntoleranceOffsetSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxCalibrationPanel::OntoleranceOffsetSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxCalibrationPanel::OntoleranceOffsetSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxCalibrationPanel::OntoleranceOffsetSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxCalibrationPanel::OnaccumOffsetSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxCalibrationPanel::OnaccumOffsetSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxCalibrationPanel::OnaccumOffsetSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxCalibrationPanel::OnaccumOffsetSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxCalibrationPanel::OnaccumOffsetSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxCalibrationPanel::OnaccumOffsetSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxCalibrationPanel::OnaccumOffsetSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxCalibrationPanel::OnaccumOffsetSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxCalibrationPanel::OnfilterOffsetSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxCalibrationPanel::OnfilterOffsetSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxCalibrationPanel::OnfilterOffsetSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxCalibrationPanel::OnfilterOffsetSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxCalibrationPanel::OnfilterOffsetSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxCalibrationPanel::OnfilterOffsetSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxCalibrationPanel::OnfilterOffsetSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxCalibrationPanel::OnfilterOffsetSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxCalibrationPanel::OnhoughThrOffsetSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxCalibrationPanel::OnhoughThrOffsetSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxCalibrationPanel::OnhoughThrOffsetSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxCalibrationPanel::OnhoughThrOffsetSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxCalibrationPanel::OnhoughThrOffsetSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxCalibrationPanel::OnhoughThrOffsetSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxCalibrationPanel::OnhoughThrOffsetSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxCalibrationPanel::OnhoughThrOffsetSliderCmdScroll);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxCalibrationPanel::OndefaultOffsetBtnClick);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxCalibrationPanel::OnoffsetMapsBtnClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxCalibrationPanel::OncheckMapsBtnClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxCalibrationPanel::OndeltaMapsBtnClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxCalibrationPanel::OnoffsetToCheckBtnClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxCalibrationPanel::OnresetCheckMapsBtnClick);
	//*)
}

wxCalibrationPanel::~wxCalibrationPanel()
{
	//(*Destroy(wxCalibrationPanel)
	//*)
}

//----------------------------------------------------------------------------------
// Init
// Inizializza il controllo
//----------------------------------------------------------------------------------
int wxCalibrationPanel::Init( SRDatabase* DBRef )
{
	DB = DBRef;

	numXEdit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.OffsetPointsNumX ) );
	numYEdit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.OffsetPointsNumY ) );
	distEdit->SetValidator( wxMyTextValidator( &DB->MachineParamsS.OffsetPointsDistance, false, 2 ) );

	UpdateConstLabels();

	return SR_OK;
}

//----------------------------------------------------------------------------------
// ShowControl
//
//----------------------------------------------------------------------------------
int wxCalibrationPanel::ShowControl()
{
	DB->SetFiducialParams( FIDUCIAL_OFFSET );

	TransferDataToWindow();
	UpdatePanel();
	return SR_OK;
}

//----------------------------------------------------------------------------------
// HideControl
//
//----------------------------------------------------------------------------------
int wxCalibrationPanel::HideControl()
{
	TransferDataFromWindow();
	return SR_OK;
}

//----------------------------------------------------------------------------------
// DrawControl
//
//----------------------------------------------------------------------------------
int wxCalibrationPanel::DrawControl( CalibrationEnum mode )
{
	wxSizerScale->Show( mode == CC_SCALE ? true : false );
	wxSizerOffset->Show( mode == CC_OFFSET ? true : false );
	return SR_OK;
}

//----------------------------------------------------------------------------------
// EnablePanel
// Abilita/disabilita i controlli
//----------------------------------------------------------------------------------
void wxCalibrationPanel::EnablePanel( bool state )
{
	wxWindowList childs = GetChildren();

	wxWindowList::iterator it = childs.begin(), end = childs.end();
	while( it != end )
	{
		if( ((*it)->GetId() == offsetMapsBtn->GetId()) || ((*it)->GetId() == checkMapsBtn->GetId()) || ((*it)->GetId() == deltaMapsBtn->GetId()) || ((*it)->GetId() == resetCheckMapsBtn->GetId()) || ((*it)->GetId() == offsetToCheckBtn->GetId()) )
			(*it)->Enable( state );
		it++;
	}
}

//----------------------------------------------------------------------------------
// UpdatePanel
//
//----------------------------------------------------------------------------------
void wxCalibrationPanel::UpdatePanel()
{
	filterOffsetSlider->SetValue( DB->pCurrentFiducial->FilterSmoothDim );
	houghThrOffsetSlider->SetValue( DB->pCurrentFiducial->FilterEdgeThr );

	float tolerance = ( 2.0f * DB->pCurrentFiducial->Tolerance ) * MM_X_PIXEL;
	tolerance = myLRound( tolerance * TOLERANCE_SCALE );
	toleranceOffsetSlider->SetValue( int( tolerance ) );
	toleranceLabel->SetLabel( wxString::Format(_("Tolerance %0.2f (mm)"), tolerance / TOLERANCE_SCALE ) );

	accumOffsetSlider->SetValue( DB->pCurrentFiducial->CircleAccum );
}

//----------------------------------------------------------------------------------
// UpdateConstLabels
//
//----------------------------------------------------------------------------------
void wxCalibrationPanel::UpdateConstLabels()
{
	xUpEdit->SetValue( wxString::Format( "%.6f", DB->MachineParamsS.UpXPixMm ) );
	yUpEdit->SetValue( wxString::Format( "%.6f", DB->MachineParamsS.UpYPixMm ) );
	xDownEdit->SetValue( wxString::Format( "%.6f", DB->MachineParamsS.DnXPixMm ) );
	yDownEdit->SetValue( wxString::Format( "%.6f", DB->MachineParamsS.DnYPixMm ) );
}

void wxCalibrationPanel::OntoleranceOffsetSliderCmdScroll(wxScrollEvent& event)
{
	float tolerancePixels = ( toleranceOffsetSlider->GetValue() / TOLERANCE_SCALE ) / MM_X_PIXEL;
	DB->pCurrentFiducial->Tolerance = myLRound( tolerancePixels / 2.0 );

	toleranceLabel->SetLabel( wxString::Format(_("Tolerance %0.2f (mm)"), float(event.GetPosition() / TOLERANCE_SCALE) ) );
}

void wxCalibrationPanel::OnfilterOffsetSliderCmdScroll(wxScrollEvent& event)
{
	DB->pCurrentFiducial->FilterSmoothDim = event.GetPosition();
}

void wxCalibrationPanel::OnhoughThrOffsetSliderCmdScroll(wxScrollEvent& event)
{
	DB->pCurrentFiducial->FilterEdgeThr = event.GetPosition();
}

void wxCalibrationPanel::OnaccumOffsetSliderCmdScroll(wxScrollEvent& event)
{
	DB->pCurrentFiducial->CircleAccum = event.GetPosition();
}

void wxCalibrationPanel::OnoffsetMapsBtnClick(wxCommandEvent& event)
{
	wxOffsetMapsDialog offsetDialog( GetParent(), wxID_ANY, wxDefaultPosition, wxDefaultSize );
	offsetDialog.Init( DB, OFFSET_VIEW_MAP );

	offsetDialog.ShowModal();
}

void wxCalibrationPanel::OncheckMapsBtnClick(wxCommandEvent& event)
{
	wxOffsetMapsDialog offsetDialog( GetParent(), wxID_ANY, wxDefaultPosition, wxDefaultSize );
	offsetDialog.Init( DB, OFFSET_VIEW_CHECK );

	offsetDialog.ShowModal();
}

void wxCalibrationPanel::OndeltaMapsBtnClick(wxCommandEvent& event)
{
	wxOffsetMapsDialog offsetDialog( GetParent(), wxID_ANY, wxDefaultPosition, wxDefaultSize );
	offsetDialog.Init( DB, OFFSET_VIEW_DELTA );

	offsetDialog.ShowModal();
}

void wxCalibrationPanel::OnoffsetToCheckBtnClick(wxCommandEvent& event)
{
	if( wxMessageBox( MSG_UPDATEMAP, MACHINE_NAME, wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION, GetParent() ) == wxYES )
	{
		OffsetPointsStruct OffsetPointsTmpS[NUM_OFFSET_POINTS];

		for( int i = 0, r = DB->MachineParamsS.OffsetPointsNumY - 1; r >= 0; r-- )
		{
			for( int c = 0; c < DB->MachineParamsS.OffsetPointsNumX; c++, i++ )
			{
				OffsetPointsTmpS[i].X = DB->OffsetPointsS[i].X;
				OffsetPointsTmpS[i].Y = DB->OffsetPointsS[i].Y;
				DB->OffsetPointsS[i].X = DB->OffsetCheckPointsS[i].X;
				DB->OffsetPointsS[i].Y = DB->OffsetCheckPointsS[i].Y;
				DB->OffsetCheckPointsS[i].X = OffsetPointsTmpS[i].X;
				DB->OffsetCheckPointsS[i].Y = OffsetPointsTmpS[i].Y;
			}
		}
		DB->SaveOffsetCheckPoints();
		DB->SaveOffsetPoints();
	}
}

void wxCalibrationPanel::OnresetCheckMapsBtnClick(wxCommandEvent& event)
{
	if( wxMessageBox( MSG_RESETCHECKMAP, MACHINE_NAME, wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION, GetParent() ) == wxYES )
	{
		DB->ResetOffsetCheckPoints();
		DB->LoadOffsetCheckPoints();
	}
}

void wxCalibrationPanel::OndefaultOffsetBtnClick(wxCommandEvent& event)
{
	numXEdit->SetValue( wxString::Format( "%d", OFFSET_NUMX_DEFAULT) );
	numYEdit->SetValue( wxString::Format( "%d", OFFSET_NUMY_DEFAULT) );
	distEdit->SetValue( wxString::Format( "%0.2f", OFFSET_DIST_DEFAULT) );

	TransferDataFromWindow();
}

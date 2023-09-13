#include "wxVisionPanel.h"

//(*InternalHeaders(wxVisionPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "wxMyTextValidator.h"
#include "wxMyComboValidator.h"
#include "Messages.h"
#include "GlobalDefs.h"
#include "GlobalUtils.h"
#include "GlobalEnum.h"


//(*IdInit(wxVisionPanel)
const long wxVisionPanel::ID_BUTTON1 = wxNewId();
const long wxVisionPanel::ID_STATICTEXT6 = wxNewId();
const long wxVisionPanel::ID_COMBOBOX1 = wxNewId();
const long wxVisionPanel::ID_SLIDER1 = wxNewId();
const long wxVisionPanel::ID_STATICTEXT3 = wxNewId();
const long wxVisionPanel::ID_SLIDER2 = wxNewId();
const long wxVisionPanel::ID_STATICTEXT4 = wxNewId();
const long wxVisionPanel::ID_SLIDER6 = wxNewId();
const long wxVisionPanel::ID_STATICTEXT9 = wxNewId();
const long wxVisionPanel::ID_SliderHUE = wxNewId();
const long wxVisionPanel::ID_STATICTEXT5 = wxNewId();
const long wxVisionPanel::ID_SLIDER7 = wxNewId();
const long wxVisionPanel::ID_SLIDER8 = wxNewId();
const long wxVisionPanel::ID_STATICTEXT10 = wxNewId();
const long wxVisionPanel::ID_SliderPasteThr = wxNewId();
const long wxVisionPanel::ID_STATICTEXT7 = wxNewId();
const long wxVisionPanel::ID_SLIDER5 = wxNewId();
const long wxVisionPanel::ID_STATICTEXT8 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxVisionPanel,wxPanel)
	//(*EventTable(wxVisionPanel)
	//*)
END_EVENT_TABLE()

wxVisionPanel::wxVisionPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxVisionPanel)
	wxBoxSizer* BoxSizer4;
	wxStaticBoxSizer* StaticBoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxBoxSizer* BoxSizer3;
	
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	SetMaxSize(wxSize(-1,290));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	tableToAlignBtn = new wxButton(this, ID_BUTTON1, _("Table to alignment position"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer1->Add(tableToAlignBtn, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Fiducial Params"));
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Shape"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	BoxSizer4->Add(StaticText6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	shapeVisionCombo = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxSize(90,25), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX1"));
	shapeVisionCombo->SetSelection( shapeVisionCombo->Append(_("CIRCLE")) );
	shapeVisionCombo->Append(_("RECTANGLE"));
	BoxSizer4->Add(shapeVisionCombo, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(BoxSizer4, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	radiusVisionSlider = new wxSlider(this, ID_SLIDER1, 0, 4, 120, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SLIDER1"));
	StaticBoxSizer1->Add(radiusVisionSlider, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	diameterVisionLabel = new wxStaticText(this, ID_STATICTEXT3, _("Diameter %0.2f (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	StaticBoxSizer1->Add(diameterVisionLabel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 15);
	sideXVisionSlider = new wxSlider(this, ID_SLIDER2, 0, 4, 120, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SLIDER2"));
	StaticBoxSizer1->Add(sideXVisionSlider, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	sideXVisionLabel = new wxStaticText(this, ID_STATICTEXT4, _("Side X %0.2f (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	StaticBoxSizer1->Add(sideXVisionLabel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 15);
	sideYVisionSlider = new wxSlider(this, ID_SLIDER6, 0, 4, 120, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SLIDER6"));
	StaticBoxSizer1->Add(sideYVisionSlider, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	sideYVisionLabel = new wxStaticText(this, ID_STATICTEXT9, _("Side Y %0.2f (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	StaticBoxSizer1->Add(sideYVisionLabel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 15);
	toleranceVisionSlider = new wxSlider(this, ID_SliderHUE, 0, 1, 6, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SliderHUE"));
	StaticBoxSizer1->Add(toleranceVisionSlider, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	toleranceVisionLabel = new wxStaticText(this, ID_STATICTEXT5, _("Tolerance %0.2f (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	StaticBoxSizer1->Add(toleranceVisionLabel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 15);
	cAccumVisionSlider = new wxSlider(this, ID_SLIDER7, 0, 10, 40, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SLIDER7"));
	StaticBoxSizer1->Add(cAccumVisionSlider, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	rAccumVisionSlider = new wxSlider(this, ID_SLIDER8, 0, 10, 40, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SLIDER8"));
	StaticBoxSizer1->Add(rAccumVisionSlider, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	accumLabel = new wxStaticText(this, ID_STATICTEXT10, _("Accumulator"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	StaticBoxSizer1->Add(accumLabel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Vision Processing Params"));
	filterVisionSlider = new wxSlider(this, ID_SliderPasteThr, 0, 3, 15, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SliderPasteThr"));
	StaticBoxSizer2->Add(filterVisionSlider, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	filterVisionLabel = new wxStaticText(this, ID_STATICTEXT7, _("Filter"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	StaticBoxSizer2->Add(filterVisionLabel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	houghThrVisionSlider = new wxSlider(this, ID_SLIDER5, 0, 10, 60, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS|wxSL_BOTTOM|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SLIDER5"));
	StaticBoxSizer2->Add(houghThrVisionSlider, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	thresholdVisionLabel = new wxStaticText(this, ID_STATICTEXT8, _("Threshold"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	StaticBoxSizer2->Add(thresholdVisionLabel, 0, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(StaticBoxSizer2, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	BoxSizer1->Add(BoxSizer3, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxVisionPanel::OntableToAlignBtnClick);
	Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&wxVisionPanel::OnshapeVisionComboSelect);
	Connect(ID_SLIDER1,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxVisionPanel::OnradiusVisionSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxVisionPanel::OnradiusVisionSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxVisionPanel::OnradiusVisionSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxVisionPanel::OnradiusVisionSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxVisionPanel::OnradiusVisionSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxVisionPanel::OnradiusVisionSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxVisionPanel::OnradiusVisionSliderCmdScroll);
	Connect(ID_SLIDER1,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxVisionPanel::OnradiusVisionSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxVisionPanel::OnsideXVisionSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxVisionPanel::OnsideXVisionSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxVisionPanel::OnsideXVisionSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxVisionPanel::OnsideXVisionSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxVisionPanel::OnsideXVisionSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxVisionPanel::OnsideXVisionSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxVisionPanel::OnsideXVisionSliderCmdScroll);
	Connect(ID_SLIDER2,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxVisionPanel::OnsideXVisionSliderCmdScroll);
	Connect(ID_SLIDER6,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxVisionPanel::OnsideYVisionSliderCmdScroll);
	Connect(ID_SLIDER6,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxVisionPanel::OnsideYVisionSliderCmdScroll);
	Connect(ID_SLIDER6,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxVisionPanel::OnsideYVisionSliderCmdScroll);
	Connect(ID_SLIDER6,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxVisionPanel::OnsideYVisionSliderCmdScroll);
	Connect(ID_SLIDER6,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxVisionPanel::OnsideYVisionSliderCmdScroll);
	Connect(ID_SLIDER6,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxVisionPanel::OnsideYVisionSliderCmdScroll);
	Connect(ID_SLIDER6,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxVisionPanel::OnsideYVisionSliderCmdScroll);
	Connect(ID_SLIDER6,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxVisionPanel::OnsideYVisionSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxVisionPanel::OntoleranceVisionSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxVisionPanel::OntoleranceVisionSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxVisionPanel::OntoleranceVisionSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxVisionPanel::OntoleranceVisionSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxVisionPanel::OntoleranceVisionSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxVisionPanel::OntoleranceVisionSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxVisionPanel::OntoleranceVisionSliderCmdScroll);
	Connect(ID_SliderHUE,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxVisionPanel::OntoleranceVisionSliderCmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxVisionPanel::OncAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxVisionPanel::OncAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxVisionPanel::OncAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxVisionPanel::OncAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxVisionPanel::OncAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxVisionPanel::OncAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxVisionPanel::OncAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER7,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxVisionPanel::OncAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER8,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxVisionPanel::OnrAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER8,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxVisionPanel::OnrAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER8,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxVisionPanel::OnrAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER8,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxVisionPanel::OnrAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER8,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxVisionPanel::OnrAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER8,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxVisionPanel::OnrAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER8,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxVisionPanel::OnrAccumVisionSliderCmdScroll);
	Connect(ID_SLIDER8,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxVisionPanel::OnrAccumVisionSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxVisionPanel::OnfilterVisionSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxVisionPanel::OnfilterVisionSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxVisionPanel::OnfilterVisionSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxVisionPanel::OnfilterVisionSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxVisionPanel::OnfilterVisionSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxVisionPanel::OnfilterVisionSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxVisionPanel::OnfilterVisionSliderCmdScroll);
	Connect(ID_SliderPasteThr,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxVisionPanel::OnfilterVisionSliderCmdScroll);
	Connect(ID_SLIDER5,wxEVT_SCROLL_TOP,(wxObjectEventFunction)&wxVisionPanel::OnhoughThrVisionSliderCmdScroll);
	Connect(ID_SLIDER5,wxEVT_SCROLL_BOTTOM,(wxObjectEventFunction)&wxVisionPanel::OnhoughThrVisionSliderCmdScroll);
	Connect(ID_SLIDER5,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxVisionPanel::OnhoughThrVisionSliderCmdScroll);
	Connect(ID_SLIDER5,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxVisionPanel::OnhoughThrVisionSliderCmdScroll);
	Connect(ID_SLIDER5,wxEVT_SCROLL_PAGEUP,(wxObjectEventFunction)&wxVisionPanel::OnhoughThrVisionSliderCmdScroll);
	Connect(ID_SLIDER5,wxEVT_SCROLL_PAGEDOWN,(wxObjectEventFunction)&wxVisionPanel::OnhoughThrVisionSliderCmdScroll);
	Connect(ID_SLIDER5,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxVisionPanel::OnhoughThrVisionSliderCmdScroll);
	Connect(ID_SLIDER5,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&wxVisionPanel::OnhoughThrVisionSliderCmdScroll);
	//*)
}

wxVisionPanel::~wxVisionPanel()
{
	//(*Destroy(wxVisionPanel)
	//*)
}

//----------------------------------------------------------------------------------
// Init
// Inizializza il controllo
//----------------------------------------------------------------------------------
int wxVisionPanel::Init( SRMachine* SRRef, SmartLog* smartLoggerRef )
{
	SR = SRRef;
	smartLogger = smartLoggerRef;

	return SR_OK;
}

//----------------------------------------------------------------------------------
// ShowControl
//
//----------------------------------------------------------------------------------
int wxVisionPanel::ShowControl()
{
	SR->DB->SetFiducialParams( FIDUCIAL_VISION_TEST );
	TransferDataToWindow();

	filterVisionSlider->SetValue( SR->DB->pCurrentFiducial->FilterSmoothDim );
	houghThrVisionSlider->SetValue( SR->DB->pCurrentFiducial->FilterEdgeThr );

	float diameter = SR->DB->pCurrentFiducial->CircleDiameter * MM_X_PIXEL;
	diameter = myLRound( diameter * CIRCLE_SCALE );
	radiusVisionSlider->SetValue( int( diameter ) );
	diameterVisionLabel->SetLabel( wxString::Format(_("Diameter %0.2f (mm)"), diameter / CIRCLE_SCALE ) );

	float sideX = SR->DB->pCurrentFiducial->RectangleSideX * MM_X_PIXEL;
	sideX = myLRound( sideX * RECTANGLE_SCALE );
	sideXVisionSlider->SetValue( int( sideX ) );
	sideXVisionLabel->SetLabel( wxString::Format(_("Side X %0.2f (mm)"), sideX / RECTANGLE_SCALE ) );

	float sideY = SR->DB->pCurrentFiducial->RectangleSideY * MM_X_PIXEL;
	sideY = myLRound( sideY * RECTANGLE_SCALE );
	sideYVisionSlider->SetValue( int( sideY ) );
	sideYVisionLabel->SetLabel( wxString::Format(_("Side Y %0.2f (mm)"), sideY / RECTANGLE_SCALE ) );

	float tolerance = SR->DB->pCurrentFiducial->Tolerance * MM_X_PIXEL;
	tolerance = myLRound( tolerance * TOLERANCE_SCALE );
	toleranceVisionSlider->SetValue( int( tolerance ) );
	toleranceVisionLabel->SetLabel( wxString::Format(_("Tolerance %0.2f (mm)"), tolerance / TOLERANCE_SCALE ) );

	cAccumVisionSlider->SetValue( SR->DB->pCurrentFiducial->CircleAccum );
	rAccumVisionSlider->SetValue( SR->DB->pCurrentFiducial->RectangleAccum );

	wxCommandEvent e;
	e.SetInt( SR->DB->pCurrentFiducial->SearchMode );
	OnshapeVisionComboSelect( e );
	shapeVisionCombo->Select( SR->DB->pCurrentFiducial->SearchMode );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// HideControl
//
//----------------------------------------------------------------------------------
int wxVisionPanel::HideControl()
{
	TransferDataFromWindow();
	return SR_OK;
}

void wxVisionPanel::OnradiusVisionSliderCmdScroll(wxScrollEvent& event)
{
	float diametersPixels = ( radiusVisionSlider->GetValue() / CIRCLE_SCALE ) / MM_X_PIXEL;
	SR->DB->pCurrentFiducial->CircleDiameter = myLRound( diametersPixels );
	diameterVisionLabel->SetLabel( wxString::Format(_("Diameter %0.2f (mm)"), float(event.GetPosition() / CIRCLE_SCALE) ) );
}

void wxVisionPanel::OntoleranceVisionSliderCmdScroll(wxScrollEvent& event)
{
	float tolerancePixels = ( toleranceVisionSlider->GetValue() / TOLERANCE_SCALE ) / MM_X_PIXEL;
	SR->DB->pCurrentFiducial->Tolerance = myLRound( tolerancePixels );
	toleranceVisionLabel->SetLabel( wxString::Format(_("Tolerance %0.2f (mm)"), float(event.GetPosition() / TOLERANCE_SCALE) ) );
}

void wxVisionPanel::OnfilterVisionSliderCmdScroll(wxScrollEvent& event)
{
	SR->DB->pCurrentFiducial->FilterSmoothDim = event.GetPosition();
}

void wxVisionPanel::OnhoughThrVisionSliderCmdScroll(wxScrollEvent& event)
{
	SR->DB->pCurrentFiducial->FilterEdgeThr = event.GetPosition();
}

void wxVisionPanel::OnshapeVisionComboSelect(wxCommandEvent& event)
{
	SR->DB->pCurrentFiducial->SearchMode = event.GetInt();

	if( event.GetInt() == 0 ) // CIRCLE
	{
		radiusVisionSlider->Show( true );
		diameterVisionLabel->Show( true );
		sideXVisionSlider->Show( false );
		sideXVisionLabel->Show( false );
		sideYVisionSlider->Show( false );
		sideYVisionLabel->Show( false );
		cAccumVisionSlider->Show( true );
		rAccumVisionSlider->Show( false );
	}
	else if( event.GetInt() == 1 ) // RECTANGLE
	{
		radiusVisionSlider->Show( false );
		diameterVisionLabel->Show( false );
		sideXVisionSlider->Show( true );
		sideXVisionLabel->Show( true );
		sideYVisionSlider->Show( true );
		sideYVisionLabel->Show( true );
		cAccumVisionSlider->Show( false );
		rAccumVisionSlider->Show( true );
	}
	Layout();
}

void wxVisionPanel::OnsideXVisionSliderCmdScroll(wxScrollEvent& event)
{
	float sidePixels = ( sideXVisionSlider->GetValue() / RECTANGLE_SCALE ) / MM_X_PIXEL;
	SR->DB->pCurrentFiducial->RectangleSideX = myLRound( sidePixels );
	sideXVisionLabel->SetLabel( wxString::Format(_("Side X %0.2f (mm)"), float(event.GetPosition() / RECTANGLE_SCALE) ) );
}

void wxVisionPanel::OnsideYVisionSliderCmdScroll(wxScrollEvent& event)
{
	float sidePixels = ( sideYVisionSlider->GetValue() / RECTANGLE_SCALE ) / MM_X_PIXEL;
	SR->DB->pCurrentFiducial->RectangleSideY = myLRound( sidePixels );
	sideYVisionLabel->SetLabel( wxString::Format(_("Side Y %0.2f (mm)"), float(event.GetPosition() / RECTANGLE_SCALE) ) );
}

void wxVisionPanel::OncAccumVisionSliderCmdScroll(wxScrollEvent& event)
{
	SR->DB->pCurrentFiducial->CircleAccum = event.GetPosition();
}

void wxVisionPanel::OnrAccumVisionSliderCmdScroll(wxScrollEvent& event)
{
	SR->DB->pCurrentFiducial->RectangleAccum = event.GetPosition();
}

void wxVisionPanel::OntableToAlignBtnClick(wxCommandEvent& event)
{
	// Roto-translate table to alignment position
	if( SR->RotateTableAndWait( SR->DB->ProductionDataS.LastRot ) == SR_ERROR )
	{
		smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
		return;
	}
	if( SR->MoveXYTableAndWait( SR->DB->ProductionDataS.LastX, SR->DB->ProductionDataS.LastY, SR->GetLimitsState() ) == SR_ERROR )
	{
		smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
		return;
	}
}

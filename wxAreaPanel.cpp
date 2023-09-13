#include "images/png_images.h"

#include "wxAreaPanel.h"
#include "GlobalUtils.h"
#include "GlobalDefs.h"

//(*InternalHeaders(wxAreaPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)


#define TABLE_FG_DIS_COLOR		wxColor( 176, 176, 176 )
#define TABLE_BG_DIS_COLOR		GetBackgroundColour()
#define TABLE_FG_COLOR			wxColor( 255, 255, 0 )
#define TABLE_BG_COLOR			wxColor( 128, 128, 128 )

#define SEARCH_AREA_MIN			1
#define SEARCH_AREA_MAX			12
#define ALARM_MIN				0
#define ALARM_MAX				100

const long wxAreaPanel::ID_EVENT = wxNewId();
const int wxAreaPanel::EVT_SEARCH_AREA = 1;


//(*IdInit(wxAreaPanel)
const long wxAreaPanel::ID_CUSTOM9 = wxNewId();
const long wxAreaPanel::ID_BITMAPBUTTON8 = wxNewId();
const long wxAreaPanel::ID_CUSTOM2 = wxNewId();
const long wxAreaPanel::ID_BITMAPBUTTON7 = wxNewId();
const long wxAreaPanel::ID_CUSTOM7 = wxNewId();
const long wxAreaPanel::ID_BITMAPBUTTON5 = wxNewId();
const long wxAreaPanel::ID_CUSTOM1 = wxNewId();
const long wxAreaPanel::ID_BITMAPBUTTON6 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxAreaPanel,wxPanel)
	//(*EventTable(wxAreaPanel)
	//*)
END_EVENT_TABLE()

wxAreaPanel::wxAreaPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxAreaPanel)
	wxBoxSizer* BoxSizer5;
	wxGridSizer* GridSizer1;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	SetBackgroundColour(wxColour(255,255,255));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	GridSizer1 = new wxGridSizer(0, 2, 0, 0);
	searchAreaPP = new wxPanelPlus(this,ID_CUSTOM9,wxDefaultPosition,wxSize(140,23));
	GridSizer1->Add(searchAreaPP, 0, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	searchAreaMinusBtn = new wxBitmapButton(this, ID_BITMAPBUTTON8, wxNullBitmap, wxDefaultPosition, wxSize(23,23), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON8"));
	BoxSizer5->Add(searchAreaMinusBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	searchAreaValuePP = new wxPanelPlus(this,ID_CUSTOM2,wxDefaultPosition,wxSize(-1,23));
	BoxSizer5->Add(searchAreaValuePP, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	searchAreaPlusBtn = new wxBitmapButton(this, ID_BITMAPBUTTON7, wxNullBitmap, wxDefaultPosition, wxSize(23,23), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON7"));
	BoxSizer5->Add(searchAreaPlusBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer5, 1, wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	alarmPP = new wxPanelPlus(this,ID_CUSTOM7,wxDefaultPosition,wxSize(140,23));
	GridSizer1->Add(alarmPP, 0, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	alarmMinusBtn = new wxBitmapButton(this, ID_BITMAPBUTTON5, wxNullBitmap, wxDefaultPosition, wxSize(23,23), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON5"));
	BoxSizer3->Add(alarmMinusBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	alarmValuePP = new wxPanelPlus(this,ID_CUSTOM1,wxDefaultPosition,wxSize(-1,23));
	BoxSizer3->Add(alarmValuePP, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	alarmPlusBtn = new wxBitmapButton(this, ID_BITMAPBUTTON6, wxNullBitmap, wxDefaultPosition, wxSize(23,23), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON6"));
	BoxSizer3->Add(alarmPlusBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer3, 0, wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(GridSizer1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BITMAPBUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxAreaPanel::OnsearchAreaMinusBtnClick);
	Connect(ID_BITMAPBUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxAreaPanel::OnsearchAreaPlusBtnClick);
	Connect(ID_BITMAPBUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxAreaPanel::OnalarmMinusBtnClick);
	Connect(ID_BITMAPBUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxAreaPanel::OnalarmPlusBtnClick);
	//*)

	// init buttons image
	searchAreaMinusBtn->SetBitmapDisabled( wxMEMORY_BITMAP( minus_round ) );
	searchAreaMinusBtn->SetBitmapLabel( wxMEMORY_BITMAP( minus_round_on ) );
	searchAreaPlusBtn->SetBitmapDisabled( wxMEMORY_BITMAP( plus_round ) );
	searchAreaPlusBtn->SetBitmapLabel( wxMEMORY_BITMAP( plus_round_on ) );
	alarmMinusBtn->SetBitmapDisabled( wxMEMORY_BITMAP( minus_round ) );
	alarmMinusBtn->SetBitmapLabel( wxMEMORY_BITMAP( minus_round_on ) );
	alarmPlusBtn->SetBitmapDisabled( wxMEMORY_BITMAP( plus_round ) );
	alarmPlusBtn->SetBitmapLabel( wxMEMORY_BITMAP( plus_round_on ) );

	// set label
	searchAreaPP->SetLabel( _("Search area") );
	alarmPP->SetLabel( _("Alarm") );

	// set foreground disable color
	searchAreaPP->SetForegroundDisableColour( TABLE_FG_DIS_COLOR );
	alarmPP->SetForegroundDisableColour( TABLE_FG_DIS_COLOR );
	searchAreaValuePP->SetForegroundDisableColour( TABLE_FG_DIS_COLOR );
	alarmValuePP->SetForegroundDisableColour( TABLE_FG_DIS_COLOR );

	// set foreground color
	searchAreaPP->SetForegroundColour( TABLE_FG_COLOR );
	alarmPP->SetForegroundColour( TABLE_FG_COLOR );

	// set background disable color
	searchAreaPP->SetBackgroundDisableColour( TABLE_BG_DIS_COLOR );
	alarmPP->SetBackgroundDisableColour( TABLE_BG_DIS_COLOR );

	// set background color
	searchAreaPP->SetBackgroundColour( TABLE_BG_COLOR );
	alarmPP->SetBackgroundColour( TABLE_BG_COLOR );

	// init values
	pSearchArea = &_searchArea;
	pAlarm = &_alarm;
	//
	_searchArea = 10;
	_alarm = 95;

	searchAreaValuePP->SetLabel( wxString::Format( "%d", *pSearchArea ) );
	alarmValuePP->SetLabel( wxString::Format( "%d %%", *pAlarm ) );
}

wxAreaPanel::~wxAreaPanel()
{
	//(*Destroy(wxAreaPanel)
	//*)
}

//----------------------------------------------------------------------------------
// SetSearchArea
//----------------------------------------------------------------------------------
void wxAreaPanel::SetSearchArea( int* value )
{
	pSearchArea = value;
	*pSearchArea = MID( SEARCH_AREA_MIN, *pSearchArea, SEARCH_AREA_MAX );
	searchAreaValuePP->SetLabel( wxString::Format( "%d", *pSearchArea ) );
}

//----------------------------------------------------------------------------------
// SetAlarm
//----------------------------------------------------------------------------------
void wxAreaPanel::SetAlarm( int* value )
{
	pAlarm = value;
	*pAlarm = MID( ALARM_MIN, *pAlarm, ALARM_MAX );
	alarmValuePP->SetLabel( wxString::Format( "%d %%", *pAlarm ) );
}

//----------------------------------------------------------------------------------
// EnableAdjustButtons
//----------------------------------------------------------------------------------
void wxAreaPanel::EnableAdjustButtons( bool enable )
{
	searchAreaMinusBtn->Enable( enable );
	searchAreaPlusBtn->Enable( enable );
	alarmMinusBtn->Enable( enable );
	alarmPlusBtn->Enable( enable );
}

//----------------------------------------------------------------------------------
// FireEvent
//----------------------------------------------------------------------------------
void wxAreaPanel::FireEvent( int eventType )
{
	wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
	e.SetId( ID_EVENT );
	e.SetInt( eventType );
	GetParent()->GetEventHandler()->AddPendingEvent( e );
}


	//------------//
	//   Events   //
	//------------//

void wxAreaPanel::OnsearchAreaMinusBtnClick(wxCommandEvent& event)
{
	if( *pSearchArea > SEARCH_AREA_MIN )
	{
		(*pSearchArea)--;
		searchAreaValuePP->SetLabel( wxString::Format( "%d", *pSearchArea ) );
		searchAreaValuePP->Refresh();

		FireEvent( EVT_SEARCH_AREA );
	}
}

void wxAreaPanel::OnsearchAreaPlusBtnClick(wxCommandEvent& event)
{
	if( *pSearchArea < SEARCH_AREA_MAX )
	{
		(*pSearchArea)++;
		searchAreaValuePP->SetLabel( wxString::Format( "%d", *pSearchArea ) );
		searchAreaValuePP->Refresh();

		FireEvent( EVT_SEARCH_AREA );
	}
}

void wxAreaPanel::OnalarmMinusBtnClick(wxCommandEvent& event)
{
	if( *pAlarm > ALARM_MIN )
	{
		(*pAlarm)--;
		alarmValuePP->SetLabel( wxString::Format( "%d %%", *pAlarm ) );
		alarmValuePP->Refresh();
	}
}

void wxAreaPanel::OnalarmPlusBtnClick(wxCommandEvent& event)
{
	if( *pAlarm < ALARM_MAX )
	{
		(*pAlarm)++;
		alarmValuePP->SetLabel( wxString::Format( "%d %%", *pAlarm ) );
		alarmValuePP->Refresh();
	}
}

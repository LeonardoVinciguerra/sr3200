#include "wxInspectionVerifyPanel.h"
#include "images/png_images.h"


//(*InternalHeaders(wxInspectionVerifyPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include "SRDatabase.h"
#include <wx/grid.h>
#include "GlobalUtils.h"

//(*IdInit(wxInspectionVerifyPanel)
const long wxInspectionVerifyPanel::ID_STATICTEXT8 = wxNewId();
const long wxInspectionVerifyPanel::ID_CHECKLISTBOX1 = wxNewId();
const long wxInspectionVerifyPanel::ID_STATICLINE3 = wxNewId();
const long wxInspectionVerifyPanel::ID_GRID1 = wxNewId();
const long wxInspectionVerifyPanel::ID_PANEL3 = wxNewId();
const long wxInspectionVerifyPanel::ID_PANEL5 = wxNewId();
const long wxInspectionVerifyPanel::ID_STATICTEXT1 = wxNewId();
const long wxInspectionVerifyPanel::ID_TEXTCTRL1 = wxNewId();
const long wxInspectionVerifyPanel::ID_STATICTEXT2 = wxNewId();
const long wxInspectionVerifyPanel::ID_TEXTCTRL2 = wxNewId();
const long wxInspectionVerifyPanel::ID_BITMAPBUTTON1 = wxNewId();
const long wxInspectionVerifyPanel::ID_CHECKBOX1 = wxNewId();
const long wxInspectionVerifyPanel::ID_CHECKBOX2 = wxNewId();
//*)
const long wxInspectionVerifyPanel::EVT_GRID_SELECTED_RECORDS = wxNewId();
const long wxInspectionVerifyPanel::ID_EVENT_RECORDS = wxNewId();
const long wxInspectionVerifyPanel::ID_CHANGEPICTURE= wxNewId();
const long wxInspectionVerifyPanel::EVT_IDENTIFY_ALL_FAULTY = wxNewId();
const long wxInspectionVerifyPanel::EVT_IDENTIFY_ALL_WARNING = wxNewId();


BEGIN_EVENT_TABLE(wxInspectionVerifyPanel,wxPanel)
	//(*EventTable(wxInspectionVerifyPanel)
	//*)
END_EVENT_TABLE()

enum ResultsGridColLabels
{
	COL_AREA,
	PASTE_PERCENTAGE,
	CONNECTED_SPOTS
};

wxInspectionVerifyPanel::wxInspectionVerifyPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxInspectionVerifyPanel)
	wxBoxSizer* siteSizer;

	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL, _T("wxID_ANY"));
	SetBackgroundColour(wxColour(208,208,208));
	SetExtraStyle( GetExtraStyle() | wxWS_EX_VALIDATE_RECURSIVELY );
	mainSizer = new wxBoxSizer(wxVERTICAL);
	sitesPanel = new wxPanel(this, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
	sitesPanel->SetBackgroundColour(wxColour(192,192,192));
	BoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
	sitesListSizer = new wxBoxSizer(wxVERTICAL);
	StaticText7 = new wxStaticText(sitesPanel, ID_STATICTEXT8, _("Inspection points"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	sitesListSizer->Add(StaticText7, 0, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	sitesCheckList = new wxCheckListBox(sitesPanel, ID_CHECKLISTBOX1, wxDefaultPosition, wxSize(109,150), 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX1"));
	sitesListSizer->Add(sitesCheckList, 1, wxTOP|wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer12->Add(sitesListSizer, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticLine3 = new wxStaticLine(sitesPanel, ID_STATICLINE3, wxDefaultPosition, wxSize(2,-1), wxLI_VERTICAL, _T("ID_STATICLINE3"));
	BoxSizer12->Add(StaticLine3, 0, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	siteSizer = new wxBoxSizer(wxVERTICAL);
	spiPanel = new wxPanel(sitesPanel, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	spiPanel->SetBackgroundColour(wxColour(192,192,192));
	spiDataSizer = new wxBoxSizer(wxVERTICAL);
	resultsGrid = new wxGrid(spiPanel, ID_GRID1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID1"));
	resultsGrid->CreateGrid(0,3);
	resultsGrid->SetCellHighlightPenWidth(0);
	resultsGrid->EnableEditing(false);
	resultsGrid->EnableGridLines(true);
	resultsGrid->SetColLabelValue(0, _("Area"));
	resultsGrid->SetColLabelValue(1, _("Covering"));
	resultsGrid->SetColLabelValue(2, _("Short"));
	resultsGrid->SetDefaultCellFont( resultsGrid->GetFont() );
	resultsGrid->SetDefaultCellTextColour( resultsGrid->GetForegroundColour() );
	spiDataSizer->Add(resultsGrid, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	spiPanel->SetSizer(spiDataSizer);
	spiDataSizer->Fit(spiPanel);
	spiDataSizer->SetSizeHints(spiPanel);
	siteSizer->Add(spiPanel, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer12->Add(siteSizer, 2, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	sitesPanel->SetSizer(BoxSizer12);
	BoxSizer12->Fit(sitesPanel);
	BoxSizer12->SetSizeHints(sitesPanel);
	mainSizer->Add(sitesPanel, 7, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Alarm:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer1->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextAlarm = new wxTextCtrl(this, ID_TEXTCTRL1, _("--"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer1->Add(TextAlarm, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Warning:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer1->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextWarning = new wxTextCtrl(this, ID_TEXTCTRL2, _("--"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer1->Add(TextWarning, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ConfirmAlarmWarning = new wxBitmapButton(this, ID_BITMAPBUTTON1, wxNullBitmap, wxDefaultPosition, wxSize(30,30), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	ConfirmAlarmWarning->SetToolTip(_("Confirm Alarm and Warning thresholds"));
	BoxSizer1->Add(ConfirmAlarmWarning, 0, wxALL|wxSHAPED|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxFaulty = new wxCheckBox(this, ID_CHECKBOX1, _("Identify faulty"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	CheckBoxFaulty->SetValue(false);
	BoxSizer1->Add(CheckBoxFaulty, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxWarning = new wxCheckBox(this, ID_CHECKBOX2, _("Identify Warning"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	CheckBoxWarning->SetValue(false);
	BoxSizer1->Add(CheckBoxWarning, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	mainSizer->Add(BoxSizer1, 1, wxALL|wxSHAPED|wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(mainSizer);
	SetSizer(mainSizer);
	Layout();

	Connect(ID_GRID1,wxEVT_GRID_CELL_LEFT_CLICK,(wxObjectEventFunction)&wxInspectionVerifyPanel::OnGridElementSelected);
	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionVerifyPanel::OnConfirmAlarmWarningClick);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxInspectionVerifyPanel::OnIdentifyAllFaulty);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxInspectionVerifyPanel::OnIdentifyAllWarning);
	Connect(wxEVT_PAINT,(wxObjectEventFunction)&wxInspectionVerifyPanel::OnPaint);
	//*)

	Connect(ID_GRID1, wxEVT_GRID_CELL_LEFT_CLICK, (wxObjectEventFunction)&wxInspectionVerifyPanel::OnSiteSelected);

	Connect(ID_CHECKLISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&wxInspectionVerifyPanel::OnsitesCheckListSelect);

	ConfirmAlarmWarning->SetBitmapLabel( wxMEMORY_BITMAP( ok_small_on ) );

}
/*const long wxInspectionVerifyPanel::EVT_GRID_SELECTED_RECORDS = wxNewId();
const long wxInspectionVerifyPanel::ID_EVENT_RECORDS = wxNewId();*/
wxInspectionVerifyPanel::~wxInspectionVerifyPanel()
{
	//(*Destroy(wxInspectionVerifyPanel)
	//*)
}


void wxInspectionVerifyPanel::OnPaint(wxPaintEvent& event)
{

}

void wxInspectionVerifyPanel::OnTextCtrl1Text(wxCommandEvent& event)
{
}

void wxInspectionVerifyPanel::OnTextCtrl1Text1(wxCommandEvent& event)
{
}

bool wxInspectionVerifyPanel::Init( SRDatabase* DBRef ) {

	DB = DBRef;

	//resultsGrid->SetRowLabelSize(0); //to eliminate the index column

		int width = resultsGrid->GetSize().x;
		for (int i=0; i< resultsGrid->GetCols(); i++){
			resultsGrid->SetColumnWidth(i, width/resultsGrid->GetCols() );
		}

	resultsGrid->SetRowLabelSize(0); //it eliminates the index column
	DB->AllFaultyStatus =0;
	DB->AllWarningStatus =0;



}

void wxInspectionVerifyPanel::OnsitesCheckListSelect(wxCommandEvent& event)
{

	//TransferDataFromWindow();//for validators
	DB->SelectedSite= event.GetInt();

	EnableSizerChilds( mainSizer, true );
	UpdateListSizer( DB->SelectedSite );
	UpdateInspectionResults( DB->SelectedSite );


	for (int i=0; i<DB->SpotsCount(); i++){
		if(DB->AUTOInspectionPointRecord[i].SiteNum == DB->SelectedSite){
			TextAlarm->ChangeValue(wxString::Format("%d", DB->AUTOInspectionPointRecord[i].Alarm));
			TextWarning->ChangeValue(wxString::Format("%d", DB->AUTOInspectionPointRecord[i].Warning));
			break;
		}
	}
	CheckBoxFaulty->SetValue(false);
	CheckBoxWarning->SetValue(false);
	DB->AllFaultyStatus =0;
	DB->AllWarningStatus =0;

	wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED ); //change picture!
	e.SetId(  ID_CHANGEPICTURE );
	e.SetInt( ID_CHANGEPICTURE );

	GetParent()->GetEventHandler()->AddPendingEvent( e );



}
//aggiunto

void wxInspectionVerifyPanel::OnGridElementSelected(wxGridEvent& event){
	TransferDataFromWindow();
	 //create an event to deliver to wxMain
	 DB->Selected_row = event.GetRow();

	 FireEvent( EVT_GRID_SELECTED_RECORDS );

}
//end
void wxInspectionVerifyPanel::FireEvent( int eventType )
{
	wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
	e.SetId( ID_EVENT_RECORDS );
	e.SetInt( eventType );
	GetParent()->GetEventHandler()->AddPendingEvent( e );
}




void wxInspectionVerifyPanel::UpdateSiteData( int point )
{
	if( DB->SiteCount() )
	{

		// results grid
		UpdateInspectionResults( point );

		// select site

		sitesCheckList->Select( DB->SiteGetSelected() );
	}
	else
	{

		resultsGrid->DeleteRows( 0, resultsGrid->GetNumberRows() );
	}
}


//----------------------------------------------------------------------------------
// UpdateInspectionResults
//----------------------------------------------------------------------------------
void wxInspectionVerifyPanel::UpdateInspectionResults( int NumSite )
{
	resultsGrid->BeginBatch();

	int totalRowNumber=0;
	std::vector<int> index;
	for( int i = 0; i < DB->SpotsCount(); i++ ){
		//cout<<DB->AUTOInspectionPointRecord[i].SiteNum<<endl;
		if(DB->AUTOInspectionPointRecord[i].SiteNum == NumSite){

			totalRowNumber++;
			index.push_back(i);
		}
	}

	if( totalRowNumber != resultsGrid->GetNumberRows() )
	{

		if( totalRowNumber > resultsGrid->GetNumberRows() )

			resultsGrid->AppendRows( totalRowNumber - resultsGrid->GetNumberRows() );
		else
		{
			if( DB->SpotsCount() == 0 )
				resultsGrid->DeleteRows( 0, resultsGrid->GetNumberRows() );
			else
				resultsGrid->DeleteRows( totalRowNumber , resultsGrid->GetNumberRows() - totalRowNumber  );

		}
	}

	for( int i = 0; i < index.size(); i++ ) //all the results
	{
		resultsGrid->SetCellValue( i, COL_AREA, wxString::Format( "%d", i+1 ) );


		resultsGrid->SetCellValue( i, PASTE_PERCENTAGE, wxString::Format( "%.1f %%", 100-DB->AUTOInspectionPointRecord[ index[i] ].Percentage_covered ) );

		if (100-DB->AUTOInspectionPointRecord[ index[i] ].Percentage_covered < DB->AUTOInspectionPointRecord[ index[i] ].Alarm){
		resultsGrid->SetCellBackgroundColour( i, PASTE_PERCENTAGE, wxColor( 255, 0, 0 ) ); //color red
		}
		else{
			resultsGrid->SetCellBackgroundColour( i, PASTE_PERCENTAGE, wxColor( 255, 255, 255 ) ); //color white
		}

		if( DB->AUTOInspectionPointRecord[ index[i] ].ConnectedWith == 0 )
		{
			resultsGrid->SetCellValue( i , CONNECTED_SPOTS, wxT("No") );
			resultsGrid->SetCellBackgroundColour( i, CONNECTED_SPOTS, wxColor( 255, 255, 255 )  );
			//resultsGrid->SetCellBackgroundColour( index[i] , CONNECTED_SPOTS, resultsGrid->GetBackgroundColour() );
		}
		else
		{
			//resultsGrid->SetCellValue( i, COL_RESULT, wxString::Format( "%d %%", SR->DB->InspectionAreasS[i].Result ) );
			resultsGrid->SetCellBackgroundColour( i, CONNECTED_SPOTS, wxColor( 255, 0, 0 )  );
			resultsGrid->SetCellValue( i , CONNECTED_SPOTS, wxT("Short") );
			//resultsGrid->SetCellValue( i, CONNECTED_SPOTS, wxString::Format( "%d", DB->AUTOInspectionPointRecord[ index[i] ].ConnectedWith ) );
		}
	}

	resultsGrid->EndBatch();
}

int wxInspectionVerifyPanel::InitializeSelectedBoard(){


	DB->LoadResultsSites(DB->SelectedBoardNumber, DB->SelectedIDprod, 0); //here we load all results!

	UpdateListSizer(0);
	UpdateInspectionResults(0);

	//set the first site alarm
	TextAlarm->ChangeValue(wxString::Format("%d", DB->AUTOInspectionPointRecord[0].Alarm));
	TextWarning->ChangeValue(wxString::Format("%d", DB->AUTOInspectionPointRecord[0].Warning));
	CheckBoxFaulty->SetValue(false);
	CheckBoxWarning->SetValue(false);
	DB->AllFaultyStatus =0;
	DB->AllWarningStatus =0;

	DB->SelectedSite=0;


};

void wxInspectionVerifyPanel::UpdateListSizer(int selected )
{
	sitesCheckList->Deselect(selected); //if something is enabled, clear will call the OnsitesCheckListSelect
	sitesCheckList->Clear();
	int prev=-1;
	int counter=0;

	for( int i = 0; i < DB->SavedResult; i++ )
	{
		if (DB->AUTOInspectionPointRecord[i].SiteNum !=prev ){
			int faulty_area=0;
			int paste_short=0;
			prev=DB->AUTOInspectionPointRecord[i].SiteNum;

			for(int j = i; j < DB->SavedResult; j++ ){ //from this site
				if (DB->AUTOInspectionPointRecord[j].SiteNum !=prev ){
					break;
				}
				if(DB->AUTOInspectionPointRecord[j].Percentage_covered > 100-DB->AUTOInspectionPointRecord[j].Alarm)
					faulty_area++;
				if(DB->AUTOInspectionPointRecord[j].ConnectedWith)
					paste_short++;
			}
			sitesCheckList->AppendString( wxString::Format( "[%d-%d] %s" , faulty_area, paste_short, DB->AUTOInspectionPointRecord[i].SiteName ) );
			//sitesCheckList->AppendString( wxString::Format(  "  %s", DB->AUTOInspectionPointRecord[i].SiteName.ToAscii() )  );
			sitesCheckList->Check( counter ,true);
			counter++;

		}

	}
	if( counter > 0 ){
		sitesCheckList->Select( selected );
		// all disable
		EnableSizerChilds( sitesListSizer, true );
	}


}

void wxInspectionVerifyPanel::OnSiteSelected ( wxGridEvent& event ){

		TransferDataFromWindow();
		 //create an event to deliver to wxMain
		 DB->Selected_row = event.GetRow();


		 wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
		 e.SetId(  EVT_GRID_SELECTED_RECORDS  );

		 e.SetInt( EVT_GRID_SELECTED_RECORDS );

		 resultsGrid->SelectRow(DB->Selected_row);
		 CheckBoxFaulty->SetValue(false);
		 CheckBoxWarning->SetValue(false);
		 DB->AllFaultyStatus =0;
		 DB->AllWarningStatus =0;


		 GetParent()->GetEventHandler()->AddPendingEvent( e ); //send a message to wxMain->Smbase->SMViewRecords, tell to draw a rectangle

	}






void wxInspectionVerifyPanel::OnConfirmAlarmWarningClick(wxCommandEvent& event)
{
	int IDsite;
	for (int i=0; i<DB->SpotsCount(); i++){
			if(DB->AUTOInspectionPointRecord[i].SiteNum == DB->SelectedSite){
				IDsite=DB->AUTOInspectionPointRecord[i].ID_Site;
				break;
			}
		}

	DB->UpdateAlarmAndWarning(TextWarning->GetValue(), TextAlarm->GetValue(), IDsite);
	UpdateInspectionResults(DB->SelectedSite);
	UpdateListSizer(DB->SelectedSite);
	//TODO la BoardResult non si aggiorna! farlo?

}

void wxInspectionVerifyPanel::OnIdentifyAllFaulty(wxCommandEvent& event)
{
	if(CheckBoxWarning->IsChecked()){
		CheckBoxWarning->SetValue(false);
		DB->AllWarningStatus =0;
	}
	wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
	e.SetId(  EVT_IDENTIFY_ALL_FAULTY );
	e.SetInt( EVT_IDENTIFY_ALL_FAULTY );
	GetParent()->GetEventHandler()->AddPendingEvent( e );
}

void wxInspectionVerifyPanel::OnIdentifyAllWarning(wxCommandEvent& event)
{
	if(CheckBoxFaulty->IsChecked()){
			CheckBoxFaulty->SetValue(false);
			DB->AllFaultyStatus =0;
	}
	wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
	e.SetId(  EVT_IDENTIFY_ALL_WARNING );
	e.SetInt( EVT_IDENTIFY_ALL_WARNING );
	GetParent()->GetEventHandler()->AddPendingEvent( e );

}

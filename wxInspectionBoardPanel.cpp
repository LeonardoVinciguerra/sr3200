#include "wxInspectionBoardPanel.h"


//(*InternalHeaders(wxInspectionBoardPanel)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
#include "Messages.h"
//*)
#include "SRDatabase.h"
#include <wx/msgdlg.h>
#include <wx/grid.h>

//(*IdInit(wxInspectionBoardPanel)
const long wxInspectionBoardPanel::ID_STATICTEXT1 = wxNewId();
const long wxInspectionBoardPanel::ID_CHOICE1 = wxNewId();
const long wxInspectionBoardPanel::ID_STATICTEXT2 = wxNewId();
const long wxInspectionBoardPanel::ID_CHOICE2 = wxNewId();
const long wxInspectionBoardPanel::ID_BUTTON1 = wxNewId();
const long wxInspectionBoardPanel::ID_BUTTON2 = wxNewId();
const long wxInspectionBoardPanel::ID_PANEL1 = wxNewId();
const long wxInspectionBoardPanel::ID_GRID1 = wxNewId();
const long wxInspectionBoardPanel::ID_PANEL2 = wxNewId();
//*)ID_EVENTRECORDS
const long wxInspectionBoardPanel::ID_EVENTRECORDS = wxNewId();

BEGIN_EVENT_TABLE(wxInspectionBoardPanel,wxPanel)
	//(*EventTable(wxInspectionBoardPanel)
	//*)
END_EVENT_TABLE()

enum BoardGrid
{
	COL_Name,
	COL_NBoard,
	COL_Date,
	COL_AlertAreas,
	COL_Connected
};

wxInspectionBoardPanel::wxInspectionBoardPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxInspectionBoardPanel)
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	SetMaxSize(wxSize(-1,300));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Production"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(14,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	BoxSizer2->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Choice1 = new wxChoice(Panel1, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	BoxSizer2->Add(Choice1, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("Boards"), wxDefaultPosition, wxSize(50,23), 0, _T("ID_STATICTEXT2"));
	wxFont StaticText2Font(14,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	BoxSizer2->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Choice2 = new wxChoice(Panel1, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
	BoxSizer2->Add(Choice2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4 = new wxBoxSizer(wxVERTICAL);
	Button1 = new wxButton(Panel1, ID_BUTTON1, _(">>"), wxDefaultPosition, wxSize(30,25), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer4->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	Button2 = new wxButton(Panel1, ID_BUTTON2, _("<<"), wxDefaultPosition, wxSize(30,25), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer4->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	BoxSizer2->Add(BoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Panel1->SetSizer(BoxSizer2);
	BoxSizer2->Fit(Panel1);
	BoxSizer2->SetSizeHints(Panel1);
	BoxSizer1->Add(Panel1, 1, wxALL|wxSHAPED|wxALIGN_LEFT|wxALIGN_TOP, 5);
	Panel2 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	Panel2->SetMinSize(wxSize(-1,-1));
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	Grid1 = new wxGrid(Panel2, ID_GRID1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID1"));
	Grid1->CreateGrid(0,5);
	Grid1->SetCellHighlightPenWidth(0);
	Grid1->EnableEditing(false);
	Grid1->EnableGridLines(true);
	Grid1->SetColLabelValue(0, _("Prod Name"));
	Grid1->SetColLabelValue(1, _("Board n"));
	Grid1->SetColLabelValue(2, _("Date"));
	Grid1->SetColLabelValue(3, _("Alert areas"));
	Grid1->SetColLabelValue(4, _("Short"));
	Grid1->SetDefaultCellFont( Grid1->GetFont() );
	Grid1->SetDefaultCellTextColour( Grid1->GetForegroundColour() );
	BoxSizer3->Add(Grid1, 1, wxLEFT|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	Panel2->SetSizer(BoxSizer3);
	BoxSizer3->SetSizeHints(this);
	BoxSizer1->Add(Panel2, 5, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&wxInspectionBoardPanel::OnChoiceProductionSelect);
	Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&wxInspectionBoardPanel::OnLastChoiceSelected);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionBoardPanel::onNextResults);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxInspectionBoardPanel::onPreviousResults);
	//*)

	/*
	BoxSizer3->SetSizeHints(this);    /*al posto di:
		//SetSizer(BoxSizer3);
		//Layout(); */

	//now we connect the listener to the boards list
	Connect(ID_GRID1, wxEVT_GRID_CELL_LEFT_CLICK, (wxObjectEventFunction)&wxInspectionBoardPanel::OnBoardSelected);
	Connect(ID_GRID1, wxEVT_GRID_CELL_RIGHT_CLICK, (wxObjectEventFunction)&wxInspectionBoardPanel::OnBoardDelete);
}

wxInspectionBoardPanel::~wxInspectionBoardPanel()
{
	//(*Destroy(wxInspectionBoardPanel)
	//*)
}

bool wxInspectionBoardPanel::Init( SRDatabase* DBRef ) {

	Grid1->SetRowLabelSize(0); //to eliminate the index column

	int width = Grid1->GetSize().x;
	for (int i=0; i< Grid1->GetCols(); i++){
		Grid1->SetColumnWidth(i, width/Grid1->GetCols() );
	}
	//Grid1->SetCellHighlightPenWidth(0);

	DB = DBRef;


	wxArrayString comboLabelsLast;
	comboLabelsLast.Add(_("10"));
	comboLabelsLast.Add(_("20"));
	comboLabelsLast.Add(_("50"));
	comboLabelsLast.Add(_("100"));
	Choice2->Append(comboLabelsLast);
	Choice2->SetStringSelection("10");

	wxArrayString comboLabels;
	comboLabels.Add("All");
	Choice1->Clear();
	//Choice1->Append( DB->ProductionNames );
	Choice1->Append( DB->LoadAllNames() );
	Choice1->Append(comboLabels);
	Choice1->SetStringSelection( DB->ProductionDataS.ProductionName ); //or all?


	boardPerPage=10;
	currentPage=0;
	DB->LoadBoards( DB->ProductionDataS.ProductionName ); //1 means the second entry in comboLabelsLast
	UpdateBoardResults();




}
void wxInspectionBoardPanel::UpdateLists(){
	wxArrayString comboLabels;
	comboLabels.Add("All");
	Choice1->Clear();
	//Choice1->Append( DB->ProductionNames );
	Choice1->Append( DB->LoadAllNames() );
	Choice1->Append(comboLabels);
	Choice1->SetStringSelection( DB->ProductionDataS.ProductionName ); //or all?

	DB->LoadBoards( DB->ProductionDataS.ProductionName ); //1 means the second entry in comboLabelsLast
	UpdateBoardResults();


}




void wxInspectionBoardPanel::OnLastChoiceSelected( wxCommandEvent& event ){


	switch (Choice2->GetCurrentSelection())
	{
		case 0:
			boardPerPage = 10;
			break;
		case 1:
		boardPerPage=20;
		break;
		case 2:
			boardPerPage=50;
			break;
		case 3:
			boardPerPage =100;
			break;
	}
	currentPage = 0;

	UpdateBoardResults();


}

void wxInspectionBoardPanel::OnBoardSelected ( wxGridEvent& event ){

	TransferDataFromWindow();
	 //create an event to deliver to wxMain
	 DB->Selected_row = event.GetRow();
	 DB->SelectedBoardNumber = DB->RecordedBoardstruct[event.GetRow()+currentPage*boardPerPage].BoardNumber;
	 DB->SelectedIDprod = DB->RecordedBoardstruct[event.GetRow() + currentPage*boardPerPage].ID_production;

	 wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
	 e.SetId(  ID_EVENTRECORDS );
	 e.SetInt( ID_EVENTRECORDS );


	 Grid1->SelectRow(DB->Selected_row);

	 //m_cellHighlightROPenWidth = 0;



	 //Grid1->SetCellHighlightColour( wxColor( 120, 200, 15 ) );


	 GetParent()->GetEventHandler()->AddPendingEvent( e );




}

void wxInspectionBoardPanel::UpdateBoardResults()
{
	Grid1->BeginBatch();


	if( boardPerPage != Grid1->GetNumberRows() )
	{

		if( boardPerPage > Grid1->GetNumberRows() )

			Grid1->AppendRows( boardPerPage - Grid1->GetNumberRows() );
		else
		{
			if( boardPerPage == 0 )
				Grid1->DeleteRows( 0, Grid1->GetNumberRows() );
			else
				Grid1->DeleteRows( boardPerPage - 1, Grid1->GetNumberRows() - boardPerPage  );

		}
	}
	Grid1->ClearGrid();
	int cellStart=currentPage*boardPerPage;


	for( int i = currentPage*boardPerPage; i < (currentPage+1)*boardPerPage; i++ )
	{
		if(i>DB->BoardsNum())
			break;


		Grid1->SetCellValue( i-cellStart, COL_Name, DB->RecordedBoardstruct[i].ProductionName.ToAscii()  );

		Grid1->SetCellValue( i-cellStart, COL_NBoard, wxString::Format( "%d", DB->RecordedBoardstruct[i].BoardNumber ) );

		//wxString time= asctime(localtime(&DB->RecordedBoardstruct[i].Time));
		//time=time.substr(7);
		struct tm* c= localtime(&DB->RecordedBoardstruct[i].Time);
		wxString timeStamp;
		timeStamp<< c->tm_mday;
		timeStamp.append("/");
		timeStamp<< (c->tm_mon +1);
		timeStamp.append("  ");
		timeStamp<<c->tm_hour;
		timeStamp.append(":");
		if(c->tm_min < 10){
			timeStamp.append("0");
		}
		timeStamp<<c->tm_min;


		Grid1->SetCellValue( i-cellStart, COL_Date, timeStamp );

		Grid1->SetCellValue( i-cellStart, COL_AlertAreas, wxString::Format( "%d", DB->RecordedBoardstruct[i].WhiteAreas ) );

		Grid1->SetCellValue( i-cellStart, COL_Connected, wxString::Format( "%d", DB->RecordedBoardstruct[i].ConnectedSpots ) );


	}
	Grid1->EndBatch();
}










void wxInspectionBoardPanel::OnChoiceProductionSelect(wxCommandEvent& event)
{


	wxString ProdName = Choice1->GetStringSelection();
	currentPage=0;

	if(DB->LoadBoards( ProdName ) ==SR_ERROR){
					wxMessageBox( "Boards not found", "wxSQLite", wxOK | wxICON_ERROR );
		}
	UpdateBoardResults();
}



void wxInspectionBoardPanel::onNextResults(wxCommandEvent& event)
{
	int res=DB->BoardsNum();
	if(DB->BoardsNum()> (currentPage+1)* boardPerPage)
	{
		currentPage++;
		UpdateBoardResults();
	}

}

void wxInspectionBoardPanel::onPreviousResults(wxCommandEvent& event)
{
	if(currentPage>0)
		{
			currentPage--;
			UpdateBoardResults();
		}
}

void wxInspectionBoardPanel::SelectFirstBoard(){
	 DB->Selected_row = 0;
	 DB->SelectedBoardNumber = DB->RecordedBoardstruct[0].BoardNumber;
	 DB->SelectedIDprod = DB->RecordedBoardstruct[0].ID_production;

	 wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
	 e.SetId(  ID_EVENTRECORDS );
	 e.SetInt( ID_EVENTRECORDS );


	 Grid1->SelectRow(DB->Selected_row);


	 GetParent()->GetEventHandler()->AddPendingEvent( e );

}

void wxInspectionBoardPanel::OnBoardDelete(wxGridEvent& event){

	TransferDataFromWindow();
	if( wxMessageBox( MSG_DELETE_RESULT, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, this ) == wxYES )
		{
			DB->DeleteBoardResults(DB->RecordedBoardstruct[event.GetRow() + currentPage*boardPerPage].ID_production, DB->RecordedBoardstruct[event.GetRow()+currentPage*boardPerPage].BoardNumber);

		}

	UpdateLists();

	if(DB->Selected_row == event.GetRow()){
		SelectFirstBoard();
	}


	//SelectFirstBoard();

}

#include "wxOffsetMapsDialog.h"

//(*InternalHeaders(wxOffsetMapsDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/msgdlg.h>
#include "wxMyTextValidator.h"
#include "Messages.h"
#include "GlobalUtils.h"

#define OFFSET_DELTA			0.3

//(*IdInit(wxOffsetMapsDialog)
const long wxOffsetMapsDialog::ID_STATICTEXT1 = wxNewId();
const long wxOffsetMapsDialog::ID_GRID1 = wxNewId();
const long wxOffsetMapsDialog::ID_STATICTEXT2 = wxNewId();
const long wxOffsetMapsDialog::ID_GRID2 = wxNewId();
const long wxOffsetMapsDialog::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxOffsetMapsDialog,wxDialog)
	//(*EventTable(wxOffsetMapsDialog)
	//*)
END_EVENT_TABLE()

wxOffsetMapsDialog::wxOffsetMapsDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxOffsetMapsDialog)
	wxBoxSizer* BoxSizer1;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("X-Offset Map (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer1->Add(StaticText1, 0, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	xOffsetGrid = new wxGrid(this, ID_GRID1, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, _T("ID_GRID1"));
	xOffsetGrid->CreateGrid(15,13);
	xOffsetGrid->SetDefaultColSize(40);
	xOffsetGrid->SetDefaultRowSize(17);
	xOffsetGrid->SetRowLabelSize(0);
	xOffsetGrid->SetColLabelSize(0);
	xOffsetGrid->EnableEditing(true);
	xOffsetGrid->EnableGridLines(true);
	xOffsetGrid->SetDefaultCellFont( xOffsetGrid->GetFont() );
	xOffsetGrid->SetDefaultCellTextColour( xOffsetGrid->GetForegroundColour() );
	BoxSizer1->Add(xOffsetGrid, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Y-Offset Map (mm)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer1->Add(StaticText2, 0, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	yOffsetGrid = new wxGrid(this, ID_GRID2, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, _T("ID_GRID2"));
	yOffsetGrid->CreateGrid(15,13);
	yOffsetGrid->SetDefaultColSize(40);
	yOffsetGrid->SetDefaultRowSize(17);
	yOffsetGrid->SetRowLabelSize(0);
	yOffsetGrid->SetColLabelSize(0);
	yOffsetGrid->EnableEditing(true);
	yOffsetGrid->EnableGridLines(true);
	yOffsetGrid->SetDefaultCellFont( yOffsetGrid->GetFont() );
	yOffsetGrid->SetDefaultCellTextColour( yOffsetGrid->GetForegroundColour() );
	BoxSizer1->Add(yOffsetGrid, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	closeBtn = new wxButton(this, ID_BUTTON1, _("Close"), wxDefaultPosition, wxSize(75,25), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer1->Add(closeBtn, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_GRID1,wxEVT_GRID_CELL_CHANGE,(wxObjectEventFunction)&wxOffsetMapsDialog::OnxOffsetGridCellChange);
	Connect(ID_GRID2,wxEVT_GRID_CELL_CHANGE,(wxObjectEventFunction)&wxOffsetMapsDialog::OnyOffsetGridCellChange);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxOffsetMapsDialog::OncloseBtnClick);
	//*)

	// set controls best size
	xOffsetGrid->SetMinSize( xOffsetGrid->GetBestSize() );
	yOffsetGrid->SetMinSize( yOffsetGrid->GetBestSize() );

	// set controls props
	xOffsetGrid->EnableDragRowSize( false );
	xOffsetGrid->EnableDragColSize( false );
	yOffsetGrid->EnableDragRowSize( false );
	yOffsetGrid->EnableDragColSize( false );
	xOffsetGrid->EnableDragCell( true );
	yOffsetGrid->EnableDragCell( true );

	GetSizer()->Fit(this);
	Center();
}

wxOffsetMapsDialog::~wxOffsetMapsDialog()
{
	//(*Destroy(wxOffsetMapsDialog)
	//*)
}

//----------------------------------------------------------------------------------
// Init
// Inizializza il controllo
//----------------------------------------------------------------------------------
int wxOffsetMapsDialog::Init( SRDatabase* DBRef, int mode )
{
	DB = DBRef;
	modeView = mode;

	isChanged = false;

	for( int i = 0, r = DB->MachineParamsS.OffsetPointsNumY - 1; r >= 0; r-- )
	{
		for( int c = 0; c < DB->MachineParamsS.OffsetPointsNumX; c++, i++ )
		{
			xOffsetGrid->SetColFormatFloat( c, 4, 3 );
			yOffsetGrid->SetColFormatFloat( c, 4, 3 );

			switch( modeView )
			{
				case OFFSET_VIEW_MAP:
					xData = DB->OffsetPointsS[i].X;
					yData = DB->OffsetPointsS[i].Y;
				break;

				case OFFSET_VIEW_CHECK:
					xData = DB->OffsetCheckPointsS[i].X;
					yData = DB->OffsetCheckPointsS[i].Y;
				break;

				case OFFSET_VIEW_DELTA:
					xData = DB->OffsetPointsS[i].X - DB->OffsetCheckPointsS[i].X;
					yData = DB->OffsetPointsS[i].Y - DB->OffsetCheckPointsS[i].Y;
				break;
			}
			xOffsetGrid->SetCellValue( r, c, wxString::Format( "%.3f", xData ) );
			yOffsetGrid->SetCellValue( r, c, wxString::Format( "%.3f", yData ) );

			xOffsetGrid->SetCellEditor( r, c, new wxGridCellFloatEditor( 4, 3 ) );
			yOffsetGrid->SetCellEditor( r, c, new wxGridCellFloatEditor( 4, 3 ) );
		}
	}

	FillWithGradient();
	return SR_OK;
}

//----------------------------------------------------------------------------------
// GetScaledColor
// 
//----------------------------------------------------------------------------------
wxColour wxOffsetMapsDialog::GetScaledColor( float val, float min, float max )
{
	int r, g, b;
	float value = MID( min, val, max );
	float mid = ( max + min ) / 2.0;
	float m = MIN(min, -0.001); //per evitare lo zero...
	float M = MAX(max, 0.001); //per evitare lo zero...

	if( value <= 0 )
	{
		r = 0;
		g = 255 * (1 - ( value*0.3 / m ) );
		b = 255.0 * ( value / m );
	}
	else
	{
		r = 255.0 * ( value / M );
		g = 255 * (1 - ( value*0.3 / M ) );
		b = 0;
	}

	return wxColour( r, g, b );
}

//----------------------------------------------------------------------------------
// FillWithGradient
// 
//----------------------------------------------------------------------------------
void wxOffsetMapsDialog::FillWithGradient()
{
	float xmin = 999.0, xmax = -999.0, ymin = 999.0, ymax = -999.0;

	for( int i = 0, r = DB->MachineParamsS.OffsetPointsNumY - 1; r >= 0; r-- )
	{
		for( int c = 0; c < DB->MachineParamsS.OffsetPointsNumX; c++, i++ )
		{
			switch( modeView )
			{
				case OFFSET_VIEW_MAP:
					xData = DB->OffsetPointsS[i].X;
					yData = DB->OffsetPointsS[i].Y;
				break;

				case OFFSET_VIEW_CHECK:
					xData = DB->OffsetCheckPointsS[i].X;
					yData = DB->OffsetCheckPointsS[i].Y;
				break;

				case OFFSET_VIEW_DELTA:
					xData = DB->OffsetPointsS[i].X - DB->OffsetCheckPointsS[i].X;
					yData = DB->OffsetPointsS[i].Y - DB->OffsetCheckPointsS[i].Y;
				break;
			}
			if( xData > xmax )
				xmax = xData;
			if( xData < xmin )
				xmin = xData;
			if( yData > ymax )
				ymax = yData;
			if( yData < ymin )
				ymin = yData;
		}
	}

	for( int i = 0, r = DB->MachineParamsS.OffsetPointsNumY - 1; r >= 0; r-- )
	{
		for( int c = 0; c < DB->MachineParamsS.OffsetPointsNumX; c++, i++ )
		{
			switch( modeView )
			{
				case OFFSET_VIEW_MAP:
					xData = DB->OffsetPointsS[i].X;
					yData = DB->OffsetPointsS[i].Y;
				break;

				case OFFSET_VIEW_CHECK:
					xData = DB->OffsetCheckPointsS[i].X;
					yData = DB->OffsetCheckPointsS[i].Y;
				break;

				case OFFSET_VIEW_DELTA:
					xData = DB->OffsetPointsS[i].X - DB->OffsetCheckPointsS[i].X;
					yData = DB->OffsetPointsS[i].Y - DB->OffsetCheckPointsS[i].Y;
				break;
			}

			xOffsetGrid->SetCellBackgroundColour( r, c, GetScaledColor( xData, xmin, xmax ) );
			yOffsetGrid->SetCellBackgroundColour( r, c, GetScaledColor( yData, ymin, ymax ) );
		}
	}

	xOffsetGrid->Refresh();
	yOffsetGrid->Refresh();
}

void wxOffsetMapsDialog::OncloseBtnClick(wxCommandEvent& event)
{
	if( isChanged )
	{
		switch( modeView )
		{
			case OFFSET_VIEW_MAP:
				if( wxMessageBox( MSG_SAVE, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, GetParent() ) == wxYES )
					DB->SaveOffsetPoints();
				else
					DB->LoadOffsetPoints();
			break;

			case OFFSET_VIEW_CHECK:
				if( wxMessageBox( MSG_SAVE, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, GetParent() ) == wxYES )
					DB->SaveOffsetCheckPoints();
				else
					DB->LoadOffsetCheckPoints();
			break;

			default:
			break;
		}
	}

	EndModal( 0 );
}

void wxOffsetMapsDialog::OnxOffsetGridCellChange(wxGridEvent& event)
{
	double tmp;
	xOffsetGrid->GetCellValue( event.GetRow(), event.GetCol() ).ToDouble( &tmp );

	int c = event.GetCol();
	int r = DB->MachineParamsS.OffsetPointsNumY - 1 - event.GetRow();
	switch( modeView )
	{
		case OFFSET_VIEW_MAP:
			DB->OffsetPointsS[r * DB->MachineParamsS.OffsetPointsNumX + c].X = tmp;
			isChanged = true;
		break;

		case OFFSET_VIEW_CHECK:
			DB->OffsetCheckPointsS[r * DB->MachineParamsS.OffsetPointsNumX + c].X = tmp;
			isChanged = true;
		break;

		default:
			isChanged = false;
		break;
	}

	FillWithGradient();
}

void wxOffsetMapsDialog::OnyOffsetGridCellChange(wxGridEvent& event)
{
	double tmp;
	yOffsetGrid->GetCellValue( event.GetRow(), event.GetCol() ).ToDouble( &tmp );

	int c = event.GetCol();
	int r = DB->MachineParamsS.OffsetPointsNumY - 1 - event.GetRow();
	switch( modeView )
	{
		case OFFSET_VIEW_MAP:
			DB->OffsetPointsS[r * DB->MachineParamsS.OffsetPointsNumX + c].Y = tmp;
			isChanged = true;
		break;

		case OFFSET_VIEW_CHECK:
			DB->OffsetCheckPointsS[r * DB->MachineParamsS.OffsetPointsNumX + c].Y = tmp;
			isChanged = true;
		break;

		default:
			isChanged = false;
		break;
	}

	FillWithGradient();
}

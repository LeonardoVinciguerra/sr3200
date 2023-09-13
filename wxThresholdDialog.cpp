#include "wxThresholdDialog.h"

//(*InternalHeaders(wxThresholdDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/dcmemory.h>
#include "GlobalUtils.h"

#define HIST_MARGIN			5


//(*IdInit(wxThresholdDialog)
const long wxThresholdDialog::ID_STATICTEXT1 = wxNewId();
const long wxThresholdDialog::ID_CUSTOM1 = wxNewId();
const long wxThresholdDialog::ID_STATICLINE1 = wxNewId();
const long wxThresholdDialog::ID_STATICTEXT2 = wxNewId();
const long wxThresholdDialog::ID_BUTTON1 = wxNewId();
const long wxThresholdDialog::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxThresholdDialog,wxDialog)
	//(*EventTable(wxThresholdDialog)
	//*)
END_EVENT_TABLE()

wxThresholdDialog::wxThresholdDialog(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(wxThresholdDialog)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;
	
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	thrText = new wxStaticText(this, ID_STATICTEXT1, _("Threshold"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer3->Add(thrText, 0, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 10);
	BoxSizer1->Add(BoxSizer3, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	histPicture = new wxPictureBox(this,ID_CUSTOM1,wxDefaultPosition,wxSize(320,257));
	BoxSizer1->Add(histPicture, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	staticLine = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	BoxSizer1->Add(staticLine, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	selThrText = new wxStaticText(this, ID_STATICTEXT2, _("Selected threshold"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer2->Add(selThrText, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	okBtn = new wxButton(this, ID_BUTTON1, _("Ok"), wxDefaultPosition, wxSize(75,25), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer2->Add(okBtn, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cancelBtn = new wxButton(this, ID_BUTTON2, _("Cancel"), wxDefaultPosition, wxSize(75,25), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer2->Add(cancelBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxThresholdDialog::OnokBtnClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxThresholdDialog::OncancelBtnClick);
	//*)

	data = 0;
	dataNum = 0;
	selectedThr = -1;

	//
	histPicture->SetImageDisplacement( -histPicture->GetControlBorder() );
	histPicture->ConnectMouseEvent( wxEVT_MOTION, wxStaticCastEvent( wxMouseEventFunction, &wxThresholdDialog::HistOnMove ), this );
	histPicture->ConnectMouseEvent( wxEVT_LEAVE_WINDOW, wxStaticCastEvent( wxMouseEventFunction, &wxThresholdDialog::HistOnLeave ), this );
	histPicture->ConnectMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &wxThresholdDialog::HistOnLeftClick ), this );

	selThrText->SetLabel( _("Selected threshold") + wxString(": -") );
	okBtn->Enable( false );

	Center();
	
	histBmp = new wxBitmap( histPicture->GetSize().x - 2*histPicture->GetControlBorder(), histPicture->GetSize().y - 2*histPicture->GetControlBorder() );
}

wxThresholdDialog::~wxThresholdDialog()
{
	//(*Destroy(wxThresholdDialog)
	//*)
}

//----------------------------------------------------------------------------------
// SetScanLine
//----------------------------------------------------------------------------------
void wxThresholdDialog::SetScanLine( unsigned char* dataRef, unsigned short dataLen )
{
	data = dataRef;
	dataNum = dataLen;

	// draw hist
	wxMemoryDC dc;
	dc.SelectObject( *histBmp );
	DrawHist( dc );
	dc.SelectObject( wxNullBitmap );
	//
	histPicture->SetImage( *histBmp );
}

//-----------------------------------------------------------------------------
// DrawCursor
//-----------------------------------------------------------------------------
void wxThresholdDialog::DrawCursor( int curPos )
{
	wxBitmap img( *histBmp );

	wxMemoryDC dc;
	dc.SelectObject( img );

	if( selectedThr != -1 )
	{
		dc.SetPen( *wxGREY_PEN );
		dc.DrawLine( 0, dc.GetSize().y - selectedThr, dc.GetSize().x, dc.GetSize().y - selectedThr );
	}

	if( curPos != -1 )
	{
		dc.SetPen( wxPen( wxColour( 255, 128, 0 ) ) );
		dc.DrawLine( 0, curPos, dc.GetSize().x, curPos );

		thrText->SetLabel( _("Threshold") + wxString::Format(": %d", dc.GetSize().y - curPos ) );
	}

	dc.SelectObject( wxNullBitmap );
	histPicture->SetImage( img );
}

//----------------------------------------------------------------------------------
// DrawHist
//----------------------------------------------------------------------------------
void wxThresholdDialog::DrawHist( wxDC& dc )
{
	// set dc
	dc.SetPen( *wxWHITE );
	dc.SetBrush( *wxWHITE_BRUSH );

	// draw the rectangle
	dc.DrawRectangle( 0, 0, dc.GetSize().x, dc.GetSize().y );

	//
	float dataInc = (dataNum - 1.0f) / (dc.GetSize().x - 1.0f);
	float xInc;

	if( dataInc >= 1.0f )
	{
		xInc = 1.0f;
	}
	else
	{
		dataInc = 1.0f;
		xInc = dc.GetSize().x / (dataNum - 1.0f);
	}

	wxPoint* points = new wxPoint[dataNum];
	float x = 0.0f;
	int pointsIndex = 0;
	float dataIndex = 0.0f;

	while( dataIndex < dataNum && pointsIndex < dataNum )
	{
		points[pointsIndex].x = myLRound( x );
		points[pointsIndex].y = dc.GetSize().y - data[myLRound(dataIndex)];

		dataIndex += dataInc;
		x += xInc;

		pointsIndex++;
	}
	//
	while( pointsIndex < dataNum )
	{
		points[pointsIndex] = points[pointsIndex - 1];
		pointsIndex++;
	}

	//
	dc.SetPen( wxPen( *wxBLUE ) );
	dc.DrawLines( dataNum, points );

	delete [] points;
}

//----------------------------------------------------------------------------------
// HistOnMove
// Mouse move event
//----------------------------------------------------------------------------------
void wxThresholdDialog::HistOnMove( wxMouseEvent& e )
{
	DrawCursor( e.GetPosition().y );
}

//----------------------------------------------------------------------------------
// HistOnLeave
// Mouse leave event
//----------------------------------------------------------------------------------
void wxThresholdDialog::HistOnLeave( wxMouseEvent& e )
{
	thrText->SetLabel( _("Threshold") + wxString(": -") );
	DrawCursor( -1 );
}

//----------------------------------------------------------------------------------
// HistOnLeftClick
// Mouse left click event
//----------------------------------------------------------------------------------
void wxThresholdDialog::HistOnLeftClick( wxMouseEvent& e )
{
	selectedThr = histBmp->GetHeight() - e.GetPosition().y;
	selThrText->SetLabel( _("Selected threshold") + wxString::Format(": %d", selectedThr ) );
	DrawCursor( e.GetPosition().y );

	okBtn->Enable( true );
}



	//------------//
	//   Events   //
	//------------//

void wxThresholdDialog::OnokBtnClick(wxCommandEvent& event)
{
	EndModal( wxOK );
}

void wxThresholdDialog::OncancelBtnClick(wxCommandEvent& event)
{
	EndModal( wxCANCEL );
}

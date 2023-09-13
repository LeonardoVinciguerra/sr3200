#include "images/png_images.h"

#include "wxSR3200App.h"
#include "wxMainWin.h"

//(*InternalHeaders(wxMainWin)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/msgdlg.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include <wx/choicdlg.h>
#include <wx/filedlg.h>
#include "GlobalEnum.h"
#include "GlobalUtils.h"
#include "Messages.h"
#include "wxOffDialog.h"
#include "wxSwUpdate.h"
#include "wxWaitDialog.h"
#include <wx/process.h>
#include "wxMyPopup.h"
#include "wxInspectionPopup.h"


#define TIMER_EXPIRE_TIME	5000 //msec


//(*IdInit(wxMainWin)
const long wxMainWin::ID_STATICTEXT1 = wxNewId();
const long wxMainWin::ID_PANEL9 = wxNewId();
const long wxMainWin::ID_STATICTEXT7 = wxNewId();
const long wxMainWin::ID_PANEL10 = wxNewId();
const long wxMainWin::ID_STATICTEXT8 = wxNewId();
const long wxMainWin::ID_PANEL11 = wxNewId();
const long wxMainWin::ID_STATICTEXT10 = wxNewId();
const long wxMainWin::ID_BITMAPBUTTON1 = wxNewId();
const long wxMainWin::ID_BITMAPBUTTON4 = wxNewId();
const long wxMainWin::ID_BITMAPBUTTON10 = wxNewId();
const long wxMainWin::ID_BITMAPBUTTON3 = wxNewId();
const long wxMainWin::ID_BITMAPBUTTON11 = wxNewId();
const long wxMainWin::ID_BITMAPBUTTON12 = wxNewId();
const long wxMainWin::ID_BITMAPBUTTON2 = wxNewId();
const long wxMainWin::ID_BITMAPBUTTON9 = wxNewId();
const long wxMainWin::ID_STATICTEXT2 = wxNewId();
const long wxMainWin::ID_STATICTEXT6 = wxNewId();
const long wxMainWin::ID_STATICTEXT3 = wxNewId();
const long wxMainWin::ID_STATICTEXT9 = wxNewId();
const long wxMainWin::ID_STATICTEXT4 = wxNewId();
const long wxMainWin::ID_STATICTEXT11 = wxNewId();
const long wxMainWin::ID_STATICTEXT5 = wxNewId();
const long wxMainWin::ID_PANEL12 = wxNewId();
const long wxMainWin::ID_BUTTON25 = wxNewId();
const long wxMainWin::ID_BUTTON1 = wxNewId();
const long wxMainWin::ID_BUTTON3 = wxNewId();
const long wxMainWin::ID_BUTTON4 = wxNewId();
const long wxMainWin::ID_BUTTON26 = wxNewId();
const long wxMainWin::ID_BUTTON27 = wxNewId();
const long wxMainWin::ID_BUTTON31 = wxNewId();
const long wxMainWin::ID_BUTTON37 = wxNewId();
const long wxMainWin::ID_BUTTON32 = wxNewId();
const long wxMainWin::ID_BUTTON2 = wxNewId();
const long wxMainWin::ID_BUTTON33 = wxNewId();
const long wxMainWin::ID_BUTTON34 = wxNewId();
const long wxMainWin::ID_BUTTON35 = wxNewId();
const long wxMainWin::ID_BUTTON5 = wxNewId();
const long wxMainWin::ID_BUTTON36 = wxNewId();
const long wxMainWin::ID_BUTTON38 = wxNewId();
const long wxMainWin::ID_BUTTON39 = wxNewId();
const long wxMainWin::ID_BUTTON40 = wxNewId();
const long wxMainWin::ID_PANEL13 = wxNewId();
const long wxMainWin::ID_CUSTOM3 = wxNewId();
const long wxMainWin::ID_BITMAPBUTTON5 = wxNewId();
const long wxMainWin::ID_BITMAPBUTTON6 = wxNewId();
const long wxMainWin::ID_BITMAPBUTTON7 = wxNewId();
const long wxMainWin::ID_BITMAPBUTTON8 = wxNewId();
const long wxMainWin::ID_CUSTOM1 = wxNewId();
const long wxMainWin::ID_PANEL8 = wxNewId();
const long wxMainWin::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxMainWin,wxDialog)
	//(*EventTable(wxMainWin)
	//*)
END_EVENT_TABLE()

wxMainWin::wxMainWin(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxMainWin)
	wxBoxSizer* BoxSizer19;
	wxBoxSizer* BoxSizer15;
	wxBoxSizer* BoxSizer20;
	wxBoxSizer* BoxSizer21;
	wxBoxSizer* BoxSizer13;
	wxBoxSizer* BoxSizer23;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer11;
	wxBoxSizer* BoxSizer16;
	wxBoxSizer* BoxSizer12;
	wxBoxSizer* BoxSizer18;
	wxBoxSizer* footerSizer;
	wxBoxSizer* BoxSizer14;
	wxGridSizer* GridSizer1;
	wxBoxSizer* BoxSizer17;
	wxBoxSizer* BoxSizer24;
	wxBoxSizer* BoxSizer26;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer9;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxBoxSizer* BoxSizer22;

	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRESIZE_BORDER, _T("wxID_ANY"));
	SetMaxSize(wxSize(1920,1080));
	wxFont thisFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
	SetFont(thisFont);
	wxSizerMain = new wxBoxSizer(wxVERTICAL);
	headerSizer = new wxBoxSizer(wxHORIZONTAL);
	Panel3 = new wxPanel(this, ID_PANEL9, wxDefaultPosition, wxSize(110,33), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL9"));
	Panel3->SetMinSize(wxSize(110,33));
	Panel3->SetBackgroundColour(wxColour(120,200,15));
	BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
	StaticText4 = new wxStaticText(Panel3, ID_STATICTEXT1, _("SR3200"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT1"));
	wxFont StaticText4Font(14,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Franklin Gothic Medium"),wxFONTENCODING_DEFAULT);
	StaticText4->SetFont(StaticText4Font);
	BoxSizer14->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer9->Add(BoxSizer14, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	Panel3->SetSizer(BoxSizer9);
	//SetSizer(BoxSizer9);
	//Layout();
	headerSizer->Add(Panel3, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	Panel4 = new wxPanel(this, ID_PANEL10, wxDefaultPosition, wxSize(220,33), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL10"));
	Panel4->SetBackgroundColour(wxColour(255,255,255));
	BoxSizer15 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer16 = new wxBoxSizer(wxHORIZONTAL);
	StaticText5 = new wxStaticText(Panel4, ID_STATICTEXT7, _("TWS Automation"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT7"));
	wxFont StaticText5Font(14,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Franklin Gothic Medium"),wxFONTENCODING_DEFAULT);
	StaticText5->SetFont(StaticText5Font);
	BoxSizer16->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer15->Add(BoxSizer16, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	Panel4->SetSizer(BoxSizer15);
	//SetSizer(BoxSizer15);
	//Layout();
	headerSizer->Add(Panel4, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	Panel5 = new wxPanel(this, ID_PANEL11, wxDefaultPosition, wxSize(100,33), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL11"));
	Panel5->SetBackgroundColour(wxColour(255,0,0));
	BoxSizer17 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer18 = new wxBoxSizer(wxHORIZONTAL);
	verLabel = new wxStaticText(Panel5, ID_STATICTEXT8, _("label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	wxFont verLabelFont(14,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Franklin Gothic Medium"),wxFONTENCODING_DEFAULT);
	verLabel->SetFont(verLabelFont);
	BoxSizer18->Add(verLabel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer17->Add(BoxSizer18, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	BoxSizer17->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel5->SetSizer(BoxSizer17);
	//SetSizer(BoxSizer17);
	//Layout();
	headerSizer->Add(Panel5, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	titleSizer = new wxBoxSizer(wxHORIZONTAL);
	headerLabel = new wxStaticText(this, ID_STATICTEXT10, _("TWS Automation"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	wxFont headerLabelFont(14,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Franklin Gothic Medium"),wxFONTENCODING_DEFAULT);
	headerLabel->SetFont(headerLabelFont);
	titleSizer->Add(headerLabel, 0, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 50);
	menuBtn = new wxBitmapButton(this, ID_BITMAPBUTTON1, wxNullBitmap, wxDefaultPosition, wxSize(34,34), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	menuBtn->SetDefault();
	titleSizer->Add(menuBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	headerSizer->Add(titleSizer, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	wxSizerMain->Add(headerSizer, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	menuSizer = new wxBoxSizer(wxVERTICAL);
	menuSizer->Add(-1,-1,0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel6 = new wxPanel(this, ID_PANEL12, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL12"));
	Panel6->SetBackgroundColour(wxColour(192,192,192));
	BoxSizer19 = new wxBoxSizer(wxVERTICAL);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	BitmapButton1 = new wxBitmapButton(Panel6, ID_BITMAPBUTTON4, wxNullBitmap, wxDefaultPosition, wxSize(190,130), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON4"));
	BitmapButton1->SetMaxSize(wxSize(190,130));
	BoxSizer1->Add(BitmapButton1, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	BitmapButton5 = new wxBitmapButton(Panel6, ID_BITMAPBUTTON10, wxNullBitmap, wxDefaultPosition, wxSize(190,130), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON10"));
	BitmapButton5->SetDefault();
	BitmapButton5->SetMaxSize(wxSize(190,130));
	BoxSizer1->Add(BitmapButton5, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	BitmapButton2 = new wxBitmapButton(Panel6, ID_BITMAPBUTTON3, wxNullBitmap, wxDefaultPosition, wxSize(190,130), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
	BitmapButton2->SetDefault();
	BitmapButton2->SetMaxSize(wxSize(190,130));
	BoxSizer1->Add(BitmapButton2, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	BitmapButton6 = new wxBitmapButton(Panel6, ID_BITMAPBUTTON11, wxNullBitmap, wxDefaultPosition, wxSize(190,130), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON11"));
	BitmapButton6->SetDefault();
	BitmapButton6->SetMaxSize(wxSize(190,130));
	BoxSizer1->Add(BitmapButton6, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	BitmapButton7 = new wxBitmapButton(Panel6, ID_BITMAPBUTTON12, wxNullBitmap, wxDefaultPosition, wxSize(190,130), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON12"));
	BitmapButton7->SetDefault();
	BitmapButton7->SetMaxSize(wxSize(190,130));
	BoxSizer1->Add(BitmapButton7, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	BitmapButton3 = new wxBitmapButton(Panel6, ID_BITMAPBUTTON2, wxNullBitmap, wxDefaultPosition, wxSize(190,130), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
	BitmapButton3->SetMaxSize(wxSize(190,130));
	BoxSizer1->Add(BitmapButton3, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	BitmapButton4 = new wxBitmapButton(Panel6, ID_BITMAPBUTTON9, wxNullBitmap, wxDefaultPosition, wxSize(190,130), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON9"));
	BitmapButton4->SetDefault();
	BitmapButton4->SetMaxSize(wxSize(190,130));
	BoxSizer1->Add(BitmapButton4, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	BoxSizer19->Add(BoxSizer1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1 = new wxGridSizer(0, 7, 0, 0);
	StaticText1 = new wxStaticText(Panel6, ID_STATICTEXT2, _("Production Params"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	wxFont StaticText1Font(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Franklin Gothic Medium"),wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	GridSizer1->Add(StaticText1, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(Panel6, ID_STATICTEXT6, _("Load/Unload Board"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	wxFont StaticText7Font(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Franklin Gothic Medium"),wxFONTENCODING_DEFAULT);
	StaticText7->SetFont(StaticText7Font);
	GridSizer1->Add(StaticText7, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(Panel6, ID_STATICTEXT3, _("Alignment"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	wxFont StaticText2Font(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Franklin Gothic Medium"),wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	GridSizer1->Add(StaticText2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(Panel6, ID_STATICTEXT9, _("Pins Placement"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	wxFont StaticText8Font(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Franklin Gothic Medium"),wxFONTENCODING_DEFAULT);
	StaticText8->SetFont(StaticText8Font);
	GridSizer1->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(Panel6, ID_STATICTEXT4, _("Inspection Sites"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	wxFont StaticText3Font(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Franklin Gothic Medium"),wxFONTENCODING_DEFAULT);
	StaticText3->SetFont(StaticText3Font);
	GridSizer1->Add(StaticText3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(Panel6, ID_STATICTEXT11, _("Printing"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	wxFont StaticText9Font(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Franklin Gothic Medium"),wxFONTENCODING_DEFAULT);
	StaticText9->SetFont(StaticText9Font);
	GridSizer1->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(Panel6, ID_STATICTEXT5, _("SPI"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	wxFont StaticText6Font(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Franklin Gothic Medium"),wxFONTENCODING_DEFAULT);
	StaticText6->SetFont(StaticText6Font);
	GridSizer1->Add(StaticText6, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer19->Add(GridSizer1, 0, wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel6->SetSizer(BoxSizer19);
	BoxSizer19->Fit(Panel6);
	BoxSizer19->SetSizeHints(Panel6);
	menuSizer->Add(Panel6, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	menuSizer->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer20 = new wxBoxSizer(wxHORIZONTAL);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Configuration && Utilities"));
	BoxSizer21 = new wxBoxSizer(wxHORIZONTAL);
	Button5 = new wxButton(this, ID_BUTTON25, _("General\nParams"), wxDefaultPosition, wxSize(100,70), 0, wxDefaultValidator, _T("ID_BUTTON25"));
	BoxSizer21->Add(Button5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button1 = new wxButton(this, ID_BUTTON1, _("Motors Status"), wxDefaultPosition, wxSize(100,70), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer21->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(BoxSizer21, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer22 = new wxBoxSizer(wxHORIZONTAL);
	Button2 = new wxButton(this, ID_BUTTON3, _("Paste\nConditioning"), wxDefaultPosition, wxSize(100,70), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	BoxSizer22->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button3 = new wxButton(this, ID_BUTTON4, _("Cleaning\nCycle"), wxDefaultPosition, wxSize(100,70), 0, wxDefaultValidator, _T("ID_BUTTON4"));
	BoxSizer22->Add(Button3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(BoxSizer22, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer24 = new wxBoxSizer(wxHORIZONTAL);
	Button6 = new wxButton(this, ID_BUTTON26, _("Advanced\nParams"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON26"));
	BoxSizer24->Add(Button6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button7 = new wxButton(this, ID_BUTTON27, _("Motors Data"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON27"));
	BoxSizer24->Add(Button7, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button8 = new wxButton(this, ID_BUTTON31, _("Hardware\nTest"), wxDefaultPosition, wxSize(100,70), 0, wxDefaultValidator, _T("ID_BUTTON31"));
	BoxSizer24->Add(Button8, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button14 = new wxButton(this, ID_BUTTON37, _("Demo"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON37"));
	BoxSizer24->Add(Button14, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(BoxSizer24, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer23 = new wxBoxSizer(wxHORIZONTAL);
	Button9 = new wxButton(this, ID_BUTTON32, _("Plate Height"), wxDefaultPosition, wxSize(100,70), 0, wxDefaultValidator, _T("ID_BUTTON32"));
	BoxSizer23->Add(Button9, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	convEdgeBtn = new wxButton(this, ID_BUTTON2, _("Conveyor Edge"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer23->Add(convEdgeBtn, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button10 = new wxButton(this, ID_BUTTON33, _("Camera Focus"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON33"));
	BoxSizer23->Add(Button10, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button11 = new wxButton(this, ID_BUTTON34, _("Camera Scale"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON34"));
	BoxSizer23->Add(Button11, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button12 = new wxButton(this, ID_BUTTON35, _("Camera Offset"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON35"));
	BoxSizer23->Add(Button12, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CameraZeroButton = new wxButton(this, ID_BUTTON5, _("Camera Zero"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	BoxSizer23->Add(CameraZeroButton, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button13 = new wxButton(this, ID_BUTTON36, _("Vision"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON36"));
	BoxSizer23->Add(Button13, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(BoxSizer23, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	Panel7 = new wxPanel(this, ID_PANEL13, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL13"));
	Panel7->SetBackgroundColour(wxColour(192,192,192));
	BoxSizer26 = new wxBoxSizer(wxHORIZONTAL);
	backupBtn = new wxButton(Panel7, ID_BUTTON38, _("Backup DB"), wxDefaultPosition, wxSize(100,70), 0, wxDefaultValidator, _T("ID_BUTTON38"));
	BoxSizer26->Add(backupBtn, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	restoreBtn = new wxButton(Panel7, ID_BUTTON39, _("Restore DB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON39"));
	BoxSizer26->Add(restoreBtn, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	updateBtn = new wxButton(Panel7, ID_BUTTON40, _("Update SW"), wxDefaultPosition, wxSize(100,-1), 0, wxDefaultValidator, _T("ID_BUTTON40"));
	BoxSizer26->Add(updateBtn, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel7->SetSizer(BoxSizer26);
	BoxSizer26->Fit(Panel7);
	BoxSizer26->SetSizeHints(Panel7);
	StaticBoxSizer1->Add(Panel7, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer20->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	mainImage = new wxPictureBox(this,ID_CUSTOM3,wxDefaultPosition,wxSize(550,400));
	BoxSizer20->Add(mainImage, 0, wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	menuSizer->Add(BoxSizer20, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	menuSizer->Add(-1,-1,2, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerMain->Add(menuSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	clientLRSizer = new wxBoxSizer(wxHORIZONTAL);
	wxSizerClientL = new wxBoxSizer(wxHORIZONTAL);
	clientLRSizer->Add(wxSizerClientL, 0, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
	wxSizerClientR = new wxBoxSizer(wxVERTICAL);
	clientLRSizer->Add(wxSizerClientR, 0, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
	wxSizerMain->Add(clientLRSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	clientProductionSizer = new wxBoxSizer(wxVERTICAL);
	wxSizerMain->Add(clientProductionSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	clientParamsSizer = new wxBoxSizer(wxHORIZONTAL);
	wxSizerMain->Add(clientParamsSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	footerSizer = new wxBoxSizer(wxHORIZONTAL);
	PanelFooter = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxNO_BORDER, _T("ID_PANEL1"));
	PanelFooter->SetMaxSize(wxSize(870,110));
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	toolBox = new wxPanel(PanelFooter, ID_PANEL8, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL8"));
	toolBox->SetBackgroundColour(wxColour(128,128,128));
	BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer12 = new wxBoxSizer(wxVERTICAL);
	onBtn = new wxBitmapButton(toolBox, ID_BITMAPBUTTON5, wxNullBitmap, wxDefaultPosition, wxSize(48,48), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON5"));
	onBtn->SetDefault();
	BoxSizer12->Add(onBtn, 0, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	offBtn = new wxBitmapButton(toolBox, ID_BITMAPBUTTON6, wxNullBitmap, wxDefaultPosition, wxSize(48,48), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON6"));
	offBtn->SetDefault();
	BoxSizer12->Add(offBtn, 0, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer11->Add(BoxSizer12, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	BoxSizer13 = new wxBoxSizer(wxVERTICAL);
	homeBtn = new wxBitmapButton(toolBox, ID_BITMAPBUTTON7, wxNullBitmap, wxDefaultPosition, wxSize(48,48), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON7"));
	homeBtn->SetDefault();
	BoxSizer13->Add(homeBtn, 0, wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	originBtn = new wxBitmapButton(toolBox, ID_BITMAPBUTTON8, wxNullBitmap, wxDefaultPosition, wxSize(48,48), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON8"));
	originBtn->SetDefault();
	BoxSizer13->Add(originBtn, 0, wxTOP|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer11->Add(BoxSizer13, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	messageBox = new wxRichTextCtrl(toolBox,ID_CUSTOM1,_T(""),wxDefaultPosition,wxSize(400,-1),wxRE_READONLY|wxRE_MULTILINE);
	BoxSizer11->Add(messageBox, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	toolBox->SetSizer(BoxSizer11);
	BoxSizer11->Fit(toolBox);
	BoxSizer11->SetSizeHints(toolBox);
	BoxSizer2->Add(toolBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PanelFooter->SetSizer(BoxSizer2);
	BoxSizer2->Fit(PanelFooter);
	BoxSizer2->SetSizeHints(PanelFooter);
	footerSizer->Add(PanelFooter, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxSizerMain->Add(footerSizer, 0, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(wxSizerMain);
	wxSizerMain->Fit(this);
	wxSizerMain->SetSizeHints(this);

	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnmenuBtnClick);
	Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnButton1Click);
	Connect(ID_BITMAPBUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnBitmapButton5Click);
	Connect(ID_BITMAPBUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnButton2Click);
	Connect(ID_BITMAPBUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnBitmapButton6Click);
	Connect(ID_BITMAPBUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnInspectionSitesButtonClick);
	Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnButton3Click);
	Connect(ID_BITMAPBUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnButton4Click);
	Connect(ID_BUTTON25,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnButton5Click);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnButton1Click1);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnButton2Click1);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnButton3Click1);
	Connect(ID_BUTTON26,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnButton6Click);
	Connect(ID_BUTTON27,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnButton7Click);
	Connect(ID_BUTTON31,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnButton8Click);
	Connect(ID_BUTTON37,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnButton14Click);
	Connect(ID_BUTTON32,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnButton9Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnconvEdgeBtnClick);
	Connect(ID_BUTTON33,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnButton10Click);
	Connect(ID_BUTTON34,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnButton11Click);
	Connect(ID_BUTTON35,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnButton12Click);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnCameraZeroButtonClick);
	Connect(ID_BUTTON36,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnButton13Click);
	Connect(ID_BUTTON38,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnbackupBtnClick);
	Connect(ID_BUTTON39,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnrestoreBtnClick);
	Connect(ID_BUTTON40,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnupdateBtnClick);
	Connect(ID_BITMAPBUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnonBtnClick);
	Connect(ID_BITMAPBUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnoffBtnClick);
	Connect(ID_BITMAPBUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnhomeBtnClick);
	Connect(ID_BITMAPBUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxMainWin::OnoriginBtnClick);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&wxMainWin::OnClose);
	//*)

	Connect( wxEVT_COMMAND_BUTTON_CLICKED ,(wxObjectEventFunction)&wxMainWin::OnGUIEvents );

	//Connect( wxEVT_CHAR_HOOK,(wxObjectEventFunction)&wxMainWin::OnCharPressed, NULL, this);
	//SetFocus();

	// init buttons image
	onBtn->SetBitmapDisabled( wxMEMORY_BITMAP( startup ) );
	onBtn->SetBitmapLabel( wxMEMORY_BITMAP( startup_on ) );
	offBtn->SetBitmapDisabled( wxMEMORY_BITMAP( off ) );
	offBtn->SetBitmapLabel( wxMEMORY_BITMAP( off_on ) );
	homeBtn->SetBitmapDisabled( wxMEMORY_BITMAP( home ) );
	homeBtn->SetBitmapLabel( wxMEMORY_BITMAP( home_on ) );
	originBtn->SetBitmapDisabled( wxMEMORY_BITMAP( origins ) );
	originBtn->SetBitmapLabel( wxMEMORY_BITMAP( origins_on ) );
	menuBtn->SetBitmapDisabled( wxMEMORY_BITMAP( abort_small ) );
	menuBtn->SetBitmapLabel( wxMEMORY_BITMAP( abort_small_on ) );
	BitmapButton1->SetBitmapLabel( wxMEMORY_BITMAP( production ) );
	BitmapButton5->SetBitmapLabel( wxMEMORY_BITMAP( pcb ) );
	BitmapButton2->SetBitmapLabel( wxMEMORY_BITMAP( alignment ) );
	BitmapButton3->SetBitmapLabel( wxMEMORY_BITMAP( printing ) );
	BitmapButton4->SetBitmapLabel( wxMEMORY_BITMAP( spi ) );
	BitmapButton6->SetBitmapLabel( wxMEMORY_BITMAP( pins ) );
	BitmapButton7->SetBitmapLabel( wxMEMORY_BITMAP( sites ));

	// init main image
	mainImage->SetImage( wxMEMORY_BITMAP( main ) );

	// init labels
	verLabel->SetLabel( wxString( wxT("ver. ") ) + SW_VERSION );

	// Setup controls and vars
	onBtn->SetToolTip( TOO_ON );
	offBtn->SetToolTip( TOO_OFF );
	originBtn->SetToolTip( TOO_ORIGINS );
	homeBtn->SetToolTip( TOO_HOME );
	menuBtn->SetToolTip( TOO_MENU );
	homeBtn->Enable( false );
	originBtn->Enable( false );
	offBtn->Enable( true );
	onBtn->Enable( true );
	pswL0 = wxT("hwt");
	pswL1 = wxT("l1");
	pswL2 = wxT("l2");
	isPswL0Ok = 0;
	isPswL1Ok = 0;
	isPswL2Ok = 0;
	currentFnc = NULL_FNC;
	standbyBtnEnable = false;
	isBoardMoving = false;
	isCleaning = false;

	// Load config file
	LoadConfig();



	// full screen window
	Maximize( true );
	ShowFullScreen( true );


	// create controls
	CreateMyControls();

	// draw controls on screen
	DrawControls( NULL_FNC );
	Layout();
	wxTheApp->Yield();

	// init database and load data (last opened production)
	DB = new SRDatabase( MACHINE_DB, AUTOspi_DB );
	// init SmartLogger
	smartLogger = new SmartLog( messageBox , DB);

	//Check DB version (load the current machine params)
	DB->LoadMachineParams();
	CheckAndUpdateDB();


	DB->LoadMachineStructsFromDB();
	DB->LoadProductionNames();
	DB->LoadActualProduction();
	DB->LoadProductionStructsFromDB( DB->ActualProductionS.IdProd );



	smartLogger->LogToFileEnable( true );
	// init SRMachine
	SR = new SRMachine( DB, smartLogger, this );
	smartLogger->Write( MACHINE_NAME + wxString( wxT(" ver. ") ) + SW_VERSION );

	smartLogger->Write( MSG_WAITVIDEO );

	wxProcess *process = new wxProcess(wxPROCESS_REDIRECT);
	wxExecute( "./waitdriver.sh", 1, process );

	smartLogger->Write( MSG_VIDEOINITEND );

	//camera->SetPriority(100);
	camera = new wxCameraControl();
	if( camera->Init( SR, this ) )
	{
		// close application
		wxMessageBox( MSG_VIDEOERROR, MACHINE_NAME, wxICON_ERROR | wxOK, this );
		exit( 1 );
	}
	camera->Run();


	//camera->GetColorFrames(8);
	//camera->StartCapture();
	//condition->Wait();



	// If cleaning system is enabled, enable also dedicated button
	if( !SR->DB->MachineParamsS.CleaningInstalled )
		Button3->Enable( false );

	if( !SR->DB->MachineParamsS.CleaningInstalled )
		BitmapButton7->Enable( false );

	// init motors
	SR->InitMotors();

	// Chek if some motor modules are to be disabled
	MACHINE_CONFIG( MACHINE_ENABLE )
		MACHINE_CONFIG( DISABLE_TABLE )
			SR->Table1Motor.motor->DisableDriver( true );
			SR->Table2Motor.motor->DisableDriver( true );
			SR->Table3Motor.motor->DisableDriver( true );
		MACHINE_CONFIG_END

		MACHINE_CONFIG( DISABLE_PLATE )
			SR->PlateMotor.motor->DisableDriver( true );
		MACHINE_CONFIG_END

		MACHINE_CONFIG( DISABLE_CAMERA )
			SR->CamXMotor.motor->DisableDriver( true );
			SR->CamYMotor.motor->DisableDriver( true );
		MACHINE_CONFIG_END

		MACHINE_CONFIG( DISABLE_SQUEEGEES )
			SR->SqueegeesMotor.motor->DisableDriver( true );
		MACHINE_CONFIG_END

		MACHINE_CONFIG( DISABLE_LOADER )
			SR->LoaderMotor.motor->DisableDriver( true );
		MACHINE_CONFIG_END

		MACHINE_CONFIG( DISABLE_LCONVW )
			SR->LConvWidthMotor.motor->DisableDriver( true );
		MACHINE_CONFIG_END

		MACHINE_CONFIG( DISABLE_LCONVF )
			SR->LConvFeedMotor.motor->DisableDriver( true );
		MACHINE_CONFIG_END

		MACHINE_CONFIG( DISABLE_LCONVP )
			SR->LConvPushMotor.motor->DisableDriver( true );
		MACHINE_CONFIG_END

		MACHINE_CONFIG( DISABLE_CCONVW )
			SR->CConvWidthMotor.motor->DisableDriver( true );
		MACHINE_CONFIG_END

		MACHINE_CONFIG( DISABLE_CCONVF )
			SR->CConvFeedMotor.motor->DisableDriver( true );
		MACHINE_CONFIG_END

		if( !SR->DB->MachineParamsS.CleaningInstalled )
			SR->CleanerMotor.motor->DisableDriver( true );

		/* reduce outputs for semaphore and buzzer
		if( SR->SetOutputReduction( OUTPUT_SEMAPHORE_RED, REDUCTION_OUTPUTS_PLATE ) == SR_ERROR )
			return SR_ERROR;
		if( SR->SetOutputReduction( OUTPUT_SEMAPHORE_YELLOW, REDUCTION_OUTPUTS_PLATE ) == SR_ERROR )
			return SR_ERROR;
		if( SR->SetOutputReduction( OUTPUT_SEMAPHORE_GREEN, REDUCTION_OUTPUTS_PLATE ) == SR_ERROR )
			return SR_ERROR;
		if( SR->SetOutputReduction( OUTPUT_BUZZER, REDUCTION_OUTPUTS_PLATE ) == SR_ERROR )
			return SR_ERROR; */


	MACHINE_CONFIG_END

	// initialize controls
	InitMyControl();

	//initialize autoSPIcheck
	AutoSPIcheck= new AutoSPICheck( DB, SR, camera );
	//initialize autoSPIproc
	AutoSPIproc = new AutoSPIProc (SR, smartLogger, camera, this);

	// initialize SM
	SM = new SMBase();
	SM->Init( SR, smartLogger, datasette, controlPanel, videoMain, toolBox, menuBtn, camera, AutoSPIcheck, AutoSPIproc, this );
	onBtn->SetFocus();
}

wxMainWin::~wxMainWin()
{
	//(*Destroy(wxMainWin)
	//*)

	camera->SetVideoMain( NULL, NULL );
	camera->Delete();

	MyDELETE( SR );
	MyDELETE( DB );
	MyDELETE( SM );
}

//----------------------------------------------------------------------------------
// CreateMyControls
// Crea tutti i controlli necessari all'applicazione e li aggiunge ad i rispettivi
// sizers
//----------------------------------------------------------------------------------
void wxMainWin::CreateMyControls()
{
	// init controls
	videoMain = new wxMainVideo( this );
	videoAux = new wxAuxVideo( this );
	controlPanel = new wxControlPanel( this );
	datasette = new wxDatasette( this );
	productionPanel = new wxProductionPanel( this );
	calibrationPanel = new wxCalibrationPanel( this );
	hardwareTestPanel = new wxHardwareTestPanel( this );
	visionPanel = new wxVisionPanel( this );
	statusPanel = new wxStatusPanel( this );
	inspectionPanel = new wxInspectionPanel( this );

	//aggiunto those panels are used during record view
	InspectionVerifyPanel = new wxInspectionVerifyPanel (this);
	InspectionBoardPanel = new wxInspectionBoardPanel (this);
	//fine

	productionDataPanel = new wxProductionDataPanel( this );

	generalParamsPanel = new wxGeneralParamsPanel( this );
	advancedParamsPanel = new wxAdvancedParamsPanel( this );
	motorsDataPanel = new wxMotorsDataPanel( this );

	// wxSizerClientL
	wxSizerClientL->Add( controlPanel, 0, wxTOP );
	MACHINE_CONFIG_NOT( RES1366 )
		wxSizerClientL->AddSpacer(30);
	MACHINE_CONFIG_END
	wxSizerClientL->Add( videoMain, 0, wxTOP );
	MACHINE_CONFIG_NOT( RES1366 )
		wxSizerClientL->AddSpacer(10);
	MACHINE_CONFIG_END

	// init wxSizerClientR
	wxSizerClientR->Add( videoAux, 0, wxALIGN_CENTER );
	wxSizerClientR->Add( productionPanel, 0, wxALIGN_CENTER | wxEXPAND );
	wxSizerClientR->Add( calibrationPanel, 0, wxALIGN_CENTER | wxEXPAND );
	wxSizerClientR->Add( visionPanel, 0, wxALIGN_CENTER | wxEXPAND );
	wxSizerClientR->Add( hardwareTestPanel, 0, wxALIGN_CENTER | wxEXPAND );
	wxSizerClientR->Add( inspectionPanel, 0, wxALIGN_CENTER | wxEXPAND );
	//aggiunto
	wxSizerClientR->Add(InspectionBoardPanel, 0, wxALIGN_CENTER | wxEXPAND);
	wxSizerClientR->Add(InspectionVerifyPanel, 0, wxALIGN_CENTER | wxEXPAND);

	//fine
	MACHINE_CONFIG_NOT( RES1366 )
		wxSizerClientR->AddStretchSpacer();
	MACHINE_CONFIG_END
	wxSizerClientR->Add( datasette, 0, wxLEFT | wxBOTTOM | wxEXPAND, 5 );//wxLEFT | wxALIGN_LEFT, 5 );

	// init clientParamsSizer
	clientParamsSizer->AddStretchSpacer();
	clientParamsSizer->Add( generalParamsPanel, 0, wxALIGN_CENTER );
	clientParamsSizer->Add( advancedParamsPanel, 0, wxALIGN_CENTER );
	clientParamsSizer->Add( motorsDataPanel, 0, wxALIGN_CENTER );
	clientParamsSizer->Add( statusPanel, 0, wxALIGN_CENTER );
	clientParamsSizer->AddStretchSpacer();

	// init clientProductionSizer
	clientProductionSizer->Add( productionDataPanel, 0, wxALIGN_CENTER );
	clientProductionSizer->AddStretchSpacer();

	// hide all panels
	wxSizerClientR->Show( productionPanel, false );
	wxSizerClientR->Show( inspectionPanel, false );
	wxSizerClientR->Show( calibrationPanel, false );
	wxSizerClientR->Show( visionPanel, false );
	wxSizerClientR->Show( hardwareTestPanel, false );
	//aggiunto
	wxSizerClientR->Show(InspectionVerifyPanel, false);
	wxSizerClientR->Show(InspectionBoardPanel, false);
		//fine
	clientParamsSizer->Show( generalParamsPanel, false );
	clientParamsSizer->Show( advancedParamsPanel, false );
	clientParamsSizer->Show( motorsDataPanel, false );
	clientParamsSizer->Show( statusPanel, false );
	clientParamsSizer->Show( productionDataPanel, false );
}

//----------------------------------------------------------------------------------
// InitMyControl
// Inizializza tutti i controlli necessari all'applicazione
//----------------------------------------------------------------------------------
void wxMainWin::InitMyControl()
{
	camera->SetVideoMain( videoMain->GetPictureBox(), videoMain->GetVideoControlSizer() );
	camera->SetVideoAux( videoAux->GetPictureBox() );
	camera->SetImageFlip( DB->MachineParamsS.ImageFlip );

	videoMain->Init( SR, videoAux, camera );
	controlPanel->Init( SR, smartLogger );
	productionDataPanel->Init( SR, smartLogger, toolBox, menuBtn );
	inspectionPanel->Init( DB );
	generalParamsPanel->Init( SR, smartLogger );
	advancedParamsPanel->Init( DB, smartLogger );
	motorsDataPanel->Init( SR, smartLogger );
	hardwareTestPanel->Init( SR, smartLogger, controlPanel );
	statusPanel->Init( SR, smartLogger );
	//aggiunto these panels are used in viewrecords
	InspectionVerifyPanel->Init( DB );
	InspectionBoardPanel->Init( DB );


	datasette->Init();
	productionPanel->Init( SR, smartLogger );
	calibrationPanel->Init( DB );
	visionPanel->Init( SR, smartLogger );



	//SM->SMSetMutex(*mutex);
	//SM->SMSetCondition(*condition);


	}

//----------------------------------------------------------------------------------
// PasswordCheck
// Controlla se l'utente possiede i privilegi per utilizzare tale funzione
//----------------------------------------------------------------------------------
bool wxMainWin::PasswordCheck( FunctionEnum clickedFnc )
{
	int level = -1;
	wxString msg;

	// check if password is required
	switch( clickedFnc )
	{
		case ADVANCEDPARAMS_FNC:
		case PLATEMOVEMENT_FNC:
		case CAMERAFOCUS_FNC:
		case CAMERASCALE_FNC:
		case CAMERAOFFSET_FNC:
		case VISION_FNC:
		case CONVEDGE_FNC:
			level = 1;
			break;

		case MOTORSDATA_FNC:
			level = 2;
			break;

		case HWTEST_FNC:
			level = 0;
			break;

		default:
			break;
	}

	if( level == 0 )
	{
		if( isPswL0Ok )
			return true;

		msg = MSG_ENTERPASSWORDHWT;
	}
	else if( level == 1 )
	{
		if( isPswL1Ok )
			return true;

		msg = MSG_ENTERPASSWORDL1;
	}
	else if( level == 2 )
	{
		if( isPswL2Ok )
			return true;

		msg = MSG_ENTERPASSWORDL2;
	}
	else
		return true;

	wxPasswordEntryDialog *passwordDlg = new wxPasswordEntryDialog( this, msg, wxT(""), wxT(""), wxOK | wxCANCEL | wxCENTRE );
	passwordDlg->SetWindowStyle( passwordDlg->GetWindowStyle() - wxCAPTION );

	if( passwordDlg->ShowModal() != wxID_OK )
	{
		delete passwordDlg;
		return false;
	}

	msg = passwordDlg->GetValue();
	delete passwordDlg;

	// check string
	if( level == 0 )
	{
		if( pswL0.Cmp( msg ) == 0 )
		{
			isPswL0Ok = true;
			return true;
		}
	}
	else if( level == 1 )
	{
		if( pswL1.Cmp( msg ) == 0 )
		{
			isPswL1Ok = true;
			return true;
		}
	}
	else if( level == 2 )
	{
		if( pswL2.Cmp( msg ) == 0 )
		{
			isPswL2Ok = true;
			return true;
		}
	}

	return false;
}

//----------------------------------------------------------------------------------
// OriginSearch
//
//----------------------------------------------------------------------------------
int wxMainWin::OriginSearch()
{
	// disable limits check
	if( SR->ActivateLimits( LIMITCHECK_OFF ) == SR_ERROR )
	{
		SR->ErrorManagement();
		return SR_ERROR;
	}
	// origin search
	if( SR->OriginSearch() == SR_ERROR )
	{
		SR->StopAllMotors();
		SR->CheckOrigin();
		SR->ErrorManagement();
		return SR_ERROR;
	}

	//Second plate zearch
	if( SR->FinePlateZSearch() == SR_ERROR )
	{
		SR->ErrorManagement();
		return SR_ERROR;
	}
	//End fine zero search

	//set motors home
	if( SR->ResetMotors( MODE_SET_HOME ) == SR_ERROR )
	{
		SR->ErrorManagement();
		return SR_ERROR;
	}


	// enable limits check
	if( SR->ActivateLimits( LIMITCHECK_ON ) == SR_ERROR )
	{
		SR->ErrorManagement();
		return SR_ERROR;
	}
	if( SR->SetAlarmLight( ALARMLIGHT_YELLOW ) == SR_ERROR )
	{
		smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
		SR->ErrorManagement();
	}
	smartLogger->Write( MSG_ORIGINSEARCHENDED, MSG_SUCCESS );

	if( SR->ActivateAllMotorsPID() == SR_ERROR )
	{
		SR->ErrorManagement();
		return SR_ERROR;
	}

	myMilliSleep( 200 );

	if( SetSpeedAllMotors() == SR_ERROR )
	{
		SR->ErrorManagement();
		return SR_ERROR;
	}


	wxWaitDialog wait(this);
	wait.SetMessage( MSG_MOTORSSTARTWAIT );
	wait.Show();

	if( SR->ResetMotors( MODE_GO_HOME ) == SR_ERROR )
	{
		SR->ErrorManagement();
		return SR_ERROR;
	}

	if( SR->ResetMotors( MODE_SET_HOME ) == SR_ERROR )
	{
		SR->ErrorManagement();
		return SR_ERROR;
	}

	//this part check the screw to compensate the zero offset
	int confirmTeachZeroNeeded = wxNO;
	MACHINE_CONFIG(NO_ZERO_SEARCH)
		int ret = camera->SeachCameraZero();
		if( ret == SR_ERROR ){
			SR->ErrorManagement();
			return SR_ERROR;
		}
		else if(ret == SR_WARNING ){
			SR->MoveCameraAndWait(0, 0, ABS_MOVE);
			confirmTeachZeroNeeded = wxMessageBox( MSG_CAMERAZERONOTFOUND ,  MACHINE_NAME, wxOK | wxICON_QUESTION, this ) ;
		}
		else{
			int retVal = SM->MoveCameraToCompensateOffset(false);
			if( retVal == SR_ERROR){
				SR->ErrorManagement();
				return SR_ERROR;
			}else if (retVal == SR_WARNING){
				//Start a second search cycle
				retVal = camera->RetryCameraZero();
				if( retVal == SR_ERROR){
					SR->ErrorManagement();
					return SR_ERROR;
				}else if(retVal == SR_WARNING){
					SR->MoveCameraAndWait(0, 0, ABS_MOVE);
					wxMessageBox( MSG_CAMERAZEROOUTBONDS ,  MACHINE_NAME, wxOK | wxICON_ERROR, this ) ;
				}else{
					SM->MoveCameraToCompensateOffset(true);
				}
			}
		}
	MACHINE_CONFIG_END
	//End camera Zero procedure


	if( SR->ResetMotors( MODE_INITIAL_POSITION ) == SR_ERROR )
	{
		SR->ErrorManagement();
		return SR_ERROR;
	}

	wait.Close();

	// Ask for conveyors to move to last production position
	if( wxMessageBox( wxString::Format( MSG_CONVEYORSTOOLDSTART, SR->DB->ProductionDataS.ProductionName.ToAscii() ), MACHINE_NAME, wxYES_NO | wxICON_QUESTION, this ) == wxYES )
	{
		double convMove = SR->DB->ProductionDataS.PCBY - SR->DB->MachineParamsS.LConvMovement - SR->DB->MachineParamsS.LConvZeroMovement + CONVEYOR_WIDTH_DELTA;
		if(convMove < CONVPISTON_MIN_Y){
			wxMessageBox( MSG_CONVWIDTHMIN, MACHINE_NAME, wxOK | wxICON_ERROR, this);
			return SR_OK;
		}
		wxWaitDialog wait(this);
		wait.SetMessage( MSG_CONVEYORWAIT );
		wait.Show();

		// Move the conveyors to Y dimension
		if( SR->LConvWidthMotor.Move( SR->DB->ProductionDataS.PCBY - SR->DB->MachineParamsS.LConvMovement - SR->DB->MachineParamsS.LConvZeroMovement + CONVEYOR_WIDTH_DELTA, ABS_MOVE ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CONVWIDTHERROR, MSG_ERROR );
			SR->ErrorManagement();
		}
		if( SR->CConvWidthMotor.Move( SR->DB->ProductionDataS.PCBY - SR->DB->MachineParamsS.CConvMovement - SR->DB->MachineParamsS.CConvZeroMovement + CONVEYOR_WIDTH_DELTA, ABS_MOVE ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CONVWIDTHERROR, MSG_ERROR );
			SR->ErrorManagement();
		}

		if( SR->LConvWidthMotor.Wait() == SR_ERROR )
		{
			smartLogger->Write( MSG_CONVWIDTHERROR, MSG_ERROR );
			SR->ErrorManagement();
		}
		if( SR->CConvWidthMotor.Wait() == SR_ERROR )
		{
			smartLogger->Write( MSG_CONVWIDTHERROR, MSG_ERROR );
			SR->ErrorManagement();
		}

		wait.Close();

		smartLogger->Write( MSG_CONVEYOROK, MSG_SUCCESS );
	}

	if(confirmTeachZeroNeeded == wxOK){
		SM->doNotSaveZeroPos = true;
		ToolBarClick( CAMERAZERO_FNC );
	}


	return SR_OK;
}

//----------------------------------------------------------------------------------
// DisableAllMotors
//
//----------------------------------------------------------------------------------
int wxMainWin::DisableAllMotors()
{
	int isError = false;

	isError = SR->DisableAllMotors();

	MACHINE_CONFIG( MACHINE_ENABLE )
	wxMilliSleep( 3000 );
	MACHINE_CONFIG_END

	return isError ? SR_ERROR : SR_OK;
}

//----------------------------------------------------------------------------------
// SetSpeedAllMotors
//
//----------------------------------------------------------------------------------
int wxMainWin::SetSpeedAllMotors()
{
	bool isError = false;

	if( SR->Table1Motor.SetSpeedAcc() == SR_ERROR )
	{
		smartLogger->Write( MSG_TABLEINITERROR, MSG_ERROR );
		isError = true;
	}
	if( SR->Table2Motor.SetSpeedAcc() == SR_ERROR )
	{
		smartLogger->Write( MSG_TABLEINITERROR, MSG_ERROR );
		isError = true;
	}
	if( SR->Table3Motor.SetSpeedAcc() == SR_ERROR )
	{
		smartLogger->Write( MSG_TABLEINITERROR, MSG_ERROR );
		isError = true;
	}
	if( SR->PlateMotor.SetSpeedAcc() == SR_ERROR )
	{
		smartLogger->Write( MSG_PLATEINITERROR, MSG_ERROR );
		isError = true;
	}
	if( SR->SqueegeesMotor.SetSpeedAcc() == SR_ERROR )
	{
		smartLogger->Write( MSG_SQUEEGEESINITERROR, MSG_ERROR );
		isError = true;
	}
	if( SR->CamXMotor.SetSpeedAcc() == SR_ERROR )
	{
		smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
		isError = true;
	}
	if( SR->CamYMotor.SetSpeedAcc() == SR_ERROR )
	{
		smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
		isError = true;
	}
	if( SR->LConvWidthMotor.SetSpeedAcc() == SR_ERROR )
	{
		smartLogger->Write( MSG_LCONVWINITERROR, MSG_ERROR );
		isError = true;
	}
	if( SR->LConvFeedMotor.SetSpeedAcc() == SR_ERROR )
	{
		smartLogger->Write( MSG_LCONVFINITERROR, MSG_ERROR );
		isError = true;
	}
	MACHINE_CONFIG(CONV_PUSH_MOTOR)
	if( SR->LConvPushMotor.SetSpeedAcc() == SR_ERROR )
	{
		smartLogger->Write( MSG_LCONVPINITERROR, MSG_ERROR );
		isError = true;
	}
	MACHINE_CONFIG_END
	if( SR->CConvWidthMotor.SetSpeedAcc() == SR_ERROR )
	{
		smartLogger->Write( MSG_CCONVWINITERROR, MSG_ERROR );
		isError = true;
	}
	if( SR->CConvFeedMotor.SetSpeedAcc() == SR_ERROR )
	{
		smartLogger->Write( MSG_CCONVFINITERROR, MSG_ERROR );
		isError = true;
	}
	if( DB->MachineParamsS.LoaderInstalled )
	{
		if( SR->LoaderMotor.SetSpeedAcc() == SR_ERROR )
		{
			smartLogger->Write( MSG_LOADERINITERROR, MSG_ERROR );
			isError = true;
		}
	}

	return isError ? SR_ERROR : SR_OK;
}

//----------------------------------------------------------------------------------
// CheckAndUpdateDB
//
//----------------------------------------------------------------------------------
void wxMainWin::CheckAndUpdateDB()
{

	while( !DB->CheckVersion( DB_VERSION ) )
	{
		wxWindowDisabler disableAll;
		wxBusyCursor wait;

		// Update DB
		bool needUpdate = false;
		/*effettuare backup
		wxString db_backup;
		if( ChooseLocation( db_backup ) == false )
			return;

		wxDateTime dateTime = wxDateTime::Now();
		db_backup += wxFileName::GetPathSeparator();
		db_backup += dateTime.FormatISODate() + wxT(" ") + dateTime.FormatISOTime() + FILE_DBBACKUPEXT;
		db_backup.Replace( wxT(":"), wxT(".") );

		int retVal = DB->Backup( db_backup );

		if( retVal == 0 )
			wxMessageBox( MSG_DBBACKUPOK, MACHINE_NAME, wxOK | wxICON_INFORMATION, this );
		else
			wxMessageBox( wxString::Format( MSG_DBBACKUPERROR, retVal ), MACHINE_NAME, wxOK | wxICON_ERROR, this );
		*/
		wxCommandEvent tmp = wxCommandEvent();
		OnbackupBtnClick(tmp);

		if( needUpdate = DB->CheckVersion( wxT("1.00") ) )
		{
			smartLogger->Write( wxString( MSG_DBUPDATE ) + wxT("1.00 -> 2.00") );
			wxTheApp->Yield();
		}
		else if( needUpdate = DB->CheckVersion( wxT("2.00") ) )
		{
			smartLogger->Write( wxString( MSG_DBUPDATE ) + wxT("2.00 -> 2.01") );
			wxTheApp->Yield();
		}
		else if( needUpdate = DB->CheckVersion( wxT("2.01") ) )
		{
			smartLogger->Write( wxString( MSG_DBUPDATE ) + wxT("2.01 -> 2.02") );
			wxTheApp->Yield();
		}
		else if( needUpdate = DB->CheckVersion( wxT("2.02") ) )
		{
			smartLogger->Write( wxString( MSG_DBUPDATE ) + wxT("2.02 -> 2.03") );
			wxTheApp->Yield();
		}
		else
		{
			// Error! DB not supported
			wxMessageBox( MSG_BADDBVERSION, MACHINE_NAME, wxOK, this );
			smartLogger->Write( MSG_BADDBVERSION );
			Close();
			return;
		}
		//TODO

		if( needUpdate )
		{
			if( DB->Update() == SR_ERROR )
			{
				wxMessageBox( MSG_DBUPDATEERROR, MACHINE_NAME, wxOK, this );
				smartLogger->Write( MSG_DBUPDATEERROR );
				Close();
				return;
			}
			// Reload data
			//DB->LoadMachineStructsFromDB();
			//DB->LoadProductionNames();
			//DB->LoadActualProduction();
			//DB->LoadProductionStructsFromDB( DB->ActualProductionS.IdProd );

			smartLogger->Write( MSG_DBUPDATEOK, MSG_SUCCESS );
		}
	}
}

//----------------------------------------------------------------------------------
// OnGUIEvents
//
//----------------------------------------------------------------------------------
void wxMainWin::OnGUIEvents( wxCommandEvent& event )
{
	// if event is fired by timer (side button pressed) ...
	if( event.GetId() == SRMachine::ID_SM_TIMER )
	{
		// if the showed panel is the printing panel...
		if( currentFnc == PRINTING_FNC )
		{
			SM->OnStart();
		}
		return;
	}
	if( event.GetId() == SRMachine::ID_CAMERA_WAIT )
	{
		//
		SM->OnNext();
		return;
	}
	else if( event.GetId() == wxProductionPanel::ID_SQUEEGEES_BUTTON )
	{
		SM->MoveSqueegeesSide( event.GetInt() ? true : false );
		return;
	}
	else if( event.GetId() == wxDatasette::ID_START_BUTTON )
	{
		SM->OnStart();
		return;
	}
	else if( event.GetId() == wxDatasette::ID_STOP_BUTTON )
	{
		SM->OnStop();
		return;
	}
	else if( event.GetId() == wxDatasette::ID_NEXT_BUTTON )
	{
		SM->OnNext();
		return;
	}
	else if( event.GetId() == wxDatasette::ID_PREV_BUTTON )
	{
		SM->OnPrev();
		return;
	}
	else if( event.GetId() == wxDatasette::ID_PAUSE_BUTTON )
	{
		SM->OnPause();
		return;
	}
	else if( event.GetId() == wxCameraControl::ID_SEARCH_CIRCLE_RADIUS )
	{
		productionPanel->UpdateCircleDiameter();
		return;
	}
	else if( event.GetId() == wxCameraControl::ID_SEARCH_RECT_SIDES )
	{
		productionPanel->UpdateRectangleSides();
		return;
	}
	else if( event.GetId() == wxCameraControl::ID_SEARCH_SHAPE )
	{
		productionPanel->UpdatePanel();
		productionPanel->Layout();
		return;
	}
	// wxInspectionPanel
	//------------------------------------------------------------------------------
	else if( event.GetId() == wxInspectionPanel::ID_EVENT )
	{
		SM->OnNext( event.GetInt() );
		return;
	}
	// wxProductionPanel
	else if(event.GetId() == wxProductionPanel::ID_EVENT ){
		SM->OnNext( event.GetInt() );
	}
	else if (event.GetId() == wxProductionPanel::EVT_REQUEST_NEW_THRESHOLDS) {
		SM->OnNext( event.GetInt() );
	}
	//ViewRecords panel
	else if( event.GetId() == wxInspectionBoardPanel::ID_EVENTRECORDS ){

		if (InspectionVerifyPanel->InitializeSelectedBoard()==SR_ERROR)
			return;
		SM->OnNext( event.GetInt() );


		}
	else if ( event.GetId() == wxInspectionVerifyPanel::EVT_GRID_SELECTED_RECORDS ){
		SM->OnNext( event.GetInt() );
	}
	else if( event.GetId() == wxInspectionVerifyPanel::ID_CHANGEPICTURE ){
		SM->OnNext( event.GetInt() );
	}
	else if( event.GetId() == wxInspectionVerifyPanel::EVT_IDENTIFY_ALL_FAULTY){
		SM->OnNext( event.GetInt() );
	}
	else if( event.GetId() == wxInspectionVerifyPanel::EVT_IDENTIFY_ALL_WARNING){
		SM->OnNext( event.GetInt() );
	}
	else if(event.GetId() == wxMainVideo::ID_EVENT ){
		SM->OnNext( event.GetInt() );
	}

	event.Skip();
}

//----------------------------------------------------------------------------------
// ToolBarClick
// Gestisce la pressione dei bottoni della ToolBar
//----------------------------------------------------------------------------------
void wxMainWin::ToolBarClick( FunctionEnum clickedFnc )
{
	if(SR->isReckinLoadPosition){
		int retVal = wxMessageBox( MSG_RACKINLOADINGPOS, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, this );
		if(retVal != wxYES){
			return;
		}else{
			productionDataPanel->moveLoaderToProductionPosition();
		}
	}
	if( clickedFnc == LOAD_FNC )
	{
		//040418

		if( SR->CheckOrigin() && !isBoardMoving )
		{
			isBoardMoving = true;

			if( !SR->isBoardLoaded )
			{
				if( SR->CheckMotorsPos() == SR_ERROR )
					if( SR->ResetMotors( MODE_STARTPRINTING_POSITION ) == SR_ERROR )
					{
						isBoardMoving = false;
						return;
					}

				wxWaitDialog wait(this);
				wait.SetMessage( MSG_LOADING );
				wait.Show();

				if( SM->LoadBoardCameraCheck() == SR_ERROR )
				{
					smartLogger->Write( MSG_LOADERROR, MSG_ERROR );
				}

				wait.Close();

				// draw board
				if( SR->DB->ProductionDataS.PCBPosX != 0.0 )
					camera->DrawWorkplace( SR->DB->ProductionDataS.PCBPosX, SR->DB->ProductionDataS.PCBPosY, SR->DB->ProductionDataS.PCBX, SR->DB->ProductionDataS.PCBY );
			}
			else
			{
				if( SR->CheckMotorsPos() == SR_ERROR )
					if( SR->ResetMotors( MODE_STARTPRINTING_POSITION ) == SR_ERROR )
					{
						isBoardMoving = false;
						return;
					}

				wxWaitDialog wait(this);
				wait.SetMessage( MSG_UNLOADING );
				wait.Show();

				if( SR->UnloadBoard() == SR_ERROR )
				{
					smartLogger->Write( MSG_UNLOADERROR, MSG_ERROR );
				}

				wait.Close();

				// draw empty workplace
				camera->DrawWorkplace();
			}

			isBoardMoving = false;
		}
		else
		{
			SR->ErrorManagement();
			return;
		}

		return;
	}

	if( clickedFnc == currentFnc && clickedFnc != NULL_FNC )
		return;

	MACHINE_CONFIG( PASSWORD_ENABLE )
		// check if password is required
		if( PasswordCheck( clickedFnc ) == false )
			return;
	MACHINE_CONFIG_END

	FinalizeControl( currentFnc );
	InitializeControl( clickedFnc );
	DrawControls( clickedFnc );

	currentFnc = clickedFnc;
}

//----------------------------------------------------------------------------------
// FinalizeControl
// Finaliza il controllo attuale prima della sua chiusura
//----------------------------------------------------------------------------------
void wxMainWin::FinalizeControl( FunctionEnum clickedFnc )
{
	switch( clickedFnc )
	{
		case PRODUCTIONPARAMS_FNC:
			productionDataPanel->HideControl();
			if( SR->GetMachineState() == true )
				if( SetSpeedAllMotors() == SR_ERROR )
					SR->ErrorManagement();
			break;

		case ALIGNMENT_FNC:
		case PRINTING_FNC:
		case VERIFY_FNC:
		case PINS_FNC:
		case PASTE_FNC:
			productionPanel->HideControl();
			SM->SelectSM( SM_NONE );
			break;

		case INSPECTION_FNC:
			inspectionPanel->HideControl();
			SM->SelectSM( SM_NONE );
			break;

		case GENERALPARAMS_FNC:
			generalParamsPanel->HideControl();
			if( SR->GetMachineState() == true )
				if( SetSpeedAllMotors() == SR_ERROR )
					SR->ErrorManagement();
			break;

		case ADVANCEDPARAMS_FNC:
			advancedParamsPanel->HideControl();
			camera->SetImageFlip( DB->MachineParamsS.ImageFlip );
			break;

		case MOTORSDATA_FNC:
			motorsDataPanel->HideControl();
			if( SR->GetMachineState() == true )
			{
				if( SetSpeedAllMotors() == SR_ERROR )
					SR->ErrorManagement();
			}
			break;

		case STATUS_FNC:
			statusPanel->HideControl();
			break;

		case PLATEMOVEMENT_FNC:
		case CAMERAFOCUS_FNC:
		case CAMERASCALE_FNC:
		case CAMERAOFFSET_FNC:
		case CONVEDGE_FNC:
			calibrationPanel->HideControl();
			SM->SelectSM( SM_NONE );
			break;

		case VISION_FNC:
			visionPanel->HideControl();
			SM->SelectSM( SM_NONE );
			break;

		case HWTEST_FNC:
			hardwareTestPanel->HideControl();
			SM->SelectSM( SM_NONE );
			break;

		case DEMO_FNC:
			SM->SelectSM( SM_NONE );
			break;

		default:
			break;
	}

	// hide videoMain
	switch( clickedFnc )
	{
		case ALIGNMENT_FNC:
		case PRINTING_FNC:
		case VERIFY_FNC:
		case PINS_FNC:
		case PASTE_FNC:
		case PLATEMOVEMENT_FNC:
		case CAMERAFOCUS_FNC:
		case CAMERASCALE_FNC:
		case CAMERAOFFSET_FNC:
		case VISION_FNC:
		case HWTEST_FNC:
		case DEMO_FNC:
		case CONVEDGE_FNC:
			videoMain->HideControl();

		default:
			break;
	}

}

//----------------------------------------------------------------------------------
// InitializeControl
// Inizializza il controllo prima della sua apertura
//----------------------------------------------------------------------------------
void wxMainWin::InitializeControl( FunctionEnum clickedFnc )
{
	switch( clickedFnc )
	{
		case PRODUCTIONPARAMS_FNC:
			title = _("Production Params");
			productionDataPanel->ShowControl();
			break;
		case ALIGNMENT_FNC:
			title = _("Alignment");
			productionPanel->ShowControl();
			SM->SelectSM( SM_ALIGNMENT, productionPanel );
			break;
		case PRINTING_FNC:
			title = _("Printing");
			productionPanel->ShowControl();
			SM->SelectSM( SM_PRINTING, productionPanel );
			break;
		case INSPECTION_FNC:
			title = _("Inspection");
			inspectionPanel->ShowControl();
			SM->SelectSM( SM_INSPECTION, inspectionPanel );
			break;
		case VERIFY_FNC:
			title = _("Verify");
			productionPanel->ShowControl();
			SM->SelectSM( SM_VERIFY, productionPanel );
			break;
		case PINS_FNC:
			title = _("Pins");
			productionPanel->ShowControl();
			SM->SelectSM( SM_PINS, productionPanel );
			break;
		case PASTE_FNC:
			title = _("Paste");
			productionPanel->ShowControl();
			SM->SelectSM( SM_PASTE, productionPanel );
			break;
		case GENERALPARAMS_FNC:
			title = _("General Params");
			generalParamsPanel->ShowControl();
			break;
		case ADVANCEDPARAMS_FNC:
			title = _("Advanced Params");
			advancedParamsPanel->ShowControl();
			break;
		case MOTORSDATA_FNC:
			title = _("Motors Data");
			motorsDataPanel->ShowControl();
			break;
		case STATUS_FNC:
			title = _("Motors Status");
			statusPanel->ShowControl();
			break;
		case PLATEMOVEMENT_FNC:
			title = _("Plate Height");
			calibrationPanel->ShowControl();
			SM->SelectSM( SM_PLATEMOVEMENT, calibrationPanel );
			break;
		case CAMERAFOCUS_FNC:
			title = _("Camera Focus");
			calibrationPanel->ShowControl();
			SM->SelectSM( SM_CAMERAFOCUS, calibrationPanel );
			break;
		case CAMERASCALE_FNC:
			title = _("Camera Scale");
			calibrationPanel->ShowControl();
			SM->SelectSM( SM_CAMERASCALE, calibrationPanel );
			break;
		case CAMERAOFFSET_FNC:
			title = _("Camera Offset");
			calibrationPanel->ShowControl();
			SM->SelectSM( SM_CAMERAOFFSET, calibrationPanel );
			break;
		case CAMERAZERO_FNC:
			title = _("Camera Zero");
			productionPanel->ShowControl();
			SM->SelectSM( SM_CAMERAZERO, productionPanel );
			break;
		case VISION_FNC:
			title = _("Vision");
			visionPanel->ShowControl();
			SM->SelectSM( SM_VISION, visionPanel );
			break;
		case HWTEST_FNC:
			title = _("Hardware Test");
			hardwareTestPanel->ShowControl();
			SM->SelectSM( SM_HARDWARETEST, hardwareTestPanel );
			break;
		case DEMO_FNC:
			title = _("Demo");
			SM->SelectSM( SM_DEMOMODE, NULL );
			break;
		case CONVEDGE_FNC:
			title = _("Conveyor Edge");
			calibrationPanel->ShowControl();
			SM->SelectSM( SM_CONVEDGE, calibrationPanel );
			break;
		case VIEWRECORDS_FNC:
			title = _("View Records");
			InspectionBoardPanel->UpdateLists();
			InspectionBoardPanel->SelectFirstBoard();
			SM->SelectSM( SM_VIEWRECORDS );

			break;
		default:
			title = wxT("");
			break;
	}

	// show videoMain
	switch( clickedFnc )
	{
		case ALIGNMENT_FNC:
		case PRINTING_FNC:
		case VERIFY_FNC:
		case PINS_FNC:
		case PASTE_FNC:
		case PLATEMOVEMENT_FNC:
		case CAMERAFOCUS_FNC:
		case CAMERASCALE_FNC:
		case CAMERAOFFSET_FNC:
		case VISION_FNC:
		case HWTEST_FNC:
		case DEMO_FNC:
		case CONVEDGE_FNC:
		case VIEWRECORDS_FNC:
		case INSPECTION_FNC:
			videoMain->ShowControl();
		default:
			break;
	}

	// Set production name
	switch( clickedFnc )
	{
		case ALIGNMENT_FNC:
		case PRINTING_FNC:
		case VERIFY_FNC:
		case PINS_FNC:
		case PASTE_FNC:
		case INSPECTION_FNC:
			videoMain->SetCurrentProductionName( DB->ProductionDataS.ProductionName );
			break;
		default:
			videoMain->SetCurrentProductionName( wxT("  ---") );
			break;
	}

	// draw or not board in camera control
	switch( clickedFnc )
	{
		case ALIGNMENT_FNC:
		case PRINTING_FNC:
		case VERIFY_FNC:
		case HWTEST_FNC:
		case INSPECTION_FNC:
			if( (SR->DB->ProductionDataS.PCBPosX != 0.0) && (SR->isBoardLoaded) )
				camera->DrawWorkplace( SR->DB->ProductionDataS.PCBPosX, SR->DB->ProductionDataS.PCBPosY, SR->DB->ProductionDataS.PCBX, SR->DB->ProductionDataS.PCBY );
			else
				camera->DrawWorkplace();
			break;
		default:
			break;
	}

}

//----------------------------------------------------------------------------------
// DrawControls
// Aggiorna i controlli a video
//----------------------------------------------------------------------------------
void wxMainWin::DrawControls( FunctionEnum clickedFnc )
{
	Freeze();

	titleSizer->Show( false );

	menuSizer->Show( false );
	clientLRSizer->Show( false );
	clientLRSizer->Show( wxSizerClientL, false );
	clientLRSizer->Show( wxSizerClientR, false );
	clientParamsSizer->Show( false );
	clientProductionSizer->Show( false );


	if( clickedFnc != NULL_FNC )
	{
		headerLabel->SetLabel( title );
		titleSizer->Show( true );
	}

	// Finestra del logger a tutto schermo o piu' corta a seconda dei casi...
	if(	clickedFnc == NULL_FNC ||
		clickedFnc == PRODUCTIONPARAMS_FNC ||
		clickedFnc == GENERALPARAMS_FNC ||
		clickedFnc == ADVANCEDPARAMS_FNC ||
		clickedFnc == MOTORSDATA_FNC ||
		clickedFnc == STATUS_FNC )
	{
		MACHINE_CONFIG( RES1366 )
			PanelFooter->SetMaxSize(wxSize(1356,110));
		MACHINE_CONFIG_ELSE
			PanelFooter->SetMaxSize(wxSize(1920,110));
		MACHINE_CONFIG_END
	}
	else
	{
		MACHINE_CONFIG( RES1366 )
			PanelFooter->SetMaxSize(wxSize(1356,110));
			//PanelFooter->SetMaxSize(wxSize(870,110)); //serve ad accorciare il logger
		MACHINE_CONFIG_ELSE
			PanelFooter->SetMaxSize(wxSize(1920,110));
		MACHINE_CONFIG_END
	}

	if( clickedFnc == NULL_FNC )
	{
		menuSizer->Show( true );
	}
	else if(
		clickedFnc == ALIGNMENT_FNC ||
		clickedFnc == PRINTING_FNC ||
		clickedFnc == VERIFY_FNC ||
		clickedFnc == PINS_FNC ||
		clickedFnc == PLATEMOVEMENT_FNC ||
		clickedFnc == CAMERAFOCUS_FNC ||
		clickedFnc == CAMERASCALE_FNC ||
		clickedFnc == CAMERAOFFSET_FNC ||
		clickedFnc == VISION_FNC ||
		clickedFnc == HWTEST_FNC ||
		clickedFnc == CONVEDGE_FNC ||
		clickedFnc == INSPECTION_FNC ||
		clickedFnc == PASTE_FNC ||
		clickedFnc == DEMO_FNC ||
		clickedFnc == CAMERAZERO_FNC)
	{
		clientLRSizer->Show( true );
		clientLRSizer->Show( wxSizerClientL, true );
		clientLRSizer->Show( wxSizerClientR, true );
		wxSizerClientR->Show( videoAux, true );
		wxSizerClientR->Show( datasette,			clickedFnc == HWTEST_FNC ? false : true );
		wxSizerClientR->Show( productionPanel,		clickedFnc == ALIGNMENT_FNC ||
													clickedFnc == CAMERAZERO_FNC ||
													clickedFnc == PRINTING_FNC ||
													clickedFnc == PINS_FNC ||
													clickedFnc == PASTE_FNC ||
													clickedFnc == VERIFY_FNC ? true : false );

		wxSizerClientR->Show( calibrationPanel,		clickedFnc == PLATEMOVEMENT_FNC ||
													clickedFnc == CAMERAFOCUS_FNC ||
													clickedFnc == CAMERASCALE_FNC ||
													clickedFnc == DEMO_FNC ||
													clickedFnc == CONVEDGE_FNC ||
													clickedFnc == CAMERAOFFSET_FNC ? true : false );

		wxSizerClientR->Show( inspectionPanel,		clickedFnc == INSPECTION_FNC ? true : false );
		wxSizerClientR->Show( visionPanel,			clickedFnc == VISION_FNC ? true : false );
		wxSizerClientR->Show( hardwareTestPanel,	clickedFnc == HWTEST_FNC ? true : false );
		//aggiunto
		wxSizerClientR->Show(InspectionBoardPanel, false); //disable these 2 panels used in view records
		wxSizerClientR->Show(InspectionVerifyPanel, false);

		if( clickedFnc == ALIGNMENT_FNC )
			productionPanel->DrawControl( PP_ALIGNMENT );
		else if( clickedFnc == PRINTING_FNC )
			productionPanel->DrawControl( PP_PRINTING );
		else if( clickedFnc == VERIFY_FNC )
			productionPanel->DrawControl( PP_VERIFY );
		else if( clickedFnc == PINS_FNC )
			productionPanel->DrawControl( PP_PINS );
		else if( clickedFnc == PASTE_FNC )
			productionPanel->DrawControl( PP_PASTE );
		else if( clickedFnc ==  CAMERAZERO_FNC)
			productionPanel->DrawControl( PP_ALIGNMENT );
		else if( clickedFnc == PLATEMOVEMENT_FNC )
			calibrationPanel->DrawControl( CC_PLATE );
		else if( clickedFnc == CAMERAFOCUS_FNC )
			calibrationPanel->DrawControl( CC_FOCUS );
		else if( clickedFnc == CAMERASCALE_FNC )
			calibrationPanel->DrawControl( CC_SCALE );
		else if( clickedFnc == CAMERAOFFSET_FNC )
			calibrationPanel->DrawControl( CC_OFFSET );
		else if( clickedFnc == DEMO_FNC )
			calibrationPanel->DrawControl( CC_DEMO );
		else if( clickedFnc == CONVEDGE_FNC )
			calibrationPanel->DrawControl( CC_EDGE );

		if( productionPanel->IsShown() )
			productionPanel->Layout();
		if( calibrationPanel->IsShown() )
			calibrationPanel->Layout();
		if( inspectionPanel->IsShown() )
			inspectionPanel->Layout();
		wxSizerClientR->Layout();
	}
	else if(
		clickedFnc == GENERALPARAMS_FNC ||
		clickedFnc == ADVANCEDPARAMS_FNC ||
		clickedFnc == MOTORSDATA_FNC ||
		clickedFnc == STATUS_FNC )
	{
		clientParamsSizer->Show( true );
		clientParamsSizer->Show( generalParamsPanel,	clickedFnc == GENERALPARAMS_FNC		? true : false );
		clientParamsSizer->Show( advancedParamsPanel,	clickedFnc == ADVANCEDPARAMS_FNC	? true : false );
		clientParamsSizer->Show( motorsDataPanel,		clickedFnc == MOTORSDATA_FNC		? true : false );
		clientParamsSizer->Show( statusPanel,			clickedFnc == STATUS_FNC			? true : false );
		clientParamsSizer->Layout();
	}
	else if( clickedFnc == PRODUCTIONPARAMS_FNC )
	{
		clientProductionSizer->Show( true );
		clientProductionSizer->Show( productionDataPanel, true );
		clientProductionSizer->Layout();
	}
	else if(clickedFnc == VIEWRECORDS_FNC){

		clientLRSizer->Show( true );
		clientLRSizer->Show( wxSizerClientL, true );
		clientLRSizer->Show( wxSizerClientR, true );


		wxSizerClientR->Show( videoAux, false ); //here we disable the aux screen
		wxSizerClientR->Show( datasette, false );


		wxSizerClientR->Show( calibrationPanel,  false );
		wxSizerClientR->Show( visionPanel, false );
		wxSizerClientR->Show( hardwareTestPanel,	false );
		wxSizerClientR->Show(productionDataPanel, false);
		wxSizerClientR->Show( productionPanel, false);
		wxSizerClientR->Show( inspectionPanel,	false );

		wxSizerClientR->Show(InspectionBoardPanel, true); //this panel allows to select the board
		wxSizerClientR->Show(InspectionVerifyPanel, true); 	//this panel allows to examinate single areas
	}


	headerSizer->Layout();
	Layout();
	Thaw();
}

//----------------------------------------------------------------------------------
// ChooseLocation
// Finestra per la scelta della cartella di backup del DB
//----------------------------------------------------------------------------------
bool wxMainWin::ChooseLocation( wxString& location )
{
	long index = 0;
	wxArrayString drivesMountPoint, locationList;

	#ifndef __WXMSW__
		// get usb drive mount point
		getAllUsbMountPoints( &drivesMountPoint );
		// append (USB drive) label to better understand
		for( size_t i = 0; i < drivesMountPoint.GetCount(); ++i )
			locationList.Add( drivesMountPoint[i] + wxT(" (USB drive)") );
	#endif

	// insert local folder location at the beginning (index 0)
	drivesMountPoint.Insert( DIR_DBBACKUP, 0 );
	locationList.Insert( _("Local folder"), 0 );
	//
	index = wxGetSingleChoiceIndex( _("Choose location:"), MACHINE_NAME, locationList, this );
	if( index == -1 )
		return false;

	location = drivesMountPoint[index];
	return true;
}


	//------------//
	//   EVENTS   //
	//------------//

void wxMainWin::OnButton1Click1(wxCommandEvent& event)
{
	ToolBarClick( STATUS_FNC );
}

void wxMainWin::OnButton1Click(wxCommandEvent& event)
{
	ToolBarClick( PRODUCTIONPARAMS_FNC );
}

void wxMainWin::OnBitmapButton5Click(wxCommandEvent& event)
{
	ToolBarClick( LOAD_FNC );
}

void wxMainWin::OnButton2Click(wxCommandEvent& event)
{
	ToolBarClick( ALIGNMENT_FNC );
}

void wxMainWin::OnBitmapButton6Click(wxCommandEvent& event)
{
	ToolBarClick( PINS_FNC );
}

void wxMainWin::OnInspectionSitesButtonClick(wxCommandEvent& event) //button to Sites teach
{
	ToolBarClick( INSPECTION_FNC );

}

void wxMainWin::OnButton2Click1(wxCommandEvent& event)
{
	ToolBarClick( PASTE_FNC );
}

void wxMainWin::OnButton3Click1(wxCommandEvent& event)
{
	if( SR->CheckOrigin() && !isCleaning )
	{
		isCleaning = true;

		if( SR->CheckMotorsPos() == SR_ERROR )
			if( SR->ResetMotors( MODE_STARTPRINTING_POSITION ) == SR_ERROR )
			{
				isCleaning = false;
				return;
			}

		wxWaitDialog wait(this);
		wait.SetMessage( MSG_CLEANING );
		wait.Show();

		if( SR->CleaningCycle() == SR_ERROR )
		{
			smartLogger->Write( MSG_CLEANINGERROR, MSG_ERROR );

			// Reset original camera speed
			SR->DB->MachineParamsS.CameraSpeed = SR->cameraSavedSpeed;
			if( SR->CamXMotor.SetSpeedAcc() == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
				return;
			}
			if( SR->CamYMotor.SetSpeedAcc() == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
				return;
			}

		}

		wait.Close();

		if( SR->ResetMotors( MODE_STARTPRINTING_POSITION ) == SR_ERROR )
		{
			isCleaning = false;
			return;
		}

		isCleaning = false;

		smartLogger->Write( MSG_CLEANINGENDED, MSG_SUCCESS );
	}
	else
	{
		SR->ErrorManagement();
		return;
	}

	return;
}

void wxMainWin::OnButton3Click(wxCommandEvent& event)
{
	ToolBarClick( PRINTING_FNC );
}

void wxMainWin::OnButton4Click(wxCommandEvent& event)
{
	if( !SR->DB->MachineParamsS.CleaningInstalled ){
		ToolBarClick( VERIFY_FNC );
	}else{
		wxWindow* btn = (wxWindow*) event.GetEventObject();
		wxPoint pos = btn->ClientToScreen( wxPoint( btn->GetSize().x / 2, btn->GetSize().y ) );

		wxMyPopup* myPopup = new wxMyPopup( this, wxID_ANY );
		wxInspectionPopup* inspectionPopup = new wxInspectionPopup( myPopup );
		myPopup->SetChild( inspectionPopup );
		myPopup->SetArrowPosition( pos );
		int retVal = myPopup->ShowModal();
		delete myPopup;

		if( retVal == INSPECTIONPOPUP_TEACHING )
		{
			ToolBarClick( VIEWRECORDS_FNC );
		}
		else if( retVal == INSPECTIONPOPUP_VERIFY )
		{
			ToolBarClick( VERIFY_FNC );
		}

	}
}

void wxMainWin::OnButton5Click(wxCommandEvent& event)
{
	ToolBarClick( GENERALPARAMS_FNC );
}

void wxMainWin::OnButton6Click(wxCommandEvent& event)
{
	ToolBarClick( ADVANCEDPARAMS_FNC );
}

void wxMainWin::OnButton7Click(wxCommandEvent& event)
{
	ToolBarClick( MOTORSDATA_FNC );
}

void wxMainWin::OnButton8Click(wxCommandEvent& event)
{
	ToolBarClick( HWTEST_FNC );
}

void wxMainWin::OnButton9Click(wxCommandEvent& event)
{
	ToolBarClick( PLATEMOVEMENT_FNC );
}

void wxMainWin::OnButton10Click(wxCommandEvent& event)
{
	ToolBarClick( CAMERAFOCUS_FNC );
}

void wxMainWin::OnButton11Click(wxCommandEvent& event)
{
	ToolBarClick( CAMERASCALE_FNC );
}

void wxMainWin::OnButton12Click(wxCommandEvent& event)
{
	ToolBarClick( CAMERAOFFSET_FNC );
}

void wxMainWin::OnButton13Click(wxCommandEvent& event)
{
	ToolBarClick( VISION_FNC );
}

void wxMainWin::OnButton14Click(wxCommandEvent& event)
{
	ToolBarClick( DEMO_FNC );
}

void wxMainWin::OnconvEdgeBtnClick(wxCommandEvent& event)
{
	ToolBarClick( CONVEDGE_FNC );
}

void wxMainWin::OnmenuBtnClick(wxCommandEvent& event)
{
	ToolBarClick( NULL_FNC );
}

void wxMainWin::OnhomeBtnClick(wxCommandEvent& event)
{
	if( !SR->CheckOrigin() )
	{
		SR->ErrorManagement();
		return;
	}

	ToolBarClick( NULL_FNC );
	SR->ResetErrors();

	Enable( false );

	if( SR->ResetMotors( MODE_STARTPRINTING_POSITION ) == SR_ERROR )
	{
		SR->ErrorManagement();
		return;
	}

	Enable( true );

	smartLogger->Write( MSG_MOTORSTARTPOS );
}

void wxMainWin::OnoriginBtnClick(wxCommandEvent& event)
{
	if( SR->GetMachineState() == false )
	{
		smartLogger->Write( MSG_MACHINENOTACTIVATED );
		return;
	}
	if( SR->GetSafeModeState() == true )
	{
		smartLogger->Write( MSG_MACHINESAFEMODE );
		return;
	}
	if( SR->CheckOrigin() )
	{
		smartLogger->Write( MSG_ORIGIALREADYSET );
		if( wxMessageBox( MSG_ORIGIALREADYSET + wxString( wxT("\n") ) + MSG_ASKORIGINSEARCH, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, this ) != wxYES )
			return;
	}

	ToolBarClick( NULL_FNC );
	SR->ResetErrors();

	Enable( false );

	if( DisableAllMotors() == SR_ERROR )
	{
		SR->SetMachineState( false );
		onBtn->Enable( true );
		homeBtn->Enable( false );
		originBtn->Enable( false );
		standbyBtnEnable = false;
		Enable( true );
		return;
	}

	MACHINE_CONFIG(ENABLE_SEMAPHORE)
	//set voltage reduction for semaphore and buzzer
	if(SR->setOutputHardwareReduction() == SR_ERROR){
		smartLogger->Write( MSG_SEMAPHOREREDUCTION, MSG_ERROR );
		SR->SetMachineState( false );
		onBtn->Enable( true );
		homeBtn->Enable( false );
		originBtn->Enable( false );
		standbyBtnEnable = false;
		Enable( true );
	}
	MACHINE_CONFIG_END



	if( SR->EnableAllMotors() == SR_ERROR )
	{
		SR->SetMachineState( false );
		onBtn->Enable( true );
		homeBtn->Enable( false );
		originBtn->Enable( false );
		standbyBtnEnable = false;
		Enable( true );
		return;
	}
	if( SR->ResetMotors( MODE_SET_HOME ) == SR_ERROR )
	{
		SR->ErrorManagement();
		SR->SetMachineState( false );
		onBtn->Enable( true );
		homeBtn->Enable( false );
		originBtn->Enable( false );
		standbyBtnEnable = false;
		Enable( true );
		return;
	}

	// Warning for rack placed into loader...
	MACHINE_CONFIG( RACK_WARNING )
		if( DB->MachineParamsS.LoaderInstalled )
			wxMessageBox( MSG_REMOVERACK, MACHINE_NAME, wxOK | wxICON_WARNING, this );
	MACHINE_CONFIG_END

	if( OriginSearch() == SR_ERROR )
	{
		SR->SetMachineState( false );
		onBtn->Enable( true );
		homeBtn->Enable( false );
		originBtn->Enable( false );
		standbyBtnEnable = false;
		Enable( true );
		return;
	}

	/*if(SM->ScanSPISites()==SR_ERROR){
		wxMessageBox( "could not scan sites again", MACHINE_NAME, wxOK | wxICON_WARNING, this );
	}*/

	Enable( true );
}

void wxMainWin::OnonBtnClick(wxCommandEvent& event)
{
	onBtn->Enable( false );
	ToolBarClick( NULL_FNC );
	SR->ResetErrors();

	Enable( false );
	Update();

	if( SR->OpenSerialCom() == SR_ERROR )
	{
		SR->ErrorManagement();
		Enable( true );
		onBtn->Enable( true );
		return;
	}
	if( DisableAllMotors() == SR_ERROR && SR->GetSafeModeState() == false )
	{
		Enable( true );
		onBtn->Enable( true );
		return;
	}

	MACHINE_CONFIG(ENABLE_SEMAPHORE)
	//set voltage reduction for semaphore and buzzer
	if(SR->setOutputHardwareReduction() == SR_ERROR){
		smartLogger->Write( MSG_SEMAPHOREREDUCTION, MSG_ERROR );
		Enable( true );
		onBtn->Enable( true );
		return;
	}
	MACHINE_CONFIG_END


	if( SR->EnableAllMotors() == SR_ERROR && SR->GetSafeModeState() == false )
	{
		Enable( true );
		onBtn->Enable( true );
		return;
	}

	if( SR->ResetMotors( MODE_SET_HOME ) == SR_ERROR && SR->GetSafeModeState() == false )
	{
		SR->ErrorManagement();
		Enable( true );
		onBtn->Enable( true );
		return;
	}
	if( SR->SetAlarmLight( ALARMLIGHT_RED ) == SR_ERROR )
	{
		smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
	}

	// disable limits check
	if( SR->ActivateLimits( LIMITCHECK_OFF ) == SR_ERROR && SR->GetSafeModeState() == false )
	{
		SR->ErrorManagement();
		Enable( true );
		onBtn->Enable( true );
		return;
	}

	SR->SetMachineState( true );

	if( SR->GetSafeModeState() == false )
	{
		smartLogger->Write( MSG_MOTORINITENDED );

		if( wxMessageBox( MSG_ASKORIGINSEARCH, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, this ) == wxYES )
		{
			// Warning for rack placed into loader...
			MACHINE_CONFIG( RACK_WARNING )
				if( DB->MachineParamsS.LoaderInstalled )
					wxMessageBox( MSG_REMOVERACK, MACHINE_NAME, wxOK | wxICON_WARNING, this );
			MACHINE_CONFIG_END

			if( OriginSearch() == SR_ERROR )
			{
				Enable( true );
				homeBtn->Enable( true );
				originBtn->Enable( true );
				standbyBtnEnable = true;
				return;
			}
		}
	}

 /*	if(SM->ScanSPISites()==SR_ERROR){
			wxMessageBox( "could not scan sites again", MACHINE_NAME, wxOK | wxICON_WARNING, this );
		}*/

	homeBtn->Enable( true );
	originBtn->Enable( true );
	Enable( true );
	standbyBtnEnable = true;
}

void wxMainWin::OnoffBtnClick(wxCommandEvent& event)
{
	wxOffDialog offDialog( this, wxID_ANY, wxDefaultPosition, wxDefaultSize );

	offDialog.EnableStandbyButton( standbyBtnEnable );
	MACHINE_CONFIG( PASSWORD_ENABLE )
	offDialog.ShowExitButton( isPswL1Ok || isPswL2Ok ? true : false );
	MACHINE_CONFIG_END
	if( offDialog.ShowModal() == OFFDIALOG_CANCEL )
		return;

	ToolBarClick( NULL_FNC );
	Enable( false );

	if( SR->GetMachineState() )
	{
		if( SR->SetAlarmLight( ALARMLIGHT_OFF ) == SR_ERROR )
		{
			smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
		}
		if( SR->CheckOrigin() )
		{
			// Warning for rack placed into loader...
			MACHINE_CONFIG( RACK_WARNING )
				if( DB->MachineParamsS.LoaderInstalled )
					wxMessageBox( MSG_REMOVERACK, MACHINE_NAME, wxOK | wxICON_WARNING, this );
			MACHINE_CONFIG_END

			if( SR->ResetMotors( MODE_ZERO_POSITION ) == SR_ERROR )
			{
				SR->ErrorManagement();
			}
		}
	}

	// Disable all motors
	if( SR->isSerialComOpen() )
		DisableAllMotors();

	MACHINE_CONFIG(ENABLE_SEMAPHORE)
	//set voltage reduction for semaphore and buzzer
	if(SR->setOutputHardwareReduction() == SR_ERROR){
		smartLogger->Write( MSG_SEMAPHOREREDUCTION, MSG_ERROR );
		//return;
	}
	MACHINE_CONFIG_END


	SR->ResetOrigin();
	SR->SetMachineState( false );
	SR->ActivateSWLimits( false );
	SR->CloseSerialCom();

	Enable( true );

	if( SR->GetSafeModeState() == false )
		smartLogger->Write( MSG_MACHINEDISABLED, MSG_SUCCESS );

	if( offDialog.GetReturnCode() == OFFDIALOG_STANDBY )
	{
		onBtn->Enable( true );
		homeBtn->Enable( false );
		originBtn->Enable( false );
		standbyBtnEnable = false;
		SR->isBoardLoaded = false;

		SR->ActivateSafeMode( false );
	}
	else if( offDialog.GetReturnCode() == OFFDIALOG_SHUTDOWN )
	{
		MACHINE_CONFIG( MACHINE_ENABLE )
			wxGetApp().SetShutdown( true );
			Close();
		MACHINE_CONFIG_END
	}
	else
		Close();
}

void wxMainWin::OnClose(wxCloseEvent& event)
{
	Destroy();
}

void wxMainWin::OnbackupBtnClick(wxCommandEvent& event)
{
	wxString db_backup;
	if( ChooseLocation( db_backup ) == false )
		return;

	wxDateTime dateTime = wxDateTime::Now();
	db_backup += wxFileName::GetPathSeparator();
	db_backup += dateTime.FormatISODate() + wxT(" ") + dateTime.FormatISOTime() + FILE_DBBACKUPEXT;
	db_backup.Replace( wxT(":"), wxT(".") );

	int retVal = DB->Backup( db_backup );

	if( retVal == 0 )
		wxMessageBox( MSG_DBBACKUPOK, MACHINE_NAME, wxOK | wxICON_INFORMATION, this );
	else
		wxMessageBox( wxString::Format( MSG_DBBACKUPERROR, retVal ), MACHINE_NAME, wxOK | wxICON_ERROR, this );
}

void wxMainWin::OnrestoreBtnClick(wxCommandEvent& event)
{
	wxString db_backup;
	if( ChooseLocation( db_backup ) == false )
		return;

	wxArrayString names;
	wxDir dir( db_backup );
	wxString filename;

	names.Clear();
	for( bool cont = dir.GetFirst(&filename); cont; cont = dir.GetNext(&filename) )
	{
		if( filename.EndsWith( FILE_DBBACKUPEXT ) )
			names.Add( filename );
	}

	long index = wxGetSingleChoiceIndex( MSG_DBRESTORE, MACHINE_NAME, names, this );
	if( index == -1 )
		return;

	if( wxMessageBox( MSG_DBRESTOREAKS, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, this ) != wxYES )
		return;

	// backup current DB
	wxDateTime dateTime = wxDateTime::Now();
	db_backup += wxFileName::GetPathSeparator();
	db_backup += dateTime.FormatISODate() + wxT(" ") + dateTime.FormatISOTime() + FILE_DBBACKUPEXT;
	db_backup.Replace( wxT(":"), wxT(".") );

	DB->Backup( db_backup );

	// restore selected DB
	wxString db_restore = DIR_DBBACKUP;
	db_restore += wxFileName::GetPathSeparator();
	db_restore += names.Item( index );

	int retVal = DB->Restore( db_restore );

	if( retVal == 0 )
	{
		wxMessageBox( MSG_DBRESTOREOK, MACHINE_NAME, wxOK | wxICON_INFORMATION, this );

		// reload data (last opened production)
		DB->LoadMachineStructsFromDB();
		DB->LoadProductionNames();
		DB->LoadActualProduction();
		DB->LoadProductionStructsFromDB( DB->ActualProductionS.IdProd );
		productionDataPanel->UpdateProductionNames();

		CheckAndUpdateDB();
	}
	else
		wxMessageBox( wxString::Format( MSG_DBRESTOREERROR, retVal ), MACHINE_NAME, wxOK | wxICON_ERROR, this );
}

void wxMainWin::OnupdateBtnClick(wxCommandEvent& event)
{
	wxFileDialog *openFileDialog = new wxFileDialog( this, MSG_SWUPDATE, wxT(""), wxT(""), wxT("*.tws"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if( openFileDialog->ShowModal() == wxID_OK )
	{
		wxString swUpdateDir = DIR_SWUPDATE;
		swUpdateDir += wxFileName::GetPathSeparator();
		wxSwUpdate updater( openFileDialog->GetPath(), swUpdateDir );

		// retrieve version ( version.revision )
		wxString swVersion = SW_VERSION;
		long swVer, swRev;
		if( swVersion.Find( '.' ) == wxNOT_FOUND )
			return;
		swVersion.ToLong( &swVer );
		swVersion.Mid( swVersion.Find( '.' ) + 1 ).ToLong( &swRev );

		// Check file version and structure
		int retVal = updater.Check( swVer, swRev );

		if( retVal == 0 )
		{
			if( wxMessageBox( MSG_SWUPDATEEAKS, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, this ) != wxYES )
				return;

			// Extract file
			if( updater.Download() == 0 )
			{
				// Run updater and close application
				long childPID = updater.RunUpdater();
				if( childPID <= 0 )
				{
					wxMessageBox( "Error: wxExecute cannot run child process !", MACHINE_NAME, wxOK | wxICON_ERROR, this );
					return;
				}

				wxMilliSleep( 1000 );

				unsigned int timer = 0;
				int kill_ret = 0;
				while( (kill_ret = wxKill( childPID, wxSIGNONE )) != 0 && timer < TIMER_EXPIRE_TIME )
				{
					wxMilliSleep( 100 );
					timer += 100;
					wxTheApp->Yield();
				}
				if( timer >= TIMER_EXPIRE_TIME )
				{
					wxMessageBox( "Error: child process not running !", MACHINE_NAME, wxOK | wxICON_ERROR, this );
					return;
				}
				Close();
			}
			else
			{
				wxMessageBox( MSG_FILECORRUPTED, MACHINE_NAME, wxOK | wxICON_ERROR, this );
				return;
			}
		}
		else if( retVal == 1 )
		{
			wxMessageBox( MSG_FILEOBSOLETE, MACHINE_NAME, wxOK | wxICON_ERROR, this );
			return;
		}
		else
		{
			wxMessageBox( MSG_FILECORRUPTED, MACHINE_NAME, wxOK | wxICON_ERROR, this );
			return;
		}
    }
}



void wxMainWin::OnCameraZeroButtonClick(wxCommandEvent& event)
{
	ToolBarClick( CAMERAZERO_FNC );
}

/*void wxMainWin::OnCharPressed(wxKeyEvent& event){
	cout<<"Funzione chamata "<<endl;
	if(event.GetKeyCode() == WXK_ESCAPE){
		SR->SetBuzzerState(false);
	}
}*/


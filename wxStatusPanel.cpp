#include "images/png_images.h"
#include "wxStatusPanel.h"

//(*InternalHeaders(wxStatusPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/msgdlg.h>
#include "Messages.h"

const long wxStatusPanel::ID_STATUS_TIMER = wxNewId();

//(*IdInit(wxStatusPanel)
const long wxStatusPanel::ID_STATICBITMAP17 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT17 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP18 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT18 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP19 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT19 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP20 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT20 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP21 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT21 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP22 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT22 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP23 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT23 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP24 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT24 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP25 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT25 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP26 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT26 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP27 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT27 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP28 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT28 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP29 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT29 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP30 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT30 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP31 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT31 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP32 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT32 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP84 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT84 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP85 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT85 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP86 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT86 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP97 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT97 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP101 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT101 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP102 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT102 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP103 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT103 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP104 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT104 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP105 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT105 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP106 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT106 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP107 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT107 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP108 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT108 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP109 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT109 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP110 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT110 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP111 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT111 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP112 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT112 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP113 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT113 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP114 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT114 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP115 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT115 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP116 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT116 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP117 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT117 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP118 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT118 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP119 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT119 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP120 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT120 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP1 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT1 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP2 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT2 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP3 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT3 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP4 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT4 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP5 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT5 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP6 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT6 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP7 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT7 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP8 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT8 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP9 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT9 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP10 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT10 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP11 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT11 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP12 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT12 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP13 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT13 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP14 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT14 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP15 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT15 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP16 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT16 = wxNewId();
const long wxStatusPanel::ID_STATICLINE1 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP81 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT81 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP82 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT82 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP83 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT83 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP96 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT96 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP33 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT33 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP34 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT34 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP35 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT35 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP36 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT36 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP37 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT37 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP38 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT38 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP39 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT39 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP40 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT40 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP41 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT41 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP42 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT42 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP43 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT43 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP44 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT44 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP45 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT45 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP46 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT46 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP47 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT47 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP48 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT48 = wxNewId();
const long wxStatusPanel::ID_STATICLINE3 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP87 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT87 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP88 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT88 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP89 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT89 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP98 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT98 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP49 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT49 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP50 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT50 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP51 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT51 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP52 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT52 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP53 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT53 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP54 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT54 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP55 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT55 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP56 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT56 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP57 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT57 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP58 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT58 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP59 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT59 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP60 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT60 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP61 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT61 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP62 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT62 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP63 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT63 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP64 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT64 = wxNewId();
const long wxStatusPanel::ID_STATICLINE4 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP90 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT90 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP91 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT91 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP92 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT92 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP99 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT99 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP65 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT65 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP66 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT66 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP67 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT67 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP68 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT68 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP69 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT69 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP70 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT70 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP71 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT71 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP72 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT72 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP73 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT73 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP74 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT74 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP75 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT75 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP76 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT76 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP77 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT77 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP78 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT78 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP79 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT79 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP80 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT80 = wxNewId();
const long wxStatusPanel::ID_STATICLINE5 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP93 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT93 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP94 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT94 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP95 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT95 = wxNewId();
const long wxStatusPanel::ID_STATICBITMAP100 = wxNewId();
const long wxStatusPanel::ID_STATICTEXT100 = wxNewId();
const long wxStatusPanel::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxStatusPanel,wxPanel)
	//(*EventTable(wxStatusPanel)
	//*)
END_EVENT_TABLE()

wxStatusPanel::wxStatusPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxStatusPanel)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer16;
	wxStaticBoxSizer* StaticBoxSizer12;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticBoxSizer* StaticBoxSizer9;
	wxBoxSizer* BoxSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer7;
	wxStaticBoxSizer* StaticBoxSizer10;
	wxStaticBoxSizer* StaticBoxSizer8;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer6;
	wxFlexGridSizer* FlexGridSizer15;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer14;
	wxStaticBoxSizer* StaticBoxSizer11;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer13;
	wxFlexGridSizer* FlexGridSizer12;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer11;
	wxBoxSizer* BoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer5;
	
	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	BoxSizer3 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Table 1"));
	FlexGridSizer2 = new wxFlexGridSizer(5, 2, 0, 0);
	Table1Status1 = new wxStaticBitmap(this, ID_STATICBITMAP17, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP17"));
	FlexGridSizer2->Add(Table1Status1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText17 = new wxStaticText(this, ID_STATICTEXT17, _("Running"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	FlexGridSizer2->Add(StaticText17, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Table1Status2 = new wxStaticBitmap(this, ID_STATICBITMAP18, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP18"));
	FlexGridSizer2->Add(Table1Status2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText18 = new wxStaticText(this, ID_STATICTEXT18, _("Proc Error"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
	FlexGridSizer2->Add(StaticText18, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Table1Status3 = new wxStaticBitmap(this, ID_STATICBITMAP19, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP19"));
	FlexGridSizer2->Add(Table1Status3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText19 = new wxStaticText(this, ID_STATICTEXT19, _("Zero Search"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
	FlexGridSizer2->Add(StaticText19, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Table1Status4 = new wxStaticBitmap(this, ID_STATICBITMAP20, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP20"));
	FlexGridSizer2->Add(Table1Status4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText20 = new wxStaticText(this, ID_STATICTEXT20, _("Timeout"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
	FlexGridSizer2->Add(StaticText20, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Table1Status5 = new wxStaticBitmap(this, ID_STATICBITMAP21, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP21"));
	FlexGridSizer2->Add(Table1Status5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText21 = new wxStaticText(this, ID_STATICTEXT21, _("Limit Swtc"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
	FlexGridSizer2->Add(StaticText21, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(StaticBoxSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer6 = new wxStaticBoxSizer(wxVERTICAL, this, _("Table 2"));
	FlexGridSizer7 = new wxFlexGridSizer(5, 2, 0, 0);
	Table2Status1 = new wxStaticBitmap(this, ID_STATICBITMAP22, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP22"));
	FlexGridSizer7->Add(Table2Status1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText22 = new wxStaticText(this, ID_STATICTEXT22, _("Running"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
	FlexGridSizer7->Add(StaticText22, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Table2Status2 = new wxStaticBitmap(this, ID_STATICBITMAP23, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP23"));
	FlexGridSizer7->Add(Table2Status2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText23 = new wxStaticText(this, ID_STATICTEXT23, _("Proc Error"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
	FlexGridSizer7->Add(StaticText23, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Table2Status3 = new wxStaticBitmap(this, ID_STATICBITMAP24, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP24"));
	FlexGridSizer7->Add(Table2Status3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText24 = new wxStaticText(this, ID_STATICTEXT24, _("Zero Search"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
	FlexGridSizer7->Add(StaticText24, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Table2Status4 = new wxStaticBitmap(this, ID_STATICBITMAP25, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP25"));
	FlexGridSizer7->Add(Table2Status4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText25 = new wxStaticText(this, ID_STATICTEXT25, _("Timeout"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
	FlexGridSizer7->Add(StaticText25, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Table2Status5 = new wxStaticBitmap(this, ID_STATICBITMAP26, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP26"));
	FlexGridSizer7->Add(Table2Status5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText26 = new wxStaticText(this, ID_STATICTEXT26, _("Limit Swtc"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT26"));
	FlexGridSizer7->Add(StaticText26, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer6->Add(FlexGridSizer7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(StaticBoxSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer7 = new wxStaticBoxSizer(wxVERTICAL, this, _("Table 3"));
	FlexGridSizer11 = new wxFlexGridSizer(5, 2, 0, 0);
	Table3Status1 = new wxStaticBitmap(this, ID_STATICBITMAP27, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP27"));
	FlexGridSizer11->Add(Table3Status1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText27 = new wxStaticText(this, ID_STATICTEXT27, _("Running"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
	FlexGridSizer11->Add(StaticText27, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Table3Status2 = new wxStaticBitmap(this, ID_STATICBITMAP28, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP28"));
	FlexGridSizer11->Add(Table3Status2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText28 = new wxStaticText(this, ID_STATICTEXT28, _("Proc Error"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT28"));
	FlexGridSizer11->Add(StaticText28, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Table3Status3 = new wxStaticBitmap(this, ID_STATICBITMAP29, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP29"));
	FlexGridSizer11->Add(Table3Status3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText29 = new wxStaticText(this, ID_STATICTEXT29, _("Zero Search"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT29"));
	FlexGridSizer11->Add(StaticText29, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Table3Status4 = new wxStaticBitmap(this, ID_STATICBITMAP30, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP30"));
	FlexGridSizer11->Add(Table3Status4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText30 = new wxStaticText(this, ID_STATICTEXT30, _("Timeout"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT30"));
	FlexGridSizer11->Add(StaticText30, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Table3Status5 = new wxStaticBitmap(this, ID_STATICBITMAP31, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP31"));
	FlexGridSizer11->Add(Table3Status5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText31 = new wxStaticText(this, ID_STATICTEXT31, _("Limit Swtc"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT31"));
	FlexGridSizer11->Add(StaticText31, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer7->Add(FlexGridSizer11, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(StaticBoxSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer8 = new wxStaticBoxSizer(wxVERTICAL, this, _("Left Conv Width"));
	FlexGridSizer12 = new wxFlexGridSizer(5, 2, 0, 0);
	LConvWStatus1 = new wxStaticBitmap(this, ID_STATICBITMAP32, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP32"));
	FlexGridSizer12->Add(LConvWStatus1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText32 = new wxStaticText(this, ID_STATICTEXT32, _("Running"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT32"));
	FlexGridSizer12->Add(StaticText32, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	LConvWStatus2 = new wxStaticBitmap(this, ID_STATICBITMAP84, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP84"));
	FlexGridSizer12->Add(LConvWStatus2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText84 = new wxStaticText(this, ID_STATICTEXT84, _("Proc Error"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT84"));
	FlexGridSizer12->Add(StaticText84, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	LConvWStatus3 = new wxStaticBitmap(this, ID_STATICBITMAP85, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP85"));
	FlexGridSizer12->Add(LConvWStatus3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText85 = new wxStaticText(this, ID_STATICTEXT85, _("Zero Search"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT85"));
	FlexGridSizer12->Add(StaticText85, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	LConvWStatus4 = new wxStaticBitmap(this, ID_STATICBITMAP86, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP86"));
	FlexGridSizer12->Add(LConvWStatus4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText86 = new wxStaticText(this, ID_STATICTEXT86, _("Timeout"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT86"));
	FlexGridSizer12->Add(StaticText86, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	LConvWStatus5 = new wxStaticBitmap(this, ID_STATICBITMAP97, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP97"));
	FlexGridSizer12->Add(LConvWStatus5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText97 = new wxStaticText(this, ID_STATICTEXT97, _("Limit Swtc"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT97"));
	FlexGridSizer12->Add(StaticText97, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer8->Add(FlexGridSizer12, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(StaticBoxSizer8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer9 = new wxStaticBoxSizer(wxVERTICAL, this, _("Left Conv Feed"));
	FlexGridSizer13 = new wxFlexGridSizer(5, 2, 0, 0);
	LConvFStatus1 = new wxStaticBitmap(this, ID_STATICBITMAP101, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP101"));
	FlexGridSizer13->Add(LConvFStatus1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText101 = new wxStaticText(this, ID_STATICTEXT101, _("Running"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT101"));
	FlexGridSizer13->Add(StaticText101, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	LConvFStatus2 = new wxStaticBitmap(this, ID_STATICBITMAP102, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP102"));
	FlexGridSizer13->Add(LConvFStatus2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText102 = new wxStaticText(this, ID_STATICTEXT102, _("Proc Error"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT102"));
	FlexGridSizer13->Add(StaticText102, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	LConvFStatus3 = new wxStaticBitmap(this, ID_STATICBITMAP103, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP103"));
	FlexGridSizer13->Add(LConvFStatus3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText103 = new wxStaticText(this, ID_STATICTEXT103, _("Zero Search"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT103"));
	FlexGridSizer13->Add(StaticText103, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	LConvFStatus4 = new wxStaticBitmap(this, ID_STATICBITMAP104, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP104"));
	FlexGridSizer13->Add(LConvFStatus4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText104 = new wxStaticText(this, ID_STATICTEXT104, _("Timeout"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT104"));
	FlexGridSizer13->Add(StaticText104, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	LConvFStatus5 = new wxStaticBitmap(this, ID_STATICBITMAP105, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP105"));
	FlexGridSizer13->Add(LConvFStatus5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText105 = new wxStaticText(this, ID_STATICTEXT105, _("Limit Swtc"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT105"));
	FlexGridSizer13->Add(StaticText105, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer9->Add(FlexGridSizer13, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(StaticBoxSizer9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer10 = new wxStaticBoxSizer(wxVERTICAL, this, _("Center Conv Width"));
	FlexGridSizer14 = new wxFlexGridSizer(5, 2, 0, 0);
	CConvWStatus1 = new wxStaticBitmap(this, ID_STATICBITMAP106, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP106"));
	FlexGridSizer14->Add(CConvWStatus1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText106 = new wxStaticText(this, ID_STATICTEXT106, _("Running"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT106"));
	FlexGridSizer14->Add(StaticText106, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CConvWStatus2 = new wxStaticBitmap(this, ID_STATICBITMAP107, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP107"));
	FlexGridSizer14->Add(CConvWStatus2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText107 = new wxStaticText(this, ID_STATICTEXT107, _("Proc Error"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT107"));
	FlexGridSizer14->Add(StaticText107, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CConvWStatus3 = new wxStaticBitmap(this, ID_STATICBITMAP108, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP108"));
	FlexGridSizer14->Add(CConvWStatus3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText108 = new wxStaticText(this, ID_STATICTEXT108, _("Zero Search"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT108"));
	FlexGridSizer14->Add(StaticText108, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CConvWStatus4 = new wxStaticBitmap(this, ID_STATICBITMAP109, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP109"));
	FlexGridSizer14->Add(CConvWStatus4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText109 = new wxStaticText(this, ID_STATICTEXT109, _("Timeout"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT109"));
	FlexGridSizer14->Add(StaticText109, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CConvWStatus5 = new wxStaticBitmap(this, ID_STATICBITMAP110, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP110"));
	FlexGridSizer14->Add(CConvWStatus5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText110 = new wxStaticText(this, ID_STATICTEXT110, _("Limit Swtc"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT110"));
	FlexGridSizer14->Add(StaticText110, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer10->Add(FlexGridSizer14, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(StaticBoxSizer10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer11 = new wxStaticBoxSizer(wxVERTICAL, this, _("Center Conv Feed"));
	FlexGridSizer15 = new wxFlexGridSizer(5, 2, 0, 0);
	CConvFStatus1 = new wxStaticBitmap(this, ID_STATICBITMAP111, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP111"));
	FlexGridSizer15->Add(CConvFStatus1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText111 = new wxStaticText(this, ID_STATICTEXT111, _("Running"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT111"));
	FlexGridSizer15->Add(StaticText111, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CConvFStatus2 = new wxStaticBitmap(this, ID_STATICBITMAP112, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP112"));
	FlexGridSizer15->Add(CConvFStatus2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText112 = new wxStaticText(this, ID_STATICTEXT112, _("Proc Error"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT112"));
	FlexGridSizer15->Add(StaticText112, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CConvFStatus3 = new wxStaticBitmap(this, ID_STATICBITMAP113, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP113"));
	FlexGridSizer15->Add(CConvFStatus3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText113 = new wxStaticText(this, ID_STATICTEXT113, _("Zero Search"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT113"));
	FlexGridSizer15->Add(StaticText113, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CConvFStatus4 = new wxStaticBitmap(this, ID_STATICBITMAP114, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP114"));
	FlexGridSizer15->Add(CConvFStatus4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText114 = new wxStaticText(this, ID_STATICTEXT114, _("Timeout"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT114"));
	FlexGridSizer15->Add(StaticText114, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CConvFStatus5 = new wxStaticBitmap(this, ID_STATICBITMAP115, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP115"));
	FlexGridSizer15->Add(CConvFStatus5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText115 = new wxStaticText(this, ID_STATICTEXT115, _("Limit Swtc"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT115"));
	FlexGridSizer15->Add(StaticText115, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer11->Add(FlexGridSizer15, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(StaticBoxSizer11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer12 = new wxStaticBoxSizer(wxVERTICAL, this, _("Loader"));
	FlexGridSizer16 = new wxFlexGridSizer(5, 2, 0, 0);
	LoaderStatus1 = new wxStaticBitmap(this, ID_STATICBITMAP116, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP116"));
	FlexGridSizer16->Add(LoaderStatus1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText116 = new wxStaticText(this, ID_STATICTEXT116, _("Running"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT116"));
	FlexGridSizer16->Add(StaticText116, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	LoaderStatus2 = new wxStaticBitmap(this, ID_STATICBITMAP117, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP117"));
	FlexGridSizer16->Add(LoaderStatus2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText117 = new wxStaticText(this, ID_STATICTEXT117, _("Proc Error"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT117"));
	FlexGridSizer16->Add(StaticText117, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	LoaderStatus3 = new wxStaticBitmap(this, ID_STATICBITMAP118, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP118"));
	FlexGridSizer16->Add(LoaderStatus3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText118 = new wxStaticText(this, ID_STATICTEXT118, _("Zero Search"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT118"));
	FlexGridSizer16->Add(StaticText118, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	LoaderStatus4 = new wxStaticBitmap(this, ID_STATICBITMAP119, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP119"));
	FlexGridSizer16->Add(LoaderStatus4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText119 = new wxStaticText(this, ID_STATICTEXT119, _("Timeout"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT119"));
	FlexGridSizer16->Add(StaticText119, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	LoaderStatus5 = new wxStaticBitmap(this, ID_STATICBITMAP120, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP120"));
	FlexGridSizer16->Add(LoaderStatus5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText120 = new wxStaticText(this, ID_STATICTEXT120, _("Limit Swtc"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT120"));
	FlexGridSizer16->Add(StaticText120, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer12->Add(FlexGridSizer16, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(StaticBoxSizer12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Plate"));
	FlexGridSizer1 = new wxFlexGridSizer(8, 4, 0, 0);
	PlateStatus1 = new wxStaticBitmap(this, ID_STATICBITMAP1, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP1"));
	FlexGridSizer1->Add(PlateStatus1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Running"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlateStatus2 = new wxStaticBitmap(this, ID_STATICBITMAP2, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP2"));
	FlexGridSizer1->Add(PlateStatus2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Overcurrent"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlateStatus3 = new wxStaticBitmap(this, ID_STATICBITMAP3, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP3"));
	FlexGridSizer1->Add(PlateStatus3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Proc Error"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlateStatus4 = new wxStaticBitmap(this, ID_STATICBITMAP4, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP4"));
	FlexGridSizer1->Add(PlateStatus4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Timeout"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer1->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlateStatus5 = new wxStaticBitmap(this, ID_STATICBITMAP5, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP5"));
	FlexGridSizer1->Add(PlateStatus5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Zero Search"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer1->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlateStatus6 = new wxStaticBitmap(this, ID_STATICBITMAP6, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP6"));
	FlexGridSizer1->Add(PlateStatus6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Limit Swtc"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer1->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlateStatus7 = new wxStaticBitmap(this, ID_STATICBITMAP7, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP7"));
	FlexGridSizer1->Add(PlateStatus7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Danger"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer1->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlateStatus8 = new wxStaticBitmap(this, ID_STATICBITMAP8, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP8"));
	FlexGridSizer1->Add(PlateStatus8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Overspeed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer1->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlateStatus9 = new wxStaticBitmap(this, ID_STATICBITMAP9, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP9"));
	FlexGridSizer1->Add(PlateStatus9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("No Encoder"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer1->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlateStatus10 = new wxStaticBitmap(this, ID_STATICBITMAP10, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP10"));
	FlexGridSizer1->Add(PlateStatus10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("PID Spd On"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer1->Add(StaticText10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlateStatus11 = new wxStaticBitmap(this, ID_STATICBITMAP11, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP11"));
	FlexGridSizer1->Add(PlateStatus11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("PID Pos on"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer1->Add(StaticText11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlateStatus12 = new wxStaticBitmap(this, ID_STATICBITMAP12, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP12"));
	FlexGridSizer1->Add(PlateStatus12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Near Target"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer1->Add(StaticText12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlateStatus13 = new wxStaticBitmap(this, ID_STATICBITMAP13, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP13"));
	FlexGridSizer1->Add(PlateStatus13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("Multimove"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	FlexGridSizer1->Add(StaticText13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlateStatus14 = new wxStaticBitmap(this, ID_STATICBITMAP14, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP14"));
	FlexGridSizer1->Add(PlateStatus14, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText14 = new wxStaticText(this, ID_STATICTEXT14, _("No Follow"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	FlexGridSizer1->Add(StaticText14, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlateStatus15 = new wxStaticBitmap(this, ID_STATICBITMAP15, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP15"));
	FlexGridSizer1->Add(PlateStatus15, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _("Security"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	FlexGridSizer1->Add(StaticText15, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlateStatus16 = new wxStaticBitmap(this, ID_STATICBITMAP16, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP16"));
	FlexGridSizer1->Add(PlateStatus16, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT16, _("Steady Pos"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	FlexGridSizer1->Add(StaticText16, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	StaticBoxSizer1->Add(StaticLine1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6 = new wxFlexGridSizer(4, 2, 0, 0);
	PlateEncStatus1 = new wxStaticBitmap(this, ID_STATICBITMAP81, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP81"));
	FlexGridSizer6->Add(PlateEncStatus1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText81 = new wxStaticText(this, ID_STATICTEXT81, _("Magnetic Field"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT81"));
	FlexGridSizer6->Add(StaticText81, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlateEncStatus2 = new wxStaticBitmap(this, ID_STATICBITMAP82, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP82"));
	FlexGridSizer6->Add(PlateEncStatus2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText82 = new wxStaticText(this, ID_STATICTEXT82, _("Overrun"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT82"));
	FlexGridSizer6->Add(StaticText82, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlateEncStatus3 = new wxStaticBitmap(this, ID_STATICBITMAP83, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP83"));
	FlexGridSizer6->Add(PlateEncStatus3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText83 = new wxStaticText(this, ID_STATICTEXT83, _("Frame"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT83"));
	FlexGridSizer6->Add(StaticText83, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlateEncStatus4 = new wxStaticBitmap(this, ID_STATICBITMAP96, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP96"));
	FlexGridSizer6->Add(PlateEncStatus4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText96 = new wxStaticText(this, ID_STATICTEXT96, _("No Reception"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT96"));
	FlexGridSizer6->Add(StaticText96, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer6, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("Squeegees"));
	FlexGridSizer3 = new wxFlexGridSizer(8, 4, 0, 0);
	SqueegeesStatus1 = new wxStaticBitmap(this, ID_STATICBITMAP33, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP33"));
	FlexGridSizer3->Add(SqueegeesStatus1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText33 = new wxStaticText(this, ID_STATICTEXT33, _("Running"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT33"));
	FlexGridSizer3->Add(StaticText33, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SqueegeesStatus2 = new wxStaticBitmap(this, ID_STATICBITMAP34, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP34"));
	FlexGridSizer3->Add(SqueegeesStatus2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText34 = new wxStaticText(this, ID_STATICTEXT34, _("Overcurrent"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT34"));
	FlexGridSizer3->Add(StaticText34, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SqueegeesStatus3 = new wxStaticBitmap(this, ID_STATICBITMAP35, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP35"));
	FlexGridSizer3->Add(SqueegeesStatus3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText35 = new wxStaticText(this, ID_STATICTEXT35, _("Proc Error"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT35"));
	FlexGridSizer3->Add(StaticText35, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SqueegeesStatus4 = new wxStaticBitmap(this, ID_STATICBITMAP36, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP36"));
	FlexGridSizer3->Add(SqueegeesStatus4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText36 = new wxStaticText(this, ID_STATICTEXT36, _("Timeout"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT36"));
	FlexGridSizer3->Add(StaticText36, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SqueegeesStatus5 = new wxStaticBitmap(this, ID_STATICBITMAP37, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP37"));
	FlexGridSizer3->Add(SqueegeesStatus5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText37 = new wxStaticText(this, ID_STATICTEXT37, _("Zero Search"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT37"));
	FlexGridSizer3->Add(StaticText37, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SqueegeesStatus6 = new wxStaticBitmap(this, ID_STATICBITMAP38, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP38"));
	FlexGridSizer3->Add(SqueegeesStatus6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText38 = new wxStaticText(this, ID_STATICTEXT38, _("Limit Swtc"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT38"));
	FlexGridSizer3->Add(StaticText38, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SqueegeesStatus7 = new wxStaticBitmap(this, ID_STATICBITMAP39, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP39"));
	FlexGridSizer3->Add(SqueegeesStatus7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText39 = new wxStaticText(this, ID_STATICTEXT39, _("Danger"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT39"));
	FlexGridSizer3->Add(StaticText39, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SqueegeesStatus8 = new wxStaticBitmap(this, ID_STATICBITMAP40, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP40"));
	FlexGridSizer3->Add(SqueegeesStatus8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText40 = new wxStaticText(this, ID_STATICTEXT40, _("Overspeed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT40"));
	FlexGridSizer3->Add(StaticText40, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SqueegeesStatus9 = new wxStaticBitmap(this, ID_STATICBITMAP41, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP41"));
	FlexGridSizer3->Add(SqueegeesStatus9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText41 = new wxStaticText(this, ID_STATICTEXT41, _("No Encoder"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT41"));
	FlexGridSizer3->Add(StaticText41, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SqueegeesStatus10 = new wxStaticBitmap(this, ID_STATICBITMAP42, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP42"));
	FlexGridSizer3->Add(SqueegeesStatus10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText42 = new wxStaticText(this, ID_STATICTEXT42, _("PID Spd On"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT42"));
	FlexGridSizer3->Add(StaticText42, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SqueegeesStatus11 = new wxStaticBitmap(this, ID_STATICBITMAP43, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP43"));
	FlexGridSizer3->Add(SqueegeesStatus11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText43 = new wxStaticText(this, ID_STATICTEXT43, _("PID Pos on"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT43"));
	FlexGridSizer3->Add(StaticText43, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SqueegeesStatus12 = new wxStaticBitmap(this, ID_STATICBITMAP44, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP44"));
	FlexGridSizer3->Add(SqueegeesStatus12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText44 = new wxStaticText(this, ID_STATICTEXT44, _("Near Target"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT44"));
	FlexGridSizer3->Add(StaticText44, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SqueegeesStatus13 = new wxStaticBitmap(this, ID_STATICBITMAP45, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP45"));
	FlexGridSizer3->Add(SqueegeesStatus13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText45 = new wxStaticText(this, ID_STATICTEXT45, _("Multimove"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT45"));
	FlexGridSizer3->Add(StaticText45, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SqueegeesStatus14 = new wxStaticBitmap(this, ID_STATICBITMAP46, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP46"));
	FlexGridSizer3->Add(SqueegeesStatus14, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText46 = new wxStaticText(this, ID_STATICTEXT46, _("No Follow"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT46"));
	FlexGridSizer3->Add(StaticText46, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SqueegeesStatus15 = new wxStaticBitmap(this, ID_STATICBITMAP47, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP47"));
	FlexGridSizer3->Add(SqueegeesStatus15, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText47 = new wxStaticText(this, ID_STATICTEXT47, _("Security"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT47"));
	FlexGridSizer3->Add(StaticText47, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SqueegeesStatus16 = new wxStaticBitmap(this, ID_STATICBITMAP48, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP48"));
	FlexGridSizer3->Add(SqueegeesStatus16, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText48 = new wxStaticText(this, ID_STATICTEXT48, _("Steady Pos"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT48"));
	FlexGridSizer3->Add(StaticText48, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine3 = new wxStaticLine(this, ID_STATICLINE3, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE3"));
	StaticBoxSizer3->Add(StaticLine3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8 = new wxFlexGridSizer(3, 2, 0, 0);
	SqueegeesEncStatus1 = new wxStaticBitmap(this, ID_STATICBITMAP87, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP87"));
	FlexGridSizer8->Add(SqueegeesEncStatus1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText87 = new wxStaticText(this, ID_STATICTEXT87, _("Magnetic Field"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT87"));
	FlexGridSizer8->Add(StaticText87, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SqueegeesEncStatus2 = new wxStaticBitmap(this, ID_STATICBITMAP88, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP88"));
	FlexGridSizer8->Add(SqueegeesEncStatus2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText88 = new wxStaticText(this, ID_STATICTEXT88, _("Overrun"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT88"));
	FlexGridSizer8->Add(StaticText88, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SqueegeesEncStatus3 = new wxStaticBitmap(this, ID_STATICBITMAP89, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP89"));
	FlexGridSizer8->Add(SqueegeesEncStatus3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText89 = new wxStaticText(this, ID_STATICTEXT89, _("Frame"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT89"));
	FlexGridSizer8->Add(StaticText89, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SqueegeesEncStatus4 = new wxStaticBitmap(this, ID_STATICBITMAP98, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP98"));
	FlexGridSizer8->Add(SqueegeesEncStatus4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText98 = new wxStaticText(this, ID_STATICTEXT98, _("No Reception"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT98"));
	FlexGridSizer8->Add(StaticText98, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer8, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxVERTICAL, this, _("Camera X"));
	FlexGridSizer4 = new wxFlexGridSizer(8, 4, 0, 0);
	CamXStatus1 = new wxStaticBitmap(this, ID_STATICBITMAP49, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP49"));
	FlexGridSizer4->Add(CamXStatus1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText49 = new wxStaticText(this, ID_STATICTEXT49, _("Running"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT49"));
	FlexGridSizer4->Add(StaticText49, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamXStatus2 = new wxStaticBitmap(this, ID_STATICBITMAP50, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP50"));
	FlexGridSizer4->Add(CamXStatus2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText50 = new wxStaticText(this, ID_STATICTEXT50, _("Overcurrent"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT50"));
	FlexGridSizer4->Add(StaticText50, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamXStatus3 = new wxStaticBitmap(this, ID_STATICBITMAP51, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP51"));
	FlexGridSizer4->Add(CamXStatus3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText51 = new wxStaticText(this, ID_STATICTEXT51, _("Proc Error"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT51"));
	FlexGridSizer4->Add(StaticText51, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamXStatus4 = new wxStaticBitmap(this, ID_STATICBITMAP52, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP52"));
	FlexGridSizer4->Add(CamXStatus4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText52 = new wxStaticText(this, ID_STATICTEXT52, _("Timeout"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT52"));
	FlexGridSizer4->Add(StaticText52, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamXStatus5 = new wxStaticBitmap(this, ID_STATICBITMAP53, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP53"));
	FlexGridSizer4->Add(CamXStatus5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText53 = new wxStaticText(this, ID_STATICTEXT53, _("Zero Search"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT53"));
	FlexGridSizer4->Add(StaticText53, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamXStatus6 = new wxStaticBitmap(this, ID_STATICBITMAP54, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP54"));
	FlexGridSizer4->Add(CamXStatus6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText54 = new wxStaticText(this, ID_STATICTEXT54, _("Limit Swtc"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT54"));
	FlexGridSizer4->Add(StaticText54, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamXStatus7 = new wxStaticBitmap(this, ID_STATICBITMAP55, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP55"));
	FlexGridSizer4->Add(CamXStatus7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText55 = new wxStaticText(this, ID_STATICTEXT55, _("Danger"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT55"));
	FlexGridSizer4->Add(StaticText55, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamXStatus8 = new wxStaticBitmap(this, ID_STATICBITMAP56, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP56"));
	FlexGridSizer4->Add(CamXStatus8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText56 = new wxStaticText(this, ID_STATICTEXT56, _("Overspeed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT56"));
	FlexGridSizer4->Add(StaticText56, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamXStatus9 = new wxStaticBitmap(this, ID_STATICBITMAP57, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP57"));
	FlexGridSizer4->Add(CamXStatus9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText57 = new wxStaticText(this, ID_STATICTEXT57, _("No Encoder"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT57"));
	FlexGridSizer4->Add(StaticText57, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamXStatus10 = new wxStaticBitmap(this, ID_STATICBITMAP58, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP58"));
	FlexGridSizer4->Add(CamXStatus10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText58 = new wxStaticText(this, ID_STATICTEXT58, _("PID Spd On"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT58"));
	FlexGridSizer4->Add(StaticText58, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamXStatus11 = new wxStaticBitmap(this, ID_STATICBITMAP59, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP59"));
	FlexGridSizer4->Add(CamXStatus11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText59 = new wxStaticText(this, ID_STATICTEXT59, _("PID Pos on"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT59"));
	FlexGridSizer4->Add(StaticText59, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamXStatus12 = new wxStaticBitmap(this, ID_STATICBITMAP60, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP60"));
	FlexGridSizer4->Add(CamXStatus12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText60 = new wxStaticText(this, ID_STATICTEXT60, _("Near Target"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT60"));
	FlexGridSizer4->Add(StaticText60, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamXStatus13 = new wxStaticBitmap(this, ID_STATICBITMAP61, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP61"));
	FlexGridSizer4->Add(CamXStatus13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText61 = new wxStaticText(this, ID_STATICTEXT61, _("Multimove"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT61"));
	FlexGridSizer4->Add(StaticText61, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamXStatus14 = new wxStaticBitmap(this, ID_STATICBITMAP62, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP62"));
	FlexGridSizer4->Add(CamXStatus14, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText62 = new wxStaticText(this, ID_STATICTEXT62, _("No Follow"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT62"));
	FlexGridSizer4->Add(StaticText62, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamXStatus15 = new wxStaticBitmap(this, ID_STATICBITMAP63, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP63"));
	FlexGridSizer4->Add(CamXStatus15, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText63 = new wxStaticText(this, ID_STATICTEXT63, _("Security"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT63"));
	FlexGridSizer4->Add(StaticText63, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamXStatus16 = new wxStaticBitmap(this, ID_STATICBITMAP64, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP64"));
	FlexGridSizer4->Add(CamXStatus16, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText64 = new wxStaticText(this, ID_STATICTEXT64, _("Steady Pos"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT64"));
	FlexGridSizer4->Add(StaticText64, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(FlexGridSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine4 = new wxStaticLine(this, ID_STATICLINE4, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE4"));
	StaticBoxSizer4->Add(StaticLine4, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9 = new wxFlexGridSizer(3, 2, 0, 0);
	CamXEncStatus1 = new wxStaticBitmap(this, ID_STATICBITMAP90, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP90"));
	FlexGridSizer9->Add(CamXEncStatus1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText90 = new wxStaticText(this, ID_STATICTEXT90, _("Magnetic Field"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT90"));
	FlexGridSizer9->Add(StaticText90, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamXEncStatus2 = new wxStaticBitmap(this, ID_STATICBITMAP91, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP91"));
	FlexGridSizer9->Add(CamXEncStatus2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText91 = new wxStaticText(this, ID_STATICTEXT91, _("Overrun"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT91"));
	FlexGridSizer9->Add(StaticText91, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamXEncStatus3 = new wxStaticBitmap(this, ID_STATICBITMAP92, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP92"));
	FlexGridSizer9->Add(CamXEncStatus3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText92 = new wxStaticText(this, ID_STATICTEXT92, _("Frame"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT92"));
	FlexGridSizer9->Add(StaticText92, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamXEncStatus4 = new wxStaticBitmap(this, ID_STATICBITMAP99, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP99"));
	FlexGridSizer9->Add(CamXEncStatus4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText99 = new wxStaticText(this, ID_STATICTEXT99, _("No Reception"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT99"));
	FlexGridSizer9->Add(StaticText99, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(FlexGridSizer9, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxVERTICAL, this, _("Camera Y"));
	FlexGridSizer5 = new wxFlexGridSizer(8, 4, 0, 0);
	CamYStatus1 = new wxStaticBitmap(this, ID_STATICBITMAP65, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP65"));
	FlexGridSizer5->Add(CamYStatus1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText65 = new wxStaticText(this, ID_STATICTEXT65, _("Running"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT65"));
	FlexGridSizer5->Add(StaticText65, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamYStatus2 = new wxStaticBitmap(this, ID_STATICBITMAP66, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP66"));
	FlexGridSizer5->Add(CamYStatus2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText66 = new wxStaticText(this, ID_STATICTEXT66, _("Overcurrent"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT66"));
	FlexGridSizer5->Add(StaticText66, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamYStatus3 = new wxStaticBitmap(this, ID_STATICBITMAP67, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP67"));
	FlexGridSizer5->Add(CamYStatus3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText67 = new wxStaticText(this, ID_STATICTEXT67, _("Proc Error"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT67"));
	FlexGridSizer5->Add(StaticText67, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamYStatus4 = new wxStaticBitmap(this, ID_STATICBITMAP68, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP68"));
	FlexGridSizer5->Add(CamYStatus4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText68 = new wxStaticText(this, ID_STATICTEXT68, _("Timeout"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT68"));
	FlexGridSizer5->Add(StaticText68, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamYStatus5 = new wxStaticBitmap(this, ID_STATICBITMAP69, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP69"));
	FlexGridSizer5->Add(CamYStatus5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText69 = new wxStaticText(this, ID_STATICTEXT69, _("Zero Search"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT69"));
	FlexGridSizer5->Add(StaticText69, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamYStatus6 = new wxStaticBitmap(this, ID_STATICBITMAP70, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP70"));
	FlexGridSizer5->Add(CamYStatus6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText70 = new wxStaticText(this, ID_STATICTEXT70, _("Limit Swtc"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT70"));
	FlexGridSizer5->Add(StaticText70, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamYStatus7 = new wxStaticBitmap(this, ID_STATICBITMAP71, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP71"));
	FlexGridSizer5->Add(CamYStatus7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText71 = new wxStaticText(this, ID_STATICTEXT71, _("Danger"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT71"));
	FlexGridSizer5->Add(StaticText71, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamYStatus8 = new wxStaticBitmap(this, ID_STATICBITMAP72, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP72"));
	FlexGridSizer5->Add(CamYStatus8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText72 = new wxStaticText(this, ID_STATICTEXT72, _("Overspeed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT72"));
	FlexGridSizer5->Add(StaticText72, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamYStatus9 = new wxStaticBitmap(this, ID_STATICBITMAP73, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP73"));
	FlexGridSizer5->Add(CamYStatus9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText73 = new wxStaticText(this, ID_STATICTEXT73, _("No Encoder"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT73"));
	FlexGridSizer5->Add(StaticText73, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamYStatus10 = new wxStaticBitmap(this, ID_STATICBITMAP74, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP74"));
	FlexGridSizer5->Add(CamYStatus10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText74 = new wxStaticText(this, ID_STATICTEXT74, _("PID Spd On"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT74"));
	FlexGridSizer5->Add(StaticText74, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamYStatus11 = new wxStaticBitmap(this, ID_STATICBITMAP75, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP75"));
	FlexGridSizer5->Add(CamYStatus11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText75 = new wxStaticText(this, ID_STATICTEXT75, _("PID Pos on"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT75"));
	FlexGridSizer5->Add(StaticText75, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamYStatus12 = new wxStaticBitmap(this, ID_STATICBITMAP76, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP76"));
	FlexGridSizer5->Add(CamYStatus12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText76 = new wxStaticText(this, ID_STATICTEXT76, _("Near Target"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT76"));
	FlexGridSizer5->Add(StaticText76, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamYStatus13 = new wxStaticBitmap(this, ID_STATICBITMAP77, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP77"));
	FlexGridSizer5->Add(CamYStatus13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText77 = new wxStaticText(this, ID_STATICTEXT77, _("Multimove"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT77"));
	FlexGridSizer5->Add(StaticText77, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamYStatus14 = new wxStaticBitmap(this, ID_STATICBITMAP78, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP78"));
	FlexGridSizer5->Add(CamYStatus14, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText78 = new wxStaticText(this, ID_STATICTEXT78, _("No Follow"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT78"));
	FlexGridSizer5->Add(StaticText78, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamYStatus15 = new wxStaticBitmap(this, ID_STATICBITMAP79, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP79"));
	FlexGridSizer5->Add(CamYStatus15, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText79 = new wxStaticText(this, ID_STATICTEXT79, _("Security"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT79"));
	FlexGridSizer5->Add(StaticText79, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamYStatus16 = new wxStaticBitmap(this, ID_STATICBITMAP80, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP80"));
	FlexGridSizer5->Add(CamYStatus16, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText80 = new wxStaticText(this, ID_STATICTEXT80, _("Steady Pos"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT80"));
	FlexGridSizer5->Add(StaticText80, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(FlexGridSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine5 = new wxStaticLine(this, ID_STATICLINE5, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE5"));
	StaticBoxSizer5->Add(StaticLine5, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer10 = new wxFlexGridSizer(3, 2, 0, 0);
	CamYEncStatus1 = new wxStaticBitmap(this, ID_STATICBITMAP93, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP93"));
	FlexGridSizer10->Add(CamYEncStatus1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText93 = new wxStaticText(this, ID_STATICTEXT93, _("Magnetic Field"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT93"));
	FlexGridSizer10->Add(StaticText93, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamYEncStatus2 = new wxStaticBitmap(this, ID_STATICBITMAP94, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP94"));
	FlexGridSizer10->Add(CamYEncStatus2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText94 = new wxStaticText(this, ID_STATICTEXT94, _("Overrun"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT94"));
	FlexGridSizer10->Add(StaticText94, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamYEncStatus3 = new wxStaticBitmap(this, ID_STATICBITMAP95, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP95"));
	FlexGridSizer10->Add(CamYEncStatus3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText95 = new wxStaticText(this, ID_STATICTEXT95, _("Frame"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT95"));
	FlexGridSizer10->Add(StaticText95, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CamYEncStatus4 = new wxStaticBitmap(this, ID_STATICBITMAP100, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP100"));
	FlexGridSizer10->Add(CamYEncStatus4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText100 = new wxStaticText(this, ID_STATICTEXT100, _("No Reception"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT100"));
	FlexGridSizer10->Add(StaticText100, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(FlexGridSizer10, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(BoxSizer1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer3);
	statusTimer.SetOwner(this, ID_TIMER1);
	BoxSizer3->Fit(this);
	BoxSizer3->SetSizeHints(this);
	
	Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&wxStatusPanel::OnstatusTimerTrigger);
	Connect(wxEVT_PAINT,(wxObjectEventFunction)&wxStatusPanel::OnPaint);
	//*)
}

wxStatusPanel::~wxStatusPanel()
{
	//(*Destroy(wxStatusPanel)
	//*)
}

//----------------------------------------------------------------------------------
// Init
// Inizializza il controllo
//----------------------------------------------------------------------------------
int wxStatusPanel::Init( SRMachine* SRRef, SmartLog* smartLoggerRef )
{
	SR = SRRef;
	smartLogger = smartLoggerRef;

	isTimerBusy = false;

	plateStatus = 0;
	squeegeesStatus = 0;
	camXStatus = 0;
	camYStatus = 0;
	table1Status = 0;
	table2Status = 0;
	table3Status = 0;
	lConvWStatus = 0;
	lConvFStatus = 0;
	cConvWStatus = 0;
	cConvFStatus = 0;
	loaderStatus = 0;

	plateEncStatus = 0;
	squeegeesEncStatus = 0;
	camXEncStatus = 0;
	camYEncStatus = 0;
	
	PlateStatus1->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	PlateStatus2->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	PlateStatus3->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	PlateStatus4->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	PlateStatus5->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	PlateStatus6->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	PlateStatus7->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	PlateStatus8->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	PlateStatus9->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	PlateStatus10->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	PlateStatus11->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	PlateStatus12->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	PlateStatus13->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	PlateStatus14->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	PlateStatus15->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	PlateStatus16->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	PlateEncStatus1->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	PlateEncStatus2->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	PlateEncStatus3->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	PlateEncStatus4->SetBitmap( wxMEMORY_BITMAP( led_gray ) );

	SqueegeesStatus1->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	SqueegeesStatus2->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	SqueegeesStatus3->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	SqueegeesStatus4->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	SqueegeesStatus5->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	SqueegeesStatus6->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	SqueegeesStatus7->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	SqueegeesStatus8->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	SqueegeesStatus9->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	SqueegeesStatus10->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	SqueegeesStatus11->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	SqueegeesStatus12->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	SqueegeesStatus13->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	SqueegeesStatus14->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	SqueegeesStatus15->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	SqueegeesStatus16->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	SqueegeesEncStatus1->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	SqueegeesEncStatus2->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	SqueegeesEncStatus3->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	SqueegeesEncStatus4->SetBitmap( wxMEMORY_BITMAP( led_gray ) );

	CamXStatus1->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamXStatus2->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamXStatus3->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamXStatus4->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamXStatus5->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamXStatus6->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamXStatus7->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamXStatus8->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamXStatus9->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamXStatus10->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamXStatus11->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamXStatus12->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamXStatus13->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamXStatus14->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamXStatus15->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamXStatus16->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamXEncStatus1->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamXEncStatus2->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamXEncStatus3->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamXEncStatus4->SetBitmap( wxMEMORY_BITMAP( led_gray ) );

	CamYStatus1->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamYStatus2->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamYStatus3->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamYStatus4->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamYStatus5->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamYStatus6->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamYStatus7->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamYStatus8->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamYStatus9->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamYStatus10->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamYStatus11->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamYStatus12->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamYStatus13->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamYStatus14->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamYStatus15->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamYStatus16->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamYEncStatus1->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamYEncStatus2->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamYEncStatus3->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CamYEncStatus4->SetBitmap( wxMEMORY_BITMAP( led_gray ) );

	Table1Status1->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	Table1Status2->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	Table1Status3->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	Table1Status4->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	Table1Status5->SetBitmap( wxMEMORY_BITMAP( led_gray ) );

	Table2Status1->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	Table2Status2->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	Table2Status3->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	Table2Status4->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	Table2Status5->SetBitmap( wxMEMORY_BITMAP( led_gray ) );

	Table3Status1->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	Table3Status2->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	Table3Status3->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	Table3Status4->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	Table3Status5->SetBitmap( wxMEMORY_BITMAP( led_gray ) );

	LConvWStatus1->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	LConvWStatus2->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	LConvWStatus3->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	LConvWStatus4->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	LConvWStatus5->SetBitmap( wxMEMORY_BITMAP( led_gray ) );

	LConvFStatus1->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	LConvFStatus2->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	LConvFStatus3->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	LConvFStatus4->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	LConvFStatus5->SetBitmap( wxMEMORY_BITMAP( led_gray ) );

	CConvWStatus1->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CConvWStatus2->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CConvWStatus3->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CConvWStatus4->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CConvWStatus5->SetBitmap( wxMEMORY_BITMAP( led_gray ) );

	CConvFStatus1->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CConvFStatus2->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CConvFStatus3->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CConvFStatus4->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	CConvFStatus5->SetBitmap( wxMEMORY_BITMAP( led_gray ) );

	LoaderStatus1->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	LoaderStatus2->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	LoaderStatus3->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	LoaderStatus4->SetBitmap( wxMEMORY_BITMAP( led_gray ) );
	LoaderStatus5->SetBitmap( wxMEMORY_BITMAP( led_gray ) );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// ShowControl
//
//----------------------------------------------------------------------------------
int wxStatusPanel::ShowControl()
{
	statusTimer.Start( STATUSTIMER, true );

	TransferDataToWindow();

	return SR_OK;
}

//----------------------------------------------------------------------------------
// HideControl
//
//----------------------------------------------------------------------------------
int wxStatusPanel::HideControl()
{
	statusTimer.Stop();

	return SR_OK;
}

void wxStatusPanel::OnstatusTimerTrigger(wxTimerEvent& event)
{
	if( SR->GetMachineState() == false )
		return;

	if( isTimerBusy )
		return;

	isTimerBusy = true;

	// Lettura di tutti gli ingressi della macchina
	bool isError = false;

	if( SR->GetMotorStatus( MOTOR_PLATE_ID, plateStatus ) == SR_ERROR )
		isError = true;
	if( SR->GetEncoderStatus( MOTOR_PLATE_ID, plateEncStatus ) == SR_ERROR )
		isError = true;
	if( SR->GetMotorStatus( MOTOR_SQUEEGEES_ID, squeegeesStatus ) == SR_ERROR )
		isError = true;
	if( SR->GetEncoderStatus( MOTOR_SQUEEGEES_ID, squeegeesEncStatus ) == SR_ERROR )
		isError = true;
	if( SR->GetMotorStatus( MOTOR_CAMERAX_ID, camXStatus ) == SR_ERROR )
		isError = true;
	if( SR->GetEncoderStatus( MOTOR_CAMERAX_ID, camXEncStatus ) == SR_ERROR )
		isError = true;
	if( SR->GetMotorStatus( MOTOR_CAMERAY_ID, camYStatus ) == SR_ERROR )
		isError = true;
	if( SR->GetEncoderStatus( MOTOR_CAMERAY_ID, camYEncStatus ) == SR_ERROR )
		isError = true;
	if( SR->GetEncoderStatus( MOTOR_TABLE1_ID, table1Status ) == SR_ERROR )
		isError = true;
	if( SR->GetEncoderStatus( MOTOR_TABLE2_ID, table2Status ) == SR_ERROR )
		isError = true;
	if( SR->GetEncoderStatus( MOTOR_TABLE3_ID, table3Status ) == SR_ERROR )
		isError = true;
	if( SR->GetEncoderStatus( MOTOR_LCONV_WIDTH_ID, lConvWStatus ) == SR_ERROR )
		isError = true;
	if( SR->GetEncoderStatus( MOTOR_LCONV_FEED_ID, lConvFStatus ) == SR_ERROR )
		isError = true;
	if( SR->GetEncoderStatus( MOTOR_CCONV_WIDTH_ID, cConvWStatus ) == SR_ERROR )
		isError = true;
	if( SR->GetEncoderStatus( MOTOR_CCONV_FEED_ID, cConvFStatus ) == SR_ERROR )
		isError = true;
	if( SR->GetEncoderStatus( MOTOR_LOADER_ID, loaderStatus ) == SR_ERROR )
		isError = true;

	if( isError == true )
		smartLogger->Write( MSG_MOTORCOMMERROR, MSG_ERROR );

	isTimerBusy = false;

	wxPaintEvent e( ID_STATUS_TIMER );
	wxPostEvent( this, e );

	statusTimer.Start( STATUSTIMER, true );
}

void wxStatusPanel::OnPaint(wxPaintEvent& event)
{
	// Check if event is raised by statusTimer
	if( event.GetId() == ID_STATUS_TIMER )
	{
		Freeze();

		PlateStatus1->SetBitmap( (plateStatus & MOTOR_RUNNING) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		PlateStatus2->SetBitmap( (plateStatus & MOTOR_OVERCURRENT) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		PlateStatus3->SetBitmap( (plateStatus & MOTOR_PROCERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		PlateStatus4->SetBitmap( (plateStatus & MOTOR_TIMEOUT) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		PlateStatus5->SetBitmap( (plateStatus & MOTOR_ZERO) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		PlateStatus6->SetBitmap( (plateStatus & MOTOR_OVERRUN) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		PlateStatus7->SetBitmap( (plateStatus & MOTOR_DANGER) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		PlateStatus8->SetBitmap( (plateStatus & MOTOR_OVERSPEED) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		PlateStatus9->SetBitmap( (plateStatus & MOTOR_NOENC) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		PlateStatus10->SetBitmap( (plateStatus & MOTOR_PIDSPDON) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		PlateStatus11->SetBitmap( (plateStatus & MOTOR_PIDPOSON) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		PlateStatus12->SetBitmap( (plateStatus & MOTOR_NEARTARGET) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		PlateStatus13->SetBitmap( (plateStatus & MOTOR_MULTIMOVE) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		PlateStatus14->SetBitmap( (plateStatus & MOTOR_NO_FOLLOW) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		PlateStatus15->SetBitmap( (plateStatus & MOTOR_SECURITY) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		PlateStatus16->SetBitmap( (plateStatus & MOTOR_STEADYPOS) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		PlateEncStatus1->SetBitmap( (plateEncStatus & ENC_MF_ERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		PlateEncStatus2->SetBitmap( (plateEncStatus & ENC_OVERRUN_ERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		PlateEncStatus3->SetBitmap( (plateEncStatus & ENC_FRAME_ERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		PlateEncStatus4->SetBitmap( (plateEncStatus & ENC_NOREC_ERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );

		SqueegeesStatus1->SetBitmap( (squeegeesStatus & MOTOR_RUNNING) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		SqueegeesStatus2->SetBitmap( (squeegeesStatus & MOTOR_OVERCURRENT) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		SqueegeesStatus3->SetBitmap( (squeegeesStatus & MOTOR_PROCERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		SqueegeesStatus4->SetBitmap( (squeegeesStatus & MOTOR_TIMEOUT) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		SqueegeesStatus5->SetBitmap( (squeegeesStatus & MOTOR_ZERO) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		SqueegeesStatus6->SetBitmap( (squeegeesStatus & MOTOR_OVERRUN) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		SqueegeesStatus7->SetBitmap( (squeegeesStatus & MOTOR_DANGER) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		SqueegeesStatus8->SetBitmap( (squeegeesStatus & MOTOR_OVERSPEED) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		SqueegeesStatus9->SetBitmap( (squeegeesStatus & MOTOR_NOENC) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		SqueegeesStatus10->SetBitmap( (squeegeesStatus & MOTOR_PIDSPDON) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		SqueegeesStatus11->SetBitmap( (squeegeesStatus & MOTOR_PIDPOSON) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		SqueegeesStatus12->SetBitmap( (squeegeesStatus & MOTOR_NEARTARGET) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		SqueegeesStatus13->SetBitmap( (squeegeesStatus & MOTOR_MULTIMOVE) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		SqueegeesStatus14->SetBitmap( (squeegeesStatus & MOTOR_NO_FOLLOW) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		SqueegeesStatus15->SetBitmap( (squeegeesStatus & MOTOR_SECURITY) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		SqueegeesStatus16->SetBitmap( (squeegeesStatus & MOTOR_STEADYPOS) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		SqueegeesEncStatus1->SetBitmap( (squeegeesEncStatus & ENC_MF_ERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		SqueegeesEncStatus2->SetBitmap( (squeegeesEncStatus & ENC_OVERRUN_ERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		SqueegeesEncStatus3->SetBitmap( (squeegeesEncStatus & ENC_FRAME_ERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		SqueegeesEncStatus4->SetBitmap( (squeegeesEncStatus & ENC_NOREC_ERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );

		CamXStatus1->SetBitmap( (camXStatus & MOTOR_RUNNING) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamXStatus2->SetBitmap( (camXStatus & MOTOR_OVERCURRENT) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamXStatus3->SetBitmap( (camXStatus & MOTOR_PROCERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamXStatus4->SetBitmap( (camXStatus & MOTOR_TIMEOUT) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamXStatus5->SetBitmap( (camXStatus & MOTOR_ZERO) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamXStatus6->SetBitmap( (camXStatus & MOTOR_OVERRUN) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamXStatus7->SetBitmap( (camXStatus & MOTOR_DANGER) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamXStatus8->SetBitmap( (camXStatus & MOTOR_OVERSPEED) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamXStatus9->SetBitmap( (camXStatus & MOTOR_NOENC) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamXStatus10->SetBitmap( (camXStatus & MOTOR_PIDSPDON) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamXStatus11->SetBitmap( (camXStatus & MOTOR_PIDPOSON) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamXStatus12->SetBitmap( (camXStatus & MOTOR_NEARTARGET) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamXStatus13->SetBitmap( (camXStatus & MOTOR_MULTIMOVE) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamXStatus14->SetBitmap( (camXStatus & MOTOR_NO_FOLLOW) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamXStatus15->SetBitmap( (camXStatus & MOTOR_SECURITY) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamXStatus16->SetBitmap( (camXStatus & MOTOR_STEADYPOS) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamXEncStatus1->SetBitmap( (camXEncStatus & ENC_MF_ERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamXEncStatus2->SetBitmap( (camXEncStatus & ENC_OVERRUN_ERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamXEncStatus3->SetBitmap( (camXEncStatus & ENC_FRAME_ERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamXEncStatus4->SetBitmap( (camXEncStatus & ENC_NOREC_ERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );

		CamYStatus1->SetBitmap( (camYStatus & MOTOR_RUNNING) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamYStatus2->SetBitmap( (camYStatus & MOTOR_OVERCURRENT) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamYStatus3->SetBitmap( (camYStatus & MOTOR_PROCERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamYStatus4->SetBitmap( (camYStatus & MOTOR_TIMEOUT) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamYStatus5->SetBitmap( (camYStatus & MOTOR_ZERO) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamYStatus6->SetBitmap( (camYStatus & MOTOR_OVERRUN) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamYStatus7->SetBitmap( (camYStatus & MOTOR_DANGER) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamYStatus8->SetBitmap( (camYStatus & MOTOR_OVERSPEED) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamYStatus9->SetBitmap( (camYStatus & MOTOR_NOENC) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamYStatus10->SetBitmap( (camYStatus & MOTOR_PIDSPDON) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamYStatus11->SetBitmap( (camYStatus & MOTOR_PIDPOSON) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamYStatus12->SetBitmap( (camYStatus & MOTOR_NEARTARGET) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamYStatus13->SetBitmap( (camYStatus & MOTOR_MULTIMOVE) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamYStatus14->SetBitmap( (camYStatus & MOTOR_NO_FOLLOW) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamYStatus15->SetBitmap( (camYStatus & MOTOR_SECURITY) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamYStatus16->SetBitmap( (camYStatus & MOTOR_STEADYPOS) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamYEncStatus1->SetBitmap( (camYEncStatus & ENC_MF_ERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamYEncStatus2->SetBitmap( (camYEncStatus & ENC_OVERRUN_ERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamYEncStatus3->SetBitmap( (camYEncStatus & ENC_FRAME_ERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CamYEncStatus4->SetBitmap( (camYEncStatus & ENC_NOREC_ERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );

		Table1Status1->SetBitmap( (table1Status & MOTOR_RUNNING) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		Table1Status2->SetBitmap( (table1Status & MOTOR_PROCERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		Table1Status3->SetBitmap( (table1Status & MOTOR_ZERO) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		Table1Status4->SetBitmap( (table1Status & MOTOR_TIMEOUT) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		Table1Status5->SetBitmap( (table1Status & MOTOR_OVERRUN) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );

		Table2Status1->SetBitmap( (table2Status & MOTOR_RUNNING) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		Table2Status2->SetBitmap( (table2Status & MOTOR_PROCERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		Table2Status3->SetBitmap( (table2Status & MOTOR_ZERO) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		Table2Status4->SetBitmap( (table2Status & MOTOR_TIMEOUT) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		Table2Status5->SetBitmap( (table2Status & MOTOR_OVERRUN) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );

		Table3Status1->SetBitmap( (table3Status & MOTOR_RUNNING) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		Table3Status2->SetBitmap( (table3Status & MOTOR_PROCERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		Table3Status3->SetBitmap( (table3Status & MOTOR_ZERO) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		Table3Status4->SetBitmap( (table3Status & MOTOR_TIMEOUT) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		Table3Status5->SetBitmap( (table3Status & MOTOR_OVERRUN) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );

		LConvWStatus1->SetBitmap( (lConvWStatus & MOTOR_RUNNING) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		LConvWStatus2->SetBitmap( (lConvWStatus & MOTOR_PROCERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		LConvWStatus3->SetBitmap( (lConvWStatus & MOTOR_ZERO) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		LConvWStatus4->SetBitmap( (lConvWStatus & MOTOR_TIMEOUT) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		LConvWStatus5->SetBitmap( (lConvWStatus & MOTOR_OVERRUN) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );

		LConvFStatus1->SetBitmap( (lConvFStatus & MOTOR_RUNNING) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		LConvFStatus2->SetBitmap( (lConvFStatus & MOTOR_PROCERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		LConvFStatus3->SetBitmap( (lConvFStatus & MOTOR_ZERO) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		LConvFStatus4->SetBitmap( (lConvFStatus & MOTOR_TIMEOUT) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		LConvFStatus5->SetBitmap( (lConvFStatus & MOTOR_OVERRUN) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );

		CConvWStatus1->SetBitmap( (cConvWStatus & MOTOR_RUNNING) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CConvWStatus2->SetBitmap( (cConvWStatus & MOTOR_PROCERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CConvWStatus3->SetBitmap( (cConvWStatus & MOTOR_ZERO) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CConvWStatus4->SetBitmap( (cConvWStatus & MOTOR_TIMEOUT) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CConvWStatus5->SetBitmap( (cConvWStatus & MOTOR_OVERRUN) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );

		CConvFStatus1->SetBitmap( (cConvFStatus & MOTOR_RUNNING) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CConvFStatus2->SetBitmap( (cConvFStatus & MOTOR_PROCERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CConvFStatus3->SetBitmap( (cConvFStatus & MOTOR_ZERO) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CConvFStatus4->SetBitmap( (cConvFStatus & MOTOR_TIMEOUT) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		CConvFStatus5->SetBitmap( (cConvFStatus & MOTOR_OVERRUN) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );

		LoaderStatus1->SetBitmap( (loaderStatus & MOTOR_RUNNING) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		LoaderStatus2->SetBitmap( (loaderStatus & MOTOR_PROCERROR) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		LoaderStatus3->SetBitmap( (loaderStatus & MOTOR_ZERO) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		LoaderStatus4->SetBitmap( (loaderStatus & MOTOR_TIMEOUT) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );
		LoaderStatus5->SetBitmap( (loaderStatus & MOTOR_OVERRUN) ? wxMEMORY_BITMAP( led_green ) : wxMEMORY_BITMAP( led_gray ) );

		Thaw();
	}
	event.Skip();
}

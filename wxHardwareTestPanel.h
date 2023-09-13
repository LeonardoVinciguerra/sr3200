#ifndef WXHARDWARETESTPANEL_H
#define WXHARDWARETESTPANEL_H

//(*Headers(wxHardwareTestPanel)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/statbmp.h>
#include <wx/button.h>
#include <wx/timer.h>
//*)

#include "SRMachine.h"
#include "SmartLog.h"
#include "wxControlPanel.h"

class wxHardwareTestPanel: public wxPanel
{
	public:

		wxHardwareTestPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxHardwareTestPanel();

		//(*Declarations(wxHardwareTestPanel)
		wxStaticText* StaticText10;
		wxStaticText* StaticText9;
		wxStaticBitmap* StaticBitmap2;
		wxStaticText* StaticText20;
		wxStaticBitmap* StaticBitmap8;
		wxStaticBitmap* StaticBitmap5;
		wxStaticBitmap* StaticBitmap14;
		wxStaticBitmap* StaticBitmap7;
		wxCheckBox* safeModeCheck;
		wxStaticText* StaticText13;
		wxStaticText* StaticText2;
		wxStaticText* StaticText14;
		wxStaticBitmap* StaticBitmap16;
		wxStaticBitmap* StaticBitmap11;
		wxStaticText* StaticText6;
		wxStaticBitmap* StaticBitmap1;
		wxStaticBitmap* StaticBitmap17;
		wxStaticText* StaticText19;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxStaticBitmap* StaticBitmap4;
		wxStaticBitmap* StaticBitmap19;
		wxStaticText* StaticText18;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticBitmap* StaticBitmap21;
		wxStaticText* StaticText21;
		wxCheckBox* disableLimitsCheck;
		wxStaticBitmap* StaticBitmap15;
		wxStaticBitmap* StaticBitmap10;
		wxStaticBitmap* StaticBitmap20;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxTimer inputsTimer;
		wxStaticText* StaticText15;
		wxStaticBitmap* StaticBitmap9;
		wxStaticText* StaticText12;
		wxStaticBitmap* StaticBitmap12;
		wxStaticBitmap* StaticBitmap6;
		wxButton* table1OnFocus;
		wxStaticBitmap* StaticBitmap13;
		wxStaticBitmap* StaticBitmap18;
		wxStaticText* StaticText17;
		wxStaticText* StaticText4;
		wxCheckBox* readInputsCheck;
		wxStaticText* StaticText16;
		wxStaticBitmap* StaticBitmap3;
		//*)

	protected:

		//(*Identifiers(wxHardwareTestPanel)
		static const long ID_BUTTON1;
		static const long ID_CHECKBOX1;
		static const long ID_STATICTEXT1;
		static const long ID_STATICBITMAP1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICBITMAP2;
		static const long ID_STATICTEXT15;
		static const long ID_STATICBITMAP15;
		static const long ID_STATICTEXT3;
		static const long ID_STATICBITMAP3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICBITMAP4;
		static const long ID_STATICTEXT14;
		static const long ID_STATICBITMAP14;
		static const long ID_STATICTEXT5;
		static const long ID_STATICBITMAP5;
		static const long ID_STATICTEXT6;
		static const long ID_STATICBITMAP6;
		static const long ID_STATICTEXT17;
		static const long ID_STATICBITMAP17;
		static const long ID_STATICTEXT7;
		static const long ID_STATICBITMAP7;
		static const long ID_STATICTEXT8;
		static const long ID_STATICBITMAP8;
		static const long ID_STATICTEXT12;
		static const long ID_STATICBITMAP12;
		static const long ID_STATICTEXT9;
		static const long ID_STATICBITMAP9;
		static const long ID_STATICTEXT11;
		static const long ID_STATICBITMAP11;
		static const long ID_STATICTEXT18;
		static const long ID_STATICBITMAP18;
		static const long ID_STATICTEXT10;
		static const long ID_STATICBITMAP10;
		static const long ID_STATICTEXT19;
		static const long ID_STATICBITMAP19;
		static const long ID_STATICTEXT16;
		static const long ID_STATICBITMAP16;
		static const long ID_STATICTEXT13;
		static const long ID_STATICBITMAP13;
		static const long ID_STATICTEXT20;
		static const long ID_STATICBITMAP20;
		static const long ID_STATICTEXT23;
		static const long ID_STATICBITMAP21;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_TIMER1;
		//*)

	private:

		//(*Handlers(wxHardwareTestPanel)
		void OnreadInputsCheckClick(wxCommandEvent& event);
		void OndisableLimitsCheckClick(wxCommandEvent& event);
		void OnsafeModeCheckClick(wxCommandEvent& event);
		void OninputsTimerTrigger(wxTimerEvent& event);
		void OnPaint(wxPaintEvent& event);
		void Ontable1OnFocusClick(wxCommandEvent& event);
		//*)

	public:
		int Init( SRMachine* SRRef, SmartLog* smartLoggerRef, wxControlPanel *controlPanelRef );
		int ShowControl();
		int HideControl();

		void ResetInputs();

		int SelectInput( int inputId );

	private:
		
		static const long ID_INPUT_TIMER;

		SRMachine *SR;
		SmartLog *smartLogger;
		wxControlPanel *controlPanel;

		bool isFirstTime;
		bool limitsState;
		bool isTimerBusy;

		int inputs[NUM_MOTORS+1][6];

		DECLARE_EVENT_TABLE()
};

#endif

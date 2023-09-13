#ifndef WXMOTORSDATAPANEL_H
#define WXMOTORSDATAPANEL_H

//(*Headers(wxMotorsDataPanel)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/listbox.h>
#include <wx/spinctrl.h>
#include <wx/statline.h>
#include <wx/panel.h>
#include <wx/filedlg.h>
#include <wx/button.h>
#include <wx/combobox.h>
//*)

#include "SRMachine.h"
#include "SmartLog.h"


class wxMotorsDataPanel: public wxPanel
{
	public:

		wxMotorsDataPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxMotorsDataPanel();

		//(*Declarations(wxMotorsDataPanel)
		wxStaticText* StaticText10;
		wxComboBox* driverIdCombo;
		wxStaticText* StaticText22;
		wxStaticText* StaticText9;
		wxStaticText* StaticText20;
		wxListBox* speedList;
		wxComboBox* stepperPortCombo;
		wxButton* uploadBtn;
		wxTextCtrl* decHEdit;
		wxGridSizer* GridSizerBrush;
		wxTextCtrl* jerkEdit;
		wxTextCtrl* accNEdit;
		wxTextCtrl* PPREdit;
		wxStaticText* StaticText29;
		wxTextCtrl* speedLEdit;
		wxTextCtrl* redCurEdit;
		wxButton* openFileBtn;
		wxTextCtrl* decLEdit;
		wxTextCtrl* PTMEdit;
		wxStaticText* StaticText37;
		wxStaticText* StaticText13;
		wxStaticText* StaticText33;
		wxStaticText* StaticText2;
		wxStaticText* StaticText30;
		wxStaticText* StaticText14;
		wxTextCtrl* homeSlowSEdit;
		wxStaticText* StaticText26;
		wxStaticText* StaticText6;
		wxGridSizer* GridSizerStepper;
		wxStaticText* StaticText40;
		wxComboBox* stepperBaudCombo;
		wxTextCtrl* homeFastSEdit;
		wxComboBox* brushlessBaudCombo;
		wxStaticText* StaticText19;
		wxStaticText* StaticText42;
		wxStaticText* StaticText32;
		wxStaticText* StaticText8;
		wxStaticText* StaticText38;
		wxStaticText* StaticText11;
		wxTextCtrl* SpykeDeltaEdit;
		wxStaticText* StaticText18;
		wxTextCtrl* accHEdit;
		wxTextCtrl* openFileText;
		wxStaticText* StaticText31;
		wxStaticText* StaticText1;
		wxTextCtrl* speedHEdit;
		wxStaticText* StaticText27;
		wxStaticBoxSizer* StaticBoxLimits;
		wxTextCtrl* EndMoveDeltaEdit;
		wxStaticText* StaticText3;
		wxListBox* motorsList;
		wxTextCtrl* minLimitEdit;
		wxStaticText* StaticText21;
		wxStaticText* StaticText39;
		wxStaticLine* StaticLine2;
		wxTextCtrl* homeSlowEdit;
		wxTextCtrl* accLEdit;
		wxGridSizer* GridSizerBrushless;
		wxStaticText* StaticText23;
		wxStaticText* StaticText24;
		wxTextCtrl* homeFastEdit;
		wxFileDialog* openFileDialog;
		wxTextCtrl* accCurEdit;
		wxTextCtrl* speedNEdit;
		wxStaticText* StaticText34;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxSpinCtrl* AddressBrushSpin;
		wxTextCtrl* decNEdit;
		wxTextCtrl* KPPEdit;
		wxStaticLine* StaticLine1;
		wxStaticText* StaticText28;
		wxStaticText* StaticText41;
		wxStaticText* StaticText15;
		wxStaticText* StaticText12;
		wxCheckBox* DirectionCheck;
		wxStaticText* StaticText35;
		wxStaticBoxSizer* StaticBoxSizer_Upload;
		wxStaticText* StaticText25;
		wxTextCtrl* maxLimitEdit;
		wxTextCtrl* KCEdit;
		wxStaticText* StaticText17;
		wxStaticText* StaticText36;
		wxStaticText* StaticText4;
		wxComboBox* brushlessPortCombo;
		wxSpinCtrl* addressSpin;
		wxTextCtrl* minCurEdit;
		wxTextCtrl* maxCurEdit;
		wxSpinCtrl* addressBSpin;
		wxStaticText* StaticText16;
		wxTextCtrl* reductionEdit;
		wxTextCtrl* KISEdit;
		wxComboBox* stepCombo;
		wxTextCtrl* pulleyEdit;
		wxTextCtrl* KAEdit;
		wxTextCtrl* curEdit;
		wxTextCtrl* polesEdit;
		wxTextCtrl* KPSEdit;
		wxTextCtrl* KSEdit;
		wxTextCtrl* lineEncEdit;
		//*)

	protected:

		//(*Identifiers(wxMotorsDataPanel)
		static const long ID_LISTBOX1;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_SPINCTRL1;
		static const long ID_TEXTCTRL1;
		static const long ID_TEXTCTRL2;
		static const long ID_TEXTCTRL3;
		static const long ID_COMBOBOX2;
		static const long ID_TEXTCTRL4;
		static const long ID_TEXTCTRL5;
		static const long ID_STATICTEXT40;
		static const long ID_STATICTEXT41;
		static const long ID_TEXTCTRL35;
		static const long ID_TEXTCTRL36;
		static const long ID_STATICTEXT14;
		static const long ID_STATICTEXT15;
		static const long ID_STATICTEXT39;
		static const long ID_STATICTEXT16;
		static const long ID_STATICTEXT18;
		static const long ID_STATICTEXT27;
		static const long ID_STATICTEXT28;
		static const long ID_STATICTEXT29;
		static const long ID_STATICTEXT30;
		static const long ID_SPINCTRL2;
		static const long ID_TEXTCTRL9;
		static const long ID_TEXTCTRL34;
		static const long ID_TEXTCTRL10;
		static const long ID_TEXTCTRL11;
		static const long ID_TEXTCTRL12;
		static const long ID_TEXTCTRL13;
		static const long ID_TEXTCTRL14;
		static const long ID_TEXTCTRL24;
		static const long ID_STATICTEXT31;
		static const long ID_STATICTEXT32;
		static const long ID_STATICTEXT33;
		static const long ID_STATICTEXT34;
		static const long ID_STATICTEXT35;
		static const long ID_STATICTEXT36;
		static const long ID_STATICTEXT37;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT38;
		static const long ID_TEXTCTRL25;
		static const long ID_TEXTCTRL26;
		static const long ID_TEXTCTRL27;
		static const long ID_TEXTCTRL28;
		static const long ID_TEXTCTRL29;
		static const long ID_TEXTCTRL30;
		static const long ID_TEXTCTRL31;
		static const long ID_TEXTCTRL32;
		static const long ID_TEXTCTRL33;
		static const long ID_STATICTEXT42;
		static const long ID_SPINCTRL3;
		static const long ID_CHECKBOX1;
		static const long ID_STATICTEXT25;
		static const long ID_TEXTCTRL6;
		static const long ID_STATICTEXT26;
		static const long ID_TEXTCTRL7;
		static const long ID_STATICLINE1;
		static const long ID_LISTBOX2;
		static const long ID_STATICTEXT19;
		static const long ID_STATICTEXT20;
		static const long ID_STATICTEXT21;
		static const long ID_STATICTEXT22;
		static const long ID_TEXTCTRL15;
		static const long ID_TEXTCTRL16;
		static const long ID_TEXTCTRL17;
		static const long ID_STATICTEXT23;
		static const long ID_TEXTCTRL18;
		static const long ID_TEXTCTRL19;
		static const long ID_TEXTCTRL20;
		static const long ID_STATICTEXT24;
		static const long ID_TEXTCTRL21;
		static const long ID_TEXTCTRL22;
		static const long ID_TEXTCTRL23;
		static const long ID_STATICLINE2;
		static const long ID_STATICTEXT8;
		static const long ID_COMBOBOX1;
		static const long ID_STATICTEXT9;
		static const long ID_COMBOBOX4;
		static const long ID_STATICTEXT10;
		static const long ID_COMBOBOX5;
		static const long ID_STATICTEXT11;
		static const long ID_COMBOBOX6;
		static const long ID_STATICTEXT12;
		static const long ID_TEXTCTRL8;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT13;
		static const long ID_COMBOBOX7;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(wxMotorsDataPanel)
		void OnuploadBtnClick(wxCommandEvent& event);
		void OnmotorsListSelect(wxCommandEvent& event);
		void OnspeedListSelect(wxCommandEvent& event);
		void OnopenFileBtnClick(wxCommandEvent& event);
		void OnDirectionCheckClick(wxCommandEvent& event);
		//*)

	public:
		int Init( SRMachine* SRRef, SmartLog* smartLoggerRef );
		int ShowControl();
		int HideControl();
	
	private:
		SRMachine *SR;
		SmartLog *smartLogger;

		DECLARE_EVENT_TABLE()
};

#endif

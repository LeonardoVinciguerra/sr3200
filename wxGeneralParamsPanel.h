#ifndef WXGENERALPARAMSPANEL_H
#define WXGENERALPARAMSPANEL_H

//(*Headers(wxGeneralParamsPanel)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/combobox.h>
#include <wx/clrpicker.h>
//*)

#include "SRMachine.h"
#include "SmartLog.h"
#include <wx/msgdlg.h>

class wxGeneralParamsPanel: public wxPanel
{
	public:

		wxGeneralParamsPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxGeneralParamsPanel();

		//(*Declarations(wxGeneralParamsPanel)
		wxStaticText* StaticText10;
		wxColourPickerCtrl* ColourPickerAlarm;
		wxStaticText* StaticText9;
		wxComboBox* languageCombo;
		wxComboBox* tableSpeedCombo;
		wxStaticText* StaticText13;
		wxStaticText* StaticText2;
		wxComboBox* plateSpeedDownCombo;
		wxStaticText* StaticText14;
		wxStaticText* StaticText6;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxComboBox* convSpeedFeedCombo;
		wxStaticText* StaticText1;
		wxTextCtrl* loaderZeroMovementEdit;
		wxStaticText* StaticText3;
		wxTextCtrl* cleaningActivationTime;
		wxComboBox* convSpeedWidthCombo;
		wxCheckBox* loaderInstalledCheck;
		wxStaticText* StaticText21;
		wxTextCtrl* loaderDefPitchEdit;
		wxCheckBox* CleaningVacuum;
		wxStaticText* StaticText5;
		wxComboBox* loaderSpeedCombo;
		wxStaticText* StaticText7;
		wxTextCtrl* CameraWipeDeltaEdit;
		wxColourPickerCtrl* ColourPickerWarning;
		wxComboBox* cameraSpeedCombo;
		wxComboBox* plateSpeedUpCombo;
		wxCheckBox* cleaningInstalledCheck;
		wxStaticText* StaticText12;
		wxColourPickerCtrl* ColourPickerShort;
		wxStaticText* StaticText4;
		wxCheckBox* lowLightCheck;
		wxTextCtrl* counterEdit;
		wxCheckBox* cleaningDoubleCheck;
		wxStaticText* StaticText16;
		//*)

	protected:

		//(*Identifiers(wxGeneralParamsPanel)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT5;
		static const long ID_COMBOBOX2;
		static const long ID_STATICTEXT8;
		static const long ID_COMBOBOX6;
		static const long ID_STATICTEXT11;
		static const long ID_COMBOBOX3;
		static const long ID_CHECKBOX3;
		static const long ID_STATICTEXT21;
		static const long ID_COMBOBOX4;
		static const long ID_STATICTEXT6;
		static const long ID_COMBOBOX8;
		static const long ID_STATICTEXT7;
		static const long ID_COMBOBOX9;
		static const long ID_CHECKBOX2;
		static const long ID_STATICTEXT4;
		static const long ID_COMBOBOX7;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL6;
		static const long ID_STATICTEXT9;
		static const long ID_TEXTCTRL2;
		static const long ID_CHECKBOX1;
		static const long ID_STATICTEXT10;
		static const long ID_TEXTCTRL5;
		static const long ID_STATICTEXT16;
		static const long ID_TEXTCTRL4;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_STATICTEXT3;
		static const long ID_COMBOBOX5;
		static const long ID_STATICTEXT12;
		static const long ID_COLOURPICKERCTRL1;
		static const long ID_STATICTEXT13;
		static const long ID_COLOURPICKERCTRL2;
		static const long ID_STATICTEXT14;
		static const long ID_COLOURPICKERCTRL3;
		//*)

	private:

		//(*Handlers(wxGeneralParamsPanel)
		void OnlanguageComboSelect(wxCommandEvent& event);
		void OnsideModeRadioSelect(wxCommandEvent& event);
		void OnloaderInstalledCheckClick(wxCommandEvent& event);
		void OnloaderInstalledCheckClick1(wxCommandEvent& event);
		void OnlowLightCheckClick(wxCommandEvent& event);
		void OncleaningInstalledCheckClick(wxCommandEvent& event);
		void OncleaningDoubleCheckClick(wxCommandEvent& event);
		void OnCleaningVacuumClick(wxCommandEvent& event);
		void OnColourPickerAlarmColourChanged(wxColourPickerEvent& event);
		void OnColourPickerWarningColourChanged(wxColourPickerEvent& event);
		void OnColourPickerShortColourChanged(wxColourPickerEvent& event);
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

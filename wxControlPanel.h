#ifndef WXCONTROLPANEL_H
#define WXCONTROLPANEL_H

//(*Headers(wxControlPanel)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/radiobut.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/combobox.h>
//*)

#include "SRMachine.h"
#include "SmartLog.h"
#include "GlobalEnum.h"

enum ControlPanelMoveEnum
{
	PANEL_MOVE_DISABLE		= 0x0000,
	PANEL_MOVE_LOADER		= 0x0001,
	PANEL_MOVE_PLATE		= 0x0002,
	PANEL_MOVE_CAMERA		= 0x0004,
	PANEL_MOVE_SQUEEGEES	= 0x0008,
	PANEL_MOVE_TABLE		= 0x0010,
	PANEL_MOVE_LCONVW		= 0x0020,
	PANEL_MOVE_LCONVF		= 0x0040,
	PANEL_MOVE_CCONVW		= 0x0080,
	PANEL_MOVE_CCONVF		= 0x0100,
	PANEL_MOVE_LCONVP		= 0x0200
};

enum ControlPanelOutputEnum
{
	PANEL_OUTPUT_NONE		= 0x00000,
	PANEL_OUTPUT_LOCK		= 0x00001,
	PANEL_OUTPUT_FRONT_S	= 0x00002,
	PANEL_OUTPUT_REAR_S		= 0x00004,
	PANEL_OUTPUT_VACUUM		= 0x00008, //n.u.
	PANEL_OUTPUT_ALARM_G	= 0x00010,
	PANEL_OUTPUT_ALARM_R	= 0x00020,
	PANEL_OUTPUT_BUZZER		= 0x00040,
	PANEL_OUTPUT_LED_UP		= 0x00080,
	PANEL_OUTPUT_LED_DOWN	= 0x00100,
	PANEL_OUTPUT_BOARD_LOCK	= 0x00200,
	PANEL_OUTPUT_CONV_PIST	= 0x00400,
	PANEL_OUTPUT_CAM_PIST	= 0x00800,
	PANEL_OUTPUT_LOAD_PIST	= 0x01000,
	PANEL_OUTPUT_SAME		= 0x02000,
	PANEL_OUTPUT_CLEAN_LOCK	= 0x04000,
	PANEL_OUTPUT_CLEAN_VAC	= 0x08000,
	PANEL_OUTPUT_CLEAN_FEED	= 0x10000,
	PANEL_OUTPUT_ALARM_Y	= 0x20000,
	PANEL_OUTPUT_CLEAN_ACT	= 0x40000,
};


class wxControlPanel: public wxPanel
{
	public:

		wxControlPanel(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~wxControlPanel();

		//(*Declarations(wxControlPanel)
		wxButton* cameraPistonBtn;
		wxRadioButton* rotateRadio4;
		wxButton* frameLockBtn;
		wxButton* SwitchLightsBtn;
		wxButton* squeegeesFrontBtn;
		wxButton* CleaningActBtn;
		wxTextCtrl* pos3Edit;
		wxTextCtrl* pos2Edit;
		wxRadioButton* moveRadio1;
		wxRadioButton* rotateRadio1;
		wxButton* ledUpBtn;
		wxButton* boardLockBtn;
		wxStaticText* positionLabel;
		wxButton* cleaningLockBtn;
		wxButton* alarmLightYellowBtn;
		wxRadioButton* moveRadio4;
		wxTextCtrl* pos1Edit;
		wxBitmapButton* moveRightBtn;
		wxRadioButton* rotateRadio3;
		wxBitmapButton* rotCCWBtn;
		wxButton* alarmLightGreenBtn;
		wxButton* squeegeesRearBtn;
		wxButton* ledDownBtn;
		wxBoxSizer* BoxSizerPos;
		wxTextCtrl* rotateUserEdit;
		wxBitmapButton* moveLeftBtn;
		wxButton* alarmLightRedBtn;
		wxRadioButton* moveRadio3;
		wxComboBox* axisCombo;
		wxButton* convPistonBtn;
		wxBitmapButton* moveUpBtn;
		wxBitmapButton* moveDownBtn;
		wxStaticLine* StaticLine1;
		wxRadioButton* rotateRadio2;
		wxPanel* wxAxisPanel;
		wxTextCtrl* moveUserEdit;
		wxRadioButton* moveRadio2;
		wxButton* cleaningFeedingBtn;
		wxBitmapButton* rotCWBtn;
		wxButton* loaderPistonBtn;
		wxButton* homeBtn;
		wxButton* endBtn;
		wxButton* cleaningVacuumBtn;
		wxButton* buzzerBtn;
		//*)

	protected:

		//(*Identifiers(wxControlPanel)
		static const long ID_BITMAPBUTTON1;
		static const long ID_BITMAPBUTTON4;
		static const long ID_BITMAPBUTTON3;
		static const long ID_BITMAPBUTTON2;
		static const long ID_RADIOBUTTON2;
		static const long ID_RADIOBUTTON3;
		static const long ID_RADIOBUTTON1;
		static const long ID_RADIOBUTTON4;
		static const long ID_TEXTCTRL1;
		static const long ID_BITMAPBUTTON6;
		static const long ID_BITMAPBUTTON5;
		static const long ID_RADIOBUTTON5;
		static const long ID_RADIOBUTTON6;
		static const long ID_RADIOBUTTON7;
		static const long ID_RADIOBUTTON8;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICLINE1;
		static const long ID_COMBOBOX1;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRL3;
		static const long ID_TEXTCTRL4;
		static const long ID_TEXTCTRL5;
		static const long ID_PANEL1;
		static const long ID_BUTTON11;
		static const long ID_BUTTON12;
		static const long ID_BUTTON10;
		static const long ID_BUTTON9;
		static const long ID_BUTTON8;
		static const long ID_BUTTON2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON5;
		static const long ID_BUTTON18;
		static const long ID_BUTTON4;
		static const long ID_BUTTON3;
		static const long ID_BUTTON6;
		static const long ID_BUTTON13;
		static const long ID_BUTTON14;
		static const long ID_BUTTON15;
		static const long ID_BUTTON7;
		static const long ID_BUTTON19;
		static const long ID_BUTTON16;
		static const long ID_BUTTON17;
		static const long ID_BUTTON20;
		//*)

	private:

		//(*Handlers(wxControlPanel)
		void OnmoveUpBtnClick(wxCommandEvent& event);
		void OnmoveDownBtnClick(wxCommandEvent& event);
		void OnmoveLeftBtnClick(wxCommandEvent& event);
		void OnmoveRightBtnClick(wxCommandEvent& event);
		void OnrotCCWBtnClick(wxCommandEvent& event);
		void OnrotCWBtnClick(wxCommandEvent& event);
		void OnhomeBtnClick(wxCommandEvent& event);
		void OnendBtnClick(wxCommandEvent& event);
		void OnmoveUserEditText(wxCommandEvent& event);
		void OnrotateUserEditText(wxCommandEvent& event);
		void OnframeLockBtnClick(wxCommandEvent& event);
		void OnalarmLightGreenBtnClick(wxCommandEvent& event);
		void OnalarmLightRedBtnClick(wxCommandEvent& event);
		void OnbuzzerBtnClick(wxCommandEvent& event);
		void OnledUpBtnClick(wxCommandEvent& event);
		void OnledDownBtnClick(wxCommandEvent& event);
		void OnmoveRadioSelect(wxCommandEvent& event);
		void OnrotateRadioSelect(wxCommandEvent& event);
		void OnsqueegeesRearBtnClick(wxCommandEvent& event);
		void OnsqueegeesFrontBtnClick(wxCommandEvent& event);
		void OnaxisComboSelect(wxCommandEvent& event);
		void OnboardLockBtnClick(wxCommandEvent& event);
		void OnconvPistonBtnClick(wxCommandEvent& event);
		void OncameraPistonBtnClick(wxCommandEvent& event);
		void OnloaderPistonBtnClick(wxCommandEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OncleaningLockBtnClick(wxCommandEvent& event);
		void OncleaningVacuumBtnClick(wxCommandEvent& event);
		void OncleaningFeedingBtnClick(wxCommandEvent& event);
		void OnalarmLightYellowBtnClick(wxCommandEvent& event);
		void OnCleaningActBtnClick(wxCommandEvent& event);
		void OnSwitchLightsBtnClick(wxCommandEvent& event);
		//*)

		//void OnCharPressed(wxKeyEvent& event);

	public:
		int Init( SRMachine* SRRef, SmartLog* smartLoggerRef );
		int ShowControl();
		int HideControl();

		int SetState( int movementState, long outputState );

	private:
		SRMachine *SR;
		SmartLog *smartLogger;


		static const long ID_LIGHTS_TIMER;
		wxTimer *LightsTimer;

		int moveState;
		int axisSelected;
		bool isBusy;

		float moveValues[15][4];
		float rotateValues[4];
		char moveIndex;
		char rotateIndex;
		float moveValidatorValue;
		float rotateValidatorValue;

		// private functions
		void SetMovement( bool enableUD, bool enableLR, int state );
		void SetRotation( bool enable );
		void SetIO( bool enabe );

		void MoveUD( int direction );
		void MoveLR( int direction );
		void Rotate( int direction );


		DECLARE_EVENT_TABLE()
};

#endif

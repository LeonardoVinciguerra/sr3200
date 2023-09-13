#ifndef WXPRODUCTIONDATAPANEL_H
#define WXPRODUCTIONDATAPANEL_H

//(*Headers(wxProductionDataPanel)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include "wxPictureBox.h"
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/combobox.h>
//*)

#include "SRMachine.h"
#include "SmartLog.h"

class wxProductionDataPanel: public wxPanel
{
	public:

		wxProductionDataPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxProductionDataPanel();
		void moveLoaderToProductionPosition();

		//(*Declarations(wxProductionDataPanel)
		wxStaticText* StaticText10;
		wxStaticText* StaticText22;
		wxStaticText* StaticText9;
		wxStaticText* StaticText20;
		wxButton* squeegeesFrontBtn;
		wxPanel* Panel5;
		wxTextCtrl* plateDeltaEdit;
		wxComboBox* printingVerifyAutoCombo;
		wxComboBox* BeeperEnCombo;
		wxTextCtrl* xPistonOffsetTextEdit;
		wxStaticText* interferenceLimitsLabel;
		wxStaticText* StaticText29;
		wxTextCtrl* loaderTrayPitchEdit;
		wxPictureBox* gBotImage;
		wxTextCtrl* loaderStartPosEdit;
		wxStaticText* StaticText37;
		wxStaticText* recoveryRLimitsLabel;
		wxCheckBox* topGerber_Check;
		wxStaticText* StaticText13;
		wxStaticText* StaticText33;
		wxStaticText* StaticText2;
		wxPanel* Panel4;
		wxStaticText* StaticText14;
		wxStaticText* StaticText30;
		wxBitmapButton* editBtn;
		wxStaticText* printingVerifyTimeLimitsLabel;
		wxTextCtrl* pcbYEdit;
		wxBitmapButton* newBtn;
		wxStaticText* StaticText6;
		wxStaticText* StaticText26;
		wxBoxSizer* BoxSizer41;
		wxBitmapButton* okLoaderBtn;
		wxTextCtrl* notes1Edit;
		wxButton* topGerberBtn;
		wxStaticText* StaticText32;
		wxStaticText* StaticText19;
		wxComboBox* productionNameCombo;
		wxStaticText* StaticText38;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxTextCtrl* disengageMovementEdit;
		wxStaticText* StaticText18;
		wxStaticText* disengageMovementLimitsLabel;
		wxStaticText* StaticText31;
		wxPanel* Panel1;
		wxBitmapButton* okBtn;
		wxTextCtrl* correctionREdit;
		wxStaticText* StaticText1;
		wxStaticText* StaticText27;
		wxStaticText* StaticText3;
		wxTextCtrl* correctionXEdit;
		wxButton* verifyResetBtn;
		wxButton* squeegeesRearBtn;
		wxComboBox* differentialDisengageCombo;
		wxPanel* Panel6;
		wxTextCtrl* squeegeesZeroMoveEdit;
		wxBitmapButton* loaderStartMoveBtn;
		wxStaticText* StaticText21;
		wxPanel* Panel3;
		wxComboBox* printingVerifyCombo;
		wxStaticText* StaticText23;
		wxBitmapButton* squeegeesMoveBtn;
		wxStaticText* StaticText24;
		wxBitmapButton* loaderStartTeachBtn;
		wxCheckBox* botGerber_Check;
		wxButton* loaderAdjPosition;
		wxButton* counterResetBtn;
		wxTextCtrl* pcbXEdit;
		wxComboBox* doubleSqueegeesCombo;
		wxStaticText* StaticText34;
		wxBitmapButton* moveUpBtn;
		wxTextCtrl* notes2Edit;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxTextCtrl* correctionYEdit;
		wxComboBox* loaderEnCombo;
		wxPanel* Panel7;
		wxStaticBoxSizer* wxSizerControlPanelLoader;
		wxComboBox* cleaningEnCombo;
		wxBitmapButton* moveDownBtn;
		wxTextCtrl* squeegeesSpeedEdit;
		wxTextCtrl* moveLoaderEdit;
		wxTextCtrl* printingVerifyTimeEdit;
		wxBitmapButton* moveDownLoaderBtn;
		wxTextCtrl* DeltaYfrontRear;
		wxCheckBox* CheckBoxStopSPIWhenError;
		wxStaticBoxSizer* wxSizerControlPanel;
		wxStaticText* StaticText28;
		wxComboBox* fiducialOnFrameCombo;
		wxStaticText* moveMMLabel;
		wxStaticText* StaticText15;
		wxComboBox* VerifyAfterprintingCombo;
		wxStaticText* StaticText12;
		wxStaticText* StaticText35;
		wxTextCtrl* moveUserEdit;
		wxBitmapButton* deleteBtn;
		wxBitmapButton* cancelLoaderBtn;
		wxPanel* Panel2;
		wxTextCtrl* squeegeesMoveEdit;
		wxBitmapButton* squeegeesZeroMoveBtn;
		wxTextCtrl* notesEdit;
		wxBitmapButton* conveyorAdjustBtn;
		wxTextCtrl* squeegeesRecoveryFrontEdit;
		wxTextCtrl* squeegeesRecoveryRearEdit;
		wxStaticText* StaticText25;
		wxBitmapButton* importFromGerberBtn;
		wxButton* botGerberBtn;
		wxPictureBox* gTopImage;
		wxStaticText* StaticText36;
		wxStaticText* StaticText17;
		wxStaticText* StaticText4;
		wxTextCtrl* yPistonoffsetTextEdit;
		wxComboBox* fiducialSearchCombo;
		wxTextCtrl* counterEdit;
		wxStaticText* squeegeesSpeedLimitsLabel;
		wxTextCtrl* CleaningEngageBox;
		wxStaticText* StaticText16;
		wxStaticBoxSizer* wxSizerLoader;
		wxBitmapButton* cancelBtn;
		wxBitmapButton* moveUpLoaderBtn;
		wxStaticText* recoveryFLimitsLabel;
		wxComboBox* debugModeCombo;

		//Antireflects WorkingModes
		wxStaticText* StaticTextAntireflects;
		wxComboBox* antiReflectsCombo;
		//*)

	protected:

		//(*Identifiers(wxProductionDataPanel)
		static const long ID_STATICTEXT1;
		static const long ID_COMBOBOX1;
		static const long ID_BITMAPBUTTON1;
		static const long ID_BITMAPBUTTON2;
		static const long ID_BITMAPBUTTON3;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BITMAPBUTTON17;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRL4;
		static const long ID_BITMAPBUTTON11;
		static const long ID_PANEL5;
		static const long ID_CHECKBOX1;
		static const long ID_BUTTON3;
		static const long ID_PANEL3;
		static const long ID_CUSTOM1;
		static const long ID_CHECKBOX2;
		static const long ID_BUTTON5;
		static const long ID_PANEL7;
		static const long ID_CUSTOM2;
		static const long ID_STATICTEXT5;
		static const long ID_TEXTCTRL3;
		static const long ID_STATICTEXT25;
		static const long ID_STATICTEXT8;
		static const long ID_TEXTCTRL7;
		static const long ID_STATICTEXT9;
		static const long ID_TEXTCTRL8;
		static const long ID_STATICTEXT7;
		static const long ID_TEXTCTRL6;
		static const long ID_STATICTEXT40;
		static const long ID_TEXTCTRL5;
		static const long ID_STATICTEXT30;
		static const long ID_STATICTEXT29;
		static const long ID_STATICTEXT31;
		static const long ID_TEXTCTRL16;
		static const long ID_TEXTCTRL15;
		static const long ID_TEXTCTRL14;
		static const long ID_STATICTEXT10;
		static const long ID_TEXTCTRL9;
		static const long ID_BITMAPBUTTON4;
		static const long ID_STATICTEXT11;
		static const long ID_TEXTCTRL10;
		static const long ID_BITMAPBUTTON5;
		static const long ID_PANEL1;
		static const long ID_BITMAPBUTTON6;
		static const long ID_BITMAPBUTTON7;
		static const long ID_TEXTCTRL12;
		static const long ID_STATICTEXT14;
		static const long ID_BUTTON9;
		static const long ID_BUTTON8;
		static const long ID_BITMAPBUTTON8;
		static const long ID_BITMAPBUTTON9;
		static const long ID_PANEL2;
		static const long ID_STATICTEXT32;
		static const long ID_TEXTCTRL17;
		static const long ID_STATICTEXT34;
		static const long ID_STATICTEXT33;
		static const long ID_TEXTCTRL18;
		static const long ID_STATICTEXT35;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT19;
		static const long ID_TEXTCTRL20;
		static const long ID_BITMAPBUTTON16;
		static const long ID_BITMAPBUTTON10;
		static const long ID_PANEL6;
		static const long ID_STATICTEXT37;
		static const long ID_TEXTCTRL21;
		static const long ID_BITMAPBUTTON12;
		static const long ID_BITMAPBUTTON13;
		static const long ID_TEXTCTRL22;
		static const long ID_STATICTEXT38;
		static const long ID_BITMAPBUTTON14;
		static const long ID_BITMAPBUTTON15;
		static const long ID_PANEL4;
		static const long ID_STATICTEXT15;
		static const long ID_COMBOBOX4;
		static const long ID_STATICTEXT16;
		static const long ID_COMBOBOX5;
		static const long ID_STATICTEXT17;
		static const long ID_COMBOBOX6;
		static const long ID_STATICTEXT20;
		static const long ID_COMBOBOX9;
		static const long ID_STATICTEXT21;
		static const long ID_TEXTCTRL19;
		static const long ID_STATICTEXT36;
		static const long ID_STATICTEXT22;
		static const long ID_COMBOBOX11;
		static const long ID_BUTTON4;
		static const long ID_STATICTEXT23;
		static const long ID_COMBOBOX3;
		static const long ID_STATICTEXT24;
		static const long ID_TEXTCTRL13;
		static const long ID_STATICTEXT27;
		static const long ID_CHECKBOX3;
		static const long ID_STATICTEXT28;
		static const long ID_COMBOBOX12;
		static const long ID_STATICTEXT12;
		static const long ID_TEXTCTRL11;
		static const long ID_STATICTEXT26;
		static const long ID_STATICTEXT6;
		static const long ID_COMBOBOX8;
		static const long ID_STATICTEXT18;
		static const long ID_COMBOBOX7;
		static const long ID_STATICTEXT41;
		static const long ID_COMBOBOX10;
		static const long ID_STATICTEXT39;
		static const long ID_TEXTCTRL23;
		static const long ID_STATICTEXT42;
		static const long ID_STATICTEXT13;
		static const long ID_COMBOBOX2;
		static const long ID_STATICTEXT43;
		static const long ID_STATICTEXT44;
		static const long ID_TEXTCTRL24;
		static const long ID_STATICTEXT45;
		static const long ID_TEXTCTRL25;
		static const long ID_STATICTEXT_ANTIREFLECTS;
		static const long ID_COMBOBOX_ANTIREFLECTS;
		//*)

	private:

		//(*Handlers(wxProductionDataPanel)
		void OnproductionNameComboSelect(wxCommandEvent& event);
		void OnnewBtnClick(wxCommandEvent& event);
		void OneditBtnClick(wxCommandEvent& event);
		void OndeleteBtnClick(wxCommandEvent& event);
		void OncounterResetBtnClick(wxCommandEvent& event);
		void OnokBtnClick(wxCommandEvent& event);
		void OncancelBtnClick(wxCommandEvent& event);
		void OnmoveUpBtnClick(wxCommandEvent& event);
		void OnmoveDownBtnClick(wxCommandEvent& event);
		void OnmoveUserEditText(wxCommandEvent& event);
		void OnWorkingModesComboSelect( wxCommandEvent& event );
		void OnverifyResetBtnClick(wxCommandEvent& event);
		void OnsqueegeesRearBtnClick(wxCommandEvent& event);
		void OnsqueegeesFrontBtnClick(wxCommandEvent& event);
		void OnsqueegeesZeroMoveBtnClick(wxCommandEvent& event);
		void OnsqueegeesMoveBtnClick(wxCommandEvent& event);
		void OnloaderStartTeachBtnClick(wxCommandEvent& event);
		void OnMoveUpLoaderBtnClick(wxCommandEvent& event);
		void OnmoveDownLoaderBtnClick(wxCommandEvent& event);
		void OnokLoaderBtnClick(wxCommandEvent& event);
		void OncancelLoaderBtnClick(wxCommandEvent& event);
		void OnmoveLoaderEditText(wxCommandEvent& event);
		void OnconveyorAdjustBtnClick(wxCommandEvent& event);
		void OnloaderStartMoveBtnClick(wxCommandEvent& event);
		void OnloaderAdjPositionClick(wxCommandEvent& event);
		void OntopGerber_CheckClick(wxCommandEvent& event);
		void OnbotGerber_CheckClick(wxCommandEvent& event);
		void OntopGerberBtnClick(wxCommandEvent& event);
		void OnbotGerberBtnClick(wxCommandEvent& event);
		void OnimportFromGerberBtnClick(wxCommandEvent& event);
		void OnCheckBoxStopSPIWhenErrorClick(wxCommandEvent& event);
		//*)

	public:
		int Init( SRMachine *SRRef, SmartLog* smartLoggerRef, wxPanel *toolBoxRef, wxBitmapButton* menuBtnRef );
		int ShowControl();
		int HideControl();
		int UpdateProductionNames();

	private:
		int LoadProduction( const wxString &prodName );
		void UpdateWorkingModesCombos();
		void UpdateGerberData();
		void CheckLimitedVars();
		void GerberPreviewImage(int layerId, bool visible);

		int currentState;
		float move;
		float moveLoader;
		bool isBusy;

		SRMachine *SR;
		SmartLog *smartLogger;
		wxPanel *toolBox;
		wxBitmapButton *menuBtn;

		DECLARE_EVENT_TABLE()
};

#endif

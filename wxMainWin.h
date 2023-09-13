#ifndef WXMAINWIN_H
#define WXMAINWIN_H


//aggiunto


//(*Headers(wxMainWin)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include "wxPictureBox.h"
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

#include <wx/textdlg.h>
#include "wxMainVideo.h"
#include "wxAuxVideo.h"
#include "wxControlPanel.h"
#include "wxDatasette.h"
#include "wxProductionPanel.h"
#include "wxCalibrationPanel.h"
#include "wxProductionDataPanel.h"
#include "wxInspectionPanel.h"
#include "wxGeneralParamsPanel.h"
#include "wxAdvancedParamsPanel.h"
#include "wxMotorsDataPanel.h"
#include "wxHardwareTestPanel.h"
#include "wxVisionPanel.h"
#include "wxStatusPanel.h"

//aggiunto
#include "wxInspectionBoardPanel.h"
#include "wxInspectionVerifyPanel.h"
//fine

#include "SmartLog.h"
#include "SRDatabase.h"
#include "SRMachine.h"
#include "SMBase.h"
#include "wxCameraControl.h"

enum FunctionEnum
{
	NULL_FNC,
	PRODUCTIONPARAMS_FNC,
	ALIGNMENT_FNC,
	PRINTING_FNC,
	INSPECTION_FNC,
	VERIFY_FNC,
	GENERALPARAMS_FNC,
	ADVANCEDPARAMS_FNC,
	MOTORSDATA_FNC,
	PLATEMOVEMENT_FNC,
	CAMERAFOCUS_FNC,
	CAMERASCALE_FNC,
	CAMERAZERO_FNC,
	CAMERAOFFSET_FNC,
	VISION_FNC,
	HWTEST_FNC,
	STATUS_FNC,
	DEMO_FNC,
	CONVEDGE_FNC,
	LOAD_FNC,
	PINS_FNC,
	VIEWRECORDS_FNC,
	PASTE_FNC
};

class wxMainWin: public wxDialog
{
	public:

		wxMainWin(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxMainWin();

		//(*Declarations(wxMainWin)
		wxStaticText* StaticText9;
		wxBitmapButton* offBtn;
		wxBoxSizer* clientParamsSizer;
		wxBoxSizer* wxSizerMain;
		wxPanel* Panel5;
		wxBoxSizer* clientProductionSizer;
		wxBitmapButton* BitmapButton5;
		wxButton* convEdgeBtn;
		wxStaticText* verLabel;
		wxStaticText* StaticText2;
		wxPanel* Panel4;
		wxButton* Button1;
		wxPanel* toolBox;
		wxStaticText* StaticText6;
		wxBoxSizer* titleSizer;
		wxBitmapButton* originBtn;
		wxButton* Button14;
		wxRichTextCtrl* messageBox;
		wxStaticText* StaticText8;
		wxBitmapButton* BitmapButton2;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxBitmapButton* BitmapButton1;
		wxButton* Button2;
		wxPanel* Panel6;
		wxBitmapButton* onBtn;
		wxPanel* Panel3;
		wxButton* Button6;
		wxButton* Button10;
		wxButton* Button11;
		wxButton* Button5;
		wxStaticText* headerLabel;
		wxBoxSizer* wxSizerClientL;
		wxButton* Button3;
		wxButton* backupBtn;
		wxStaticText* StaticText5;
		wxButton* Button7;
		wxStaticText* StaticText7;
		wxPanel* Panel7;
		wxButton* Button9;
		wxBitmapButton* BitmapButton6;
		wxButton* restoreBtn;
		wxBitmapButton* BitmapButton7;
		wxBitmapButton* menuBtn;
		wxPictureBox* mainImage;
		wxBitmapButton* BitmapButton4;
		wxBoxSizer* wxSizerClientR;
		wxBoxSizer* clientLRSizer;
		wxBoxSizer* headerSizer;
		wxBitmapButton* BitmapButton3;
		wxButton* updateBtn;
		wxButton* CameraZeroButton;
		wxButton* Button13;
		wxStaticText* StaticText4;
		wxBoxSizer* menuSizer;
		wxButton* Button8;
		wxButton* Button12;
		wxPanel* PanelFooter;
		wxBitmapButton* homeBtn;
		//*)

	protected:

		//(*Identifiers(wxMainWin)
		static const long ID_STATICTEXT1;
		static const long ID_PANEL9;
		static const long ID_STATICTEXT7;
		static const long ID_PANEL10;
		static const long ID_STATICTEXT8;
		static const long ID_PANEL11;
		static const long ID_STATICTEXT10;
		static const long ID_BITMAPBUTTON1;
		static const long ID_BITMAPBUTTON4;
		static const long ID_BITMAPBUTTON10;
		static const long ID_BITMAPBUTTON3;
		static const long ID_BITMAPBUTTON11;
		static const long ID_BITMAPBUTTON12;
		static const long ID_BITMAPBUTTON2;
		static const long ID_BITMAPBUTTON9;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT9;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT11;
		static const long ID_STATICTEXT5;
		static const long ID_PANEL12;
		static const long ID_BUTTON25;
		static const long ID_BUTTON1;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_BUTTON26;
		static const long ID_BUTTON27;
		static const long ID_BUTTON31;
		static const long ID_BUTTON37;
		static const long ID_BUTTON32;
		static const long ID_BUTTON2;
		static const long ID_BUTTON33;
		static const long ID_BUTTON34;
		static const long ID_BUTTON35;
		static const long ID_BUTTON5;
		static const long ID_BUTTON36;
		static const long ID_BUTTON38;
		static const long ID_BUTTON39;
		static const long ID_BUTTON40;
		static const long ID_PANEL13;
		static const long ID_CUSTOM3;
		static const long ID_BITMAPBUTTON5;
		static const long ID_BITMAPBUTTON6;
		static const long ID_BITMAPBUTTON7;
		static const long ID_BITMAPBUTTON8;
		static const long ID_CUSTOM1;
		static const long ID_PANEL8;
		static const long ID_PANEL1;
		//*)

	private:

		//(*Handlers(wxMainWin)
		void OnhomeBtnClick(wxCommandEvent& event);
		void OnoriginBtnClick(wxCommandEvent& event);
		void OnonBtnClick(wxCommandEvent& event);
		void OnoffBtnClick(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnbackupBtnClick(wxCommandEvent& event);
		void OnrestoreBtnClick(wxCommandEvent& event);
		void OnupdateBtnClick(wxCommandEvent& event);
		void OnmenuBtnClick(wxCommandEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnButton3Click(wxCommandEvent& event);
		void OnButton4Click(wxCommandEvent& event);
		void OnButton5Click(wxCommandEvent& event);
		void OnButton6Click(wxCommandEvent& event);
		void OnButton7Click(wxCommandEvent& event);
		void OnButton8Click(wxCommandEvent& event);
		void OnButton9Click(wxCommandEvent& event);
		void OnButton10Click(wxCommandEvent& event);
		void OnButton11Click(wxCommandEvent& event);
		void OnButton12Click(wxCommandEvent& event);
		void OnButton13Click(wxCommandEvent& event);
		void OnButton14Click(wxCommandEvent& event);
		void OnButton1Click1(wxCommandEvent& event);
		void OnconvEdgeBtnClick(wxCommandEvent& event);
		void OnBitmapButton5Click(wxCommandEvent& event);
		void OnBitmapButton6Click(wxCommandEvent& event);
		void OnInspectionSitesButtonClick(wxCommandEvent& event); //Inspection sites teach button
		void OnButton2Click1(wxCommandEvent& event);
		void OnButton3Click1(wxCommandEvent& event);
		void OnCameraZeroButtonClick(wxCommandEvent& event);
		//*)

		void OnCharPressed(wxKeyEvent& event);


	private:
		SmartLog *smartLogger;
		SRDatabase *DB;
		SRMachine *SR;
		SMBase *SM;
		wxCameraControl *camera;

		AutoSPICheck *AutoSPIcheck;
		AutoSPIProc *AutoSPIproc;

		FunctionEnum currentFnc;
		wxString title;


		void CreateMyControls();
		void InitMyControl();
		
		void ToolBarClick( FunctionEnum clickedFnc );
		void FinalizeControl( FunctionEnum clickedFnc );
		void InitializeControl( FunctionEnum clickedFnc );
		void DrawControls( FunctionEnum clickedFnc );
		
		int OriginSearch();
		int DisableAllMotors();
		int SetSpeedAllMotors();

		void CheckAndUpdateDB();

		bool ChooseLocation( wxString& location );

		// password
		wxString pswL0;
		wxString pswL1;
		wxString pswL2;
		bool isPswL0Ok;
		bool isPswL1Ok;
		bool isPswL2Ok;
		bool PasswordCheck( FunctionEnum clickedFnc );

		void OnGUIEvents( wxCommandEvent& event );

		bool standbyBtnEnable;

		bool isBoardMoving;				// se 1, indica che c'e' una scheda in fase di carico/scarico

		bool isCleaning;				// se 1, indica che c'e' un'operazione di pulizia telaio in corso

		// controls
		wxMainVideo *videoMain;
		wxAuxVideo *videoAux;
		wxControlPanel *controlPanel;
		wxDatasette *datasette;
		wxProductionPanel *productionPanel;
		wxCalibrationPanel *calibrationPanel;
		wxVisionPanel *visionPanel;
		wxInspectionPanel* inspectionPanel;

		wxProductionDataPanel *productionDataPanel;

		wxGeneralParamsPanel *generalParamsPanel;
		wxAdvancedParamsPanel *advancedParamsPanel;
		wxMotorsDataPanel *motorsDataPanel;
		wxHardwareTestPanel *hardwareTestPanel;
		wxStatusPanel *statusPanel;

		//aggiunti for records
		wxInspectionVerifyPanel *InspectionVerifyPanel;
		wxInspectionBoardPanel *InspectionBoardPanel;

		DECLARE_EVENT_TABLE()
};

#endif

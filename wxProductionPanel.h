#ifndef WXPRODUCTIONPANEL_H
#define WXPRODUCTIONPANEL_H

//(*Headers(wxProductionPanel)
#include <wx/sizer.h>
#include "wxPanelPlus.h"
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/checklst.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/statline.h>
#include <wx/radiobut.h>
#include "wxPictureBox.h"
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/bmpbuttn.h>
#include <wx/combobox.h>
//*)

#include "SRMachine.h"
#include "GlobalEnum.h"

enum ProductionEnum
{
	PP_ALIGNMENT,
	PP_PRINTING,
	PP_VERIFY,
	PP_PINS,
	PP_SPI,
	PP_PHASE1,
	PP_PHASE2,
	PP_PASTE
};
enum ColorChannels
{
	COLOR_RED,
	COLOR_GREEN,
	COLOR_BLUE,
	DISTANCE
};

class wxProductionPanel: public wxPanel
{
	public:

		wxProductionPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxProductionPanel();

		//(*Declarations(wxProductionPanel)
		wxStaticText* StaticText10;
		wxBoxSizer* BoxSizerPhase2Settings;
		wxBoxSizer* wxSizerRackMove;
		wxStaticText* StaticText9;
		wxStaticBoxSizer* wxSizerMoveSqueegees;
		wxBitmapButton* gerberBtn;
		wxPanel* sitesPanel;
		wxBitmapButton* CancelChangesPhase2;
		wxBitmapButton* immediateStopBtn;
		wxTextCtrl* rackPosEdit;
		wxRadioBox* ChannelRadioBox;
		wxBitmapButton* CancelChangesPhase1;
		wxStaticText* thresholdLabel;
		wxSlider* diameterSlider;
		wxStaticText* StaticText2;
		wxBitmapButton* rackUpBtn;
		wxRadioBox* RadioBoxBestChannel;
		wxBitmapButton* rackDnBtn;
		wxStaticText* StaticText14;
		wxBoxSizer* BoxSizer13;
		wxBoxSizer* wxSizerVerifyEvery;
		wxStaticText* sideXLabel;
		wxBitmapButton* AcceptChangesPhase2;
		wxStaticText* StaticText6;
		wxSpinCtrl* ColorPadsWidthSpin;
		wxSlider* SliderPasteThr;
		wxTextCtrl* CondIterNumber;
		wxTextCtrl* loaderBoardNumberEdit;
		wxSlider* toleranceSlider;
		wxBoxSizer* BoxSizerCleanEvery;
		wxSlider* houghThrSlider;
		wxStaticText* filterLabel;
		wxBoxSizer* wxSizerPrinting;
		wxBoxSizer* sizerConditioningNum;
		wxStaticText* diameterLabel;
		wxComboBox* shapeCombo;
		wxStaticText* StaticText32;
		wxRadioButton* squeegees2Radio;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxBitmapButton* ModifySpiParam;
		wxPanel* Panel1;
		wxSlider* sideXSlider;
		wxPictureBox* templateImage;
		wxStaticText* StaticText1;
		wxStaticText* sideYLabel;
		wxStaticText* StaticText3;
		wxBitmapButton* fiducialBtn;
		wxSpinCtrl* HueCenterSpin;
		wxBitmapButton* squeegeesMoveBtn;
		wxBoxSizer* BoxSizerInspection;
		wxBoxSizer* BoxSizer14;
		wxRadioButton* ColorPadCriteria;
		wxStaticText* templateLabel;
		wxBitmapButton* AcceptChangesPhase1;
		wxStaticText* StaticText5;
		wxTextCtrl* lastRackPosEdit;
		wxStaticText* StaticText7;
		wxSlider* filterSlider;
		wxStaticText* toleranceLabel;
		wxBitmapButton* rackPosBtn;
		wxRadioButton* squeegees1Radio;
		wxStaticLine* StaticLine1;
		wxTextCtrl* nameValueText;
		wxSlider* sideYSlider;
		wxCheckBox* SuggestCorrectionCheckbox;
		wxStaticText* accumLabel;
		wxSlider* templateSlider;
		wxStaticText* StaticText15;
		wxBoxSizer* BoxSizerPhase1Settings;
		wxBoxSizer* wxSizerAlignment;
		wxGrid* resultsGrid;
		wxSlider* rAccumVisionSlider;
		wxSpinCtrl* HueWidthSpin;
		wxFlexGridSizer* FlexGridSizer1;
		wxRadioButton* HuePadCriteria;
		wxPanel* templatePanel;
		wxCheckBox* manualCheck;
		wxCheckListBox* sitesCheckList;
		wxStaticText* StaticText4;
		wxTextCtrl* cleanEveryEdit;
		wxTextCtrl* verifyEveryEdit;
		wxPanelPlus* positionValuePP;
		wxSlider* cAccumVisionSlider;
		wxBoxSizer* mainSizer;
		//*)

		bool UpdatePadThresholds(int red, int green, int blue);

	protected:

		//(*Identifiers(wxProductionPanel)
		static const long ID_CHECKBOX1;
		static const long ID_BITMAPBUTTON2;
		static const long ID_BITMAPBUTTON4;
		static const long ID_STATICTEXT3;
		static const long ID_COMBOBOX1;
		static const long ID_SLIDER1;
		static const long ID_STATICTEXT1;
		static const long ID_SLIDER5;
		static const long ID_STATICTEXT7;
		static const long ID_SLIDER6;
		static const long ID_STATICTEXT6;
		static const long ID_SLIDER2;
		static const long ID_STATICTEXT2;
		static const long ID_SLIDER9;
		static const long ID_SLIDER7;
		static const long ID_STATICTEXT10;
		static const long ID_SliderHUE;
		static const long ID_STATICTEXT4;
		static const long ID_SliderPasteThr;
		static const long ID_STATICTEXT5;
		static const long ID_RADIOBUTTON3;
		static const long ID_RADIOBUTTON4;
		static const long ID_BITMAPBUTTON3;
		static const long ID_BITMAPBUTTON1;
		static const long ID_STATICTEXT17;
		static const long ID_TEXTCTRL4;
		static const long ID_BITMAPBUTTON5;
		static const long ID_BITMAPBUTTON6;
		static const long ID_STATICTEXT8;
		static const long ID_TEXTCTRL1;
		static const long ID_BITMAPBUTTON7;
		static const long ID_PANEL2;
		static const long ID_STATICTEXT39;
		static const long ID_TEXTCTRL23;
		static const long ID_STATICTEXT11;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT12;
		static const long ID_TEXTCTRL3;
		static const long ID_STATICTEXT18;
		static const long ID_TEXTCTRL5;
		static const long ID_CHECKBOX2;
		static const long ID_CUSTOM1;
		static const long ID_SLIDER8;
		static const long ID_STATICTEXT9;
		static const long ID_PANEL1;
		static const long ID_RadioBoxBestChannel;
		static const long ID_BITMAPBUTTON12;
		static const long ID_BITMAPBUTTON13;
		static const long ID_STATICTEXT16;
		static const long ID_SLIDER15;
		static const long ID_BITMAPBUTTON11;
		static const long ID_BITMAPBUTTON10;
		static const long ID_RADIOBUTTON1;
		static const long ID_STATICTEXT13;
		static const long ID_RADIOBOX1;
		static const long ID_SPINCTRL1;
		static const long ID_RADIOBUTTON2;
		static const long ID_STATICTEXT14;
		static const long ID_SPINCTRL2;
		static const long ID_STATICTEXT15;
		static const long ID_SPINCTRL3;
		static const long ID_STATICTEXT19;
		static const long ID_CHECKLISTBOX2;
		static const long ID_STATICLINE1;
		static const long ID_STATICTEXT23;
		static const long ID_TEXTCTRL6;
		static const long ID_STATICTEXT24;
		static const long ID_CUSTOM2;
		static const long ID_GRID2;
		static const long RequestSpiChangeBtn;
		static const long ID_PANEL5;
		//*)

	private:

		//(*Handlers(wxProductionPanel)
		void OnradiusSliderCmdScroll(wxScrollEvent& event);
		void OntoleranceSliderCmdScroll(wxScrollEvent& event);
		void OnfilterSliderCmdScroll(wxScrollEvent& event);
		void OnhoughThrSliderCmdScroll(wxScrollEvent& event);
		void OnshapeComboSelect(wxCommandEvent& event);
		void OnimmediateStopBtnClick(wxCommandEvent& event);
		void OnsideYSliderCmdScroll(wxScrollEvent& event);
		void OnsideXSliderCmdScroll(wxScrollEvent& event);
		void OnfiducialBtnClick(wxCommandEvent& event);
		void OnsqueegeesMoveBtnClick(wxCommandEvent& event);
		void OntemplateSliderCmdScroll(wxScrollEvent& event);
		void OnrAccumVisionSliderCmdScroll(wxScrollEvent& event);
		void OncAccumVisionSliderCmdScroll(wxScrollEvent& event);
		void OngerberBtnClick(wxCommandEvent& event);
		void OnrackUpBtnClick(wxCommandEvent& event);
		void OnrackPosBtnClick(wxCommandEvent& event);
		void OnrackDnBtnClick(wxCommandEvent& event);
		void OnrackUpBtnClick1(wxCommandEvent& event);
		void OnrackPosBtnClick1(wxCommandEvent& event);
		void OnrackDnBtnClick1(wxCommandEvent& event);
		//aggiunti dalla 3100
		void OnsitesCheckListSelect(wxCommandEvent& event);
		void FireEvent( int eventType );
		//aggiunto
		void OnGridElementSelected(wxGridEvent& event);
		void OnSuggestCorrectionCheckboxClick(wxCommandEvent& event);
		void OnPadThrSliderCmdScroll(wxScrollEvent& event);
		void OnAcceptChangesClick(wxCommandEvent& event);
		void OnCancelChangesClick(wxCommandEvent& event);
		void OnModifySpiParamClick(wxCommandEvent& event);
		void OnHUESliderCmdScroll(wxScrollEvent& event);
		void OnChannelChanged(wxCommandEvent& event);
		void onCancelChangesPhase2(wxCommandEvent& event);
		void OnHueCenterSpinChange(wxSpinEvent& event);
		void OnHueWidthSpinChange(wxSpinEvent& event);
		void OnColorPadCriteriaSelect(wxCommandEvent& event);
		void OnHuePadCriteriaSelect(wxCommandEvent& event);
		void OnChannelRadioBoxSelect(wxCommandEvent& event);
		//*)

	public:

		static const long ID_SQUEEGEES_BUTTON;
		//aggiunto dalla 3100, chiama il refreshquando si cambia sito
		static const int EVT_NEED_UPDATE;

		static const int EVT_GRID_SELECTED;
		//aggiunto gestisce l'evento del click quando si cambia inspection site
		static const long ID_EVENT;
		static const long EVT_PARAMETERS_CHANGED;
		static const long EVT_ACCEPT_CHANGES;
		static const long EVT_REQUEST_NEW_THRESHOLDS;

		int Init( SRMachine* SRRef, SmartLog* smartLoggerRef );
		int ShowControl();
		int HideControl();

		int DrawControl( ProductionEnum mode );
		//aggiunto dalla 3100
		void UpdateSiteData( int point );
		void UpdateInspectionResults( int point );
		void UpdateListSizer( char mode );
		void UpdateSPISliders();


		void EnablePrintingPanel( bool state );
		void UpdatePrintingPanel();
		void UpdatePrintingData();

		void UpdatePanel();
		void UpdatePanelCameraZero();
		void EnableShapeCombo( bool state );
		void UpdateCircleDiameter();
		void UpdateRectangleSides();

		void ShowAlignmentPanel( bool state );
		void EnableAlignmentPanel( bool state );
		
		void ShowManualCheck( bool state );
		void EnableManualCheck( bool state ) { manualCheck->Enable( state ); };
		void SetManualCheckValue( bool value ) { manualCheck->SetValue( value ); };
		bool GetManualCheck() { return manualCheck->IsChecked(); };

		void ShowFiducialButton( bool state ) { fiducialBtn->Show( state ); };
		void EnableFiducialButton( bool state ) { fiducialBtn->Enable( state ); };
		void SetFiducialButton( bool state );
		bool IsFiducialReviewSelected() { return isFiducialBtnOn; };
		
		void ShowTemplatePanel( bool state );
		void ShowTemplateImage( const wxBitmap& bmp );




	private:
		SRMachine* SR;
		SmartLog *smartLogger;

		bool isBusy;
		bool isFiducialBtnOn;

		long rackPos;

		void ConfigureAlignmentPanel( int searchMode );
		void CheckLimitedVars();
		bool vetoEvents;



		DECLARE_EVENT_TABLE()
};

#endif

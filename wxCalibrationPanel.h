#ifndef WXCALIBRATIONPANEL_H
#define WXCALIBRATIONPANEL_H

//(*Headers(wxCalibrationPanel)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/radiobut.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/button.h>
//*)

#include "SRDatabase.h"
#include "GlobalEnum.h"

enum CalibrationEnum
{
	CC_FOCUS,
	CC_PLATE,
	CC_SCALE,
	CC_OFFSET,
	CC_DEMO,
	CC_EDGE
};

class wxCalibrationPanel: public wxPanel
{
	public:

		wxCalibrationPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxCalibrationPanel();

		//(*Declarations(wxCalibrationPanel)
		wxSlider* toleranceOffsetSlider;
		wxButton* offsetMapsBtn;
		wxButton* resetCheckMapsBtn;
		wxStaticText* thresholdLabel;
		wxTextCtrl* distEdit;
		wxStaticText* StaticText2;
		wxStaticText* xUpLabel;
		wxSlider* houghThrOffsetSlider;
		wxStaticText* filterLabel;
		wxTextCtrl* xDownEdit;
		wxTextCtrl* yDownEdit;
		wxTextCtrl* yUpEdit;
		wxStaticText* StaticText1;
		wxStaticText* yUpLabel;
		wxButton* offsetToCheckBtn;
		wxStaticText* xDownLabel;
		wxStaticText* StaticText3;
		wxSlider* filterOffsetSlider;
		wxBoxSizer* wxSizerOffset;
		wxButton* deltaMapsBtn;
		wxButton* defaultOffsetBtn;
		wxButton* checkMapsBtn;
		wxSlider* accumOffsetSlider;
		wxStaticText* toleranceLabel;
		wxBoxSizer* wxSizerScale;
		wxRadioButton* cameraUpRadio;
		wxTextCtrl* numXEdit;
		wxStaticText* accumLabel;
		wxTextCtrl* xUpEdit;
		wxTextCtrl* numYEdit;
		wxStaticText* yDownLabel;
		wxRadioButton* cameraDownRadio;
		//*)

	protected:

		//(*Identifiers(wxCalibrationPanel)
		static const long ID_RADIOBUTTON1;
		static const long ID_RADIOBUTTON2;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT5;
		static const long ID_TEXTCTRL3;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRL4;
		static const long ID_STATICTEXT6;
		static const long ID_TEXTCTRL5;
		static const long ID_SLIDER1;
		static const long ID_STATICTEXT7;
		static const long ID_SliderPasteThr;
		static const long ID_STATICTEXT10;
		static const long ID_SLIDER2;
		static const long ID_STATICTEXT8;
		static const long ID_SliderHUE;
		static const long ID_STATICTEXT9;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL6;
		static const long ID_STATICTEXT11;
		static const long ID_TEXTCTRL7;
		static const long ID_BUTTON6;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON4;
		static const long ID_BUTTON3;
		static const long ID_BUTTON5;
		//*)

	private:

		//(*Handlers(wxCalibrationPanel)
		void OnoffsetMapsBtnClick(wxCommandEvent& event);
		void OntoleranceOffsetSliderCmdScroll(wxScrollEvent& event);
		void OnfilterOffsetSliderCmdScroll(wxScrollEvent& event);
		void OnhoughThrOffsetSliderCmdScroll(wxScrollEvent& event);
		void OnaccumOffsetSliderCmdScroll(wxScrollEvent& event);
		void OncheckMapsBtnClick(wxCommandEvent& event);
		void OnoffsetToCheckBtnClick(wxCommandEvent& event);
		void OndeltaMapsBtnClick(wxCommandEvent& event);
		void OnresetCheckMapsBtnClick(wxCommandEvent& event);
		void OndefaultOffsetBtnClick(wxCommandEvent& event);
		//*)

	public:
		int Init( SRDatabase* DBRef );
		int ShowControl();
		int HideControl();

		int DrawControl( CalibrationEnum mode );

		void EnablePanel( bool state );
		void UpdatePanel();
		CameraEnum GetSelectedCamera() { return cameraUpRadio->GetValue() ? CAMERA_UP : CAMERA_DOWN; };
		void UpdateConstLabels();

	private:
		SRDatabase *DB;

		DECLARE_EVENT_TABLE()
};

#endif

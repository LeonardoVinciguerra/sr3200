#ifndef WXVISIONPANEL_H
#define WXVISIONPANEL_H

//(*Headers(wxVisionPanel)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/combobox.h>
//*)

#include "SRMachine.h"
#include "SmartLog.h"

class wxVisionPanel: public wxPanel
{
	public:

		wxVisionPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxVisionPanel();

		//(*Declarations(wxVisionPanel)
		wxStaticText* thresholdVisionLabel;
		wxSlider* filterVisionSlider;
		wxStaticText* diameterVisionLabel;
		wxStaticText* StaticText6;
		wxSlider* radiusVisionSlider;
		wxSlider* toleranceVisionSlider;
		wxStaticText* sideXVisionLabel;
		wxStaticText* toleranceVisionLabel;
		wxStaticText* filterVisionLabel;
		wxSlider* sideYVisionSlider;
		wxButton* tableToAlignBtn;
		wxSlider* houghThrVisionSlider;
		wxComboBox* shapeVisionCombo;
		wxStaticText* accumLabel;
		wxSlider* rAccumVisionSlider;
		wxStaticText* sideYVisionLabel;
		wxSlider* cAccumVisionSlider;
		wxSlider* sideXVisionSlider;
		//*)

	protected:

		//(*Identifiers(wxVisionPanel)
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT6;
		static const long ID_COMBOBOX1;
		static const long ID_SLIDER1;
		static const long ID_STATICTEXT3;
		static const long ID_SLIDER2;
		static const long ID_STATICTEXT4;
		static const long ID_SLIDER6;
		static const long ID_STATICTEXT9;
		static const long ID_SliderHUE;
		static const long ID_STATICTEXT5;
		static const long ID_SLIDER7;
		static const long ID_SLIDER8;
		static const long ID_STATICTEXT10;
		static const long ID_SliderPasteThr;
		static const long ID_STATICTEXT7;
		static const long ID_SLIDER5;
		static const long ID_STATICTEXT8;
		//*)

	private:

		//(*Handlers(wxVisionPanel)
		void OnradiusVisionSliderCmdScroll(wxScrollEvent& event);
		void OntoleranceVisionSliderCmdScroll(wxScrollEvent& event);
		void OnfilterVisionSliderCmdScroll(wxScrollEvent& event);
		void OnhoughThrVisionSliderCmdScroll(wxScrollEvent& event);
		void OnshapeVisionComboSelect(wxCommandEvent& event);
		void OnsideXVisionSliderCmdScroll(wxScrollEvent& event);
		void OnsideYVisionSliderCmdScroll(wxScrollEvent& event);
		void OncAccumVisionSliderCmdScroll(wxScrollEvent& event);
		void OnrAccumVisionSliderCmdScroll(wxScrollEvent& event);
		void OntableToAlignBtnClick(wxCommandEvent& event);
		//*)

	public:
		int Init( SRMachine* SRRef, SmartLog* smartLoggerRef );
		int ShowControl();
		int HideControl();

	private:
		SRMachine* SR;
		SmartLog *smartLogger;

		DECLARE_EVENT_TABLE()
};

#endif

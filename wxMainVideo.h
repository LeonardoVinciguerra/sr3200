#ifndef WXMAINVIDEO_H
#define WXMAINVIDEO_H

//(*Headers(wxMainVideo)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include "wxPictureBox.h"
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
//*)

#include "SRMachine.h"
#include "wxAuxVideo.h"
#include "wxCameraControl.h"



class wxMainVideo: public wxPanel
{
	public:

		wxMainVideo(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxMainVideo();

		//(*Declarations(wxMainVideo)
		wxStaticText* StaticText10;
		wxStaticText* StaticText9;
		wxStaticText* StaticText13;
		wxTextCtrl* productionNameEdit;
		wxBoxSizer* videoControlSizer;
		wxTextCtrl* infoEdit;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxStaticLine* StaticLine2;
		wxStaticText* StaticText7;
		wxPictureBox* videoMain;
		wxStaticLine* StaticLine1;
		wxStaticText* StaticText12;
		wxPanel* Panel2;
		wxSlider* contrastSlider;
		wxSlider* brightnessSlider;
		wxBitmapButton* auxVideoBtn;
		//*)

		static const long ID_EVENT;
		static const long CHANGE_SPI_PREVIEW;

	protected:

		//(*Identifiers(wxMainVideo)
		static const long ID_CUSTOM1;
		static const long ID_STATICTEXT8;
		static const long ID_SliderBrightness;
		static const long ID_STATICTEXT9;
		static const long ID_STATICTEXT10;
		static const long ID_STATICLINE2;
		static const long ID_STATICTEXT11;
		static const long ID_SliderContrast;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT13;
		static const long ID_PANEL2;
		static const long ID_BITMAPBUTTON1;
		static const long ID_STATICLINE1;
		static const long ID_STATICTEXT7;
		static const long ID_TEXTCTRL1;
		static const long ID_TEXTCTRL2;
		//*)

	private:

		//(*Handlers(wxMainVideo)
		void OnbrightnessSliderCmdScroll(wxScrollEvent& event);
		void OncontrastSliderCmdScroll(wxScrollEvent& event);
		void OnauxVideoBtnClick(wxCommandEvent& event);
		//*)

	public:
		int Init( SRMachine* SRRef, wxAuxVideo *auxVideoRef, wxCameraControl *cameraRef );
		int ShowControl();
		int HideControl();

		int UpdateControl();

		void ConnectMainVideoMouseEvent( int eventType, wxMouseEventFunction func, wxEvtHandler* eventSink ) { videoMain->ConnectMouseEvent( eventType, func, eventSink ); };
		void DisconnectMainVideoMouseEvent( int eventType, wxMouseEventFunction func, wxEvtHandler* eventSink ) { videoMain->DisconnectMouseEvent( eventType, func, eventSink ); };
		void ConnectAuxVideoMouseEvent( int eventType, wxMouseEventFunction func, wxEvtHandler* eventSink ) { videoAux->ConnectAuxVideoMouseEvent( eventType, func, eventSink ); };
		void DisconnectAuxVideoMouseEvent( int eventType, wxMouseEventFunction func, wxEvtHandler* eventSink ) { videoAux->DisconnectAuxVideoMouseEvent( eventType, func, eventSink ); };

		void ConnectMainVideoKeyEvent( int eventType, wxCharEventFunction func, wxEvtHandler* eventSink ) { videoMain->ConnectKeyEvent( eventType, func, eventSink ); };
		void DisconnectMainVideoKeyEvent( int eventType, wxCharEventFunction func, wxEvtHandler* eventSink ) { videoMain->DisconnectKeyEvent( eventType, func, eventSink ); };

		int GetMainVideoDisplacement() { return videoMain->GetImageDisplacement() + videoMain->GetControlBorder(); };
		int GetAuxVideoDisplacement() { return videoAux->GetAuxVideoDisplacement(); };

		wxPictureBox* GetPictureBox() { return videoMain; };
		wxSizer* GetVideoControlSizer() { return videoControlSizer; };

		void SetCurrentProductionName( const wxString &name ) { productionNameEdit->SetValue( name ); };
		void SetInfo( const wxString &msg ) { infoEdit->SetValue( msg ); };

	private:
		SRMachine *SR;
		wxAuxVideo *videoAux;
		wxCameraControl *camera;

		DECLARE_EVENT_TABLE()
};

#endif

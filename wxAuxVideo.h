#ifndef WXAUXVIDEO_H
#define WXAUXVIDEO_H

//(*Headers(wxAuxVideo)
#include <wx/sizer.h>
#include "wxPictureBox.h"
#include <wx/panel.h>
//*)

class wxAuxVideo: public wxPanel
{
	public:

		wxAuxVideo(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxAuxVideo();

		//(*Declarations(wxAuxVideo)
		wxPictureBox* videoAux;
		//*)

	protected:

		//(*Identifiers(wxAuxVideo)
		static const long ID_CUSTOM1;
		//*)

	private:

		//(*Handlers(wxAuxVideo)
		//*)

	public:
		wxPictureBox* GetPictureBox() { return videoAux; };
		void SetImage( const wxBitmap& img );
		int GetAuxVideoDisplacement() { return videoAux->GetImageDisplacement() + videoAux->GetControlBorder(); };

		void ConnectAuxVideoMouseEvent( int eventType, wxMouseEventFunction func, wxEvtHandler* eventSink ) { videoAux->ConnectMouseEvent( eventType, func, eventSink ); };
		void DisconnectAuxVideoMouseEvent( int eventType, wxMouseEventFunction func, wxEvtHandler* eventSink ) { videoAux->DisconnectMouseEvent( eventType, func, eventSink ); };

		DECLARE_EVENT_TABLE()
};

#endif

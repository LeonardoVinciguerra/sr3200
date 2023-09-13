#ifndef WXDATASETTE_H
#define WXDATASETTE_H

//(*Headers(wxDatasette)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
//*)

class wxDatasette: public wxPanel
{
	public:

		wxDatasette(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxDatasette();

		//(*Declarations(wxDatasette)
		wxBitmapButton* nextBtn;
		wxBitmapButton* prevBtn;
		wxBitmapButton* stopBtn;
		wxBitmapButton* pauseBtn;
		wxStaticText* funcName;
		wxBitmapButton* startBtn;
		//*)

	protected:

		//(*Identifiers(wxDatasette)
		static const long ID_BITMAPBUTTON1;
		static const long ID_BITMAPBUTTON2;
		static const long ID_BITMAPBUTTON3;
		static const long ID_BITMAPBUTTON5;
		static const long ID_BITMAPBUTTON4;
		static const long ID_STATICTEXT6;
		//*)

	private:

		//(*Handlers(wxDatasette)
		void OnstartBtnClick(wxCommandEvent& event);
		void OnprevBtnClick(wxCommandEvent& event);
		void OnnextBtnClick(wxCommandEvent& event);
		void OnstopBtnClick(wxCommandEvent& event);
		void OnpauseBtnClick(wxCommandEvent& event);
		//*)

	public:
		static const long ID_START_BUTTON;
		static const long ID_STOP_BUTTON;
		static const long ID_NEXT_BUTTON;
		static const long ID_PREV_BUTTON;
		static const long ID_PAUSE_BUTTON;

		int Init();

		void StartEnable( bool enable ) { startBtn->Enable( enable ); };
		bool IsStartEnable() { return startBtn->IsEnabled(); };
		void StopEnable( bool enable ) { stopBtn->Enable( enable ); };
		void PrevEnable( bool enable ) { prevBtn->Enable( enable ); };
		void NextEnable( bool enable ) { nextBtn->Enable( enable ); };
		void PauseEnable( bool enable ) { pauseBtn->Enable( enable ); };
		void SetFuncLabel( const wxString& name ) { funcName->SetLabel( name ); };

	private:
		DECLARE_EVENT_TABLE()
};

#endif

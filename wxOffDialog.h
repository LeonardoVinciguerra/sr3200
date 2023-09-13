#ifndef WXOFFDIALOG_H
#define WXOFFDIALOG_H

//(*Headers(wxOffDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

enum wxOffDialogRetCode
{
	OFFDIALOG_CANCEL,
	OFFDIALOG_SHUTDOWN,
	OFFDIALOG_STANDBY,
	OFFDIALOG_EXIT
};

class wxOffDialog: public wxDialog
{
	public:

		wxOffDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxOffDialog();

		//(*Declarations(wxOffDialog)
		wxBitmapButton* standbyBtn;
		wxButton* exitBtn;
		wxStaticText* StaticText2;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxBitmapButton* shutdownBtn;
		wxStaticText* StaticText3;
		wxPanel* Panel3;
		wxButton* cancelBtn;
		wxPanel* Panel2;
		//*)

	protected:

		//(*Identifiers(wxOffDialog)
		static const long ID_STATICTEXT3;
		static const long ID_PANEL1;
		static const long ID_PANEL2;
		static const long ID_PANEL3;
		static const long ID_BITMAPBUTTON1;
		static const long ID_STATICTEXT1;
		static const long ID_BITMAPBUTTON2;
		static const long ID_STATICTEXT2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(wxOffDialog)
		void OnexitBtnClick(wxCommandEvent& event);
		void OncancelBtnClick(wxCommandEvent& event);
		void OnstandbyBtnClick(wxCommandEvent& event);
		void OnshutdownBtnClick(wxCommandEvent& event);
		//*)

	public:
		void ShowExitButton( bool state ) { exitBtn->Show( state ); };
		void EnableStandbyButton( bool state ) { standbyBtn->Enable( state ); };

	private:
		DECLARE_EVENT_TABLE()
};

#endif

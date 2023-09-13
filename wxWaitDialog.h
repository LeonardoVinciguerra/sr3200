#ifndef WXWAITDIALOG_H
#define WXWAITDIALOG_H

//(*Headers(wxWaitDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/dialog.h>
//*)

class wxWaitDialog: public wxDialog
{
	public:

		wxWaitDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxWaitDialog();

		//(*Declarations(wxWaitDialog)
		wxStaticText* messageText;
		wxPanel* Panel1;
		wxStaticText* StaticText3;
		wxPanel* Panel3;
		wxPanel* Panel2;
		//*)

		void SetMessage( wxString mess ) { messageText->SetLabel(mess); }

	protected:

		//(*Identifiers(wxWaitDialog)
		static const long ID_STATICTEXT3;
		static const long ID_PANEL1;
		static const long ID_PANEL2;
		static const long ID_PANEL3;
		static const long ID_STATICTEXT1;
		//*)

	private:

		//(*Handlers(wxWaitDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif

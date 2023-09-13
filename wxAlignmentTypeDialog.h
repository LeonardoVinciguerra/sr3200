#ifndef WXALIGNMENTTYPEDIALOG_H
#define WXALIGNMENTTYPEDIALOG_H

//(*Headers(wxAlignmentTypeDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
#include <wx/dialog.h>
//*)

enum wxAlignmentTypeDialogDialogRetCode
{
	ALIGNMENTTYPE_TEMPLATE,
	ALIGNMENTTYPE_VECTORIAL
};

class wxAlignmentTypeDialog: public wxDialog
{
	public:

		wxAlignmentTypeDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxAlignmentTypeDialog();

		//(*Declarations(wxAlignmentTypeDialog)
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticText* lastUsedLbl;
		wxBitmapButton* vectorialBtn;
		wxStaticText* StaticText4;
		wxBitmapButton* templateBtn;
		//*)

	protected:

		//(*Identifiers(wxAlignmentTypeDialog)
		static const long ID_STATICTEXT1;
		static const long ID_BITMAPBUTTON1;
		static const long ID_BITMAPBUTTON2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_PANEL1;
		static const long ID_STATICTEXT2;
		//*)

	private:

		//(*Handlers(wxAlignmentTypeDialog)
		void OntemplateBtnClick(wxCommandEvent& event);
		void OnvectorialBtnClick(wxCommandEvent& event);
		//*)

	public:
		void SetLastUsedMethod( int method );

	private:
		DECLARE_EVENT_TABLE()
};

#endif

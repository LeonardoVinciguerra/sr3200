#ifndef WXINSPECTIONPOPUP_H
#define WXINSPECTIONPOPUP_H

//(*Headers(wxInspectionPopup)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
//*)

enum wxInspectionPopupDialogRetCode
{
	INSPECTIONPOPUP_TEACHING,
	INSPECTIONPOPUP_VERIFY
};


class wxInspectionPopup: public wxPanel
{
	public:

		wxInspectionPopup(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxInspectionPopup();

		//(*Declarations(wxInspectionPopup)
		wxStaticText* StaticText2;
		wxBitmapButton* BitmapButton2;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxBitmapButton* BitmapButton1;
		wxBitmapButton* cancelBtn;
		//*)

	protected:

		//(*Identifiers(wxInspectionPopup)
		static const long ID_STATICTEXT3;
		static const long ID_BITMAPBUTTON12;
		static const long ID_BITMAPBUTTON4;
		static const long ID_BITMAPBUTTON1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT1;
		//*)

	private:

		//(*Handlers(wxInspectionPopup)
		void OncancelBtnClick(wxCommandEvent& event);
		void OnBitmapButton1Click(wxCommandEvent& event);
		void OnBitmapButton2Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif

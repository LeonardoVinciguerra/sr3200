#ifndef WXADVANCEDPARAMSPANEL_H
#define WXADVANCEDPARAMSPANEL_H

//(*Headers(wxAdvancedParamsPanel)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/combobox.h>
//*)

#include "SRDatabase.h"
#include "SmartLog.h"
#include "Messages.h"
#include <wx/msgdlg.h>

class wxAdvancedParamsPanel: public wxPanel
{
	public:

		wxAdvancedParamsPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxAdvancedParamsPanel();

		//(*Declarations(wxAdvancedParamsPanel)
		wxStaticText* StaticText10;
		wxStaticText* StaticText22;
		wxTextCtrl* rectangleAccumEdit;
		wxStaticText* StaticText9;
		wxStaticText* StaticText20;
		wxTextCtrl* convEdgeYEdit;
		wxCheckBox* flipXCheck;
		wxStaticText* StaticText29;
		wxTextCtrl* searchAreaEdit;
		wxTextCtrl* tableZeroMovement1Edit;
		wxTextCtrl* focalHeightEdit;
		wxTextCtrl* GlobalOffsetXInput;
		wxStaticText* StaticText13;
		wxStaticText* StaticText2;
		wxTextCtrl* upXEdit;
		wxButton* Button1;
		wxStaticText* StaticText26;
		wxStaticText* StaticText6;
		wxTextCtrl* downXEdit;
		wxTextCtrl* tableZeroMovement3Edit;
		wxTextCtrl* loaderAdjPositionEdit;
		wxStaticText* StaticText19;
		wxTextCtrl* convEdgeXEdit;
		wxStaticText* StaticText11;
		wxStaticText* StaticText18;
		wxTextCtrl* tableZeroMovement2Edit;
		wxStaticText* StaticText1;
		wxStaticText* StaticText27;
		wxStaticText* StaticText3;
		wxTextCtrl* plateZeroMovementEdit;
		wxTextCtrl* fpsEdit;
		wxTextCtrl* plateMovementEdit;
		wxStaticText* StaticText23;
		wxStaticText* StaticText24;
		wxCheckBox* InputSensorCheckBox;
		wxTextCtrl* circleAccumEdit;
		wxTextCtrl* upYEdit;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxCheckBox* flipYCheck;
		wxStaticText* StaticText28;
		wxStaticText* StaticText12;
		wxButton* setGlobaloffsetButton;
		wxTextCtrl* squeegeesDefZeroEdit;
		wxTextCtrl* cConvZeroMovementEdit;
		wxTextCtrl* cConvMovementEdit;
		wxStaticText* StaticText25;
		wxTextCtrl* downYEdit;
		wxStaticText* StaticText17;
		wxStaticText* StaticText4;
		wxTextCtrl* lConvZeroMovementEdit;
		wxStaticText* StaticText16;
		wxComboBox* smoothMethodCombo;
		wxTextCtrl* lConvMovementEdit;
		wxTextCtrl* GlobalOffsetYInput;
		//*)

	protected:

		//(*Identifiers(wxAdvancedParamsPanel)
		static const long ID_STATICTEXT6;
		static const long ID_TEXTCTRL4;
		static const long ID_STATICTEXT7;
		static const long ID_TEXTCTRL5;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRL23;
		static const long ID_STATICTEXT5;
		static const long ID_TEXTCTRL24;
		static const long ID_BUTTON2;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT12;
		static const long ID_TEXTCTRL9;
		static const long ID_STATICTEXT13;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL2;
		static const long ID_TEXTCTRL3;
		static const long ID_STATICTEXT16;
		static const long ID_TEXTCTRL11;
		static const long ID_STATICTEXT17;
		static const long ID_TEXTCTRL12;
		static const long ID_STATICTEXT19;
		static const long ID_TEXTCTRL13;
		static const long ID_STATICTEXT20;
		static const long ID_TEXTCTRL14;
		static const long ID_STATICTEXT18;
		static const long ID_TEXTCTRL10;
		static const long ID_STATICTEXT24;
		static const long ID_TEXTCTRL17;
		static const long ID_STATICTEXT25;
		static const long ID_TEXTCTRL18;
		static const long ID_STATICTEXT26;
		static const long ID_TEXTCTRL19;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL6;
		static const long ID_STATICTEXT9;
		static const long ID_TEXTCTRL7;
		static const long ID_STATICTEXT10;
		static const long ID_TEXTCTRL8;
		static const long ID_CHECKBOX3;
		static const long ID_STATICTEXT11;
		static const long ID_TEXTCTRL22;
		static const long ID_STATICTEXT22;
		static const long ID_COMBOBOX5;
		static const long ID_STATICTEXT28;
		static const long ID_TEXTCTRL20;
		static const long ID_STATICTEXT23;
		static const long ID_TEXTCTRL15;
		static const long ID_STATICTEXT29;
		static const long ID_TEXTCTRL21;
		static const long ID_STATICTEXT27;
		static const long ID_TEXTCTRL16;
		//*)

	private:

		//(*Handlers(wxAdvancedParamsPanel)
		void OnflipXCheckClick(wxCommandEvent& event);
		void OnflipYCheckClick(wxCommandEvent& event);
		void OnCheckBox1Click(wxCommandEvent& event);
		void OnInputSensorCheckedChanged(wxCommandEvent& event);
		void OnCorrectOffssetmapButtonClick(wxCommandEvent& event);
		void OnTextCtrl2Text(wxCommandEvent& event);
		void OnsetGlobaloffsetButtonClick(wxCommandEvent& event);
		//*)

	public:
		int Init( SRDatabase* DBRef, SmartLog* smartLoggerRef );
		int ShowControl();
		int HideControl();
		void flipXCheckClick(wxCommandEvent& event);
		void flipYCheckClick(wxCommandEvent& event);

	private:
		SRDatabase *DB;
		SmartLog *smartLogger;

		DECLARE_EVENT_TABLE()
};

#endif

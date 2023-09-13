#ifndef WXINSPECTIONPANEL_H
#define WXINSPECTIONPANEL_H

//(*Headers(wxInspectionPanel)
#include <wx/sizer.h>
#include "wxPanelPlus.h"
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checklst.h>
#include <wx/spinctrl.h>
#include <wx/statline.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
#include <wx/combobox.h>
//*)
#include "SRDatabase.h"

enum InspectionEnum
{
	IP_UPDATE,
	IP_OFFLINE,
	IP_OFFLINE_NO_IMG,
	IP_ONLINE_MOVE,
	IP_TEACH,
	IP_TEACH_OFFLINE,
	IP_TEACH_THR,
	TEACH_OFFLINE
};


class wxInspectionPanel: public wxPanel
{
	public:

		wxInspectionPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxInspectionPanel();

		//(*Declarations(wxInspectionPanel)
		wxBoxSizer* sitesListSizer;
		wxFlexGridSizer* namePosSizer;
		wxPanel* sitesPanel;
		wxBitmapButton* teachBtn;
		wxPanel* spiPanel;
		wxStaticText* StaticText2;
		wxBoxSizer* modeSizer;
		wxSpinCtrl* SpinAlarm;
		wxPanel* teachPanel;
		wxStaticText* StaticText6;
		wxBitmapButton* Expand_button;
		wxComboBox* inspectionTypeCombo;
		wxBitmapButton* moveRightBtn;
		wxPanelPlus* thresholdPP;
		wxBitmapButton* removeSiteBtn;
		wxBitmapButton* okBtn;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxSpinCtrl* SpinWarning;
		wxBitmapButton* thrGetBtn;
		wxStaticLine* StaticLine4;
		wxStaticLine* StaticLine2;
		wxBoxSizer* thrSizer;
		wxBitmapButton* moveLeftBtn;
		wxBitmapButton* moveUpBtn;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxBitmapButton* thrPlusBtn;
		wxBitmapButton* moveDownBtn;
		wxBoxSizer* teachSizer;
		wxStaticLine* StaticLine3;
		wxTextCtrl* nameValueText;
		wxBitmapButton* Reduce_button;
		wxBitmapButton* addSiteBtn;
		wxStaticText* StaticText4;
		wxCheckListBox* sitesCheckList;
		wxPanelPlus* thresholdValuePP;
		wxPanelPlus* positionValuePP;
		wxBitmapButton* thrMinusBtn;
		wxBoxSizer* mainSizer;
		wxBitmapButton* cancelBtn;
		//*)

	protected:

		//(*Identifiers(wxInspectionPanel)
		static const long ID_STATICTEXT2;
		static const long ID_COMBOBOX1;
		static const long ID_STATICTEXT8;
		static const long ID_CHECKLISTBOX1;
		static const long ID_BITMAPBUTTON9;
		static const long ID_BITMAPBUTTON10;
		static const long ID_STATICLINE3;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT5;
		static const long ID_CUSTOM13;
		static const long ID_STATICLINE2;
		static const long ID_CUSTOM10;
		static const long ID_BITMAPBUTTON16;
		static const long ID_CUSTOM4;
		static const long ID_BITMAPBUTTON17;
		static const long ID_BITMAPBUTTON18;
		static const long ID_BITMAPBUTTON1;
		static const long ID_BITMAPBUTTON4;
		static const long ID_BITMAPBUTTON3;
		static const long ID_BITMAPBUTTON2;
		static const long ID_BITMAPBUTTON6;
		static const long ID_BITMAPBUTTON5;
		static const long ID_STATICTEXT3;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT6;
		static const long ID_SPINCTRL2;
		static const long ID_STATICLINE4;
		static const long ID_PANEL3;
		static const long ID_PANEL5;
		static const long ID_BITMAPBUTTON15;
		static const long ID_STATICTEXT1;
		static const long ID_BITMAPBUTTON11;
		static const long ID_BITMAPBUTTON12;
		static const long ID_PANEL2;
		//*)

	private:

		//(*Handlers(wxInspectionPanel)
		void OnremoveSiteBtnClick(wxCommandEvent& event);
		void OnaddSiteBtnClick(wxCommandEvent& event);
		void OnteachBtnClick(wxCommandEvent& event);
		void OnokBtnClick(wxCommandEvent& event);
		void OncancelBtnClick(wxCommandEvent& event);
		void OnnameValueTextText(wxCommandEvent& event);
		void OnthrMinusBtnClick(wxCommandEvent& event);
		void OnthrPlusBtnClick(wxCommandEvent& event);
		void OnthrGetBtnClick(wxCommandEvent& event);
		void OninspectionTypeComboSelect(wxCommandEvent& event);
		void OnsitesCheckListSelect(wxCommandEvent& event);
		void OnsitesCheckListToggled(wxCommandEvent& event);
		//void OnareasNotebookPageClose(wxAuiNotebookEvent& event);
		//void OnareasNotebookPageChanging(wxAuiNotebookEvent& event);
		//void OnballDiameterEditTextEnter(wxCommandEvent& event);
		void OnMoveUpBtnClick(wxCommandEvent& event);
		void OnMoveDownBtnClick(wxCommandEvent& event);
		void OnMoveLeftBtnClick(wxCommandEvent& event);
		void OnMoveRightBtnClick(wxCommandEvent& event);
		void OnEnlargeBtnClick(wxCommandEvent& event);
		void OnReduceBtnClick(wxCommandEvent& event);
		void OnSpinAlarmChange(wxSpinEvent& event);
		void OnSpinWarningChange(wxSpinEvent& event);
		//*)

		//void OnMoveLeftBtnClick (wxCommandEvent& event);
		//void OnMoveRightBtnClick (wxCommandEvent& event);
		//void OnMoveUpBtnClick (wxCommandEvent& event);
		//void OnMoveDownBtnClick (wxCommandEvent& event);

		//void OnEnlargeBtnClick (wxCommandEvent& event);
		//void OnReduceBtnClick (wxCommandEvent& event);

	public:
		static const long ID_EVENT;
		static const int EVT_TEACH;
		static const int EVT_OK;
		static const int EVT_CANCEL;
		static const int EVT_THRESHOLD;
		static const int EVT_SET_THRESHOLD;
		static const int EVT_NEED_REFRESH;
		static const int EVT_NEED_REFRESH_IMAGE;
		static const int EVT_NEED_UPDATE;
		static const int EVT_MOVMENT;

		bool Init( SRDatabase* DBRef );
		bool ShowControl();
		bool HideControl();
		void UpdateSiteData( char mode );

		void DrawControl( InspectionEnum mode );

	private:
		void FireEvent( int eventType );

		void OnGUIEvents( wxCommandEvent& event );

		void UpdateListSizer( char mode );
		void UpdateThreshold( char mode );
		void UpdateSiteTypeData( char mode );
		void UpdateAreas( char mode );
		void UpdateTeach( char mode );
		void UpdateAlarmAndWarning( );

		SRDatabase *DB;

		InspectionEnum currentMode;

		bool manageAreasFlag;
		bool vetoEvents;

		float _ballDiameter;

		DECLARE_EVENT_TABLE()
};

#endif

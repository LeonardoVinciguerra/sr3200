#ifndef WXINSPECTIONVERIFYPANEL_H
#define WXINSPECTIONVERIFYPANEL_H

//(*Headers(wxInspectionVerifyPanel)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checklst.h>
#include <wx/checkbox.h>
#include <wx/statline.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/bmpbuttn.h>
//*)
#include <wx/grid.h>
#include "SRDatabase.h"



class wxInspectionVerifyPanel: public wxPanel
{
	public:

		wxInspectionVerifyPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxInspectionVerifyPanel();

		//(*Declarations(wxInspectionVerifyPanel)
		wxBoxSizer* spiDataSizer;
		wxBoxSizer* sitesListSizer;
		wxPanel* sitesPanel;
		wxPanel* spiPanel;
		wxStaticText* StaticText2;
		wxTextCtrl* TextAlarm;
		wxStaticText* StaticText1;
		wxBitmapButton* ConfirmAlarmWarning;
		wxTextCtrl* TextWarning;
		wxBoxSizer* BoxSizer12;
		wxCheckBox* CheckBoxFaulty;
		wxStaticText* StaticText7;
		wxStaticLine* StaticLine3;
		wxBoxSizer* BoxSizer1;
		wxGrid* resultsGrid;
		wxCheckListBox* sitesCheckList;
		wxCheckBox* CheckBoxWarning;
		wxBoxSizer* mainSizer;
		//*)

		bool Init( SRDatabase* DBRef );

		static const long EVT_NEED_UPDATE_RECORDS;
		static const long EVT_GRID_SELECTED_RECORDS;
		static const long ID_EVENT_RECORDS;
		static const long ID_CHANGEPICTURE;
		static const long EVT_IDENTIFY_ALL_FAULTY;
		static const long EVT_IDENTIFY_ALL_WARNING;


		int InitializeSelectedBoard();


	protected:

		//(*Identifiers(wxInspectionVerifyPanel)
		static const long ID_STATICTEXT8;
		static const long ID_CHECKLISTBOX1;
		static const long ID_STATICLINE3;
		static const long ID_GRID1;
		static const long ID_PANEL3;
		static const long ID_PANEL5;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_BITMAPBUTTON1;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		//*)

	private:

		//(*Handlers(wxInspectionVerifyPanel)
		void OnPaint(wxPaintEvent& event);
		void OnTextCtrl1Text(wxCommandEvent& event);
		void OnTextCtrl1Text1(wxCommandEvent& event);
		void OnGrid1CellLeftClick(wxGridEvent& event);
		void OnGridElementSelected(wxGridEvent& event);
		void OnConfirmAlarmWarningClick(wxCommandEvent& event);
		void OnIdentifyAllFaulty(wxCommandEvent& event);
		void OnIdentifyAllWarning(wxCommandEvent& event);
		//*)
		SRDatabase* DB;

		void OnsitesCheckListSelect(wxCommandEvent& event);
		//void OnGridElementSelected(wxGridEvent& event);
		void FireEvent( int eventType );
		void UpdateInspectionResults( int NumSite );
		void UpdateListSizer( char mode );
		void UpdateSiteData( int point );
		void UpdateListSizer(int selected);

		void OnSiteSelected ( wxGridEvent& event );






		DECLARE_EVENT_TABLE()
};

#endif

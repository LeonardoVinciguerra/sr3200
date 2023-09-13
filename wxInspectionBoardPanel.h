#ifndef WXINSPECTIONBOARDPANEL_H
#define WXINSPECTIONBOARDPANEL_H

//(*Headers(wxInspectionBoardPanel)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/choice.h>
#include <wx/button.h>
//*)
#include "SRDatabase.h"

class wxInspectionBoardPanel: public wxPanel
{
	public:

		wxInspectionBoardPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxInspectionBoardPanel();

		void UpdateLists();
		void SelectFirstBoard();

		//(*Declarations(wxInspectionBoardPanel)
		wxStaticText* StaticText2;
		wxButton* Button1;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxGrid* Grid1;
		wxButton* Button2;
		wxPanel* Panel2;
		wxBoxSizer* BoxSizer3;
		wxChoice* Choice1;
		wxChoice* Choice2;
		//*)
		bool Init( SRDatabase* DBRef );
		static const long ID_EVENTRECORDS; //this id is used to send a message to the mainwin, to ask to update the sites panel

	protected:

		//(*Identifiers(wxInspectionBoardPanel)
		static const long ID_STATICTEXT1;
		static const long ID_CHOICE1;
		static const long ID_STATICTEXT2;
		static const long ID_CHOICE2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_PANEL1;
		static const long ID_GRID1;
		static const long ID_PANEL2;
		//*)

	private:

		//(*Handlers(wxInspectionBoardPanel)
		void OnRadioButtonProductionSelect(wxCommandEvent& event);
		void OnRadioButtonNumberSelect(wxCommandEvent& event);
		void OnRadioButtonSelect(wxCommandEvent& event);
		void OnChoiceProductionSelect(wxCommandEvent& event);
		void OnLastChoiceSelected(wxCommandEvent& event);
		void onNextResults(wxCommandEvent& event);
		void onPreviousResults(wxCommandEvent& event);
		void OnBoardDelete(wxGridEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
		SRDatabase* DB;
		void OnRadioButtonSelected(  wxCommandEvent& event );
		void OnPeriodChoiceSelected( wxCommandEvent& event );
		//void OnLastChoiceSelected( wxCommandEvent& event );
		void OnBoardSelected  ( wxGridEvent& event );
		void UpdateBoardResults();

		int currentPage;
		int boardPerPage;
};

#endif

#ifndef WXAREAPANEL_H
#define WXAREAPANEL_H

//(*Headers(wxAreaPanel)
#include <wx/sizer.h>
#include "wxPanelPlus.h"
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
//*)

class wxAreaPanel: public wxPanel
{
	public:

		wxAreaPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxAreaPanel();

		//(*Declarations(wxAreaPanel)
		wxPanelPlus* searchAreaPP;
		wxPanelPlus* alarmValuePP;
		wxBitmapButton* alarmMinusBtn;
		wxBitmapButton* alarmPlusBtn;
		wxPanelPlus* searchAreaValuePP;
		wxPanelPlus* alarmPP;
		wxBitmapButton* searchAreaPlusBtn;
		wxBitmapButton* searchAreaMinusBtn;
		//*)

	protected:

		//(*Identifiers(wxAreaPanel)
		static const long ID_CUSTOM9;
		static const long ID_BITMAPBUTTON8;
		static const long ID_CUSTOM2;
		static const long ID_BITMAPBUTTON7;
		static const long ID_CUSTOM7;
		static const long ID_BITMAPBUTTON5;
		static const long ID_CUSTOM1;
		static const long ID_BITMAPBUTTON6;
		//*)

	private:

		//(*Handlers(wxAreaPanel)
		void OnsearchAreaMinusBtnClick(wxCommandEvent& event);
		void OnsearchAreaPlusBtnClick(wxCommandEvent& event);
		void OnalarmMinusBtnClick(wxCommandEvent& event);
		void OnalarmPlusBtnClick(wxCommandEvent& event);
		//*)

	public:
		static const long ID_EVENT;
		static const int EVT_SEARCH_AREA;

		void SetSearchArea( int* value );
		void SetAlarm( int* value );

		void EnableAdjustButtons( bool enable );

	private:
		void FireEvent( int eventType );

		int* pSearchArea;
		int* pAlarm;

		// dummy vars
		int _searchArea;
		int _alarm;

		DECLARE_EVENT_TABLE()
};

#endif

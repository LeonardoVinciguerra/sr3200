#ifndef WXOFFSETMAPSDIALOG_H
#define WXOFFSETMAPSDIALOG_H

//(*Headers(wxOffsetMapsDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/grid.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

#include "SRDatabase.h"
#include "GlobalEnum.h"

class wxOffsetMapsDialog: public wxDialog
{
	public:

		wxOffsetMapsDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxOffsetMapsDialog();

		//(*Declarations(wxOffsetMapsDialog)
		wxStaticText* StaticText2;
		wxStaticText* StaticText1;
		wxGrid* yOffsetGrid;
		wxGrid* xOffsetGrid;
		wxButton* closeBtn;
		//*)

	protected:

		//(*Identifiers(wxOffsetMapsDialog)
		static const long ID_STATICTEXT1;
		static const long ID_GRID1;
		static const long ID_STATICTEXT2;
		static const long ID_GRID2;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(wxOffsetMapsDialog)
		void OncloseBtnClick(wxCommandEvent& event);
		void OnxOffsetGridCellChange(wxGridEvent& event);
		void OnyOffsetGridCellChange(wxGridEvent& event);
		//*)

	public:
		int Init( SRDatabase* DBRef, int mode );

	private:
		wxColour GetScaledColor( float val, float min, float max );
		void FillWithGradient();
		SRDatabase *DB;
		int modeView;
		float xData, yData;

		bool isChanged;

		DECLARE_EVENT_TABLE()
};

#endif

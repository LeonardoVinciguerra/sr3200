#ifndef WXTHRESHOLDDIALOG_H
#define WXTHRESHOLDDIALOG_H

//(*Headers(wxThresholdDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include "wxPictureBox.h"
#include <wx/button.h>
#include <wx/dialog.h>
//*)


class wxThresholdDialog: public wxDialog
{
	public:

		wxThresholdDialog(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~wxThresholdDialog();

		//(*Declarations(wxThresholdDialog)
		wxStaticLine* staticLine;
		wxStaticText* thrText;
		wxButton* okBtn;
		wxButton* cancelBtn;
		wxPictureBox* histPicture;
		wxStaticText* selThrText;
		//*)

	protected:

		//(*Identifiers(wxThresholdDialog)
		static const long ID_STATICTEXT1;
		static const long ID_CUSTOM1;
		static const long ID_STATICLINE1;
		static const long ID_STATICTEXT2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(wxThresholdDialog)
		void OnokBtnClick(wxCommandEvent& event);
		void OncancelBtnClick(wxCommandEvent& event);
		//*)

	public:
		void SetScanLine( unsigned char* dataRef, unsigned short dataLen );
		int GetThreshold() { return selectedThr; };

	private:
		unsigned char* data;
		unsigned short dataNum;
		unsigned short selectedThr;

		wxBitmap* histBmp;

		void DrawHist( wxDC& dc );
		void DrawCursor( int curPos );

		void HistOnMove( wxMouseEvent& e );
		void HistOnLeave( wxMouseEvent& e );
		void HistOnLeftClick( wxMouseEvent& e );

		DECLARE_EVENT_TABLE()
};

#endif

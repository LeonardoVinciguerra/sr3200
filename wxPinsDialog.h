#ifndef WXPINSDIALOG_H
#define WXPINSDIALOG_H

//(*Headers(wxPinsDialog)
#include <wx/sizer.h>
#include "wxPictureBox.h"
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

#include "myGerbv.h"
#include "SRMachine.h"

#define MAX_GERBER_DIFF		2.0
#define PINS_RADIUS			6

enum wxPinsDialogRetCode
{
	PINSDIALOG_CANCEL,
	PINSDIALOG_OK
};

class wxPinsDialog: public wxDialog
{
	public:

		wxPinsDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxPinsDialog();

		//(*Declarations(wxPinsDialog)
		wxButton* resetBtn;
		wxBitmapButton* okBtn;
		wxBitmapButton* abortBtn;
		wxPictureBox* pcbImage;
		//*)

		void Init( SRMachine *SRRef );

	protected:

		//(*Identifiers(wxPinsDialog)
		static const long ID_CUSTOM1;
		static const long ID_BUTTON1;
		static const long ID_BITMAPBUTTON3;
		static const long ID_BITMAPBUTTON4;
		//*)

	private:

		//(*Handlers(wxPinsDialog)
		void OnabortBtnClick(wxCommandEvent& event);
		void OnokBtnClick(wxCommandEvent& event);
		void OnpcbImageMouseEnter(wxMouseEvent& event);
		void OnresetBtnClick(wxCommandEvent& event);
		//*)

		SRMachine *SR;

		/* this holds our rendering info like window size, scale factor, and translation */
		gerbv_render_info_t screenRenderInfo;

		/* create a top level libgerbv structure */
		gerbv_project_t *mainProject;

		int width, height;
		int topPixelY, leftPixelX;
		double rot;
		int gerberIndex;
		int layer;
		int layerFlip;
		bool isClickEnable;
		int numPins;
		wxPoint pinsCenter[NUM_PINS_POINTS];

		int minXclickable;
		int maxXclickable;
		int minYclickable;
		int maxYclickable;
		int minYWarning;
		int maxYWarning;

		void ImageLeftClick( wxMouseEvent& e );
		void cairoDraw(unsigned char *buffer, gerbv_project_t *gerber, gerbv_render_info_t *screenRenderInfo, double angle = 0.0, int flip = 0);
		int gerberRedraw(double angle = 0.0, int flip = 0);
		int SortFiducials();

		DECLARE_EVENT_TABLE()
};

#endif

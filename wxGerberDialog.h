#ifndef WXGERBERDIALOG_H
#define WXGERBERDIALOG_H

//(*Headers(wxGerberDialog)
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include "wxPictureBox.h"
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

#include "myGerbv.h"
#include "SRMachine.h"

#define TOP_LAYER		0
#define BOTTOM_LAYER	1

enum wxGerberDialogRetCode
{
	GERBERDIALOG_CANCEL,
	GERBERDIALOG_OK
};

class wxGerberDialog: public wxDialog
{
	public:

		wxGerberDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxGerberDialog();

		//(*Declarations(wxGerberDialog)
		wxCheckBox* mechCheck;
		wxCheckBox* flip_Check;
		wxButton* mechBtn;
		wxCheckBox* solderCheck;
		wxBitmapButton* ccwRotBtn;
		wxButton* solderBtn;
		wxBitmapButton* okBtn;
		wxBitmapButton* cwRotBtn;
		wxBitmapButton* abortBtn;
		wxPictureBox* pcbImage;
		//*)

		void Init( SRMachine *SRRef );
		void SetCurrentLayer( int id ) { layer = id; };
		int GetLayerFlip() { return layerFlip; };
		double GetLayerRot() { return rot; };
		bool SaveProject();

	protected:

		//(*Identifiers(wxGerberDialog)
		static const long ID_CUSTOM1;
		static const long ID_CHECKBOX3;
		static const long ID_BUTTON2;
		static const long ID_CHECKBOX2;
		static const long ID_BUTTON4;
		static const long ID_CHECKBOX4;
		static const long ID_BITMAPBUTTON1;
		static const long ID_BITMAPBUTTON2;
		static const long ID_BITMAPBUTTON3;
		static const long ID_BITMAPBUTTON4;
		//*)

	private:

		//(*Handlers(wxGerberDialog)
		void OnsolderBtnClick(wxCommandEvent& event);
		void OnmechBtnClick(wxCommandEvent& event);
		void OnsolderCheckClick(wxCommandEvent& event);
		void OnpadsCheckClick(wxCommandEvent& event);
		void OnmechCheckClick(wxCommandEvent& event);
		void OnccwRotBtnClick(wxCommandEvent& event);
		void OncwRotBtnClick(wxCommandEvent& event);
		void OnokBtnClick(wxCommandEvent& event);
		void OnabortBtnClick(wxCommandEvent& event);
		void Onflip_CheckClick(wxCommandEvent& event);
		//*)

		SRMachine *SR;

		/* this holds our rendering info like window size, scale factor, and translation */
		gerbv_render_info_t screenRenderInfo;

		/* create a top level libgerbv structure */
		gerbv_project_t *mainProject;

		int width, height;
		double rot;
		int gerberIndex, solderIndex, mechIndex;
		int layer;
		int layerFlip;

		void cairoDraw(unsigned char *buffer, gerbv_project_t *gerber, gerbv_render_info_t *screenRenderInfo, double angle = 0.0, int flip = 0);
		void gerberRedraw(double angle = 0.0, int flip = 0);

		DECLARE_EVENT_TABLE()
};

#endif

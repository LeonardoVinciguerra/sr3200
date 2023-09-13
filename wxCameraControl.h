//---------------------------------------------------------------------------
//
// Name:        wxCameraControl.h
// Author:      Gabriel Ferri
// Created:     19/12/2008
// Description: wxCommInterface class declaration
//
//---------------------------------------------------------------------------
#ifndef _WXCAMERACONTROL_H_
#define _WXCAMERACONTROL_H_

#include <wx/thread.h>
#include <wx/event.h>
#include "wxPictureBox.h"
#include "SRMachine.h"
#include "GlobalUtils.h"
#include "myGerbv.h"

#ifdef __WXMSW__
	#include "videoInput.h"
	#include <cv.h>
	#include <highgui.h>
#else
	#include "VideoDevice.h"
	#include <opencv/cv.h>
	#include <opencv/highgui.h>
#endif


	//-------------------//
	// Vision algorithms //
	//-------------------//

#define MAX_FRAMES_FIDUCIAL			1
#define OFFSET_FRAMES				1
#define MAX_COLOR_FRAMES			8


	//-------------//
	// Camera defs //
	//-------------//

#define CAM_W						640
#define CAM_H						480

#define CAM_W_COLOR					640
#define CAM_H_COLOR					480


#define distance_inspection_rectangle 30

#define AUX_WIN_W					480
#define AUX_WIN_H					360


	//----------------//
	// Workplace defs //
	//----------------//

#define WORKPLACE_X					-375
#define WORKPLACE_Y					-5 //0 //-130
#define WORKPLACE_DIM_X				430
#define WORKPLACE_DIM_Y				600

#define WORKPLACE_CENTER_X			-160
#define WORKPLACE_CENTER_Y			-305

#define WORKPLACE_IMG_W				260
#define WORKPLACE_IMG_H				360
#define WORKPLACE_IMG_DELTA			110
#define WORKPLACE_IMG_CAM_W			12
#define WORKPLACE_IMG_CAM_H			9

#define TEMPLATE_DIM_MAX			250		//pixels
#define TEMPLATE_DIM_MIN			80		//pixels
#define TEMPLATE_DIM_INIT			160		//pixels
#define TEMPLATE_DIM_INC			4		//pixels

#define MAX_ZOOM					4.0
#define MIN_ZOOM 					1.0

#define PEN_SHAPE_FOUNDED			*wxGREEN_PEN
#define PEN_SEARCH_AREA				*wxRED_PEN
#define	 PEN_OFFSET_LINE			wxPen( wxColour( 255, 128, 0 ) ) // orange

enum MainVideoModeEnum
{
	MAIN_BLANK,
	MAIN_NO_CUR,
	MAIN_CAMERA_CUR,
	MAIN_CAMERA_MOVE,
	MAIN_MOUSE_CUR,
	MAIN_MOUSE_CUR_MANUAL,
	MAIN_LINE_X,
	MAIN_LINE_Y,
	MAIN_LINE_XY,
	MAIN_CAMERA_VERIFY,
	MAIN_MOUSE_CUR_TEACH,
	MAIN_CAMERA_TEMPLATE,
	MAIN_MOUSE_CUR_NO_CROSSHAIR,
	//aggiunto
	MAIN_CAMERA_INSPECTION_RECTANGLE,
	MAIN_INSPECTION_ZOOM
};

enum AuxVideoModeEnum
{
	AUX_BLANK,
	AUX_SMOOTH_EDGE,
	AUX_CAMPOSITION,
	//aggiunto
	AUX_INSPECTION_MASK,
	AUX_PRINTING_MASK,
	AUX_HISTOGRAM
};

enum CrosshairShapeEnum
{
	CROSSHAIR_RECT,
	CROSSHAIR_CIRCLE
};



class wxCameraControl : public wxEvtHandler, public wxThread
{
	public:
		wxCameraControl();
		~wxCameraControl();

		static const long ID_SEARCH_SHAPE;
		static const long ID_SEARCH_CIRCLE_RADIUS;
		static const long ID_SEARCH_RECT_SIDES;

		virtual void* Entry();


		int Init( SRMachine *SRRef, wxWindow *parentRef );
		void SetImageFlip( int flip ) { imageFlip = ( flip < 0 || flip > 3 ) ? 0 : flip; };
		int ReallocateCamera();

		void SetVideoMain( wxPictureBox *main, wxSizer *sizer );
		void SetVideoAux( wxPictureBox *aux ) { videoAux = aux; };
		void SetVideoMainImage( const wxBitmap& img );

		//aggiunto
		void SetVideoAUXImage( const wxBitmap& img ){videoAux->SetImage( img );};


		void SetMainMode( MainVideoModeEnum mode );
		MainVideoModeEnum GetMainMode() { return modeMain; };
		void SetAuxMode( AuxVideoModeEnum mode );
		AuxVideoModeEnum GetAuxMode() { return modeAux; };
		void SetMainP1( int x, int y ) { p1Main.x = x; p1Main.y = y; };
		void SetMainP2( int x, int y ) { p2Main.x = x; p2Main.y = y; };
		void SetMainShape();
		void SetMainCamZeroShape();
		void GetMainShape();

		void PaintMain();
		void PaintAux();

		//void StartCapture() { isVideoTimerOn = true; Run();};
		void StartCapture(bool correctBAndC = true) { isVideoTimerOn = true; correctBC = correctBAndC; };
		void StopCapture();

		void GetCursorPositionMain( int &X, int &Y ) { X = cursorMain.x; Y = cursorMain.y; };
		PointI GetCursorPositionMain2(){int X = cursorMain.x; int Y = cursorMain.y; PointI pippo(X,Y); return pippo;};;
		void EnableRightClickOnMain( bool state ) { rightClickEnable = state; };
		void EnableWheelOnMain( bool state ) { wheelEnable = state; };

		PointI ToWorkplace( float x, float y );
		PointF FromWorkplace( float x, float y );
		void DrawWorkplace( float left = 0.0f, float low = 0.0f, float w = 0.0f, float h = 0.0f );
		void DrawWorkplaceWithSites( float left = 0.0f, float low = 0.0f, float w = 0.0f, float h = 0.0f );
		void DrawWorkplacePoint( float x, float y, CvScalar color );

		// Vision functions
		void GetFrames( int num );
		void GetColorFrames( int num );
		IplImage* GetWorkingFrame() { return openCVFramesArray[0]; };
		cv::Mat GetWorkingColorFrame(int frame);// { return openCVFramesColorArray[frame]; };
		int FindCircle2( int expectedX, int expectedY, float &X, float &Y, float &R );
		int FindCircleAccurate( int expectedX, int expectedY, float &X, float &Y, float &R );
		int FindCircleCameraZero( int expectedX, int expectedY, float &X, float &Y, float &R );
		int FindRectangle( int expectedX, int expectedY, float &X, float &Y, float &rectX, float &rectY );
		bool FindOffsetPattern3( float &X, float &Y );
		void SaveTemplateImage( const wxString& filename );
		wxBitmap LoadTemplateImage( const wxString& filename );
		int FindTemplate( const wxString& filename, float &X, float &Y, float &score );
		bool CheckTemplateImage( const wxString& filename );
		wxColour getPixelColor(int x, int y);
		int SeachCameraZero();
		int RetryCameraZero();

		//
		void SetTemplateDim( int value ) { templateRectDim = MID( TEMPLATE_DIM_MIN, value, TEMPLATE_DIM_MAX ); };
		int GetTemplateDim() { return templateRectDim; };

		// Camera parameters
		int GetBrightness();
		void SetBrightness( int value );
		int GetContrast();
		void SetContrast( int value );
		bool ResetZoom(){currentZoomLevel=1; return true;};

		cv::Mat Mask_frame; //this frame holds the picture of the mask
		cv::Mat Working_frame; //this frame is used for the SPI process, contains the last picture taken
		cv::Mat Pad_Mask_frame; //this one is used to store the pads after printing

	private:
		wxCriticalSection cs;

		SRMachine *SR;
		wxWindow *parent;
		std::string device;



		bool isDeviceReady;

		wxPictureBox *videoMain;
		wxPictureBox *videoAux;
		wxSizer *videoControl;
		MainVideoModeEnum modeMain;
		AuxVideoModeEnum modeAux;

		// camera device
		#ifdef __WXMSW__
		int VIDev;
		videoInput VI;
		#else
		VideoDevice v4lDevice;
		#endif

		// open cv & video
		bool isVideoTimerOn;
		bool correctBC;
		bool isVideoTimerOn_lock;
		int imageFlip;
		IplImage* openCVFrame_8;				// opencv image buffer GRAY
		IplImage* openCVFrame_24;				// opencv image buffer RGB
		//IplImage* openCVFrame_24_big;			//720*576 color image
		IplImage* openCVBuffer_8;				// opencv working buffer 8bit
		IplImage* openCVBuffer_24;				// opencv working buffer 24bit
		IplImage* openCVWorkPlace;				// opencv WorkPlace buffer
		IplImage* openCVFrame_24_YUYV;			// opencv image buffer for color camera
		cv::Mat temp;
		//aggiunto

		int framesLeft;
		int ColorFramesLeft;
		IplImage* openCVFramesArray[MAX(MAX_FRAMES_FIDUCIAL, OFFSET_FRAMES)];
		//IplImage* openCVFramesColorArray[MAX_COLOR_FRAMES];
		cv::Mat openCVFramesColorArray[MAX_COLOR_FRAMES];

		float Contrast;
		float Brightness;

		CrosshairShapeEnum crosshairShape;		// crosshair shape (circle, square)
		int crosshairCR;						// crosshair - circle radius
		int crosshairRX,crosshairRY;			// crosshair - rectangle sides
		wxPoint cursorMain;						// current cursor position over video main
		wxPoint p1Main, p2Main;					// shape points
		int templateRectDim;					// template rectangle dimension
		bool rightClickEnable;					// enable/disable right click on main video
		bool wheelEnable;						// enable/disable wheel on main video
		float currentZoomLevel;

		/* this holds our rendering info like window size, scale factor, and translation */
		gerbv_render_info_t screenRenderInfo;

		/* create a top level libgerbv structure */
		gerbv_project_t *mainProject;

		int width, height, side;
		int topPixelY, leftPixelX;
		double rot;
		int gerberIndex;
		int layer;
		int layerFlip;
		bool drawGerber;
		int boardX1, boardX2, boardY1, boardY2;
		void loadGerber();
		void cairoDraw(unsigned char *buffer, gerbv_project_t *gerber, gerbv_render_info_t *screenRenderInfo, double angle = 0.0, int flip = 0);

		void VideoMainOnRightClick( wxMouseEvent& e );
		void VideoMainOnWheel( wxMouseEvent& e );
		void VideoMainOnMove( wxMouseEvent& e );
		void VideoMainOnEnter( wxMouseEvent& e );
		void VideoMainOnLeave( wxMouseEvent& e );
		void VideoMainOnKeyPress( wxKeyEvent& e );
		bool wxFindUncoveredPads(cv::Mat* frame);
};

#endif // _WXCOMMINTERFACE_H_

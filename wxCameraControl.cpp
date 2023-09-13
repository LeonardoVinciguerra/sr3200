//---------------------------------------------------------------------------
//
// Name:        wxCameraControl.cpp
// Author:      Gabriel Ferri
// Created:     19/12/2008
// Description: wxCommInterface class implementation
//
//---------------------------------------------------------------------------
#include "wxCameraControl.h"
#include "GlobalUtils.h"
#include <wx/image.h>


#define TICK_DISPLACE				20
#define TICK_WIDTH					8
#define CIRCLE_RADIUS_MIN_PIX		((CIRCLE_DIAMETER_MIN_MM/MM_X_PIXEL)/2.0)
#define CIRCLE_RADIUS_MAX_PIX		((CIRCLE_DIAMETER_MAX_MM/MM_X_PIXEL)/2.0)
#define CIRCLE_DIAMETER_STEP_MM		(1/CIRCLE_SCALE)
#define RECTANGLE_SIDE_STEP_MM		(1/RECTANGLE_SCALE)

const long wxCameraControl::ID_SEARCH_SHAPE = wxNewId();
const long wxCameraControl::ID_SEARCH_CIRCLE_RADIUS = wxNewId();
const long wxCameraControl::ID_SEARCH_RECT_SIDES = wxNewId();

enum channels {
	BLUE_CHANNEL,
	GREEN_CHANNEL,
	RED_CHANNEL
};

wxCameraControl::wxCameraControl()

: wxEvtHandler(), wxThread()
{

	isDeviceReady = false;
	isVideoTimerOn = false;
	isVideoTimerOn_lock = false;
	imageFlip = 0;
	correctBC = true;

	modeMain = MAIN_BLANK;
	modeAux = AUX_BLANK;

	openCVFrame_8	= NULL;
	openCVFrame_24	= NULL;
	openCVBuffer_8	= NULL;
	openCVBuffer_24	= NULL;

	// crosshair default values
	crosshairShape = CROSSHAIR_CIRCLE;
	crosshairCR = 20;
	crosshairRX = crosshairRY = 20;
	templateRectDim = TEMPLATE_DIM_INIT;
	rightClickEnable = true;
	wheelEnable = true;
	drawGerber = false;

	Create();
}

wxCameraControl::~wxCameraControl()
{
	isDeviceReady = false;

	MACHINE_CONFIG( CAMERA_ENABLE )
	#ifdef __WXMSW__
	VI.stopDevice( VIDev );
	#endif
	MACHINE_CONFIG_END

	if( openCVFrame_8 != NULL )
		cvReleaseImage( &openCVFrame_8 );
	if( openCVFrame_24 != NULL )
		cvReleaseImage( &openCVFrame_24 );
	if( openCVBuffer_8 != NULL )
		cvReleaseImage( &openCVBuffer_8 );
	if( openCVBuffer_24 != NULL )
		cvReleaseImage( &openCVBuffer_24 );
	if( &openCVWorkPlace != NULL )
		cvReleaseImage( &openCVWorkPlace );
	if(&openCVFrame_24_YUYV != NULL)
		cvReleaseImage( &openCVFrame_24_YUYV );
	//if(&openCVFrame_24_big != NULL)
		//cvReleaseImage(&openCVFrame_24_big);


	for( int i = 0; i < MAX(MAX_FRAMES_FIDUCIAL, OFFSET_FRAMES); i++ )
		if( openCVFramesArray[i] != NULL )
			cvReleaseImage( &openCVFramesArray[i] );
}


//----------------------------------------------------------------------------------
// InitDevice
// Inizializza il dispositivo video
//----------------------------------------------------------------------------------
int wxCameraControl::Init( SRMachine *SRRef, wxWindow *parentRef )
{
	SR = SRRef;
	parent = parentRef;

	videoMain = NULL;
	videoAux = NULL;
	videoControl = NULL;

	MACHINE_CONFIG( CAMERA_ENABLE )
		#ifdef __WXMSW__
			MACHINE_CONFIG( GRABBER_ENABLE )
				// Configure frame grabber
				system( "ConfigEZ.exe" );
			MACHINE_CONFIG_END

			VIDev = 0;
			videoInput::setVerbose( false );

			if( VI.setupDevice( VIDev, CAM_W, CAM_H ) == false )
				return 1;
		#else

			//std::string device = "/dev/v4l/by-id/usb-MACROSIL_AV_TO_USB2.0-video-index0";
			device = "/dev/video0";

			MACHINE_CONFIG(CAMERA_COLOR)
				// Init v4l driver
				system( "v4lctl -c /dev/video0 setinput Composite" );
				system( "v4lctl -c /dev/video0 setnorm PAL" );
				if ( !v4lDevice.openDevice( device, CAM_W_COLOR, CAM_H_COLOR, V4L2_PIX_FMT_YUYV )){
					device = "/dev/video1";
					if ( !v4lDevice.openDevice( device, CAM_W_COLOR, CAM_H_COLOR, V4L2_PIX_FMT_YUYV )){
						return SR_ERROR;
					}
				}
			MACHINE_CONFIG_ELSE
				// Init v4l driver
				system( "v4lctl -c /dev/video0 setinput composite1" );
				system( "v4lctl -c /dev/video0 setnorm PAL-N" );
				system( "v4lctl -c /dev/video0 setnorm PAL-Nc" );
				if ( !v4lDevice.openDevice( device, CAM_W, CAM_H, V4L2_PIX_FMT_GREY ) )
					{
						return SR_ERROR;
					}

			MACHINE_CONFIG_END

		#endif
	MACHINE_CONFIG_END

	// open cv
	openCVFrame_8		= cvCreateImage( cvSize(CAM_W, CAM_H), IPL_DEPTH_8U, 1 );
	openCVFrame_24		= cvCreateImage( cvSize(CAM_W, CAM_H), IPL_DEPTH_8U, 3 );
	//openCVFrame_24_big  = cvCreateImage( cvSize(CAM_W_COLOR, CAM_H_COLOR), IPL_DEPTH_8U, 3 );
	openCVFrame_24_YUYV = cvCreateImage( cvSize(CAM_W, CAM_H), IPL_DEPTH_8U, 2);
	openCVBuffer_8		= cvCreateImage( cvSize(AUX_WIN_W, AUX_WIN_H), IPL_DEPTH_8U, 1 );
	openCVBuffer_24		= cvCreateImage( cvSize(AUX_WIN_W, AUX_WIN_H), IPL_DEPTH_8U, 3 );
	openCVWorkPlace		= cvCreateImage( cvSize(AUX_WIN_W, AUX_WIN_H), IPL_DEPTH_8U, 3 );
	temp = cv::Mat().zeros(CAM_W, CAM_H, CV_8UC3);

	currentZoomLevel=1;

	framesLeft = 0;
	ColorFramesLeft =0;
	for( int i = 0; i < MAX(MAX_FRAMES_FIDUCIAL, OFFSET_FRAMES); i++ )
		openCVFramesArray[i] = cvCreateImage( cvSize(CAM_W, CAM_H), IPL_DEPTH_8U, 1 );

	for (int i = 0; i < MAX_COLOR_FRAMES; i++){
		openCVFramesColorArray[i] = cv::Mat(CAM_H, CAM_W, CV_8UC3);
	}

	DrawWorkplace();

	isDeviceReady = true;
	return 0;
}

//----------------------------------------------------------------------------------
// Entry
// Ciclo di lavoro del thread
//----------------------------------------------------------------------------------
/*
void* wxCameraControl::Entry()
{
	bool deviceState;

	for(;;)
	{
		cs.Enter();
		deviceState = isDeviceReady;
		cs.Leave();

		if( deviceState == false )
		{
			Sleep(100 );
			continue;
		}

		MACHINE_CONFIG( CAMERA_ENABLE )

		MACHINE_CONFIG_NOT( CAMERA_COLOR )
		#ifdef __WXMSW__
		if( VI.isFrameNew( VIDev ) )
		{
			IplImage* openCVFrame_WIN = cvCreateImageHeader( cvSize(CAM_W, CAM_H), IPL_DEPTH_8U, 3 );

			// Retrieve frame and store it in OpenCV image format
			openCVFrame_WIN->imageData = (char *)VI.getPixels( VIDev, false );
			cvCvtColor( openCVFrame_WIN, openCVFrame_8, CV_BGR2GRAY );

			cvReleaseImageHeader( &openCVFrame_WIN );
		}
		#else


		if( v4lDevice.getFrame( &openCVFrame_8->imageData ) )
		{
		#endif
			if( imageFlip == 1 )
			{
				// Flip image around X
				cvFlip( openCVFrame_8, NULL, 0 );
			}
			else if( imageFlip == 2 )
			{
				// Flip image around Y
				cvFlip( openCVFrame_8, NULL, 1 );
			}
			else if( imageFlip == 3 )
			{
				// Flip image around X and Y
				cvFlip( openCVFrame_8, NULL, -1 );
			}

			cs.Enter();
			if( !isVideoTimerOn )
			{
				isVideoTimerOn_lock = false;
				cs.Leave();
				continue;
			}
			isVideoTimerOn_lock = true;
			cs.Leave();

			cvCvtColor( openCVFrame_8, openCVFrame_24, CV_GRAY2BGR );


			if( framesLeft > 0 )
			{
				memcpy( openCVFramesArray[--framesLeft]->imageData, openCVFrame_8->imageData, CAM_W * CAM_H );
				continue;
			}
		}


		MACHINE_CONFIG_ELSE
		#ifdef __WXMSW__
		if( VI.isFrameNew( VIDev ) )
		{
			IplImage* openCVFrame_WIN = cvCreateImageHeader( cvSize(CAM_W, CAM_H), IPL_DEPTH_8U, 3 );

			// Retrieve frame and store it in OpenCV image format
			openCVFrame_WIN->imageData = (char *)VI.getPixels( VIDev, false );
			cvCvtColor( openCVFrame_WIN, openCVFrame_8, CV_BGR2GRAY );

			cvReleaseImageHeader( &openCVFrame_WIN );
		}
		#else

		if( v4lDevice.getFrame( &openCVFrame_24_YUYV->imageData ) )
		{
		#endif

			cs.Enter();
			if( !isVideoTimerOn )
			{
				isVideoTimerOn_lock = false;
				cs.Leave();
				continue;
			}
			isVideoTimerOn_lock = true;
			cs.Leave();

			cvCvtColor( openCVFrame_24_YUYV, openCVFrame_24_big,CV_YUV2RGB_YUYV);
			cvResize(openCVFrame_24_big, openCVFrame_24, CV_INTER_LINEAR ); // the new picture is 720*576

			if( imageFlip == 1 )
			{
				// Flip image around X
				cvFlip( openCVFrame_24, NULL, 0 );
			}
			else if( imageFlip == 2 )
			{
				// Flip image around Y
				cvFlip( openCVFrame_24, NULL, 1 );
			}
			else if( imageFlip == 3 )
			{
				// Flip image around X and Y
				cvFlip( openCVFrame_24, NULL, -1 );
			}



			temp.data = (unsigned char*)openCVFrame_24->imageData;
			temp.convertTo(temp, -1, Contrast, Brightness);



			if( framesLeft > 0 )
			{
				cvCvtColor(openCVFrame_24, openCVFrame_8, CV_BGR2GRAY);
				memcpy( openCVFramesArray[--framesLeft]->imageData, openCVFrame_8->imageData, CAM_W * CAM_H );


			}
			if (ColorFramesLeft >0 )
			{
				memcpy( openCVFramesColorArray[--ColorFramesLeft].data, openCVFrame_24->imageData, CAM_W * CAM_H*3 );
				//if(ColorFramesLeft==0){
					//wxMutexLocker lock(*m_mutex);
					//m_condition->Broadcast();
				//}
			}

		}
		MACHINE_CONFIG_END

		//if(ColorFramesLeft==0){
			#ifndef __WXMSW__
			wxMutexGuiEnter();
			#endif

			// paint main
			if( videoMain != NULL )
				PaintMain();

			// paint aux
			if( videoAux != NULL )
				PaintAux();

			#ifndef __WXMSW__
			wxMutexGuiLeave();
			#endif
		//}


		MACHINE_CONFIG_END


		if( TestDestroy() )
			return NULL;
	}

	return NULL;
}
*/
void* wxCameraControl::Entry()
{
	bool deviceState;

	for(;;)
	{
		cs.Enter();
		deviceState = isDeviceReady;
		cs.Leave();

		if( deviceState == false )
		{
			Sleep(100 );
			continue;
		}

		MACHINE_CONFIG( CAMERA_ENABLE )
		MACHINE_CONFIG_NOT( CAMERA_COLOR )
		#ifdef __WXMSW__
		if( VI.isFrameNew( VIDev ) )
		{
			IplImage* openCVFrame_WIN = cvCreateImageHeader( cvSize(CAM_W, CAM_H), IPL_DEPTH_8U, 3 );

			// Retrieve frame and store it in OpenCV image format
			openCVFrame_WIN->imageData = (char *)VI.getPixels( VIDev, false );
			cvCvtColor( openCVFrame_WIN, openCVFrame_8, CV_BGR2GRAY );

			cvReleaseImageHeader( &openCVFrame_WIN );
		}
		#else
		bool frameStatus = v4lDevice.getFrame( &openCVFrame_8->imageData );
		if(frameStatus == false){
			ReallocateCamera();
			continue;
		}

		if( frameStatus )
		{
		#endif
			if( imageFlip == 1 )
			{
				// Flip image around X
				cvFlip( openCVFrame_8, NULL, 0 );
			}
			else if( imageFlip == 2 )
			{
				// Flip image around Y
				cvFlip( openCVFrame_8, NULL, 1 );
			}
			else if( imageFlip == 3 )
			{
				// Flip image around X and Y
				cvFlip( openCVFrame_8, NULL, -1 );
			}

			cs.Enter();
			if( !isVideoTimerOn )
			{
				isVideoTimerOn_lock = false;
				cs.Leave();
				continue;
			}
			isVideoTimerOn_lock = true;
			cs.Leave();

			//cv::imshow("imager ", cv::Mat(openCVFrame_8));
			//cv::waitKey(500);
			//sleep(1);

			cvCvtColor( openCVFrame_8, openCVFrame_24, CV_GRAY2BGR );


			if( framesLeft > 0 )
			{
				memcpy( openCVFramesArray[--framesLeft]->imageData, openCVFrame_8->imageData, CAM_W * CAM_H );
				continue;
			}
		}


		MACHINE_CONFIG_ELSE

		#ifdef __WXMSW__
		if( VI.isFrameNew( VIDev ) )
		{
			IplImage* openCVFrame_WIN = cvCreateImageHeader( cvSize(CAM_W, CAM_H), IPL_DEPTH_8U, 3 );

			// Retrieve frame and store it in OpenCV image format
			openCVFrame_WIN->imageData = (char *)VI.getPixels( VIDev, false );
			cvCvtColor( openCVFrame_WIN, openCVFrame_8, CV_BGR2GRAY );

			cvReleaseImageHeader( &openCVFrame_WIN );
		#else
		//if( v4lDevice.getFrame( &openCVFrame_8->imageData ) )
		bool frameStatus = v4lDevice.getFrame( &openCVFrame_24_YUYV->imageData );
		if(frameStatus == false){
			ReallocateCamera();
			continue;
		}
		if( frameStatus )
		{

			cs.Enter();
			if( !isVideoTimerOn )
			{
				isVideoTimerOn_lock = false;
				cs.Leave();
				continue;
			}
			isVideoTimerOn_lock = true;
			cs.Leave();

			cvCvtColor(openCVFrame_24_YUYV,openCVFrame_24, CV_YUV2RGB_YUYV);


		#endif
			if( imageFlip == 1 )
			{
				// Flip image around X
				cvFlip( openCVFrame_24, NULL, 0 );
			}
			else if( imageFlip == 2 )
			{
				// Flip image around Y
				cvFlip( openCVFrame_24, NULL, 1 );
			}
			else if( imageFlip == 3 )
			{
				// Flip image around X and Y
				cvFlip( openCVFrame_24, NULL, -1 );
			}


			if(correctBC){
				//cvCvtColor( openCVFrame_8, openCVFrame_24, CV_GRAY2BGR );
				temp.data = (unsigned char*)openCVFrame_24->imageData;
				temp.convertTo(temp, -1, Contrast, Brightness);
				//cout<<"brightness: "<<Brightness<< " contrast: "<<Contrast<<endl;
				openCVFrame_24->imageData = (char*)temp.data;
			}

			if( framesLeft > 0 )
			{
				cvCvtColor(openCVFrame_24, openCVFrame_8, CV_RGB2GRAY);
				memcpy( openCVFramesArray[--framesLeft]->imageData, openCVFrame_8->imageData, CAM_W * CAM_H );
				continue;
			}
			if (ColorFramesLeft >0 )
			{
				memcpy( openCVFramesColorArray[--ColorFramesLeft].data, openCVFrame_24->imageData, CAM_W * CAM_H*3 );
				continue;
			}


			MACHINE_CONFIG_END




		}
		MACHINE_CONFIG_END

		#ifndef __WXMSW__
		wxMutexGuiEnter();
		#endif

		// paint main
		if( videoMain != NULL )
			PaintMain();

		// paint aux
		if( videoAux != NULL )
			PaintAux();

		#ifndef __WXMSW__
		wxMutexGuiLeave();
		#endif

		if( TestDestroy() )
			return NULL;

		#ifndef __WXMSW__
		Sleep( 75 );
		#endif
	}
	
	return NULL;
}

//----------------------------------------------------------------------------------
// SetVideoMain
// Set the main video display
//----------------------------------------------------------------------------------
void wxCameraControl::SetVideoMain( wxPictureBox *main, wxSizer *sizer )
{
	// disconnect events
	if( videoMain != NULL )
	{
		videoMain->DisconnectMouseEvent( wxEVT_RIGHT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &wxCameraControl::VideoMainOnRightClick ), this );
		videoMain->DisconnectMouseEvent( wxEVT_MOUSEWHEEL, wxStaticCastEvent( wxMouseEventFunction, &wxCameraControl::VideoMainOnWheel ), this );
		videoMain->DisconnectMouseEvent( wxEVT_MOTION, wxStaticCastEvent( wxMouseEventFunction, &wxCameraControl::VideoMainOnMove ), this );
		videoMain->DisconnectMouseEvent( wxEVT_ENTER_WINDOW, wxStaticCastEvent( wxMouseEventFunction, &wxCameraControl::VideoMainOnEnter ), this );
		videoMain->DisconnectMouseEvent( wxEVT_LEAVE_WINDOW, wxStaticCastEvent( wxMouseEventFunction, &wxCameraControl::VideoMainOnLeave ), this );
		videoMain->DisconnectKeyEvent( wxEVT_CHAR, wxStaticCastEvent( wxCharEventFunction, &wxCameraControl::VideoMainOnKeyPress ), this );
	}

	videoMain = main;
	videoControl = sizer;

	// connect events
	if( videoMain != NULL )
	{
		videoMain->ConnectMouseEvent( wxEVT_RIGHT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &wxCameraControl::VideoMainOnRightClick ), this );
		videoMain->ConnectMouseEvent( wxEVT_MOUSEWHEEL, wxStaticCastEvent( wxMouseEventFunction, &wxCameraControl::VideoMainOnWheel ), this );
		videoMain->ConnectMouseEvent( wxEVT_MOTION, wxStaticCastEvent( wxMouseEventFunction, &wxCameraControl::VideoMainOnMove ), this );
		videoMain->ConnectMouseEvent( wxEVT_ENTER_WINDOW, wxStaticCastEvent( wxMouseEventFunction, &wxCameraControl::VideoMainOnEnter ), this );
		videoMain->ConnectMouseEvent( wxEVT_LEAVE_WINDOW, wxStaticCastEvent( wxMouseEventFunction, &wxCameraControl::VideoMainOnLeave ), this );
		videoMain->ConnectKeyEvent( wxEVT_CHAR, wxStaticCastEvent( wxCharEventFunction, &wxCameraControl::VideoMainOnKeyPress ), this );
	}
}

//----------------------------------------------------------------------------------
// SetVideoMainImage
// Set the main video display
//----------------------------------------------------------------------------------
void wxCameraControl::SetVideoMainImage( const wxBitmap& img )
{
	videoMain->SetImage( img );
}

//----------------------------------------------------------------------------------
// SetVideoMode
// Set the main video display mode
//----------------------------------------------------------------------------------
void wxCameraControl::SetMainMode( MainVideoModeEnum mode )
{
	if( videoMain == NULL )
		return;

	modeMain = mode;

	wxBitmap blankBmp = wxBitmap( CAM_W, CAM_H );
	wxMemoryDC dc;

	wxPoint mouseVideoMainPosition = videoMain->ScreenToClient( wxGetMousePosition() );

	EnableSizerChilds( videoControl, modeMain == MAIN_BLANK ? false : true );

	switch( modeMain )
	{
		case MAIN_BLANK:
			dc.SelectObject( blankBmp );
			dc.SetBackground( *wxBLACK_BRUSH );
			dc.Clear();
			dc.SelectObject( wxNullBitmap );
			videoMain->SetImage( blankBmp );
			break;

		case MAIN_NO_CUR:
		case MAIN_CAMERA_CUR:
		//aggiunto
		case MAIN_CAMERA_INSPECTION_RECTANGLE:
		//fine
		case MAIN_CAMERA_MOVE:
		case MAIN_CAMERA_VERIFY:
		case MAIN_CAMERA_TEMPLATE:
			break;

		case MAIN_MOUSE_CUR_MANUAL:
		case MAIN_MOUSE_CUR:
		case MAIN_MOUSE_CUR_TEACH:
		case MAIN_MOUSE_CUR_NO_CROSSHAIR:
			cursorMain.x = mouseVideoMainPosition.x + videoMain->GetImageDisplacement() + videoMain->GetControlBorder();
			cursorMain.y = mouseVideoMainPosition.y + videoMain->GetImageDisplacement() + videoMain->GetControlBorder();
			if( !isVideoTimerOn )
				PaintMain();
			break;

		case MAIN_LINE_X:
		case MAIN_LINE_Y:
		case MAIN_LINE_XY:
			break;
	}
}

//----------------------------------------------------------------------------------
// SetAuxMode
// Set the main video display mode
//----------------------------------------------------------------------------------
void wxCameraControl::SetAuxMode( AuxVideoModeEnum mode )
{
	if( videoAux == NULL )
		return;

	modeAux = mode;

	wxBitmap blankBmp = wxBitmap( AUX_WIN_W, AUX_WIN_H );
	wxMemoryDC dc;

	switch( modeAux )
	{
		case AUX_BLANK:
			dc.SelectObject( blankBmp );
			dc.SetBackground( *wxBLACK_BRUSH );
			dc.Clear();
			dc.SelectObject( wxNullBitmap );
			videoAux->SetImage( blankBmp );
			break;
		case AUX_INSPECTION_MASK:
			PaintAux();
			break;
		case AUX_HISTOGRAM:
			PaintAux();
			break;
		case AUX_PRINTING_MASK:
			PaintAux();
			break;

		case AUX_SMOOTH_EDGE:
		case AUX_CAMPOSITION:
			//aggiunto

			break;
	}
}

//----------------------------------------------------------------------------------
// SetMainShape
// 
//----------------------------------------------------------------------------------
void wxCameraControl::SetMainShape()
{
	crosshairShape = SR->DB->pCurrentFiducial->SearchMode == SEARCH_MODE_CIRCLE ? CROSSHAIR_CIRCLE : CROSSHAIR_RECT;
	crosshairCR = myLRound( SR->DB->pCurrentFiducial->CircleDiameter / 2.0f );
	crosshairRX = myLRound( SR->DB->pCurrentFiducial->RectangleSideX / 2.0f );
	crosshairRY = myLRound( SR->DB->pCurrentFiducial->RectangleSideY / 2.0f );
}
void wxCameraControl::SetMainCamZeroShape()
{
	crosshairShape = CROSSHAIR_CIRCLE ;
	crosshairCR = myLRound( SR->DB->CameraZeroParamsS.CircleDiameter / 2.0f );
	crosshairRX = myLRound( SR->DB->CameraZeroParamsS.RectangleSideX / 2.0f );
	crosshairRY = myLRound( SR->DB->CameraZeroParamsS.RectangleSideY / 2.0f );
}

//----------------------------------------------------------------------------------
// GetMainShape
// 
//----------------------------------------------------------------------------------
void wxCameraControl::GetMainShape()
{
	SR->DB->pCurrentFiducial->SearchMode = crosshairShape == CROSSHAIR_CIRCLE ? SEARCH_MODE_CIRCLE : SEARCH_MODE_RECTANGLE;
	SR->DB->pCurrentFiducial->CircleDiameter = crosshairCR * 2;
	SR->DB->pCurrentFiducial->RectangleSideX = crosshairRX * 2;
	SR->DB->pCurrentFiducial->RectangleSideY = crosshairRY * 2;
}

//----------------------------------------------------------------------------------
// PaintMain
// 
//----------------------------------------------------------------------------------
void wxCameraControl::PaintMain()
{
	MainVideoModeEnum modeMainState;
	cs.Enter();
	modeMainState = modeMain;
	cs.Leave();

	if( modeMainState == MAIN_BLANK )
		return;

	wxBitmap bmp = wxImage( CAM_W, CAM_H, (unsigned char*)openCVFrame_24->imageData, true );
	wxMemoryDC dc;
	dc.SelectObject( bmp );

	if( modeMainState == MAIN_CAMERA_CUR )
	{
		dc.SetPen( wxPen( wxColour( 255, 0, 0 ) ) );
		dc.SetBrush( *wxTRANSPARENT_BRUSH );

		// Draw main cross
		dc.DrawLine( CAM_W/2, 0, CAM_W/2, CAM_H );
		dc.DrawLine( 0,	CAM_H/2, CAM_W, CAM_H/2 );

		// Draw ticks on cross axes
		for( int i = 0; i < (CAM_W/2)/TICK_DISPLACE; i++ )
		{
			dc.DrawLine( CAM_W/2+(i*TICK_DISPLACE), CAM_H/2-TICK_WIDTH/2, CAM_W/2+(i*TICK_DISPLACE), CAM_H/2+TICK_WIDTH/2+1 );
			dc.DrawLine( CAM_W/2-(i*TICK_DISPLACE), CAM_H/2-TICK_WIDTH/2, CAM_W/2-(i*TICK_DISPLACE), CAM_H/2+TICK_WIDTH/2+1 );
		}
		for( int i = 0; i < (CAM_H/2)/TICK_DISPLACE; i++ )
		{
			dc.DrawLine( CAM_W/2-TICK_WIDTH/2, CAM_H/2+(i*TICK_DISPLACE), CAM_W/2+TICK_WIDTH/2+1, CAM_H/2+(i*TICK_DISPLACE) );
			dc.DrawLine( CAM_W/2-TICK_WIDTH/2, CAM_H/2-(i*TICK_DISPLACE), CAM_W/2+TICK_WIDTH/2+1, CAM_H/2-(i*TICK_DISPLACE) );
		}
	}
	else if(modeMainState == MAIN_CAMERA_INSPECTION_RECTANGLE){
		dc.SetPen( wxPen( wxColour( 255, 0, 0 ) ) );
				dc.SetBrush( *wxTRANSPARENT_BRUSH );

				// Draw main cross
				dc.DrawLine( CAM_W/2, 0, CAM_W/2, CAM_H );
				dc.DrawLine( 0,	CAM_H/2, CAM_W, CAM_H/2 );

				// Draw ticks on cross axes
				for( int i = 0; i < (CAM_W/2)/TICK_DISPLACE; i++ )
				{
					dc.DrawLine( CAM_W/2+(i*TICK_DISPLACE), CAM_H/2-TICK_WIDTH/2, CAM_W/2+(i*TICK_DISPLACE), CAM_H/2+TICK_WIDTH/2+1 );
					dc.DrawLine( CAM_W/2-(i*TICK_DISPLACE), CAM_H/2-TICK_WIDTH/2, CAM_W/2-(i*TICK_DISPLACE), CAM_H/2+TICK_WIDTH/2+1 );
				}
				for( int i = 0; i < (CAM_H/2)/TICK_DISPLACE; i++ )
				{
					dc.DrawLine( CAM_W/2-TICK_WIDTH/2, CAM_H/2+(i*TICK_DISPLACE), CAM_W/2+TICK_WIDTH/2+1, CAM_H/2+(i*TICK_DISPLACE) );
					dc.DrawLine( CAM_W/2-TICK_WIDTH/2, CAM_H/2-(i*TICK_DISPLACE), CAM_W/2+TICK_WIDTH/2+1, CAM_H/2-(i*TICK_DISPLACE) );
				}
				dc.DrawRectangle(distance_inspection_rectangle, distance_inspection_rectangle, CAM_W-2*distance_inspection_rectangle, CAM_H- 2*distance_inspection_rectangle);
	}
	else if( modeMainState == MAIN_CAMERA_MOVE )
	{
		dc.SetPen( wxPen( wxColour( 255, 0, 0 ), 2 ) );
		dc.SetBrush( *wxTRANSPARENT_BRUSH );

		// Draw rectangle
		dc.DrawRectangle( CAM_W/4, CAM_H/4, CAM_W/2, CAM_H/2 );

		// Draw main cross
		dc.SetPen( wxPen( wxColour( 255, 0, 0 ) ) );
		dc.DrawLine( CAM_W/2, 0, CAM_W/2, CAM_H/4+7 );
		dc.DrawLine( 0,	CAM_H/2, CAM_W/4+7, CAM_H/2 );
		dc.DrawLine( CAM_W/2, 3*CAM_H/4-8, CAM_W/2, CAM_H );
		dc.DrawLine( 3*CAM_W/4-8, CAM_H/2, CAM_W, CAM_H/2 );
		// center
		dc.DrawLine( CAM_W/2-5, CAM_H/2, CAM_W/2+6, CAM_H/2 );
		dc.DrawLine( CAM_W/2, CAM_H/2-5, CAM_W/2, CAM_H/2+6 );
	}
	else if( modeMainState == MAIN_MOUSE_CUR )
	{
		dc.SetPen( wxPen( wxColour( 255, 128, 0 ) ) );
		dc.SetBrush( *wxTRANSPARENT_BRUSH );

		// Draw main cross
		dc.DrawLine( cursorMain.x, 0, cursorMain.x, CAM_H );
		dc.DrawLine( 0, cursorMain.y, CAM_W, cursorMain.y );

		// Draw crosshair shape
		if( SR->DB->pCurrentFiducial->SearchMode == SEARCH_MODE_CIRCLE )
			dc.DrawCircle( cursorMain.x, cursorMain.y, SR->DB->pCurrentFiducial->CircleDiameter/2.0 );
		else if( SR->DB->pCurrentFiducial->SearchMode == SEARCH_MODE_RECTANGLE )
			dc.DrawRectangle( cursorMain.x-SR->DB->pCurrentFiducial->RectangleSideX/2, cursorMain.y-SR->DB->pCurrentFiducial->RectangleSideY/2, SR->DB->pCurrentFiducial->RectangleSideX, SR->DB->pCurrentFiducial->RectangleSideY );
	}
	else if( modeMainState == MAIN_MOUSE_CUR_MANUAL )
	{
		dc.SetPen( wxPen( wxColour( 0, 255, 0 ) ) );
		dc.SetBrush( *wxTRANSPARENT_BRUSH );

		// Draw main cross
		dc.DrawLine( cursorMain.x, 0, cursorMain.x, CAM_H );
		dc.DrawLine( 0, cursorMain.y, CAM_W, cursorMain.y );

		// Draw crosshair shape
		if( crosshairShape == CROSSHAIR_CIRCLE && crosshairCR > 0 )
			dc.DrawCircle( cursorMain.x, cursorMain.y, crosshairCR );
		else if( crosshairShape == CROSSHAIR_RECT && crosshairRX > 0 && crosshairRY > 0 )
			dc.DrawRectangle( cursorMain.x-crosshairRX, cursorMain.y-crosshairRY, 2*crosshairRX, 2*crosshairRY );
	}
	else if( modeMainState == MAIN_MOUSE_CUR_NO_CROSSHAIR )
	{
		dc.SetPen( wxPen( wxColour( 255, 128, 0 ) ) );
		dc.SetBrush( *wxTRANSPARENT_BRUSH );

		// Draw main cross
		dc.DrawLine( cursorMain.x, 0, cursorMain.x, CAM_H );
		dc.DrawLine( 0,	cursorMain.y, CAM_W, cursorMain.y );
	}
	else if( modeMainState == MAIN_LINE_X )
	{
		dc.SetPen( wxPen( wxColour( 0, 255, 0 ) ) );
		dc.SetBrush( *wxTRANSPARENT_BRUSH );

		// Draw main cross
		dc.DrawLine( cursorMain.x, 0, cursorMain.x, CAM_H );
		dc.DrawLine( 0, cursorMain.y, CAM_W, cursorMain.y );

		// Draw line
		if( cursorMain.x > 0 && cursorMain.y > 0 )
		{
			dc.SetPen( wxPen( wxColour( 255, 0, 0 ), 3 ) );

			dc.DrawLine( p1Main.x, p1Main.y + 4, p1Main.x, p1Main.y - 3 );
			dc.DrawLine( cursorMain.x, p1Main.y + 4, cursorMain.x, p1Main.y - 3 );
			dc.DrawLine( p1Main.x, p1Main.y, cursorMain.x, p1Main.y );
		}
	}
	else if( modeMainState == MAIN_LINE_Y )
	{
		dc.SetPen( wxPen( wxColour( 0, 255, 0 ) ) );
		dc.SetBrush( *wxTRANSPARENT_BRUSH );

		// Draw main cross
		dc.DrawLine( cursorMain.x, 0, cursorMain.x, CAM_H );
		dc.DrawLine( 0, cursorMain.y, CAM_W, cursorMain.y );

		// Draw line
		if( cursorMain.x > 0 && cursorMain.y > 0 )
		{
			dc.SetPen( wxPen( wxColour( 255, 0, 0 ), 3 ) );

			dc.DrawLine( p1Main.x + 4, p1Main.y, p1Main.x - 3, p1Main.y );
			dc.DrawLine( p1Main.x + 4, cursorMain.y, p1Main.x - 3, cursorMain.y );
			dc.DrawLine( p1Main.x, p1Main.y, p1Main.x, cursorMain.y );
		}
	}
	else if( modeMainState == MAIN_LINE_XY )
	{
		dc.SetPen( wxPen( wxColour( 0, 255, 0 ) ) );
		dc.SetBrush( *wxTRANSPARENT_BRUSH );

		// Draw main cross
		dc.DrawLine( cursorMain.x, 0, cursorMain.x, CAM_H );
		dc.DrawLine( 0, cursorMain.y, CAM_W, cursorMain.y );

		// Draw line
		if( cursorMain.x > 0 && cursorMain.y > 0 )
		{
			dc.SetPen( wxPen( wxColour( 255, 0, 0 ) ) );

			dc.DrawLine( p1Main.x, p1Main.y, cursorMain.x, cursorMain.y );
		}
	}
	else if( modeMainState == MAIN_CAMERA_VERIFY )
	{
		dc.SetPen( wxPen( wxColour( 255, 0, 0 ) ) );
		dc.SetBrush( *wxTRANSPARENT_BRUSH );

		// Draw main cross
		dc.DrawLine( CAM_W/2, 0, CAM_W/2, CAM_H );
		dc.DrawLine( 0,	CAM_H/2, CAM_W, CAM_H/2 );

		// Get offset
		double cameraX, cameraY;
		SR->GetCameraPosition( cameraX, cameraY );
		double offsetX, offsetY;
		SR->GetOffset( cameraX, cameraY, offsetX, offsetY );

		int x = CAM_W / 2 - offsetX / SR->DB->MachineParamsS.UpXPixMm;
		int y = CAM_H / 2 + offsetY / SR->DB->MachineParamsS.UpYPixMm;
		// Le immagini hanno l'asse Y opposto rispetto al piano macchina

		// Draw crosshair shape
		if( crosshairShape == CROSSHAIR_CIRCLE && crosshairCR > 0 )
		{
			dc.DrawCircle( CAM_W/2, CAM_H/2, crosshairCR );
			dc.SetPen( wxPen( wxColour( 0, 255, 0 ) ) );
			dc.DrawCircle( x, y, crosshairCR );
		}
		else if( crosshairShape == CROSSHAIR_RECT && crosshairRX > 0 && crosshairRY > 0 )
		{
			dc.DrawRectangle( CAM_W/2-crosshairRX, CAM_H/2-crosshairRY, 2*crosshairRX, 2*crosshairRY );
			dc.SetPen( wxPen( wxColour( 0, 255, 0 ) ) );
			dc.DrawRectangle( x-crosshairRX, y-crosshairRY, 2*crosshairRX, 2*crosshairRY );
		}
	}
	else if( modeMainState == MAIN_MOUSE_CUR_TEACH )
	{
		dc.SetPen( wxPen( wxColour( 128, 255, 255 ) ) );
		dc.SetBrush( *wxTRANSPARENT_BRUSH );

		// Draw main cross
		dc.DrawLine( cursorMain.x, 0, cursorMain.x, CAM_H );
		dc.DrawLine( 0,	cursorMain.y, CAM_W, cursorMain.y );

		// Draw shape
		dc.SetPen( wxPen( wxColour( 255, 0, 0 ) ) );
		if( p1Main.x > 0 && p1Main.y > 0 )
		{
			if( crosshairShape == CROSSHAIR_CIRCLE )
			{
				if( p2Main.x > 0 && p2Main.y > 0 )
				{
					float dx = (p1Main.x-p2Main.x)/2;
					float dy = (p1Main.y-p2Main.y)/2;
					dc.DrawCircle( (p1Main.x+p2Main.x)/2, (p1Main.y+p2Main.y)/2, sqrt( dx*dx + dy*dy ) );
				}
				else if( cursorMain.x > 0 && cursorMain.y > 0 )
				{
					float dx = (p1Main.x-cursorMain.x)/2;
					float dy = (p1Main.y-cursorMain.y)/2;
					dc.DrawCircle( (p1Main.x+cursorMain.x)/2, (p1Main.y+cursorMain.y)/2, sqrt( dx*dx + dy*dy ) );
				}
			}
			else if( crosshairShape == CROSSHAIR_RECT )
			{
				if( p2Main.x > 0 && p2Main.y > 0 )
				{
					dc.DrawRectangle(	MIN( p1Main.x, p2Main.x ),
										MIN( p1Main.y, p2Main.y ),
										abs(p1Main.x-p2Main.x), abs(p1Main.y-p2Main.y) );
				}
				else if( cursorMain.x > 0 && cursorMain.y > 0 )
				{
					dc.DrawRectangle(	MIN( p1Main.x, cursorMain.x ),
										MIN( p1Main.y, cursorMain.y ),
										abs(p1Main.x-cursorMain.x), abs(p1Main.y-cursorMain.y) );
				}
			}
		}
	}
	else if( modeMainState == MAIN_CAMERA_TEMPLATE )
	{
		dc.SetPen( wxPen( wxColour( 255, 128, 0 ) ) );
		dc.SetBrush( *wxTRANSPARENT_BRUSH );

		// Draw rectangle
		dc.DrawRectangle( (CAM_W-templateRectDim)/2, (CAM_H-templateRectDim)/2, templateRectDim, templateRectDim );

		// Draw main cross
		dc.DrawLine( CAM_W/2, 0, CAM_W/2, (CAM_H-templateRectDim)/2 );
		dc.DrawLine( 0,	CAM_H/2, (CAM_W-templateRectDim)/2, CAM_H/2 );
		dc.DrawLine( CAM_W/2, (CAM_H+templateRectDim)/2, CAM_W/2, CAM_H );
		dc.DrawLine( (CAM_W+templateRectDim)/2, CAM_H/2, CAM_W, CAM_H/2 );
		// center
		dc.DrawLine( CAM_W/2-5, CAM_H/2, CAM_W/2+6, CAM_H/2 );
		dc.DrawLine( CAM_W/2, CAM_H/2-5, CAM_W/2, CAM_H/2+6 );
	}
	dc.SelectObject( wxNullBitmap );

	videoMain->SetImage( bmp );
}

//----------------------------------------------------------------------------------
// loadGerber
//
//----------------------------------------------------------------------------------
void wxCameraControl::loadGerber()
{
    // loads level from saved files and show on image
	char pathBase[MAXNPATH];
	char layerName[MAXNPATH];
	char fileNumber[2];

	gerberIndex = 0;

	strcpy(pathBase,DIR_GERBER);
    strcat(pathBase,"/");
    strcat(pathBase,SR->DB->ProductionDataS.ProductionName);
	strcat(pathBase,"-t.l");

	if( SR->DB->ProductionDataS.TopGerberSolder != 0 )
	{
		strcpy(layerName,pathBase);
    	sprintf(fileNumber,"%d",SR->DB->ProductionDataS.TopGerberSolder-1);
		strcat(layerName, fileNumber);
		gerbv_open_layer_from_filename( mainProject, layerName );
		// change the color of the image
		GdkColor goldColor = {0, 56000, 51000, 2550};
		mainProject->file[gerberIndex]->color = goldColor;
		gerberIndex++;
	}
	if( SR->DB->ProductionDataS.TopGerberPads != 0 )
	{
		strcpy(layerName,pathBase);
    	sprintf(fileNumber,"%d",SR->DB->ProductionDataS.TopGerberPads-1);
		strcat(layerName, fileNumber);
		gerbv_open_layer_from_filename( mainProject, layerName );
		// change the color of the image
		GdkColor greenishColor = {0, 10000, 65000, 10000};
		mainProject->file[gerberIndex]->color = greenishColor;
		gerberIndex++;
	}
	if( SR->DB->ProductionDataS.TopGerberMech != 0 )
	{
		strcpy(layerName,pathBase);
    	sprintf(fileNumber,"%d",SR->DB->ProductionDataS.TopGerberMech-1);
		strcat(layerName, fileNumber);
		gerbv_open_layer_from_filename( mainProject, layerName );
		// change the color of the image
		GdkColor whiteColor = {0, 65000, 65000, 65000};
		mainProject->file[gerberIndex]->color = whiteColor;
		gerberIndex++;
	}
}

void wxCameraControl::cairoDraw(unsigned char *buffer, gerbv_project_t *gerber, gerbv_render_info_t *screenRenderInfo, double angle, int flip)
{
	int width = screenRenderInfo->displayWidth;
	int height = screenRenderInfo->displayHeight;

	cairo_t *cr;
	cairo_surface_t* surface;
	cairo_format_t format = CAIRO_FORMAT_RGB24;

	surface = cairo_image_surface_create_for_data(buffer, format, width, height, width*4);
	cr = cairo_create(surface);

	// White background.
	//cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	// Dark green background.
	cairo_set_source_rgb(cr, 0, 0.3, 0);
	cairo_paint (cr);
	//cairo_rectangle(cr, 0, 0, width, height);
	//cairo_fill(cr);

	if( flip )
	{
		cairo_matrix_t matrix;
		cairo_translate(cr,width/2,height/2); // translate origin to the center
		//flip around Y axis
		cairo_matrix_init_scale (&matrix, -1.0, 1.0);
		cairo_transform (cr, &matrix);
		cairo_translate(cr,-width/2,-height/2); // translate origin back
	}

	if( angle != 0.0 )
	{
		cairo_translate(cr,width/2,height/2); // translate origin to the center
		cairo_rotate (cr, angle);
		cairo_translate(cr,-width/2,-height/2); // translate origin back
	}

	//gerbv_render_zoom_to_fit_display(gerber, screenRenderInfo);
	gerbv_render_zoom_to_fit_display_nobound(gerber, screenRenderInfo);

	if( SR->DB->ProductionDataS.TopGerberSolder != 0 )
	{
        cairo_push_group (cr);
		gerbv_render_layer_to_cairo_target (cr, mainProject->file[SR->DB->ProductionDataS.TopGerberSolder-1], screenRenderInfo);
        cairo_pop_group_to_source (cr);
        cairo_paint_with_alpha (cr, 0.9);
	}
	if( SR->DB->ProductionDataS.TopGerberPads != 0 )
	{
        cairo_push_group (cr);
		gerbv_render_layer_to_cairo_target (cr, mainProject->file[SR->DB->ProductionDataS.TopGerberPads-1], screenRenderInfo);
        cairo_pop_group_to_source (cr);
        cairo_paint_with_alpha (cr, 0.3);
	}
	if( SR->DB->ProductionDataS.TopGerberMech != 0 )
	{
        cairo_push_group (cr);
		gerbv_render_layer_to_cairo_target (cr, mainProject->file[SR->DB->ProductionDataS.TopGerberMech-1], screenRenderInfo);
        cairo_pop_group_to_source (cr);
        cairo_paint_with_alpha (cr, 1);
	}

	// Cleanup.
	cairo_destroy(cr);
	cairo_surface_destroy(surface);
}

//----------------------------------------------------------------------------------
// PaintAux
// 
//----------------------------------------------------------------------------------
void wxCameraControl::PaintAux()
{
	AuxVideoModeEnum modeAuxState;
	cs.Enter();
	modeAuxState = modeAux;
	cs.Leave();

	if( modeAuxState == AUX_BLANK )
		return;

	if( modeAuxState == AUX_SMOOTH_EDGE )
	{
		// control FilterSmoothDim value
		int filterSmoothDim = SR->DB->pCurrentFiducial->FilterSmoothDim | 0x00000001;

		MACHINE_CONFIG(CAMERA_COLOR)
			cvCvtColor( openCVFrame_24, openCVFrame_8, CV_BGR2GRAY );
		MACHINE_CONFIG_END

		cvSetImageROI( openCVFrame_8, cvRect( (CAM_W - AUX_WIN_W)/2, (CAM_H - AUX_WIN_H)/2, AUX_WIN_W, AUX_WIN_H ) );
		cvCopy( openCVFrame_8, openCVBuffer_8 );
		cvResetImageROI( openCVFrame_8 );
		cvSmooth( openCVBuffer_8, openCVBuffer_8, SR->DB->pCurrentFiducial->FilterSmoothType + 1, filterSmoothDim, filterSmoothDim );
		cvCanny( openCVBuffer_8, openCVBuffer_8, SR->DB->pCurrentFiducial->FilterEdgeThr, SR->DB->pCurrentFiducial->FilterEdgeThr/2 );
		cvCvtColor( openCVBuffer_8, openCVBuffer_24, CV_GRAY2BGR );

		videoAux->SetImage( wxImage( AUX_WIN_W, AUX_WIN_H, (unsigned char*)openCVBuffer_24->imageData, true ) );
	}
	else if( modeAuxState == AUX_CAMPOSITION )
	{
		cvCopy( openCVWorkPlace, openCVBuffer_24 );

		double cameraX, cameraY;
		SR->GetCameraPosition( cameraX, cameraY );

		int x1 = (cameraX - WORKPLACE_X)*(float(WORKPLACE_IMG_W - 1)/WORKPLACE_DIM_X) - WORKPLACE_IMG_CAM_W / 2 + WORKPLACE_IMG_DELTA;
		int y1 = -(cameraY - WORKPLACE_Y)*(float(WORKPLACE_IMG_H - 1)/WORKPLACE_DIM_Y) - WORKPLACE_IMG_CAM_H / 2;

		// if top gerber selected, draw it
		if( SR->DB->ProductionDataS.TopGerberOn && drawGerber )
		{
			// create a top level libgerbv structure
			GdkColor darkGreenColor = {0, 0, 19000, 0};
			mainProject = gerbv_create_project();
			mainProject->background = darkGreenColor;

			//width = pcbImage->GetWidth();
			//height = pcbImage->GetHeight();
			width = abs(boardX2 - boardX1)+1;
			height = abs(boardY2 - boardY1)+1;
			side = MAX(width, height);

			//width = 100;
			//height = 100;
			rot = 0.0;
			layerFlip = 0;

			topPixelY = 0;
			leftPixelX = 0;

		    // make sure we change the render type to "cairo" instead of the GDK alternative
		    screenRenderInfo.renderType = GERBV_RENDER_TYPE_CAIRO_HIGH_QUALITY;
		    screenRenderInfo.displayHeight = side;
		    screenRenderInfo.displayWidth = side;

		    // Numero di livelli inseriti nel progetto
		    gerberIndex = 0;

			loadGerber();

			wxBitmap blankBmp( wxImage( AUX_WIN_W, AUX_WIN_H, (unsigned char*)openCVBuffer_24->imageData, true ) );
			wxMemoryDC dc;
			dc.SelectObject( blankBmp );

		    unsigned char *cairo_buffer = new unsigned char[side*side*4];
		    unsigned char* wx_buffer = new unsigned char[side*side*4];

		    cairoDraw(cairo_buffer, mainProject, &screenRenderInfo, SR->DB->ProductionDataS.TopGerberRot, SR->DB->ProductionDataS.TopGerberFlip);
		    cairoToWxImageFormat(cairo_buffer, wx_buffer, screenRenderInfo.displayWidth, screenRenderInfo.displayHeight);

			// Blit final image to the screen.
			wxBitmap m_bitmap(wxImage(side, side, wx_buffer, true));

			// Get dimensions
			gerbv_render_size_t boundingbox;
			gerbv_render_get_boundingbox(mainProject, &boundingbox);
			double xdim, ydim;
			xdim = INCH_TO_MM*fabs(boundingbox.right-boundingbox.left);
			ydim = INCH_TO_MM*fabs(boundingbox.top-boundingbox.bottom);
			double Cx = fabs( xdim * cos(SR->DB->ProductionDataS.TopGerberRot) + ydim * sin(SR->DB->ProductionDataS.TopGerberRot) );
			double Cy = fabs( -xdim * sin(SR->DB->ProductionDataS.TopGerberRot) + ydim * cos(SR->DB->ProductionDataS.TopGerberRot) );

			//dc.DrawBitmap(m_bitmap, boardX1, boardY2, true);

			// if not a squared pcb...
			if( width != height )
			{
				int val = 128;

				// Draw rectangles in the outside of pcb borders
				dc.SetPen( wxPen( wxColour( val, val, val ), 1 ) );
				wxBrush brush( wxColour( val, val, val ) );
				dc.SetBrush(brush);

				if( Cx >= Cy )
				{
					// pcb with a top and bottom clear space on the window image
					topPixelY = ( side - myLRound( Cy / INCH_TO_MM * screenRenderInfo.scaleFactorY) )/2;
					dc.DrawBitmap(m_bitmap, boardX1, boardY2-topPixelY, true);
					dc.DrawRectangle( boardX1, boardY2-topPixelY-1, side, topPixelY+1 );
					dc.DrawRectangle( boardX1, boardY2+height, side, topPixelY+1 );
				}
				else
				{
					// pcb with a left and right clear space on the window image
					leftPixelX = ( side - myLRound( Cx / INCH_TO_MM * screenRenderInfo.scaleFactorX) )/2 ;
					dc.DrawBitmap(m_bitmap, boardX1-leftPixelX-1, boardY2, true);
					dc.DrawRectangle( boardX1-leftPixelX-1, boardY2, leftPixelX+1, side );
					dc.DrawRectangle( boardX1+width+1, boardY2, leftPixelX+1, side );
				}
			}
			else
				dc.DrawBitmap(m_bitmap, boardX1, boardY2, true);

			dc.SetPen( wxPen( wxColour( 255, 0, 0 ), 1 ) );
			dc.SetBrush( *wxTRANSPARENT_BRUSH );
			dc.DrawRectangle( x1, y1, WORKPLACE_IMG_CAM_W, WORKPLACE_IMG_CAM_H );

			// Cleanup.
			delete wx_buffer;
			delete cairo_buffer;
			gerbv_destroy_project (mainProject);

			videoAux->SetImage(blankBmp);
		}
		else
		{
			cvRectangle( openCVBuffer_24, cvPoint( x1, y1 ), cvPoint( x1 + WORKPLACE_IMG_CAM_W, y1 + WORKPLACE_IMG_CAM_H ), CV_RGB( 0, 0, 255 ), 1 );

			videoAux->SetImage( wxImage( AUX_WIN_W, AUX_WIN_H, (unsigned char*)openCVBuffer_24->imageData, true ) );
		}
	}
	else if(modeAuxState == AUX_INSPECTION_MASK){

		videoAux->SetImage( wxImage( AUX_WIN_W, AUX_WIN_H, (unsigned char*)Mask_frame.data, true ) );


	}

	else if(modeAuxState == AUX_HISTOGRAM){

		if(Working_frame.empty())
			return;

		cv::Mat frame_tmp=Working_frame.clone();
		cv::cvtColor(frame_tmp,frame_tmp, CV_BGR2HSV);
		vector<cv::Mat> bgr_planes;
		split( frame_tmp, bgr_planes );
		//cout<<"hue histogram: "<<SR->DB->pAUTOInspectionCurrentSiteStruct->BestHue<<endl;
		bgr_planes[0]=bgr_planes[0]*SR->DB->pAUTOInspectionCurrentSiteStruct->BestHue;
		merge(bgr_planes,frame_tmp ); //hue changed
		cv::cvtColor(frame_tmp,frame_tmp, CV_HSV2BGR);

		split( frame_tmp, bgr_planes ); // those planes contains BGR
		/// Establish the number of bins
		int histSize = 64;
		/// Set the ranges ( for B,G,R) )
		float range[] = { 0, 255 } ;
		const float* histRange = { range };

		bool uniform = true; bool accumulate = false;

		cv::Mat b_hist, g_hist, r_hist;

		/// Compute the histograms:
		calcHist( &bgr_planes[0], 1, 0, cv::Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
		calcHist( &bgr_planes[1], 1, 0, cv::Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
		calcHist( &bgr_planes[2], 1, 0, cv::Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

		// Draw the histograms for B, G and R
		int hist_w = AUX_WIN_W; int hist_h = AUX_WIN_H;
		int bin_w = cvRound( (double) hist_w/histSize );

		cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );

		/// Normalize the result to [ 0, histImage.rows ]
		normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );
		normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );
		normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );

		/// Draw for each channel
		for( int i = 1; i < histSize; i++ )
		{
			cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
							 cv::Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
							 cv::Scalar( 255, 0, 0), 2, 8, 0  );
			cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
							 cv::Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
							 cv::Scalar( 0, 255, 0), 2, 8, 0  );
			cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
							 cv::Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
							 cv::Scalar( 0, 0, 255), 2, 8, 0  );
		}
		if(SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannel==0){
			cv::line(histImage ,cv::Point(SR->DB->pAUTOInspectionCurrentSiteStruct->PadThreshold*2, 0), cv::Point(SR->DB->pAUTOInspectionCurrentSiteStruct->PadThreshold*2, AUX_WIN_H), cv::Scalar(255,0,0));
		}
		if(SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannel==1){
			cv::line(histImage ,cv::Point(SR->DB->pAUTOInspectionCurrentSiteStruct->PadThreshold*2, 0), cv::Point(SR->DB->pAUTOInspectionCurrentSiteStruct->PadThreshold*2, AUX_WIN_H), cv::Scalar(0,255,0));
		}
		if(SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannel==2){
			cv::line(histImage ,cv::Point(SR->DB->pAUTOInspectionCurrentSiteStruct->PadThreshold*2, 0), cv::Point(SR->DB->pAUTOInspectionCurrentSiteStruct->PadThreshold*2, AUX_WIN_H), cv::Scalar(0,0,255));
		}

		videoAux->SetImage( wxImage( AUX_WIN_W, AUX_WIN_H, (unsigned char*)histImage.data, true ) );
	}
	else if(modeAuxState ==AUX_PRINTING_MASK){

		if (Pad_Mask_frame.empty())
			return;

		if(Pad_Mask_frame.channels()==1){
			cv::cvtColor(Pad_Mask_frame,Pad_Mask_frame, CV_GRAY2RGB);
		}
		//set the mask image on aux
		if(Pad_Mask_frame.rows == AUX_WIN_H && Pad_Mask_frame.cols == AUX_WIN_W)
			videoAux->SetImage( wxImage( AUX_WIN_W, AUX_WIN_H, (unsigned char*)Pad_Mask_frame.data, true ) );
		else{
			cv::resize(Pad_Mask_frame, Pad_Mask_frame, cv::Size(AUX_WIN_W, AUX_WIN_H) );
			videoAux->SetImage( wxImage( AUX_WIN_W, AUX_WIN_H, (unsigned char*)Pad_Mask_frame.data, true ) );
		}

	}
}

//----------------------------------------------------------------------------------
// StopCapture
// 
//----------------------------------------------------------------------------------
void wxCameraControl::StopCapture()
{
	isVideoTimerOn = false;
	correctBC = true;

	MACHINE_CONFIG( CAMERA_ENABLE )
		while( isVideoTimerOn_lock == true )
		{
			::wxMilliSleep(10);
			::wxYieldIfNeeded();
			::wxMilliSleep(10);
		}
	MACHINE_CONFIG_END
}

//----------------------------------------------------------------------------------
// VideoMainOnRightClick
// Mouse right click event
//----------------------------------------------------------------------------------
void wxCameraControl::VideoMainOnRightClick( wxMouseEvent& e )
{
	if( modeMain == MAIN_MOUSE_CUR_MANUAL ||
		modeMain == MAIN_CAMERA_VERIFY )
	{
		// change crosshair shape
		crosshairShape = ( crosshairShape == CROSSHAIR_CIRCLE ) ? CROSSHAIR_RECT : CROSSHAIR_CIRCLE;

		if( !isVideoTimerOn )
			PaintMain();
	}
	else if( modeMain == MAIN_MOUSE_CUR )
	{
		// if right click is disabled skip
		if( !rightClickEnable )
			return;

		// if this fiducial is on frame skip
		if( !IsFiducialOnPCB( SR->DB->pCurrentFiducial->Type ) )
			return;

		// change fiducial shape
		SR->DB->pCurrentFiducial->SearchMode = ( SR->DB->pCurrentFiducial->SearchMode == SEARCH_MODE_CIRCLE ) ? SEARCH_MODE_RECTANGLE : SEARCH_MODE_CIRCLE;

		wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
		e.SetId( ID_SEARCH_SHAPE );
		parent->GetEventHandler()->AddPendingEvent( e );

		if( !isVideoTimerOn )
			PaintMain();
	}
}

//----------------------------------------------------------------------------------
// VideoMainOnWheel
// Mouse wheel event
//----------------------------------------------------------------------------------
void wxCameraControl::VideoMainOnWheel( wxMouseEvent& e )
{
	if( modeMain == MAIN_MOUSE_CUR_MANUAL ||
		modeMain == MAIN_CAMERA_VERIFY )
	{
		if( crosshairShape == CROSSHAIR_CIRCLE )
		{
			if( e.GetWheelRotation() > 0 && crosshairCR < MIN( CAM_W/2, CAM_H/2 ) )
				crosshairCR++;
			else if( e.GetWheelRotation() < 0 && crosshairCR > 0 )
				crosshairCR--;
		}
		else if( crosshairShape == CROSSHAIR_RECT )
		{
			if( e.GetWheelRotation() > 0 )
			{
				if( e.AltDown() && crosshairRX < MIN( CAM_W/2, CAM_H/2 ) )
					crosshairRX++;
				else if( e.ControlDown() && crosshairRY < MIN( CAM_W/2, CAM_H/2 ) )
					crosshairRY++;
				else if( crosshairRX < MIN( CAM_W/2, CAM_H/2 ) && crosshairRY < MIN( CAM_W/2, CAM_H/2 ) )
				{
					crosshairRX++;
					crosshairRY++;
				}
			}
			else if( e.GetWheelRotation() < 0 )
			{
				if( e.AltDown() && crosshairRX > 0 )
					crosshairRX--;
				else if( e.ControlDown() && crosshairRY > 0 )
					crosshairRY--;
				else if( crosshairRX > 0 && crosshairRY > 0 )
				{
					crosshairRX--;
					crosshairRY--;
				}
			}
		}

		if( !isVideoTimerOn )
			PaintMain();
	}
	else if( modeMain == MAIN_MOUSE_CUR )
	{
		// if wheel is disabled skip
		if( !wheelEnable )
			return;

		if( SR->DB->pCurrentFiducial->SearchMode == SEARCH_MODE_CIRCLE )
		{
			int old = SR->DB->pCurrentFiducial->CircleDiameter;
			//
			float diameter_mm = SR->DB->pCurrentFiducial->CircleDiameter * MM_X_PIXEL;
			if( e.GetWheelRotation() > 0 )
				diameter_mm += CIRCLE_DIAMETER_STEP_MM;
			else if( e.GetWheelRotation() < 0 )
				diameter_mm -= CIRCLE_DIAMETER_STEP_MM;
			diameter_mm = MID( CIRCLE_DIAMETER_MIN_MM, diameter_mm, CIRCLE_DIAMETER_MAX_MM );
			//
			SR->DB->pCurrentFiducial->CircleDiameter = myLRound( diameter_mm / MM_X_PIXEL );
			SR->DB->CameraZeroParamsS.CircleDiameter = myLRound( diameter_mm / MM_X_PIXEL );
			//
			if( old != SR->DB->pCurrentFiducial->CircleDiameter )
			{
				wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
				e.SetId( ID_SEARCH_CIRCLE_RADIUS );
				parent->GetEventHandler()->AddPendingEvent( e );
			}
		}
		else if( SR->DB->pCurrentFiducial->SearchMode == SEARCH_MODE_RECTANGLE )
		{
			int oldX = SR->DB->pCurrentFiducial->RectangleSideX;
			int oldY = SR->DB->pCurrentFiducial->RectangleSideY;
			//
			float sideX_mm = SR->DB->pCurrentFiducial->RectangleSideX * MM_X_PIXEL;
			float sideY_mm = SR->DB->pCurrentFiducial->RectangleSideY * MM_X_PIXEL;

			if( e.GetWheelRotation() > 0 )
			{
				if( e.AltDown() )
					sideX_mm += RECTANGLE_SIDE_STEP_MM;
				else if( e.ControlDown() )
					sideY_mm += RECTANGLE_SIDE_STEP_MM;
				else
				{
					sideX_mm += RECTANGLE_SIDE_STEP_MM;
					sideY_mm += RECTANGLE_SIDE_STEP_MM;
				}
			}
			else if( e.GetWheelRotation() < 0 )
			{
				if( e.AltDown() )
					sideX_mm -= RECTANGLE_SIDE_STEP_MM;
				else if( e.ControlDown() )
					sideY_mm -= RECTANGLE_SIDE_STEP_MM;
				else
				{
					sideX_mm -= RECTANGLE_SIDE_STEP_MM;
					sideY_mm -= RECTANGLE_SIDE_STEP_MM;
				}
			}
			sideX_mm = MID( RECT_X_MIN_MM, sideX_mm, RECT_X_MAX_MM );
			sideY_mm = MID( RECT_Y_MIN_MM, sideY_mm, RECT_Y_MAX_MM );
			//
			SR->DB->pCurrentFiducial->RectangleSideX = myLRound( sideX_mm / MM_X_PIXEL );
			SR->DB->pCurrentFiducial->RectangleSideY = myLRound( sideY_mm / MM_X_PIXEL );
			//
			if( oldX != SR->DB->pCurrentFiducial->RectangleSideX || oldY != SR->DB->pCurrentFiducial->RectangleSideY )
			{
				wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
				e.SetId( ID_SEARCH_RECT_SIDES );
				parent->GetEventHandler()->AddPendingEvent( e );
			}
		}

		if( !isVideoTimerOn )
			PaintMain();
	}
	else if( modeMain == MAIN_CAMERA_TEMPLATE )
	{
		if( e.GetWheelRotation() > 0 && templateRectDim < TEMPLATE_DIM_MAX )
			templateRectDim += TEMPLATE_DIM_INC;
		else if( e.GetWheelRotation() < 0 && templateRectDim > TEMPLATE_DIM_MIN )
			templateRectDim -= TEMPLATE_DIM_INC;

		if( !isVideoTimerOn )
			PaintMain();
	}
	else if(modeMain == MAIN_INSPECTION_ZOOM)
	{
		if( e.GetWheelRotation() > 0 && currentZoomLevel < MAX_ZOOM ){
			currentZoomLevel += 0.5;
		}
		else if( e.GetWheelRotation() < 0 && currentZoomLevel > MIN_ZOOM ){
			currentZoomLevel -= 0.5;
			if(currentZoomLevel==1){
				cv::Mat OriginalPicture=Working_frame.clone();
				wxFindUncoveredPads(&OriginalPicture); //this function draws the red lines

				wxBitmap bmp = wxImage( CAM_W, CAM_H, (unsigned char*)OriginalPicture.data, true );
				videoMain->SetImage( bmp );
				return;
			}
		}
		else if(currentZoomLevel==1||currentZoomLevel==4){
			return;
		}

		if( (Working_frame.cols ==0) || (Working_frame.rows ==0)){
			return;
		}
		int originalX;
		int originalY;
		cv::Mat OriginalPicture(Working_frame);
		cv::Mat CroppedPicture( round(CAM_H/currentZoomLevel), round(CAM_W/ currentZoomLevel), CV_8UC3);
		cv::Mat ZoomedPicture;
		for(int i =0; i<CroppedPicture.rows; i++){
			for(int j =0; j<CroppedPicture.cols; j++){
				originalY = i+cursorMain.y - CroppedPicture.cols/2;
				originalX = j+cursorMain.x - CroppedPicture.rows/2;
				if(originalY<0){
					originalY=0;
				}
				if(originalX<0){
					originalX=0;
				}

				if(originalX> CAM_W || originalY>CAM_H){
					CroppedPicture.at<cv::Vec3b>(i,j) = cv::Vec3b(0,0,0);
					continue;
				}

				CroppedPicture.at<cv::Vec3b>(i,j) = OriginalPicture.at<cv::Vec3b>(originalY,originalX);


				}
		}
		//cv::imshow("immagine croppata", CroppedPicture);
		//cv::waitKey(100);
		cv::resize(CroppedPicture,ZoomedPicture, cv::Size(CAM_W, CAM_H));
		wxFindUncoveredPads(&ZoomedPicture); //this function draws the red lines

		wxBitmap bmp = wxImage( CAM_W, CAM_H, (unsigned char*)ZoomedPicture.data, true );
		videoMain->SetImage( bmp );
	}

}

bool wxCameraControl::wxFindUncoveredPads(cv::Mat* frame){

	if(frame->rows==0 || frame->cols==0){
		return false;
	}

	//we use the HUE
	if(SR->DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE != -1){
		cv::Mat frame_copy = frame->clone();
		vector<cv::Mat> bgr_planes;
		cv::Mat frame_HSV;
		cv::cvtColor(*frame, frame_HSV , CV_BGR2HSV);
		cv::split( frame_HSV, bgr_planes );

		cv::Mat PadTHR(bgr_planes[0].rows,bgr_planes[0].cols , CV_8UC1);
		//double treshold, up and down
		for (int i=0; i< bgr_planes[0].rows; i++)
		{
				for (int j=0; j< bgr_planes[0].cols; j++)
				{
					int editValue=bgr_planes[0].at<uchar>(i,j);

					if((editValue> (SR->DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE - SR->DB->pAUTOInspectionCurrentSiteStruct->PasteHUEWidth/2) )&&(editValue < SR->DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE + SR->DB->pAUTOInspectionCurrentSiteStruct->PasteHUEWidth/2)) //check whether value is within range.
					{
						PadTHR.at<uchar>(i,j)=255;
					}
					else
					{
						PadTHR.at<uchar>(i,j)=0;
					}
				}
			}
		//cv::imshow("padThr", PadTHR);
		//cv::waitKey(100);

		vector<vector<cv::Point> > contours;
		cv::findContours( PadTHR, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		int area_region;

		for (int i = 0; i < contours.size(); i++){
				// Check area
			//area_region=cv::contourArea(contours[i]);
			//if ( area_region < MIN_AREA_SPI) continue;

			bool exit_cycle = false;
			for (int j = 0; j < contours[i].size(); j++){
				if(contours[i][j].x<BORDER_DISTANCE_POST_PRINTING||contours[i][j].x>frame_copy.cols-BORDER_DISTANCE_POST_PRINTING)
				{
					exit_cycle=true;
					break;
				};
				if(contours[i][j].y<BORDER_DISTANCE_POST_PRINTING||contours[i][j].y>frame_copy.rows-BORDER_DISTANCE_POST_PRINTING)
				{
					exit_cycle=true;
					break;
				};
			}

			if (exit_cycle){
				continue;
			}
			cv::drawContours(frame_copy, contours, i, CV_RGB(0,0,255) );

		}
		frame_copy.copyTo(*frame);
		return true;

	}//end HUE part
	else if(SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads != -1){

		cv::Mat frame_copy = frame->clone();
		vector<cv::Mat> bgr_planes;
		cv::split( *frame, bgr_planes );
		cv::Mat BestChannelImg;
		switch (SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads){
			case BLUE_CHANNEL:
				BestChannelImg = bgr_planes[0].clone();
				//cout<<"best channel blue"<<endl;
				break;
			case GREEN_CHANNEL:
				BestChannelImg = bgr_planes[1].clone();
				//cout<<"best channel green"<<endl;
				break;
			case RED_CHANNEL:
				BestChannelImg = bgr_planes[2].clone();
				//cout<<"best channel red"<<endl;
				break;
		}
		//imshow("BestChannelImg",BestChannelImg);
		//cv::waitKey(100);
		//cout<<"central pad color"<< DB->pAUTOInspectionCurrentSiteStruct->CentralPadsColor<<endl;
		//cout<<"width /2"<< DB->pAUTOInspectionCurrentSiteStruct->PadsColorWidth/2<<endl;

		cv::Mat PadTHR(bgr_planes[0].rows,bgr_planes[0].cols , CV_8UC1);

		for (int i=0; i< bgr_planes[0].rows; i++)
		{
				for (int j=0; j< bgr_planes[0].cols; j++)
				{
					int editValue=BestChannelImg.at<uchar>(i,j);

					if((editValue >= (SR->DB->pAUTOInspectionCurrentSiteStruct->CentralPadsColor - SR->DB->pAUTOInspectionCurrentSiteStruct->PadsColorWidth) )&&(editValue <= SR->DB->pAUTOInspectionCurrentSiteStruct->CentralPadsColor + SR->DB->pAUTOInspectionCurrentSiteStruct->PadsColorWidth)) //check whether value is within range.
					{
						PadTHR.at<uchar>(i,j)=255;
					}
					else
					{
						PadTHR.at<uchar>(i,j)=0;
					}
				}
			}
		//cv::imshow("padThr", PadTHR);
		//cv::waitKey(100);

		vector<vector<cv::Point> > contours;
		cv::findContours( PadTHR, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		int area_region;

		for (int i = 0; i < contours.size(); i++){

							bool exit_cycle = false;
							for (int j = 0; j < contours[i].size(); j++){
								if(contours[i][j].x<BORDER_DISTANCE_POST_PRINTING||contours[i][j].x>frame_copy.cols-BORDER_DISTANCE_POST_PRINTING)
								{
									exit_cycle=true;
									break;
								};
								if(contours[i][j].y<BORDER_DISTANCE_POST_PRINTING||contours[i][j].y>frame_copy.rows-BORDER_DISTANCE_POST_PRINTING)
								{
									exit_cycle=true;
									break;
								};
							}

							if (exit_cycle){
								continue;
							}
							cv::drawContours(frame_copy, contours, i, CV_RGB(0,0,255) );

							}
		frame_copy.copyTo(*frame);
		return true;

	}




}

//----------------------------------------------------------------------------------
// VideoMainOnMove
// Mouse move event
//----------------------------------------------------------------------------------
void wxCameraControl::VideoMainOnMove( wxMouseEvent& e )
{
	if( modeMain == MAIN_MOUSE_CUR ||
		modeMain == MAIN_MOUSE_CUR_MANUAL ||
		modeMain == MAIN_LINE_X ||
		modeMain == MAIN_LINE_Y ||
		modeMain == MAIN_LINE_XY ||
		modeMain == MAIN_MOUSE_CUR_NO_CROSSHAIR ||
		modeMain == MAIN_MOUSE_CUR_TEACH )
	{
		cursorMain.x = e.GetPosition().x + videoMain->GetImageDisplacement() + videoMain->GetControlBorder();
		cursorMain.y = e.GetPosition().y + videoMain->GetImageDisplacement() + videoMain->GetControlBorder();

		if( !isVideoTimerOn )
			PaintMain();
	}
	//aggiunto!
	cursorMain.x = e.GetPosition().x + videoMain->GetImageDisplacement() + videoMain->GetControlBorder();
	cursorMain.y = e.GetPosition().y + videoMain->GetImageDisplacement() + videoMain->GetControlBorder();
}

//----------------------------------------------------------------------------------
// VideoMainOnEnter
// Mouse enter event
//----------------------------------------------------------------------------------
void wxCameraControl::VideoMainOnEnter( wxMouseEvent& e )
{
	// Set cross cursor
	if( modeMain == MAIN_MOUSE_CUR ||
		modeMain == MAIN_MOUSE_CUR_MANUAL ||
		modeMain == MAIN_LINE_X ||
		modeMain == MAIN_LINE_Y ||
		modeMain == MAIN_LINE_XY ||
		modeMain == MAIN_MOUSE_CUR_NO_CROSSHAIR ||
		modeMain == MAIN_MOUSE_CUR_TEACH )
	{
		videoMain->SetCursor( wxCURSOR_CROSS );
	}

	// Set focus on videoMain control
	videoMain->SetFocus();
}

//----------------------------------------------------------------------------------
// VideoMainOnLeave
// Mouse leave event
//----------------------------------------------------------------------------------
void wxCameraControl::VideoMainOnLeave( wxMouseEvent& e )
{
	if( modeMain == MAIN_MOUSE_CUR ||
		modeMain == MAIN_MOUSE_CUR_MANUAL ||
		modeMain == MAIN_LINE_X ||
		modeMain == MAIN_LINE_Y ||
		modeMain == MAIN_LINE_XY ||
		modeMain == MAIN_MOUSE_CUR_NO_CROSSHAIR ||
		modeMain == MAIN_MOUSE_CUR_TEACH )
	{
		cursorMain.x = -CAM_W;
		cursorMain.y = -CAM_H;

		if( !isVideoTimerOn )
			PaintMain();
	}

	// Set focus on another control
	if( videoAux != NULL )
		videoAux->SetFocus();
}

//----------------------------------------------------------------------------------
// MainVideoKeyPress
// Mouse enter event
//----------------------------------------------------------------------------------
void wxCameraControl::VideoMainOnKeyPress( wxKeyEvent& e )
{
	if( modeMain == MAIN_MOUSE_CUR ||
		modeMain == MAIN_MOUSE_CUR_MANUAL ||
		modeMain == MAIN_LINE_X ||
		modeMain == MAIN_LINE_Y ||
		modeMain == MAIN_LINE_XY ||
		modeMain == MAIN_MOUSE_CUR_NO_CROSSHAIR ||
		modeMain == MAIN_MOUSE_CUR_TEACH )
	{
		switch( e.GetKeyCode() )
		{
			case WXK_UP:
				if( cursorMain.y > 10 )
				{
					cursorMain.y--;
				}
				if( !isVideoTimerOn )
					PaintMain();
				break;

			case WXK_DOWN:
				if( cursorMain.y < CAM_H - 10 )
				{
					cursorMain.y++;
				}
				if( !isVideoTimerOn )
					PaintMain();
				break;

			case WXK_LEFT:
				if( cursorMain.x > 10 )
				{
					cursorMain.x--;
				}
				if( !isVideoTimerOn )
					PaintMain();
				break;

			case WXK_RIGHT:
				if( cursorMain.x < CAM_W - 10 )
				{
					cursorMain.x++;
				}
				if( !isVideoTimerOn )
					PaintMain();
				break;
		}
	}
}

//----------------------------------------------------------------------------------
// ToWorkplace
//----------------------------------------------------------------------------------
PointI wxCameraControl::ToWorkplace( float x, float y )
{
	PointI pos;
	pos.X = (x - WORKPLACE_X)*(float(WORKPLACE_IMG_W - 1)/WORKPLACE_DIM_X) + WORKPLACE_IMG_DELTA;
	pos.Y = -(y - WORKPLACE_Y)*(float(WORKPLACE_IMG_H - 1)/WORKPLACE_DIM_Y);
	return pos;
}


//----------------------------------------------------------------------------------
// FromWorkplace
//----------------------------------------------------------------------------------
PointF wxCameraControl::FromWorkplace( float x, float y )
{
	PointF pos;
	pos.X = (x - WORKPLACE_IMG_DELTA)*(WORKPLACE_DIM_X/float(WORKPLACE_IMG_W - 1)) + WORKPLACE_X;
	pos.Y = -y*(WORKPLACE_DIM_Y/float(WORKPLACE_IMG_H - 1)) + WORKPLACE_Y;
	return pos;
}


//----------------------------------------------------------------------------------
// DrawWorkplace
// Draw the workplace image
//----------------------------------------------------------------------------------
void wxCameraControl::DrawWorkplace( float left, float low, float w, float h )
{
	// clear image
	cvSetZero( openCVWorkPlace );

	// workplace
	cvRectangle( openCVWorkPlace, cvPoint( WORKPLACE_IMG_DELTA, 0 ), cvPoint( WORKPLACE_IMG_W + WORKPLACE_IMG_DELTA, WORKPLACE_IMG_H ), CV_RGB( 128, 128, 128 ), CV_FILLED );

	// board
	if( w > 0 && h > 0 )
	{
		boardX1 = (left - WORKPLACE_X)*(float(WORKPLACE_IMG_W - 1)/WORKPLACE_DIM_X) + WORKPLACE_IMG_DELTA;
		boardY1 = -(low - WORKPLACE_Y)*(float(WORKPLACE_IMG_H - 1)/WORKPLACE_DIM_Y);

		// si considera: 1 mm = 1 pixel
		boardX2 = boardX1 + w*(float(WORKPLACE_IMG_W - 1)/WORKPLACE_DIM_X);
		boardY2 = boardY1 - h*(float(WORKPLACE_IMG_H - 1)/WORKPLACE_DIM_Y);

		if( SR->DB->ProductionDataS.TopGerberOn )
			drawGerber = true;
		else
			cvRectangle( openCVWorkPlace, cvPoint( boardX1, boardY1 ), cvPoint( boardX2, boardY2 ), CV_RGB( 0, 255, 0 ), CV_FILLED );
	}
	else
		drawGerber = false;
}

//----------------------------------------------------------------------------------
// DrawWorkplaceWithSites
// Draw the workplace image and inspection sites
//----------------------------------------------------------------------------------
void wxCameraControl::DrawWorkplaceWithSites( float left, float low, float w, float h )
{
	DrawWorkplace( left, low, w, h );

	for( int i = 0; i < SR->DB->SiteCount(); i++ )
	{
		if( SR->DB->AUTOInspectionSiteStruct[i].X != 0.0 && SR->DB->AUTOInspectionSiteStruct[i].Y != 0.0 )
		{
			//PointI pos = ToWorkplace( SR->DB->ProductionDataS.PCBPosX + SR->DB->AUTOInspectionSiteStruct[i].X, SR->DB->ProductionDataS.PCBPosY + SR->DB->AUTOInspectionSiteStruct[i].Y );
			PointI pos = ToWorkplace(  (SR->DB->ProductionDataS.PCBPosX +SR->DB->FiducialParamsS[FIDUCIAL_TRA].X )  + SR->DB->AUTOInspectionSiteStruct[i].X,
					SR->DB->ProductionDataS.PCBPosY + SR->DB->FiducialParamsS[FIDUCIAL_TRA].Y + SR->DB->AUTOInspectionSiteStruct[i].Y );

			pos.X -= WORKPLACE_IMG_CAM_W / 2;
			pos.Y -= WORKPLACE_IMG_CAM_H / 2;

			cvRectangle( openCVWorkPlace, cvPoint( pos.X, pos.Y ), cvPoint( pos.X + WORKPLACE_IMG_CAM_W, pos.Y + WORKPLACE_IMG_CAM_H ), CV_RGB( 255, 0, 0 ), 1 );
		}
	}

}

//----------------------------------------------------------------------------------
// DrawWorkplacePoint
// Draw a point on the workplace
//----------------------------------------------------------------------------------
void wxCameraControl::DrawWorkplacePoint( float x, float y, CvScalar color )
{
	int X = (x - WORKPLACE_X)*(float(WORKPLACE_IMG_W - 1)/WORKPLACE_DIM_X) + WORKPLACE_IMG_DELTA;
	int Y = -(y - WORKPLACE_Y)*(float(WORKPLACE_IMG_H - 1)/WORKPLACE_DIM_Y);

	cvCircle( openCVWorkPlace, cvPoint( X, Y ), 2, color, CV_FILLED );
	PaintAux();
}

//----------------------------------------------------------------------------------
// GetFrames
// Wait untill num frames are stored
//----------------------------------------------------------------------------------
void wxCameraControl::GetFrames( int num )
{
	MACHINE_CONFIG( CAMERA_ENABLE )
		framesLeft = num;
	
		while( framesLeft > 0 )
		{
			::wxMilliSleep(10);
			::wxYieldIfNeeded();
			::wxMilliSleep(10);
		}
	MACHINE_CONFIG_END
}

//----------------------------------------------------------------------------------
// GetColorFrames
// Wait untill num frames are stored
//----------------------------------------------------------------------------------
void wxCameraControl::GetColorFrames( int num )
{
	MACHINE_CONFIG( CAMERA_ENABLE )
		MACHINE_CONFIG( CAMERA_COLOR )
		ColorFramesLeft = num;

		while( ColorFramesLeft > 0 )
		{
			::wxMilliSleep(10);
			::wxYieldIfNeeded();
			::wxMilliSleep(10);
		}

		MACHINE_CONFIG_END
	MACHINE_CONFIG_END
}

//----------------------------------------------------------------------------------
// GetBrightness
// Get video device brightness
//----------------------------------------------------------------------------------
int wxCameraControl::GetBrightness()
{
	unsigned int ret = 0;
	#ifndef __WXMSW__
	MACHINE_CONFIG( CAMERA_ENABLE )
		MACHINE_CONFIG_NOT( CAMERA_COLOR )
			v4lDevice.getBrightness( ret );
		MACHINE_CONFIG_ELSE
			ret= Brightness*327 - 32767;
		MACHINE_CONFIG_END
	MACHINE_CONFIG_END
	#endif

	return (int)ret;
}

//----------------------------------------------------------------------------------
// SetBrightness
// Set video device brightness
//----------------------------------------------------------------------------------
void wxCameraControl::SetBrightness( int value )
{
	#ifndef __WXMSW__
	MACHINE_CONFIG( CAMERA_ENABLE )
		MACHINE_CONFIG_NOT( CAMERA_COLOR )
			v4lDevice.setBrightness( value );
		MACHINE_CONFIG_ELSE
			Brightness = (value - 32767)/327.0; //in the range -100 +100
		MACHINE_CONFIG_END

	MACHINE_CONFIG_END
	#endif
}

//----------------------------------------------------------------------------------
// GetContrast
// Get video device contrast
//----------------------------------------------------------------------------------
int wxCameraControl::GetContrast()
{
	unsigned int ret = 0;
	#ifndef __WXMSW__
	MACHINE_CONFIG( CAMERA_ENABLE )
		MACHINE_CONFIG_NOT( CAMERA_COLOR )
			v4lDevice.getContrast( ret );
		MACHINE_CONFIG_ELSE
			ret = Contrast*32768;
		MACHINE_CONFIG_END
	MACHINE_CONFIG_END
	#endif

	return (int)ret;
}

//----------------------------------------------------------------------------------
// SetContrast
// Set video device contrast
//----------------------------------------------------------------------------------
void wxCameraControl::SetContrast( int value )
{
	#ifndef __WXMSW__
	MACHINE_CONFIG( CAMERA_ENABLE )
		MACHINE_CONFIG_NOT( CAMERA_COLOR )
			v4lDevice.setContrast( value );
		MACHINE_CONFIG_ELSE
			Contrast = (float)value/32767.0;
		MACHINE_CONFIG_END
	MACHINE_CONFIG_END
	#endif
}

cv::Mat wxCameraControl::GetWorkingColorFrame(int frame){
	return openCVFramesColorArray[frame];
};

wxColour wxCameraControl::getPixelColor(int x, int y){
	return videoMain->GetPixelColour(x,y);
}
int wxCameraControl::SeachCameraZero(){
	// Move the board to reaches the camera focus
	if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
	{
		return SR_ERROR;
	}
	cout<<"Posizione movimento x: "<<SR->DB->CameraZeroParamsS.X << "  y: "<<SR->DB->CameraZeroParamsS.Y<<endl;
	if(SR->MoveCameraAndWait( SR->DB->CameraZeroParamsS.X, SR->DB->CameraZeroParamsS.Y, ABS_MOVE )==SR_ERROR){
		cout<< "Camera can't reach position x: "<< SR->DB->CameraZeroParamsS.X << "  y: "<< SR->DB->CameraZeroParamsS.Y<< "  In SeachCameraZero"<< endl;
		return SR_ERROR;
	}
	if( SR->SetCamera( CAMERA_DOWN ) == SR_ERROR )
	{
		return SR_ERROR;
	}


	/*MACHINE_CONFIG_NOT( CAMERA_COLOR )
		SetBrightness( SR->DB->CameraZeroParamsS.CameraBrightness  );
		SetContrast( SR->DB->CameraZeroParamsS.CameraContrast  );
	MACHINE_CONFIG_ELSE
		SetBrightness( SR->DB->CameraZeroParamsS.CameraBrightness * 65535 );
		SetContrast( SR->DB->CameraZeroParamsS.CameraContrast * 65535 );
	MACHINE_CONFIG_END*/
	SetBrightness( SR->DB->CameraZeroParamsS.CameraBrightness * 65535 );
	SetContrast( SR->DB->CameraZeroParamsS.CameraContrast * 65535 );

	myMilliSleep(FLICKERING_DELAY*2);

	StartCapture();
	GetFrames( MAX_FRAMES_FIDUCIAL );
	StopCapture();

	//cv::imshow("zero camera", cv::Mat(openCVFramesArray[0]));
	//cv::waitKey(0);

	if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
	{
		return SR_ERROR;
	}


	float centerX = 0;
	float centerY = 0;
	float radius = 0;

	if( FindCircleCameraZero( CAM_W/2, CAM_H/2, centerX, centerY, radius ) == SR_OK )
	{
		SR->DB->cameraZeroFound.X = centerX;
		SR->DB->cameraZeroFound.Y = centerY;
		//cout<< "Circle found at coords x: "<<centerX<< " y: "<< centerY<< " and R: "<< radius<< endl;
		return SR_OK;
	}

	//cout<< "Circle NOT found "<<endl;

	return SR_WARNING;
}

int wxCameraControl::RetryCameraZero(){
	double differenceX = (SR->DB->cameraZeroFound.X - CAM_W / 2) * SR->DB->MachineParamsS.DnXPixMm;
	double differenceY = (SR->DB->cameraZeroFound.Y - CAM_H / 2) * SR->DB->MachineParamsS.DnYPixMm;
	//if( SR->MoveCameraAndWait(differenceX, differenceY, ABS_MOVE , LIMIT_OFF) == SR_ERROR ){
	if( SR->MoveCameraAndWait(differenceX, -differenceY, REL_MOVE) == SR_ERROR ){
		return SR_ERROR;
	}

	if( SR->SetCamera( CAMERA_DOWN ) == SR_ERROR ){
		return SR_ERROR;
	}
	SetBrightness( SR->DB->CameraZeroParamsS.CameraBrightness * 65535 );
	SetContrast( SR->DB->CameraZeroParamsS.CameraContrast * 65535 );

	myMilliSleep(FLICKERING_DELAY*2);

	StartCapture();
	GetFrames( MAX_FRAMES_FIDUCIAL );
	StopCapture();

	if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR ){
		return SR_ERROR;
	}


	float centerX = 0;
	float centerY = 0;
	float radius = 0;

	if( FindCircleCameraZero( CAM_W/2, CAM_H/2, centerX, centerY, radius ) == SR_OK )
	{
		SR->DB->cameraZeroFound.X += (centerX - CAM_W / 2);
		SR->DB->cameraZeroFound.Y += (centerY - CAM_H / 2);
		return SR_OK;
	}

	return SR_ERROR;
}

int wxCameraControl::ReallocateCamera(){

	if(device == "/dev/video0"){
		device = "/dev/video1";
	}else{
		device = "/dev/video0";
	}

	v4lDevice.closeDevice();
	sleep(1);
	std::cout<<"Reallocazione del device"<<device<<std::endl;

	MACHINE_CONFIG(CAMERA_COLOR)
		// Init v4l driver
		if ( !v4lDevice.openDevice( device, CAM_W_COLOR, CAM_H_COLOR, V4L2_PIX_FMT_YUYV ) ){
			return SR_ERROR;
		}
	MACHINE_CONFIG_ELSE
		// Init v4l driver
		if ( !v4lDevice.openDevice( device, CAM_W, CAM_H, V4L2_PIX_FMT_GREY ) ){
			return SR_ERROR;
		}

	MACHINE_CONFIG_END
}



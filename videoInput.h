#ifndef _VIDEOINPUT
#define _VIDEOINPUT


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include <wchar.h>

//////////////////////////////////////////////////////////
//Written by Theodore Watson - theo.watson@gmail.com    //
//Do whatever you want with this code but if you find   //
//a bug or make an improvement I would love to know!    //
//														//
//Warning This code is experimental 					//
//use at your own risk :)								//
//////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
/*                     Shoutouts 

Thanks to: 
			
		   Dillip Kumar Kara for crossbar code.
           Martin C Martin for msft event code
		   Zachary Lieberman for getting me into this stuff
		   and for being so generous with time and code.
		   The guys at Potion Design for helping me with VC++
		   Josh Fisher for being a serious C++ nerd :)
		   
		   And all the people using this library who send in 
		   bugs suggestions and thanks and keep me working on 
		   the next version - yeah thanks a lot ;)
		   
*/
/////////////////////////////////////////////////////////


//Example Usage
/*
	
	//create a videoInput object
	videoInput VI;
	
	//Prints out a list of available devices and returns num of devices found
	int numDevices = VI.listDevices();	
	
	int device1 = 0;  //this could be any deviceID that shows up in listDevices
	int device2 = 1;  //this could be any deviceID that shows up in listDevices
	
	//setup the first device - there are a number of options:
	
	VI.setupDevice(device1); 						  //setup the first device with the default settings
	//VI.setupDevice(device1, VI_COMPOSITE); 			  //or setup device with specific connection type
	//VI.setupDevice(device1, 320, 240);				  //or setup device with specified video size
	//VI.setupDevice(device1, 320, 240, VI_COMPOSITE);  //or setup device with video size and connection type

	
	//optionally setup a second (or third, fourth ...) device - same options as above
	VI.setupDevice(device2); 						  

	//As requested width and height can not always be accomodated
	//make sure to check the size once the device is setup

	int width 	= VI.getWidth(device1);
	int height 	= VI.getHeight(device1);
	int size	= VI.getSize(device1);
	
	
	//to get the data from the device first check if the data is new
	if(VI.isFrameNew(device1))
	{
		VI.getPixels(device1, false);	//returns pixels as a BGR (for openCV) unsigned char array
		VI.getPixels(device1, true); 	//returns pixels as a RGB (for openGL) unsigned char array	
	}
	
	//same applies to device2 etc
	
	//to get a settings dialog for the device
	VI.showSettingsWindow(device1);
	
	
	//Shut down devices properly
	VI.stopDevice(device1);
	VI.stopDevice(device2);
*/


//////////////////////////////////////   VARS AND DEFS   //////////////////////////////////

//videoInput defines
#define VI_VERSION	 0.195
#define VI_MAX_CAMERAS  20
#define VI_NUM_TYPES    18 //DON'T TOUCH =)

//defines for setPhyCon
#define VI_COMPOSITE 0
#define VI_S_VIDEO   1
#define VI_TUNER     2
#define VI_USB       3
	
//allows us to directShow classes here with the includes in the cpp
struct ICaptureGraphBuilder2;
struct IGraphBuilder;
struct IBaseFilter;
struct IAMCrossbar;
struct IMediaControl;
struct ISampleGrabber;
struct IMediaEventEx;
struct IAMStreamConfig;
struct _AMMediaType;
class SampleGrabberCallback;
typedef _AMMediaType AM_MEDIA_TYPE;

//keeps track of how many instances of VI are being used
static int comInitCount = 0;
static bool verbose     = true;

////////////////////////////////////////   VIDEO DEVICE   ///////////////////////////////////


class videoDevice{

	
	public:
		 
		videoDevice();
		void setSize(int w, int h);
		void NukeDownstream(IBaseFilter *pBF);
		void destroyGraph();
		~videoDevice();
		
		int videoSize;
		int width;
		int height;
		int tryWidth;
		int tryHeight;
		
		ICaptureGraphBuilder2 *pCaptureGraph;	// Capture graph builder object
		IGraphBuilder *pGraph;					// Graph builder object
	    IMediaControl *pControl;				// Media control object
		IBaseFilter *pVideoInputFilter;  		// Video Capture filter
		IBaseFilter *pGrabberF;
		IBaseFilter * pDestFilter;
		IAMStreamConfig *streamConf;
		ISampleGrabber * pGrabber;    			// Grabs frame
		AM_MEDIA_TYPE * pAmMediaType;
		
		IMediaEventEx * pMediaEvent;
		
		GUID videoType;
		
		SampleGrabberCallback * sgCallback;				
		long cbBuffer;
		
		bool tryDiffSize;
		bool useCrossbar;
		bool readyToCapture;
		bool sizeSet;
		bool setupStarted;
		int  connection;
		int	 storeConn;
		int  myID;
		
		char 	nDeviceName[255];
		WCHAR 	wDeviceName[255];
		
		unsigned char * pixels;
};




//////////////////////////////////////   VIDEO INPUT   /////////////////////////////////////



class videoInput{

	public:
		videoInput();
		~videoInput();
		
		//turns off console messages - default is to print messages
		static void setVerbose(bool _verbose);
		
		//Functions in rough order they should be used.
		static int listDevices(bool silent = false);
		
		//Choose one of these four to setup your device
		bool setupDevice(int deviceID);
		bool setupDevice(int deviceID, int w, int h);
		
		//These two are only for capture cards
		//USB and Firewire cameras souldn't specify connection 
		bool setupDevice(int deviceID, int connection);	
		bool setupDevice(int deviceID, int w, int h, int connection); 
		
		//Tells you when a new frame has arrived
		bool isFrameNew(int deviceID); 
		
		bool isDeviceSetup(int deviceID);
		    
		//Returns the pixels - flipRedAndBlue toggles RGB/BGR flipping
		unsigned char * getPixels(int deviceID, bool flipRedAndBlue);
		
		//Or pass in a buffer for getPixels to fill returns true if successful.
		bool getPixels(int id, unsigned char * pixels, bool flipRedAndBlue);
		
		//Launches a pop up settings window
		//For some reason in GLUT you have to call it twice each time. 
		void showSettingsWindow(int deviceID);
		
		//get width, height and number of pixels
		int  getWidth(int deviceID);
		int  getHeight(int deviceID);
		int  getSize(int deviceID);
		
		//completely stops and frees a device
		void stopDevice(int deviceID);
		
		//as above but then sets it up with same settings
		bool restartDevice(int deviceID);
		
		//number of devices available
		int  devicesFound;

		
	private:		
		void setPhyCon(int deviceID, int conn);                   
		void setAttemptCaptureSize(int deviceID, int w, int h);   
		bool setup(int deviceID);
		int  start(int deviceID, videoDevice * VD);                   
		int  getDeviceCount();
		
		HRESULT getDevice(IBaseFilter **pSrcFilter, int deviceID, WCHAR * wDeviceName, char * nDeviceName);
		HRESULT ShowFilterPropertyPages(IBaseFilter *pFilter);
		HRESULT SaveGraphFile(IGraphBuilder *pGraph, WCHAR *wszPath);
		HRESULT routeCrossbar(ICaptureGraphBuilder2 **ppBuild, IBaseFilter **pVidInFilter, int conType, GUID captureMode);
			
		//don't touch
		static bool comInit();
		static bool comUnInit();

		int  connection;
		
		GUID CAPTURE_MODE;
		
		//Extra video subtypes
		GUID MEDIASUBTYPE_Y800;
		GUID MEDIASUBTYPE_Y8;
		GUID MEDIASUBTYPE_GREY;

		videoDevice * VDList[VI_MAX_CAMERAS];
		GUID mediaSubtypes[VI_NUM_TYPES];

}; 
  
 
 
 #endif


















/////////////////////////////////////////////////////////////////////////////
//IAMCrossbar Stuff 
//- Borrowed and adapted from CCaptureVideo::StartTVTuner in CaptureVideo.cpp
//--------------------------------------------------------------------------//
// Copyright DILLIP KUMAR KARA 2004
// You may do whatever you want with this code, as long as you include this
// copyright notice in your implementation files.
// Comments and bug Reports: codeguru_bank@yahoo.com
//--------------------------------------------------------------------------//
 
 
 
//Modified streams.h file 
/*

//------------------------------------------------------------------------------
// File: Streams.h
//
// Desc: DirectShow base classes - defines overall streams architecture.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#ifndef __STREAMS__
#define __STREAMS__

#ifdef	_MSC_VER
// disable some level-4 warnings, use #pragma warning(enable:###) to re-enable
#pragma warning(disable:4100) // warning C4100: unreferenced formal parameter
#pragma warning(disable:4127) // warning C4127: conditional expression is constant
#pragma warning(disable:4189) // warning C4189: local variable is initialized but not referenced
#pragma warning(disable:4201) // warning C4201: nonstandard extension used : nameless struct/union
#pragma warning(disable:4511) // warning C4511: copy constructor could not be generated
#pragma warning(disable:4512) // warning C4512: assignment operator could not be generated
#pragma warning(disable:4514) // warning C4514: unreferenced inline function has been removed
#pragma warning(disable:4710) // warning C4710: 'function' not inlined

#if _MSC_VER>=1100

#define AM_NOVTABLE __declspec(novtable)
#else
#define AM_NOVTABLE
#endif
#else                                    //new line
#define AM_NOVTABLE    //new line
#endif // MSC_VER

// Because of differences between Visual C++ and older Microsoft SDKs,
// you may have defined _DEBUG without defining DEBUG.  This logic
// ensures that both will be set if Visual C++ sets _DEBUG.
#ifdef _DEBUG
#ifndef DEBUG
#define DEBUG
#endif
#endif


#include <windows.h>
#include <windowsx.h>
#include <olectl.h>
#include <ddraw.h>

// Disable warning message for C4201 - use of nameless struct/union
// Otherwise, strmif.h will generate warnings for Win32 debug builds
#pragma warning( disable : 4201 )  

#include <mmsystem.h>

#ifndef NUMELMS
   #define NUMELMS(aa) (sizeof(aa)/sizeof((aa)[0]))
#endif

///////////////////////////////////////////////////////////////////////////
// The following definitions come from the Platform SDK and are required if
// the applicaiton is being compiled with the headers from Visual C++ 6.0.
///////////////////////////////////////////////////////////////////////////
#ifndef InterlockedExchangePointer
	#define InterlockedExchangePointer(Target, Value) \
   (PVOID)InterlockedExchange((PLONG)(Target), (LONG)(Value))
#endif

#ifndef _WAVEFORMATEXTENSIBLE_
#define _WAVEFORMATEXTENSIBLE_
typedef struct {
    WAVEFORMATEX    Format;
    union {
        WORD wValidBitsPerSample;       // bits of precision  //
        WORD wSamplesPerBlock;          // valid if wBitsPerSample==0 //
        WORD wReserved;                 // If neither applies, set to zero. //
    } Samples;
    DWORD           dwChannelMask;      // which channels are //
                                        // present in stream  //
    GUID            SubFormat;
} WAVEFORMATEXTENSIBLE, *PWAVEFORMATEXTENSIBLE;
#endif // !_WAVEFORMATEXTENSIBLE_

#if !defined(WAVE_FORMAT_EXTENSIBLE)
#define  WAVE_FORMAT_EXTENSIBLE                 0xFFFE
#endif // !defined(WAVE_FORMAT_EXTENSIBLE)

#ifndef GetWindowLongPtr
  #define GetWindowLongPtrA   GetWindowLongA
  #define GetWindowLongPtrW   GetWindowLongW
  #ifdef UNICODE
    #define GetWindowLongPtr  GetWindowLongPtrW
  #else
    #define GetWindowLongPtr  GetWindowLongPtrA
  #endif // !UNICODE
#endif // !GetWindowLongPtr

#ifndef SetWindowLongPtr
  #define SetWindowLongPtrA   SetWindowLongA
  #define SetWindowLongPtrW   SetWindowLongW
  #ifdef UNICODE
    #define SetWindowLongPtr  SetWindowLongPtrW
  #else
    #define SetWindowLongPtr  SetWindowLongPtrA
  #endif // !UNICODE
#endif // !SetWindowLongPtr

#ifndef GWLP_WNDPROC
  #define GWLP_WNDPROC        (-4)
#endif
#ifndef GWLP_HINSTANCE
  #define GWLP_HINSTANCE      (-6)
#endif
#ifndef GWLP_HWNDPARENT
  #define GWLP_HWNDPARENT     (-8)
#endif
#ifndef GWLP_USERDATA
  #define GWLP_USERDATA       (-21)
#endif
#ifndef GWLP_ID
  #define GWLP_ID             (-12)
#endif
#ifndef DWLP_MSGRESULT
  #define DWLP_MSGRESULT  0
#endif
#ifndef DWLP_DLGPROC 
  #define DWLP_DLGPROC    DWLP_MSGRESULT + sizeof(LRESULT)
#endif
#ifndef DWLP_USER
  #define DWLP_USER       DWLP_DLGPROC + sizeof(DLGPROC)
#endif
///////////////////////////////////////////////////////////////////////////
// End Platform SDK definitions
///////////////////////////////////////////////////////////////////////////


#pragma warning(disable:4201) // warning C4201: nonstandard extension used : nameless struct/union
#include <strmif.h>     // Generated IDL header file for streams interfaces

#include <reftime.h>    // Helper class for REFERENCE_TIME management
#include <wxdebug.h>    // Debug support for logging and ASSERTs
#include <amvideo.h>    // ActiveMovie video interfaces and definitions
//include amaudio.h explicitly if you need it.  it requires the DirectX SDK.
//#include <amaudio.h>    // ActiveMovie audio interfaces and definitions
#include <wxutil.h>     // General helper classes for threads etc
#include <combase.h>    // Base COM classes to support IUnknown
#include <dllsetup.h>   // Filter registration support functions
#include <measure.h>    // Performance measurement
#include <comlite.h>    // Light weight com function prototypes

#include <cache.h>      // Simple cache container class
#include <wxlist.h>     // Non MFC generic list class
#include <msgthrd.h>	// CMsgThread
#include <mtype.h>      // Helper class for managing media types
#include <fourcc.h>     // conversions between FOURCCs and GUIDs
#include <control.h>    // generated from control.odl
#include <ctlutil.h>    // control interface utility classes
#include <evcode.h>     // event code definitions
#include <amfilter.h>   // Main streams architecture class hierachy
#include <transfrm.h>   // Generic transform filter
#include <transip.h>    // Generic transform-in-place filter
#include <uuids.h>      // declaration of type GUIDs and well-known clsids
#include <source.h>	// Generic source filter
#include <outputq.h>    // Output pin queueing
#include <errors.h>     // HRESULT status and error definitions
#include <renbase.h>    // Base class for writing ActiveX renderers
#include <winutil.h>    // Helps with filters that manage windows
#include <winctrl.h>    // Implements the IVideoWindow interface
#include <videoctl.h>   // Specifically video related classes
#include <refclock.h>	// Base clock class
#include <sysclock.h>	// System clock
#include <pstream.h>    // IPersistStream helper class
#include <vtrans.h>     // Video Transform Filter base class
#include <amextra.h>
#include <cprop.h>      // Base property page class
#include <strmctl.h>    // IAMStreamControl support
#include <edevdefs.h>   // External device control interface defines
#include <audevcod.h>   // audio filter device error event codes

#else
    #ifdef DEBUG
    #pragma message("STREAMS.H included TWICE")
    #endif
#endif // __STREAMS__

*/
 
 
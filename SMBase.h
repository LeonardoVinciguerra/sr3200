//---------------------------------------------------------------------------
//
// Name:        SMBase.h
// Author:      Gabriel Ferri
// Created:     11/10/2010
// Description: SMBase class declaration
//
//---------------------------------------------------------------------------
#pragma once

#include <wx/event.h>
#include "wxDatasette.h"
#include "SRMachine.h"
#include "SmartLog.h"
#include "wxControlPanel.h"
#include "wxMainVideo.h"
#include "SMEnums.h"
#include "wxCameraControl.h"
#include "wxInspectionPanel.h"
#include "AutoSPI.h"

struct CheckStruct
{
	bool cover;
	bool air;
	bool pcb;
	bool frame;
	bool motors_pos;
	float pcb_height;
	int motor_state;
};

class SMBase : public wxEvtHandler
{
	public:

		SMBase() {};
		virtual ~SMBase() {};

		int Init( SRMachine* SRRef, SmartLog* smartLoggerRef, wxDatasette* datasetteRef, wxControlPanel* controlPanelRef, wxMainVideo* mainVideoRef, wxPanel *toolBoxRef, wxBitmapButton* menuBtnRef, wxCameraControl *cameraRef, AutoSPICheck *AutoSPIcheck, AutoSPIProc *AutoSPIprocRef, wxWindow* parentRef );

		// SM functions and variables
		int SelectSM( SMEnum sm, wxPanel *panelRef = NULL );
		void MoveSqueegeesSide( bool operatorSide );
		
		void OnStart();
		void OnStop();
		void OnNext( int data = 0 );
		void OnPrev( int data = 0 );
		void OnPause();

		int MoveCameraToCompensateOffset(bool secondCycle);
		bool doNotSaveZeroPos;
		int LoadBoardCameraCheck();

	private:
		// SM functions and variables
		void SMReset();
		void SMAuxVideoLeftClick( wxMouseEvent& e );
		void SMMainVideoKeyPress( wxKeyEvent& e );

		// SM useful functions
		int SMInitCheck( CheckStruct check );
		void CopyFiducial( int dest, int source );
		void CopyFiducials();
		bool CheckTemplateImage();

		// SPI Check
		void ISite_CreateArray();
		bool ISite_SelectFirst();
		bool ISite_SelectNext();
		bool ISite_SelectPrev();
		bool ISite_IsFirst();
		int ISite_Count();
		int ISite_GetSelected();
		bool iSitesEnabled[NUM_INSPECTION_SITES];

		//TEMP
		bool findTemplate( void* pImage, const wxString& filename, PointF& position, float& score );
		int antiReflects( int fiducialType);
		SMEnum currentSM;
		wxPanel *currentPanel;



		int currentState;
		bool isMainVideoClickEnable;
		bool isAuxVideoClickEnable;
		bool fiducialAutoFounded;
		bool fiducialSearchTerminated;
		int xClicked, yClicked;
		int expectedX, expectedY;
		int currentFiducial;
		int currentVerifyPoint;
		int currentPinsPoint;
		PointD fidPosition[NUM_FIDUCIALS];
		double boardRot, frameRot;
		PointD boardTra;
		PointD camPos;
		double offsetX, offsetY;
		double offsetR1X, offsetR1Y;
		double offsetR2X, offsetR2Y;
		float templateScore;
		int input;
		float centerX, centerY;
		float circleR;
		float rectangleX, rectangleY;
		int retVal;
		int pasteCounter;
		CheckStruct initCheck;
		int currentSpeed;
		int verifyCounter;
		PointI expectedPos;
		PointI startPos;
		PointF center;
		int cleanCounter;
		wxString fullpath;
		bool SiteOK;

		// SMAlignment
		int SMAlignmentInitialize();
		int SMAlignmentFinalize();
		void SMAlignmentReset();
		int SMAlignment( int nextState );
		void SMAlignmentNext();
		void SMAlignmentPrev();
		void SMAlignmentMainVideoLeftClick( wxMouseEvent& e );

		int isTableSubMovementOk;
		int alignmentType; // see wxAlignmentTypeDialogDialogRetCode
		PointD table2PosErr;
		bool isExistingProduction;	// serve per aggiornare le produzioni esistenti la prima volta
									// che si esegue l'allineamento con versioni superiori alla 2.00

		// SMPrinting
		int SMPrintingInitialize();
		int SMPrintingFinalize();
		void SMPrintingReset();
		int SMPrinting( int nextState );
		void SMPrintingNext( int data);
		void SMPrintingPrev();
		void SMPrintingMainVideoLeftClick( wxMouseEvent& e );

		int verifyAutoFlag;

		// SMVerify
		int SMVerifyInitialize();
		int SMVerifyFinalize();
		void SMVerifyReset();
		int SMVerify( int nextState );
		void SMVerifyNext();
		void SMVerifyPrev();

		// SMInspection
		int SMInspectionInitialize();
		int SMInspectionFinalize();
		void SMInspectionReset();
		int SMInspection( int nextState );
		void SMInspectionNext( int data );
		void SMInspectionPrev( int data );
		void SMInspectionMainVideoLeftClick( wxMouseEvent& e );
		void SMInspectionMainVideoLeftClickUp( wxMouseEvent& e );
		void SMInspectionMainVideoMove( wxMouseEvent& e );

		cv::Mat Frame_to_Mat;
		cv::Mat FrameHighExposure;

		// SMPasteConditioning
		int SMPasteConditioningInitialize();
		int SMPasteConditioningFinalize();
		void SMPasteConditioningReset();
		int SMPasteConditioning( int nextState );

		// SMPins
		int SMPinsInitialize();
		int SMPinsFinalize();
		void SMPinsReset();
		int SMPins( int nextState );
		void SMPinsNext();
		void SMPinsPrev();

		// SMPlateMovement
		int SMPlateMovementInitialize();
		int SMPlateMovementFinalize();
		void SMPlateMovementReset();
		int SMPlateMovement( int nextState );
		void SMPlateMovementNext();

		// SMCameraFocus
		int SMCameraFocusInitialize();
		int SMCameraFocusFinalize();
		void SMCameraFocusReset();
		int SMCameraFocus( int nextState );
		void SMCameraFocusNext();

		// SMCameraScale
		int SMCameraScaleInitialize();
		int SMCameraScaleFinalize();
		void SMCameraScaleReset();
		int SMCameraScale( int nextState );
		void SMCameraScaleNext();
		void SMCameraScalePrev();
		void SMCameraScaleMainVideoLeftClick( wxMouseEvent& e );

		int start_x, start_y;
		double scale_x, scale_y;

		// SMCameraOffset
		int SMCameraOffsetInitialize();
		int SMCameraOffsetFinalize();
		void SMCameraOffsetReset();
		int SMCameraOffset( int nextState );
		void SMCameraOffsetNext();
		void SMCameraOffsetPrev();
		void SMCameraOffsetMainVideoLeftClick( wxMouseEvent& e );

		int currentPoint;
		float rowStartX, rowStartY;
		PointF offsetMapDown[NUM_OFFSET_POINTS];
		PointF offsetMapUp[NUM_OFFSET_POINTS];
		char offsetMapState[NUM_OFFSET_POINTS];
		bool isSearching;
		bool errorShown;

		// SMHardwareTest
		int SMHardwareTestInitialize();
		int SMHardwareTestFinalize();

		// SMVision
		int SMVisionInitialize();
		int SMVisionFinalize();
		void SMVisionReset();
		int SMVision( int nextState );
		void SMVisionNext();
		void SMVisionPrev();
		void SMVisionMainVideoLeftClick( wxMouseEvent& e );

		// SMDemomode
		int SMDemomodeInitialize();
		int SMDemomodeFinalize();
		void SMDemomodeReset();
		int SMDemomode( int nextState );

		// SMConveyorEdge
		int SMConveyorEdgeInitialize();
		int SMConveyorEdgeFinalize();
		void SMConveyorEdgeReset();
		int SMConveyorEdge( int nextState );
		void SMConveyorEdgeNext();

		//SMviewRecords
		int SMViewRecordsFinalize();
		int SMViewRecordsInitialize();
		int SMViewRecordsNext( int data );

		// SMCameraZero
		int SMCameraZeroInitialize();
		int SMCameraZeroFinalize();
		void SMCameraZeroReset();
		int SMCameraZero( int nextState );
		void SMCameraZeroNext();
		void SMCameraZeroPrev();
		void SMCameraZeroMainVideoLeftClick( wxMouseEvent& e );




		int cycleCounter;

		SRMachine *SR;
		SmartLog *smartLogger;
		wxDatasette *datasette;
		wxControlPanel *controlPanel;
		wxMainVideo *mainVideo;
		wxPanel *toolBox;
		wxBitmapButton* menuBtn;
		wxCameraControl *camera;
		wxWindow *parent;

		AutoSPIProc *AutoSPIproc;
		AutoSPICheck *AutoSPIcheck;


};

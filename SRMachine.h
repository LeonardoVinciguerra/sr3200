//---------------------------------------------------------------------------
//
// Name:        SRMachine.h
// Author:      Gabriel Ferri
// Created:     15/04/2008
// Description: SRMachine class declaration
//
//---------------------------------------------------------------------------
#pragma once

#include <wx/file.h>
#include <wx/progdlg.h>
#include <wx/timer.h>
#include "SRDatabase.h"
#include "SmartLog.h"
#include "GlobalEnum.h"
#include "wxMySerialPort.h"
#include "wxCommInterface.h"
#include "MotorModule.h"
#include "StepperModule.h"
#include "BrushlessModule.h"
#include "BrushModule.h"
#include "Motor.h"
#include "Errors.h"


enum ResetMotorEnum
{
	MODE_INITIAL_POSITION,
	MODE_START_POSITION,
	MODE_ZERO_POSITION,
	MODE_GO_HOME,
	MODE_SET_HOME,
	MODE_STARTPRINTING_POSITION,
	MODE_LOAD_POSITION
};

enum CheckMotorEnum
{
	CHECK_SECURITY_POSITION,
	CHECK_LOAD_POSITION
};

enum BoardLoadingCheck{
	CHECK_DISABLED,
	CHECK_ENABLED

};


class SRMachine : public wxEvtHandler
{
public:
	SRMachine( SRDatabase *DBRef, SmartLog* smartLoggerRef, wxWindow* parentRef );
	~SRMachine();

	static const long ID_SM_TIMER;
	static const long ID_CAMERA_WAIT;

	// General functions
	void SetMachineState( bool state ) { machineState = state; };
	bool GetMachineState() { return machineState; };

	int OriginSearch();
	bool CheckOrigin();
	void ResetOrigin() { originFlag = false; };

	int OpenSerialCom();
	int CloseSerialCom();
	bool isSerialComOpen();

	void InitMotors();
	int ResetMotors( int mode );
	int EnableAllMotors();
	int DisableAllMotors();
	int StopAllMotors();
	int ActivateAllMotorsPID();
	int CheckMotorsPos( int mode = CHECK_SECURITY_POSITION );
	void GetOffset( float xcoord, float ycoord, double &xoff, double &yoff );
	int ActivateLimits( bool state );
	void ActivateSWLimits( bool state ) { limitsOn = state; };
	bool GetLimitsState() { return limitsOn; };
	void ActivateSafeMode( bool state ) { safeMode = state; };
	bool GetSafeModeState() { return safeMode; };
	void ErrorManagement();
	int setOutputHardwareReduction();
	int FinePlateZSearch();

	int SetCamera( CameraEnum state );
	int SetAlarmLight( AlarmLightEnum state );
	int SetBuzzerState( bool state = false );
	int SetCameraLight( CameraLightEnum mode );

	int UpdateDriver( int driverId, wxFile *inFile );

	// I/Os
	int SetOutput( int outputId, int val );
	int SetOutputReduction( int outputId, int mode );
	int SetPulseModeAndTime( int outputId, int mode, int msec );
	int GetInput( int inputId );
	int GetAllInput( int driverId, int &in0, int &in1, int &in2 );
	int GetAllInput( int driverId, int &in0, int &in1, int &in2, int &in3, int &in4, int &in5 );
	void CheckCover( bool state ) { checkCover = state; };
	int GetMotorStatus( int driverId, int &status );
	int GetEncoderStatus( int driverId, int &status );

	wxTimer *ioTimer;
	bool isTimerBusy;
	void OnTimer( wxTimerEvent& event );
	void OnSwitchLightTimer(wxTimerEvent& event);

	// Errors
	void ResetErrors();
	wxString GetErrors();

	// Immediate Stop
	void SetStop( bool state );
	bool GetStop() { return immediateStop; };

	// Loader continous printing interruption
	void SetLoaderStop( bool state );
	bool GetLoaderStop() { return loaderStop; };

	// Squeegees public functions
	void SetSqueegeesCycle( bool state ) { firstSqueegeesCycle = state; };
	bool GetSqueegeesCycle() { return firstSqueegeesCycle; };

	// Table public functions
	int RotateTable( double deg, int limit = LIMIT_ON );
	int MoveXYTable( double x, double y, int limit = LIMIT_ON );
	int ResetTable();
	int WaitTable();
	int RotateTableAndWait( double deg, int limit = LIMIT_ON );
	int MoveXYTableAndWait( double x, double y, int limit = LIMIT_ON );
	void GetTablePosition( double &x, double &y, double &theta );
	int RotateTableCheck( double deg );
	int MoveXYTableCheck( double x, double y );

	// Camera public functions
	int CheckCamera( double x, double y, int mode );
	int MoveCamera( double x, double y, int mode = REL_MOVE, int limit = LIMIT_ON );
	int WaitCamera();
	int MoveCameraAndWait( double x, double y, int mode = REL_MOVE, int limit = LIMIT_ON );
	int GetCameraPosition( double &x, double &y );
	void SetCounter( int val ) { cameraCounter = val; };
	int GetCounter() { return cameraCounter; };

	// Board loading/unloading functions
	int LoadBoard( int mode = CHECK_ENABLED);
	int UnloadBoard( int mode = CHECK_ENABLED );
	int convPusherEnabled( bool state );

	int startBoardLoading(); //Used for camera recognition
	int finishBoardLoading(); //Used for camera recognition

	// Loader public functions
	int GetRackPos()  { return actualRackPos; };
	void SetRackPos( int val ) { actualRackPos = val; };
	int GetLastPrintedRackPos()  { return lastPrintedRackPos; };
	void SetLastPrintedRackPos( int val ) { lastPrintedRackPos = val; };
	int LoaderMove( int pos );
	int WaitMotorAndCheckSensor(int inputID, Motor* motor);

	// Stencil cleaning cycle
	int CleaningCycle(bool feedPaper = true);


	//
	int isFrameUnlocked;			// se 1, indica telaio sbloccato
	int isSqueegeesFrontOn;			// se 1, indica la racla 1 alta
	int isSqueegeesRearOn;			// se 1, indica la racla 2 alta
	int isSemaphoreRed;				// se 1, indica luce rossa del semaforo accesa
	int isSemaphoreGreen;			// se 1, indica luce verde del semaforo accesa
	int isSemaphoreYellow;			// se 1, indica luce gialla del semaforo accesa
	int isBuzzerOn;					// se 1, indica la sirena attiva
	int isLedUpOn;					// se 1, indica led alto della camera acceso
	int isLedDownOn;				// se 1, indica led basso della camera acceso
	int isBoardLocked;				// se 1, indica blocco scheda attivo
	int isLoaderPistonOn;			// se 1, indica il pistone del loader attivo
	int isConveyorPistonOn;			// se 1, indica il pistone del convogliatore di sinistra attivo
	int isCameraPistonOn;			// se 1, indica il pistone del blocco camera attivo
	int isCleaningLockOn;			// se 1, indica il pistone di blocco sistema di pulizia attivo
	int isCleaningVacuumOn;			// se 1, indica il vuoto del sistema di pulizia attivo
	int isCleaningActive;			// se 1, indica il pistone di sollevamento attivo
	int isReckinLoadPosition;		// se 1, indica il reck in posizione di carico

	int isBoardLoaded;				// se 1, indica che c'e' una scheda caricata in macchina

	int isInputEngaged;				// se 1, indica che e' stato attivato il sensore d'ingresso e deve ancora essere liberato

	int verifyEvery;

	int cleanEvery;

	int suggestCorrections;

	int cameraSavedSpeed;

	int pasteConditionIters;

	SRDatabase* DB;

	Motor Table1Motor;
	Motor Table2Motor;
	Motor Table3Motor;
	Motor CamXMotor;
	Motor CamYMotor;
	Motor PlateMotor;
	Motor SqueegeesMotor;
	Motor LConvWidthMotor;
	Motor LConvFeedMotor;
	Motor LConvPushMotor;
	Motor CConvWidthMotor;
	Motor CConvFeedMotor;
	Motor LoaderMotor;
	Motor CleanerMotor;
	MotorModule* AllStepperMotors;
	MotorModule* AllBrushlessMotors;

private:
	wxWindow* parent;
	SmartLog* smartLogger;

	// motors serial ports and interfaces
	wxMySerialPort* serialPortStepper;
	wxMySerialPort* serialPortBrushless;
	wxCommInterface* commIntStepper;
	wxCommInterface* commIntBrushless;

	double ActRotTable;				// Table actual rotation
	double ActPosXTable;			// Table actual X position
	double ActPosYTable;			// Table actual Y position

	bool limitsOn;					// Indica la presenza o meno del check dei limiti
	bool firstSqueegeesCycle;		// If TRUE squeegees are on the operator side
	bool originFlag;				// TRUE if origins search has been succesfully executed and everything is ok
	bool machineState;				// TRUE if machine motors are enabled
	int errorCode;					// contains the error codes bits
	bool immediateStop;				// If TRUE current movements are stopped
	bool backlashRecover;			// If TRUE linear motors negative movements use backlash recovery
	double backlashMm;				// BackLash value in mm
	bool safeMode;					// Indica se la macchina va attivata anche se uno o più moduli non rispondono
	bool sideButtonPressed;
	bool checkCover;
	int cameraCounter;
	bool loaderStop;				// If TRUE, loader cycle is interrupted at the end of current one
	int actualRackPos;
	int lastPrintedRackPos;

	//aggiunto
	bool sitesSPIScaned;

	// private functions
	int SearchPlateOrigin();
	int SearchPlateOrigin_Wait( wxProgressDialog *progressDialog, int value );
	int SearchSqueegeesOrigin();
	int SearchSqueegeesOrigin_Wait( wxProgressDialog *progressDialog, int value );
	int SearchTableOrigin_1();
	int SearchTableOrigin_2();
	int SearchTableOrigin_3();
	int SearchTableOrigin_Wait( wxProgressDialog *progressDialog, int value );
	int SearchCameraXOrigin();
	int SearchCameraXOrigin_Wait( wxProgressDialog *progressDialog, int value );
	int SearchCameraYOrigin();
	int SearchCameraYOrigin_Wait( wxProgressDialog *progressDialog, int value );
	int SearchLConveyorOrigin();
	int SearchLConveyorOrigin_Wait( wxProgressDialog *progressDialog, int value );
	int SearchLConveyorPushOrigin();
	int SearchLConveyorPushOrigin_Wait( wxProgressDialog *progressDialog, int value );
	int SearchCConveyorOrigin();
	int SearchCConveyorOrigin_Wait( wxProgressDialog *progressDialog, int value );
	int SearchLoaderOrigin();
	int SearchLoaderOrigin_Wait( wxProgressDialog *progressDialog, int value );


	float OffsetXMap( int x, int y ) { return DB->OffsetPointsS[x + y * DB->MachineParamsS.OffsetPointsNumX].X; };
	float OffsetYMap( int x, int y ) { return DB->OffsetPointsS[x + y * DB->MachineParamsS.OffsetPointsNumX].Y; };
};


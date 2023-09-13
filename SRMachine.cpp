//-------------------------------------------f--------------------------------
//
// Name:        SRMachine.cpp
// Author:      Gabriel Ferri
// Created:     15/04/2008
// Description: SRMachine class implementation
//
//---------------------------------------------------------------------------
#include <wx/msgdlg.h>
#include "SRMachine.h"
#include "GlobalUtils.h"
#include "Errors.h"
#include "Messages.h"

#define PLATESCREW_STEP			12.0
#define LINEAR_STEP				0.0035
#define CONVSCREW_STEP			6.0
#define LOADERSCREW_STEP		12.0

#define WAIT_RETRY				3

const long SRMachine::ID_SM_TIMER = wxNewId();
const long SRMachine::ID_CAMERA_WAIT = wxNewId();

SRMachine::SRMachine( SRDatabase *DBRef, SmartLog* smartLoggerRef, wxWindow* parentRef )
: wxEvtHandler()
{
	DB = DBRef;
	smartLogger = smartLoggerRef;
	parent = parentRef;

	isFrameUnlocked		= false;
	isSqueegeesFrontOn	= false;
	isSqueegeesRearOn	= false;
	isSemaphoreRed		= false;
	isSemaphoreGreen	= false;
	isSemaphoreYellow	= false;
	isBuzzerOn			= false;
	isLedUpOn			= false;
	isLedDownOn			= false;
	isBoardLocked		= false;
	isLoaderPistonOn	= false;
	isConveyorPistonOn	= false;
	isCameraPistonOn	= false;
	isBoardLoaded		= false;
	isInputEngaged		= false;
	isCleaningLockOn	= false;
	isCleaningVacuumOn	= false;
	isCleaningActive	= false;
	isReckinLoadPosition= false;


	// init serial ports and interfaces
	serialPortStepper = new wxMySerialPort();
	serialPortStepper->SetTimeout( COMTIMEOUT );
	commIntStepper = new wxCommInterface( serialPortStepper, PROTOCOL_TWS );
	commIntStepper->Run();

	serialPortBrushless = new wxMySerialPort();
	serialPortBrushless->SetTimeout( COMTIMEOUT );
	commIntBrushless = new wxCommInterface( serialPortBrushless, PROTOCOL_TWS );
	commIntBrushless->Run();

	ActRotTable = 0;
	ActPosXTable = 0;
	ActPosYTable = 0;
	Table1Motor.ResetPosition();
	Table2Motor.ResetPosition();
	Table3Motor.ResetPosition();
	CamXMotor.ResetPosition();
	CamYMotor.ResetPosition();
	PlateMotor.ResetPosition();
	SqueegeesMotor.ResetPosition();
	LConvWidthMotor.ResetPosition();
	LConvFeedMotor.ResetPosition();
	CConvWidthMotor.ResetPosition();
	CConvFeedMotor.ResetPosition();
	LoaderMotor.ResetPosition();

	limitsOn = LIMIT_OFF;
	firstSqueegeesCycle = false;
	originFlag = false;
	machineState = false;
	errorCode = 0;
	immediateStop = false;
	backlashRecover = false;
	backlashMm = 1.0;
	safeMode = false;
	sideButtonPressed = false;
	checkCover = false;
	loaderStop = false;
	cameraCounter = 0;
	actualRackPos = 0;
	lastPrintedRackPos = 0;
	verifyEvery = 1;
	cleanEvery = 1;
	pasteConditionIters = 3;

	//aggiunto
	sitesSPIScaned = false;

	ioTimer = new wxTimer( this, ID_SM_TIMER );
	Connect( ID_SM_TIMER, wxEVT_TIMER, wxTimerEventHandler( SRMachine::OnTimer ), NULL, this );

	isTimerBusy = false;
	ioTimer->Start( INPUTTIMER );



	//Connect(smartLoggerRef->Get, DISABLE_BUZZER_ID, SRMachine(SRMachine::SetBuzzerState), NULL, this );
}

SRMachine::~SRMachine()
{
	commIntStepper->Delete();
	commIntBrushless->Delete();

	MyDELETE( serialPortStepper );
	MyDELETE( serialPortBrushless );

	MyDELETE( AllStepperMotors );
	MyDELETE( AllBrushlessMotors );

	MyDELETE( ioTimer );
}

//----------------------------------------------------------------------------------
// OpenSerialCom
// 
//----------------------------------------------------------------------------------
int SRMachine::OpenSerialCom()
{
	MACHINE_CONFIG( MACHINE_ENABLE )
		// Stepper Modules
		if( !serialPortStepper->IsOpen() )
		{
			if( serialPortStepper->MyOpen( DB->SerialParamsS[DRIVER_STEPPER_ID].SerialPort, (wxBaud)DB->SerialParamsS[DRIVER_STEPPER_ID].SerialSpeed, true ) == wxSERIAL_ERROR )
			{
				smartLogger->Write( MSG_SPORTOPENERRORSTEPPER, MSG_ERROR );
				wxMessageBox( MSG_SPORTOPENERRORSTEPPER, MACHINE_NAME, wxOK | wxICON_ERROR, parent );
	
				errorCode |= ERR_SERIALPORT;
				return SR_ERROR;
			}
	
			smartLogger->Write( MSG_SPORTOPENOKSTEPPER );
		}
	
		// Brushless Modules
		if( !serialPortBrushless->IsOpen() )
		{
			if( serialPortBrushless->MyOpen( DB->SerialParamsS[DRIVER_BRUSHLESS_ID].SerialPort, (wxBaud)DB->SerialParamsS[DRIVER_BRUSHLESS_ID].SerialSpeed, true ) == wxSERIAL_ERROR )
			{
				smartLogger->Write( MSG_SPORTOPENERRORBRUSHLESS, MSG_ERROR );
				wxMessageBox( MSG_SPORTOPENERRORBRUSHLESS, MACHINE_NAME, wxOK | wxICON_ERROR, parent );
	
				errorCode |= ERR_SERIALPORT;
				return SR_ERROR;
			}
	
			smartLogger->Write( MSG_SPORTOPENOKBRUSHLESS );
		}
	MACHINE_CONFIG_END

	return SR_OK;
}

//----------------------------------------------------------------------------------
// CloseSerialCom
// 
//----------------------------------------------------------------------------------
int SRMachine::CloseSerialCom()
{
	MACHINE_CONFIG( MACHINE_ENABLE )
		if( serialPortStepper->MyClose() == wxSERIAL_ERROR )
		{
			smartLogger->Write( MSG_SPORTCLOSEERRORSTEPPER, MSG_ERROR );
		}

		if( serialPortBrushless->MyClose() == wxSERIAL_ERROR )
		{
			smartLogger->Write( MSG_SPORTCLOSEERRORBRUSHLESS, MSG_ERROR );
		}
	MACHINE_CONFIG_END

	return SR_OK;
}

//----------------------------------------------------------------------------------
// isSerialComOpen
// 
//----------------------------------------------------------------------------------
bool SRMachine::isSerialComOpen()
{
	bool isOpen = true;

	MACHINE_CONFIG( MACHINE_ENABLE )
		if( !serialPortStepper->IsOpen() )
			isOpen = false;

		if( !serialPortBrushless->IsOpen() )
			isOpen = false;
	MACHINE_CONFIG_END

	return isOpen;
}

//----------------------------------------------------------------------------------
// SetStop
// 
//----------------------------------------------------------------------------------
void SRMachine::SetStop( bool state ) 
{ 
	immediateStop = state;
	
	if( state )
		errorCode |= ERR_IMMEDIATESTOP; 
};

//----------------------------------------------------------------------------------
// SetLoaderStop
//
//----------------------------------------------------------------------------------
void SRMachine::SetLoaderStop( bool state )
{
	loaderStop = state;
};

//----------------------------------------------------------------------------------
// InitMotors
// 
//----------------------------------------------------------------------------------
void SRMachine::InitMotors()
{
	MotorStruct motorData;

	motorData.commIntStepper	= commIntStepper;
	motorData.commIntBrushless	= commIntBrushless;
	motorData.errorCode		= &errorCode;
	motorData.limitsOn		= &limitsOn;
	motorData.immediateStop	= &immediateStop;

	// Table1
	motorData.Address		= &DB->MotorParamsS[MOTOR_TABLE1_ID].Address;
	motorData.MinCurrent	= &DB->MotorParamsS[MOTOR_TABLE1_ID].MinCurrent;
	motorData.AccCurrent	= &DB->MotorParamsS[MOTOR_TABLE1_ID].AccCurrent;
	motorData.MaxCurrent	= &DB->MotorParamsS[MOTOR_TABLE1_ID].MaxCurrent;
	motorData.Microstepping	= &DB->MotorParamsS[MOTOR_TABLE1_ID].Microstepping;
	motorData.Pulley		= &DB->MotorParamsS[MOTOR_TABLE1_ID].Pulley;
	motorData.Reduction		= &DB->MotorParamsS[MOTOR_TABLE1_ID].Reduction;
	motorData.Driver		= &DB->MotorParamsS[MOTOR_TABLE1_ID].Driver;
	motorData.Current		= &DB->MotorParamsS[MOTOR_TABLE1_ID].Current;
	motorData.KP_speed		= &DB->MotorParamsS[MOTOR_TABLE1_ID].KP_speed;
	motorData.KI_speed		= &DB->MotorParamsS[MOTOR_TABLE1_ID].KI_speed;
	motorData.KP_pos		= &DB->MotorParamsS[MOTOR_TABLE1_ID].KP_pos;
	motorData.LineEnc		= &DB->MotorParamsS[MOTOR_TABLE1_ID].LineEnc;
	motorData.PulsesToMm	= &DB->MotorParamsS[MOTOR_TABLE1_ID].PulsesToMm;
	motorData.PPR			= &DB->MotorParamsS[MOTOR_TABLE1_ID].PPR;
	motorData.Poles			= &DB->MotorParamsS[MOTOR_TABLE1_ID].Poles;
	motorData.Jerk			= &DB->MotorParamsS[MOTOR_TABLE1_ID].Jerk;
	motorData.KA			= &DB->MotorParamsS[MOTOR_TABLE1_ID].KA;
	motorData.KS			= &DB->MotorParamsS[MOTOR_TABLE1_ID].KS;
	motorData.KC			= &DB->MotorParamsS[MOTOR_TABLE1_ID].KC;
	motorData.HomeFast		= &DB->MotorParamsS[MOTOR_TABLE1_ID].HomeFast;
	motorData.HomeSlow		= &DB->MotorParamsS[MOTOR_TABLE1_ID].HomeSlow;
	motorData.Profile		= &DB->MotorParamsS[MOTOR_TABLE1_ID].Profile;
	motorData.EndMovementDelta	= &DB->MotorParamsS[MOTOR_TABLE1_ID].EndMovementDelta;
	motorData.SpykeDelta	= &DB->MotorParamsS[MOTOR_TABLE1_ID].SpykeDelta;
	motorData.RedCurrent	= &DB->MotorParamsS[MOTOR_TABLE1_ID].RedCurrent;
	motorData.Speed			= DB->SpeedTableS[SPEED_TABLE_ID].Speed;
	motorData.Acc			= DB->SpeedTableS[SPEED_TABLE_ID].Acc;
	motorData.Dec			= DB->SpeedTableS[SPEED_TABLE_ID].Dec;
	motorData.SpeedIndex	= &DB->MachineParamsS.TableSpeed;
	motorData.MinLimit		= &DB->LimitsS[MOTOR_TABLE1_ID].MinLimit;
	motorData.MaxLimit		= &DB->LimitsS[MOTOR_TABLE1_ID].MaxLimit;
	motorData.ScrewStep		= 0.0;
	motorData.LinearStep	= LINEAR_STEP;
	motorData.Direction		= &DB->MotorParamsS[MOTOR_TABLE1_ID].Direction;
	Table1Motor.Init( motorData );

	// Table2
	motorData.Address		= &DB->MotorParamsS[MOTOR_TABLE2_ID].Address;
	motorData.MinCurrent	= &DB->MotorParamsS[MOTOR_TABLE2_ID].MinCurrent;
	motorData.AccCurrent	= &DB->MotorParamsS[MOTOR_TABLE2_ID].AccCurrent;
	motorData.MaxCurrent	= &DB->MotorParamsS[MOTOR_TABLE2_ID].MaxCurrent;
	motorData.Microstepping	= &DB->MotorParamsS[MOTOR_TABLE2_ID].Microstepping;
	motorData.Pulley		= &DB->MotorParamsS[MOTOR_TABLE2_ID].Pulley;
	motorData.Reduction		= &DB->MotorParamsS[MOTOR_TABLE2_ID].Reduction;
	motorData.Driver		= &DB->MotorParamsS[MOTOR_TABLE2_ID].Driver;
	motorData.Current		= &DB->MotorParamsS[MOTOR_TABLE2_ID].Current;
	motorData.KP_speed		= &DB->MotorParamsS[MOTOR_TABLE2_ID].KP_speed;
	motorData.KI_speed		= &DB->MotorParamsS[MOTOR_TABLE2_ID].KI_speed;
	motorData.KP_pos		= &DB->MotorParamsS[MOTOR_TABLE2_ID].KP_pos;
	motorData.LineEnc		= &DB->MotorParamsS[MOTOR_TABLE2_ID].LineEnc;
	motorData.PulsesToMm	= &DB->MotorParamsS[MOTOR_TABLE2_ID].PulsesToMm;
	motorData.PPR			= &DB->MotorParamsS[MOTOR_TABLE2_ID].PPR;
	motorData.Poles			= &DB->MotorParamsS[MOTOR_TABLE2_ID].Poles;
	motorData.Jerk			= &DB->MotorParamsS[MOTOR_TABLE2_ID].Jerk;
	motorData.KA			= &DB->MotorParamsS[MOTOR_TABLE2_ID].KA;
	motorData.KS			= &DB->MotorParamsS[MOTOR_TABLE2_ID].KS;
	motorData.KC			= &DB->MotorParamsS[MOTOR_TABLE2_ID].KC;
	motorData.HomeFast		= &DB->MotorParamsS[MOTOR_TABLE2_ID].HomeFast;
	motorData.HomeSlow		= &DB->MotorParamsS[MOTOR_TABLE2_ID].HomeSlow;
	motorData.Profile		= &DB->MotorParamsS[MOTOR_TABLE2_ID].Profile;
	motorData.EndMovementDelta	= &DB->MotorParamsS[MOTOR_TABLE2_ID].EndMovementDelta;
	motorData.SpykeDelta	= &DB->MotorParamsS[MOTOR_TABLE2_ID].SpykeDelta;
	motorData.RedCurrent	= &DB->MotorParamsS[MOTOR_TABLE2_ID].RedCurrent;
	motorData.Speed			= DB->SpeedTableS[SPEED_TABLE_ID].Speed;
	motorData.Acc			= DB->SpeedTableS[SPEED_TABLE_ID].Acc;
	motorData.Dec			= DB->SpeedTableS[SPEED_TABLE_ID].Dec;
	motorData.SpeedIndex	= &DB->MachineParamsS.TableSpeed;
	motorData.MinLimit		= &DB->LimitsS[MOTOR_TABLE2_ID].MinLimit;
	motorData.MaxLimit		= &DB->LimitsS[MOTOR_TABLE2_ID].MaxLimit;
	motorData.ScrewStep		= 0.0;
	motorData.LinearStep	= LINEAR_STEP;
	motorData.Direction		= &DB->MotorParamsS[MOTOR_TABLE2_ID].Direction;
	Table2Motor.Init( motorData );

	// Table3
	motorData.Address		= &DB->MotorParamsS[MOTOR_TABLE3_ID].Address;
	motorData.MinCurrent	= &DB->MotorParamsS[MOTOR_TABLE3_ID].MinCurrent;
	motorData.AccCurrent	= &DB->MotorParamsS[MOTOR_TABLE3_ID].AccCurrent;
	motorData.MaxCurrent	= &DB->MotorParamsS[MOTOR_TABLE3_ID].MaxCurrent;
	motorData.Microstepping	= &DB->MotorParamsS[MOTOR_TABLE3_ID].Microstepping;
	motorData.Pulley		= &DB->MotorParamsS[MOTOR_TABLE3_ID].Pulley;
	motorData.Reduction		= &DB->MotorParamsS[MOTOR_TABLE3_ID].Reduction;
	motorData.Driver		= &DB->MotorParamsS[MOTOR_TABLE3_ID].Driver;
	motorData.Current		= &DB->MotorParamsS[MOTOR_TABLE3_ID].Current;
	motorData.KP_speed		= &DB->MotorParamsS[MOTOR_TABLE3_ID].KP_speed;
	motorData.KI_speed		= &DB->MotorParamsS[MOTOR_TABLE3_ID].KI_speed;
	motorData.KP_pos		= &DB->MotorParamsS[MOTOR_TABLE3_ID].KP_pos;
	motorData.LineEnc		= &DB->MotorParamsS[MOTOR_TABLE3_ID].LineEnc;
	motorData.PulsesToMm	= &DB->MotorParamsS[MOTOR_TABLE3_ID].PulsesToMm;
	motorData.PPR			= &DB->MotorParamsS[MOTOR_TABLE3_ID].PPR;
	motorData.Poles			= &DB->MotorParamsS[MOTOR_TABLE3_ID].Poles;
	motorData.Jerk			= &DB->MotorParamsS[MOTOR_TABLE3_ID].Jerk;
	motorData.KA			= &DB->MotorParamsS[MOTOR_TABLE3_ID].KA;
	motorData.KS			= &DB->MotorParamsS[MOTOR_TABLE3_ID].KS;
	motorData.KC			= &DB->MotorParamsS[MOTOR_TABLE3_ID].KC;
	motorData.HomeFast		= &DB->MotorParamsS[MOTOR_TABLE3_ID].HomeFast;
	motorData.HomeSlow		= &DB->MotorParamsS[MOTOR_TABLE3_ID].HomeSlow;
	motorData.Profile		= &DB->MotorParamsS[MOTOR_TABLE3_ID].Profile;
	motorData.EndMovementDelta	= &DB->MotorParamsS[MOTOR_TABLE3_ID].EndMovementDelta;
	motorData.SpykeDelta	= &DB->MotorParamsS[MOTOR_TABLE3_ID].SpykeDelta;
	motorData.RedCurrent	= &DB->MotorParamsS[MOTOR_TABLE3_ID].RedCurrent;
	motorData.Speed			= DB->SpeedTableS[SPEED_TABLE_ID].Speed;
	motorData.Acc			= DB->SpeedTableS[SPEED_TABLE_ID].Acc;
	motorData.Dec			= DB->SpeedTableS[SPEED_TABLE_ID].Dec;
	motorData.SpeedIndex	= &DB->MachineParamsS.TableSpeed;
	motorData.MinLimit		= &DB->LimitsS[MOTOR_TABLE3_ID].MinLimit;
	motorData.MaxLimit		= &DB->LimitsS[MOTOR_TABLE3_ID].MaxLimit;
	motorData.ScrewStep		= 0.0;
	motorData.LinearStep	= LINEAR_STEP;
	motorData.Direction		= &DB->MotorParamsS[MOTOR_TABLE3_ID].Direction;
	Table3Motor.Init( motorData );

	// Plate
	motorData.Address		= &DB->MotorParamsS[MOTOR_PLATE_ID].Address;
	motorData.MinCurrent	= &DB->MotorParamsS[MOTOR_PLATE_ID].MinCurrent;
	motorData.AccCurrent	= &DB->MotorParamsS[MOTOR_PLATE_ID].AccCurrent;
	motorData.MaxCurrent	= &DB->MotorParamsS[MOTOR_PLATE_ID].MaxCurrent;
	motorData.Microstepping	= &DB->MotorParamsS[MOTOR_PLATE_ID].Microstepping;
	motorData.Pulley		= &DB->MotorParamsS[MOTOR_PLATE_ID].Pulley;
	motorData.Reduction		= &DB->MotorParamsS[MOTOR_PLATE_ID].Reduction;
	motorData.Driver		= &DB->MotorParamsS[MOTOR_PLATE_ID].Driver;
	motorData.Current		= &DB->MotorParamsS[MOTOR_PLATE_ID].Current;
	motorData.KP_speed		= &DB->MotorParamsS[MOTOR_PLATE_ID].KP_speed;
	motorData.KI_speed		= &DB->MotorParamsS[MOTOR_PLATE_ID].KI_speed;
	motorData.KP_pos		= &DB->MotorParamsS[MOTOR_PLATE_ID].KP_pos;
	motorData.LineEnc		= &DB->MotorParamsS[MOTOR_PLATE_ID].LineEnc;
	motorData.PulsesToMm	= &DB->MotorParamsS[MOTOR_PLATE_ID].PulsesToMm;
	motorData.PPR			= &DB->MotorParamsS[MOTOR_PLATE_ID].PPR;
	motorData.Poles			= &DB->MotorParamsS[MOTOR_PLATE_ID].Poles;
	motorData.Jerk			= &DB->MotorParamsS[MOTOR_PLATE_ID].Jerk;
	motorData.KA			= &DB->MotorParamsS[MOTOR_PLATE_ID].KA;
	motorData.KS			= &DB->MotorParamsS[MOTOR_PLATE_ID].KS;
	motorData.KC			= &DB->MotorParamsS[MOTOR_PLATE_ID].KC;
	motorData.HomeFast		= &DB->MotorParamsS[MOTOR_PLATE_ID].HomeFast;
	motorData.HomeSlow		= &DB->MotorParamsS[MOTOR_PLATE_ID].HomeSlow;
	motorData.Profile		= &DB->MotorParamsS[MOTOR_PLATE_ID].Profile;
	motorData.EndMovementDelta	= &DB->MotorParamsS[MOTOR_PLATE_ID].EndMovementDelta;
	motorData.SpykeDelta	= &DB->MotorParamsS[MOTOR_PLATE_ID].SpykeDelta;
	motorData.RedCurrent	= &DB->MotorParamsS[MOTOR_PLATE_ID].RedCurrent;
	motorData.Speed			= DB->SpeedTableS[SPEED_PLATE_UP_ID].Speed;
	motorData.Acc			= DB->SpeedTableS[SPEED_PLATE_UP_ID].Acc;
	motorData.Dec			= DB->SpeedTableS[SPEED_PLATE_UP_ID].Dec;
	motorData.SpeedIndex	= &DB->MachineParamsS.PlateUpSpeed;
	motorData.MinLimit		= &DB->LimitsS[MOTOR_PLATE_ID].MinLimit;
	motorData.MaxLimit		= &DB->LimitsS[MOTOR_PLATE_ID].MaxLimit;
	motorData.ScrewStep		= PLATESCREW_STEP;
	motorData.LinearStep	= 0.0;
	motorData.Direction		= &DB->MotorParamsS[MOTOR_PLATE_ID].Direction;
	motorData.EncoderMode		= &DB->MotorParamsS[MOTOR_PLATE_ID].EncoderMode;
	motorData.EncoderType		= &DB->MotorParamsS[MOTOR_PLATE_ID].EncoderType;
	PlateMotor.Init( motorData );

	// Squeegees
	motorData.Address		= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].Address;
	motorData.MinCurrent	= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].MinCurrent;
	motorData.AccCurrent	= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].AccCurrent;
	motorData.MaxCurrent	= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].MaxCurrent;
	motorData.Microstepping	= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].Microstepping;
	motorData.Pulley		= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].Pulley;
	motorData.Reduction		= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].Reduction;
	motorData.Driver		= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].Driver;
	motorData.Current		= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].Current;
	motorData.KP_speed		= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].KP_speed;
	motorData.KI_speed		= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].KI_speed;
	motorData.KP_pos		= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].KP_pos;
	motorData.LineEnc		= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].LineEnc;
	motorData.PulsesToMm	= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].PulsesToMm;
	motorData.PPR			= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].PPR;
	motorData.Poles			= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].Poles;
	motorData.Jerk			= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].Jerk;
	motorData.KA			= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].KA;
	motorData.KS			= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].KS;
	motorData.KC			= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].KC;
	motorData.HomeFast		= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].HomeFast;
	motorData.HomeSlow		= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].HomeSlow;
	motorData.Profile		= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].Profile;
	motorData.EndMovementDelta	= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].EndMovementDelta;
	motorData.SpykeDelta	= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].SpykeDelta;
	motorData.RedCurrent	= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].RedCurrent;
	motorData.Speed			= DB->SpeedTableS[SPEED_SQUEEGEES_ID].Speed;
	motorData.Acc			= DB->SpeedTableS[SPEED_SQUEEGEES_ID].Acc;
	motorData.Dec			= DB->SpeedTableS[SPEED_SQUEEGEES_ID].Dec;
	motorData.SpeedIndex	= &DB->WorkingModesS.SqueegeesSpeed;
	motorData.MinLimit		= &DB->LimitsS[MOTOR_SQUEEGEES_ID].MinLimit;
	motorData.MaxLimit		= &DB->LimitsS[MOTOR_SQUEEGEES_ID].MaxLimit;
	motorData.ScrewStep		= 0.0;
	motorData.LinearStep	= 0.0;
	motorData.Direction		= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].Direction;
	motorData.EncoderMode		= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].EncoderMode;
	motorData.EncoderType		= &DB->MotorParamsS[MOTOR_SQUEEGEES_ID].EncoderType;
	SqueegeesMotor.Init( motorData );

	// Camera X
	motorData.Address		= &DB->MotorParamsS[MOTOR_CAMERAX_ID].Address;
	motorData.MinCurrent	= &DB->MotorParamsS[MOTOR_CAMERAX_ID].MinCurrent;
	motorData.AccCurrent	= &DB->MotorParamsS[MOTOR_CAMERAX_ID].AccCurrent;
	motorData.MaxCurrent	= &DB->MotorParamsS[MOTOR_CAMERAX_ID].MaxCurrent;
	motorData.Microstepping	= &DB->MotorParamsS[MOTOR_CAMERAX_ID].Microstepping;
	motorData.Pulley		= &DB->MotorParamsS[MOTOR_CAMERAX_ID].Pulley;
	motorData.Reduction		= &DB->MotorParamsS[MOTOR_CAMERAX_ID].Reduction;
	motorData.Driver		= &DB->MotorParamsS[MOTOR_CAMERAX_ID].Driver;
	motorData.Current		= &DB->MotorParamsS[MOTOR_CAMERAX_ID].Current;
	motorData.KP_speed		= &DB->MotorParamsS[MOTOR_CAMERAX_ID].KP_speed;
	motorData.KI_speed		= &DB->MotorParamsS[MOTOR_CAMERAX_ID].KI_speed;
	motorData.KP_pos		= &DB->MotorParamsS[MOTOR_CAMERAX_ID].KP_pos;
	motorData.LineEnc		= &DB->MotorParamsS[MOTOR_CAMERAX_ID].LineEnc;
	motorData.PulsesToMm	= &DB->MotorParamsS[MOTOR_CAMERAX_ID].PulsesToMm;
	motorData.PPR			= &DB->MotorParamsS[MOTOR_CAMERAX_ID].PPR;
	motorData.Poles			= &DB->MotorParamsS[MOTOR_CAMERAX_ID].Poles;
	motorData.Jerk			= &DB->MotorParamsS[MOTOR_CAMERAX_ID].Jerk;
	motorData.KA			= &DB->MotorParamsS[MOTOR_CAMERAX_ID].KA;
	motorData.KS			= &DB->MotorParamsS[MOTOR_CAMERAX_ID].KS;
	motorData.KC			= &DB->MotorParamsS[MOTOR_CAMERAX_ID].KC;
	motorData.HomeFast		= &DB->MotorParamsS[MOTOR_CAMERAX_ID].HomeFast;
	motorData.HomeSlow		= &DB->MotorParamsS[MOTOR_CAMERAX_ID].HomeSlow;
	motorData.Profile		= &DB->MotorParamsS[MOTOR_CAMERAX_ID].Profile;
	motorData.EndMovementDelta	= &DB->MotorParamsS[MOTOR_CAMERAX_ID].EndMovementDelta;
	motorData.SpykeDelta	= &DB->MotorParamsS[MOTOR_CAMERAX_ID].SpykeDelta;
	motorData.RedCurrent	= &DB->MotorParamsS[MOTOR_CAMERAX_ID].RedCurrent;
	motorData.Speed			= DB->SpeedTableS[SPEED_CAMERA_ID].Speed;
	motorData.Acc			= DB->SpeedTableS[SPEED_CAMERA_ID].Acc;
	motorData.Dec			= DB->SpeedTableS[SPEED_CAMERA_ID].Dec;
	motorData.SpeedIndex	= &DB->MachineParamsS.CameraSpeed;
	motorData.MinLimit		= &DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit;
	motorData.MaxLimit		= &DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit;
	motorData.ScrewStep		= 0.0;
	motorData.LinearStep	= 0.0;
	motorData.Direction		= &DB->MotorParamsS[MOTOR_CAMERAX_ID].Direction;
	motorData.EncoderMode		= &DB->MotorParamsS[MOTOR_CAMERAX_ID].EncoderMode;
	motorData.EncoderType		= &DB->MotorParamsS[MOTOR_CAMERAX_ID].EncoderType;
	CamXMotor.Init( motorData );

	// Camera Y
	motorData.Address		= &DB->MotorParamsS[MOTOR_CAMERAY_ID].Address;
	motorData.MinCurrent	= &DB->MotorParamsS[MOTOR_CAMERAY_ID].MinCurrent;
	motorData.AccCurrent	= &DB->MotorParamsS[MOTOR_CAMERAY_ID].AccCurrent;
	motorData.MaxCurrent	= &DB->MotorParamsS[MOTOR_CAMERAY_ID].MaxCurrent;
	motorData.Microstepping	= &DB->MotorParamsS[MOTOR_CAMERAY_ID].Microstepping;
	motorData.Pulley		= &DB->MotorParamsS[MOTOR_CAMERAY_ID].Pulley;
	motorData.Reduction		= &DB->MotorParamsS[MOTOR_CAMERAY_ID].Reduction;
	motorData.Driver		= &DB->MotorParamsS[MOTOR_CAMERAY_ID].Driver;
	motorData.Current		= &DB->MotorParamsS[MOTOR_CAMERAY_ID].Current;
	motorData.KP_speed		= &DB->MotorParamsS[MOTOR_CAMERAY_ID].KP_speed;
	motorData.KI_speed		= &DB->MotorParamsS[MOTOR_CAMERAY_ID].KI_speed;
	motorData.KP_pos		= &DB->MotorParamsS[MOTOR_CAMERAY_ID].KP_pos;
	motorData.LineEnc		= &DB->MotorParamsS[MOTOR_CAMERAY_ID].LineEnc;
	motorData.PulsesToMm	= &DB->MotorParamsS[MOTOR_CAMERAY_ID].PulsesToMm;
	motorData.PPR			= &DB->MotorParamsS[MOTOR_CAMERAY_ID].PPR;
	motorData.Poles			= &DB->MotorParamsS[MOTOR_CAMERAY_ID].Poles;
	motorData.Jerk			= &DB->MotorParamsS[MOTOR_CAMERAY_ID].Jerk;
	motorData.KA			= &DB->MotorParamsS[MOTOR_CAMERAY_ID].KA;
	motorData.KS			= &DB->MotorParamsS[MOTOR_CAMERAY_ID].KS;
	motorData.KC			= &DB->MotorParamsS[MOTOR_CAMERAY_ID].KC;
	motorData.HomeFast		= &DB->MotorParamsS[MOTOR_CAMERAY_ID].HomeFast;
	motorData.HomeSlow		= &DB->MotorParamsS[MOTOR_CAMERAY_ID].HomeSlow;
	motorData.Profile		= &DB->MotorParamsS[MOTOR_CAMERAY_ID].Profile;
	motorData.EndMovementDelta	= &DB->MotorParamsS[MOTOR_CAMERAY_ID].EndMovementDelta;
	motorData.SpykeDelta	= &DB->MotorParamsS[MOTOR_CAMERAY_ID].SpykeDelta;
	motorData.RedCurrent	= &DB->MotorParamsS[MOTOR_CAMERAY_ID].RedCurrent;
	motorData.Speed			= DB->SpeedTableS[SPEED_CAMERA_ID].Speed;
	motorData.Acc			= DB->SpeedTableS[SPEED_CAMERA_ID].Acc;
	motorData.Dec			= DB->SpeedTableS[SPEED_CAMERA_ID].Dec;
	motorData.SpeedIndex	= &DB->MachineParamsS.CameraSpeed;
	motorData.MinLimit		= &DB->LimitsS[MOTOR_CAMERAY_ID].MinLimit;
	motorData.MaxLimit		= &DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit;
	motorData.ScrewStep		= 0.0;
	motorData.LinearStep	= 0.0;
	motorData.Direction		= &DB->MotorParamsS[MOTOR_CAMERAY_ID].Direction;
	motorData.EncoderMode		= &DB->MotorParamsS[MOTOR_CAMERAY_ID].EncoderMode;
	motorData.EncoderType		= &DB->MotorParamsS[MOTOR_CAMERAY_ID].EncoderType;
	CamYMotor.Init( motorData );

	// Left Conveyor Width
	motorData.Address		= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].Address;
	motorData.MinCurrent	= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].MinCurrent;
	motorData.AccCurrent	= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].AccCurrent;
	motorData.MaxCurrent	= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].MaxCurrent;
	motorData.Microstepping	= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].Microstepping;
	motorData.Pulley		= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].Pulley;
	motorData.Reduction		= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].Reduction;
	motorData.Driver		= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].Driver;
	motorData.Current		= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].Current;
	motorData.KP_speed		= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].KP_speed;
	motorData.KI_speed		= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].KI_speed;
	motorData.KP_pos		= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].KP_pos;
	motorData.LineEnc		= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].LineEnc;
	motorData.PulsesToMm	= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].PulsesToMm;
	motorData.PPR			= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].PPR;
	motorData.Poles			= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].Poles;
	motorData.Jerk			= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].Jerk;
	motorData.KA			= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].KA;
	motorData.KS			= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].KS;
	motorData.KC			= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].KC;
	motorData.HomeFast		= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].HomeFast;
	motorData.HomeSlow		= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].HomeSlow;
	motorData.Profile		= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].Profile;
	motorData.EndMovementDelta	= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].EndMovementDelta;
	motorData.SpykeDelta	= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].SpykeDelta;
	motorData.RedCurrent	= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].RedCurrent;
	motorData.Speed			= DB->SpeedTableS[SPEED_CONV_WIDTH_ID].Speed;
	motorData.Acc			= DB->SpeedTableS[SPEED_CONV_WIDTH_ID].Acc;
	motorData.Dec			= DB->SpeedTableS[SPEED_CONV_WIDTH_ID].Dec;
	motorData.SpeedIndex	= &DB->MachineParamsS.ConvWidthSpeed;
	motorData.MinLimit		= &DB->LimitsS[MOTOR_LCONV_WIDTH_ID].MinLimit;
	motorData.MaxLimit		= &DB->LimitsS[MOTOR_LCONV_WIDTH_ID].MaxLimit;
	motorData.ScrewStep		= CONVSCREW_STEP;
	motorData.LinearStep	= 0.0;
	motorData.Direction		= &DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].Direction;
	LConvWidthMotor.Init( motorData );

	// Left Conveyor Feed
	motorData.Address		= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].Address;
	motorData.MinCurrent	= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].MinCurrent;
	motorData.AccCurrent	= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].AccCurrent;
	motorData.MaxCurrent	= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].MaxCurrent;
	motorData.Microstepping	= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].Microstepping;
	motorData.Pulley		= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].Pulley;
	motorData.Reduction		= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].Reduction;
	motorData.Driver		= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].Driver;
	motorData.Current		= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].Current;
	motorData.KP_speed		= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].KP_speed;
	motorData.KI_speed		= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].KI_speed;
	motorData.KP_pos		= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].KP_pos;
	motorData.LineEnc		= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].LineEnc;
	motorData.PulsesToMm	= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].PulsesToMm;
	motorData.PPR			= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].PPR;
	motorData.Poles			= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].Poles;
	motorData.Jerk			= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].Jerk;
	motorData.KA			= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].KA;
	motorData.KS			= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].KS;
	motorData.KC			= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].KC;
	motorData.HomeFast		= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].HomeFast;
	motorData.HomeSlow		= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].HomeSlow;
	motorData.Profile		= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].Profile;
	motorData.EndMovementDelta	= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].EndMovementDelta;
	motorData.SpykeDelta	= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].SpykeDelta;
	motorData.RedCurrent	= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].RedCurrent;
	motorData.Speed			= DB->SpeedTableS[SPEED_CONV_FEED_ID].Speed;
	motorData.Acc			= DB->SpeedTableS[SPEED_CONV_FEED_ID].Acc;
	motorData.Dec			= DB->SpeedTableS[SPEED_CONV_FEED_ID].Dec;
	motorData.SpeedIndex	= &DB->MachineParamsS.ConvFeedSpeed;
	motorData.MinLimit		= &DB->LimitsS[MOTOR_LCONV_FEED_ID].MinLimit;
	motorData.MaxLimit		= &DB->LimitsS[MOTOR_LCONV_FEED_ID].MaxLimit;
	motorData.ScrewStep		= 0.0;
	motorData.LinearStep	= 0.0;
	motorData.Direction		= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].Direction;
	LConvFeedMotor.Init( motorData );

	MACHINE_CONFIG(CONV_PUSH_MOTOR)
		// Left Conveyor Push
		motorData.Address		= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].Address;
		motorData.MinCurrent	= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].MinCurrent;
		motorData.AccCurrent	= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].AccCurrent;
		motorData.MaxCurrent	= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].MaxCurrent;
		motorData.Microstepping	= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].Microstepping;
		motorData.Pulley		= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].Pulley;
		motorData.Reduction		= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].Reduction;
		motorData.Driver		= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].Driver;
		motorData.Current		= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].Current;
		motorData.KP_speed		= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].KP_speed;
		motorData.KI_speed		= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].KI_speed;
		motorData.KP_pos		= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].KP_pos;
		motorData.LineEnc		= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].LineEnc;
		motorData.PulsesToMm	= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].PulsesToMm;
		motorData.PPR			= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].PPR;
		motorData.Poles			= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].Poles;
		motorData.Jerk			= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].Jerk;
		motorData.KA			= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].KA;
		motorData.KS			= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].KS;
		motorData.KC			= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].KC;
		motorData.HomeFast		= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].HomeFast;
		motorData.HomeSlow		= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].HomeSlow;
		motorData.Profile		= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].Profile;
		motorData.EndMovementDelta	= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].EndMovementDelta;
		motorData.SpykeDelta	= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].SpykeDelta;
		motorData.RedCurrent	= &DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].RedCurrent;
		motorData.Speed			= DB->SpeedTableS[SPEED_CONV_PUSH_ID].Speed;
		motorData.Acc			= DB->SpeedTableS[SPEED_CONV_PUSH_ID].Acc;
		motorData.Dec			= DB->SpeedTableS[SPEED_CONV_PUSH_ID].Dec;
		motorData.SpeedIndex	= &DB->MachineParamsS.ConvPushSpeed;
		motorData.MinLimit		= &DB->LimitsS[MOTOR_LCONV_PUSH_ID].MinLimit;
		motorData.MaxLimit		= &DB->LimitsS[MOTOR_LCONV_PUSH_ID].MaxLimit;
		motorData.ScrewStep		= 0.0;
		motorData.LinearStep	= 0.0;
		motorData.Direction		= &DB->MotorParamsS[MOTOR_LCONV_FEED_ID].Direction;
		LConvPushMotor.Init( motorData );
	MACHINE_CONFIG_END

	// Center Conveyor Width
	motorData.Address		= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].Address;
	motorData.MinCurrent	= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].MinCurrent;
	motorData.AccCurrent	= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].AccCurrent;
	motorData.MaxCurrent	= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].MaxCurrent;
	motorData.Microstepping	= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].Microstepping;
	motorData.Pulley		= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].Pulley;
	motorData.Reduction		= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].Reduction;
	motorData.Driver		= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].Driver;
	motorData.Current		= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].Current;
	motorData.KP_speed		= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].KP_speed;
	motorData.KI_speed		= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].KI_speed;
	motorData.KP_pos		= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].KP_pos;
	motorData.LineEnc		= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].LineEnc;
	motorData.PulsesToMm	= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].PulsesToMm;
	motorData.PPR			= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].PPR;
	motorData.Poles			= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].Poles;
	motorData.Jerk			= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].Jerk;
	motorData.KA			= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].KA;
	motorData.KS			= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].KS;
	motorData.KC			= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].KC;
	motorData.HomeFast		= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].HomeFast;
	motorData.HomeSlow		= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].HomeSlow;
	motorData.Profile		= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].Profile;
	motorData.EndMovementDelta	= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].EndMovementDelta;
	motorData.SpykeDelta	= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].SpykeDelta;
	motorData.RedCurrent	= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].RedCurrent;
	motorData.Speed			= DB->SpeedTableS[SPEED_CONV_WIDTH_ID].Speed;
	motorData.Acc			= DB->SpeedTableS[SPEED_CONV_WIDTH_ID].Acc;
	motorData.Dec			= DB->SpeedTableS[SPEED_CONV_WIDTH_ID].Dec;
	motorData.SpeedIndex	= &DB->MachineParamsS.ConvWidthSpeed;
	motorData.MinLimit		= &DB->LimitsS[MOTOR_CCONV_WIDTH_ID].MinLimit;
	motorData.MaxLimit		= &DB->LimitsS[MOTOR_CCONV_WIDTH_ID].MaxLimit;
	motorData.ScrewStep		= CONVSCREW_STEP;
	motorData.LinearStep	= 0.0;
	motorData.Direction		= &DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].Direction;
	CConvWidthMotor.Init( motorData );

	// Center Conveyor Feed
	motorData.Address		= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].Address;
	motorData.MinCurrent	= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].MinCurrent;
	motorData.AccCurrent	= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].AccCurrent;
	motorData.MaxCurrent	= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].MaxCurrent;
	motorData.Microstepping	= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].Microstepping;
	motorData.Pulley		= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].Pulley;
	motorData.Reduction		= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].Reduction;
	motorData.Driver		= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].Driver;
	motorData.Current		= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].Current;
	motorData.KP_speed		= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].KP_speed;
	motorData.KI_speed		= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].KI_speed;
	motorData.KP_pos		= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].KP_pos;
	motorData.LineEnc		= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].LineEnc;
	motorData.PulsesToMm	= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].PulsesToMm;
	motorData.PPR			= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].PPR;
	motorData.Poles			= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].Poles;
	motorData.Jerk			= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].Jerk;
	motorData.KA			= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].KA;
	motorData.KS			= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].KS;
	motorData.KC			= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].KC;
	motorData.HomeFast		= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].HomeFast;
	motorData.HomeSlow		= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].HomeSlow;
	motorData.Profile		= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].Profile;
	motorData.EndMovementDelta	= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].EndMovementDelta;
	motorData.SpykeDelta	= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].SpykeDelta;
	motorData.RedCurrent	= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].RedCurrent;
	motorData.Speed			= DB->SpeedTableS[SPEED_CONV_FEED_ID].Speed;
	motorData.Acc			= DB->SpeedTableS[SPEED_CONV_FEED_ID].Acc;
	motorData.Dec			= DB->SpeedTableS[SPEED_CONV_FEED_ID].Dec;
	motorData.SpeedIndex	= &DB->MachineParamsS.ConvFeedSpeed;
	motorData.MinLimit		= &DB->LimitsS[MOTOR_CCONV_FEED_ID].MinLimit;
	motorData.MaxLimit		= &DB->LimitsS[MOTOR_CCONV_FEED_ID].MaxLimit;
	motorData.ScrewStep		= 0.0;
	motorData.LinearStep	= 0.0;
	motorData.Direction		= &DB->MotorParamsS[MOTOR_CCONV_FEED_ID].Direction;
	CConvFeedMotor.Init( motorData );

	// Loader
	motorData.Address		= &DB->MotorParamsS[MOTOR_LOADER_ID].Address;
	motorData.MinCurrent	= &DB->MotorParamsS[MOTOR_LOADER_ID].MinCurrent;
	motorData.AccCurrent	= &DB->MotorParamsS[MOTOR_LOADER_ID].AccCurrent;
	motorData.MaxCurrent	= &DB->MotorParamsS[MOTOR_LOADER_ID].MaxCurrent;
	motorData.Microstepping	= &DB->MotorParamsS[MOTOR_LOADER_ID].Microstepping;
	motorData.Pulley		= &DB->MotorParamsS[MOTOR_LOADER_ID].Pulley;
	motorData.Reduction		= &DB->MotorParamsS[MOTOR_LOADER_ID].Reduction;
	motorData.Driver		= &DB->MotorParamsS[MOTOR_LOADER_ID].Driver;
	motorData.Current		= &DB->MotorParamsS[MOTOR_LOADER_ID].Current;
	motorData.KP_speed		= &DB->MotorParamsS[MOTOR_LOADER_ID].KP_speed;
	motorData.KI_speed		= &DB->MotorParamsS[MOTOR_LOADER_ID].KI_speed;
	motorData.KP_pos		= &DB->MotorParamsS[MOTOR_LOADER_ID].KP_pos;
	motorData.LineEnc		= &DB->MotorParamsS[MOTOR_LOADER_ID].LineEnc;
	motorData.PulsesToMm	= &DB->MotorParamsS[MOTOR_LOADER_ID].PulsesToMm;
	motorData.PPR			= &DB->MotorParamsS[MOTOR_LOADER_ID].PPR;
	motorData.Poles			= &DB->MotorParamsS[MOTOR_LOADER_ID].Poles;
	motorData.Jerk			= &DB->MotorParamsS[MOTOR_LOADER_ID].Jerk;
	motorData.KA			= &DB->MotorParamsS[MOTOR_LOADER_ID].KA;
	motorData.KS			= &DB->MotorParamsS[MOTOR_LOADER_ID].KS;
	motorData.KC			= &DB->MotorParamsS[MOTOR_LOADER_ID].KC;
	motorData.HomeFast		= &DB->MotorParamsS[MOTOR_LOADER_ID].HomeFast;
	motorData.HomeSlow		= &DB->MotorParamsS[MOTOR_LOADER_ID].HomeSlow;
	motorData.Profile		= &DB->MotorParamsS[MOTOR_LOADER_ID].Profile;
	motorData.EndMovementDelta	= &DB->MotorParamsS[MOTOR_LOADER_ID].EndMovementDelta;
	motorData.SpykeDelta	= &DB->MotorParamsS[MOTOR_LOADER_ID].SpykeDelta;
	motorData.RedCurrent	= &DB->MotorParamsS[MOTOR_LOADER_ID].RedCurrent;
	motorData.Speed			= DB->SpeedTableS[SPEED_LOADER_ID].Speed;
	motorData.Acc			= DB->SpeedTableS[SPEED_LOADER_ID].Acc;
	motorData.Dec			= DB->SpeedTableS[SPEED_LOADER_ID].Dec;
	motorData.SpeedIndex	= &DB->MachineParamsS.LoaderSpeed;
	motorData.MinLimit		= &DB->LimitsS[MOTOR_LOADER_ID].MinLimit;
	motorData.MaxLimit		= &DB->LimitsS[MOTOR_LOADER_ID].MaxLimit;
	motorData.ScrewStep		= LOADERSCREW_STEP;
	motorData.LinearStep	= 0.0;
	motorData.Direction		= &DB->MotorParamsS[MOTOR_LOADER_ID].Direction;
	LoaderMotor.Init( motorData );

	// Cleaner
	motorData.Address		= &DB->MotorParamsS[MOTOR_CLEANING_ID].Address;
	motorData.MinCurrent	= &DB->MotorParamsS[MOTOR_CLEANING_ID].MinCurrent;
	motorData.AccCurrent	= &DB->MotorParamsS[MOTOR_CLEANING_ID].AccCurrent;
	motorData.MaxCurrent	= &DB->MotorParamsS[MOTOR_CLEANING_ID].MaxCurrent;
	motorData.Microstepping	= &DB->MotorParamsS[MOTOR_CLEANING_ID].Microstepping;
	motorData.Pulley		= &DB->MotorParamsS[MOTOR_CLEANING_ID].Pulley;
	motorData.Reduction		= &DB->MotorParamsS[MOTOR_CLEANING_ID].Reduction;
	motorData.Driver		= &DB->MotorParamsS[MOTOR_CLEANING_ID].Driver;
	motorData.Current		= &DB->MotorParamsS[MOTOR_CLEANING_ID].Current;
	motorData.KP_speed		= &DB->MotorParamsS[MOTOR_CLEANING_ID].KP_speed;
	motorData.KI_speed		= &DB->MotorParamsS[MOTOR_CLEANING_ID].KI_speed;
	motorData.KP_pos		= &DB->MotorParamsS[MOTOR_CLEANING_ID].KP_pos;
	motorData.LineEnc		= &DB->MotorParamsS[MOTOR_CLEANING_ID].LineEnc;
	motorData.PulsesToMm	= &DB->MotorParamsS[MOTOR_CLEANING_ID].PulsesToMm;
	motorData.PPR			= &DB->MotorParamsS[MOTOR_CLEANING_ID].PPR;
	motorData.Poles			= &DB->MotorParamsS[MOTOR_CLEANING_ID].Poles;
	motorData.Jerk			= &DB->MotorParamsS[MOTOR_CLEANING_ID].Jerk;
	motorData.KA			= &DB->MotorParamsS[MOTOR_CLEANING_ID].KA;
	motorData.KS			= &DB->MotorParamsS[MOTOR_CLEANING_ID].KS;
	motorData.KC			= &DB->MotorParamsS[MOTOR_CLEANING_ID].KC;
	motorData.HomeFast		= &DB->MotorParamsS[MOTOR_CLEANING_ID].HomeFast;
	motorData.HomeSlow		= &DB->MotorParamsS[MOTOR_CLEANING_ID].HomeSlow;
	motorData.Profile		= &DB->MotorParamsS[MOTOR_CLEANING_ID].Profile;
	motorData.EndMovementDelta	= &DB->MotorParamsS[MOTOR_CLEANING_ID].EndMovementDelta;
	motorData.SpykeDelta	= &DB->MotorParamsS[MOTOR_CLEANING_ID].SpykeDelta;
	motorData.RedCurrent	= &DB->MotorParamsS[MOTOR_CLEANING_ID].RedCurrent;
	motorData.Speed			= DB->SpeedTableS[SPEED_CAMERA_ID].Speed;
	motorData.Acc			= DB->SpeedTableS[SPEED_CAMERA_ID].Acc;
	motorData.Dec			= DB->SpeedTableS[SPEED_CAMERA_ID].Dec;
	motorData.SpeedIndex	= 0; //LOW SPEED
	motorData.MinLimit		= &DB->LimitsS[MOTOR_CLEANING_ID].MinLimit;
	motorData.MaxLimit		= &DB->LimitsS[MOTOR_CLEANING_ID].MaxLimit;
	motorData.ScrewStep		= 0.0;
	motorData.LinearStep	= 0.0;
	motorData.Direction		= &DB->MotorParamsS[MOTOR_CLEANING_ID].Direction;
	CleanerMotor.Init( motorData );

	// All stepper and brushless drivers
	AllStepperMotors = new StepperModule(commIntStepper, 0);
	AllBrushlessMotors = new BrushlessModule(commIntBrushless, 0);
}

//----------------------------------------------------------------------------------
// ResetMotors
// 
//----------------------------------------------------------------------------------
int SRMachine::ResetMotors( int mode )
{
	SetStop( false );

	MACHINE_CONFIG( MACHINE_ENABLE )
		if( mode == MODE_SET_HOME )
		{
			bool isError = false;

			if( Table1Motor.motor->Home() == MOTOR_ERROR )
				isError = true;
			if( Table2Motor.motor->Home() == MOTOR_ERROR )
				isError = true;
			if( Table3Motor.motor->Home() == MOTOR_ERROR )
				isError = true;
			if( PlateMotor.motor->Home() == MOTOR_ERROR )
				isError = true;
			if( SqueegeesMotor.motor->Home() == MOTOR_ERROR )
				isError = true;
			if( CamXMotor.motor->Home() == MOTOR_ERROR )
				isError = true;
			if( CamYMotor.motor->Home() == MOTOR_ERROR )
				isError = true;
			if( LConvWidthMotor.motor->Home() == MOTOR_ERROR )
				isError = true;
			if( LConvFeedMotor.motor->Home() == MOTOR_ERROR )
				isError = true;
			if( CConvWidthMotor.motor->Home() == MOTOR_ERROR )
				isError = true;
			if( CConvFeedMotor.motor->Home() == MOTOR_ERROR )
				isError = true;
			if( DB->MachineParamsS.LoaderInstalled )
				if( LoaderMotor.motor->Home() == MOTOR_ERROR )
					isError = true;

			// reset internal variables
			ActRotTable		= 0;
			ActPosXTable	= 0;
			ActPosYTable	= 0;
			Table1Motor.ResetPosition();
			Table2Motor.ResetPosition();
			Table3Motor.ResetPosition();
			CamXMotor.ResetPosition();
			CamYMotor.ResetPosition();
			PlateMotor.ResetPosition();
			SqueegeesMotor.ResetPosition();
			LConvWidthMotor.ResetPosition();
			LConvFeedMotor.ResetPosition();
			CConvWidthMotor.ResetPosition();
			CConvFeedMotor.ResetPosition();
			LoaderMotor.ResetPosition();

			if( isError == true )
			{
				errorCode |= ERR_DRIVER;
				return SR_ERROR;
			}
		}
		else if( mode == MODE_INITIAL_POSITION )
		{
			// reset loader position
			if( DB->MachineParamsS.LoaderInstalled )
			{
				if( LoaderMotor.Move( DB->MachineParamsS.LoaderZeroMovement, ABS_MOVE ) != SR_OK )
					return SR_ERROR;

				actualRackPos = 1;
			}

			// Release camera piston
			if( SetOutput( OUTPUT_CAMERA_PISTON, false ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMPISTONERROR, MSG_ERROR );
				return SR_ERROR;
			}
			myMilliSleep( CAMPISTON_DELAY );

			// reset Plate
			if( PlateMotor.Move( 0, ABS_MOVE ) != SR_OK )
				return SR_ERROR;

			if( PlateMotor.Wait() != SR_OK )
				return SR_ERROR;

			// reset Camera, Squeegees and Table position

			// Save actual camera speed and set low speed
			int currentSpeed = DB->MachineParamsS.CameraSpeed;
			DB->MachineParamsS.CameraSpeed = 0;
			if( CamXMotor.SetSpeedAcc() == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
				return SR_ERROR;
			}
			if( CamYMotor.SetSpeedAcc() == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
				return SR_ERROR;
			}
			if( MoveCamera( (DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit - DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit)/2, DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit, ABS_MOVE ) != SR_OK )
				return SR_ERROR;

			if( SqueegeesMotor.Move( DB->ProductionDataS.SqueegeesZeroMove, ABS_MOVE ) != SR_OK )
				return SR_ERROR;
			SetSqueegeesCycle( false );

			if( ResetTable() != SR_OK )
				return SR_ERROR;

			if( WaitCamera() != SR_OK )
				return SR_ERROR;

			// Reset original camera speed
			DB->MachineParamsS.CameraSpeed = currentSpeed;
			if( CamXMotor.SetSpeedAcc() == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
				return SR_ERROR;
			}
			if( CamYMotor.SetSpeedAcc() == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
				return SR_ERROR;
			}

			if( SqueegeesMotor.Wait() != SR_OK )
				return SR_ERROR;

			if( WaitTable() != SR_OK )
				return SR_ERROR;

			if( DB->MachineParamsS.LoaderInstalled )
				if( LoaderMotor.Wait() != SR_OK )
					return SR_ERROR;
		}
		else if( mode == MODE_START_POSITION )
		{
			// Release camera piston
			if( SetOutput( OUTPUT_CAMERA_PISTON, false ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMPISTONERROR, MSG_ERROR );
				return SR_ERROR;
			}
			myMilliSleep( CAMPISTON_DELAY );

			// reset Plate
			if( PlateMotor.Move( 0, ABS_MOVE ) != SR_OK )
				return SR_ERROR;

			if( PlateMotor.Wait() != SR_OK )
				return SR_ERROR;

			// reset Camera, Squeegees and Table position
			// Save actual camera speed and set low speed
			int currentSpeed = DB->MachineParamsS.CameraSpeed;
			DB->MachineParamsS.CameraSpeed = 0;
			if( CamXMotor.SetSpeedAcc() == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
				return SR_ERROR;
			}
			if( CamYMotor.SetSpeedAcc() == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
				return SR_ERROR;
			}
			if( MoveCamera( (DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit - DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit)/2, DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit, ABS_MOVE ) != SR_OK )
				return SR_ERROR;

			if( SqueegeesMotor.Move( DB->ProductionDataS.SqueegeesZeroMove, ABS_MOVE ) != SR_OK )
				return SR_ERROR;
			SetSqueegeesCycle( false );

			if( ResetTable() != SR_OK )
				return SR_ERROR;

			if( WaitCamera() != SR_OK )
				return SR_ERROR;

			// Reset original camera speed
			DB->MachineParamsS.CameraSpeed = currentSpeed;
			if( CamXMotor.SetSpeedAcc() == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
				return SR_ERROR;
			}
			if( CamYMotor.SetSpeedAcc() == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
				return SR_ERROR;
			}

			if( SqueegeesMotor.Wait() != SR_OK )
				return SR_ERROR;

			if( WaitTable() != SR_OK )
				return SR_ERROR;
		}
		else if( mode == MODE_GO_HOME )
		{
			// Plate at zero movement
			if( PlateMotor.Move( DB->MachineParamsS.PlateZeroMovement, ABS_MOVE, LIMIT_OFF ) != SR_OK )
				return SR_ERROR;

			if( PlateMotor.Wait() != SR_OK )
				return SR_ERROR;

			// Conveyors at zero movement
			if( LConvWidthMotor.Move( DB->MachineParamsS.LConvZeroMovement, ABS_MOVE, LIMIT_OFF ) != SR_OK )
				return SR_ERROR;

			if( CConvWidthMotor.Move( DB->MachineParamsS.CConvZeroMovement, ABS_MOVE, LIMIT_OFF ) != SR_OK )
				return SR_ERROR;

			if( LConvWidthMotor.Wait() != SR_OK )
				return SR_ERROR;

			if( CConvWidthMotor.Wait() != SR_OK )
				return SR_ERROR;
		}
		else if( mode == MODE_STARTPRINTING_POSITION )
		{
			// loader to actual rack position
			if( DB->MachineParamsS.LoaderInstalled )
				if( LoaderMove( actualRackPos ) != SR_OK )
					return SR_ERROR;

			// Release camera piston
			if( SetOutput( OUTPUT_CAMERA_PISTON, false ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMPISTONERROR, MSG_ERROR );
				return SR_ERROR;
			}
			myMilliSleep( CAMPISTON_DELAY );

			// reset Plate position
			if( PlateMotor.Move( 0, ABS_MOVE ) != SR_OK )
				return SR_ERROR;

			if( PlateMotor.Wait() != SR_OK )
				return SR_ERROR;

			// reset Camera and Table position
			if( MoveCamera( (DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit - DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit)/2, DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit, ABS_MOVE ) != SR_OK )
				return SR_ERROR;

			if( ResetTable() != SR_OK )
				return SR_ERROR;

			if( WaitCamera() != SR_OK )
				return SR_ERROR;

			if( WaitTable() != SR_OK )
				return SR_ERROR;
		}
		else if( mode == MODE_ZERO_POSITION )
		{
			wxMessageBox( MSG_REMEMBERSQUEGEES, MACHINE_NAME, wxOK | wxICON_INFORMATION, parent );
			//cout<<"messageBox comparsa"<<endl;
			// reset loader position
			if( DB->MachineParamsS.LoaderInstalled )
				if( LoaderMotor.Move( 0, ABS_MOVE ) != SR_OK )
					return SR_ERROR;

			// Release camera piston
			if( SetOutput( OUTPUT_CAMERA_PISTON, false ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMPISTONERROR, MSG_ERROR );
				return SR_ERROR;
			}
			myMilliSleep( CAMPISTON_DELAY );

			// reset Plate position
			if( PlateMotor.Move( 0, ABS_MOVE ) != SR_OK )
				return SR_ERROR;

			if( PlateMotor.Wait() != SR_OK )
				return SR_ERROR;

			// reset Camera, Squeegees and Table position
			if( MoveCamera( DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit-SHUTDOWN_AXIS_MARGIN, DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit-SHUTDOWN_AXIS_MARGIN, ABS_MOVE ) != SR_OK )
				return SR_ERROR;

			if( SqueegeesMotor.Move( 0, ABS_MOVE ) != SR_OK )
				return SR_ERROR;

			if( ResetTable() != SR_OK )
				return SR_ERROR;

			if( WaitCamera() != SR_OK )
				return SR_ERROR;

			if( SqueegeesMotor.Wait() != SR_OK )
				return SR_ERROR;

			if( WaitTable() != SR_OK )
				return SR_ERROR;

			if( DB->MachineParamsS.LoaderInstalled )
				if( LoaderMotor.Wait() != SR_OK )
					return SR_ERROR;
		}
		else if( mode == MODE_LOAD_POSITION )
		{
			// loader to actual rack position
			if( DB->MachineParamsS.LoaderInstalled )
				if( LoaderMove( actualRackPos ) != SR_OK )
					return SR_ERROR;

			// reset Plate
			if( PlateMotor.Move( 0, ABS_MOVE ) != SR_OK )
				return SR_ERROR;

			if( PlateMotor.Wait() != SR_OK )
				return SR_ERROR;

			if( ResetTable() != SR_OK )
				return SR_ERROR;

			if( WaitTable() != SR_OK )
				return SR_ERROR;
		}
		else
			return SR_ERROR;
	MACHINE_CONFIG_END

	return SR_OK;
}

//----------------------------------------------------------------------------------
// CheckMotorsPos
// 
//----------------------------------------------------------------------------------
int SRMachine::CheckMotorsPos( int mode )
{
	if( mode == CHECK_SECURITY_POSITION )
	{
		if( (ActRotTable		!= 0.0) ||
			(ActPosXTable		!= 0.0) ||
			(ActPosYTable		!= 0.0) ||
			(PlateMotor.GetPosition()	!= 0.0) ||
			(CamXMotor.GetPosition()	!= (DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit - DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit)/2) ||
			(CamYMotor.GetPosition()	!= DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit) ||
			((SqueegeesMotor.GetPosition() != DB->ProductionDataS.SqueegeesZeroMove) && (firstSqueegeesCycle == false)) ||
				((SqueegeesMotor.GetPosition() != (DB->ProductionDataS.SqueegeesMove - DB->ProductionDataS.SqueegeesZeroMove)) && (firstSqueegeesCycle == true)) )

			return SR_ERROR;
		else
			return SR_OK;
	}
	else if( mode == CHECK_LOAD_POSITION )
	{
		if( (ActRotTable		!= 0.0) ||
			(ActPosXTable		!= 0.0) ||
			(ActPosYTable		!= 0.0) ||
			(PlateMotor.GetPosition()	!= 0.0) )

			return SR_ERROR;
		else
			return SR_OK;
	}
	else
		return SR_ERROR;
}

//----------------------------------------------------------------------------------
// SetOutput
// 
//----------------------------------------------------------------------------------
int SRMachine::SetOutput( int outputId, int val )
{
	MACHINE_CONFIG( MACHINE_ENABLE )
		int res = 0;
		int id = DB->IOParamsS[outputId].DriverId - 1;


		if( DB->MotorParamsS[id].Driver == DRIVER_STEPPER_ID )
		{
			StepperModule IOStepper( commIntStepper, DB->MotorParamsS[id].Address );
			res = IOStepper.SetOutputs( DB->IOParamsS[outputId].DriverPort, val );
		}
		else if( DB->MotorParamsS[id].Driver == DRIVER_BRUSHLESS_ID )
		{
			BrushlessModule IOBrushless( commIntBrushless, DB->MotorParamsS[id].Address );
			res = IOBrushless.SetOutputs( DB->IOParamsS[outputId].DriverPort, val );
		}
		else
		{
			BrushModule IOBrush( commIntBrushless, DB->MotorParamsS[id].Address );
			res = IOBrush.SetOutputs( DB->IOParamsS[outputId].DriverPort, val );
		}
		if( res == MOTOR_ERROR )
		{
			errorCode |= ERR_SETOUTPUT;
			return SR_ERROR;
		}

		switch( outputId )
		{
			case OUTPUT_FRAMEUNLOCK:
				isFrameUnlocked = val;
				break;
			case OUTPUT_SQUEEGEESFRONT:
				isSqueegeesFrontOn = val;
				break;
			case OUTPUT_SQUEEGEESREAR:
				isSqueegeesRearOn = val;
				break;
			case OUTPUT_SEMAPHORE_RED:
				isSemaphoreRed = val;
				break;
			case OUTPUT_SEMAPHORE_YELLOW:
				isSemaphoreYellow = val;
				break;
			case OUTPUT_SEMAPHORE_GREEN:
				isSemaphoreGreen = val;
				break;
			case OUTPUT_BUZZER:
				isBuzzerOn = val;
				break;
			case OUTPUT_LEDUP:
				isLedUpOn = val;
				break;
			case OUTPUT_LEDDOWN:
				isLedDownOn = val;
				break;
			case OUTPUT_BOARDLOCK:
				isBoardLocked = val;
				break;
			case OUTPUT_CONVEYOR_PISTON:
				isConveyorPistonOn = val;
				break;
			case OUTPUT_LOADER_PISTON:
				isLoaderPistonOn = val;
				break;
			case OUTPUT_CAMERA_PISTON:
				isCameraPistonOn = val;
				break;
			case OUTPUT_CLEANINGLOCK:
				isCleaningLockOn = val;
				break;
			case OUTPUT_CLEANINGVACUUM:
				isCleaningVacuumOn = val;
				break;
			case OUTPUT_CLEANINGACTIVATE:
				isCleaningActive = val;
				break;
		}
	MACHINE_CONFIG_END

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SetOutputSetOutputReduction
//
//----------------------------------------------------------------------------------
int SRMachine::SetOutputReduction( int outputId, int mode )
{
	MACHINE_CONFIG( MACHINE_ENABLE )
		int res = 0;
		int id = DB->IOParamsS[outputId].DriverId - 1;

		if( DB->MotorParamsS[id].Driver == DRIVER_BRUSHLESS_ID )
		{
			BrushlessModule IOBrushless( commIntBrushless, DB->MotorParamsS[id].Address );
			res = IOBrushless.SetOutputDivider( DB->IOParamsS[outputId].DriverPort, mode );
			if( mode > 1 ) //se devo ridurre, setto anche il red time < 1000
			{
				res = IOBrushless.SetOutputReductionTime( DB->IOParamsS[outputId].DriverPort, OUTPUTREDTIME_PARAM );
			}
			else
			{
				res = IOBrushless.SetOutputReductionTime( DB->IOParamsS[outputId].DriverPort, 1000 );
			}
		}
		if( res == MOTOR_ERROR )
		{
			errorCode |= ERR_SETOUTPUT;
			return SR_ERROR;
		}
	MACHINE_CONFIG_END

	return SR_OK;
}
//----------------------------------------------------------------------------------
// SetOutputSetOutputReduction
//
//----------------------------------------------------------------------------------
int SRMachine::SetPulseModeAndTime( int outputId, int mode, int msec ){
	MACHINE_CONFIG( MACHINE_ENABLE )
			int res = 0;
			int id = DB->IOParamsS[outputId].DriverId - 1;

			if( DB->MotorParamsS[id].Driver == DRIVER_BRUSHLESS_ID )
			{
				BrushlessModule IOBrushless( commIntBrushless, DB->MotorParamsS[id].Address );

				res = IOBrushless.SetOutputPulseTime( DB->IOParamsS[outputId].DriverPort, msec );

				res |= IOBrushless.SetOutputPulseMode( DB->IOParamsS[outputId].DriverPort, mode );

			}
			if( res == MOTOR_ERROR )
			{
				errorCode |= ERR_SETOUTPUT;
				return SR_ERROR;
			}
		MACHINE_CONFIG_END

		return SR_OK;
}

//----------------------------------------------------------------------------------
// GetInput
// 
//----------------------------------------------------------------------------------
int SRMachine::GetInput( int inputId )
{
	int res = 0;
	int id = DB->IOParamsS[inputId].DriverId - 1;
	int portNum = DB->IOParamsS[inputId].DriverPort;

	MACHINE_CONFIG( MACHINE_ENABLE )
		if( DB->MotorParamsS[id].Driver == DRIVER_STEPPER_ID )
		{
			StepperModule IOStepper( commIntStepper, DB->MotorParamsS[id].Address );
			res = IOStepper.ActualInputs();
		}
		else if( DB->MotorParamsS[id].Driver == DRIVER_BRUSHLESS_ID )
		{
			BrushlessModule IOBrushless( commIntBrushless, DB->MotorParamsS[id].Address );
			res = IOBrushless.ActualInputs();
		}
		else
		{
			BrushModule IOBrush( commIntBrushless, DB->MotorParamsS[id].Address );
			res = IOBrush.ActualInputs();
		}
		if( res == MOTOR_ERROR )
		{
			errorCode |= ERR_GETINPUT;
			return SR_ERROR;
		}
	MACHINE_CONFIG_END

	return res & (1<<portNum) ? 1 : 0;
}

//----------------------------------------------------------------------------------
// GetAllInput
// 
//----------------------------------------------------------------------------------
int SRMachine::GetAllInput( int driverId, int &in0, int &in1, int &in2 )
{
	int res = 0;

	MACHINE_CONFIG( MACHINE_ENABLE )
		if( DB->MotorParamsS[driverId].Driver == DRIVER_STEPPER_ID )
		{
			StepperModule IOStepper( commIntStepper, DB->MotorParamsS[driverId].Address );
			res = IOStepper.ActualInputs();
		}
		else if( DB->MotorParamsS[driverId].Driver == DRIVER_BRUSHLESS_ID )
		{
			BrushlessModule IOBrushless( commIntBrushless, DB->MotorParamsS[driverId].Address );
			res = IOBrushless.ActualInputs();
		}
		else
		{
			BrushModule IOBrush( commIntBrushless, DB->MotorParamsS[driverId].Address );
			res = IOBrush.ActualInputs();
		}
		if( res == MOTOR_ERROR )
		{
			errorCode |= ERR_GETINPUT;
			return SR_ERROR;
		}

		in0 = res & 0x0001 ? 1 : 0;
		in1 = res & 0x0002 ? 1 : 0;
		in2 = res & 0x0004 ? 1 : 0;
	MACHINE_CONFIG_END

	return SR_OK;
}

//----------------------------------------------------------------------------------
// GetAllInput
// 
//----------------------------------------------------------------------------------
int SRMachine::GetAllInput( int driverId, int &in0, int &in1, int &in2, int &in3, int &in4, int &in5 )
{
	MACHINE_CONFIG( MACHINE_ENABLE )
	int res = 0;

	if( DB->MotorParamsS[driverId].Driver == DRIVER_STEPPER_ID )
	{
		StepperModule IOStepper( commIntStepper, DB->MotorParamsS[driverId].Address );
		res = IOStepper.ActualInputs();
	}
	else
		return SR_ERROR;

	if( res == MOTOR_ERROR )
	{
		errorCode |= ERR_GETINPUT;
		return SR_ERROR;
	}

	in0 = res & 0x0001 ? 1 : 0;
	in1 = res & 0x0002 ? 1 : 0;
	in2 = res & 0x0004 ? 1 : 0;
	in3 = res & 0x0008 ? 1 : 0;
	in4 = res & 0x0010 ? 1 : 0;
	in5 = res & 0x0020 ? 1 : 0;
	MACHINE_CONFIG_END

	return SR_OK;
}

//----------------------------------------------------------------------------------
// GetMotorStatus
// 
//----------------------------------------------------------------------------------
int SRMachine::GetMotorStatus( int driverId, int &status )
{
	int res = 0;

	MACHINE_CONFIG( MACHINE_ENABLE )
	if( DB->MotorParamsS[driverId].Driver == DRIVER_STEPPER_ID )
	{
		StepperModule IOStepper( commIntStepper, DB->MotorParamsS[driverId].Address );
		status = IOStepper.MotorStatus();
	}
	else if( DB->MotorParamsS[driverId].Driver == DRIVER_BRUSHLESS_ID )
	{
		BrushlessModule IOBrushless( commIntBrushless, DB->MotorParamsS[driverId].Address );
		status = IOBrushless.MotorStatus();
	}
	else
	{
		BrushModule IOBrush( commIntBrushless, DB->MotorParamsS[driverId].Address );
		status = IOBrush.MotorStatus();
	}
	if( status == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}
	MACHINE_CONFIG_END

	return SR_OK;
}

//----------------------------------------------------------------------------------
// GetEncoderStatus
// 
//----------------------------------------------------------------------------------
int SRMachine::GetEncoderStatus( int driverId, int &status )
{
	int res = 0;

	MACHINE_CONFIG( MACHINE_ENABLE )
	if( DB->MotorParamsS[driverId].Driver == DRIVER_STEPPER_ID )
	{
		StepperModule IOStepper( commIntStepper, DB->MotorParamsS[driverId].Address );
		status = IOStepper.EncoderStatus();
	}
	else if( DB->MotorParamsS[driverId].Driver == DRIVER_BRUSHLESS_ID )
	{
		BrushlessModule IOBrushless( commIntBrushless, DB->MotorParamsS[driverId].Address );
		status = IOBrushless.EncoderStatus();
	}
	if( status == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}
	MACHINE_CONFIG_END

	return SR_OK;
}

//----------------------------------------------------------------------------------
// OnTimer
// Manage the external inputs and sensors
//----------------------------------------------------------------------------------
void SRMachine::OnTimer( wxTimerEvent& event )
{
	//std::cout<<"timer partito, statoo: " <<smartLogger->requestedBuzzerStop<< std::endl;
	if(smartLogger->requestedBuzzerStop){
		//std::cout<<"Buzzer da silenziare"<<std::endl;
		smartLogger->requestedBuzzerStop = false;
		SetBuzzerState(false);
	}

	if( GetMachineState() == false )
		return;

	if( isTimerBusy )
		return;

	isTimerBusy = true;

	MACHINE_CONFIG( MACHINE_ENABLE )

		// cover input
		if( checkCover )
		{
			if( GetInput( INPUT_COVER ) == 0 )
			{
				if( wxMessageBox( MSG_COVEROPEN, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, parent ) != wxYES )
					immediateStop = true;
				checkCover = false;
			}
		}

	MACHINE_CONFIG_END

	// camera counter state handling
	if( cameraCounter )
	{
		cameraCounter--;

		if( cameraCounter == 0 )
		{
			wxCommandEvent e( wxEVT_COMMAND_BUTTON_CLICKED );
			e.SetId( ID_CAMERA_WAIT );
			parent->GetEventHandler()->AddPendingEvent( e );

			smartLogger->Write( MSG_FIDUCIALSEARCH );
		}
	}

	isTimerBusy = false;
}


void SRMachine::OnSwitchLightTimer(wxTimerEvent& event){

		if(isLedUpOn){
			if(SetCamera(CAMERA_DOWN)== SR_ERROR){
				return;
			}
			isLedUpOn = false;
			//cout<<"Accendo giu"<<endl;
		}else{
			SetCamera(CAMERA_UP);
			isLedUpOn = true;
			//cout<<"Accendo su"<<endl;
		}
}
//----------------------------------------------------------------------------------
// GetOffset
// 
//----------------------------------------------------------------------------------
void SRMachine::GetOffset( float xcoord, float ycoord, double &xoff, double &yoff )
{
	int cellx, celly;
	float scartox, scartoy;
	float xpos_tab, ypos_tab;

	MachineParamsStruct* p = &DB->MachineParamsS;

	// Casi in cui la coordinata X e' < della X di start
	if( xcoord <= p->OffsetPointsStartX )
	{
		// Y < Y di start
		if( ycoord <= p->OffsetPointsStartY )
		{
			xoff = OffsetXMap(0, 0);
			yoff = OffsetYMap(0, 0);
		}
		// Y > Y di end
		else if( ycoord >= p->OffsetPointsStartY + (p->OffsetPointsNumY - 1) * p->OffsetPointsDistance )
		{
			xoff = OffsetXMap(0, p->OffsetPointsNumY-1);
			yoff = OffsetYMap(0, p->OffsetPointsNumY-1);
		}
		// Y in mezzo alla zona mappata (interpolazione lineare)
		else
		{
			// Recupero la cella di appartenenza della coordinata y
			ypos_tab = ycoord - p->OffsetPointsStartY;
			celly = (int)floor(ypos_tab / p->OffsetPointsDistance);
			scartoy = ypos_tab - celly * p->OffsetPointsDistance;

			xoff = OffsetXMap(0, celly) + scartoy * (OffsetXMap(0, celly+1) - OffsetXMap(0, celly)) / p->OffsetPointsDistance;
			yoff = OffsetYMap(0, celly) + scartoy * (OffsetYMap(0, celly+1) - OffsetYMap(0, celly)) / p->OffsetPointsDistance;
		}
	}
	// Casi in cui la coordinata X e' > della X di end
	else if( xcoord >= p->OffsetPointsStartX + (p->OffsetPointsNumX - 1) * p->OffsetPointsDistance )
	{
		// Y < Y di start
		if( ycoord <= p->OffsetPointsStartY )
		{
			xoff = OffsetXMap(p->OffsetPointsNumX-1, 0);
			yoff = OffsetYMap(p->OffsetPointsNumX-1, 0);
		}
		// Y > Y di end
		else if( ycoord >= p->OffsetPointsStartY + (p->OffsetPointsNumY - 1) * p->OffsetPointsDistance )
		{
			xoff = OffsetXMap(p->OffsetPointsNumX-1, p->OffsetPointsNumY-1);
			yoff = OffsetYMap(p->OffsetPointsNumX-1, p->OffsetPointsNumY-1);
		}
		// Y in mezzo alla zona mappata (interpolazione lineare)
		else
		{
			// Recupero la cella di appartenenza della coordinata y
			ypos_tab = ycoord - p->OffsetPointsStartY;
			celly = (int)floor(ypos_tab / p->OffsetPointsDistance);
			scartoy = ypos_tab - celly * p->OffsetPointsDistance;

			xoff = OffsetXMap(p->OffsetPointsNumX-1, celly) + scartoy * (OffsetXMap(p->OffsetPointsNumX-1, celly+1) - OffsetXMap(p->OffsetPointsNumX-1, celly)) / p->OffsetPointsDistance;
			yoff = OffsetYMap(p->OffsetPointsNumX-1, celly) + scartoy * (OffsetYMap(p->OffsetPointsNumX-1, celly+1) - OffsetYMap(p->OffsetPointsNumX-1, celly)) / p->OffsetPointsDistance;
		}
	}
	// X in mezzo alla zona mappata (interpolazione lineare)
	else
	{
		// Y < Y di start
		if( ycoord <= p->OffsetPointsStartY )
		{
			// Recupero la cella di appartenenza della coordinata x
			xpos_tab = xcoord - p->OffsetPointsStartX;
			cellx = (int)floor(xpos_tab / p->OffsetPointsDistance);
			scartox = xpos_tab - cellx * p->OffsetPointsDistance;

			xoff = OffsetXMap(cellx, 0) + scartox * (OffsetXMap(cellx+1, 0) - OffsetXMap(cellx, 0)) / p->OffsetPointsDistance;
			yoff = OffsetYMap(cellx, 0) + scartox * (OffsetYMap(cellx+1, 0) - OffsetYMap(cellx, 0)) / p->OffsetPointsDistance;
		}
		// Y > Y di end
		else if( ycoord >= p->OffsetPointsStartY + (p->OffsetPointsNumY - 1) * p->OffsetPointsDistance )
		{
			// Recupero la cella di appartenenza della coordinata x
			xpos_tab = xcoord - p->OffsetPointsStartX;
			cellx = (int)floor(xpos_tab / p->OffsetPointsDistance);
			scartox = xpos_tab - cellx * p->OffsetPointsDistance;

			xoff = OffsetXMap(cellx, p->OffsetPointsNumY-1) + scartox * (OffsetXMap(cellx+1, p->OffsetPointsNumY-1) - OffsetXMap(cellx, p->OffsetPointsNumY-1)) / p->OffsetPointsDistance;
			yoff = OffsetYMap(cellx, p->OffsetPointsNumY-1) + scartox * (OffsetYMap(cellx+1, p->OffsetPointsNumY-1) - OffsetYMap(cellx, p->OffsetPointsNumY-1)) / p->OffsetPointsDistance;
		}
		// X e Y in mezzo alla zona mappata (Metodo delle piramidi)
		else
		{
			// Recupero la cella di appartenenza della coordinata x
			xpos_tab = xcoord - p->OffsetPointsStartX;
			cellx = (int)floor(xpos_tab / p->OffsetPointsDistance);
			scartox = xpos_tab - cellx * p->OffsetPointsDistance;

			// Recupero la cella di appartenenza della coordinata y
			ypos_tab = ycoord - p->OffsetPointsStartY;
			celly = (int)floor(ypos_tab / p->OffsetPointsDistance);
			scartoy = ypos_tab - celly * p->OffsetPointsDistance;

			xoff = (OffsetXMap(cellx, celly)/p->OffsetPointsDistance*(p->OffsetPointsDistance-scartox)*(p->OffsetPointsDistance-scartoy)+
					OffsetXMap(cellx+1, celly)/p->OffsetPointsDistance*scartox*(p->OffsetPointsDistance-scartoy)+
					OffsetXMap(cellx+1, celly+1)/p->OffsetPointsDistance*scartox*scartoy+
					OffsetXMap(cellx, celly+1)/p->OffsetPointsDistance*(p->OffsetPointsDistance-scartox)*scartoy)/p->OffsetPointsDistance;

			yoff = (OffsetYMap(cellx, celly)/p->OffsetPointsDistance*(p->OffsetPointsDistance-scartox)*(p->OffsetPointsDistance-scartoy)+
					OffsetYMap(cellx+1, celly)/p->OffsetPointsDistance*scartox*(p->OffsetPointsDistance-scartoy)+
					OffsetYMap(cellx+1, celly+1)/p->OffsetPointsDistance*scartox*scartoy+
					OffsetYMap(cellx, celly+1)/p->OffsetPointsDistance*(p->OffsetPointsDistance-scartox)*scartoy)/p->OffsetPointsDistance;
		}
	}

	xoff += DB->GlobalOffset.X;
	yoff += DB->GlobalOffset.Y;

}

//----------------------------------------------------------------------------------
// OriginSearch
// Ricerca origine per ciascun asse della macchina
//----------------------------------------------------------------------------------
int SRMachine::OriginSearch()
{
	float update_step = 5.0f;
	float current_step = 0.0f;
	wxProgressDialog progressDialog( MACHINE_NAME, wxString( MSG_ORIGINSEARCH ) + wxT("                          "), 100, parent, wxPD_AUTO_HIDE | wxPD_APP_MODAL | wxPD_CAN_ABORT );

	MACHINE_CONFIG( MACHINE_ENABLE )
		// Primo lavoro si allontana il convogliatore centrale dal left portando tutti fuori i motori tavola
		if( SearchTableOrigin_1() == SR_ERROR )
			return SR_ERROR;
		if( progressDialog.Update( current_step += update_step ) == false )
			return SR_ERROR;

		// Start loader 0 search (if enabled)
		if( DB->MachineParamsS.LoaderInstalled )
		{
			if( SearchLoaderOrigin() == SR_ERROR )
				return SR_ERROR;
			if( progressDialog.Update( current_step += update_step ) == false )
				return SR_ERROR;
		}

		// Wait - table
		if( SearchTableOrigin_Wait( &progressDialog, current_step += update_step ) == SR_ERROR )
			return SR_ERROR;

		// Start plate 0 search
		if( SearchPlateOrigin() == SR_ERROR )
			return SR_ERROR;
		if( progressDialog.Update( current_step += update_step ) == false )
			return SR_ERROR;

		// Start squeegees 0 search
		if( SearchSqueegeesOrigin() == SR_ERROR )
			return SR_ERROR;
		if( progressDialog.Update( current_step += update_step ) == false )
			return SR_ERROR;

		// Wait - plate
		if( SearchPlateOrigin_Wait( &progressDialog, current_step += update_step ) == SR_ERROR )
			return SR_ERROR;

		// Move away zero - table
		if( SearchTableOrigin_2() == SR_ERROR )
			return SR_ERROR;
		if( progressDialog.Update( current_step += update_step ) == false )
			return SR_ERROR;

		// Start camera X 0 search
		if( SearchCameraXOrigin() == SR_ERROR )
			return SR_ERROR;
		if( progressDialog.Update( current_step += update_step ) == false )
			return SR_ERROR;

		// Start camera Y 0 search
		if( SearchCameraYOrigin() == SR_ERROR )
			return SR_ERROR;
		if( progressDialog.Update( current_step += update_step ) == false )
			return SR_ERROR;

		// Start conveyors 0 search
		if( SearchLConveyorOrigin() == SR_ERROR )
			return SR_ERROR;
		if( progressDialog.Update( current_step += update_step ) == false )
			return SR_ERROR;

		if( SearchCConveyorOrigin() == SR_ERROR )
			return SR_ERROR;
		if( progressDialog.Update( current_step += update_step ) == false )
			return SR_ERROR;

		// Wait - table
		if( SearchTableOrigin_Wait( &progressDialog, current_step += update_step ) == SR_ERROR )
			return SR_ERROR;

		// Move zero position - table
		if( SearchTableOrigin_3() == SR_ERROR )
			return SR_ERROR;
		if( progressDialog.Update( current_step += update_step ) == false )
			return SR_ERROR;

		// Wait - table
		if( SearchTableOrigin_Wait( &progressDialog, current_step += update_step ) == SR_ERROR )
			return SR_ERROR;

		// Wait - camera X
		if( SearchCameraXOrigin_Wait( &progressDialog, current_step += update_step ) == SR_ERROR )
			return SR_ERROR;

		// Wait - camera Y
		if( SearchCameraYOrigin_Wait( &progressDialog, current_step += update_step ) == SR_ERROR )
			return SR_ERROR;

		// Wait - squeegees
		if( SearchSqueegeesOrigin_Wait( &progressDialog, current_step += update_step ) == SR_ERROR )
			return SR_ERROR;

		// Wait - conveyors
		if( SearchLConveyorOrigin_Wait( &progressDialog, current_step += update_step ) == SR_ERROR )
			return SR_ERROR;

		if( SearchCConveyorOrigin_Wait( &progressDialog, current_step += update_step ) == SR_ERROR )
			return SR_ERROR;

		MACHINE_CONFIG(CONV_PUSH_MOTOR)
			//Push
			if( SearchLConveyorPushOrigin() == SR_ERROR )
				return SR_ERROR;

			if(SearchLConveyorPushOrigin_Wait( &progressDialog, current_step += update_step ) == SR_ERROR )
				return SR_ERROR;
		MACHINE_CONFIG_END

		// Wait - loader (if enabled)
		if( DB->MachineParamsS.LoaderInstalled )
		{
			if( SearchLoaderOrigin_Wait( &progressDialog, current_step += update_step ) == SR_ERROR )
				return SR_ERROR;
		}

	MACHINE_CONFIG_END

	progressDialog.Update( 100 );

	originFlag = true;
	immediateStop = false;
	loaderStop = false;
	return SR_OK;
}

int SRMachine::FinePlateZSearch(){

	MACHINE_CONFIG( DISABLE_PLATE )
		return SR_OK;
	MACHINE_CONFIG_END

	int input1, input2, input3;
	int* sensorCovered;

	if( GetAllInput( MOTOR_PLATE_ID, input1, input2, input3 ) == SR_ERROR ){
		smartLogger->Write( "Plate inputs read failed!", MSG_ERROR );
		return SR_ERROR;
	}

	if(DB->IOParamsS[INPUT_PLATEZERO].DriverPort == 0){
		sensorCovered = &input1;
	}else if(DB->IOParamsS[INPUT_PLATEZERO].DriverPort == 1){
		sensorCovered = &input2;
	}else if(DB->IOParamsS[INPUT_PLATEZERO].DriverPort == 2){
		sensorCovered = &input3;
	}

	int MAX_DOWN_CYCLES = 50;
	while(!(*sensorCovered) && MAX_DOWN_CYCLES){

		MAX_DOWN_CYCLES--;
		if(PlateMotor.MoveAndWait(-0.5, REL_MOVE, false) == SR_ERROR){
			return SR_ERROR;
		}
		if( GetAllInput( MOTOR_PLATE_ID, input1, input2, input3 ) == SR_ERROR ){
			smartLogger->Write( "Plate inputs read failed!", MSG_ERROR );
			return SR_ERROR;
		}
		//cout<<"DISCESA, Letti gli input, Valgono "<<input1<<" "<<input2<<" "<< input3<< " e sensorCovered: "<<*sensorCovered<<endl;;
	}

	if(MAX_DOWN_CYCLES == 0){
		smartLogger->Write( "Plate, Max Iterations Down reached!", MSG_ERROR );
		return SR_ERROR;
	}

	//Adesso si torna Up
	int MAX_UP_CYCLES = 90;
	while( (*sensorCovered) && MAX_UP_CYCLES){

		MAX_UP_CYCLES--;
		if(PlateMotor.MoveAndWait(0.1, REL_MOVE, false) == SR_ERROR){
			return SR_ERROR;
		}
		if( GetAllInput( MOTOR_PLATE_ID, input1, input2, input3 ) == SR_ERROR ){
			smartLogger->Write( "Plate inputs read failed!", MSG_ERROR );
			return SR_ERROR;
		}
		//cout<<"SALITA, Letti gli input, Valgono "<<input1<<" "<<input2<<" "<< input3<< " e sensorCovered: "<<*sensorCovered<<endl;
	}

	if(MAX_UP_CYCLES == 0){
		smartLogger->Write( "Plate, Max Iterations UP reached!", MSG_ERROR );
		return SR_ERROR;
	}

	if(PlateMotor.motor->Home() == SR_ERROR){
		return SR_ERROR;
	}
	PlateMotor.ResetPosition();
	return SR_OK;
}

//----------------------------------------------------------------------------------
// CheckOrigin
// 
//----------------------------------------------------------------------------------
bool SRMachine::CheckOrigin()
{
	MACHINE_CONFIG( MACHINE_ENABLE )
		if( !originFlag )
			errorCode |= ERR_ORIGNOSET;

		return originFlag;
	MACHINE_CONFIG_ELSE
		return true;
	MACHINE_CONFIG_END
}


//----------------------------------------------------------------------------------
// ActivateLimits
// Attiva/disattiva il check dei sensori di finecorsa
//----------------------------------------------------------------------------------
int SRMachine::ActivateLimits( bool state )
{
	limitsOn = state;

	bool isError = false;
	MACHINE_CONFIG( MACHINE_ENABLE )
    if( PlateMotor.motor->SetLimitsCheck( state, LIMITLEVEL_HIGH ) == MOTOR_ERROR )
		isError = true;
    if( CamXMotor.motor->SetLimitsCheck( state, LIMITLEVEL_HIGH ) == MOTOR_ERROR )
		isError = true;
    if( CamYMotor.motor->SetLimitsCheck( state, LIMITLEVEL_HIGH ) == MOTOR_ERROR )
		isError = true;
    if( SqueegeesMotor.motor->SetLimitsCheck( state, LIMITLEVEL_HIGH ) == MOTOR_ERROR )
		isError = true;
    if( LConvWidthMotor.motor->SetLimitsCheck( state, LIMITLEVEL_HIGH ) == MOTOR_ERROR )
		isError = true;
    if( CConvWidthMotor.motor->SetLimitsCheck( state, LIMITLEVEL_HIGH ) == MOTOR_ERROR )
		isError = true;
    if( DB->MachineParamsS.LoaderInstalled )
    {
        if( LoaderMotor.motor->SetLimitsCheck( state, LIMITLEVEL_HIGH ) == MOTOR_ERROR )
    		isError = true;
    }
	MACHINE_CONFIG_END
	if( isError == true )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}
	return SR_OK;
}

//----------------------------------------------------------------------------------
// ResetErrors
// 
//----------------------------------------------------------------------------------
void SRMachine::ResetErrors()
{ 
	// Resetto il flag generico di errore
	errorCode = 0; 
	
	// Resetto i singoli flag dei moduli motore
	Table1Motor.ResetErrors();
	Table2Motor.ResetErrors();
	Table3Motor.ResetErrors();
	PlateMotor.ResetErrors();
	CamXMotor.ResetErrors();
	CamYMotor.ResetErrors();
	SqueegeesMotor.ResetErrors();
	LConvWidthMotor.ResetErrors();
	LConvFeedMotor.ResetErrors();
	CConvWidthMotor.ResetErrors();
	CConvFeedMotor.ResetErrors();
	LoaderMotor.ResetErrors();
	CleanerMotor.ResetErrors();
};

//----------------------------------------------------------------------------------
// GetErrors
// 
//----------------------------------------------------------------------------------
wxString SRMachine::GetErrors()
{ 
	wxString modules;
				
	// Leggo gli errori dai vari moduli e ritorno la stringa coi nomi degli eventuali
	// moduli in errore
	if( Table1Motor.GetErrors() )
	{
		modules += wxString(MSG_TABLE1) + wxT(" ");
	}
	if( Table2Motor.GetErrors() )
	{
		modules += wxString(MSG_TABLE2) + wxT(" ");
	}
	if( Table3Motor.GetErrors() )
	{
		modules += wxString(MSG_TABLE3) + wxT(" ");
	}
	if( PlateMotor.GetErrors() )
	{
		modules += wxString(MSG_PLATE) + wxT(" ");
	}
	if( CamXMotor.GetErrors() )
	{
		modules += wxString(MSG_CAMERAX) + wxT(" ");
	}
	if( CamYMotor.GetErrors() )
	{
		modules += wxString(MSG_CAMERAY) + wxT(" ");
	}
	if( SqueegeesMotor.GetErrors() )
	{
		modules += wxString(MSG_SQUEEGEES) + wxT(" ");
	}
	if( LConvWidthMotor.GetErrors() )
	{
		modules += wxString(MSG_LCONVWIDTH) + wxT(" ");
	}
	if( LConvFeedMotor.GetErrors() )
	{
		modules += wxString(MSG_LCONVFEED) + wxT(" ");
	}
	if( CConvWidthMotor.GetErrors() )
	{
		modules += wxString(MSG_CCONVWIDTH) + wxT(" ");
	}
	if( CConvFeedMotor.GetErrors() )
	{
		modules += wxString(MSG_CCONVFEED) + wxT(" ");
	}
	if( DB->MachineParamsS.LoaderInstalled )
	{
		if( LoaderMotor.GetErrors() )
		{
			modules += wxString(MSG_LOADER) + wxT(" ");
		}
	}
	if( DB->MachineParamsS.CleaningInstalled )
	{
		if( CleanerMotor.GetErrors() )
		{
			modules += wxString(MSG_LOADER) + wxT(" ");
		}
	}
	
	return modules;
};

//----------------------------------------------------------------------------------
// ErrorManagement
// 
//----------------------------------------------------------------------------------
void SRMachine::ErrorManagement()
{
	//wxString modules;
	
	// error already handled
	if( errorCode == 0 )
		return;

	// get the errorCode that generates the ErrorManagement call
	int lastErrorCode = errorCode;

	// origini non settate
	if( lastErrorCode & ERR_ORIGNOSET )
	{
		smartLogger->Write( MSG_ORIGINOSET, MSG_ERROR );
		ResetErrors();
		return;
	}

	// limiti software
	if( lastErrorCode & ERR_LIMITSOFTWARE )
	{
		smartLogger->Write( MSG_MOTORLIMERROR, MSG_ERROR );
		ResetErrors();
		return;
	}

	// stop immediato
	if( lastErrorCode & ERR_IMMEDIATESTOP )
	{
		smartLogger->Write( MSG_ABORTEDBYUSER, MSG_ERROR );
		ResetErrors();
		return;
	}

	// init serial port
	if( lastErrorCode & ERR_SERIALPORT )
	{
		ResetErrors();
		return;
	}

	// Error notify
	SetAlarmLight( ALARMLIGHT_RED );
	SetOutput( OUTPUT_BUZZER, true );
	wxMessageBox( MSG_ERROROCCURRED, MACHINE_NAME, wxICON_ERROR | wxOK, parent  );
	SetOutput( OUTPUT_BUZZER, false );

	if( lastErrorCode & ERR_MOTORINIT )
	{
		smartLogger->Write( MSG_MOTORINITERROR, MSG_ERROR );
		ResetErrors();
		return;
	}

	if( lastErrorCode & ERR_SETOUTPUT ||
		lastErrorCode & ERR_GETINPUT ||
		lastErrorCode & ERR_SETINPUT )
	{
		SetAlarmLight( ALARMLIGHT_YELLOW );
		smartLogger->Write( MSG_MOTORCOMMERROR, MSG_ERROR );
		ResetErrors();
		return;
	}

	// limiti hardware
	if(	lastErrorCode & ERR_LIMITSWITCH )
	{
		smartLogger->Write( MSG_MOTORLIMITSWTCERROR, MSG_ERROR );

		// need a new origin search
		originFlag = false;
		ResetErrors();
		return;
	}

	// errore driver brushless
	if(	lastErrorCode & ERR_BRUSHLESS ||
		lastErrorCode & ERR_DRIVER )
	{
		smartLogger->Write( MSG_MOTORDRIVERERROR, MSG_ERROR );

		// need a new origin search
		originFlag = false;
		ResetErrors();
		return;
	}

	if( lastErrorCode & ERR_MOTORMOVE ){
		smartLogger->Write( MSG_MOTORMOVEERROR, MSG_ERROR );
		SetAlarmLight( ALARMLIGHT_YELLOW );
	}

	if(lastErrorCode & ERR_MOTORWAIT )
	{
		smartLogger->Write( MSG_MOTORWAITERROR, MSG_ERROR );
		SetAlarmLight( ALARMLIGHT_YELLOW );
	}

	ResetErrors();
}

//----------------------------------------------------------------------------------
// SetCamera
// Abilita/disabilita la visione dal lato desiderato
//----------------------------------------------------------------------------------
int SRMachine::SetCamera( CameraEnum state )
{
	switch( state )
	{
		case CAMERA_OFF:
			if( SetOutput( OUTPUT_LEDUP, false ) == SR_ERROR )
				return SR_ERROR;
			if( SetOutput( OUTPUT_LEDDOWN, false ) == SR_ERROR )
				return SR_ERROR;
			break;

		case CAMERA_UP:
			if( SetOutput( OUTPUT_LEDDOWN, false ) == SR_ERROR )
				return SR_ERROR;
			if( SetOutput( OUTPUT_LEDUP, true ) == SR_ERROR )
				return SR_ERROR;
			break;

		case CAMERA_DOWN:
			if( SetOutput( OUTPUT_LEDUP, false ) == SR_ERROR )
				return SR_ERROR;
			if( SetOutput( OUTPUT_LEDDOWN, true ) == SR_ERROR )
				return SR_ERROR;
			break;

		default:
			return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SetCameraLight
// Regola l'intensita' dei led dell'illuminatore
//----------------------------------------------------------------------------------
int SRMachine::SetCameraLight( CameraLightEnum mode )
{
	int redParam = OUTPUTDIVIDER_PARAM;
	MACHINE_CONFIG(CAMERA_COLOR)
		redParam = OUTPUTDIVIDERLEDCOLOR_PARAM;
	MACHINE_CONFIG_END

	switch( mode )
	{
		case LED_HIGH:
			if( SetOutputReduction( OUTPUT_LEDUP, redParam ) == SR_ERROR )
				return SR_ERROR;
			if( SetOutputReduction( OUTPUT_LEDDOWN, redParam ) == SR_ERROR )
				return SR_ERROR;
			break;

		case LED_LOW:
			if( SetOutputReduction( OUTPUT_LEDUP, redParam*2 ) == SR_ERROR )
				return SR_ERROR;
			if( SetOutputReduction( OUTPUT_LEDDOWN, redParam*2 ) == SR_ERROR )
				return SR_ERROR;
			break;

		default:
			return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SetAlarmLight
// Setta lo stato del semaforo
//----------------------------------------------------------------------------------
int SRMachine::SetAlarmLight( AlarmLightEnum state )
{
	MACHINE_CONFIG( MACHINE_ENABLE )
		MACHINE_CONFIG( ENABLE_SEMAPHORE )
			switch( state )
			{
				case ALARMLIGHT_RED:
					if( SetOutput( OUTPUT_SEMAPHORE_RED, true ) == SR_ERROR )
						return SR_ERROR;
					if( SetOutput( OUTPUT_SEMAPHORE_GREEN, false ) == SR_ERROR )
						return SR_ERROR;
					if( SetOutput( OUTPUT_SEMAPHORE_YELLOW, false ) == SR_ERROR )
						return SR_ERROR;
					if(DB->MachineParamsS.BeeperEn){
						if( SetOutput( OUTPUT_BUZZER, true ) == SR_ERROR )
							return SR_ERROR;
					}
					break;

				case ALARMLIGHT_GREEN:
					if( SetOutput( OUTPUT_SEMAPHORE_RED, false ) == SR_ERROR )
						return SR_ERROR;
					if( SetOutput( OUTPUT_SEMAPHORE_GREEN, true ) == SR_ERROR )
						return SR_ERROR;
					if( SetOutput( OUTPUT_SEMAPHORE_YELLOW, false ) == SR_ERROR )
						return SR_ERROR;
					if(DB->MachineParamsS.BeeperEn){
						if( SetOutput( OUTPUT_BUZZER, false ) == SR_ERROR )
							return SR_ERROR;
					}
					break;

				case ALARMLIGHT_YELLOW:
					if( SetOutput( OUTPUT_SEMAPHORE_RED, false ) == SR_ERROR )
						return SR_ERROR;
					if( SetOutput( OUTPUT_SEMAPHORE_GREEN, false ) == SR_ERROR )
						return SR_ERROR;
					if( SetOutput( OUTPUT_SEMAPHORE_YELLOW, true ) == SR_ERROR )
						return SR_ERROR;
					if(DB->MachineParamsS.BeeperEn){
						if( SetOutput( OUTPUT_BUZZER, false ) == SR_ERROR )
							return SR_ERROR;
					}
					break;

				case ALARMLIGHT_OFF:
					if( SetOutput( OUTPUT_SEMAPHORE_RED, false ) == SR_ERROR )
						return SR_ERROR;
					if( SetOutput( OUTPUT_SEMAPHORE_GREEN, false ) == SR_ERROR )
						return SR_ERROR;
					if( SetOutput( OUTPUT_SEMAPHORE_YELLOW, false ) == SR_ERROR )
						return SR_ERROR;
					if(DB->MachineParamsS.BeeperEn){
						if( SetOutput( OUTPUT_BUZZER, false ) == SR_ERROR )
							return SR_ERROR;
					}
					break;

				default:
					return SR_ERROR;
			}
		MACHINE_CONFIG_END
	MACHINE_CONFIG_END
	return SR_OK;
}

int SRMachine::SetBuzzerState( bool state ){
	//cout<<"setto bstato buzzer: "<<state<<endl;
	if(DB->MachineParamsS.BeeperEn){
		if( SetOutput( OUTPUT_BUZZER, state ) == SR_ERROR )
			return SR_ERROR;
	}
	return SR_OK;
}
//----------------------------------------------------------------------------------
// EnableAllMotors
// Abilita tutti i motori
//----------------------------------------------------------------------------------
int SRMachine::EnableAllMotors()
{
	bool isError = false;
	
	char ver, rev;

	float update_step = 7.69f;
	float current_step = 0.0f;
	wxProgressDialog progressDialog( MACHINE_NAME, wxString( MSG_MOTORENABLE ) + " (" + wxString( MSG_TABLE1 ) + ")...", 100, parent, wxPD_AUTO_HIDE | wxPD_APP_MODAL | wxPD_CAN_ABORT );

	MACHINE_CONFIG( MACHINE_ENABLE )
		// Activate multimode for table motors (base address is table 1 motor)
		if( Table1Motor.motor->MultiMotorMode( 1 ) == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_TABLEMMERROR, MSG_ERROR );
			isError = true;
		}

		// TABLE 1
		if( Table1Motor.Enable() == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_TABLEINITERROR, MSG_ERROR );
			isError = true;
		}
		if( Table1Motor.GetFirmwareVersion( ver, rev ) == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_TABLEINITERROR, MSG_ERROR );
			isError = true;
		}
		else
			smartLogger->Write( _("Table") + wxString::Format( "%d firmware ver: %d.%d", 1, ver, rev ) );

		if( progressDialog.Update( current_step += update_step, wxString( MSG_MOTORENABLE ) + " (" + wxString( MSG_TABLE2 ) + ")..." ) == false )
			return SR_ERROR;
	
		// TABLE 2
		if( Table2Motor.Enable() == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_TABLEINITERROR, MSG_ERROR );
			isError = true;
		}
		if( Table2Motor.GetFirmwareVersion( ver, rev ) == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_TABLEINITERROR, MSG_ERROR );
			isError = true;
		}
		else
			smartLogger->Write( _("Table") + wxString::Format( "%d firmware ver: %d.%d", 2, ver, rev ) );
		
		if( progressDialog.Update( current_step += update_step, wxString( MSG_MOTORENABLE ) + " (" + wxString( MSG_TABLE3 ) + ")..." ) == false )
			return SR_ERROR;
	
		// TABLE 3
		if( Table3Motor.Enable() == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_TABLEINITERROR, MSG_ERROR );
			isError = true;
		}
		if( Table3Motor.GetFirmwareVersion( ver, rev ) == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_TABLEINITERROR, MSG_ERROR );
			isError = true;
		}
		else
			smartLogger->Write( _("Table") + wxString::Format( "%d firmware ver: %d.%d", 3, ver, rev ) );
		
		if( progressDialog.Update( current_step += update_step, wxString( MSG_MOTORENABLE ) + " (" + wxString( MSG_PLATE ) + ")..." ) == false )
			return SR_ERROR;

		// PLATE
		PlateMotor.SetMovementSign( 1 );
		PlateMotor.SetPhaseRotSign( 1 );
		if( PlateMotor.Enable() == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_PLATEINITERROR, MSG_ERROR );
			isError = true;
		}
		if( PlateMotor.GetFirmwareVersion( ver, rev ) == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_PLATEINITERROR, MSG_ERROR );
			isError = true;
		}
		else{
			smartLogger->Write( _("Plate") + wxString::Format( " firmware ver: %d.%d", ver, rev ) );
		}
		
		if( progressDialog.Update( current_step += update_step, wxString( MSG_MOTORENABLE ) + " (" + wxString( MSG_SQUEEGEES ) + ")..." ) == false )
			return SR_ERROR;

		// SQUEEGEES
		SqueegeesMotor.SetMovementSign( -1 );
		SqueegeesMotor.SetPhaseRotSign( -1 );
		if( SqueegeesMotor.Enable() == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_SQUEEGEESINITERROR, MSG_ERROR );
			isError = true;
		}
		if( SqueegeesMotor.GetFirmwareVersion( ver, rev ) == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_SQUEEGEESINITERROR, MSG_ERROR );
			isError = true;
		}
		else
			smartLogger->Write( _("Squeegees") + wxString::Format( " firmware ver: %d.%d", ver, rev ) );
		
		if( progressDialog.Update( current_step += update_step, wxString( MSG_MOTORENABLE ) + " (" + wxString( MSG_CAMERAX ) + ")..." ) == false )
			return SR_ERROR;

		// CAMERA X
		CamXMotor.SetMovementSign( 1 );
		CamXMotor.SetPhaseRotSign( -1 );
		if( CamXMotor.Enable() == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
			isError = true;
		}
		if( CamXMotor.GetFirmwareVersion( ver, rev ) == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
			isError = true;
		}
		else
			smartLogger->Write( _("Camera") + wxString::Format( "X firmware ver: %d.%d", ver, rev ) );
		
		if( progressDialog.Update( current_step += update_step, wxString( MSG_MOTORENABLE ) + " (" + wxString( MSG_CAMERAY ) + ")..." ) == false )
			return SR_ERROR;

		// CAMERA Y
		CamYMotor.SetMovementSign( 1 );
		CamYMotor.SetPhaseRotSign( -1 );
		if( CamYMotor.Enable() == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
			isError = true;
		}
		if( CamYMotor.GetFirmwareVersion( ver, rev ) == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
			isError = true;
		}
		else
			smartLogger->Write( _("Camera") + wxString::Format( "Y firmware ver: %d.%d", ver, rev ) );

		if( progressDialog.Update( current_step += update_step, wxString( MSG_MOTORENABLE ) + " (" + wxString( MSG_LCONVWIDTH ) + ")..." ) == false )
			return SR_ERROR;

		// Activate multimode for left conveyor motors (base address is width motor)
		if( LConvWidthMotor.motor->MultiMotorMode( 1 ) == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_LCONVMMERROR, MSG_ERROR );
			isError = true;
		}

		// LCONVW
		LConvWidthMotor.SetMovementSign( -1 );
		if( LConvWidthMotor.Enable() == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_LCONVWINITERROR, MSG_ERROR );
			isError = true;
		}
		if( LConvWidthMotor.GetFirmwareVersion( ver, rev ) == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_LCONVWINITERROR, MSG_ERROR );
			isError = true;
		}
		else
			smartLogger->Write( _("Left Conveyor Width") + wxString::Format( " firmware ver: %d.%d", ver, rev ) );

		if( progressDialog.Update( current_step += update_step, wxString( MSG_MOTORENABLE ) + " (" + wxString( MSG_LCONVFEED ) + ")..." ) == false )
			return SR_ERROR;

		// LCONVF
		LConvFeedMotor.SetMovementSign( -1 );
		if( LConvFeedMotor.Enable() == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_LCONVFINITERROR, MSG_ERROR );
			isError = true;
		}
		if( LConvFeedMotor.GetFirmwareVersion( ver, rev ) == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_LCONVFINITERROR, MSG_ERROR );
			isError = true;
		}
		else
			smartLogger->Write( _("Left Conveyor Feed") + wxString::Format( " firmware ver: %d.%d", ver, rev ) );

		if( progressDialog.Update( current_step += update_step, wxString( MSG_MOTORENABLE ) + " (" + wxString( MSG_CCONVWIDTH ) + ")..." ) == false )
			return SR_ERROR;

		// Activate multimode for center conveyor motors (base address is width motor)
		if( CConvWidthMotor.motor->MultiMotorMode( 1 ) == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_CCONVMMERROR, MSG_ERROR );
			isError = true;
		}

		// CCONVW
		CConvWidthMotor.SetMovementSign( -1 );
		if( CConvWidthMotor.Enable() == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_CCONVWINITERROR, MSG_ERROR );
			isError = true;
		}
		if( CConvWidthMotor.GetFirmwareVersion( ver, rev ) == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_CCONVWINITERROR, MSG_ERROR );
			isError = true;
		}
		else
			smartLogger->Write( _("Center Conveyor Width") + wxString::Format( " firmware ver: %d.%d", ver, rev ) );

		if( progressDialog.Update( current_step += update_step, wxString( MSG_MOTORENABLE ) + " (" + wxString( MSG_CCONVFEED ) + ")..." ) == false )
			return SR_ERROR;

		// CCONVF
		CConvFeedMotor.SetMovementSign( -1 );
		if( CConvFeedMotor.Enable() == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_CCONVFINITERROR, MSG_ERROR );
			isError = true;
		}
		if( CConvFeedMotor.GetFirmwareVersion( ver, rev ) == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_CCONVFINITERROR, MSG_ERROR );
			isError = true;
		}
		else
			smartLogger->Write( _("Center Conveyor Feed") + wxString::Format( " firmware ver: %d.%d", ver, rev ) );

		if( DB->MachineParamsS.LoaderInstalled )
		{
			if( progressDialog.Update( current_step += update_step, wxString( MSG_MOTORENABLE ) + " (" + wxString( MSG_LOADER ) + ")..." ) == false )
				return SR_ERROR;

			// LOADER
			if( LoaderMotor.Enable() == MOTOR_ERROR )
			{
				smartLogger->Write( MSG_LOADERINITERROR, MSG_ERROR );
				isError = true;
			}
			if( LoaderMotor.GetFirmwareVersion( ver, rev ) == MOTOR_ERROR )
			{
				smartLogger->Write( MSG_LOADERINITERROR, MSG_ERROR );
				isError = true;
			}
			else
				smartLogger->Write( _("Loader") + wxString::Format( " firmware ver: %d.%d", ver, rev ) );
		}
		
		if( DB->MachineParamsS.CleaningInstalled )
		{
			if( progressDialog.Update( current_step += update_step, wxString( MSG_MOTORENABLE ) + " (" + wxString( MSG_CLEANER ) + ")..." ) == false )
				return SR_ERROR;

			// CLEANER
			if( CleanerMotor.Enable() == MOTOR_ERROR )
			{
				smartLogger->Write( MSG_CLEANERINITERROR, MSG_ERROR );
				isError = true;
			}
			if( CleanerMotor.Enable() == MOTOR_ERROR )
			{
				smartLogger->Write( MSG_CLEANERINITERROR, MSG_ERROR );
				isError = true;
			}
			if( CleanerMotor.GetFirmwareVersion( ver, rev ) == MOTOR_ERROR )
			{
				smartLogger->Write( MSG_CLEANERINITERROR, MSG_ERROR );
				isError = true;
			}
			else
				smartLogger->Write( _("Cleaning System") + wxString::Format( " firmware ver: %d.%d", ver, rev ) );
		}

		// Se richiesto, riduce la corrente dei led del giano
		if( DB->MachineParamsS.LedLightReduced )
		{
			SetCameraLight( LED_LOW );
		}
		else
		{
			SetCameraLight( LED_HIGH );
		}

		if( progressDialog.Update( current_step += update_step ) == false )
			return SR_ERROR;

	MACHINE_CONFIG_END
	return isError ? SR_ERROR : SR_OK;
}

//----------------------------------------------------------------------------------
// DisableAllMotors
// Disabilita tutti i motori
//----------------------------------------------------------------------------------
int SRMachine::DisableAllMotors()
{
	MACHINE_CONFIG( MACHINE_ENABLE )
		AllStepperMotors->ResetDrive();
		AllBrushlessMotors->ResetDrive();
	MACHINE_CONFIG_END

	return SR_OK;
}

//----------------------------------------------------------------------------------
// StopAllMotors
// Ferma tutti i motori
//----------------------------------------------------------------------------------
int SRMachine::StopAllMotors()
{
	AllStepperMotors->StopRotation( RAMP );
	AllBrushlessMotors->StopRotation( RAMP );

	return SR_OK;
}

int SRMachine::setOutputHardwareReduction(){
	// reduce outputs for semaphore and buzzer
	if( SetOutputReduction( OUTPUT_SEMAPHORE_RED, REDUCTION_SEMAPHORE ) == SR_ERROR )
		return SR_ERROR;
	if( SetOutputReduction( OUTPUT_SEMAPHORE_YELLOW, REDUCTION_SEMAPHORE ) == SR_ERROR )
		return SR_ERROR;
	if( SetPulseModeAndTime( OUTPUT_SEMAPHORE_YELLOW, PULSED_MODE_ON, PULSED_MODE_PERIOD/2 ) == SR_ERROR )
		return SR_ERROR;
	if( SetOutputReduction( OUTPUT_SEMAPHORE_GREEN, REDUCTION_SEMAPHORE ) == SR_ERROR )
		return SR_ERROR;
	//if( SetOutputReduction( OUTPUT_BUZZER, REDUCTION_BUZZER ) == SR_ERROR )
		//return SR_ERROR;
//	if( SetPulseModeAndTime( OUTPUT_BUZZER, PULSED_MODE_ON, PULSED_MODE_PERIOD/2 ) == SR_ERROR )
//		return SR_ERROR;

	return SR_OK;
}

//----------------------------------------------------------------------------------
// ActivateAllMotorsPID
// Abilita tutti i motori
//----------------------------------------------------------------------------------
int SRMachine::ActivateAllMotorsPID()
{
	bool isError = false;
	
	MACHINE_CONFIG( MACHINE_ENABLE )
		// PLATE
		/*
		if( PlateMotor.EnableControlPID() == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_PLATEINITERROR, MSG_ERROR );
			isError = true;
		}
		*/

		// SQUEEGEES
		if( SqueegeesMotor.EnableControlPID() == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_PLATEINITERROR, MSG_ERROR );
			isError = true;
		}

		// CAMERA X
		if( CamXMotor.EnableControlPID() == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_PLATEINITERROR, MSG_ERROR );
			isError = true;
		}

		// CAMERA Y
		if( CamYMotor.EnableControlPID() == MOTOR_ERROR )
		{
			smartLogger->Write( MSG_PLATEINITERROR, MSG_ERROR );
			isError = true;
		}

	MACHINE_CONFIG_END
	return isError ? SR_ERROR : SR_OK;
}

//----------------------------------------------------------------------------------
// Cleaning Cycle
// Esegue un ciclo di pulizia lamina
//----------------------------------------------------------------------------------
int SRMachine::CleaningCycle(bool feedPaper)
{
	MACHINE_CONFIG( MACHINE_ENABLE )

		if(DB->WorkingModesS.CleaningEngageDistance==0){
			DB->WorkingModesS.CleaningEngageDistance = floor(DB->ProductionDataS.PCBY - DB->MachineParamsS.CConvMovement - DB->MachineParamsS.CConvZeroMovement + CLEANING_CONVEYOR_OFFSET - DB->MachineParamsS.CleaningCameraDelta);
		}


		// Save actual camera speed and set low speed
		cameraSavedSpeed = DB->MachineParamsS.CameraSpeed;
		DB->MachineParamsS.CameraSpeed = 0;
		if( CamXMotor.SetSpeedAcc() == SR_ERROR )
		{
			smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
			return SR_ERROR;
		}
		if( CamYMotor.SetSpeedAcc() == SR_ERROR )
		{
			smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
			return SR_ERROR;
		}

		// Move camera to cleaning system engagement position
		if( MoveCameraAndWait( (DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit - DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit)/2, DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit, ABS_MOVE ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
			return SR_ERROR;
		}

		// Engage cleaning system
		if( SetOutput( OUTPUT_CLEANINGLOCK, true ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CLEANPISTONERROR, MSG_ERROR );
			return SR_ERROR;
		}
		myMilliSleep( CLEANINGPISTON_DELAY );

		// Advance cleaning wipe
		if(feedPaper){
			if( CleanerMotor.Move( DB->MachineParamsS.CleaningActivationTime ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CLEANERERROR, MSG_ERROR );
				//return SR_ERROR;
			}
		}

		// If necessary, activate cleaning system vacuum
		if( DB->MachineParamsS.CleaningVacuumOn )
		{
			if( SetOutput( OUTPUT_CLEANINGVACUUM, true ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CLEANVACUUMERROR, MSG_ERROR );
				return SR_ERROR;
			}
		}

		// Move cleaning system to engage position
		if( MoveCameraAndWait( (DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit - DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit)/2, DB->WorkingModesS.CleaningEngageDistance, ABS_MOVE ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
			return SR_ERROR;
		}
		// Move up cleaning system
		if( SetOutput( OUTPUT_CLEANINGACTIVATE, true ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CLEANACTIVATEERROR, MSG_ERROR );
			return SR_ERROR;
		}
		myMilliSleep( CLEANINGUP_DELAY );


		// Move camera and cleaning system to front position
		if( MoveCameraAndWait( (DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit - DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit)/2, DB->LimitsS[MOTOR_CAMERAY_ID].MinLimit, ABS_MOVE ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
			return SR_ERROR;
		}

		// If double feeding mode, advance cleaning wipe
		if( DB->MachineParamsS.CleaningDoubleFeed )
		{
			//deActivate
			// Move down cleaning system
			if( SetOutput( OUTPUT_CLEANINGACTIVATE, false ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CLEANACTIVATEERROR, MSG_ERROR );
				return SR_ERROR;
			}
			myMilliSleep( 500 );
			if( CleanerMotor.Move( DB->MachineParamsS.CleaningActivationTime ) == SR_ERROR )
			{
				//smartLogger->Write( MSG_CLEANERERROR, MSG_ERROR );
				//return SR_ERROR;
			}
			//ReActivate
			// Move down cleaning system
			if( SetOutput( OUTPUT_CLEANINGACTIVATE, true ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CLEANACTIVATEERROR, MSG_ERROR );
				return SR_ERROR;
			}
			//myMilliSleep( FLICKERING_DELAY );
		}
		// Move cleaning system to engage position
		if( MoveCameraAndWait( (DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit - DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit)/2, DB->WorkingModesS.CleaningEngageDistance, ABS_MOVE ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
			return SR_ERROR;
		}
		// Move down cleaning system
		if( SetOutput( OUTPUT_CLEANINGACTIVATE, false ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CLEANACTIVATEERROR, MSG_ERROR );
			return SR_ERROR;
		}
		myMilliSleep( CLEANINGUP_DELAY );

		// Move camera back to cleaning system engagement position
		if( MoveCameraAndWait( (DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit - DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit)/2, DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit, ABS_MOVE ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
			return SR_ERROR;
		}

		// If necessary, deactivate cleaning system vacuum
		if( DB->MachineParamsS.CleaningVacuumOn )
		{
			if( SetOutput( OUTPUT_CLEANINGVACUUM, false ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CLEANVACUUMERROR, MSG_ERROR );
				return SR_ERROR;
			}
		}

		// Disengage cleaning system
		if( SetOutput( OUTPUT_CLEANINGLOCK, false ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CLEANPISTONERROR, MSG_ERROR );
			return SR_ERROR;
		}

		// Reset motors
		if( ResetMotors( MODE_STARTPRINTING_POSITION ) == SR_ERROR )
		{
			return SR_ERROR;
		}

		// Reset original camera speed
		DB->MachineParamsS.CameraSpeed = cameraSavedSpeed;
		if( CamXMotor.SetSpeedAcc() == SR_ERROR )
		{
			smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
			return SR_ERROR;
		}
		if( CamYMotor.SetSpeedAcc() == SR_ERROR )
		{
			smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
			return SR_ERROR;
		}

	MACHINE_CONFIG_END

	return SR_OK;
}

int SRMachine::WaitMotorAndCheckSensor(int inputID, Motor* MainMotor){

	int isOK = 0;
	int limit = 0;
	int status = 0;
	int retry = 0;
	int brushless = 0;
	int extSensorChecked = 0;
	int intSensorChecked = 0;

	MACHINE_CONFIG( MACHINE_ENABLE )

			do
			{
				status = MainMotor->motor->MotorStatus();
				if( status == MOTOR_ERROR )
				{
					retry++;
					continue;
				}

				if( !(status & MOTOR_RUNNING) )
					isOK = 1;

				if( (status & MOTOR_OVERRUN) && MainMotor->data.limitsOn )
					limit = 1;

				if( *MainMotor->data.Driver == DRIVER_BRUSHLESS_ID )
				{
					if( (status & MOTOR_OVERCURRENT) || (status & MOTOR_TIMEOUT) || (status & MOTOR_OVERSPEED) || (status & MOTOR_NOENC) || (status & MOTOR_NO_FOLLOW) )
						brushless = 1;
				}
				// Check for input sensor
				//cout<<"Sensor output: "<<outputSensor<<endl;
				if( GetInput( INPUT_SENSOR_EXT ) == 1 ){
					extSensorChecked = true;
				}
				MACHINE_CONFIG(CONV_PUSH_MOTOR)
				if( GetInput( INPUT_SENSOR_INT ) == 1 ){
					intSensorChecked = true;
				}
				MACHINE_CONFIG_END

				::wxYield();
			}
			while( !isOK && !limit && retry < WAIT_RETRY && !brushless );

			if( retry >= WAIT_RETRY )
			{
				*MainMotor->data.errorCode |= ERR_MOTORWAIT;
				return MOTOR_ERROR;
			}
			if( limit )
			{
				*MainMotor->data.errorCode |= ERR_LIMITSWITCH;
				return MOTOR_ERROR;
			}
			if( brushless )
			{
				*MainMotor->data.errorCode |= ERR_BRUSHLESS;
				return MOTOR_ERROR;
			}

			if( *MainMotor->data.Driver == DRIVER_BRUSHLESS_ID )
			{
				// Set reduced current as nominal current
				if( MainMotor->motor->SetNominalCurrent( *MainMotor->data.RedCurrent ) == MOTOR_ERROR )
				{
					*MainMotor->data.errorCode |= ERR_MOTORINIT;
					return MOTOR_ERROR;
				}
			}
		MACHINE_CONFIG_END

		bool passageSeen = extSensorChecked;
		MACHINE_CONFIG(CONV_PUSH_MOTOR)
			passageSeen &= intSensorChecked;
		MACHINE_CONFIG_END
		if(passageSeen){
			return MOTOR_OK;
		}else{
			return MOTOR_OK_NO_SENSOR;
		}

}






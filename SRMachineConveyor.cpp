//---------------------------------------------------------------------------
//
// Name:        SRMachineConveyor.cpp
// Author:      Daniele Belloni
// Created:     18/06/2015
// Description: SRMachine class implementation
//
//---------------------------------------------------------------------------
#include "SRMachine.h"
#include "GlobalEnum.h"
#include "GlobalUtils.h"
#include "GlobalDefs.h"
#include "Errors.h"
#include "Messages.h"
#include <wx/msgdlg.h>

#define CONVEYOR_WIDTH_ZEROTIMEOUT		40000
#define CONVEYOR_PUSH_ZEROTIMEOUT		40000

int SRMachine::SearchLConveyorOrigin()
{
	int flag = DB->IOParamsS[INPUT_LCONVWZERO].DriverPort + 1;

	// Set motor params

	// Set timeout
	if( LConvWidthMotor.motor->SetHomeTimeout( CONVEYOR_WIDTH_ZEROTIMEOUT ) == MOTOR_ERROR )
	{
		errorCode |= ERR_SETINPUT;
		return SR_ERROR;
	}

	// Set 0 sensor input
	if( LConvWidthMotor.motor->HomeSensorInput( flag ) == MOTOR_ERROR )
	{
		errorCode |= ERR_SETINPUT;
		return SR_ERROR;
	}

	// Set homing speeds
	if( LConvWidthMotor.motor->SetHomingSpeed( HOME_SLOW, DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].HomeSlow ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}
	if( LConvWidthMotor.motor->SetHomingSpeed( HOME_FAST, DB->MotorParamsS[MOTOR_LCONV_WIDTH_ID].HomeFast ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}

	if( LConvWidthMotor.motor->SetHomeSensorLevel( ZEROLEVEL_HIGH ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}

	// Set home movement
	double Resolution = LConvWidthMotor.GetResolution();
	long StepActPulse = myLRound(fabs(DB->LimitsS[MOTOR_LCONV_WIDTH_ID].MinLimit) / Resolution);

	if( LConvWidthMotor.motor->SetHomeMove( StepActPulse ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return MOTOR_ERROR;
	}

	// Start 0 search
	if( LConvWidthMotor.motor->SearchPos0( ZEROSEARCH_POS ) == SR_ERROR )
		return SR_ERROR;

	return SR_OK;
}

int SRMachine::SearchLConveyorOrigin_Wait( wxProgressDialog *progressDialog, int value )
{
	int flag = true;

	while( flag )
	{
		::wxYield();
		if( progressDialog->Update( value ) == false )
			return SR_ERROR;

		flag = LConvWidthMotor.motor->MotorStatus();
		if( (flag == MOTOR_ERROR) || (flag & MOTOR_PROCERROR) )
		{
			errorCode |= ERR_DRIVER;
			return SR_ERROR;
		}

		flag = flag & MOTOR_ZERO;

		myMilliSleep( MOTOR_STATUS_DELAY );
	}
	
	return SR_OK;
}

int SRMachine::SearchLConveyorPushOrigin(){
	int flag = DB->IOParamsS[INPUT_LCONVPZERO].DriverPort + 1;

	// Set motor params

	// Set timeout
	if( LConvPushMotor.motor->SetHomeTimeout( CONVEYOR_PUSH_ZEROTIMEOUT ) == MOTOR_ERROR )
	{
		errorCode |= ERR_SETINPUT;
		return SR_ERROR;
	}

	// Set 0 sensor input
	if( LConvPushMotor.motor->HomeSensorInput( flag ) == MOTOR_ERROR )
	{
		errorCode |= ERR_SETINPUT;
		return SR_ERROR;
	}

	// Set homing speeds
	if( LConvPushMotor.motor->SetHomingSpeed( HOME_SLOW, DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].HomeSlow ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}
	if( LConvPushMotor.motor->SetHomingSpeed( HOME_FAST, DB->MotorParamsS[MOTOR_LCONV_PUSH_ID].HomeFast ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}

	if( LConvPushMotor.motor->SetHomeSensorLevel( ZEROLEVEL_HIGH ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}

	// Set home movement
	double Resolution = LConvPushMotor.GetResolution();
	long StepActPulse = myLRound(fabs(1.2*DB->LimitsS[MOTOR_LCONV_PUSH_ID].MaxLimit) / Resolution);

	if( LConvPushMotor.motor->SetHomeMove( StepActPulse ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return MOTOR_ERROR;
	}

	// Start 0 search
	if( LConvPushMotor.motor->SearchPos0( ZEROSEARCH_POS ) == SR_ERROR )
			return SR_ERROR;

	return SR_OK;
}

int SRMachine::SearchLConveyorPushOrigin_Wait( wxProgressDialog *progressDialog, int value ){
	int flag = true;

	while( flag ){
		::wxYield();
		if( progressDialog->Update( value ) == false )
			return SR_ERROR;

		flag = LConvPushMotor.motor->MotorStatus();
		if( (flag == MOTOR_ERROR) || (flag & MOTOR_PROCERROR) )
		{
			errorCode |= ERR_DRIVER;
			return SR_ERROR;
		}

		flag = flag & MOTOR_ZERO;

		myMilliSleep( MOTOR_STATUS_DELAY );
	}

	return SR_OK;
}

int SRMachine::SearchCConveyorOrigin()
{
	int flag = DB->IOParamsS[INPUT_CCONVWZERO].DriverPort + 1;

	// Set motor params

	// Set timeout
	if( CConvWidthMotor.motor->SetHomeTimeout( CONVEYOR_WIDTH_ZEROTIMEOUT ) == MOTOR_ERROR )
	{
		errorCode |= ERR_SETINPUT;
		return SR_ERROR;
	}

	// Set 0 sensor input
	if( CConvWidthMotor.motor->HomeSensorInput( flag ) == MOTOR_ERROR )
	{
		errorCode |= ERR_SETINPUT;
		return SR_ERROR;
	}

	// Set homing speeds
	if( CConvWidthMotor.motor->SetHomingSpeed( HOME_SLOW, DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].HomeSlow ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}
	if( CConvWidthMotor.motor->SetHomingSpeed( HOME_FAST, DB->MotorParamsS[MOTOR_CCONV_WIDTH_ID].HomeFast ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}

	if( CConvWidthMotor.motor->SetHomeSensorLevel( ZEROLEVEL_HIGH ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}

	// Set home movement
	double Resolution = CConvWidthMotor.GetResolution();
	long StepActPulse = myLRound(fabs(DB->LimitsS[MOTOR_CCONV_WIDTH_ID].MinLimit) / Resolution);

	if( CConvWidthMotor.motor->SetHomeMove( StepActPulse ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return MOTOR_ERROR;
	}

	// Start 0 search
	if( CConvWidthMotor.motor->SearchPos0( ZEROSEARCH_POS ) == SR_ERROR )
		return SR_ERROR;

	return SR_OK;
}

int SRMachine::SearchCConveyorOrigin_Wait( wxProgressDialog *progressDialog, int value )
{
	int flag = true;

	while( flag )
	{
		::wxYield();
		if( progressDialog->Update( value ) == false )
			return SR_ERROR;

		flag = CConvWidthMotor.motor->MotorStatus();
		if( (flag == MOTOR_ERROR) || (flag & MOTOR_PROCERROR) )
		{
			errorCode |= ERR_DRIVER;
			return SR_ERROR;
		}

		flag = flag & MOTOR_ZERO;

		myMilliSleep( MOTOR_STATUS_DELAY );
	}

	return SR_OK;
}

int SRMachine::LoadBoard( int mode )
{
	if( isBoardLoaded )
		return SR_OK;

	smartLogger->Write( MSG_LOADING );

	MACHINE_CONFIG( MACHINE_ENABLE )
		// Check for motors position
		if( CheckMotorsPos( CHECK_LOAD_POSITION ) == SR_ERROR )
			if( ResetMotors( MODE_LOAD_POSITION ) == SR_ERROR )
				return SR_ERROR;

		// Camera piston to correct position to stop the board
		if( MoveCameraAndWait( DB->MachineParamsS.ConvEdgeX + DB->ProductionDataS.PCBX/2 + DB->MachineParamsS.CamPistonDeltaX + DB->WorkingModesS.PistonLoadingDeltaX,
				DB->MachineParamsS.ConvEdgeY + DB->ProductionDataS.PCBY/2 + DB->MachineParamsS.CamPistonDeltaY + DB->WorkingModesS.PistonLoadingDeltaY, ABS_MOVE ) == SR_ERROR )
			return SR_ERROR;



		// Activate camera piston
		if( SetOutput( OUTPUT_CAMERA_PISTON, true ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CAMPISTONERROR, MSG_ERROR );
			return SR_ERROR;
		}

		// If loader enabled...
		if( DB->MachineParamsS.LoaderInstalled && DB->WorkingModesS.LoaderEn )
		{
			// Activate loader piston
			// We suppose a board is ready in the output position!
			if( SetOutput( OUTPUT_LOADER_PISTON, true ) == SR_ERROR )
			{
				smartLogger->Write( MSG_LOADERPISTONERROR, MSG_ERROR );
				return SR_ERROR;
			}

			myMilliSleep( LOADERPISTON_DELAY );

			if( SetOutput( OUTPUT_LOADER_PISTON, false ) == SR_ERROR )
			{
				smartLogger->Write( MSG_LOADERPISTONERROR, MSG_ERROR );
				return SR_ERROR;
			}
		}

		// Move conveyors belts
		if( LConvFeedMotor.motor->Home() == SR_ERROR )
			return SR_ERROR;
		LConvFeedMotor.ResetPosition();
		if( CConvFeedMotor.motor->Home() == SR_ERROR )
			return SR_ERROR;
		CConvFeedMotor.ResetPosition();

		if( LConvFeedMotor.Move( DB->LimitsS[MOTOR_LCONV_FEED_ID].MaxLimit ) == SR_ERROR )
			return SR_ERROR;
		if( CConvFeedMotor.Move( DB->LimitsS[MOTOR_CCONV_FEED_ID].MaxLimit ) == SR_ERROR )
			return SR_ERROR;

		if(mode && DB->WorkingModesS.InputSensorEnabled ){
			if(WaitMotorAndCheckSensor(INPUT_SENSOR_EXT, &CConvFeedMotor) == MOTOR_OK_NO_SENSOR){
				if( SetAlarmLight(ALARMLIGHT_RED) == SR_ERROR ){
					smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
					return SR_ERROR;
				}
				wxMessageBox( MSG_INPUTSECURITYSERROR2, MACHINE_NAME, wxOK | wxICON_ERROR, parent );
				if( SetAlarmLight(ALARMLIGHT_OFF) == SR_ERROR ){
					smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
					return SR_ERROR;
				}
				return SR_ERROR;
			}
		}else{
			if(LConvFeedMotor.Wait()== SR_ERROR )
				return SR_ERROR;
			if(CConvFeedMotor.Wait()== SR_ERROR )
				return SR_ERROR;
		}

		// Release camera piston
		if( SetOutput( OUTPUT_CAMERA_PISTON, false ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CAMPISTONERROR, MSG_ERROR );
			return SR_ERROR;
		}
		myMilliSleep( CAMPISTON_DELAY );

		// Move camera in home position
		if( MoveCameraAndWait( (DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit - DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit)/2, DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit, ABS_MOVE ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
			return SR_ERROR;
		}

		// Check for input sensor
		if( GetInput( INPUT_SENSOR_EXT ) == 1 ){
			wxMessageBox( MSG_INPUTSECURITYSERROR, MACHINE_NAME, wxOK | wxICON_ERROR, parent );
			return SR_ERROR;
		}
		MACHINE_CONFIG(CONV_PUSH_MOTOR)
			if( GetInput( INPUT_SENSOR_INT ) == 1 ){
				wxMessageBox( MSG_INPUTSECURITYSERROR, MACHINE_NAME, wxOK | wxICON_ERROR, parent );
				return SR_ERROR;
			}
		MACHINE_CONFIG_END

		// Activate board lock
		if( SetOutput( OUTPUT_BOARDLOCK, true ) == SR_ERROR )
		{
			smartLogger->Write( MSG_BOARDLOCKERROR, MSG_ERROR );
			return SR_ERROR;
		}
	MACHINE_CONFIG_END

	isBoardLoaded = true;

	return SR_OK;
}

int SRMachine::startBoardLoading(){
	if( isBoardLoaded )
			return SR_OK;

	smartLogger->Write( MSG_LOADING );

	MACHINE_CONFIG( MACHINE_ENABLE )
		// Activate camera piston
		if( SetOutput( OUTPUT_CAMERA_PISTON, true ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CAMPISTONERROR, MSG_ERROR );
			return SR_ERROR;
		}

		// If loader enabled...
		if( DB->MachineParamsS.LoaderInstalled && DB->WorkingModesS.LoaderEn ){
			if( SetOutput( OUTPUT_LOADER_PISTON, true ) == SR_ERROR )
			{
				smartLogger->Write( MSG_LOADERPISTONERROR, MSG_ERROR );
				return SR_ERROR;
			}
			myMilliSleep( LOADERPISTON_DELAY );
			if( SetOutput( OUTPUT_LOADER_PISTON, false ) == SR_ERROR )
			{
				smartLogger->Write( MSG_LOADERPISTONERROR, MSG_ERROR );
				return SR_ERROR;
			}
		}

		// Move conveyors belts
		if( LConvFeedMotor.motor->Home() == SR_ERROR )
			return SR_ERROR;
		LConvFeedMotor.ResetPosition();
		if( CConvFeedMotor.motor->Home() == SR_ERROR )
			return SR_ERROR;
		CConvFeedMotor.ResetPosition();

		if( LConvFeedMotor.Move( DB->LimitsS[MOTOR_LCONV_FEED_ID].MaxLimit ) == SR_ERROR )
			return SR_ERROR;
		if( CConvFeedMotor.Move( DB->LimitsS[MOTOR_CCONV_FEED_ID].MaxLimit ) == SR_ERROR )
			return SR_ERROR;

		if(LConvFeedMotor.Wait()== SR_ERROR )
			return SR_ERROR;
		if(CConvFeedMotor.Wait()== SR_ERROR )
			return SR_ERROR;

	MACHINE_CONFIG_END
	return SR_OK;
}
int SRMachine::finishBoardLoading(){
	// Release camera piston
	MACHINE_CONFIG( MACHINE_ENABLE )
		if( SetOutput( OUTPUT_CAMERA_PISTON, false ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CAMPISTONERROR, MSG_ERROR );
			return SR_ERROR;
		}
		myMilliSleep( CAMPISTON_DELAY );

		// Move camera in home position
		if( MoveCameraAndWait( (DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit - DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit)/2, DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit, ABS_MOVE ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
			return SR_ERROR;
		}

//		// Check for input sensor
//		if( GetInput( INPUT_SENSOR_EXT ) == 1 ){
//			wxMessageBox( MSG_INPUTSECURITYSERROR, MACHINE_NAME, wxOK | wxICON_ERROR, parent );
//			return SR_ERROR;
//		}
//		MACHINE_CONFIG(CONV_PUSH_MOTOR)
//			if( GetInput( INPUT_SENSOR_INT ) == 1 ){
//				wxMessageBox( MSG_INPUTSECURITYSERROR, MACHINE_NAME, wxOK | wxICON_ERROR, parent );
//				return SR_ERROR;
//			}
//		MACHINE_CONFIG_END

		// Activate board lock
		if( SetOutput( OUTPUT_BOARDLOCK, true ) == SR_ERROR )
		{
			smartLogger->Write( MSG_BOARDLOCKERROR, MSG_ERROR );
			return SR_ERROR;
		}
	MACHINE_CONFIG_END

	isBoardLoaded = true;

	return SR_OK;
}

int SRMachine::UnloadBoard( int mode )
{
	if( !isBoardLoaded )
		return SR_OK;

	smartLogger->Write( MSG_UNLOADING );

	MACHINE_CONFIG( MACHINE_ENABLE )
		// Check for motors position
		if( CheckMotorsPos( CHECK_LOAD_POSITION ) == SR_ERROR )
			if( ResetMotors( MODE_LOAD_POSITION ) == SR_ERROR )
				return SR_ERROR;

		// Unlock board
		if( SetOutput( OUTPUT_BOARDLOCK, false ) == SR_ERROR )
		{
			smartLogger->Write( MSG_BOARDLOCKERROR, MSG_ERROR );
			return SR_ERROR;
		}
		myMilliSleep( LOCKPISTON_DELAY );

		// Move conveyors belts
		if( LConvFeedMotor.motor->Home() == SR_ERROR )
			return SR_ERROR;
		LConvFeedMotor.ResetPosition();
		if( CConvFeedMotor.motor->Home() == SR_ERROR )
			return SR_ERROR;
		CConvFeedMotor.ResetPosition();

		if( CConvFeedMotor.Move( DB->LimitsS[MOTOR_CCONV_FEED_ID].MinLimit ) == SR_ERROR )
			return SR_ERROR;
		if( LConvFeedMotor.Move( DB->LimitsS[MOTOR_LCONV_FEED_ID].MinLimit ) == SR_ERROR )
			return SR_ERROR;

		if((mode == CHECK_ENABLED) && DB->WorkingModesS.InputSensorEnabled ){
			if(WaitMotorAndCheckSensor(INPUT_SENSOR_EXT, &CConvFeedMotor) == MOTOR_OK_NO_SENSOR){
				if( SetAlarmLight(ALARMLIGHT_RED) == SR_ERROR ){
					smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
					return SR_ERROR;
				}
				int retval = wxMessageBox( MSG_INPUTSECURITYSERROR2, MACHINE_NAME, wxYES_NO | wxICON_ERROR, parent );

				if( SetAlarmLight(ALARMLIGHT_OFF) == SR_ERROR ){
					smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
					return SR_ERROR;
				}
				if(retval == wxNO){
					return SR_ERROR;
				}
			}
		}else {
			if(LConvFeedMotor.Wait()== SR_ERROR )
				return SR_ERROR;
			if(CConvFeedMotor.Wait()== SR_ERROR )
				return SR_ERROR;
		}

		isBoardLoaded = false;

		// Check for input sensor
		MACHINE_CONFIG(CONV_PUSH_MOTOR)
			if( GetInput( INPUT_SENSOR_INT ) == 1 ){
				wxMessageBox( MSG_INPUTSECURITYSERROR, MACHINE_NAME, wxOK | wxICON_ERROR, parent );
				return SR_ERROR;
			}
		MACHINE_CONFIG_END



		// If loader enabled...
		if( DB->MachineParamsS.LoaderInstalled && DB->WorkingModesS.LoaderEn )
		{
			// Activate conveyor piston
			// We suppose loader is ready to receive a board!
			convPusherEnabled(true);
			myMilliSleep( CONVPISTON_DELAY );
			convPusherEnabled(false);

			MACHINE_CONFIG(CONV_PUSH_MOTOR)
				if( GetInput( INPUT_SENSOR_EXT ) == 1 ){
					wxMessageBox( MSG_INPUTSECURITYSERROR, MACHINE_NAME, wxOK | wxICON_ERROR, parent );
					return SR_ERROR;
				}
			MACHINE_CONFIG_END

			//check is performed if sensor is placed outside the conveyor (and push is not present).
			MACHINE_CONFIG(EXTERNAL_CONV_SENSOR)
				if( GetInput( INPUT_SENSOR_EXT ) == 1 ){
					wxMessageBox( MSG_INPUTSECURITYSERROR, MACHINE_NAME, wxOK | wxICON_ERROR, parent );
					return SR_ERROR;
				}
			MACHINE_CONFIG_END

		}
	MACHINE_CONFIG_END

	return SR_OK;
}

int SRMachine::convPusherEnabled( bool state ){
	MACHINE_CONFIG(CONV_PUSH_MOTOR)
		double finalPos = state ? DB->LimitsS[MOTOR_LCONV_PUSH_ID].MaxLimit : 0;
		if(LConvPushMotor.MoveAndWait(finalPos, ABS_MOVE) == SR_ERROR){
			smartLogger->Write( MSG_CONVPISTONERROR, MSG_ERROR );
			return SR_ERROR;
		}
	MACHINE_CONFIG_ELSE
		if( SetOutput( OUTPUT_CONVEYOR_PISTON, state ) == SR_ERROR ){
			smartLogger->Write( MSG_CONVPISTONERROR, MSG_ERROR );
			return SR_ERROR;
		}
	MACHINE_CONFIG_END
	isConveyorPistonOn = state;
	return MOTOR_OK;
}

//---------------------------------------------------------------------------
//
// Name:        SRMachineLoader.cpp
// Author:      Daniele Belloni
// Created:     18/06/2015
// Description: SRMachine class implementation
//
//---------------------------------------------------------------------------
#include "SRMachine.h"
#include "GlobalEnum.h"
#include "GlobalUtils.h"
#include "Errors.h"


int SRMachine::SearchLoaderOrigin()
{
	int flag = DB->IOParamsS[INPUT_LOADERZERO].DriverPort + 1;

	// Set motor params

	// Set 0 sensor input
	if( LoaderMotor.motor->HomeSensorInput( flag ) == MOTOR_ERROR )
	{
		errorCode |= ERR_SETINPUT;
		return SR_ERROR;
	}

	// Set homing speeds
	if( LoaderMotor.motor->SetHomingSpeed( HOME_SLOW, DB->MotorParamsS[MOTOR_LOADER_ID].HomeSlow ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}
	if( LoaderMotor.motor->SetHomingSpeed( HOME_FAST, DB->MotorParamsS[MOTOR_LOADER_ID].HomeFast ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}

	if( LoaderMotor.motor->SetHomeSensorLevel( ZEROLEVEL_HIGH ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}

	// Set home movement
	double Resolution = LoaderMotor.GetResolution();
	long StepActPulse = myLRound(DB->LimitsS[MOTOR_LOADER_ID].MaxLimit / Resolution);

	if( LoaderMotor.motor->SetHomeMove( StepActPulse ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return MOTOR_ERROR;
	}

	// Start 0 search
	if( LoaderMotor.motor->SearchPos0( ZEROSEARCH_POS ) == SR_ERROR )
		return SR_ERROR;

	return SR_OK;
}

int SRMachine::SearchLoaderOrigin_Wait( wxProgressDialog *progressDialog, int value )
{
	int flag = true;

	while( flag )
	{
		::wxYield();
		if( progressDialog->Update( value ) == false )
			return SR_ERROR;

		flag = LoaderMotor.motor->MotorStatus();
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

int SRMachine::LoaderMove( int pos )
{
	if( pos != GetRackPos() )
	{
		if( (pos <= MAX_RACK_POS) && (pos >= MIN_RACK_POS) )
		{
			// Move the loader to start position
			if( LoaderMotor.MoveAndWait( DB->MachineParamsS.LoaderZeroMovement + DB->ProductionDataS.LoaderStartPos + (pos-1)*DB->ProductionDataS.LoaderTrayPitch, ABS_MOVE ) == SR_ERROR )
			{
				errorCode |= ERR_DRIVER;
				return SR_ERROR;
			}

			SetRackPos( pos );
		}
	}

	return SR_OK;
}

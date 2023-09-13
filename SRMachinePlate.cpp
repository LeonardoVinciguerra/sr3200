//---------------------------------------------------------------------------
//
// Name:        SRMachinePlate.cpp
// Author:      Gabriel Ferri
// Created:     08/05/2008
// Description: SRMachine class implementation
//
//---------------------------------------------------------------------------
#include "SRMachine.h"
#include "GlobalEnum.h"
#include "GlobalUtils.h"
#include "Errors.h"


int SRMachine::SearchPlateOrigin()
{
	int flag = DB->IOParamsS[INPUT_PLATEZERO].DriverPort + 1;

	// Set motor params

	// Set current (nominal current)
	if( PlateMotor.motor->SetNominalCurrent( DB->MotorParamsS[MOTOR_PLATE_ID].Current ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return MOTOR_ERROR;
	}

	// Set 0 sensor input
	if( PlateMotor.motor->HomeSensorInput( flag ) == MOTOR_ERROR )
	{
		errorCode |= ERR_SETINPUT;
		return SR_ERROR;
	}

	// Set homing speeds
	if( PlateMotor.motor->SetHomingSpeed( HOME_SLOW, _IQ24( DB->MotorParamsS[MOTOR_PLATE_ID].HomeSlow ) ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}
	if( PlateMotor.motor->SetHomingSpeed( HOME_FAST, _IQ24( DB->MotorParamsS[MOTOR_PLATE_ID].HomeFast ) ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}
	if( PlateMotor.motor->SetHomeSensorLevel( ZEROLEVEL_HIGH ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}

	// Start 0 search
	if( PlateMotor.motor->SearchPos0( ZEROSEARCH_POS ) == SR_ERROR )
		return SR_ERROR;

	return SR_OK;
}

int SRMachine::SearchPlateOrigin_Wait( wxProgressDialog *progressDialog, int value )
{
	int flag = true;
	while( flag )
	{
		::wxYield();
		if( progressDialog->Update( value ) == false )
			return SR_ERROR;

		flag = PlateMotor.motor->MotorStatus();
		if( (flag == MOTOR_ERROR) || (flag & MOTOR_PROCERROR) || (flag & MOTOR_OVERCURRENT) || (flag & MOTOR_NOENC) )
		{
			errorCode |= ERR_DRIVER;
			return SR_ERROR;
		}

		flag = flag & MOTOR_ZERO;

		myMilliSleep( MOTOR_STATUS_DELAY );
	}

	// Set reduced current as nominal current
	if( PlateMotor.motor->SetNominalCurrent( DB->MotorParamsS[MOTOR_PLATE_ID].RedCurrent ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return MOTOR_ERROR;
	}
	
	if( PlateMotor.motor->Home() == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return MOTOR_ERROR;
	}
	PlateMotor.ResetPosition();
	if( PlateMotor.EnableControlPID() == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return MOTOR_ERROR;
	}


	return SR_OK;
}

//---------------------------------------------------------------------------
//
// Name:        SRMachineSqueegees.cpp
// Author:      Gabriel Ferri
// Created:     08/05/2008
// Description: SRMachine class implementation
//
//---------------------------------------------------------------------------
#include "SRMachine.h"
#include "GlobalEnum.h"
#include "GlobalUtils.h"
#include "Errors.h"


int SRMachine::SearchSqueegeesOrigin()
{
	int flag = DB->IOParamsS[INPUT_SQUEEGEESZERO].DriverPort + 1;

	// Set motor params

	// Set current (nominal current)
	if( SqueegeesMotor.motor->SetNominalCurrent( DB->MotorParamsS[MOTOR_SQUEEGEES_ID].Current ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return MOTOR_ERROR;
	}
	
	// Set 0 sensor input
	if( SqueegeesMotor.motor->HomeSensorInput( flag ) == MOTOR_ERROR )
	{
		errorCode |= ERR_SETINPUT;
		return SR_ERROR;
	}

	// Set homing speeds
	if( SqueegeesMotor.motor->SetHomingSpeed( HOME_SLOW, _IQ24( DB->MotorParamsS[MOTOR_SQUEEGEES_ID].HomeSlow ) ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}
	if( SqueegeesMotor.motor->SetHomingSpeed( HOME_FAST, _IQ24( DB->MotorParamsS[MOTOR_SQUEEGEES_ID].HomeFast ) ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}
	if( SqueegeesMotor.motor->SetHomeSensorLevel( ZEROLEVEL_HIGH ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}

	// Start 0 search
	if( SqueegeesMotor.motor->SearchPos0( ZEROSEARCH_NEG ) == SR_ERROR )
		return SR_ERROR;

	return SR_OK;
}

int SRMachine::SearchSqueegeesOrigin_Wait( wxProgressDialog *progressDialog, int value )
{
	int flag = true;
	while( flag )
	{
		::wxYield();
		if( progressDialog->Update( value ) == false )
			return SR_ERROR;

		flag = SqueegeesMotor.motor->MotorStatus();
		if( (flag == MOTOR_ERROR) || (flag & MOTOR_PROCERROR) || (flag & MOTOR_OVERCURRENT)|| (flag & MOTOR_NOENC) )
		{
			errorCode |= ERR_DRIVER;
			return SR_ERROR;
		}

		flag = flag & MOTOR_ZERO;

		myMilliSleep( MOTOR_STATUS_DELAY );
	}
	
	// Set reduced current as nominal current
	if( SqueegeesMotor.motor->SetNominalCurrent( DB->MotorParamsS[MOTOR_SQUEEGEES_ID].RedCurrent ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return MOTOR_ERROR;
	}
	
	return SR_OK;
}
//---------------------------------------------------------------------------
//
// Name:        SRMachineCamera.cpp
// Author:      Gabriel Ferri
// Created:     08/05/2008
// Description: SRMachine class implementation
//
//---------------------------------------------------------------------------
#include "SRMachine.h"
#include "GlobalEnum.h"
#include "GlobalUtils.h"
#include "Errors.h"


int SRMachine::CheckCamera( double x, double y, int mode )
{
	if( CamXMotor.Check( x, mode ) == MOTOR_ERROR )
		return SR_ERROR;
	if( CamYMotor.Check( y, mode ) == MOTOR_ERROR )
		return SR_ERROR;
	return SR_OK;
}

int SRMachine::MoveCamera( double x, double y, int mode, int limit )
{
	if( limit == LIMIT_ON )
	{
		if( CamXMotor.Check( x, mode ) == MOTOR_ERROR )
		{
			return SR_ERROR;
		}
		if( CamYMotor.Check( y, mode ) == MOTOR_ERROR )
		{
			return SR_ERROR;
		}
	}
	if( CamXMotor.Move( x, mode, limit ) == MOTOR_ERROR )
	{
		smartLogger->Write( "Motor X Error", MSG_ERROR );
		return SR_ERROR;
	}
	if( CamYMotor.Move( y, mode, limit ) == MOTOR_ERROR )
	{
		smartLogger->Write( "Motor Y Error", MSG_ERROR );
		return SR_ERROR;
	}
	return SR_OK;
}


int SRMachine::WaitCamera()
{
	bool isError = false;
	if( CamXMotor.Wait() == MOTOR_ERROR )
		isError = true;
	if( CamYMotor.Wait() == MOTOR_ERROR )
		isError = true;
	return isError ? SR_ERROR : SR_OK;
}

int SRMachine::MoveCameraAndWait( double x, double y, int mode, int limit )
{
	if( MoveCamera( x, y, mode, limit ) == SR_ERROR )
		return SR_ERROR;
	if( WaitCamera() == SR_ERROR )
		return SR_ERROR;
	return SR_OK;
}

int SRMachine::GetCameraPosition( double &x, double &y )
{
	MACHINE_CONFIG( MACHINE_ENABLE )
		x = CamXMotor.GetPosition();
		y = CamYMotor.GetPosition();
	MACHINE_CONFIG_END

	return SR_OK;
}

int SRMachine::SearchCameraXOrigin()
{
	int flag = DB->IOParamsS[INPUT_CAMXZERO].DriverPort + 1;

	// Set motor params

	// Set current (nominal current)
	if( CamXMotor.motor->SetNominalCurrent( DB->MotorParamsS[MOTOR_CAMERAX_ID].Current ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return MOTOR_ERROR;
	}

	// Set 0 sensor input
	if( CamXMotor.motor->HomeSensorInput( flag ) == MOTOR_ERROR )
	{
		errorCode |= ERR_SETINPUT;
		return SR_ERROR;
	}

	// Set homing speeds
	if( CamXMotor.motor->SetHomingSpeed( HOME_SLOW, _IQ24( DB->MotorParamsS[MOTOR_CAMERAX_ID].HomeSlow ) ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}
	if( CamXMotor.motor->SetHomingSpeed( HOME_FAST, _IQ24( DB->MotorParamsS[MOTOR_CAMERAX_ID].HomeFast ) ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}
	if( CamXMotor.motor->SetHomeSensorLevel( ZEROLEVEL_HIGH ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}

	// Start 0 search
	if( CamXMotor.motor->SearchPos0( ZEROSEARCH_NEG ) == SR_ERROR )
		return SR_ERROR;

	return SR_OK;
}

int SRMachine::SearchCameraXOrigin_Wait( wxProgressDialog *progressDialog, int value )
{
	int flag = true;
	while( flag )
	{
		::wxYield();
		if( progressDialog->Update( value ) == false )
			return SR_ERROR;

		flag = CamXMotor.motor->MotorStatus();
		if( (flag == MOTOR_ERROR) || (flag & MOTOR_PROCERROR) || (flag & MOTOR_OVERCURRENT)|| (flag & MOTOR_NOENC) )
		{
			errorCode |= ERR_DRIVER;
			return SR_ERROR;
		}

		flag = flag & MOTOR_ZERO;

		myMilliSleep( MOTOR_STATUS_DELAY );
	}
	
	// Set reduced current as nominal current
	if( CamXMotor.motor->SetNominalCurrent( DB->MotorParamsS[MOTOR_CAMERAX_ID].RedCurrent ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return MOTOR_ERROR;
	}

	return SR_OK;
}

int SRMachine::SearchCameraYOrigin()
{
	int flag = DB->IOParamsS[INPUT_CAMYZERO].DriverPort + 1;

	// Set motor params

	// Set current (nominal current)
	if( CamYMotor.motor->SetNominalCurrent( DB->MotorParamsS[MOTOR_CAMERAY_ID].Current ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return MOTOR_ERROR;
	}

	// Set 0 sensor input
	if( CamYMotor.motor->HomeSensorInput( flag ) == MOTOR_ERROR )
	{
		errorCode |= ERR_SETINPUT;
		return SR_ERROR;
	}

	// Set homing speeds
	if( CamYMotor.motor->SetHomingSpeed( HOME_SLOW, _IQ24( DB->MotorParamsS[MOTOR_CAMERAY_ID].HomeSlow ) ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}
	if( CamYMotor.motor->SetHomingSpeed( HOME_FAST, _IQ24( DB->MotorParamsS[MOTOR_CAMERAY_ID].HomeFast ) ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}
	if( CamYMotor.motor->SetHomeSensorLevel( ZEROLEVEL_HIGH ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}

	// Start 0 search
	if( CamYMotor.motor->SearchPos0( ZEROSEARCH_NEG ) == SR_ERROR )
		return SR_ERROR;

	return SR_OK;
}

int SRMachine::SearchCameraYOrigin_Wait( wxProgressDialog *progressDialog, int value )
{
	int flag = true;
	while( flag )
	{
		::wxYield();
		if( progressDialog->Update( value ) == false )
			return SR_ERROR;

		flag = CamYMotor.motor->MotorStatus();
		if( (flag == MOTOR_ERROR) || (flag & MOTOR_PROCERROR) || (flag & MOTOR_OVERCURRENT)|| (flag & MOTOR_NOENC) )
		{
			errorCode |= ERR_DRIVER;
			return SR_ERROR;
		}

		flag = flag & MOTOR_ZERO;

		myMilliSleep( MOTOR_STATUS_DELAY );
	}
	
	// Set reduced current as nominal current
	if( CamYMotor.motor->SetNominalCurrent( DB->MotorParamsS[MOTOR_CAMERAY_ID].RedCurrent ) == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return MOTOR_ERROR;
	}

	return SR_OK;
}

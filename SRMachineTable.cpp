//---------------------------------------------------------------------------
//
// Name:        SRMachineTable.cpp
// Author:      Gabriel Ferri
// Created:     08/05/2008
// Description: SRMachine class implementation
//
//---------------------------------------------------------------------------
#include "SRMachine.h"
#include "GlobalEnum.h"
#include "GlobalUtils.h"
#include "Errors.h"
#include <math.h>


#define DIST_LIN				262.0		// Distance between Table1 and Table2 motors

//#define WAIT_RETRY				3


int SRMachine::RotateTableCheck( double deg )
{
	// SOLO MOVIMENTI RELATIVI
	double degInt = deg + ActRotTable;

	// Angle conversion to radians 
	double radMov = degInt / 360 * 2 * PI;

	double Cr = ( -DIST_LIN * tan(radMov) ) / 2;

	double C1 = ActPosXTable + Cr;
	double C2 = ActPosXTable - Cr;

	// C1 and C2 are already ABS positions

	// Check movements
	if( Table1Motor.Check( C1, ABS_MOVE ) == MOTOR_ERROR )
		return SR_ERROR;
	if( Table2Motor.Check( C2, ABS_MOVE ) == MOTOR_ERROR )
		return SR_ERROR;

	return SR_OK;
}

int SRMachine::RotateTable( double deg, int limit )
{
	MACHINE_CONFIG( MACHINE_ENABLE )
		// SOLO MOVIMENTI RELATIVI
		double degInt = deg + ActRotTable;
	
		// Angle conversion to radians
		double radMov = degInt / 360 * 2 * PI;
	
		double Cr = ( -DIST_LIN * tan(radMov) ) / 2;
	
		double C1 = ActPosXTable + Cr;
		double C2 = ActPosXTable - Cr;
	
		// C1 and C2 are already ABS positions
	
		if( limit == LIMIT_ON )
		{
			// Check movements
			if( Table1Motor.Check( C1, ABS_MOVE ) == MOTOR_ERROR )
				return SR_ERROR;
			if( Table2Motor.Check( C2, ABS_MOVE ) == MOTOR_ERROR )
				return SR_ERROR;
		}
	
		// Backlash recovery
		if( backlashRecover )
		{
			if( C1 < Table1Motor.GetPosition() )
			{
				if( Table1Motor.Move( MAX( C1 - backlashMm, DB->LimitsS[MOTOR_TABLE1_ID].MinLimit ), ABS_MOVE ) == SR_ERROR )
					return SR_ERROR;
			}
	
			if( C2 < Table2Motor.GetPosition() )
			{
				if( Table2Motor.Move( MAX( C2 - backlashMm, DB->LimitsS[MOTOR_TABLE2_ID].MinLimit ), ABS_MOVE ) == SR_ERROR )
					return SR_ERROR;
			}
	
			WaitTable();
		}
	
		// Motors movements
		if( Table1Motor.Move( C1, ABS_MOVE ) == SR_ERROR )
			return SR_ERROR;
		if( Table2Motor.Move( C2, ABS_MOVE ) == SR_ERROR )
			return SR_ERROR;
	
		// Actual table position update
		ActRotTable = degInt;
	MACHINE_CONFIG_END
	return SR_OK;
}

int SRMachine::MoveXYTableCheck( double x, double y )
{
	// SOLO MOVIMENTI RELATIVI
	double deltax = x;
	double deltay = y;

	// Angle conversion to radians 
	double rad = ActRotTable / 360 * 2 * PI;

	double Cx1 = ( deltax * cos(rad) + deltay * sin(rad) ) / cos(rad);
	double Cx2 = Cx1;
	double Cy = ( -deltax * sin(rad) + deltay * cos(rad) ) / cos(rad);

	// Compute ABS position
	Cx1 += Table1Motor.GetPosition();
	Cx2 += Table2Motor.GetPosition();
	Cy  += Table3Motor.GetPosition();

	// Check movements
	if( Table1Motor.Check( Cx1, ABS_MOVE ) == MOTOR_ERROR )
		return SR_ERROR;
	if( Table2Motor.Check( Cx2, ABS_MOVE ) == MOTOR_ERROR )
		return SR_ERROR;
	if( Table3Motor.Check( Cy, ABS_MOVE ) == MOTOR_ERROR )
		return SR_ERROR;

	return SR_OK;
}

int SRMachine::MoveXYTable( double x, double y, int limit )
{
	MACHINE_CONFIG( MACHINE_ENABLE )
		// SOLO MOVIMENTI RELATIVI
		double deltax = x;
		double deltay = y;
	
		// Angle conversion to radians 
		double rad = ActRotTable / 360 * 2 * PI;
	
		double Cx1 = ( deltax * cos(rad) + deltay * sin(rad) ) / cos(rad);
		double Cx2 = Cx1;
		double Cy = ( -deltax * sin(rad) + deltay * cos(rad) ) / cos(rad);
	
		// Compute ABS position
		Cx1 += Table1Motor.GetPosition();
		Cx2 += Table2Motor.GetPosition();
		Cy  += Table3Motor.GetPosition();
	
		if( limit == LIMIT_ON )
		{
			// Check movements
			if( Table1Motor.Check( Cx1, ABS_MOVE ) == MOTOR_ERROR )
				return SR_ERROR;
			if( Table2Motor.Check( Cx2, ABS_MOVE ) == MOTOR_ERROR )
				return SR_ERROR;
			if( Table3Motor.Check( Cy, ABS_MOVE ) == MOTOR_ERROR )
				return SR_ERROR;
		}
	
		// Backlash recovery
		if( backlashRecover )
		{
			if( Cx1 < Table1Motor.GetPosition() )
			{
				if( Table1Motor.Move( MAX( Cx1 - backlashMm, DB->LimitsS[MOTOR_TABLE1_ID].MinLimit ), ABS_MOVE ) == SR_ERROR )
					return SR_ERROR;
			}
	
			if( Cx2 < Table2Motor.GetPosition() )
			{
				if( Table2Motor.Move( MAX( Cx2 - backlashMm, DB->LimitsS[MOTOR_TABLE2_ID].MinLimit ), ABS_MOVE ) == SR_ERROR )
					return SR_ERROR;
			}
	
			if( Cy < Table3Motor.GetPosition() )
			{
				if( Table3Motor.Move( MAX( Cy - backlashMm, DB->LimitsS[MOTOR_TABLE3_ID].MinLimit ), ABS_MOVE ) == SR_ERROR )
					return SR_ERROR;
			}
			WaitTable();
		}
	
		// Motors movements
		if( Table1Motor.Move( Cx1, ABS_MOVE, limit ) == SR_ERROR )
			return SR_ERROR;
		if( Table2Motor.Move( Cx2, ABS_MOVE, limit ) == SR_ERROR )
			return SR_ERROR;
		if( Table3Motor.Move( Cy, ABS_MOVE, limit ) == SR_ERROR )
			return SR_ERROR;
	
		// Actual table position update
		ActPosXTable += deltax;
		ActPosYTable += deltay;
	MACHINE_CONFIG_END
	return SR_OK;
}

int SRMachine::ResetTable()
{
	MACHINE_CONFIG( MACHINE_ENABLE )
		if( backlashRecover )
		{
			if( Table1Motor.GetPosition() != 0 )
				if( Table1Motor.Move( -backlashMm, ABS_MOVE ) == SR_ERROR )
					return SR_ERROR;
			if( Table2Motor.GetPosition() != 0 )
				if( Table2Motor.Move( -backlashMm, ABS_MOVE ) == SR_ERROR )
					return SR_ERROR;
			if( Table3Motor.GetPosition() != 0 )
				if( Table3Motor.Move( -backlashMm, ABS_MOVE ) == SR_ERROR )
					return SR_ERROR;
			WaitTable();
		}

		if( Table1Motor.GetPosition() != 0 )
			if( Table1Motor.Move( 0, ABS_MOVE ) == SR_ERROR )
				return SR_ERROR;
		if( Table2Motor.GetPosition() != 0 )
			if( Table2Motor.Move( 0, ABS_MOVE ) == SR_ERROR )
				return SR_ERROR;
		if( Table3Motor.GetPosition() != 0 )
			if( Table3Motor.Move( 0, ABS_MOVE ) == SR_ERROR )
				return SR_ERROR;

		// General positions variables update
		ActPosXTable = 0;
		ActPosYTable = 0;
		ActRotTable = 0;
	MACHINE_CONFIG_END
	return SR_OK;
}

int SRMachine::WaitTable()
{
	bool isError = false;
	if( Table1Motor.Wait() == MOTOR_ERROR )
		isError = true;
	if( Table2Motor.Wait() == MOTOR_ERROR )
		isError = true;
	if( Table3Motor.Wait() == MOTOR_ERROR )
		isError = true;
	return isError ? SR_ERROR : SR_OK;
}

int SRMachine::RotateTableAndWait( double deg, int limit )
{
	if( RotateTable( deg, limit ) == SR_ERROR )
		return SR_ERROR;
	if( WaitTable() == SR_ERROR )
		return SR_ERROR;
	return SR_OK;
}

int SRMachine::MoveXYTableAndWait( double x, double y, int limit )
{
	if( MoveXYTable( x, y, limit ) == SR_ERROR )
		return SR_ERROR;
	if( WaitTable() == SR_ERROR )
		return SR_ERROR;
	return SR_OK;
}

void SRMachine::GetTablePosition( double &x, double &y, double &theta )
{
	x = ActPosXTable;
	y = ActPosYTable;
	theta = ActRotTable;
}

int SRMachine::SearchTableOrigin_1()
{
	backlashRecover = false;

	// Reset table motors
	if( MoveXYTable( 11, 11, LIMIT_OFF ) == SR_ERROR )
		return SR_ERROR;

	return SR_OK;
}

int SRMachine::SearchTableOrigin_2()
{
	// Set motors home
	if( Table1Motor.motor->Home() == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}
	if( Table2Motor.motor->Home() == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}
	if( Table3Motor.motor->Home() == MOTOR_ERROR )
	{
		errorCode |= ERR_DRIVER;
		return SR_ERROR;
	}

	// Move the motors to the zero position
	if( Table1Motor.Move( DB->MachineParamsS.TableZeroMovement1 - backlashMm, ABS_MOVE, LIMIT_OFF ) == SR_ERROR )
		return SR_ERROR;
	if( Table2Motor.Move( DB->MachineParamsS.TableZeroMovement2 - backlashMm, ABS_MOVE, LIMIT_OFF ) == SR_ERROR )
		return SR_ERROR;
	if( Table3Motor.Move( DB->MachineParamsS.TableZeroMovement3 - backlashMm, ABS_MOVE, LIMIT_OFF ) == SR_ERROR )
		return SR_ERROR;

	return SR_OK;
}

int SRMachine::SearchTableOrigin_3()
{
	// Move the motors to the zero position
	if( Table1Motor.Move( DB->MachineParamsS.TableZeroMovement1, ABS_MOVE, LIMIT_OFF ) == SR_ERROR )
		return SR_ERROR;
	if( Table2Motor.Move( DB->MachineParamsS.TableZeroMovement2, ABS_MOVE, LIMIT_OFF ) == SR_ERROR )
		return SR_ERROR;
	if( Table3Motor.Move( DB->MachineParamsS.TableZeroMovement3, ABS_MOVE, LIMIT_OFF ) == SR_ERROR )
		return SR_ERROR;

	backlashRecover = true;
	return SR_OK;
}

int SRMachine::SearchTableOrigin_Wait( wxProgressDialog *progressDialog, int value )
{
	return WaitTable();
}

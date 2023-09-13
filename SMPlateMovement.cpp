//---------------------------------------------------------------------------
//
// Name:        SMPlateMovement.cpp
// Author:      Gabriel Ferri
// Created:     05/09/2008 10.56
// Description: Plate movement - State Machine functions implementation
//
//---------------------------------------------------------------------------

#include "SMBase.h"
#include "wxCalibrationPanel.h"
#include <wx/msgdlg.h>
#include "Messages.h"

#define PANEL_PLATEMOV			PANEL_MOVE_DISABLE, PANEL_OUTPUT_LOCK
#define PANEL_PLATEMOV_PLATE	PANEL_MOVE_PLATE, PANEL_OUTPUT_LOCK
#define PANEL_DISABLE			PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE

//----------------------------------------------------------------------------------
// SMPlateMovementInitialize
// Inizializza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMPlateMovementInitialize()
{
	controlPanel->SetState( PANEL_PLATEMOV );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMPlateMovementFinalize
// Finalizza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMPlateMovementFinalize()
{
	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMPlateMovementReset
// Resetta la macchina a stati
//----------------------------------------------------------------------------------
void SMBase::SMPlateMovementReset()
{
	controlPanel->SetState( PANEL_PLATEMOV );

	wxCalibrationPanel *panel = (wxCalibrationPanel *)currentPanel;
	panel->Enable( true );
}

//----------------------------------------------------------------------------------
// SMPlateMovement
// Macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMPlateMovement( int nextState )
{
	datasette->StopEnable( false );
	datasette->NextEnable( false );
	datasette->PrevEnable( false );
	controlPanel->SetState( PANEL_DISABLE );

	currentState = nextState;
	wxCalibrationPanel *panel = (wxCalibrationPanel *)currentPanel;

	switch( currentState )
	{
		case PLATEMOVEMENT_STATE_INIT:
			panel->Enable( false );

			initCheck.cover			= false;
			initCheck.air			= true;
			initCheck.pcb			= false;
			initCheck.pcb_height	= 0;
			initCheck.frame			= true;
			initCheck.motors_pos	= true;
			initCheck.motor_state	= MODE_START_POSITION;

			if( SMInitCheck( initCheck ) == SR_ERROR )
				return SR_ERROR;

			// Move the board to reaches the frame
			if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.PlateMovement, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// sets controls state
			datasette->StopEnable( true );
			datasette->NextEnable( true );

			controlPanel->SetState( PANEL_PLATEMOV_PLATE );
			smartLogger->Write( MSG_PLATEMOVESTART );
			break;

		case PLATEMOVEMENT_STATE_RESET:
			// Check for motors position
			if( SR->CheckMotorsPos() == SR_ERROR )
			{
				if( SR->ResetMotors( MODE_START_POSITION ) == SR_ERROR )
				{
					return SR_ERROR;
				}
			}

			panel->Enable( true );
			toolBox->Enable( true );
			menuBtn->Enable( true );
			datasette->StartEnable( true );

			controlPanel->SetState( PANEL_PLATEMOV );
			break;

		case PLATEMOVEMENT_STATE_FINAL:
			// save plate movement
			SR->DB->MachineParamsS.PlateMovement = SR->PlateMotor.GetPosition();
			SR->DB->SaveMachineParams();

			smartLogger->Write( MSG_PLATEMOVEENDED, MSG_SUCCESS );
			if( SMPlateMovement( PLATEMOVEMENT_STATE_RESET ) == SR_ERROR )
				return SR_ERROR;
			break;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMPlateMovementNext
// Aggiorna lo stato dell SM
//----------------------------------------------------------------------------------
void SMBase::SMPlateMovementNext()
{
	retVal = SR_OK;

	switch( currentState )
	{
		case PLATEMOVEMENT_STATE_INIT:
			retVal = SMPlateMovement( PLATEMOVEMENT_STATE_FINAL );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

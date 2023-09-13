//---------------------------------------------------------------------------
//
// Name:        SMPins.cpp
// Author:      Daniele Belloni
// Created:     15/02/2016 11.23
// Description: Pins position - State Machine functions implementation
//
//---------------------------------------------------------------------------

#include "SMBase.h"
#include "wxProductionPanel.h"
#include <wx/msgdlg.h>
#include "GlobalUtils.h"
#include "Messages.h"

#define PANEL_PINS			PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE
#define PANEL_PINS_MOVE		PANEL_MOVE_CAMERA, PANEL_OUTPUT_LED_UP | PANEL_OUTPUT_LED_DOWN
#define PANEL_DISABLE		PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE

//----------------------------------------------------------------------------------
// SMPinsInitialize
// Inizializza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMPinsInitialize()
{
	mainVideo->ConnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );
	
	controlPanel->SetState( PANEL_PINS );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMPinsFinalize
// Finalizza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMPinsFinalize()
{
	mainVideo->DisconnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMPinsReset
// Resetta la macchina a stati
//----------------------------------------------------------------------------------
void SMBase::SMPinsReset()
{
	SR->CheckCover( false );

	wxProductionPanel *panel = (wxProductionPanel *)currentPanel;
	panel->Enable( true );
}

//----------------------------------------------------------------------------------
// SMPins
// Macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMPins( int nextState )
{
	retVal = SR_OK;

	datasette->StopEnable( false );
	datasette->NextEnable( false );
	datasette->PrevEnable( false );
	controlPanel->SetState( PANEL_DISABLE );

	currentState = nextState;
	wxProductionPanel *panel = (wxProductionPanel *)currentPanel;

	switch( currentState )
	{
		case PINS_STATE_INIT:
			panel->Enable( false );

			initCheck.cover			= false;
			initCheck.air			= true;
			initCheck.pcb			= false;
			initCheck.pcb_height	= 0;
			initCheck.frame			= false;
			initCheck.motors_pos	= true;
			initCheck.motor_state	= MODE_STARTPRINTING_POSITION;

			// If no pins points have been teached...
			if( SR->DB->ProductionDataS.PinsPointsNumber == 0 )
			{
				wxMessageBox( MSG_PINSNOPOINT, MACHINE_NAME, wxOK | wxICON_ERROR, parent );
				return SR_ERROR;
			}

			if( SMInitCheck( initCheck ) == SR_ERROR )
				return SR_ERROR;

			// Pins cycle can begin...

			// If there's a board inside the machine, unload it
			if( SR->UnloadBoard() == SR_ERROR )
			{
				smartLogger->Write( MSG_LOADERROR, MSG_ERROR );
				return SR_ERROR;
			}

			currentPinsPoint = 1;

			// Move the board to reaches the camera focus
			if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}
			// Enable camera
			if( SR->SetCamera( CAMERA_DOWN ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Start live video
			camera->SetMainMode( MAIN_CAMERA_CUR );
			camera->SetAuxMode( AUX_CAMPOSITION );
			camera->StartCapture();

			// Save actual camera speed and set low speed
			currentSpeed = SR->DB->MachineParamsS.CameraSpeed;
			SR->DB->MachineParamsS.CameraSpeed = 0;
			if( SR->CamXMotor.SetSpeedAcc() == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
				return SR_ERROR;
			}
			if( SR->CamYMotor.SetSpeedAcc() == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
				return SR_ERROR;
			}

			if( SMPins( PINS_STATE_CHECKCOVER ) == SR_ERROR )
				return SR_ERROR;
			break;

		case PINS_STATE_RESET:
			isMainVideoClickEnable = false;
			isAuxVideoClickEnable = false;

			// stop live video
			camera->StopCapture();
			camera->SetMainMode( MAIN_BLANK );
			camera->SetAuxMode( AUX_BLANK );

			// Disable camera
			if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			// Reset original camera speed
			SR->DB->MachineParamsS.CameraSpeed = currentSpeed;
			if( SR->CamXMotor.SetSpeedAcc() == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
				return SR_ERROR;
			}
			if( SR->CamYMotor.SetSpeedAcc() == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAINITERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Check for motors position
			if( SR->CheckMotorsPos() == SR_ERROR )
			{
				if( SR->ResetMotors( MODE_STARTPRINTING_POSITION ) == SR_ERROR )
				{
					return SR_ERROR;
				}
			}

			/*
			// Move the board outside the machine
			if( SR->UnloadBoard() == SR_ERROR )
			{
				smartLogger->Write( MSG_LOADERROR, MSG_ERROR );
				return SR_ERROR;
			}
			*/

			// draw empty workplace
			camera->DrawWorkplace();

			controlPanel->SetState( PANEL_PINS );

			panel->Enable( true );
			toolBox->Enable( true );
			menuBtn->Enable( true );
			datasette->StartEnable( true );
			datasette->StopEnable( false );
			datasette->NextEnable( false );
			datasette->PrevEnable( false );

			SR->CheckCover( false );
			break;

		case PINS_STATE_CHECKCOVER:
			if( SR->GetInput( INPUT_COVER ) == 0 )
			{
				smartLogger->Write( MSG_PINSCOVER, MSG_ERROR );

				if( SMPins( PINS_STATE_WAITCOVER ) == SR_ERROR )
					return SR_ERROR;
			}
			else
			{
				if( SMPins( PINS_STATE_SELECT ) == SR_ERROR )
					return SR_ERROR;
			}
			break;

		case PINS_STATE_WAITCOVER:
			datasette->StopEnable( true );
			datasette->NextEnable( true );

			break;

		case PINS_STATE_SELECT:
			smartLogger->Write( wxString::Format( MSG_PINSPOINT, currentPinsPoint) );

			// Move camera...
			if( SR->DB->PinsPointsS[currentPinsPoint-1].X != 0.0 || SR->DB->PinsPointsS[currentPinsPoint-1].Y != 0.0 )
			{
				// to pin point
				retVal = SR->MoveCamera( SR->DB->ProductionDataS.PCBPosX + SR->DB->PinsPointsS[currentPinsPoint-1].X, SR->DB->ProductionDataS.PCBPosY + SR->DB->ProductionDataS.PCBY - SR->DB->PinsPointsS[currentPinsPoint-1].Y, ABS_MOVE );
			}

			if( retVal == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Wait camera
			if( SR->WaitCamera() == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				return SR_ERROR;
			}

			//controlPanel->SetState( PANEL_PINS_MOVE );
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			datasette->PrevEnable( currentPinsPoint != 1 );
			// enable mouse click
			isAuxVideoClickEnable = true;
			break;

		case PINS_STATE_SELECT_NEXT:
			if( currentPinsPoint < NUM_PINS_POINTS && currentPinsPoint < SR->DB->ProductionDataS.PinsPointsNumber )
			{
				currentPinsPoint++;
				if( SMPins( PINS_STATE_CHECKCOVER ) == SR_ERROR )
					return SR_ERROR;
			}
			else
			{
				// Save pins point
				SR->DB->SavePinsPoints();

				smartLogger->Write( MSG_PINSENDED, MSG_SUCCESS );

				if( SMPins( PINS_STATE_RESET ) == SR_ERROR )
					return SR_ERROR;
			}
			break;

		case PINS_STATE_SELECT_PREV:
			currentPinsPoint--;
			if( SMPins( PINS_STATE_CHECKCOVER ) == SR_ERROR )
				return SR_ERROR;
			break;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMPinsNext
// Aggiorna lo stato dell SM
//----------------------------------------------------------------------------------
void SMBase::SMPinsNext()
{
	retVal = SR_OK;

	switch( currentState )
	{
		case PINS_STATE_WAITCOVER:
			retVal = SMPins( PINS_STATE_CHECKCOVER );
			break;

		case PINS_STATE_SELECT:
			retVal = SMPins( PINS_STATE_SELECT_NEXT );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

//----------------------------------------------------------------------------------
// SMPinsPrev
// Aggiorna lo stato dell SM
//----------------------------------------------------------------------------------
void SMBase::SMPinsPrev()
{
	retVal = SR_OK;

	switch( currentState )
	{
		case PINS_STATE_SELECT:
			retVal = SMPins( PINS_STATE_SELECT_PREV );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

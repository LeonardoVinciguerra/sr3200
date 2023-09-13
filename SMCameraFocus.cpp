//---------------------------------------------------------------------------
//
// Name:        SMCameraFocus.cpp
// Author:      Gabriel Ferri
// Created:     20/05/2008 16.35
// Description: Camera focus - State Machine functions implementation
//
//---------------------------------------------------------------------------

#include "SMBase.h"
#include "wxCalibrationPanel.h"
#include <wx/msgdlg.h>
#include "Messages.h"

#define PANEL_CAMERAFOCUS		PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE
#define PANEL_CAMERAFOCUS_MOVE	PANEL_MOVE_PLATE | PANEL_MOVE_CAMERA, PANEL_OUTPUT_NONE
#define PANEL_DISABLE			PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE

//----------------------------------------------------------------------------------
// SMCameraFocusInitialize
// Inizializza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMCameraFocusInitialize()
{
	mainVideo->ConnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );

	controlPanel->SetState( PANEL_CAMERAFOCUS );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMCameraFocusFinalize
// Finalizza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMCameraFocusFinalize()
{
	mainVideo->DisconnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMCameraFocusReset
// Resetta la macchina a stati
//----------------------------------------------------------------------------------
void SMBase::SMCameraFocusReset()
{
	controlPanel->SetState( PANEL_CAMERAFOCUS );

	wxCalibrationPanel *panel = (wxCalibrationPanel *)currentPanel;
	panel->Enable( true );
}

//----------------------------------------------------------------------------------
// SMCameraFocus
// Macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMCameraFocus( int nextState )
{
	datasette->StopEnable( false );
	datasette->NextEnable( false );
	datasette->PrevEnable( false );
	controlPanel->SetState( PANEL_DISABLE );

	currentState = nextState;
	wxCalibrationPanel *panel = (wxCalibrationPanel *)currentPanel;

	switch( currentState )
	{
		case CAMERAFOCUS_STATE_INIT:
			panel->Enable( false );

			initCheck.cover			= false;
			initCheck.air			= true;
			initCheck.pcb			= false;
			initCheck.pcb_height	= 0;
			initCheck.frame			= false;
			initCheck.motors_pos	= true;
			initCheck.motor_state	= MODE_START_POSITION;

			if( SMInitCheck( initCheck ) == SR_ERROR )
				return SR_ERROR;

			// Move the board to reaches the camera focus (the one saved in DB)
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
			camera->SetMainMode( MAIN_NO_CUR );
			camera->StartCapture();

			// enable mouse click
			isAuxVideoClickEnable = true;

			// sets controls state
			datasette->StopEnable( true );
			datasette->NextEnable( true );

			controlPanel->SetState( PANEL_CAMERAFOCUS_MOVE );
			smartLogger->Write( MSG_CAMERAFOCUSSTART );
			break;

		case CAMERAFOCUS_STATE_RESET:			
			// disable mouse click
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

			controlPanel->SetState( PANEL_CAMERAFOCUS );
			break;

		case CAMERAFOCUS_STATE_FINAL:
			// save camera focus
			SR->DB->MachineParamsS.CameraFocus = SR->PlateMotor.GetPosition();
			SR->DB->SaveMachineParams();

			smartLogger->Write( MSG_CAMERAFOCUSENDED, MSG_SUCCESS );
			if( SMCameraFocus( CAMERAFOCUS_STATE_RESET ) == SR_ERROR )
				return SR_ERROR;
			break;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMCameraFocusNext
// Aggiorna lo stato dell SM
//----------------------------------------------------------------------------------
void SMBase::SMCameraFocusNext()
{
	retVal = SR_OK;

	switch( currentState )
	{
		case CAMERAFOCUS_STATE_INIT:
			retVal = SMCameraFocus( CAMERAFOCUS_STATE_FINAL );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

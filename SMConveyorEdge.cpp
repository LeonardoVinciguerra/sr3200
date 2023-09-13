//---------------------------------------------------------------------------
//
// Name:        SMConveyorEdge.cpp
// Author:      Daniele Belloni
// Created:     25/06/2015
// Description: Conveyor Edge - State Machine functions implementation
//
//---------------------------------------------------------------------------

#include "SMBase.h"
#include "wxCalibrationPanel.h"
#include <wx/msgdlg.h>
#include "Messages.h"

#define PANEL_CONVEDGE			PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE
#define PANEL_CONVEDGE_MOVE		PANEL_MOVE_CAMERA, PANEL_OUTPUT_NONE
#define PANEL_DISABLE			PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE

//----------------------------------------------------------------------------------
// SMConveyorEdgeInitialize
// Inizializza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMConveyorEdgeInitialize()
{
	mainVideo->ConnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );

	controlPanel->SetState( PANEL_CONVEDGE );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMConveyorEdgeFinalize
// Finalizza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMConveyorEdgeFinalize()
{
	mainVideo->DisconnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMConveyorEdgeReset
// Resetta la macchina a stati
//----------------------------------------------------------------------------------
void SMBase::SMConveyorEdgeReset()
{
	controlPanel->SetState( PANEL_CONVEDGE );

	wxCalibrationPanel *panel = (wxCalibrationPanel *)currentPanel;
	panel->Enable( true );
}

//----------------------------------------------------------------------------------
// SMConveyorEdge
// Macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMConveyorEdge( int nextState )
{
	datasette->StopEnable( false );
	datasette->NextEnable( false );
	datasette->PrevEnable( false );
	controlPanel->SetState( PANEL_DISABLE );

	currentState = nextState;
	wxCalibrationPanel *panel = (wxCalibrationPanel *)currentPanel;

	switch( currentState )
	{
		case CONVEDGE_STATE_INIT:
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

			// Move the conveyor to reach the camera focus (the one saved in DB)
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
			camera->StartCapture();

			// enable mouse click
			isAuxVideoClickEnable = true;

			// sets controls state
			datasette->StopEnable( true );
			datasette->NextEnable( true );

			controlPanel->SetState( PANEL_CONVEDGE_MOVE );
			smartLogger->Write( MSG_CONVEDGESTART );
			break;

		case CONVEDGE_STATE_RESET:
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

			controlPanel->SetState( PANEL_CONVEDGE );
			break;

		case CONVEDGE_STATE_FINAL:
			// save edge values
			SR->DB->MachineParamsS.ConvEdgeX = SR->CamXMotor.GetPosition();
			SR->DB->MachineParamsS.ConvEdgeY = SR->CamYMotor.GetPosition();
			SR->DB->SaveMachineParams();

			smartLogger->Write( MSG_CONVEDGEENDED, MSG_SUCCESS );
			if( SMConveyorEdge( CONVEDGE_STATE_RESET ) == SR_ERROR )
				return SR_ERROR;
			break;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMConveyorEdgeNext
// Aggiorna lo stato dell SM
//----------------------------------------------------------------------------------
void SMBase::SMConveyorEdgeNext()
{
	retVal = SR_OK;

	switch( currentState )
	{
		case CONVEDGE_STATE_INIT:
			retVal = SMConveyorEdge( CONVEDGE_STATE_FINAL );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

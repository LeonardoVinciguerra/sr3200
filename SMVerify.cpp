//---------------------------------------------------------------------------
//
// Name:        SMVerify.cpp
// Author:      Gabriel Ferri
// Created:     20/05/2008 11.23
// Description: Verify - State Machine functions implementation
//
//---------------------------------------------------------------------------

#include "SMBase.h"
#include "wxProductionPanel.h"
#include <wx/msgdlg.h>
#include "GlobalUtils.h"
#include "Messages.h"

#define PANEL_VERIFY		PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE
#define PANEL_VERIFY_MOVE	PANEL_MOVE_CAMERA, PANEL_OUTPUT_LED_UP | PANEL_OUTPUT_LED_DOWN
#define PANEL_DISABLE		PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE

//----------------------------------------------------------------------------------
// SMVerifyInitialize
// Inizializza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMVerifyInitialize()
{
	mainVideo->ConnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );
	
	controlPanel->SetState( PANEL_VERIFY );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMVerifyFinalize
// Finalizza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMVerifyFinalize()
{
	mainVideo->DisconnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMVerifyReset
// Resetta la macchina a stati
//----------------------------------------------------------------------------------
void SMBase::SMVerifyReset()
{
	SR->CheckCover( false );

	wxProductionPanel *panel = (wxProductionPanel *)currentPanel;
	panel->Enable( true );
}

//----------------------------------------------------------------------------------
// SMVerify
// Macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMVerify( int nextState )
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
		case VERIFY_STATE_INIT:
			// check if there are some points to verify
			if( SR->DB->WorkingModesS.PrintingVerify == 0 )
			{
				wxMessageBox( MSG_NOVERIFYPOINTS, MACHINE_NAME, wxOK | wxICON_QUESTION, parent );
				return SR_ERROR;
			}

			panel->Enable( false );

			initCheck.cover			= true;
			initCheck.air			= true;
			initCheck.pcb			= false;
			initCheck.pcb_height	= 0;
			initCheck.frame			= false;
			initCheck.motors_pos	= true;
			initCheck.motor_state	= MODE_STARTPRINTING_POSITION;

			if( SMInitCheck( initCheck ) == SR_ERROR )
				return SR_ERROR;

			// Verify cycle can begin...
			// Move the board inside the machine
			if( LoadBoardCameraCheck() == SR_ERROR )
			{
				smartLogger->Write( MSG_LOADERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// draw board
			if( SR->DB->ProductionDataS.PCBPosX != 0.0 )
				camera->DrawWorkplace( SR->DB->ProductionDataS.PCBPosX, SR->DB->ProductionDataS.PCBPosY, SR->DB->ProductionDataS.PCBX, SR->DB->ProductionDataS.PCBY );

			currentVerifyPoint = 1;
			if( SMVerify( VERIFY_STATE_VERIFY ) == SR_ERROR )
				return SR_ERROR;
			break;

		case VERIFY_STATE_RESET:
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
				if( SR->ResetMotors( MODE_STARTPRINTING_POSITION ) == SR_ERROR )
				{
					return SR_ERROR;
				}
			}
			// Move the board outside the machine
			if( SR->UnloadBoard() == SR_ERROR )
			{
				smartLogger->Write( MSG_LOADERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// draw empty workplace
			camera->DrawWorkplace();

			controlPanel->SetState( PANEL_VERIFY );

			panel->Enable( true );
			toolBox->Enable( true );
			menuBtn->Enable( true );
			datasette->StartEnable( true );

			SR->CheckCover( false );
			break;

		case VERIFY_STATE_VERIFY:
			smartLogger->Write( wxString::Format( MSG_VERIFYPOINT, currentVerifyPoint) );

			// Move camera...
			if( SR->DB->VerifyPointsS[currentVerifyPoint-1].X != 0.0 || SR->DB->VerifyPointsS[currentVerifyPoint-1].Y != 0.0 )
			{
				// to verify point
				retVal = SR->MoveCamera( SR->DB->ProductionDataS.PCBPosX + SR->DB->VerifyPointsS[currentVerifyPoint-1].X, SR->DB->ProductionDataS.PCBPosY + SR->DB->VerifyPointsS[currentVerifyPoint-1].Y, ABS_MOVE );
			}
			else
			{
				if( currentVerifyPoint == 1 )
				{
					// this is the first fiducial then move to the pcb center position
					retVal = SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX + SR->DB->ProductionDataS.PCBX/2.0f, SR->DB->ProductionDataS.PCBPosY + SR->DB->ProductionDataS.PCBY/2.0f, ABS_MOVE );
				}
			}
			if( retVal == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				return SR_ERROR;
			}

			if( currentVerifyPoint == 1 )
			{
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
			}

			// Wait camera
			if( SR->WaitCamera() == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				return SR_ERROR;
			}

			controlPanel->SetState( PANEL_VERIFY_MOVE );
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			datasette->PrevEnable( currentVerifyPoint != 1 );
			// enable mouse click
			isAuxVideoClickEnable = true;
			break;

		case VERIFY_STATE_VERIFY_NEXT:
			SR->GetCameraPosition( SR->DB->VerifyPointsS[currentVerifyPoint-1].X, SR->DB->VerifyPointsS[currentVerifyPoint-1].Y );

			// check points
			SR->DB->VerifyPointsS[currentVerifyPoint-1].X = MID( SR->DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit, SR->DB->VerifyPointsS[currentVerifyPoint-1].X, SR->DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit );
			SR->DB->VerifyPointsS[currentVerifyPoint-1].Y = MID( SR->DB->LimitsS[MOTOR_CAMERAY_ID].MinLimit, SR->DB->VerifyPointsS[currentVerifyPoint-1].Y, SR->DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit );
			
			// refers position to the PCB origin
			SR->DB->VerifyPointsS[currentVerifyPoint-1].X -= SR->DB->ProductionDataS.PCBPosX;
			SR->DB->VerifyPointsS[currentVerifyPoint-1].Y -= SR->DB->ProductionDataS.PCBPosY;

			if( currentVerifyPoint < NUM_VERIFY_POINTS && currentVerifyPoint <= SR->DB->WorkingModesS.PrintingVerify ) //<= perche 0 equivale ad un sito d'ispezione
			{
				currentVerifyPoint++;
				if( SMVerify( VERIFY_STATE_VERIFY ) == SR_ERROR )
					return SR_ERROR;
			}
			else
			{
				// Save verify point
				SR->DB->SaveVerifyPoints();

				smartLogger->Write( MSG_VERIFYENDED, MSG_SUCCESS );

				if( SMVerify( VERIFY_STATE_RESET ) == SR_ERROR )
					return SR_ERROR;
			}
			break;

		case VERIFY_STATE_VERIFY_PREV:
			SR->GetCameraPosition( SR->DB->VerifyPointsS[currentVerifyPoint-1].X, SR->DB->VerifyPointsS[currentVerifyPoint-1].Y );

			// check points
			SR->DB->VerifyPointsS[currentVerifyPoint-1].X = MID( SR->DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit, SR->DB->VerifyPointsS[currentVerifyPoint-1].X, SR->DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit );
			SR->DB->VerifyPointsS[currentVerifyPoint-1].Y = MID( SR->DB->LimitsS[MOTOR_CAMERAY_ID].MinLimit, SR->DB->VerifyPointsS[currentVerifyPoint-1].Y, SR->DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit );
			
			// refers position to the PCB origin
			SR->DB->VerifyPointsS[currentVerifyPoint-1].X -= SR->DB->ProductionDataS.PCBPosX;
			SR->DB->VerifyPointsS[currentVerifyPoint-1].Y -= SR->DB->ProductionDataS.PCBPosY;

			currentVerifyPoint--;
			if( SMVerify( VERIFY_STATE_VERIFY ) == SR_ERROR )
				return SR_ERROR;
			break;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMVerifyNext
// Aggiorna lo stato dell SM
//----------------------------------------------------------------------------------
void SMBase::SMVerifyNext()
{
	retVal = SR_OK;

	switch( currentState )
	{
		case VERIFY_STATE_VERIFY:
			retVal = SMVerify( VERIFY_STATE_VERIFY_NEXT );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

//----------------------------------------------------------------------------------
// SMVerifyPrev
// Aggiorna lo stato dell SM
//----------------------------------------------------------------------------------
void SMBase::SMVerifyPrev()
{
	retVal = SR_OK;

	switch( currentState )
	{
		case VERIFY_STATE_VERIFY:
			retVal = SMVerify( VERIFY_STATE_VERIFY_PREV );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

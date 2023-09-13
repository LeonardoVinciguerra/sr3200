//---------------------------------------------------------------------------
//
// Name:        SMVision.cpp
// Author:      Gabriel Ferri
// Created:     02/10/2008 17.31
// Description: Vision - State Machine functions implementation
//
//---------------------------------------------------------------------------

#include "SMBase.h"
#include "wxVisionPanel.h"
#include "Messages.h"

#define PANEL_VISION		PANEL_MOVE_DISABLE, PANEL_OUTPUT_LOCK | PANEL_OUTPUT_LED_UP | PANEL_OUTPUT_LED_DOWN
#define PANEL_VISION_CAMERA PANEL_MOVE_CAMERA, PANEL_OUTPUT_LOCK | PANEL_OUTPUT_LED_UP | PANEL_OUTPUT_LED_DOWN
#define PANEL_DISABLE		PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE

//----------------------------------------------------------------------------------
// SMVisionInitialize
// Inizializza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMVisionInitialize()
{
	mainVideo->ConnectMainVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMVisionMainVideoLeftClick ), this );
	mainVideo->ConnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );

	controlPanel->SetState( PANEL_VISION );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMVisionFinalize
// Finalizza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMVisionFinalize()
{
	mainVideo->DisconnectMainVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMVisionMainVideoLeftClick ), this );
	mainVideo->DisconnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMVisionReset
// Resetta la macchina a stati
//----------------------------------------------------------------------------------
void SMBase::SMVisionReset()
{
	controlPanel->SetState( PANEL_VISION );
}

//----------------------------------------------------------------------------------
// SMVision
// Macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMVision( int nextState )
{
	datasette->StopEnable( false );
	datasette->NextEnable( false );
	datasette->PrevEnable( false );
	controlPanel->SetState( PANEL_DISABLE );

	currentState = nextState;
	wxVisionPanel *panel = (wxVisionPanel *)currentPanel;

	switch( currentState )
	{
		case VISION_STATE_INIT:
			initCheck.cover			= true;
			initCheck.air			= true;
			initCheck.pcb			= false;
			initCheck.pcb_height	= 0;
			initCheck.frame			= false;
			initCheck.motors_pos	= true;
			initCheck.motor_state	= MODE_START_POSITION;

			if( SMInitCheck( initCheck ) == SR_ERROR )
				return SR_ERROR;

			// Move the board to reaches the camera focus
			if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}
			// Move camera to reach the workplace center position
			if( SR->MoveCameraAndWait( WORKPLACE_CENTER_X, WORKPLACE_CENTER_Y, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				return SR_ERROR;
			}
			// Enable camera
			if( SR->SetCamera( CAMERA_DOWN ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				return SR_ERROR;
			}

			if( SMVision( VISION_STATE_MOVE ) == SR_ERROR )
				return SR_ERROR;
			break;

		case VISION_STATE_MOVE:
			camera->SetMainMode( MAIN_CAMERA_MOVE );
			camera->SetAuxMode( AUX_CAMPOSITION );
			camera->StartCapture();

			controlPanel->SetState( PANEL_VISION_CAMERA );

			isMainVideoClickEnable = false;
			isAuxVideoClickEnable = true;

			smartLogger->Write( MSG_ALIGNMOVENEXTPOINT );

			datasette->StopEnable( true );
			datasette->NextEnable( true );
			break;

		case VISION_STATE_TEACH:
			camera->SetAuxMode( AUX_SMOOTH_EDGE );
			camera->SetMainMode( MAIN_MOUSE_CUR );
			camera->StartCapture();

			controlPanel->SetState( PANEL_DISABLE );
			isMainVideoClickEnable = true;

			smartLogger->Write( MSG_CLICKFIDUCIAL );

			datasette->StopEnable( true );
			datasette->PrevEnable( true );
			break;

		case VISION_STATE_SEARCH:
			camera->SetMainMode( MAIN_NO_CUR );
			camera->GetFrames( MAX_FRAMES_FIDUCIAL );
			camera->StopCapture();

			isMainVideoClickEnable = false;

			// Get current camera coords and offset
			SR->GetCameraPosition( camPos.X, camPos.Y );
			SR->GetOffset( camPos.X, camPos.Y, offsetX, offsetY );

			// Call function to search the fiducial...
			if( SR->DB->pCurrentFiducial->SearchMode == SEARCH_MODE_CIRCLE )
			{
				if( camera->FindCircle2( xClicked, yClicked, centerX, centerY, circleR ) == SR_OK )
				{
					smartLogger->Write( wxString::Format( MSG_FIDFOUND_CIRCLE, centerX, centerY, circleR ) );
					smartLogger->Write( wxString::Format( "Cam pos: (%5.3f, %5.3f) - Offset: (%5.3f, %5.3f)", camPos.X, camPos.Y, offsetX, offsetY ) );
					smartLogger->Write( wxString::Format( "Fiducial pos if on PCB: (%5.3f, %5.3f)", camPos.X + (centerX - CAM_W / 2) * SR->DB->MachineParamsS.DnXPixMm, camPos.Y - (centerY - CAM_H / 2) * SR->DB->MachineParamsS.DnYPixMm ) );
					smartLogger->Write( wxString::Format( "Fiducial pos if on stencil: (%5.3f, %5.3f)", camPos.X + (centerX - CAM_W / 2) * SR->DB->MachineParamsS.UpXPixMm, camPos.Y - (centerY - CAM_H / 2) * SR->DB->MachineParamsS.UpYPixMm ) );

					datasette->StopEnable( true );
					datasette->NextEnable( true );
					break;
				}
			}
			else if( SR->DB->pCurrentFiducial->SearchMode == SEARCH_MODE_RECTANGLE )
			{
				if( camera->FindRectangle( xClicked, yClicked, centerX, centerY, rectangleX, rectangleY ) == SR_OK )
				{
					smartLogger->Write( wxString::Format( MSG_FIDFOUND_RECT, centerX, centerY, rectangleX, rectangleY ) );
					smartLogger->Write( wxString::Format( "Cam pos: (%5.3f, %5.3f) - Offset: (%5.3f, %5.3f)", camPos.X, camPos.Y, offsetX, offsetY ) );
					smartLogger->Write( wxString::Format( "Fiducial pos if on PCB: (%5.3f, %5.3f)", camPos.X + (centerX - CAM_W / 2) * SR->DB->MachineParamsS.DnXPixMm, camPos.Y - (centerY - CAM_H / 2) * SR->DB->MachineParamsS.DnYPixMm ) );
					smartLogger->Write( wxString::Format( "Fiducial pos if on stencil: (%5.3f, %5.3f)", camPos.X + (centerX - CAM_W / 2) * SR->DB->MachineParamsS.UpXPixMm, camPos.Y - (centerY - CAM_H / 2) * SR->DB->MachineParamsS.UpYPixMm ) );

					datasette->StopEnable( true );
					datasette->NextEnable( true );
					break;
				}
			}

			// Fiducial not found
			smartLogger->Write( MSG_FIDNOTFOUND, MSG_ERROR );
			if( SMVision( VISION_STATE_TEACH ) == SR_ERROR )
				return SR_ERROR;
			break;

		case VISION_STATE_RESET:
			// stop live video
			camera->StopCapture();
			camera->SetMainMode( MAIN_BLANK );
			camera->SetAuxMode( AUX_BLANK );

			// disable mouse click
			isMainVideoClickEnable = false;
			isAuxVideoClickEnable = false;

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

			toolBox->Enable( true );
			menuBtn->Enable( true );
			datasette->StartEnable( true );

			controlPanel->SetState( PANEL_VISION );
			break;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMVisionNext
// Aggiorna lo stato dell SM
//----------------------------------------------------------------------------------
void SMBase::SMVisionNext()
{
	retVal = SR_OK;

	switch( currentState )
	{
		case VISION_STATE_MOVE:
			retVal = SMVision( VISION_STATE_TEACH );
			break;

		case VISION_STATE_TEACH:
		case VISION_STATE_SEARCH:
			retVal = SMVision( VISION_STATE_MOVE );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

//----------------------------------------------------------------------------------
// SMVisionPrev
// Aggiorna lo stato dell SM
//----------------------------------------------------------------------------------
void SMBase::SMVisionPrev()
{
	retVal = SR_OK;

	switch( currentState )
	{
		case VISION_STATE_TEACH:
			retVal = SMVision( VISION_STATE_MOVE );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

//----------------------------------------------------------------------------------
// SMVisionMainVideoLeftClick
// 
//----------------------------------------------------------------------------------
void SMBase::SMVisionMainVideoLeftClick( wxMouseEvent& e )
{
	retVal = SR_OK;

	if( !isMainVideoClickEnable )
		return;

	switch( currentState )
	{
		case VISION_STATE_TEACH:
			// Cursor position
			camera->GetCursorPositionMain( xClicked, yClicked );

			retVal = SMVision( VISION_STATE_SEARCH );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

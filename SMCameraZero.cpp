#include "SMBase.h"
#include "wxProductionPanel.h"
#include <wx/msgdlg.h>
#include "GlobalUtils.h"
#include "Messages.h"
#include "wxAlignmentTypeDialog.h"

#define PANEL_ALIGNMENT			PANEL_MOVE_DISABLE, PANEL_OUTPUT_LOCK
#define PANEL_CAMERA_VERIFY		PANEL_MOVE_CAMERA, PANEL_OUTPUT_LED_UP | PANEL_OUTPUT_LED_DOWN
#define PANEL_TEACH_SQUEEGEES	PANEL_MOVE_SQUEEGEES, PANEL_OUTPUT_FRONT_S | PANEL_OUTPUT_REAR_S
#define PANEL_DISABLE			PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE

int SMBase::SMCameraZeroInitialize()
{
	mainVideo->ConnectMainVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMCameraZeroMainVideoLeftClick ), this );
	mainVideo->ConnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );
	mainVideo->ConnectMainVideoKeyEvent( wxEVT_CHAR, wxStaticCastEvent( wxCharEventFunction, &SMBase::SMMainVideoKeyPress ), this );
	controlPanel->SetState( PANEL_ALIGNMENT );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMCameraZeroFinalize
// Finalizza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMCameraZeroFinalize()
{
	mainVideo->DisconnectMainVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMCameraZeroMainVideoLeftClick ), this );
	mainVideo->DisconnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );
	mainVideo->DisconnectMainVideoKeyEvent( wxEVT_CHAR, wxStaticCastEvent( wxCharEventFunction, &SMBase::SMMainVideoKeyPress ), this );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMCameraZeroReset
// Resetta la macchina a stati
//----------------------------------------------------------------------------------
void SMBase::SMCameraZeroReset()
{
	SR->CheckCover( false );

	controlPanel->SetState( PANEL_ALIGNMENT );

	// avoid to save not congruent data

	wxProductionPanel *panel = (wxProductionPanel *)currentPanel;
	panel->ShowTemplatePanel( false );
	panel->ShowManualCheck( false );
	panel->ShowFiducialButton( true );
	panel->ShowAlignmentPanel( false );
}

//----------------------------------------------------------------------------------
// SMCameraZero
// Macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMCameraZero( int nextState )
{
	retVal = SR_OK;

	datasette->StopEnable( false );
	datasette->NextEnable( false );
	datasette->PrevEnable( false );
	controlPanel->SetState( PANEL_DISABLE );

	currentState = nextState;
	wxProductionPanel *panel = (wxProductionPanel *)currentPanel;
	panel->EnableAlignmentPanel( false );

	switch( currentState )
	{
		//----------------------------------------------------------------------------------
		case CAMERAZERO_STATE_INIT0:
			initCheck.cover			= true;
			initCheck.air			= true;
			initCheck.pcb			= false;
			initCheck.pcb_height	= 0;
			initCheck.frame			= true;
			initCheck.motors_pos	= true;
			initCheck.motor_state	= MODE_START_POSITION;

			if( SMInitCheck( initCheck ) == SR_ERROR )
				return SR_ERROR;

			panel->ShowFiducialButton( false );

			camera->EnableRightClickOnMain( true );
			camera->EnableWheelOnMain( true );
			//break;

		//----------------------------------------------------------------------------------
		case CAMERAZERO_STATE_INIT:

			// Move the board to reaches the camera focus
			if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}
			if( SMCameraZero( CAMERAZERO_STATE_MOVE ) == SR_ERROR )
				return SR_ERROR;

		//----------------------------------------------------------------------------------
		case CAMERAZERO_STATE_MOVE:
			camera->SetMainMode( MAIN_BLANK );
			camera->SetAuxMode( AUX_BLANK );


			SR->DB->SetFiducialParams( currentFiducial );
			mainVideo->UpdateControl();
			panel->UpdatePanel();

			// Move camera...
			if( SR->DB->CameraZeroParamsS.X == 0.0 || SR->DB->CameraZeroParamsS.X == 0.0 )
			{
				// this is the first time
				retVal = SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX + SR->DB->ProductionDataS.PCBX/2.0f, SR->DB->ProductionDataS.PCBPosY + SR->DB->ProductionDataS.PCBY/2.0f, ABS_MOVE );
			}
			else
			{
				// this isn't the first time then move to the old position
				retVal = SR->MoveCameraAndWait( SR->DB->CameraZeroParamsS.X, SR->DB->CameraZeroParamsS.Y, ABS_MOVE );
			}
			if( retVal == SR_ERROR )
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

			// is done here so on PREV button it could be enabled again
			panel->ShowAlignmentPanel( false );

			// Start live video
			camera->SetMainMode( MAIN_CAMERA_MOVE );
			camera->SetAuxMode( AUX_CAMPOSITION );
			camera->StartCapture();

			controlPanel->SetState( PANEL_MOVE_CAMERA, PANEL_OUTPUT_NONE );
			isAuxVideoClickEnable = true;
			// sets controls state
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case CAMERAZERO_STATE_TEACH:
			// Start live video
			camera->StartCapture();
			camera->SetAuxMode( AUX_SMOOTH_EDGE );

			if( !panel->GetManualCheck() )
			{
				camera->SetMainCamZeroShape();
				camera->SetMainMode( MAIN_MOUSE_CUR );
				smartLogger->Write( MSG_CLICKFIDUCIAL );
				panel->UpdatePanelCameraZero();
				panel->ShowAlignmentPanel( true );
				panel->EnableAlignmentPanel( true );
				panel->EnableShapeCombo( IsFiducialOnPCB( currentFiducial ) ? true : false );
			}
			else
			{
				camera->SetMainCamZeroShape();
				camera->SetMainMode( MAIN_MOUSE_CUR_MANUAL );
				smartLogger->Write( MSG_FIDMANUALTEACH );
			}

			datasette->StopEnable( true );
			datasette->PrevEnable( true );
			isMainVideoClickEnable = true;
			break;


		//----------------------------------------------------------------------------------
		case CAMERAZERO_STATE_SEARCH:
			// Get frames and stop video
			camera->SetMainMode( MAIN_NO_CUR );
			if( !panel->GetManualCheck() )
				camera->GetFrames( MAX_FRAMES_FIDUCIAL );
			camera->StopCapture();

			// Disable camera
			/*if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}*/

			centerX = 0;
			centerY = 0;
			circleR = 0;

			if( !panel->GetManualCheck() )
			{
					if( camera->FindCircleCameraZero( xClicked, yClicked, centerX, centerY, circleR ) == SR_OK )
					{
						smartLogger->Write( wxString::Format( MSG_FIDFOUND_CIRCLE, centerX, centerY, circleR ) );
						if( SMCameraZero( CAMERAZERO_STATE_FOUND_WAIT ) == SR_ERROR )
							return SR_ERROR;
						break;
					}



				// Fiducial not found
				smartLogger->Write( MSG_FIDNOTFOUND, MSG_ERROR );
				// Notify manual fiducial search
				wxMessageBox( MSG_FIDUCIALMANUAL, MACHINE_NAME, wxOK | wxICON_WARNING, parent );

				/* Manual fiducial search
				smartLogger->Write( MSG_FIDMANUALTEACH );
				camera->SetMainCamZeroShape();
				camera->SetMainMode( MAIN_MOUSE_CUR_MANUAL );
				datasette->StopEnable( true );
				datasette->PrevEnable( true );
				// Enable mouse click
				isMainVideoClickEnable = true;*/
				if( SMCameraZero( CAMERAZERO_STATE_TEACH ) == SR_ERROR )
					return SR_ERROR;
			}
			else
			{
				centerX = xClicked;
				centerY = yClicked;

				if( SMCameraZero( CAMERAZERO_STATE_FOUND_WAIT ) == SR_ERROR )
					return SR_ERROR;
			}
			break;

		//----------------------------------------------------------------------------------
		case CAMERAZERO_STATE_FOUND_WAIT:
			// sets controls state
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			datasette->PrevEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case CAMERAZERO_STATE_FOUND:
			// Get current camera coords
			SR->GetCameraPosition( camPos.X, camPos.Y );
			// At this point, we have the fiducial coords (manual or auto...)
			SR->DB->CameraZeroParamsS.X = camPos.X + (centerX - CAM_W / 2) * SR->DB->MachineParamsS.DnXPixMm;
			SR->DB->CameraZeroParamsS.Y = camPos.Y - (centerY - CAM_H / 2) * SR->DB->MachineParamsS.DnYPixMm;


			// reset unused values
			SR->DB->CameraZeroParamsS.DeltaX = 0.0;
			SR->DB->CameraZeroParamsS.DeltaY = 0.0;

			//SR->DB->CameraZeroParamsS.CircleDiameter = circleR*(SR->DB->MachineParamsS.DnXPixMm + SR->DB->MachineParamsS.DnYPixMm);
			SR->DB->CameraZeroParamsS.CircleDiameter = circleR*2;

			// Stop live video
			camera->StopCapture();
			camera->SetMainMode( MAIN_BLANK );
			camera->SetAuxMode( AUX_BLANK );

			panel->ShowAlignmentPanel( false );

			// Disable camera
			if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Save Zero params
			if(!doNotSaveZeroPos){
				SR->DB->SaveCameraZero();
			}

			//Reset home position
			if(SR->MoveCameraAndWait( -SR->DB->CameraZeroParamsS.X, -SR->DB->CameraZeroParamsS.Y, REL_MOVE ) == SR_ERROR){
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				return SR_ERROR;
			}

			if( SR->CamXMotor.motor->Home() == MOTOR_ERROR )
				return SR_ERROR;
			if( SR->CamYMotor.motor->Home() == MOTOR_ERROR )
				return SR_ERROR;
			SR->CamXMotor.ResetPosition();
			SR->CamYMotor.ResetPosition();

			smartLogger->Write( MSG_CAMERAZEROENDED, MSG_SUCCESS );
			if( SMCameraZero( CAMERAZERO_STATE_RESET ) == SR_ERROR )
				return SR_ERROR;

			break;


		//----------------------------------------------------------------------------------
		case CAMERAZERO_STATE_RESET:
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
			// Move the plate to disengage the board
			if( SR->PlateMotor.MoveAndWait( 0, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}
			// Check for motors position
			if( SR->CheckMotorsPos() == SR_ERROR )
			{
				if( panel->IsFiducialReviewSelected() )
				{
					if( SR->ResetMotors( MODE_STARTPRINTING_POSITION ) == SR_ERROR )
					{
						return SR_ERROR;
					}
				}
				else
				{
					if( SR->ResetMotors( MODE_START_POSITION ) == SR_ERROR )
					{
						return SR_ERROR;
					}
				}
			}

			SR->CheckCover( false );

			controlPanel->SetState( PANEL_ALIGNMENT );

			// avoid to save not congruent data

			panel->ShowTemplatePanel( false );
			panel->ShowManualCheck( false );
			panel->ShowFiducialButton( true );
			panel->ShowAlignmentPanel( false );

			toolBox->Enable( true );
			menuBtn->Enable( true );
			datasette->StartEnable( true );
			break;

	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMCameraZeroNext
// Aggiorna lo stato dell SM
//----------------------------------------------------------------------------------
void SMBase::SMCameraZeroNext()
{
	retVal = SR_OK;

	switch( currentState )
	{
		case CAMERAZERO_STATE_INIT0:
			retVal = SMCameraZero( CAMERAZERO_STATE_INIT );
			break;

		case CAMERAZERO_STATE_MOVE:
			retVal = SMCameraZero( CAMERAZERO_STATE_TEACH );
			break;
		case CAMERAZERO_STATE_FOUND_WAIT:
			retVal = SMCameraZero( CAMERAZERO_STATE_FOUND );
			break;

	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

//----------------------------------------------------------------------------------
// SMCameraZeroPrev
// Aggiorna lo stato della SM
//----------------------------------------------------------------------------------
void SMBase::SMCameraZeroPrev()
{
	retVal = SR_OK;

	switch( currentState )
	{
	case CAMERAZERO_STATE_TEACH:
		retVal = SMCameraZero( CAMERAZERO_STATE_MOVE );
		break;
	case CAMERAZERO_STATE_FOUND_WAIT:
		retVal = SMCameraZero(CAMERAZERO_STATE_TEACH);
		break;
	case CAMERAZERO_STATE_SEARCH:
		retVal = SMCameraZero(CAMERAZERO_STATE_SEARCH);
		break;
	}


	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

//----------------------------------------------------------------------------------
// SMCameraZeroMainVideoLeftClick
//
//----------------------------------------------------------------------------------
void SMBase::SMCameraZeroMainVideoLeftClick( wxMouseEvent& e )
{
	retVal = SR_OK;

	if( !isMainVideoClickEnable )
		return;

	wxProductionPanel *panel = (wxProductionPanel *)currentPanel;

	switch( currentState )
	{
		case CAMERAZERO_STATE_TEACH:
			camera->GetCursorPositionMain( xClicked, yClicked );
			retVal = SMCameraZero( CAMERAZERO_STATE_SEARCH );
			break;
		case CAMERAZERO_STATE_SEARCH:
			camera->GetCursorPositionMain( xClicked, yClicked );
			circleR = SR->DB->CameraZeroParamsS.CircleDiameter/2;
			centerX = xClicked;
			centerY = yClicked;
			retVal = SMCameraZero( CAMERAZERO_STATE_FOUND );

			break;

	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

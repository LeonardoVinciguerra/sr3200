//---------------------------------------------------------------------------
//
// Name:        SMCameraScale.cpp
// Author:      Gabriel Ferri
// Created:     20/05/2008 11.23
// Description: Camera scale - State Machine functions implementation
//
//---------------------------------------------------------------------------

#include "SMBase.h"
#include "wxCalibrationPanel.h"
#include <wx/msgdlg.h>
#include "Messages.h"
#include "wxMyEntryDialog.h"
#include "wxMyTextValidator.h"

#define PANEL_CAMERASCALE		PANEL_MOVE_DISABLE, PANEL_OUTPUT_LOCK | PANEL_OUTPUT_BOARD_LOCK
#define PANEL_CAMERASCALE_MOVE	PANEL_MOVE_TABLE | PANEL_MOVE_CAMERA, PANEL_OUTPUT_LOCK | PANEL_OUTPUT_BOARD_LOCK
#define PANEL_DISABLE			PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE

//----------------------------------------------------------------------------------
// SMCameraScaleInitialize
// Inizializza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMCameraScaleInitialize()
{
	mainVideo->ConnectMainVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMCameraScaleMainVideoLeftClick ), this );
	mainVideo->ConnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );
	mainVideo->ConnectMainVideoKeyEvent( wxEVT_CHAR, wxStaticCastEvent( wxCharEventFunction, &SMBase::SMMainVideoKeyPress ), this );

	controlPanel->SetState( PANEL_CAMERASCALE );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMCameraScaleFinalize
// Finalizza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMCameraScaleFinalize()
{
	mainVideo->DisconnectMainVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMCameraScaleMainVideoLeftClick ), this );
	mainVideo->DisconnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );
	mainVideo->DisconnectMainVideoKeyEvent( wxEVT_CHAR, wxStaticCastEvent( wxCharEventFunction, &SMBase::SMMainVideoKeyPress ), this );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMCameraScaleReset
// Resetta la macchina a stati
//----------------------------------------------------------------------------------
void SMBase::SMCameraScaleReset()
{
	controlPanel->SetState( PANEL_CAMERASCALE );

	wxCalibrationPanel *panel = (wxCalibrationPanel *)currentPanel;
	panel->Enable( true );
}

//----------------------------------------------------------------------------------
// SMCameraScale
// Macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMCameraScale( int nextState )
{
	float inputValue = 0.0;
	wxMyEntryDialog *entryDlg;

	datasette->StopEnable( false );
	datasette->NextEnable( false );
	datasette->PrevEnable( false );
	controlPanel->SetState( PANEL_DISABLE );

	currentState = nextState;
	wxCalibrationPanel *panel = (wxCalibrationPanel *)currentPanel;

	switch( currentState )
	{
		case CAMERASCALE_STATE_INIT:
			panel->Enable( false );

			initCheck.cover			= false;
			initCheck.air			= true;
			initCheck.pcb			= false;
			initCheck.pcb_height	= 0;
			initCheck.frame			= panel->GetSelectedCamera() != CAMERA_DOWN;
			initCheck.motors_pos	= true;
			initCheck.motor_state	= MODE_START_POSITION;

			if( SMInitCheck( initCheck ) == SR_ERROR )
				return SR_ERROR;

			// Camera scale calibration cycle can begin...
			if( panel->GetSelectedCamera() == CAMERA_DOWN )
			{
				// Move the board to reaches the camera focus
				if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
				{
					smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
					return SR_ERROR;
				}
			}

			if( SMCameraScale( CAMERASCALE_STATE_MOVE ) == SR_ERROR )
				return SR_ERROR;
			break;

		case CAMERASCALE_STATE_RESET:
			// disable mouse click
			isMainVideoClickEnable = false;
			isAuxVideoClickEnable = false;

			panel->UpdateConstLabels();

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
			controlPanel->SetState( PANEL_CAMERASCALE );
			break;

		case CAMERASCALE_STATE_MOVE:
			// Enable camera
			if( SR->SetCamera( panel->GetSelectedCamera() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Start live video
			camera->SetMainMode( MAIN_CAMERA_CUR );
			camera->SetAuxMode( AUX_CAMPOSITION );
			camera->StartCapture();

			smartLogger->Write( MSG_CAMERASCALESTART );

			// enable mouse click
			isAuxVideoClickEnable = true;

			controlPanel->SetState( PANEL_MOVE_CAMERA | PANEL_MOVE_TABLE, PANEL_OUTPUT_NONE );
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			break;

		case CAMERASCALE_STATE_X_START:
			// stop live video
			camera->StopCapture();
			camera->SetMainMode( MAIN_MOUSE_CUR );
			camera->SetAuxMode( AUX_BLANK );

			// Disable camera
			if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			smartLogger->Write( MSG_CAMERASCALEXAXIS );

			// Enable mouse click
			isMainVideoClickEnable = true;

			datasette->StopEnable( true );
			datasette->PrevEnable( true );
			break;

		case CAMERASCALE_STATE_X_END:
			camera->SetMainP1( xClicked, yClicked );
			camera->SetMainMode( MAIN_LINE_X );
			start_x = xClicked;
			start_y = yClicked;

			datasette->StopEnable( true );
			datasette->PrevEnable( true );
			break;

		case CAMERASCALE_STATE_X_SAVE:
			camera->SetMainMode( MAIN_NO_CUR );

			// Disable mouse click
			isMainVideoClickEnable = false;

			// insert value in mm
			entryDlg = new wxMyEntryDialog( parent, MSG_CAMERASCALEXAXISMM, MACHINE_NAME, wxT("0"), wxOK | wxCANCEL | wxCENTRE );
			entryDlg->SetMyValidator( wxMyTextValidator( &inputValue, false ) );

			if(	entryDlg->ShowModal() == wxID_CANCEL )
			{
				delete entryDlg;
				if( SMCameraScale( CAMERASCALE_STATE_X_START ) == SR_ERROR )
					return SR_ERROR;
				break;
			}

			scale_x = inputValue / abs( start_x - xClicked );
			smartLogger->Write( wxString::Format( (panel->GetSelectedCamera() == CAMERA_UP ? _("X Up") : _("X Down")) + wxString(": %.6f"), scale_x ) );
			delete entryDlg;

			if( SMCameraScale( CAMERASCALE_STATE_Y_START ) == SR_ERROR )
				return SR_ERROR;
			break;

		case CAMERASCALE_STATE_Y_START:
			camera->SetMainMode( MAIN_MOUSE_CUR );
			smartLogger->Write( MSG_CAMERASCALEYAXIS );

			// Enable mouse click
			isMainVideoClickEnable = true;

			datasette->StopEnable( true );
			datasette->PrevEnable( true );
			break;

		case CAMERASCALE_STATE_Y_END:
			camera->SetMainP1( xClicked, yClicked );
			camera->SetMainMode( MAIN_LINE_Y );
			start_x = xClicked;
			start_y = yClicked;

			datasette->StopEnable( true );
			datasette->PrevEnable( true );
			break;

		case CAMERASCALE_STATE_Y_SAVE:
			camera->SetMainMode( MAIN_NO_CUR );

			// Disable mouse click
			isMainVideoClickEnable = false;

			// insert value in mm
			entryDlg = new wxMyEntryDialog( parent, MSG_CAMERASCALEYAXISMM, MACHINE_NAME, wxT("0"), wxOK | wxCANCEL | wxCENTRE );
			entryDlg->SetMyValidator( wxMyTextValidator( &inputValue, false ) );

			if(	entryDlg->ShowModal() == wxID_CANCEL )
			{
				delete entryDlg;
				if( SMCameraScale( CAMERASCALE_STATE_Y_START ) == SR_ERROR )
					return SR_ERROR;
				break;
			}

			scale_y = inputValue / abs( start_y - yClicked );
			smartLogger->Write( wxString::Format( (panel->GetSelectedCamera() == CAMERA_UP ? _("Y Up") : _("Y Down")) + wxString(": %.6f"), scale_y ) );
			delete entryDlg;

			// save data to struct and DB
			if( panel->GetSelectedCamera() == CAMERA_UP )
			{
				SR->DB->MachineParamsS.UpXPixMm = scale_x;
				SR->DB->MachineParamsS.UpYPixMm = scale_y;
			}
			else
			{
				SR->DB->MachineParamsS.DnXPixMm = scale_x;
				SR->DB->MachineParamsS.DnYPixMm = scale_y;
			}
			SR->DB->SaveMachineParams();
			panel->UpdateConstLabels();

			smartLogger->Write( MSG_CAMERASCALEENDED, MSG_SUCCESS );
			if( SMCameraScale( CAMERASCALE_STATE_RESET ) == SR_ERROR )
				return SR_ERROR;
			break;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMCameraScaleNext
// Aggiorna lo stato dell SM
//----------------------------------------------------------------------------------
void SMBase::SMCameraScaleNext()
{
	retVal = SR_OK;

	switch( currentState )
	{
		case CAMERASCALE_STATE_MOVE:
			retVal = SMCameraScale( CAMERASCALE_STATE_X_START );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

//----------------------------------------------------------------------------------
// SMCameraScalePrev
// Aggiorna lo stato dell SM
//----------------------------------------------------------------------------------
void SMBase::SMCameraScalePrev()
{
	retVal = SR_OK;

	switch( currentState )
	{
		case CAMERASCALE_STATE_X_START:
			retVal = SMCameraScale( CAMERASCALE_STATE_MOVE );
			break;

		case CAMERASCALE_STATE_X_END:
			retVal = SMCameraScale( CAMERASCALE_STATE_X_START );
			break;

		case CAMERASCALE_STATE_Y_START:
			retVal = SMCameraScale( CAMERASCALE_STATE_X_START );
			break;

		case CAMERASCALE_STATE_Y_END:
			retVal = SMCameraScale( CAMERASCALE_STATE_Y_START );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

//----------------------------------------------------------------------------------
// SMCameraScaleMainVideoLeftClick
// 
//----------------------------------------------------------------------------------
void SMBase::SMCameraScaleMainVideoLeftClick( wxMouseEvent& e )
{
	retVal = SR_OK;

	if( !isMainVideoClickEnable )
		return;

	// Cursor position
	camera->GetCursorPositionMain( xClicked, yClicked );

	switch( currentState )
	{
		case CAMERASCALE_STATE_X_START:
			retVal = SMCameraScale( CAMERASCALE_STATE_X_END );
			break;

		case CAMERASCALE_STATE_X_END:
			retVal = SMCameraScale( CAMERASCALE_STATE_X_SAVE );
			break;

		case CAMERASCALE_STATE_Y_START:
			retVal = SMCameraScale( CAMERASCALE_STATE_Y_END );
			break;

		case CAMERASCALE_STATE_Y_END:
			retVal = SMCameraScale( CAMERASCALE_STATE_Y_SAVE );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

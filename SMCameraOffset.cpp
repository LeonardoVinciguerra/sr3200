//---------------------------------------------------------------------------
//
// Name:        SMCameraOffset.cpp
// Author:      Gabriel Ferri
// Created:     09/06/2008 09.33
// Description: Camera offset - State Machine functions implementation
//
//---------------------------------------------------------------------------

#include "SMBase.h"
#include "wxCalibrationPanel.h"
#include <wx/msgdlg.h>
#include "GlobalUtils.h"
#include "Messages.h"

#define PANEL_CAMERAOFFSET			PANEL_MOVE_DISABLE, PANEL_OUTPUT_LOCK | PANEL_OUTPUT_LED_UP | PANEL_OUTPUT_LED_DOWN | PANEL_OUTPUT_BOARD_LOCK
#define PANEL_CAMERAOFFSET_CAMERA	PANEL_MOVE_CAMERA, PANEL_OUTPUT_LOCK | PANEL_OUTPUT_LED_UP | PANEL_OUTPUT_LED_DOWN | PANEL_OUTPUT_BOARD_LOCK
#define PANEL_DISABLE				PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE

#define OFFSET_POINT_OK			0
#define OFFSET_POINT_ERROR		1


//----------------------------------------------------------------------------------
// SMCameraOffsetInitialize
// Inizializza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMCameraOffsetInitialize()
{
	mainVideo->ConnectMainVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMCameraOffsetMainVideoLeftClick ), this );
	mainVideo->ConnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );
	mainVideo->ConnectMainVideoKeyEvent( wxEVT_CHAR, wxStaticCastEvent( wxCharEventFunction, &SMBase::SMMainVideoKeyPress ), this );

	controlPanel->SetState( PANEL_CAMERAOFFSET );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMCameraOffsetFinalize
// Finalizza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMCameraOffsetFinalize()
{
	mainVideo->DisconnectMainVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMCameraOffsetMainVideoLeftClick ), this );
	mainVideo->DisconnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );
	mainVideo->DisconnectMainVideoKeyEvent( wxEVT_CHAR, wxStaticCastEvent( wxCharEventFunction, &SMBase::SMMainVideoKeyPress ), this );

	camera->DrawWorkplace();

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMCameraOffsetReset
// Resetta la macchina a stati
//----------------------------------------------------------------------------------
void SMBase::SMCameraOffsetReset()
{
	// load from database to avoid data inconsistency
	SR->DB->LoadOffsetPoints();
	SR->DB->LoadOffsetCheckPoints();

	controlPanel->SetState( PANEL_CAMERAOFFSET );

	wxCalibrationPanel *panel = (wxCalibrationPanel *)currentPanel;
	panel->EnablePanel( true );
}

//----------------------------------------------------------------------------------
// SMCameraOffset
// Macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMCameraOffset( int nextState )
{
	datasette->StopEnable( isSearching ? true : false );
	datasette->NextEnable( false );
	datasette->PrevEnable( false );
	controlPanel->SetState( PANEL_DISABLE );

	currentState = nextState;
	wxCalibrationPanel *panel = (wxCalibrationPanel *)currentPanel;

	switch( currentState )
	{
		//----------------------------------------------------------------------------------
		case CAMERAOFFSET_STATE_INIT:
			panel->EnablePanel( false );

			initCheck.cover			= false;
			initCheck.air			= true;
			initCheck.pcb			= false;
			initCheck.pcb_height	= 0;
			initCheck.frame			= false;
			initCheck.motors_pos	= true;
			initCheck.motor_state	= MODE_START_POSITION;

			if( SMInitCheck( initCheck ) == SR_ERROR )
				return SR_ERROR;

			isSearching = false;

			// Move camera to the saved start point
			if( SR->MoveCameraAndWait( SR->DB->MachineParamsS.OffsetPointsStartX, SR->DB->MachineParamsS.OffsetPointsStartY, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				return SR_ERROR;
			}
			// Enable camera
			if( SR->SetCamera( CAMERA_UP ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Start live video
			camera->SetMainMode( MAIN_CAMERA_CUR );
			camera->SetAuxMode( AUX_CAMPOSITION );
			camera->StartCapture();

			smartLogger->Write( MSG_BGACAMCENTERFIRST );

			// enable mouse click
			isAuxVideoClickEnable = true;

			controlPanel->SetState( PANEL_CAMERAOFFSET_CAMERA );
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case CAMERAOFFSET_STATE_RESET:
			// if it is searching stop it
			if( isSearching )
			{
				isSearching = false;
				return SR_OK;
			}

			// disable mouse click
			isMainVideoClickEnable = false;
			isAuxVideoClickEnable = false;

			// stop live video
			camera->StopCapture();
			camera->SetMainMode( MAIN_BLANK );
			camera->SetAuxMode( AUX_BLANK );

			// load from database to avoid data inconsistency
			SR->DB->LoadOffsetPoints();
			SR->DB->LoadOffsetCheckPoints();

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
					return SR_ERROR;
			}

			controlPanel->SetState( PANEL_CAMERAOFFSET );
			panel->EnablePanel( true );
			toolBox->Enable( true );
			menuBtn->Enable( true );
			datasette->StartEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case CAMERAOFFSET_STATE_PRINTING:
			// disable mouse click
			isAuxVideoClickEnable = false;
			camera->SetMainMode( MAIN_BLANK );
			camera->SetAuxMode( AUX_BLANK );
			
			//
			SR->GetCameraPosition( camPos.X, camPos.Y );

			// check frame position
			if( SR->CheckCamera( camPos.X + (SR->DB->MachineParamsS.OffsetPointsNumX-1) * SR->DB->MachineParamsS.OffsetPointsDistance, camPos.Y, ABS_MOVE ) == SR_ERROR )
			{
				wxMessageBox( MSG_WRONGFRAMEPOSITION, MACHINE_NAME, wxOK | wxICON_ERROR, parent );
				SMCameraOffset( CAMERAOFFSET_STATE_RESET );
				return SR_ERROR;
			}

			// save start position
			SR->DB->MachineParamsS.OffsetPointsStartX = camPos.X;
			SR->DB->MachineParamsS.OffsetPointsStartY = camPos.Y;
			SR->DB->SaveMachineParams();

			// Disable camera
			if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			// Move camera out
			if( SR->MoveCameraAndWait( (SR->DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit - SR->DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit)/2, SR->DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Move the board to reaches the frame
			if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.PlateMovement, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// init data
			memset( offsetMapState, 0, NUM_OFFSET_POINTS );
			currentPoint = 0;
			currentFiducial = FIDUCIAL_OFFSET;
			camera->DrawWorkplace();

			controlPanel->SetState( PANEL_CAMERAOFFSET );
			smartLogger->Write( MSG_PRINTMANUALLY );
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			break;

		//----------------------------------------------------------------------------------
		//ADD
		case CAMERAOFFSET_STATE_MECH_OFFSET:
			// disable mouse click
			isAuxVideoClickEnable = false;
			camera->SetMainMode( MAIN_BLANK );
			camera->SetAuxMode( AUX_BLANK );
			
			// Move the board to reaches the camera focus
			if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}
			// Move camera to the start point
			if( SR->MoveCameraAndWait( SR->DB->MachineParamsS.OffsetPointsStartX, SR->DB->MachineParamsS.OffsetPointsStartY, ABS_MOVE ) == SR_ERROR )
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

			smartLogger->Write( MSG_BGAPARMADJ );

			camera->SetMainMode( MAIN_CAMERA_CUR );
			camera->SetAuxMode( AUX_CAMPOSITION );
			isAuxVideoClickEnable = true;

			controlPanel->SetState( PANEL_CAMERAOFFSET_CAMERA );
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case CAMERAOFFSET_STATE_SEARCH_TESTDN:
			// disable mouse click
			isAuxVideoClickEnable = false;

			camera->SetMainMode( MAIN_NO_CUR );
			camera->SetAuxMode( AUX_CAMPOSITION );

			// Enable camera
			if( SR->SetCamera( CAMERA_DOWN ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				return SR_ERROR;
			}
			
			myMilliSleep( FLICKERING_DELAY );

			// Wait to avoid flickering and get frames
			camera->SetMainMode( MAIN_NO_CUR );
			camera->StartCapture();
			camera->GetFrames( MAX_FRAMES_FIDUCIAL );
			camera->StopCapture();

			// Disable camera
			if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			//TEMP - gestire anche il fatto dei parametri di ricerca da cambiare
			SR->DB->SetFiducialParams( currentFiducial );
			panel->UpdatePanel();
			mainVideo->UpdateControl();

			// Call function to get the center of the BGA pattern...
			if( camera->FindOffsetPattern3( centerX, centerY ) == true )
			{
				smartLogger->Write( wxString::Format( MSG_BGAFOUND, centerX, centerY ) );
			}
			else
			{
				smartLogger->Write( MSG_BGANOTFOUND, MSG_ERROR );
			}

			currentFiducial = FIDUCIAL_OFFSET_FRAME;

			if( SMCameraOffset( CAMERAOFFSET_STATE_SEARCH_TESTWAIT ) == SR_ERROR )
				return SR_ERROR;
			break;

		//----------------------------------------------------------------------------------
		case CAMERAOFFSET_STATE_SEARCH_TESTWAIT:

			datasette->PrevEnable( true );
			datasette->StopEnable( true );
			datasette->NextEnable( true );

			break;

		//----------------------------------------------------------------------------------
		case CAMERAOFFSET_STATE_SEARCH_PARUP:
			smartLogger->Write( MSG_BGAPARMADJ );

			// Enable camera
			camera->StartCapture();
			if( SR->SetCamera( CAMERA_UP ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			SR->DB->SetFiducialParams( currentFiducial );
			panel->UpdatePanel();
			mainVideo->UpdateControl();

			datasette->StopEnable( true );
			datasette->NextEnable( true );

			break;

		//----------------------------------------------------------------------------------
		case CAMERAOFFSET_STATE_SEARCH_TESTUP:
			// disable mouse click
			isAuxVideoClickEnable = false;

			camera->SetMainMode( MAIN_NO_CUR );

			// Enable camera
			if( SR->SetCamera( currentFiducial == FIDUCIAL_OFFSET ? CAMERA_DOWN : CAMERA_UP ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			myMilliSleep( FLICKERING_DELAY );

			// Wait to avoid flickering and get frames
			camera->SetMainMode( MAIN_NO_CUR );
			camera->StartCapture();
			camera->GetFrames( MAX_FRAMES_FIDUCIAL );
			camera->StopCapture();

			// Disable camera
			if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			//TEMP - gestire anche il fatto dei parametri di ricerca da cambiare
			SR->DB->SetFiducialParams( currentFiducial );
			panel->UpdatePanel();
			mainVideo->UpdateControl();

			// Call function to get the center of the BGA pattern...
			if( camera->FindOffsetPattern3( centerX, centerY ) == true )
			{
				smartLogger->Write( wxString::Format( MSG_BGAFOUND, centerX, centerY ) );
			}
			else
			{
				smartLogger->Write( MSG_BGANOTFOUND, MSG_ERROR );
			}
			currentFiducial = FIDUCIAL_OFFSET;

			if( SMCameraOffset( CAMERAOFFSET_STATE_SEARCH_TESTWAIT ) == SR_ERROR )
				return SR_ERROR;
			break;

		//----------------------------------------------------------------------------------
		case CAMERAOFFSET_STATE_SEARCH:
			// disable mouse click
			isAuxVideoClickEnable = false;

			// this is the first point
			if( currentPoint == 0 && currentFiducial == FIDUCIAL_OFFSET )
			{
				// sets searching flag
				isSearching = true;
				
				camera->SetMainMode( MAIN_NO_CUR );
				camera->SetAuxMode( AUX_CAMPOSITION );
			}

			// check searching flag
			if( isSearching == false )
			{
				// stop button pressed
				if( SMCameraOffset( CAMERAOFFSET_STATE_RESET ) == SR_ERROR )
					return SR_ERROR;
				return SR_OK;
			}

			// Enable camera
			if( SR->SetCamera( currentFiducial == FIDUCIAL_OFFSET ? CAMERA_DOWN : CAMERA_UP ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			myMilliSleep( FLICKERING_DELAY );

			// Wait to avoid flickering and get frames
			camera->SetMainMode( MAIN_NO_CUR );
			camera->StartCapture();
			camera->GetFrames( MAX_FRAMES_FIDUCIAL );
			camera->StopCapture();

			// Disable camera
			if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			//TEMP - gestire anche il fatto dei parametri di ricerca da cambiare
			SR->DB->SetFiducialParams( currentFiducial );
			panel->UpdatePanel();
			mainVideo->UpdateControl();

			//
			SR->GetCameraPosition( camPos.X, camPos.Y );

			// show point number
			if( currentFiducial == FIDUCIAL_OFFSET )
				smartLogger->Write( wxString::Format( MSG_SEARCHTPOINT, currentPoint+1) );

			// Call function to get the center of the BGA pattern...
			if( camera->FindOffsetPattern3( centerX, centerY ) == true )
			{
				smartLogger->Write( wxString::Format( MSG_BGAFOUND, centerX, centerY ) );

				if( currentFiducial == FIDUCIAL_OFFSET )
				{
					offsetMapDown[currentPoint].X = ( centerX - CAM_W / 2 ) * SR->DB->MachineParamsS.DnXPixMm;
					offsetMapDown[currentPoint].Y = ( centerY - CAM_H / 2 ) * SR->DB->MachineParamsS.DnYPixMm;
				}
				else
				{
					offsetMapUp[currentPoint].X = ( centerX - CAM_W / 2 ) * SR->DB->MachineParamsS.UpXPixMm;
					offsetMapUp[currentPoint].Y = ( centerY - CAM_H / 2 ) * SR->DB->MachineParamsS.UpYPixMm;
				}
				// draw point on workplace
				camera->DrawWorkplacePoint( camPos.X, camPos.Y, CV_RGB( 0, 255, 0 ) ); // GREEN
			}
			else
			{
				smartLogger->Write( MSG_BGANOTFOUND, MSG_ERROR );
				
				offsetMapState[currentPoint] = OFFSET_POINT_ERROR;
				// save the camera position to use later
				offsetMapDown[currentPoint].X = camPos.X;
				offsetMapDown[currentPoint].Y = camPos.Y;
				// draw point on workplace
				camera->DrawWorkplacePoint( camPos.X, camPos.Y, CV_RGB( 0, 0, 255 ) ); // RED
			}
			
			// check searching flag
			if( isSearching == false )
			{
				// stop button pressed
				if( SMCameraOffset( CAMERAOFFSET_STATE_RESET ) == SR_ERROR )
					return SR_ERROR;
				return SR_OK;
			}

			// If current fiducial is Down...
			if( currentFiducial == FIDUCIAL_OFFSET )
			{
				if( offsetMapState[currentPoint] != OFFSET_POINT_ERROR )
				{
					camPos.X += offsetMapDown[currentPoint].X;
					camPos.Y -= offsetMapDown[currentPoint].Y;
				}

				// if this is the first row point save its position
				if( currentPoint % SR->DB->MachineParamsS.OffsetPointsNumX == 0 )
				{
					rowStartX = camPos.X;
					rowStartY = camPos.Y;
				}

				// if no error search point on frame
				if( offsetMapState[currentPoint] != OFFSET_POINT_ERROR )
				{
					currentFiducial = FIDUCIAL_OFFSET_FRAME;
					if( SMCameraOffset( CAMERAOFFSET_STATE_SEARCH ) == SR_ERROR )
						return SR_ERROR;
					break;
				}
				//else continue with next point
			}

			// go to next point
			currentPoint++;
			
			if( currentPoint < SR->DB->MachineParamsS.OffsetPointsNumX * SR->DB->MachineParamsS.OffsetPointsNumY )
			{
				// move camera on the next point (Scansione per linee)
				if( currentPoint % SR->DB->MachineParamsS.OffsetPointsNumX == 0 )
				{
					// move on next line
					retVal = SR->MoveCameraAndWait( rowStartX, rowStartY + SR->DB->MachineParamsS.OffsetPointsDistance, ABS_MOVE );
				}
				else
				{
					// move on next point (same line)
					retVal = SR->MoveCameraAndWait( camPos.X + SR->DB->MachineParamsS.OffsetPointsDistance, camPos.Y, ABS_MOVE );
				}
				if( retVal == SR_ERROR )
				{
					smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
					return SR_ERROR;
				}

				currentFiducial = FIDUCIAL_OFFSET;
				if( SMCameraOffset( CAMERAOFFSET_STATE_SEARCH ) == SR_ERROR )
					return SR_ERROR;
			}
			else
			{
				isSearching = false;
				currentPoint = 0;
				errorShown = false;
				if( SMCameraOffset( CAMERAOFFSET_STATE_CHECK ) == SR_ERROR )
					return SR_ERROR;
			}
			break;

		//----------------------------------------------------------------------------------
		case CAMERAOFFSET_STATE_CHECK:
			// look for error
			if( offsetMapState[currentPoint] == OFFSET_POINT_ERROR )
			{
				if( !errorShown )
				{
					errorShown = true;
					
					SR->SetOutput( OUTPUT_BUZZER, true );
					wxMessageBox( MSG_CAMERAOFFSETMANUAL, MACHINE_NAME, wxOK | wxICON_INFORMATION, parent );
					SR->SetOutput( OUTPUT_BUZZER, false );
				}
				smartLogger->Write( wxString::Format( MSG_SEARCHTPOINT, currentPoint+1) );

				// move camera on the missing point (camera position is stored in maps vector)
				if( SR->MoveCameraAndWait( offsetMapDown[currentPoint].X, offsetMapDown[currentPoint].Y, ABS_MOVE ) == SR_ERROR )
				{
					smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
					return SR_ERROR;
				}

				// correct the error...
				currentFiducial = FIDUCIAL_OFFSET;
				if( SMCameraOffset( CAMERAOFFSET_STATE_REVIEW_SEARCH ) == SR_ERROR )
					return SR_ERROR;
				break;
			}
			
			// draw point on workplace
			SR->GetCameraPosition( camPos.X, camPos.Y );
			camera->DrawWorkplacePoint( camPos.X, camPos.Y, CV_RGB( 0, 255, 0 ) ); // GREEN

			currentPoint++;
			if( currentPoint < SR->DB->MachineParamsS.OffsetPointsNumX * SR->DB->MachineParamsS.OffsetPointsNumY )
			{
				if( SMCameraOffset( CAMERAOFFSET_STATE_CHECK ) == SR_ERROR )
					return SR_ERROR;
			}
			else
			{
				// this is necessary to correctly close the wxProgressDialog
				myMilliSleep( 1 );
				wxProgressDialog wait( MACHINE_NAME, MSG_WAITWORKING, 100, parent, wxPD_AUTO_HIDE | wxPD_APP_MODAL );
				float waitInc = 100.0f / (SR->DB->MachineParamsS.OffsetPointsNumX * SR->DB->MachineParamsS.OffsetPointsNumY);
				// calc offset
				for( currentPoint = 0; currentPoint < SR->DB->MachineParamsS.OffsetPointsNumX * SR->DB->MachineParamsS.OffsetPointsNumY; currentPoint++ )
				{
					wait.Update( waitInc * (currentPoint+1) );
					
					SR->DB->OffsetCheckPointsS[currentPoint].X = offsetMapDown[currentPoint].X - offsetMapUp[currentPoint].X;
					// Le immagini hanno l'asse Y oppposto rispetto al piano di riferimento utilizzato
					SR->DB->OffsetCheckPointsS[currentPoint].Y = -(offsetMapDown[currentPoint].Y - offsetMapUp[currentPoint].Y);
				}

				// update database
				SR->DB->SaveOffsetCheckPoints();

				smartLogger->Write( MSG_CAMERAOFFSETENDED );

				if( SMCameraOffset( CAMERAOFFSET_STATE_RESET ) == SR_ERROR )
					return SR_ERROR;
			}

			break;

		//----------------------------------------------------------------------------------
		case CAMERAOFFSET_STATE_REVIEW_SEARCH:
			// disable mouse click
			isAuxVideoClickEnable = false;

			// Enable camera
			if( SR->SetCamera( currentFiducial == FIDUCIAL_OFFSET ? CAMERA_DOWN : CAMERA_UP ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			myMilliSleep( FLICKERING_DELAY );

			// Wait to avoid flickering and get frames
			camera->SetMainMode( MAIN_NO_CUR );
			camera->StartCapture();
			camera->GetFrames( MAX_FRAMES_FIDUCIAL );
			camera->StopCapture();

			// Disable camera
			if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			SR->DB->SetFiducialParams( currentFiducial );
			panel->UpdatePanel();
			mainVideo->UpdateControl();

			// Call function to get the center of the BGA pattern...
			if( camera->FindOffsetPattern3( centerX, centerY ) == true )
			{
				smartLogger->Write( wxString::Format( MSG_BGAFOUND, centerX, centerY ) );

				if( SMCameraOffset( CAMERAOFFSET_STATE_REVIEW_FOUND_WAIT ) == SR_ERROR )
					return SR_ERROR;
				break;
			}

			// Fiducial not found
			// Notify manual fiducial search
			wxMessageBox( MSG_BGAMANUAL, MACHINE_NAME, wxOK | wxICON_WARNING, parent );
			smartLogger->Write( MSG_BGAMANUALSEARCH );

			// Enable camera
			if( SR->SetCamera( currentFiducial == FIDUCIAL_OFFSET ? CAMERA_DOWN : CAMERA_UP ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}
			camera->SetMainMode( MAIN_NO_CUR );
			camera->StartCapture();
			camera->SetMainMode( MAIN_MOUSE_CUR_MANUAL );

			datasette->StopEnable( true );
			datasette->PrevEnable( false );
			// Enable mouse click
			isMainVideoClickEnable = true;
			break;

		//----------------------------------------------------------------------------------
		case CAMERAOFFSET_STATE_REVIEW_FOUND_WAIT:
			// sets controls state
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			datasette->PrevEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case CAMERAOFFSET_STATE_REVIEW_ASK_MANUAL:
			// Ask for manual search
			if( wxMessageBox( MSG_BGAASKMANUAL, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, parent ) == wxYES )
			{
				// Manual teaching
				// Enable camera
				if( SR->SetCamera( currentFiducial == FIDUCIAL_OFFSET ? CAMERA_DOWN : CAMERA_UP ) == SR_ERROR )
				{
					smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
					return SR_ERROR;
				}

				camera->SetMainMode( MAIN_NO_CUR );
				camera->StartCapture();

				smartLogger->Write( MSG_BGAMANUALSEARCH );
				camera->SetMainMode( MAIN_MOUSE_CUR_MANUAL );
				datasette->StopEnable( true );
				// Enable mouse click
				isMainVideoClickEnable = true;
			}
			else
			{
				if( SMCameraOffset( CAMERAOFFSET_STATE_REVIEW_SEARCH ) == SR_ERROR )
					return SR_ERROR;
			}
			break;

		//----------------------------------------------------------------------------------
		case CAMERAOFFSET_STATE_REVIEW_FOUND:
			// disable mouse click
			isMainVideoClickEnable = false;
			// At this point, we have the fiducial coords (manual or auto...)
			if( currentFiducial == FIDUCIAL_OFFSET )
			{
				offsetMapDown[currentPoint].X = ( centerX - CAM_W / 2 ) * SR->DB->MachineParamsS.DnXPixMm;
				offsetMapDown[currentPoint].Y = ( centerY - CAM_H / 2 ) * SR->DB->MachineParamsS.DnYPixMm;
				
				currentFiducial = FIDUCIAL_OFFSET_FRAME;
				if( SMCameraOffset( CAMERAOFFSET_STATE_REVIEW_SEARCH ) == SR_ERROR )
					return SR_ERROR;
			}
			else
			{
				offsetMapUp[currentPoint].X = ( centerX - CAM_W / 2 ) * SR->DB->MachineParamsS.UpXPixMm;
				offsetMapUp[currentPoint].Y = ( centerY - CAM_H / 2 ) * SR->DB->MachineParamsS.UpYPixMm;

				offsetMapState[currentPoint] = OFFSET_POINT_OK;
				if( SMCameraOffset( CAMERAOFFSET_STATE_CHECK ) == SR_ERROR )
					return SR_ERROR;
			}
			break;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMCameraOffsetNext
// Aggiorna lo stato dell SM
//----------------------------------------------------------------------------------
void SMBase::SMCameraOffsetNext()
{
	retVal = SR_OK;

	switch( currentState )
	{
		case CAMERAOFFSET_STATE_INIT:
			retVal = SMCameraOffset( CAMERAOFFSET_STATE_PRINTING );
			break;

		case CAMERAOFFSET_STATE_PRINTING:
			retVal = SMCameraOffset( CAMERAOFFSET_STATE_MECH_OFFSET );
			break;

		case CAMERAOFFSET_STATE_MECH_OFFSET:
			retVal = SMCameraOffset( CAMERAOFFSET_STATE_SEARCH_TESTDN );
			break;

		case CAMERAOFFSET_STATE_SEARCH_TESTWAIT:
			if( currentFiducial == FIDUCIAL_OFFSET_FRAME ){
				retVal = SMCameraOffset( CAMERAOFFSET_STATE_SEARCH_PARUP );
			}else{ //050618
				if( SR->MoveCameraAndWait( SR->DB->MachineParamsS.OffsetPointsStartX, SR->DB->MachineParamsS.OffsetPointsStartY, ABS_MOVE ) == SR_ERROR )
				{
					smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
					return;
				}
				retVal = SMCameraOffset( CAMERAOFFSET_STATE_SEARCH );
			}
			break;

		case CAMERAOFFSET_STATE_SEARCH_PARUP:
			retVal = SMCameraOffset( CAMERAOFFSET_STATE_SEARCH_TESTUP );
			break;

		case CAMERAOFFSET_STATE_REVIEW_FOUND_WAIT:
			retVal = SMCameraOffset( CAMERAOFFSET_STATE_REVIEW_FOUND );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

//----------------------------------------------------------------------------------
// SMCameraOffsetPrev
// Aggiorna lo stato dell SM
//----------------------------------------------------------------------------------
void SMBase::SMCameraOffsetPrev()
{
	retVal = SR_OK;

	switch( currentState )
	{
		case CAMERAOFFSET_STATE_SEARCH_TESTWAIT:
			if( currentFiducial == FIDUCIAL_OFFSET_FRAME )
			{
				currentFiducial = FIDUCIAL_OFFSET;
				retVal = SMCameraOffset( CAMERAOFFSET_STATE_SEARCH_TESTDN );
			}
			else
			{
				currentFiducial = FIDUCIAL_OFFSET_FRAME;
				retVal = SMCameraOffset( CAMERAOFFSET_STATE_SEARCH_TESTUP );
			}
			break;

		case CAMERAOFFSET_STATE_REVIEW_FOUND_WAIT:
			retVal = SMCameraOffset( CAMERAOFFSET_STATE_REVIEW_ASK_MANUAL );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

//----------------------------------------------------------------------------------
// SMCameraOffsetMainVideoLeftClick
// 
//----------------------------------------------------------------------------------
void SMBase::SMCameraOffsetMainVideoLeftClick( wxMouseEvent& e )
{
	retVal = SR_OK;

	if( !isMainVideoClickEnable )
		return;

	switch( currentState )
	{
		case CAMERAOFFSET_STATE_REVIEW_SEARCH:
		case CAMERAOFFSET_STATE_REVIEW_ASK_MANUAL:
			camera->StopCapture();
			// Cursor position
			camera->GetCursorPositionMain( xClicked, yClicked );
			camera->SetMainMode( MAIN_NO_CUR );
			centerX = xClicked;
			centerY = yClicked;

			smartLogger->Write( wxString::Format( MSG_BGAFOUNDMAN, xClicked, yClicked ) );
			retVal = SMCameraOffset( CAMERAOFFSET_STATE_REVIEW_FOUND_WAIT );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

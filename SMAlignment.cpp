//---------------------------------------------------------------------------
//
// Name:        SMAlignment.cpp
// Author:      Gabriel Ferri
// Created:     04/06/2008 17.31
// Description: Alignment - State Machine functions implementation
//
//---------------------------------------------------------------------------

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


wxAlignmentTypeDialog* alignmentTypeDialog;


//----------------------------------------------------------------------------------
// SMAlignmentInitialize
// Inizializza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMAlignmentInitialize()
{
	mainVideo->ConnectMainVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAlignmentMainVideoLeftClick ), this );
	mainVideo->ConnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );
	mainVideo->ConnectMainVideoKeyEvent( wxEVT_CHAR, wxStaticCastEvent( wxCharEventFunction, &SMBase::SMMainVideoKeyPress ), this );

	controlPanel->SetState( PANEL_ALIGNMENT );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMAlignmentFinalize
// Finalizza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMAlignmentFinalize()
{
	mainVideo->DisconnectMainVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAlignmentMainVideoLeftClick ), this );
	mainVideo->DisconnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );
	mainVideo->DisconnectMainVideoKeyEvent( wxEVT_CHAR, wxStaticCastEvent( wxCharEventFunction, &SMBase::SMMainVideoKeyPress ), this );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMAlignmentReset
// Resetta la macchina a stati
//----------------------------------------------------------------------------------
void SMBase::SMAlignmentReset()
{
	SR->CheckCover( false );

	controlPanel->SetState( PANEL_ALIGNMENT );

	// avoid to save not congruent data
	SR->DB->LoadFiducialParams();

	wxProductionPanel *panel = (wxProductionPanel *)currentPanel;
	panel->ShowTemplatePanel( false );
	panel->ShowManualCheck( false );
	panel->ShowFiducialButton( true );
	panel->ShowAlignmentPanel( false );
}

//----------------------------------------------------------------------------------
// SMAlignment
// Macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMAlignment( int nextState )
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
		case ALIGNMENT_STATE_INIT0:
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

			if( panel->IsFiducialReviewSelected() )
			{
				currentFiducial = FIDUCIAL_ROT1;
				fiducialSearchTerminated = false;

				camera->EnableRightClickOnMain( false );
				camera->EnableWheelOnMain( true );

				if( SMAlignment( ALIGNMENT_STATE_REVIEW_TEACH ) == SR_ERROR )
					return SR_ERROR;
			}
			else
			{
				camera->EnableRightClickOnMain( true );
				camera->EnableWheelOnMain( true );

				if( SMAlignment( ALIGNMENT_STATE_INIT1 ) == SR_ERROR )
					return SR_ERROR;
			}
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_INIT1:
			// Move the board inside the machine
			if( LoadBoardCameraCheck() == SR_ERROR )
			{
				smartLogger->Write( MSG_LOADERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// draw empty workplace
			camera->DrawWorkplace();

			// check whether the PCB position is equal to zero
			isExistingProduction = ( SR->DB->ProductionDataS.PCBPosX == 0.0 && ( SR->DB->FiducialParamsS[FIDUCIAL_ROT1].X != 0.0 || SR->DB->FiducialParamsS[FIDUCIAL_ROT1].Y != 0.0 ) ) ? true : false;

			// Move the board to reaches the frame
			if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.PlateMovement + SR->DB->ProductionDataS.PlateMovementDelta, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			controlPanel->SetState( PANEL_ALIGNMENT );
			smartLogger->Write( MSG_ALIGNFRAME );

			// set state
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_INIT2:
			// We assure the frame is correctly locked
			if( SR->SetOutput( OUTPUT_FRAMEUNLOCK, false ) == SR_ERROR )
			{
				smartLogger->Write( MSG_FRAMELOCKERROR, MSG_ERROR );
				return SR_ERROR;
			}
			// Move the board to reaches the camera focus
			if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			offsetR1X = 0.0;
			offsetR1Y = 0.0;
			offsetR2X = 0.0;
			offsetR2Y = 0.0;

			// Information about board position teaching
			wxMessageBox( MSG_ALIGNBOARDTEACH, MACHINE_NAME, wxOK | wxICON_INFORMATION, parent );
			if( SMAlignment( ALIGNMENT_STATE_LEFTBORDER ) == SR_ERROR )
				return SR_ERROR;
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_LEFTBORDER:
			// PCB low border is always the Y conveyor edge
			SR->DB->ProductionDataS.PCBPosY = SR->DB->MachineParamsS.ConvEdgeY;

			// If if the first time, move camera to the theorical PCB left border...
			if( SR->DB->ProductionDataS.PCBPosX == 0.0 )
			{
				retVal = SR->MoveCameraAndWait( SR->DB->MachineParamsS.ConvEdgeX - SR->DB->ProductionDataS.PCBX/2, SR->DB->ProductionDataS.PCBPosY + SR->DB->ProductionDataS.PCBY/2.0f, ABS_MOVE );
			}
			else
			{
				// this isn't the first time then use the last position
				retVal = SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX, SR->DB->ProductionDataS.PCBPosY + SR->DB->ProductionDataS.PCBY/2.0f, ABS_MOVE );
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

			// Start live video
			camera->SetMainMode( MAIN_CAMERA_CUR );
			camera->SetAuxMode( AUX_CAMPOSITION );
			camera->StartCapture();
			isAuxVideoClickEnable = true;
			controlPanel->SetState( PANEL_MOVE_CAMERA, PANEL_OUTPUT_NONE );

			smartLogger->Write( MSG_ALIGNLEFTEDGE );

			// sets controls state
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_DRAWBOARD:
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

			// draw board
			camera->DrawWorkplace( SR->DB->ProductionDataS.PCBPosX, SR->DB->ProductionDataS.PCBPosY, SR->DB->ProductionDataS.PCBX, SR->DB->ProductionDataS.PCBY );

			if( SR->DB->WorkingModesS.FiducialSearch == FIDUCIAL_AUTO )
			{
				// ask about alignment start
				alignmentTypeDialog = new wxAlignmentTypeDialog( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize );

				// set last used search mode
				if( SR->DB->FiducialParamsS[FIDUCIAL_ROT1_A].X != 0.0 && SR->DB->FiducialParamsS[FIDUCIAL_ROT1_A].Y != 0.0 )
				{
					if( SR->DB->FiducialParamsS[FIDUCIAL_ROT1].SearchMode == SEARCH_MODE_TEMPLATE )
						alignmentTypeDialog->SetLastUsedMethod( ALIGNMENTTYPE_TEMPLATE );
					else
						alignmentTypeDialog->SetLastUsedMethod( ALIGNMENTTYPE_VECTORIAL );
				}
				
				alignmentType = alignmentTypeDialog->ShowModal();
				delete alignmentTypeDialog;
				// set manual check status
				panel->SetManualCheckValue( alignmentType == ALIGNMENTTYPE_TEMPLATE ? true : false );
			}
			else
			{
				// information about alignment start
				wxMessageBox( MSG_ALIGNSTART, MACHINE_NAME, wxOK | wxICON_INFORMATION, parent );
				// set manual check to true
				panel->SetManualCheckValue( true );
			}

			// init values for alignment
			currentFiducial = FIDUCIAL_ROT1_A;
			fiducialSearchTerminated = false;

			if( SMAlignment( ALIGNMENT_STATE_MOVE_A ) == SR_ERROR )
				return SR_ERROR;
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_MOVE_A:
			camera->SetMainMode( MAIN_BLANK );
			camera->SetAuxMode( AUX_BLANK );

			// needs if PREV button is pressed
			if( currentFiducial == FIDUCIAL_ROT1_FRAME_A )
				currentFiducial = FIDUCIAL_ROT1_A;
			else if( currentFiducial == FIDUCIAL_ROT2_FRAME_A )
				currentFiducial = FIDUCIAL_ROT2_A;
			else if( currentFiducial == FIDUCIAL_TRA_FRAME_A )
				currentFiducial = FIDUCIAL_TRA_A;

			SR->DB->SetFiducialParams( currentFiducial );
			mainVideo->UpdateControl();
			panel->UpdatePanel();

			// Move camera...
			if( SR->DB->FiducialParamsS[currentFiducial].X == 0.0 || SR->DB->FiducialParamsS[currentFiducial].Y == 0.0 )
			{
				// this is the first time...
				if( currentFiducial == FIDUCIAL_ROT1_A )
				{
					// this is the first fiducial then move to the pcb center position
					retVal = SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX + SR->DB->ProductionDataS.PCBX/2.0f, SR->DB->ProductionDataS.PCBPosY + SR->DB->ProductionDataS.PCBY/2.0f, ABS_MOVE );
				}
				else
				{
					// do nothing
					retVal = SR_OK;
				}
			}
			else
			{
				// this isn't the first time then move to the old position
				retVal = SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX + SR->DB->FiducialParamsS[currentFiducial].X, SR->DB->ProductionDataS.PCBPosY + SR->DB->FiducialParamsS[currentFiducial].Y, ABS_MOVE );
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
			if( currentFiducial == FIDUCIAL_ROT1_A )
			{
				if( SR->DB->WorkingModesS.FiducialSearch == FIDUCIAL_MANUAL )
					panel->EnableManualCheck( false );
				else if( alignmentType == ALIGNMENTTYPE_TEMPLATE )
					panel->EnableManualCheck( false );
				else if( SR->DB->WorkingModesS.FiducialOnFrame )
					panel->EnableManualCheck( false );
				else
					panel->EnableManualCheck( true );
				panel->ShowManualCheck( true );
			}
			panel->ShowAlignmentPanel( false );

			// Start live video
			camera->SetMainMode( MAIN_CAMERA_MOVE );
			camera->SetAuxMode( AUX_CAMPOSITION );
			camera->StartCapture();

			controlPanel->SetState( PANEL_MOVE_CAMERA, PANEL_OUTPUT_NONE );
			isAuxVideoClickEnable = true;

			if( currentFiducial == FIDUCIAL_ROT1_A )
				smartLogger->Write( MSG_ALIGNMOVE1FID );
			else if( currentFiducial == FIDUCIAL_ROT2_A )
				smartLogger->Write( MSG_ALIGNMOVE2FID );
			else if( currentFiducial == FIDUCIAL_TRA_A )
				smartLogger->Write( MSG_ALIGNMOVE3FID );

			// sets controls state
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_TEACH_A:
			// check the position of the second point (rotation) to avoid singularity...
			if( currentFiducial == FIDUCIAL_ROT2_A )
			{
				// Get current camera coords
				SR->GetCameraPosition( camPos.X, camPos.Y );

				MACHINE_CONFIG( MACHINE_ENABLE )
					if( abs( camPos.X - (SR->DB->ProductionDataS.PCBPosX + SR->DB->FiducialParamsS[FIDUCIAL_ROT1_A].X) ) < ALIGNMENT_ROTATION_DIFF &&
						abs( camPos.Y - (SR->DB->ProductionDataS.PCBPosY + SR->DB->FiducialParamsS[FIDUCIAL_ROT1_A].Y) ) < ALIGNMENT_ROTATION_DIFF )
					{
						wxMessageBox( MSG_ALIGNSAMEPOINT, MACHINE_NAME, wxOK | wxICON_INFORMATION, parent );
						return SMAlignment( ALIGNMENT_STATE_MOVE_A );
					}
				MACHINE_CONFIG_END
			}

			panel->EnableManualCheck( false );

			//ADD
			{
				// save old values
				int down_fiducial_search_mode = SR->DB->pCurrentFiducial->SearchMode;
				int down_fiducial_circle_diameter = SR->DB->pCurrentFiducial->CircleDiameter;
				int down_fiducial_rectangle_x = SR->DB->pCurrentFiducial->RectangleSideX;
				int down_fiducial_rectangle_y = SR->DB->pCurrentFiducial->RectangleSideY;
				int down_fiducial_tolerance = SR->DB->pCurrentFiducial->Tolerance;

				SR->DB->SetFiducialParams( currentFiducial );
				antiReflects(currentFiducial);
				// if fiducial is on frame then set the values of the PCB one
				if( !IsFiducialOnPCB( currentFiducial ) )
				{
					SR->DB->pCurrentFiducial->SearchMode = down_fiducial_search_mode;
					SR->DB->pCurrentFiducial->CircleDiameter = down_fiducial_circle_diameter;
					SR->DB->pCurrentFiducial->RectangleSideX = down_fiducial_rectangle_x;
					SR->DB->pCurrentFiducial->RectangleSideY = down_fiducial_rectangle_y;
					SR->DB->pCurrentFiducial->Tolerance = down_fiducial_tolerance;
				}
			}

			mainVideo->UpdateControl();

			if( SR->DB->pCurrentFiducial->SearchMode != SEARCH_MODE_CIRCLE && SR->DB->pCurrentFiducial->SearchMode != SEARCH_MODE_RECTANGLE )
			{
				SR->DB->pCurrentFiducial->SearchMode = SEARCH_MODE_CIRCLE;
			}

			if( !panel->GetManualCheck() )
			{
				panel->UpdatePanel();
				panel->ShowAlignmentPanel( true );
				panel->EnableAlignmentPanel( true );

				panel->EnableShapeCombo( IsFiducialOnPCB( currentFiducial ) ? true : false );
			}

			// Plate down for reflects
			antiReflects(currentFiducial);

			retVal = IsFiducialOnPCB( currentFiducial ) ? SR->SetCamera( CAMERA_DOWN ) : SR->SetCamera( CAMERA_UP );
			if( retVal == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			// Start live video
			camera->StartCapture();
			camera->SetAuxMode( AUX_SMOOTH_EDGE );

			if( !panel->GetManualCheck() )
			{
				camera->SetMainMode( MAIN_MOUSE_CUR );
				smartLogger->Write( MSG_CLICKFIDUCIAL );
			}
			else
			{
				camera->SetMainShape();
				camera->SetMainMode( MAIN_MOUSE_CUR_MANUAL );
				smartLogger->Write( MSG_FIDMANUALTEACH );
			}

			datasette->StopEnable( true );
			datasette->PrevEnable( true );
			isMainVideoClickEnable = true;
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_SEARCH_A:
			// Get frames and stop video
			camera->SetMainMode( MAIN_NO_CUR );
			if( !panel->GetManualCheck() ){
				myMilliSleep( FLICKERING_DELAY );
				camera->GetFrames( MAX_FRAMES_FIDUCIAL );
			}
			camera->StopCapture();

			// Disable camera
			if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			if( !panel->GetManualCheck() )
			{
				// Call function to get the center of the fiducial...
				if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_CIRCLE )
				{
					if( camera->FindCircle2( xClicked, yClicked, centerX, centerY, circleR ) == SR_OK )
					{
						smartLogger->Write( wxString::Format( MSG_FIDFOUND_CIRCLE, centerX, centerY, circleR ) );
						if( SMAlignment( ALIGNMENT_STATE_FOUND_WAIT_A ) == SR_ERROR )
							return SR_ERROR;
						break;
					}
				}
				else if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_RECTANGLE )
				{
					if( camera->FindRectangle( xClicked, yClicked, centerX, centerY, rectangleX, rectangleY ) == SR_OK )
					{
						smartLogger->Write( wxString::Format( MSG_FIDFOUND_RECT, centerX, centerY, rectangleX, rectangleY ) );
						if( SMAlignment( ALIGNMENT_STATE_FOUND_WAIT_A ) == SR_ERROR )
							return SR_ERROR;
						break;
					}
				}

				// Fiducial not found
				smartLogger->Write( MSG_FIDNOTFOUND, MSG_ERROR );
				// Notify manual fiducial search
				wxMessageBox( MSG_FIDUCIALMANUAL, MACHINE_NAME, wxOK | wxICON_WARNING, parent );

				// Manual fiducial search
				smartLogger->Write( MSG_FIDMANUALTEACH );
				camera->SetMainShape();
				camera->SetMainMode( MAIN_MOUSE_CUR_MANUAL );
				datasette->StopEnable( true );
				datasette->PrevEnable( true );
				// Enable mouse click
				isMainVideoClickEnable = true;
			}
			else
			{
				centerX = xClicked;
				centerY = yClicked;

				camera->GetMainShape();

				if( SMAlignment( ALIGNMENT_STATE_FOUND_WAIT_A ) == SR_ERROR )
					return SR_ERROR;
			}
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_FOUND_WAIT_A:
			// sets controls state
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			datasette->PrevEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_FOUND_A:
			antiReflects(currentFiducial);
			// Get current camera coords
			SR->GetCameraPosition( camPos.X, camPos.Y );
			// At this point, we have the fiducial coords (manual or auto...)
			if( IsFiducialOnPCB( currentFiducial ) )
			{
				SR->DB->FiducialParamsS[currentFiducial].X = camPos.X + (centerX - CAM_W / 2) * SR->DB->MachineParamsS.DnXPixMm;
				SR->DB->FiducialParamsS[currentFiducial].Y = camPos.Y - (centerY - CAM_H / 2) * SR->DB->MachineParamsS.DnYPixMm;
			}
			else
			{
				SR->DB->FiducialParamsS[currentFiducial].X = camPos.X + (centerX - CAM_W / 2) * SR->DB->MachineParamsS.UpXPixMm;
				SR->DB->FiducialParamsS[currentFiducial].Y = camPos.Y - (centerY - CAM_H / 2) * SR->DB->MachineParamsS.UpYPixMm;
			}
			// refers position to the PCB origin
			SR->DB->FiducialParamsS[currentFiducial].X -= SR->DB->ProductionDataS.PCBPosX;
			SR->DB->FiducialParamsS[currentFiducial].Y -= SR->DB->ProductionDataS.PCBPosY;
			// reset unused values
			SR->DB->FiducialParamsS[currentFiducial].DeltaX = 0.0;
			SR->DB->FiducialParamsS[currentFiducial].DeltaY = 0.0;

			if( currentFiducial == FIDUCIAL_ROT1_A )
				SR->GetOffset( camPos.X, camPos.Y, offsetR1X, offsetR1Y );
			else if( currentFiducial == FIDUCIAL_ROT2_A )
				SR->GetOffset( camPos.X, camPos.Y, offsetR2X, offsetR2Y );

			// switch to next fiducial
			if( currentFiducial == FIDUCIAL_ROT1_A )
				currentFiducial = FIDUCIAL_ROT1_FRAME_A;
			else if( currentFiducial == FIDUCIAL_ROT2_A )
				currentFiducial = FIDUCIAL_ROT2_FRAME_A;
			else if( currentFiducial == FIDUCIAL_TRA_A )
				currentFiducial = FIDUCIAL_TRA_FRAME_A;
			else if( currentFiducial == FIDUCIAL_ROT1_FRAME_A )
				currentFiducial = FIDUCIAL_ROT2_A;
			else if( currentFiducial == FIDUCIAL_ROT2_FRAME_A )
				currentFiducial = FIDUCIAL_TRA_A;
			else if( currentFiducial == FIDUCIAL_TRA_FRAME_A )
				fiducialSearchTerminated = true;

			if( fiducialSearchTerminated )
			{
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

				// Save fiducials params
				SR->DB->SaveFiducialParams();

				// apply TRA correction
				if( SMAlignment( ALIGNMENT_STATE_TRA_A ) == SR_ERROR )
					return SR_ERROR;

				retVal = wxNO;
				MACHINE_CONFIG( VISION_VERIFY_ENABLE )
				retVal = wxMessageBox( MSG_ALIGNVERIFYVISIONQ, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, parent );
				MACHINE_CONFIG_END

				if( retVal == wxYES )
				{
					if( SMAlignment( ALIGNMENT_STATE_TEACH_VERIFY ) == SR_ERROR )
						return SR_ERROR;
				}
				else
				{
					if( SMAlignment( ALIGNMENT_STATE_VERIFY ) == SR_ERROR )
						return SR_ERROR;
				}
			}
			else
			{
				if( currentFiducial == FIDUCIAL_TRA_A )
				{
					// Stop live video
					camera->StopCapture();
					camera->SetMainMode( MAIN_BLANK );
					camera->SetAuxMode( AUX_BLANK );

					// Disable camera
					if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
					{
						smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
						return SR_ERROR;
					}

					// apply ROT correction
					if( SMAlignment( ALIGNMENT_STATE_ROT_A ) == SR_ERROR )
						return SR_ERROR;
				}
				antiReflects(currentFiducial);
				if( IsFiducialOnPCB( currentFiducial ) )
				{
					if( SMAlignment( ALIGNMENT_STATE_MOVE_A ) == SR_ERROR )
						return SR_ERROR;
				}
				else
				{
					if( SMAlignment( ALIGNMENT_STATE_TEACH_A ) == SR_ERROR )
						return SR_ERROR;
				}
			}
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_ROT_A:
			// Calc frame rotation
			if( ((SR->DB->FiducialParamsS[FIDUCIAL_ROT2_FRAME_A].Y + offsetR2Y) - (SR->DB->FiducialParamsS[FIDUCIAL_ROT1_FRAME_A].Y + offsetR1Y) == 0) && ((SR->DB->FiducialParamsS[FIDUCIAL_ROT2_FRAME_A].X + offsetR2X) - (SR->DB->FiducialParamsS[FIDUCIAL_ROT1_FRAME_A].X + offsetR1X) == 0) )
				frameRot = 0.0;
			else
				frameRot = atan2( (SR->DB->FiducialParamsS[FIDUCIAL_ROT2_FRAME_A].Y + offsetR2Y) - (SR->DB->FiducialParamsS[FIDUCIAL_ROT1_FRAME_A].Y + offsetR1Y), (SR->DB->FiducialParamsS[FIDUCIAL_ROT2_FRAME_A].X + offsetR2X) - (SR->DB->FiducialParamsS[FIDUCIAL_ROT1_FRAME_A].X + offsetR1X) );
			frameRot = frameRot * 180 / PI;

			// Calc board rotation
			if( (SR->DB->FiducialParamsS[FIDUCIAL_ROT2_A].Y - SR->DB->FiducialParamsS[FIDUCIAL_ROT1_A].Y == 0) && (SR->DB->FiducialParamsS[FIDUCIAL_ROT2_A].X - SR->DB->FiducialParamsS[FIDUCIAL_ROT1_A].X == 0) )
				boardRot = 0.0;
			else
				boardRot = atan2( SR->DB->FiducialParamsS[FIDUCIAL_ROT2_A].Y - SR->DB->FiducialParamsS[FIDUCIAL_ROT1_A].Y, SR->DB->FiducialParamsS[FIDUCIAL_ROT2_A].X - SR->DB->FiducialParamsS[FIDUCIAL_ROT1_A].X );
			boardRot = boardRot * 180 / PI;

			boardRot = frameRot - boardRot;

			if( SR->RotateTableAndWait( boardRot ) == SR_ERROR )
			{
				smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Save actual board rotation
			SR->DB->ProductionDataS.LastRot = boardRot;

			smartLogger->Write( wxString::Format( MSG_ROTDONE, boardRot ), MSG_SUCCESS );
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_TRA_A:
			SR->GetOffset( camPos.X, camPos.Y, offsetX, offsetY );

			boardTra.X = SR->DB->FiducialParamsS[FIDUCIAL_TRA_FRAME_A].X - SR->DB->FiducialParamsS[FIDUCIAL_TRA_A].X + offsetX;
			boardTra.Y = SR->DB->FiducialParamsS[FIDUCIAL_TRA_FRAME_A].Y - SR->DB->FiducialParamsS[FIDUCIAL_TRA_A].Y + offsetY;

			if( SR->MoveXYTableAndWait( boardTra.X, boardTra.Y, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Save actual board translations
			SR->DB->ProductionDataS.LastX = boardTra.X;
			SR->DB->ProductionDataS.LastY = boardTra.Y;

			smartLogger->Write( wxString::Format( MSG_TRASLDONE, boardTra.X, boardTra.Y ), MSG_SUCCESS );
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_VERIFY:
			// stop live video
			camera->StopCapture();
			camera->SetMainMode( MAIN_BLANK );
			camera->SetAuxMode( AUX_BLANK );

			// Move camera in home position
			if( SR->MoveCameraAndWait( (SR->DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit - SR->DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit)/2, SR->DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				return SR_ERROR;
			}
			// Move the board to reaches the frame
			if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.PlateMovement + SR->DB->ProductionDataS.PlateMovementDelta, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			smartLogger->Write( MSG_ALIGNVERIFY );

			// sets controls state
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_CHECK:
			smartLogger->Write( MSG_ALIGNENDED, MSG_SUCCESS );

			// if printing manual teach is true then terminate
			if( SR->DB->WorkingModesS.FiducialSearch == FIDUCIAL_MANUAL )
			{
				// save PCB position
				SR->DB->SaveProductionData();
				// save fiducial for printing
				CopyFiducials();
				SR->DB->SaveFiducialParams();
				// adjust verify points
				if( isExistingProduction )
					SR->DB->AdjustVerifyPoints( SR->DB->ProductionDataS.PCBPosX, SR->DB->ProductionDataS.PCBPosY );

				if( SMAlignment( ALIGNMENT_STATE_SQUEEGEES_ZERO ) == SR_ERROR )
					return SR_ERROR;
				break;
			}

			// if search mode is vectorial and fiducial on frame is true then terminate
			if( alignmentType == ALIGNMENTTYPE_VECTORIAL && SR->DB->WorkingModesS.FiducialOnFrame )
			{
				// save PCB position
				SR->DB->SaveProductionData();
				// save fiducial for printing
				CopyFiducials();
				SR->DB->SaveFiducialParams();
				// adjust verify points
				if( isExistingProduction )
					SR->DB->AdjustVerifyPoints( SR->DB->ProductionDataS.PCBPosX, SR->DB->ProductionDataS.PCBPosY );

				if( SMAlignment( ALIGNMENT_STATE_SQUEEGEES_ZERO ) == SR_ERROR )
					return SR_ERROR;
				break;
			}

			// from here: PCB without fiducial on frame or/and search mode template
			panel->ShowManualCheck( false );

			wxMessageBox( MSG_FIDUCIALTEACHSTART, MACHINE_NAME, wxOK | wxICON_INFORMATION, parent );

			currentFiducial = FIDUCIAL_ROT1;
			fiducialSearchTerminated = false;

			if( SMAlignment( ALIGNMENT_STATE_FID_MOVE ) == SR_ERROR )
				return SR_ERROR;
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_FID_MOVE:
			camera->SetMainMode( MAIN_BLANK );
			camera->SetAuxMode( AUX_BLANK );

			// needs if PREV button is pressed
			if( currentFiducial == FIDUCIAL_ROT1_FRAME )
				currentFiducial = FIDUCIAL_ROT1;
			else if( currentFiducial == FIDUCIAL_ROT2_FRAME )
				currentFiducial = FIDUCIAL_ROT2;
			else if( currentFiducial == FIDUCIAL_TRA_FRAME )
				currentFiducial = FIDUCIAL_TRA;

			//ADD
			SR->DB->SetFiducialParams( currentFiducial );
			mainVideo->UpdateControl();

			// Move the board to reaches the camera focus
			if( currentFiducial == FIDUCIAL_ROT1 )
			{
				if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
				{
					smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
					return SR_ERROR;
				}
			}

			// Move camera...
			if( SR->DB->FiducialParamsS[currentFiducial].X == 0.0 || SR->DB->FiducialParamsS[currentFiducial].Y == 0.0 )
			{
				// this is the first time...
				if( currentFiducial == FIDUCIAL_ROT1 )
				{
					// this is the first fiducial then move to the pcb center position
					double x = ( SR->DB->ProductionDataS.PCBX == 0.0f ) ? WORKPLACE_CENTER_X : SR->DB->ProductionDataS.PCBPosX + SR->DB->ProductionDataS.PCBX/2.0f;
					double y = ( SR->DB->ProductionDataS.PCBY == 0.0f ) ? WORKPLACE_CENTER_Y : SR->DB->ProductionDataS.PCBPosY + SR->DB->ProductionDataS.PCBY/2.0f;
					retVal = SR->MoveCameraAndWait( x, y, ABS_MOVE );
				}
				else
				{
					// do nothing
					retVal = SR_OK;
				}
			}
			else
			{
				// this isn't the first time then move to the old position
				if( isExistingProduction )
					retVal = SR->MoveCameraAndWait( SR->DB->FiducialParamsS[currentFiducial].X, SR->DB->FiducialParamsS[currentFiducial].Y, ABS_MOVE );
				else
					retVal = SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX + SR->DB->FiducialParamsS[currentFiducial].X, SR->DB->ProductionDataS.PCBPosY + SR->DB->FiducialParamsS[currentFiducial].Y, ABS_MOVE );
			}
			if( retVal == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				return SR_ERROR;
			}
			// Plate down for reflects
			antiReflects(currentFiducial);

			// Enable camera
			retVal = IsFiducialOnPCB( currentFiducial ) ? SR->SetCamera( CAMERA_DOWN ) : SR->SetCamera( CAMERA_UP );
			if( retVal == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				return SR_ERROR;
			}

			panel->ShowAlignmentPanel( false );

			// Start live video
			camera->SetMainMode( MAIN_CAMERA_MOVE );
			camera->SetAuxMode( AUX_CAMPOSITION );
			camera->StartCapture();

			controlPanel->SetState( PANEL_MOVE_CAMERA, PANEL_OUTPUT_NONE );
			isAuxVideoClickEnable = true;

			if( currentFiducial == FIDUCIAL_ROT1 )
				smartLogger->Write( MSG_ALIGNMOVE1FID );
			else if( currentFiducial == FIDUCIAL_ROT2 )
				smartLogger->Write( MSG_ALIGNMOVE2FID );
			else if( currentFiducial == FIDUCIAL_TRA )
				smartLogger->Write( MSG_ALIGNMOVE3FID );

			// sets controls state
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_FID_TEACH:
			// check the position of the second point (rotation) to avoid singularity...
			if( currentFiducial == FIDUCIAL_ROT2 )
			{
				// Get current camera coords
				SR->GetCameraPosition( camPos.X, camPos.Y );
				
				MACHINE_CONFIG( MACHINE_ENABLE )
					if( abs( camPos.X - (SR->DB->ProductionDataS.PCBPosX + SR->DB->FiducialParamsS[FIDUCIAL_ROT1].X) ) < ALIGNMENT_ROTATION_DIFF &&
						abs( camPos.Y - (SR->DB->ProductionDataS.PCBPosY + SR->DB->FiducialParamsS[FIDUCIAL_ROT1].Y) ) < ALIGNMENT_ROTATION_DIFF )
					{
						wxMessageBox( MSG_ALIGNSAMEPOINT, MACHINE_NAME, wxOK | wxICON_INFORMATION, parent );
						return SMAlignment( ALIGNMENT_STATE_FID_MOVE );
					}
				MACHINE_CONFIG_END
			}
			antiReflects(currentFiducial);
			if( !IsFiducialOnPCB( currentFiducial ) )
			{
				SR->DB->SetFiducialParams( currentFiducial );
				mainVideo->UpdateControl();
			}
			// Plate down for reflects
			antiReflects(currentFiducial);
			// Enable camera
			retVal = IsFiducialOnPCB( currentFiducial ) ? SR->SetCamera( CAMERA_DOWN ) : SR->SetCamera( CAMERA_UP );
			if( retVal == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Start live video
			camera->StartCapture();
			camera->SetAuxMode( AUX_SMOOTH_EDGE );

			// if template matching is selected...
			if( alignmentType == ALIGNMENTTYPE_TEMPLATE )
			{
				SR->DB->FiducialParamsS[currentFiducial].SearchMode = SEARCH_MODE_TEMPLATE;
				camera->SetTemplateDim( SR->DB->FiducialParamsS[currentFiducial].TemplateDim );

				camera->SetMainMode( MAIN_CAMERA_TEMPLATE );
				smartLogger->Write( MSG_SETTEMPLATE );
				datasette->NextEnable( true );
			}
			else
			{
				if( SR->DB->FiducialParamsS[currentFiducial].SearchMode != SEARCH_MODE_CIRCLE && SR->DB->FiducialParamsS[currentFiducial].SearchMode != SEARCH_MODE_RECTANGLE )
					SR->DB->FiducialParamsS[currentFiducial].SearchMode = SEARCH_MODE_CIRCLE;

				panel->UpdatePanel();
				panel->EnableAlignmentPanel( true );
				panel->ShowAlignmentPanel( true );

				camera->SetMainMode( MAIN_MOUSE_CUR );
				smartLogger->Write( MSG_CLICKFIDUCIAL );
			}

			datasette->StopEnable( true );
			datasette->PrevEnable( true );
			isMainVideoClickEnable = true;
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_FID_SEARCH:
			// Plate down for reflects
			antiReflects(currentFiducial);

			// Get frames and stop video
			camera->SetMainMode( MAIN_NO_CUR );
			myMilliSleep( FLICKERING_DELAY );
			camera->GetFrames( MAX_FRAMES_FIDUCIAL );
			camera->StopCapture();

			// Disable camera
			if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			// Call function to get the center of the fiducial...
			if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_CIRCLE )
			{
				if( camera->FindCircle2( xClicked, yClicked, centerX, centerY, circleR ) == SR_OK )
				{
					smartLogger->Write( wxString::Format( MSG_FIDFOUND_CIRCLE, centerX, centerY, circleR ) );
					if( SMAlignment( ALIGNMENT_STATE_FID_FOUND_WAIT ) == SR_ERROR )
						return SR_ERROR;
					break;
				}
			}
			else if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_RECTANGLE )
			{
				if( camera->FindRectangle( xClicked, yClicked, centerX, centerY, rectangleX, rectangleY ) == SR_OK )
				{
					smartLogger->Write( wxString::Format( MSG_FIDFOUND_RECT, centerX, centerY, rectangleX, rectangleY ) );
					if( SMAlignment( ALIGNMENT_STATE_FID_FOUND_WAIT ) == SR_ERROR )
						return SR_ERROR;
					break;
				}
			}
			else if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_TEMPLATE )
			{
				SR->DB->FiducialParamsS[currentFiducial].TemplateDim = camera->GetTemplateDim() & 0xFFFFFFFC;

				centerX = CAM_W / 2;
				centerY = CAM_H / 2;
			
				if( SMAlignment( ALIGNMENT_STATE_FID_FOUND ) == SR_ERROR )
					return SR_ERROR;
				break;
			}

			// Fiducial not found
			smartLogger->Write( MSG_FIDNOTFOUND, MSG_ERROR );
			// Notify manual fiducial search
			wxMessageBox( MSG_FIDUCIALMANUAL, MACHINE_NAME, wxOK | wxICON_WARNING, parent );

			// Manual fiducial search
			smartLogger->Write( MSG_FIDMANUALTEACH );
			camera->SetMainShape();
			camera->SetMainMode( MAIN_MOUSE_CUR_MANUAL );
			datasette->StopEnable( true );
			datasette->PrevEnable( true );
			// Enable mouse click
			isMainVideoClickEnable = true;
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_FID_FOUND_WAIT:
			// sets controls state
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			datasette->PrevEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_FID_FOUND:
			antiReflects(currentFiducial);
			// Get current camera coords
			SR->GetCameraPosition( camPos.X, camPos.Y );
			// At this point, we have the fiducial coords (manual or auto...)
			if( IsFiducialOnPCB( currentFiducial ) )
			{
				SR->DB->FiducialParamsS[currentFiducial].X = camPos.X + (centerX - CAM_W / 2) * SR->DB->MachineParamsS.DnXPixMm;
				SR->DB->FiducialParamsS[currentFiducial].Y = camPos.Y - (centerY - CAM_H / 2) * SR->DB->MachineParamsS.DnYPixMm;
			}
			else
			{
				SR->DB->FiducialParamsS[currentFiducial].X = camPos.X + (centerX - CAM_W / 2) * SR->DB->MachineParamsS.UpXPixMm;
				SR->DB->FiducialParamsS[currentFiducial].Y = camPos.Y - (centerY - CAM_H / 2) * SR->DB->MachineParamsS.UpYPixMm;
			}
			// refers position to the PCB origin
			SR->DB->FiducialParamsS[currentFiducial].X -= SR->DB->ProductionDataS.PCBPosX;
			SR->DB->FiducialParamsS[currentFiducial].Y -= SR->DB->ProductionDataS.PCBPosY;

			// switch to next fiducial
			if( currentFiducial == FIDUCIAL_ROT1 )
				currentFiducial = SR->DB->WorkingModesS.FiducialOnFrame ? FIDUCIAL_ROT1_FRAME : FIDUCIAL_ROT2;
			else if( currentFiducial == FIDUCIAL_ROT2 )
				currentFiducial = SR->DB->WorkingModesS.FiducialOnFrame ? FIDUCIAL_ROT2_FRAME : FIDUCIAL_TRA;
			else if( currentFiducial == FIDUCIAL_TRA )
			{
				if( SR->DB->WorkingModesS.FiducialOnFrame )
					currentFiducial = FIDUCIAL_TRA_FRAME;
				else
					fiducialSearchTerminated = true;
			}
			else if( currentFiducial == FIDUCIAL_ROT1_FRAME )
				currentFiducial = FIDUCIAL_ROT2;
			else if( currentFiducial == FIDUCIAL_ROT2_FRAME )
				currentFiducial = FIDUCIAL_TRA;
			else if( currentFiducial == FIDUCIAL_TRA_FRAME )
				fiducialSearchTerminated = true;

			if( fiducialSearchTerminated )
			{
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

				// Save fiducials params
				SR->DB->SaveFiducialParams();

				// teach fiducials again to minimize the errors due to encoders lack
				currentFiducial = FIDUCIAL_ROT1;
				fiducialSearchTerminated = false;
				if( SMAlignment( ALIGNMENT_STATE_AGAIN_SEARCH ) == SR_ERROR )
					return SR_ERROR;
			}
			else
			{
				antiReflects(currentFiducial);
				if( IsFiducialOnPCB( currentFiducial ) )
				{
					if( SMAlignment( ALIGNMENT_STATE_FID_MOVE ) == SR_ERROR )
						return SR_ERROR;
				}
				else
				{
					if( SMAlignment( ALIGNMENT_STATE_FID_TEACH ) == SR_ERROR )
						return SR_ERROR;
				}
			}
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_RESET:
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
			SR->DB->LoadFiducialParams();

			panel->ShowTemplatePanel( false );
			panel->ShowManualCheck( false );
			panel->ShowFiducialButton( true );
			panel->ShowAlignmentPanel( false );
			
			toolBox->Enable( true );
			menuBtn->Enable( true );
			datasette->StartEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_TEACH_VERIFY:
			// Enable camera
			if( SR->SetCamera( CAMERA_DOWN ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Start live video
			camera->SetMainMode( MAIN_CAMERA_VERIFY );
			camera->SetAuxMode( AUX_CAMPOSITION );
			camera->StartCapture();

			controlPanel->SetState( PANEL_CAMERA_VERIFY );

			// Disable mouse click
			isMainVideoClickEnable = false;
			isAuxVideoClickEnable = true;

			smartLogger->Write( MSG_ALIGNVERIFYVISION );

			// sets controls state
			datasette->StopEnable( true );
			datasette->NextEnable( true );

			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_SQUEEGEES_ZERO:
			// Ask for squeegees zero teach
			if( wxMessageBox( MSG_ASKSQUEEGEESZTEACH, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, parent ) != wxYES )
			{
				if( SMAlignment( ALIGNMENT_STATE_SQUEEGEES_MOVE ) == SR_ERROR )
					return SR_ERROR;
				break;
			}
			smartLogger->Write( MSG_SQUEEGEESZERO );

			controlPanel->SetState( PANEL_TEACH_SQUEEGEES );
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			datasette->PrevEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_SQUEEGEES_ZERO_SAVE:
			// Deactivate squeegees
			if( SR->SetOutput( OUTPUT_SQUEEGEESFRONT, false ) == SR_ERROR )
			{
				smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			if( SR->SetOutput( OUTPUT_SQUEEGEESREAR, false ) == SR_ERROR )
			{
				smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
				SR->ErrorManagement();
			}

			// save squeegees zero
			SR->DB->ProductionDataS.SqueegeesZeroMove = SR->SqueegeesMotor.GetPosition();
			SR->DB->SaveProductionData();

			if( SMAlignment( ALIGNMENT_STATE_SQUEEGEES_MOVE ) == SR_ERROR )
				return SR_ERROR;
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_SQUEEGEES_MOVE:
			// Ask for squeegees movement teach
			if( wxMessageBox( MSG_ASKSQUEEGEESMTEACH, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, parent ) != wxYES )
			{
				wxMessageBox( wxString::Format( "%s\n%s", MSG_ALIGNFIDENDED, MSG_ALIGNFIDENDEDNEXT1 ), MACHINE_NAME, wxOK | wxICON_INFORMATION, parent );

				if( SMAlignment( ALIGNMENT_STATE_RESET ) == SR_ERROR )
					return SR_ERROR;
				break;
			}
			smartLogger->Write( MSG_SQUEEGEESMOVE );

			controlPanel->SetState( PANEL_TEACH_SQUEEGEES );
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			datasette->PrevEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_SQUEEGEES_MOVE_SAVE:
			// Deactivate squeegees
			if( SR->SetOutput( OUTPUT_SQUEEGEESFRONT, false ) == SR_ERROR )
			{
				smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
				SR->ErrorManagement();
			}
			if( SR->SetOutput( OUTPUT_SQUEEGEESREAR, false ) == SR_ERROR )
			{
				smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
				SR->ErrorManagement();
			}

			// save squeegees movement
			SR->DB->ProductionDataS.SqueegeesMove = SR->SqueegeesMotor.GetPosition() - SR->DB->ProductionDataS.SqueegeesZeroMove;
			SR->DB->SaveProductionData();

			wxMessageBox( wxString::Format( "%s\n%s", MSG_ALIGNFIDENDED, MSG_ALIGNFIDENDEDNEXT1 ), MACHINE_NAME, wxOK | wxICON_INFORMATION, parent );

			if( SMAlignment( ALIGNMENT_STATE_RESET ) == SR_ERROR )
				return SR_ERROR;
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_MOVE_T2:
			camera->StopCapture();
			camera->SetMainMode( MAIN_BLANK );
			camera->SetAuxMode( AUX_BLANK );

			// if this is the first fiducial...
			if( currentFiducial == FIDUCIAL_ROT1 )
			{
				// if template matching check image existance
				if( SR->DB->FiducialParamsS[FIDUCIAL_ROT1].SearchMode == SEARCH_MODE_TEMPLATE )
				{
					if( CheckTemplateImage() == false )
					{
						wxMessageBox( MSG_NOTEMPLATEIMAGE, MACHINE_NAME, wxOK | wxICON_ERROR, parent );

						if( SMPrinting( PRINTING_STATE_RESET ) == SR_ERROR )
							return SR_ERROR;
						break;
					}
				}
			}

			// Move camera...
			if( currentFiducial == FIDUCIAL_ROT1 )
				retVal = SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX + SR->DB->FiducialParamsS[FIDUCIAL_ROT1_FRAME].X, SR->DB->ProductionDataS.PCBPosY + SR->DB->FiducialParamsS[FIDUCIAL_ROT1_FRAME].Y, ABS_MOVE );
			else if( currentFiducial == FIDUCIAL_ROT2 )
				retVal = SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX + SR->DB->FiducialParamsS[FIDUCIAL_ROT2_FRAME].X + table2PosErr.X, SR->DB->ProductionDataS.PCBPosY + SR->DB->FiducialParamsS[FIDUCIAL_ROT2_FRAME].Y + table2PosErr.Y, ABS_MOVE );
			else if( currentFiducial == FIDUCIAL_TRA )
				retVal = SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX + SR->DB->FiducialParamsS[FIDUCIAL_TRA_FRAME].X + table2PosErr.X, SR->DB->ProductionDataS.PCBPosY + SR->DB->FiducialParamsS[FIDUCIAL_TRA_FRAME].Y + table2PosErr.Y, ABS_MOVE );
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

			SR->DB->SetFiducialParams( currentFiducial );
			mainVideo->UpdateControl();

			// Start live video
			camera->SetMainMode( MAIN_CAMERA_MOVE );
			camera->SetAuxMode( AUX_CAMPOSITION );
			camera->StartCapture();

			controlPanel->SetState( PANEL_MOVE_CAMERA, PANEL_OUTPUT_NONE );
			isAuxVideoClickEnable = true;

			if( currentFiducial == FIDUCIAL_ROT1 )
				smartLogger->Write( MSG_ALIGNMOVE1FID );
			else if( currentFiducial == FIDUCIAL_ROT2 )
				smartLogger->Write( MSG_ALIGNMOVE2FID );
			else if( currentFiducial == FIDUCIAL_TRA )
				smartLogger->Write( MSG_ALIGNMOVE3FID );

			// sets controls state
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_TEACH_T2:
			// Enable camera
			if( SR->SetCamera( CAMERA_DOWN ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Start live video
			camera->SetAuxMode( AUX_SMOOTH_EDGE );
			camera->StartCapture();

			if( SR->DB->WorkingModesS.FiducialSearch == FIDUCIAL_AUTO )
			{
				camera->SetMainMode( MAIN_MOUSE_CUR );
				smartLogger->Write( MSG_CLICKFIDUCIAL );
				
				if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_TEMPLATE )
				{
					if( SMAlignment( ALIGNMENT_STATE_SEARCH_T2 ) == SR_ERROR )
						return SR_ERROR;
					break;
				}
			}
			else
			{
				camera->SetMainMode( MAIN_MOUSE_CUR_MANUAL );
				smartLogger->Write( MSG_FIDMANUALTEACH );
			}

			datasette->StopEnable( true );
			datasette->PrevEnable( true );
			isMainVideoClickEnable = true;
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_SEARCH_T2:
			// Get frames and stop video
			camera->SetMainMode( MAIN_NO_CUR );
			if( SR->DB->WorkingModesS.FiducialSearch == FIDUCIAL_AUTO ){
				myMilliSleep( FLICKERING_DELAY );
				camera->GetFrames( MAX_FRAMES_FIDUCIAL );
			}
			camera->StopCapture();

			// Disable camera
			if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			if( SR->DB->WorkingModesS.FiducialSearch == FIDUCIAL_AUTO )
			{
				// Call function to get the center of the fiducial...
				if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_CIRCLE )
				{
					if( camera->FindCircle2( xClicked, yClicked, centerX, centerY, circleR ) == SR_OK )
					{
						smartLogger->Write( wxString::Format( MSG_FIDFOUND_CIRCLE, centerX, centerY, circleR ) );
						if( SMAlignment( ALIGNMENT_STATE_FOUND_WAIT_T2 ) == SR_ERROR )
							return SR_ERROR;
						break;
					}
				}
				else if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_RECTANGLE )
				{
					if( camera->FindRectangle( xClicked, yClicked, centerX, centerY, rectangleX, rectangleY ) == SR_OK )
					{
						smartLogger->Write( wxString::Format( MSG_FIDFOUND_RECT, centerX, centerY, rectangleX, rectangleY ) );
						if( SMAlignment( ALIGNMENT_STATE_FOUND_WAIT_T2 ) == SR_ERROR )
							return SR_ERROR;
						break;
					}
				}
				else if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_TEMPLATE )
				{
					centerX = CAM_W / 2;
					centerY = CAM_H / 2;
					
					if( camera->FindTemplate( wxString::Format( "%s_%d.jpeg", SR->DB->ProductionDataS.ProductionName.ToAscii(), currentFiducial ), centerX, centerY, templateScore ) == SR_OK )
					{
						smartLogger->Write( wxString::Format( MSG_FIDFOUND_TEMPLATE, centerX, centerY, templateScore ) );
						if( SMAlignment( ALIGNMENT_STATE_FOUND_WAIT_T2 ) == SR_ERROR )
							return SR_ERROR;
						break;
					}
				}

				// Fiducial not found
				smartLogger->Write( MSG_FIDNOTFOUND, MSG_ERROR );
				// Notify manual fiducial search
				wxMessageBox( MSG_FIDUCIALMANUAL, MACHINE_NAME, wxOK | wxICON_WARNING, parent );

				// Manual fiducial search
				smartLogger->Write( MSG_FIDMANUALTEACH );
				camera->SetMainShape();
				camera->SetMainMode( MAIN_MOUSE_CUR_MANUAL );
				datasette->StopEnable( true );
				datasette->PrevEnable( true );
				// Enable mouse click
				isMainVideoClickEnable = true;
			}
			else
			{
				centerX = xClicked;
				centerY = yClicked;

				if( SMAlignment( ALIGNMENT_STATE_FOUND_WAIT_T2 ) == SR_ERROR )
					return SR_ERROR;
			}
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_FOUND_WAIT_T2:
			// sets controls state
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			datasette->PrevEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_FOUND_T2:
			// Get current camera coords
			SR->GetCameraPosition( camPos.X, camPos.Y );
			// At this point, we have the fiducial coords (manual or auto...)
			// align T2 use only fiducials on PCB
			fidPosition[currentFiducial].X = camPos.X + (centerX - CAM_W / 2) * SR->DB->MachineParamsS.DnXPixMm;
			fidPosition[currentFiducial].Y = camPos.Y - (centerY - CAM_H / 2) * SR->DB->MachineParamsS.DnYPixMm;
			// refers position to the PCB origin
			fidPosition[currentFiducial].X -= SR->DB->ProductionDataS.PCBPosX;
			fidPosition[currentFiducial].Y -= SR->DB->ProductionDataS.PCBPosY;

			// switch to next fiducial
			if( currentFiducial == FIDUCIAL_ROT1 )
			{
				currentFiducial = FIDUCIAL_ROT2;

				// calc table 2 position error
				table2PosErr.X = fidPosition[FIDUCIAL_ROT1].X - SR->DB->FiducialParamsS[FIDUCIAL_ROT1_FRAME].X;
				table2PosErr.Y = fidPosition[FIDUCIAL_ROT1].Y - SR->DB->FiducialParamsS[FIDUCIAL_ROT1_FRAME].Y;
			}
			else if( currentFiducial == FIDUCIAL_ROT2 )
				currentFiducial = FIDUCIAL_TRA;
			else if( currentFiducial == FIDUCIAL_TRA )
				fiducialSearchTerminated = true;

			if( fiducialSearchTerminated )
			{
				// Stop live video
				camera->StopCapture();
				camera->SetMainMode( MAIN_BLANK );
				camera->SetAuxMode( AUX_BLANK );

				// Disable camera
				if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
				{
					smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
					return SR_ERROR;
				}

				// Save fiducials params
				SR->DB->SaveFiducialParams();

				// apply TRA correction
				if( SMAlignment( ALIGNMENT_STATE_TRA_T2 ) == SR_ERROR )
					return SR_ERROR;

				retVal = wxNO;
				MACHINE_CONFIG( VISION_VERIFY_ENABLE )
				retVal = wxMessageBox( MSG_ALIGNVERIFYVISIONQ, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, parent );
				MACHINE_CONFIG_END

				if( retVal == wxYES )
				{
					if( SMAlignment( ALIGNMENT_STATE_TEACH_VERIFY ) == SR_ERROR )
						return SR_ERROR;
				}
				else
				{
					if( SMAlignment( ALIGNMENT_STATE_VERIFY ) == SR_ERROR )
						return SR_ERROR;
				}
			}
			else
			{
				if( currentFiducial == FIDUCIAL_TRA )
				{
					// Stop live video
					camera->StopCapture();
					camera->SetMainMode( MAIN_BLANK );
					camera->SetAuxMode( AUX_BLANK );

					// Disable camera
					if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
					{
						smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
						return SR_ERROR;
					}

					// apply ROT correction
					if( SMAlignment( ALIGNMENT_STATE_ROT_T2 ) == SR_ERROR )
						return SR_ERROR;
				}

				if( SMAlignment( ALIGNMENT_STATE_MOVE_T2 ) == SR_ERROR )
					return SR_ERROR;
			}
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_ROT_T2:
			if( SR->DB->WorkingModesS.FiducialOnFrame )
			{
				// use the fiducials on the frame
				fidPosition[FIDUCIAL_ROT1_FRAME].X = SR->DB->FiducialParamsS[FIDUCIAL_ROT1_FRAME].DeltaX + SR->DB->FiducialParamsS[FIDUCIAL_ROT1_FRAME].X;
				fidPosition[FIDUCIAL_ROT1_FRAME].Y = SR->DB->FiducialParamsS[FIDUCIAL_ROT1_FRAME].DeltaY + SR->DB->FiducialParamsS[FIDUCIAL_ROT1_FRAME].Y;
				fidPosition[FIDUCIAL_ROT2_FRAME].X = SR->DB->FiducialParamsS[FIDUCIAL_ROT2_FRAME].DeltaX + SR->DB->FiducialParamsS[FIDUCIAL_ROT2_FRAME].X;
				fidPosition[FIDUCIAL_ROT2_FRAME].Y = SR->DB->FiducialParamsS[FIDUCIAL_ROT2_FRAME].DeltaY + SR->DB->FiducialParamsS[FIDUCIAL_ROT2_FRAME].Y;
			}
			else
			{
				// use the fiducials on the PCB
				fidPosition[FIDUCIAL_ROT1_FRAME].X = SR->DB->FiducialParamsS[FIDUCIAL_ROT1].DeltaX + SR->DB->FiducialParamsS[FIDUCIAL_ROT1].X;
				fidPosition[FIDUCIAL_ROT1_FRAME].Y = SR->DB->FiducialParamsS[FIDUCIAL_ROT1].DeltaY + SR->DB->FiducialParamsS[FIDUCIAL_ROT1].Y;
				fidPosition[FIDUCIAL_ROT2_FRAME].X = SR->DB->FiducialParamsS[FIDUCIAL_ROT2].DeltaX + SR->DB->FiducialParamsS[FIDUCIAL_ROT2].X;
				fidPosition[FIDUCIAL_ROT2_FRAME].Y = SR->DB->FiducialParamsS[FIDUCIAL_ROT2].DeltaY + SR->DB->FiducialParamsS[FIDUCIAL_ROT2].Y;
			}

			// Calc frame rotation
			if( fidPosition[FIDUCIAL_ROT2_FRAME].Y - fidPosition[FIDUCIAL_ROT1_FRAME].Y == 0 && fidPosition[FIDUCIAL_ROT2_FRAME].X - fidPosition[FIDUCIAL_ROT1_FRAME].X == 0 )
				frameRot = 0;
			else
				frameRot = atan2( fidPosition[FIDUCIAL_ROT2_FRAME].Y - fidPosition[FIDUCIAL_ROT1_FRAME].Y, fidPosition[FIDUCIAL_ROT2_FRAME].X - fidPosition[FIDUCIAL_ROT1_FRAME].X );
			frameRot = frameRot * 180 / PI;

			// Calc board rotation
			if( fidPosition[FIDUCIAL_ROT2].Y - fidPosition[FIDUCIAL_ROT1].Y == 0 && fidPosition[FIDUCIAL_ROT2].X - fidPosition[FIDUCIAL_ROT1].X == 0 )
				boardRot = 0;
			else
				boardRot = atan2( fidPosition[FIDUCIAL_ROT2].Y - fidPosition[FIDUCIAL_ROT1].Y, fidPosition[FIDUCIAL_ROT2].X - fidPosition[FIDUCIAL_ROT1].X );
			boardRot = boardRot * 180 / PI;

			boardRot = frameRot - boardRot;

			// Test 3 sub-movements
			isTableSubMovementOk = 0;
			for( int i = 1; i < 4; i++ )
			{
				if( SR->RotateTableCheck( boardRot / double(i) ) == SR_OK )
				{
					SR->ResetErrors();
					isTableSubMovementOk = 1;

					for( int ii = 0; ii < i; ii++ )
					{
						// Rotate
						if( SR->RotateTableAndWait( boardRot / double(i) ) == SR_ERROR )
						{
							smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
							return SR_ERROR;
						}
						// Disengage board from table
						if( SR->PlateMotor.MoveAndWait( 0, ABS_MOVE ) == SR_ERROR )
						{
							smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
							return SR_ERROR;
						}
						// Reset table
						if( SR->ResetTable() == SR_ERROR )
						{
							smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
							return SR_ERROR;
						}
						if( SR->WaitTable() == SR_ERROR )
						{
							smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
							return SR_ERROR;
						}
						// Move the board to reaches the camera focus
						if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
						{
							smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
							return SR_ERROR;
						}
					}
					break;
				}
			}
			if( isTableSubMovementOk == 0 )
			{
				smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Save actual board rotation
			SR->DB->ProductionDataS.LastRot = boardRot;

			smartLogger->Write( wxString::Format( MSG_ROTDONE, boardRot ), MSG_SUCCESS );
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_TRA_T2:
			if( !SR->DB->WorkingModesS.FiducialOnFrame )
			{
				offsetX = offsetY = 0.0;

				// use the fiducials on the PCB
				fidPosition[FIDUCIAL_TRA_FRAME].X = SR->DB->FiducialParamsS[FIDUCIAL_TRA].DeltaX + SR->DB->FiducialParamsS[FIDUCIAL_TRA].X;
				fidPosition[FIDUCIAL_TRA_FRAME].Y = SR->DB->FiducialParamsS[FIDUCIAL_TRA].DeltaY + SR->DB->FiducialParamsS[FIDUCIAL_TRA].Y;
			}
			else
			{
				SR->GetOffset( camPos.X, camPos.Y, offsetX, offsetY );

				// use the fiducials on the frame
				fidPosition[FIDUCIAL_TRA_FRAME].X = SR->DB->FiducialParamsS[FIDUCIAL_TRA_FRAME].DeltaX + SR->DB->FiducialParamsS[FIDUCIAL_TRA_FRAME].X;
				fidPosition[FIDUCIAL_TRA_FRAME].Y = SR->DB->FiducialParamsS[FIDUCIAL_TRA_FRAME].DeltaY + SR->DB->FiducialParamsS[FIDUCIAL_TRA_FRAME].Y;
			}

			// Calc translation
			boardTra.X = fidPosition[FIDUCIAL_TRA_FRAME].X - fidPosition[FIDUCIAL_TRA].X + offsetX;
			boardTra.Y = fidPosition[FIDUCIAL_TRA_FRAME].Y - fidPosition[FIDUCIAL_TRA].Y + offsetY;

			// Test 3 sub-movements
			isTableSubMovementOk = 0;
			for( int i = 1; i < 4; i++ )
			{
				if( SR->MoveXYTableCheck( boardTra.X / double(i), boardTra.Y / double(i) ) == SR_OK )
				{
					SR->ResetErrors();
					isTableSubMovementOk = 1;

					for( int ii = 0; ii < i; ii++ )
					{
						if( ii != 0 )
						{
							// Disengage board from table
							if( SR->PlateMotor.MoveAndWait( 0, ABS_MOVE ) == SR_ERROR )
							{
								smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
								return SR_ERROR;
							}
							// Reset table
							if( SR->ResetTable() == SR_ERROR )
							{
								smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
								return SR_ERROR;
							}
							if( SR->WaitTable() == SR_ERROR )
							{
								smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
								return SR_ERROR;
							}
							// Move the board to reaches the camera focus
							if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
							{
								smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
								return SR_ERROR;
							}
						}
						// MoveXY
						if( SR->MoveXYTableAndWait( boardTra.X / double(i), boardTra.Y / double(i) ) == SR_ERROR )
						{
							smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
							return SR_ERROR;
						}
					}
					break;
				}
			}
			if( isTableSubMovementOk == 0 )
			{
				smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Save actual board translations
			SR->DB->ProductionDataS.LastX = boardTra.X;
			SR->DB->ProductionDataS.LastY = boardTra.Y;

			smartLogger->Write( wxString::Format( MSG_TRASLDONE, boardTra.X, boardTra.Y ), MSG_SUCCESS );
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_REVIEW_TEACH:
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

			SR->DB->SetFiducialParams( currentFiducial );
			mainVideo->UpdateControl();

			// if this is the first fiducial...
			if( currentFiducial == FIDUCIAL_ROT1 )
			{
				// if template matching chek image existance
				if( SR->DB->FiducialParamsS[FIDUCIAL_ROT1].SearchMode == SEARCH_MODE_TEMPLATE )
				{
					if( CheckTemplateImage() == false )
					{
						wxMessageBox( MSG_NOTEMPLATEIMAGE, MACHINE_NAME, wxOK | wxICON_ERROR, parent );
						panel->SetFiducialButton( false );

						if( SMAlignment( ALIGNMENT_STATE_RESET ) == SR_ERROR )
							return SR_ERROR;
						break;
					}
				}

				// Move the board inside the machine
				if( LoadBoardCameraCheck() == SR_ERROR )
				{
					smartLogger->Write( MSG_LOADERROR, MSG_ERROR );
					return SR_ERROR;
				}

				// draw board
				if( SR->DB->ProductionDataS.PCBPosX != 0.0 )
					camera->DrawWorkplace( SR->DB->ProductionDataS.PCBPosX, SR->DB->ProductionDataS.PCBPosY, SR->DB->ProductionDataS.PCBX, SR->DB->ProductionDataS.PCBY );

				// Move the board to reaches the camera focus
				if( SR->PlateMotor.Move( this->SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
				{
					smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
					return SR_ERROR;
				}
			}
			antiReflects(currentFiducial);
			// Move camera on the fiducial
			if( IsFiducialOnPCB( currentFiducial ) )
			{
				if( SR->DB->WorkingModesS.FiducialOnFrame )
				{
					if( currentFiducial == FIDUCIAL_ROT1 )
						retVal = SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX + SR->DB->FiducialParamsS[FIDUCIAL_ROT1_FRAME].X, SR->DB->ProductionDataS.PCBPosY + SR->DB->FiducialParamsS[FIDUCIAL_ROT1_FRAME].Y, ABS_MOVE );
					else if( currentFiducial == FIDUCIAL_ROT2 )
						retVal = SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX + SR->DB->FiducialParamsS[FIDUCIAL_ROT2_FRAME].X, SR->DB->ProductionDataS.PCBPosY + SR->DB->FiducialParamsS[FIDUCIAL_ROT2_FRAME].Y, ABS_MOVE );
					else if( currentFiducial == FIDUCIAL_TRA )
						retVal = SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX + SR->DB->FiducialParamsS[FIDUCIAL_TRA_FRAME].X, SR->DB->ProductionDataS.PCBPosY + SR->DB->FiducialParamsS[FIDUCIAL_TRA_FRAME].Y, ABS_MOVE );
				}
				else
					retVal = SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX + SR->DB->FiducialParamsS[currentFiducial].X, SR->DB->ProductionDataS.PCBPosY + SR->DB->FiducialParamsS[currentFiducial].Y, ABS_MOVE );

				if( retVal == SR_ERROR )
				{
					smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
					return SR_ERROR;
				}
			}

			// if this is the first fiducial...
			if( currentFiducial == FIDUCIAL_ROT1 )
			{
				if( SR->PlateMotor.Wait() == SR_ERROR )
				{
					smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
					return SR_ERROR;
				}
			}

			panel->UpdatePanel();
			if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_TEMPLATE )
			{
				panel->ShowTemplatePanel( true );
				wxBitmap bmp = camera->LoadTemplateImage( wxString::Format( "%s_%d.jpeg", SR->DB->ProductionDataS.ProductionName.ToAscii(), currentFiducial ) );
				panel->ShowTemplateImage( bmp );
			}
			else // VECTORIAL
			{
				panel->ShowAlignmentPanel( true );
				panel->EnableAlignmentPanel( true );
				panel->EnableShapeCombo( false );
			}

			// Plate down for reflects
			antiReflects(currentFiducial);

			// Enable camera
			retVal = IsFiducialOnPCB( currentFiducial ) ? SR->SetCamera( CAMERA_DOWN ) : SR->SetCamera( CAMERA_UP );
			if( retVal == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			camera->SetMainMode( MAIN_MOUSE_CUR );
			camera->SetAuxMode( AUX_SMOOTH_EDGE );
			camera->StartCapture();

			if( currentFiducial == FIDUCIAL_ROT1 )
				smartLogger->Write( MSG_SEARCHFIDROT1 );
			else if( currentFiducial == FIDUCIAL_ROT2 )
				smartLogger->Write( MSG_SEARCHFIDROT2 );
			else if( currentFiducial == FIDUCIAL_TRA )
				smartLogger->Write( MSG_SEARCHFIDTRA );
			else if( currentFiducial == FIDUCIAL_ROT1_FRAME )
				smartLogger->Write( MSG_SEARCHFIDROT1FRAME );
			else if( currentFiducial == FIDUCIAL_ROT2_FRAME )
				smartLogger->Write( MSG_SEARCHFIDROT2FRAME );
			else if( currentFiducial == FIDUCIAL_TRA_FRAME )
				smartLogger->Write( MSG_SEARCHFIDTRAFRAME );

			datasette->StopEnable( true );
			datasette->NextEnable( true );
			// Enable mouse click
			isMainVideoClickEnable = true;
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_REVIEW_SEARCH:
			camera->SetMainMode( MAIN_NO_CUR );
			myMilliSleep( FLICKERING_DELAY );
			camera->GetFrames( MAX_FRAMES_FIDUCIAL );
			camera->StopCapture();

			// Disable camera
			if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}
			// Disable mouse click
			isMainVideoClickEnable = false;

			// Call function to get the center of the fiducial...
			if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_CIRCLE )
			{
				if( camera->FindCircle2( xClicked, yClicked, centerX, centerY, circleR ) == SR_OK )
					smartLogger->Write( wxString::Format( MSG_FIDFOUND_CIRCLE, centerX, centerY, circleR ) );
				else
					smartLogger->Write( MSG_FIDNOTFOUND, MSG_ERROR );
			}
			else if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_RECTANGLE )
			{
				if( camera->FindRectangle( xClicked, yClicked, centerX, centerY, rectangleX, rectangleY ) == SR_OK )
					smartLogger->Write( wxString::Format( MSG_FIDFOUND_RECT, centerX, centerY, rectangleX, rectangleY ) );
				else
					smartLogger->Write( MSG_FIDNOTFOUND, MSG_ERROR );
			}
			else if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_TEMPLATE )
			{
				centerX = CAM_W / 2;
				centerY = CAM_H / 2;

				if( camera->FindTemplate( wxString::Format( "%s_%d.jpeg", SR->DB->ProductionDataS.ProductionName.ToAscii(), currentFiducial ), centerX, centerY, templateScore ) == SR_OK )
					smartLogger->Write( wxString::Format( MSG_FIDFOUND_TEMPLATE, centerX, centerY, templateScore ) );
				else
					smartLogger->Write( MSG_FIDNOTFOUND, MSG_ERROR );
			}

			datasette->StopEnable( true );
			datasette->NextEnable( true );
			datasette->PrevEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_REVIEW_NEXT:
			// switch to next fiducial
			if( currentFiducial == FIDUCIAL_ROT1 )
				currentFiducial = SR->DB->WorkingModesS.FiducialOnFrame ? FIDUCIAL_ROT1_FRAME : FIDUCIAL_ROT2;
			else if( currentFiducial == FIDUCIAL_ROT2 )
				currentFiducial = SR->DB->WorkingModesS.FiducialOnFrame ? FIDUCIAL_ROT2_FRAME : FIDUCIAL_TRA;
			else if( currentFiducial == FIDUCIAL_TRA )
			{
				if( SR->DB->WorkingModesS.FiducialOnFrame )
					currentFiducial = FIDUCIAL_TRA_FRAME;
				else
					fiducialSearchTerminated = true;
			}
			else if( currentFiducial == FIDUCIAL_ROT1_FRAME )
				currentFiducial = FIDUCIAL_ROT2;
			else if( currentFiducial == FIDUCIAL_ROT2_FRAME )
				currentFiducial = FIDUCIAL_TRA;
			else if( currentFiducial == FIDUCIAL_TRA_FRAME )
				fiducialSearchTerminated = true;
			
			if( fiducialSearchTerminated )
			{
				SR->DB->SaveFiducialParams();

				if( SMAlignment( ALIGNMENT_STATE_RESET ) == SR_ERROR )
					return SR_ERROR;
				break;
			}

			if( SMAlignment( ALIGNMENT_STATE_REVIEW_TEACH ) == SR_ERROR )
				return SR_ERROR;
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_AGAIN_SEARCH:
			SR->DB->SetFiducialParams( currentFiducial );
			mainVideo->UpdateControl();
			panel->UpdatePanel();

			panel->ShowAlignmentPanel( false );

			if( currentFiducial == FIDUCIAL_ROT1 )
			{
				// Move camera in start position
				if( SR->MoveCameraAndWait( (SR->DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit - SR->DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit)/2, SR->DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit, ABS_MOVE ) == SR_ERROR )
				{
					smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
					return SR_ERROR;
				}
			}

			// Move camera on the fiducial
			if( SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX + SR->DB->FiducialParamsS[currentFiducial].X, SR->DB->ProductionDataS.PCBPosY + SR->DB->FiducialParamsS[currentFiducial].Y, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				return SR_ERROR;
			}
			// Plate down for reflects
			antiReflects(currentFiducial);

			// Enable camera
			retVal = IsFiducialOnPCB( currentFiducial ) ? SR->SetCamera( CAMERA_DOWN ) : SR->SetCamera( CAMERA_UP );
			if( retVal == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Wait to avoid flickering and get frames
			camera->SetMainMode( MAIN_NO_CUR );
			camera->StartCapture();

			myMilliSleep( FLICKERING_DELAY );

			camera->GetFrames( MAX_FRAMES_FIDUCIAL );
			camera->StopCapture();

			// Disable camera
			if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			if( currentFiducial == FIDUCIAL_ROT1 )
				smartLogger->Write( MSG_SEARCHFIDROT1 );
			else if( currentFiducial == FIDUCIAL_ROT2 )
				smartLogger->Write( MSG_SEARCHFIDROT2 );
			else if( currentFiducial == FIDUCIAL_TRA )
				smartLogger->Write( MSG_SEARCHFIDTRA );
			else if( currentFiducial == FIDUCIAL_ROT1_FRAME )
				smartLogger->Write( MSG_SEARCHFIDROT1FRAME );
			else if( currentFiducial == FIDUCIAL_ROT2_FRAME )
				smartLogger->Write( MSG_SEARCHFIDROT2FRAME );
			else if( currentFiducial == FIDUCIAL_TRA_FRAME )
				smartLogger->Write( MSG_SEARCHFIDTRAFRAME );

			fiducialAutoFounded = false;

			expectedX = (CAM_W / 2);
			expectedY = (CAM_H / 2);

			// Call function to get the center of the fiducial
			if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_CIRCLE )
			{
				if( camera->FindCircle2( expectedX, expectedY, centerX, centerY, circleR ) == SR_OK )
				{
					smartLogger->Write( wxString::Format( MSG_FIDFOUND_CIRCLE, centerX, centerY, circleR ) );
					fiducialAutoFounded = true;
					if( SMAlignment( ALIGNMENT_STATE_AGAIN_FOUND ) == SR_ERROR )
						return SR_ERROR;
					break;
				}
			}
			else if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_RECTANGLE )
			{
				if( camera->FindRectangle( expectedX, expectedY, centerX, centerY, rectangleX, rectangleY ) == SR_OK )
				{
					smartLogger->Write( wxString::Format( MSG_FIDFOUND_RECT, centerX, centerY, rectangleX, rectangleY ) );
					fiducialAutoFounded = true;
					if( SMAlignment( ALIGNMENT_STATE_AGAIN_FOUND ) == SR_ERROR )
						return SR_ERROR;
					break;
				}
			}
			else if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_TEMPLATE )
			{
				// save image
				camera->SaveTemplateImage( wxString::Format( "%s_%d.jpeg", SR->DB->ProductionDataS.ProductionName.ToAscii(), currentFiducial ) );
			
				centerX = CAM_W / 2;
				centerY = CAM_H / 2;
			
				if( SMAlignment( ALIGNMENT_STATE_AGAIN_FOUND ) == SR_ERROR )
					return SR_ERROR;
				break;
			}

			// Fiducial not found
			smartLogger->Write( MSG_FIDNOTFOUND, MSG_ERROR );
			// Notify manual fiducial search
			wxMessageBox( MSG_FIDUCIALMANUAL, MACHINE_NAME, wxOK | wxICON_WARNING, parent );

			panel->EnableAlignmentPanel( true );
			panel->ShowAlignmentPanel( true );
			panel->EnableShapeCombo( false );

			// Manual fiducial search
			smartLogger->Write( MSG_FIDMANUALTEACH );
			camera->SetMainShape();
			camera->SetMainMode( MAIN_MOUSE_CUR_MANUAL );
			datasette->StopEnable( true );
			datasette->PrevEnable( true );
			// Enable mouse click
			isMainVideoClickEnable = true;
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_AGAIN_FOUND:
			antiReflects(currentFiducial);
			// Get current camera coords
			SR->GetCameraPosition( camPos.X, camPos.Y );
			// At this point, we have the fiducial coords (manual or auto...)
			SR->DB->FiducialParamsS[currentFiducial].X = camPos.X;
			SR->DB->FiducialParamsS[currentFiducial].Y = camPos.Y;
			if( IsFiducialOnPCB( currentFiducial ) )
			{
				SR->DB->FiducialParamsS[currentFiducial].DeltaX = (centerX - CAM_W / 2 ) * SR->DB->MachineParamsS.DnXPixMm;
				SR->DB->FiducialParamsS[currentFiducial].DeltaY = -(centerY - CAM_H / 2 ) * SR->DB->MachineParamsS.DnYPixMm;
			}
			else
			{
				SR->DB->FiducialParamsS[currentFiducial].DeltaX = (centerX - CAM_W / 2 ) * SR->DB->MachineParamsS.UpXPixMm;
				SR->DB->FiducialParamsS[currentFiducial].DeltaY = -(centerY - CAM_H / 2 ) * SR->DB->MachineParamsS.UpYPixMm;
			}
			// refers position to the PCB origin
			SR->DB->FiducialParamsS[currentFiducial].X -= SR->DB->ProductionDataS.PCBPosX;
			SR->DB->FiducialParamsS[currentFiducial].Y -= SR->DB->ProductionDataS.PCBPosY;

			panel->ShowAlignmentPanel( false );

			// If vision debug is acivated...
			if( SR->DB->WorkingModesS.DebugMode && fiducialAutoFounded )
			{
				// ...wait for next button
				datasette->StopEnable( true );
				datasette->NextEnable( true );
				break;
			}
			else
			{
				// serve per vedere se il fiduciale e' stato riconosciuto correttamente
				myMilliSleep( 250 );

				if( SMAlignment( ALIGNMENT_STATE_AGAIN_NEXT ) == SR_ERROR )
					return SR_ERROR;
			}
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_AGAIN_FOUND_WAIT:
			panel->ShowAlignmentPanel( false );
			
			// sets controls state
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			datasette->PrevEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case ALIGNMENT_STATE_AGAIN_NEXT:
			// switch to next fiducial
			if( currentFiducial == FIDUCIAL_ROT1 )
				currentFiducial = SR->DB->WorkingModesS.FiducialOnFrame ? FIDUCIAL_ROT1_FRAME : FIDUCIAL_ROT2;
			else if( currentFiducial == FIDUCIAL_ROT2 )
				currentFiducial = SR->DB->WorkingModesS.FiducialOnFrame ? FIDUCIAL_ROT2_FRAME : FIDUCIAL_TRA;
			else if( currentFiducial == FIDUCIAL_TRA )
			{
				if( SR->DB->WorkingModesS.FiducialOnFrame )
					currentFiducial = FIDUCIAL_TRA_FRAME;
				else
					fiducialSearchTerminated = true;
			}
			else if( currentFiducial == FIDUCIAL_ROT1_FRAME )
				currentFiducial = FIDUCIAL_ROT2;
			else if( currentFiducial == FIDUCIAL_ROT2_FRAME )
				currentFiducial = FIDUCIAL_TRA;
			else if( currentFiducial == FIDUCIAL_TRA_FRAME )
				fiducialSearchTerminated = true;

			if( fiducialSearchTerminated )
			{
				// save PCB position
				SR->DB->SaveProductionData();
				// save fiducial for printing
				SR->DB->SaveFiducialParams();
				// adjust verify points
				if( isExistingProduction )
					SR->DB->AdjustVerifyPoints( SR->DB->ProductionDataS.PCBPosX, SR->DB->ProductionDataS.PCBPosY );

				smartLogger->Write( MSG_ALIGNFIDENDED, MSG_SUCCESS );

				camera->SetMainMode( MAIN_BLANK );
				camera->SetAuxMode( AUX_BLANK );

				if( SMAlignment( ALIGNMENT_STATE_SQUEEGEES_ZERO ) == SR_ERROR )
					return SR_ERROR;
			}
			else
			{
				if( SMAlignment( ALIGNMENT_STATE_AGAIN_SEARCH ) == SR_ERROR )
					return SR_ERROR;
			}
			break;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMAlignmentNext
// Aggiorna lo stato dell SM
//----------------------------------------------------------------------------------
void SMBase::SMAlignmentNext()
{
	retVal = SR_OK;

	switch( currentState )
	{
		case ALIGNMENT_STATE_INIT1:
			retVal = SMAlignment( ALIGNMENT_STATE_INIT2 );
			break;

		case ALIGNMENT_STATE_INIT2:
			retVal = SMAlignment( ALIGNMENT_STATE_CHECK );
			break;

		case ALIGNMENT_STATE_LEFTBORDER:
			SR->GetCameraPosition( SR->DB->ProductionDataS.PCBPosX, camPos.Y );
			retVal = SMAlignment( ALIGNMENT_STATE_DRAWBOARD );
			break;

		case ALIGNMENT_STATE_MOVE_A:
			retVal = SMAlignment( ALIGNMENT_STATE_TEACH_A );
			break;

		case ALIGNMENT_STATE_VERIFY:
			retVal = SMAlignment( ALIGNMENT_STATE_CHECK );
			break;

		case ALIGNMENT_STATE_FID_MOVE:
			retVal = SMAlignment( ALIGNMENT_STATE_FID_TEACH );
			break;

		case ALIGNMENT_STATE_TEACH_VERIFY:
			retVal = SMAlignment( ALIGNMENT_STATE_VERIFY );
			break;

		case ALIGNMENT_STATE_SQUEEGEES_ZERO:
			retVal = SMAlignment( ALIGNMENT_STATE_SQUEEGEES_ZERO_SAVE );
			break;

		case ALIGNMENT_STATE_SQUEEGEES_MOVE:
			retVal = SMAlignment( ALIGNMENT_STATE_SQUEEGEES_MOVE_SAVE );
			break;

		case ALIGNMENT_STATE_FOUND_WAIT_A:
			retVal = SMAlignment( ALIGNMENT_STATE_FOUND_A );
			break;

		// Used with TEMPLATE
		case ALIGNMENT_STATE_FID_TEACH:
			retVal = SMAlignment( ALIGNMENT_STATE_FID_SEARCH );
			break;
			
		case ALIGNMENT_STATE_FID_FOUND_WAIT:
			retVal = SMAlignment( ALIGNMENT_STATE_FID_FOUND );
			break;

		case ALIGNMENT_STATE_MOVE_T2:
			retVal = SMAlignment( ALIGNMENT_STATE_TEACH_T2 );
			break;

		case ALIGNMENT_STATE_FOUND_WAIT_T2:
			retVal = SMAlignment( ALIGNMENT_STATE_FOUND_T2 );
			break;

		case ALIGNMENT_STATE_REVIEW_TEACH:
		case ALIGNMENT_STATE_REVIEW_SEARCH:
			retVal = SMAlignment( ALIGNMENT_STATE_REVIEW_NEXT );
			break;

		case ALIGNMENT_STATE_AGAIN_FOUND_WAIT:
			retVal = SMAlignment( ALIGNMENT_STATE_AGAIN_FOUND );
			break;

		// If vision debug is acivated...
		case ALIGNMENT_STATE_AGAIN_FOUND:
			retVal = SMAlignment( ALIGNMENT_STATE_AGAIN_NEXT );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

//----------------------------------------------------------------------------------
// SMPrintingPrev
// Aggiorna lo stato della SM
//----------------------------------------------------------------------------------
void SMBase::SMAlignmentPrev()
{
	retVal = SR_OK;

	switch( currentState )
	{
		case ALIGNMENT_STATE_TEACH_A:
			retVal = SMAlignment( ALIGNMENT_STATE_MOVE_A );
			break;

		case ALIGNMENT_STATE_SEARCH_A:
		case ALIGNMENT_STATE_FOUND_WAIT_A:
			retVal = SMAlignment( ALIGNMENT_STATE_TEACH_A );
			break;

		case ALIGNMENT_STATE_FID_TEACH:
			retVal = SMAlignment( ALIGNMENT_STATE_FID_MOVE );
			break;

		case ALIGNMENT_STATE_FID_SEARCH:
		case ALIGNMENT_STATE_FID_FOUND_WAIT:
			retVal = SMAlignment( ALIGNMENT_STATE_FID_TEACH );
			break;

		case ALIGNMENT_STATE_SQUEEGEES_ZERO:
		case ALIGNMENT_STATE_SQUEEGEES_MOVE:
			retVal = SMAlignment( ALIGNMENT_STATE_SQUEEGEES_ZERO );
			break;

		case ALIGNMENT_STATE_TEACH_T2:
			retVal = SMAlignment( ALIGNMENT_STATE_MOVE_T2 );
			break;

		case ALIGNMENT_STATE_SEARCH_T2:
		case ALIGNMENT_STATE_FOUND_WAIT_T2:
			retVal = SMAlignment( ALIGNMENT_STATE_TEACH_T2 );
			break;

		case ALIGNMENT_STATE_REVIEW_SEARCH:
			retVal = SMAlignment( ALIGNMENT_STATE_REVIEW_TEACH );
			break;

		case ALIGNMENT_STATE_AGAIN_SEARCH:
		case ALIGNMENT_STATE_AGAIN_FOUND_WAIT:
			retVal = SMAlignment( ALIGNMENT_STATE_AGAIN_SEARCH );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

//----------------------------------------------------------------------------------
// SMAlignmentMainVideoLeftClick
// 
//----------------------------------------------------------------------------------
void SMBase::SMAlignmentMainVideoLeftClick( wxMouseEvent& e )
{
	retVal = SR_OK;

	if( !isMainVideoClickEnable )
		return;

	wxProductionPanel *panel = (wxProductionPanel *)currentPanel;

	switch( currentState )
	{
		case ALIGNMENT_STATE_TEACH_A:
			camera->GetCursorPositionMain( xClicked, yClicked );

			retVal = SMAlignment( ALIGNMENT_STATE_SEARCH_A );
			break;

		case ALIGNMENT_STATE_SEARCH_A:
			camera->GetCursorPositionMain( xClicked, yClicked );
			centerX = xClicked;
			centerY = yClicked;

			camera->SetMainMode( MAIN_NO_CUR );

			smartLogger->Write( wxString::Format( MSG_FIDFOUNDMAN, xClicked, yClicked ) );
			retVal = SMAlignment( ALIGNMENT_STATE_FOUND_WAIT_A );
			break;

		case ALIGNMENT_STATE_FID_TEACH:
			camera->GetCursorPositionMain( xClicked, yClicked );

			retVal = SMAlignment( ALIGNMENT_STATE_FID_SEARCH );
			break;

		case ALIGNMENT_STATE_FID_SEARCH:
			camera->GetCursorPositionMain( xClicked, yClicked );
			centerX = xClicked;
			centerY = yClicked;

			camera->SetMainMode( MAIN_NO_CUR );

			smartLogger->Write( wxString::Format( MSG_FIDFOUNDMAN, xClicked, yClicked ) );
			retVal = SMAlignment( ALIGNMENT_STATE_FID_FOUND_WAIT );
			break;

		case ALIGNMENT_STATE_TEACH_T2:
			camera->GetCursorPositionMain( xClicked, yClicked );

			retVal = SMAlignment( ALIGNMENT_STATE_SEARCH_T2 );
			break;

		case ALIGNMENT_STATE_SEARCH_T2:
			camera->GetCursorPositionMain( xClicked, yClicked );
			centerX = xClicked;
			centerY = yClicked;

			camera->SetMainMode( MAIN_NO_CUR );

			smartLogger->Write( wxString::Format( MSG_FIDFOUNDMAN, xClicked, yClicked ) );
			retVal = SMAlignment( ALIGNMENT_STATE_FOUND_WAIT_T2 );
			break;

		case ALIGNMENT_STATE_REVIEW_TEACH:
			camera->GetCursorPositionMain( xClicked, yClicked );

			retVal = SMAlignment( ALIGNMENT_STATE_REVIEW_SEARCH );
			break;

		case ALIGNMENT_STATE_AGAIN_SEARCH:
			// Cursor position
			camera->GetCursorPositionMain( xClicked, yClicked );
			centerX = xClicked;
			centerY = yClicked;

			camera->SetMainMode( MAIN_NO_CUR );

			smartLogger->Write( wxString::Format( MSG_FIDFOUNDMAN, xClicked, yClicked ) );
			retVal = SMAlignment( ALIGNMENT_STATE_AGAIN_FOUND_WAIT );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

//---------------------------------------------------------------------------
//
// Name:        SMInspection.cpp
// Author:      Gabriel Ferri
// Created:     20/05/2008 11.23
// Description: Verify - State Machine functions implementation
//
//---------------------------------------------------------------------------

#include "SMBase.h"
#include "wxInspectionPanel.h"
#include <wx/msgdlg.h>
#include "GlobalUtils.h"
#include "Messages.h"
#include "FileFunctions.h"
#include "SmartLog.h"
#include "SRDatabase.h"
#include "SRMachine.h"
#include "wxCameraControl.h"
#include "wxControlPanel.h"
#include "wxDatasette.h"

//aggiunto
#include <string>
#include "AutoSPI.h"


#define PANEL_INSPECTION		PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE
#define PANEL_INSPECTION_MOVE	PANEL_MOVE_CAMERA, PANEL_OUTPUT_LED_UP | PANEL_OUTPUT_LED_DOWN
#define PANEL_DISABLE			PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE

#define SPI_REF_IMAGE_SIZE		360
#define SPI_DRAG_MIN_DIST		10


	//-----------------//
	//   Global Vars   //
	//-----------------//

bool isOffline = true;
bool isFirstTime = true;

// shadow vars
AUTOInspectionSitesStruct shadow_site;

//----------------------------------------------------------------------------------
// SMInspectionInitialize
// Inizializza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMInspectionInitialize()
{
	mainVideo->ConnectMainVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMInspectionMainVideoLeftClick ), this );
	mainVideo->ConnectMainVideoMouseEvent( wxEVT_LEFT_UP, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMInspectionMainVideoLeftClickUp ), this );
	mainVideo->ConnectMainVideoMouseEvent( wxEVT_MOTION, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMInspectionMainVideoMove ), this );
	mainVideo->ConnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );
	//mainVideo->ConnectMainVideoKeyEvent( wxEVT_CHAR, wxStaticCastEvent( wxCharEventFunction, &SMBase::SMMainVideoKeyPress ), this );

	camera->SetAuxMode( AUX_BLANK );
	controlPanel->SetState( PANEL_INSPECTION );

	wxInspectionPanel *panel = (wxInspectionPanel *)currentPanel;
	panel->DrawControl( IP_OFFLINE );

	SR->DB->SiteRestorePosition();
	//non piu necessario inizializzare le immagini
	//spiProc->spiBegin();



	SMInspection( INSPECTION_STATE_IDLE_FIND );
	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMInspectionFinalize
// Finalizza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMInspectionFinalize()
{
	//non piu necessario dellocare
	//spiProc->spiEnd();

	SR->DB->SiteSavePosition();

	mainVideo->DisconnectMainVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMInspectionMainVideoLeftClick ), this );
	mainVideo->DisconnectMainVideoMouseEvent( wxEVT_LEFT_UP, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMInspectionMainVideoLeftClickUp ), this );
	mainVideo->DisconnectMainVideoMouseEvent( wxEVT_MOTION, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMInspectionMainVideoMove ), this );
	mainVideo->DisconnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );
	//mainVideo->DisconnectMainVideoKeyEvent( wxEVT_CHAR, wxStaticCastEvent( wxCharEventFunction, &SMBase::SMMainVideoKeyPress ), this );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMInspectionReset
// Resetta la macchina a stati
//----------------------------------------------------------------------------------
void SMBase::SMInspectionReset()
{
	wxInspectionPanel* panel = (wxInspectionPanel*)currentPanel;

	SR->CheckCover( false );

	if( !isOffline )
	{
		// Disable camera
		if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
		{
			smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
			SR->ErrorManagement();
		}

		if( !SR->GetStop() )
		{
			// Check for motors position
			if( SR->CheckMotorsPos() == SR_ERROR )
			{
				if( SR->ResetMotors( MODE_STARTPRINTING_POSITION ) == SR_ERROR )
					SR->ErrorManagement();
			}
		}
	}

	camera->SetAuxMode( AUX_BLANK );
	camera->SetMainMode( MAIN_BLANK );

	// sets controls state
	panel->DrawControl( IP_OFFLINE );
	panel->Enable( true );
	//
	controlPanel->SetState( PANEL_INSPECTION );

	SMInspection( INSPECTION_STATE_IDLE_FIND );
}

//----------------------------------------------------------------------------------
// SMInspection
// Macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMInspection( int nextState )
{
	retVal = SR_OK;

	datasette->StopEnable( false );
	datasette->NextEnable( false );
	datasette->PrevEnable( false );
	controlPanel->SetState( PANEL_DISABLE );
	// disable mouse click
	isMainVideoClickEnable = false;
	isAuxVideoClickEnable = false;

	currentState = nextState;
	wxInspectionPanel *panel = (wxInspectionPanel *)currentPanel;

	switch( currentState )
	{
		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_RESET:
			toolBox->Enable(true);
			datasette->StopEnable( false );
			datasette->StartEnable( false );
			//schermo nero, pannelli disabilitati, poi va in IDLE_FIND
			SMInspectionReset();

			break;
		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_IDLE_FIND:
			// set controls state
			controlPanel->SetState( PANEL_INSPECTION );
			isOffline = true;
			panel->thrGetBtn->Disable();
			panel->Layout();

			//fine
			panel->Enable(true);

			//if( SR->DB->SiteCount() == 0 || SR->DB->WorkingModesS.InspectionType != INSPECTION_SPI )
			if(  SR->DB->WorkingModesS.InspectionType != INSPECTION_SPI )
			{
				isFirstTime = false;
				// sets controls state
				camera->SetMainMode( MAIN_BLANK );
				camera->SetAuxMode(AUX_BLANK);
				panel->DrawControl( IP_OFFLINE_NO_IMG );
				//panel->DrawControl( IP_TEACH );
				controlPanel->SetState( PANEL_INSPECTION );
				panel->sitesPanel->Disable();
				datasette->StartEnable(false);
				break;
			}
			else{
				panel->DrawControl( IP_OFFLINE );
				panel->sitesPanel->Enable(true);
				datasette->Enable(true);
				datasette->StartEnable(true);
				menuBtn->Enable(true);
			}

			if( SR->DB->pAUTOInspectionCurrentSiteStruct->PointsNum == 0 || AutoSPIproc->LoadDraw(&Frame_to_Mat, simple) == SR_ERROR )
				{
				isFirstTime = false;
				SR->DB->ClearInspectionSite( SR->DB->SiteGetSelected() );
				// sets controls state
				camera->SetMainMode( MAIN_BLANK );
				camera->SetAuxMode( AUX_BLANK );
				panel->DrawControl( IP_OFFLINE_NO_IMG );
				controlPanel->SetState( PANEL_INSPECTION );
				//panel->sitesPanel->Disable();
				break;
					}
			AutoSPIproc->LoadDraw(&Frame_to_Mat, adaptive);

			// continue to following state (internal event)
			currentState = INSPECTION_STATE_IDLE_DRAW;

		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_IDLE_DRAW:

			//in Frame_to_Mat there is the picture chosen in FindRegion
			AutoSPIproc->spiDraw( &Frame_to_Mat);
			camera->SetAuxMode(AUX_INSPECTION_MASK);

			// sets controls state
			panel->DrawControl( IP_OFFLINE );
			controlPanel->SetState( PANEL_INSPECTION );

			break;

		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_INIT:
			camera->SetMainMode( MAIN_BLANK );
			camera->SetAuxMode( AUX_BLANK );
			panel->Enable( false );

			// check if any site is present
			if( SR->DB->SiteCount() == 0 )
			{
				// ask to add new site
				if( wxMessageBox( MSG_ASK_ADD_SITE, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, parent ) != wxYES )
				{
					// procedure complete
					wxMessageBox( MSG_NOSITESTOTEACH, MACHINE_NAME, wxOK | wxICON_INFORMATION, parent );
					smartLogger->Write( MSG_NOSITESTOTEACH );
					return SR_ERROR;
				}

				// add inspection site
				if( SR->DB->InsertInspectionSite() == SR_ERROR )
				{
					wxMessageBox( MSG_MAXSITEREACHED, MACHINE_NAME, wxOK | wxICON_INFORMATION, parent );

					// procedure complete
					smartLogger->Write( MSG_INSP_TECH_ENDED, MSG_SUCCESS );
					return SR_ERROR;
				}

				// select new site
				SR->DB->SiteLast();
			}

			initCheck.cover			= true;
			initCheck.air			= true;
			initCheck.pcb			= false;
			initCheck.pcb_height	= 0;
			initCheck.frame			= true;
			initCheck.motors_pos	= true;
			initCheck.motor_state	= MODE_START_POSITION;

			if( SMInitCheck( initCheck ) == SR_ERROR )
				return SR_ERROR;

			// if template matching check image existance
			if( SR->DB->FiducialParamsS[FIDUCIAL_ROT1].SearchMode == SEARCH_MODE_TEMPLATE )
			{
				if( CheckTemplateImage() == false )
				{
					wxMessageBox( MSG_NOTEMPLATEIMAGE, MACHINE_NAME, wxOK | wxICON_ERROR, parent );
					return SR_ERROR;
				}
			}

			// Inspection cycle can begin

			//isFirstTime = true;

			// Move the board inside the machine
			if( LoadBoardCameraCheck() == SR_ERROR )
			{
				smartLogger->Write( MSG_LOADERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// draw board and sites
			if( SR->DB->ProductionDataS.PCBPosX != 0.0 )
				camera->DrawWorkplaceWithSites( SR->DB->ProductionDataS.PCBPosX, SR->DB->ProductionDataS.PCBPosY, SR->DB->ProductionDataS.PCBX, SR->DB->ProductionDataS.PCBY );

			// Move the board to reaches the camera focus
			if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			currentFiducial = FIDUCIAL_ROT1;
			fiducialSearchTerminated = false;

			MACHINE_CONFIG( MACHINE_ENABLE )
				if( SMInspection( INSPECTION_STATE_SEARCH_A ) == SR_ERROR )
					return SR_ERROR;
			MACHINE_CONFIG_ELSE
				// se macchina disabilitata salta la procedura di allineamento
				if( SMInspection( INSPECTION_STATE_MOVE ) == SR_ERROR )
					return SR_ERROR;
			MACHINE_CONFIG_END
			break;

		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_SEARCH_A:
			SR->DB->SetFiducialParams( currentFiducial );
			mainVideo->UpdateControl();

			// Enable camera
			retVal = IsFiducialOnPCB( currentFiducial ) ? SR->SetCamera( CAMERA_DOWN ) : SR->SetCamera( CAMERA_UP );
			if( retVal == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

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
					retVal = SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX + SR->DB->pCurrentFiducial->X, SR->DB->ProductionDataS.PCBPosY + SR->DB->pCurrentFiducial->Y, ABS_MOVE );

				if( retVal == SR_ERROR )
					return SR_ERROR;
			}

			// if this is the first fiducial...
			if( currentFiducial == FIDUCIAL_ROT1 )
			{
				if( SR->PlateMotor.Wait() == SR_ERROR )
					return SR_ERROR;
			}

			// Wait to avoid flickering and get frames
			myMilliSleep( FLICKERING_DELAY );

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
			if( SR->DB->WorkingModesS.FiducialSearch == FIDUCIAL_AUTO )
			{
				expectedPos.X = CAM_W / 2;
				expectedPos.Y = CAM_H / 2;
				if( !SR->DB->WorkingModesS.FiducialOnFrame )
				{
					expectedPos.X += ( SR->DB->pCurrentFiducial->DeltaX / SR->DB->MachineParamsS.DnXPixMm );
					expectedPos.Y -= ( SR->DB->pCurrentFiducial->DeltaY / SR->DB->MachineParamsS.DnYPixMm );
				}

				// Call function to get the center of the fiducial
				if( SR->DB->pCurrentFiducial->SearchMode == SEARCH_MODE_CIRCLE )
				{
					if( camera->FindCircle2( expectedPos.X, expectedPos.Y, centerX, centerY, circleR ) == SR_OK )
					{
						smartLogger->Write( wxString::Format( MSG_FIDFOUND_CIRCLE, centerX, centerY, circleR ) );
						fiducialAutoFounded = true;
						if( SMInspection( INSPECTION_STATE_FOUND_A ) == SR_ERROR )
							return SR_ERROR;
						break;
					}
				}
				else if( SR->DB->pCurrentFiducial->SearchMode == SEARCH_MODE_RECTANGLE )
				{
					if( camera->FindRectangle( expectedPos.X, expectedPos.Y, centerX, centerY, rectangleX, rectangleY ) == SR_OK )
					{
						smartLogger->Write( wxString::Format( MSG_FIDFOUND_RECT, centerX, centerY, rectangleX, rectangleY ) );
						fiducialAutoFounded = true;
						if( SMInspection( INSPECTION_STATE_FOUND_A ) == SR_ERROR )
							return SR_ERROR;
						break;
					}
				}
				else if( SR->DB->pCurrentFiducial->SearchMode == SEARCH_MODE_TEMPLATE )
				{
					centerX = CAM_W / 2;
					centerY = CAM_H / 2;
					
					if( camera->FindTemplate( wxString::Format( "%s_%d.jpeg", SR->DB->ProductionDataS.ProductionName.ToAscii(), currentFiducial ), centerX, centerY, templateScore ) == SR_OK )
					{
						smartLogger->Write( wxString::Format( MSG_FIDFOUND_TEMPLATE, centerX, centerY, templateScore ) );
						fiducialAutoFounded = true;
						if( SMInspection( INSPECTION_STATE_FOUND_A ) == SR_ERROR )
							return SR_ERROR;
						break;
					}
				}

				// Fiducial not found...
				smartLogger->Write( MSG_FIDNOTFOUND, MSG_ERROR );
				// ...manual fiducial search
				wxMessageBox( MSG_FIDUCIALMANUAL, MACHINE_NAME, wxOK | wxICON_WARNING, parent );
			}

			// Manual fiducial search
			smartLogger->Write( MSG_FIDMANUALTEACH );
			camera->SetMainShape();
			camera->SetMainMode( MAIN_MOUSE_CUR_MANUAL );
			// Enable camera
			retVal = IsFiducialOnPCB( currentFiducial ) ? SR->SetCamera( CAMERA_DOWN ) : SR->SetCamera( CAMERA_UP );
			if( retVal == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			// sets controls state
			isMainVideoClickEnable = true;
			//
			datasette->StopEnable( true );
			datasette->PrevEnable( SR->DB->WorkingModesS.FiducialSearch == FIDUCIAL_AUTO ? true : false );
			break;

		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_FOUND_WAIT_A:
			// sets controls state
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			datasette->PrevEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_FOUND_A:
			// Get current camera coords
			SR->GetCameraPosition( camPos.X, camPos.Y );
			// At this point, we have the fiducial coords (manual or auto...)
			if( IsFiducialOnPCB( currentFiducial ) )
			{
				// serve per vedere se il fiduciale e' stato riconosciuto correttamente
				myMilliSleep( 250 );

				fidPosition[currentFiducial].X = camPos.X + (centerX - CAM_W / 2) * SR->DB->MachineParamsS.DnXPixMm;
				fidPosition[currentFiducial].Y = camPos.Y - (centerY - CAM_H / 2) * SR->DB->MachineParamsS.DnYPixMm;
			}
			else
			{
				fidPosition[currentFiducial].X = camPos.X + (centerX - CAM_W / 2) * SR->DB->MachineParamsS.UpXPixMm;
				fidPosition[currentFiducial].Y = camPos.Y - (centerY - CAM_H / 2) * SR->DB->MachineParamsS.UpYPixMm;
			}
			// refers position to the PCB origin
			fidPosition[currentFiducial].X -= SR->DB->ProductionDataS.PCBPosX;
			fidPosition[currentFiducial].Y -= SR->DB->ProductionDataS.PCBPosY;

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
				if( SMInspection( INSPECTION_STATE_NEXT_A ) == SR_ERROR )
					return SR_ERROR;
			}
			break;

		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_NEXT_A:
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
				// apply TRA correction
				if( SMInspection( INSPECTION_STATE_TRA_A ) == SR_ERROR )
					return SR_ERROR;

				if( SMInspection( INSPECTION_STATE_MOVE ) == SR_ERROR )
					return SR_ERROR;
			}
			else
			{
				if( currentFiducial == FIDUCIAL_TRA )
				{
					// apply ROT correction
					if( SMInspection( INSPECTION_STATE_ROT_A ) == SR_ERROR )
						return SR_ERROR;
				}

				if( SMInspection( INSPECTION_STATE_SEARCH_A ) == SR_ERROR )
					return SR_ERROR;
			}
			break;

		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_ROT_A:
			if( !SR->DB->WorkingModesS.FiducialOnFrame )
			{
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

			// Apply user's corrections
			boardRot = frameRot - boardRot + SR->DB->ProductionDataS.CorrectionTheta;

			if( SR->RotateTableAndWait( boardRot ) == SR_ERROR )
				return SR_ERROR;

			smartLogger->Write( wxString::Format( MSG_ROTDONE, boardRot ), MSG_SUCCESS );
			break;

		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_TRA_A:
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
			}

			// Calc translation
			boardTra.X = fidPosition[FIDUCIAL_TRA_FRAME].X - fidPosition[FIDUCIAL_TRA].X + offsetX;
			boardTra.Y = fidPosition[FIDUCIAL_TRA_FRAME].Y - fidPosition[FIDUCIAL_TRA].Y + offsetY;

			// Apply user's corrections
			boardTra.X += SR->DB->ProductionDataS.CorrectionX;
			boardTra.Y += SR->DB->ProductionDataS.CorrectionY;

			if( SR->MoveXYTable( boardTra.X, boardTra.Y, SR->GetLimitsState() ) == SR_ERROR )
				return SR_ERROR;

			// Move camera out
			if( SR->MoveCameraAndWait( SR->DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit, SR->DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit, ABS_MOVE ) == SR_ERROR )
				return SR_ERROR;

			if( SR->WaitTable() == SR_ERROR )
				return SR_ERROR;



			smartLogger->Write( wxString::Format( MSG_TRASLDONE, boardTra.X, boardTra.Y ), MSG_SUCCESS );
			break;


		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_MOVE:
			panel->Enable( false );
			isOffline = false;
			isFirstTime =true;

			// sono stati eliminati tutti i siti
			if( SR->DB->SiteCount() == 0 )
			{
				// ask to add new site
				if( wxMessageBox( MSG_ASK_ADD_SITE, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, parent ) != wxYES )
				{
					// procedure complete
					wxMessageBox( MSG_NOSITESTOTEACH, MACHINE_NAME, wxOK | wxICON_INFORMATION, parent );
					smartLogger->Write( MSG_NOSITESTOTEACH );
					SMReset();
					break;
				}

				// add inspection site
				if( SR->DB->InsertInspectionSite() == SR_ERROR )
				{
					wxMessageBox( MSG_MAXSITEREACHED, MACHINE_NAME, wxOK | wxICON_INFORMATION, parent );

					// procedure complete
					smartLogger->Write( MSG_INSP_TECH_ENDED, MSG_SUCCESS );
					SMReset();
					break;
				}

				// select new site
				SR->DB->SiteLast();
			}

			// sets site params
			SR->DB->SetFiducialParams( FIDUCIAL_VISION_TEST );
			SR->DB->pCurrentFiducial->CameraBrightness = SR->DB->pAUTOInspectionCurrentSiteStruct->CameraBrightness;
			SR->DB->pCurrentFiducial->CameraContrast = SR->DB->pAUTOInspectionCurrentSiteStruct->CameraContrast;
			mainVideo->UpdateControl();


			// Enable camera
			if( SR->SetCamera( CAMERA_UP ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Move camera...
			if( SR->DB->pAUTOInspectionCurrentSiteStruct->X != 0.0 && SR->DB->pAUTOInspectionCurrentSiteStruct->Y != 0.0 )
			{
				// to verify point
				// to verify point with referece in the tra_fiducial
				//grab local coords
				float xCords =  SR->DB->pAUTOInspectionCurrentSiteStruct->X;
				float yCords =  SR->DB->pAUTOInspectionCurrentSiteStruct->Y;

				//correct rotation offset
				float DeltaAngle = -SR->DB->pAUTOInspectionCurrentSiteStruct->Orientation + frameRot/180*PI;
				// TMP_TODO
				//DeltaAngle =0;
				//cout<< "Delta angle: "<< DeltaAngle<<" frameRot: "<< frameRot<<endl;

				float xTmp = xCords;
				xCords = xCords *cos(DeltaAngle) - yCords*sin(DeltaAngle);
				yCords = xTmp * sin(DeltaAngle) + yCords*cos(DeltaAngle);

				//convert local coords to machine coords
				xCords +=  (fidPosition[FIDUCIAL_TRA].X + boardTra.X);
				yCords +=  (fidPosition[FIDUCIAL_TRA].Y + boardTra.Y);
				//retVal = SR->MoveCameraAndWait(xCords, yCords, ABS_MOVE);
				retVal = SR->MoveCameraAndWait(xCords + SR->DB->ProductionDataS.PCBPosX , yCords +SR->DB->ProductionDataS.PCBPosY, ABS_MOVE);

				//retVal = SR->MoveCameraAndWait( (fidPosition[FIDUCIAL_TRA].X + boardTra.X)  + SR->DB->pAUTOInspectionCurrentSiteStruct->X, (fidPosition[FIDUCIAL_TRA].Y + boardTra.Y) + SR->DB->pAUTOInspectionCurrentSiteStruct->Y, ABS_MOVE );
				//in questo modo, va sempre sul fiduciale!
				//retVal = SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX +fidPosition[FIDUCIAL_TRA].X + boardTra.X , SR->DB->ProductionDataS.PCBPosY +fidPosition[FIDUCIAL_TRA].Y + boardTra.Y, ABS_MOVE );

			}
			else
			{
				// to the pcb center position
				retVal = SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX + SR->DB->ProductionDataS.PCBX/2.0f, SR->DB->ProductionDataS.PCBPosY + SR->DB->ProductionDataS.PCBY/2.0f, ABS_MOVE );
			}
			if( retVal == SR_ERROR )
				return SR_ERROR;

			// Start live video
			camera->SetMainMode( MAIN_CAMERA_INSPECTION_RECTANGLE );
			camera->SetAuxMode( AUX_CAMPOSITION );
			camera->StartCapture();

			// sets controls state
			controlPanel->SetState( PANEL_INSPECTION_MOVE );
			panel->Enable( true );
			panel->DrawControl( IP_ONLINE_MOVE );
			isAuxVideoClickEnable = true;
			//
			datasette->StopEnable( true );
			isFirstTime=true;
			break;

		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_TEACH:
			camera->SetMainMode( MAIN_BLANK );
			camera->SetAuxMode( AUX_BLANK );
			menuBtn->Enable(false);
			datasette->StartEnable(false);


			if( SR->DB->WorkingModesS.InspectionType != INSPECTION_SPI )
			{
				if( SMInspection( INSPECTION_STATE_TEACH_OK ) == SR_ERROR )
					return SR_ERROR;
				break;
			}

			// save params
			shadow_site = *SR->DB->pAUTOInspectionCurrentSiteStruct;

			if( !isOffline )
			{
				//TEMP - scelta provvisoria per velocizzare il tutto
				// chiede se duplicare sito precedente
				bool duplicate = false;
				if( SR->DB->SiteGetSelected() > 0 )
				{
					if( wxMessageBox( "Duplicare i parametri dal sito precedente ?", MACHINE_NAME, wxYES_NO | wxICON_QUESTION, parent ) == wxYES )
					{
						

						duplicate = true;

						//aggiunto!
						SR->DB->pAUTOInspectionCurrentSiteStruct--;
						AUTOInspectionSitesStruct previous_site =*SR->DB->pAUTOInspectionCurrentSiteStruct;
						SR->DB->pAUTOInspectionCurrentSiteStruct++;
						previous_site.IdSite = SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite;;
						previous_site.Name = SR->DB->pAUTOInspectionCurrentSiteStruct->Name;;
						*SR->DB->pAUTOInspectionCurrentSiteStruct = previous_site;

						SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids.clear(); //must be dome because push_back is additive!
						SR->DB->pAUTOInspectionCurrentSiteStruct->Area.clear();
						SR->DB->pAUTOInspectionCurrentSiteStruct->Contours.clear();
						SR->DB->pAUTOInspectionCurrentSiteStruct->SpotEnable.clear();

						SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask.clear();
						SR->DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask.clear();
						SR->DB->pAUTOInspectionCurrentSiteStruct->Area_Mask.clear();
						SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.Mask.clear();
						SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.PCB.clear();

						SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor =0;



					}
					SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor =0;
				}


			}

			// continue to following state (internal event)
			currentState = INSPECTION_STATE_TEACH_FIND;

		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_TEACH_FIND:

				if( !isOffline )
				{

					if(isFirstTime){

						if( SR->SetCamera( CAMERA_UP ) == SR_ERROR )
						{
							smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
							return SR_ERROR;
						}
						myMilliSleep( FLICKERING_DELAY );
						camera->StartCapture();
						camera->GetColorFrames(1);
						camera->StopCapture();
						Frame_to_Mat = camera->GetWorkingColorFrame(0);


						wxString fullpath( wxString::Format(FILE_PRODUCTION_FOLDER, SR->DB->ProductionDataS.ProductionName.ToAscii() ) );
						// check if dir exist, if no create it
						if( !wxDirExists( fullpath ) )
							wxMkdir( fullpath );

						fullpath.Append( wxString::Format( FILE_SITEREF, SR->DB->ProductionDataS.ProductionName.ToAscii(), SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite ).ToAscii() );
						cv::imwrite(fullpath.ToAscii(), Frame_to_Mat);

						AutoSPIproc->FindRegions(&Frame_to_Mat, adaptive, true); //scan the mask

						// Enable camera
						if( SR->SetCamera( CAMERA_DOWN ) == SR_ERROR )
							{
							 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
							 return SR_ERROR;
							}

						myMilliSleep( FLICKERING_DELAY );
						camera->StartCapture();
						camera->GetColorFrames(1);
						camera->StopCapture();

						isFirstTime =false;
						AutoSPIproc->FindRegions( &Frame_to_Mat, simple, true ); //scan the site
						SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots = AutoSPIproc->MatchRegions(true);
						AutoSPIproc->CorrectTraslation();
						SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.Mask.clear();
						SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.PCB.clear();

						SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots = AutoSPIproc->MatchRegions(false);
						AutoSPIproc->AdaptScale(&Frame_to_Mat);

					}
					else{
						AutoSPIproc->FindRegions( &Frame_to_Mat, simple, true ); //scan the site
						AutoSPIproc->FindRegions( &camera->Mask_frame, adaptive, false );//scan the Mask, with the picture in memory
						SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots = AutoSPIproc->MatchRegions(true);
						AutoSPIproc->CorrectTraslation();
						SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.Mask.clear();
						SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.PCB.clear();

						SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots = AutoSPIproc->MatchRegions(false);
					}

			}
			else
			{

				//Frame_to_Mat=cv::cvarrToMat(camera->GetWorkingFrame());
				AutoSPIproc->FindRegions( &camera->Mask_frame, simple, false );
				AutoSPIproc->FindRegions( &camera->Mask_frame, adaptive, false );//scan the Mask, with the picture in memory
				SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots = AutoSPIproc->MatchRegions(true); //true means distance between centroids is used
				AutoSPIproc->CorrectTraslation();
				SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.Mask.clear();
				SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.PCB.clear();

				SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots = AutoSPIproc->MatchRegions(false);	//false means we use pointPolytest



			}

			// continue to following state (internal event)
			currentState = INSPECTION_STATE_TEACH_DRAW;

		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_TEACH_DRAW:



			camera->SetAuxMode( AUX_INSPECTION_MASK );
			//Frame_to_Mat=cv::cvarrToMat(camera->GetWorkingFrame());


			AutoSPIproc->spiDraw( &Frame_to_Mat );

			// sets controls state
			if(!isOffline){
				panel->DrawControl( IP_TEACH );
			}
			else{
				//panel->DrawControl( IP_TEACH );
				panel->DrawControl( IP_TEACH_OFFLINE );
			}

			isMainVideoClickEnable = true;



			break;

		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_TEACH_OK:
			camera->SetMainMode( MAIN_BLANK );
			camera->SetAuxMode( AUX_BLANK );

			if( !isOffline )
			{


				//get position and refers it to the translational fiducial + how much it was shifted
				SR->GetCameraPosition( camPos.X, camPos.Y );
				SR->DB->pAUTOInspectionCurrentSiteStruct->X = camPos.X - (SR->DB->ProductionDataS.PCBPosX +fidPosition[FIDUCIAL_TRA].X + boardTra.X);
				SR->DB->pAUTOInspectionCurrentSiteStruct->Y = camPos.Y - (SR->DB->ProductionDataS.PCBPosY +fidPosition[FIDUCIAL_TRA].Y + boardTra.Y);
				//SR->DB->pAUTOInspectionCurrentSiteStruct->X = camPos.X - (fidPosition[FIDUCIAL_TRA].X + boardTra.X);
				//SR->DB->pAUTOInspectionCurrentSiteStruct->Y = camPos.Y - (fidPosition[FIDUCIAL_TRA].Y + boardTra.Y);

				SR->DB->pAUTOInspectionCurrentSiteStruct->Orientation =frameRot/180*PI;

			}

			// Enable current site
			AutoSPIproc->ComputeSupposedUncoveredArea();

			//aggiunto
			SR->DB->pAUTOInspectionCurrentSiteStruct->Enable = 1;


			// get camera params
			SR->DB->pAUTOInspectionCurrentSiteStruct->CameraBrightness = SR->DB->pCurrentFiducial->CameraBrightness;
			SR->DB->pAUTOInspectionCurrentSiteStruct->CameraContrast = SR->DB->pCurrentFiducial->CameraContrast;
			// save

			SR->DB->SaveInspectionSite( SR->DB->SiteGetSelected() );
			SR->DB->SaveInspectionSiteMask();

			if( !isOffline )
			{
				// save image (to work offline)
				//IplImage* _image = camera->GetWorkingFrame();
				wxString fullpath( wxString::Format(FILE_PRODUCTION_FOLDER, SR->DB->ProductionDataS.ProductionName.ToAscii() ) );
				// check if dir exist, if no create it
				if( !wxDirExists( fullpath ) )
					wxMkdir( fullpath );

				fullpath.Append( wxString::Format( FILE_SITE, SR->DB->ProductionDataS.ProductionName.ToAscii(), SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite ).ToAscii() );
				cv::imwrite(fullpath.ToAscii(), Frame_to_Mat);

				// draw board and sites
				if( SR->DB->ProductionDataS.PCBPosX != 0.0 )
					//TODO
					camera->DrawWorkplaceWithSites( SR->DB->ProductionDataS.PCBPosX, SR->DB->ProductionDataS.PCBPosY, SR->DB->ProductionDataS.PCBX, SR->DB->ProductionDataS.PCBY );

				// goto next site
				if( SR->DB->SiteNext() == false )
				{
					// last site reached: ask to add new site
					if( wxMessageBox( MSG_ASK_ADD_SITE, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, parent ) != wxYES )
					{
						// procedure complete
						smartLogger->Write( MSG_INSP_TECH_ENDED, MSG_SUCCESS );
						SMReset();
						break;
					}

					// add inspection site
					if( SR->DB->InsertInspectionSite() == SR_ERROR )
					{
						wxMessageBox( MSG_MAXSITEREACHED, MACHINE_NAME, wxOK | wxICON_INFORMATION, parent );

						// procedure complete
						smartLogger->Write( MSG_INSP_TECH_ENDED, MSG_SUCCESS );
						SMReset();
						break;
					}

					// select new site
					SR->DB->SiteLast();
				}
				if( SMInspection( INSPECTION_STATE_MOVE ) == SR_ERROR )
					return SR_ERROR;
			}
			else
			{
				SMReset();
			}
			//menuBtn->Enable(true);
			//datasette->StartEnable(true);
			break;

		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_TEACH_CANCEL:
			// avoid to save not congruent data
			shadow_site.Name = SR->DB->pAUTOInspectionCurrentSiteStruct->Name; // name is always saved

			*SR->DB->pAUTOInspectionCurrentSiteStruct = shadow_site;
			toolBox -> Enable(true);
			menuBtn->Enable(true);
			datasette->StartEnable(true);

			if( !isOffline )
			{
				if( SMInspection( INSPECTION_STATE_RESET ) == SR_ERROR )
					return SR_ERROR;
			}
			else
			{
				SMReset();
			}
			break;

		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_SET_THRESHOLD_START:


			camera->SetMainMode( MAIN_MOUSE_CUR_NO_CROSSHAIR );
			AutoSPIproc->LoadDraw(&Frame_to_Mat, simple);
			AutoSPIproc->spiDraw( &Frame_to_Mat);
			//spiProc->spiDraw( camera->GetWorkingFrame(), false, false );
			//camera->SetVideoMainImage( wxImage(CAM_W, CAM_H, (unsigned char*)Frame_to_Mat.data ,true) );
			camera->SetMainMode( MAIN_MOUSE_CUR_NO_CROSSHAIR );

			// sets controls state
			panel->DrawControl( IP_TEACH_THR );
			isMainVideoClickEnable = true;
			break;

		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_SET_THRESHOLD_END:
			camera->SetMainP1( xClicked, yClicked );
			camera->SetMainMode( MAIN_LINE_XY );
			startPos.X = xClicked;
			startPos.Y = yClicked;

			// Enable mouse click
			isMainVideoClickEnable = true;
			break;

		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_SET_THRESHOLD_DIALOG:
			camera->SetMainMode( MAIN_NO_CUR );

			if( AutoSPIproc->spiSelectThresholdMat( &Frame_to_Mat, startPos, PointI( xClicked, yClicked ) ) );
				//isFirstTime = true;

			if( SMInspection( INSPECTION_STATE_TEACH_FIND ) == SR_ERROR )
				return SR_ERROR;
			break;

		//----------------------------------------------------------------------------------
		case INSPECTION_STATE_SET_THRESHOLD_CANCEL:
			camera->SetMainMode( MAIN_NO_CUR );

			if( SMInspection( INSPECTION_STATE_TEACH_DRAW ) == SR_ERROR )
				return SR_ERROR;
			break;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMInspectionNext
// Aggiorna lo stato della SM
//----------------------------------------------------------------------------------
void SMBase::SMInspectionNext( int data )
{
	retVal = SR_OK;

	switch( currentState )
	{
		case INSPECTION_STATE_IDLE_FIND:
		case INSPECTION_STATE_IDLE_DRAW:
			if( data == wxInspectionPanel::EVT_TEACH )
				retVal = SMInspection( INSPECTION_STATE_TEACH );
			else if( data == wxInspectionPanel::EVT_NEED_REFRESH )
				retVal = SMInspection( INSPECTION_STATE_IDLE_DRAW );
			else if( data == wxInspectionPanel::EVT_NEED_REFRESH_IMAGE )
			{

				//Frame_to_Mat =cv::cvarrToMat(camera->GetWorkingFrame());
				AutoSPIproc->spiDraw(&Frame_to_Mat);
			}
			else if( data == wxInspectionPanel::EVT_NEED_UPDATE )
				retVal = SMInspection( INSPECTION_STATE_IDLE_FIND );
			//aggiunto, now play calls onnexte and not Inspection(0)
			else if (data==-1){
				retVal = SMInspection(INSPECTION_STATE_INIT);
			}

			break;

		case INSPECTION_STATE_FOUND_WAIT_A:
			retVal = SMInspection( INSPECTION_STATE_FOUND_A );
			break;

		case INSPECTION_STATE_FOUND_A:
			retVal = SMInspection( INSPECTION_STATE_NEXT_A );
			break;

		case INSPECTION_STATE_MOVE:
			if( data == wxInspectionPanel::EVT_TEACH )
				retVal = SMInspection( INSPECTION_STATE_TEACH );
			else if( data == wxInspectionPanel::EVT_NEED_REFRESH )
				retVal = SMInspection( INSPECTION_STATE_MOVE );
			else if( data == wxInspectionPanel::EVT_NEED_UPDATE )
				retVal = SMInspection( INSPECTION_STATE_MOVE );
			break;

		case INSPECTION_STATE_TEACH_DRAW:
			if( data == wxInspectionPanel::EVT_THRESHOLD )
				retVal = SMInspection( INSPECTION_STATE_TEACH_FIND );
			else if( data == wxInspectionPanel::EVT_SET_THRESHOLD )
				retVal = SMInspection( INSPECTION_STATE_SET_THRESHOLD_START );
			else if( data == wxInspectionPanel::EVT_NEED_REFRESH )
				retVal = SMInspection( INSPECTION_STATE_TEACH_DRAW );
			else if( data == wxInspectionPanel::EVT_NEED_REFRESH_IMAGE ){
				//Frame_to_Mat=cv::cvarrToMat(camera->GetWorkingFrame());
				AutoSPIproc->spiDraw( &Frame_to_Mat);
			}
			else if( data == wxInspectionPanel::EVT_OK )
				retVal = SMInspection( INSPECTION_STATE_TEACH_OK );
			else if( data == wxInspectionPanel::EVT_CANCEL )
				retVal = SMInspection( INSPECTION_STATE_TEACH_CANCEL );

			else if( data == wxInspectionPanel::EVT_NEED_UPDATE )
				retVal = SMInspection( INSPECTION_STATE_IDLE_FIND );
			break;

		case INSPECTION_STATE_SET_THRESHOLD_START:
		case INSPECTION_STATE_SET_THRESHOLD_END:
			retVal = SMInspection( INSPECTION_STATE_SET_THRESHOLD_CANCEL );
			break;
		//case INSPECTION_STATE_REFERENCE_MASK:
			//retVal = SMInspection( INSPECTION_STATE_REFERENCE_MASK_TEACH);
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

//----------------------------------------------------------------------------------
// SMInspectionPrev
// Aggiorna lo stato della SM
//----------------------------------------------------------------------------------
void SMBase::SMInspectionPrev( int data )
{
	retVal = SR_OK;

	switch( currentState )
	{
		case INSPECTION_STATE_SEARCH_A:
		case INSPECTION_STATE_FOUND_WAIT_A:
			retVal = SMInspection( INSPECTION_STATE_SEARCH_A );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}


//----------------------------------------------------------------------------------
// SMInspectionMainVideoLeftClick
//----------------------------------------------------------------------------------
void SMBase::SMInspectionMainVideoLeftClick( wxMouseEvent& e )
{
	retVal = SR_OK;

	if( !isMainVideoClickEnable )
		return;

	// Cursor position
	camera->GetCursorPositionMain( xClicked, yClicked );

	switch( currentState )
	{
		case INSPECTION_STATE_SEARCH_A:
			centerX = xClicked;
			centerY = yClicked;

			camera->SetMainMode( MAIN_NO_CUR );
			// Disable camera
			if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
			}

			smartLogger->Write( wxString::Format( MSG_FIDFOUNDMAN, xClicked, yClicked ) );
			retVal = SMInspection( INSPECTION_STATE_FOUND_WAIT_A );
			break;

		case INSPECTION_STATE_TEACH_DRAW:
			// save click position
			startPos = PointI( xClicked, yClicked );
			cout<<"start position x: "<<xClicked<< "   y: "<< yClicked<<endl;
			break;

		case INSPECTION_STATE_SET_THRESHOLD_START:
			retVal = SMInspection( INSPECTION_STATE_SET_THRESHOLD_END );
			break;

		case INSPECTION_STATE_SET_THRESHOLD_END:
			retVal = SMInspection( INSPECTION_STATE_SET_THRESHOLD_DIALOG );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

//----------------------------------------------------------------------------------
// SMInspectionMainVideoLeftClickUp
//----------------------------------------------------------------------------------
void SMBase::SMInspectionMainVideoLeftClickUp( wxMouseEvent& e )
{
	retVal = SR_OK;

	// Cursor position
	camera->GetCursorPositionMain( xClicked, yClicked );
	cout<<"end position x: "<<xClicked<< "   y: "<< yClicked<<endl;

	switch( currentState )
	{

		case INSPECTION_STATE_TEACH_DRAW:


			if( abs( startPos.X - xClicked ) <= SPI_DRAG_MIN_DIST && abs( startPos.Y - yClicked ) <= SPI_DRAG_MIN_DIST ){
				//spiProc->spiTogglePointAt( PointI( xClicked, yClicked ) );
				AutoSPIproc->TogglePointAt(PointI( xClicked, yClicked ) );
			}
			else{
				// if Ctrl is pressed deselect, otherwise select
				AutoSPIproc->spiSetPointsInsideRect( startPos, PointI( xClicked, yClicked ), e.ControlDown() ? false : true );
			}
			// draw is always needed to erase the drag rectangle

			//Frame_to_Mat =cv::cvarrToMat(camera->GetWorkingFrame());
			AutoSPIproc->spiDraw(&Frame_to_Mat);
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

//----------------------------------------------------------------------------------
// SMInspectionMainVideoMove
//----------------------------------------------------------------------------------
void SMBase::SMInspectionMainVideoMove( wxMouseEvent& e )
{
	e.Skip();

	retVal = SR_OK;

	if( !e.LeftIsDown() )
		return;

	// Cursor position
	camera->GetCursorPositionMain( xClicked, yClicked );

	switch( currentState )
	{
		case INSPECTION_STATE_TEACH_DRAW:
			//Frame_to_Mat=cv::cvarrToMat(camera->GetWorkingFrame());
			AutoSPIproc->spiDrawMouseDrag( startPos, PointI( xClicked, yClicked ) , &Frame_to_Mat );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

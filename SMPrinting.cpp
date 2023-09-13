//---------------------------------------------------------------------------
//
// Name:        SMPrinting.cpp
// Author:      Daniele Belloni, Gabriel Ferri
// Created:     20/05/2008 11.23
// Description: Printing - State Machine functions implementation
//
//---------------------------------------------------------------------------

#include "SMBase.h"
#include "wxProductionPanel.h"
#include "wxInspectionPanel.h"
#include <wx/msgdlg.h>
#include "GlobalUtils.h"
#include "Messages.h"



#include "FileFunctions.h"

#define PANEL_PRINTING		PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE
#define PANEL_VERIFY_MOVE	PANEL_MOVE_CAMERA, PANEL_OUTPUT_LED_UP | PANEL_OUTPUT_LED_DOWN
#define PANEL_DISABLE		PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE



//----------------------------------------------------------------------------------
// SMPrintingInitialize
// Inizializza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMPrintingInitialize()
{
	mainVideo->ConnectMainVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMPrintingMainVideoLeftClick ), this );
	mainVideo->ConnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );
	mainVideo->ConnectMainVideoKeyEvent( wxEVT_CHAR, wxStaticCastEvent( wxCharEventFunction, &SMBase::SMMainVideoKeyPress ), this );

	controlPanel->SetState( PANEL_PRINTING );
	cleanCounter = 0;
	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMPrintingFinalize
// Finalizza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMPrintingFinalize()
{
	mainVideo->DisconnectMainVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMPrintingMainVideoLeftClick ), this );
	mainVideo->DisconnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );
	mainVideo->DisconnectMainVideoKeyEvent( wxEVT_CHAR, wxStaticCastEvent( wxCharEventFunction, &SMBase::SMMainVideoKeyPress ), this );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMPrintingReset
// Resetta la macchina a stati
//----------------------------------------------------------------------------------
void SMBase::SMPrintingReset()
{
	SR->CheckCover( false );

	// Reset plate to normal movement params
	SR->PlateMotor.SetSpeedAcc();

	controlPanel->SetState( PANEL_PRINTING );

	wxProductionPanel *panel = (wxProductionPanel *)currentPanel;
	panel->UpdatePrintingPanel();
	panel->EnablePrintingPanel( true );
	//Squeegees up, both
	if( SR->SetOutput( OUTPUT_SQUEEGEESFRONT, false ) == SR_ERROR  )
		{
			smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
		}
	if( SR->SetOutput( OUTPUT_SQUEEGEESREAR, false ) == SR_ERROR  )
		{
			smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
		}
	//Disable cleaner and Disengage
	if( SR->DB->MachineParamsS.CleaningInstalled && SR->DB->WorkingModesS.CleaningEn ){
		if( SR->DB->MachineParamsS.CleaningVacuumOn ){
			if( SR->SetOutput( OUTPUT_CLEANINGVACUUM, false ) == SR_ERROR )	{
				smartLogger->Write( MSG_CLEANVACUUMERROR, MSG_ERROR );
			}
		}

		// Disengage cleaning system
		if( SR->SetOutput( OUTPUT_CLEANINGLOCK, false ) == SR_ERROR ){
				smartLogger->Write( MSG_CLEANPISTONERROR, MSG_ERROR );
		}
	}

	//Release camera piston
	if( SR->SetOutput( OUTPUT_CAMERA_PISTON, false ) == SR_ERROR )
	{
		smartLogger->Write( MSG_CAMPISTONERROR, MSG_ERROR );
	}

	//Disable light
	if( SR->SetCamera( CAMERA_OFF )== SR_ERROR){
		smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
	}
	// Move camera out
	if( SR->MoveCameraAndWait( (SR->DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit - SR->DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit)/2, SR->DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit, ABS_MOVE ) == SR_ERROR )
	{
		smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
	}


}

//----------------------------------------------------------------------------------
// SMPrinting
// Macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMPrinting( int nextState )
{
	retVal = SR_OK;

	datasette->StopEnable( false );
	datasette->NextEnable( false );
	datasette->PrevEnable( false );
	controlPanel->SetState( PANEL_DISABLE );

	currentState = nextState;
	wxProductionPanel *panel = (wxProductionPanel *)currentPanel;
	SpeedTableStruct speed_entry;


	// Se e' stato premuto il pulsante di stop...
	if( SR->GetStop() )
		currentState = PRINTING_STATE_STOP;

	switch( currentState )
	{
		//----------------------------------------------------------------------------------
		case PRINTING_STATE_INIT1:

			// Aggiorna i dati editati dal pannello
			panel->UpdatePrintingData();

			//aggiunto
			expectedPos.X=0;
			expectedPos.Y=0;

			// Se sono in modalita' loader, abilito il pulsante di stop nel datasette per poter
			// eventualmente terminare il ciclo continuo di serigrafia
			if( SR->DB->MachineParamsS.LoaderInstalled && SR->DB->WorkingModesS.LoaderEn )
			{
				if( SR->DB->ProductionDataS.LoaderBoardNumber == 0 )
				{
					if( wxMessageBox( MSG_PRINTINGZEROBOARD, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, parent ) != wxYES )
					{
						smartLogger->Write( MSG_PRINTINGABORTED, MSG_ERROR );
						if( SMPrinting( PRINTING_STATE_RESET ) == SR_ERROR )
							return SR_ERROR;
						break;
					}
				}
				else
				{
					SR->SetLoaderStop( false );
					datasette->PauseEnable( true );
				}
				//if the last printed position = rack position
				int ss = SR->GetLastPrintedRackPos();
				int fff= SR->GetRackPos();
				//if(SR->GetLastPrintedRackPos() == SR->GetRackPos()){
				if(SR->GetLastPrintedRackPos() == SR->GetRackPos() && !SR->isBoardLoaded){
					if( wxMessageBox( MSG_WARNINGDOUBLEPRNT, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, parent ) == wxYES )
					{
						if( SR->LoaderMove( SR->GetRackPos()+1 ) == SR_ERROR )
						{
							smartLogger->Write( MSG_LOADERERROR, MSG_ERROR );
							return SR_ERROR;
						}
					}
					//si continua con la stampa sulla scheda
				}
			}


			panel->EnablePrintingPanel( false );

			initCheck.cover			= true;
			initCheck.air			= true;
			initCheck.pcb			= false;
			initCheck.pcb_height	= 0;
			initCheck.frame			= true;
			initCheck.motors_pos	= true;
			initCheck.motor_state	= MODE_STARTPRINTING_POSITION;

			// Contatore per far partire la verifica
			// Se il loader non e' abilitato, lo metto sempre ad 1, in modo da far partire la verifica (se abilitata)
			if( SR->DB->MachineParamsS.LoaderInstalled && SR->DB->WorkingModesS.LoaderEn )
				verifyCounter = SR->verifyEvery;
			else
				verifyCounter = 1;

			if(cleanCounter == 0){
				cleanCounter = SR->cleanEvery;
			}
			/*
			// Contatore per far partire la verifica
			if( SR->DB->MachineParamsS.CleaningInstalled && SR->DB->WorkingModesS.CleaningEn && SR->DB->MachineParamsS.LoaderInstalled && SR->DB->WorkingModesS.LoaderEn )
				cleanCounter = SR->cleanEvery;
			else if( SR->DB->MachineParamsS.CleaningInstalled && SR->DB->WorkingModesS.CleaningEn )
				cleanCounter = 1;
			else
				cleanCounter = -1;*/

			if( SMInitCheck( initCheck ) == SR_ERROR )
				return SR_ERROR;

			// Printing cycle can begin.
			if( SMPrinting( PRINTING_STATE_INIT2 ) == SR_ERROR )
				return SR_ERROR;
			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_INIT2:

			if( SR->SetAlarmLight( ALARMLIGHT_GREEN ) == SR_ERROR )
			{
				smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
				return SR_ERROR;
			}

			panel->DrawControl(PP_PRINTING);
			panel->Layout();
			panel->EnablePrintingPanel( false );

			// Move the board inside the machine
			if( LoadBoardCameraCheck() == SR_ERROR )
			{
				smartLogger->Write( MSG_LOADERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// draw board
			if( SR->DB->ProductionDataS.PCBPosX != 0.0 )
				camera->DrawWorkplace( SR->DB->ProductionDataS.PCBPosX, SR->DB->ProductionDataS.PCBPosY, SR->DB->ProductionDataS.PCBX, SR->DB->ProductionDataS.PCBY );

			camera->SetAuxMode( AUX_SMOOTH_EDGE );

			currentFiducial = FIDUCIAL_ROT1;
			fiducialSearchTerminated = false;
			verifyAutoFlag = SR->DB->WorkingModesS.PrintingVerifyAuto;
			offsetR1X = 0.0;
			offsetR1Y = 0.0;
			offsetR2X = 0.0;
			offsetR2Y = 0.0;

			if( SMPrinting( PRINTING_STATE_ALIGNPOS ) == SR_ERROR )
				return SR_ERROR;
			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_RESET:

			// stop live video
			camera->StopCapture();
			camera->SetMainMode( MAIN_BLANK );
			camera->SetAuxMode( AUX_BLANK );



			// disable mouse click
			isMainVideoClickEnable = false;
			isAuxVideoClickEnable = false;

			// Reset plate to normal movement params
			if( SR->PlateMotor.SetSpeedAcc() == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Disable camera
			if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}
			// Check for motors position
			if( SR->CheckMotorsPos() == SR_ERROR )
			{
				if( SR->ResetMotors( SR->GetStop() ? MODE_START_POSITION : MODE_STARTPRINTING_POSITION ) == SR_ERROR )
					return SR_ERROR;
			}

			panel->UpdatePrintingPanel();
			panel->EnablePrintingPanel( true );
			toolBox->Enable( true );
			menuBtn->Enable( true );
			datasette->StartEnable( true );
			datasette->PauseEnable( false );

			SR->CheckCover( false );

			controlPanel->SetState( PANEL_PRINTING );

			if( SR->SetAlarmLight( ALARMLIGHT_YELLOW ) == SR_ERROR )
			{
				smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
				return SR_ERROR;
			}


			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_ALIGNPOS:
			// Move the board to reaches the camera focus
			if( SR->PlateMotor.Move( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Roto-translate table to alignment position
			if( SR->RotateTableAndWait( SR->DB->ProductionDataS.LastRot ) == SR_ERROR )
			{
				smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
				return SR_ERROR;
			}
			if( SR->MoveXYTableAndWait( SR->DB->ProductionDataS.LastX, SR->DB->ProductionDataS.LastY, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			if( SMPrinting( PRINTING_STATE_SEARCH ) == SR_ERROR )
				return SR_ERROR;
			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_PRINT1:
			camera->SetMainMode( MAIN_BLANK );
			camera->SetAuxMode( AUX_BLANK );

			// Move the board to reaches the frame
			if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.PlateMovement + SR->DB->ProductionDataS.PlateMovementDelta, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}
			// If vision debug is activated...
			if( SR->DB->WorkingModesS.DebugMode )
			{
				// ...check the board position and wait next button 
				smartLogger->Write( MSG_PRINTINGVERIFY );

				datasette->StopEnable( true );
				datasette->NextEnable( true );
				break;
			}

			if( SMPrinting( PRINTING_STATE_PRINT2 ) == SR_ERROR )
				return SR_ERROR;
			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_PRINT2:
			// Move squeegees for printing
			smartLogger->Write( MSG_PRINTING );

			for( int i = 0; i < SR->DB->WorkingModesS.DoubleSqueegees + 1; i++ )
			{
				if( ( SR->GetSqueegeesCycle() == true && SR->DB->ProductionDataS.SqueegeesMove <= 0 ) ||
					( SR->GetSqueegeesCycle() == false && SR->DB->ProductionDataS.SqueegeesMove > 0 ) )
				{
					// Squeeges are on the back side...

					// Move the squeegees
					float squeegeesMovement = 0.0f;
					// Move the squeegees - recovery movement
					if( SR->DB->ProductionDataS.SqueegeesRecoveryRear != 0.0f )
					{
						if( SR->SqueegeesMotor.Check( SR->DB->ProductionDataS.SqueegeesRecoveryRear, REL_MOVE ) == MOTOR_OK )
						{
							if( SR->SqueegeesMotor.MoveAndWait( SR->DB->ProductionDataS.SqueegeesRecoveryRear, REL_MOVE ) == SR_ERROR )
							{
								smartLogger->Write( MSG_SQUEEGEESERROR, MSG_ERROR );
								return SR_ERROR;
							}
							squeegeesMovement -= SR->DB->ProductionDataS.SqueegeesRecoveryRear;
							myMilliSleep( SQUEEGEES_RECOVERY_DELAY );
						}
						else
							smartLogger->Write( MSG_PRINTINGRECOVERYERR, MSG_ERROR );
					}

					// ...activate rear squeegee and, just in case, deactivate front one
					if( SR->SetOutput( OUTPUT_SQUEEGEESREAR, true ) == SR_ERROR )
					{
						smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
						return SR_ERROR;
					}

					if( SR->SetOutput( OUTPUT_SQUEEGEESFRONT, false ) == SR_ERROR )
					{
						smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
						return SR_ERROR;
					}
					// Wait to be sure the squeegees are activated
					myMilliSleep( SQUEEGEES_DELAY );

					// Move the squeegees - print movement
					squeegeesMovement += fabs( SR->DB->ProductionDataS.SqueegeesMove );
					if( SR->SqueegeesMotor.MoveAndWait( squeegeesMovement, REL_MOVE ) == SR_ERROR )
					{
						smartLogger->Write( MSG_SQUEEGEESERROR, MSG_ERROR );
						return SR_ERROR;
					}

					if( (!SR->DB->WorkingModesS.DoubleSqueegees) || (i==SR->DB->WorkingModesS.DoubleSqueegees) ){
						// Deactivate rear squeege

						if( SR->SetOutput( OUTPUT_SQUEEGEESREAR, false ) == SR_ERROR )
						{
							smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
							return SR_ERROR;
						}
						SR->SetSqueegeesCycle( !SR->GetSqueegeesCycle() );
					}else{
						//se c'è del front recovery
						if( SR->DB->ProductionDataS.SqueegeesRecoveryFront != 0.0f )
						{
							//c'e del recovery, ignoriamo il fatto di dove far calare la racla prima di sollevare quella appena usata

							if( SR->SetOutput( OUTPUT_SQUEEGEESREAR, false ) == SR_ERROR )
							{
								smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
								return SR_ERROR;
							}
							myMilliSleep( SQUEEGEES_DELAY ); //attendiamo che cali

							SR->SetSqueegeesCycle( !SR->GetSqueegeesCycle() );
							continue;
						}

						if( SR->SetOutput( OUTPUT_SQUEEGEESFRONT, true ) == SR_ERROR )
							{
								smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
								return SR_ERROR;
							}
						myMilliSleep( SQUEEGEES_DELAY ); //attendiamo che cali
						if( SR->SetOutput( OUTPUT_SQUEEGEESREAR, false ) == SR_ERROR )
							{
								smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
								return SR_ERROR;
							}
							SR->SetSqueegeesCycle( !SR->GetSqueegeesCycle() );
					}
				}
				else
				{
					// Squeegees are on the operator side...

					// Move the squeegees
					float squeegeesMovement = 0.0f;
					// Move the squeegees - recovery movement
					if( SR->DB->ProductionDataS.SqueegeesRecoveryFront != 0.0f )
					{
						if( SR->SqueegeesMotor.Check( SR->DB->ProductionDataS.SqueegeesRecoveryFront, REL_MOVE ) == MOTOR_OK )
						{
							if( SR->SqueegeesMotor.MoveAndWait( SR->DB->ProductionDataS.SqueegeesRecoveryFront, REL_MOVE ) == SR_ERROR )
							{
								smartLogger->Write( MSG_SQUEEGEESERROR, MSG_ERROR );
								return SR_ERROR;
							}
							squeegeesMovement -= SR->DB->ProductionDataS.SqueegeesRecoveryFront;
							myMilliSleep( SQUEEGEES_RECOVERY_DELAY );
						}
						else
							smartLogger->Write( MSG_PRINTINGRECOVERYERR, MSG_ERROR );
					}

					// ...activate front squeege and, just in case, deactivate rear one
					if( SR->SetOutput( OUTPUT_SQUEEGEESFRONT, true ) == SR_ERROR )
					{
						smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
						return SR_ERROR;
					}

					if( SR->SetOutput( OUTPUT_SQUEEGEESREAR, false ) == SR_ERROR )
					{
						smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
						return SR_ERROR;
					}
					// Wait to be sure the squeegees are activated
					myMilliSleep( SQUEEGEES_DELAY );

					// Move the squeegees - print movement
					squeegeesMovement -= fabs( SR->DB->ProductionDataS.SqueegeesMove );
					if( SR->SqueegeesMotor.MoveAndWait( squeegeesMovement, REL_MOVE ) == SR_ERROR )
					{
						smartLogger->Write( MSG_SQUEEGEESERROR, MSG_ERROR );
						return SR_ERROR;
					}

					if( (!SR->DB->WorkingModesS.DoubleSqueegees) || (i==SR->DB->WorkingModesS.DoubleSqueegees) ){
						// Deactivate front squeegees

						if( SR->SetOutput( OUTPUT_SQUEEGEESFRONT, false ) == SR_ERROR  )
						{
							smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
							return SR_ERROR;
						}
						SR->SetSqueegeesCycle( !SR->GetSqueegeesCycle() );
					}else{
						//da fare il secondo giro!
						if( SR->DB->ProductionDataS.SqueegeesRecoveryRear != 0.0f )
						{
							//c'e del recovery, ignoriamo il fatto di dove far calare la racla prima di sollevare quella appena usata

							if( SR->SetOutput( OUTPUT_SQUEEGEESFRONT, false ) == SR_ERROR )
							{
								smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
								return SR_ERROR;
							}
							myMilliSleep( SQUEEGEES_DELAY );
							SR->SetSqueegeesCycle( !SR->GetSqueegeesCycle() );
							continue;
						}

						if( SR->SetOutput( OUTPUT_SQUEEGEESREAR, true ) == SR_ERROR )
							{
								smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
								return SR_ERROR;
							}
						myMilliSleep( SQUEEGEES_DELAY ); //attendiamo che cali
						if( SR->SetOutput( OUTPUT_SQUEEGEESFRONT, false ) == SR_ERROR )
							{
								smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
								return SR_ERROR;
							}
							SR->SetSqueegeesCycle( !SR->GetSqueegeesCycle() );
					}
					//SR->SetSqueegeesCycle( !SR->GetSqueegeesCycle() );

				}
			}

			// Increment counters
			SR->DB->ProductionDataS.Counter++;
			SR->DB->SaveProductionData();
			SR->DB->MachineParamsS.Counter++;
			SR->DB->SaveMachineParams();

			// Disengage board from frame...
			
			// Wait to be sure the squeegees are up
			myMilliSleep( SQUEEGEES_DELAY );
			
			// If required, execute a slow speed disengage
			if( SR->DB->WorkingModesS.DifferentialDisengage && ( SR->DB->WorkingModesS.DisengageSpeed != 0.0 ) )
			{
				// Set plate disengage movement params
				speed_entry = SR->DB->SpeedTableS[SPEED_PLATE_DOWN_ID];
				if( SR->PlateMotor.SetSpeedAcc( lround(SR->DB->WorkingModesS.DisengageSpeed), speed_entry.Acc[SR->DB->MachineParamsS.PlateDownSpeed], speed_entry.Dec[SR->DB->MachineParamsS.PlateDownSpeed] ) == SR_ERROR )
				{
					smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
					return SR_ERROR;
				}
				if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
				{
					smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
					return SR_ERROR;
				}
			}

			// Set plate down parameters
			speed_entry = SR->DB->SpeedTableS[SPEED_PLATE_DOWN_ID];
			if( SR->PlateMotor.SetSpeedAcc( speed_entry.Speed[SR->DB->MachineParamsS.PlateDownSpeed], speed_entry.Acc[SR->DB->MachineParamsS.PlateDownSpeed], speed_entry.Dec[SR->DB->MachineParamsS.PlateDownSpeed] ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			if( SMPrinting( PRINTING_STATE_CHOOSE ) == SR_ERROR )
							return SR_ERROR;
			break;


		//----------------------------------------------------------------------------------
		case PRINTING_STATE_CHOOSE:

			// If printing verify is enabled...
			if( SR->DB->WorkingModesS.VerifyON )
			{
				//questo ounter verifica ogni x schede
				verifyCounter--;

				if( !verifyCounter )
				{
					verifyCounter = SR->verifyEvery;
					currentVerifyPoint = 1;

					if( SR->DB->WorkingModesS.InspectionType == INSPECTION_SPI )
					{
						ISite_CreateArray();

						if( ISite_SelectFirst() )
						{

							panel->UpdateSiteData( -1 );// clean results
							// Move the board to reaches the camera focus
							if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
							{
								smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
								return SR_ERROR;
							}
							//spiCheck->Initialize();
							AutoSPIcheck->Initialize();
							if( SMPrinting( PRINTING_STATE_INSPECTION_MOVE ) == SR_ERROR )
								return SR_ERROR;


						}
						else{
							if( SMPrinting( PRINTING_STATE_CLEANING_CHECK ) == SR_ERROR )
								return SR_ERROR;
						}
					}else if(SR->DB->WorkingModesS.InspectionType == INSPECTION_OPERATOR ){
						if(SMPrinting( PRINTING_STATE_VERIFY ) == SR_ERROR)
						return SR_ERROR;
						break;
					}
				}else{
					if( SMPrinting( PRINTING_STATE_CLEANING_CHECK ) == SR_ERROR )
						return SR_ERROR;
				}
			}else{
				if( SMPrinting( PRINTING_STATE_CLEANING_CHECK ) == SR_ERROR )
				return SR_ERROR;
			}
			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_SEARCH:
			SR->DB->SetFiducialParams( currentFiducial );
			mainVideo->UpdateControl();

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
				
				// Wait for axis to be completly stables
				myMilliSleep( CAMAXIS_DELAY );
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
			antiReflects(currentFiducial);
			// Enable camera
			retVal = IsFiducialOnPCB( currentFiducial ) ? SR->SetCamera( CAMERA_DOWN ) : SR->SetCamera( CAMERA_UP );
			if( retVal == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			// Wait to avoid flickering and get frames
			myMilliSleep( 2*FLICKERING_DELAY );

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
				expectedX = CAM_W / 2;
				expectedY = CAM_H / 2;
				if( !SR->DB->WorkingModesS.FiducialOnFrame )
				{
					expectedX += ( SR->DB->FiducialParamsS[currentFiducial].DeltaX / SR->DB->MachineParamsS.DnXPixMm );
					expectedY -= ( SR->DB->FiducialParamsS[currentFiducial].DeltaY / SR->DB->MachineParamsS.DnYPixMm );
				}

				// Call function to get the center of the fiducial
				if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_CIRCLE )
				{
					if( camera->FindCircle2( expectedX, expectedY, centerX, centerY, circleR ) == SR_OK )
					{
						smartLogger->Write( wxString::Format( MSG_FIDFOUND_CIRCLE, centerX, centerY, circleR ) );
						fiducialAutoFounded = true;
						if( SMPrinting( PRINTING_STATE_FOUND ) == SR_ERROR )
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
						if( SMPrinting( PRINTING_STATE_FOUND ) == SR_ERROR )
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
						fiducialAutoFounded = true;
						if( SMPrinting( PRINTING_STATE_FOUND ) == SR_ERROR )
							return SR_ERROR;
						break;
					}
				}

				// Fiducial not found
				smartLogger->Write( MSG_FIDNOTFOUND, MSG_ERROR );

				if( SR->SetAlarmLight( ALARMLIGHT_RED ) == SR_ERROR )
				{
					smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
					return SR_ERROR;
				}

				// Notify manual fiducial search
				wxMessageBox( MSG_FIDUCIALMANUAL, MACHINE_NAME, wxOK | wxICON_WARNING, parent );
			}

			// Manual fiducial search
			smartLogger->Write( MSG_FIDMANUALTEACH );
			camera->SetMainShape();
			camera->SetMainMode( MAIN_MOUSE_CUR_MANUAL );
			antiReflects(currentFiducial);
			// Enable camera
			retVal = IsFiducialOnPCB( currentFiducial ) ? SR->SetCamera( CAMERA_DOWN ) : SR->SetCamera( CAMERA_UP );
			if( retVal == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			datasette->StopEnable( true );
			datasette->PrevEnable( true );
			// Enable mouse click
			isMainVideoClickEnable = true;
			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_FOUND_WAIT:
			// sets controls state
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			datasette->PrevEnable( true );
			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_FOUND:
			antiReflects(currentFiducial);
			if( SR->SetAlarmLight( ALARMLIGHT_GREEN ) == SR_ERROR )
			{
				smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
				return SR_ERROR;
			}

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

			if( currentFiducial == FIDUCIAL_ROT1 )
				SR->GetOffset( camPos.X, camPos.Y, offsetR1X, offsetR1Y );
			else if( currentFiducial == FIDUCIAL_ROT2 )
				SR->GetOffset( camPos.X, camPos.Y, offsetR2X, offsetR2Y );

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
				if( SMPrinting( PRINTING_STATE_NEXT ) == SR_ERROR )
					return SR_ERROR;
			}
			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_NEXT:
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
				if( SMPrinting( PRINTING_STATE_TRA ) == SR_ERROR )
					return SR_ERROR;
				//200618
				if( SMPrinting( PRINTING_STATE_TRA_CHECK ) == SR_ERROR )
									return SR_ERROR;

				if( SMPrinting( PRINTING_STATE_PRINT1 ) == SR_ERROR )
					return SR_ERROR;
			}
			else
			{
				if( currentFiducial == FIDUCIAL_TRA )
				{
					// apply ROT correction
					if( SMPrinting( PRINTING_STATE_ROT ) == SR_ERROR )
						return SR_ERROR;

					//TODO mettiamo un workingmodes?
					if(true){
						// check ROT correction
						if( SMPrinting( PRINTING_STATE_ROT_CHECK ) == SR_ERROR )
							return SR_ERROR;
					}
				}



				if( SMPrinting( PRINTING_STATE_SEARCH ) == SR_ERROR )
					return SR_ERROR;
			}
			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_ROT:
			if( !SR->DB->WorkingModesS.FiducialOnFrame )
			{
				fidPosition[FIDUCIAL_ROT1_FRAME].X = SR->DB->FiducialParamsS[FIDUCIAL_ROT1].DeltaX + SR->DB->FiducialParamsS[FIDUCIAL_ROT1].X;
				fidPosition[FIDUCIAL_ROT1_FRAME].Y = SR->DB->FiducialParamsS[FIDUCIAL_ROT1].DeltaY + SR->DB->FiducialParamsS[FIDUCIAL_ROT1].Y;
				fidPosition[FIDUCIAL_ROT2_FRAME].X = SR->DB->FiducialParamsS[FIDUCIAL_ROT2].DeltaX + SR->DB->FiducialParamsS[FIDUCIAL_ROT2].X;
				fidPosition[FIDUCIAL_ROT2_FRAME].Y = SR->DB->FiducialParamsS[FIDUCIAL_ROT2].DeltaY + SR->DB->FiducialParamsS[FIDUCIAL_ROT2].Y;

				// Calc frame rotation
				if( fidPosition[FIDUCIAL_ROT2_FRAME].Y - fidPosition[FIDUCIAL_ROT1_FRAME].Y == 0 && fidPosition[FIDUCIAL_ROT2_FRAME].X - fidPosition[FIDUCIAL_ROT1_FRAME].X == 0 )
					frameRot = 0;
				else
					frameRot = atan2( fidPosition[FIDUCIAL_ROT2_FRAME].Y - fidPosition[FIDUCIAL_ROT1_FRAME].Y, fidPosition[FIDUCIAL_ROT2_FRAME].X - fidPosition[FIDUCIAL_ROT1_FRAME].X );
			}
			else
			{
				// Calc frame rotation
				if( (fidPosition[FIDUCIAL_ROT2_FRAME].Y + offsetR2Y) - (fidPosition[FIDUCIAL_ROT1_FRAME].Y + offsetR1Y) == 0 && (fidPosition[FIDUCIAL_ROT2_FRAME].X + offsetR2X) - (fidPosition[FIDUCIAL_ROT1_FRAME].X + offsetR1X) == 0 )
					frameRot = 0;
				else
					frameRot = atan2( (fidPosition[FIDUCIAL_ROT2_FRAME].Y + offsetR2Y) - (fidPosition[FIDUCIAL_ROT1_FRAME].Y + offsetR1Y), (fidPosition[FIDUCIAL_ROT2_FRAME].X + offsetR2X) - (fidPosition[FIDUCIAL_ROT1_FRAME].X + offsetR1X) );
			}

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
			{
				smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			smartLogger->Write( wxString::Format( MSG_ROTDONE, boardRot ), MSG_SUCCESS );
			break;



		//----------------------------------------------------------------------------------
		case PRINTING_STATE_ROT_CHECK:
			if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}
			//TODO
			if( SR->SetCamera( CAMERA_DOWN ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}
			if(SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX + SR->DB->FiducialParamsS[FIDUCIAL_ROT1].X, SR->DB->ProductionDataS.PCBPosY + SR->DB->FiducialParamsS[FIDUCIAL_ROT1].Y, ABS_MOVE )){
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				return SR_ERROR;
			}
			myMilliSleep( 2*FLICKERING_DELAY );
			camera->StartCapture();
			camera->GetFrames( MAX_FRAMES_FIDUCIAL );
			camera->StopCapture();

			SR->GetCameraPosition( camPos.X, camPos.Y );

			double currentX1, currentY1;
			if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_CIRCLE )
			{
				expectedX = CAM_W / 2;
				expectedY = CAM_H / 2;
				if( camera->FindCircle2( expectedX, expectedY, centerX, centerY, circleR ) == SR_OK )
				{
					smartLogger->Write( wxString::Format( MSG_FIDFOUND_CIRCLE, centerX, centerY, circleR ) );
					currentX1 = camPos.X + (centerX - CAM_W / 2) * SR->DB->MachineParamsS.DnXPixMm - SR->DB->ProductionDataS.PCBPosX;
					currentY1 = camPos.Y - (centerY - CAM_H / 2) * SR->DB->MachineParamsS.DnYPixMm - SR->DB->ProductionDataS.PCBPosY;
				}else{
					smartLogger->Write( "Non ho trovato il fiduciale di rotazione 1" );
					break;
				}
			}


			if(SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX + SR->DB->FiducialParamsS[FIDUCIAL_ROT2].X, SR->DB->ProductionDataS.PCBPosY + SR->DB->FiducialParamsS[FIDUCIAL_ROT2].Y, ABS_MOVE )){
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				return SR_ERROR;
			}
			myMilliSleep( 2*FLICKERING_DELAY );
			camera->StartCapture();
			camera->GetFrames( MAX_FRAMES_FIDUCIAL );
			camera->StopCapture();

			SR->GetCameraPosition( camPos.X, camPos.Y );

			double currentX2, currentY2;
			if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_CIRCLE )
			{
				expectedX = CAM_W / 2;
				expectedY = CAM_H / 2;
				if( camera->FindCircle2( expectedX, expectedY, centerX, centerY, circleR ) == SR_OK )
				{
					smartLogger->Write( wxString::Format( MSG_FIDFOUND_CIRCLE, centerX, centerY, circleR ) );
					currentX2 = camPos.X + (centerX - CAM_W / 2) * SR->DB->MachineParamsS.DnXPixMm - SR->DB->ProductionDataS.PCBPosX;
					currentY2 = camPos.Y - (centerY - CAM_H / 2) * SR->DB->MachineParamsS.DnYPixMm - SR->DB->ProductionDataS.PCBPosY;
				}else{
					smartLogger->Write( "Non ho trovato il fiduciale di rotazione 2" );
					break;
				}
			}
			if(true){
				double boardRotation = atan2( currentY2 - currentY1, currentX2 - currentX1 );
				//boardRot
				//frameRot
  			    smartLogger->Write( wxString::Format( MSG_ROTCHECKDETECTED, (frameRot -  boardRotation * 180 / PI) ), MSG_SUCCESS );
				//smartLogger->Write( wxString::Format( "Angolo telaio: %3.3f Check rotazione: %3.3f", frameRot,  boardRotation * 180 / PI) );
			}


			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_TRA:
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

			// SR->GetSqueegeesCycle() if true, squegees are in the operator side!
			if( ( !SR->DB->WorkingModesS.DoubleSqueegees & SR->GetSqueegeesCycle() ) || (SR->DB->WorkingModesS.DoubleSqueegees & !SR->GetSqueegeesCycle() ) ){
				cout<<"metto anche l'offset"<<endl;
				boardTra.Y += SR->DB->ProductionDataS.DeltaYFrontRear;
			}else{
				cout<<" non metto l'offset"<<endl;
			}

			if( SR->MoveXYTable( boardTra.X, boardTra.Y, SR->GetLimitsState() ) == SR_ERROR )
			{
				smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
				return SR_ERROR;
			}
			// Move camera out
			/*if( SR->MoveCameraAndWait( (SR->DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit - SR->DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit)/2, SR->DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				return SR_ERROR;
			}*/
			if( SR->WaitTable() == SR_ERROR )
			{
				smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			smartLogger->Write( wxString::Format( MSG_TRASLDONE, boardTra.X, boardTra.Y ), MSG_SUCCESS );
			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_TRA_CHECK:
			if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
			{
			smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
			return SR_ERROR;
			}
			if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}
			if( SR->SetCamera( CAMERA_DOWN ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}
			myMilliSleep( 250 );

			camera->SetMainMode( MAIN_NO_CUR );
			camera->StartCapture();
			camera->GetFrames( MAX_FRAMES_FIDUCIAL );
			camera->StopCapture();

			if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			//foto acquisita
			fiducialAutoFounded = false;
			if( SR->DB->WorkingModesS.FiducialSearch == FIDUCIAL_AUTO )
			{
				expectedX = CAM_W / 2;
				expectedY = CAM_H / 2;
				// Call function to get the center of the fiducial
				if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_CIRCLE )
				{
					if( camera->FindCircleAccurate( expectedX, expectedY, centerX, centerY, circleR ) == SR_OK )
					{
						double currentX, currentY;
						currentX = camPos.X + (centerX - CAM_W / 2) * SR->DB->MachineParamsS.DnXPixMm - SR->DB->ProductionDataS.PCBPosX;
						currentY = camPos.Y - (centerY - CAM_H / 2) * SR->DB->MachineParamsS.DnYPixMm - SR->DB->ProductionDataS.PCBPosY;
						//SR->GetOffset( camPos.X, camPos.Y, offsetX, offsetY );

						double residualX = fidPosition[FIDUCIAL_TRA_FRAME].X - currentX + offsetX;
						double residualY = fidPosition[FIDUCIAL_TRA_FRAME].Y - currentY + offsetY;

						residualX += SR->DB->ProductionDataS.CorrectionX;
						residualY += SR->DB->ProductionDataS.CorrectionY;
						if( ( !SR->DB->WorkingModesS.DoubleSqueegees & SR->GetSqueegeesCycle() ) || (SR->DB->WorkingModesS.DoubleSqueegees & !SR->GetSqueegeesCycle() ) ){
							residualY += SR->DB->ProductionDataS.DeltaYFrontRear;
						}
						smartLogger->Write( wxString::Format( MSG_TRASLATION_CHECK, residualX, residualY ) );
						fiducialAutoFounded = true;
						//21012019
						if( SR->MoveXYTable( residualX, residualY, SR->GetLimitsState() ) == SR_ERROR )
						{
							smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
							return SR_ERROR;
						}
					}
				}
				else if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_RECTANGLE )
				{
					if( camera->FindRectangle( expectedX, expectedY, centerX, centerY, rectangleX, rectangleY ) == SR_OK )
					{
						double currentX, currentY;
						currentX = camPos.X + (centerX - CAM_W / 2) * SR->DB->MachineParamsS.DnXPixMm - SR->DB->ProductionDataS.PCBPosX;
						currentY = camPos.Y - (centerY - CAM_H / 2) * SR->DB->MachineParamsS.DnYPixMm - SR->DB->ProductionDataS.PCBPosY;
						SR->GetOffset( camPos.X, camPos.Y, offsetX, offsetY );

						double residualX = currentX - fidPosition[FIDUCIAL_TRA_FRAME].X+ offsetX;
						double residualY = currentY - fidPosition[FIDUCIAL_TRA_FRAME].Y+ offsetY;
						residualX += SR->DB->ProductionDataS.CorrectionX;
						residualY += SR->DB->ProductionDataS.CorrectionY;
						if( ( !SR->DB->WorkingModesS.DoubleSqueegees & SR->GetSqueegeesCycle() ) || (SR->DB->WorkingModesS.DoubleSqueegees & !SR->GetSqueegeesCycle() ) ){
							residualY += SR->DB->ProductionDataS.DeltaYFrontRear;
						}
						smartLogger->Write( wxString::Format( MSG_TRASLATION_CHECK, residualX, residualY ) );
						fiducialAutoFounded = true;
					}
				}
				else if( SR->DB->FiducialParamsS[currentFiducial].SearchMode == SEARCH_MODE_TEMPLATE )
				{
					centerX = CAM_W / 2;
					centerY = CAM_H / 2;

					if( camera->FindTemplate( wxString::Format( "%s_%d.jpeg", SR->DB->ProductionDataS.ProductionName.ToAscii(), currentFiducial ), centerX, centerY, templateScore ) == SR_OK )
					{
						double currentX, currentY;
						currentX = camPos.X + (centerX - CAM_W / 2) * SR->DB->MachineParamsS.DnXPixMm - SR->DB->ProductionDataS.PCBPosX;
						currentY = camPos.Y - (centerY - CAM_H / 2) * SR->DB->MachineParamsS.DnYPixMm - SR->DB->ProductionDataS.PCBPosY;
						SR->GetOffset( camPos.X, camPos.Y, offsetX, offsetY );

						double residualX = currentX - fidPosition[FIDUCIAL_TRA_FRAME].X+ offsetX;
						double residualY = currentY - fidPosition[FIDUCIAL_TRA_FRAME].Y+ offsetY;
						residualX += SR->DB->ProductionDataS.CorrectionX;
						residualY += SR->DB->ProductionDataS.CorrectionY;
						if( ( !SR->DB->WorkingModesS.DoubleSqueegees & SR->GetSqueegeesCycle() ) || (SR->DB->WorkingModesS.DoubleSqueegees & !SR->GetSqueegeesCycle() ) ){
							residualY += SR->DB->ProductionDataS.DeltaYFrontRear;
						}
						smartLogger->Write( wxString::Format( MSG_TRASLATION_CHECK, residualX, residualY ) );
						fiducialAutoFounded = true;
					}
				}

				/*// Fiducial not found
				if(!fiducialAutoFounded){
					smartLogger->Write( MSG_FIDNOTFOUND_CHECK, MSG_ERROR );

					if( SR->SetAlarmLight( ALARMLIGHT_RED ) == SR_ERROR )
					{
						smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
						return SR_ERROR;
					}
				}*/
			}

			/* Manual fiducial search (NON contemplato in fase di check)
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

			datasette->StopEnable( true );
			datasette->PrevEnable( true );
			// Enable mouse click
			isMainVideoClickEnable = true;*/


			// Move camera out
			if( SR->MoveCameraAndWait( (SR->DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit - SR->DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit)/2, SR->DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				return SR_ERROR;
			}
			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_VERIFY:
			smartLogger->Write( wxString::Format(MSG_VERIFYPOINT, currentVerifyPoint) );

			if( currentVerifyPoint == 1 )
			{
				// Move the board to reaches the camera focus
				if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
				{
					smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
					return SR_ERROR;
				}
			}

			// check if currentVerifyPoint has been teached...
			if( verifyAutoFlag == VERIFY_AUTO && SR->DB->VerifyPointsS[currentVerifyPoint-1].X == 0.0 && SR->DB->VerifyPointsS[currentVerifyPoint-1].Y == 0.0 )
			{
				// ...some points need manual teach (just this time)
				wxMessageBox( MSG_PRINTINGNOPOINT, MACHINE_NAME, wxOK | wxICON_INFORMATION, parent );
				verifyAutoFlag = VERIFY_MANUAL;
			}

			// Move camera...
			if( SR->DB->VerifyPointsS[currentVerifyPoint-1].X != 0.0 || SR->DB->VerifyPointsS[currentVerifyPoint-1].Y != 0.0 )
			{
				// to verify point
				retVal = SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX + SR->DB->VerifyPointsS[currentVerifyPoint-1].X, SR->DB->ProductionDataS.PCBPosY + SR->DB->VerifyPointsS[currentVerifyPoint-1].Y, ABS_MOVE );
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

			// if auto mode wait and then go to next points...
			if( verifyAutoFlag == VERIFY_AUTO )
			{
				/*
				// wait
				bool wait_flag = true;
				wxDateTime start = wxDateTime::UNow();
				while( wait_flag )
				{
					myMilliSleep( 50 );
					wxTimeSpan time_diff = wxDateTime::UNow() - start;
					wait_flag = time_diff.GetMilliseconds() > (SR->DB->WorkingModesS.PrintingVerifyTime * 1000) ? false : true;
				}

				if( SMPrinting( PRINTING_STATE_VERIFY_NEXT ) == SR_ERROR )
					return SR_ERROR;
				*/

				SR->SetCounter( SR->DB->WorkingModesS.PrintingVerifyTime * 2 );

				if( SMPrinting( PRINTING_STATE_VERIFY_CAMERA ) == SR_ERROR )
					return SR_ERROR;

			}
			else
			{
				controlPanel->SetState( PANEL_VERIFY_MOVE );
				datasette->StopEnable( true );
				datasette->NextEnable( true );
				datasette->PrevEnable( currentVerifyPoint != 1 );
				// enable mouse click
				isAuxVideoClickEnable = true;
			}
			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_VERIFY_CAMERA:

			//::wxYield();
			wxMilliSleep(10);
			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_VERIFY_NEXT:
			SR->GetCameraPosition( SR->DB->VerifyPointsS[currentVerifyPoint-1].X, SR->DB->VerifyPointsS[currentVerifyPoint-1].Y );
			
			// check points
			SR->DB->VerifyPointsS[currentVerifyPoint-1].X = MID( SR->DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit, SR->DB->VerifyPointsS[currentVerifyPoint-1].X, SR->DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit );
			SR->DB->VerifyPointsS[currentVerifyPoint-1].Y = MID( SR->DB->LimitsS[MOTOR_CAMERAY_ID].MinLimit, SR->DB->VerifyPointsS[currentVerifyPoint-1].Y, SR->DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit );
			
			// refers position to the PCB origin
			SR->DB->VerifyPointsS[currentVerifyPoint-1].X -= SR->DB->ProductionDataS.PCBPosX;
			SR->DB->VerifyPointsS[currentVerifyPoint-1].Y -= SR->DB->ProductionDataS.PCBPosY;

			if( currentVerifyPoint < NUM_VERIFY_POINTS && currentVerifyPoint <= SR->DB->WorkingModesS.PrintingVerify  ) // <= perche la lista parte da 0
			{
				currentVerifyPoint++;
				if( SMPrinting( PRINTING_STATE_VERIFY ) == SR_ERROR )
					return SR_ERROR;
			}
			else
			{
				// Save verify points
				SR->DB->SaveVerifyPoints();

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

				if( SMPrinting( PRINTING_STATE_CLEANING_CHECK ) == SR_ERROR )
					return SR_ERROR;
			}
			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_VERIFY_PREV:
			SR->GetCameraPosition( SR->DB->VerifyPointsS[currentVerifyPoint-1].X, SR->DB->VerifyPointsS[currentVerifyPoint-1].Y );
			
			// check points
			SR->DB->VerifyPointsS[currentVerifyPoint-1].X = MID( SR->DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit, SR->DB->VerifyPointsS[currentVerifyPoint-1].X, SR->DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit );
			SR->DB->VerifyPointsS[currentVerifyPoint-1].Y = MID( SR->DB->LimitsS[MOTOR_CAMERAY_ID].MinLimit, SR->DB->VerifyPointsS[currentVerifyPoint-1].Y, SR->DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit );
			
			// refers position to the PCB origin
			SR->DB->VerifyPointsS[currentVerifyPoint-1].X -= SR->DB->ProductionDataS.PCBPosX;
			SR->DB->VerifyPointsS[currentVerifyPoint-1].Y -= SR->DB->ProductionDataS.PCBPosY;

			currentVerifyPoint--;
			if( SMPrinting( PRINTING_STATE_VERIFY ) == SR_ERROR )
				return SR_ERROR;
			break;

		case PRINTING_STATE_INSPECTION_MOVE:

			// qui comincia la fase di ispezione SPI
			panel->DrawControl( PP_SPI );
			panel->Layout();

			smartLogger->Write( wxString::Format(MSG_INSPECTINGSITE, ISite_GetSelected()+1, ISite_Count() ) );

			camera->SetMainMode( MAIN_BLANK );
			camera->SetAuxMode( AUX_BLANK );

			//controlPanel->Update();

			// sets site params
			SR->DB->SetFiducialParams( FIDUCIAL_VISION_TEST );


			SR->DB->pCurrentFiducial->CameraBrightness = SR->DB->pAUTOInspectionCurrentSiteStruct->CameraBrightness;
			SR->DB->pCurrentFiducial->CameraContrast = SR->DB->pAUTOInspectionCurrentSiteStruct->CameraContrast;
			mainVideo->UpdateControl();

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

			// Move camera to inspection site
			//if( SR->MoveCameraAndWait( (SR->DB->ProductionDataS.PCBPosX +fidPosition[FIDUCIAL_TRA].X + boardTra.X)  + SR->DB->pAUTOInspectionCurrentSiteStruct->X , (SR->DB->ProductionDataS.PCBPosY +fidPosition[FIDUCIAL_TRA].Y + boardTra.Y) + SR->DB->pAUTOInspectionCurrentSiteStruct->Y, ABS_MOVE ) )
				//return SR_ERROR;


			// setup inspection points during camera movement
			//controllo se le immagini esistono
			retVal = AutoSPIcheck->CheckImages( SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite );



			if( !retVal )
			{
				//TEMP - gestire errore
				smartLogger->Write( wxString::Format("Error on inspection points %d !", SR->DB->SiteGetSelected()+1), MSG_ERROR );
				wxMessageBox( wxString::Format("Error on inspection points %d !", SR->DB->SiteGetSelected()+1), MACHINE_NAME, wxOK | wxICON_ERROR, parent );

				// Wait camera
				if( SR->WaitCamera() == SR_ERROR )
					return SR_ERROR;

				if( SMPrinting( PRINTING_STATE_INSPECTION_NEXT ) == SR_ERROR )
					return SR_ERROR;
				break;
			}

			// Wait camera
			if( SR->WaitCamera() == SR_ERROR )
				return SR_ERROR;

			// Wait to avoid flickering and get frames
			/*
			MACHINE_CONFIG( USE_EVER )
				myMilliSleep( FLICKERING_DELAY_PROTOTYPE );
			MACHINE_CONFIG_ELSE
				myMilliSleep( FLICKERING_DELAY );
			MACHINE_CONFIG_END
			/**/
			//SR->SetCounter( 2 );

			if( SMPrinting( PRINTING_STATE_INSPECTION_WAIT ) == SR_ERROR )
				return SR_ERROR;
			break;

		case PRINTING_STATE_INSPECTION_WAIT:
					//aggiunto
			myMilliSleep( 2*FLICKERING_DELAY );
			if( SMPrinting( PRINTING_STATE_INSPECTION_CHECK ) == SR_ERROR )
				return SR_ERROR;

			break;

		case PRINTING_STATE_INSPECTION_CHECK:

			camera->SetMainMode( MAIN_NO_CUR );
			camera->SetAuxMode( AUX_CAMPOSITION );

			if (SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.PCB.size()==0) //if there are no associations, find it
				SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots = AutoSPIproc->MatchRegions(false);


			// Enable camera led


			/////////////////////////////////////////
			//this part aquires several pictures
			///////////////////////////////////////////

			int four_images;
			four_images=1; //WARNING! 4 PICTURES FOR b/w camera

			if(four_images)
			{
				float shift=2;
				if(SR->SetCameraLight( LED_HIGH )== SR_ERROR){
					return SR_ERROR;
				}

				//grab local coords
				float xCords =  SR->DB->pAUTOInspectionCurrentSiteStruct->X;
				float yCords =  SR->DB->pAUTOInspectionCurrentSiteStruct->Y;

				//correct rotation offset
				float DeltaAngle = -SR->DB->pAUTOInspectionCurrentSiteStruct->Orientation + frameRot/180*PI;
				//cout<< "Delta angle: "<< DeltaAngle<<" frameRot: "<< frameRot<<endl;

				float xTmp = xCords;
				xCords = xCords *cos(DeltaAngle) - yCords*sin(DeltaAngle);
				yCords = xTmp * sin(DeltaAngle) + yCords*cos(DeltaAngle);

				//convert local coords to machine coords
				xCords +=  (fidPosition[FIDUCIAL_TRA].X + boardTra.X) + SR->DB->ProductionDataS.PCBPosX;
				yCords +=  (fidPosition[FIDUCIAL_TRA].Y + boardTra.Y) + SR->DB->ProductionDataS.PCBPosY;

				if( SR->MoveCameraAndWait( xCords+ shift, yCords, ABS_MOVE ) )
					return SR_ERROR;


				wxString fullpath;
				fullpath.Append( wxString::Format(FILE_PRODUCTION_FOLDER, SR->DB->ProductionDataS.ProductionName.ToAscii() ) );
				fullpath.append("x+2");
				fullpath.Append( wxString::Format( FILE_SITE, SR->DB->ProductionDataS.ProductionName.ToAscii(), SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite ));
				myMilliSleep( MULTIPLE_IMAGES_DELAY);

				camera->StartCapture(false);
				camera->GetColorFrames(1); //acquire n picures
				camera->StopCapture();
				cv::Mat Xplus = camera->GetWorkingColorFrame(0).clone();
				//cv::imwrite(fullpath.ToAscii(), Xplus );



				if( SR->MoveCameraAndWait(  xCords - shift, yCords, ABS_MOVE ) )
				//if( SR->MoveCamera( fidPosition[FIDUCIAL_TRA_FRAME].X +boardTra.X+ SR->DB->pAUTOInspectionCurrentSiteStruct->X - shift, fidPosition[FIDUCIAL_TRA_FRAME].Y +boardTra.Y+ SR->DB->pAUTOInspectionCurrentSiteStruct->Y, ABS_MOVE ) == SR_ERROR )
								return SR_ERROR;


				fullpath.clear();
				fullpath.Append( wxString::Format(FILE_PRODUCTION_FOLDER, SR->DB->ProductionDataS.ProductionName.ToAscii() ) );
				fullpath.append("x-2");
				fullpath.Append( wxString::Format( FILE_SITE, SR->DB->ProductionDataS.ProductionName.ToAscii(), SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite ));
				myMilliSleep( MULTIPLE_IMAGES_DELAY);

				camera->StartCapture(false);
				camera->GetColorFrames(1);
				camera->StopCapture();
				cv::Mat Xminus = camera->GetWorkingColorFrame(0).clone();
				//cv::imwrite(fullpath.ToAscii(), Xminus );

				if( SR->MoveCameraAndWait( xCords , yCords + shift, ABS_MOVE ) )
				//if( SR->MoveCamera( fidPosition[FIDUCIAL_TRA_FRAME].X +boardTra.X+ SR->DB->pAUTOInspectionCurrentSiteStruct->X , fidPosition[FIDUCIAL_TRA_FRAME].Y +boardTra.Y+ SR->DB->pAUTOInspectionCurrentSiteStruct->Y + shift, ABS_MOVE ) == SR_ERROR )
						return SR_ERROR;

				//if( SR->MoveCameraAndWait( SR->DB->ProductionDataS.PCBPosX + SR->DB->pAUTOInspectionCurrentSiteStruct->X , SR->DB->ProductionDataS.PCBPosY + SR->DB->pAUTOInspectionCurrentSiteStruct->Y + shift, ABS_MOVE ) == SR_ERROR )
					//return SR_ERROR;

				myMilliSleep( MULTIPLE_IMAGES_DELAY);
				fullpath.clear();
				fullpath.Append( wxString::Format(FILE_PRODUCTION_FOLDER, SR->DB->ProductionDataS.ProductionName.ToAscii() ) );
				fullpath.append("y+2");
				fullpath.Append( wxString::Format( FILE_SITE, SR->DB->ProductionDataS.ProductionName.ToAscii(), SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite ));

				camera->StartCapture(false);
				camera->GetColorFrames(1); //acquire n picures
				camera->StopCapture();
				cv:: Mat Yplus = camera->GetWorkingColorFrame(0).clone();
				//cv::imwrite(fullpath.ToAscii(), Yplus );

				if( SR->MoveCameraAndWait( xCords , yCords - shift, ABS_MOVE ) )
					return SR_ERROR;

				myMilliSleep( MULTIPLE_IMAGES_DELAY);
				fullpath.clear();
				fullpath.Append( wxString::Format(FILE_PRODUCTION_FOLDER, SR->DB->ProductionDataS.ProductionName.ToAscii() ) );
				fullpath.append("y-2");
				fullpath.Append( wxString::Format( FILE_SITE, SR->DB->ProductionDataS.ProductionName.ToAscii(), SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite ));

				camera->StartCapture(false);
				camera->GetColorFrames(1);
				camera->StopCapture();
				cv:: Mat Yminus = camera->GetWorkingColorFrame(0).clone();
				//cv::imwrite(fullpath.ToAscii(), Yminus );

				//AutoSPIcheck->Merge4Images(&Xplus, &Xminus, &Yplus, &Yminus, &Frame_to_Mat, shift );
				AutoSPIcheck->Merge4Images(&Xplus, &Xminus, &Yplus, &Yminus, &FrameHighExposure, shift );

				//GET THE IMAGE WITH LOW EXPOSURE
				if(SR->SetCameraLight( LED_LOW )== SR_ERROR){
					return SR_ERROR;
				}


				if( SR->MoveCameraAndWait( xCords, yCords, ABS_MOVE ) )
					return SR_ERROR;

				myMilliSleep( FLICKERING_DELAY );
				camera->StartCapture();
				camera->GetColorFrames(1);
				camera->StopCapture();
				Frame_to_Mat = camera->GetWorkingColorFrame(0).clone();

			}
			else {

				//grab local coords
				float xCords =  SR->DB->pAUTOInspectionCurrentSiteStruct->X;
				float yCords =  SR->DB->pAUTOInspectionCurrentSiteStruct->Y;

				//correct rotation offset
				float DeltaAngle = -SR->DB->pAUTOInspectionCurrentSiteStruct->Orientation + frameRot/180*PI;
				//cout<< "Delta angle: "<< DeltaAngle<<" frameRot: "<< frameRot<<endl;

				float xTmp = xCords;
				xCords = xCords *cos(DeltaAngle) - yCords*sin(DeltaAngle);
				yCords = xTmp * sin(DeltaAngle) + yCords*cos(DeltaAngle);

				//convert local coords to machine coords
				xCords +=  (fidPosition[FIDUCIAL_TRA].X + boardTra.X) + SR->DB->ProductionDataS.PCBPosX;
				yCords +=  (fidPosition[FIDUCIAL_TRA].Y + boardTra.Y) + SR->DB->ProductionDataS.PCBPosY;
				// boardTra is necessary!
				//xCords +=  (fidPosition[FIDUCIAL_TRA].X ) + SR->DB->ProductionDataS.PCBPosX;
				//yCords +=  (fidPosition[FIDUCIAL_TRA].Y ) + SR->DB->ProductionDataS.PCBPosY;

				if( SR->MoveCameraAndWait( xCords, yCords, ABS_MOVE ) )
					return SR_ERROR;

				myMilliSleep( MULTIPLE_IMAGES_DELAY);
				camera->StartCapture();
				camera->GetColorFrames(MAX_COLOR_FRAMES/2); //acquire n picures
				camera->StopCapture();
				Frame_to_Mat = camera->GetWorkingColorFrame(0).clone();

			}

			mainVideo->UpdateControl();

			center= PointF(expectedPos.X, expectedPos.Y);



			fullpath.clear();
			fullpath.Append( wxString::Format(FILE_PRODUCTION_FOLDER, SR->DB->ProductionDataS.ProductionName.ToAscii() ) );
			fullpath.Append( wxString::Format( FILE_SITE, SR->DB->ProductionDataS.ProductionName.ToAscii(), SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite ));

			AutoSPIcheck->Align(&Frame_to_Mat, fullpath, center.X, center.Y);
			//is it really necessary? yes it is! camera position may vary up to 5-6 px
			//center.X = 0;
			//center.Y = 0;

			//both pictures should be aligned now!
			smartLogger->Write( wxString::Format( MSG_FIDFOUND_TEMPLATE, center.X, center.Y ) );

			expectedPos.X=center.X;
			expectedPos.Y=center.Y;

			center.X = center.X * SR->DB->MachineParamsS.UpXPixMm;
			center.Y = center.Y * SR->DB->MachineParamsS.UpYPixMm;


			if( fabs( center.X ) > MAX_ALIGNMENT_ERROR || fabs( center.Y ) > MAX_ALIGNMENT_ERROR )
			{
				center.X = 0.f;
				center.Y = 0.f;

				expectedPos.X=0;
				expectedPos.Y=0;

				smartLogger->Write( MSG_SPI_REFIMG_POS_ERR, MSG_ERROR );
				wxMessageBox( MSG_SPI_REFIMG_POS_ERR, MACHINE_NAME, wxOK | wxICON_ERROR, parent );
			}

			// Disable camera
			if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
				 return SR_ERROR;
			}

			// continue to following state (internal event)
			if(SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannel!=-1 ||  SR->DB->pAUTOInspectionCurrentSiteStruct->PadThreshold !=-1){

				if(SMPrinting(PRINTING_STATE_INSPECTION)== SR_ERROR ){
					return SR_ERROR;
				}
				//currentState = PRINTING_STATE_INSPECTION;
			}
			else{
				if( SMPrinting(PRINTING_STATE_IDLE_PHASE1_DRAW)== SR_ERROR ){
					return SR_ERROR;
				}

			}
			break;


		//----------------------------------------------------------------------------------
		case PRINTING_STATE_IDLE_PHASE1_DRAW:
			currentState = PRINTING_STATE_IDLE_PHASE1;
			panel->DrawControl(PP_PHASE1);
			panel->Layout();

		//----------------------------------------------------------------------------------

		case PRINTING_STATE_IDLE_PHASE1:

			AutoSPIcheck->FindPaste(&Frame_to_Mat, &FrameHighExposure);
			camera->SetAuxMode(AUX_HISTOGRAM);
			camera->SetVideoMainImage(  wxImage( AutoSPIcheck->TemplateImg.cols, AutoSPIcheck->TemplateImg.rows, (unsigned char*)AutoSPIcheck->TemplateImg.data, true)   );
			panel->UpdateSPISliders();
			break;
		//------------------------------------------------------------------------------------------
		case PRINTING_STATE_IDLE_PHASE2_DRAW:

			currentState = PRINTING_STATE_IDLE_PHASE2;
			panel->DrawControl(PP_PHASE2);
			panel->Layout();
			camera->SetMainMode(MAIN_INSPECTION_ZOOM);

			if(panel->ColorPadCriteria->GetValue()){ //if the pads are chosen on colors
				if(SR->DB->pAUTOInspectionCurrentSiteStruct->CentralPadsColor == -1 ){ //if it is the first time
					if( !SR->DB->SiteIsFirst() ){	//assign the same of the prev site
						SR->DB->pAUTOInspectionCurrentSiteStruct--;
						int previous_center = SR->DB->pAUTOInspectionCurrentSiteStruct->CentralPadsColor;
						int previous_width = SR->DB->pAUTOInspectionCurrentSiteStruct->PadsColorWidth;
						int previous_channel = SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads;
						SR->DB->pAUTOInspectionCurrentSiteStruct++;
						SR->DB->pAUTOInspectionCurrentSiteStruct->CentralPadsColor = previous_center;
						SR->DB->pAUTOInspectionCurrentSiteStruct->PadsColorWidth = previous_width;
						SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads = previous_channel;
					}
					else{	//default values
						SR->DB->pAUTOInspectionCurrentSiteStruct->CentralPadsColor = PAD_COLOR_CENTER;
						SR->DB->pAUTOInspectionCurrentSiteStruct->PadsColorWidth = PAD_COLOR_WIDTH;
						SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads = BLUE_CHANNEL;
					}
					SR->DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE = -1;
					SR->DB->pAUTOInspectionCurrentSiteStruct->PasteHUEWidth = -1;
				}
			}
			else{ //pads are chosen on HUE
				if(SR->DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE ==-1 ){ //if it is the first time
					if( !SR->DB->SiteIsFirst() ){
						SR->DB->pAUTOInspectionCurrentSiteStruct--;
						int previous_center = SR->DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE;
						int previous_width = SR->DB->pAUTOInspectionCurrentSiteStruct->PasteHUEWidth;
						SR->DB->pAUTOInspectionCurrentSiteStruct++;
						SR->DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE = previous_center;
						SR->DB->pAUTOInspectionCurrentSiteStruct->PasteHUEWidth = previous_width;
					}
					else{
						SR->DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE = CENTRAL_HUE_GOLD;
						SR->DB->pAUTOInspectionCurrentSiteStruct->PasteHUEWidth = HUE_WIDTH_GOLD;
					}
					SR->DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads = -1;
				}
			}
			panel->UpdateSPISliders();

		//------------------------------------------------------------------------------------------

		case PRINTING_STATE_IDLE_PHASE2:
			isMainVideoClickEnable = true;
			AutoSPIcheck->FindUncoveredPads(&Frame_to_Mat);
			camera->SetAuxMode(AUX_PRINTING_MASK);
			camera->SetVideoMainImage(  wxImage( AutoSPIcheck->TemplateImg.cols, AutoSPIcheck->TemplateImg.rows, (unsigned char*)AutoSPIcheck->TemplateImg.data, true)   );
			camera->ResetZoom();
			//panel->UpdateSPISliders();
			break;
		//------------------------------------------------------------------------------------------
		case PRINTING_STATE_INSPECTION:
			panel->DrawControl( PP_SPI );
			panel->Layout();
			SR->DB->WriteSPIparams();
			camera->SetMainMode(MAIN_NO_CUR);
			SiteOK = AutoSPIcheck->Inspect(&Frame_to_Mat, &FrameHighExposure, PointI(expectedPos.X,expectedPos.Y), SR->suggestCorrections );

			panel->UpdateListSizer(1);
			panel->sitesCheckList->Disable();
			panel->UpdateSiteData( SR->DB->SiteGetSelected() );

			camera->SetVideoMainImage(  wxImage( AutoSPIcheck->TemplateImg.cols, AutoSPIcheck->TemplateImg.rows, (unsigned char*)AutoSPIcheck->TemplateImg.data, true)   );

			// sets controls state
			isMainVideoClickEnable = false;
			//
			datasette->StopEnable( true );
			datasette->NextEnable( true );
			datasette->PrevEnable(false);
			//datasette->PrevEnable( !ISite_IsFirst() || SR->DB->SiteAreaGetSelected() > 0 );
			if( verifyAutoFlag == VERIFY_AUTO )
			{
				if(SR->DB->WorkingModesS.SPIStopsWhenFaulty){
					if(!SiteOK)
					{
						if( SR->SetAlarmLight( ALARMLIGHT_RED ) == SR_ERROR )
						{
							smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
							return SR_ERROR;
						}

						break;
					}
				}


				if( SMPrinting( PRINTING_STATE_INSPECTION_NEXT ) == SR_ERROR )
					return SR_ERROR;

			} // else si aspetta il next


			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_INSPECTION_NEXT:
			camera->SetMainMode( MAIN_BLANK );
			camera->SetAuxMode(  AUX_BLANK );
			panel->UpdateListSizer(-1);
			SR->DB->SaveResults(); // call this BEFORE select a new site

			if(SR->suggestCorrections){
				wxString xy= wxString::Format("Correction X: %f",SR->DB->InspectionSiteSuggestedCorrection[SR->DB->SiteGetSelected()].x);
				xy.Append("   ");
				xy.Append( wxString::Format("Y: %f ",SR->DB->InspectionSiteSuggestedCorrection[SR->DB->SiteGetSelected()].y));

				wxMessageBox( xy, "wxSQLite_AREA_PCB", wxOK | wxICON_INFORMATION, parent );
			}

			// passa al sito successivo
			if( ISite_SelectNext() )
			{
				//TEMP - provvisorio
				/*
				if( SMPrinting( PRINTING_STATE_INSPECTION_MOVE ) == SR_ERROR )
					return SR_ERROR;
				*/
				if( SMPrinting( PRINTING_STATE_INSPECTION_MOVE ) == SR_ERROR )
					return SR_ERROR;
				//TEMP - provvisorio
			}
			else
			{
				if( SMPrinting( PRINTING_STATE_CLEANING_CHECK ) == SR_ERROR )
					return SR_ERROR;
			}
			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_INSPECTION_PREV:

			// passa al sito precedente
			ISite_SelectPrev();

			if( SMPrinting( PRINTING_STATE_INSPECTION_MOVE ) == SR_ERROR )
				return SR_ERROR;
			break;
		//fine parte della 3100


		//----------------------------------------------------------------------------------
		case PRINTING_STATE_CLEANING_CHECK:


			if (SR->suggestCorrections && (SR->DB->SiteCount()>1))
			{
				AutoSPIcheck->EstimateCorrection();
				wxMessageBox( wxString::Format(MSG_ESTIMATED_CORR, SR->DB->estimated_rotation), MACHINE_NAME, wxYES_NO | wxICON_QUESTION, parent ) ;
			}

			// Plate in zero position
			if( SR->PlateMotor.MoveAndWait( 0, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}
			// Reset plate to normal movement params
			if( SR->PlateMotor.SetSpeedAcc() == SR_ERROR )
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
			// Move camera to zero position
			if( SR->MoveCameraAndWait( (SR->DB->LimitsS[MOTOR_CAMERAX_ID].MinLimit - SR->DB->LimitsS[MOTOR_CAMERAX_ID].MaxLimit)/2, SR->DB->LimitsS[MOTOR_CAMERAY_ID].MaxLimit, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
				return SR_ERROR;
			}

			if( SR->WaitTable() == SR_ERROR )
			{
				smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Move the board outside the machine
			if( SR->UnloadBoard() == SR_ERROR )
			{
				smartLogger->Write( MSG_LOADERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// draw empty workplace
			camera->DrawWorkplace();

			if( cleanCounter > 0 )
			{
				//smartLogger->Write( wxString::Format( "cleanCounter: %d", cleanCounter ) );

				cleanCounter--;

				if( !cleanCounter )
				{
					cleanCounter = SR->cleanEvery;
					if( SR->DB->MachineParamsS.CleaningInstalled && SR->DB->WorkingModesS.CleaningEn )
					{
						if( SMPrinting( PRINTING_STATE_CLEANING ) == SR_ERROR )
							return SR_ERROR;
					}else{
						if( SR->SetAlarmLight( ALARMLIGHT_RED ) == SR_ERROR )
						{
							smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
							return SR_ERROR;
						}
						wxMessageBox( MSG_MANUALCLEAN, MACHINE_NAME, wxOK | wxICON_INFORMATION, parent );
						if( SR->SetAlarmLight( ALARMLIGHT_GREEN ) == SR_ERROR )
						{
							smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
							return SR_ERROR;
						}
						if( SMPrinting( PRINTING_STATE_FINAL ) == SR_ERROR )
							return SR_ERROR;
					}

				}
				else
				{
					if( SMPrinting( PRINTING_STATE_FINAL ) == SR_ERROR )
						return SR_ERROR;
				}
			}
			else
			{
				if( SMPrinting( PRINTING_STATE_FINAL ) == SR_ERROR )
					return SR_ERROR;
			}

			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_CLEANING:

			smartLogger->Write( MSG_CLEANING );

			if( SR->CleaningCycle() == SR_ERROR )
			{
				smartLogger->Write( MSG_CLEANINGERROR, MSG_ERROR );

				// Reset original camera speed
				SR->DB->MachineParamsS.CameraSpeed = SR->cameraSavedSpeed;
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

				return SR_ERROR;
			}

			if( SMPrinting( PRINTING_STATE_FINAL ) == SR_ERROR )
				return SR_ERROR;
			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_FINAL:

			// Se loader abilitato, decremento il numero di schede e, se necessario, faccio avanzare
			// il loader per preparare la prossima scheda
			if( SR->DB->MachineParamsS.LoaderInstalled && SR->DB->WorkingModesS.LoaderEn )
			{
				SR->SetLastPrintedRackPos( SR->GetRackPos() );

				if( SR->DB->ProductionDataS.LoaderBoardNumber > 0 )
				{
					SR->DB->ProductionDataS.LoaderBoardNumber--;

					panel->UpdatePrintingPanel();

					// Se il numero di board e' ancora maggiore di 0, alzo il loader e faccio ripartire il ciclo di serigrafia
					if( SR->DB->ProductionDataS.LoaderBoardNumber > 0 )
					{
						smartLogger->Write( wxString::Format(MSG_PRINTINGLEFT, SR->DB->ProductionDataS.LoaderBoardNumber), MSG_SUCCESS );

						if( SR->LoaderMove( SR->GetRackPos()+1 ) == SR_ERROR )
						{
							smartLogger->Write( MSG_LOADERERROR, MSG_ERROR );
							return SR_ERROR;
						}

						panel->UpdatePrintingPanel();

						// Mi assicuro di avere abilitato il check del cover ( in caso sia stato aperto e scelto di proseguire)
						SR->CheckCover( true );

						if( !SR->GetLoaderStop() )
						{
							if( SMPrinting( PRINTING_STATE_INIT2 ) == SR_ERROR )
								return SR_ERROR;

							break;
						}
					}
				}
			}

			// Se e' stato premuto il pulsante di pausa nel datasette o se in modalita' senza loader
			// o se terminate le schede nel loader termino il ciclo di serigrafia
			if( SR->GetLoaderStop() || !(SR->DB->MachineParamsS.LoaderInstalled && SR->DB->WorkingModesS.LoaderEn) || (SR->DB->WorkingModesS.LoaderEn && (SR->DB->ProductionDataS.LoaderBoardNumber == 0)) )
			{
				controlPanel->SetState( PANEL_PRINTING );


				panel->UpdatePrintingPanel();
				panel->EnablePrintingPanel( true );
				toolBox->Enable( true );
				menuBtn->Enable( true );
				datasette->StartEnable( true );
				datasette->PauseEnable( false );

				SR->CheckCover( false );

				smartLogger->Write( MSG_PRINTINGENDED, MSG_SUCCESS );

				SR->SetLoaderStop( false );

				if( SR->SetAlarmLight( ALARMLIGHT_YELLOW ) == SR_ERROR )
				{
					smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
					return SR_ERROR;
				}

			}
			//aggiunto
			panel->DrawControl(PP_PRINTING);
			panel->Layout();
			panel->EnablePrintingPanel(true);
			//fine

			break;

		//----------------------------------------------------------------------------------
		case PRINTING_STATE_STOP:
			// Wait all motors to end movement
			if( SR->PlateMotor.Wait() == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}
			if( SR->CamXMotor.Wait() == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAXERROR, MSG_ERROR );
				return SR_ERROR;
			}
			if( SR->CamYMotor.Wait() == SR_ERROR )
			{
				smartLogger->Write( MSG_CAMERAYERROR, MSG_ERROR );
				return SR_ERROR;
			}
			if( SR->SqueegeesMotor.Wait() == SR_ERROR )
			{
				smartLogger->Write( MSG_SQUEEGEESERROR, MSG_ERROR );
				return SR_ERROR;
			}
			if( SR->WaitTable() == SR_ERROR )
			{
				smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			SR->ErrorManagement();

			controlPanel->SetState( PANEL_PRINTING );

			panel->DrawControl(PP_PRINTING);
			panel->Layout();
			panel->UpdatePrintingPanel();
			//panel->EnablePrintingPanel( !SR->isBoardLoaded ); //stoppando, il pannello si abilita solo se la scheda non e inserita!
			panel->EnablePrintingPanel( true );
			toolBox->Enable( true );
			menuBtn->Enable( true );
			datasette->StartEnable( true );
			datasette->PauseEnable( false );

			SR->CheckCover( false );
			break;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMPrintingNext
// Aggiorna lo stato della SM
//----------------------------------------------------------------------------------
void SMBase::SMPrintingNext(int data)
{
	retVal = SR_OK;

	switch( currentState )
	{
		case PRINTING_STATE_PRINT1:
			retVal = SMPrinting( PRINTING_STATE_PRINT2 );
			break;

		case PRINTING_STATE_FINAL:
			retVal = SMPrinting( PRINTING_STATE_INIT2 );
			break;
			
		case PRINTING_STATE_FOUND_WAIT:
			retVal = SMPrinting( PRINTING_STATE_FOUND );
			break;

		case PRINTING_STATE_FOUND:
			retVal = SMPrinting( PRINTING_STATE_NEXT );
			break;

		case PRINTING_STATE_VERIFY:
		case PRINTING_STATE_VERIFY_CAMERA:
			retVal = SMPrinting( PRINTING_STATE_VERIFY_NEXT );
			break;

		case PRINTING_STATE_INSPECTION_NEXT_MOVE:
			retVal = SMPrinting( PRINTING_STATE_INSPECTION_MOVE );
			break;

		case PRINTING_STATE_INSPECTION:

			if( data == wxProductionPanel::EVT_GRID_SELECTED )
			{
				cv::Mat Frame_and_rect= AutoSPIcheck->TemplateImg.clone();
				int index_contour=0;
				int sum=0;

				for (int i=0; i<SR->DB->pAUTOInspectionCurrentSiteStruct->PointsNum; i++)
				{
					sum += SR->DB->pAUTOInspectionCurrentSiteStruct->SpotEnable[i];
					if (sum == SR->DB->Selected_row +1)
					{
						index_contour=i;
						break;
					}
				}

				cv::Rect boundRect = cv::boundingRect( SR->DB->pAUTOInspectionCurrentSiteStruct->Contours[index_contour] );
				if(Frame_and_rect.channels()==1)
				{
					cv::cvtColor(Frame_and_rect,Frame_and_rect, CV_GRAY2BGR);
				}

				cv::Point br;
				cv::Point tl;
				if(0.2*boundRect.width> 20){
					br = cv::Point(boundRect.br().x + 20 - expectedPos.X, boundRect.br().y + 2 -expectedPos.Y);
					tl = cv::Point(boundRect.tl().x - 20 - expectedPos.X, boundRect.tl().y - 20 -expectedPos.Y);;
				}
				else{
					br = cv::Point(boundRect.br().x + 0.2*boundRect.width - expectedPos.X, boundRect.br().y + 0.2*boundRect.height -expectedPos.Y);
					tl = cv::Point(boundRect.tl().x - 0.2*boundRect.width - expectedPos.X, boundRect.tl().y - 0.2*boundRect.height -expectedPos.Y);;
				}


				cv::Rect big_rec(tl,br);
				cv::rectangle( Frame_and_rect, big_rec, cv::Scalar(0,0,255), SPI_RECTANGLE_THICKNESS);

				camera->SetVideoMainImage(  wxImage( Frame_and_rect.cols,Frame_and_rect.rows, (unsigned char*)Frame_and_rect.data, true)   );

				break;
			}
			else if(data == wxProductionPanel::EVT_REQUEST_NEW_THRESHOLDS){
				retVal= SMPrinting(PRINTING_STATE_IDLE_PHASE1_DRAW);
			}
			else if(data == wxMainVideo::CHANGE_SPI_PREVIEW){
				if(AutoSPIcheck->SPIdrawings){
					camera->SetVideoMainImage(  wxImage( Frame_to_Mat.cols, Frame_to_Mat.rows, (unsigned char*)Frame_to_Mat.data, true)   );
					AutoSPIcheck->SPIdrawings = !AutoSPIcheck->SPIdrawings;
				}else{
					camera->SetVideoMainImage(  wxImage( AutoSPIcheck->TemplateImg.cols, AutoSPIcheck->TemplateImg.rows, (unsigned char*)AutoSPIcheck->TemplateImg.data, true)   );
					AutoSPIcheck->SPIdrawings = !AutoSPIcheck->SPIdrawings;
				}
			}
			else
			{
				if( SR->SetAlarmLight( ALARMLIGHT_GREEN ) == SR_ERROR )
				{
					smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
				}

				retVal = SMPrinting( PRINTING_STATE_INSPECTION_NEXT ); //this is the next button
			}

			break;

		case PRINTING_STATE_INSPECTION_WAIT:
			retVal= SMPrinting(PRINTING_STATE_INSPECTION_CHECK);
			break;
		case PRINTING_STATE_IDLE_PHASE1: //means a new parameter arrived!
			if( data == wxProductionPanel::EVT_PARAMETERS_CHANGED){
				retVal= SMPrinting(PRINTING_STATE_IDLE_PHASE1);
			}
			else if(data == wxProductionPanel::EVT_ACCEPT_CHANGES){
				SR->DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE = 30;
				SR->DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE = 20; ///default values!

				retVal= SMPrinting(PRINTING_STATE_IDLE_PHASE2_DRAW);//this is the next button
			}
			break;
		case PRINTING_STATE_IDLE_PHASE2:
			if( data == wxProductionPanel::EVT_PARAMETERS_CHANGED){
				retVal= SMPrinting(PRINTING_STATE_IDLE_PHASE2);
			}
			else if(data == wxProductionPanel::EVT_ACCEPT_CHANGES){
				retVal= SMPrinting(PRINTING_STATE_INSPECTION);//this is the next button
			}
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
void SMBase::SMPrintingPrev()
{
	retVal = SR_OK;

	switch( currentState )
	{
		case PRINTING_STATE_SEARCH:
		case PRINTING_STATE_FOUND_WAIT:
			retVal = SMPrinting( PRINTING_STATE_SEARCH );
			break;

		case PRINTING_STATE_VERIFY:
			retVal = SMPrinting( PRINTING_STATE_VERIFY_PREV );
			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}


//----------------------------------------------------------------------------------
// SMPrintingMainVideoLeftClick
// 
//----------------------------------------------------------------------------------
void SMBase::SMPrintingMainVideoLeftClick( wxMouseEvent& e )
{
	retVal = SR_OK;

	if( !isMainVideoClickEnable ){
		std::cout<<"video non abilitato, stato attuale: "<<currentState<<std::endl;
		//wxMessageBox(  wxString::Format( "video non abilitato, stato attuale %d",currentState), MACHINE_NAME, wxOK | wxICON_WARNING, parent );
		return;
	}

	switch( currentState )
	{
		case PRINTING_STATE_SEARCH:
			// Cursor position
			camera->GetCursorPositionMain( xClicked, yClicked );
			centerX = xClicked;
			centerY = yClicked;

			camera->SetMainMode( MAIN_NO_CUR );
			// Disable camera
			if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
			{
				 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
			}

			smartLogger->Write( wxString::Format( MSG_FIDFOUNDMAN, xClicked, yClicked ) );
			retVal = SMPrinting( PRINTING_STATE_FOUND_WAIT );
			break;
		case PRINTING_STATE_IDLE_PHASE2:
			camera->GetCursorPositionMain( xClicked, yClicked );
			//cout<<"premuto il mouse at :"<<xClicked<< "  "<<yClicked <<endl;
			wxColour color = camera->getPixelColor(xClicked, yClicked );
			//std::cout<<(int)color.Red()<< "  "<< (int)color.Green() << " "<< (int)color.Blue()<<std::endl;
			wxProductionPanel *panel = (wxProductionPanel *)currentPanel;
			panel->UpdatePadThresholds( (int)color.Red(), (int)color.Green(), (int)color.Blue() );

			break;
	}

	if( retVal == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

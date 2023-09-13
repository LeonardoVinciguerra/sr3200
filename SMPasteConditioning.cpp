//---------------------------------------------------------------------------
//
// Name:        SMPasteConditioning.cpp
// Author:      Daniele Belloni
// Created:     05/09/2017
// Description: Paste conditioning - State Machine functions implementation
//
//---------------------------------------------------------------------------

#include "SMBase.h"
#include "wxProductionPanel.h"
#include <wx/msgdlg.h>
#include "GlobalUtils.h"
#include "Messages.h"

#include "FileFunctions.h"

#define PANEL_PASTE			PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE
#define PANEL_VERIFY_MOVE	PANEL_MOVE_CAMERA, PANEL_OUTPUT_LED_UP | PANEL_OUTPUT_LED_DOWN
#define PANEL_DISABLE		PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE


//----------------------------------------------------------------------------------
// SMPasteConditioningInitialize
// Inizializza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMPasteConditioningInitialize()
{
	controlPanel->SetState( PANEL_PASTE );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMPasteConditioningFinalize
// Finalizza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMPasteConditioningFinalize()
{
	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMPasteConditioningReset
// Resetta la macchina a stati
//----------------------------------------------------------------------------------
void SMBase::SMPasteConditioningReset()
{
	SR->CheckCover( false );

	// Reset plate to normal movement params
	SR->PlateMotor.SetSpeedAcc();

	controlPanel->SetState( PANEL_PASTE );

	wxProductionPanel *panel = (wxProductionPanel *)currentPanel;
}

//----------------------------------------------------------------------------------
// SMPasteConditioning
// Macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMPasteConditioning( int nextState )
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
		currentState = PASTE_STATE_STOP;

	switch( currentState )
	{
		//----------------------------------------------------------------------------------
		case PASTE_STATE_INIT1:
			initCheck.cover			= true;
			initCheck.air			= true;
			initCheck.pcb			= false;
			initCheck.pcb_height	= 0;
			initCheck.frame			= true;
			initCheck.motors_pos	= true;
			initCheck.motor_state	= MODE_STARTPRINTING_POSITION;

			// Contatore del numero di cicli di paste conditioning
			pasteCounter = 0;

			if( SMInitCheck( initCheck ) == SR_ERROR )
				return SR_ERROR;

			// Paste conditioning cycle can begin.
			if( SMPasteConditioning( PASTE_STATE_INIT2 ) == SR_ERROR )
				return SR_ERROR;
			break;

		//----------------------------------------------------------------------------------
		case PASTE_STATE_INIT2:

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

			if( SMPasteConditioning( PASTE_STATE_PRINT1 ) == SR_ERROR )
				return SR_ERROR;
			break;

		//----------------------------------------------------------------------------------
		case PASTE_STATE_RESET:

			// Reset plate to normal movement params
			if( SR->PlateMotor.SetSpeedAcc() == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// Check for motors position
			if( SR->CheckMotorsPos() == SR_ERROR )
			{
				if( SR->ResetMotors( SR->GetStop() ? MODE_START_POSITION : MODE_STARTPRINTING_POSITION ) == SR_ERROR )
					return SR_ERROR;
			}

			toolBox->Enable( true );
			menuBtn->Enable( true );
			datasette->StartEnable( true );
			datasette->PauseEnable( false );

			SR->CheckCover( false );

			controlPanel->SetState( PANEL_PASTE );
			break;

		//----------------------------------------------------------------------------------
		case PASTE_STATE_PRINT1:
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

			// Ask for a paper to be placed on the PCB
			wxMessageBox( MSG_PASTEASKPAPER, MACHINE_NAME, wxOK | wxICON_INFORMATION, parent );

			// Move the board to reaches the frame
			if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.PlateMovement + SR->DB->ProductionDataS.PlateMovementDelta, ABS_MOVE ) == SR_ERROR )
			{
				smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
				return SR_ERROR;
			}

			if( SMPasteConditioning( PASTE_STATE_PRINT2 ) == SR_ERROR )
				return SR_ERROR;
			break;

		//----------------------------------------------------------------------------------
		case PASTE_STATE_PRINT2:
			// Move squeegees for printing
			smartLogger->Write( wxString::Format( MSG_PASTECYCLE, pasteCounter+1, SR->pasteConditionIters ) );

			if( SMPasteConditioning( PASTE_STATE_PRINT3 ) == SR_ERROR )
				return SR_ERROR;
			break;
		//----------------------------------------------------------------------------------
		case PASTE_STATE_PRINT3:
			for( int i = 0; i < 2; i++ ) //2 = front-rear
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

					// Deactivate rear squeege
					if( SR->SetOutput( OUTPUT_SQUEEGEESREAR, false ) == SR_ERROR )
					{
						smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
						return SR_ERROR;
					}
					SR->SetSqueegeesCycle( !SR->GetSqueegeesCycle() );
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
					if( SR->SetOutput( OUTPUT_SQUEEGEESREAR, false ) == SR_ERROR )
					{
						smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
						return SR_ERROR;
					}
					if( SR->SetOutput( OUTPUT_SQUEEGEESFRONT, true ) == SR_ERROR )
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

					// Deactivate front squeegees
					if( SR->SetOutput( OUTPUT_SQUEEGEESFRONT, false ) == SR_ERROR )
					{
						smartLogger->Write( MSG_SQUEEGEESACTERROR, MSG_ERROR );
						return SR_ERROR;
					}
					SR->SetSqueegeesCycle( !SR->GetSqueegeesCycle() );
				}
			}

			// Wait to be sure the squeegees are up
			myMilliSleep( SQUEEGEES_DELAY );

			// Increment counters
			SR->DB->MachineParamsS.Counter++;
			SR->DB->SaveMachineParams();

			pasteCounter++;

			if( pasteCounter < SR->pasteConditionIters )
			{
				if( SMPasteConditioning( PASTE_STATE_PRINT2 ) == SR_ERROR )
					return SR_ERROR;
			}
			else
			{
				if( SMPasteConditioning( PASTE_STATE_DISENGAGE ) == SR_ERROR )
					return SR_ERROR;
			}

			break;

		//----------------------------------------------------------------------------------
		case PASTE_STATE_DISENGAGE:

			// Disengage board from frame...
			
			// If required, execute a slow speed disengage
			if( SR->DB->WorkingModesS.DifferentialDisengage && ( SR->DB->WorkingModesS.DisengageSpeed != 0.0 ) )
			{
				// Set plate disengage movement params
				speed_entry = SR->DB->SpeedTableS[SPEED_PLATE_DOWN_ID];
				if( SR->PlateMotor.SetSpeedAcc( lround(SR->DB->WorkingModesS.DisengageSpeed) , speed_entry.Acc[SR->DB->MachineParamsS.PlateDownSpeed], speed_entry.Dec[SR->DB->MachineParamsS.PlateDownSpeed] ) == SR_ERROR )
				{
					smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
					return SR_ERROR;
				}
				if( SR->PlateMotor.MoveAndWait( 0, ABS_MOVE ) == SR_ERROR )
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

			if( SMPasteConditioning( PASTE_STATE_FINAL ) == SR_ERROR )
				return SR_ERROR;
			break;

		//----------------------------------------------------------------------------------
		case PASTE_STATE_FINAL:
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

			// Ask for paper to be removed from the PCB
			wxMessageBox( MSG_PASTEREMOVEPAPER, MACHINE_NAME, wxOK | wxICON_INFORMATION, parent );

			// Move the board outside the machine
			if( SR->UnloadBoard() == SR_ERROR )
			{
				smartLogger->Write( MSG_LOADERROR, MSG_ERROR );
				return SR_ERROR;
			}

			// draw empty workplace
			camera->DrawWorkplace();

			smartLogger->Write( MSG_PASTEENDED, MSG_SUCCESS );

			if( SMPasteConditioning( PASTE_STATE_RESET ) == SR_ERROR )
				return SR_ERROR;

			break;

		//----------------------------------------------------------------------------------
		case PASTE_STATE_STOP:
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

			controlPanel->SetState( PANEL_PASTE );

			panel->DrawControl(PP_PASTE);
			panel->Layout();
			toolBox->Enable( true );
			menuBtn->Enable( true );
			datasette->StartEnable( true );
			datasette->PauseEnable( false );

			SR->CheckCover( false );
			break;
	}

	return SR_OK;
}


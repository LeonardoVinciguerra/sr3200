//---------------------------------------------------------------------------
//
// Name:        SMDemomode.cpp
// Author:      Gabriel Ferri
// Created:     02/10/2008 17.31
// Description: Vision - State Machine functions implementation
//
//---------------------------------------------------------------------------

#include "SMBase.h"
#include "GlobalUtils.h"
#include <wx/msgdlg.h>
#include "Messages.h"

#define PANEL_VISION		PANEL_MOVE_DISABLE, PANEL_OUTPUT_LOCK | PANEL_OUTPUT_LED_UP | PANEL_OUTPUT_LED_DOWN
#define PANEL_DISABLE		PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE

#define MAX_CYCLES			300


//----------------------------------------------------------------------------------
// SMDemomodeInitialize
// Inizializza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMDemomodeInitialize()
{
	controlPanel->SetState( PANEL_VISION );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMDemomodeFinalize
// Finalizza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMDemomodeFinalize()
{
	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMDemomodeReset
// Resetta la macchina a stati
//----------------------------------------------------------------------------------
void SMBase::SMDemomodeReset()
{
	controlPanel->SetState( PANEL_VISION );
}

//----------------------------------------------------------------------------------
// SMDemomode
// Macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMDemomode( int nextState )
{
	datasette->StopEnable( true );
	datasette->NextEnable( false );
	datasette->PrevEnable( false );
	controlPanel->SetState( PANEL_DISABLE );

	currentState = nextState;

	switch( currentState )
	{
		case DEMOMODE_STATE_INIT:
			initCheck.cover			= false;
			initCheck.air			= true;
			initCheck.pcb			= false;
			initCheck.pcb_height	= 0;
			initCheck.frame			= true;
			initCheck.motors_pos	= true;
			initCheck.motor_state	= MODE_STARTPRINTING_POSITION;

			if( SMInitCheck( initCheck ) == SR_ERROR )
				return SR_ERROR;

			if( SR->SetAlarmLight(ALARMLIGHT_GREEN) == SR_ERROR ){
				smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
				return SR_ERROR;
			}

			cycleCounter = 0;

			while( cycleCounter < MAX_CYCLES )
			{

				// Move the board inside the machine
				if( SR->LoadBoard(CHECK_DISABLED) == SR_ERROR )
				{
					smartLogger->Write( MSG_LOADERROR, MSG_ERROR );
					return SR_ERROR;
				}

				// draw board
				if( SR->DB->ProductionDataS.PCBPosX != 0.0 )
					camera->DrawWorkplace( SR->DB->ProductionDataS.PCBPosX, SR->DB->ProductionDataS.PCBPosY, SR->DB->ProductionDataS.PCBX, SR->DB->ProductionDataS.PCBY );

				// Move the board to reaches the camera focus
				if( SR->PlateMotor.Move( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
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
				if( SR->PlateMotor.Wait() == SR_ERROR )
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

				// Simulate a down/up camera vision
				camera->SetMainMode( MAIN_NO_CUR );
				camera->StartCapture();
				
				myMilliSleep( 1000 );

				// Enable camera
				if( SR->SetCamera( CAMERA_UP ) == SR_ERROR )
				{
					 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
					 return SR_ERROR;
				}

				myMilliSleep( 1000 );

				camera->StopCapture();

				// Disable camera
				if( SR->SetCamera( CAMERA_OFF ) == SR_ERROR )
				{
					 smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
					 return SR_ERROR;
				}

				if( SR->MoveXYTable( 3, 3, SR->GetLimitsState() ) == SR_ERROR )
				{
					smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
					return SR_ERROR;
				}
				// Move camera out
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
				// Move the board to reaches the frame
				if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.PlateMovement + SR->DB->ProductionDataS.PlateMovementDelta, ABS_MOVE ) == SR_ERROR )
				{
					smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
					return SR_ERROR;
				}
				// Move squeegees
				for( int i = 0; i < SR->DB->WorkingModesS.DoubleSqueegees + 1; i++ )
				{
					if( ( SR->GetSqueegeesCycle() == true && SR->DB->ProductionDataS.SqueegeesMove <= 0 ) ||
						( SR->GetSqueegeesCycle() == false && SR->DB->ProductionDataS.SqueegeesMove > 0 ) )
					{
						// Sueeges are on the back side...
						// ...activate rear squeege and, just in case, deactivate front one
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
						// Move the squeegees
						if( SR->SqueegeesMotor.MoveAndWait( SR->DB->ProductionDataS.SqueegeesMove, REL_MOVE ) == SR_ERROR )
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
						// Sueeges are on the operator side...
						// ...activate front squeegee and, just in case, deactivate rear one
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
						// Move the squeegees
						if( SR->SqueegeesMotor.MoveAndWait( SR->DB->ProductionDataS.SqueegeesZeroMove, ABS_MOVE ) == SR_ERROR )
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
				// Reset table
				if( SR->ResetTable() == SR_ERROR )
				{
					smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
					return SR_ERROR;
				}
				// Plate in zero position
				if( SR->PlateMotor.MoveAndWait( 0, ABS_MOVE ) == SR_ERROR )
				{
					smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
					return SR_ERROR;
				}
				if( SR->WaitTable() == SR_ERROR )
				{
					smartLogger->Write( MSG_TABLEERROR, MSG_ERROR );
					return SR_ERROR;
				}
				//Cleaning cycle
				if(SR->DB->WorkingModesS.CleaningEn && SR->DB->MachineParamsS.CleaningInstalled){
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

				}
				// Move the board outside the machine
				if( SR->UnloadBoard(CHECK_DISABLED) == SR_ERROR )
				{
					smartLogger->Write( MSG_LOADERROR, MSG_ERROR );
					return SR_ERROR;
				}

				// draw empty workplace
				camera->DrawWorkplace();

				if( cycleCounter < MAX_CYCLES )
						smartLogger->Write( wxString::Format( "Cycle num. %d", ++cycleCounter ) );
			}

			if( SR->SetAlarmLight(ALARMLIGHT_YELLOW) == SR_ERROR){
				smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
				return SR_ERROR;
			}
			toolBox->Enable( true );
			menuBtn->Enable( true );
			datasette->StartEnable( true );

			controlPanel->SetState( PANEL_VISION );
			break;

		case VISION_STATE_RESET:
			if( SR->SetAlarmLight(ALARMLIGHT_YELLOW) == SR_ERROR){
				smartLogger->Write( MSG_SEMAPHOREERROR, MSG_ERROR );
				return SR_ERROR;
			}
			datasette->StopEnable( false );
			cycleCounter = MAX_CYCLES;
			break;
	}

	return SR_OK;
}

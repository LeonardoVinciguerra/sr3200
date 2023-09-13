//---------------------------------------------------------------------------
//
// Name:        Motor.cpp
// Author:      Gabriel Ferri
// Created:     09/06/2009
// Description: Motor class implementation
//
//---------------------------------------------------------------------------

#include "Motor.h"
#include "GlobalDefs.h"
#include "GlobalEnum.h"
#include "GlobalUtils.h"
#include "Errors.h"
#include "StepperModule.h"
#include "BrushlessModule.h"
#include "BrushModule.h"
#include "iqmath.h"
#include <iostream>

#define	MINIMUM_FREQ_STEPPER			200
#define	MAXIMUM_FREQ_STEPPER			1280000

#define WAIT_RETRY				3


Motor::Motor()
{
	motor = NULL;

	actualPos = 0.0;
	movement_sign = 1;
}

Motor::~Motor()
{
	MyDELETE( motor );
}

//----------------------------------------------------------------------------------
// MmToPU
// Ritorna la posizione in p.u.
//----------------------------------------------------------------------------------
long Motor::MmToPU( double mm )
{
	long val;

	val = _IQ24( movement_sign * mm * (*data.PulsesToMm) / (*data.LineEnc) + 0.5 );

	return val;
}

//----------------------------------------------------------------------------------
// PUToMm
// Ritorna i mm relativi ai p.u. passati
//----------------------------------------------------------------------------------
double Motor::PUToMm( long pu )
{
	double val;

	val = movement_sign * (_IQ24ToF( pu ) - 0.5) * (*data.LineEnc) / (*data.PulsesToMm);

	return val;
}

int Motor::Init( MotorStruct dataRef )
{
	data = dataRef;

	if( *data.Address == 255 )
	{
		*data.errorCode |= ERR_MOTORINIT;
		return MOTOR_ERROR;
	}

	MACHINE_CONFIG( MACHINE_ENABLE )
		if( motor == NULL )
		{
			if( *data.Driver == DRIVER_STEPPER_ID )
				motor = new StepperModule( data.commIntStepper, *data.Address );
			else if( *data.Driver == DRIVER_BRUSHLESS_ID )
				motor = new BrushlessModule( data.commIntBrushless, *data.Address );
			else
				motor = new BrushModule( data.commIntBrushless, *data.Address );
		}
		else
			motor->ChangeAddress( *data.Address );
	MACHINE_CONFIG_END

	return MOTOR_OK;
}

int Motor::Enable()
{
	MACHINE_CONFIG( MACHINE_ENABLE )
		if( *data.Driver == DRIVER_STEPPER_ID )
		{
			if( SetSpeedAcc( data.Speed[(*data.SpeedIndex)], data.Acc[(*data.SpeedIndex)], data.Dec[(*data.SpeedIndex)] ) == MOTOR_ERROR )
			{
				return MOTOR_ERROR;
			}

			if( motor->MicroStepping( *data.Microstepping ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			if( SetCurrent() == MOTOR_ERROR )
			{
				return MOTOR_ERROR;
			}

			if( motor->MotorEnable( MOTOR_ON ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}
		}
		else if( *data.Driver == DRIVER_BRUSHLESS_ID )
		{
			_iq val;

			// setta output dividers (dal momento che la macchina e' alimentata a 48V e le uscite prevedono 24V)
			if( motor->SetOutputDivider( OUT0, OUTPUTDIVIDER_PARAM ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}
			if( motor->SetOutputDivider( OUT1, OUTPUTDIVIDER_PARAM ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}
			if( motor->SetOutputDivider( OUT2, OUTPUTDIVIDER_PARAM ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// setta output reduction times (dopo alcuni ms, divido la tensione per 4)
			if( motor->SetOutputReductionTime( OUT0, OUTPUTREDTIME_PARAM ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}
			if( motor->SetOutputReductionTime( OUT1, OUTPUTREDTIME_PARAM ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}
			if( motor->SetOutputReductionTime( OUT2, OUTPUTREDTIME_PARAM ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// set board max current
			if( motor->SetMaxReadCurrent( BOARDMAXCURRENT_PARAM ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// Set current (nominal current)
			if( motor->SetNominalCurrent( *data.Current ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// Set PIDs parameters
			if( SetPIDs() == false )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// Encoder Mode
			if( *data.EncoderType == ENCODER_QEP ){
				if( motor->EncoderMode( ENCODER_QEP, *data.EncoderMode ) == MOTOR_ERROR ){
					*data.errorCode |= ERR_MOTORINIT;
					return MOTOR_ERROR;
				}
			}else if(*data.EncoderType == ENCODER_SER){
				if( motor->EncoderMode( ENCODER_SER, *data.EncoderMode ) == MOTOR_ERROR ){
					*data.errorCode |= ERR_MOTORINIT;
					return MOTOR_ERROR;
				}
			}


			// Line Encoder 1
			if( motor->SetLineEncoder( *data.LineEnc ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// Line Encoder 2
			if( motor->SetLineEncoder2( *data.LineEnc ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// Pulses Per Revolution
			if( motor->SetPulsesPerRev( *data.PPR ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// Poles
			if( motor->SetPoles( *data.Poles ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// Pulses To Mm
			if( motor->SetPulsesToMm( *data.PulsesToMm ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// Calibrated Angle
			if( motor->SetCalibratedAngle( CALANGLE_PARAM ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// setta overspeed
			if( motor->SetOverSpeed( OVERSPEED_PARAM ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// aggiorna valore overspeed
			if( motor->UpdateOverSpeed() == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// ADC calibration
			if( motor->SetIdRef( 0 ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}
			if( motor->SetIqRef( 0 ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// Reset speed module
			if( motor->ResetSpeed() == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			for( int i=0; i<5; i++ )
			{
				if( motor->ADCCalEnable( ADCCAL_ON ) == MOTOR_ERROR )
				{
					*data.errorCode |= ERR_MOTORINIT;
					return MOTOR_ERROR;
				}

				if( motor->IsDriverEnable() )
					wxMilliSleep( 100 );

				if( motor->ADCCalEnable( ADCCAL_OFF ) == MOTOR_ERROR )
				{
					*data.errorCode |= ERR_MOTORINIT;
					return MOTOR_ERROR;
				}

				if( motor->IsDriverEnable() )
					wxMilliSleep( 100 );
			}

			// Angle calibration
			if( motor->ElecThetaGeneration( ELECTTHETA_OFF ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			//val = _IQ24( CAL_ANGLE_CURRENT/2.0 );
			val = _IQ24( CAL_ANGLE_CURRENT );
			if( motor->SetIdRef( val ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			if( motor->SetPhaseRotationNumber(1) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			if( motor->SetPhaseRotation( (phaserot_sign > 0) ? PHASEROT_POS : PHASEROT_NEG ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			if( motor->IsDriverEnable() )
				wxMilliSleep( CAL_PHASE_ROT_DELAY );
/*
			if( motor->SetPhaseRotationNumber(1) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			if( motor->SetPhaseRotation( (phaserot_sign > 0) ? PHASEROT_NEG : PHASEROT_POS ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			if( motor->IsDriverEnable() )
				wxMilliSleep( CAL_PHASE_ROT_DELAY );
*/
			// setta velocita' iniziali
			if( !SetStartSpeeds() )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// aggiorna valore overspeed
			if( motor->UpdateOverSpeed() == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}
			
			if( motor->ElecThetaGeneration( ELECTTHETA_OFF ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			val = _IQ24( CAL_ANGLE_CURRENT );
			if( motor->SetIdRef( val ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			val = _IQ24( 0 );
			if( motor->SetIParkAngle( val ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			if( motor->IsDriverEnable() )
				wxMilliSleep( CAL_ANGLE_DELAY );

			if( motor->ResetEncoder() == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			if( motor->SetIdRef( 0 ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			if( motor->ElecThetaGeneration( ELECTTHETA_ON ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// Setta il proximity gap
			if( motor->SetProximityGap( _IQ24( PROXIMITYGAP_PARAM ) ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// Setta il PID pos activation gap
			if( motor->SetPIDPosActivationGap( _IQ24( PIDPOSACTIVATIONGAP_PARAM ) ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			/*
			// Setta il following error
			if( head[module]->SetFollowingError( _IQ24( headParams[module].FollowingError * headParams[module].PulsesToMm / headParams[module].LineEnc1 ) ) == MOTOR_ERROR )
			{
				error |= ERR_DRIVER;
				return false;
			}

			// Setta speed filter
			if( head[module]->SetSpeedFilter( headParams[module].SpeedFilter ) == MOTOR_ERROR )
			{
				error |= ERR_DRIVER;
				return false;
			}

			// Setta start ticks
			if( head[module]->SetStartTicks( headParams[module].StartTicks ) == MOTOR_ERROR )
			{
				error |= ERR_DRIVER;
				return false;
			}
			*/

			// Abilita il ciclo di controllo di posizione
			if( motor->MotorEnable( MOTOR_ON ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// attiva controllo velocita'
			if( motor->OverSpeedCheck( 1 ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}
			
			// Se il delta di fine movimento e' settato a 0 nel db, si prende quello di deafault (si usa nel caso di motori con encoder rotativo..)
			// altrimenti si considera il dato del db come espresso in mm
			if( *data.EndMovementDelta == 0 )
			{
				if( motor->SetEndMovementDelta( _IQ24( ENDMOVEDELTA_PARAM ) ) == MOTOR_ERROR )
				{
					*data.errorCode |= ERR_MOTORINIT;
					return MOTOR_ERROR;
				}
			}
			else
			{
				if( motor->SetEndMovementDelta( _IQ24( *data.EndMovementDelta * *data.PulsesToMm / *data.LineEnc ) ) == MOTOR_ERROR )
				{
					*data.errorCode |= ERR_MOTORINIT;
					return MOTOR_ERROR;
				}
			}

			if( motor->SetEndMovementSpeed( _IQ24( ENDMOVESPEED_PARAM ) ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// setta jerk
			if( motor->SetMaxJerk( *data.Jerk ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// setta Coulomb friction
			if( motor->SetCFriction( _IQ24( *data.KC ) ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// setta speed feed-forward
			if( motor->SetSpdFFWD( _IQ24( *data.KS ) ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// setta acc feed-forward
			if( motor->SetAccFFWD( _IQ24( *data.KA ) ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// setta spyke delta
			if( motor->SetEncoderSpykeDelta( *data.SpykeDelta ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// setta profile mode
			if( motor->SetSpeedProfile( *data.Profile ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			// Set reduced current as nominal current
			if( motor->SetNominalCurrent( *data.RedCurrent ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			/*
			// setta parametri logger
			if( SetLogParams( module ) == false )
				return false;
			*/

		}
		else
		{
			if( motor->SetDirection( *data.Direction ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}
		}
	MACHINE_CONFIG_END

	return MOTOR_OK;
}

int Motor::Disable()
{
	MACHINE_CONFIG( MACHINE_ENABLE )
		if( motor->ResetDrive() == MOTOR_ERROR )
		{
			*data.errorCode |= ERR_MOTORINIT;
			return MOTOR_ERROR;
		}
	MACHINE_CONFIG_END

	return MOTOR_OK;
}

int Motor::EnableControlPID()
{
	MACHINE_CONFIG( MACHINE_ENABLE )
		if( *data.Driver == DRIVER_BRUSHLESS_ID )
		{
			// Abilita il ciclo di controllo di posizione
			if( motor->MotorEnable( MOTOR_ON ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}
		}
	MACHINE_CONFIG_END

	return MOTOR_OK;
}

int Motor::GetFirmwareVersion( char &ver, char &rev )
{
	int ret_val = 0;

	MACHINE_CONFIG( MACHINE_ENABLE )
		ret_val = motor->GetVersion();
		if( ret_val == MOTOR_ERROR )
		{
			*data.errorCode |= ERR_DRIVER;
			return MOTOR_ERROR;
		}
	MACHINE_CONFIG_END

	ver = ret_val >> 8;
	rev = ret_val % 256;

	return MOTOR_OK;
}

//---------------------------------------------------------------------------------
// SetCurrent
// Setta valori delle correnti nel caso di stepper
//---------------------------------------------------------------------------------
int Motor::SetCurrent()
{
	if( motor->SetMinCurrent(*data.MinCurrent) == MOTOR_ERROR )
	{
		*data.errorCode |= ERR_MOTORINIT;
		return MOTOR_ERROR;
	}
	if( motor->SetMaxCurrent(*data.MaxCurrent) == MOTOR_ERROR )
	{
		*data.errorCode |= ERR_MOTORINIT;
		return MOTOR_ERROR;
	}
	if( motor->SetNominalCurrent(*data.MaxCurrent) == MOTOR_ERROR )
	{
		*data.errorCode |= ERR_MOTORINIT;
		return MOTOR_ERROR;
	}
	if( motor->SetDecay( SLOW_DECAY ) == MOTOR_ERROR )
	{
		*data.errorCode |= ERR_MOTORINIT;
		return MOTOR_ERROR;
	}
	return MOTOR_OK;
}

//---------------------------------------------------------------------------------
// SetPIDs
// Setta valori PID del modulo
//---------------------------------------------------------------------------------
bool Motor::SetPIDs()
{
	// Set PIDs parameters
	if( motor->SetPIDIqParams( _IQ24(KP_I_PARAM), _IQ24(KI_I_PARAM), _IQ24(KD_I_PARAM), _IQ24(KC_I_PARAM), _IQ24(MAX_I_PARAM), _IQ24(MIN_I_PARAM) ) == MOTOR_ERROR )
	{
		return false;
	}
	if( motor->SetPIDIdParams( _IQ24(KP_I_PARAM), _IQ24(KI_I_PARAM), _IQ24(KD_I_PARAM), _IQ24(KC_I_PARAM), _IQ24(MAX_I_PARAM), _IQ24(MIN_I_PARAM) ) == MOTOR_ERROR )
	{
		return false;
	}
	if( motor->SetPIDSpdParams( PIDSET_DEF, _IQ24(*data.KP_speed), _IQ24(*data.KI_speed), _IQ24(KD_S_PARAM), _IQ24(KC_S_PARAM), _IQ24(MAX_S_PARAM), _IQ24(MIN_S_PARAM) ) == MOTOR_ERROR )
	{
		return false;
	}
	if( motor->SetPIDSpdParams( PIDSET_0, _IQ24(*data.KP_speed), _IQ24(*data.KI_speed), _IQ24(KD_S_PARAM), _IQ24(KC_S_PARAM), _IQ24(MAX_S_PARAM), _IQ24(MIN_S_PARAM) ) == MOTOR_ERROR )
	{
		return false;
	}
	if( motor->SetPIDSpdParams( PIDSET_SPD, _IQ24(*data.KP_speed), _IQ24(*data.KI_speed), _IQ24(KD_S_PARAM), _IQ24(KC_S_PARAM), _IQ24(MAX_S_PARAM), _IQ24(MIN_S_PARAM) ) == MOTOR_ERROR )
	{
		return false;
	}
	if( motor->SetPIDPosParams( PIDSET_DEF, _IQ24(*data.KP_pos), _IQ24(KI_P_PARAM), _IQ24(KD_P_PARAM), _IQ24(KC_P_PARAM), _IQ24(MAX_P_PARAM), _IQ24(MIN_P_PARAM) ) == MOTOR_ERROR )
	{
		return false;
	}
	if( motor->SetPIDPosParams( PIDSET_0, _IQ24(*data.KP_pos), _IQ24(KI_P_PARAM), _IQ24(KD_P_PARAM), _IQ24(KC_P_PARAM), _IQ24(MAX_P_PARAM), _IQ24(MIN_P_PARAM) ) == MOTOR_ERROR )
	{
		return false;
	}

	return true;
}

//---------------------------------------------------------------------------------
// Setta velocita' iniziali per i brushless (minime)
//---------------------------------------------------------------------------------
bool Motor::SetStartSpeeds()
{
	if( motor->MinimumFreq( _IQ24(STARTSTOP_FREQ) ) == MOTOR_ERROR )
	{
		return false;
	}
	if( motor->MaximumFreq( _IQ24(MINIMUM_FREQ) ) == MOTOR_ERROR )
	{
		return false;
	}
	if( motor->Aceleration( _IQ24(MINIMUM_ACC) ) == MOTOR_ERROR )
	{
		return false;
	}
	if( motor->Deceleration( _IQ24(MINIMUM_ACC) ) == MOTOR_ERROR )
	{
		return false;
	}

	return true;
}

int Motor::SetSpeedAcc()
{
	return SetSpeedAcc( data.Speed[(*data.SpeedIndex)], data.Acc[(*data.SpeedIndex)], data.Dec[(*data.SpeedIndex)] );
}

int Motor::SetSpeedAcc( long speed, long acc, long dec )
{
	MACHINE_CONFIG( MACHINE_ENABLE )
		if( *data.Driver == DRIVER_STEPPER_ID )
		{
			long frequence = speed;
			frequence = MID( MINIMUM_FREQ_STEPPER, frequence, MAXIMUM_FREQ_STEPPER );

			if( motor->MinimumFreq( MINIMUM_FREQ_STEPPER )  == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}
			
			if( motor->MaximumFreq( frequence ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			if( motor->Aceleration( acc ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}
			if( motor->Deceleration( dec ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}
		}
		else if( *data.Driver == DRIVER_BRUSHLESS_ID )
		{
			if( motor->MaximumFreq( _IQ24((double)speed/1000.0) ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			if( motor->Aceleration( _IQ24((double)acc/1000.0) ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}

			if( motor->Deceleration( _IQ24((double)dec/1000.0) ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}
		}
	MACHINE_CONFIG_END

	return MOTOR_OK;
}

int Motor::Check( double pos, int mode )
{
	MACHINE_CONFIG( MACHINE_ENABLE )
		double posTmp = pos;
		if( mode == REL_MOVE )
			posTmp += actualPos;

		if( posTmp > *data.MaxLimit || posTmp < *data.MinLimit || isNan( posTmp ) )
		{
			*data.errorCode |= ERR_LIMITSOFTWARE;
			return MOTOR_ERROR;
		}
	MACHINE_CONFIG_END

	return MOTOR_OK;
}

int Motor::Move( double pos, int mode, int limit )
{
	MACHINE_CONFIG( MACHINE_ENABLE )
		double posTmp = pos;

		if( *data.Driver != DRIVER_BRUSH_ID )
		{
			if( mode == REL_MOVE )
				posTmp += actualPos;

			// Check dei limiti
			if( limit == LIMIT_ON )
			{
				if( posTmp > *data.MaxLimit || posTmp < *data.MinLimit || isNan( posTmp ) )
				{
					*data.errorCode |= ERR_LIMITSOFTWARE;
					std::cout<<"Software limt Error NO brush!"<<std::endl;
					return MOTOR_ERROR;
				}
			}
		}

		if( *data.Driver == DRIVER_STEPPER_ID )
		{
			// If limit check activated, reset of all possible alarms...
			if( *data.limitsOn )
			{
				if( motor->ResetAlarms() == MOTOR_ERROR )
				{
					*data.errorCode |= ERR_DRIVER;
					return MOTOR_ERROR;
				}
			}

			// Working params computing
			double Resolution = GetResolution();
			long int StepActPulse = movement_sign * myLRound(posTmp / Resolution);

			if( motor->GotoPos0( StepActPulse ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORMOVE;
				return MOTOR_ERROR;
			}
		}
		else if( *data.Driver == DRIVER_BRUSHLESS_ID )
		{
			if( *data.errorCode != 0 ){
				std::cout<<"Error present in struct !"<<std::endl;
				return MOTOR_ERROR;
			}
	
			// Set current (nominal current)
			if( motor->SetNominalCurrent( *data.Current ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				std::cout<<"Motor init Error (SetNominalCurrent) !"<<std::endl;
				return MOTOR_ERROR;
			}

			if( motor->GotoPos0( MmToPU( posTmp ) ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORMOVE;
				std::cout<<"Motor move Error (GotoPos0) !"<<std::endl;
				return MOTOR_ERROR;
			}
		}
		else if( *data.Driver == DRIVER_BRUSH_ID )
		{
			if( motor->StartRotation( int(pos) ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORMOVE;
				std::cout<<"Motor move Error (StartRotation) !"<<std::endl;
				return MOTOR_ERROR;
			}
		}

		if( *data.Driver != DRIVER_BRUSH_ID )
			actualPos = posTmp;
	MACHINE_CONFIG_END

	return MOTOR_OK;
}

int Motor::Wait()
{
	MACHINE_CONFIG( MACHINE_ENABLE )
		int isOK = 0;
		int limit = 0;
		int status = 0;
		int retry = 0;
		int brushless = 0;
		//int sensorChecked = 0;

		do
		{
			status = motor->MotorStatus();
			if( status == MOTOR_ERROR )
			{
				retry++;
				continue;
			}

			if( !(status & MOTOR_RUNNING) )
				isOK = 1;

			if( (status & MOTOR_OVERRUN) && *data.limitsOn )
				limit = 1;

			if( *data.Driver == DRIVER_BRUSHLESS_ID )
			{
				if( (status & MOTOR_OVERCURRENT) || (status & MOTOR_TIMEOUT) || (status & MOTOR_OVERSPEED) || (status & MOTOR_NOENC) || (status & MOTOR_NO_FOLLOW) )
					brushless = 1;
			}

			::wxYield();
		}
		while( !isOK && !limit && retry < WAIT_RETRY && !brushless );

		if( retry >= WAIT_RETRY )
		{
			*data.errorCode |= ERR_MOTORWAIT;
			return MOTOR_ERROR;
		}
		if( limit )
		{
			*data.errorCode |= ERR_LIMITSWITCH;
			return MOTOR_ERROR;
		}
		if( brushless )
		{
			*data.errorCode |= ERR_BRUSHLESS;
			return MOTOR_ERROR;
		}
		
		if( *data.Driver == DRIVER_BRUSHLESS_ID )
		{
			// Set reduced current as nominal current
			if( motor->SetNominalCurrent( *data.RedCurrent ) == MOTOR_ERROR )
			{
				*data.errorCode |= ERR_MOTORINIT;
				return MOTOR_ERROR;
			}
		}
	MACHINE_CONFIG_END


	return MOTOR_OK;

}

int Motor::MoveAndWait( double pos, int mode, int limit )
{
	if( Move( pos, mode, limit ) == MOTOR_ERROR )
		return MOTOR_ERROR;
	if( Wait() == MOTOR_ERROR )
		return MOTOR_ERROR;

	return MOTOR_OK;
}

double Motor::GetResolution()
{
	double resolution;

	if( data.ScrewStep )
		resolution =  data.ScrewStep * (*data.Reduction) / ( MOTOR_SPR * (*data.Microstepping) );
	else if( data.LinearStep )
		resolution = data.LinearStep / (*data.Microstepping);
	else
		resolution = ( PI * (*data.Pulley) * (*data.Reduction) ) / ( MOTOR_SPR * (*data.Microstepping) );

	return resolution;
}


//---------------------------------------------------------------------------
//
// Name:        StepperModule.h
// Author:      Daniele Belloni, Gabriel Ferri
// Created:     07/05/2008
// Description: StepperModule class declaration
//
//---------------------------------------------------------------------------
#ifndef __STEPPERMODULE_H
#define __STEPPERMODULE_H

#include "MotorModule.h"

class StepperModule : public MotorModule
{
public:
	StepperModule( wxCommInterface* ComInt, int address );
	~StepperModule();
 
	virtual unsigned short GetVersion();
	virtual int  SetMinCurrent( int val );
	virtual int  SetMaxCurrent( int val );
	virtual int  SetNominalCurrent( int val );
	virtual int  GetNominalCurrent();
	virtual int  FreeRotation( int sensoRot );
	virtual int  StopRotation( int ramp );
	virtual int  MicroStepping( int frazione );
	virtual long ActualPosition();
	virtual int  SetActualPosition( long pos );
	virtual int  Home();
	virtual int  GotoPosRel( long pos );
	virtual int  GotoPos0( long pos );
	virtual int  MinimumFreq( int mFreq );
	virtual int  MaximumFreq( long MFreq );
	virtual int  Aceleration( long acc );
	virtual int  Deceleration( long dec );
	virtual int  SlopeValue( long slopeFactor );
	virtual long ActualVelocity();
	virtual int  MotorStatus();
	virtual int  ActualInputs();
	virtual int  SetOutputs( int outId, int outVal );
	virtual int  SetLimitsCheck( int limit, int limitLevel = LIMITLEVEL_HIGH );
	virtual int  ResetAlarms();
	virtual int  MotorEnable( int command );
	virtual int  ResetDrive();
	virtual long GetEncoderActualPosition();
	virtual int  EncoderMode( int type, int mode );
	virtual int  GetEncoderMode( int type );
	virtual int  InputsSetting( long val );
	virtual int  SearchPos0( int dir );
	virtual int  SetDecay( int val );
	virtual int  SuspendDrive();
	virtual int  SetPIDIqParams( long KP, long KI, long KD, long KC, long OMax, long OMin );
	virtual int  GetPIDIqParams( long *KP, long *KI, long *KD, long *KC, long *OMax, long *OMin );
	virtual int  SetPIDIdParams( long KP, long KI, long KD, long KC, long OMax, long OMin );
	virtual int  GetPIDIdParams( long *KP, long *KI, long *KD, long *KC, long *OMax, long *OMin );
	virtual int  SetPIDSpdParams( unsigned short set, long KP, long KI, long KD, long KC, long OMax, long OMin );
	virtual int  GetPIDSpdParams( unsigned short set, long *KP, long *KI, long *KD, long *KC, long *OMax, long *OMin );
	virtual int  SetPIDPosParams( unsigned short set, long KP, long KI, long KD, long KC, long OMax, long OMin );
	virtual int  GetPIDPosParams( unsigned short set, long *KP, long *KI, long *KD, long *KC, long *OMax, long *OMin );
	virtual long GetLineEncoder();
	virtual int  SetLineEncoder( long lines );
	virtual long GetPulsesPerRev();
	virtual int  SetPulsesPerRev( long ppr );
	virtual int  GetPoles();
	virtual int  SetPoles( int poles );
	virtual int  GetCalibratedAngle();
	virtual int  SetCalibratedAngle( int angle );
	virtual int  GetLoggerTrigger();
	virtual int  SetLoggerTrigger( int trig );
	virtual int  GetLoggerPrescaler();
	virtual int  SetLoggerPrescaler( int prescal );
	virtual int  GetLoggerChannelData( int channel );
	virtual int  SetLoggerChannelInput( int channel, int input );
	virtual long GetEncoderActualSpeed( int mode );
	virtual int  PWMEnable( int command );
	virtual int  PhaseEnable( int phase, int command );
	virtual int  ADCCalEnable( int command );
	virtual long GetClarkeAs();
	virtual long GetClarkeBs();
	virtual long GetADCOffset( int channel );
	virtual int  SetADCOffset( int channel, long val );
	virtual long GetPIDIqOut();
	virtual long GetPIDIdOut();
	virtual long GetPIDSpdOut();
	virtual long GetPIDPosOut();
	virtual long GetPIDIqFdb();
	virtual long GetPIDIdFdb();
	virtual long GetPIDSpdFdb();
	virtual long GetPIDPosFdb();
	virtual long GetIqRef();
	virtual int  SetIqRef( long val );
	virtual long GetIdRef();
	virtual int  SetIdRef( long val );
	virtual int  GetEncoderType();
	virtual int  SetEncoderType( int type );
	virtual int  ElecThetaGeneration( int mode );
	virtual int  GetMaxSpeed();
	virtual int  SetMaxSpeed( int spd );
	virtual int  GetRamps();
	virtual int  SetRamps( int mode );
	virtual long ActualStartStopVelocity();
	virtual long ActualAceleration();
	virtual long ActualDeceleration();
	virtual int  SetActualPIDSpd( unsigned short set );
	virtual int  SetActualPIDPos( unsigned short set );
	virtual int  LoggerTriggerMode( int mode );
	virtual long GetEncoderActualPulses();
	virtual int  SetPhaseCurrent( long val );
	virtual long GetPhaseCurrent();
	virtual int  GetDecelerationAdvance();
	virtual int  SetDecelerationAdvance( int val );
	virtual int  GetPulsesToMm();
	virtual int  SetPulsesToMm( int ptm );
	virtual int  DecCompensationMode( int mode );
	virtual int  SetProximityGap( long val );
	virtual long GetProximityGap();
	virtual int  SetPIDPosActivationGap( long val );
	virtual long GetPIDPosActivationGap();
	virtual int  SetIParkAngle( long val );
	virtual long GetIParkAngle();
	virtual long GetDangerLimit( int limit );
	virtual int  SetDangerLimit( int limit, long val );
	virtual int  DangerLimitMode( int mode );
	virtual int  ResetEncoder();
	virtual int  HomeSensorInput( int val );
	virtual long GetHomingSpeed( int speed );
	virtual int  SetHomingSpeed( int speed, long val );
	virtual int  GetOverSpeed();
	virtual int  SetOverSpeed( int val );
	virtual int  SetReferenceActualPos();
	virtual int  ResetPIDSpd();
	virtual int  ResetPIDPos();
	virtual int  PIDStatus();
	virtual int  GetMaxReadCurrent();
	virtual int  SetMaxReadCurrent( int val );
	virtual long GetPhaseC();
	virtual long GetEncoder360ActualPosition();
	virtual long GetElecTheta();
	virtual long GetAccFFWD();
	virtual int  SetAccFFWD( long val );
	virtual long GetSpdFFWD();
	virtual int  SetSpdFFWD( long val );
	virtual int  GetMaxJerk();
	virtual int  SetMaxJerk( int val );
	virtual long GetCFriction();
	virtual int  SetCFriction( long val );
	virtual long GetEndMovementSpeed();
	virtual int  SetEndMovementSpeed( long val );
	virtual long GetEndMovementDelta();
	virtual int  SetEndMovementDelta( long val );
	virtual int  GotoPos0_Multi( unsigned char addX, long posX, unsigned char addY, long posY, long maxFreq, long acc, long proximityDeltaX, long proximityDeltaY );
	virtual int  ResetFlag_Multi();
	virtual long GetEncoder2ActualPosition();
	virtual long GetEncoder2ActualPulses();
	virtual long GetLineEncoder2();
	virtual int  SetLineEncoder2( long lines );
	virtual long GetEncoderInterpActualPosition();
	virtual int  GetStatus_ResetFlagMulti();
	virtual int  SetFollowingError( long val );
	virtual long GetFollowingError();
	virtual int  EncoderStatus();
	virtual int  SetStartTicks( int ticks );
	virtual int  SetPhaseRotation( int value );
	virtual int  SetPhaseRotationNumber( int value );
	virtual int  SetSpeedFilter( unsigned short window );
	virtual int  SetSecurityCheck( int limit, int limitLevel );
	virtual int  SetSecurityInput( int val );
	virtual long GetVPower();
	virtual int  GetTemperature();
	virtual int  SetSteadyPosFollowError( long val );
	virtual long GetSteadyPosFollowError();
	virtual int  SetEncoderSpykeDelta( int delta );
	virtual int  GetEncoderSpykeDelta();
	virtual int  SetSpeedProfile( int mode );
	virtual int  UpdateOverSpeed();
	virtual int  OverSpeedCheck( int enable );
	virtual int  SetHomeSensorLevel( int level );
	virtual int  ResetSpeed();
	virtual int  SetOutputDivider( int outId, int divider );
	virtual int  GetOutputDivider( int outId );
	virtual int  SetOutputReductionTime( int outId, int time );
	virtual int  GetOutputReductionTime( int outId );
	virtual int  SetHomeMove( long val );
	virtual long GetHomeMove();
	virtual int  MultiMotorMode(int mode);
	virtual int  SetHomeTimeout( long val );
	virtual int  StartRotation( int msec );
	virtual int  SetDuration( int msec );
	virtual int  GetDuration();
	virtual int  SetDirection( int dir );
	virtual int  GetDirection();
	virtual int  SetOutputPulseTime(int outId, int msec);
	virtual int  SetOutputPulseMode(int outId, int mode);

protected:
	int Read_Reg_Micro( unsigned char RegAdd, unsigned short* Value );
	int Write_Reg_Micro( unsigned char RegAdd, unsigned short Value );

};

#endif

//---------------------------------------------------------------------------
//
// Name:        MotorModule.h
// Author:      Gabriel Ferri
// Created:     07/05/2008
// Description: MotorModule class declaration
//
//---------------------------------------------------------------------------
#ifndef __MOTORMODULE_H
#define __MOTORMODULE_H

#include "wxCommInterface.h"

#define MOTOR_DATA_LEN		512

#define	MOTOR_ERROR			-1		// Command execution error
#define	MOTOR_OK			0		// No error

#define FAST_DECAY			0
#define SLOW_DECAY			1

#define CW					0x01
#define CCW					0x00

#define IO0					0x01
#define IO1					0x02
#define IO2					0x04
#define IO3					0x08
#define DIO0				0x10
#define DIO1				0x20
#define DIO2				0x40

#define IOIN				0
#define IOOUT				1

#define LOW					0
#define HIGH				1

#define NORAMP				0
#define RAMP				1

#define OUT0				0
#define OUT1				1
#define OUT2				2


// Maschere per la funzione MotorStatus
#define MOTOR_RUNNING		0x0001		// Il motore si sta muovendo
#define MOTOR_OVERCURRENT	0x0002		// Overcurrent
#define MOTOR_PROCERROR		0x0004		// Errore nella procedura (usato in ricerca zero)
#define MOTOR_TIMEOUT		0x0008		// Timeout nel movimento
#define MOTOR_ZERO			0x0010		// Ricerca origini in corso
#define MOTOR_OVERRUN		0x0020		// Raggiunto un finecorsa
#define MOTOR_DANGER		0x0040		// Raggiunto il limite software di movimento
#define MOTOR_OVERSPEED		0x0080		// Overspeed
#define MOTOR_NOENC			0x0100		// Nessuna variazione encoder rilevata
#define MOTOR_PIDSPDON		0x0200		// PID di velocita' attivo
#define MOTOR_PIDPOSON		0x0400		// PID di posizione attivo
#define MOTOR_NEARTARGET	0x0800		// Il motore e' in prossimita della posizione obiettivo
#define MOTOR_MULTIMOVE		0x1000		// Il motore ha eseguito un movimento "multi-motore"
#define MOTOR_NO_FOLLOW		0x2000		// Errore inseguimento traiettoria "eccessivo"
#define MOTOR_SECURITY		0x4000		// Sensore di sicurezza attivo
#define MOTOR_STEADYPOS		0x8000		// Errore mantenimento posizione di regime


// Attivazione o disattivazione check dei limiti dei movimenti
#define LIMITCHECK_OFF		0
#define LIMITCHECK_ON		1
// Livello check limiti (attivi alti o bassi)
#define LIMITLEVEL_LOW		0
#define LIMITLEVEL_HIGH		1

// Attivazione, disattivazione o stato dei movimenti del motore
#define MOTOR_OFF			0
#define MOTOR_ON			1
#define MOTOR_STATUS		2

// Velocita' di homing
#define HOME_SLOW  			0
#define HOME_FAST  			1

class MotorModule
{
public:
	MotorModule( wxCommInterface* ComInt, int Address );
	~MotorModule();

	void ChangeAddress( int address ) { m_Address = address; }
	int GetAddress() { return m_Address; }
	int GetErrorCode() { return errorCode; }
	void SerialComActivation( bool status ) { serialComStatus = status; }

	void DisableDriver( bool disable ) { isDisabled = disable; }
	bool IsDriverEnable() { return !isDisabled; }

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
	wxCommInterface* m_comInt;
	int m_Address;
	unsigned char m_Data[MOTOR_DATA_LEN];

	bool serialComStatus;

	int errorCode;

	bool isDisabled;
};

#endif

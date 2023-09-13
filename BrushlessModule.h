//---------------------------------------------------------------------------
//
// File:     BrushlessModule.h
// Info:     Definitions for the Brushless control module BrushlessModule.cpp
// Created:  Daniele Belloni
//
//---------------------------------------------------------------------------

#ifndef __BRUSHLESSMODULE_H
#define __BRUSHLESSMODULE_H

#include "MotorModule.h"

// Maschere per la funzione PIDStatus
#define PID_SPDDEF			0x0001		// Parametri di default PID di velocita' attivi
#define PID_SPD0			0x0002		// Parametri di regime PID di velocita' attivi
#define PID_SPDSPD			0x0004		// Parametri di loop di velocita' PID di velocita' attivi
#define PID_POSDEF			0x0008		// Parametri di default PID di posizione attivi
#define PID_POS0			0x0010		// Parametri di regime PID di posizione attivi

// Maschere per la funzione EncoderStatus
#define ENC_MF_ERROR		0x0001		// Magnetic field error
#define ENC_OVERRUN_ERROR	0x0002		// Overrun error
#define ENC_FRAME_ERROR		0x0004		// Frame error
#define ENC_NOREC_ERROR		0x0008		// No reception error

// Attivazione o disattivazione check dei limiti dei movimenti
#define LIMITCHECK_OFF		0
#define LIMITCHECK_ON		1
// Livello check limiti (attivi alti o bassi)
#define LIMITLEVEL_LOW		0
#define LIMITLEVEL_HIGH		1

// Livello check sensore di zero (attivo alto o basso)
#define ZEROLEVEL_HIGH					0
#define ZEROLEVEL_LOW					1

// Attivazione o disattivazione check del sensore di sicurezza
#define SECURITYCHECK_OFF   0
#define SECURITYCHECK_ON    1
// Livello check sensore sicurezza (attivo alto o basso)
#define SECURITYLEVEL_LOW   0
#define SECURITYLEVEL_HIGH  1

// Attivazione, disattivazione o stato dei movimenti del motore
#define MOTOR_OFF			0
#define MOTOR_ON			1
#define MOTOR_SPD_ON		2

// Modalita' di rotazione senza encoder
#define PHASEROT_DISABLE    0
#define PHASEROT_POS        1
#define PHASEROT_NEG        2

// Tipo encoder (quadratura o seriale)
#define ENCODER_QEP			0
#define ENCODER_SER			1

// Modalita' di funzionamento dell'encoder (normale o invertito)
#define ENCODER_NORMAL		0
#define ENCODER_INVERTED	1

// Modalita' di generazione angolo elettrico con encoder
#define ELECTTHETA_ON		0
#define ELECTTHETA_OFF		1

// Logger channel IDs
enum eLogChannels
{
	LOG_CH1 = 0,
	LOG_CH2,
	LOG_CH3,
	LOG_CH4,
	LOG_CH_NUM
};

#define LOG_BUF_SIZE		100

// Livello del trigger del logger
#define LOWTOHIGH_TRIG 		0
#define HIGHTOLOW_TRIG 		1

// Logger channel IDs
#define LOGGER_CH1			0
#define LOGGER_CH2			1
#define LOGGER_CH3			2
#define LOGGER_CH4			3

// Ingressi canali logger
#define LOGGER_MECHTHETA		0
#define LOGGER_SPEED			1
#define LOGGER_CLARKA			2
#define LOGGER_CLARKB			3
#define LOGGER_PIDIDOUT			4
#define LOGGER_PIDIQOUT			5
#define LOGGER_PIDIDFDB			6
#define LOGGER_PIDIQFDB			7
#define LOGGER_PIDIDREF			8
#define LOGGER_PIDIQREF			9
#define LOGGER_SPEEDREF			10
#define LOGGER_POSREF			11
#define LOGGER_POSERR			12
#define LOGGER_PIDIDERR			13
#define LOGGER_PIDIQERR			14
#define LOGGER_SPEEDERR			15
#define LOGGER_SPEEDREFNOPOS	16
#define LOGGER_ELECERROR		17
#define LOGGER_ELECRAMP			18
#define LOGGER_VPWR				19

// Indici fasi motore
#define PHASE1_INDEX		0
#define PHASE2_INDEX		1
#define PHASE3_INDEX		2

// Attivazione e disattivazione dei PWM delle fasi del motore
#define PWM_OFF				0
#define PWM_ON				1

// Attivazione e disattivazione della modalita' calibrazione ADC
#define ADCCAL_OFF			0
#define ADCCAL_ON			1

// Parametri usati durante la calibrazione dello zero elettrico
#define CAL_ANGLE_CURRENT	0.3
#define CAL_PHASE_ROT_DELAY	2000
#define CAL_ANGLE_DELAY		2000
#define CAL_PARKANGLE		0.1
#define CAL_ERROR			40

// Canali ADC
#define ADC_CHANNEL0		0
#define ADC_CHANNEL1		1

// Tipo encoder
#define ROTATIVE_ENC		0
#define LINEAR_ENC			1

// Bits di modalita' del modulo (relativi alla variabile work_vars dedicata...)
#define MODE_LIMITS         0
#define MODE_LIMITSLEVEL    1
#define MODE_RAMP           2 //n.u.
#define MODE_SECURITY       3
#define MODE_SECURITYLEVEL  4

// Attivazione/disattivazione rampe accelerazione/decelerazione
#define RAMP_ON  			0
#define RAMP_OFF  			1

// Lettura velocita'
#define SPEED_PU			0
#define SPEED_RPM			1
#define SPEED_MS			2

// Set di parametri del PID di velocita'
#define PIDSET_DEF			0
#define PIDSET_0			1
#define PIDSET_SPD			2

// Attivazione/disattivazione compensazione decelerazione
#define DECCOMP_ON  		0
#define DECCOMP_OFF  		1

// Attivazione/disattivazione limiti di pericolosita'
#define DANGERLIMIT_ON  	0
#define DANGERLIMIT_OFF  	1

// Direzione ricerca zero
#define ZEROSEARCH_POS  	0
#define ZEROSEARCH_NEG  	1

// Tipo di profilo
#define FIFTHDEGREE_PROFILE				0
#define TRAPEZOIDAL_PROFILE				1

#define PULSED_MODE_ON				0
#define PULSED_MODE_OFF				1

class BrushlessModule : public MotorModule
{
public:
	short bufDataLog[LOG_CH_NUM][LOG_BUF_SIZE];

	BrushlessModule( wxCommInterface* ComInt, int Address );
	~BrushlessModule();

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
	virtual int  MaximumAccFreq( long MFreq );
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
	virtual int  SetDecay( int val ); //
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

	unsigned char ver;
	unsigned char rev;
};

#endif

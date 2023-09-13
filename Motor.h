//---------------------------------------------------------------------------
//
// Name:        Motor.h
// Author:      Gabriel Ferri
// Created:     09/06/2009
// Description: Motor class declaration
//
//---------------------------------------------------------------------------

#ifndef __MOTOR_H
#define __MOTOR_H

#include "wxCommInterface.h"
#include "MotorModule.h"
#include "iqmath.h"

#define	MOTOR_OK				0
#define	MOTOR_ERROR				-1
#define MOTOR_OK_NO_SENSOR		-2

#define REL_MOVE				1
#define ABS_MOVE				0

#define LIMIT_ON				1
#define LIMIT_OFF				0


//Brushless Params
#define STARTSTOP_FREQ				0.002
#define MINIMUM_FREQ				0.05
#define MINIMUM_ACC					0.05
#define BOARDMAXCURRENT_PARAM		16000
#define KP_I_PARAM					0.1
#define KI_I_PARAM					0.7
#define KD_I_PARAM					0.0
#define KC_I_PARAM					0.7
#define MIN_I_PARAM					-0.7
#define MAX_I_PARAM					0.7
#define KD_S_PARAM					0.0
#define KC_S_PARAM					0.5
#define MIN_S_PARAM					-0.99
#define MAX_S_PARAM					0.99
#define KI_P_PARAM					0.0
#define KD_P_PARAM					0.0
#define KC_P_PARAM					0.0
#define MIN_P_PARAM					-0.99
#define MAX_P_PARAM					0.99
#define CALANGLE_PARAM				0
#define PROXIMITYGAP_PARAM			0.01
#define PIDPOSACTIVATIONGAP_PARAM	0.0001
#define ENDMOVEDELTA_PARAM			0.000916719 //0.0000916719
#define ENDMOVESPEED_PARAM			0.01
#define OVERSPEED_PARAM				100
#define OUTPUTDIVIDER_PARAM			2
#define OUTPUTDIVIDERLEDCOLOR_PARAM	1
#define OUTPUTREDTIME_PARAM			50

// Stepper Params
#define	MOTOR_SPR					200 // Motor "Step Per Revolution"


struct MotorStruct
{
	wxCommInterface* commIntStepper;
	wxCommInterface* commIntBrushless;

	int *Driver;

	int *Address;

	// Par stepper
	int *MinCurrent;
	int *AccCurrent;
	int *MaxCurrent;
	int *Microstepping;
	float *Pulley;
	float *Reduction;

	// Par brushless
	int *Current;
	float *KP_speed;
	float *KI_speed;
	float *KP_pos;
	long *LineEnc;
	int *PulsesToMm;
	int *PPR;
	int *Poles;
	int *Jerk;
	float *KA;
	float *KS;
	float *KC;
	float *HomeFast;
	float *HomeSlow;
	int *Profile;
	float *EndMovementDelta;
	int *SpykeDelta;
	int *RedCurrent;

	int *Speed;
	int *Acc;
	int *Dec;
	int *SpeedIndex;

	float *MinLimit;
	float *MaxLimit;

	int *errorCode;
	bool *limitsOn;
	bool *immediateStop;

	double ScrewStep;
	double LinearStep;

	int *Direction;

	int *EncoderMode;
	int *EncoderType;
};

class Motor
{
public:
	Motor();
	~Motor();

	int Init( MotorStruct dataRef );
	int Enable();
	int Disable();
	int EnableControlPID();

	void ResetErrors() { *data.errorCode = 0; };
	int GetErrors() { return *data.errorCode; };
	
	int GetFirmwareVersion( char &ver, char &rev );

	bool SetPIDs();
	
	int SetSpeedAcc();
	int SetSpeedAcc( long speed, long acc, long dec );

	void SetMovementSign( int sign ) { movement_sign = (sign >= 0) ? 1 : -1; };
	void SetPhaseRotSign( int sign ) { phaserot_sign = (sign >= 0) ? 1 : -1; };

	void ResetPosition() { actualPos = 0.0; };
	double GetPosition() { return actualPos; };

	double GetResolution();

	int Check( double pos, int mode = REL_MOVE );
	int Move( double pos, int mode = REL_MOVE, int limit = LIMIT_ON );
	int Wait();
	int MoveAndWait( double pos, int mode = REL_MOVE, int limit = LIMIT_ON);

	MotorModule* motor;
	MotorStruct data;

private:
	// Funzioni dedicate ai brushless
	long MmToPU( double mm );
	double PUToMm( long pu );
	bool SetStartSpeeds();

	// Funzioni dedicate agli stepper
	int SetCurrent();



	double actualPos;
	int movement_sign;
	int phaserot_sign;
};

#endif

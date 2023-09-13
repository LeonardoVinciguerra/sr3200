//---------------------------------------------------------------------------
//
// Name:        MotorModule.cpp
// Author:      Gabriel Ferri
// Created:     07/05/2008
// Description: MotorModule class implementation
//
//---------------------------------------------------------------------------
#include "MotorModule.h"

MotorModule::MotorModule( wxCommInterface* ComInt, int Address )
{
	m_comInt = ComInt;
	m_Address = Address;
	serialComStatus = true;
	isDisabled = false;
}

MotorModule::~MotorModule()
{
}

/*----------------------------------------------------------------------
FUNCTION:   unsigned short GetVersion()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the board firmware version
INPUT:      -
OUTPUT:     Version:
				- Bytes[1]: Version
				- Bytes[0]: Revision
GLOBAL:     -
RETURN:     Version on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
unsigned short MotorModule::GetVersion()
{
	return 0;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetMinCurrent( int val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor's reduced current
INPUT:      val: Current value
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::SetMinCurrent( int val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetMaxCurrent( int val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor's current when running at
            constant speed
INPUT:      val: Current value
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::SetMaxCurrent( int val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetNominalCurrent( int val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor's nominal current. No movements
            allowed if nominal current is 0
INPUT:      val: Current value
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::SetNominalCurrent( int val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetNominalCurrent()
AUTHOR:     Daniele Belloni
INFO:       Function used to get the motor's nominal current.
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     Current value in mA, MOTOR_ERROR if errors
----------------------------------------------------------------------*/
int MotorModule::GetNominalCurrent()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int FreeRotation( int sensoRot )
AUTHOR:     Daniele Belloni
INFO:       Function used to send the motor an infinite motion command
INPUT:      sensoRot: Rotation versus (0=CW, 1=CCW)
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::FreeRotation( int sensoRot )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int StopRotation( int ramp )
AUTHOR:     Daniele Belloni
INFO:       Function used to stop the motor
INPUT:      ramp: stop with or without ramp (0 without, 1 with)
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::StopRotation( int ramp)
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int MicroStepping( int Fraction )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor steps per revolution
INPUT:      Fraction: motor step fraction (1..128)
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::MicroStepping( int Fraction )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long ActualPosition()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the motor's actual position
INPUT:      -
GLOBAL:     -
RETURN:     Motor actual position, MOTOR_ERROR on error
----------------------------------------------------------------------*/
long MotorModule::ActualPosition()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetActualPosition( long pos )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor's actual position
INPUT:      pos: motor position
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::SetActualPosition( long pos )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int Home()
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor's home position
INPUT:      -
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::Home()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GotoPosRel( long pos )
AUTHOR:     Daniele Belloni
INFO:       Function used to move the motor (relative motion)
INPUT:      pos: number of steps
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::GotoPosRel( long pos )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GotoPos0( long pos )
AUTHOR:     Daniele Belloni
INFO:       Function used to move the motor (absolute motion)
INPUT:      pos: number of steps
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::GotoPos0( long pos )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int MinimumFreq( int mFreq )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor starting frequency in ms.
            (200 to 4000)
INPUT:      mFreq: frequency
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::MinimumFreq( int mFreq )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int MaximumFreq( long MFreq )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor working frequency in ms.
            (1 to MaximumAccFreq)
INPUT:      MFreq: frequency
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::MaximumFreq( long MFreq )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int Aceleration( long acc )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor aceleration time in ms.
            (1 to 10000)
INPUT:      acc: aceleration time
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::Aceleration( long acc )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int Deceleration( long dec )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor deceleration time in ms.
            (1 to 10000)
INPUT:      dec: deceleration time
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::Deceleration( long dec )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SlopeValue( long slopeFactor )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor aceleration and deceleration
            time in ms. (1 to 10000)
INPUT:      slopeFactor: aceleration and deceleration time
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::SlopeValue( long slopeFactor )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long ActualVelocity()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the motor's actual velocity
INPUT:      -
GLOBAL:     -
RETURN:     Motor actual velocity, MOTOR_ERROR on error
----------------------------------------------------------------------*/
long MotorModule::ActualVelocity()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int MotorStatus()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the motor's status
            Used with masks:
            MOTOR_RUNNING: the motor is moving
            MOTOR_OVERRUN: limit switch reached
INPUT:      -
GLOBAL:     -
RETURN:     Motor status, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::MotorStatus()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int ActualInputs()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the driver's actual digital inputs
INPUT:      -
GLOBAL:     -
RETURN:     Driver actual inputs status, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::ActualInputs()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetOutputs( int outId, int outVal )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the driver's digital outputs
INPUT:      outId: Output id (OUT0, OUT1, OUT2)
            outVal: Output val (LOW, HIGH)
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::SetOutputs( int outId, int outVal )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetLimitsCheck( int limit, int limitLevel )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor limits check.
INPUT:      limitLevel: Set limit check level high or low (LIMITLEVEL_HIGH,
                        LIMITLEVEL_LOW)
            limit: Activate or deactivate limits check (LIMITCHECK_ON,
                   LIMITCHECK_OFF)
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::SetLimitsCheck( int limit, int limitLevel )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int ResetAlarms()
AUTHOR:     Daniele Belloni
INFO:       Function used to reset driver alarms.
INPUT:      -
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::ResetAlarms()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int MotorEnable( int command )
AUTHOR:     Daniele Belloni
INFO:       Function used to reset driver alarms.
INPUT:      command: action
                     MOTOR_OFF:    disable motor
                     MOTOR_ON:     enable motor
                     MOTOR_STATUS: motor status
GLOBAL:     -
RETURN:     If status required, 0 if enabled, 1 if enabled. MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::MotorEnable( int command )
{
	return 0;
}

/*----------------------------------------------------------------------
FUNCTION:   int ResetDrive()
AUTHOR:     Daniele Belloni
INFO:       Function used reset the drive
INPUT:      -
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::ResetDrive()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetEncoderActualPosition()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the encoder's actual position
INPUT:      -
GLOBAL:     -
RETURN:     Encoder actual position, MOTOR_ERROR on error
----------------------------------------------------------------------*/
long MotorModule::GetEncoderActualPosition()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int EncoderMode( long mode )
AUTHOR:     Daniele Belloni
INFO:       Function used to activate the encoder's motor control mode
INPUT:      mode: working mode
				  ENCODER_NORMAL: normal
				  ENCODER_INVERTED: inverted
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::EncoderMode( int type, int mode )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetEncoderMode()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the encoder control mode
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     encoder mode (0: normal, 1: inverted), -1 if errors
----------------------------------------------------------------------*/
int MotorModule::GetEncoderMode( int type )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int InputsSetting( long val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set motion controllers inputs setting
INPUT:      val: inputs setting DWORD
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::InputsSetting( long val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SearchPos0( int dir )
AUTHOR:     Daniele Belloni
INFO:       Function used to search motor's home position
INPUT:      dir: search direction (ZEROSEARCH_POS, ZEROSEARCH_NEG)
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SearchPos0( int dir )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetDecay( int val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set motor's decay
INPUT:      val: decays
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::SetDecay( int val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SuspendDrive()
AUTHOR:     Daniele Belloni
INFO:       Function used to suspend the drive serial communication
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on OK, MOTOR_ERROR on error
----------------------------------------------------------------------*/
int MotorModule::SuspendDrive()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetPIDIqParams()
AUTHOR:     Daniele Belloni
INFO:       Function used to set Iq current PID params
INPUT:      PID coefficients
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetPIDIqParams( long KP, long KI, long KD, long KC, long OMax, long OMin )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetPIDIqParams()
AUTHOR:     Daniele Belloni
INFO:       Function used to get Iq current PID params
INPUT:      -
OUTPUT:     PID coefficients
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::GetPIDIqParams( long *KP, long *KI, long *KD, long *KC, long *OMax, long *OMin )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetPIDIdParams()
AUTHOR:     Daniele Belloni
INFO:       Function used to set Id current PID params
INPUT:      PID coefficients
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetPIDIdParams( long KP, long KI, long KD, long KC, long OMax, long OMin )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetPIDIdParams()
AUTHOR:     Daniele Belloni
INFO:       Function used to get Id current PID params
INPUT:      -
OUTPUT:     PID coefficients
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::GetPIDIdParams( long *KP, long *KI, long *KD, long *KC, long *OMax, long *OMin )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetPIDSpdParams()
AUTHOR:     Daniele Belloni
INFO:       Function used to set speed PID params
INPUT:      PID set id and PID coefficients
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetPIDSpdParams( unsigned short set, long KP, long KI, long KD, long KC, long OMax, long OMin )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetPIDSpdParams()
AUTHOR:     Daniele Belloni
INFO:       Function used to get speed PID params
INPUT:      PID set id
OUTPUT:     PID coefficients
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::GetPIDSpdParams( unsigned short set, long *KP, long *KI, long *KD, long *KC, long *OMax, long *OMin )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetPIDPosParams()
AUTHOR:     Daniele Belloni
INFO:       Function used to set position PID params
INPUT:      PID set id and PID coefficients
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetPIDPosParams( unsigned short set, long KP, long KI, long KD, long KC, long OMax, long OMin )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetPIDPosParams()
AUTHOR:     Daniele Belloni
INFO:       Function used to get position PID params
INPUT:      PID set id
OUTPUT:     PID coefficients
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::GetPIDPosParams( unsigned short set, long *KP, long *KI, long *KD, long *KC, long *OMax, long *OMin )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetLineEncoder()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the motor's encoder line number
OUTPUT:     -
GLOBAL:     -
RETURN:     Motor line encoder
----------------------------------------------------------------------*/
long MotorModule::GetLineEncoder()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetLineEncoder( long lines )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor's encoder line number
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetLineEncoder( long lines )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetPulsesPerRev()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the motor's encoder pulses per revolution
OUTPUT:     -
GLOBAL:     -
RETURN:     Motor encoder pulses per revolution
----------------------------------------------------------------------*/
long MotorModule::GetPulsesPerRev()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetPulsesPerRev( long ppr )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor's encoder pulses per revolution
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetPulsesPerRev( long ppr )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetPoles()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the motor's poles
OUTPUT:     -
GLOBAL:     -
RETURN:     Motor encoder poles
----------------------------------------------------------------------*/
int MotorModule::GetPoles()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetPoles( int poles )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor's poles
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetPoles( int poles )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetCalibratedAngle()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the motor's calibrated angle
OUTPUT:     -
GLOBAL:     -
RETURN:     Motor calibrated angle
----------------------------------------------------------------------*/
int MotorModule::GetCalibratedAngle()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetCalibratedAngle( int angle )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor's calibrated angle
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetCalibratedAngle( int angle )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetLoggerTrigger()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the logger trigger level
OUTPUT:     -
GLOBAL:     -
RETURN:     Logger trigger
----------------------------------------------------------------------*/
int MotorModule::GetLoggerTrigger()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetLoggerTrigger( int trig )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the logger trigger level
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetLoggerTrigger( int trig )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetLoggerPrescaler()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the logger prescaler
OUTPUT:     -
GLOBAL:     -
RETURN:     Logger prescaler
----------------------------------------------------------------------*/
int MotorModule::GetLoggerPrescaler()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetLoggerPrescaler( int prescal )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the logger prescaler
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetLoggerPrescaler( int prescal )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetLoggerChannelData()
AUTHOR:     Daniele Belloni
INFO:       Function used to get the logger channel data
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::GetLoggerChannelData( int channel )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetLoggerChannelInput( int channel, int input )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the logger channels input
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetLoggerChannelInput( int channel, int input )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetEncoderActualSpeed( int mode )
AUTHOR:     Daniele Belloni
INFO:       Function used to read the encoder's actual speed
INPUT:      mode: action
                     SPEED_PU:  speed in p.u.
                     SPEED_RPM: speed in RPM
                     SPEED_MS:  speed in m/s
OUTPUT:     -
GLOBAL:     -
RETURN:     Encoder actual speed
----------------------------------------------------------------------*/
long MotorModule::GetEncoderActualSpeed( int mode )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int PWMEnable( int command )
AUTHOR:     Daniele Belloni
INFO:       Function used to enable motor PWM generation
INPUT:      command: action
                     PWM_OFF:    disable pwm
                     PWM_ON:     enable pwm
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::PWMEnable( int command )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int PhaseEnable( int phase, int command )
AUTHOR:     Daniele Belloni
INFO:       Function used to enable single motor phase
INPUT:      phase:	 phase to activate/deactivate
			command: action
                     PWM_OFF:    disable pwm
                     PWM_ON:     enable pwm
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::PhaseEnable( int phase, int command )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int ADCCalEnable( int command )
AUTHOR:     Daniele Belloni
INFO:       Function used to enable ADC Calibration mode
INPUT:      command: action
                     ADCCAL_OFF:    disable ADC cal
                     ADCCAL_ON:     enable ADC cal
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::ADCCalEnable( int command )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetClarkeAs()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the Clark module As input
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     Clarke As component in IQ24
----------------------------------------------------------------------*/
long MotorModule::GetClarkeAs()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetClarkeBs()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the Clark module Bs input
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     Clarke Bs component in IQ24
----------------------------------------------------------------------*/
long MotorModule::GetClarkeBs()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetADC0Offset( int channel )
AUTHOR:     Daniele Belloni
INFO:       Function used to get ADC offset
INPUT:      channel: action
                     ADC_CHANNEL0:  read ADC channel 0
                     ADC_CHANNEL1:  read ADC channel 1
OUTPUT:     -
GLOBAL:     -
RETURN:     ADCx offset
----------------------------------------------------------------------*/
long MotorModule::GetADCOffset( int channel )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetADCOffset( int channel, long val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set ADC offset
INPUT:      channel: action
                     ADC_CHANNEL0:  set ADC channel 0
                     ADC_CHANNEL1:  set ADC channel 1
		    val: value to assign to ADC channel
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetADCOffset( int channel, long val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetPIDIqOut()
AUTHOR:     Daniele Belloni
INFO:       Function used to get PID Iq out
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     PID Iq out in IQ24
----------------------------------------------------------------------*/
long MotorModule::GetPIDIqOut()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetPIDIdOut()
AUTHOR:     Daniele Belloni
INFO:       Function used to get PID Id out
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     PID Id out in IQ24
----------------------------------------------------------------------*/
long MotorModule::GetPIDIdOut()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetPIDSpdOut()
AUTHOR:     Daniele Belloni
INFO:       Function used to get PID speed out
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     PID speed out in IQ24
----------------------------------------------------------------------*/
long MotorModule::GetPIDSpdOut()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetPIDPosOut()
AUTHOR:     Daniele Belloni
INFO:       Function used to get PID position out
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     PID position out in IQ24
----------------------------------------------------------------------*/
long MotorModule::GetPIDPosOut()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetPIDIqFdb()
AUTHOR:     Daniele Belloni
INFO:       Function used to get PID Iq feedback
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     PID Iq feedback in IQ24
----------------------------------------------------------------------*/
long MotorModule::GetPIDIqFdb()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetPIDIdFdb()
AUTHOR:     Daniele Belloni
INFO:       Function used to get PID Id feedback
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     PID Id feedback in IQ24
----------------------------------------------------------------------*/
long MotorModule::GetPIDIdFdb()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetPIDSpdFdb()
AUTHOR:     Daniele Belloni
INFO:       Function used to get PID speed feedback
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     PID speed feedback in IQ24
----------------------------------------------------------------------*/
long MotorModule::GetPIDSpdFdb()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetPIDPosFdb()
AUTHOR:     Daniele Belloni
INFO:       Function used to get PID position feedback
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     PID position feedback in IQ24
----------------------------------------------------------------------*/
long MotorModule::GetPIDPosFdb()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetIqRef()
AUTHOR:     Daniele Belloni
INFO:       Function used to get Iq reference current
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     Iq reference in IQ24
----------------------------------------------------------------------*/
long MotorModule::GetIqRef()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetIqRef( long val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set Iq reference
INPUT:      val: value to assign to Iq reference
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetIqRef( long val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetIdRef()
AUTHOR:     Daniele Belloni
INFO:       Function used to get Id reference current
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     Id reference in IQ24
----------------------------------------------------------------------*/
long MotorModule::GetIdRef()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetIdRef( long val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set Id reference
INPUT:      val: value to assign to Id reference
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetIdRef( long val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int	GetEncoderType()
AUTHOR:     Daniele Belloni
INFO:       Function used to get encoder type
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     Encoder type
----------------------------------------------------------------------*/
int MotorModule::GetEncoderType()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetEncoderType( int type )
AUTHOR:     Daniele Belloni
INFO:       Function used to set encoder type
INPUT:      type: action
                     ROTATIVE_ENC:  rotative encoder
                     LINEAR_ENC:    linear encoder
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetEncoderType( int type )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int ElecThetaGeneration( int mode )
AUTHOR:     Daniele Belloni
INFO:       Function used to activate/deactivate the encoder's elec theta generation
INPUT:      mode: working mode 
				  ELECTTHETA_ON
				  ELECTTHETA_OFF
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::ElecThetaGeneration( int mode )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetMaxSpeed()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the motor's max speed
OUTPUT:     -
GLOBAL:     -
RETURN:     Motor max speed (RPM)
----------------------------------------------------------------------*/
int MotorModule::GetMaxSpeed()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetMaxSpeed( int spd )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor's max speed (in RPM)
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetMaxSpeed( int spd )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetRamps()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the acc/dec ramps mode (n.u.)
OUTPUT:     -
GLOBAL:     -
RETURN:     Motor acc/dec ramp mode
----------------------------------------------------------------------*/
int MotorModule::GetRamps()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetRamps( int mode )
AUTHOR:     Daniele Belloni
INFO:       Function used to activate/deactivate the acc/dec ramps (n.u.)
INPUT:      mode: working mode 
				  RAMP_ON 
				  RAMP_OFF
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetRamps( int mode )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long ActualStartStopVelocity()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the motor's actual setted start/stop velocity
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     Motor actual setted start/stop velocity, -1 if errors
----------------------------------------------------------------------*/
long MotorModule::ActualStartStopVelocity()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long ActualAceleration()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the motor aceleration.
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     aceleration (in m/s), -1 if errors
----------------------------------------------------------------------*/
long MotorModule::ActualAceleration()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long ActualDeceleration()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the motor deceleration.
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     deceleration (in m/s), -1 if errors
----------------------------------------------------------------------*/
long MotorModule::ActualDeceleration()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetActualPIDSpd( unsigned short set )
AUTHOR:     Daniele Belloni
INFO:       Function used to set actual speed PID
INPUT:      PID set id
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetActualPIDSpd( unsigned short set )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetActualPIDPos( unsigned short set )
AUTHOR:     Daniele Belloni
INFO:       Function used to set actual position PID
INPUT:      PID set id
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetActualPIDPos( unsigned short set )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int LoggerTriggerMode( int mode )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the trigger level
INPUT:      mode: working mode 
				  LOWTOHIGH_TRIG
				  HIGHTOLOW_TRIG
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::LoggerTriggerMode( int mode )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetEncoderActualPulses()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the encoder's counter register
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     Encoder actual counter register
----------------------------------------------------------------------*/
long MotorModule::GetEncoderActualPulses()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetPhaseCurrent( long val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set phase current (used during phases generation deactivation)
INPUT:      val: phase current value
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetPhaseCurrent( long val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetPhaseCurrent()
AUTHOR:     Daniele Belloni
INFO:       Function used to get phase current
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     phase current
----------------------------------------------------------------------*/
long MotorModule::GetPhaseCurrent()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetDecelerationAdvance()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the motor's deceleration advance
OUTPUT:     -
GLOBAL:     -
RETURN:     Motor's deceleration advance (%)
----------------------------------------------------------------------*/
int MotorModule::GetDecelerationAdvance()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetDecelerationAdvance( int val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor's deceleration advance (in %)
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetDecelerationAdvance( int val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetPulsesToMm()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the motor's encoder pulses to mm constant
OUTPUT:     -
GLOBAL:     -
RETURN:     Motor encoder pulses per revolution
----------------------------------------------------------------------*/
int MotorModule::GetPulsesToMm()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetPulsesToMm( int ptm )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor's encoder pulses to mm constant
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetPulsesToMm( int ptm )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int DecCompensationMode( int mode )
AUTHOR:     Daniele Belloni
INFO:       Function used to activate/deactivate the deceleration compensation mode
INPUT:      mode: working mode 
				  DECCOMP_ON
				  DECCOMP_OFF
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::DecCompensationMode( int mode )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetProximityGap( long val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set proximity gap
INPUT:      val: proximity value in p.u.
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetProximityGap( long val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetProximityGap()
AUTHOR:     Daniele Belloni
INFO:       Function used to get proximity gap
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     proximity gap in p.u.
----------------------------------------------------------------------*/
long MotorModule::GetProximityGap()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetPIDPosActivationGap( long val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set PID Pos activation gap
INPUT:      val: PID Pos activation gap value in p.u.
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetPIDPosActivationGap( long val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetPIDPosActivationGap()
AUTHOR:     Daniele Belloni
INFO:       Function used to get PID Pos activation gap
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     PID Pos activation gap in p.u.
----------------------------------------------------------------------*/
long MotorModule::GetPIDPosActivationGap()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetIParkAngle( long val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set iPark angle during calibration
INPUT:      val: iPark angle value in p.u.
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetIParkAngle( long val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetIParkAngle()
AUTHOR:     Daniele Belloni
INFO:       Function used to get iPark angle during calibration
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     iPark angle in p.u.
----------------------------------------------------------------------*/
long MotorModule::GetIParkAngle()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetDangerLimit( int limit )
AUTHOR:     Daniele Belloni
INFO:       Function used to get the danger limits
INPUT:      limit: action
                     LOW:  low danger limit
                     HIGH: high danger limit
OUTPUT:     -
GLOBAL:     -
RETURN:     Danger limits
----------------------------------------------------------------------*/
long MotorModule::GetDangerLimit( int limit )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetDangerLimit( int limit, long val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the danger limits
INPUT:      limit: action
                     LOW:  low danger limit
                     HIGH: high danger limit
		    val: value to assign to the selected limit
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetDangerLimit( int limit, long val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int DangerLimitMode( int mode )
AUTHOR:     Daniele Belloni
INFO:       Function used to activate/deactivate the danger limits
INPUT:      mode: working mode 
				  DANGERLIMIT_ON
				  DANGERLIMIT_OFF
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::DangerLimitMode( int mode )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int ResetEncoder()
AUTHOR:     Daniele Belloni
INFO:       Function used to reset the motor's encoder position
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::ResetEncoder()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int HomeSensorInput( int val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set motion controllers home sensor input
INPUT:      val: home sensor input
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::HomeSensorInput( int val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetHomingSpeed( int speed )
AUTHOR:     Daniele Belloni
INFO:       Function used to get homing speeds (fast and slow)
INPUT:      speed: action
                     HOME_SLOW: read homing slow speed
                     HOME_FAST: read homing fast speed
OUTPUT:     -
GLOBAL:     -
RETURN:     Homing speeds, -1 if errors
----------------------------------------------------------------------*/
long MotorModule::GetHomingSpeed( int speed )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetHomingSpeed( int speed, long val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set homing speeds (fast and slow)
INPUT:      speed: action
                     HOME_SLOW: read homing slow speed
                     HOME_FAST: read homing fast speed
		    val: speed value
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetHomingSpeed( int speed, long val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetOverSpeed()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the motor's speed overspeed percentage
OUTPUT:     -
GLOBAL:     -
RETURN:     Motor's speed overspeed (%)
----------------------------------------------------------------------*/
int MotorModule::GetOverSpeed()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetOverSpeed( int val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor's speed overspeed percentage
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetOverSpeed( int val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetReferenceActualPos()
AUTHOR:     Daniele Belloni
INFO:       Function used to set actual position as the reference one
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetReferenceActualPos()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int ResetPIDSpd()
AUTHOR:     Daniele Belloni
INFO:       Function used to reset speed PID output.
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::ResetPIDSpd()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int ResetPIDPos()
AUTHOR:     Daniele Belloni
INFO:       Function used to reset position PID output.
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::ResetPIDPos()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int PIDStatus()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the PIDs status
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     PIDs status, MOTOR_ERROR if errors
----------------------------------------------------------------------*/
int MotorModule::PIDStatus()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetMaxReadCurrent()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the board max read current
OUTPUT:     -
GLOBAL:     -
RETURN:     Board max current (mA), MOTOR_ERROR if errors
----------------------------------------------------------------------*/
int MotorModule::GetMaxReadCurrent()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetMaxReadCurrent( int val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the board max read current (mA)
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK if OK, MOTOR_ERROR if errors
----------------------------------------------------------------------*/
int MotorModule::SetMaxReadCurrent( int val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetPhaseC()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the phase C current
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     phase C current in IQ24, MOTOR_ERROR if errors
----------------------------------------------------------------------*/
long MotorModule::GetPhaseC()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetEncoder360ActualPosition()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the encoder's actual position in 360 degrees
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     Encoder actual position in IQ24, MOTOR_ERROR if errors
----------------------------------------------------------------------*/
long MotorModule::GetEncoder360ActualPosition()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetElecTheta()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the encoder's electrical theta
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     Encoder electrical theta in IQ24, MOTOR_ERROR if errors
----------------------------------------------------------------------*/
long MotorModule::GetElecTheta()
{
	return MOTOR_OK;
}

//----------------------------------------------------------------------
// FUNCTION:   GetAccFFWD
// INFO:       Function used to get the acc feed-forward
// RETURN:     acc feed-forward (IQ24) if OK, MOTOR_ERROR otherwise
//----------------------------------------------------------------------
long MotorModule::GetAccFFWD()
{
	return MOTOR_OK;
}

//----------------------------------------------------------------------
// FUNCTION:   SetAccFFWD
// INFO:       Function used to set the acc feed-forward
// INPUT:      val: acc feed-forward (IQ24)
// RETURN:     MOTOR_OK if OK, MOTOR_ERROR otherwise
//----------------------------------------------------------------------
int MotorModule::SetAccFFWD( long val )
{
	return MOTOR_OK;
}

//----------------------------------------------------------------------
// FUNCTION:   GetSpdFFWD
// INFO:       Function used to get the speed feed-forward
// RETURN:     speed feed-forward (IQ24) if OK, MOTOR_ERROR otherwise
//----------------------------------------------------------------------
long MotorModule::GetSpdFFWD()
{
	return MOTOR_OK;
}

//----------------------------------------------------------------------
// FUNCTION:   SetSpdFFWD
// INFO:       Function used to set the speed feed-forward
// INPUT:      val: speed feed-forward (IQ24)
// RETURN:     MOTOR_OK if OK, MOTOR_ERROR otherwise
//----------------------------------------------------------------------
int MotorModule::SetSpdFFWD( long val )
{
	return MOTOR_OK;
}

//----------------------------------------------------------------------
// FUNCTION:   GetMaxJerk
// INFO:       Function used to get the maximum jerk
// RETURN:     maximum jerk if OK, MOTOR_ERROR otherwise
//----------------------------------------------------------------------
int MotorModule::GetMaxJerk()
{
	return MOTOR_OK;
}

//----------------------------------------------------------------------
// FUNCTION:   SetMaxJerk
// INFO:       Function used to set the maximum jerk
// INPUT:      val: maximum jerk
// RETURN:     MOTOR_OK if OK, MOTOR_ERROR otherwise
//----------------------------------------------------------------------
int MotorModule::SetMaxJerk( int val )
{
	return MOTOR_OK;
}


//----------------------------------------------------------------------
// FUNCTION:   GetCFriction
// INFO:       Function used to get Coulomb friction constant
// RETURN:     Coulomb friction constant (IQ24) if OK, MOTOR_ERROR otherwise
//----------------------------------------------------------------------
long MotorModule::GetCFriction()
{
	return MOTOR_OK;
}

//----------------------------------------------------------------------
// FUNCTION:   SetCFriction
// INFO:       Function used to set Coulomb friction constant
// INPUT:      val: Coulomb friction constant (IQ24)
// RETURN:     MOTOR_OK if OK, MOTOR_ERROR otherwise
//----------------------------------------------------------------------
int MotorModule::SetCFriction( long val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetEndMovementSpeed()
AUTHOR:     Daniele Belloni
INFO:       Function used to get the speed for end movement
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     speed in m/s IQ24 if OK, MOTOR_ERROR if errors
----------------------------------------------------------------------*/
long MotorModule::GetEndMovementSpeed()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetEndMovementSpeed( long val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the speed for end movement
INPUT:      val: speed in m/s IQ24
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK if OK, MOTOR_ERROR if errors
----------------------------------------------------------------------*/
int MotorModule::SetEndMovementSpeed( long val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetEndMovementDelta()
AUTHOR:     Daniele Belloni
INFO:       Function used to get the encoder delta for end movement
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     delta in pulses if OK, MOTOR_ERROR if errors
----------------------------------------------------------------------*/
long MotorModule::GetEndMovementDelta()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetEndMovementDelta( long val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the encoder delta for end movement
INPUT:      val: delta in pulses
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK if OK, MOTOR_ERROR if errors
----------------------------------------------------------------------*/
int MotorModule::SetEndMovementDelta( long val )
{
	return MOTOR_OK;
}

//----------------------------------------------------------------------
// FUNCTION:   GotoPos0_Multi
// INFO:       Function used to move multiple motors (absolute motion)
//             with specified speed/acc
// INPUT:      addX, posX: address and absolute position for each motor
//             maxFreq: movement speed
//             acc: movement acceleration
//             posXnorm: X normalized position (double encoder)
// RETURN:     MOTOR_OK if OK, MOTOR_ERROR otherwise
//----------------------------------------------------------------------
int MotorModule::GotoPos0_Multi( unsigned char addX, long posX, unsigned char addY, long posY, long maxFreq, long acc, long proximityDeltaX, long proximityDeltaY )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int ResetFlag_Multi()
AUTHOR:     Daniele Belloni
INFO:       Function used to reset multiple motors command flag
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK if OK, MOTOR_ERROR if errors
----------------------------------------------------------------------*/
int MotorModule::ResetFlag_Multi()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetEncoder2ActualPosition()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the encoder's actual position
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     Encoder actual position in IQ24
----------------------------------------------------------------------*/
long MotorModule::GetEncoder2ActualPosition()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetEncoder2ActualPulses()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the encoder's counter register
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     Encoder actual counter register
----------------------------------------------------------------------*/
long MotorModule::GetEncoder2ActualPulses()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetLineEncoder2()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the motor's encoder line number
OUTPUT:     -
GLOBAL:     -
RETURN:     Motor line encoder
----------------------------------------------------------------------*/
long MotorModule::GetLineEncoder2()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetLineEncoder2( long lines )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor's encoder line number
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetLineEncoder2( long lines )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetEncoderInterpActualPosition()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the encoder's actual position
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     Encoder actual position in IQ24
----------------------------------------------------------------------*/
long MotorModule::GetEncoderInterpActualPosition()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetStatus_ResetFlagMulti()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the motor's status and reset multimove flag
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     Motor status, -1 if errors
----------------------------------------------------------------------*/
int MotorModule::GetStatus_ResetFlagMulti()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetFollowingError( long val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set following error
INPUT:      val: following error value in p.u.
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetFollowingError( long val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetFollowingError()
AUTHOR:     Daniele Belloni
INFO:       Function used to get following error
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     following error in p.u.
----------------------------------------------------------------------*/
long MotorModule::GetFollowingError()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int EncoderStatus()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the encoder status
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     encoder status, MOTOR_ERROR if errors
----------------------------------------------------------------------*/
int MotorModule::EncoderStatus()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetStartTicks( int ticks )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the start ticks
INPUT:      ticks: start ticks
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetStartTicks( int ticks )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetPhaseRotation( int value )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the phase rotation
INPUT:      value: phase rotation
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetPhaseRotation( int value )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetPhaseRotationNumber( int value )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the phase rotation number
INPUT:      value: phase rotation number
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetPhaseRotationNumber( int value )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetSpeedFilter( unsigned short window )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the speed filter window
INPUT:      window: speed filter window in ms
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetSpeedFilter( unsigned short window )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetSecurityCheck( int limit, int limitLevel )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor security check.
INPUT:      limitLevel: Set security check level high or low (SECURITYLEVEL_HIGH,
                        SECURITYLEVEL_LOW)
            limit: Activate or deactivate security check (SECURITYCHECK_ON,
                   SECURITYCHECK_OFF)
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetSecurityCheck( int limit, int limitLevel )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetSecurityInput( int val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the security check input
INPUT:      val:
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetSecurityInput( int val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetVPower()
AUTHOR:     Daniele Belloni
INFO:       Function used to get the supplied voltage
RETURN:     voltage if OK, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
long MotorModule::GetVPower()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetSteadyPosFollowError( long val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the following error when motor is stopped
INPUT:      val: error in IQ24
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetSteadyPosFollowError( long val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetSteadyPosFollowError()
AUTHOR:     Daniele Belloni
INFO:       Function used to get the following error when motor is stopped
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     error in IQ24
----------------------------------------------------------------------*/
long MotorModule::GetSteadyPosFollowError()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetEncoderSpykeDelta( int delta )
AUTHOR:     Daniele Belloni
INFO:       Function used to set encoder spyke delta
INPUT:      delta: delta in pulses
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetEncoderSpykeDelta( int delta )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetEncoderSpykeDelta()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the encoder spyke delta
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     delta in pulses
----------------------------------------------------------------------*/
int MotorModule::GetEncoderSpykeDelta()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetSpeedProfile( int mode )
AUTHOR:     Daniele Belloni
INFO:       Function used to set speed profile
INPUT:      mode: profile type
				FIFTHDEGREE_PROFILE
				TRAPEZOIDAL_PROFILE
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetSpeedProfile( int mode )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetTemperature()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the micro temperature
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     Temperature
----------------------------------------------------------------------*/
int MotorModule::GetTemperature()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int UpdateOverSpeed()
AUTHOR:     Daniele Belloni
INFO:       Function used to update the overspeed check value
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::UpdateOverSpeed()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int OverSpeedCheck( int enable )
AUTHOR:     Daniele Belloni
INFO:       Function used to Enable/disable the overspeed check
INPUT:      enable: activate/deactivate overspeed check
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::OverSpeedCheck( int enable )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetHomeSensorLevel( int level )
AUTHOR:     Daniele Belloni
INFO:       Function used to set home sensor level
INPUT:      level: zero sensor check level
				ZEROLEVEL_HIGH
				ZEROLEVEL_LOW
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetHomeSensorLevel( int level )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int ResetSpeed()
AUTHOR:     Daniele Belloni
INFO:       Function used to reset speed module
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::ResetSpeed()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetOutputDivider( int outId, int divider )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the driver's digital outputs dividers
INPUT:      outId: Output id (OUT0, OUT1, OUT2)
            divider: Divider val (1, 2, 4)
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetOutputDivider( int outId, int divider )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetOutputDivider( int outId )
AUTHOR:     Daniele Belloni
INFO:       Function used to get the driver's digital outputs dividers
INPUT:      outId: Output id (OUT0, OUT1, OUT2)
OUTPUT:     -
GLOBAL:     -
RETURN:     Output divider on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::GetOutputDivider( int outId )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetOutputReductionTime( int outId, int time )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the driver's digital outputs reduction time
INPUT:      outId: Output id (OUT0, OUT1, OUT2)
            time: Reduction time in ms
OUTPUT:     -
GLOBAL:     -
RETURN:     MOTOR_OK on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::SetOutputReductionTime( int outId, int time )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetOutputReductionTime( int outId )
AUTHOR:     Daniele Belloni
INFO:       Function used to get the driver's digital outputs dividers reduction time
INPUT:      outId: Output id (OUT0, OUT1, OUT2)
OUTPUT:     -
GLOBAL:     -
RETURN:     Reduction time on success, MOTOR_ERROR otherwise
----------------------------------------------------------------------*/
int MotorModule::GetOutputReductionTime( int outId )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long SetHomeMove()
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor's homing movement
OUTPUT:     -
GLOBAL:     -
RETURN:
----------------------------------------------------------------------*/
int MotorModule::SetHomeMove( long val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   long GetHomeMove()
AUTHOR:     Daniele Belloni
INFO:       Function used to read the motor's homing movement
OUTPUT:     -
GLOBAL:     -
RETURN:     Motor homing movement in steps
----------------------------------------------------------------------*/
long MotorModule::GetHomeMove()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int MultiMotorMode(int mode)
AUTHOR:     Daniele Belloni
INFO:       Function used to enable multimotor mode
INPUT:      mode
OUTPUT:     -
GLOBAL:     -
RETURN:     0 OK, 1 if errors
----------------------------------------------------------------------*/
int MotorModule::MultiMotorMode(int mode)
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetHomeTimeout( long val )
AUTHOR:     Daniele Belloni
INFO:       Function used to set the motor's homing timeout
OUTPUT:     -
GLOBAL:     -
RETURN:
----------------------------------------------------------------------*/
int MotorModule::SetHomeTimeout( long val )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int StartRotation( int msec )
AUTHOR:     Daniele Belloni
INFO:       Function used to start brush motor rotation
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     0 OK, 1 if errors
----------------------------------------------------------------------*/
int MotorModule::StartRotation( int msec )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetDuration( int msec )
AUTHOR:     Daniele Belloni
INFO:       Function used to set rotation duration in msec
INPUT:      msec
OUTPUT:     -
GLOBAL:     -
RETURN:     0 OK, 1 if errors
----------------------------------------------------------------------*/
int MotorModule::SetDuration( int msec )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetDuration()
AUTHOR:     Daniele Belloni
INFO:       Function used to get rotation duration in msec
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     0 OK, 1 if errors
----------------------------------------------------------------------*/
int MotorModule::GetDuration()
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int SetDirection( int dir )
AUTHOR:     Daniele Belloni
INFO:       Function used to set rotation direction (CW/CCW)
INPUT:      dir
OUTPUT:     -
GLOBAL:     -
RETURN:     0 OK, 1 if errors
----------------------------------------------------------------------*/
int MotorModule::SetDirection( int dir )
{
	return MOTOR_OK;
}

/*----------------------------------------------------------------------
FUNCTION:   int GetDirection()
AUTHOR:     Daniele Belloni
INFO:       Function used to get rotation direction
INPUT:      -
OUTPUT:     -
GLOBAL:     -
RETURN:     0 OK, 1 if errors
----------------------------------------------------------------------*/
int MotorModule::GetDirection()
{
	return MOTOR_OK;
}

int  MotorModule::SetOutputPulseTime(int outId, int msec){
	return MOTOR_OK;
}
int  MotorModule::SetOutputPulseMode(int outId, int mode){
	return MOTOR_OK;
}



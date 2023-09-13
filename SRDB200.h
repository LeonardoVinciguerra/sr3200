//---------------------------------------------------------------------------
//
// Name:        SRDatabase.h
// Author:      Daniele Belloni
// Created:     22/11/2013
// Description: SRDatabase Struct declaration
//
//---------------------------------------------------------------------------
#ifndef __SRDB200_H
#define __SRDB200_H

#include <wx/string.h>


	//------------//
	// DB Structs //
	//------------//

struct WorkingModesStruct_201
{
	int IdProd;
	int FiducialSearch;
	int DebugMode;
	int DoublePlate;
	int DoublePlateEn;
	int DoubleSqueegees;
	int PrintingVerify;
	int FiducialOnFrame;
	int SqueegeesSpeed;
	int PrintingVerifyAuto;
	int PrintingVerifyTime;
	int SPIStopsWhenFaulty;
	int DifferentialDisengage;
	double DisengageSpeed;
	int SqueegeesSpeedValue;	// speed in mm/sec
	int LoaderEn;
	int InspectionType;			// 0 = Operator, 1 = SPI
	int VerifyON;			//0= do not check solder 1=check solder
	int CleaningEn;
	double CleaningEngageDistance;
	double PistonLoadingDeltaX;
	double PistonLoadingDeltaY;
	int InputSensorEnabled;
	int AntiReflectsEn;
};

struct MachineParamsStruct_200
{
	float PlateZeroMovement;
	float CameraFocus;
	double UpXPixMm;
	double UpYPixMm;
	double DnXPixMm;
	double DnYPixMm;
	float TableZeroMovement1;
	float TableZeroMovement2;
	float TableZeroMovement3;
	float PlateMovement;
	float SqueegeesDefZeroMove;
	int Counter;
	wxString Version;
	int FPS;
	int CameraSpeed;
	int TableSpeed;
	int ImageFlip;
	double OffsetPointsStartX;
	double OffsetPointsStartY;
	float OffsetPointsDistance;
	int OffsetPointsNumX;
	int OffsetPointsNumY;
	int PlateUpSpeed;
	int PlateDownSpeed;
	int InputSensorMode; //n.u.
	int AutoVacuumMode;
	int ConvWidthSpeed;
	int ConvFeedSpeed;
	int ConvPushSpeed;
	int LoaderSpeed;
	float LConvZeroMovement;
	float CConvZeroMovement;
	float RConvZeroMovement;
	float LoaderZeroMovement;
	float LConvMovement;
	float CConvMovement;
	float RConvMovement;
	int ConveyorMode;
	double ConvEdgeX;
	double ConvEdgeY;
	float LoaderAdjPosition;
	double CamPistonDeltaX;
	double CamPistonDeltaY;
	int LoaderInstalled;
	double LoaderDefPitch;
	int LedLightReduced;
	int CleaningInstalled;
	int CleaningActivationTime;
	int CleaningDoubleFeed;
	int CleaningVacuumOn;
	double CleaningCameraDelta;
	wxString SPIAlarmColor;
	wxString SPIShortColor;
	wxString SPIWarningColor;
	int BeeperEn;
};

struct MotorParamsStruct_200
{
	int Id;
	int Address;
	int MinCurrent;
	int AccCurrent;
	int MaxCurrent;
	int Microstepping;
	float Pulley;
	float Reduction;
	int Driver;
	int Current;
	float KP_speed;
	float KI_speed;
	float KP_pos;
	long LineEnc;
	int PulsesToMm;
	int Poles;
	int Jerk;
	float KA;
	float KS;
	float KC;
	float HomeFast;
	float HomeSlow;
	int PPR;
	int Profile;
	float EndMovementDelta;
	int SpykeDelta;
	int RedCurrent;
	int Direction;
};

struct MotorParamsStruct_202
{
	int Id;
	int Address;
	int MinCurrent;
	int AccCurrent;
	int MaxCurrent;
	int Microstepping;
	float Pulley;
	float Reduction;
	int Driver;
	int Current;
	float KP_speed;
	float KI_speed;
	float KP_pos;
	long LineEnc;
	int PulsesToMm;
	int Poles;
	int Jerk;
	float KA;
	float KS;
	float KC;
	float HomeFast;
	float HomeSlow;
	int PPR;
	int Profile;
	float EndMovementDelta;
	int SpykeDelta;
	int RedCurrent;
	int Direction;
	int EncoderType;
	int EncoderMode;
};

#endif

//---------------------------------------------------------------------------
//
// Name:        SRDatabase.h
// Author:      Daniele Belloni
// Created:     22/11/2013
// Description: SRDatabase Struct declaration
//
//---------------------------------------------------------------------------
#ifndef __SRDB101_H
#define __SRDB101_H

#include <wx/string.h>


	//------------//
	// DB Structs //
	//------------//

struct WorkingModesStruct_101
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
	int DisengageSpeed;
	float DisengageMovement;
	int SqueegeesSpeedValue;	// speed in mm/sec
	int LoaderEn;
	int InspectionType;			// 0 = Operator, 1 = SPI
	int VerifyON;			//0= do not check solder 1=check solder
	int CleaningEn;
	double CleaningEngageDistance;
};

struct MachineParamsStruct_101
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
	wxString SPIAlarmColor;
	wxString SPIShortColor;
	wxString SPIWarningColor;
};

struct MotorParamsStruct_101
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

#endif

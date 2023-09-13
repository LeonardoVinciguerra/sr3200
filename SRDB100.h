//---------------------------------------------------------------------------
//
// Name:        SRDatabase.h
// Author:      Daniele Belloni
// Created:     22/11/2013
// Description: SRDatabase Struct declaration
//
//---------------------------------------------------------------------------
#ifndef __SRDB100_H
#define __SRDB100_H

#include <wx/string.h>


	//------------//
	// DB Structs //
	//------------//

struct ActualProductionStruct_100
{
	int IdProd;
};

struct ProductionDataStruct_100
{
	wxString ProductionName;
	int IdProd;
	float PCBHeight;
	float PCBX;
	float PCBY;
	double SqueegeesMove;
	double SqueegeesZeroMove;
	float CorrectionX;
	float CorrectionY;
	float DeltaYFrontRear;
	float CorrectionTheta;
	int Counter;
	float PlateMovementDelta;
	wxString Notes;
	wxString Notes1;
	wxString Notes2;
	float SqueegeesRecoveryFront;
	float SqueegeesRecoveryRear;
	double PCBPosX;
	double PCBPosY;
	double LoaderTrayPitch;
	double LoaderStartPos;
	int LoaderBoardNumber;
	int TopGerberOn;
	int BotGerberOn;
	double TopGerberRot;
	double BotGerberRot;
	int TopGerberFlip;
	int BotGerberFlip;
	int TopGerberSolder;
	int TopGerberPads;
	int TopGerberMech;
	int BotGerberSolder;
	int BotGerberPads; //n.u.
	int BotGerberMech;
	int PinsPointsNumber;
	double LastRot;
	double LastX;
	double LastY;
};

struct FiducialParamsStruct_100
{
	int Id;
	int IdProd;
	double Y;
	double X;
	double DeltaX;
	double DeltaY;
	int FilterSmoothType;
	int FilterSmoothDim;
	int FilterEdgeThr;
	int SearchMode;			// see SearchModeEnum in GlobalEnum.h
	float SearchAreaMul;
	int CircleAccum;
	int CircleDiameter;
	int RectangleAccum;
	int RectangleSideX;
	int RectangleSideY;
	int Tolerance;
	int Type;
	int TemplateDim;		// volatile - not in DB
	float TemplateThr;
	float CameraBrightness;
	float CameraContrast;
};

struct WorkingModesStruct_100
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
	int DifferentialDisengage;
	int DisengageSpeed;
	float DisengageMovement;
	int SqueegeesSpeedValue;	// speed in mm/sec
	int LoaderEn;
};

struct VerifyPointsStruct_100
{
	int Id;
	int IdProd;
	double X;
	double Y;
};

struct PinsPointsStruct_100
{
	int Id;
	int IdProd;
	double X;
	double Y;
};

struct SpeedTableStruct_100
{
	int Id;
	int Speed[3];
	int Acc[3];
	int Dec[3];
};

struct LimitsStruct_100
{
	int Id;
	float MinLimit;
	float MaxLimit;
};

struct SerialParamsStruct_100
{
	int Id;
	wxString SerialPort;
	int SerialSpeed;
};

struct IOParamsStruct_100
{
	int Id;
	int Type;
	int DriverId;
	int DriverPort;
};

struct MotorParamsStruct_100
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
};

struct MachineParamsStruct_100
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
};

struct OffsetPointsStruct_100
{
	int Id;
	float X;
	float Y;
};

struct OffsetCheckPointsStruct_100
{
	int Id;
	float X;
	float Y;
};

#endif

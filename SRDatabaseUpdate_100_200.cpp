//---------------------------------------------------------------------------
//
// Name:        SRDatabase.cpp
// Author:      Gabriel Ferri
// Created:     11/04/2008
// Description: SRDatabase class implementation
//
//---------------------------------------------------------------------------

// COME ESEMPIO!!!!!!

#include "SRDatabase.h"
#include <wx/wxsqlite3.h>
#include <wx/msgdlg.h>

//#include "SRDB100.h"

#define OFFSET_POINTS_DISTANCE	28.0f
#define OFFSET_POINTS_X			13
#define OFFSET_POINTS_Y			15
#define OFFSET_POINTS_101		195
#define NUM_VERIFY_POINTS		10
#define DEFAULT_DISENGAGE_SPEED	50.0


//----------------------------------------------------------------------------------
// From_100_to_200
// 
//----------------------------------------------------------------------------------

int SRDatabase::From_100_to_200( const char *new_db_file )
{
	wxSQLite3Database new_db;
	wxSQLite3ResultSet q;
	wxSQLite3StatementBuffer stmtBuffer;
	try
	{
		cout<<"Path del DB: "<<new_db_file <<endl;
		new_db.Open( wxString::Format( "%s", new_db_file ) );
		if(!new_db.IsOpen()){
			cout<<"Non Sono riuscito ad aprire il db!"<<endl;
		}

		// ActualProduction
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM ActualProduction") );
		new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO ActualProduction VALUES ( %d )", q.GetInt("IdProd")) );
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (ActualProduction)", wxOK );
		cout<<" DB Update (ActualProduction) ERROR!: "<< exc.GetMessage() <<endl;
		return 1;
	}

	try
		{

		//fiducialPrams
		FiducialParamsStruct_100 FiducialParamsS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM FiducialParams"));
		while( q.NextRow() ){
			FiducialParamsS.CameraBrightness  = q.GetDouble( wxT("CameraBrightness") );
			FiducialParamsS.CameraContrast  = q.GetDouble( wxT("CameraContrast") );
			FiducialParamsS.CircleAccum  = q.GetInt( wxT("CircleAccum") );
			FiducialParamsS.CircleDiameter  = q.GetInt( wxT("CircleDiameter") );
			FiducialParamsS.DeltaX  = q.GetDouble( wxT("DeltaX") );
			FiducialParamsS.DeltaY  = q.GetDouble( wxT("DeltaY") );
			FiducialParamsS.FilterEdgeThr  = q.GetInt( wxT("FilterEdgeThr") );
			FiducialParamsS.FilterSmoothDim  = q.GetInt( wxT("FilterSmoothDim") );
			FiducialParamsS.FilterSmoothType  = q.GetInt( wxT("FilterSmoothType") );
			FiducialParamsS.Id  = q.GetInt( wxT("Id") );
			FiducialParamsS.IdProd  = q.GetInt( wxT("IdProd") );
			FiducialParamsS.RectangleAccum  = q.GetInt( wxT("RectangleAccum") );
			FiducialParamsS.RectangleSideX  = q.GetInt( wxT("RectangleSideX") );
			FiducialParamsS.RectangleSideY  = q.GetInt( wxT("RectangleSideY") );
			FiducialParamsS.SearchAreaMul  = q.GetDouble( wxT("SearchAreaMul") );
			FiducialParamsS.SearchMode  = q.GetInt( wxT("SearchMode") );
			//FiducialParamsS.TemplateDim  = q.GetInt( wxT("TemplateDim") ); tolto
			FiducialParamsS.TemplateThr  = q.GetDouble( wxT("TemplateThr") );
			FiducialParamsS.Tolerance  = q.GetInt( wxT("Tolerance") );
			FiducialParamsS.Type  = q.GetInt( wxT("Type") );
			FiducialParamsS.X  = q.GetDouble( wxT("X") );
			FiducialParamsS.Y  = q.GetDouble( wxT("Y") );
			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO FiducialParams VALUES ( %d, %d, %f, %f, %f, %f, %d, %d, %d, %d, %f, %d, %d, %d, %d, %d, %d, %d, %f, %f, %f  )",
					FiducialParamsS.Id,
					FiducialParamsS.IdProd,
					FiducialParamsS.X,
					FiducialParamsS.Y,
					FiducialParamsS.DeltaX,
					FiducialParamsS.DeltaY,
					FiducialParamsS.FilterSmoothType,
					FiducialParamsS.FilterSmoothDim,
					FiducialParamsS.FilterEdgeThr,
					FiducialParamsS.SearchMode,
					FiducialParamsS.SearchAreaMul,
					FiducialParamsS.CircleAccum,
					FiducialParamsS.CircleDiameter,
					FiducialParamsS.RectangleAccum,
					FiducialParamsS.RectangleSideX,
					FiducialParamsS.RectangleSideY,
					FiducialParamsS.Tolerance,
					FiducialParamsS.Type,
					FiducialParamsS.TemplateThr,
					FiducialParamsS.CameraBrightness,
					FiducialParamsS.CameraContrast
					)
				);
		}
		//add The Cam Zero fiducial
		new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO FiducialParams VALUES ( %d, %d, %f, %f, %f, %f, %d, %d, %d, %d, %f, %d, %d, %d, %d, %d, %d, %d, %f, %f, %f  )",
							FiducialParamsS.Id+1,
							-1,//FiducialParamsS.IdProd,
							-268.86,//FiducialParamsS.X,
							-512.69,//FiducialParamsS.Y,
							0.0,//FiducialParamsS.DeltaX,
							0.0,//FiducialParamsS.DeltaY,
							1,//FiducialParamsS.FilterSmoothType,
							15,//FiducialParamsS.FilterSmoothDim,
							57,//FiducialParamsS.FilterEdgeThr,
							0,//FiducialParamsS.SearchMode,
							2.0,//FiducialParamsS.SearchAreaMul,
							10,//FiducialParamsS.CircleAccum,
							266,//FiducialParamsS.CircleDiameter,
							25,//FiducialParamsS.RectangleAccum,
							60,//FiducialParamsS.RectangleSideX,
							60,//FiducialParamsS.RectangleSideY,
							5,//FiducialParamsS.Tolerance,
							10,//FiducialParamsS.Type,
							75.0,//FiducialParamsS.TemplateThr,
							0.5,//FiducialParamsS.CameraBrightness,
							0.5//FiducialParamsS.CameraContrast
							)
						);
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (FiducialParams)", wxOK );
		cout<<" DB Update (FiducialParams) ERROR!: "<< exc.GetMessage() <<endl;
		return 1;
	}

	try
		{


		// IOParams
		IOParamsStruct_100 IOParamsS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM IOParams") );

		while( q.NextRow() )
		{
			IOParamsS.Id			= q.GetInt( wxT("Id") );
			IOParamsS.Type			= q.GetInt( wxT("Type") );
			IOParamsS.DriverId		= q.GetInt( wxT("DriverId") );
			IOParamsS.DriverPort	= q.GetInt( wxT("DriverPort") );

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO IOParams VALUES ( %d, %d, %d, %d )",
				IOParamsS.Id,
				IOParamsS.Type,
				IOParamsS.DriverId,
				IOParamsS.DriverPort) );
		}
		//Inserire anche altre 4 uscite, relative a cleaningVacuum, SemaphoreYellow, CleaningActivate
		new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO IOParams VALUES ( %d, %d, %d, %d )",
						OUTPUT_CLEANINGVACUUM,
						1,
						5,
						0) );

		new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO IOParams VALUES ( %d, %d, %d, %d )",
						OUTPUT_SEMAPHORE_YELLOW,
						1,
						6,
						2) );
		new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO IOParams VALUES ( %d, %d, %d, %d )",
						OUTPUT_CLEANINGACTIVATE,
						1,
						13,
						1) );

	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (IOParams)", wxOK );
		cout<<" DB Update (IOParams) ERROR!: "<< exc.GetMessage() <<endl;
		return 1;
	}

	try
	{

		// Limits
		LimitsStruct_100 LimitsS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM Limits") );

		while( q.NextRow() )
		{
			LimitsS.Id			= q.GetInt( wxT("Id") );
			LimitsS.MinLimit	= q.GetDouble( wxT("Min") );
			LimitsS.MaxLimit	= q.GetDouble( wxT("Max") );

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO Limits VALUES ( %d, %f, %f )",
				LimitsS.Id,
				LimitsS.MinLimit,
				LimitsS.MaxLimit) );
		}
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (Limits)", wxOK );
		cout<<" DB Update (Limits) ERROR!: "<< exc.GetMessage() <<endl;
		return 1;
	}

	try
	{

		// MachineParams
		MachineParamsStruct_100 MachineParamsS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM MachineParams") );

		while( q.NextRow() )
		{
			//id=0
			MachineParamsS.PlateZeroMovement	= q.GetDouble( wxT("PlateZeroMovement") );
			MachineParamsS.CameraFocus	= q.GetDouble( wxT("CameraFocus") );
			MachineParamsS.UpXPixMm	= q.GetDouble( wxT("UpXPixMm") );
			MachineParamsS.UpYPixMm	= q.GetDouble( wxT("UpYPixMm") );
			MachineParamsS.DnXPixMm	= q.GetDouble( wxT("DnXPixMm") );
			MachineParamsS.DnYPixMm	= q.GetDouble( wxT("DnYPixMm") );
			MachineParamsS.TableZeroMovement1	= q.GetDouble( wxT("TableZeroMovement1") );
			MachineParamsS.TableZeroMovement2	= q.GetDouble( wxT("TableZeroMovement2") );
			MachineParamsS.TableZeroMovement3	= q.GetDouble( wxT("TableZeroMovement3") );

			MachineParamsS.PlateMovement	= q.GetDouble( wxT("PlateMovement") );
			MachineParamsS.SqueegeesDefZeroMove	= q.GetDouble( wxT("SqueegeesDefZeroMove") );
			MachineParamsS.Counter	= q.GetInt( wxT("Counter") );
			MachineParamsS.Version	= "2.00";
			MachineParamsS.FPS	= q.GetInt( wxT("FPS") );
			MachineParamsS.CameraSpeed	= q.GetInt( wxT("CameraSpeed") );
			MachineParamsS.TableSpeed	= q.GetInt( wxT("TableSpeed") );
			MachineParamsS.ImageFlip	= q.GetInt( wxT("ImageFlip") );
			MachineParamsS.OffsetPointsStartX	= q.GetDouble( wxT("OffsetPointsStartX") );
			MachineParamsS.OffsetPointsStartY	= q.GetDouble( wxT("OffsetPointsStartY") );

			MachineParamsS.OffsetPointsDistance	= q.GetDouble( wxT("OffsetPointsDistance") );
			MachineParamsS.OffsetPointsNumX	= q.GetInt( wxT("OffsetPointsNumX") );
			MachineParamsS.OffsetPointsNumY	= q.GetInt( wxT("OffsetPointsNumY") );
			MachineParamsS.PlateUpSpeed	= q.GetInt( wxT("PlateUpSpeed") );
			MachineParamsS.PlateDownSpeed	= q.GetInt( wxT("PlateDownSpeed") );
			MachineParamsS.InputSensorMode	= q.GetInt( wxT("InputSensorMode") );
			MachineParamsS.AutoVacuumMode	= q.GetInt( wxT("AutoVacuumMode") );
			MachineParamsS.ConvWidthSpeed	= q.GetInt( wxT("ConvWidthSpeed") );
			MachineParamsS.ConvFeedSpeed	= q.GetInt( wxT("ConvFeedSpeed") );
			MachineParamsS.LoaderSpeed	= q.GetInt( wxT("LoaderSpeed") );

			MachineParamsS.LConvZeroMovement	= q.GetDouble( wxT("LConvZeroMovement") );
			MachineParamsS.CConvZeroMovement	= q.GetDouble( wxT("CConvZeroMovement") );
			MachineParamsS.RConvZeroMovement	= q.GetDouble( wxT("RConvZeroMovement") );
			MachineParamsS.LoaderZeroMovement	= q.GetDouble( wxT("LoaderZeroMovement") );
			MachineParamsS.LConvMovement	= q.GetDouble( wxT("LConvMovement") );
			MachineParamsS.CConvMovement	= q.GetDouble( wxT("CConvMovement") );
			MachineParamsS.RConvMovement	= q.GetDouble( wxT("RConvMovement") );
			MachineParamsS.ConveyorMode	= q.GetInt( wxT("ConveyorMode") );
			MachineParamsS.ConvEdgeX	= q.GetDouble( wxT("ConvEdgeX") );
			MachineParamsS.ConvEdgeY	= q.GetDouble( wxT("ConvEdgeY") );

			MachineParamsS.LoaderAdjPosition = q.GetDouble( wxT("LoaderAdjPosition") );
			MachineParamsS.CamPistonDeltaX	= q.GetDouble( wxT("CamPistonDeltaX") );
			MachineParamsS.CamPistonDeltaY	= q.GetDouble( wxT("CamPistonDeltaY") );
			MachineParamsS.LoaderInstalled	= q.GetInt( wxT("LoaderInstalled") );
			MachineParamsS.LoaderDefPitch	= q.GetDouble( wxT("LoaderDefPitch") );
			MachineParamsS.LedLightReduced	= q.GetInt( wxT("LedLightReduced") );
			//0 //cleaning_installed
			//0 //cleaning_ActTime
			//0 //cleaning_DoubleFeed
			//0 //cleaning_Vacuum on
			//0 //cleaning_Camera_Delta

			//""	//spiAlarmColor
			//""	//spiWarningColor
			//""	//spiShortColor


			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO machineparams VALUES ( %d, %f, %f, %f, %f, %f, %f, %f, %f, %f,   "
					"																   %f, %f, %d, '%s', %d, %d, %d, %d, %f, %f,	"
					"																   %f, %d, %d, %d, %d, %d, %d, %d, %d, %d, "
					"																   %f, %f, %f, %f, %f, %f, %f, %d, %f, %f, "
					"																   %f, %f, %f, %d, %f, %d, %d, %d, %d, %d, "
					"																   %f, '%s', '%s', '%s', %d)",
					0, //ID
					MachineParamsS.PlateZeroMovement,
					MachineParamsS.CameraFocus,
					MachineParamsS.UpXPixMm,
					MachineParamsS.UpYPixMm,
					MachineParamsS.DnXPixMm,
					MachineParamsS.DnYPixMm,
					MachineParamsS.TableZeroMovement1,
					MachineParamsS.TableZeroMovement2,
					MachineParamsS.TableZeroMovement3,

					MachineParamsS.PlateMovement,
					MachineParamsS.SqueegeesDefZeroMove,
					MachineParamsS.Counter,
					MachineParamsS.Version.ToAscii(),
					MachineParamsS.FPS,
					MachineParamsS.CameraSpeed,
					MachineParamsS.TableSpeed,
					MachineParamsS.ImageFlip,
					MachineParamsS.OffsetPointsStartX,
					MachineParamsS.OffsetPointsStartY,

					MachineParamsS.OffsetPointsDistance,
					MachineParamsS.OffsetPointsNumX,
					MachineParamsS.OffsetPointsNumY,
					MachineParamsS.PlateUpSpeed,
					MachineParamsS.PlateDownSpeed,
					MachineParamsS.InputSensorMode,
					MachineParamsS.AutoVacuumMode,
					MachineParamsS.ConvWidthSpeed,
					MachineParamsS.ConvFeedSpeed,
					MachineParamsS.LoaderSpeed,

					MachineParamsS.LConvZeroMovement,
					MachineParamsS.CConvZeroMovement,
					MachineParamsS.RConvZeroMovement,
					MachineParamsS.LoaderZeroMovement,
					MachineParamsS.LConvMovement,
					MachineParamsS.CConvMovement,
					MachineParamsS.RConvMovement,
					MachineParamsS.ConveyorMode,
					MachineParamsS.ConvEdgeX,
					MachineParamsS.ConvEdgeY,

					MachineParamsS.LoaderAdjPosition,
					MachineParamsS.CamPistonDeltaX,
					MachineParamsS.CamPistonDeltaY,
					MachineParamsS.LoaderInstalled,
					MachineParamsS.LoaderDefPitch,
					MachineParamsS.LedLightReduced,
					0, //cleaning_installed
					0, //cleaning_ActTime
					0, //cleaning_DoubleFeed
					0, //cleaning_Vaccum on

					0, //CleaningCameraDelta
					"",	//spiAlarmColor
					"",	//spiWarningColor
					"",	//spiShortColor
					0  //Beeper en
			) );
		}
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (MachineParams)", wxOK );
		cout<<" DB Update (MachineParams) ERROR!: "<< exc.GetMessage() <<endl;
		return 1;
	}

	try{

		// MotorParams
		MotorParamsStruct_100 MotorParamsS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM MotorParams") );

		while( q.NextRow() )
		{
			MotorParamsS.Id				= q.GetInt( wxT("Id") );
			MotorParamsS.Address		= q.GetInt( wxT("Address") );
			MotorParamsS.MinCurrent		= q.GetInt( wxT("MinCurrent") );
			MotorParamsS.MaxCurrent		= q.GetInt( wxT("MaxCurrent") );
			MotorParamsS.Microstepping	= q.GetInt( wxT("Microstepping") );
			MotorParamsS.Pulley			= q.GetDouble( wxT("Pulley") );
			MotorParamsS.Reduction		= q.GetDouble( wxT("Reduction") );
			MotorParamsS.Driver			= q.GetInt( wxT("Driver") );
			MotorParamsS.AccCurrent		= q.GetInt( wxT("AccCurrent") );
			MotorParamsS.Current 		= q.GetInt( wxT("Current") );

			MotorParamsS.KP_speed		= q.GetDouble( wxT("KP_speed") );
			MotorParamsS.KI_speed		= q.GetDouble( wxT("KI_speed") );
			MotorParamsS.KP_pos			= q.GetDouble( wxT("KP_pos") );
			MotorParamsS.LineEnc 		= q.GetInt( wxT("LineEnc") ); //boh!
			MotorParamsS.PulsesToMm 	= q.GetInt( wxT("PulsesToMm") );
			MotorParamsS.Poles 			= q.GetInt( wxT("Poles") );
			MotorParamsS.Jerk			= q.GetInt( wxT("Jerk") );
			MotorParamsS.KA				= q.GetDouble( wxT("KA") );
			MotorParamsS.KS				= q.GetDouble( wxT("KS") );
			MotorParamsS.KC				= q.GetDouble( wxT("KC") );

			MotorParamsS.HomeFast		= q.GetDouble( wxT("HomeFast") );
			MotorParamsS.HomeSlow		= q.GetDouble( wxT("HomeSlow") );
			MotorParamsS.PPR 			= q.GetInt( wxT("PPR") );
			MotorParamsS.Profile 		= q.GetInt( wxT("Profile") );
			MotorParamsS.EndMovementDelta	= q.GetDouble( wxT("EndMovementDelta") );
			MotorParamsS.SpykeDelta		= q.GetInt( wxT("SpykeDelta") );
			MotorParamsS.RedCurrent		= q.GetInt( wxT("RedCurrent") );
			//0 //direction

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO MotorParams VALUES ( %d, %d, %d, %d, %d, %f, %f, %d, %d, %d, "
				"																	 %f, %f, %f, %d, %d, %d, %d, %f, %f, %f, "
				"																	 %f, %f, %d, %d, %f, %d, %d, %d )",
				MotorParamsS.Id,
				MotorParamsS.Address,
				MotorParamsS.MinCurrent,
				MotorParamsS.MaxCurrent,
				MotorParamsS.Microstepping,
				MotorParamsS.Pulley,
				MotorParamsS.Reduction,
				MotorParamsS.Driver,
				MotorParamsS.AccCurrent,
				MotorParamsS.Current,

				MotorParamsS.KP_speed,
				MotorParamsS.KI_speed,
				MotorParamsS.KP_pos,
				MotorParamsS.LineEnc,
				MotorParamsS.PulsesToMm,
				MotorParamsS.Poles,
				MotorParamsS.Jerk,
				MotorParamsS.KA	,
				MotorParamsS.KS	,
				MotorParamsS.KC,

				MotorParamsS.HomeFast,
				MotorParamsS.HomeSlow,
				MotorParamsS.PPR,
				MotorParamsS.Profile,
				MotorParamsS.EndMovementDelta,
				MotorParamsS.SpykeDelta,
				MotorParamsS.RedCurrent,
				0 //direction
				) );
		}

	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (MotorParams)", wxOK );
		cout<<" DB Update (MotorParams) ERROR!: "<< exc.GetMessage() <<endl;
		return 1;
	}


	try{

		//OffsetChekPoints
		OffsetCheckPointsStruct_100 OffsetCheckPoints;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM OffsetCheckPoints") );

		while( q.NextRow() )
		{
			OffsetCheckPoints.Id = q.GetInt( wxT("Id") );
			OffsetCheckPoints.X = q.GetDouble( wxT("X") );
			OffsetCheckPoints.Y = q.GetDouble( wxT("Y") );

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO OffsetCheckPoints VALUES ( %d, %f, %f )",
					OffsetCheckPoints.Id,
					OffsetCheckPoints.X,
					OffsetCheckPoints.Y) );
		}
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (OffsetCheckPoints)", wxOK );
		cout<<" DB Update (OffsetCheckPoints) ERROR!: "<< exc.GetMessage() <<endl;
		return 1;
	}

	try
	{

		//OffsetPoints
		OffsetPointsStruct_100 OffsetPoints;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM OffsetPoints") );

		while( q.NextRow() )
		{
			OffsetPoints.Id = q.GetInt( wxT("Id") );
			OffsetPoints.X = q.GetDouble( wxT("X") );
			OffsetPoints.Y = q.GetDouble( wxT("Y") );

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO OffsetPoints VALUES ( %d, %f, %f )",
					OffsetPoints.Id,
					OffsetPoints.X,
					OffsetPoints.Y) );
		}
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (OffsetPoints)", wxOK );
		cout<<" DB Update (OffsetPoints) ERROR!: "<< exc.GetMessage() <<endl;
		return 1;
	}

	try
	{

		//PinsPoints
		PinsPointsStruct_100 PinsPoints;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM PinsPoints") );

		while( q.NextRow() )
		{
			PinsPoints.Id = q.GetInt( wxT("Id") );
			PinsPoints.IdProd = q.GetInt( wxT("IdProd") );
			PinsPoints.X = q.GetDouble( wxT("X") );
			PinsPoints.Y = q.GetDouble( wxT("Y") );

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO PinsPoints VALUES ( %d, %d, %f, %f )",
					PinsPoints.Id,
					PinsPoints.IdProd,
					PinsPoints.X,
					PinsPoints.Y) );
		}
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (PinsPoints)", wxOK );
		cout<<" DB Update (PinsPoints) ERROR!: "<< exc.GetMessage() <<endl;
		return 1;
	}

	try
	{

		// ProductionData
		ProductionDataStruct_100 ProductionDataS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM ProductionData") );

		while( q.NextRow() )
		{
			ProductionDataS.IdProd  =  q.GetInt( wxT("IdProd") );
			ProductionDataS.ProductionName		= q.GetString( wxT("ProductionName") );
			ProductionDataS.PCBHeight			= q.GetDouble( wxT("PCBHeight") );
			ProductionDataS.PCBX				= q.GetDouble( wxT("PCBX") );
			ProductionDataS.PCBY				= q.GetDouble( wxT("PCBY") );
			ProductionDataS.SqueegeesMove  		= q.GetDouble( wxT("SqueegeesMove") );
			ProductionDataS.SqueegeesZeroMove 	= q.GetDouble( wxT("SqueegeesZeroMove") );
			ProductionDataS.CorrectionX 		= q.GetDouble( wxT("CorrectionX") );
			ProductionDataS.CorrectionY 		= q.GetDouble( wxT("CorrectionY") );
			//0 //DeltaYFrontRear

			ProductionDataS.CorrectionTheta 	= q.GetDouble( wxT("CorrectionTheta") );
			ProductionDataS.Counter  			= q.GetInt( wxT("Counter") );
			ProductionDataS.PlateMovementDelta 	= q.GetDouble( wxT("PlateMovementDelta") );
			ProductionDataS.Notes				= q.GetString( wxT("Notes") );
			ProductionDataS.Notes1				= q.GetString( wxT("Notes1") );
			ProductionDataS.Notes2				= q.GetString( wxT("Notes2") );
			ProductionDataS.SqueegeesRecoveryFront 	= q.GetDouble( wxT("SqueegeesRecoveryFront") );
			ProductionDataS.SqueegeesRecoveryRear 	= q.GetDouble( wxT("SqueegeesRecoveryRear") );
			ProductionDataS.PCBPosX 			= q.GetDouble( wxT("PCBPosX") );
			ProductionDataS.PCBPosY 			= q.GetDouble( wxT("PCBPosY") );

			ProductionDataS.LoaderTrayPitch 	= q.GetDouble( wxT("LoaderTrayPitch") );
			ProductionDataS.LoaderStartPos 		= q.GetDouble( wxT("LoaderStartPos") );
			ProductionDataS.LoaderBoardNumber 	= q.GetInt( wxT("LoaderBoardNumber") );
			ProductionDataS.TopGerberOn 		= q.GetInt( wxT("TopGerberOn") );
			ProductionDataS.BotGerberOn 		= q.GetInt( wxT("BotGerberOn") );
			ProductionDataS.TopGerberRot 		= q.GetDouble( wxT("TopGerberRot") );
			ProductionDataS.BotGerberRot 		= q.GetDouble( wxT("BotGerberRot") );
			ProductionDataS.TopGerberFlip 		= q.GetInt( wxT("TopGerberFlip") );
			ProductionDataS.BotGerberFlip 		= q.GetInt( wxT("BotGerberFlip") );
			ProductionDataS.TopGerberSolder		= q.GetInt( wxT("TopGerberSolder") );

			ProductionDataS.TopGerberPads		= q.GetInt( wxT("TopGerberPads") );
			ProductionDataS.TopGerberMech		= q.GetInt( wxT("TopGerberMech") );
			ProductionDataS.BotGerberSolder		= q.GetInt( wxT("BotGerberSolder") );
			ProductionDataS.BotGerberPads		= q.GetInt( wxT("BotGerberPads") );
			ProductionDataS.BotGerberMech		= q.GetInt( wxT("BotGerberMech") );
			ProductionDataS.PinsPointsNumber		= q.GetInt( wxT("PinsPointsNumber") );
			ProductionDataS.LastRot 			= q.GetDouble( wxT("LastRot") );
			ProductionDataS.LastX				= q.GetDouble( wxT("LastX") );
			ProductionDataS.LastY				= q.GetDouble( wxT("LastY") );
			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO ProductionData VALUES ( %d, '%s', %f, %f, %f, %f, %f, %f, %f, %f, "
					"																    %f, %d, %f, '%s', '%s', '%s', %f, %f, %f, %f,"
					"																	 %f, %f, %d, %d, %d, %f, %f, %d, %d, %d, "
					"																	 %d, %d, %d, %d, %d, %d, %f, %f, %f	)",
					ProductionDataS.IdProd,
					ProductionDataS.ProductionName.ToAscii(),
					ProductionDataS.PCBHeight,
					ProductionDataS.PCBX,
					ProductionDataS.PCBY,
					ProductionDataS.SqueegeesMove,
					ProductionDataS.SqueegeesZeroMove,
					ProductionDataS.CorrectionX,
					ProductionDataS.CorrectionY,
					0.0, //DeltaYFrontRear

					ProductionDataS.CorrectionTheta,
					ProductionDataS.Counter,
					ProductionDataS.PlateMovementDelta,
					ProductionDataS.Notes.ToAscii(),
					ProductionDataS.Notes1.ToAscii(),
					ProductionDataS.Notes2.ToAscii(),
					ProductionDataS.SqueegeesRecoveryFront,
					ProductionDataS.SqueegeesRecoveryRear,
					ProductionDataS.PCBPosX,
					ProductionDataS.PCBPosY,

					ProductionDataS.LoaderTrayPitch,
					ProductionDataS.LoaderStartPos,
					ProductionDataS.LoaderBoardNumber,
					ProductionDataS.TopGerberOn,
					ProductionDataS.BotGerberOn,
					ProductionDataS.TopGerberRot,
					ProductionDataS.BotGerberRot,
					ProductionDataS.TopGerberFlip,
					ProductionDataS.BotGerberFlip,
					ProductionDataS.TopGerberSolder,

					ProductionDataS.TopGerberPads,
					ProductionDataS.TopGerberMech,
					ProductionDataS.BotGerberSolder,
					ProductionDataS.BotGerberPads,
					ProductionDataS.BotGerberMech,
					ProductionDataS.PinsPointsNumber,
					ProductionDataS.LastRot,
					ProductionDataS.LastX,
					ProductionDataS.LastY
					));
		}
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (ProductionData)", wxOK );
		cout<<" DB Update (ProductionData) ERROR!: "<< exc.GetMessage() <<endl;
		return 1;
	}

	try{

		// SerialParams
		SerialParamsStruct_100 SerialParamsS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM SerialParams") );

		while( q.NextRow() )
		{
			SerialParamsS.Id			= q.GetInt( wxT("Id") );
			SerialParamsS.SerialPort	= q.GetString( wxT("SerialPort") );
			SerialParamsS.SerialSpeed	= q.GetInt( wxT("SerialSpeed") );

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO SerialParams VALUES ( %d, '%s', %d )",
				SerialParamsS.Id,
				SerialParamsS.SerialPort.ToAscii(),
				SerialParamsS.SerialSpeed) );
		}
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (SerialParams)", wxOK );
		cout<<" DB Update (SerialParams) ERROR!: "<< exc.GetMessage() <<endl;
		return 1;
	}

	try
	{

		// SpeedTable
		SpeedTableStruct_100 SpeedTableS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM SpeedTable") );

		while( q.NextRow() )
		{
			SpeedTableS.Id			= q.GetInt( wxT("Id") );
			SpeedTableS.Speed[0]	= q.GetInt( wxT("LowSpeed") );
			SpeedTableS.Acc[0]		= q.GetInt( wxT("LowAcc") );
			SpeedTableS.Dec[0]		= q.GetInt( wxT("LowDec") );
			SpeedTableS.Speed[1]	= q.GetInt( wxT("NormalSpeed") );
			SpeedTableS.Acc[1]		= q.GetInt( wxT("NormalAcc") );
			SpeedTableS.Dec[1]		= q.GetInt( wxT("NormalDec") );
			SpeedTableS.Speed[2]	= q.GetInt( wxT("HighSpeed") );
			SpeedTableS.Acc[2]		= q.GetInt( wxT("HighAcc") );
			SpeedTableS.Dec[2]		= q.GetInt( wxT("HighDec") );

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO SpeedTable VALUES ( %d, %d, %d, %d, %d, %d, %d, %d, %d, %d )",
				SpeedTableS.Id,
				SpeedTableS.Speed[0],
				SpeedTableS.Acc[0],
				SpeedTableS.Dec[0],
				SpeedTableS.Speed[1],
				SpeedTableS.Acc[1],
				SpeedTableS.Dec[1],
				SpeedTableS.Speed[2],
				SpeedTableS.Acc[2],
				SpeedTableS.Dec[2]) );
		}
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (SpeedTable)", wxOK );
		cout<<" DB Update (SpeedTable) ERROR!: "<< exc.GetMessage() <<endl;
		return 1;
	}

	try
	{

		//VerifyPoints
		VerifyPointsStruct_100 VerifyPoints;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM VerifyPoints") );

		while( q.NextRow() )
		{
			VerifyPoints.Id = q.GetInt( wxT("Id") );
			VerifyPoints.IdProd = q.GetInt( wxT("IdProd") );
			VerifyPoints.X = q.GetDouble( wxT("X") );
			VerifyPoints.Y = q.GetDouble( wxT("Y") );

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO VerifyPoints VALUES ( %d, %d, %f, %f )",
					VerifyPoints.Id,
					VerifyPoints.IdProd,
					VerifyPoints.X,
					VerifyPoints.Y) );
		}
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (VerifyPoints)", wxOK );
		cout<<" DB Update (VerifyPoints) ERROR!: "<< exc.GetMessage() <<endl;
		return 1;
	}

	try
	{

		// WorkingModes
		WorkingModesStruct_100 WorkingModesS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM WorkingModes") );

		while( q.NextRow() )
		{
			WorkingModesS.IdProd				= q.GetInt( wxT("IdProd") );
			WorkingModesS.FiducialSearch		= q.GetInt( wxT("FiducialSearch") );
			WorkingModesS.DebugMode				= q.GetInt( wxT("DebugMode") );
			WorkingModesS.DoublePlate			= q.GetInt( wxT("DoublePlate") );
			WorkingModesS.DoublePlateEn			= q.GetInt( wxT("DoublePlateEn") );
			WorkingModesS.DoubleSqueegees		= q.GetInt( wxT("DoubleSqueegees") );
			WorkingModesS.PrintingVerify		= q.GetInt( wxT("PrintingVerify") );
			WorkingModesS.FiducialOnFrame		= q.GetInt( wxT("FiducialOnFrame") );
			WorkingModesS.SqueegeesSpeed		= q.GetInt( wxT("SqueegeesSpeed") );
			WorkingModesS.PrintingVerifyAuto	= q.GetInt( wxT("PrintingVerifyAuto") );

			WorkingModesS.PrintingVerifyTime	= q.GetInt( wxT("PrintingVerifyTime") );
			WorkingModesS.DifferentialDisengage	= q.GetInt( wxT("DifferentialDisengage") ); //Yes/No
			WorkingModesS.DisengageSpeed		= DEFAULT_DISENGAGE_SPEED;
			WorkingModesS.DisengageMovement		= q.GetDouble( wxT("DisengageMovement") ); //Deprecato
			WorkingModesS.SqueegeesSpeedValue	= q.GetInt( wxT("SqueegeesSpeedValue") );
			WorkingModesS.LoaderEn				= q.GetInt( wxT("LoaderEn") );
			//0 //inspectionType
			//0 //verifyOn
			//0 //CleaningEn
			//0 //cleaningEngageDistance
			//0	//stopsExec

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO WorkingModes VALUES ( %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, "
			"																			 %d, %d, %f, %f,  %d, %d, %d, %d, %d, %d, "
	"																					%d )",
			WorkingModesS.IdProd,
			WorkingModesS.FiducialSearch,
			WorkingModesS.DebugMode,
			WorkingModesS.DoublePlate,
			WorkingModesS.DoublePlateEn,
			WorkingModesS.DoubleSqueegees,
			WorkingModesS.PrintingVerify,
			WorkingModesS.FiducialOnFrame,
			WorkingModesS.SqueegeesSpeed,
			WorkingModesS.PrintingVerifyAuto,

			WorkingModesS.PrintingVerifyTime,
			WorkingModesS.DifferentialDisengage,
			WorkingModesS.DisengageSpeed,
			WorkingModesS.DisengageMovement,
			WorkingModesS.SqueegeesSpeedValue,
			WorkingModesS.LoaderEn,
			0, //inspectionType
			0, //verifyOn
			0, //CleaningEn
			0, //cleaningEngageDistance
			0
				) );
		}
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (WorkingModes)", wxOK );
		cout<<" DB Update (WorkingModes) ERROR!: "<< exc.GetMessage() <<endl;
		return 1;
	}

		//_SR3200.Close();
		new_db.Close();



	return 0;
}
/* PROTOTIPI
 * // ActualProduction
		new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO ActualProduction VALUES ( %d )", 0) );

		// ProductionData
		ProductionDataStruct_100 ProductionDataS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM ProductionData") );

		while( q.NextRow() )
		{
			ProductionDataS.Id					= q.GetInt( wxT("Id") );
			ProductionDataS.ProductionName		= q.GetString( wxT("ProductionName") );
			ProductionDataS.PCBHeight			= q.GetDouble( wxT("PCBHeight") );
			ProductionDataS.PCBX				= q.GetDouble( wxT("PCBX") );
			ProductionDataS.PCBY				= q.GetDouble( wxT("PCBY") );
			ProductionDataS.ZeroCoordX			= q.GetDouble( wxT("ZeroCoordX") );
			ProductionDataS.ZeroCoordY			= q.GetDouble( wxT("ZeroCoordY") );
			ProductionDataS.RefCoordX			= q.GetDouble( wxT("RefCoordX") );
			ProductionDataS.RefCoordY			= q.GetDouble( wxT("RefCoordY") );
			ProductionDataS.TableRot1			= q.GetDouble( wxT("TableRot1") );
			ProductionDataS.TableCoordX1		= q.GetDouble( wxT("TableCoordX1") );
			ProductionDataS.TableCoordY1		= q.GetDouble( wxT("TableCoordY1") );
			ProductionDataS.TableRot2			= q.GetDouble( wxT("TableRot2") );
			ProductionDataS.TableCoordX2		= q.GetDouble( wxT("TableCoordX2") );
			ProductionDataS.TableCoordY2		= q.GetDouble( wxT("TableCoordY2") );
			ProductionDataS.VerifyX1			= q.GetDouble( wxT("VerifyX1") );
			ProductionDataS.VerifyY1			= q.GetDouble( wxT("VerifyY1") );
			ProductionDataS.VerifyX2			= q.GetDouble( wxT("VerifyX2") );
			ProductionDataS.VerifyY2			= q.GetDouble( wxT("VerifyY2") );
			ProductionDataS.VerifyX3			= q.GetDouble( wxT("VerifyX3") );
			ProductionDataS.VerifyY3			= q.GetDouble( wxT("VerifyY3") );
			ProductionDataS.SqueegesMove		= q.GetDouble( wxT("SqueegesMove") );
			ProductionDataS.SqueegesZeroMove	= q.GetDouble( wxT("SqueegesZeroMove") );
			ProductionDataS.CorrectionX			= q.GetDouble( wxT("CorrectionX") );
			ProductionDataS.CorrectionY			= q.GetDouble( wxT("CorrectionY") );
			ProductionDataS.CorrectionTheta		= q.GetDouble( wxT("CorrectionTheta") );
			ProductionDataS.Counter				= q.GetInt( wxT("Counter") );
			ProductionDataS.PlateMovementDelta	= q.GetDouble( wxT("PlateMovementDelta") );

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO ProductionData VALUES ( %d, '%s', %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %d, %f )",
				ProductionDataS.Id,
				ProductionDataS.ProductionName.ToAscii(),
				ProductionDataS.PCBHeight,
				ProductionDataS.PCBX,
				ProductionDataS.PCBY,
				ProductionDataS.ZeroCoordX,
				ProductionDataS.ZeroCoordY,
				ProductionDataS.RefCoordX,
				ProductionDataS.RefCoordY,
				ProductionDataS.VerifyX1,
				ProductionDataS.VerifyY1,
				ProductionDataS.VerifyX2,
				ProductionDataS.VerifyY2,
				ProductionDataS.VerifyX3,
				ProductionDataS.VerifyY3,
				ProductionDataS.SqueegesMove,
				ProductionDataS.SqueegesZeroMove,
				ProductionDataS.CorrectionX,
				ProductionDataS.CorrectionY,
				ProductionDataS.CorrectionTheta,
				ProductionDataS.Counter,
				ProductionDataS.PlateMovementDelta) );
		}


		// AdvancedParams
		AdvancedParamsStruct_100 AdvancedParamsS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM AdvancedParams") );

		while( q.NextRow() )
		{
			AdvancedParamsS.Id					= q.GetInt( wxT("Id") );
			AdvancedParamsS.FiducialType		= q.GetInt( wxT("FiducialType") );
			AdvancedParamsS.SearchArea			= q.GetInt( wxT("SearchArea") );
			AdvancedParamsS.FilterSmoothType	= q.GetInt( wxT("FilterSmoothType") );
			AdvancedParamsS.FilterSmoothDim		= q.GetInt( wxT("FilterSmoothDim") );
			AdvancedParamsS.FilterEdgeThr		= q.GetInt( wxT("FilterEdgeThr") );
			AdvancedParamsS.CircleMinDistance	= q.GetInt( wxT("CircleMinDistance") );
			AdvancedParamsS.CircleAccumulator	= q.GetInt( wxT("CircleAccumulator") );
			AdvancedParamsS.CircleMinRadius		= q.GetInt( wxT("CircleMinRadius") );
			AdvancedParamsS.CircleMaxRadius		= q.GetInt( wxT("CircleMaxRadius") );

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO AdvancedParams VALUES ( %d, %d, %f, %d, %d, %d, %d, %d, %d )",
				AdvancedParamsS.Id,
				AdvancedParamsS.FiducialType,
				float(AdvancedParamsS.SearchArea),
				AdvancedParamsS.FilterSmoothType,
				AdvancedParamsS.FilterSmoothDim,
				AdvancedParamsS.FilterEdgeThr,
				AdvancedParamsS.CircleAccumulator,
				int((AdvancedParamsS.CircleMaxRadius + AdvancedParamsS.CircleMinRadius) / 2),
				int((AdvancedParamsS.CircleMaxRadius - AdvancedParamsS.CircleMinRadius) / 2)) );
		}


		// WorkingModes
		WorkingModesStruct_100 WorkingModesS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM WorkingModes") );

		while( q.NextRow() )
		{
			WorkingModesS.Id					= q.GetInt( wxT("Id") );
			WorkingModesS.SlowDisengage			= q.GetInt( wxT("SlowDisengage") );
			WorkingModesS.VisionAlign			= q.GetInt( wxT("VisionAlign") );
			WorkingModesS.FiducialSearch		= q.GetInt( wxT("FiducialSearch") );
			WorkingModesS.DebugMode				= q.GetInt( wxT("DebugMode") );
			WorkingModesS.DoublePlate			= q.GetInt( wxT("DoublePlate") );
			WorkingModesS.DoublePlateEn			= q.GetInt( wxT("DoublePlateEn") );
			WorkingModesS.DoubleSqueeges		= q.GetInt( wxT("DoubleSqueeges") );
			WorkingModesS.PrintingVerify		= q.GetInt( wxT("PrintingVerify") );
			WorkingModesS.FiducialOnFrame		= q.GetInt( wxT("FiducialOnFrame") );
			WorkingModesS.PlateDisengage		= q.GetDouble( wxT("PlateDisengage") );
			WorkingModesS.SqueegesSpeed			= q.GetInt( wxT("SqueegesSpeed") );

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO WorkingModes VALUES ( %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %f, %d )",
				WorkingModesS.Id,
				WorkingModesS.SlowDisengage,
				WorkingModesS.VisionAlign,
				WorkingModesS.FiducialSearch,
				WorkingModesS.DebugMode,
				WorkingModesS.DoublePlate,
				WorkingModesS.DoublePlateEn,
				WorkingModesS.DoubleSqueeges,
				WorkingModesS.PrintingVerify,
				WorkingModesS.FiducialOnFrame,
				WorkingModesS.PlateDisengage,
				WorkingModesS.SqueegesSpeed) );
		}


		// MachineParams
		MachineParamsStruct_100 MachineParamsS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM MachineParams") );

		while( q.NextRow() )
		{
			MachineParamsS.PlateZeroMovement	= q.GetDouble( wxT("PlateZeroMovement") );
			MachineParamsS.CameraFocus			= q.GetDouble( wxT("CameraFocus") );
			MachineParamsS.UpXPixMm				= q.GetDouble( wxT("UpXPixMm") );
			MachineParamsS.UpYPixMm				= q.GetDouble( wxT("UpYPixMm") );
			MachineParamsS.DnXPixMm				= q.GetDouble( wxT("DnXPixMm") );
			MachineParamsS.DnYPixMm				= q.GetDouble( wxT("DnYPixMm") );
			MachineParamsS.TableZeroMovement1	= q.GetDouble( wxT("TableZeroMovement1") );
			MachineParamsS.TableZeroMovement2	= q.GetDouble( wxT("TableZeroMovement2") );
			MachineParamsS.TableZeroMovement3	= q.GetDouble( wxT("TableZeroMovement3") );
			MachineParamsS.PlateMovement		= q.GetDouble( wxT("PlateMovement") );
			MachineParamsS.SqueegesDefZeroMove	= q.GetDouble( wxT("SqueegesDefZeroMove") );
			MachineParamsS.Counter				= q.GetInt( wxT("Counter") );
			MachineParamsS.Version				= q.GetString( wxT("Version") );
			MachineParamsS.FPS					= q.GetInt( wxT("FPS") );
			MachineParamsS.PlateSpeed			= q.GetInt( wxT("PlateSpeed") );
			MachineParamsS.CameraSpeed			= q.GetInt( wxT("CameraSpeed") );
			MachineParamsS.TableSpeed			= q.GetInt( wxT("TableSpeed") );
			MachineParamsS.PlateDisengageSpeed	= q.GetInt( wxT("PlateDisengageSpeed") );
			MachineParamsS.PlateDisengageAcc	= q.GetInt( wxT("PlateDisengageAcc") );
			MachineParamsS.PlateDisengageDec	= q.GetInt( wxT("PlateDisengageDec") );
			MachineParamsS.ImageFlip			= q.GetInt( wxT("ImageFlip") );

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO MachineParams VALUES ( %d, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %d, '%s', %d, %d, %d, %d, %d, %d, %d, %d, %d )",
				0,
				MachineParamsS.PlateZeroMovement,
				MachineParamsS.CameraFocus,
				MachineParamsS.UpXPixMm,
				MachineParamsS.UpYPixMm,
				MachineParamsS.DnXPixMm,
				MachineParamsS.DnYPixMm,
				MachineParamsS.TableZeroMovement1,
				MachineParamsS.TableZeroMovement2,
				MachineParamsS.TableZeroMovement3,
				MachineParamsS.PlateMovement,
				MachineParamsS.SqueegesDefZeroMove,
				MachineParamsS.Counter,
				wxString( wxT("1.01") ).ToAscii(),
				MachineParamsS.FPS > 0 ? MachineParamsS.FPS : 10,
				MachineParamsS.PlateSpeed,
				MachineParamsS.CameraSpeed,
				MachineParamsS.TableSpeed,
				MachineParamsS.PlateDisengageSpeed,
				MachineParamsS.PlateDisengageAcc,
				MachineParamsS.PlateDisengageDec,
				MachineParamsS.ImageFlip) );
		}


		// SettingParams
		SettingParamsStruct_100 SettingParamsS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM SettingParams") );

		while( q.NextRow() )
		{
			SettingParamsS.OffsetStartPosX		= q.GetDouble( wxT("OffsetStartPosX") );
			SettingParamsS.OffsetStartPosY		= q.GetDouble( wxT("OffsetStartPosY") );
			SettingParamsS.OffsetPointsDistance	= q.GetDouble( wxT("OffsetPointsDistance") );
			SettingParamsS.OffsetNumPointsX		= q.GetInt( wxT("OffsetNumPointsX") );
			SettingParamsS.OffsetNumPointsY		= q.GetInt( wxT("OffsetNumPointsY") );

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO SettingParams VALUES ( %d, %f, %f, %f, %d, %d )",
				0,
				SettingParamsS.OffsetStartPosX,
				SettingParamsS.OffsetStartPosY,
				OFFSET_POINTS_DISTANCE,
				OFFSET_POINTS_X,
				OFFSET_POINTS_Y) );
		}


		// CameraOffset
		int CameraOffsetPoints = 0, CameraOffsetLastId = 0;
		CameraOffsetStruct_100 CameraOffsetS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM CameraOffset") );

		while( q.NextRow() )
		{
			CameraOffsetS.Id	= q.GetInt( wxT("Id") );
			CameraOffsetS.X		= q.GetDouble( wxT("X") );
			CameraOffsetS.Y		= q.GetDouble( wxT("Y") );

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO CameraOffset VALUES ( %d, %f, %f )",
				CameraOffsetS.Id,
				CameraOffsetS.X,
				CameraOffsetS.Y) );

			CameraOffsetPoints++;
			CameraOffsetLastId = CameraOffsetS.Id + 1;
		}

		while( CameraOffsetPoints < OFFSET_POINTS_101 )
		{
			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO CameraOffset VALUES ( %d, %f, %f )",
				CameraOffsetLastId,
				0.0f,
				0.0f) );

			CameraOffsetPoints++;
			CameraOffsetLastId++;
		}


		// Limits
		LimitsStruct_100 LimitsS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM Limits") );

		while( q.NextRow() )
		{
			LimitsS.Id			= q.GetInt( wxT("Id") );
			LimitsS.MinLimit	= q.GetDouble( wxT("Min") );
			LimitsS.MaxLimit	= q.GetDouble( wxT("Max") );

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO Limits VALUES ( %d, %f, %f )",
				LimitsS.Id,
				LimitsS.MinLimit,
				LimitsS.MaxLimit) );
		}


		// SerialParams
		SerialParamsStruct_100 SerialParamsS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM SerialParams") );

		while( q.NextRow() )
		{
			SerialParamsS.Id			= q.GetInt( wxT("Id") );
			SerialParamsS.SerialPort	= q.GetString( wxT("SerialPort") );
			SerialParamsS.SerialSpeed	= q.GetInt( wxT("SerialSpeed") );

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO SerialParams VALUES ( %d, '%s', %d )",
				SerialParamsS.Id,
				SerialParamsS.SerialPort.ToAscii(),
				SerialParamsS.SerialSpeed) );
		}


		// MotorParams
		MotorParamsStruct_100 MotorParamsS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM MotorParams") );

		while( q.NextRow() )
		{
			MotorParamsS.Id				= q.GetInt( wxT("Id") );
			MotorParamsS.Address		= q.GetInt( wxT("Address") );
			MotorParamsS.MinCurrent		= q.GetInt( wxT("MinCurrent") );
			MotorParamsS.AccCurrent		= q.GetInt( wxT("AccCurrent") );
			MotorParamsS.MaxCurrent		= q.GetInt( wxT("MaxCurrent") );
			MotorParamsS.Microstepping	= q.GetInt( wxT("Microstepping") );
			MotorParamsS.Pulley			= q.GetDouble( wxT("Pulley") );
			MotorParamsS.Reduction		= q.GetDouble( wxT("Reduction") );
			MotorParamsS.Driver			= q.GetInt( wxT("Driver") );

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO MotorParams VALUES ( %d, %d, %d, %d, %d, %f, %f, %d, %d )",
				MotorParamsS.Id,
				MotorParamsS.Address,
				MotorParamsS.MinCurrent,
				MotorParamsS.MaxCurrent,
				MotorParamsS.Microstepping,
				MotorParamsS.Pulley,
				MotorParamsS.Reduction,
				MotorParamsS.Driver,
				MotorParamsS.AccCurrent) );
		}


		// IOParams
		IOParamsStruct_100 IOParamsS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM IOParams") );

		while( q.NextRow() )
		{
			IOParamsS.Id			= q.GetInt( wxT("Id") );
			IOParamsS.Type			= q.GetInt( wxT("Type") );
			IOParamsS.DriverId		= q.GetInt( wxT("DriverId") );
			IOParamsS.DriverPort	= q.GetInt( wxT("DriverPort") );

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO IOParams VALUES ( %d, %d, %d, %d )",
				IOParamsS.Id,
				IOParamsS.Type,
				IOParamsS.DriverId,
				IOParamsS.DriverPort) );
		}


		// SpeedTable
		SpeedTableStruct_100 SpeedTableS;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM SpeedTable") );

		while( q.NextRow() )
		{
			SpeedTableS.Id			= q.GetInt( wxT("Id") );
			SpeedTableS.Speed[0]	= q.GetInt( wxT("LowSpeed") );
			SpeedTableS.Speed[1]	= q.GetInt( wxT("NormalSpeed") );
			SpeedTableS.Speed[2]	= q.GetInt( wxT("HighSpeed") );
			SpeedTableS.Acc[0]		= q.GetInt( wxT("LowAcc") );
			SpeedTableS.Acc[1]		= q.GetInt( wxT("NormalAcc") );
			SpeedTableS.Acc[2]		= q.GetInt( wxT("HighAcc") );
			SpeedTableS.Dec[0]		= q.GetInt( wxT("LowDec") );
			SpeedTableS.Dec[1]		= q.GetInt( wxT("NormalDec") );
			SpeedTableS.Dec[2]		= q.GetInt( wxT("HighDec") );

			new_db.ExecuteQuery( stmtBuffer.Format("INSERT INTO SpeedTable VALUES ( %d, %d, %d, %d, %d, %d, %d, %d, %d, %d )",
				SpeedTableS.Id,
				SpeedTableS.Speed[0],
				SpeedTableS.Acc[0],
				SpeedTableS.Dec[0],
				SpeedTableS.Speed[1],
				SpeedTableS.Acc[1],
				SpeedTableS.Dec[1],
				SpeedTableS.Speed[2],
				SpeedTableS.Acc[2],
				SpeedTableS.Dec[2]) );
		}


		_SR3200.Close();
		new_db.Close();
	}
	catch( wxSQLite3Exception& )
	{
		return 1;
	}

	return 0;
 */


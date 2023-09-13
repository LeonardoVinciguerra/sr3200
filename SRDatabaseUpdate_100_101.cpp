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
//#include "SRDB100.h"

#define OFFSET_POINTS_DISTANCE	28.0f
#define OFFSET_POINTS_X			13
#define OFFSET_POINTS_Y			15
#define OFFSET_POINTS_101		195
#define NUM_VERIFY_POINTS		10


//----------------------------------------------------------------------------------
// From_100_to_101
// 
//----------------------------------------------------------------------------------
/* COME ESEMPIO!!
int SRDatabase::From_100_to_101( const char *db_file_in, const char *db_file_out )
{
	wxSQLite3Database db_in, db_out;
	wxSQLite3ResultSet q;
	wxSQLite3StatementBuffer stmtBuffer;

	try
	{
		db_in.Open( wxString::Format( "%s", db_file_in ) );
		db_out.Open( wxString::Format( "%s", db_file_out ) );


		// ActualProduction
		db_out.ExecuteQuery( stmtBuffer.Format("INSERT INTO ActualProduction VALUES ( %d )", 0) );

		// ProductionData
		ProductionDataStruct_100 ProductionDataS;
		q = db_in.ExecuteQuery( wxT("SELECT * FROM ProductionData") );

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

			db_out.ExecuteQuery( stmtBuffer.Format("INSERT INTO ProductionData VALUES ( %d, '%s', %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %d, %f )",
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
		q = db_in.ExecuteQuery( wxT("SELECT * FROM AdvancedParams") );

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

			db_out.ExecuteQuery( stmtBuffer.Format("INSERT INTO AdvancedParams VALUES ( %d, %d, %f, %d, %d, %d, %d, %d, %d )",
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
		q = db_in.ExecuteQuery( wxT("SELECT * FROM WorkingModes") );

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

			db_out.ExecuteQuery( stmtBuffer.Format("INSERT INTO WorkingModes VALUES ( %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %f, %d )",
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
		q = db_in.ExecuteQuery( wxT("SELECT * FROM MachineParams") );

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

			db_out.ExecuteQuery( stmtBuffer.Format("INSERT INTO MachineParams VALUES ( %d, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %d, '%s', %d, %d, %d, %d, %d, %d, %d, %d, %d )",
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
		q = db_in.ExecuteQuery( wxT("SELECT * FROM SettingParams") );

		while( q.NextRow() )
		{
			SettingParamsS.OffsetStartPosX		= q.GetDouble( wxT("OffsetStartPosX") );
			SettingParamsS.OffsetStartPosY		= q.GetDouble( wxT("OffsetStartPosY") );
			SettingParamsS.OffsetPointsDistance	= q.GetDouble( wxT("OffsetPointsDistance") );
			SettingParamsS.OffsetNumPointsX		= q.GetInt( wxT("OffsetNumPointsX") );
			SettingParamsS.OffsetNumPointsY		= q.GetInt( wxT("OffsetNumPointsY") );

			db_out.ExecuteQuery( stmtBuffer.Format("INSERT INTO SettingParams VALUES ( %d, %f, %f, %f, %d, %d )",
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
		q = db_in.ExecuteQuery( wxT("SELECT * FROM CameraOffset") );

		while( q.NextRow() )
		{
			CameraOffsetS.Id	= q.GetInt( wxT("Id") );
			CameraOffsetS.X		= q.GetDouble( wxT("X") );
			CameraOffsetS.Y		= q.GetDouble( wxT("Y") );

			db_out.ExecuteQuery( stmtBuffer.Format("INSERT INTO CameraOffset VALUES ( %d, %f, %f )",
				CameraOffsetS.Id,
				CameraOffsetS.X,
				CameraOffsetS.Y) );

			CameraOffsetPoints++;
			CameraOffsetLastId = CameraOffsetS.Id + 1;
		}

		while( CameraOffsetPoints < OFFSET_POINTS_101 )
		{
			db_out.ExecuteQuery( stmtBuffer.Format("INSERT INTO CameraOffset VALUES ( %d, %f, %f )",
				CameraOffsetLastId,
				0.0f,
				0.0f) );

			CameraOffsetPoints++;
			CameraOffsetLastId++;
		}


		// Limits
		LimitsStruct_100 LimitsS;
		q = db_in.ExecuteQuery( wxT("SELECT * FROM Limits") );

		while( q.NextRow() )
		{
			LimitsS.Id			= q.GetInt( wxT("Id") );
			LimitsS.MinLimit	= q.GetDouble( wxT("Min") );
			LimitsS.MaxLimit	= q.GetDouble( wxT("Max") );

			db_out.ExecuteQuery( stmtBuffer.Format("INSERT INTO Limits VALUES ( %d, %f, %f )",
				LimitsS.Id,
				LimitsS.MinLimit,
				LimitsS.MaxLimit) );
		}


		// SerialParams
		SerialParamsStruct_100 SerialParamsS;
		q = db_in.ExecuteQuery( wxT("SELECT * FROM SerialParams") );

		while( q.NextRow() )
		{
			SerialParamsS.Id			= q.GetInt( wxT("Id") );
			SerialParamsS.SerialPort	= q.GetString( wxT("SerialPort") );
			SerialParamsS.SerialSpeed	= q.GetInt( wxT("SerialSpeed") );

			db_out.ExecuteQuery( stmtBuffer.Format("INSERT INTO SerialParams VALUES ( %d, '%s', %d )",
				SerialParamsS.Id,
				SerialParamsS.SerialPort.ToAscii(),
				SerialParamsS.SerialSpeed) );
		}


		// MotorParams
		MotorParamsStruct_100 MotorParamsS;
		q = db_in.ExecuteQuery( wxT("SELECT * FROM MotorParams") );

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

			db_out.ExecuteQuery( stmtBuffer.Format("INSERT INTO MotorParams VALUES ( %d, %d, %d, %d, %d, %f, %f, %d, %d )",
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
		q = db_in.ExecuteQuery( wxT("SELECT * FROM IOParams") );

		while( q.NextRow() )
		{
			IOParamsS.Id			= q.GetInt( wxT("Id") );
			IOParamsS.Type			= q.GetInt( wxT("Type") );
			IOParamsS.DriverId		= q.GetInt( wxT("DriverId") );
			IOParamsS.DriverPort	= q.GetInt( wxT("DriverPort") );

			db_out.ExecuteQuery( stmtBuffer.Format("INSERT INTO IOParams VALUES ( %d, %d, %d, %d )",
				IOParamsS.Id,
				IOParamsS.Type,
				IOParamsS.DriverId,
				IOParamsS.DriverPort) );
		}


		// SpeedTable
		SpeedTableStruct_100 SpeedTableS;
		q = db_in.ExecuteQuery( wxT("SELECT * FROM SpeedTable") );

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

			db_out.ExecuteQuery( stmtBuffer.Format("INSERT INTO SpeedTable VALUES ( %d, %d, %d, %d, %d, %d, %d, %d, %d, %d )",
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


		db_in.Close();
		db_out.Close();
	}
	catch( wxSQLite3Exception& )
	{
		return 1;
	}

	return 0;
}
*/


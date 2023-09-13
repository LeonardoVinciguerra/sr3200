//---------------------------------------------------------------------------
//
// Name:        SRDatabase.cpp
// Author:      Gabriel Ferri
// Created:     11/04/2008
// Description: SRDatabase class implementation
//
//---------------------------------------------------------------------------
//aggiunto
#define _GLIBCXX_USE_C99 1


#include "SRDatabase.h"
#include <wx/wxsqlite3.h>
#include <wx/msgdlg.h>
#include "GlobalUtils.h"
#include "GlobalEnum.h"




//----------------------------------------------------------------------------------
// Construttore / Distruttore
// 
//----------------------------------------------------------------------------------
SRDatabase::SRDatabase( const wxString& machineDB, const wxString& AUTOspiDB )
{
	_SR3200.Open( machineDB );
	//aggiunto
	_DBspiAUTO.Open(AUTOspiDB);

	dbFile = machineDB;

	offsetUParamsS.SearchMode		= offsetDParamsS.SearchMode			= visionTestParamsS.SearchMode			= 0;
	offsetUParamsS.SearchAreaMul	= offsetDParamsS.SearchAreaMul		= visionTestParamsS.SearchAreaMul		= 2;
	offsetUParamsS.FilterSmoothType	= offsetDParamsS.FilterSmoothType	= visionTestParamsS.FilterSmoothType	= 1;
	offsetUParamsS.FilterSmoothDim	= offsetDParamsS.FilterSmoothDim	= visionTestParamsS.FilterSmoothDim		= 9;
	offsetUParamsS.FilterEdgeThr	= offsetDParamsS.FilterEdgeThr		= visionTestParamsS.FilterEdgeThr		= 50;
	offsetUParamsS.CircleAccum		= offsetDParamsS.CircleAccum		= 50;
	visionTestParamsS.CircleAccum	= 10;
	offsetUParamsS.CircleDiameter	= offsetDParamsS.CircleDiameter		= visionTestParamsS.CircleDiameter		= 60;
	offsetUParamsS.Tolerance		= offsetDParamsS.Tolerance			= visionTestParamsS.Tolerance			= 5;
	offsetUParamsS.RectangleAccum	= offsetDParamsS.RectangleAccum		= visionTestParamsS.RectangleAccum		= 25;
	offsetUParamsS.RectangleSideX	= offsetDParamsS.RectangleSideX		= visionTestParamsS.RectangleSideX		= 60;
	offsetUParamsS.RectangleSideY	= offsetDParamsS.RectangleSideY		= visionTestParamsS.RectangleSideY		= 60;
	
	offsetUParamsS.CameraBrightness	= offsetDParamsS.CameraBrightness	= visionTestParamsS.CameraBrightness	= 0.5f;
	offsetUParamsS.CameraContrast	= offsetDParamsS.CameraContrast		= visionTestParamsS.CameraContrast		= 0.5f;
}

SRDatabase::~SRDatabase()
{
	if( _SR3200.IsOpen() )
		_SR3200.Close();

	//aggiunto
	if( _DBspiAUTO.IsOpen() )
		_DBspiAUTO.Close();
}

//----------------------------------------------------------------------------------
// Backup
// Salva il DB
//----------------------------------------------------------------------------------
int SRDatabase::Backup( const wxString &backupFile )
{
	return CopyFile( dbFile.ToAscii(), backupFile.ToAscii() );
}

//----------------------------------------------------------------------------------
// Restore
// Ripristina un database precedentemente salvato
//----------------------------------------------------------------------------------
int SRDatabase::Restore( const wxString &restoreFile )
{
	return CopyFile( restoreFile.ToAscii(), dbFile.ToAscii() );
}

//----------------------------------------------------------------------------------
// LoadProductionStructsFromDB
// Carica dal DB tutti i dati relativi alla produzione
//----------------------------------------------------------------------------------
int SRDatabase::LoadProductionStructsFromDB( int id )
{
	if( LoadProductionData( id ) == SR_ERROR )
		return SR_ERROR;
	if( LoadFiducialParams() == SR_ERROR )
		return SR_ERROR;
	if( LoadVerifyPoints() == SR_ERROR )
		return SR_ERROR;
	if( LoadWorkingModes() == SR_ERROR )
		return SR_ERROR;
	if( LoadPinsPoints() == SR_ERROR )
		return SR_ERROR;
	if( LoadInspectionSites() == SR_ERROR )
		return SR_ERROR;
	if( LoadZeroCamParams() == SR_ERROR )
		return SR_ERROR;
	SetFiducialParams( FIDUCIAL_ROT1 );
	return SR_OK;
}

int SRDatabase::LoadProductionStructsFromDB( const wxString &prodName )
{
	if( LoadProductionData( prodName ) == SR_ERROR )
		return SR_ERROR;
	if( LoadFiducialParams() == SR_ERROR )
		return SR_ERROR;
	if( LoadVerifyPoints() == SR_ERROR )
		return SR_ERROR;
	if( LoadWorkingModes() == SR_ERROR )
		return SR_ERROR;
	if( LoadPinsPoints() == SR_ERROR )
		return SR_ERROR;
	if( LoadInspectionSites() == SR_ERROR )
		return SR_ERROR;
	SetFiducialParams( FIDUCIAL_ROT1 );
	return SR_OK;
}

//----------------------------------------------------------------------------------
// LoadMachineStructsFromDB
// Carica dal DB tutti i dati relativi alla macchina
//----------------------------------------------------------------------------------
int SRDatabase::LoadMachineStructsFromDB()
{
	if( LoadMachineParams() == SR_ERROR )
		return SR_ERROR;
	if( LoadSpeedTable() == SR_ERROR )
		return SR_ERROR;
	if( LoadLimits() == SR_ERROR )
		return SR_ERROR;
	if( LoadSerialParams() == SR_ERROR )
		return SR_ERROR;
	if( LoadIOParams() == SR_ERROR )
		return SR_ERROR;
	if( LoadMotorParams() == SR_ERROR )
		return SR_ERROR;
	if( LoadOffsetPoints() == SR_ERROR )
		return SR_ERROR;
	if( LoadOffsetCheckPoints() == SR_ERROR )
		return SR_ERROR;
	return SR_OK;
}

//----------------------------------------------------------------------------------
// LoadProductionNames
// Carica dal DB i nomi di tutte le produzioni presenti
//----------------------------------------------------------------------------------
int SRDatabase::LoadProductionNames()
{
	try
	{
		wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxT("SELECT * FROM ProductionData") );

		ProductionNames.Clear();
		while( q.NextRow() )
		{
			ProductionNames.Add( q.GetString( wxT("ProductionName") ) );
		}

		ProductionNames.Sort();
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// InsertProduction
// Inserisce nel DB una nuova produzione
//----------------------------------------------------------------------------------
int SRDatabase::InsertProduction( const wxString &prodName, float squeegeesDefZeroMove )
{
	wxString empty_str( wxT("") );

	try
	{
		// Retrieve the highest Production Id
		int HighestProductionId = -1;
		wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxT("SELECT * FROM ProductionData") );
		while( q.NextRow() )
		{
			int productionId = q.GetInt( wxT("IdProd") );
			if( productionId > HighestProductionId )
				HighestProductionId = productionId;
		}
		HighestProductionId++;

		// Retrieve the highest Fiducial Id
		int HighestFiducialId = -1;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM FiducialParams") );
		while( q.NextRow() )
		{
			int fiducialId = q.GetInt( wxT("Id") );
			if( fiducialId > HighestFiducialId )
				HighestFiducialId = fiducialId;
		}
		HighestFiducialId++;

		// Retrieve the highest VerifyPoint Id
		int HighestVerifyPointId = -1;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM VerifyPoints") );
		while( q.NextRow() )
		{
			int verifyId = q.GetInt( wxT("Id") );
			if( verifyId > HighestVerifyPointId )
				HighestVerifyPointId = verifyId;
		}
		HighestVerifyPointId++;

		// Retrieve the highest PinsPoint Id
		int HighestPinsPointId = -1;
		q = _SR3200.ExecuteQuery( wxT("SELECT * FROM PinsPoints") );
		while( q.NextRow() )
		{
			int pinsId = q.GetInt( wxT("Id") );
			if( pinsId > HighestPinsPointId )
				HighestPinsPointId = pinsId;
		}
		HighestPinsPointId++;

		// Insert ProductionData and WorkingModes
		wxSQLite3StatementBuffer stmtBuffer;
		try{
			_SR3200.ExecuteQuery( stmtBuffer.Format("INSERT INTO ProductionData VALUES ( %d, '%s', 0, 0, 0, 0, %f, 0, 0, 0, 0, 0, 0, '%s', '%s', '%s', 0.0, 0.0, 0.0, 0.0, %f, 0.0, 0, 0, 0, 0.0, 0.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0, 0.0, 0.0 )", HighestProductionId, prodName.ToAscii(), squeegeesDefZeroMove, empty_str.ToAscii(), empty_str.ToAscii(), empty_str.ToAscii(), MachineParamsS.LoaderDefPitch ) );
			_SR3200.ExecuteQuery( stmtBuffer.Format("INSERT INTO WorkingModes VALUES ( %d, 0, 0, 0, 1, 0, 3, 1, 1, 1, 5, 0, 20.0, %d, 0, 0, 0, 0, 0, 0, 0, 0, 0 )", HighestProductionId, SQUEEGEES_DEF_SPEED ) );
		}
		catch( wxSQLite3Exception& exc ){
			wxMessageBox( exc.GetMessage(), "wxSQLite_WorkingModes", wxOK | wxICON_ERROR );
			return SR_ERROR;
		}
		// Insert FiducialParams
		for( int i = 0; i < NUM_FIDUCIALS; i++ )
		{
			try{
				_SR3200.ExecuteQuery( stmtBuffer.Format("INSERT INTO FiducialParams VALUES ( %d, %d, 0.0, 0.0, 0.0, 0.0, 1, 11, 50, 0, 2.0, 10, 60, 25, 60, 60, 5, %d, 75.0, 0.5, 0.5 )", HighestFiducialId, HighestProductionId, i ) );
				HighestFiducialId++;
			}
			catch( wxSQLite3Exception& exc ){
				wxMessageBox( exc.GetMessage(), "wxSQLite_FiducialParams", wxOK | wxICON_ERROR );
				return SR_ERROR;
			}
		}
		// Insert VerifyPoints
		for( int i = 0; i < NUM_VERIFY_POINTS; i++ )
		{
			try	{
				_SR3200.ExecuteQuery( stmtBuffer.Format("INSERT INTO VerifyPoints VALUES ( %d, %d, 0.0, 0.0 )", HighestVerifyPointId, HighestProductionId ) );
				HighestVerifyPointId++;
			}
			catch( wxSQLite3Exception& exc ){
				wxMessageBox( exc.GetMessage(), "wxSQLite_VerifyPoints", wxOK | wxICON_ERROR );
				return SR_ERROR;
			}
		}
		// Insert PinsPoints
		for( int i = 0; i < NUM_PINS_POINTS; i++ )
		{
			try{
			_SR3200.ExecuteQuery( stmtBuffer.Format("INSERT INTO PinsPoints VALUES ( %d, %d, 0.0, 0.0 )", HighestPinsPointId, HighestProductionId ) );
			HighestPinsPointId++;
			}
			catch( wxSQLite3Exception& exc ){
				wxMessageBox( exc.GetMessage(), "wxSQLite_PinsPoints", wxOK | wxICON_ERROR );
				return SR_ERROR;
			}
		}
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// DeleteProduction
// Inserisce nel DB una nuova produzione
//----------------------------------------------------------------------------------
int SRDatabase::DeleteProduction( int id, bool keepResults )
{
	try
	{
		wxSQLite3StatementBuffer stmtBuffer;
		_SR3200.ExecuteQuery( stmtBuffer.Format("DELETE FROM ProductionData WHERE IdProd = %d", id ) );
		_SR3200.ExecuteQuery( stmtBuffer.Format("DELETE FROM FiducialParams WHERE IdProd = %d", id ) );
		_SR3200.ExecuteQuery( stmtBuffer.Format("DELETE FROM VerifyPoints WHERE IdProd = %d", id ) );
		_SR3200.ExecuteQuery( stmtBuffer.Format("DELETE FROM WorkingModes WHERE IdProd = %d", id ) );
		_SR3200.ExecuteQuery( stmtBuffer.Format("DELETE FROM PinsPoints WHERE IdProd = %d", id ) );
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	if(DeleteInspectionSiteAll(id, keepResults)==SR_OK)
		return SR_OK;

	//return SR_OK;
}

//----------------------------------------------------------------------------------
// LoadActualProduction
// Carica dal DB la tabella ActualProduction
//----------------------------------------------------------------------------------
int SRDatabase::LoadActualProduction()
{
	try
	{
		wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxT("SELECT * FROM ActualProduction") );

		while( q.NextRow() )
		{
			ActualProductionS.IdProd = q.GetInt( wxT("IdProd") );
		}
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SaveActualProduction
// Salva nel DB la tabella ActualProduction
//----------------------------------------------------------------------------------
int SRDatabase::SaveActualProduction()
{
	try
	{
		wxSQLite3StatementBuffer stmtBuffer;
		_SR3200.ExecuteUpdate( stmtBuffer.Format("UPDATE ActualProduction SET IdProd = %d;", ActualProductionS.IdProd) );
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// LoadProductionData
// Carica dal DB la tabella ProductionData
//----------------------------------------------------------------------------------
int SRDatabase::LoadProductionData( int id )
{
	try
	{
		wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxString::Format("SELECT * FROM ProductionData WHERE IdProd = %d;", id) );

		while( q.NextRow() )
		{
			ProductionDataS.IdProd					= q.GetInt( wxT("IdProd") );
			ProductionDataS.ProductionName			= q.GetString( wxT("ProductionName") );
			ProductionDataS.PCBHeight				= q.GetDouble( wxT("PCBHeight") );
			ProductionDataS.PCBX					= q.GetDouble( wxT("PCBX") );
			ProductionDataS.PCBY					= q.GetDouble( wxT("PCBY") );
			ProductionDataS.SqueegeesMove			= q.GetDouble( wxT("SqueegeesMove") );
			ProductionDataS.SqueegeesZeroMove		= q.GetDouble( wxT("SqueegeesZeroMove") );
			ProductionDataS.CorrectionX				= q.GetDouble( wxT("CorrectionX") );
			ProductionDataS.CorrectionY				= q.GetDouble( wxT("CorrectionY") );
			ProductionDataS.DeltaYFrontRear			= q.GetDouble( wxT("DeltaYFrontRear") );
			ProductionDataS.CorrectionTheta			= q.GetDouble( wxT("CorrectionTheta") );
			ProductionDataS.Counter					= q.GetInt( wxT("Counter") );
			ProductionDataS.PlateMovementDelta		= q.GetDouble( wxT("PlateMovementDelta") );
			ProductionDataS.Notes					= q.GetString( wxT("Notes") );
			ProductionDataS.Notes1					= q.GetString( wxT("Notes1") );
			ProductionDataS.Notes2					= q.GetString( wxT("Notes2") );
			ProductionDataS.SqueegeesRecoveryFront	= q.GetDouble( wxT("SqueegeesRecoveryFront") );
			ProductionDataS.SqueegeesRecoveryRear	= q.GetDouble( wxT("SqueegeesRecoveryRear") );
			ProductionDataS.PCBPosX					= q.GetDouble( wxT("PCBPosX") );
			ProductionDataS.PCBPosY					= q.GetDouble( wxT("PCBPosY") );
			ProductionDataS.LoaderTrayPitch			= q.GetDouble( wxT("LoaderTrayPitch") );
			ProductionDataS.LoaderStartPos			= q.GetDouble( wxT("LoaderStartPos") );
			ProductionDataS.LoaderBoardNumber		= q.GetInt( wxT("LoaderBoardNumber") );
			ProductionDataS.TopGerberOn				= q.GetInt( wxT("TopGerberOn") );
			ProductionDataS.BotGerberOn				= q.GetInt( wxT("BotGerberOn") );
			ProductionDataS.TopGerberRot			= q.GetDouble( wxT("TopGerberRot") );
			ProductionDataS.BotGerberRot			= q.GetDouble( wxT("BotGerberRot") );
			ProductionDataS.TopGerberFlip			= q.GetInt( wxT("TopGerberFlip") );
			ProductionDataS.BotGerberFlip			= q.GetInt( wxT("BotGerberFlip") );
			ProductionDataS.TopGerberSolder			= q.GetInt( wxT("TopGerberSolder") );
			ProductionDataS.TopGerberPads			= q.GetInt( wxT("TopGerberPads") );
			ProductionDataS.TopGerberMech			= q.GetInt( wxT("TopGerberMech") );
			ProductionDataS.BotGerberSolder			= q.GetInt( wxT("BotGerberSolder") );
			ProductionDataS.BotGerberPads			= q.GetInt( wxT("BotGerberPads") );
			ProductionDataS.BotGerberMech			= q.GetInt( wxT("BotGerberMech") );
			ProductionDataS.PinsPointsNumber		= q.GetInt( wxT("PinsPointsNumber") );
			ProductionDataS.LastRot					= q.GetDouble( wxT("LastRot") );
			ProductionDataS.LastX					= q.GetDouble( wxT("LastX") );
			ProductionDataS.LastY					= q.GetDouble( wxT("LastY") );
		}
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "wxSQLite_Production_Data", wxOK | wxICON_ERROR );
		return SR_ERROR;
	}

	return SR_OK;
}

int SRDatabase::LoadProductionData( const wxString &prodName )
{
	int idProd = -1;

	try
	{
		wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxString::Format("SELECT * FROM ProductionData WHERE ProductionName = '%s';", prodName.ToAscii()) );

		while( q.NextRow() )
		{
			idProd = q.GetInt( wxT("IdProd") );
		}
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	if( idProd == -1 )
		return SR_ERROR;

	return LoadProductionData( idProd );
}

//----------------------------------------------------------------------------------
// SaveProductionData
// Salva nel DB la tabella ProductionData
//----------------------------------------------------------------------------------
int SRDatabase::SaveProductionData()
{
	try
	{
		wxSQLite3StatementBuffer stmtBuffer;
		_SR3200.ExecuteUpdate( stmtBuffer.Format("UPDATE ProductionData SET ProductionName = '%s', PCBHeight = %f, PCBX = %f, PCBY = %f, SqueegeesMove = %f, SqueegeesZeroMove = %f, CorrectionX = %f, CorrectionY = %f, DeltaYFrontRear = %f, CorrectionTheta = %f, Counter = %d, PlateMovementDelta = %f, Notes = '%s', Notes1 = '%s', Notes2 = '%s', SqueegeesRecoveryFront = %f, SqueegeesRecoveryRear = %f, PCBPosX = %f, PCBPosY = %f, LoaderTrayPitch = %f, LoaderStartPos = %f, LoaderBoardNumber = %d, TopGerberOn = %d, BotGerberOn = %d, TopGerberRot = %f, BotGerberRot = %f, TopGerberFlip = %d, BotGerberFlip = %d, TopGerberSolder = %d, TopGerberPads = %d, TopGerberMech = %d, BotGerberSolder = %d, BotGerberPads = %d, BotGerberMech = %d, PinsPointsNumber = %d, LastRot = %f, LastX = %f, LastY = %f WHERE IdProd = %d;",
				ProductionDataS.ProductionName.ToAscii(),
				ProductionDataS.PCBHeight,
				ProductionDataS.PCBX,
				ProductionDataS.PCBY,
				ProductionDataS.SqueegeesMove,
				ProductionDataS.SqueegeesZeroMove,
				ProductionDataS.CorrectionX,
				ProductionDataS.CorrectionY,
				ProductionDataS.DeltaYFrontRear,
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
				ProductionDataS.LastY,
				ProductionDataS.IdProd) );
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "wxSQLite_Save_Production_Data", wxOK | wxICON_ERROR );
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// LoadFiducialParams
// Carica dal DB la tabella FiducialParams
//----------------------------------------------------------------------------------
int SRDatabase::LoadFiducialParams()
{
	try
	{
		wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxString::Format("SELECT * FROM FiducialParams WHERE IdProd = %d;", ProductionDataS.IdProd) );

		while( q.NextRow() )
		{
			int type = q.GetInt( wxT("Type") );
			if( type < 0 || type > NUM_FIDUCIALS )
			{
				return SR_ERROR;
			}

			FiducialParamsS[type].Id				= q.GetInt( wxT("Id") );
			FiducialParamsS[type].IdProd			= ProductionDataS.IdProd;
			FiducialParamsS[type].X					= q.GetDouble( wxT("X") );
			FiducialParamsS[type].Y					= q.GetDouble( wxT("Y") );
			FiducialParamsS[type].DeltaX			= q.GetDouble( wxT("DeltaX") );
			FiducialParamsS[type].DeltaY			= q.GetDouble( wxT("DeltaY") );
			FiducialParamsS[type].FilterSmoothType	= q.GetInt( wxT("FilterSmoothType") );
			FiducialParamsS[type].FilterSmoothDim	= q.GetInt( wxT("FilterSmoothDim") );
			FiducialParamsS[type].FilterEdgeThr		= q.GetInt( wxT("FilterEdgeThr") );
			FiducialParamsS[type].SearchMode		= q.GetInt( wxT("SearchMode") );
			FiducialParamsS[type].SearchAreaMul		= q.GetDouble( wxT("SearchAreaMul") );
			FiducialParamsS[type].CircleAccum		= q.GetInt( wxT("CircleAccum") );
			FiducialParamsS[type].CircleDiameter	= q.GetInt( wxT("CircleDiameter") );
			FiducialParamsS[type].RectangleAccum	= q.GetInt( wxT("RectangleAccum") );
			FiducialParamsS[type].RectangleSideX	= q.GetInt( wxT("RectangleSideX") );
			FiducialParamsS[type].RectangleSideY	= q.GetInt( wxT("RectangleSideY") );
			FiducialParamsS[type].Tolerance			= q.GetInt( wxT("Tolerance") );
			FiducialParamsS[type].Type				= q.GetInt( wxT("Type") );
			FiducialParamsS[type].TemplateThr		= q.GetDouble( wxT("TemplateThr") );
			FiducialParamsS[type].CameraBrightness	= q.GetDouble( wxT("CameraBrightness") );
			FiducialParamsS[type].CameraContrast	= q.GetDouble( wxT("CameraContrast") );
		}
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "wxSQLite_Fiducial_Params", wxOK | wxICON_ERROR );
		return SR_ERROR;
	}


	return SR_OK;
}
int SRDatabase::LoadZeroCamParams(){

	try{
			wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxString::Format("SELECT * FROM FiducialParams WHERE IdProd = %d;", -1) );

				while( q.NextRow() )
				{
					CameraZeroParamsS.Id				= q.GetInt( wxT("Id") );
					CameraZeroParamsS.IdProd			= -1;
					CameraZeroParamsS.X					= q.GetDouble( wxT("X") );
					CameraZeroParamsS.Y					= q.GetDouble( wxT("Y") );
					CameraZeroParamsS.DeltaX			= q.GetDouble( wxT("DeltaX") );
					CameraZeroParamsS.DeltaY			= q.GetDouble( wxT("DeltaY") );
					CameraZeroParamsS.FilterSmoothType	= q.GetInt( wxT("FilterSmoothType") );
					CameraZeroParamsS.FilterSmoothDim	= q.GetInt( wxT("FilterSmoothDim") );
					CameraZeroParamsS.FilterEdgeThr		= q.GetInt( wxT("FilterEdgeThr") );
					CameraZeroParamsS.SearchMode		= q.GetInt( wxT("SearchMode") );
					CameraZeroParamsS.SearchAreaMul		= q.GetDouble( wxT("SearchAreaMul") );
					CameraZeroParamsS.CircleAccum		= q.GetInt( wxT("CircleAccum") );
					CameraZeroParamsS.CircleDiameter	= q.GetInt( wxT("CircleDiameter") );
					CameraZeroParamsS.RectangleAccum	= q.GetInt( wxT("RectangleAccum") );
					CameraZeroParamsS.RectangleSideX	= q.GetInt( wxT("RectangleSideX") );
					CameraZeroParamsS.RectangleSideY	= q.GetInt( wxT("RectangleSideY") );
					CameraZeroParamsS.Tolerance			= q.GetInt( wxT("Tolerance") );
					CameraZeroParamsS.Type				= q.GetInt( wxT("Type") );
					CameraZeroParamsS.TemplateThr		= q.GetDouble( wxT("TemplateThr") );
					CameraZeroParamsS.CameraBrightness	= q.GetDouble( wxT("CameraBrightness") );
					CameraZeroParamsS.CameraContrast	= q.GetDouble( wxT("CameraContrast") );
			}
		}
		catch( wxSQLite3Exception&  exc )
		{
			cout<< "SELECT CameraZeroParamsS failed: "<<endl;
			return SR_ERROR;
		}
}

//----------------------------------------------------------------------------------
// SaveFiducialParams
// Salva nel DB la tabella FiducialParams
//----------------------------------------------------------------------------------
int SRDatabase::SaveFiducialParams()
{
	try
	{
		wxSQLite3StatementBuffer stmtBuffer;

		for( int i = 0; i < NUM_FIDUCIALS; i++ )
		{
			_SR3200.ExecuteUpdate( stmtBuffer.Format("UPDATE FiducialParams SET IdProd = %d, X = %f, Y = %f, DeltaX = %f, DeltaY = %f, FilterSmoothType = %d, FilterSmoothDim = %d, FilterEdgeThr = %d, SearchMode = %d, SearchAreaMul = %f, CircleAccum = %d, CircleDiameter = %d, RectangleAccum = %d, RectangleSideX = %d, RectangleSideY = %d, Tolerance = %d, Type = %d, TemplateThr = %f, CameraBrightness = %f, CameraContrast = %f WHERE Id = %d;",
					FiducialParamsS[i].IdProd,
					FiducialParamsS[i].X,
					FiducialParamsS[i].Y,
					FiducialParamsS[i].DeltaX,
					FiducialParamsS[i].DeltaY,
					FiducialParamsS[i].FilterSmoothType,
					FiducialParamsS[i].FilterSmoothDim,
					FiducialParamsS[i].FilterEdgeThr,
					FiducialParamsS[i].SearchMode,
					FiducialParamsS[i].SearchAreaMul,
					FiducialParamsS[i].CircleAccum,
					FiducialParamsS[i].CircleDiameter,
					FiducialParamsS[i].RectangleAccum,
					FiducialParamsS[i].RectangleSideX,
					FiducialParamsS[i].RectangleSideY,
					FiducialParamsS[i].Tolerance,
					FiducialParamsS[i].Type,
					FiducialParamsS[i].TemplateThr,
					FiducialParamsS[i].CameraBrightness,
					FiducialParamsS[i].CameraContrast,
					FiducialParamsS[i].Id) );
		}
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "wxSQLite_Save_Fid_Params", wxOK | wxICON_ERROR );
		return SR_ERROR;
	}

	return SR_OK;
}


int SRDatabase::SaveCameraZero(){
	try
		{
			wxSQLite3StatementBuffer stmtBuffer;

				_SR3200.ExecuteUpdate( stmtBuffer.Format("UPDATE FiducialParams SET IdProd = -1, "
						"X = %f, Y = %f, "
						"DeltaX = %f, DeltaY = %f, "
						"FilterSmoothType = %d, FilterSmoothDim = %d, "
						"FilterEdgeThr = %d, SearchMode = %d, "
						"SearchAreaMul = %f, CircleAccum = %d, "
						"CircleDiameter = %d, RectangleAccum = %d, "
						"RectangleSideX = %d, RectangleSideY = %d, "
						"Tolerance = %d, Type = %d, "
						"TemplateThr = %f, "
						"CameraBrightness = %f, "
						"CameraContrast = %f WHERE Id = %d;",
						CameraZeroParamsS.X,
						CameraZeroParamsS.Y,
						CameraZeroParamsS.DeltaX,
						CameraZeroParamsS.DeltaY,
						CameraZeroParamsS.FilterSmoothType,
						CameraZeroParamsS.FilterSmoothDim,
						CameraZeroParamsS.FilterEdgeThr,
						CameraZeroParamsS.SearchMode,
						CameraZeroParamsS.SearchAreaMul,
						CameraZeroParamsS.CircleAccum,
						CameraZeroParamsS.CircleDiameter,
						CameraZeroParamsS.RectangleAccum,
						CameraZeroParamsS.RectangleSideX,
						CameraZeroParamsS.RectangleSideY,
						CameraZeroParamsS.Tolerance,
						CameraZeroParamsS.Type,
						CameraZeroParamsS.TemplateThr,
						CameraZeroParamsS.CameraBrightness,
						CameraZeroParamsS.CameraContrast,
						CameraZeroParamsS.Id) );

		}
		catch( wxSQLite3Exception& exc)
		{
			cout<<"Update error in SaveCameraZero: "<< exc.GetMessage()<<endl;
			return SR_ERROR;
		}

		return SR_OK;
}
//----------------------------------------------------------------------------------
// LoadVerifyPoints
// Carica dal DB la tabella VerifyPoints
//----------------------------------------------------------------------------------
int SRDatabase::LoadVerifyPoints()
{
	try
	{
		wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxString::Format("SELECT * FROM VerifyPoints WHERE IdProd = %d;", ProductionDataS.IdProd) );

		int counter = 0;
		while( q.NextRow() )
		{
			if( counter >= NUM_VERIFY_POINTS )
			{
				return SR_ERROR;
			}

			VerifyPointsS[counter].Id		= q.GetInt( wxT("Id") );
			VerifyPointsS[counter].IdProd	= ProductionDataS.IdProd;
			VerifyPointsS[counter].X		= q.GetDouble( wxT("X") );
			VerifyPointsS[counter].Y		= q.GetDouble( wxT("Y") );

			counter++;
		}
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SaveVerifyPoints
// Salva nel DB la tabella VerifyPoints
//----------------------------------------------------------------------------------
int SRDatabase::SaveVerifyPoints()
{
	try
	{
		wxSQLite3StatementBuffer stmtBuffer;

		for( int i = 0; i < NUM_VERIFY_POINTS; i++ )
		{
			_SR3200.ExecuteUpdate( stmtBuffer.Format("UPDATE VerifyPoints SET IdProd = %d, X = %f, Y = %f WHERE Id = %d;",
					VerifyPointsS[i].IdProd,
					VerifyPointsS[i].X,
					VerifyPointsS[i].Y,
					VerifyPointsS[i].Id) );
		}
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// LoadWorkingModes
// Carica dal DB la tabella WorkingModes
//----------------------------------------------------------------------------------
int SRDatabase::LoadWorkingModes()
{
	try
	{
		wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxString::Format("SELECT * FROM WorkingModes WHERE IdProd = %d;", ProductionDataS.IdProd) );

		while( q.NextRow() )
		{
			WorkingModesS.IdProd				= ProductionDataS.IdProd;
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
			WorkingModesS.DifferentialDisengage	= q.GetInt( wxT("DifferentialDisengage") );
			WorkingModesS.DisengageSpeed		= q.GetDouble( wxT("DisengageSpeed") );
			WorkingModesS.SqueegeesSpeedValue	= q.GetInt( wxT("SqueegeesSpeedValue") );
			WorkingModesS.LoaderEn				= q.GetInt( wxT("LoaderEn") );
			WorkingModesS.InspectionType		= q.GetInt( wxT("InspectionType") );
			WorkingModesS.VerifyON				= q.GetInt( wxT("VerifyON") );
			WorkingModesS.CleaningEn			= q.GetInt( wxT("CleaningEn") );
			WorkingModesS.CleaningEngageDistance= q.GetDouble( wxT("CleaningEngageDistance") );
			WorkingModesS.SPIStopsWhenFaulty 	= q.GetInt( wxT("SPIStopsWhenFaulty") );
			WorkingModesS.PistonLoadingDeltaX 	= q.GetInt( wxT("PistonLoadingDeltaX") );
			WorkingModesS.PistonLoadingDeltaY 	= q.GetInt( wxT("PistonLoadingDeltaY") );
			WorkingModesS.InputSensorEnabled 	= true; //Default always active
			WorkingModesS.AntiReflectsEn 	= q.GetInt( wxT("AntiReflectsEn") );

		}

		//ATTENZIONE - serve per poter inserire la velocit� delle racle in mm/sec
		// l'indice � sempre su NORMAL, il valore che cambia � quello della tabella delle velocit� della entry NORMAL,
		// i valori delle entries LOW, HIGH vengono utilizzati come limiti
		WorkingModesS.SqueegeesSpeed = 1; // NORMAL entry
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "wxSQLite_Working_Modes", wxOK | wxICON_ERROR );
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SaveWorkingModes
// Salva nel DB la tabella WorkingModes
//----------------------------------------------------------------------------------
int SRDatabase::SaveWorkingModes()
{
	try
	{
		wxSQLite3StatementBuffer stmtBuffer;
		_SR3200.ExecuteUpdate( stmtBuffer.Format("UPDATE WorkingModes SET "
				"FiducialSearch = %d, "
				"DebugMode = %d, "
				"DoublePlate = %d, "
				"DoublePlateEn = %d, "
				"DoubleSqueegees = %d, "
				"PrintingVerify = %d, "
				"FiducialOnFrame = %d, "
				"SqueegeesSpeed = %d, "
				"PrintingVerifyAuto = %d, "
				"PrintingVerifyTime = %d, "
				"DifferentialDisengage = %d, "
				"DisengageSpeed = %f, "
				"SqueegeesSpeedValue = %d, "
				"LoaderEn = %d, "
				"InspectionType = %d, "
				"VerifyON = %d, "
				"SPIStopsWhenFaulty=%d, "
				"CleaningEn = %d, "
				"AntiReflectsEn = %d, "
				"CleaningEngageDistance = %f, "
				"PistonLoadingDeltaX = %f, "
				"PistonLoadingDeltaY = %f "
				"WHERE IdProd = %d;",
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
				WorkingModesS.SqueegeesSpeedValue,
				WorkingModesS.LoaderEn,
				WorkingModesS.InspectionType,
				WorkingModesS.VerifyON,
				WorkingModesS.SPIStopsWhenFaulty,
				WorkingModesS.CleaningEn,
				WorkingModesS.AntiReflectsEn,
				WorkingModesS.CleaningEngageDistance,
				WorkingModesS.PistonLoadingDeltaX,
				WorkingModesS.PistonLoadingDeltaY,
				ProductionDataS.IdProd) );
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "wxSQLite_Save_Working_Modes", wxOK | wxICON_ERROR );
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// LoadPinsPoints
// Carica dal DB la tabella PinsPoints
//----------------------------------------------------------------------------------
int SRDatabase::LoadPinsPoints()
{
	try
	{
		wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxString::Format("SELECT * FROM PinsPoints WHERE IdProd = %d;", ProductionDataS.IdProd) );

		int counter = 0;
		while( q.NextRow() )
		{
			if( counter >= NUM_PINS_POINTS )
			{
				return SR_ERROR;
			}

			PinsPointsS[counter].Id			= q.GetInt( wxT("Id") );
			PinsPointsS[counter].IdProd		= ProductionDataS.IdProd;
			PinsPointsS[counter].X			= q.GetDouble( wxT("X") );
			PinsPointsS[counter].Y			= q.GetDouble( wxT("Y") );

			counter++;
		}
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "wxSQLite_Pin_Points", wxOK | wxICON_ERROR );
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SavePinsPoints
// Salva nel DB la tabella PinsPoints
//----------------------------------------------------------------------------------
int SRDatabase::SavePinsPoints()
{
	try
	{
		wxSQLite3StatementBuffer stmtBuffer;

		for( int i = 0; i < NUM_PINS_POINTS; i++ )
		{
			_SR3200.ExecuteUpdate( stmtBuffer.Format("UPDATE PinsPoints SET IdProd = %d, X = %f, Y = %f WHERE Id = %d;",
					PinsPointsS[i].IdProd,
					PinsPointsS[i].X,
					PinsPointsS[i].Y,
					PinsPointsS[i].Id) );
		}
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "wxSQLite_Save_Pin_Points", wxOK | wxICON_ERROR );
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// LoadMachineParams
// Carica dal DB la tabella MachineParams
//----------------------------------------------------------------------------------
int SRDatabase::LoadMachineParams()
{
	// legge la versione separatamente per evitare errori nelle modifiche delle altre variabili
	try
	{
		wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxT("SELECT * FROM MachineParams") );

		while( q.NextRow() )
		{
			MachineParamsS.Version = q.GetString( wxT("Version") );
		}
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	// restanti variabili
	wxString AlarmString;
	wxString ShortString;
	wxString WarningString;
	try
	{
		wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxT("SELECT * FROM MachineParams") );

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
			MachineParamsS.SqueegeesDefZeroMove	= q.GetDouble( wxT("SqueegeesDefZeroMove") );
			MachineParamsS.Counter				= q.GetInt( wxT("Counter") );
			MachineParamsS.FPS					= q.GetInt( wxT("FPS") );
			MachineParamsS.CameraSpeed			= q.GetInt( wxT("CameraSpeed") );
			MachineParamsS.TableSpeed			= q.GetInt( wxT("TableSpeed") );
			MachineParamsS.ImageFlip			= q.GetInt( wxT("ImageFlip") );
			MachineParamsS.OffsetPointsStartX	= q.GetDouble( wxT("OffsetPointsStartX") );
			MachineParamsS.OffsetPointsStartY	= q.GetDouble( wxT("OffsetPointsStartY") );
			MachineParamsS.OffsetPointsDistance	= q.GetDouble( wxT("OffsetPointsDistance") );
			MachineParamsS.OffsetPointsNumX		= q.GetInt( wxT("OffsetPointsNumX") );
			MachineParamsS.OffsetPointsNumY		= q.GetInt( wxT("OffsetPointsNumY") );
			MachineParamsS.PlateUpSpeed			= q.GetInt( wxT("PlateUpSpeed") );
			MachineParamsS.PlateDownSpeed		= q.GetInt( wxT("PlateDownSpeed") );
			MachineParamsS.InputSensorMode		= q.GetInt( wxT("InputSensorMode") );
			MachineParamsS.AutoVacuumMode		= q.GetInt( wxT("AutoVacuumMode") );
			MachineParamsS.ConvWidthSpeed		= q.GetInt( wxT("ConvWidthSpeed") );
			MachineParamsS.ConvFeedSpeed		= q.GetInt( wxT("ConvFeedSpeed") );
			MachineParamsS.LoaderSpeed			= q.GetInt( wxT("LoaderSpeed") );
			MachineParamsS.ConvPushSpeed		= 2; //TOD sempre alta
			MachineParamsS.LConvZeroMovement	= q.GetDouble( wxT("LConvZeroMovement") );
			MachineParamsS.CConvZeroMovement	= q.GetDouble( wxT("CConvZeroMovement") );
			MachineParamsS.RConvZeroMovement	= q.GetDouble( wxT("RConvZeroMovement") );
			MachineParamsS.LoaderZeroMovement	= q.GetDouble( wxT("LoaderZeroMovement") );
			MachineParamsS.LConvMovement		= q.GetDouble( wxT("LConvMovement") );
			MachineParamsS.CConvMovement		= q.GetDouble( wxT("CConvMovement") );
			MachineParamsS.RConvMovement		= q.GetDouble( wxT("RConvMovement") );
			MachineParamsS.ConveyorMode			= q.GetInt( wxT("ConveyorMode") );
			MachineParamsS.ConvEdgeX			= q.GetDouble( wxT("ConvEdgeX") );
			MachineParamsS.ConvEdgeY			= q.GetDouble( wxT("ConvEdgeY") );
			MachineParamsS.LoaderAdjPosition	= q.GetDouble( wxT("LoaderAdjPosition") );
			MachineParamsS.CamPistonDeltaX		= q.GetDouble( wxT("CamPistonDeltaX") );
			MachineParamsS.CamPistonDeltaY		= q.GetDouble( wxT("CamPistonDeltaY") );
			MachineParamsS.LoaderInstalled		= q.GetInt( wxT("LoaderInstalled") );
			MachineParamsS.LoaderDefPitch		= q.GetDouble( wxT("LoaderDefPitch") );
			MachineParamsS.LedLightReduced		= q.GetInt( wxT("LedLightReduced") );
			MachineParamsS.CleaningInstalled	= q.GetInt( wxT("CleaningInstalled") );
			MachineParamsS.CleaningActivationTime	= q.GetInt( wxT("CleaningActivationTime") );
			MachineParamsS.CleaningDoubleFeed	= q.GetInt( wxT("CleaningDoubleFeed") );
			MachineParamsS.CleaningVacuumOn		= q.GetInt( wxT("CleaningVacuumOn") );
			MachineParamsS.CleaningCameraDelta  = q.GetDouble( wxT("CleaningCameraDelta") );
			MachineParamsS.SPIAlarmColor 		= q.GetString(wxT("SPIAlarmColor"));
			MachineParamsS.SPIShortColor 		= q.GetString(wxT("SPIShortColor"));
			MachineParamsS.SPIWarningColor 		= q.GetString(wxT("SPIWarningColor"));
			MachineParamsS.BeeperEn				= q.GetInt( wxT("BeeperEn") );
		}
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "wxSQLite_Machine_Params", wxOK | wxICON_ERROR );
		return SR_ERROR;
	}

	//split points
	std::string delimiter = ";";
	size_t pos = 0;
	int counter_points=0;
	string stringAlarm = MachineParamsS.SPIAlarmColor.ToAscii();
	string stringShort = MachineParamsS.SPIShortColor.ToAscii();
	string stringWarning = MachineParamsS.SPIWarningColor.ToAscii();

	while ( (pos = stringAlarm.find(delimiter)) != std::string::npos) {
		ALARM_COLOR.val[counter_points]= std::atoi( stringAlarm.substr(0, pos).c_str() );
		stringAlarm.erase(0, pos + delimiter.length());
		counter_points++;
	}
	pos = 0;
	counter_points=0;
	while ( (pos = stringShort.find(delimiter)) != std::string::npos) {
			SHORT_COLOR.val[counter_points]= std::atoi( stringShort.substr(0, pos).c_str() );
			stringShort.erase(0, pos + delimiter.length());
			counter_points++;
	}
	pos = 0;
	counter_points=0;
	while ( (pos = stringWarning.find(delimiter)) != std::string::npos) {
			WARNING_COLOR.val[counter_points]= std::atoi( stringWarning.substr(0, pos).c_str() );
			stringWarning.erase(0, pos + delimiter.length());
			counter_points++;
	}



	return SR_OK;
}

//----------------------------------------------------------------------------------
// SaveMachineParams
// Salva nel DB la tabella MachineParams
//----------------------------------------------------------------------------------
int SRDatabase::SaveMachineParams()
{

	try
	{
		wxSQLite3StatementBuffer stmtBuffer;
		_SR3200.ExecuteUpdate( stmtBuffer.Format("UPDATE MachineParams SET PlateZeroMovement = %f, CameraFocus = %f, UpXPixMm = %f, UpYPixMm = %f, DnXPixMm = %f, DnYPixMm = %f, TableZeroMovement1 = %f, TableZeroMovement2 = %f, TableZeroMovement3 = %f, PlateMovement = %f, SqueegeesDefZeroMove = %f, Counter = %d, Version = '%s', FPS = %d, CameraSpeed = %d, TableSpeed = %d, ImageFlip = %d, OffsetPointsStartX = %f, OffsetPointsStartY = %f, OffsetPointsDistance = %f, OffsetPointsNumX = %d, OffsetPointsNumY = %d, PlateUpSpeed = %d, PlateDownSpeed = %d, InputSensorMode = %d, AutoVacuumMode = %d, ConvWidthSpeed = %d, ConvFeedSpeed = %d, LoaderSpeed = %d, LConvZeroMovement = %f, CConvZeroMovement = %f, RConvZeroMovement = %f, LoaderZeroMovement = %f, LConvMovement = %f, CConvMovement = %f, RConvMovement = %f, ConveyorMode = %d, ConvEdgeX = %f, ConvEdgeY = %f, LoaderAdjPosition = %f, CamPistonDeltaX = %f, CamPistonDeltaY = %f, LoaderInstalled = %d, LoaderDefPitch = %f, LedLightReduced = %d, CleaningInstalled = %d, CleaningActivationTime = %d, CleaningDoubleFeed = %d, CleaningVacuumOn = %d, CleaningCameraDelta = %f, SPIAlarmColor ='%s', SPIWarningColor ='%s', SPIShortColor ='%s' , BeeperEn = %d; ",
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
				MachineParamsS.CleaningInstalled,
				MachineParamsS.CleaningActivationTime,
				MachineParamsS.CleaningDoubleFeed,
				MachineParamsS.CleaningVacuumOn,
				MachineParamsS.CleaningCameraDelta,
				MachineParamsS.SPIAlarmColor.ToAscii(),
				MachineParamsS.SPIShortColor.ToAscii(),
				MachineParamsS.SPIWarningColor.ToAscii(),
				MachineParamsS.BeeperEn
		) );
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "wxSQLite_Save_Machine_Params", wxOK | wxICON_ERROR );
		return SR_ERROR;
	}

	return SR_OK;
}

int SRDatabase::SaveCurrentGlobalOffsetValues(){
	try{
		wxSQLite3StatementBuffer stmtBuffer;
		_SR3200.ExecuteUpdate( stmtBuffer.Format("UPDATE GLOBAL_OFFSET SET GLOBAL_OFFSET_DELTA_X = %f, GLOBAL_OFFSET_DELTA_Y = %f ",
				GlobalOffset.X,
				GlobalOffset.Y
		) );
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "wxSQLite_Save_Global_Offset", wxOK | wxICON_ERROR );
		return SR_ERROR;
	}

	return SR_OK;
}
int SRDatabase::ResetProductionOffsetValues(){
	try{
		wxSQLite3StatementBuffer stmtBuffer;
		_SR3200.ExecuteUpdate( stmtBuffer.Format("UPDATE ProductionData SET  CorrectionX = %f, CorrectionY = %f ",
				0.0,
				0.0 ) );
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "wxSQLite_UPDATE_Production_OFFSET", wxOK | wxICON_ERROR );
		return SR_ERROR;
	}

	ProductionDataS.CorrectionX = 0;
	ProductionDataS.CorrectionY = 0;

	return SR_OK;
}
//----------------------------------------------------------------------------------
// LoadOffsetPoints
// Carica dal DB la tabella OffsetPoints
//----------------------------------------------------------------------------------
int SRDatabase::LoadOffsetPoints()
{
	try
	{
		wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxT("SELECT * FROM OffsetPoints") );

		int i = 0;
		while( q.NextRow() )
		{
			OffsetPointsS[i].Id	= q.GetInt( wxT("Id") );
			OffsetPointsS[i].X	= q.GetDouble( wxT("X") );
			OffsetPointsS[i].Y	= q.GetDouble( wxT("Y") );
			i++;
		}
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "wxSQLite_Offset_Points", wxOK | wxICON_ERROR );
		return SR_ERROR;
	}

	try{
		wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxT("SELECT * FROM GLOBAL_OFFSET") );

		int i = 0;
		while( q.NextRow() )
		{
			GlobalOffset.X	= q.GetDouble( wxT("GLOBAL_OFFSET_DELTA_X") );
			GlobalOffset.Y	= q.GetDouble( wxT("GLOBAL_OFFSET_DELTA_Y") );
			i++;
		}
	}catch( wxSQLite3Exception& exc){
		wxMessageBox( exc.GetMessage(), "wxSQLite_Offset_Global", wxOK | wxICON_ERROR );
		return SR_ERROR;
	}


	return SR_OK;
}

//----------------------------------------------------------------------------------
// SaveOffsetPoints
// Salva nel DB la tabella OffsetPoints
//----------------------------------------------------------------------------------
int SRDatabase::SaveOffsetPoints()
{
	try
	{
		wxSQLite3StatementBuffer stmtBuffer;

		for( int i = 0; i < NUM_OFFSET_POINTS; i++ )
		{
			_SR3200.ExecuteUpdate( stmtBuffer.Format("UPDATE OffsetPoints SET X = %f, Y = %f WHERE Id = %d;",
					OffsetPointsS[i].X,
					OffsetPointsS[i].Y,
					OffsetPointsS[i].Id) );
		}
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "wxSQLite_Save_Offset_Points", wxOK | wxICON_ERROR );
		return SR_ERROR;
	}

	return SR_OK;
}
//----------------------------------------------------------------------------------
// SaveOffsetPoints
// Corregge prima e ultima riga della matrice e Salva nel DB la tabella OffsetPoints
//----------------------------------------------------------------------------------

int SRDatabase::CorrectOffsetPoints(){

	//Correct low operator side
	int lineOffset = MachineParamsS.OffsetPointsNumX;
	for(int i =0; i< MachineParamsS.OffsetPointsNumX; i++){

		OffsetPointsS[i].X = OffsetPointsS[i+lineOffset].X + (OffsetPointsS[i+ lineOffset].X - OffsetPointsS[i+ 2*lineOffset].X);
		OffsetPointsS[i].Y = OffsetPointsS[i+lineOffset].Y + (OffsetPointsS[i+ lineOffset].Y - OffsetPointsS[i+ 2*lineOffset].Y);
	}

	//Correct row rear side
	int startingPoint = MachineParamsS.OffsetPointsNumX*(MachineParamsS.OffsetPointsNumY-1);
	int maxPoint = MachineParamsS.OffsetPointsNumX*MachineParamsS.OffsetPointsNumY;
	for(int i = startingPoint; i< maxPoint; i++){
		OffsetPointsS[i].X = OffsetPointsS[i-lineOffset].X + (OffsetPointsS[i-lineOffset].X - OffsetPointsS[i-2*lineOffset].X);
		OffsetPointsS[i].Y = OffsetPointsS[i-lineOffset].Y + (OffsetPointsS[i-lineOffset].Y - OffsetPointsS[i-2*lineOffset].Y);
	}

	SaveOffsetPoints();
}

//----------------------------------------------------------------------------------
// LoadOffsetCheckPoints
// Carica dal DB la tabella OffsetCheckPoints
//----------------------------------------------------------------------------------
int SRDatabase::LoadOffsetCheckPoints()
{
	try
	{
		wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxT("SELECT * FROM OffsetCheckPoints") );

		int i = 0;
		while( q.NextRow() )
		{
			OffsetCheckPointsS[i].Id= q.GetInt( wxT("Id") );
			OffsetCheckPointsS[i].X	= q.GetDouble( wxT("X") );
			OffsetCheckPointsS[i].Y	= q.GetDouble( wxT("Y") );
			i++;
		}
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SaveOffsetCheckPoints
// Salva nel DB la tabella OffsetCheckPoints
//----------------------------------------------------------------------------------
int SRDatabase::SaveOffsetCheckPoints()
{
	try
	{
		wxSQLite3StatementBuffer stmtBuffer;

		for( int i = 0; i < NUM_OFFSET_POINTS; i++ )
		{
			_SR3200.ExecuteUpdate( stmtBuffer.Format("UPDATE OffsetCheckPoints SET X = %f, Y = %f WHERE Id = %d;",
					OffsetCheckPointsS[i].X,
					OffsetCheckPointsS[i].Y,
					OffsetCheckPointsS[i].Id) );
		}
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	return SR_OK;
}


//----------------------------------------------------------------------------------
// CreateOffsetCheckPoints
// Crea le entry della tabella OffsetCheckPoints
//----------------------------------------------------------------------------------
int SRDatabase::CreateOffsetCheckPoints()
{
	try
	{
		wxSQLite3StatementBuffer stmtBuffer;

		for( int i = 0; i < NUM_OFFSET_POINTS; i++ )
		{
			_SR3200.ExecuteUpdate( stmtBuffer.Format("INSERT INTO OffsetCheckPoints VALUES (%d, %f, %f);", i+1, 0.0, 0.0 ) );
		}
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// ResetOffsetCheckPoints
// Resetta nel DB la tabella OffsetCheckPoints
//----------------------------------------------------------------------------------
int SRDatabase::ResetOffsetCheckPoints()
{
	try
	{
		wxSQLite3StatementBuffer stmtBuffer;

		for( int i = 0; i < NUM_OFFSET_POINTS; i++ )
		{
			_SR3200.ExecuteUpdate( stmtBuffer.Format("UPDATE OffsetCheckPoints SET X = %f, Y = %f WHERE Id = %d;",
					0.0,
					0.0,
					OffsetCheckPointsS[i].Id) );
		}
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// LoadLimits
// Carica dal DB la tabella Limits
//----------------------------------------------------------------------------------
int SRDatabase::LoadLimits()
{
	try
	{
		wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxT("SELECT * FROM Limits") );

		int i = 0;
		while( q.NextRow() )
		{
			LimitsS[i].Id		= q.GetInt( wxT("Id") );
			LimitsS[i].MinLimit	= q.GetDouble( wxT("Min") );
			LimitsS[i].MaxLimit	= q.GetDouble( wxT("Max") );
			i++;
		}
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SaveLimits
// Salva nel DB la tabella Limits
//----------------------------------------------------------------------------------
int SRDatabase::SaveLimits()
{
	try
	{
		wxSQLite3StatementBuffer stmtBuffer;

		for( int i = 0; i < NUM_MOTORS; i++ )
		{
			_SR3200.ExecuteUpdate( stmtBuffer.Format("UPDATE Limits SET Min = %f, Max = %f WHERE Id = %d;",
					LimitsS[i].MinLimit,
					LimitsS[i].MaxLimit,
					LimitsS[i].Id) );
		}
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// LoadSerialParams
// Carica dal DB la tabella SerialParams
//----------------------------------------------------------------------------------
int SRDatabase::LoadSerialParams()
{
	try
	{
		wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxT("SELECT * FROM SerialParams") );

		int i = 0;
		while( q.NextRow() )
		{
			SerialParamsS[i].Id				= q.GetInt( wxT("Id") );
			SerialParamsS[i].SerialPort		= q.GetString( wxT("SerialPort") );
			SerialParamsS[i].SerialSpeed	= q.GetInt( wxT("SerialSpeed") );
			i++;
		}
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SaveSerialParams
// Salva nel DB la tabella SerialParams
//----------------------------------------------------------------------------------
int SRDatabase::SaveSerialParams()
{
	try
	{
		wxSQLite3StatementBuffer stmtBuffer;

		for( int i = 0; i < NUM_SERIALS; i++ )
		{
			_SR3200.ExecuteUpdate( stmtBuffer.Format("UPDATE SerialParams SET SerialPort = '%s', SerialSpeed = %d WHERE Id = %d;",
					SerialParamsS[i].SerialPort.ToAscii(),
					SerialParamsS[i].SerialSpeed,
					SerialParamsS[i].Id) );
		}
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// LoadMotorParams
// Carica dal DB la tabella MotorParams
//----------------------------------------------------------------------------------
int SRDatabase::LoadMotorParams()
{
	try
	{
		wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxT("SELECT * FROM MotorParams") );

		int i = 0;
		while( q.NextRow() )
		{
			MotorParamsS[i].Id					= q.GetInt( wxT("Id") );
			MotorParamsS[i].Address				= q.GetInt( wxT("Address") );
			MotorParamsS[i].MinCurrent			= q.GetInt( wxT("MinCurrent") );
			MotorParamsS[i].AccCurrent			= q.GetInt( wxT("AccCurrent") );
			MotorParamsS[i].MaxCurrent			= q.GetInt( wxT("MaxCurrent") );
			MotorParamsS[i].Microstepping		= q.GetInt( wxT("Microstepping") );
			MotorParamsS[i].Pulley				= q.GetDouble( wxT("Pulley") );
			MotorParamsS[i].Reduction			= q.GetDouble( wxT("Reduction") );
			MotorParamsS[i].Driver				= q.GetInt( wxT("Driver") );
			MotorParamsS[i].Current				= q.GetInt( wxT("Current") );
			MotorParamsS[i].KP_speed			= q.GetDouble( wxT("KP_speed") );
			MotorParamsS[i].KI_speed			= q.GetDouble( wxT("KI_speed") );
			MotorParamsS[i].KP_pos				= q.GetDouble( wxT("KP_pos") );
			MotorParamsS[i].LineEnc				= q.GetInt( wxT("LineEnc") );
			MotorParamsS[i].PulsesToMm			= q.GetInt( wxT("PulsesToMm") );
			MotorParamsS[i].Poles				= q.GetInt( wxT("Poles") );
			MotorParamsS[i].Jerk				= q.GetInt( wxT("Jerk") );
			MotorParamsS[i].KA					= q.GetDouble( wxT("KA") );
			MotorParamsS[i].KS					= q.GetDouble( wxT("KS") );
			MotorParamsS[i].KC					= q.GetDouble( wxT("KC") );
			MotorParamsS[i].HomeFast			= q.GetDouble( wxT("HomeFast") );
			MotorParamsS[i].HomeSlow			= q.GetDouble( wxT("HomeSlow") );
			MotorParamsS[i].PPR					= q.GetInt( wxT("PPR") );
			MotorParamsS[i].Profile				= q.GetInt( wxT("Profile") );
			MotorParamsS[i].EndMovementDelta	= q.GetDouble( wxT("EndMovementDelta") );
			MotorParamsS[i].SpykeDelta			= q.GetInt( wxT("SpykeDelta") );
			MotorParamsS[i].RedCurrent			= q.GetInt( wxT("RedCurrent") );
			MotorParamsS[i].Direction			= q.GetInt( wxT("Direction") );
			MotorParamsS[i].EncoderMode			= q.GetInt( wxT("EncoderMode") );
			MotorParamsS[i].EncoderType			= q.GetInt( wxT("EncoderType") );

			i++;
		}
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SaveMotorParams
// Salva nel DB la tabella MotorParams
//----------------------------------------------------------------------------------
int SRDatabase::SaveMotorParams()
{
	try
	{
		wxSQLite3StatementBuffer stmtBuffer;

		for( int i = 0; i < NUM_MOTORS; i++ )
		{
			_SR3200.ExecuteUpdate( stmtBuffer.Format("UPDATE MotorParams SET Address = %d, MinCurrent = %d, AccCurrent = %d, MaxCurrent = %d, Microstepping = %d, Pulley = %f, Reduction = %f, Driver = %d, Current = %d, KP_speed = %f, KI_speed = %f, KP_pos = %f, LineEnc = %d, PulsesToMm = %d, Poles = %d, Jerk = %d, KA = %f, KS = %f, KC = %f, HomeFast = %f, HomeSlow = %f, PPR = %d, Profile = %d, EndMovementDelta = %f, SpykeDelta = %d, RedCurrent = %d, Direction = %d WHERE Id = %d;",
					MotorParamsS[i].Address,
					MotorParamsS[i].MinCurrent,
					MotorParamsS[i].AccCurrent,
					MotorParamsS[i].MaxCurrent,
					MotorParamsS[i].Microstepping,
					MotorParamsS[i].Pulley,
					MotorParamsS[i].Reduction,
					MotorParamsS[i].Driver,
					MotorParamsS[i].Current,
					MotorParamsS[i].KP_speed,
					MotorParamsS[i].KI_speed,
					MotorParamsS[i].KP_pos,
					MotorParamsS[i].LineEnc,
					MotorParamsS[i].PulsesToMm,
					MotorParamsS[i].Poles,
					MotorParamsS[i].Jerk,
					MotorParamsS[i].KA,
					MotorParamsS[i].KS,
					MotorParamsS[i].KC,
					MotorParamsS[i].HomeFast,
					MotorParamsS[i].HomeSlow,
					MotorParamsS[i].PPR,
					MotorParamsS[i].Profile,
					MotorParamsS[i].EndMovementDelta,
	 				MotorParamsS[i].SpykeDelta,
  					MotorParamsS[i].RedCurrent,
  					MotorParamsS[i].Direction,
  					MotorParamsS[i].Id) );
		}
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// LoadIOParams
// Carica dal DB la tabella IOParams
//----------------------------------------------------------------------------------
int SRDatabase::LoadIOParams()
{
	try
	{
		wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxT("SELECT * FROM IOParams") );

		int i = 0;
		while( q.NextRow() )
		{
			IOParamsS[i].Id			= q.GetInt( wxT("Id") );
			IOParamsS[i].Type		= q.GetInt( wxT("Type") );
			IOParamsS[i].DriverId	= q.GetInt( wxT("DriverId") );
			IOParamsS[i].DriverPort	= q.GetInt( wxT("DriverPort") );
			i++;
		}
	}
	catch( wxSQLite3Exception& exc)
	{
		cout<<" Exception in LoadIOParams: "<<exc.GetMessage()<<endl;
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SaveIOParams
// Salva nel DB la tabella IOParams
//----------------------------------------------------------------------------------
int SRDatabase::SaveIOParams()
{
	try
	{
		wxSQLite3StatementBuffer stmtBuffer;

		for( int i = 0; i < NUM_IO; i++ )
		{
			_SR3200.ExecuteUpdate( stmtBuffer.Format("UPDATE IOParams SET Type = %d, DriverId = %d, DriverPort = %d WHERE Id = %d;",
					IOParamsS[i].Type,
					IOParamsS[i].DriverId,
					IOParamsS[i].DriverPort,
					IOParamsS[i].Id) );
		}
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// LoadSpeedTable
// Carica dal DB la tabella SpeedTable
//----------------------------------------------------------------------------------
int SRDatabase::LoadSpeedTable()
{
	try
	{
		wxSQLite3ResultSet q = _SR3200.ExecuteQuery( wxT("SELECT * FROM SpeedTable") );

		int i = 0;
		while( q.NextRow() )
		{
			SpeedTableS[i].Id		= q.GetInt( wxT("Id") );
			SpeedTableS[i].Speed[0]	= q.GetInt( wxT("LowSpeed") );
			SpeedTableS[i].Speed[1]	= q.GetInt( wxT("NormalSpeed") );
			SpeedTableS[i].Speed[2]	= q.GetInt( wxT("HighSpeed") );
			SpeedTableS[i].Acc[0]	= q.GetInt( wxT("LowAcc") );
			SpeedTableS[i].Acc[1]	= q.GetInt( wxT("NormalAcc") );
			SpeedTableS[i].Acc[2]	= q.GetInt( wxT("HighAcc") );
			SpeedTableS[i].Dec[0]	= q.GetInt( wxT("LowDec") );
			SpeedTableS[i].Dec[1]	= q.GetInt( wxT("NormalDec") );
			SpeedTableS[i].Dec[2]	= q.GetInt( wxT("HighDec") );
			i++;
		}
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SaveSpeedTable
// Salva nel DB la tabella SpeedTable
//----------------------------------------------------------------------------------
int SRDatabase::SaveSpeedTable()
{
	try
	{
		wxSQLite3StatementBuffer stmtBuffer;

		for( int i = 0; i < NUM_SPEEDS; i++ )
		{
			_SR3200.ExecuteUpdate( stmtBuffer.Format("UPDATE SpeedTable SET LowSpeed = %d, NormalSpeed = %d, HighSpeed = %d, LowAcc = %d, NormalAcc = %d, HighAcc = %d, LowDec = %d, NormalDec = %d, HighDec = %d WHERE Id = %d;",
					SpeedTableS[i].Speed[0],
					SpeedTableS[i].Speed[1],
					SpeedTableS[i].Speed[2],
					SpeedTableS[i].Acc[0],
					SpeedTableS[i].Acc[1],
					SpeedTableS[i].Acc[2],
					SpeedTableS[i].Dec[0],
					SpeedTableS[i].Dec[1],
					SpeedTableS[i].Dec[2],
					SpeedTableS[i].Id) );
		}
	}
	catch( wxSQLite3Exception& )
	{
		return SR_ERROR;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SetFiducialParams
// Associa i puntatori all'insieme di parametri selezionato
//----------------------------------------------------------------------------------
void SRDatabase::SetFiducialParams( int type )
{
	switch( type )
	{
	case FIDUCIAL_ROT1:
	case FIDUCIAL_ROT2:
	case FIDUCIAL_TRA:
	case FIDUCIAL_ROT1_FRAME:
	case FIDUCIAL_ROT2_FRAME:
	case FIDUCIAL_TRA_FRAME:
	case FIDUCIAL_ROT1_A:
	case FIDUCIAL_ROT2_A:
	case FIDUCIAL_TRA_A:
	case FIDUCIAL_ROT1_FRAME_A:
	case FIDUCIAL_ROT2_FRAME_A:
	case FIDUCIAL_TRA_FRAME_A:
		pCurrentFiducial = &FiducialParamsS[type];
		break;

	case FIDUCIAL_OFFSET:
		pCurrentFiducial = &offsetDParamsS;
		break;

	case FIDUCIAL_OFFSET_FRAME:
		pCurrentFiducial = &offsetUParamsS;
		break;

	case FIDUCIAL_VISION_TEST:
		pCurrentFiducial = &visionTestParamsS;
		break;
	}
}

//----------------------------------------------------------------------------------
// ResetVerifyPoints
// Resetta i punti di verifica della produzione corrente
//----------------------------------------------------------------------------------
void SRDatabase::ResetVerifyPoints()
{
	for( int i = 0; i < NUM_VERIFY_POINTS; i++ )
	{
		VerifyPointsS[i].X = 0.0;
		VerifyPointsS[i].Y = 0.0;
	}
	SaveVerifyPoints();
}

//----------------------------------------------------------------------------------
// AdjustVerifyPoints
// Modifica i punti di verifica della produzione corrente
//----------------------------------------------------------------------------------
void SRDatabase::AdjustVerifyPoints( float x, float y )
{
	for( int i = 0; i < NUM_VERIFY_POINTS; i++ )
	{
		if( VerifyPointsS[i].X != 0.0 && VerifyPointsS[i].Y != 0.0 )
		{
			VerifyPointsS[i].X -= x;
			VerifyPointsS[i].Y -= y;
		}
	}
	SaveVerifyPoints();
}

//----------------------------------------------------------------------------------
// ResetPinsPoints
// Resetta i punti di posizionamento pins della produzione corrente
//----------------------------------------------------------------------------------
void SRDatabase::ResetPinsPoints()
{
	for( int i = 0; i < NUM_PINS_POINTS; i++ )
	{
		PinsPointsS[i].X = 0.0;
		PinsPointsS[i].Y = 0.0;
	}
	SavePinsPoints();
}

//----------------------------------------------------------------------------------
// AdjustPinsPoints
// Modifica i punti di posizionamento pins della produzione corrente
//----------------------------------------------------------------------------------
void SRDatabase::AdjustPinsPoints( float x, float y )
{
	for( int i = 0; i < NUM_PINS_POINTS; i++ )
	{
		if( PinsPointsS[i].X != 0.0 && PinsPointsS[i].Y != 0.0 )
		{
			PinsPointsS[i].X -= x;
			PinsPointsS[i].Y -= y;
		}
	}
	SavePinsPoints();
}



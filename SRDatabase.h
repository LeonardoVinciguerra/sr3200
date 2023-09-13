//---------------------------------------------------------------------------
//
// Name:        SRDatabase.h
// Author:      Gabriel Ferri
// Created:     11/04/2008
// Description: SRDatabase class declaration
//
//---------------------------------------------------------------------------
#ifndef __SRDATABASE_H
#define __SRDATABASE_H

#include "SRDB100.h"
#include "SRDB200.h"
#include "dbSPI_100.h"
#include <wx/wxsqlite3.h>
#include "GlobalDefs.h"
#include <wx/string.h>
#include <wx/arrstr.h>
#include <vector>
using namespace std;


	//------------//
	// DB Structs //
	//------------//

typedef ActualProductionStruct_100	ActualProductionStruct;
typedef ProductionDataStruct_100	ProductionDataStruct;
typedef FiducialParamsStruct_100	FiducialParamsStruct;
typedef WorkingModesStruct_201		WorkingModesStruct;
typedef VerifyPointsStruct_100		VerifyPointsStruct;
typedef SpeedTableStruct_100		SpeedTableStruct;
typedef LimitsStruct_100			LimitsStruct;
typedef SerialParamsStruct_100		SerialParamsStruct;
typedef IOParamsStruct_100			IOParamsStruct;
typedef MotorParamsStruct_202		MotorParamsStruct;
typedef MachineParamsStruct_200		MachineParamsStruct;
typedef OffsetPointsStruct_100		OffsetPointsStruct;
typedef PinsPointsStruct_100		PinsPointsStruct;
typedef OffsetCheckPointsStruct_100	OffsetCheckPointsStruct;

// dbSPI.db //
typedef InspectionSitesStruct_100	InspectionSitesStruct;
typedef ExceptionsStruct_100		ExceptionsStruct;

//aggiunto
typedef AUTOInspectionSitesStruct_100	AUTOInspectionSitesStruct;
typedef InspectionPointResult_100 InspectionPointResult;
typedef InspectionPointRecord_100 InspectionPointRecord;
typedef EstimatedSiteTraslation_100 EstimatedSiteTraslation;

struct InspectionPointStruct
{
	int WhitePixels;
	float XCentroidWhite;
	float YCentroidWhite;
	float PercentageCovered;
};

struct InspectionAreasStruct
{
	int SearchArea;
	int Alarm;
	int Result;
};



typedef RecordedBoardStruct_100 RecordedBoardStruct;

	//------------------//
	// SRDatabase Class //
	//------------------//

class SRDatabase
{
public:
	SRDatabase( const wxString& machineDB, const wxString& AUTOspiDB);
	~SRDatabase();

	int Backup( const wxString &backupFile );
	int Restore( const wxString &restoreFile );

	bool CheckVersion( const wxString ver );
	int Update();
	int From_100_to_200( const char *db_file_in );
	int From_200_to_201();
	int From_201_to_202();
	int From_202_to_203();

	int LoadProductionStructsFromDB( int id );
	int LoadProductionStructsFromDB( const wxString &prodName );
	int LoadMachineStructsFromDB();

	// Production Names
	int LoadProductionNames();
	wxArrayString ProductionNames;

	// Insert/Delete Production
	int InsertProduction( const wxString &prodName, float squeegeesDefZeroMove );
	int DeleteProduction( int id , bool KeepResults);

	// Production Structs
	int LoadActualProduction();
	int SaveActualProduction();
	int LoadProductionData( int id );
	int LoadProductionData( const wxString &prodName );	
	int SaveProductionData();
	int LoadFiducialParams();
	int LoadZeroCamParams();
	int SaveFiducialParams();
	int LoadVerifyPoints();
	int SaveVerifyPoints();
	int LoadWorkingModes();
	int SaveWorkingModes();
	int LoadPinsPoints();
	int SavePinsPoints();


	// Machine Structs
	int LoadMachineParams();
	int SaveMachineParams();
	int LoadOffsetPoints();
	int SaveOffsetPoints();
	int LoadOffsetCheckPoints();
	int SaveOffsetCheckPoints();
	int CorrectOffsetPoints();
	int CreateOffsetCheckPoints();
	int ResetOffsetCheckPoints();
	int LoadLimits();
	int SaveLimits();
	int LoadSerialParams();
	int SaveSerialParams();
	int LoadMotorParams();
	int SaveMotorParams();
	int LoadIOParams();
	int SaveIOParams();
	int LoadSpeedTable();
	int SaveSpeedTable();
	int SaveCameraZero();
	int SaveCurrentGlobalOffsetValues();
	int ResetProductionOffsetValues();

	ProductionDataStruct	ProductionDataS;
	ActualProductionStruct	ActualProductionS;
	FiducialParamsStruct	FiducialParamsS[NUM_FIDUCIALS];
	VerifyPointsStruct		VerifyPointsS[NUM_VERIFY_POINTS];
	WorkingModesStruct		WorkingModesS;
	SpeedTableStruct		SpeedTableS[NUM_SPEEDS];
	LimitsStruct			LimitsS[NUM_MOTORS];
	SerialParamsStruct		SerialParamsS[NUM_SERIALS];
	IOParamsStruct			IOParamsS[NUM_IO];
	MotorParamsStruct		MotorParamsS[NUM_MOTORS];
	MachineParamsStruct		MachineParamsS;
	OffsetPointsStruct		OffsetPointsS[NUM_OFFSET_POINTS];
	OffsetPointsStruct		GlobalOffset;
	OffsetCheckPointsStruct	OffsetCheckPointsS[NUM_OFFSET_POINTS];
	PinsPointsStruct		PinsPointsS[NUM_PINS_POINTS];

	wxString dbFile;

	// Offset pattern params (volatile)
	FiducialParamsStruct	offsetUParamsS;
	FiducialParamsStruct	offsetDParamsS;
	// Vision test params (volatile)
	FiducialParamsStruct	visionTestParamsS;
	// CameraZero params
	FiducialParamsStruct	CameraZeroParamsS;

	// Fiducial params pointers - params linked to the GUI
	void SetFiducialParams( int type );
	FiducialParamsStruct *pCurrentFiducial;

	// Verify points
	void ResetVerifyPoints();
	void AdjustVerifyPoints( float x, float y );

	// Pins points
	void ResetPinsPoints();
	void AdjustPinsPoints( float x, float y );

	// Inspection sites
	InspectionSitesStruct	InspectionSitesS[NUM_INSPECTION_SITES];
	InspectionAreasStruct	InspectionAreasS[NUM_INSPECTION_AREAS];
	//aggiunto
	AUTOInspectionSitesStruct 	AUTOInspectionSiteStruct[NUM_INSPECTION_SITES];
	InspectionPointResult 		AUTOInspectionResults[NUM_INSPECTION_POINTS];

	InspectionPointRecord  	AUTOInspectionPointRecord[NUM_INSPECTION_RESULTS];

	//vector<cv::Point2f> 			InspectionSiteSuggestedCorrection;
	EstimatedSiteTraslation	InspectionSiteSuggestedCorrection[NUM_INSPECTION_SITES];

	vector<double> theta;
	double estimated_rotation;

	RecordedBoardStruct RecordedBoardstruct[NUM_INSPECTION_POINTS]; //set the max value to 500

	wxSQLite3Database _SR3200;

	//aggiunto
	wxSQLite3Database _DBspiAUTO;


	//
	int LoadInspectionSites();
	int SaveInspectionSite( int siteNum );
	int SaveInspectionSiteMask();
	int UpdateName( int siteNum );
	int InsertInspectionSite();
	int DeleteInspectionSite( int siteNum );
	int DeleteInspectionSiteAll( int idProd , bool KeepResults);
	int ClearInspectionSite( int siteNum );
	bool UpdateAlarmAndWarning(wxString Warning, wxString Alarm, int IDSite);

	bool WriteSPIparams();
	bool RestoreSPIparams();
	bool RestoreSPIparamsPhase2();

	//results
	int SaveResults();
	int ResultsCount(){ return Spots2Save ; }; //should return the number of structures
	int SpotsCount(){ return SavedResult ; }; //should return the number of structures
	bool ClearResultStruct();
	bool DeleteBoardResults(int IDprod, int BoardNum);


	//
	bool SiteIsFirst() { return pAUTOInspectionCurrentSiteStruct==AUTOInspectionSiteStruct;};
	bool SiteIsLast() { return pAUTOInspectionCurrentSiteStruct==&AUTOInspectionSiteStruct[sitesNum-1];};
	bool SiteFirst();
	bool SiteLast();
	bool SiteNext();
	bool SitePrev();
	int SiteGetSelected();
	bool SiteSelect( int pos );
	int SiteCount() { return sitesNum; };

	int LoadResultsSites( int BoardNumber, int IDprod, int SiteNum);
	bool ClearBoardStruct();
	bool ClearPointsStruct();
	wxString LoadProductionName ( int IDprod );
	wxArrayString LoadAllNames();
	//
	AUTOInspectionSitesStruct* pAUTOInspectionCurrentSiteStruct;


	int SiteAreaCount() { return siteAreasNum; };
	bool SiteAreaSelect( int num );
	int SiteAreaGetSelected();
	int SiteAreaAdd();
	int SiteAreaRemove( int num );
	void SiteAreaRemoveAll();




	void SiteSavePosition();
	void SiteRestorePosition();

	PointD fidTra;
	PointD boardTra;
	PointD cameraZeroFound;
	int savedArea;
	int siteAreasNum;
	int final_id_spots;
	int final_id_results;
	int SavedResult;
	int Selected_row;
	int Spots2Save;

	int SelectedBoardNumber;
	int SelectedIDprod;
	int SelectedSite;
	int AllFaultyStatus;
	int AllWarningStatus;

	cv::Scalar ALARM_COLOR;
	cv::Scalar WARNING_COLOR;
	cv::Scalar SHORT_COLOR;

	//ViewResults
	int LoadBoards(wxString Name);
	int BoardsNum();
	int recordNum;

	int RecordedsitesNum;
	int RecordedSiteCount() { return RecordedsitesNum; };



private:
	//int From_100_to_101( const char *db_file_in, const char *db_file_out ); //COME ESEMPIO!!!
	int sitesNum;
	//
	int savedSite;

};

#endif

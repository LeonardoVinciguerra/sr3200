//---------------------------------------------------------------------------
//
// Name:        dbSPI_100.h
// Author:      Gabriel Ferri
// Created:     18/05/2011
// Description: dbSPI class declaration
//
//---------------------------------------------------------------------------
#ifndef __DBSPI_100_H
#define __DBSPI_100_H

//aggiunto
#include <vector>
#ifdef __WXMSW__
	#include <wx/msw/winundef.h>
	#include <cv.h>
	#include <highgui.h>
#else
	#include <opencv/cv.h>
	#include <opencv/highgui.h>
#endif


struct InspectionSitesStruct_100
{
	int IdSite;			// unico all'interno della produzione
	int IdProd;
	wxString Name;
	float X;
	float Y;
	int BinarizationThr;
	int Enable;
	float CameraBrightness;
	float CameraContrast;
	int PointsNum;
	wxString Points;
	int AreasNum;
	wxString Areas;
	int Type;
	int BGABallDiameter; // mm/100
};

struct ExceptionsStruct_100
{
	int Id;
	int Type;		// 0: NULL
					// 1: BGA
	wxString Filename;
	int Param1;		// BGA: ball diameter (mm/100)
	int Param2;		// BGA: threshold (0-100)
};

struct coupled_spots
	{
		cv::vector<int> Mask;
		cv::vector<int> PCB;
	};

#endif //__DBSPI_100_H

struct AUTOInspectionSitesStruct_100
{
	int IdSite;
	wxString Name;
	float X;
	float Y;
	float Orientation;
	int BinarizationThr;
	int Enable;
	float CameraBrightness;
	float CameraContrast;
	int PointsNum;
	int IdProd;

	std::vector<double> Area;
	std::vector<cv::Point2f> Centroids;
	std::vector<std::vector<cv::Point> > Contours;
	std::vector<bool> SpotEnable;

	std::vector<double> Area_Mask;
	std::vector<cv::Point2f> Centroids_Mask;
	std::vector<std::vector<cv::Point> > Contours_Mask;

	coupled_spots Coupled_spots;
	std::vector<double> Uncovered_Area;
	int Alarm;
	int Warning;
	wxString Type;
	int ImgScaleFactor;

	int BestChannel;
	float BestHue;
	int PadThreshold;


	int PasteCentralHUE;
	int PasteHUEWidth;
	int BestChannelPads;
	int CentralPadsColor;
	int PadsColorWidth;



};

struct InspectionPointResult_100
{
	int SpotNum;
	int White_pixels;
	float SiteX; //x Pad
	float SiteY; //y Pad
	float Percentage_covered;
	float WhiteX; //white region
	float WhiteY; //white region
	int Connected;
};

struct EstimatedSiteTraslation_100
{
	double x;
	double y;
};

struct InspectionPointRecord_100{

	int SpotNum;
	int White_pixels;
	float x;
	float y;
	float Percentage_covered;
	int ConnectedWith; // this contains the spotID connected with the selected spot
	//wxString SiteName; //a bit redundant
	//std::string SiteName;
	char SiteName[50];
	int SiteNum; //id is unique for each site, this number indicates the position of the site inside the production (es id=28, sitenum=0, id=43 sitenum+1..)
	int Alarm;
	int Warning;
	cv::Point Centroids_PCB;
	int ID_Site;
};

struct RecordedBoardStruct_100
{
	int ID_production;
	wxString ProductionName;
	int BoardNumber;
	int WhiteAreas;
	int ConnectedSpots;
	long int Time; //seconds from 1st jan 1970

};

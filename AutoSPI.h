//---------------------------------------------------------------------------
//
// Name:        AutoSPI.h
// Author:      Daniele Pelitti
// Created:     05/06/2017
// Description: SPI (Solder Paste Inspection) functions implementation
//
//---------------------------------------------------------------------------
#ifndef __AUTOSPI_H
#define __AUTOSPI_H

#ifdef __WXMSW__
	#include <wx/msw/winundef.h>
	#include <cv.h>
	#include <highgui.h>
#else
	#include <opencv/cv.h>
	#include <opencv/highgui.h>
#endif

#include <wx/string.h>
#include "GlobalDefs.h"
#include "SRMachine.h"
#include "wxCameraControl.h"

//TEMP - da sistemare
#define CAM_W				640
#define CAM_H				480
//TEMP - da sistemare
//probabily they're useless
#define SPI_ROI_W			(CAM_W-60)
#define SPI_ROI_H			(CAM_H-60)
#define SPI_ROI_X			(CAM_W/2 - SPI_ROI_W/2)
#define SPI_ROI_Y			(CAM_H/2 - SPI_ROI_H/2)

//
#define SPI_SMOOTH			9
#define SPI_LOW_THR			0.65
#define MIN_CONTOUR_AREA	25.0	// quadrato 5x5

//TEMP_BGA
#define BGA_AREA_USE		0.5f
#define BGA_AREA_DRAW		0.2f

//
#define CONTOUR_MAX_LEVEL		8
#define CONTOUR_DISABLE_COLOR	CV_RGB(0,128,255)
#define CONTOUR_ENABLE_COLOR	CV_RGB(0,255,0)
//end useless

struct Contours_and_proprieties
		{
			vector<vector<cv::Point> > contours;
			vector<cv::Point2f> centroids;
			vector<double> Areas;
		};




struct connected_domains
	{
		cv::vector<int> domain_a;
		cv::vector<int> domain_b;
	};

enum type_shift
{
	HORIZONTAL,
	VERTICAL
};

enum type_threshold{
	adaptive,
	simple
};

enum channels {
	BLUE_CHANNEL,
	GREEN_CHANNEL,
	RED_CHANNEL,
	COMPOSITE_CHANNEL
};




class AutoSPIProc
{
public:
	AutoSPIProc( SRMachine* SRRef, SmartLog* smartLoggerRef, wxCameraControl *cameraRef, wxWindow* parentRef );
	~AutoSPIProc();
	void spiDraw( cv::Mat* image );
	int FindRegions(cv::Mat* image, int type, bool newFind); 		//find the spots
	coupled_spots MatchRegions (bool first_time);
	int TogglePointAt( PointI position );
	int spiSetPointsInsideRect( PointI p1, PointI p2, bool check );
	int CorrectTraslation();
	int LoadDraw( cv::Mat* image, int type);

	int AdaptScale(cv::Mat* currentPicture);
	double ScaleCost( bool overwrite, int pixel_cut=0);
	cv::Mat Resize (cv::Mat* image, double i, int direction);
	bool ComputeSupposedUncoveredArea ();


	void spiDrawMouseDrag( const PointI& p1, const PointI& p2, cv::Mat* Image );
	int spiTogglePointAt( PointI position );

	bool spiSelectThresholdMat( cv::Mat* pImage_8, PointI p1, PointI p2 );
	int spiCountWhitePixels( IplImage* img, RectI bb, int searchArea );
	int spiGetPointAt( PointI position );

private:

	float norm2 (cv::Point2f v1, cv::Point2f v2);

	coupled_spots Coupled_Spots;

	SRMachine *SR;
	SmartLog *smartLogger;
	wxCameraControl *camera;
	wxWindow *parent;

	IplImage* spiImg_8;
	IplImage* spiImg_8_lowThr;
	IplImage* spiImg_24;
	IplImage* spiImg_Drag_24;
	CvMemStorage* spiStorageFind;
	CvMemStorage* spiStorageDraw;


	//aggiunto
	cv::Mat* Mat_Img;
	//int current_site=0;
	int current_site;
	int Border_distance_inspection_rectangle; //change it in wxCameraControl.h (defs) distance_inspection_rectangle
};



class AutoSPICheck
{
public:

	AutoSPICheck( SRDatabase *DBRef, SRMachine *SRRef, wxCameraControl *cameraRef );
	~AutoSPICheck();
	void Initialize();

	bool CheckImages( int idSite );
	bool Inspect( cv::Mat* frame,  cv::Mat* frameHighExposure, const PointI& offset, bool suggestCorrections ); //find white spots after printing
	void EstimateCorrection();
	void ShowResults( cv::Mat* image, bool drawSearchArea, const PointI& offset );


	double MutualEntropy (cv::Mat* reference, cv::Mat* target);

	bool Align (cv::Mat* reference, cv::Mat* target, float &x, float &y); //align frames
	bool Align (cv::Mat* reference, wxString fullpath, float &x, float &y);

	double Entropy (cv::Mat* image);
	void Merge4Images(cv::Mat* Xplus, cv::Mat* Xminus, cv::Mat* Yplus, cv::Mat* Yminus, cv::Mat* dest, float shift=0);

	bool FindPaste(cv::Mat* frame, cv::Mat* frameHighExposure);
	bool FindUncoveredPads(cv::Mat* frame);



	cv::Mat Resize (cv::Mat* image, double i, int direction);

	cv::Mat RegionGrowingMean (cv::Mat* image, cv::Point seed, int connectivity, int Thr, int Npixels);

	cv::Mat TemplateImg;

	bool SPIdrawings;

private:
	float norm2 (cv::Point2f v1, cv::Point2f v2);
	int whitePixels( cv::Mat Image);


	SRDatabase* DB;
	SRMachine* SR;
	bool initFlag;
	wxCameraControl *camera;







};
#endif //__AUTOSPI_H

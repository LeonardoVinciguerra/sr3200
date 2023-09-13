//---------------------------------------------------------------------------
//
// Name:        FindCircle.cpp
// Author:      Gabriel Ferri
// Created:     07/10/2008
// Description: FindCircle function implementation
//
//---------------------------------------------------------------------------

#include "wxCameraControl.h"
#include <wx/image.h>
#include <wx/dcmemory.h>
#include <wx/dcbuffer.h>
#include "GlobalUtils.h"
#include "hough.h"

//----------------------------------------------------------------------------------
// FindCircle2
// Find the nearest circle to the expected position.
// ATTENTION!!! - Before calling this function you MUST call GetFrames() function
//----------------------------------------------------------------------------------
int wxCameraControl::FindCircle2( int expectedX, int expectedY, float &X, float &Y, float &R )
{
	// Cropping
	int searchArea = (SR->DB->pCurrentFiducial->CircleDiameter + SR->DB->pCurrentFiducial->Tolerance) * SR->DB->pCurrentFiducial->SearchAreaMul;
	int roi_x = MAX( 0, expectedX - searchArea / 2.0 );
	int roi_y = MAX( 0, expectedY - searchArea / 2.0 );
	int roi_w = MIN( CAM_W - 1, roi_x + searchArea ) - roi_x;
	int roi_h = MIN( CAM_H - 1, roi_y + searchArea ) - roi_y;

	IplImage *crop = cvCreateImage( cvSize(roi_w, roi_h), IPL_DEPTH_8U, 1 );

	cvSetImageROI( openCVFramesArray[0], cvRect( roi_x, roi_y, roi_w, roi_h ) );
	cvCopy( openCVFramesArray[0], crop );
	cvResetImageROI( openCVFramesArray[0] );

	// control FilterSmoothDim value
	int filterSmoothDim = SR->DB->pCurrentFiducial->FilterSmoothDim | 0x00000001;

	// Improve edge detection reducing image background noise
	cvSmooth( crop, crop, SR->DB->pCurrentFiducial->FilterSmoothType + 1, filterSmoothDim, filterSmoothDim );

	// Edge detection
	IplImage *edges = cvCreateImage( cvSize(crop->width, crop->height), IPL_DEPTH_8U, 1 );
	cvCanny( crop, edges, SR->DB->pCurrentFiducial->FilterEdgeThr/2, SR->DB->pCurrentFiducial->FilterEdgeThr, 3 );

	// radii array
	CvMat *radii = cvCreateMat( 1, SR->DB->pCurrentFiducial->Tolerance+1, CV_32F );
	int minRadius = ( SR->DB->pCurrentFiducial->CircleDiameter - SR->DB->pCurrentFiducial->Tolerance ) / 2.0;
	cvRange( radii, minRadius, minRadius + radii->cols );

	// edges matrix
	CvMat stub, *edges_mat = (CvMat*)edges;
	edges_mat = cvGetMat( edges_mat, &stub );

	// resolution
	float dp = 0.5;

	// search circle
	int x, y, index;
	houghCircle( edges_mat, radii, dp, x, y, index, MID( 0.0, SR->DB->pCurrentFiducial->CircleAccum/100.0, 1.0 ) );

	if( index != -1 )
	{
		// returned values are in ROI coordinates
		X = x*dp + roi_x;
		Y = y*dp + roi_y;
		R = cvGetReal1D( radii, index );
	}

	// Clean
	cvReleaseImage( &crop );
	cvReleaseImage( &edges );
	cvReleaseMat( &radii );

	// draw search area & circle
	wxBitmap bmp = wxImage( CAM_W, CAM_H, (unsigned char*)openCVFrame_24->imageData, true );
	wxMemoryDC dc;

	dc.SelectObject( bmp );
	dc.SetBrush( *wxTRANSPARENT_BRUSH );

	if( SR->DB->WorkingModesS.DebugMode )
	{
		dc.SetPen( wxPen( wxColour( 0, 255, 0 ) ) );
		dc.DrawRectangle( roi_x, roi_y, roi_w, roi_h );
	}
	if( index != -1 )
	{
		dc.SetPen( wxPen( wxColour( 255, 0, 0 ) ) );
		dc.DrawCircle( X, Y, R );
	}

	dc.SelectObject( wxNullBitmap );
	videoMain->SetImage( bmp );

	return index == -1 ? SR_ERROR : SR_OK;
}

//----------------------------------------------------------------------------------
// FindCircleAccurate
// Find the nearest circle to the expected position. Performs also centroid check
//----------------------------------------------------------------------------------
int wxCameraControl::FindCircleAccurate( int expectedX, int expectedY, float &X, float &Y, float &R )
{
	// Cropping
	int searchArea = (SR->DB->pCurrentFiducial->CircleDiameter + SR->DB->pCurrentFiducial->Tolerance) * SR->DB->pCurrentFiducial->SearchAreaMul;
	int roi_x = MAX( 0, expectedX - searchArea / 2.0 );
	int roi_y = MAX( 0, expectedY - searchArea / 2.0 );
	int roi_w = MIN( CAM_W - 1, roi_x + searchArea ) - roi_x;
	int roi_h = MIN( CAM_H - 1, roi_y + searchArea ) - roi_y;

	IplImage *crop = cvCreateImage( cvSize(roi_w, roi_h), IPL_DEPTH_8U, 1 );

	cvSetImageROI( openCVFramesArray[0], cvRect( roi_x, roi_y, roi_w, roi_h ) );
	cvCopy( openCVFramesArray[0], crop );
	cvResetImageROI( openCVFramesArray[0] );

	// control FilterSmoothDim value
	int filterSmoothDim = SR->DB->pCurrentFiducial->FilterSmoothDim | 0x00000001;

	// Improve edge detection reducing image background noise
	cvSmooth( crop, crop, SR->DB->pCurrentFiducial->FilterSmoothType + 1, filterSmoothDim, filterSmoothDim );

	// Edge detection
	IplImage *edges = cvCreateImage( cvSize(crop->width, crop->height), IPL_DEPTH_8U, 1 );
	cvCanny( crop, edges, SR->DB->pCurrentFiducial->FilterEdgeThr/2, SR->DB->pCurrentFiducial->FilterEdgeThr, 3 );

	// radii array
	CvMat *radii = cvCreateMat( 1, SR->DB->pCurrentFiducial->Tolerance+1, CV_32F );
	int minRadius = ( SR->DB->pCurrentFiducial->CircleDiameter - SR->DB->pCurrentFiducial->Tolerance ) / 2.0;
	cvRange( radii, minRadius, minRadius + radii->cols );

	// edges matrix
	CvMat stub, *edges_mat = (CvMat*)edges;
	edges_mat = cvGetMat( edges_mat, &stub );

	// resolution
	float dp = 0.5;

	// search circle
	int x, y, index;
	houghCircle( edges_mat, radii, dp, x, y, index, MID( 0.0, SR->DB->pCurrentFiducial->CircleAccum/100.0, 1.0 ) );

	if( index != -1 )
	{
		// returned values are in ROI coordinates
		X = x*dp + roi_x;
		Y = y*dp + roi_y;
		R = cvGetReal1D( radii, index );
	}else{
		return SR_ERROR;
	}

	//Centroid
	cv::Mat centroidImage = cv::Mat(crop, true);
	int dynamicThreshold = centroidImage.at<uchar>(centroidImage.cols/2, centroidImage.rows/2)*0.9;
	cv::threshold(centroidImage,centroidImage,dynamicThreshold, 255, cv::THRESH_BINARY);

	vector<vector<cv::Point> > contours;
	cv::findContours(centroidImage, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
	//Remove the outer contours!
	vector<vector<cv::Point> > GoodContours;
	const int externalBorderRemoval = 10;
	for (int i = 0; i < contours.size(); ++i){
		// Check area
		bool exit_cycle = false;
		for (int j = 0; j < contours[i].size(); j++){
			if(contours[i][j].x<externalBorderRemoval||contours[i][j].x>centroidImage.cols-externalBorderRemoval)
			{
				exit_cycle=true;
				break;
			};
			if(contours[i][j].y<externalBorderRemoval||contours[i][j].y>centroidImage.rows-externalBorderRemoval)
			{
				exit_cycle=true;
				break;
			};
		}

		if (exit_cycle){
			continue;
		}

		GoodContours.push_back(contours[i]);
	}



	int minArea = 999999;
	int minIndex = -1;
	for(int i = 0; i<GoodContours.size(); i++ ){
		int area_region= cv::contourArea(GoodContours[i]);
		if( (area_region < minArea) && (area_region>MIN_AREA_SPI)){
			minArea = area_region;
			minIndex = i;
		}
	}

	if(minIndex != -1){
		cv::Moments mu = cv::moments( GoodContours[minIndex] );
		double positionX = mu.m10/mu.m00;
		double positionY = mu.m01/mu.m00;
		cout<<"Posizioni fiduciale houges: "<< x*dp<< " "<< y*dp<<" Posizione centroide "<<positionX<<" "<<positionY;
		if(fabs(positionX - centroidImage.cols/2) > MAX_CHECK_DISALIGNMENT_PX){
			return SR_ERROR;
		}
		if(fabs(positionY - centroidImage.rows/2) > MAX_CHECK_DISALIGNMENT_PX){
			return SR_ERROR;
		}
		X = positionX + roi_x;
		Y = positionY + roi_y;
	}else{
		return SR_ERROR;
	}
	//Salvare foto fiduciale x experimental!
	//wxString fullpath( FILE_FIDUCIALS_FOLDER);
	//fullpath.Append( wxString::Format("Fiducial_%s_%d.jpeg", SR->DB->ProductionDataS.ProductionName.ToAscii(), SR->DB->ProductionDataS.Counter ));
	//cv::Mat imgToSave = cv::Mat(openCVFramesArray[0], true);
	//cv::circle(imgToSave, cv::Point(X,Y), R, cv::Scalar(0));
	//cv::imwrite( fullpath.ToAscii(),  imgToSave );


	// Clean
	cvReleaseImage( &crop );
	cvReleaseImage( &edges );
	cvReleaseMat( &radii );

	// draw search area & circle
	wxBitmap bmp = wxImage( CAM_W, CAM_H, (unsigned char*)openCVFrame_24->imageData, true );
	wxMemoryDC dc;

	dc.SelectObject( bmp );
	dc.SetBrush( *wxTRANSPARENT_BRUSH );

	if( SR->DB->WorkingModesS.DebugMode )
	{
		dc.SetPen( wxPen( wxColour( 0, 255, 0 ) ) );
		dc.DrawRectangle( roi_x, roi_y, roi_w, roi_h );
	}
	if( index != -1 )
	{
		dc.SetPen( wxPen( wxColour( 255, 0, 0 ) ) );
		dc.DrawCircle( X, Y, R );
	}

	dc.SelectObject( wxNullBitmap );
	videoMain->SetImage( bmp );

	return index == -1 ? SR_ERROR : SR_OK;
}

int wxCameraControl::FindCircleCameraZero( int expectedX, int expectedY, float &X, float &Y, float &R )
{
	// Cropping
	int searchArea = (SR->DB->CameraZeroParamsS.CircleDiameter + SR->DB->CameraZeroParamsS.Tolerance) * SR->DB->CameraZeroParamsS.SearchAreaMul;
	int roi_x = MAX( 0, expectedX - searchArea / 2.0 );
	int roi_y = MAX( 0, expectedY - searchArea / 2.0 );
	int roi_w = MIN( CAM_W - 1, roi_x + searchArea ) - roi_x;
	int roi_h = MIN( CAM_H - 1, roi_y + searchArea ) - roi_y;

	IplImage *crop = cvCreateImage( cvSize(roi_w, roi_h), IPL_DEPTH_8U, 1 );


	cvSetImageROI( openCVFramesArray[0], cvRect( roi_x, roi_y, roi_w, roi_h ) );
	cvCopy( openCVFramesArray[0], crop );
	cvResetImageROI( openCVFramesArray[0] );

	// control FilterSmoothDim value
	int filterSmoothDim = SR->DB->CameraZeroParamsS.FilterSmoothDim | 0x00000001;

	// Improve edge detection reducing image background noise
	cvSmooth( crop, crop, SR->DB->CameraZeroParamsS.FilterSmoothType + 1, filterSmoothDim, filterSmoothDim );

	// Edge detection
	IplImage *edges = cvCreateImage( cvSize(crop->width, crop->height), IPL_DEPTH_8U, 1 );
	cvCanny( crop, edges, SR->DB->CameraZeroParamsS.FilterEdgeThr/2, SR->DB->CameraZeroParamsS.FilterEdgeThr, 3 );


	// radii array
	CvMat *radii = cvCreateMat( 1, SR->DB->CameraZeroParamsS.Tolerance+1, CV_32F );
	int minRadius = ( SR->DB->CameraZeroParamsS.CircleDiameter - SR->DB->CameraZeroParamsS.Tolerance ) / 2.0;
	cvRange( radii, minRadius, minRadius + radii->cols );

	// edges matrix
	CvMat stub, *edges_mat = (CvMat*)edges;
	edges_mat = cvGetMat( edges_mat, &stub );

	// resolution
	float dp = 0.5;

	// search circle
	int x, y, index;
	//houghCircle( edges_mat, radii, dp, x, y, index, MID( 0.0, SR->DB->CameraZeroParamsS.CircleAccum/100.0, 1.0 ) );
	houghCircle( edges_mat, radii, dp, x, y, index, MID( 0.0, SR->DB->CameraZeroParamsS.CircleAccum/200.0, 1.0 ) );

	if( index != -1 )
	{
		// returned values are in ROI coordinates
		X = x*dp + roi_x;
		Y = y*dp + roi_y;
		R = cvGetReal1D( radii, index );
		/*wxString accumulator = "Zero Found (crop) ";
		cv::imshow(accumulator.ToAscii(), cv::Mat(crop, false));
		wxString params = "Found ";
		params<< "D "<< SR->DB->CameraZeroParamsS.CircleDiameter;
		params<< " A "<< SR->DB->CameraZeroParamsS.CircleAccum;
		params<< " T "<<SR->DB->CameraZeroParamsS.Tolerance;
		params<< " I "<<index;
		cv::imshow(params.ToAscii(), cv::Mat(edges, false));*/
	}
	else{
		MACHINE_CONFIG_NOT(PASSWORD_ENABLE)
			wxString accumulator = "Zero not Found (crop) ";
			accumulator << SR->DB->CameraZeroParamsS.CircleAccum;
			cv::imshow(accumulator.ToAscii(), cv::Mat(crop, false));
			wxString params;
			params<< "D "<< SR->DB->CameraZeroParamsS.CircleDiameter;
			params<< " A "<< SR->DB->CameraZeroParamsS.CircleAccum;
			params<< " T "<<SR->DB->CameraZeroParamsS.Tolerance;
			params<< " I "<<index;
			cv::imshow(params.ToAscii(), cv::Mat(edges, false));
			cv::waitKey(0);
		MACHINE_CONFIG_END
	}

	// Clean
	cvReleaseImage( &crop );
	cvReleaseImage( &edges );
	cvReleaseMat( &radii );

	// draw search area & circle
	wxBitmap bmp = wxImage( CAM_W, CAM_H, (unsigned char*)openCVFrame_24->imageData, true );
	wxMemoryDC dc;

	dc.SelectObject( bmp );
	dc.SetBrush( *wxTRANSPARENT_BRUSH );

	if( SR->DB->WorkingModesS.DebugMode )
	{
		dc.SetPen( wxPen( wxColour( 0, 255, 0 ) ) );
		dc.DrawRectangle( roi_x, roi_y, roi_w, roi_h );
	}
	if( index != -1 )
	{
		dc.SetPen( wxPen( wxColour( 255, 0, 0 ) ) );
		dc.DrawCircle( X, Y, R );
	}

	dc.SelectObject( wxNullBitmap );
	videoMain->SetImage( bmp );

	return index == -1 ? SR_ERROR : SR_OK;
}

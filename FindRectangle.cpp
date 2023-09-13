//---------------------------------------------------------------------------
//
// Name:        FindRectangle.cpp
// Author:      Gabriel Ferri
// Created:     07/10/2008
// Description: FindRectangle function implementation
//
//---------------------------------------------------------------------------

#include "wxCameraControl.h"
#include <wx/image.h>
#include <wx/dcmemory.h>
#include <wx/dcbuffer.h>
#include "GlobalUtils.h"
#include "hough.h"


//----------------------------------------------------------------------------------
// FindRectangle
//
// ATTENTION!!! - Before calling this function you MUST call GetFrames() function
//----------------------------------------------------------------------------------
int wxCameraControl::FindRectangle( int expectedX, int expectedY, float &X, float &Y, float &rectX, float &rectY )
{
	// Cropping
	int searchAreaX = (SR->DB->pCurrentFiducial->RectangleSideX + SR->DB->pCurrentFiducial->Tolerance) * SR->DB->pCurrentFiducial->SearchAreaMul;
	int searchAreaY = (SR->DB->pCurrentFiducial->RectangleSideY + SR->DB->pCurrentFiducial->Tolerance) * SR->DB->pCurrentFiducial->SearchAreaMul;
	int roi_x = MAX( 0, expectedX - searchAreaX / 2.0 );
	int roi_y = MAX( 0, expectedY - searchAreaY / 2.0 );
	int roi_w = MIN( CAM_W - 1, roi_x + searchAreaX ) - roi_x;
	int roi_h = MIN( CAM_H - 1, roi_y + searchAreaY ) - roi_y;

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

	// sides array
	CvMat *sideX = cvCreateMat( 1, SR->DB->pCurrentFiducial->Tolerance+1, CV_32F );
	int minSideX = SR->DB->pCurrentFiducial->RectangleSideX - SR->DB->pCurrentFiducial->Tolerance/2;
	cvRange( sideX, minSideX, minSideX + sideX->cols );

	CvMat *sideY = cvCreateMat( 1, SR->DB->pCurrentFiducial->Tolerance+1, CV_32F );
	int minSideY = SR->DB->pCurrentFiducial->RectangleSideY - SR->DB->pCurrentFiducial->Tolerance/2;
	cvRange( sideY, minSideY, minSideY + sideY->cols );

	// edges matrix
	CvMat stub, *edges_mat = (CvMat*)edges;
	edges_mat = cvGetMat( edges_mat, &stub );

	// resolution
	float dp = 0.5;

	// search rectangle
	int x, y, indexX, indexY;
	houghRectangle( edges_mat, sideX, sideY, dp, x, y, indexX, indexY, MID( 0.0, SR->DB->pCurrentFiducial->RectangleAccum/100.0, 1.0 ) );

	if( indexX != -1 )
	{
		// returned values are in ROI coordinates
		X = x*dp + roi_x;
		Y = y*dp + roi_y;
		rectX = cvGetReal1D( sideX, indexX );
		rectY = cvGetReal1D( sideY, indexY );
	}

	// Clean
	cvReleaseImage( &crop );
	cvReleaseImage( &edges );
	cvReleaseMat( &sideX );
	cvReleaseMat( &sideY );

	// draw search area & rectangle
	wxBitmap bmp = wxImage( CAM_W, CAM_H, (unsigned char*)openCVFrame_24->imageData, true );
	wxMemoryDC dc;

	dc.SelectObject( bmp );
	dc.SetBrush( *wxTRANSPARENT_BRUSH );

	if( SR->DB->WorkingModesS.DebugMode )
	{
		dc.SetPen( wxPen( wxColour( 0, 255, 0 ) ) );
		dc.DrawRectangle( roi_x, roi_y, roi_w, roi_h );
	}
	if( indexX != -1 )
	{
		dc.SetPen( wxPen( wxColour( 255, 0, 0 ) ) );
		dc.DrawRectangle( X-rectX/2.0, Y-rectY/2.0, rectX, rectY );
	}

	dc.SelectObject( wxNullBitmap );
	videoMain->SetImage( bmp );

	return indexX == -1 ? SR_ERROR : SR_OK;
}

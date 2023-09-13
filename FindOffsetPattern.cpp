//---------------------------------------------------------------------------
//
// Name:        FindOffsetPattern.cpp
// Author:      Gabriel Ferri
// Created:     07/10/2008
// Description: FindOffsetPattern function implementation
//
//---------------------------------------------------------------------------

#include "wxCameraControl.h"
#include <wx/image.h>
#include <wx/dcmemory.h>
#include "GlobalUtils.h"
#include "GlobalDefs.h"
#include "hough.h"


#define PATTERN_HOLE				0.4f
#define PATTERN_CIRCLES				15 // numero massimo di punti riconosciuti nell'immagine
#define PATTERN_PPL					9 // numero massimo di punti utilizzati per il riconoscimento della linea
#define PATTERN_ALIGN_TOLERANCE		10 // distanza massima (pixel) per considerare i punti allineati
#define PATTERN_ALIGN_MIN			3 // numero minimo di punti allineati
#define PATTERN_NORMAL_ERROR		2.f // errore (gradi) di perpendicolarit� massimo


//----------------------------------------------------------------------------------
// FindOffsetPattern
// Find the pattern used to calibrate camera offset
// ATTENTION!!! - Before calling this function you MUST call GetFrames() function
//----------------------------------------------------------------------------------
bool wxCameraControl::FindOffsetPattern3( float &X, float &Y )
{
	bool isError = false;

	X = -1;
	Y = -1;

	// cropping
	//-----------------------------------------------------
	int roi_x = 10;
	int roi_y = 10;
	int roi_w = CAM_W - 2 * roi_x;
	int roi_h = CAM_H - 2 * roi_y;

	IplImage* crop = cvCreateImage( cvSize(roi_w, roi_h), IPL_DEPTH_8U, 1 );

	cvSetImageROI( openCVFramesArray[0], cvRect( roi_x, roi_y, roi_w, roi_h ) );
	cvCopy( openCVFramesArray[0], crop );
	cvResetImageROI( openCVFramesArray[0] );

	// filtering
	//-----------------------------------------------------

	// improve edge detection reducing image background noise
	int filterSmoothDim = SR->DB->pCurrentFiducial->FilterSmoothDim | 0x00000001;
	cvSmooth( crop, crop, SR->DB->pCurrentFiducial->FilterSmoothType + 1, filterSmoothDim, filterSmoothDim );

	// edge detection
	IplImage* edges = cvCreateImage( cvSize(crop->width, crop->height), IPL_DEPTH_8U, 1 );
	cvCanny( crop, edges, SR->DB->pCurrentFiducial->FilterEdgeThr/2, SR->DB->pCurrentFiducial->FilterEdgeThr, 3 );

	// setup data
	//-----------------------------------------------------

	// radii array
	float scale = 0.02f;
	int min_radius = ( PATTERN_HOLE / scale / 2 ) - SR->DB->pCurrentFiducial->Tolerance;
	CvMat* radii = cvCreateMat( 1, 2*SR->DB->pCurrentFiducial->Tolerance+1, CV_32F );
	cvRange( radii, min_radius, min_radius + radii->cols );

	// edges matrix
	CvMat stub, *edges_mat = (CvMat*)edges;
	edges_mat = cvGetMat( edges_mat, &stub );

	// resolution
	float dp = 1.f;
	float idp = 1.f / dp;

	int acc_rows = crop->height * idp;
	int acc_cols = crop->width * idp;

	// accumulator matrix
	CvMat *acc = cvCreateMat( acc_rows, acc_cols, CV_16UC1 );
	// indices matrix
	CvMat *indices = cvCreateMat( acc_rows, acc_cols, CV_8UC1 );

	// search circles
	//-----------------------------------------------------
	houghCircles( edges_mat, radii, dp, acc, indices, MID( 0.0, SR->DB->pCurrentFiducial->CircleAccum/100.0, 1.0 ) );

	CirclePattern circlesArray[PATTERN_CIRCLES];
	for( int y = 0; y < acc_rows; y++ )
	{
		for( int x = 0; x < acc_cols; x++ )
		{
			int value = cvGet2D( acc, y, x ).val[0];

			for( int i = 0; i < PATTERN_CIRCLES ; i++ )
			{
				if( value > circlesArray[i].value )
				{
					if( i == 0 )
					{
						circlesArray[i].value = value;
						circlesArray[i].ok = true;
						// returned values are in ROI coordinates
						circlesArray[i].point.X = x*dp + roi_x;
						circlesArray[i].point.Y = y*dp + roi_y;
						int index = cvGet2D( indices, y, x ).val[0];
						circlesArray[i].point.R = cvGetReal1D( radii, index );
					}
					else
					{
						CirclePattern tc = circlesArray[i];
						circlesArray[i] = circlesArray[i-1];
						circlesArray[i-1] = tc;
					}
				}
				else
					break;
			}
		}
	}

	// clean
	cvReleaseImage( &crop );
	cvReleaseImage( &edges );
	cvReleaseMat( &acc );
	cvReleaseMat( &indices );
	cvReleaseMat( &radii );

	//DEBUG
	/*
	printf( " Search points   OK\n" );
	CvFont font;
	char text[8];
	cvInitFont( &font, CV_FONT_HERSHEY_COMPLEX, 1, 1 );
	for( int c = 0; c < PATTERN_CIRCLES; c++ )
	{
		if( circlesArray[c].ok )
		{
			cvCircle( openCVFramesArray_RGB[img_num], cvPoint(circlesArray[c].point.X,circlesArray[c].point.Y), circlesArray[c].point.R, CV_RGB(255,255,0) );
			sprintf_s( text, 8, "%d", c );
			cvPutText( openCVFramesArray_RGB[img_num], text, cvPoint(circlesArray[c].point.X,circlesArray[c].point.Y), &font, CV_RGB(0,128,0) );
		}
	}
	*/

	
	//  points check : relative distances
	//-----------------------------------------------------
	int min_distance = int( PATTERN_HOLE / scale / 2 );
	bool circlesArrayRemove[PATTERN_CIRCLES];
	memset( circlesArrayRemove, 0, sizeof(bool) * PATTERN_CIRCLES );

	for( int i1 = 0; i1 < PATTERN_CIRCLES; i1++ )
	{
		if( !circlesArray[i1].ok )
			continue;

		for( int i2 = 0; i2 < PATTERN_CIRCLES; i2++ )
		{
			if( !circlesArray[i2].ok || i1 == i2 )
				continue;

			if( abs( circlesArray[i1].point.X - circlesArray[i2].point.X ) < min_distance &&
				abs( circlesArray[i1].point.Y - circlesArray[i2].point.Y ) < min_distance )
			{
				circlesArrayRemove[i1] = true;
				break;
			}
		}
	}

	for( int i1 = 0; i1 < PATTERN_CIRCLES; i1++ )
	{
		if( circlesArrayRemove[i1] )
			circlesArray[i1].ok = false;
	}

	//DEBUG
	/*
	printf( " Points check   OK\n" );
	for( int c = 0; c < PATTERN_CIRCLES; c++ )
	{
		if( circlesArrayRemove[c] )
			cvCircle( openCVFramesArray_RGB[img_num], cvPoint(circlesArray[c].point.X,circlesArray[c].point.Y), circlesArray[c].point.R, CV_RGB(255,0,0) );
	}
	*/


	//  points alignment
	//-----------------------------------------------------
	// Un punto � preso in considerazione se � in linea con almeno altri (PATTERN_ALIGN_MIN-1) punti

	int lineX_i = 0, lineY_i = 0;
	int lineX[PATTERN_PPL];
	int lineY[PATTERN_PPL];

	// lineX - orizzontale
	for( int i1 = 0; i1 < PATTERN_CIRCLES; i1++ )
	{
		if( !circlesArray[i1].ok )
			continue;

		int matching = 0;
		for( int i2 = 0; i2 < PATTERN_CIRCLES; i2++ )
		{
			if( !circlesArray[i2].ok || i1 == i2 )
				continue;

			if( abs( circlesArray[i1].point.Y - circlesArray[i2].point.Y ) < PATTERN_ALIGN_TOLERANCE )
			{
				matching++;
				if( matching == PATTERN_ALIGN_MIN - 1 )
				{
					lineX[lineX_i] = i1;
					lineX_i++;

					if( lineX_i == PATTERN_PPL )
					{
						// exit condition
						i1 = i2 = PATTERN_CIRCLES;
					}
					break;
				}
			}
		}
	}

	// lineY - vertical
	for( int i1 = 0; i1 < PATTERN_CIRCLES; i1++ )
	{
		if( !circlesArray[i1].ok )
			continue;

		int matching = 0;
		for( int i2 = 0; i2 < PATTERN_CIRCLES; i2++ )
		{
			if( !circlesArray[i2].ok || i1 == i2 )
				continue;

			if( abs( circlesArray[i1].point.X - circlesArray[i2].point.X ) < PATTERN_ALIGN_TOLERANCE )
			{
				matching++;
				if( matching == PATTERN_ALIGN_MIN - 1 )
				{
					lineY[lineY_i] = i1;
					lineY_i++;

					if( lineY_i == PATTERN_PPL )
					{
						// exit condition
						i1 = i2 = PATTERN_CIRCLES;
					}
					break;
				}
			}
		}
	}

	if( lineX_i < PATTERN_ALIGN_MIN || lineY_i < PATTERN_ALIGN_MIN )
		isError = true;

	//DEBUG
	/*
	printf( " Points alignment   " );
	isError ? printf( "ERROR" ) : printf( "OK" );
	printf( "\n" );

	printf( "   X = [ " );
	for( int i = 0; i < lineX_i; i++ )
		printf( " %d ", lineX[i] );
	printf( "]  #%d\n", lineX_i );

	printf( "   Y = [ " );
	for( int i = 0; i < lineY_i; i++ )
		printf( " %d ", lineY[i] );
	printf( "]  #%d\n", lineY_i );
	*/

	if( isError )
		return false;


	//  fit lines
	//-----------------------------------------------------
	float lineX_fit[4], lineY_fit[4]; // [ Vx, Vy, x, y ]
	CvMat *points;

	// lineX - orizzontale
	points = cvCreateMat( 1, lineX_i, CV_32FC2 );
	for( int counter = 0; counter < lineX_i; counter++ )
		cvSet2D( points, 0, counter, cvScalar( circlesArray[lineX[counter]].point.X, circlesArray[lineX[counter]].point.Y ) );
	cvFitLine( points, CV_DIST_L2, 0, 0.01, 0.01, lineX_fit );
	cvReleaseMat( &points );

	// lineY - vertical
	points = cvCreateMat( 1, lineY_i, CV_32FC2 );
	for( int counter = 0; counter < lineY_i; counter++ )
		cvSet2D( points, 0, counter, cvScalar( circlesArray[lineY[counter]].point.X, circlesArray[lineY[counter]].point.Y ) );
	cvFitLine( points, CV_DIST_L2, 0, 0.01, 0.01, lineY_fit );
	cvReleaseMat( &points );

	//DEBUG
	/*
	printf( " Fit lines   OK\n" );
	printf( "   X: [ %.3f, %.3f, %.2f, %.2f ]\n", lineX_fit[0], lineX_fit[1], lineX_fit[2], lineX_fit[3] );
	printf( "   Y: [ %.3f, %.3f, %.2f, %.2f ]\n", lineY_fit[0], lineY_fit[1], lineY_fit[2], lineY_fit[3] );

	cvLine( openCVFramesArray_RGB[img_num], cvPoint(lineY_fit[2]+lineY_fit[0]*500,lineY_fit[3]+lineY_fit[1]*500), cvPoint(lineY_fit[2]-lineY_fit[0]*500,lineY_fit[3]-lineY_fit[1]*500), CV_RGB(0,255,0) );
	cvLine( openCVFramesArray_RGB[img_num], cvPoint(lineX_fit[2]+lineX_fit[0]*500,lineX_fit[3]+lineX_fit[1]*500), cvPoint(lineX_fit[2]-lineX_fit[0]*500,lineX_fit[3]-lineX_fit[1]*500), CV_RGB(0,255,0) );
	*/


	//  Normal check
	//-----------------------------------------------------
	float a1, a2;

	if( lineX_fit[0] != 0.f ) //TEMP - da rivedere controllo
		a1 = atan( lineX_fit[1] / lineX_fit[0] );
	else
		isError = true;

	if( lineY_fit[1] != 0.f )
		a2 = -atan( lineY_fit[0] / lineY_fit[1] );
	else
		isError = true;

	if( RTOD(fabs(a1-a2)) > PATTERN_NORMAL_ERROR )
		isError = true;

	//DEBUG
	/*
	printf( " Normal check   " );
	isError ? printf( "ERROR" ) : printf( "OK" );
	printf( "\n" );

	if( lineX_fit[0] == 0.f )
		printf( "   X -> Vx = 0\n" );
	else if( lineY_fit[1] == 0.f )
		printf( "   Y -> Vy = 0\n" );
	else
		printf( "   Diff angle (deg): %.2f  <  %.2f\n", RTOD(fabs(a1-a2)), float(PATTERN_NORMAL_ERROR) );
	*/

	if( isError )
		return false;


	//  intersection
	//-----------------------------------------------------
	

	// num2 = Vx1*(y2-y1) - Vy1*(x2-x1)
	float num2 = lineX_fit[0]*(lineY_fit[3]-lineX_fit[3]) - lineX_fit[1]*(lineY_fit[2]-lineX_fit[2]);
	// den2 = Vx2*Vy1 - Vx1*Vy2
	float den2 = lineY_fit[0]*lineX_fit[1] - lineX_fit[0]*lineY_fit[1];
	if( den2 == 0 )
		isError = true;
	else
	{
		float K2 = num2 / den2;
		X = lineY_fit[2] + K2 * lineY_fit[0];
		Y = lineY_fit[3] + K2 * lineY_fit[1];
	}

	//DEBUG
	/*
	printf( " Intersection   " );
	isError ? printf( "ERROR" ) : printf( "OK" );
	printf( "\n" );

	if( !isError )
	{
		printf( "   Point ( %.2f , %.2f )\n", X, Y );
		cvCircle( openCVFramesArray_RGB[img_num], cvPoint( X, Y ), 2, CV_RGB(255,255,0), CV_FILLED );
	}
	*/
	
	if( isError )
		return false;


	///////////////////////////////////////////////////////
	// Prepare image to display
	wxBitmap bmp = wxImage( CAM_W, CAM_H, (unsigned char*)openCVFrame_24->imageData, true );
	wxMemoryDC dc;
	dc.SelectObject( bmp );
	dc.SetBrush( *wxTRANSPARENT_BRUSH );

	// circles
	dc.SetPen( wxPen( wxColour( 255, 0, 0 ) ) );
	for( int i = 0; i < PATTERN_CIRCLES; i++ )
		if( circlesArray[i].ok )
			dc.DrawCircle( circlesArray[i].point.X, circlesArray[i].point.Y, circlesArray[i].point.R );

	// fitted lines
	dc.SetPen( wxPen( wxColour( 0, 255, 0 ) ) );
	dc.DrawLine( lineX_fit[2]+lineX_fit[0]*500, lineX_fit[3]+lineX_fit[1]*500, lineX_fit[2]-lineX_fit[0]*500, lineX_fit[3]-lineX_fit[1]*500 );
	dc.DrawLine( lineY_fit[2]+lineY_fit[0]*500, lineY_fit[3]+lineY_fit[1]*500, lineY_fit[2]-lineY_fit[0]*500, lineY_fit[3]-lineY_fit[1]*500 );

	// intersection
	dc.SetBrush( *wxCYAN_BRUSH );
	dc.SetPen( *wxCYAN_PEN );
	dc.DrawCircle( X, Y, 2 );

	///////////////////////////////////////////////////////
	// Display image
	dc.SelectObject( wxNullBitmap );
	videoMain->SetImage( bmp );

	return true;
}

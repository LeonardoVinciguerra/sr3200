//---------------------------------------------------------------------------
//
// Name:        VisionFunctions.cpp
// Author:      Gabriel Ferri
// Created:     17/05/2011
// Description: VisionFunctions function implementation
//
//---------------------------------------------------------------------------

#include "VisionFunctions.h"
#include <wx/dcmemory.h>
#include <wx/image.h>
#include "GlobalUtils.h"
#include "hough.h"

//----------------------------------------------------------------------------------
// cvMaxLocLim
// ATTENZIONE!!! Funziona solo con IplImage del tipo IPL_DEPTH_32F a singolo canale
//----------------------------------------------------------------------------------
void cvMaxLocLim( const IplImage* pVotes, double* max_val, CvPoint* max_loc = 0, double max_lim = 1.0f )
{
	int col_max, row_max;

	*max_val = cvGetReal2D( pVotes, 0, 0 );
	for( int row = 0; row < pVotes->height; row++ )
	{
		float *val_ptr = (float*)((unsigned char*)pVotes->imageDataOrigin + row * pVotes->widthStep);

		for( int col = 0; col < pVotes->width; col++ )
		{
			if( *val_ptr > *max_val && *val_ptr < max_lim )
			{
				*max_val = *val_ptr;
				col_max = col;
				row_max = row;
			}
			*val_ptr++;
		}
	}

	if( max_loc )
	{
		max_loc->x = col_max;
		max_loc->y = row_max;
	}
}

//----------------------------------------------------------------------------------
// FindTemplate
//----------------------------------------------------------------------------------
bool FindTemplate( IplImage* pImage, const char* filename, PointF& position, float& score )
{
	IplImage* pTemplateImage = cvLoadImage( filename, CV_LOAD_IMAGE_GRAYSCALE );

	// create votes matrix
	CvRect roi = cvGetImageROI( pImage );
	int vote_w = roi.width - pTemplateImage->width + 1;
	int vote_h = roi.height - pTemplateImage->height + 1;

	if( vote_w <= 0 || vote_h <= 0 )
	{
		cvReleaseImage( &pTemplateImage );
		return false;
	}

	IplImage* votes = cvCreateImage( cvSize( vote_w, vote_h ), IPL_DEPTH_32F, 1 );

	cvMatchTemplate( pImage, pTemplateImage, votes, CV_TM_CCOEFF_NORMED );

	// find max value in the "votes"-image and its positions
	CvPoint pp;
	double maxVal;
	cvMaxLocLim( votes, &maxVal, &pp, 1.0f );

	// calc results
	position.X = pp.x + pTemplateImage->width/2.f;
	position.Y = pp.y + pTemplateImage->height/2.f;
	score = float( maxVal );

	// Clean
	cvReleaseImage( &votes );
	cvReleaseImage( &pTemplateImage );

	return true;
}


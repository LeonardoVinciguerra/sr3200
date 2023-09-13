//---------------------------------------------------------------------------
//
// Name:        VisionFunctions.h
// Author:      Gabriel Ferri
// Created:     17/05/2011
// Description: VisionFunctions functions definition
//
//---------------------------------------------------------------------------
#ifndef __VISIONFUNCTIONS_H
#define __VISIONFUNCTIONS_H

#ifdef __WXMSW__
	#include <wx/msw/winundef.h>
	#include <cv.h>
	#include <highgui.h>
#else
	#include <opencv/cv.h>
	#include <opencv/highgui.h>
#endif
#include "GlobalDefs.h"

void cvMaxLocLim( const IplImage* pVotes, double* max_val, CvPoint* max_loc, double max_lim );
bool FindTemplate( IplImage* pImage, const char* filename, PointF& position, float& score );

#endif //__VISIONFUNCTIONS_H

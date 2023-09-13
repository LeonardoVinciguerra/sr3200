//---------------------------------------------------------------------------
//
// Name:        FindTemplate.cpp
// Author:      Gabriel Ferri
// Created:     07/10/2008
// Description: FindTemplate function implementation
//
//---------------------------------------------------------------------------

#include "wxCameraControl.h"
#include "VisionFunctions.h"
#include <wx/image.h>
#include <wx/dcmemory.h>
#include <wx/dcbuffer.h>
#include "GlobalUtils.h"

#ifdef __WXMSW__
#define TEMPLATE_FOLDER		"vision\\"
#else
#define TEMPLATE_FOLDER		"vision/"
#endif


//----------------------------------------------------------------------------------
// CheckTemplateImage
// Check template image existance
//----------------------------------------------------------------------------------
bool wxCameraControl::CheckTemplateImage( const wxString& filename )
{
	wxString fullpath( TEMPLATE_FOLDER );
	fullpath.Append( filename );
	return wxFileExists( fullpath.ToAscii() );
}

//----------------------------------------------------------------------------------
// SaveTemplateImage
// Save template image to use in template matching
//----------------------------------------------------------------------------------
void wxCameraControl::SaveTemplateImage( const wxString& filename )
{
	// Cropping
	int roi_x = MAX( 0, (CAM_W-(SR->DB->pCurrentFiducial->TemplateDim))/2 );
	int roi_y = MAX( 0, (CAM_H-(SR->DB->pCurrentFiducial->TemplateDim))/2 );
	int roi_w = MIN( CAM_W - 1, roi_x + (SR->DB->pCurrentFiducial->TemplateDim) ) - roi_x;
	int roi_h = MIN( CAM_H - 1, roi_y + (SR->DB->pCurrentFiducial->TemplateDim) ) - roi_y;

	IplImage *crop = cvCreateImage( cvSize(roi_w, roi_h), IPL_DEPTH_8U, 1 );

	cvSetImageROI( openCVFramesArray[0], cvRect( roi_x, roi_y, roi_w, roi_h ) );
	cvCopy( openCVFramesArray[0], crop );
	cvResetImageROI( openCVFramesArray[0] );

	wxString fullpath( TEMPLATE_FOLDER );
	// check if dir exist; if no create it
	if( !wxDirExists( fullpath ) )
		wxMkdir( fullpath );

	fullpath.Append( filename );
	cvSaveImage( fullpath.ToAscii(), crop );

	cvReleaseImage( &crop );

	// draw template area
	wxBitmap bmp = wxImage( CAM_W, CAM_H, (unsigned char*)openCVFrame_24->imageData, true );
	wxMemoryDC dc;

	dc.SelectObject( bmp );
	dc.SetBrush( *wxTRANSPARENT_BRUSH );

	dc.SetPen( wxPen( wxColour( 255, 0, 0 ) ) );
	dc.DrawRectangle( roi_x, roi_y, roi_w, roi_h );

	dc.SelectObject( wxNullBitmap );
	videoMain->SetImage( bmp );
}

//----------------------------------------------------------------------------------
// LoadTemplateImage
// Load template image to use in template matching
// WARNING: file MUST exist - should be checked using CheckTemplateImage
//----------------------------------------------------------------------------------
wxBitmap wxCameraControl::LoadTemplateImage( const wxString& filename )
{
	wxString fullpath( TEMPLATE_FOLDER );
	fullpath.Append( filename );
	IplImage *pTemplateImage = cvLoadImage( fullpath.ToAscii(), CV_LOAD_IMAGE_COLOR );

	wxBitmap bmp = wxImage( pTemplateImage->width, pTemplateImage->height, (unsigned char*)pTemplateImage->imageData, true );

	cvReleaseImage( &pTemplateImage );
	return bmp;
}

//----------------------------------------------------------------------------------
// FindTemplate
// 
// WARNING!!! Before calling this function you MUST call GetFrames() function
//----------------------------------------------------------------------------------
int wxCameraControl::FindTemplate( const wxString& filename, float &X, float &Y, float &score )
{
	int retVal = SR_ERROR;

	wxString fullpath( TEMPLATE_FOLDER );
	fullpath.Append( filename );
	IplImage *pTemplateImage = cvLoadImage( fullpath.ToAscii(), CV_LOAD_IMAGE_GRAYSCALE );

	// create votes matrix
	int vote_w = openCVFramesArray[0]->width - pTemplateImage->width + 1;
	int vote_h = openCVFramesArray[0]->height - pTemplateImage->height + 1;
	IplImage *votes = cvCreateImage( cvSize( vote_w, vote_h ), IPL_DEPTH_32F, 1 );

	cvMatchTemplate( openCVFramesArray[0], pTemplateImage, votes, CV_TM_CCOEFF_NORMED );

	// find max value in the "votes"-image and its positions
	CvPoint pp;
	double maxVal;
	cvMaxLocLim( votes, &maxVal, &pp, 1.0f );

	X = pp.x + pTemplateImage->width/2;
	Y = pp.y + pTemplateImage->height/2;
	score = float( maxVal );

	// draw template position
	wxBitmap bmp = wxImage( CAM_W, CAM_H, (unsigned char*)openCVFrame_24->imageData, true );
	wxMemoryDC dc;

	dc.SelectObject( bmp );
	dc.SetBrush( *wxTRANSPARENT_BRUSH );

	if( score >= (SR->DB->pCurrentFiducial->TemplateThr / 100.0f) )
	{
		dc.SetPen( wxPen( wxColour( 255, 0, 0 ) ) );
		dc.DrawRectangle( pp.x, pp.y, pTemplateImage->width, pTemplateImage->height );
		retVal = SR_OK;
	}

	dc.SelectObject( wxNullBitmap );
	videoMain->SetImage( bmp );
	
	// Clean
	cvReleaseImage( &votes );
	cvReleaseImage( &pTemplateImage );
	
	return retVal;
}

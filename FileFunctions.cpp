//---------------------------------------------------------------------------
//
// Name:        FileFunctions.cpp
// Author:      Gabriel Ferri
// Created:     16/05/2011
// Description: FileFunctions functions implementation
//
//---------------------------------------------------------------------------

#include "FileFunctions.h"

#ifdef __WXMSW__
	#include <wx/msw/winundef.h>
	#include <cv.h>
	#include <highgui.h>
#else
	#include <opencv/cv.h>
	#include <opencv/highgui.h>
#endif

#include "GlobalDefs.h"
#include <wx/file.h>
#include <wx/image.h>


//----------------------------------------------------------------------------------
// ffCopyFile
//----------------------------------------------------------------------------------
bool ffCopyFile( const char *file_in, const char *file_out )
{
	FILE *in, *out;
	char ch;

	if( ( in = fopen( file_in, "rb" ) ) == NULL )
		return false;

	if( ( out = fopen( file_out, "wb" ) ) == NULL )
		return false;

	while( !feof(in) )
	{
		ch = getc(in);
		if( ferror(in) )
		{
			clearerr(in);
			fclose(in);
			fclose(out);
			return false;
		}
		if( !feof(in) )
			putc(ch, out);
		if( ferror(out) )
		{
			clearerr(out);
			fclose(in);
			fclose(out);
			return false;
		}
	}

	fclose(in);
	fclose(out);
	return true;
}

//----------------------------------------------------------------------------------
// ffRemoveFile
//----------------------------------------------------------------------------------
bool ffRemoveFile( const char* dir, const char* filename )
{
	wxString fullpath( dir );
	fullpath.Append( filename );
	return wxRemoveFile( fullpath );
}

//----------------------------------------------------------------------------------
// ffCheckFile
//----------------------------------------------------------------------------------
bool ffCheckFile( const char* dir, const char* filename )
{
	wxString fullpath( dir );
	fullpath.Append( filename );
	return wxFileExists( fullpath );
}

//----------------------------------------------------------------------------------
// ffLoad_IplImage
// WARNING: file MUST exist - should be checked using ffCheckFile
//----------------------------------------------------------------------------------
void ffLoad_IplImage_8( const char* dir, const char* filename, void* pImage )
{
	wxString fullpath( dir );
	fullpath.Append( filename );
	IplImage* _image = cvLoadImage( fullpath.ToAscii(), CV_LOAD_IMAGE_GRAYSCALE );

	cvCopyImage( _image, (IplImage*)pImage );

	cvReleaseImage( &_image );
}
//----------------------------------------------------------------------------------
// ffLoad_Mat_24
// WARNING: file MUST exist - should be checked using ffCheckFile
//----------------------------------------------------------------------------------
void ffLoad_Mat_24( const char* dir, const char* filename, cv::Mat* Image )
{
	wxString fullpath( dir );
	fullpath.Append( filename );
	cv::Mat image_temp =  cv::imread(fullpath.ToAscii(), CV_LOAD_IMAGE_COLOR);

	image_temp.copyTo(*Image);

}

//----------------------------------------------------------------------------------
// ffSave_Mat_24
//----------------------------------------------------------------------------------
void ffSave_Mat_24( const char* dir, const char* filename, cv::Mat* Image )
{
	wxString fullpath( dir );

	// check if dir exist, if no create it
	if( !wxDirExists( fullpath ) )
		wxMkdir( fullpath );

	fullpath.Append( filename );
	cv::imwrite(fullpath.ToAscii(), *Image);
	//cvSaveImage( fullpath.ToAscii(), (IplImage*)pImage );
}

//----------------------------------------------------------------------------------
// ffSave_IplImage_8
//----------------------------------------------------------------------------------
void ffSave_IplImage_8( const char* dir, const char* filename, void* pImage )
{
	wxString fullpath( dir );

	// check if dir exist, if no create it
	if( !wxDirExists( fullpath ) )
		wxMkdir( fullpath );

	fullpath.Append( filename );
	cvSaveImage( fullpath.ToAscii(), (IplImage*)pImage );
}



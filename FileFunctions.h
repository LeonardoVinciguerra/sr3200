//---------------------------------------------------------------------------
//
// Name:        FileFunctions.h
// Author:      Gabriel Ferri
// Created:     16/05/2011
// Description: FileFunctions functions declaration
//
//---------------------------------------------------------------------------

#ifndef __FILEFUNCTIONS_H
#define __FILEFUNCTIONS_H

#include <wx/bitmap.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

bool ffCopyFile( const char* file_in, const char* file_out );
bool ffRemoveFile( const char* dir, const char* filename );
bool ffCheckFile( const char* dir, const char* filename );

void ffLoad_IplImage_8( const char* dir, const char* filename, void* pImage );
void ffSave_IplImage_8( const char* dir, const char* filename, void* pImage );

void ffLoad_Mat_24( const char* dir, const char* filename, cv::Mat* Image );
void ffSave_Mat_24( const char* dir, const char* filename, cv::Mat* Image );

#endif //__FILEFUNCTIONS_H

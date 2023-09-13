//---------------------------------------------------------------------------
//
// Name:        VideoDevice.cpp
// Author:      Gabriel Ferri
// Created:     25/07/2008
// Description: VideoDevice class implementation
//
//---------------------------------------------------------------------------
#include "VideoDevice.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

using namespace std;

VideoDevice::VideoDevice()
{
	isOpen = false;
}

VideoDevice::~VideoDevice()
{
	if( v4l )
		delete v4l;
	if( isOpen )
		close( fd );
}

bool VideoDevice::openDevice( const std::string &device, unsigned int width, unsigned int height, int format )
{
	if( isOpen )
		close( fd );

	fd = open( device.c_str(), O_RDWR ); // open video device
	if( fd < 0 )
	{
		isOpen = false;
		return false;
	}
	isOpen = true;

	if( !width || !height )
	{
		//setting min resolution
		struct video_capability caps;
		if( queryCapabilities(&caps) )
		{
			width = caps.minwidth;
			height = caps.minheight;
		}
		else
		{
			width = 320;
			height = 240;
		}
	}

	// Determining video4linux API version
	struct v4l2_capability cap;
	if( queryCapabilities(&cap) )
	{
		// OK! Using video4linux 2 API
		v4l = new VideoForLinux2();
	}
	else
	{
		close(fd);
		return(false);
	}

	v4l->setParameters( fd, format );
	v4l->mMap( width, height );

	return true;
}

bool VideoDevice::getFrame(char **buffer)
{
	if( v4l )
		return v4l->getFrame( buffer );
	else
		return false;
}

bool VideoDevice::setResolution(unsigned int width, unsigned int height, unsigned int frameRate)
{
	if(v4l)
		return v4l->setResolution(width, height, frameRate);
	else
		return false;
}

bool VideoDevice::getResolution(unsigned int &width, unsigned int &height, unsigned int &frameRate)
{
	if(v4l)
		return v4l->getResolution(width, height, frameRate);
	else
		return false;
}

bool VideoDevice::setBrightness(unsigned int value)
{
	if(v4l)
		return v4l->setBrightness(value);
	else
		return false;
}

bool VideoDevice::getBrightness(unsigned int &value)
{
	if(v4l)
		return v4l->getBrightness(value);
	else
		return false;
}

bool VideoDevice::setContrast(unsigned int value)
{
	if(v4l)
		return v4l->setContrast(value);
	else
		return false;
}

bool VideoDevice::getContrast(unsigned int &value)
{
	if(v4l)
		return v4l->getContrast(value);
	else
		return false;
}

bool VideoDevice::setGamma(unsigned int value)
{
	if(v4l)
		return v4l->setGamma(value);
	else
		return false;
}

bool VideoDevice::getGamma(unsigned int &value)
{
	if(v4l)
		return v4l->getGamma(value);
	else
		return false;
}

bool VideoDevice::setSaturation(unsigned int value)
{
	if(v4l)
		return v4l->setSaturation(value);
	else
		return false;
}

bool VideoDevice::getSaturation(unsigned int &value)
{
	if(v4l)
		return v4l->getSaturation(value);
	else
		return false;
}

bool VideoDevice::queryCapabilities(struct video_capability *caps) /*VIDIOCGCAP*/
{
	if( ioctl( fd, VIDIOCGCAP, caps ) < 0 )
	{
		return false;
	}
	return true;
}

bool VideoDevice::queryCapabilities(struct v4l2_capability *cap) /*VIDIOC_QUERYCAP*/
{
	if( ioctl(fd, VIDIOC_QUERYCAP, cap) == -1 )
	{
		return false;
	}

	if( !(cap->capabilities & V4L2_CAP_VIDEO_CAPTURE) )
	{
		return false;
	}

	return true;
}

void VideoDevice::closeDevice()
{
	if( isOpen )
	{
		close( fd );
		isOpen=false;
	}
}

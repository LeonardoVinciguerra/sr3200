/***************************************************************************
 *   Copyright (C) 2007 by Marco Lorrai                                    *
 *   marco.lorrai@abbeynet.it                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "v4l2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <asm/types.h>          /* for videodev2.h */
#include <linux/videodev2.h>
#include <iostream>

struct sVideoModes
{
	unsigned int modeId;
	const char* name;
	bool supported;
};

const struct sVideoModes videoModes[]=
{ 
	{ V4L2_PIX_FMT_RGB332	, "V4L2_PIX_FMT_RGB332" ,false },
 	{ V4L2_PIX_FMT_RGB444	, "V4L2_PIX_FMT_RGB444" ,false },
	{ V4L2_PIX_FMT_RGB555  	, "V4L2_PIX_FMT_RGB555" , false },
	{ V4L2_PIX_FMT_RGB565  	, "V4L2_PIX_FMT_RGB565" , false },
	{ V4L2_PIX_FMT_RGB555X 	, "V4L2_PIX_FMT_RGB555X" , false },
	{ V4L2_PIX_FMT_RGB565X 	, "V4L2_PIX_FMT_RGB565X" , false },
	{ V4L2_PIX_FMT_BGR24   	, "V4L2_PIX_FMT_BGR24" , false },
	{ V4L2_PIX_FMT_RGB24   	, "V4L2_PIX_FMT_RGB24" , false },
	{ V4L2_PIX_FMT_BGR32   	, "V4L2_PIX_FMT_BGR32" , false },
	{ V4L2_PIX_FMT_RGB32   	, "V4L2_PIX_FMT_RGB32" , false },
	{ V4L2_PIX_FMT_GREY    	, "V4L2_PIX_FMT_GREY" , true},
	{ V4L2_PIX_FMT_PAL8    	, "V4L2_PIX_FMT_PAL8" , false },
	{ V4L2_PIX_FMT_YVU410  	, "V4L2_PIX_FMT_YVU410" , false },
	{ V4L2_PIX_FMT_YVU420  	, "V4L2_PIX_FMT_YVU420" , false },
	{ V4L2_PIX_FMT_YUYV    	, "V4L2_PIX_FMT_YUYV" , true },
	{ V4L2_PIX_FMT_UYVY    	, "V4L2_PIX_FMT_UYVY" , false },
	{ V4L2_PIX_FMT_YUV422P 	, "V4L2_PIX_FMT_YUV422P" , false },
	{ V4L2_PIX_FMT_YUV411P 	, "V4L2_PIX_FMT_YUV411P" , false },
	{ V4L2_PIX_FMT_Y41P    	, "V4L2_PIX_FMT_Y41P" , false },
	{ V4L2_PIX_FMT_YUV444  	, "V4L2_PIX_FMT_YUV444" , false },
	{ V4L2_PIX_FMT_YUV444  	, "V4L2_PIX_FMT_YUV444" , false },
	{ V4L2_PIX_FMT_YUV565  	, "V4L2_PIX_FMT_YUV565" , false },
	{ V4L2_PIX_FMT_YUV32   	, "V4L2_PIX_FMT_YUV32" , false },
	{ V4L2_PIX_FMT_YUV410  	, "V4L2_PIX_FMT_YUV410" , false },
	{ V4L2_PIX_FMT_YUV420  	, "V4L2_PIX_FMT_YUV420" , false },
	{ V4L2_PIX_FMT_YYUV    	, "V4L2_PIX_FMT_YYUV" , false },
	{ V4L2_PIX_FMT_YYUV   	, "V4L2_PIX_FMT_YYUV" , false },
	{ V4L2_PIX_FMT_HM12    	, "V4L2_PIX_FMT_HM12" , false },
	{ 0, NULL}
 };

VideoForLinux2::VideoForLinux2()
{
	isMapped = false;
	buffers = NULL;
	n_buffers = 0;
	first = true;
	controlsSetted = false;
	pixelFormat = 0;
}

VideoForLinux2::~VideoForLinux2()
{
	unsigned int i;
	enum v4l2_buf_type type;
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	if (ioctl (fd, VIDIOC_STREAMOFF, &type) == -1)
		perror("VIDIOC_STREAMOFF");

		for (i = 0; i < n_buffers; ++i)
			if (munmap (buffers[i].start, buffers[i].length) == -1)
				perror("munmap");

	free(buffers);
}

void VideoForLinux2::closeDevice()
{
	unsigned int i;
	enum v4l2_buf_type type;
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	first = true;
	if (ioctl (fd, VIDIOC_STREAMOFF, &type) == -1)
		perror("VIDIOC_STREAMOFF");

		for (i = 0; i < n_buffers; ++i)
			if (munmap (buffers[i].start, buffers[i].length) == -1)
				perror("munmap");

	free(buffers);
}

bool VideoForLinux2::mMap(int w, int h)
{
	struct v4l2_cropcap cropcap;
	struct v4l2_crop crop;
	struct v4l2_format fmt;
	unsigned int min;

	pixelFormat = 0;

	if(!controlsSetted)
		setControls();

	memset(&cropcap, 0, sizeof(struct v4l2_cropcap));
	cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	if (!ioctl(fd, VIDIOC_CROPCAP, &cropcap))
	{
		crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		crop.c = cropcap.defrect; /* reset to default */

		if (ioctl(fd, VIDIOC_S_CROP, &crop) == -1)
		{
			if (EINVAL == errno)
			{
				fprintf( stderr, "Cropping not supported\n" );
			}
			else
			{
				/* Errors ignored. */
			}
		}
	}
	else
	{
		/* Errors ignored. */
	}

	memset(&fmt, 0, sizeof(struct v4l2_format));
	fmt.type			= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width	= w;
	fmt.fmt.pix.height	= h;
	

	std::cout<<"Determining pixel format..."<<std::endl;
	
	int mode_idx = 0;
	
	while(videoModes[mode_idx].modeId)
	{
		if(frameFormat == videoModes[mode_idx].modeId)
		{
			break;
		}
		mode_idx++;
	}
	
	if(videoModes[mode_idx].modeId == 0)
	{
		std::cout << "Unknown mode format" << std::endl;
		return(false);
	}
	
	if(!videoModes[mode_idx].supported)
	{
		std::cout << "Mode " << videoModes[mode_idx].name << " is not supported by library" << std::endl;
		return(false);
	}
	
	struct v4l2_fmtdesc argp;
	memset(&argp, 0, sizeof(struct v4l2_fmtdesc));
	argp.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	
	fmt.fmt.pix.pixelformat = 0;
	
	for(int index = 0 ;; index++)
	{
		argp.index=index;
		if (ioctl(fd, VIDIOC_ENUM_FMT, &argp) == 1)
		{
			break;
		}
			
		if(argp.pixelformat == videoModes[mode_idx].modeId)
		{
			fmt.fmt.pix.pixelformat = videoModes[mode_idx].modeId;
			break;
		}
	}
	
	pixelFormat = fmt.fmt.pix.pixelformat;
	
	if(fmt.fmt.pix.pixelformat == 0)
	{
		std::cout << "Mode " << videoModes[mode_idx].name << " is not supported by grabber" << std::endl;
		return(false);
	}
		
	fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

	if (ioctl (fd, VIDIOC_S_FMT, &fmt) == -1)
	{
		perror("VIDIOC_S_FMT");
		return false;
	}

	if(isMapped)
		closeDevice();

	/* Buggy driver paranoia. */
	min = fmt.fmt.pix.width * 2;
	if (fmt.fmt.pix.bytesperline < min)
		fmt.fmt.pix.bytesperline = min;
	min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
	if (fmt.fmt.pix.sizeimage < min)
		fmt.fmt.pix.sizeimage = min;

	width = w;
	height = h;

    return init_mmap();
}

bool VideoForLinux2::init_mmap()
{
	struct v4l2_requestbuffers req;

	memset(&req, 0, sizeof(struct v4l2_requestbuffers));

	req.count	= 4;
	req.type	= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory	= V4L2_MEMORY_MMAP;

	if (ioctl (fd, VIDIOC_REQBUFS, &req) == -1)
	{
		if (EINVAL == errno)
		{
			fprintf (stderr, "Memory mapping not supported\n");
			return false;
		}
		else
		{
			perror("VIDIOC_REQBUFS");
			return false;
		}
	}

	if (req.count < 2)
	{
		fprintf (stderr, "insufficient buffer memory\n");
		return false;
	}

	/*if(buffers)
	{
		for (unsigned int i = 0; i < n_buffers; ++i)
			if (munmap (buffers[i].start, buffers[i].length) == -1)
				perror("munmap");
		free(buffers);
	}*/

	buffers = (buffer*)calloc(req.count, sizeof (*buffers));
	if (!buffers)
	{
		fprintf (stderr, "Out of memory\n");
		return false;
	}

	for (n_buffers = 0; n_buffers < req.count; ++n_buffers)
	{
		struct v4l2_buffer buf;

		memset(&buf, 0, sizeof(struct v4l2_buffer));

		buf.type	= V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory	= V4L2_MEMORY_MMAP;
		buf.index	= n_buffers;

		if (ioctl (fd, VIDIOC_QUERYBUF, &buf) == -1)
		{
			perror("VIDIOC_QUERYBUF");
			return false;
		}

		buffers[n_buffers].length = buf.length;
		buffers[n_buffers].start =
						mmap (NULL /* start anywhere */,
						buf.length,
						PROT_READ | PROT_WRITE /* required */,
						MAP_SHARED /* recommended */,
						fd, buf.m.offset);

		if (MAP_FAILED == buffers[n_buffers].start)
		{
			perror("mmap");
			return false;
		}
	}
	isMapped = true;
	return true;
}

bool VideoForLinux2::getFrame(char **buffer)
{
	unsigned int i;
	enum v4l2_buf_type type;
	struct v4l2_buffer buf;

	if(!isMapped)
	{
		fprintf (stderr, "Device not mapped");
		return false;
	}

	if(first)
	{
		for (i = 0; i < n_buffers; ++i)
		{
			memset(&buf, 0, sizeof(struct v4l2_buffer));

			buf.type	= V4L2_BUF_TYPE_VIDEO_CAPTURE;
			buf.memory	= V4L2_MEMORY_MMAP;
			buf.index	= i;

			if (ioctl (fd, VIDIOC_QBUF, &buf) == -1)
			{
				perror("VIDIOC_QBUF");
				return false;
			}
		}

		type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

		if (ioctl (fd, VIDIOC_STREAMON, &type) == -1)
		{
			perror("VIDIOC_STREAMON");
			return false;
		}
	}

	first = false;
	memset(&buf, 0, sizeof(struct v4l2_buffer));

	buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf.memory = V4L2_MEMORY_MMAP;

	if (ioctl (fd, VIDIOC_DQBUF, &buf) == -1)
	{
		if( EAGAIN == errno )
		{
			return false;
		}
		else
		{
			perror("VIDIOC_DQBUF");
			return false;
		}
	}

	assert(buf.index < n_buffers);

	switch(pixelFormat)
	{
		case V4L2_PIX_FMT_GREY:
			memcpy( *buffer, buffers[buf.index].start, width*height );
			break;
		case V4L2_PIX_FMT_YUYV:
			memcpy( *buffer, buffers[buf.index].start, width*height *2 );
			break;
		default:
			std::cout << __FUNCTION__ << " : pixelformat is unknown" << std::endl;
			break;
	}

	if (ioctl (fd, VIDIOC_QBUF, &buf) == -1)
	{
		perror("VIDIOC_QBUF");
		return false;
	}

	return true;
}

void VideoForLinux2::setParameters(int fd, int format)
{
	this->fd = fd;
	frameFormat = format;
}

bool VideoForLinux2::setResolution(unsigned int width, unsigned int height, unsigned int frameRate)
{
	frameRate=0; /*ignored*/
	return mMap(width, height);
}

bool VideoForLinux2::getResolution(unsigned int &width, unsigned int &height, unsigned int &frameRate)
{
	struct v4l2_format fmt;
	memset(&fmt, 0, sizeof(struct v4l2_format));
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	frameRate = 0; /*ignored*/
	if (ioctl (fd, VIDIOC_G_FMT, &fmt) == -1)
	{
		perror("VIDIOC_G_FMT");
		return false;
	}
	width = fmt.fmt.pix.width;
	height = fmt.fmt.pix.height;
	return true;
}

bool VideoForLinux2::setBrightness(unsigned int value)
{
	struct v4l2_control control;
	memset (&control, 0, sizeof (control));
	control.id = V4L2_CID_BRIGHTNESS;
	control.value = (int)(((float)(controls.maxbrightness - controls.minbrightness)/(float)65535) * (float)value + controls.minbrightness);

	if (ioctl (fd, VIDIOC_S_CTRL, &control) == -1) {
		perror ("VIDIOC_S_CTRL");
		return false;
	}

	return true;
}

bool VideoForLinux2::getBrightness(unsigned int &value)
{
	struct v4l2_control control;
	memset (&control, 0, sizeof (control));
	control.id = V4L2_CID_BRIGHTNESS;

	if (ioctl (fd, VIDIOC_G_CTRL, &control) == 0) {
		value = (control.value - controls.minbrightness) * (int)((float)65535/(float)(controls.maxbrightness - controls.minbrightness));
		/* Ignore if V4L2_CID_BRIGHTNESS is unsupported */
	}
	else if (errno != EINVAL) {
		perror ("VIDIOC_G_CTRL");
		return false;
	}
	return true;
}

bool VideoForLinux2::setContrast(unsigned int value)
{
    struct v4l2_control control;
    memset (&control, 0, sizeof (control));
    control.id = V4L2_CID_CONTRAST;
    control.value = (int)(((float)(controls.maxcontrast - controls.mincontrast)/(float)65535) * (float)value + controls.mincontrast);

    if (ioctl (fd, VIDIOC_S_CTRL, &control) == -1) {
        perror ("VIDIOC_S_CTRL");
        return false;
    }

    return true;
}

bool VideoForLinux2::getContrast(unsigned int &value)
{
    struct v4l2_control control;
    memset (&control, 0, sizeof (control));
    control.id = V4L2_CID_CONTRAST;

    if (ioctl (fd, VIDIOC_G_CTRL, &control) == 0) {
        value = (control.value - controls.mincontrast) * (int)((float)65535/(float)(controls.maxcontrast - controls.mincontrast));
        /* Ignore if V4L2_CID_CONTRAST is unsupported */
    }
    else if (errno != EINVAL) {
        perror ("VIDIOC_G_CTRL");
        return false;
    }
    return true;
}

bool VideoForLinux2::setGamma(unsigned int value)
{
    struct v4l2_control control;
    memset (&control, 0, sizeof (control));
    control.id = V4L2_CID_GAMMA;
    control.value = (int)(((float)(controls.maxgamma - controls.mingamma)/(float)65535) * (float)value + controls.mingamma);

    if (ioctl (fd, VIDIOC_S_CTRL, &control) == -1) {
        perror ("VIDIOC_S_CTRL");
        return false;
    }

    return true;
}

bool VideoForLinux2::getGamma(unsigned int &value)
{
    struct v4l2_control control;
    memset (&control, 0, sizeof (control));
    control.id = V4L2_CID_GAMMA;

    if (ioctl (fd, VIDIOC_G_CTRL, &control) == 0) {
        value = (control.value - controls.mingamma) * (int)((float)65535/(float)(controls.maxgamma - controls.mingamma));
        /* Ignore if V4L2_CID_GAMMA is unsupported */
    }
    else if (errno != EINVAL) {
        perror ("VIDIOC_G_CTRL");
        return false;
    }
    return true;
}

bool VideoForLinux2::setSaturation(unsigned int value)
{
    struct v4l2_control control;
    memset (&control, 0, sizeof (control));
    control.id = V4L2_CID_SATURATION;
    control.value = (int)(((float)(controls.maxsaturation - controls.minsaturation)/(float)65535) * (float)value + controls.minsaturation);

    if (ioctl (fd, VIDIOC_S_CTRL, &control) == -1) {
        perror ("VIDIOC_S_CTRL");
        return false;
    }

    return true;
}

bool VideoForLinux2::getSaturation(unsigned int &value)
{
    struct v4l2_control control;
    memset (&control, 0, sizeof (control));
    control.id = V4L2_CID_SATURATION;

    if (ioctl (fd, VIDIOC_G_CTRL, &control) == 0) {
        value = (control.value - controls.minsaturation) * (int)((float)65535/(float)(controls.maxsaturation - controls.minsaturation));
        /* Ignore if V4L2_CID_SATURATION is unsupported */
    }
    else if (errno != EINVAL) {
        perror ("VIDIOC_G_CTRL");
        return false;
    }
    return true;
}

void VideoForLinux2::setControls()
{
	struct v4l2_queryctrl queryctrl;

	controlsSetted = true;
	//enumerateControls();

	/*BRIGHTNESS*/
	memset (&queryctrl, 0, sizeof (queryctrl));
	queryctrl.id = V4L2_CID_BRIGHTNESS;

	if (ioctl (fd, VIDIOC_QUERYCTRL, &queryctrl) == -1)
	{
		if (errno != EINVAL)
		{
				perror ("VIDIOC_QUERYCTRL");
				//return false;
		}
		else
		{
			fprintf (stderr, "V4L2_CID_BRIGHTNESS is not supported\n");
		}
	}
	else if (queryctrl.flags & V4L2_CTRL_FLAG_DISABLED)
	{
		fprintf (stderr, "V4L2_CID_BRIGHTNESS is not supported\n");
	}

	controls.minbrightness = queryctrl.minimum;
	controls.maxbrightness = queryctrl.maximum;

	/*CONTRAST*/
	memset (&queryctrl, 0, sizeof (queryctrl));
	queryctrl.id = V4L2_CID_CONTRAST;

	if (ioctl (fd, VIDIOC_QUERYCTRL, &queryctrl) ==-1)
	{
		if (errno != EINVAL)
		{
				perror ("VIDIOC_QUERYCTRL");
				//return false;
		}
		else 
		{
			fprintf (stderr, "V4L2_CID_CONTRAST is not supported\n");
		}
	}
	else if (queryctrl.flags & V4L2_CTRL_FLAG_DISABLED)
	{
		fprintf (stderr, "V4L2_CID_CONTRAST is not supported\n");
	}

	controls.mincontrast = queryctrl.minimum;
	controls.maxcontrast = queryctrl.maximum;

	/*GAMMA*/
	memset (&queryctrl, 0, sizeof (queryctrl));
	queryctrl.id = V4L2_CID_GAMMA;

	if (ioctl (fd, VIDIOC_QUERYCTRL, &queryctrl) ==-1)
	{
		if (errno != EINVAL)
		{
				perror ("VIDIOC_QUERYCTRL");
				//return false;
		}
		else {
			fprintf (stderr, "V4L2_CID_GAMMA is not supported\n");
		}
	}
	else if (queryctrl.flags & V4L2_CTRL_FLAG_DISABLED)
	{
		fprintf (stderr, "V4L2_CID_GAMMA is not supported\n");
	}

	controls.mingamma = queryctrl.minimum;
	controls.maxgamma = queryctrl.maximum;

	/*SATURATION*/
	memset (&queryctrl, 0, sizeof (queryctrl));
	queryctrl.id = V4L2_CID_SATURATION;

	if (ioctl (fd, VIDIOC_QUERYCTRL, &queryctrl) ==-1)
	{
		if (errno != EINVAL)
		{
				perror ("VIDIOC_QUERYCTRL");
				//return false;
		}
		else
		{
			fprintf (stderr, "V4L2_CID_SATURATION is not supported\n");
		}
	}
	else if (queryctrl.flags & V4L2_CTRL_FLAG_DISABLED)
	{
		fprintf (stderr, "V4L2_CID_SATURATION is not supported\n");
	}

	controls.minsaturation = queryctrl.minimum;
	controls.maxsaturation = queryctrl.maximum;
}

void VideoForLinux2::enumerateMenu(struct v4l2_queryctrl &queryctrl, struct v4l2_querymenu querymenu)
{
	printf ("  Menu items:\n");

	memset (&querymenu, 0, sizeof (querymenu));
	querymenu.id = queryctrl.id;

	for (querymenu.index = queryctrl.minimum; querymenu.index <= queryctrl.maximum; querymenu.index++)
	{
		if (0 == ioctl (fd, VIDIOC_QUERYMENU, &querymenu))
		{
			printf ("  %s\n", querymenu.name);
		}
		else
		{
			perror ("VIDIOC_QUERYMENU");
			exit (EXIT_FAILURE);
		}
	}
}

void VideoForLinux2::enumerateControls()
{
	struct v4l2_queryctrl queryctrl;
	struct v4l2_querymenu querymenu;

	memset (&queryctrl, 0, sizeof (queryctrl));

	for (queryctrl.id = V4L2_CID_BASE; queryctrl.id < V4L2_CID_LASTP1; queryctrl.id++)
	{
		if (ioctl(fd, VIDIOC_QUERYCTRL, &queryctrl) == 0) {
			if (queryctrl.flags & V4L2_CTRL_FLAG_DISABLED) {
				printf("Control %s disabled\n", queryctrl.name);
				continue;
			}

			printf("Control %s\n", queryctrl.name);

			if (queryctrl.type == V4L2_CTRL_TYPE_MENU)
				enumerateMenu(queryctrl, querymenu);
		}
		else {
			if (errno == EINVAL) {
				//perror("VIDIOC_QUERYCTRL");
				continue;
			}

			perror("VIDIOC_QUERYCTRL");
			exit(EXIT_FAILURE);
		}
	}
	
	for (queryctrl.id = V4L2_CID_PRIVATE_BASE; ; queryctrl.id++)
	{
		if (0 == ioctl(fd, VIDIOC_QUERYCTRL, &queryctrl)) {
			if (queryctrl.flags & V4L2_CTRL_FLAG_DISABLED)
				continue;

			printf("Control %s\n", queryctrl.name);

			if (queryctrl.type == V4L2_CTRL_TYPE_MENU)
				enumerateMenu(queryctrl, querymenu);
		}
		else {
			if (errno == EINVAL)
				break;

			perror("VIDIOC_QUERYCTRL");
			exit(EXIT_FAILURE);
		}
	}
}

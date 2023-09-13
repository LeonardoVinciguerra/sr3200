//---------------------------------------------------------------------------
//
// Name:        VideoDevice.h
// Author:      Gabriel Ferri
// Created:     25/07/2008
// Description: VideoDevice class definition
//
//---------------------------------------------------------------------------
#ifndef _VIDEODEVICE_H
#define _VIDEODEVICE_H

#include <string>
#include <linux/videodev2.h>
#include "v4l2.h"

#define VIDIOCGCAP              _IOR('v',1,struct video_capability)     /* Get capabilities */

struct video_capability
{
         char name[32];
         int type;
         int channels;   /* Num channels */
         int audios;     /* Num audio devices */
         int maxwidth;   /* Supported width */
         int maxheight;  /* And height */
         int minwidth;   /* Supported width */
         int minheight;  /* And height */
};

class VideoDevice
{
public:
	VideoDevice();
	~VideoDevice();

	void closeDevice();
	bool openDevice( const std::string &device, unsigned int width, unsigned int height, int format);
	/*binded functions*/
	bool getFrame(char **buffer);
	bool setResolution(unsigned int width, unsigned int height, unsigned int frameRate=0);
	bool getResolution(unsigned int &width, unsigned int &height, unsigned int &frameRate);
	bool setBrightness(unsigned int value);
	bool getBrightness(unsigned int &value);
	bool setContrast(unsigned int value);
	bool getContrast(unsigned int &value);
	bool setGamma(unsigned int value);
	bool getGamma(unsigned int &value);
	bool setSaturation(unsigned int value);
	bool getSaturation(unsigned int &value);
	/*end binded functions*/
	bool queryCapabilities(struct video_capability *caps); /*VIDIOCGCAP*/
	bool queryCapabilities(struct v4l2_capability *cap); /*VIDIOC_QUERYCAPP*/

private:

	bool adjustColors;
	bool isOpen;
	int fd;
	VideoForLinux2 *v4l;
};

#endif /* _VIDEODEVICE_H */

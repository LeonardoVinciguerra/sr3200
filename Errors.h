//---------------------------------------------------------------------------
//
// Name:        Errors.h
// Author:      Daniele Belloni
// Created:     16/10/2007
// Description: Definitions for the SR3200 errors
//
//---------------------------------------------------------------------------
#ifndef __ERRORS_H
#define __ERRORS_H

#define ERR_NOERROR				0x00000000
#define ERR_ORIGNOSET			0x00000001
#define ERR_SETOUTPUT			0x00000002
#define ERR_GETINPUT			0x00000004
#define ERR_SETINPUT			0x00000008
#define ERR_LIMITSOFTWARE		0x00000010
#define ERR_LIMITSWITCH			0x00000020
#define ERR_MOTORMOVE			0x00000040
#define ERR_MOTORWAIT			0x00000080
#define ERR_CAMSECURITY			0x00000100 //n.u.
#define ERR_ZSECURITY			0x00000200 //n.u.
#define ERR_MOTORINIT			0x00000400
#define ERR_DRIVER				0x00000800
#define ERR_IMMEDIATESTOP		0x00001000
#define ERR_SERIALPORT			0x00002000
#define ERR_BRUSHLESS			0x00004000

#endif

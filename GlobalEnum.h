//---------------------------------------------------------------------------
//
// Name:        GlobalEnum.h
// Author:      Gabriel Ferri
// Created:     25/10/2007
// Description: Definitions for the SR3200 enum
//
//---------------------------------------------------------------------------
#ifndef __GLOBALENUM_H
#define __GLOBALENUM_H

enum MotorEnum
{
	MOTOR_TABLE1_ID,
	MOTOR_TABLE2_ID,
	MOTOR_TABLE3_ID,
	MOTOR_CAMERAX_ID,
	MOTOR_CAMERAY_ID,
	MOTOR_PLATE_ID,
	MOTOR_SQUEEGEES_ID,
	MOTOR_LOADER_ID,
	MOTOR_LCONV_WIDTH_ID,
	MOTOR_LCONV_FEED_ID,
	MOTOR_CCONV_WIDTH_ID,
	MOTOR_CCONV_FEED_ID,
	MOTOR_CLEANING_ID,
	MOTOR_LCONV_PUSH_ID,
};

enum SpeedEnum
{
	SPEED_PLATE_UP_ID,
	SPEED_CAMERA_ID,
	SPEED_SQUEEGEES_ID,
	SPEED_TABLE_ID,
	SPEED_DISENGAGE_ID,
	SPEED_PLATE_DOWN_ID,
	SPEED_CONV_WIDTH_ID,
	SPEED_CONV_FEED_ID,
	SPEED_LOADER_ID,
	SPEED_CONV_PUSH_ID
};

enum DriverEnum
{
	DRIVER_STEPPER_ID,
	DRIVER_BRUSHLESS_ID,
	DRIVER_BRUSH_ID
};

enum CameraEnum
{
	CAMERA_OFF,
	CAMERA_UP,
	CAMERA_DOWN
};

enum CameraLightEnum
{
	LED_HIGH,
	LED_LOW
};

enum AlarmLightEnum
{
	ALARMLIGHT_RED,
	ALARMLIGHT_GREEN,
	ALARMLIGHT_YELLOW,
	ALARMLIGHT_OFF
};

enum FiducialTypeEnum
{
	// points used during alignment STEP2 and printing
	FIDUCIAL_ROT1,
	FIDUCIAL_ROT2,
	FIDUCIAL_TRA,
	FIDUCIAL_ROT1_FRAME,
	FIDUCIAL_ROT2_FRAME,
	FIDUCIAL_TRA_FRAME,
	// points used during alignment STEP1
	FIDUCIAL_ROT1_A,
	FIDUCIAL_ROT2_A,
	FIDUCIAL_TRA_A,
	FIDUCIAL_ROT1_FRAME_A,
	FIDUCIAL_ROT2_FRAME_A,
	FIDUCIAL_TRA_FRAME_A,
	// points used during other functions
	FIDUCIAL_OFFSET,
	FIDUCIAL_OFFSET_FRAME,
	FIDUCIAL_VISION_TEST
};

enum FiducialSearchModeEnum
{
	FIDUCIAL_AUTO,
	FIDUCIAL_MANUAL
};

enum SearchModeEnum
{
	SEARCH_MODE_CIRCLE,
	SEARCH_MODE_RECTANGLE,
	SEARCH_MODE_TEMPLATE
};

enum VerifyModeEnum
{
	VERIFY_AUTO,
	VERIFY_MANUAL
};

enum InputSensorModeEnum
{
	INPUT_SENSOR_EXT_NONE,
	INPUT_SENSOR_EXT_LOAD,
	INPUT_SENSOR_EXT_START
};

enum OffsetDialogModeEnum
{
	OFFSET_VIEW_MAP,
	OFFSET_VIEW_CHECK,
	OFFSET_VIEW_DELTA
};

enum InspectionTypeEnum
{
	INSPECTION_OPERATOR,
	INSPECTION_SPI
};

enum VerifyONEnum
{
	VERYFYON_ON,
	VERYFYON_OFF,
};

enum InspectionOperatorTypeEnum
{
	INSPECTION_OPERATOR_AUTO,
	INSPECTION_OPERATOR_MANUAL
};

enum SiteTypeEnum
{
	SITE_TYPE_GENERIC,
	SITE_TYPE_BGA
};

enum ExceptionTypeEnum
{
	EXC_TYPE_NULL,
	EXC_TYPE_BGA
};

#endif

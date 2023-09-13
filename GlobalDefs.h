//---------------------------------------------------------------------------
//
// Name:        GlobalDefs.h
// Author:      Gabriel Ferri
// Created:     11/04/2008
// Description: Definitions for the SR3200 application
//
//---------------------------------------------------------------------------
#ifndef __GLOBALDEFS_H
#define __GLOBALDEFS_H

#define MACHINE_NAME				wxT("SR3200 Evo")


	//----------//
	// Versions //
	//----------//

#define SW_VERSION					wxT("2.11")
//#define DB_VERSION					wxT("1.00")
#define DB_VERSION					wxT("2.03")
#define SPI_DB_REL					1
#define SPI_DB_REV					0


	//------------------//
	// Application defs //
	//------------------//

#define	SR_OK						0
#define	SR_ERROR					-1
#define	SR_WARNING					-2

#define MACHINE_DB					wxT("SR3200.db")
//mio DB
#define AUTOspi_DB					wxT("DBspi.db")
//fine
#define FILE_DBEMPTY				wxT("empty.db")
#define FILE_DBEMPTY_SPI			wxT("empty.SPI.db")
#define FILE_DBBACKUPEXT			wxT(".dbb")
#define FILE_TEMPLATE				wxT("%s_%d.jpg")
#define FILE_PRODUCTION_FOLDER		wxT(".//vision//%s//")
#define FILE_FIDUCIALS_FOLDER		wxT(".//Fiducials/")
#define FILE_SITE					wxT("%s_%03d_site.jpeg")
#define FILE_SITEREF				wxT("%s_%03d_ref.jpeg")
#define FILE_CORRECTION_MASK		wxT("%s_Correction_Mask.jpeg")
#define DIR_LANGUAGES				wxT(".//languages")
#define DIR_DBBACKUP				wxT(".//backup//db")
#define DIR_SWBACKUP				wxT(".//backup//sw")
#define DIR_SWUPDATE				wxT(".//update")
#define DIR_DBUPDATE				wxT(".//dbupdate")
#define DIR_GERBER					wxT("./gerber")
#define DIR_LOGS					wxT("./logs")
#define DIR_SHARED_LOGS				wxT("/mnt/qserver/logs")
#define DIR_VISION					wxT(".//vision//")
#define DIR_SPI						wxT(".//spi//")

#define NUM_FIDUCIALS				12
#define NUM_MOTORS					14
#define NUM_SPEEDS					10
#define NUM_SERIALS					2
#define NUM_OFFSET_POINTS			195
#define NUM_IO						44
#define NUM_VERIFY_POINTS			10
#define NUM_PINS_POINTS				20
#define NUM_MOTORSBOARDS			9
#define NUM_INSPECTION_SITES		20
#define NUM_INSPECTION_POINTS		500
#define NUM_INSPECTION_RESULTS		1000
#define NUM_INSPECTION_AREAS		5
#define MAX_DISTANCE_TOGGLE			50.0f
#define HUE_DENOMINATOR				2.0
#define HUE_SLIDER_DENOM_FACTOR 	33.0
#define SPI_RECTANGLE_THICKNESS		2
#define SPI_RECTANGLE_OFFSET		10
#define SPI_SMALL_AREA_FACTOR		90.0
#define SPI_SMALL_AREA_MAX_CORR		1.1
#define SPI_SMALL_AREA_THRESHOLD	15.0
#define SPI_SMALL_AREA_VALIDITY		40.0
#define MAX_SCALE_ADAPTING			20
#define MAX_DISTANCE_SCALE_COST		30
#define CAMERA_ZERO_MAX_OFFSET		2.0
#define SHUTDOWN_AXIS_MARGIN		30

#define COMTIMEOUT					100
#define MOTOR_STATUS_DELAY			150

#define ORIGIN_SEARCH_SPEED_DIV		4

#define SQUEEGEES_DELAY				1000
#define SQUEEGEES_RECOVERY_DELAY	200
#define SQUEEGEES_DEF_SPEED			20

#define FLICKERING_DELAY			300
#define FLICKERING_DELAY_PROTOTYPE	400
#define MULTIPLE_IMAGES_DELAY		600
#define PIXEL_FROM_CENTER			3

#define CAMAXIS_DELAY				1000

#define INPUTTIMER					500
#define INPUTTIMERHWT				500
#define STATUSTIMER					500

#define MM_X_PIXEL					0.02f
// slider scale: eg. 20 -> 1/20=0.05 per step
#define CIRCLE_SCALE				20.0f
#define RECTANGLE_SCALE				20.0f
#define TOLERANCE_SCALE				20.0f
//
#define CIRCLE_DIAMETER_MIN_MM		0.20f
#define CIRCLE_DIAMETER_MAX_MM		8.00f
#define RECT_X_MIN_MM				0.20f
#define RECT_X_MAX_MM				6.00f
#define RECT_Y_MIN_MM				0.20f
#define RECT_Y_MAX_MM				6.00f
#define TOLERANCE_MIN_MM			0.05f
#define TOLERANCE_MAX_MM			0.30f
#define MAX_ALIGNMENT_ERROR			1.0f
#define MAX_UINT_VALUE				255

#define PLATE_MOVEMENT_DELTA_MIN	-3.0f
#define PLATE_MOVEMENT_DELTA_MAX	3.0f
#define PLATE_DISENGAGE_MIN			0.1f
#define PLATE_DISENGAGE_MAX			150.0f
#define VERIFY_DELAY_MIN			1
#define VERIFY_DELAY_MAX			10
#define RECOVERY_F_MIN				-50.0f
#define RECOVERY_F_MAX				50.0f
#define RECOVERY_R_MIN				-50.0f
#define RECOVERY_R_MAX				50.0f

#define OFFSET_NUMX_DEFAULT			13
#define OFFSET_NUMY_DEFAULT			15
#define OFFSET_DIST_DEFAULT			28.0

#define ALIGNMENT_ROTATION_DIFF		10.0f

#define CAMPISTON_DELAY				500

#define LOADERPISTON_DELAY			3500

#define LOCKPISTON_DELAY			500

#define CONVPISTON_DELAY			2700
#define CONVPISTON_MIN_Y			-390

#define CONVEYOR_WIDTH_DELTA		0.5f
#define CLEANING_CONVEYOR_OFFSET	30.0
//#define CAMERA_RAG_DISTANCE			150.0

#define CLEANINGPISTON_DELAY		500
#define CLEANINGUP_DELAY			1000

#define INCH_TO_MM					25.4f

#define PIN_PLACEMENT_SECURITY_DISTANCE 18.0
#define PIN_SORTING_THRESHOLD		30

#define MIN_RACK_POS				1
#define MAX_RACK_POS				50

#define  MIN_AREA_SPI				45
#define  MIN_AREA_SPI_PRINTING		5
#define  BORDER_DISTANCE_POST_PRINTING 30
#define  MAX_CHECK_DISALIGNMENT_PX	5

#define CENTRAL_HUE_GOLD			90
#define HUE_WIDTH_GOLD				20
#define PAD_COLOR_CENTER			240
#define PAD_COLOR_WIDTH				30

#define REDUCTION_SEMAPHORE			2
#define REDUCTION_BUZZER			2
#define PULSED_MODE_PERIOD			1000

#define MIN_NON_ZERO_PIXELS			100

	//--------------------//
	// Inputs/Outputs IDs //
	//--------------------//

#define OUTPUT_LEDUP				0
#define OUTPUT_LEDDOWN				1
#define OUTPUT_SQUEEGEESFRONT		2
#define OUTPUT_SQUEEGEESREAR		3
#define OUTPUT_FRAMEUNLOCK			4
#define OUTPUT_SEMAPHORE_RED		5
#define OUTPUT_SEMAPHORE_GREEN		6
#define OUTPUT_BUZZER				7
#define OUTPUT_TABLEVACUUM			8 // n.u. in SR3200
#define OUTPUT_BOARDLOCK			9
#define OUTPUT_CONVEYOR_PISTON		10
#define OUTPUT_LOADER_PISTON		11
#define OUTPUT_CAMERA_PISTON		12
#define OUTPUT_CLEANINGLOCK			38
#define OUTPUT_CLEANINGVACUUM		39
#define OUTPUT_SEMAPHORE_YELLOW		40
#define OUTPUT_CLEANINGACTIVATE		41

#define INPUT_LOADERCWLIM			13
#define INPUT_LOADERCCWLIM			14
#define INPUT_LOADERZERO			15
#define INPUT_SENSOR_EXT			16
#define INPUT_PEDALSTART			17 // n.u. in SR3200
#define INPUT_AIR					18
#define INPUT_PLATECWLIM			19
#define INPUT_PLATECCWLIM			20
#define INPUT_PLATEZERO				21
#define INPUT_SQUEEGEESCWLIM		22
#define INPUT_SQUEEGEESCCWLIM		23
#define INPUT_SQUEEGEESZERO			24
#define INPUT_CAMXZERO				25
#define INPUT_CAMYZERO				26
#define INPUT_COVER					27
#define INPUT_CAMXCWLIM				28
#define INPUT_CAMXCCWLIM			29
#define INPUT_CAMYCWLIM				30
#define INPUT_CAMYCCWLIM			31
#define INPUT_LCONVWZERO			32
#define INPUT_CCONVWZERO			33
#define INPUT_LCONVWCWLIM			34
#define INPUT_LCONVWCCWLIM			35
#define INPUT_CCONVWCWLIM			36
#define INPUT_CCONVWCCWLIM			37
#define INPUT_LCONVPZERO			42
#define INPUT_SENSOR_INT			43

//INPUT_SENSOR_EXT 		//Questo sensore e' il primo inserito nella macchina, si trovava a cavallo tra i due convogliatori.
						//Adesso e' stato messo all'esterno del convogliatore di sx

//INPUT_SENSOR_EXT 		//Questo sensore e' il secondo inserito. Presente solo nelle versioni con push motor

#define DISABLE_BUZZER_ID = 9989701;
	//--------------//
	// Structs Defs //
	//--------------//

struct PointD
{
	PointD() { X = 0.0; Y = 0.0; };
	PointD( double x, double y ) { X = x; Y = y; };
	PointD( const PointD& p ) { X = p.X; Y = p.Y; };

	double X, Y;
};

struct PointF
{
	PointF() { X = 0.f; Y = 0.f; };
	PointF( float x, float y ) { X = x; Y = y; };
	PointF( const PointF& p ) { X = p.X; Y = p.Y; };

	float X, Y;
};

struct PointI
{
	PointI() { X = 0; Y = 0; };
	PointI( int x, int y ) { X = x; Y = y; };
	PointI( const PointI& p ) { X = p.X; Y = p.Y; };

	int X, Y;
};

struct RectI
{
	RectI() { X = 0; Y = 0; Width = 0; Height = 0; };
	RectI( int x, int y, int width, int height ) { X = x; Y = y; Width = width; Height = height; };
	RectI( const RectI& r ) { X = r.X; Y = r.Y; Width = r.Width; Height = r.Height; };

	int X, Y, Width, Height;
};

struct CircleF
{
	CircleF() { X = Y = R = 0.f; };
	CircleF( float x, float y, float r ) { X = x; Y = y; R = r; };
	CircleF( const CircleF& c ) { X = c.X; Y = c.Y; R = c.R; };

	float X, Y, R;
};

struct CirclePattern
{
	CirclePattern()
	{
		value = 0;
		ok = false;
	};

	CircleF point;
	int value;
	bool ok;
};


#endif

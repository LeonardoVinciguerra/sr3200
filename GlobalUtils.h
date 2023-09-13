//---------------------------------------------------------------------------
//
// Name:        GlobalUtils.h
// Author:      Gabriel Ferri
// Created:     23/06/2008
// Description: GlobalUtils functions declaration
//
//---------------------------------------------------------------------------

#ifndef __GLOBALUTILS_H
#define __GLOBALUTILS_H

#include <wx/sizer.h>
#include <vector>

#define MAXNPATH				1024

#ifndef MAX
#define MAX(a, b)			(((a)>(b))?(a):(b)) 
#endif

#ifndef MIN
#define MIN(a, b)			(((a)>(b))?(b):(a))
#endif

#ifndef MID
#define MID(m,x,M)			(MIN(MAX((m),(x)),(M)))
#endif

#define MyDELETE(p)			if ( (p) != NULL ) { delete p; p = NULL; }
#define MyDELETEA(p)		if ( (p) ) { delete [] (p); p = NULL; }

#define PI					3.141592

#define RTOD(r)				((r) * 180 / PI)
#define DTOR(d)				((d) * PI / 180)
#define NORMALIZE(z)		atan2(sin(z), cos(z))

#define isNan(x)			((x) != (x))

#define FA_DIREC				1
#define FA_IGNORE_CASE			(1 << 8)

#define FFBLK_MAXFILE 			255
#define FFBLK_MAXDIR_NAME		768

#define DIR_CREATION_FLAG		S_IRWXG | S_IRWXU | S_IROTH | S_IXOTH

#define chsize(handle,size)		ftruncate(handle,size)

struct ffblk
{
	char lfn_magic[6];			/* LFN: the magic "LFN32" signature */
	short lfn_handle;			/* LFN: the handle used by findfirst/findnext */
	unsigned short lfn_ctime;	/* LFN: file creation time */
	unsigned short lfn_cdate;	/* LFN: file creation date */
	unsigned short lfn_atime;	/* LFN: file last access time (usually 0) */
	unsigned short lfn_adate;	/* LFN: file last access date */
	char ff_reserved[5];		/* used to hold the state of the search */
	mode_t ff_attrib;	/* actual attributes of the file found */
	unsigned short ff_ftime;	/* hours:5, minutes:6, (seconds/2):5 */
	unsigned short ff_fdate;	/* (year-1980):7, month:4, day:5 */
	unsigned long ff_fsize;		/* size of file */
	char ff_name[FFBLK_MAXFILE+1];	/* name of file as ASCIIZ string */

	//only for linux
	DIR*			dirp;
	struct dirent*	dir_entry;
	unsigned int	attributes;
	char			filespec[FFBLK_MAXFILE+1];
	char			path[FFBLK_MAXDIR_NAME+1];
};

int findnext(struct ffblk *ffblk);
int findfirst(const char *pathname, struct ffblk *ffblk, int attrib);
void end_findfirst(ffblk* fb);

void myMilliSleep( unsigned int milliseconds );

long myLRound( double x );

void EnableSizerChilds( wxSizer* container, bool state );

int CopyFile( const char *file_in, const char *file_out );
bool CheckFile( const char* filename );
bool FindFiles( const char* path, const char* type, std::vector<std::string>& list, bool removeExt );
bool DeleteFiles( const char* dir, const char* filename );
bool RenameFiles( const char* dir, const char* oldName, const char* newName );
bool CheckDirectory( const char* dir );

bool IsFiducialOnPCB( int fiducialType );

void cairoToWxImageFormat(unsigned char *source, unsigned char *dest, int width, int height);

#ifndef __WXMSW__
	size_t getAllUsbMountPoints( wxArrayString* drives );
#endif


	//--------//
	// Config //
	//--------//

#define CONFIG_FILE				wxT( "sr3200.cfg" )

#define MACHINE_ENABLE			1
#define VISION_VERIFY_ENABLE	2
#define PASSWORD_ENABLE			3
#define CAMERA_ENABLE			4
#define GRABBER_ENABLE			5
#define DISABLE_TABLE			6
#define DISABLE_PLATE			7
#define DISABLE_CAMERA			8
#define DISABLE_LOADER			9
#define DISABLE_SQUEEGEES		10
#define ENABLE_SEMAPHORE		11
#define DISABLE_LCONVW			12
#define DISABLE_LCONVF			13
#define DISABLE_CCONVW			14
#define DISABLE_CCONVF			15
#define EXTERNAL_CONV_SENSOR		16
#define RES1366					17
#define RACK_WARNING			18
#define DISABLE_CLEANER			19
#define CAMERA_COLOR			20
#define NO_ZERO_SEARCH			21
#define CONV_PUSH_MOTOR			22
#define DISABLE_LCONVP			23
#define SHARED_LOG				24


void LoadConfig();
int MachineConfig( int mode );

#define MACHINE_CONFIG(mode)		if( MachineConfig( mode ) ) {
#define MACHINE_CONFIG_NOT(mode)	if( !MachineConfig( mode ) ) {
#define MACHINE_CONFIG_END			}
#define MACHINE_CONFIG_ELSE			} else {

#endif

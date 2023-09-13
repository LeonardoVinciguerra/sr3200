//---------------------------------------------------------------------------
//
// Name:        GlobalUtils.cpp
// Author:      Gabriel Ferri
// Created:     23/06/2008
// Description: GlobalUtils functions implementation
//
//---------------------------------------------------------------------------

#include "GlobalUtils.h"
#include <wx/file.h>
#include "GlobalEnum.h"
#include <errno.h>
#include <fnmatch.h>
#include <iostream>
#ifndef __WXMSW__
#include <mntent.h>

#define DISK_DEV_PREFIX 		"/dev/sd"
#define USB_MOUNT_PREFIX 		"/media"
//flag per /sys/block/xxx/capability
#define GENHD_FL_CD				0x08
#endif


//----------------------------------------------------------------------------------
// myMilliSleep
// 
//----------------------------------------------------------------------------------
void myMilliSleep( unsigned int milliseconds )
{
	for( unsigned int i = 0; i < milliseconds; i += 2 )
	{
		::wxYield();
		wxMilliSleep( 1 );
	}
}

//----------------------------------------------------------------------------------
// myLRound
// 
//----------------------------------------------------------------------------------
long myLRound( double x )
{
	if( x >= 0.0 )
		return ( x - long( x ) > 0.5 ) ? long( x ) + 1 : long( x );
	else
		return ( x - long( x ) > -0.5 ) ? long( x ) : long( x ) - 1;
}

//----------------------------------------------------------------------------------
// EnableSizerChilds
// Abilita/disabilita tutti i controlli all'interno di un sizer
//----------------------------------------------------------------------------------
void EnableSizerChilds( wxSizer* container, bool state )
{
	wxSizerItemList childs = container->GetChildren();

	wxSizerItemList::iterator it = childs.begin(), end = childs.end();
	while( it != end )
	{
		if( (*it)->IsWindow() )
			((*it)->GetWindow())->Enable( state );
		else if( (*it)->IsSizer() )
			EnableSizerChilds( (*it)->GetSizer(), state );
		it++;
	}
}

//----------------------------------------------------------------------------------
// IsFiducialOnPCB
// Controlla se il fiduciale � sul PCB o no
//----------------------------------------------------------------------------------
bool IsFiducialOnPCB( int fiducialType )
{
	if( fiducialType == FIDUCIAL_ROT1 || fiducialType == FIDUCIAL_ROT2 || fiducialType == FIDUCIAL_TRA ||
		fiducialType == FIDUCIAL_ROT1_A || fiducialType == FIDUCIAL_ROT2_A || fiducialType == FIDUCIAL_TRA_A )
		return true;
	return false;
}

#ifndef __WXMSW__
//----------------------------------------------------------------------------------
// strncpyQ
// Overload della funzione strncpy per gestire l'inserimento del carattere di fine
// stringa in s1, quando s2 e' piu' lunga di maxcar
//----------------------------------------------------------------------------------
char *strncpyQ(char *s1,const char *s2,unsigned int maxcar)
{
	if((s1==NULL) || (s2==NULL))
		return(NULL);

	if(*s2=='\0')
	{
		*s1='\0';
	}
	else
	{
		if(strlen(s2)<=maxcar)
		{
			memcpy((char *)s1,(char *)s2,strlen(s2)+1);
		}
		else
		{
			memcpy((char *)s1,(char *)s2,maxcar);
			s1[maxcar]='\0';
		}
	}

	return(s1);
}

//----------------------------------------------------------------------------------
// isDeviceRemovable
// Controlla se il dispositivo passato come parametro � un disco rimovibile
//----------------------------------------------------------------------------------
bool isDeviceRemovable( char* dev )
{
	char path[MAXNPATH];
	char buf[8];
	int data;
	FILE* f;
	
	char* d = strstr(dev,"/dev/");
	if(d == NULL)
	{
		return false;
	}
	
	strcpy(path,"/sys/block/");
	strcat(path,d+strlen("/dev/"));
	strcat(path,"/removable");
	f = fopen(path,"r");
	if(f == NULL)
	{
		return false;
	}
	fgets(buf,2,f);
	sscanf(buf,"%d",&data);
	if(data == 0)
	{
		fclose(f);
		return false;
	}
	else
	{
		fclose(f);
	}
	
	strcpy(path,"/sys/block/");
	strcat(path,dev);
	strcat(path,"/capability");
	f = fopen(path,"r");
	if(f == NULL)
	{
		return true;
	}
	fgets(buf,2,f);
	sscanf(buf,"%x",&data);
	if(data & GENHD_FL_CD)
	{
		//e'un CD !!
		fclose(f);
		return false;
	}
	else
	{
		fclose(f);
		return true;
	}
}

//----------------------------------------------------------------------------------
// getAllUsbMountPoints
// Ricerca tutti i dispositivi rimovibili
//----------------------------------------------------------------------------------
size_t getAllUsbMountPoints( wxArrayString* drives )
{
	drives->Clear();

	FILE* f = setmntent("/etc/mtab","r");
	
	if( f == NULL )
	{
		return 0;
	}
	
	struct mntent *mnt;
	bool ret = false;
	
	while(mnt = getmntent(f))
	{
		struct stat st;
		if(stat(mnt->mnt_dir,&st) == 0)
		{
			if(!strncmp(mnt->mnt_fsname,DISK_DEV_PREFIX,strlen(DISK_DEV_PREFIX)) && !strncmp(mnt->mnt_dir,USB_MOUNT_PREFIX,strlen(USB_MOUNT_PREFIX)))
			{
				char buf[MAXNPATH];
				strncpyQ(buf,mnt->mnt_fsname,strlen(DISK_DEV_PREFIX)+1);
				if(isDeviceRemovable(buf))
				{
					drives->Add( mnt->mnt_dir );
				}
			}
		}
	}
	
	endmntent(f);
	return drives->GetCount();
}
#endif

static struct stat _dir_stat_data;

int findfirst( const char* pathname, ffblk* fb, int attrib )
{
	char *slash_ptr = (char*)pathname;
	char *prev_slash_ptr = NULL;

	do
	{
		slash_ptr = strchr(slash_ptr,'/');
		if(slash_ptr)
		{
			prev_slash_ptr = slash_ptr;
			slash_ptr++;
		}
		else
		{
			break;
		}
	} while(1);

	if(prev_slash_ptr)
	{
		strncpy(fb->path,pathname,prev_slash_ptr - pathname);
		strcpy(fb->filespec,prev_slash_ptr + 1);
		fb->path[prev_slash_ptr - pathname ]=0;
	}
	else
	{
		strcpy(fb->path,".");
		strcpy(fb->filespec,pathname);
	}

	fb->attributes = attrib;
	fb->dirp = opendir(fb->path);

	int r = findnext(fb);

	return r;
}

int findnext(ffblk* fb)
{
	char fullpath[FFBLK_MAXDIR_NAME];

	if(!fb->dirp)
	{
		memset(fb,0,sizeof(fb));
		errno = ENOENT;
		return(-1);
	}

	while((fb->dir_entry = readdir(fb->dirp)) != NULL)
	{
		strcpy(fullpath,fb->path);
		strcat(fullpath,"/");
		strcat(fullpath,fb->dir_entry->d_name);

		if(stat(fullpath, &_dir_stat_data))
		{
			continue;
		}

		bool dot_added = false;

		char *dot = strchr(fb->dir_entry->d_name,'.');
		if(!dot)
		{
			strcat(fb->dir_entry->d_name,".");
			dot_added = true;
		}

		if( S_ISDIR(_dir_stat_data.st_mode) )
		{
			if( !(fb->attributes & FA_DIREC) )
			{
				continue;
			}
		}
		else
		{
			if( fb->attributes & FA_DIREC )
			{
				continue;
			}
		}

		int flags = FNM_PATHNAME;
		if(fb->attributes & FA_IGNORE_CASE)
		{
			flags|=FNM_CASEFOLD;
		}

		if(!fnmatch(fb->filespec, fb->dir_entry->d_name,flags))
		{
			strncpy(fb->ff_name,fb->dir_entry->d_name,FFBLK_MAXFILE);
			if(dot_added)
			{
				fb->ff_name[strlen(fb->ff_name) - 1] = '\0';
			}

			fb->ff_fsize = _dir_stat_data.st_size;

			struct tm *t;
			t = localtime(&_dir_stat_data.st_mtime);

			fb->ff_ftime = (t->tm_sec /2) & 0x1f;
			fb->ff_ftime |= (t->tm_min & 0x3f) << 5;
			fb->ff_ftime |= (t->tm_min & 0x1f) << 11;

			fb->ff_fdate = (t->tm_mday & 0x1f);
			fb->ff_fdate |= (t->tm_mon & 0x0f) << 5;
			fb->ff_fdate  |= ((t->tm_year - 80) & 0x7f) << 9;

			fb->ff_attrib = _dir_stat_data.st_mode;

			return(0);
		}
	}

	closedir(fb->dirp);
	fb->dirp = NULL;

	memset(fb,0,sizeof(fb));
	errno = ENOENT;
	return(-1);
}

void end_findfirst(ffblk* fb)
{
	if(fb->dirp != NULL)
	{
		closedir(fb->dirp);
		fb->dirp = NULL;
	}
}

//---------------------------------------------------------------------------
// Ritorna true se il file e' presente
//---------------------------------------------------------------------------
bool CheckFile( const char* filename )
{
	return access( filename, F_OK ) == 0 ? true : false;
}

//----------------------------------------------------------------------------------
// CopyFile
// Copia file_in in file_out
//----------------------------------------------------------------------------------
int CopyFile( const char *file_in, const char *file_out )
{
	FILE *in, *out;
	char ch;

	if( ( in = fopen( file_in, "rb" ) ) == NULL )
		return 1;

	if( ( out = fopen( file_out, "wb" ) ) == NULL )
		return 2;

	while( !feof(in) )
	{
		ch = getc(in);
		if( ferror(in) )
		{
			clearerr(in);
			fclose(in);
			fclose(out);
			return 3;
		}
		if( !feof(in) )
			putc(ch, out);
		if( ferror(out) )
		{
			clearerr(out);
			fclose(in);
			fclose(out);
			return 4;
		}
	}

	fclose(in);
	fclose(out);
	return 0;
}

//---------------------------------------------------------------------------
// Cerca file o cartelle (se type = 0 cerca cartelle)
//---------------------------------------------------------------------------
bool FindFiles( const char* path, const char* type, std::vector<std::string>& list, bool removeExt )
{
	char filesName[MAXNPATH];

	int flags = FA_IGNORE_CASE;
	if( type == 0 )
	{
		flags |= FA_DIREC;
		snprintf( filesName, MAXNPATH, "%s/*", path );
	}
	else
	{
		snprintf( filesName, MAXNPATH, "%s/%s", path, type );
	}

	struct ffblk ffblk;
	int done = findfirst( filesName, &ffblk, flags );

	while( !done )
	{
		if( removeExt )
		{
			char* p = strchr( ffblk.ff_name, '.' );
			if( p != NULL && p != ffblk.ff_name )
			{
				*p = '\0';
			}
		}

		if( flags & FA_DIREC )
		{
			if( ffblk.ff_name[0] != '.' )
			{
				list.push_back( ffblk.ff_name );
			}
		}
		else
		{
			list.push_back( ffblk.ff_name );
		}

		done = findnext( &ffblk );
	}

	return true;
}

//---------------------------------------------------------------------------
// Elimina tutti i files filename.* dalla cartella dir
//---------------------------------------------------------------------------
bool DeleteFiles( const char* dir, const char* filename )
{
	char sFile[MAXNPATH];
	std::vector<std::string> fileslist;

	std::string filemask = filename;
	filemask.append( ".*" );

	FindFiles( dir, filemask.c_str(), fileslist, false );

	bool err = false;

	for( unsigned int i = 0; i < fileslist.size(); i++ )
	{
		snprintf( sFile, MAXNPATH, "%s/%s", dir, fileslist[i].c_str() );

		if( remove( sFile ) != 0 )
		{
			err = true;
		}
	}

	return !err;
}

//---------------------------------------------------------------------------
// Rinomina tutti i files oldName.* in newName.*
//---------------------------------------------------------------------------
bool RenameFiles( const char* dir, const char* oldName, const char* newName )
{
	char dFile[MAXNPATH];
	char sFile[MAXNPATH];
	std::vector<std::string> fileslist;

	std::string filemask = oldName;
	filemask.append( ".*" );

	FindFiles( dir, filemask.c_str(), fileslist, false );

	bool err = false;

	for( unsigned int i = 0; i < fileslist.size(); i++ )
	{
		size_t found = fileslist[i].find_last_of( "." );
		if( found == std::string::npos )
			continue;

		snprintf( sFile, MAXNPATH, "%s/%s", dir, fileslist[i].c_str() );
		snprintf( dFile, MAXNPATH, "%s/%s%s", dir, newName, fileslist[i].substr(found).c_str() );

		if( rename( sFile, dFile ) != 0 )
		{
			err = true;
		}
	}

	return !err;
}

//---------------------------------------------------------------------------
// Ritorna true se la directory e' presente
//---------------------------------------------------------------------------
bool CheckDirectory( const char* dir )
{
	std::cout << "dir: "<< dir;
	struct stat st;
	if( stat( dir, &st ) == 0 )
	{
		if( S_ISDIR( st.st_mode ) )
		{
			return true;
		}
	}
	else
	{
		perror( "stat" );
	}

	return false;
}

//---------------------------------------------------------------------------
// Translate the raw image data from the format stored
// by cairo into a format understood by wxImage.
//---------------------------------------------------------------------------
void cairoToWxImageFormat(unsigned char *source, unsigned char *dest, int width, int height)
{
	int offset = 0;
	for(size_t count = 0; count < width*height*4; count+=4)
	{
		int r = *(source+count+2);
		*(dest + offset) = r;
		offset++;
		int g = *(source+count+1);
		*(dest + offset) = g;
		offset++;
		int b = *(source+count+0);
		*(dest + offset) = b;
		offset++;
	}
}

	//--------//
	// Config //
	//--------//

int flag_machine_enable = 1;
int flag_vision_verify = 0;
int flag_use_password = 1;
int flag_camera_enable = 1;
int flag_grabber_enable = 1;
int flag_table_disable = 0;
int flag_plate_disable = 0;
int flag_cameraxy_disable = 0;
int flag_squeegees_disable = 0;
int flag_semaphore_enable = 0;
int flag_loader_disable = 0;
int flag_lconvw_disable = 0;
int flag_lconvf_disable = 0;
int flag_cconvw_disable = 0;
int flag_cconvf_disable = 0;
int flag_ext_conv_sensor = 0;
int flag_res_1366 = 0;
int flag_rack_warning = 0;
int flag_cleaner_disable = 0;
int flag_camera_color = 0;
int flag_camera_zero_search = 1;
int flag_conv_push_motor = 0;
int flag_lconvp_disable = 0;
int flag_shared_log = 0;

//----------------------------------------------------------------------------------
// LoadConfig
// Carica, se esiste, il file di configurazione della macchina
//----------------------------------------------------------------------------------
void LoadConfig()
{
	wxFile *inFile = new wxFile( CONFIG_FILE, wxFile::read );

	if( !inFile->IsOpened() )
	{
		delete inFile;
		return;
	}

	//read
	wxFileOffset len = inFile->Length();
	char *filebuf = new char[ len + 1 ];
	inFile->Seek( 0, wxFromStart );
	inFile->Read( filebuf, len );
	filebuf[len] = '\0';

	//
	char *pfilebuf;
	pfilebuf = strstr( filebuf, "NO_MACHINE" );
	if( pfilebuf != NULL )
		flag_machine_enable = 0;
	else
		flag_machine_enable = 1;

	pfilebuf = strstr( filebuf, "VISION_VERIFY" );
	if( pfilebuf != NULL )
		flag_vision_verify = 1;
	else
		flag_vision_verify = 0;

	pfilebuf = strstr( filebuf, "NO_PASSWORD" );
	if( pfilebuf != NULL )
		flag_use_password = 0;
	else
		flag_use_password = 1;

	pfilebuf = strstr( filebuf, "NO_CAMERA" );
	if( pfilebuf != NULL )
		flag_camera_enable = 0;
	else
		flag_camera_enable = 1;

	pfilebuf = strstr( filebuf, "NO_GRABBER" );
	if( pfilebuf != NULL )
		flag_grabber_enable = 0;
	else
		flag_grabber_enable = 1;

	pfilebuf = strstr( filebuf, "DISABLE_TABLE" );
	if( pfilebuf != NULL )
		flag_table_disable = 1;
	else
		flag_table_disable = 0;

	pfilebuf = strstr( filebuf, "DISABLE_PLATE" );
	if( pfilebuf != NULL )
		flag_plate_disable = 1;
	else
		flag_plate_disable = 0;

	pfilebuf = strstr( filebuf, "DISABLE_CAMERA" );
	if( pfilebuf != NULL )
		flag_cameraxy_disable = 1;
	else
		flag_cameraxy_disable = 0;

	pfilebuf = strstr( filebuf, "DISABLE_SQUEEGEES" );
	if( pfilebuf != NULL )
		flag_squeegees_disable = 1;
	else
		flag_squeegees_disable = 0;

	pfilebuf = strstr( filebuf, "DISABLE_LOADER" );
	if( pfilebuf != NULL )
		flag_loader_disable = 1;
	else
		flag_loader_disable = 0;

	pfilebuf = strstr( filebuf, "DISABLE_LCONVW" );
	if( pfilebuf != NULL )
		flag_lconvw_disable = 1;
	else
		flag_lconvw_disable = 0;

	pfilebuf = strstr( filebuf, "DISABLE_LCONVF" );
	if( pfilebuf != NULL )
		flag_lconvf_disable = 1;
	else
		flag_lconvf_disable = 0;

	pfilebuf = strstr( filebuf, "DISABLE_CCONVW" );
	if( pfilebuf != NULL )
		flag_cconvw_disable = 1;
	else
		flag_cconvw_disable = 0;

	pfilebuf = strstr( filebuf, "DISABLE_CCONVF" );
	if( pfilebuf != NULL )
		flag_cconvf_disable = 1;
	else
		flag_cconvf_disable = 0;

	pfilebuf = strstr( filebuf, "ENABLE_SEMAPHORE" );
	if( pfilebuf != NULL )
		flag_semaphore_enable = 1;
	else
		flag_semaphore_enable = 0;

	pfilebuf = strstr( filebuf, "EXTERNAL_CONV_SENSOR" );
	if( pfilebuf != NULL )
		flag_ext_conv_sensor = 1;
	else
		flag_ext_conv_sensor = 0;

	pfilebuf = strstr( filebuf, "RES1366" );
	if( pfilebuf != NULL )
		flag_res_1366 = 1;
	else
		flag_res_1366 = 0;

	pfilebuf = strstr( filebuf, "RACK_WARNING" );
	if( pfilebuf != NULL )
		flag_rack_warning = 1;
	else
		flag_rack_warning = 0;

	pfilebuf = strstr( filebuf, "DISABLE_CLEANER" );
	if( pfilebuf != NULL )
		flag_cleaner_disable = 1;
	else
		flag_cleaner_disable = 0;

	pfilebuf = strstr( filebuf, "CAMERA_COLOR" );
	if( pfilebuf != NULL )
		flag_camera_color = 1;
	else
		flag_camera_color = 0;
	pfilebuf = strstr( filebuf, "NO_ZERO_SEARCH" );
	if( pfilebuf != NULL )
		flag_camera_zero_search = 0;
	else
		flag_camera_zero_search = 1;
	pfilebuf = strstr( filebuf, "CONV_PUSH_MOTOR" );
	if( pfilebuf != NULL )
		flag_conv_push_motor = 1;
	else
		flag_conv_push_motor = 0;

	pfilebuf = strstr( filebuf, "DISABLE_LCONVP" );
	if( pfilebuf != NULL )
		flag_lconvp_disable = 1;
	else
		flag_lconvp_disable = 0;
	pfilebuf = strstr( filebuf, "SHARED_LOG" );
	if( pfilebuf != NULL )
		flag_shared_log = 1;
	else
		flag_shared_log = 0;

	//clear
	delete [] filebuf;
	inFile->Close();
	delete inFile;
}

//----------------------------------------------------------------------------------
// MachineConfig
// Ritorna il valore del flag relativo al modo passato come argomento
//----------------------------------------------------------------------------------
int MachineConfig( int mode )
{
	int ret_val;

	switch( mode )
	{
	case MACHINE_ENABLE:
		ret_val = flag_machine_enable;
		break;

	case VISION_VERIFY_ENABLE:
		ret_val = flag_vision_verify;
		break;

	case PASSWORD_ENABLE:
		ret_val = flag_use_password;
		break;

	case CAMERA_ENABLE:
		ret_val = flag_camera_enable;
		break;

	case GRABBER_ENABLE:
		ret_val = flag_grabber_enable;
		break;

	case DISABLE_TABLE:
		ret_val = flag_table_disable;
		break;

	case DISABLE_PLATE:
		ret_val = flag_plate_disable;
		break;

	case DISABLE_CAMERA:
		ret_val = flag_cameraxy_disable;
		break;

	case DISABLE_SQUEEGEES:
		ret_val = flag_squeegees_disable;
		break;

	case DISABLE_LOADER:
		ret_val = flag_loader_disable;
		break;

	case DISABLE_LCONVW:
		ret_val = flag_lconvw_disable;
		break;

	case DISABLE_LCONVF:
		ret_val = flag_lconvf_disable;
		break;

	case DISABLE_CCONVW:
		ret_val = flag_cconvw_disable;
		break;

	case DISABLE_CCONVF:
		ret_val = flag_cconvf_disable;
		break;

	case ENABLE_SEMAPHORE:
		ret_val = flag_semaphore_enable;
		break;

	case EXTERNAL_CONV_SENSOR:
		ret_val = flag_ext_conv_sensor;
		break;

	case RES1366:
		ret_val = flag_res_1366;
		break;

	case RACK_WARNING:
		ret_val = flag_rack_warning;
		break;

	case DISABLE_CLEANER:
		ret_val = flag_cleaner_disable;
		break;

	case CAMERA_COLOR:
		ret_val = flag_camera_color;
		break;
	case NO_ZERO_SEARCH:
		ret_val = flag_camera_zero_search;
		break;
	case CONV_PUSH_MOTOR:
		ret_val = flag_conv_push_motor;
		break;
	case DISABLE_LCONVP:
		ret_val = flag_lconvp_disable;
		break;
	case SHARED_LOG:
		ret_val = flag_shared_log;
		break;
	default:
		ret_val = -1;
	}

	return ret_val;
}

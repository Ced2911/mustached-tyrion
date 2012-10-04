#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>

#include <debug.h>

#include "../qcommon/qcommon.h"
#include "errno.h"

int	curtime;

unsigned	sys_frame_time;

void Sys_Error (char *error, ...)
{
	va_list		argptr;

	printf ("Sys_Error: ");	
	va_start (argptr,error);
	vprintf (error,argptr);
	va_end (argptr);
	printf ("\n");

	exit (1);
}

void Sys_Quit (void)
{
	exit (0);
}

void Sys_UnloadGame (void)
{
	TR;
}

void *Sys_GetGameAPI (void *parms)
{
	return (void*)GetGameAPI(parms);
}

char *Sys_ConsoleInput (void)
{
	return NULL;
}

void Sys_ConsoleOutput (char *string)
{
	printf(string);
	printf("\n");
}

void Sys_SendKeyEvents (void)
{
}

void Sys_AppActivate (void)
{
}

void Sys_CopyProtect (void)
{
	TR
}

char *Sys_GetClipboardData( void )
{
	return NULL;
}

//===============================================================================
static byte *membase;
static int maxhunksize;
static int curhunksize;
#define CACHE_LINE_SIZE 256

void *Hunk_Begin (int maxsize)
{
	// reserve a huge chunk of memory, but don't commit any yet
	maxhunksize = maxsize;
	curhunksize = 0;
	membase = malloc(maxhunksize);
	if (membase == NULL)
		Sys_Error(ERR_FATAL, "unable to allocate %d bytes", maxsize);
	memset(membase, 0, maxhunksize);
	return membase;
}

void *Hunk_Alloc (int size)
{
	byte *buf;

	// round to cacheline
	size = (size+(CACHE_LINE_SIZE-1))&~(CACHE_LINE_SIZE-1);
	//size = (size+31)&~31;
	if (curhunksize + size > maxhunksize)
		Sys_Error(ERR_FATAL, "Hunk_Alloc overflow");
	buf = membase + curhunksize;
	curhunksize += size;
	return buf;
}

int Hunk_End (void)
{
	byte *n;

	n = realloc(membase, curhunksize);
	if (n != membase)
		Sys_Error(ERR_FATAL, "Hunk_End:  Could not remap virtual block (%d)", errno);
	
	return curhunksize;
}

void Hunk_Free (void *base)
{
	if (base) 
		free(base);
}

//===============================================================================

int	Sys_Milliseconds (void)
{
	struct timeval tp;
	struct timezone tzp;
	static int		secbase;

	gettimeofday(&tp, &tzp);
	
	if (!secbase)
	{
		secbase = tp.tv_sec;
		return tp.tv_usec/1000;
	}

	curtime = (tp.tv_sec - secbase)*1000 + tp.tv_usec/1000;
	
	return curtime;
}

//===============================================================================

void Sys_Mkdir (char *path)
{
	mkdir (path, 0777);
}

//============================================

static	char	findbase[MAX_OSPATH];
static	char	findpath[MAX_OSPATH];
static	char	findpattern[MAX_OSPATH];
static	DIR		*fdir;

static qboolean CompareAttributes(char *path, char *name,
	unsigned musthave, unsigned canthave )
{
	struct stat st;
	char fn[MAX_OSPATH];

// . and .. never match
	if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
		return false;

	sprintf(fn, "%s/%s", path, name);
	if (stat(fn, &st) == -1)
		return false; // shouldn't happen

	if ( ( st.st_mode & S_IFDIR ) && ( canthave & SFF_SUBDIR ) )
		return false;

	if ( ( musthave & SFF_SUBDIR ) && !( st.st_mode & S_IFDIR ) )
		return false;

	return true;
}

char	*Sys_FindFirst (char *path, unsigned musthave, unsigned canhave)
{
	struct dirent *d;
	char *p;

	if (fdir)
		Sys_Error ("Sys_BeginFind without close");

//	COM_FilePath (path, findbase);
	strcpy(findbase, path);

	if ((p = strrchr(findbase, '/')) != NULL) {
		*p = 0;
		strcpy(findpattern, p + 1);
	} else
		strcpy(findpattern, "*");

	if (strcmp(findpattern, "*.*") == 0)
		strcpy(findpattern, "*");
	
	if ((fdir = opendir(findbase)) == NULL) {
		return NULL;
	}
	while ((d = readdir(fdir)) != NULL) {
		if (!*findpattern || glob_match(findpattern, d->d_name)) {
//			if (*findpattern)
//				printf("%s matched %s\n", findpattern, d->d_name);
			if (CompareAttributes(findbase, d->d_name, musthave, canhave)) {
				sprintf (findpath, "%s/%s", findbase, d->d_name);
				return findpath;
			}
		}
	}
	return NULL;
}

char	*Sys_FindNext (unsigned musthave, unsigned canhave)
{
	struct dirent *d;

	if (fdir == NULL)
		return NULL;
	while ((d = readdir(fdir)) != NULL) {
		if (!*findpattern || glob_match(findpattern, d->d_name)) {
//			if (*findpattern)
//				printf("%s matched %s\n", findpattern, d->d_name);
			if (CompareAttributes(findbase, d->d_name, musthave, canhave)) {
				sprintf (findpath, "%s/%s", findbase, d->d_name);
				return findpath;
			}
		}
	}
	return NULL;
}

void	Sys_FindClose (void)
{
	if (fdir != NULL)
		closedir(fdir);
	fdir = NULL;
}

//===============================================================================

void	Sys_Init (void)
{
}


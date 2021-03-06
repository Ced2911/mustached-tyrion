#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <debug.h>
#include <xenos/xenos.h>
#include <diskio/ata.h>
#include <input/input.h>
#include <console/console.h>
#include <diskio/disc_io.h>
#include <sys/iosupport.h>
#include <usb/usbmain.h>
#include <time/time.h>
#include <ppc/timebase.h>
#include <ppc/atomic.h>
#include <xenon_soc/xenon_power.h>
#include <elf/elf.h>
#include <dirent.h>

#include <libfat/fat.h>

extern void network_init_sys();
extern void threading_init();
#ifdef CAPS
extern DISC_INTERFACE usb2mass_ops_1;
#endif


#ifdef CAPS
#ifndef mutex_t
typedef int mutex_t;
#endif

void _FAT_lock_init(mutex_t *mutex)
{
	*mutex=0;
}

void _FAT_lock_deinit(mutex_t *mutex)
{
	*mutex=0;
}

void _FAT_lock(mutex_t *mutex)
{
	lock(mutex);
}

void _FAT_unlock(mutex_t *mutex)
{
	unlock(mutex);
}
#endif

void main (int argc, char **argv)
{
	// Init libxenon
	xenos_init(VIDEO_MODE_AUTO);
	console_init();

	xenon_make_it_faster(XENON_SPEED_FULL);

#if 0
	threading_init();
	network_init_sys();
#endif

	usb_init();
	usb_do_poll();

	xenon_ata_init();

	xenon_atapi_init();

	fatInitDefault();
#ifdef CAPS	
	fatMountSimple("udb", &usb2mass_ops_1);
	printf("CAPTURE BUILD !!!\n");
#endif	
	// Quake II
	
	char * newargv[] = {
		"uda:/q3.elf",
		//"+set", "game", "baseq2", "+set", "cddir", "uda:/baseq2/"
		"+set", "basedir" , "uda:/",
		"+set", "cddir", "uda:/baseq2/",
		"+set", "cl_maxfps", "400"
	};
	int newargc = sizeof (newargv) / sizeof (char *);
	
	Qcommon_Init (newargc, newargv);
	
	console_close();

	int	time, oldtime, newtime;
	oldtime = Sys_Milliseconds();
	while (1)
	{
		do {
			newtime = Sys_Milliseconds ();
			time = newtime - oldtime;
		} while (time < 1);
		Qcommon_Frame (time);
		oldtime = newtime;
	}
}

// vid_null.c -- null video driver to aid porting efforts
// this assumes that one of the refs is statically linked to the executable
#include <debug.h>
#include "../client/client.h"
#include <xenos/xe.h>
#include <xenos/edram.h>
#include "video.h"

typedef unsigned int DWORD;
#include "hlsl/ps.h"
#include "hlsl/vs.h"


viddef_t	viddef;				// global video state

refexport_t	re;

refexport_t GetRefAPI (refimport_t rimp);

/*
==========================================================================

DIRECT LINK GLUE

==========================================================================
*/

#define	MAXPRINTMSG	4096
void VID_Printf (int print_level, char *fmt, ...)
{
        va_list		argptr;
        char		msg[MAXPRINTMSG];

        va_start (argptr,fmt);
        vsprintf (msg,fmt,argptr);
        va_end (argptr);

        if (print_level == PRINT_ALL)
                Com_Printf ("%s", msg);
        else
                Com_DPrintf ("%s", msg);
}

void VID_Error (int err_level, char *fmt, ...)
{
        va_list		argptr;
        char		msg[MAXPRINTMSG];

        va_start (argptr,fmt);
        vsprintf (msg,fmt,argptr);
        va_end (argptr);

		Com_Error (err_level, "%s", msg);
}

void VID_NewWindow (int width, int height)
{
        viddef.width = width;
        viddef.height = height;
}

/*
** VID_GetModeInfo
*/
typedef struct vidmode_s
{
    const char *description;
    int         width, height;
    int         mode;
} vidmode_t;

vidmode_t vid_modes[] =
{
    { "Mode 0: 320x240",   320, 240,   0 },
    { "Mode 1: 400x300",   400, 300,   1 },
    { "Mode 2: 512x384",   512, 384,   2 },
    { "Mode 3: 640x480",   640, 480,   3 },
    { "Mode 4: 800x600",   800, 600,   4 },
    { "Mode 5: 960x720",   960, 720,   5 },
    { "Mode 6: 1024x768",  1024, 768,  6 },
    { "Mode 7: 1152x864",  1152, 864,  7 },
    { "Mode 8: 1280x960",  1280, 960, 8 },
    { "Mode 9: 1600x1200", 1600, 1200, 9 }
};
#define VID_NUM_MODES ( sizeof( vid_modes ) / sizeof( vid_modes[0] ) )

qboolean VID_GetModeInfo( int *width, int *height, int mode )
{
    if ( mode < 0 || mode >= VID_NUM_MODES )
        return false;

    *width  = vid_modes[mode].width;
    *height = vid_modes[mode].height;

    return true;
}


void	VID_Init (void)
{
	TR;
    refimport_t	ri;

    viddef.width = 320;
    viddef.height = 240;

    ri.Cmd_AddCommand = Cmd_AddCommand;
    ri.Cmd_RemoveCommand = Cmd_RemoveCommand;
    ri.Cmd_Argc = Cmd_Argc;
    ri.Cmd_Argv = Cmd_Argv;
    ri.Cmd_ExecuteText = Cbuf_ExecuteText;
    ri.Con_Printf = VID_Printf;
    ri.Sys_Error = VID_Error;
    ri.FS_LoadFile = FS_LoadFile;
    ri.FS_FreeFile = FS_FreeFile;
    ri.FS_Gamedir = FS_Gamedir;
    ri.Vid_MenuInit = VID_MenuInit;
	ri.Vid_NewWindow = VID_NewWindow;
    ri.Cvar_Get = Cvar_Get;
    ri.Cvar_Set = Cvar_Set;
    ri.Cvar_SetValue = Cvar_SetValue;
    ri.Vid_GetModeInfo = VID_GetModeInfo;

    re = GetRefAPI(ri);
#ifdef USE_SOFT
	xe=&_xe;
	
	Xe_Init(xe);
	
	edram_init(xe);
	Xe_SetRenderTarget(xe, Xe_GetFramebufferSurface(xe));
	static const struct XenosVBFFormat vbf = {
		3,
		{
			{XE_USAGE_POSITION, 0, XE_TYPE_FLOAT4},
			{XE_USAGE_COLOR, 0, XE_TYPE_UBYTE4},
			{XE_USAGE_TEXCOORD, 0, XE_TYPE_FLOAT2},
		}
	};
	
	pPixelShader = Xe_LoadShaderFromMemory(xe, (void*) g_xps_PS);
	Xe_InstantiateShader(xe, pPixelShader, 0);

	pVertexShader = Xe_LoadShaderFromMemory(xe, (void*) g_xvs_VS);
	Xe_InstantiateShader(xe, pVertexShader, 0);
	Xe_ShaderApplyVFetchPatches(xe, pVertexShader, 0, &vbf);
	
	// Create vb
	pVBSw = Xe_CreateVertexBuffer(xe, 3 * sizeof (DrawVerticeFormats));
	
	DrawVerticeFormats *Rect = Xe_VB_Lock(xe, pVBSw, 0, 3 * sizeof (DrawVerticeFormats), XE_LOCK_WRITE);
	{
		// top left
		Rect[0].x = -1;
		Rect[0].y = 1;
		Rect[0].u = 0;
		Rect[0].v = 0;
		Rect[0].color = 0;

		// bottom left
		Rect[1].x = -1;
		Rect[1].y = -1;
		Rect[1].u = 0;
		Rect[1].v = 1;
		Rect[1].color = 0;

		// top right
		Rect[2].x = 1;
		Rect[2].y = 1;
		Rect[2].u = 1;
		Rect[2].v = 0;
		Rect[2].color = 0;

		int i = 0;
		for (i = 0; i < 3; i++) {
			Rect[i].z = 0.0;
			Rect[i].w = 1.0;
		}
	}
	Xe_VB_Unlock(xe, pVBSw);
	
	pVideoSurface = NULL;
	
#endif	
	if (re.api_version != API_VERSION)
        Com_Error (ERR_FATAL, "Re has incompatible api_version");
    
        // call the init function
    if (re.Init (NULL, NULL) == -1)
		Com_Error (ERR_FATAL, "Couldn't start refresh");
}

void	VID_Shutdown (void)
{
    if (re.Shutdown)
	    re.Shutdown ();
}

void	VID_CheckChanges (void)
{

}

void	VID_MenuInit (void)
{
	TR;
}

void	VID_MenuDraw (void)
{
	TR;
}

const char *VID_MenuKey( int k)
{
	return NULL;
}

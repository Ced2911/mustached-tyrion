#include "../ref_gl/gl_local.h"

#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/gl_xenos.h>
#include <console/console.h>
#include <xenos/xenos.h>
#include <xenon_soc/xenon_power.h>
#include <debug.h>


void GLimp_BeginFrame( float camera_separation )
{
}

void GLimp_EndFrame( void )
{
	XenonGLDisplay();
}

int GLimp_Init( void *hinstance, void *hWnd )
{
	TR;
	XenonGLInit();
	QGL_Init("fake");
	return true;
}

void GLimp_Shutdown( void )
{
	TR
}

int GLimp_SetMode( int *pwidth, int *pheight, int mode, qboolean fullscreen )
{
	int width, height;
	GLint attribs[32];

	ri.Con_Printf( PRINT_ALL, "Initializing OpenGL display\n");

	ri.Con_Printf (PRINT_ALL, "...setting mode %d:", mode );

	if ( !ri.Vid_GetModeInfo( &width, &height, mode ) )
	{
		ri.Con_Printf( PRINT_ALL, " invalid mode\n" );
		return rserr_invalid_mode;
	}

	ri.Con_Printf( PRINT_ALL, " %d %d\n", width, height );

	// destroy the existing window
	GLimp_Shutdown ();

	*pwidth = width;
	*pheight = height;
	
	// let the sound and input subsystems know about the new window
	ri.Vid_NewWindow (width, height);
	return rserr_ok;
}

void GLimp_AppActivate( qboolean active )
{
}


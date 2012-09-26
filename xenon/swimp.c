
#include "../ref_soft/r_local.h"
#include <xenos/xe.h>

extern struct XenosDevice _xe, *xe;
struct XenosSurface * pMainSurface = NULL;

void		SWimp_BeginFrame( float camera_separation )
{
}

void		SWimp_EndFrame (void)
{
}

int			SWimp_Init( void *hInstance, void *wndProc )
{
	/*VID_InitModes();*/
	return true;
}

void		SWimp_SetPalette( const unsigned char *palette)
{
}

void		SWimp_Shutdown( void )
{
}

rserr_t		SWimp_SetMode( int *pwidth, int *pheight, int mode, qboolean fullscreen )
{
	rserr_t retval = rserr_ok;

	ri.Con_Printf (PRINT_ALL, "setting mode %d:", mode );

	if ( !ri.Vid_GetModeInfo( pwidth, pheight, mode ) )
	{
		ri.Con_Printf( PRINT_ALL, " invalid mode\n" );
		return rserr_invalid_mode;
	}

	ri.Con_Printf( PRINT_ALL, " %d %d\n", *pwidth, *pheight);

/*
	if ( !SWimp_InitGraphics( false ) ) {
		// failed to set a valid mode in windowed mode
		return rserr_invalid_mode;
	}
*/
	R_GammaCorrectAndSetPalette( ( const unsigned char * ) d_8to24table );

	return retval;
}

void		SWimp_AppActivate( qboolean active )
{
}


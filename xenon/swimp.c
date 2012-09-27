
#include "../ref_soft/r_local.h"
#include <xenos/xe.h>
#include "video.h"
#include <debug.h>
#include <ppc/timebase.h>
#include <byteswap.h>

static unsigned int * pQ2Palette = NULL;

void SWimp_BeginFrame( float camera_separation )
{       
    
}

static void ShowFPS() {
	static unsigned long lastTick = 0;
	static int frames = 0;
	unsigned long nowTick;
	frames++;
	nowTick = mftb() / (PPC_TIMEBASE_FREQ / 1000);
	if (lastTick + 1000 <= nowTick) {

		printf("SWimp_EndFrame %d fps\r\n", frames);

		frames = 0;
		lastTick = nowTick;
	}
}

void SWimp_EndFrame (void)
{
	// Reset states
    Xe_InvalidateState(xe);
    Xe_SetClearColor(xe, -1);
    
    Xe_SetBlendOp(xe, XE_BLENDOP_ADD);
    Xe_SetSrcBlend(xe, XE_BLEND_SRCALPHA);
    Xe_SetDestBlend(xe, XE_BLEND_INVSRCALPHA);

	// Refresh texture cash
    unsigned int * pBitmap = Xe_Surface_LockRect(xe, pVideoSurface, 0, 0, 0, 0, XE_LOCK_WRITE);
    int i;
    for(i = 0;i<(vid.width*vid.height);i++)
	{
		//Make an ARGB bitmap
		unsigned int c = (pQ2Palette[vid.buffer[i]]) >> 8 | ( 0xFF << 24 );
		pBitmap[i] = c;
	}
    
    Xe_Surface_Unlock(xe, pVideoSurface);

    // Select stream and shaders
    Xe_SetTexture(xe, 0, pVideoSurface);
    Xe_SetCullMode(xe, XE_CULL_NONE);
    Xe_SetStreamSource(xe, 0, pVBSw, 0, 10);
    Xe_SetShader(xe, SHADER_TYPE_PIXEL, pPixelShader, 0);
    Xe_SetShader(xe, SHADER_TYPE_VERTEX, pVertexShader, 0);
   
    // Draw
    Xe_DrawPrimitive(xe, XE_PRIMTYPE_RECTLIST, 0, 1);
    
    // Resolve
    Xe_Resolve(xe);
    Xe_Sync(xe);
 
	ShowFPS();
}

int	SWimp_Init( void *hInstance, void *wndProc )
{
	/*VID_InitModes();*/
	return true;
}

void SWimp_SetPalette( const unsigned char *palette)
{
	if ( !palette )
		palette = ( const unsigned char * ) sw_state.currentpalette;
		
	pQ2Palette = palette;
}

void SWimp_Shutdown( void )
{
}

static qboolean SWimp_InitGraphics(qboolean unused) {
	TR;
	// let the sound and input subsystems know about the new window
	ri.Vid_NewWindow (vid.width, vid.height);
	
	printf("SWimp_InitGraphics %d - %d \n", vid.width, vid.height);
	
	// create a new bitmap	
	pVideoSurface = Xe_CreateTexture(xe, vid.width, vid.height, 1, XE_FMT_8888 | XE_FMT_ARGB, 0);
	
	printf("pVideoSurface->wpitch : %d\n", pVideoSurface->wpitch);
	printf("pVideoSurface->base : %p\n", pVideoSurface->base);

	vid.rowbytes = vid.width;
	vid.buffer = malloc(vid.rowbytes * vid.height);
	
	printf("pVideoSurface %p\n", pVideoSurface);
	return true;
}

rserr_t	SWimp_SetMode( int *pwidth, int *pheight, int mode, qboolean fullscreen )
{
	rserr_t retval = rserr_ok;

	ri.Con_Printf (PRINT_ALL, "setting mode %d:", mode );

	if ( !ri.Vid_GetModeInfo( pwidth, pheight, mode ) )
	{
		ri.Con_Printf( PRINT_ALL, " invalid mode\n" );
		return rserr_invalid_mode;
	}

	ri.Con_Printf( PRINT_ALL, " %d %d\n", *pwidth, *pheight);
	
	if ( !SWimp_InitGraphics( false ) ) {
		// failed to set a valid mode in windowed mode
		return rserr_invalid_mode;
	}

	R_GammaCorrectAndSetPalette( ( const unsigned char * ) d_8to24table );

	return retval;
}

void SWimp_AppActivate( qboolean active )
{
}


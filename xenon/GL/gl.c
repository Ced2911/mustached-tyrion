#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ppc/timebase.h>
#include <xenos/edram.h>
#include "gl_xenos.h"

typedef unsigned int DWORD;
#include "shaders/opengl.ps.color.h"
#include "shaders/opengl.ps.modulate.h"
#include "shaders/opengl.ps.texture.h"
#include "shaders/opengl.vs.h"

void XenonGLInit(){
	// init video
	xe=&_xe;
	
	Xe_Init(xe);
	
	edram_init(xe);
	Xe_SetRenderTarget(xe, Xe_GetFramebufferSurface(xe));
	static const struct XenosVBFFormat vbf = {
		4,
		{
			{XE_USAGE_POSITION, 0, XE_TYPE_FLOAT4},
			{XE_USAGE_TEXCOORD, 0, XE_TYPE_FLOAT2},			
			{XE_USAGE_TEXCOORD, 1, XE_TYPE_FLOAT2},
			{XE_USAGE_COLOR, 0, XE_TYPE_UBYTE4},
		}
	};
	
	pPixelTextureShader = Xe_LoadShaderFromMemory(xe, (void*) g_xps_ps_texture);
	Xe_InstantiateShader(xe, pPixelTextureShader, 0);
	
	pPixelModulateShader = Xe_LoadShaderFromMemory(xe, (void*) g_xps_ps_modulate);
	Xe_InstantiateShader(xe, pPixelModulateShader, 0);
	
	pPixelColorShader = Xe_LoadShaderFromMemory(xe, (void*) g_xps_ps_color);
	Xe_InstantiateShader(xe, pPixelColorShader, 0);
	
	pCurrentPs = g_xps_ps_color;
	pCurrentTexturedPs = g_xps_ps_texture;

	pVertexShader = Xe_LoadShaderFromMemory(xe, (void*) g_xvs_vs_main);
	Xe_InstantiateShader(xe, pVertexShader, 0);
	Xe_ShaderApplyVFetchPatches(xe, pVertexShader, 0, &vbf);
	
	// Create vb
	pVbGL = Xe_CreateVertexBuffer(xe, XE_MAX_VERTICES);
	xe_Vertices = Xe_VB_Lock(xe, pVbGL, 0, XE_MAX_VERTICES, XE_LOCK_WRITE);
	Xe_VB_Unlock(xe, pVbGL);
	
	// init matrices
	XeGlInitializeMatrix(&projection_matrix);
	XeGlInitializeMatrix(&modelview_matrix);
	
	// init vertices
	xe_NumVerts = 0;
	xe_CurrentColor.u32 = 0xFFFFFFFF;
	
	// init textures
	XeGLInitTextures();
	
	// not yet ...
	Xe_InvalidateState(xe);
	Xe_SetClearColor(xe, 0);
	
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

void XenonGLDisplay()
{    
    // update vb cache !!!
    Xe_VB_Lock(xe, pVbGL, 0, XE_MAX_VERTICES, XE_LOCK_WRITE);
	Xe_VB_Unlock(xe, pVbGL);    
    
    // Resolve
    Xe_Resolve(xe);
    //while(!Xe_IsVBlank(xe));
    Xe_Sync(xe);
    
    // Reset states
    Xe_InvalidateState(xe);
    Xe_SetClearColor(xe, 0);
    
    // Reset vertices
    xe_NumVerts = xe_PrevNumVerts = 0;
 
	ShowFPS();
}

void xe_gl_error(const char * format, ...)
{
	printf(format);
	delay(1);
};
void xe_gl_log(const char * format, ...)
{
	printf(format);
};

static const char * GL_Description = "OpenGL Xenon By Ced2911";
static const char * GL_Driver = "OpenGL Xenon";
static char *GL_VersionString = "1.1";
static char *GL_ExtensionString = "";

const GLubyte *glGetString (GLenum name)
{
	switch (name)
	{
	case GL_VENDOR:
		return GL_Description;
	case GL_RENDERER:
		return GL_Driver;
	case GL_VERSION:
		return GL_VersionString;
	case GL_EXTENSIONS:
	default:
		return GL_ExtensionString;
	}
}
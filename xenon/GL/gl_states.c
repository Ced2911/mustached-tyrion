#include "gl_xenos.h"

GLenum gl_cull_mode = GL_BACK;
static GLboolean gl_cull_enable = GL_FALSE;
GLenum gl_front_face = GL_CCW;

// Missing from libxenon
#define XE_NONE_FRONTFACE_CCW  0x0
#define XE_FRONT_FRONTFACE_CCW 0x1
#define XE_BACK_FRONTFACE_CCW  0x2
#define XE_NONE_FRONTFACE_CW   0x4
#define XE_FRONT_FRONTFACE_CW  0x5
#define XE_BACK_FRONTFACE_CW   0x6

void glShadeModel (GLenum mode)
{
	
}

/***********************************************************************
 * Clear
 ***********************************************************************/
static int scissor_x, scissor_y, scissor_w, scissor_h;

static void updateScissor(int enabled)
{
	//Xe_SetScissor(xe, enabled, scissor_x, scissor_y, scissor_x+scissor_w, scissor_y+scissor_h);
}

void glScissor (GLint x, GLint y, GLsizei width, GLsizei height)
{
	scissor_x = x;
	scissor_y = y;
	scissor_w = width;
	scissor_h = height;
	
	//Xe_SetScissor(xe, 1, scissor_x, scissor_y, scissor_x+scissor_w, scissor_y+scissor_h);
}

/***********************************************************************
 * Clear
 ***********************************************************************/
void glClear (GLbitfield mask)
{
	unsigned int flags = 0;

	if (mask & GL_COLOR_BUFFER_BIT) flags |= XE_CLEAR_COLOR;
	if (mask & GL_DEPTH_BUFFER_BIT) flags |= XE_CLEAR_DS;
	if (mask & GL_STENCIL_BUFFER_BIT) flags |= XE_CLEAR_DS;

	Xe_Clear(xe, flags);
}

#define MAKE_COLOR4(r,g,b,a) ((a&0xFF)<<24 | ((b&0xFF)<<16) | ((g&0xFF)<<8) | (r&0xFF))

void glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	unsigned int c = MAKE_COLOR4((int)(red * 255), (int)(green * 255), (int)(blue * 255), (int)(alpha * 255));
	Xe_SetClearColor(xe, c);
}

void glClearDepth(GLclampd depth)
{
	Xe_Clear(xe, XE_CLEAR_DS);
}

/***********************************************************************
 * Cull
 ***********************************************************************/
static void updateCullMode()
{
#if 1
	if (gl_cull_enable == GL_FALSE)
	{
		// disable culling
		Xe_SetCullMode(xe, XE_CULL_NONE);
		return;
	}
	
	if (gl_cull_mode == GL_FRONT_AND_BACK) {
		printf("GL_FRONT_AND_BACK: not implemented \n");
		return;
	}

	if (gl_front_face == GL_CCW)
	{
		if (gl_cull_mode == GL_BACK)
			Xe_SetCullMode(xe, XE_BACK_FRONTFACE_CCW);
		else if (gl_cull_mode == GL_FRONT)
			Xe_SetCullMode(xe, XE_FRONT_FRONTFACE_CCW);
		else xe_gl_error ("GL_UpdateCull: illegal glCullFace\n");
	}
	else if (gl_front_face == GL_CW)
	{
		if (gl_cull_mode == GL_BACK)
			Xe_SetCullMode(xe, XE_BACK_FRONTFACE_CW);
		else if (gl_cull_mode == GL_FRONT)
			Xe_SetCullMode(xe, XE_FRONT_FRONTFACE_CW);
		else xe_gl_error ("GL_UpdateCull: illegal glCullFace\n");
	}
	else 
		xe_gl_error ("GL_UpdateCull: illegal glFrontFace\n");
#else 
	if (gl_cull_enable == GL_FALSE)
	{
		// disable culling
		Xe_SetCullMode(xe, XE_CULL_NONE);
		return;
	}
	if (gl_front_face == GL_CCW) {
		Xe_SetCullMode(xe, XE_CULL_CW);
	} else {
		Xe_SetCullMode(xe, XE_CULL_CCW);
	}
#endif
}
void glFrontFace (GLenum mode)
{
	gl_front_face = mode;
	updateCullMode();
}
void glCullFace (GLenum mode)
{
	gl_cull_mode = mode;
	updateCullMode();
}
/***********************************************************************
 * Depth
 ***********************************************************************/
int Gl_Cmp_2_Xe(GLenum mode)
{
	int cmp = 0;
	switch (mode)
	{
	case GL_NEVER:
		cmp = XE_CMP_NEVER;
		break;

	case GL_LESS:
		cmp = XE_CMP_LESS;
		break;

	case GL_LEQUAL:
		cmp = XE_CMP_LESSEQUAL;
		break;

	case GL_EQUAL:
		cmp = XE_CMP_EQUAL;
		break;

	case GL_GREATER:
		cmp = XE_CMP_GREATER;
		break;

	case GL_NOTEQUAL:
		cmp = XE_CMP_NOTEQUAL;
		break;

	case GL_GEQUAL:
		cmp = XE_CMP_GREATEREQUAL;
		break;

	case GL_ALWAYS:
	default:
		cmp = XE_CMP_ALWAYS;
		break;
	}
	return cmp;
} 
int Gl_ZCmp_2_Xe(GLenum mode)
{
	int cmp = 0;
	switch (mode)
	{
	case GL_NEVER:
		cmp = XE_CMP_NEVER;
		break;

	case GL_LESS:
		cmp = XE_CMP_GREATER;
		break;

	case GL_LEQUAL:
		cmp = XE_CMP_GREATEREQUAL;
		break;

	case GL_EQUAL:
		cmp = XE_CMP_EQUAL;
		break;

	case GL_GREATER:
		cmp = XE_CMP_LESS;
		break;

	case GL_NOTEQUAL:
		cmp = XE_CMP_NOTEQUAL;
		break;

	case GL_GEQUAL:
		cmp = XE_CMP_LESSEQUAL;
		break;

	case GL_ALWAYS:
	default:
		cmp = XE_CMP_ALWAYS;
		break;
	}
	return cmp;
} 

void glDepthFunc (GLenum func)
{
	Xe_SetZFunc(xe, Gl_Cmp_2_Xe(func));
	//Xe_SetZFunc(xe, Gl_Cmp_2_Xe(func));
}

void glDepthMask (GLboolean flag)
{
	Xe_SetZWrite(xe, flag == GL_TRUE ? 1 : 0);
}

void glAlphaFunc (GLenum func, GLclampf ref)
{
	int cmp = Gl_Cmp_2_Xe(func);
	if (cmp == XE_CMP_GREATEREQUAL) {
		ref -= 1.f/255.f;
		cmp = XE_CMP_GREATER;
	}
	Xe_SetAlphaFunc(xe, cmp);
	Xe_SetAlphaRef(xe, ref);
}

/***********************************************************************
 * Blend
 ***********************************************************************/
int Gl_Blend_2_Xe(GLenum factor)
{
	int blend = XE_BLEND_ONE;

	switch (factor)
	{
	case GL_ZERO:
		blend = XE_BLEND_ZERO;
		break;

	case GL_ONE:
		blend = XE_BLEND_ONE;
		break;

	case GL_SRC_COLOR:
		blend = XE_BLEND_SRCCOLOR;
		break;

	case GL_ONE_MINUS_SRC_COLOR:
		blend = XE_BLEND_INVSRCCOLOR;
		break;

	case GL_DST_COLOR:
		blend = XE_BLEND_DESTCOLOR;
		break;

	case GL_ONE_MINUS_DST_COLOR:
		blend = XE_BLEND_INVDESTCOLOR;
		break;

	case GL_SRC_ALPHA:
		blend = XE_BLEND_SRCALPHA;
		break;

	case GL_ONE_MINUS_SRC_ALPHA:
		blend = XE_BLEND_INVSRCALPHA;
		break;

	case GL_DST_ALPHA:
		blend = XE_BLEND_DESTALPHA;
		break;

	case GL_ONE_MINUS_DST_ALPHA:
		blend = XE_BLEND_INVDESTALPHA;
		break;

	case GL_SRC_ALPHA_SATURATE:
		blend = XE_BLEND_SRCALPHASAT;
		break;

	default:
		xe_gl_error("glBlendFunc: unknown factor");
	}
	return blend;
}

static int old_src_blend = XE_BLEND_ONE;
static int old_dst_blend = XE_BLEND_ZERO;
static int old_blend_op = XE_BLENDOP_ADD;
static int blend_enabled = 0;

static void updateBlend()
{
	#if 1
	if (blend_enabled) {
		Xe_SetBlendControl(xe, old_src_blend, old_blend_op, old_dst_blend, old_src_blend, old_blend_op, old_dst_blend);
	} else {
		Xe_SetBlendControl(xe, XE_BLEND_ONE, XE_BLENDOP_ADD, XE_BLEND_ZERO, XE_BLEND_ONE, XE_BLENDOP_ADD, XE_BLEND_ZERO);
	}
	
	//printf("blend_enabled : %d, src : %d, dst : %d\n",blend_enabled,old_src_blend,old_dst_blend);
	#else
	// Xe_SetBlendControl(xe, old_src_blend, old_blend_op, old_dst_blend, old_src_blend, old_blend_op, old_dst_blend);
		
	Xe_SetBlendControl(xe, XE_BLEND_SRCALPHA, XE_BLENDOP_ADD, XE_BLEND_INVSRCALPHA, XE_BLEND_SRCALPHA, XE_BLENDOP_ADD, XE_BLEND_INVSRCALPHA); 
	#endif
}

void glBlendFunc(GLenum sfactor, GLenum dfactor)
{
	//printf("glBlendFunc src : %x, dst : %x\n",sfactor,dfactor);
	old_src_blend = Gl_Blend_2_Xe(sfactor);
	old_dst_blend = Gl_Blend_2_Xe(dfactor);
	updateBlend();
}
/***********************************************************************
 * Blend
 ***********************************************************************/
void GlEnableDisable(GLenum cap, int enable)
{
	switch (cap)
	{
	case GL_SCISSOR_TEST:
		updateScissor(enable);
		break;
		
	case GL_BLEND:
		blend_enabled = enable;
		updateBlend();
		break;
		
	case GL_ALPHA_TEST:
		Xe_SetAlphaTestEnable(xe, enable);
		break;

	case GL_TEXTURE_2D:
		xeTmus[xeCurrentTMU].enabled = enable;
		return;

	case GL_CULL_FACE:
		if (!enable)
			gl_cull_enable = GL_FALSE;
		else
			gl_cull_enable = GL_TRUE;
		updateCullMode();
		return;
		
	case GL_DEPTH_TEST:
		Xe_SetZEnable(xe, enable);
		return;
		
	case GL_FOG:
	case GL_POLYGON_OFFSET_FILL:
	case GL_POLYGON_OFFSET_LINE:
	default:
		return;
	}
}

void glEnable(GLenum cap)
{
	GlEnableDisable(cap, 1);
}

void glDisable(GLenum cap)
{
	GlEnableDisable(cap, 0);
}


/***********************************************************************
 * Misc
 ***********************************************************************/
static int fill_back = 0;
static int fill_front = 0;
void glPolygonMode (GLenum face, GLenum mode)
{
	int xmode = 0;
	
	if (mode == GL_LINE)
		xmode = XE_FILL_WIREFRAME;
	else if (mode == GL_POINT)
		xmode = XE_FILL_POINT;
	else 
		xmode = XE_FILL_SOLID;
	
	if (face == GL_FRONT)
		fill_front = xmode;
	else if (face == GL_BACK)
		fill_back = xmode;
	else
		fill_back = fill_front = xmode;
	
	Xe_SetFillMode(xe, fill_front, fill_back);
}


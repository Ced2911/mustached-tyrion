#include "gl_xenos.h"
#include <debug.h>

/*
#define XE_PRIMTYPE_POINTLIST 1
#define XE_PRIMTYPE_LINELIST 2
#define XE_PRIMTYPE_LINESTRIP 3
#define XE_PRIMTYPE_TRIANGLELIST 4
#define XE_PRIMTYPE_TRIANGLEFAN 5
#define XE_PRIMTYPE_TRIANGLESTRIP 6
#define XE_PRIMTYPE_RECTLIST 8
#define XE_PRIMTYPE_QUADLIST 13
*/

int Gl_Prim_2_Xe_Prim(GLenum mode)
{
	// default to this
	int ret = XE_PRIMTYPE_TRIANGLELIST;
	switch (xe_PrimitiveMode) {
		case GL_TRIANGLE_FAN:
		case GL_POLYGON:
			ret = XE_PRIMTYPE_TRIANGLEFAN;
			break;
		case GL_TRIANGLES:
			ret = XE_PRIMTYPE_TRIANGLELIST;
			break;
		case GL_TRIANGLE_STRIP:
			ret = XE_PRIMTYPE_TRIANGLESTRIP;
			break;
		case GL_POINTS:
			ret = XE_PRIMTYPE_POINTLIST;
			break;
		case GL_LINES:
			ret = XE_PRIMTYPE_LINELIST;
			break;
		case GL_QUAD_STRIP:
		case GL_QUADS:
			ret = XE_PRIMTYPE_QUADLIST;
			break;
		default:
			xe_gl_error("Unknow prim : %x\n", mode);
			break;
	}
	
	return ret;
}

int Gl_Prim_2_Size(GLenum mode, int size) {
	// default to this
	int ret = size;
	switch (xe_PrimitiveMode) {
		case GL_TRIANGLES:
			ret = size / 3;
			break;
		case GL_POLYGON:
		case GL_TRIANGLE_FAN:
		case GL_TRIANGLE_STRIP:
			// 2 = first triangle
			ret = size - 2;
			break;
		// don't know ...
		case GL_POINTS:
		case GL_LINES:
			ret = size;
			break;
		case GL_QUAD_STRIP:
		case GL_QUADS:
			ret = size/4;
			break;
	}
	
	return ret;
}
extern GLenum gl_cull_mode;
void GL_SubmitVertexes()
{	
	
	//if (gl_cull_mode != GL_FRONT_AND_BACK)
	//	return;
	// update if dirty
	XeGlCheckDirtyMatrix(&projection_matrix);
	XeGlCheckDirtyMatrix(&modelview_matrix);
	
    Xe_SetStreamSource(xe, 0, pVbGL, xe_PrevNumVerts * sizeof(glVerticesFormat_t), 10);
    Xe_SetShader(xe, SHADER_TYPE_VERTEX, pVertexShader, 0);
    
    // set texture
    if (xeTmus[xeCurrentTMU].enabled && xeTmus[xeCurrentTMU].boundtexture) {
		if (xeTmus[xeCurrentTMU].texture_env_mode == GL_REPLACE) {
			// tex
			Xe_SetShader(xe, SHADER_TYPE_PIXEL, pPixelTextureShader, 0);
		} else {
			// Color * tex
			Xe_SetShader(xe, SHADER_TYPE_PIXEL, pPixelModulateShader, 0);
		}
		Xe_SetTexture(xe, 0, xeTmus[xeCurrentTMU].boundtexture->teximg);
	}
	else {
		Xe_SetShader(xe, SHADER_TYPE_PIXEL, pPixelColorShader, 0);	
		Xe_SetTexture(xe, 0, NULL);
	}
	// draw
	// if (!(xe_PrimitiveMode == GL_QUADS || xe_PrimitiveMode == GL_QUAD_STRIP))
	Xe_DrawPrimitive(xe, Gl_Prim_2_Xe_Prim(xe_PrimitiveMode), 0, Gl_Prim_2_Size(xe_PrimitiveMode, (xe_NumVerts - xe_PrevNumVerts)));
}

void glBegin(GLenum mode)
{
	xe_PrimitiveMode = mode;

	xe_PrevNumVerts = xe_NumVerts;
}

void glEnd()
{
	// submit vertices
	GL_SubmitVertexes();
};


void glVertex3f (GLfloat x, GLfloat y, GLfloat z)
{
	// add a new vertex to the list with the specified xyz and inheriting the current normal, color and texcoords
	// (per spec at http://www.opengl.org/sdk/docs/man/xhtml/glVertex.xml)
#if 0	
	xe_Vertices[xe_NumVerts].x = x;
	xe_Vertices[xe_NumVerts].y = y;
	xe_Vertices[xe_NumVerts].z = z;
	xe_Vertices[xe_NumVerts].w = 1;

	xe_Vertices[xe_NumVerts].color = xe_CurrentColor.u32;

	xe_Vertices[xe_NumVerts].u0 = xe_TextCoord[0].u;
	xe_Vertices[xe_NumVerts].v0 = xe_TextCoord[0].v;
	xe_Vertices[xe_NumVerts].u1 = xe_TextCoord[1].u;
	xe_Vertices[xe_NumVerts].v1 = xe_TextCoord[1].v;	
#else 
	union {
		float f;
		unsigned int u32;
	} c;
	
	c.u32 = xe_CurrentColor.u32;
	//c.u32 = 0xFFFFFFFF;
	
	*xe_Vertices++ = x;
	*xe_Vertices++ = y;
	*xe_Vertices++ = z;
	*xe_Vertices++ = 1;

	*xe_Vertices++ = xe_TextCoord[0].u;
	*xe_Vertices++ = xe_TextCoord[0].v;
	*xe_Vertices++ = xe_TextCoord[1].u;
	*xe_Vertices++ = xe_TextCoord[1].v;

	*xe_Vertices++ = c.f;
#endif	
	// next vertex
	xe_NumVerts++;
}

void glVertex2fv (const GLfloat *v)
{
	glVertex3f (v[0], v[1], 0);
}


void glVertex2f (GLfloat x, GLfloat y)
{
	glVertex3f (x, y, 0);
}


void glVertex3fv (const GLfloat *v)
{
	glVertex3f (v[0], v[1], v[2]);
}

void glTexCoord2f (GLfloat s, GLfloat t)
{
	xe_TextCoord[0].u = s;
	xe_TextCoord[0].v = t;
}


void glTexCoord2fv (const GLfloat *v)
{
	xe_TextCoord[0].u = v[0];
	xe_TextCoord[0].v = v[1];
}

void glEnableClientState(GLenum array)
{
	TR
}

void glPointSize(GLfloat size)
{
	TR
}

void glDrawBuffer (GLenum mode)
{
	
}

void glFinish (void)
{
	
}
void glArrayElement(GLint i)
{
	TR
}

void glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *	pointer)
{
	TR
}

GLenum glGetError(){
	return GL_NO_ERROR;
}

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

extern GLenum gl_cull_mode;
static int use_indice_buffer = 0;

static int Gl_Prim_2_Xe_Prim(GLenum mode)
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

static int Gl_Prim_2_Size(GLenum mode, int size) {
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
static void GL_SubmitVertexes()
{	
	// never draw this one
	if (gl_cull_mode == GL_FRONT_AND_BACK)
		return;

	// update if dirty
	XeGlCheckDirtyMatrix(&projection_matrix);
	XeGlCheckDirtyMatrix(&modelview_matrix);
	
    // Xe_SetStreamSource(xe, 0, pVbGL, xe_PrevNumVerts * sizeof(glVerticesFormat_t), 10);
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
		Xe_SetShader(xe, SHADER_TYPE_PIXEL, pPixelModulateShader, 0);
		Xe_SetTexture(xe, 0, xeTmus[xeCurrentTMU].boundtexture->teximg);
	}
	else {
		Xe_SetShader(xe, SHADER_TYPE_PIXEL, pPixelColorShader, 0);	
		Xe_SetTexture(xe, 0, NULL);
	}
	// draw
	Xe_DrawPrimitive(xe, Gl_Prim_2_Xe_Prim(xe_PrimitiveMode), xe_PrevNumVerts, Gl_Prim_2_Size(xe_PrimitiveMode, (xe_NumVerts - xe_PrevNumVerts)));
}

void glBegin(GLenum mode)
{
	xe_PrimitiveMode = mode;
	
	xe_PrevNumVerts = xe_NumVerts;
	xe_PrevNumIndices = xe_NumIndices;
}

void glEnd()
{
	// submit vertices
	GL_SubmitVertexes();
	use_indice_buffer = 0;
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
	
	*xe_Vertices++ = x;
	*xe_Vertices++ = y;
	*xe_Vertices++ = z;
	*xe_Vertices++ = 1;

	/* 
*xe_Vertices++ = xe_TextCoord[0].u;
*xe_Vertices++ = xe_TextCoord[0].v;
*xe_Vertices++ = xe_TextCoord[1].u;
*xe_Vertices++ = xe_TextCoord[1].v;
	*/

	int i = 0;
	for(i = 0; i < XE_MAX_TMUS; i++) {
		*xe_Vertices++ = xe_TextCoord[i].u;
		*xe_Vertices++ = xe_TextCoord[i].v;
	}
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


void glFinish (void)
{
	
}

GLenum glGetError(){
	return GL_NO_ERROR;
}

void glPointSize(GLfloat size)
{
	
}
void glPointParameterf(	GLenum pname, GLfloat param)
{
	
}

void glPointParameterfv(GLenum pname,const GLfloat *  params)
{
	
}

/***********************************************************************
 * 
 * Batch Rendering
 * 
 **********************************************************************/ 
 
typedef struct gl_varray_pointer_s
{
	GLint size;
	GLenum type;
	GLsizei stride;
	GLvoid *pointer;
} gl_varray_pointer_t;

static gl_varray_pointer_t vertexPointer;
static gl_varray_pointer_t colorPointer;
static gl_varray_pointer_t texCoordPointer[XE_MAX_TMUS];
static int vArray_TMU = 0;

void glDrawBuffer (GLenum mode)
{
	TR
}
 
void glArrayElement(GLint i)
{
	// TR
}

void glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *	pointer)
{
	if (type != GL_FLOAT) 
		xe_gl_error("Unimplemented color pointer type");

	colorPointer.size = size;
	colorPointer.type = type;
	colorPointer.stride = stride;
	colorPointer.pointer = (GLvoid *) pointer;
}

void glTexCoordPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	if (type != GL_FLOAT) 
		xe_gl_error("Unimplemented texcoord pointer type\n");

	texCoordPointer[vArray_TMU].size = size;
	texCoordPointer[vArray_TMU].type = type;
	texCoordPointer[vArray_TMU].stride = stride;
	texCoordPointer[vArray_TMU].pointer = (GLvoid *) pointer;
}

void glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	if (type != GL_FLOAT) 
		xe_gl_error("Unimplemented vertex pointer type");

	vertexPointer.size = size;
	vertexPointer.type = type;
	vertexPointer.stride = stride;
	vertexPointer.pointer = (GLvoid *) pointer;
}

void glDrawArrays (GLenum mode, GLint first, GLsizei count)
{
	int i;
	int v;
	int tmu;
	unsigned char *vp;
	unsigned char *stp[XE_MAX_TMUS];

	// required by the spec
	if (!vertexPointer.pointer) return;

	vp = ((unsigned char *) vertexPointer.pointer + first);

	for (tmu = 0; tmu < XE_MAX_TMUS; tmu++)
	{
		if (texCoordPointer[tmu].pointer)
			stp[tmu] = ((unsigned char *) texCoordPointer[tmu].pointer + first);
		else stp[tmu] = NULL;
	}

	// send through standard begin/end processing
	glBegin (mode);

	for (i = 0, v = first; i < count; i++, v++)
	{
		for (tmu = 0; tmu < XE_MAX_TMUS; tmu++)
		{
			if (stp[tmu])
			{
				xe_TextCoord[tmu].u = ((float *) stp[tmu])[0];
				xe_TextCoord[tmu].v = ((float *) stp[tmu])[1];

				stp[tmu] += texCoordPointer[tmu].stride;
			}
		}

		if (vertexPointer.size == 2)
			glVertex2fv ((float *) vp);
		else if (vertexPointer.size == 3)
			glVertex3fv ((float *) vp);

		vp += vertexPointer.stride;
	}

	glEnd ();
}

void glEnableClientState(GLenum array)
{
	
}

void glDisableClientState (GLenum array)
{
	// switch the pointer to NULL
	switch (array)
	{
	case GL_VERTEX_ARRAY:
		vertexPointer.pointer = NULL;
		break;

	case GL_COLOR_ARRAY:
		colorPointer.pointer = NULL;
		break;

	case GL_TEXTURE_COORD_ARRAY:
		texCoordPointer[vArray_TMU].pointer = NULL;
		break;

	default:
		xe_gl_error("Invalid Vertex Array Spec...!\n");
	}
}

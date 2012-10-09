/*
** QGL_WIN.C
**
** This file implements the operating system binding of GL to QGL function
** pointers.  When doing a port of Quake2 you must implement the following
** two functions:
**
** QGL_Init() - loads libraries, assigns function pointers, etc.
** QGL_Shutdown() - unloads libraries, NULLs function pointers
*/

#define QGL
#include "../ref_gl/gl_local.h"

void ( APIENTRY * qglAccum )(GLenum op, GLfloat value);
void ( APIENTRY * qglAlphaFunc )(GLenum func, GLclampf ref);
GLboolean ( APIENTRY * qglAreTexturesResident )(GLsizei n, const GLuint *textures, GLboolean *residences);
void ( APIENTRY * qglArrayElement )(GLint i);
void ( APIENTRY * qglBegin )(GLenum mode);
void ( APIENTRY * qglBindTexture )(GLenum target, GLuint texture);
void ( APIENTRY * qglBitmap )(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap);
void ( APIENTRY * qglBlendFunc )(GLenum sfactor, GLenum dfactor);
void ( APIENTRY * qglCallList )(GLuint list);
void ( APIENTRY * qglCallLists )(GLsizei n, GLenum type, const GLvoid *lists);
void ( APIENTRY * qglClear )(GLbitfield mask);
void ( APIENTRY * qglClearAccum )(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void ( APIENTRY * qglClearColor )(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
void ( APIENTRY * qglClearDepth )(GLclampd depth);
void ( APIENTRY * qglClearIndex )(GLfloat c);
void ( APIENTRY * qglClearStencil )(GLint s);
void ( APIENTRY * qglClipPlane )(GLenum plane, const GLdouble *equation);
void ( APIENTRY * qglColor3b )(GLbyte red, GLbyte green, GLbyte blue);
void ( APIENTRY * qglColor3bv )(const GLbyte *v);
void ( APIENTRY * qglColor3d )(GLdouble red, GLdouble green, GLdouble blue);
void ( APIENTRY * qglColor3dv )(const GLdouble *v);
void ( APIENTRY * qglColor3f )(GLfloat red, GLfloat green, GLfloat blue);
void ( APIENTRY * qglColor3fv )(const GLfloat *v);
void ( APIENTRY * qglColor3i )(GLint red, GLint green, GLint blue);
void ( APIENTRY * qglColor3iv )(const GLint *v);
void ( APIENTRY * qglColor3s )(GLshort red, GLshort green, GLshort blue);
void ( APIENTRY * qglColor3sv )(const GLshort *v);
void ( APIENTRY * qglColor3ub )(GLubyte red, GLubyte green, GLubyte blue);
void ( APIENTRY * qglColor3ubv )(const GLubyte *v);
void ( APIENTRY * qglColor3ui )(GLuint red, GLuint green, GLuint blue);
void ( APIENTRY * qglColor3uiv )(const GLuint *v);
void ( APIENTRY * qglColor3us )(GLushort red, GLushort green, GLushort blue);
void ( APIENTRY * qglColor3usv )(const GLushort *v);
void ( APIENTRY * qglColor4b )(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
void ( APIENTRY * qglColor4bv )(const GLbyte *v);
void ( APIENTRY * qglColor4d )(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
void ( APIENTRY * qglColor4dv )(const GLdouble *v);
void ( APIENTRY * qglColor4f )(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void ( APIENTRY * qglColor4fv )(const GLfloat *v);
void ( APIENTRY * qglColor4i )(GLint red, GLint green, GLint blue, GLint alpha);
void ( APIENTRY * qglColor4iv )(const GLint *v);
void ( APIENTRY * qglColor4s )(GLshort red, GLshort green, GLshort blue, GLshort alpha);
void ( APIENTRY * qglColor4sv )(const GLshort *v);
void ( APIENTRY * qglColor4ub )(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
void ( APIENTRY * qglColor4ubv )(const GLubyte *v);
void ( APIENTRY * qglColor4ui )(GLuint red, GLuint green, GLuint blue, GLuint alpha);
void ( APIENTRY * qglColor4uiv )(const GLuint *v);
void ( APIENTRY * qglColor4us )(GLushort red, GLushort green, GLushort blue, GLushort alpha);
void ( APIENTRY * qglColor4usv )(const GLushort *v);
void ( APIENTRY * qglColorMask )(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
void ( APIENTRY * qglColorMaterial )(GLenum face, GLenum mode);
void ( APIENTRY * qglColorPointer )(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
void ( APIENTRY * qglCopyPixels )(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
void ( APIENTRY * qglCopyTexImage1D )(GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLint border);
void ( APIENTRY * qglCopyTexImage2D )(GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
void ( APIENTRY * qglCopyTexSubImage1D )(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
void ( APIENTRY * qglCopyTexSubImage2D )(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
void ( APIENTRY * qglCullFace )(GLenum mode);
void ( APIENTRY * qglDeleteLists )(GLuint list, GLsizei range);
void ( APIENTRY * qglDeleteTextures )(GLsizei n, const GLuint *textures);
void ( APIENTRY * qglDepthFunc )(GLenum func);
void ( APIENTRY * qglDepthMask )(GLboolean flag);
void ( APIENTRY * qglDepthRange )(GLclampd zNear, GLclampd zFar);
void ( APIENTRY * qglDisable )(GLenum cap);
void ( APIENTRY * qglDisableClientState )(GLenum array);
void ( APIENTRY * qglDrawArrays )(GLenum mode, GLint first, GLsizei count);
void ( APIENTRY * qglDrawBuffer )(GLenum mode);
void ( APIENTRY * qglDrawElements )(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
void ( APIENTRY * qglDrawPixels )(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
void ( APIENTRY * qglEdgeFlag )(GLboolean flag);
void ( APIENTRY * qglEdgeFlagPointer )(GLsizei stride, const GLvoid *pointer);
void ( APIENTRY * qglEdgeFlagv )(const GLboolean *flag);
void ( APIENTRY * qglEnable )(GLenum cap);
void ( APIENTRY * qglEnableClientState )(GLenum array);
void ( APIENTRY * qglEnd )(void);
void ( APIENTRY * qglEndList )(void);
void ( APIENTRY * qglEvalCoord1d )(GLdouble u);
void ( APIENTRY * qglEvalCoord1dv )(const GLdouble *u);
void ( APIENTRY * qglEvalCoord1f )(GLfloat u);
void ( APIENTRY * qglEvalCoord1fv )(const GLfloat *u);
void ( APIENTRY * qglEvalCoord2d )(GLdouble u, GLdouble v);
void ( APIENTRY * qglEvalCoord2dv )(const GLdouble *u);
void ( APIENTRY * qglEvalCoord2f )(GLfloat u, GLfloat v);
void ( APIENTRY * qglEvalCoord2fv )(const GLfloat *u);
void ( APIENTRY * qglEvalMesh1 )(GLenum mode, GLint i1, GLint i2);
void ( APIENTRY * qglEvalMesh2 )(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
void ( APIENTRY * qglEvalPoint1 )(GLint i);
void ( APIENTRY * qglEvalPoint2 )(GLint i, GLint j);
void ( APIENTRY * qglFeedbackBuffer )(GLsizei size, GLenum type, GLfloat *buffer);
void ( APIENTRY * qglFinish )(void);
void ( APIENTRY * qglFlush )(void);
void ( APIENTRY * qglFogf )(GLenum pname, GLfloat param);
void ( APIENTRY * qglFogfv )(GLenum pname, const GLfloat *params);
void ( APIENTRY * qglFogi )(GLenum pname, GLint param);
void ( APIENTRY * qglFogiv )(GLenum pname, const GLint *params);
void ( APIENTRY * qglFrontFace )(GLenum mode);
void ( APIENTRY * qglFrustum )(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
GLuint ( APIENTRY * qglGenLists )(GLsizei range);
void ( APIENTRY * qglGenTextures )(GLsizei n, GLuint *textures);
void ( APIENTRY * qglGetBooleanv )(GLenum pname, GLboolean *params);
void ( APIENTRY * qglGetClipPlane )(GLenum plane, GLdouble *equation);
void ( APIENTRY * qglGetDoublev )(GLenum pname, GLdouble *params);
GLenum ( APIENTRY * qglGetError )(void);
void ( APIENTRY * qglGetFloatv )(GLenum pname, GLfloat *params);
void ( APIENTRY * qglGetIntegerv )(GLenum pname, GLint *params);
void ( APIENTRY * qglGetLightfv )(GLenum light, GLenum pname, GLfloat *params);
void ( APIENTRY * qglGetLightiv )(GLenum light, GLenum pname, GLint *params);
void ( APIENTRY * qglGetMapdv )(GLenum target, GLenum query, GLdouble *v);
void ( APIENTRY * qglGetMapfv )(GLenum target, GLenum query, GLfloat *v);
void ( APIENTRY * qglGetMapiv )(GLenum target, GLenum query, GLint *v);
void ( APIENTRY * qglGetMaterialfv )(GLenum face, GLenum pname, GLfloat *params);
void ( APIENTRY * qglGetMaterialiv )(GLenum face, GLenum pname, GLint *params);
void ( APIENTRY * qglGetPixelMapfv )(GLenum map, GLfloat *values);
void ( APIENTRY * qglGetPixelMapuiv )(GLenum map, GLuint *values);
void ( APIENTRY * qglGetPixelMapusv )(GLenum map, GLushort *values);
void ( APIENTRY * qglGetPointerv )(GLenum pname, GLvoid* *params);
void ( APIENTRY * qglGetPolygonStipple )(GLubyte *mask);
const GLubyte * ( APIENTRY * qglGetString )(GLenum name);
void ( APIENTRY * qglGetTexEnvfv )(GLenum target, GLenum pname, GLfloat *params);
void ( APIENTRY * qglGetTexEnviv )(GLenum target, GLenum pname, GLint *params);
void ( APIENTRY * qglGetTexGendv )(GLenum coord, GLenum pname, GLdouble *params);
void ( APIENTRY * qglGetTexGenfv )(GLenum coord, GLenum pname, GLfloat *params);
void ( APIENTRY * qglGetTexGeniv )(GLenum coord, GLenum pname, GLint *params);
void ( APIENTRY * qglGetTexImage )(GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);
void ( APIENTRY * qglGetTexLevelParameterfv )(GLenum target, GLint level, GLenum pname, GLfloat *params);
void ( APIENTRY * qglGetTexLevelParameteriv )(GLenum target, GLint level, GLenum pname, GLint *params);
void ( APIENTRY * qglGetTexParameterfv )(GLenum target, GLenum pname, GLfloat *params);
void ( APIENTRY * qglGetTexParameteriv )(GLenum target, GLenum pname, GLint *params);
void ( APIENTRY * qglHint )(GLenum target, GLenum mode);
void ( APIENTRY * qglIndexMask )(GLuint mask);
void ( APIENTRY * qglIndexPointer )(GLenum type, GLsizei stride, const GLvoid *pointer);
void ( APIENTRY * qglIndexd )(GLdouble c);
void ( APIENTRY * qglIndexdv )(const GLdouble *c);
void ( APIENTRY * qglIndexf )(GLfloat c);
void ( APIENTRY * qglIndexfv )(const GLfloat *c);
void ( APIENTRY * qglIndexi )(GLint c);
void ( APIENTRY * qglIndexiv )(const GLint *c);
void ( APIENTRY * qglIndexs )(GLshort c);
void ( APIENTRY * qglIndexsv )(const GLshort *c);
void ( APIENTRY * qglIndexub )(GLubyte c);
void ( APIENTRY * qglIndexubv )(const GLubyte *c);
void ( APIENTRY * qglInitNames )(void);
void ( APIENTRY * qglInterleavedArrays )(GLenum format, GLsizei stride, const GLvoid *pointer);
GLboolean ( APIENTRY * qglIsEnabled )(GLenum cap);
GLboolean ( APIENTRY * qglIsList )(GLuint list);
GLboolean ( APIENTRY * qglIsTexture )(GLuint texture);
void ( APIENTRY * qglLightModelf )(GLenum pname, GLfloat param);
void ( APIENTRY * qglLightModelfv )(GLenum pname, const GLfloat *params);
void ( APIENTRY * qglLightModeli )(GLenum pname, GLint param);
void ( APIENTRY * qglLightModeliv )(GLenum pname, const GLint *params);
void ( APIENTRY * qglLightf )(GLenum light, GLenum pname, GLfloat param);
void ( APIENTRY * qglLightfv )(GLenum light, GLenum pname, const GLfloat *params);
void ( APIENTRY * qglLighti )(GLenum light, GLenum pname, GLint param);
void ( APIENTRY * qglLightiv )(GLenum light, GLenum pname, const GLint *params);
void ( APIENTRY * qglLineStipple )(GLint factor, GLushort pattern);
void ( APIENTRY * qglLineWidth )(GLfloat width);
void ( APIENTRY * qglListBase )(GLuint base);
void ( APIENTRY * qglLoadIdentity )(void);
void ( APIENTRY * qglLoadMatrixd )(const GLdouble *m);
void ( APIENTRY * qglLoadMatrixf )(const GLfloat *m);
void ( APIENTRY * qglLoadName )(GLuint name);
void ( APIENTRY * qglLogicOp )(GLenum opcode);
void ( APIENTRY * qglMap1d )(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points);
void ( APIENTRY * qglMap1f )(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
void ( APIENTRY * qglMap2d )(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points);
void ( APIENTRY * qglMap2f )(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points);
void ( APIENTRY * qglMapGrid1d )(GLint un, GLdouble u1, GLdouble u2);
void ( APIENTRY * qglMapGrid1f )(GLint un, GLfloat u1, GLfloat u2);
void ( APIENTRY * qglMapGrid2d )(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
void ( APIENTRY * qglMapGrid2f )(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
void ( APIENTRY * qglMaterialf )(GLenum face, GLenum pname, GLfloat param);
void ( APIENTRY * qglMaterialfv )(GLenum face, GLenum pname, const GLfloat *params);
void ( APIENTRY * qglMateriali )(GLenum face, GLenum pname, GLint param);
void ( APIENTRY * qglMaterialiv )(GLenum face, GLenum pname, const GLint *params);
void ( APIENTRY * qglMatrixMode )(GLenum mode);
void ( APIENTRY * qglMultMatrixd )(const GLdouble *m);
void ( APIENTRY * qglMultMatrixf )(const GLfloat *m);
void ( APIENTRY * qglNewList )(GLuint list, GLenum mode);
void ( APIENTRY * qglNormal3b )(GLbyte nx, GLbyte ny, GLbyte nz);
void ( APIENTRY * qglNormal3bv )(const GLbyte *v);
void ( APIENTRY * qglNormal3d )(GLdouble nx, GLdouble ny, GLdouble nz);
void ( APIENTRY * qglNormal3dv )(const GLdouble *v);
void ( APIENTRY * qglNormal3f )(GLfloat nx, GLfloat ny, GLfloat nz);
void ( APIENTRY * qglNormal3fv )(const GLfloat *v);
void ( APIENTRY * qglNormal3i )(GLint nx, GLint ny, GLint nz);
void ( APIENTRY * qglNormal3iv )(const GLint *v);
void ( APIENTRY * qglNormal3s )(GLshort nx, GLshort ny, GLshort nz);
void ( APIENTRY * qglNormal3sv )(const GLshort *v);
void ( APIENTRY * qglNormalPointer )(GLenum type, GLsizei stride, const GLvoid *pointer);
void ( APIENTRY * qglOrtho )(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
void ( APIENTRY * qglPassThrough )(GLfloat token);
void ( APIENTRY * qglPixelMapfv )(GLenum map, GLsizei mapsize, const GLfloat *values);
void ( APIENTRY * qglPixelMapuiv )(GLenum map, GLsizei mapsize, const GLuint *values);
void ( APIENTRY * qglPixelMapusv )(GLenum map, GLsizei mapsize, const GLushort *values);
void ( APIENTRY * qglPixelStoref )(GLenum pname, GLfloat param);
void ( APIENTRY * qglPixelStorei )(GLenum pname, GLint param);
void ( APIENTRY * qglPixelTransferf )(GLenum pname, GLfloat param);
void ( APIENTRY * qglPixelTransferi )(GLenum pname, GLint param);
void ( APIENTRY * qglPixelZoom )(GLfloat xfactor, GLfloat yfactor);
void ( APIENTRY * qglPointSize )(GLfloat size);
void ( APIENTRY * qglPolygonMode )(GLenum face, GLenum mode);
void ( APIENTRY * qglPolygonOffset )(GLfloat factor, GLfloat units);
void ( APIENTRY * qglPolygonStipple )(const GLubyte *mask);
void ( APIENTRY * qglPopAttrib )(void);
void ( APIENTRY * qglPopClientAttrib )(void);
void ( APIENTRY * qglPopMatrix )(void);
void ( APIENTRY * qglPopName )(void);
void ( APIENTRY * qglPrioritizeTextures )(GLsizei n, const GLuint *textures, const GLclampf *priorities);
void ( APIENTRY * qglPushAttrib )(GLbitfield mask);
void ( APIENTRY * qglPushClientAttrib )(GLbitfield mask);
void ( APIENTRY * qglPushMatrix )(void);
void ( APIENTRY * qglPushName )(GLuint name);
void ( APIENTRY * qglRasterPos2d )(GLdouble x, GLdouble y);
void ( APIENTRY * qglRasterPos2dv )(const GLdouble *v);
void ( APIENTRY * qglRasterPos2f )(GLfloat x, GLfloat y);
void ( APIENTRY * qglRasterPos2fv )(const GLfloat *v);
void ( APIENTRY * qglRasterPos2i )(GLint x, GLint y);
void ( APIENTRY * qglRasterPos2iv )(const GLint *v);
void ( APIENTRY * qglRasterPos2s )(GLshort x, GLshort y);
void ( APIENTRY * qglRasterPos2sv )(const GLshort *v);
void ( APIENTRY * qglRasterPos3d )(GLdouble x, GLdouble y, GLdouble z);
void ( APIENTRY * qglRasterPos3dv )(const GLdouble *v);
void ( APIENTRY * qglRasterPos3f )(GLfloat x, GLfloat y, GLfloat z);
void ( APIENTRY * qglRasterPos3fv )(const GLfloat *v);
void ( APIENTRY * qglRasterPos3i )(GLint x, GLint y, GLint z);
void ( APIENTRY * qglRasterPos3iv )(const GLint *v);
void ( APIENTRY * qglRasterPos3s )(GLshort x, GLshort y, GLshort z);
void ( APIENTRY * qglRasterPos3sv )(const GLshort *v);
void ( APIENTRY * qglRasterPos4d )(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
void ( APIENTRY * qglRasterPos4dv )(const GLdouble *v);
void ( APIENTRY * qglRasterPos4f )(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void ( APIENTRY * qglRasterPos4fv )(const GLfloat *v);
void ( APIENTRY * qglRasterPos4i )(GLint x, GLint y, GLint z, GLint w);
void ( APIENTRY * qglRasterPos4iv )(const GLint *v);
void ( APIENTRY * qglRasterPos4s )(GLshort x, GLshort y, GLshort z, GLshort w);
void ( APIENTRY * qglRasterPos4sv )(const GLshort *v);
void ( APIENTRY * qglReadBuffer )(GLenum mode);
void ( APIENTRY * qglReadPixels )(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
void ( APIENTRY * qglRectd )(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
void ( APIENTRY * qglRectdv )(const GLdouble *v1, const GLdouble *v2);
void ( APIENTRY * qglRectf )(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
void ( APIENTRY * qglRectfv )(const GLfloat *v1, const GLfloat *v2);
void ( APIENTRY * qglRecti )(GLint x1, GLint y1, GLint x2, GLint y2);
void ( APIENTRY * qglRectiv )(const GLint *v1, const GLint *v2);
void ( APIENTRY * qglRects )(GLshort x1, GLshort y1, GLshort x2, GLshort y2);
void ( APIENTRY * qglRectsv )(const GLshort *v1, const GLshort *v2);
GLint ( APIENTRY * qglRenderMode )(GLenum mode);
void ( APIENTRY * qglRotated )(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
void ( APIENTRY * qglRotatef )(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
void ( APIENTRY * qglScaled )(GLdouble x, GLdouble y, GLdouble z);
void ( APIENTRY * qglScalef )(GLfloat x, GLfloat y, GLfloat z);
void ( APIENTRY * qglScissor )(GLint x, GLint y, GLsizei width, GLsizei height);
void ( APIENTRY * qglSelectBuffer )(GLsizei size, GLuint *buffer);
void ( APIENTRY * qglShadeModel )(GLenum mode);
void ( APIENTRY * qglStencilFunc )(GLenum func, GLint ref, GLuint mask);
void ( APIENTRY * qglStencilMask )(GLuint mask);
void ( APIENTRY * qglStencilOp )(GLenum fail, GLenum zfail, GLenum zpass);
void ( APIENTRY * qglTexCoord1d )(GLdouble s);
void ( APIENTRY * qglTexCoord1dv )(const GLdouble *v);
void ( APIENTRY * qglTexCoord1f )(GLfloat s);
void ( APIENTRY * qglTexCoord1fv )(const GLfloat *v);
void ( APIENTRY * qglTexCoord1i )(GLint s);
void ( APIENTRY * qglTexCoord1iv )(const GLint *v);
void ( APIENTRY * qglTexCoord1s )(GLshort s);
void ( APIENTRY * qglTexCoord1sv )(const GLshort *v);
void ( APIENTRY * qglTexCoord2d )(GLdouble s, GLdouble t);
void ( APIENTRY * qglTexCoord2dv )(const GLdouble *v);
void ( APIENTRY * qglTexCoord2f )(GLfloat s, GLfloat t);
void ( APIENTRY * qglTexCoord2fv )(const GLfloat *v);
void ( APIENTRY * qglTexCoord2i )(GLint s, GLint t);
void ( APIENTRY * qglTexCoord2iv )(const GLint *v);
void ( APIENTRY * qglTexCoord2s )(GLshort s, GLshort t);
void ( APIENTRY * qglTexCoord2sv )(const GLshort *v);
void ( APIENTRY * qglTexCoord3d )(GLdouble s, GLdouble t, GLdouble r);
void ( APIENTRY * qglTexCoord3dv )(const GLdouble *v);
void ( APIENTRY * qglTexCoord3f )(GLfloat s, GLfloat t, GLfloat r);
void ( APIENTRY * qglTexCoord3fv )(const GLfloat *v);
void ( APIENTRY * qglTexCoord3i )(GLint s, GLint t, GLint r);
void ( APIENTRY * qglTexCoord3iv )(const GLint *v);
void ( APIENTRY * qglTexCoord3s )(GLshort s, GLshort t, GLshort r);
void ( APIENTRY * qglTexCoord3sv )(const GLshort *v);
void ( APIENTRY * qglTexCoord4d )(GLdouble s, GLdouble t, GLdouble r, GLdouble q);
void ( APIENTRY * qglTexCoord4dv )(const GLdouble *v);
void ( APIENTRY * qglTexCoord4f )(GLfloat s, GLfloat t, GLfloat r, GLfloat q);
void ( APIENTRY * qglTexCoord4fv )(const GLfloat *v);
void ( APIENTRY * qglTexCoord4i )(GLint s, GLint t, GLint r, GLint q);
void ( APIENTRY * qglTexCoord4iv )(const GLint *v);
void ( APIENTRY * qglTexCoord4s )(GLshort s, GLshort t, GLshort r, GLshort q);
void ( APIENTRY * qglTexCoord4sv )(const GLshort *v);
void ( APIENTRY * qglTexCoordPointer )(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
void ( APIENTRY * qglTexEnvf )(GLenum target, GLenum pname, GLfloat param);
void ( APIENTRY * qglTexEnvfv )(GLenum target, GLenum pname, const GLfloat *params);
void ( APIENTRY * qglTexEnvi )(GLenum target, GLenum pname, GLint param);
void ( APIENTRY * qglTexEnviv )(GLenum target, GLenum pname, const GLint *params);
void ( APIENTRY * qglTexGend )(GLenum coord, GLenum pname, GLdouble param);
void ( APIENTRY * qglTexGendv )(GLenum coord, GLenum pname, const GLdouble *params);
void ( APIENTRY * qglTexGenf )(GLenum coord, GLenum pname, GLfloat param);
void ( APIENTRY * qglTexGenfv )(GLenum coord, GLenum pname, const GLfloat *params);
void ( APIENTRY * qglTexGeni )(GLenum coord, GLenum pname, GLint param);
void ( APIENTRY * qglTexGeniv )(GLenum coord, GLenum pname, const GLint *params);
void ( APIENTRY * qglTexImage1D )(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
void ( APIENTRY * qglTexImage2D )(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
void ( APIENTRY * qglTexParameterf )(GLenum target, GLenum pname, GLfloat param);
void ( APIENTRY * qglTexParameterfv )(GLenum target, GLenum pname, const GLfloat *params);
void ( APIENTRY * qglTexParameteri )(GLenum target, GLenum pname, GLint param);
void ( APIENTRY * qglTexParameteriv )(GLenum target, GLenum pname, const GLint *params);
void ( APIENTRY * qglTexSubImage1D )(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
void ( APIENTRY * qglTexSubImage2D )(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
void ( APIENTRY * qglTranslated )(GLdouble x, GLdouble y, GLdouble z);
void ( APIENTRY * qglTranslatef )(GLfloat x, GLfloat y, GLfloat z);
void ( APIENTRY * qglVertex2d )(GLdouble x, GLdouble y);
void ( APIENTRY * qglVertex2dv )(const GLdouble *v);
void ( APIENTRY * qglVertex2f )(GLfloat x, GLfloat y);
void ( APIENTRY * qglVertex2fv )(const GLfloat *v);
void ( APIENTRY * qglVertex2i )(GLint x, GLint y);
void ( APIENTRY * qglVertex2iv )(const GLint *v);
void ( APIENTRY * qglVertex2s )(GLshort x, GLshort y);
void ( APIENTRY * qglVertex2sv )(const GLshort *v);
void ( APIENTRY * qglVertex3d )(GLdouble x, GLdouble y, GLdouble z);
void ( APIENTRY * qglVertex3dv )(const GLdouble *v);
void ( APIENTRY * qglVertex3f )(GLfloat x, GLfloat y, GLfloat z);
void ( APIENTRY * qglVertex3fv )(const GLfloat *v);
void ( APIENTRY * qglVertex3i )(GLint x, GLint y, GLint z);
void ( APIENTRY * qglVertex3iv )(const GLint *v);
void ( APIENTRY * qglVertex3s )(GLshort x, GLshort y, GLshort z);
void ( APIENTRY * qglVertex3sv )(const GLshort *v);
void ( APIENTRY * qglVertex4d )(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
void ( APIENTRY * qglVertex4dv )(const GLdouble *v);
void ( APIENTRY * qglVertex4f )(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void ( APIENTRY * qglVertex4fv )(const GLfloat *v);
void ( APIENTRY * qglVertex4i )(GLint x, GLint y, GLint z, GLint w);
void ( APIENTRY * qglVertex4iv )(const GLint *v);
void ( APIENTRY * qglVertex4s )(GLshort x, GLshort y, GLshort z, GLshort w);
void ( APIENTRY * qglVertex4sv )(const GLshort *v);
void ( APIENTRY * qglVertexPointer )(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
void ( APIENTRY * qglViewport )(GLint x, GLint y, GLsizei width, GLsizei height);

void ( APIENTRY * qglLockArraysEXT)( int, int);
void ( APIENTRY * qglUnlockArraysEXT) ( void );

void ( APIENTRY * qglPointParameterfEXT)( GLenum param, GLfloat value );
void ( APIENTRY * qglPointParameterfvEXT)( GLenum param, const GLfloat *value );
void ( APIENTRY * qglColorTableEXT)( int, int, int, int, int, const void * );
void ( APIENTRY * qglSelectTextureSGIS)( GLenum );
void ( APIENTRY * qglMTexCoord2fSGIS)( GLenum, GLfloat, GLfloat );

/*
** QGL_Shutdown
**
** Unloads the specified DLL then nulls out all the proc pointers.
*/
void QGL_Shutdown( void )
{
	qglAccum                     = NULL;
	qglAlphaFunc                 = NULL;
	qglAreTexturesResident       = NULL;
	qglArrayElement              = NULL;
	qglBegin                     = NULL;
	qglBindTexture               = NULL;
	qglBitmap                    = NULL;
	qglBlendFunc                 = NULL;
	qglCallList                  = NULL;
	qglCallLists                 = NULL;
	qglClear                     = NULL;
	qglClearAccum                = NULL;
	qglClearColor                = NULL;
	qglClearDepth                = NULL;
	qglClearIndex                = NULL;
	qglClearStencil              = NULL;
	qglClipPlane                 = NULL;
	qglColor3b                   = NULL;
	qglColor3bv                  = NULL;
	qglColor3d                   = NULL;
	qglColor3dv                  = NULL;
	qglColor3f                   = NULL;
	qglColor3fv                  = NULL;
	qglColor3i                   = NULL;
	qglColor3iv                  = NULL;
	qglColor3s                   = NULL;
	qglColor3sv                  = NULL;
	qglColor3ub                  = NULL;
	qglColor3ubv                 = NULL;
	qglColor3ui                  = NULL;
	qglColor3uiv                 = NULL;
	qglColor3us                  = NULL;
	qglColor3usv                 = NULL;
	qglColor4b                   = NULL;
	qglColor4bv                  = NULL;
	qglColor4d                   = NULL;
	qglColor4dv                  = NULL;
	qglColor4f                   = NULL;
	qglColor4fv                  = NULL;
	qglColor4i                   = NULL;
	qglColor4iv                  = NULL;
	qglColor4s                   = NULL;
	qglColor4sv                  = NULL;
	qglColor4ub                  = NULL;
	qglColor4ubv                 = NULL;
	qglColor4ui                  = NULL;
	qglColor4uiv                 = NULL;
	qglColor4us                  = NULL;
	qglColor4usv                 = NULL;
	qglColorMask                 = NULL;
	qglColorMaterial             = NULL;
	qglColorPointer              = NULL;
	qglCopyPixels                = NULL;
	qglCopyTexImage1D            = NULL;
	qglCopyTexImage2D            = NULL;
	qglCopyTexSubImage1D         = NULL;
	qglCopyTexSubImage2D         = NULL;
	qglCullFace                  = NULL;
	qglDeleteLists               = NULL;
	qglDeleteTextures            = NULL;
	qglDepthFunc                 = NULL;
	qglDepthMask                 = NULL;
	qglDepthRange                = NULL;
	qglDisable                   = NULL;
	qglDisableClientState        = NULL;
	qglDrawArrays                = NULL;
	qglDrawBuffer                = NULL;
	qglDrawElements              = NULL;
	qglDrawPixels                = NULL;
	qglEdgeFlag                  = NULL;
	qglEdgeFlagPointer           = NULL;
	qglEdgeFlagv                 = NULL;
	qglEnable                    = NULL;
	qglEnableClientState         = NULL;
	qglEnd                       = NULL;
	qglEndList                   = NULL;
	qglEvalCoord1d               = NULL;
	qglEvalCoord1dv              = NULL;
	qglEvalCoord1f               = NULL;
	qglEvalCoord1fv              = NULL;
	qglEvalCoord2d               = NULL;
	qglEvalCoord2dv              = NULL;
	qglEvalCoord2f               = NULL;
	qglEvalCoord2fv              = NULL;
	qglEvalMesh1                 = NULL;
	qglEvalMesh2                 = NULL;
	qglEvalPoint1                = NULL;
	qglEvalPoint2                = NULL;
	qglFeedbackBuffer            = NULL;
	qglFinish                    = NULL;
	qglFlush                     = NULL;
	qglFogf                      = NULL;
	qglFogfv                     = NULL;
	qglFogi                      = NULL;
	qglFogiv                     = NULL;
	qglFrontFace                 = NULL;
	qglFrustum                   = NULL;
	qglGenLists                  = NULL;
	qglGenTextures               = NULL;
	qglGetBooleanv               = NULL;
	qglGetClipPlane              = NULL;
	qglGetDoublev                = NULL;
	qglGetError                  = NULL;
	qglGetFloatv                 = NULL;
	qglGetIntegerv               = NULL;
	qglGetLightfv                = NULL;
	qglGetLightiv                = NULL;
	qglGetMapdv                  = NULL;
	qglGetMapfv                  = NULL;
	qglGetMapiv                  = NULL;
	qglGetMaterialfv             = NULL;
	qglGetMaterialiv             = NULL;
	qglGetPixelMapfv             = NULL;
	qglGetPixelMapuiv            = NULL;
	qglGetPixelMapusv            = NULL;
	qglGetPointerv               = NULL;
	qglGetPolygonStipple         = NULL;
	qglGetString                 = NULL;
	qglGetTexEnvfv               = NULL;
	qglGetTexEnviv               = NULL;
	qglGetTexGendv               = NULL;
	qglGetTexGenfv               = NULL;
	qglGetTexGeniv               = NULL;
	qglGetTexImage               = NULL;
	qglGetTexLevelParameterfv    = NULL;
	qglGetTexLevelParameteriv    = NULL;
	qglGetTexParameterfv         = NULL;
	qglGetTexParameteriv         = NULL;
	qglHint                      = NULL;
	qglIndexMask                 = NULL;
	qglIndexPointer              = NULL;
	qglIndexd                    = NULL;
	qglIndexdv                   = NULL;
	qglIndexf                    = NULL;
	qglIndexfv                   = NULL;
	qglIndexi                    = NULL;
	qglIndexiv                   = NULL;
	qglIndexs                    = NULL;
	qglIndexsv                   = NULL;
	qglIndexub                   = NULL;
	qglIndexubv                  = NULL;
	qglInitNames                 = NULL;
	qglInterleavedArrays         = NULL;
	qglIsEnabled                 = NULL;
	qglIsList                    = NULL;
	qglIsTexture                 = NULL;
	qglLightModelf               = NULL;
	qglLightModelfv              = NULL;
	qglLightModeli               = NULL;
	qglLightModeliv              = NULL;
	qglLightf                    = NULL;
	qglLightfv                   = NULL;
	qglLighti                    = NULL;
	qglLightiv                   = NULL;
	qglLineStipple               = NULL;
	qglLineWidth                 = NULL;
	qglListBase                  = NULL;
	qglLoadIdentity              = NULL;
	qglLoadMatrixd               = NULL;
	qglLoadMatrixf               = NULL;
	qglLoadName                  = NULL;
	qglLogicOp                   = NULL;
	qglMap1d                     = NULL;
	qglMap1f                     = NULL;
	qglMap2d                     = NULL;
	qglMap2f                     = NULL;
	qglMapGrid1d                 = NULL;
	qglMapGrid1f                 = NULL;
	qglMapGrid2d                 = NULL;
	qglMapGrid2f                 = NULL;
	qglMaterialf                 = NULL;
	qglMaterialfv                = NULL;
	qglMateriali                 = NULL;
	qglMaterialiv                = NULL;
	qglMatrixMode                = NULL;
	qglMultMatrixd               = NULL;
	qglMultMatrixf               = NULL;
	qglNewList                   = NULL;
	qglNormal3b                  = NULL;
	qglNormal3bv                 = NULL;
	qglNormal3d                  = NULL;
	qglNormal3dv                 = NULL;
	qglNormal3f                  = NULL;
	qglNormal3fv                 = NULL;
	qglNormal3i                  = NULL;
	qglNormal3iv                 = NULL;
	qglNormal3s                  = NULL;
	qglNormal3sv                 = NULL;
	qglNormalPointer             = NULL;
	qglOrtho                     = NULL;
	qglPassThrough               = NULL;
	qglPixelMapfv                = NULL;
	qglPixelMapuiv               = NULL;
	qglPixelMapusv               = NULL;
	qglPixelStoref               = NULL;
	qglPixelStorei               = NULL;
	qglPixelTransferf            = NULL;
	qglPixelTransferi            = NULL;
	qglPixelZoom                 = NULL;
	qglPointSize                 = NULL;
	qglPolygonMode               = NULL;
	qglPolygonOffset             = NULL;
	qglPolygonStipple            = NULL;
	qglPopAttrib                 = NULL;
	qglPopClientAttrib           = NULL;
	qglPopMatrix                 = NULL;
	qglPopName                   = NULL;
	qglPrioritizeTextures        = NULL;
	qglPushAttrib                = NULL;
	qglPushClientAttrib          = NULL;
	qglPushMatrix                = NULL;
	qglPushName                  = NULL;
	qglRasterPos2d               = NULL;
	qglRasterPos2dv              = NULL;
	qglRasterPos2f               = NULL;
	qglRasterPos2fv              = NULL;
	qglRasterPos2i               = NULL;
	qglRasterPos2iv              = NULL;
	qglRasterPos2s               = NULL;
	qglRasterPos2sv              = NULL;
	qglRasterPos3d               = NULL;
	qglRasterPos3dv              = NULL;
	qglRasterPos3f               = NULL;
	qglRasterPos3fv              = NULL;
	qglRasterPos3i               = NULL;
	qglRasterPos3iv              = NULL;
	qglRasterPos3s               = NULL;
	qglRasterPos3sv              = NULL;
	qglRasterPos4d               = NULL;
	qglRasterPos4dv              = NULL;
	qglRasterPos4f               = NULL;
	qglRasterPos4fv              = NULL;
	qglRasterPos4i               = NULL;
	qglRasterPos4iv              = NULL;
	qglRasterPos4s               = NULL;
	qglRasterPos4sv              = NULL;
	qglReadBuffer                = NULL;
	qglReadPixels                = NULL;
	qglRectd                     = NULL;
	qglRectdv                    = NULL;
	qglRectf                     = NULL;
	qglRectfv                    = NULL;
	qglRecti                     = NULL;
	qglRectiv                    = NULL;
	qglRects                     = NULL;
	qglRectsv                    = NULL;
	qglRenderMode                = NULL;
	qglRotated                   = NULL;
	qglRotatef                   = NULL;
	qglScaled                    = NULL;
	qglScalef                    = NULL;
	qglScissor                   = NULL;
	qglSelectBuffer              = NULL;
	qglShadeModel                = NULL;
	qglStencilFunc               = NULL;
	qglStencilMask               = NULL;
	qglStencilOp                 = NULL;
	qglTexCoord1d                = NULL;
	qglTexCoord1dv               = NULL;
	qglTexCoord1f                = NULL;
	qglTexCoord1fv               = NULL;
	qglTexCoord1i                = NULL;
	qglTexCoord1iv               = NULL;
	qglTexCoord1s                = NULL;
	qglTexCoord1sv               = NULL;
	qglTexCoord2d                = NULL;
	qglTexCoord2dv               = NULL;
	qglTexCoord2f                = NULL;
	qglTexCoord2fv               = NULL;
	qglTexCoord2i                = NULL;
	qglTexCoord2iv               = NULL;
	qglTexCoord2s                = NULL;
	qglTexCoord2sv               = NULL;
	qglTexCoord3d                = NULL;
	qglTexCoord3dv               = NULL;
	qglTexCoord3f                = NULL;
	qglTexCoord3fv               = NULL;
	qglTexCoord3i                = NULL;
	qglTexCoord3iv               = NULL;
	qglTexCoord3s                = NULL;
	qglTexCoord3sv               = NULL;
	qglTexCoord4d                = NULL;
	qglTexCoord4dv               = NULL;
	qglTexCoord4f                = NULL;
	qglTexCoord4fv               = NULL;
	qglTexCoord4i                = NULL;
	qglTexCoord4iv               = NULL;
	qglTexCoord4s                = NULL;
	qglTexCoord4sv               = NULL;
	qglTexCoordPointer           = NULL;
	qglTexEnvf                   = NULL;
	qglTexEnvfv                  = NULL;
	qglTexEnvi                   = NULL;
	qglTexEnviv                  = NULL;
	qglTexGend                   = NULL;
	qglTexGendv                  = NULL;
	qglTexGenf                   = NULL;
	qglTexGenfv                  = NULL;
	qglTexGeni                   = NULL;
	qglTexGeniv                  = NULL;
	qglTexImage1D                = NULL;
	qglTexImage2D                = NULL;
	qglTexParameterf             = NULL;
	qglTexParameterfv            = NULL;
	qglTexParameteri             = NULL;
	qglTexParameteriv            = NULL;
	qglTexSubImage1D             = NULL;
	qglTexSubImage2D             = NULL;
	qglTranslated                = NULL;
	qglTranslatef                = NULL;
	qglVertex2d                  = NULL;
	qglVertex2dv                 = NULL;
	qglVertex2f                  = NULL;
	qglVertex2fv                 = NULL;
	qglVertex2i                  = NULL;
	qglVertex2iv                 = NULL;
	qglVertex2s                  = NULL;
	qglVertex2sv                 = NULL;
	qglVertex3d                  = NULL;
	qglVertex3dv                 = NULL;
	qglVertex3f                  = NULL;
	qglVertex3fv                 = NULL;
	qglVertex3i                  = NULL;
	qglVertex3iv                 = NULL;
	qglVertex3s                  = NULL;
	qglVertex3sv                 = NULL;
	qglVertex4d                  = NULL;
	qglVertex4dv                 = NULL;
	qglVertex4f                  = NULL;
	qglVertex4fv                 = NULL;
	qglVertex4i                  = NULL;
	qglVertex4iv                 = NULL;
	qglVertex4s                  = NULL;
	qglVertex4sv                 = NULL;
	qglVertexPointer             = NULL;
	qglViewport                  = NULL;
}
void glPointParameterf(GLenum pname, GLfloat param);
void glPointParameterfv(GLenum pname, const GLfloat * params);

/*
** QGL_Init
**
** This is responsible for binding our qgl function pointers to 
** the appropriate GL stuff.  In Windows this means doing a 
** LoadLibrary and a bunch of calls to GetProcAddress.  On other
** operating systems we need to do the right thing, whatever that
** might be.
** 
*/
qboolean QGL_Init( const char *dllname )
{
#if 0
	qglAccum                     = 	dllAccum = glAccum;// not needed
	qglAlphaFunc                 = 	dllAlphaFunc = glAlphaFunc;
	qglAreTexturesResident       = 	dllAreTexturesResident = glAreTexturesResident;// not needed
	qglArrayElement              = 	dllArrayElement = glArrayElement;
	qglBegin                     = 	dllBegin = glBegin;
	qglBindTexture               = 	dllBindTexture = glBindTexture;
	qglBitmap                    = 	dllBitmap = glBitmap;// not needed
	qglBlendFunc                 = 	dllBlendFunc = glBlendFunc;
	qglCallList                  = 	dllCallList = glCallList;// not needed
	qglCallLists                 = 	dllCallLists = glCallLists;// not needed
	qglClear                     = 	dllClear = glClear;
	qglClearAccum                = 	dllClearAccum = glClearAccum;// not needed
	qglClearColor                = 	dllClearColor = glClearColor;
	qglClearDepth                = 	dllClearDepth = glClearDepth;
	qglClearIndex                = 	dllClearIndex = glClearIndex;// not needed
	qglClearStencil              = 	dllClearStencil = glClearStencil;
	qglClipPlane                 = 	dllClipPlane = glClipPlane;// not needed
	qglColor3b                   = 	dllColor3b = glColor3b;// not needed
	qglColor3bv                  = 	dllColor3bv = glColor3bv;// not needed
	qglColor3d                   = 	dllColor3d = glColor3d;// not needed
	qglColor3dv                  = 	dllColor3dv = glColor3dv;// not needed
	qglColor3f                   = 	dllColor3f = glColor3f;
	qglColor3fv                  = 	dllColor3fv = glColor3fv;
	qglColor3i                   = 	dllColor3i = glColor3i;// not needed
	qglColor3iv                  = 	dllColor3iv = glColor3iv;// not needed
	qglColor3s                   = 	dllColor3s = glColor3s;// not needed
	qglColor3sv                  = 	dllColor3sv = glColor3sv;// not needed
	qglColor3ub                  = 	dllColor3ub = glColor3ub;// not needed
	qglColor3ubv                 = 	dllColor3ubv = glColor3ubv;
	qglColor3ui                  = 	dllColor3ui = glColor3ui;// not needed
	qglColor3uiv                 = 	dllColor3uiv = glColor3uiv;// not needed
	qglColor3us                  = 	dllColor3us = glColor3us;// not needed
	qglColor3usv                 = 	dllColor3usv = glColor3usv;// not needed
	qglColor4b                   = 	dllColor4b = glColor4b;// not needed
	qglColor4bv                  = 	dllColor4bv = glColor4bv;// not needed
	qglColor4d                   = 	dllColor4d = glColor4d;// not needed
	qglColor4dv                  = 	dllColor4dv = glColor4dv;// not needed
	qglColor4f                   = 	dllColor4f = glColor4f;
	qglColor4fv                  = 	dllColor4fv = glColor4fv;
	qglColor4i                   = 	dllColor4i = glColor4i;// not needed
	qglColor4iv                  = 	dllColor4iv = glColor4iv;// not needed
	qglColor4s                   = 	dllColor4s = glColor4s;// not needed
	qglColor4sv                  = 	dllColor4sv = glColor4sv;// not needed
	qglColor4ub                  = 	dllColor4ub = glColor4ub;// not needed
	qglColor4ubv                 = 	dllColor4ubv = glColor4ubv;
	qglColor4ui                  = 	dllColor4ui = glColor4ui;// not needed
	qglColor4uiv                 = 	dllColor4uiv = glColor4uiv;// not needed
	qglColor4us                  = 	dllColor4us = glColor4us;// not needed
	qglColor4usv                 = 	dllColor4usv = glColor4usv;// not needed
	qglColorMask                 = 	dllColorMask = glColorMask;// not needed
	qglColorMaterial             = 	dllColorMaterial = glColorMaterial;// not needed
	qglColorPointer              = 	dllColorPointer = glColorPointer;
	qglCopyPixels                = 	dllCopyPixels = glCopyPixels;// not needed
	qglCopyTexImage1D            = 	dllCopyTexImage1D = glCopyTexImage1D;// not needed
	qglCopyTexImage2D            = 	dllCopyTexImage2D = glCopyTexImage2D;// not needed
	qglCopyTexSubImage1D         = 	dllCopyTexSubImage1D = glCopyTexSubImage1D;// not needed
	qglCopyTexSubImage2D         = 	dllCopyTexSubImage2D = glCopyTexSubImage2D;// not needed
	qglCullFace                  = 	dllCullFace = glCullFace;
	qglDeleteLists               = 	dllDeleteLists = glDeleteLists; // not needed
	qglDeleteTextures            = 	dllDeleteTextures = glDeleteTextures;
	qglDepthFunc                 = 	dllDepthFunc = glDepthFunc;
	qglDepthMask                 = 	dllDepthMask = glDepthMask;
	qglDepthRange                = 	dllDepthRange = glDepthRange;
	qglDisable                   = 	dllDisable = glDisable;
	qglDisableClientState        = 	dllDisableClientState = glDisableClientState; // not needed
	qglDrawArrays                = 	dllDrawArrays = glDrawArrays; // not needed
	qglDrawBuffer                = 	dllDrawBuffer 				 = glDrawBuffer;
	qglDrawElements              = 	dllDrawElements				 = glDrawElements;		// not needed
	qglDrawPixels                = 	dllDrawPixels				 = glDrawPixels;		// not needed
	qglEdgeFlag                  = 	dllEdgeFlag					 = glEdgeFlag;			// not needed
	qglEdgeFlagPointer           = 	dllEdgeFlagPointer			 = glEdgeFlagPointer;	// not needed
	qglEdgeFlagv                 = 	dllEdgeFlagv				 = glEdgeFlagv;			// not needed
	qglEnable                    = 	dllEnable                    = glEnable;
	qglEnableClientState         = 	dllEnableClientState         = glEnableClientState;
	qglEnd                       = 	dllEnd                       = glEnd;
	qglEndList                   = 	dllEndList                   = glEndList;			// not needed
	qglEvalCoord1d				 = 	dllEvalCoord1d				 = glEvalCoord1d;		// not needed
	qglEvalCoord1dv              = 	dllEvalCoord1dv              = glEvalCoord1dv;		// not needed
	qglEvalCoord1f               = 	dllEvalCoord1f               = glEvalCoord1f;		// not needed
	qglEvalCoord1fv              = 	dllEvalCoord1fv              = glEvalCoord1fv;		// not needed
	qglEvalCoord2d               = 	dllEvalCoord2d               = glEvalCoord2d;		// not needed
	qglEvalCoord2dv              = 	dllEvalCoord2dv              = glEvalCoord2dv;		// not needed
	qglEvalCoord2f               = 	dllEvalCoord2f               = glEvalCoord2f;		// not needed
	qglEvalCoord2fv              = 	dllEvalCoord2fv              = glEvalCoord2fv;		// not needed
	qglEvalMesh1                 = 	dllEvalMesh1                 = glEvalMesh1;			// not needed
	qglEvalMesh2                 = 	dllEvalMesh2                 = glEvalMesh2;			// not needed
	qglEvalPoint1                = 	dllEvalPoint1                = glEvalPoint1;		// not needed
	qglEvalPoint2                = 	dllEvalPoint2                = glEvalPoint2;		// not needed
	qglFeedbackBuffer            = 	dllFeedbackBuffer            = glFeedbackBuffer;	// not needed
	qglFinish                    = 	dllFinish                    = glFinish;
	qglFlush                     = 	dllFlush                     = glFlush;				// not needed
	qglFogf                      = 	dllFogf                      = glFogf;				// not needed
	qglFogfv                     = 	dllFogfv                     = glFogfv;				// not needed
	qglFogi                      = 	dllFogi                      = glFogi;				// not needed
	qglFogiv                     = 	dllFogiv                     = glFogiv;				// not needed
	qglFrontFace                 = 	dllFrontFace                 = glFrontFace;
	qglFrustum                   = 	dllFrustum                   = glFrustum;
	qglGenLists                  = 	dllGenLists                  = glGenLists;			// not needed
	qglGenTextures               = 	dllGenTextures               = glGenTextures;	
	qglGetBooleanv               = 	dllGetBooleanv               = glGetBooleanv;		// not needed
	qglGetClipPlane              = 	dllGetClipPlane              = glGetClipPlane;		// not needed
	qglGetDoublev                = 	dllGetDoublev                = glGetDoublev;		// not needed
	qglGetError                  = 	dllGetError                  = glGetError;
	qglGetFloatv                 = 	dllGetFloatv                 = glGetFloatv;			
	qglGetIntegerv               = 	dllGetIntegerv               = glGetIntegerv;		// not needed
	qglGetLightfv                = 	dllGetLightfv                = glGetLightfv;		// not needed
	qglGetLightiv                = 	dllGetLightiv                = glGetLightiv;		// not needed
	qglGetMapdv                  = 	dllGetMapdv                  = glGetMapdv;			// not needed
	qglGetMapfv                  = 	dllGetMapfv                  = glGetMapfv;			// not needed
	qglGetMapiv                  = 	dllGetMapiv                  = glGetMapiv;			// not needed
	qglGetMaterialfv             = 	dllGetMaterialfv             = glGetMaterialfv;		// not needed
	qglGetMaterialiv             = 	dllGetMaterialiv             = glGetMaterialiv;		// not needed
	qglGetPixelMapfv             = 	dllGetPixelMapfv             = glGetPixelMapfv;		// not needed
	qglGetPixelMapuiv            = 	dllGetPixelMapuiv            = glGetPixelMapuiv;	// not needed
	qglGetPixelMapusv            = 	dllGetPixelMapusv            = glGetPixelMapusv;	// not needed
	qglGetPointerv               = 	dllGetPointerv               = glGetPointerv;		// not needed
	qglGetPolygonStipple         = 	dllGetPolygonStipple         = glGetPolygonStipple;	// not needed
	qglGetString                 = 	dllGetString                 = glGetString;			// not needed
	qglGetTexEnvfv               = 	dllGetTexEnvfv               = glGetTexEnvfv;		// not needed
	qglGetTexEnviv               = 	dllGetTexEnviv               = glGetTexEnviv;		// not needed
	qglGetTexGendv               = 	dllGetTexGendv               = glGetTexGendv;		// not needed
	qglGetTexGenfv               = 	dllGetTexGenfv               = glGetTexGenfv;		// not needed
	qglGetTexGeniv               = 	dllGetTexGeniv               = glGetTexGeniv;		// not needed
	qglGetTexImage               = 	dllGetTexImage               = glGetTexImage;		// not needed
//	qglGetTexLevelParameterfv    = 	dllGetTexLevelParameterfv    = glGetLevelParameterfv;
//	qglGetTexLevelParameteriv    = 	dllGetTexLevelParameteriv    = glGetLevelParameteriv;
	qglGetTexParameterfv         = 	dllGetTexParameterfv         = glGetTexParameterfv; // not needed
	qglGetTexParameteriv         = 	dllGetTexParameteriv         = glGetTexParameteriv; // not needed
	qglHint                      = 	dllHint                      = glHint;				// not needed
	qglIndexMask                 = 	dllIndexMask                 = glIndexMask;			// not needed
	qglIndexPointer              = 	dllIndexPointer              = glIndexPointer;		// not needed
	qglIndexd                    = 	dllIndexd                    = glIndexd;			// not needed
	qglIndexdv                   = 	dllIndexdv                   = glIndexdv;			// not needed
	qglIndexf                    = 	dllIndexf                    = glIndexf;			// not needed
	qglIndexfv                   = 	dllIndexfv                   = glIndexfv;			// not needed
	qglIndexi                    = 	dllIndexi                    = glIndexi;			// not needed
	qglIndexiv                   = 	dllIndexiv                   = glIndexiv;			// not needed
	qglIndexs                    = 	dllIndexs                    = glIndexs;			// not needed
	qglIndexsv                   = 	dllIndexsv                   = glIndexsv;			// not needed
	qglIndexub                   = 	dllIndexub                   = glIndexub;			// not needed
	qglIndexubv                  = 	dllIndexubv                  = glIndexubv;			// not needed
	qglInitNames                 = 	dllInitNames                 = glInitNames;			// not needed
	qglInterleavedArrays         = 	dllInterleavedArrays         = glInterleavedArrays;	// not needed
	qglIsEnabled                 = 	dllIsEnabled                 = glIsEnabled;			// not needed
	qglIsList                    = 	dllIsList                    = glIsList;			// not needed
	qglIsTexture                 = 	dllIsTexture                 = glIsTexture;			// not needed
	qglLightModelf               = 	dllLightModelf               = glLightModelf;		// not needed
	qglLightModelfv              = 	dllLightModelfv              = glLightModelfv;		// not needed
	qglLightModeli               = 	dllLightModeli               = glLightModeli;		// not needed
	qglLightModeliv              = 	dllLightModeliv              = glLightModeliv;		// not needed
	qglLightf                    = 	dllLightf                    = glLightf;			// not needed
	qglLightfv                   = 	dllLightfv                   = glLightfv;			// not needed
	qglLighti                    = 	dllLighti                    = glLighti;			// not needed
	qglLightiv                   = 	dllLightiv                   = glLightiv;			// not needed
	qglLineStipple               = 	dllLineStipple               = glLineStipple;		// not needed
	qglLineWidth                 = 	dllLineWidth                 = glLineWidth;			// not needed
	qglListBase                  = 	dllListBase                  = glListBase;			// not needed
	qglLoadIdentity              = 	dllLoadIdentity              = glLoadIdentity;
	qglLoadMatrixd               = 	dllLoadMatrixd               = glLoadMatrixd;		// not needed
	qglLoadMatrixf               = 	dllLoadMatrixf               = glLoadMatrixf;
	qglLoadName                  = 	dllLoadName                  = glLoadName;			// not needed
	qglLogicOp                   = 	dllLogicOp                   = glLogicOp;			// not needed
	qglMap1d                     = 	dllMap1d                     = glMap1d;				// not needed
	qglMap1f                     = 	dllMap1f                     = glMap1f;				// not needed
	qglMap2d                     = 	dllMap2d                     = glMap2d;				// not needed
	qglMap2f                     = 	dllMap2f                     = glMap2f;				// not needed
	qglMapGrid1d                 = 	dllMapGrid1d                 = glMapGrid1d;			// not needed
	qglMapGrid1f                 = 	dllMapGrid1f                 = glMapGrid1f;			// not needed
	qglMapGrid2d                 = 	dllMapGrid2d                 = glMapGrid2d;			// not needed
	qglMapGrid2f                 = 	dllMapGrid2f                 = glMapGrid2f;			// not needed
	qglMaterialf                 = 	dllMaterialf                 = glMaterialf;			// not needed
	qglMaterialfv                = 	dllMaterialfv                = glMaterialfv;		// not needed
	qglMateriali                 = 	dllMateriali                 = glMateriali;			// not needed
	qglMaterialiv                = 	dllMaterialiv                = glMaterialiv;		// not needed
	qglMatrixMode                = 	dllMatrixMode                = glMatrixMode;
	qglMultMatrixd               = 	dllMultMatrixd               = glMultMatrixd;		// not needed
	qglMultMatrixf               = 	dllMultMatrixf               = glMultMatrixf;		// not needed
	qglNewList                   = 	dllNewList                   = glNewList;			// not needed
	qglNormal3b                  = 	dllNormal3b                  = glNormal3b;			// not needed
	qglNormal3bv                 = 	dllNormal3bv                 = glNormal3bv;			// not needed
	qglNormal3d                  = 	dllNormal3d                  = glNormal3d;			// not needed
	qglNormal3dv                 = 	dllNormal3dv                 = glNormal3dv;			// not needed
	qglNormal3f                  = 	dllNormal3f                  = glNormal3f;			// not needed
	qglNormal3fv                 = 	dllNormal3fv                 = glNormal3fv;			// not needed
	qglNormal3i                  = 	dllNormal3i                  = glNormal3i;			// not needed
	qglNormal3iv                 = 	dllNormal3iv                 = glNormal3iv;			// not needed
	qglNormal3s                  = 	dllNormal3s                  = glNormal3s;			// not needed
	qglNormal3sv                 = 	dllNormal3sv                 = glNormal3sv;			// not needed
	qglNormalPointer             = 	dllNormalPointer             = glNormalPointer;		// not needed
	qglOrtho                     = 	dllOrtho                     = glOrtho;
	qglPassThrough               = 	dllPassThrough               = glPassThrough;		// not needed
	qglPixelMapfv                = 	dllPixelMapfv                = glPixelMapfv;		// not needed
	qglPixelMapuiv               = 	dllPixelMapuiv               = glPixelMapuiv;		// not needed
	qglPixelMapusv               = 	dllPixelMapusv               = glPixelMapusv;		// not needed
	qglPixelStoref               = 	dllPixelStoref               = glPixelStoref;		// not needed
	qglPixelStorei               = 	dllPixelStorei               = glPixelStorei;		// not needed
	qglPixelTransferf            = 	dllPixelTransferf            = glPixelTransferf;	// not needed
	qglPixelTransferi            = 	dllPixelTransferi            = glPixelTransferi;	// not needed
	qglPixelZoom                 = 	dllPixelZoom                 = glPixelZoom;			// not needed
	qglPointSize                 = 	dllPointSize                 = glPointSize;
	qglPolygonMode               = 	dllPolygonMode               = glPolygonMode;
	qglPolygonOffset             = 	dllPolygonOffset             = glPolygonOffset;		// not needed
	qglPolygonStipple            = 	dllPolygonStipple            = glPolygonStipple;	// not needed
	qglPopAttrib                 = 	dllPopAttrib                 = glPopAttrib;			// not needed
	qglPopClientAttrib           = 	dllPopClientAttrib           = glPopClientAttrib;	// not needed
	qglPopMatrix                 = 	dllPopMatrix                 = glPopMatrix;			
	qglPopName                   = 	dllPopName                   = glPopName;			// not needed
	qglPrioritizeTextures        = 	dllPrioritizeTextures        = glPrioritizeTextures;// not needed
	qglPushAttrib                = 	dllPushAttrib                = glPushAttrib;		// not needed
	qglPushClientAttrib          = 	dllPushClientAttrib          = glPushClientAttrib;	// not needed
	qglPushMatrix                = 	dllPushMatrix                = glPushMatrix;		
	qglPushName                  = 	dllPushName                  = glPushName;			// not needed
	qglRasterPos2d               = 	dllRasterPos2d               = glRasterPos2d;		// not needed
	qglRasterPos2dv              = 	dllRasterPos2dv              = glRasterPos2dv;		// not needed
	qglRasterPos2f               = 	dllRasterPos2f               = glRasterPos2f;		// not needed
	qglRasterPos2fv              = 	dllRasterPos2fv              = glRasterPos2fv;		// not needed
	qglRasterPos2i               = 	dllRasterPos2i               = glRasterPos2i;		// not needed
	qglRasterPos2iv              = 	dllRasterPos2iv              = glRasterPos2iv;		// not needed
	qglRasterPos2s               = 	dllRasterPos2s               = glRasterPos2s;		// not needed
	qglRasterPos2sv              = 	dllRasterPos2sv              = glRasterPos2sv;		// not needed
	qglRasterPos3d               = 	dllRasterPos3d               = glRasterPos3d;		// not needed
	qglRasterPos3dv              = 	dllRasterPos3dv              = glRasterPos3dv;		// not needed
	qglRasterPos3f               = 	dllRasterPos3f               = glRasterPos3f;		// not needed
	qglRasterPos3fv              = 	dllRasterPos3fv              = glRasterPos3fv;		// not needed
	qglRasterPos3i               = 	dllRasterPos3i               = glRasterPos3i;		// not needed
	qglRasterPos3iv              = 	dllRasterPos3iv              = glRasterPos3iv;		// not needed
	qglRasterPos3s               = 	dllRasterPos3s               = glRasterPos3s;		// not needed
	qglRasterPos3sv              = 	dllRasterPos3sv              = glRasterPos3sv;		// not needed
	qglRasterPos4d               = 	dllRasterPos4d               = glRasterPos4d;		// not needed
	qglRasterPos4dv              = 	dllRasterPos4dv              = glRasterPos4dv;		// not needed
	qglRasterPos4f               = 	dllRasterPos4f               = glRasterPos4f;		// not needed
	qglRasterPos4fv              = 	dllRasterPos4fv              = glRasterPos4fv;		// not needed
	qglRasterPos4i               = 	dllRasterPos4i               = glRasterPos4i;		// not needed
	qglRasterPos4iv              = 	dllRasterPos4iv              = glRasterPos4iv;		// not needed
	qglRasterPos4s               = 	dllRasterPos4s               = glRasterPos4s;		// not needed
	qglRasterPos4sv              = 	dllRasterPos4sv              = glRasterPos4sv;		// not needed
	qglReadBuffer                = 	dllReadBuffer                = glReadBuffer;		// not needed
	qglReadPixels                = 	dllReadPixels                = glReadPixels;
	qglRectd                     = 	dllRectd                     = glRectd;				// not needed
	qglRectdv                    = 	dllRectdv                    = glRectdv;			// not needed
	qglRectf                     = 	dllRectf                     = glRectf;				// not needed
	qglRectfv                    = 	dllRectfv                    = glRectfv;			// not needed
	qglRecti                     = 	dllRecti                     = glRecti;				// not needed
	qglRectiv                    = 	dllRectiv                    = glRectiv;			// not needed
	qglRects                     = 	dllRects                     = glRects;				// not needed
	qglRectsv                    = 	dllRectsv                    = glRectsv;			// not needed
	qglRenderMode                = 	dllRenderMode                = glRenderMode;		// not needed
	qglRotated                   = 	dllRotated                   = glRotated;			// not needed
	qglRotatef                   = 	dllRotatef                   = glRotatef;
	qglScaled                    = 	dllScaled                    = glScaled;			// not needed
	qglScalef                    = 	dllScalef                    = glScalef;
	qglScissor                   = 	dllScissor                   = glScissor;
	qglSelectBuffer              = 	dllSelectBuffer              = glSelectBuffer;		// not needed
	qglShadeModel                = 	dllShadeModel                = glShadeModel;
	qglStencilFunc               = 	dllStencilFunc               = glStencilFunc;		// not needed
	qglStencilMask               = 	dllStencilMask               = glStencilMask;		// not needed
	qglStencilOp                 = 	dllStencilOp                 = glStencilOp;			// not needed
	qglTexCoord1d                = 	dllTexCoord1d                = glTexCoord1d;		// not needed
	qglTexCoord1dv               = 	dllTexCoord1dv               = glTexCoord1dv;		// not needed
	qglTexCoord1f                = 	dllTexCoord1f                = glTexCoord1f;		// not needed
	qglTexCoord1fv               = 	dllTexCoord1fv               = glTexCoord1fv;		// not needed
	qglTexCoord1i                = 	dllTexCoord1i                = glTexCoord1i;		// not needed
	qglTexCoord1iv               = 	dllTexCoord1iv               = glTexCoord1iv;		// not needed
	qglTexCoord1s                = 	dllTexCoord1s                = glTexCoord1s;		// not needed
	qglTexCoord1sv               = 	dllTexCoord1sv               = glTexCoord1sv;		// not needed
	qglTexCoord2d                = 	dllTexCoord2d                = glTexCoord2d;		// not needed
	qglTexCoord2dv               = 	dllTexCoord2dv               = glTexCoord2dv;		// not needed
	qglTexCoord2f                = 	dllTexCoord2f                = glTexCoord2f;
	qglTexCoord2fv               = 	dllTexCoord2fv               = glTexCoord2fv;		// not needed
	qglTexCoord2i                = 	dllTexCoord2i                = glTexCoord2i;		// not needed
	qglTexCoord2iv               = 	dllTexCoord2iv               = glTexCoord2iv;		// not needed
	qglTexCoord2s                = 	dllTexCoord2s                = glTexCoord2s;		// not needed
	qglTexCoord2sv               = 	dllTexCoord2sv               = glTexCoord2sv;		// not needed
	qglTexCoord3d                = 	dllTexCoord3d                = glTexCoord3d;		// not needed
	qglTexCoord3dv               = 	dllTexCoord3dv               = glTexCoord3dv;		// not needed
	qglTexCoord3f                = 	dllTexCoord3f                = glTexCoord3f;		// not needed
	qglTexCoord3fv               = 	dllTexCoord3fv               = glTexCoord3fv;		// not needed
	qglTexCoord3i                = 	dllTexCoord3i                = glTexCoord3i;		// not needed
	qglTexCoord3iv               = 	dllTexCoord3iv               = glTexCoord3iv;		// not needed
	qglTexCoord3s                = 	dllTexCoord3s                = glTexCoord3s;		// not needed
	qglTexCoord3sv               = 	dllTexCoord3sv               = glTexCoord3sv;		// not needed
	qglTexCoord4d                = 	dllTexCoord4d                = glTexCoord4d;		// not needed
	qglTexCoord4dv               = 	dllTexCoord4dv               = glTexCoord4dv;		// not needed
	qglTexCoord4f                = 	dllTexCoord4f                = glTexCoord4f;		// not needed
	qglTexCoord4fv               = 	dllTexCoord4fv               = glTexCoord4fv;		// not needed
	qglTexCoord4i                = 	dllTexCoord4i                = glTexCoord4i;		// not needed
	qglTexCoord4iv               = 	dllTexCoord4iv               = glTexCoord4iv;		// not needed
	qglTexCoord4s                = 	dllTexCoord4s                = glTexCoord4s;		// not needed
	qglTexCoord4sv               = 	dllTexCoord4sv               = glTexCoord4sv;		// not needed
	qglTexCoordPointer           = 	dllTexCoordPointer           = glTexCoordPointer;	// not needed
	qglTexEnvf                   = 	dllTexEnvf                   = glTexEnvf;
	qglTexEnvfv                  = 	dllTexEnvfv                  = glTexEnvfv;			// not needed
	qglTexEnvi                   = 	dllTexEnvi                   = glTexEnvi;			// not needed
	qglTexEnviv                  = 	dllTexEnviv                  = glTexEnviv;			// not needed
	qglTexGend                   = 	dllTexGend                   = glTexGend;			// not needed
	qglTexGendv                  = 	dllTexGendv                  = glTexGendv;			// not needed
	qglTexGenf                   = 	dllTexGenf                   = glTexGenf;			// not needed
	qglTexGenfv                  = 	dllTexGenfv                  = glTexGenfv;			// not needed
	qglTexGeni                   = 	dllTexGeni                   = glTexGeni;			// not needed
	qglTexGeniv                  = 	dllTexGeniv                  = glTexGeniv;			// not needed
	qglTexImage1D                = 	dllTexImage1D                = glTexImage1D;		// not needed
	qglTexImage2D                = 	dllTexImage2D                = glTexImage2D;
	qglTexParameterf             = 	dllTexParameterf             = glTexParameterf;
	qglTexParameterfv            = 	dllTexParameterfv            = glTexParameterfv;	// not needed
	qglTexParameteri             = 	dllTexParameteri             = glTexParameteri;		// not needed
	qglTexParameteriv            = 	dllTexParameteriv            = glTexParameteriv;	// not needed
	qglTexSubImage1D             = 	dllTexSubImage1D             = glTexSubImage1D;		// not needed
	qglTexSubImage2D             = 	dllTexSubImage2D             = glTexSubImage2D;
	qglTranslated                = 	dllTranslated                = glTranslated;		// not needed
	qglTranslatef                = 	dllTranslatef                = glTranslatef;
	qglVertex2d                  = 	dllVertex2d                  = glVertex2d;			// not needed
	qglVertex2dv                 = 	dllVertex2dv                 = glVertex2dv;			// not needed
	qglVertex2f                  = 	dllVertex2f                  = glVertex2f;
	qglVertex2fv                 = 	dllVertex2fv                 = glVertex2fv;
	qglVertex2i                  = 	dllVertex2i                  = glVertex2i;			// not needed
	qglVertex2iv                 = 	dllVertex2iv                 = glVertex2iv;			// not needed
	qglVertex2s                  = 	dllVertex2s                  = glVertex2s;			// not needed
	qglVertex2sv                 = 	dllVertex2sv                 = glVertex2sv;			// not needed
	qglVertex3d                  = 	dllVertex3d                  = glVertex3d;			// not needed
	qglVertex3dv                 = 	dllVertex3dv                 = glVertex3dv;			// not needed
	qglVertex3f                  = 	dllVertex3f                  = glVertex3f;
	qglVertex3fv                 = 	dllVertex3fv                 = glVertex3fv;
	qglVertex3i                  = 	dllVertex3i                  = glVertex3i;			// not needed
	qglVertex3iv                 = 	dllVertex3iv                 = glVertex3iv;			// not needed
	qglVertex3s                  = 	dllVertex3s                  = glVertex3s;			// not needed
	qglVertex3sv                 = 	dllVertex3sv                 = glVertex3sv;			// not needed
	qglVertex4d                  = 	dllVertex4d                  = glVertex4d;			// not needed
	qglVertex4dv                 = 	dllVertex4dv                 = glVertex4dv;			// not needed
	qglVertex4f                  = 	dllVertex4f                  = glVertex4f;			// not needed
	qglVertex4fv                 = 	dllVertex4fv                 = glVertex4fv;			// not needed
	qglVertex4i                  = 	dllVertex4i                  = glVertex4i;			// not needed
	qglVertex4iv                 = 	dllVertex4iv                 = glVertex4iv;			// not needed
	qglVertex4s                  = 	dllVertex4s                  = glVertex4s;			// not needed
	qglVertex4sv                 = 	dllVertex4sv                 = glVertex4sv;			// not needed
	qglVertexPointer             = 	dllVertexPointer             = glVertexPointer;		// not needed
	qglViewport                  = 	dllViewport                  = glViewport;

	qglPointParameterfEXT = 0;
	qglPointParameterfvEXT = 0;
	qglColorTableEXT = 0;
	qglSelectTextureSGIS = 0;
	qglMTexCoord2fSGIS = 0;
#else
#endif
	qglPointParameterfEXT = 0;
	qglPointParameterfvEXT = 0;
	qglColorTableEXT = 0;
	qglSelectTextureSGIS = 0;
	qglMTexCoord2fSGIS = 0;
#if 1 // real !!!
	qglAlphaFunc                 = 	glAlphaFunc;
	qglArrayElement              = 	glArrayElement;
	qglBegin                     = 	glBegin;
	qglBindTexture               = 	glBindTexture;
	qglBlendFunc                 = 	glBlendFunc;
	qglClear                     = 	glClear;
	qglClearColor                = 	glClearColor;
	qglClearDepth                = 	glClearDepth;
	qglColor3f                   = 	glColor3f;
	qglColor3fv                  = 	glColor3fv;
	qglColor4f                   = 	glColor4f;
	qglColor4fv                  = 	glColor4fv;
	qglColor3ubv                 = 	glColor3ubv;
	qglColor4ubv                 = 	glColor4ubv;
	qglColorPointer              = 	glColorPointer;
	qglCullFace                  = 	glCullFace;
	qglDeleteTextures            = 	glDeleteTextures;
	qglDepthFunc                 = 	glDepthFunc;
	qglDepthMask                 = 	glDepthMask;
	qglDepthRange                = 	glDepthRange;
	qglDisable                   = 	glDisable;
	qglDrawBuffer                = 	glDrawBuffer;
	qglEnable                    = 	glEnable;
	qglEnableClientState         = 	glEnableClientState;
	qglEnd                       = 	glEnd;
	qglFinish                    = 	glFinish;
	qglFrontFace                 = 	glFrontFace;
	qglFrustum                   = 	glFrustum;	
	qglGenTextures               = 	glGenTextures;
	qglGetError                  = 	glGetError;
	qglGetFloatv                 = 	glGetFloatv;
	qglLoadIdentity              = 	glLoadIdentity;
	qglLoadMatrixf               = 	glLoadMatrixf;
	qglMatrixMode                = 	glMatrixMode;
	qglOrtho                     = 	glOrtho;
	qglPointSize                 = 	glPointSize;
	qglPolygonMode               = 	glPolygonMode;
	qglPopMatrix                 = 	glPopMatrix;	
	qglPushMatrix                = 	glPushMatrix;
	//qglReadPixels                =  = glReadPixels; // screenshot
	qglRotatef                   = 	glRotatef;
	qglScalef                    = 	glScalef;
	qglScissor                   = 	glScissor;
	qglShadeModel                = 	glShadeModel;
	qglTexCoord2f                = 	glTexCoord2f;
	qglTexEnvf                   = 	glTexEnvf;
	qglTexImage2D                = 	glTexImage2D;
	qglTexParameterf             = 	glTexParameterf;
	qglTexSubImage2D             = 	glTexSubImage2D;
	qglTranslatef                = 	glTranslatef;
	qglVertex2f                  = 	glVertex2f;
	qglVertex2fv                 = 	glVertex2fv;
	qglVertex3f                  = 	glVertex3f;
	qglVertex3fv                 = 	glVertex3fv;
	qglViewport                  = 	glViewport;
	
	// extentions
	qglVertexPointer             = 	glVertexPointer;
	qglTexCoordPointer           = 	glTexCoordPointer;
	qglColorPointer              = 	glColorPointer;
	qglDisableClientState        = 	glDisableClientState;
	qglEnableClientState         = 	glEnableClientState;
	qglDrawArrays                = 	glDrawArrays;
	/*
	qglPointParameterfEXT = glPointParameterf;
	qglPointParameterfvEXT = glPointParameterfv;
	qglPointSize = glPointSize;
	*/
	qglSelectTextureSGIS = glActiveTexture;
	qglMTexCoord2fSGIS = glMultiTexCoord2f;
#endif	
	qglGetString = glGetString;
	return true;
}

void GLimp_EnableLogging( qboolean enable )
{
	return;
}


void GLimp_LogNewFrame( void )
{
	printf( "*** R_BeginFrame ***\n");
}



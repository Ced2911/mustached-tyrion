/* 
 * File:   xee.h
 * Author: ced
 *
 * Created on 18 octobre 2012, 20:20
 */

#ifndef XEE_H
#define	XEE_H

#ifdef	__cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Vertices
 ******************************************************************************/
void xeeSubmit();
void xeeBegin(GLenum mode);
void xeeEnd();
void xeeVertex3f (GLfloat x, GLfloat y, GLfloat z);
void xeeVertex2fv (const GLfloat *v);
void xeeVertex2f (GLfloat x, GLfloat y);
void xeeVertex3fv (const GLfloat *v);
void xeeTexCoord2f (GLfloat s, GLfloat t);
void xeeTexCoord2fv (const GLfloat *v);


#ifdef	__cplusplus
}
#endif

#endif	/* XEE_H */


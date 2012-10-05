#include "gl_xenos.h"
#include <string.h>
#include <malloc.h>
#include <debug.h>
#include <assert.h>

#define XE_MAX_TEXTURE 50000

glXeSurface_t * glXeSurfaces = NULL;

extern void *Xe_pAlloc(struct XenosDevice *xe, u32 *phys, int size, int align);

#define TEXMIN 255

struct XenosSurface * My_Xe_CreateTexture(struct XenosDevice *xe, unsigned int width, unsigned int height, unsigned int levels, int format, int tiled)
{	
	struct XenosSurface *surface = malloc(sizeof(struct XenosSurface));
	memset(surface, 0, sizeof(struct XenosSurface));
	int bypp = 0;

	switch (format & XE_FMT_MASK)
	{
	case XE_FMT_8: bypp = 1; break;
	case XE_FMT_5551: bypp = 2; break;
	case XE_FMT_565: bypp = 2; break;
	case XE_FMT_8888: bypp = 4; break;
	case XE_FMT_16161616: bypp = 8; break;
	}
	assert(bypp);

	int wpitch = (width * bypp + TEXMIN) &~TEXMIN;
	int hpitch = (height + TEXMIN) &~TEXMIN;

	surface->width = width;
	surface->height = height;
	surface->wpitch = wpitch;
	surface->hpitch = hpitch;
	surface->tiled = tiled;
	surface->format = format;
	surface->ptr_mip = 0;
	surface->bypp = bypp;
    surface->base = Xe_pAlloc(xe, &surface->ptr, hpitch * wpitch, 4096);

    surface->use_filtering = 1;
    surface->u_addressing = XE_TEXADDR_WRAP;
    surface->v_addressing = XE_TEXADDR_WRAP;

	return surface;
}

#define Xe_CreateTexture My_Xe_CreateTexture

static inline void handle_small_surface_u8(struct XenosSurface * surf, void * buffer)
{
	int width;
	int height;
	int wpitch;
	int hpitch;
	int yp,xp,y,x;
	uint8_t * surf_data;
	uint8_t * data;
	uint8_t * src;	

	// don't handle big texture
	if (surf->width>TEXMIN && surf->height>TEXMIN) {
		return;
	}	

	width = surf->width;
	height = surf->height;
	wpitch = surf->wpitch;
	hpitch = surf->hpitch;	

	if(buffer)
        surf_data = (uint8_t *)buffer;
    else
        surf_data = (uint8_t *)Xe_Surface_LockRect(xe, surf, 0, 0, 0, 0, XE_LOCK_WRITE);

	src = data = surf_data;

	for(yp=height; yp<hpitch;yp+=height) {
		int max_h = height;
		if (yp + height> hpitch)
				max_h = hpitch % height;
		for(y = 0; y<max_h; y++){
			//x order
			for(xp = width;xp<wpitch;xp+=width) {
				int max_w = width;
				if (xp + width> wpitch)
					max_w = wpitch % width;

				for(x = 0; x<max_w; x++) {
					data[x+xp + ((y+yp)*wpitch)]=src[x+ (y*wpitch)];
				}
			}
		}
	}

    if(!buffer)
        Xe_Surface_Unlock(xe, surf);
}

static inline void handle_small_surface(struct XenosSurface * surf, void * buffer){
	int width;
	int height;
	int wpitch;
	int hpitch;
	int yp,xp,y,x;
	uint32_t * surf_data;
	uint32_t * data;
	uint32_t * src;	

	// don't handle big texture
	if (surf->width>TEXMIN && surf->height>TEXMIN) {
		return;
	}
	if (surf->bypp == 1) {
		handle_small_surface_u8(surf, buffer);
		return;
	} 
	if (surf->bypp != 4) {
		return;
	}
	

	width = surf->width;
	height = surf->height;
	wpitch = surf->wpitch / 4;
	hpitch = surf->hpitch;	

	if(buffer)
        surf_data = (uint32_t *)buffer;
    else
        surf_data = (uint32_t *)Xe_Surface_LockRect(xe, surf, 0, 0, 0, 0, XE_LOCK_WRITE);

	src = data = surf_data;

	for(yp=height; yp<hpitch;yp+=height) {
		int max_h = height;
		if (yp + height> hpitch)
				max_h = hpitch % height;
		for(y = 0; y<max_h; y++){
			//x order
			for(xp = width;xp<wpitch;xp+=width) {
				int max_w = width;
				if (xp + width> wpitch)
					max_w = wpitch % width;

				for(x = 0; x<max_w; x++) {
					data[x+xp + ((y+yp)*wpitch)]=src[x+ (y*wpitch)];
				}
			}
		}
	}

    if(!buffer)
        Xe_Surface_Unlock(xe, surf);
} 

/***********************************************************************
 * Texture environnement
 ***********************************************************************/

void glTexEnvf (GLenum target, GLenum pname, GLfloat param)
{
	if (target != GL_TEXTURE_ENV)
		xe_gl_error("glTexEnvf: unimplemented target\n");
	
	if (!xeTmus[xeCurrentTMU].boundtexture) return;
	if (!xeTmus[xeCurrentTMU].boundtexture->teximg ) return;
	if (target != GL_TEXTURE_2D) return;
	
	/** Do shader work here !! **/
	switch (pname)
	{
		case GL_TEXTURE_ENV_MODE:
		switch ((GLint)param)
		{
			case GL_REPLACE:
			xeTmus[xeCurrentTMU].texture_env_mode = (int)GL_REPLACE;
			break;

			case GL_MODULATE:
			xeTmus[xeCurrentTMU].texture_env_mode = (int)GL_MODULATE;			
			break;
			
			default:
			xe_gl_error("glTexEnvf: unimplemented param\n");
			break;
		}
	}
}

void glTexEnvi (GLenum target, GLenum pname, GLint param)
{
	
}

/***********************************************************************
 * Create/Gen/Delete images
 ***********************************************************************/
void XeGLInitTextures()
{
	glXeSurfaces = (glXeSurface_t *)malloc(sizeof(glXeSurface_t) * XE_MAX_TEXTURE);
	memset(glXeSurfaces, 0, sizeof(glXeSurface_t) * XE_MAX_TEXTURE);
}
 
 
static int d3d_TextureExtensionNumber = 1;
int xeCurrentTMU = 0;

static void Xe_InitTexture(glXeSurface_t *tex)
{
	tex->glnum = 0;

	if (tex->teximg)
	{
		Xe_DestroyTexture(xe, tex->teximg);
		tex->teximg = NULL;
	}
}

static glXeSurface_t *Xe_AllocTexture(void)
{
	int i = 0;
	glXeSurface_t *tex;

	// find a free texture
	for (i = 0; i< XE_MAX_TEXTURE; i++)
	{
		tex = &glXeSurfaces[i];
		// if either of these are 0 (or NULL) we just reuse it
		if (!tex->teximg)
		{
			Xe_InitTexture(tex);
			return tex;
		}

		if (!tex->glnum)
		{
			Xe_InitTexture(tex);
			return tex;
		}
	}

	xe_gl_error("Xe_AllocTexture: out of textures!!!\n");

	return NULL;
}


static void Xe_ReleaseTextures (void)
{
	glXeSurface_t *tex;
	int i;

	// explicitly NULL all textures and force texparams to dirty
	for (i = 0; i< XE_MAX_TEXTURE; i++)
	{
		tex = &glXeSurfaces[i];
		Xe_InitTexture(tex);
	}
} 
 
void glDeleteTextures(GLsizei n, const GLuint *textures)
{
	int i;
	glXeSurface_t *tex;

	for (i = 0; i < n; i++) {
		for (i = 0; i< XE_MAX_TEXTURE; i++)
		{
			tex = &glXeSurfaces[i];
			
			if (tex->glnum == textures[i]) {
				Xe_InitTexture(tex);
				break;
			}
		}
	}
}

void glGenTextures(GLsizei n, GLuint *textures)
{
	int i;
	
	for(i = 0; i < n; i++)
	{
		glXeSurface_t *tex = Xe_AllocTexture();
		tex->glnum = textures[i] = d3d_TextureExtensionNumber;
		d3d_TextureExtensionNumber++;
	}
}

void glBindTexture(GLenum target, GLuint texture)
{
	int i;
	
	glXeSurface_t *tex;
	if (target != GL_TEXTURE_2D) 
		return;
		
	// no texture
	if (texture == 0) {
		xeTmus[xeCurrentTMU].boundtexture = NULL;
		return;
	}
	xeTmus[xeCurrentTMU].boundtexture = NULL;
	
	// find a texture
	for (i = 0; i< XE_MAX_TEXTURE; i++)
	{
		tex = &glXeSurfaces[i];
		
		if (tex && tex->glnum && tex->glnum == texture)
		{
			xeTmus[xeCurrentTMU].boundtexture = tex;
			break;
		}
	}
	
	// did we find it?
	if (!xeTmus[xeCurrentTMU].boundtexture)
	{
		// nope, so fill in a new one (this will make it work with texture_extension_number)
		// (i don't know if the spec formally allows this but id seem to have gotten away with it...)
		xeTmus[xeCurrentTMU].boundtexture = Xe_AllocTexture();

		// reserve this slot
		xeTmus[xeCurrentTMU].boundtexture->glnum = texture;

		// ensure that it won't be reused
		if (texture > d3d_TextureExtensionNumber)
			d3d_TextureExtensionNumber = texture;
	}
	// this should never happen
	if (!xeTmus[xeCurrentTMU].boundtexture) 
		xe_gl_error("glBindTexture: out of textures!!!\n");
		
	// dirty the params
	xeTmus[xeCurrentTMU].texparamdirty = TRUE;
}

/***********************************************************************
 * Images manipulation
 ***********************************************************************/

void check_format(int srcbytes, int dstbytes) {
	int d = 0;
	
	if (srcbytes == 4) {
		if (dstbytes == 4) {
			d++;
		} else if(dstbytes == 1) {
			d++;
		}
	} else if (srcbytes == 3) {
		if (dstbytes == 4) {
			d++;
		} else if (dstbytes == 1) {
			d++;
		}
	} else if (srcbytes == 1) {
		if (dstbytes == 1) {
			d++;
		} else if (dstbytes == 4) {
			d++;
		}
	}
				
	if (d == 0) {
		printf("Error check that src = %d dst = %d\n", srcbytes, dstbytes);
	}
}

static inline int src_format_to_bypp(GLenum format)
{
	if (format == 1 || format == GL_LUMINANCE)
		return 1;
	else if (format == 3 || format == GL_RGB)
		return 3;
	else if (format == 4 || format == GL_RGBA)
		return 4;
	xe_gl_error ("D3D_FillTextureLevel: illegal format");
	return 0;
}

static inline int dst_format_to_bypp(GLenum format)
{
	if (format == 1 || format == GL_LUMINANCE)
		return 1;
	else if (format == 3 || format == GL_RGB)
		return 4;
	else if (format == 4 || format == GL_RGBA)
		return 4;
	xe_gl_error ("D3D_FillTextureLevel: illegal format");
	return 0;
}

void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels)
{
	if (level > 0)
		return;
	struct XenosSurface * surf = NULL;
	
	if (xeTmus[xeCurrentTMU].boundtexture && xeTmus[xeCurrentTMU].boundtexture->teximg ) {
		surf = xeTmus[xeCurrentTMU].boundtexture->teximg;
	}
	
	int srcbytes = src_format_to_bypp(format);
	int dstbytes = dst_format_to_bypp(xeTmus[xeCurrentTMU].boundtexture->internalformat);
	
	uint8_t * surfbuf = (uint8_t*) Xe_Surface_LockRect(xe, surf, 0, 0, 0, 0, XE_LOCK_WRITE);
	uint8_t * srcdata = (uint8_t*) pixels;
	uint8_t * dstdata = surfbuf;
	
	int y, x;

	int pitch = (width * dstbytes);
	int offset = 0;
	
	check_format(srcbytes, dstbytes);

	for (y = yoffset; y < (yoffset + height); y++) {
		offset = (y * pitch)+(xoffset * dstbytes);

		dstdata = surfbuf + offset;
		for (x = xoffset; x < (xoffset + width); x++) {
			if (srcbytes == 4) {
				if (dstbytes == 4) {
					dstdata[0] = srcdata[3];
					dstdata[3] = srcdata[2];
					dstdata[2] = srcdata[1];
					dstdata[1] = srcdata[0];
				} else if(dstbytes == 1) {
					dstdata[0] = ((int) srcdata[0] + (int) srcdata[1] + (int) srcdata[2] + (int) srcdata[3]) / 3;
				}
					
				srcdata += srcbytes;
				dstdata += dstbytes;
				
			} else if (srcbytes == 3) {
				if (dstbytes == 4) {					
					dstdata[0] = 0xff;
					dstdata[3] = srcdata[2];
					dstdata[2] = srcdata[1];
					dstdata[1] = srcdata[0];
				} else if (dstbytes == 1) {
					dstdata[0] = ((int) srcdata[0] + (int) srcdata[1] + (int) srcdata[2]) / 3;
				}
					
				srcdata += srcbytes;
				dstdata += dstbytes;
			} else if (srcbytes == 1) {
				if (dstbytes == 1) {
					dstdata[0] = srcdata[0];
				} else if (dstbytes == 4) {
					dstdata[0] = srcdata[0];
					dstdata[1] = srcdata[0];
					dstdata[2] = srcdata[0];
					dstdata[3] = srcdata[0];
				}
				srcdata += srcbytes;
				dstdata += dstbytes;
			}
		}
	}
	Xe_Surface_Unlock(xe, surf);
	
	handle_small_surface(surf, NULL);
}

void glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum pixelformat, GLenum type, const GLvoid *pixels)
{
	int format;
	if (type != GL_UNSIGNED_BYTE) {
		xe_gl_error("glTexImage2D: Unrecognised pixel format\n");
	}
	
	if (target != GL_TEXTURE_2D)
		return;
		
	if (!xeTmus[xeCurrentTMU].boundtexture)
		return;
		
	if (level > 0)
		return;
		
	int srcbytes = src_format_to_bypp(pixelformat);
	int dstbytes = 4;
	
	// validate format
	switch (internalformat)
	{
	case 1:
	case GL_LUMINANCE:
		dstbytes = 1;
		format = XE_FMT_8;
		break;
	case 3:
	case GL_RGB:
		dstbytes = 4;
		format = XE_FMT_ARGB|XE_FMT_8888;
		break;
	case 4:
	case GL_RGBA:
		dstbytes = 4;
		format = XE_FMT_ARGB|XE_FMT_8888;
		break;
	default:
		xe_gl_error ("invalid texture internal format\n");
		return;
	}
	
	struct XenosSurface * surf = Xe_CreateTexture(xe, width, height, 0, format, 0);
	memset(surf->base, 0xFF, surf->wpitch * surf->hpitch);
	
	xeTmus[xeCurrentTMU].boundtexture->teximg = surf;
	xeTmus[xeCurrentTMU].boundtexture->internalformat = internalformat;
		
	uint8_t * surfbuf = (uint8_t*) Xe_Surface_LockRect(xe, surf, 0, 0, 0, 0, XE_LOCK_WRITE);
	uint8_t * srcdata = (uint8_t*) pixels;
	uint8_t * dstdata = surfbuf;
	int y, x;
	
	check_format(srcbytes, dstbytes);

	for (y = 0; y <height; y++) {
		dstdata = surfbuf + (y * (width * dstbytes));
		for (x = 0; x < width; x++) {
			if (srcbytes == 4) {
				if (dstbytes == 4) {
					dstdata[0] = srcdata[3];
					dstdata[3] = srcdata[2];
					dstdata[2] = srcdata[1];
					dstdata[1] = srcdata[0];
				} else if(dstbytes == 1) {
					dstdata[0] = ((int) srcdata[0] + (int) srcdata[1] + (int) srcdata[2] + (int) srcdata[3]) / 3;
				}
					
				srcdata += srcbytes;
				dstdata += dstbytes;
				
			} else if (srcbytes == 3) {
				if (dstbytes == 4) {		
					dstdata[0] = 0xff;
					dstdata[3] = srcdata[2];
					dstdata[2] = srcdata[1];
					dstdata[1] = srcdata[0];
				} else if (dstbytes == 1) {
					dstdata[0] = ((int) srcdata[0] + (int) srcdata[1] + (int) srcdata[2]) / 3;
				}
					
				srcdata += srcbytes;
				dstdata += dstbytes;
			} else if (srcbytes == 1) {
				if (dstbytes == 1) {
					dstdata[0] = srcdata[0];
				} else if (dstbytes == 4) {
					dstdata[0] = srcdata[0];
					dstdata[1] = srcdata[0];
					dstdata[2] = srcdata[0];
					dstdata[3] = srcdata[0];
				}
				srcdata += srcbytes;
				dstdata += dstbytes;
			}
		}
	}
	
	printf("w: %d - h : %d - s : %d - d : %d\n", width, height, pixelformat, internalformat);
	
	Xe_Surface_Unlock(xe, surf);
	handle_small_surface(surf, NULL);
}

/** Not used in QII */
void glGetTexImage (GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels)
{
	
}

/***********************************************************************
 * Images parameters
 ***********************************************************************/
 
#define XE_TEXF_NONE	2
#define XE_TEXF_POINT 0
#define XE_TEXF_LINEAR 1
#define XE_TEXF_ANISOTROPIC 4

void glTexParameterf (GLenum target, GLenum pname, GLfloat param)
{
	if (!xeTmus[xeCurrentTMU].boundtexture) return;
	if (!xeTmus[xeCurrentTMU].boundtexture->teximg ) return;
	if (target != GL_TEXTURE_2D) return;

	xeTmus[xeCurrentTMU].texparamdirty = TRUE;

	switch (pname)
	{
	case GL_TEXTURE_MIN_FILTER:
		if ((int) param == GL_NEAREST_MIPMAP_NEAREST)
		{
			xeTmus[xeCurrentTMU].boundtexture->teximg->use_filtering = XE_TEXF_POINT;
			xeTmus[xeCurrentTMU].boundtexture->teximg->use_filtering = XE_TEXF_POINT;
		}
		else if ((int) param == GL_LINEAR_MIPMAP_NEAREST)
		{
			xeTmus[xeCurrentTMU].boundtexture->teximg->use_filtering = XE_TEXF_LINEAR;
			xeTmus[xeCurrentTMU].boundtexture->teximg->use_filtering = XE_TEXF_POINT;
		}
		else if ((int) param == GL_NEAREST_MIPMAP_LINEAR)
		{
			xeTmus[xeCurrentTMU].boundtexture->teximg->use_filtering = XE_TEXF_POINT;
			xeTmus[xeCurrentTMU].boundtexture->teximg->use_filtering = XE_TEXF_LINEAR;
		}
		else if ((int) param == GL_LINEAR_MIPMAP_LINEAR)
		{
			xeTmus[xeCurrentTMU].boundtexture->teximg->use_filtering = XE_TEXF_LINEAR;
			xeTmus[xeCurrentTMU].boundtexture->teximg->use_filtering = XE_TEXF_LINEAR;
		}
		else if ((int) param == GL_LINEAR)
		{
			xeTmus[xeCurrentTMU].boundtexture->teximg->use_filtering = XE_TEXF_LINEAR;
			xeTmus[xeCurrentTMU].boundtexture->teximg->use_filtering = XE_TEXF_NONE;
		}
		else
		{
			// GL_NEAREST
			xeTmus[xeCurrentTMU].boundtexture->teximg->use_filtering = XE_TEXF_POINT;
			xeTmus[xeCurrentTMU].boundtexture->teximg->use_filtering = XE_TEXF_NONE;
		}
		break;

	case GL_TEXTURE_MAG_FILTER:
		if ((int) param == GL_LINEAR)
			xeTmus[xeCurrentTMU].boundtexture->teximg->use_filtering = XE_TEXF_LINEAR;
		else xeTmus[xeCurrentTMU].boundtexture->teximg->use_filtering = XE_TEXF_POINT;
		break;

	case GL_TEXTURE_WRAP_S:
		if ((int) param == GL_CLAMP)
			xeTmus[xeCurrentTMU].boundtexture->teximg->u_addressing = XE_TEXADDR_CLAMP;
		else xeTmus[xeCurrentTMU].boundtexture->teximg->u_addressing = XE_TEXADDR_WRAP;
		break;

	case GL_TEXTURE_WRAP_T:
		if ((int) param == GL_CLAMP)
			xeTmus[xeCurrentTMU].boundtexture->teximg->v_addressing = XE_TEXADDR_CLAMP;
		else xeTmus[xeCurrentTMU].boundtexture->teximg->v_addressing = XE_TEXADDR_WRAP;
		break;

	default:
		break;
	}
}

 
void glTexParameteri (GLenum target, GLenum pname, GLint param)
{
	glTexParameterf (target, pname, param);
}

void glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params)
{
	
}



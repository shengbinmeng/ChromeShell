#ifndef __LENTPDEC_H__
#define __LENTPDEC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifndef LENTAPI
	#if defined(_WIN32) || defined(WIN32)
		#define LENTAPI __stdcall
	#else
		#define LENTAPI
	#endif
#endif

#ifndef LENTPCOLORSPACE_DEFINED
#define LENTPCOLORSPACE_DEFINED
enum LENTPCOLORSPACE {
	/* Invalid color space */
	LENTPCS_NULL      = 0x00,
	/* YUV color space */
	LENTPCS_GRAYSCALE = 0x01,
	LENTPCS_YUV420    = 0x02,
	LENTPCS_YUV422    = 0x03,
	LENTPCS_YUV444    = 0x04,
	LENTPCS_YUVA420   = 0x11,
	/* RGB color space */
	LENTPCS_RGB       = 0x21,
	LENTPCS_BGR       = 0x22,
	LENTPCS_RGB565LE  = 0x31,
	LENTPCS_RGB565BE  = 0x32,
	LENTPCS_RGBA      = 0x41,
	LENTPCS_BGRA      = 0x42,
	LENTPCS_ARGB      = 0x43,
	LENTPCS_ABGR      = 0x44,
	LENTPCS_RGBA4444LE= 0x51,
	LENTPCS_RGBA4444BE= 0x52,
	LENTPCS_ARGB4444LE= 0x53,
	LENTPCS_ARGB4444BE= 0x54,
	LENTPCS_RGBX      = 0x61,
	LENTPCS_BGRX      = 0x62,
	LENTPCS_XRGB      = 0x63,
	LENTPCS_XBGR      = 0x64,
	/* Coded data */
	LENTPCS_LENTP     = 0x7f
};
#endif

#ifndef LENTPINFO_DEFINED
#define LENTPINFO_DEFINED
struct LENTPINFO {
	int32_t size;   /* size in byte of this struct, initialize by caller for extendibility */
	int32_t version;/* 2bits */
	int32_t alpha;	/* have Alpha channel */
	int32_t width;	/* max 24bit */
	int32_t height;	/* max 24bit */
};
#endif

#ifndef LENTPDECPARAM_DEFINED
#define LENTPDECPARAM_DEFINED
#define LENTPDECPARAM_FLAG_DITHER	0x1 /* for rgb color space which channel bit depth less than 8 */
#define LENTPDECPARAM_FLAG_PREMULTIPLY	0x2 /* for color space with alpha channel */
#define LENTPDECPARAM_FLAG_DISABLEASM	0x10000 /* disable all assembler optimizations */
#define LENTPDECPARAM_SCALE_DEFAULT	 0
#define LENTPDECPARAM_SCALE_NEAREST	 1
#define LENTPDECPARAM_SCALE_BILINEAR 2
#define LENTPDECPARAM_SCALE_AREA     3
struct LENTPDECPARAM {
	int32_t size; /* size in byte of this struct, initialize by caller for extendibility */
	int32_t out_color_space; /* output picture's color space */
	uint32_t flags;
	int32_t out_width;
	int32_t out_height;
	int32_t scaling_method;
};
#endif


/* 
 * Get version of this library 
 */
uint32_t LENTAPI lentpdec_version(void);


/* 
 * Get picture info from picture header
 * return the bit count read from data if success, otherwith return a negative number
 */
int32_t LENTAPI lentpdec_getinfo(const uint8_t *data, size_t data_size, struct LENTPINFO *info);


/* 
 * Decode one picture
 * param:
 *     lentp_buf.......Buffer contains the input LentP image data
 *     lentp_size......Data size of the input LentP image
 *     param...........Decoding parameters
 *     out_plane.......Buffers of each bit-planes for output image data.
 *     out_stride......Line stride of each bit-plane
 * return:
 *     0: succeeded
 *     !=0: failed
 */
int32_t LENTAPI lentpdec_decode(const uint8_t *lentp_buf, size_t lentp_size,
                                struct LENTPDECPARAM *param,
                                uint8_t **out_plane, int32_t *out_stride);






/*****************************************************************************
 * Incremental decoding                                                      *
 *****************************************************************************/


/*
 * Incremental decoder context or handle
 */
typedef void* lentpdec_ctx;

/*
 * Create incremental decoder
 */
int32_t LENTAPI lentpdec_inc_new(struct LENTPDECPARAM *param, lentpdec_ctx *ctx);

/*
 * Append data to the incremental decoder
 * Decoder will try to decode the append data. If some new scan line become
 * available, you can call lentpdec_inc_getlines to get it later
 */
int32_t LENTAPI lentpdec_inc_append(lentpdec_ctx ctx, const uint8_t *data, size_t data_size);

/*
 * Get dimension if available
 */
int32_t LENTAPI lentpdec_inc_getdimension(lentpdec_ctx ctx, int32_t *width, int32_t *height);

/*
 * Get output scan lines
 * the plane specify the line buffers of each bit plane, and the stride specify
 * the line stride of each bit plane.
 * max_lines specify the max lines got from decoder, the line buffer shuld large
 * enough to store max_lines lines data
 * got_lines return the actual lines read from decoder successfully
 */
int32_t LENTAPI lentpdec_inc_getlines(lentpdec_ctx ctx, uint8_t **plane, int32_t *stride, int32_t max_lines, int32_t *got_lines);

/*
 * Delete incremental decoder
 */
void LENTAPI lentpdec_inc_del(lentpdec_ctx ctx);




#ifdef __cplusplus
}
#endif

#endif/* __LENTPDEC_H__ */

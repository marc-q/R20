#ifndef __R20_BMP_H__
#define __R20_BMP_H__

#define BMP_MAGIC 19778

#define BMP_GET_PADDING(a) ((a)%4)

struct _bmp_header
{
	unsigned int bfSize;
	unsigned int bfReserved;
	unsigned int bfOffBits;
	unsigned int biSize;
	int biWidth;
	int biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	int biXPelsPerMeter;
	int biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
};

typedef struct _bmp_header bmp_header;

struct _bmp_pixel
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};

typedef struct _bmp_pixel bmp_pixel;

void bmp_header_init_df (bmp_header*, int, int);
void bmp_pixel_init (bmp_pixel*, unsigned char, unsigned char, unsigned char);
short bmp_write_img (char*, bmp_pixel**, int, int);

#endif /* __R20_BMP_H__ */

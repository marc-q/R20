/* Copyright 2016 Marc Volker Dickmann */
#include <stdio.h>
#include <stdlib.h>
#include "r20_bmp.h"

void bmp_header_init_df (bmp_header *header, int width, int height)
{
	header->bfSize = sizeof (bmp_pixel) * (width * height);
	header->bfReserved = 0;
	header->bfOffBits = 54;
	header->biSize = 40;
	header->biWidth = width;
	header->biHeight = height;
	header->biPlanes = 1;
	header->biBitCount = 24;
	header->biCompression = 0;
	header->biSizeImage = 0;
	header->biXPelsPerMeter = 0;
	header->biYPelsPerMeter = 0;
	header->biClrUsed = 0;
	header->biClrImportant = 0;
}

void bmp_pixel_init (bmp_pixel *pxl, unsigned char red, unsigned char green, unsigned char blue)
{
	pxl->red = red;
	pxl->green = green;
	pxl->blue = blue;
}

short bmp_write_img (char *filename, bmp_pixel **pxls, int width, int height)
{
	unsigned int x, y;
	unsigned short magic;
	FILE *img_file;
	bmp_header header;
	
	magic = BMP_MAGIC;
	img_file = fopen (filename, "wb");
	
	if (img_file == NULL)
	{
		return -1;
	}
	
	bmp_header_init_df (&header, width, height);
	
	fwrite (&magic, sizeof (magic), 1, img_file);
	fwrite (&header, sizeof (header), 1, img_file);
	
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			fwrite (&pxls[y][x], sizeof (bmp_pixel), 1, img_file);
		}
	}
	
	fclose (img_file);
	
	return 0;
}

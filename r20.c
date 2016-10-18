/* Copyright 2016 Marc Volker Dickmann */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "lib/libbmp.h"
#include "src/r20_math.h"
#include "src/r20_shader.h"
#include "src/r20_plane.h"

#define FENCE_HEIGHT 50.0
#define MATS_AMNT 2
#define LIGHTS_AMNT 4
#define MODELS_AMNT 10

#define MODEL_PLANE 0
#define MODEL_CUBE 1
#define MODEL_PATH 2
#define MODEL_FENCE 3

/* +------------------------------------+
   |		 TEXTURES		|
   +------------------------------------+*/

char texture_gen_base (obj_texturedata *td)
{
	if (td->type == 0)
	{
		bmp_pixel_init (td->pxl, 64, 64, 64);
	}
	
	return 0;
}

/* WOODEN */
char texture_gen_woodenplanksx (obj_texturedata *td)
{
	if (td->type == 0)
	{
		if (td->x % 16 == 0 || rand () % 100 == 0)
		{
			bmp_pixel_init (td->pxl, 16, 16, 16);
		}
		else if (td->x % 32 <= 16)
		{
			bmp_pixel_init (td->pxl, 48, 32, 16);
		}
		else
		{
			bmp_pixel_init (td->pxl, 32, 16, 8);
		}
	}
	
	return 0;
}

char texture_gen_woodenplanksy (obj_texturedata *td)
{
	if (td->type == 0)
	{
		if (td->y % 16 == 0 || rand () % 100 == 0)
		{
			bmp_pixel_init (td->pxl, 16, 16, 16);
		}
		else if (td->y % 32 <= 16)
		{
			bmp_pixel_init (td->pxl, 48, 32, 16);
		}
		else
		{
			bmp_pixel_init (td->pxl, 32, 16, 8);
		}
	}
	
	return 0;
}

char texture_gen_woodenplanksfloor (obj_texturedata *td)
{
	if (td->type == 0)
	{
		if (td->x % 16 == 0 || td->y % 64 == 0)
		{
			bmp_pixel_init (td->pxl, 16, 16, 16);
		}
		else if (td->x % 32 <= 16 && td->y % 128 <= 64 ||
			 td->x % 32 > 16 && td->y % 128 > 64)
		{
			bmp_pixel_init (td->pxl, 48, 32, 16);
		}
		else
		{
			bmp_pixel_init (td->pxl, 32, 16, 8);
		}
	}
	
	return 0;
}

/* STONE */
char texture_gen_rndstone (obj_texturedata *td)
{
	if (td->type == 0)
	{
		if (rand () % 48 == 0)
		{
			bmp_pixel_init (td->pxl, 16, 16, 16);
		}
		else
		{
			bmp_pixel_init (td->pxl, 32, 32, 32);
		}
	}
	
	return 0;
}

char texture_gen_stonetiles (obj_texturedata *td)
{
	if (td->type == 0)
	{
		if (td->x % 16 == 0 || td->y % 16 == 0 || rand () % 100 == 0)
		{
			bmp_pixel_init (td->pxl, 16, 16, 16);
		}
		else if (td->x % 32 <= 16 && td->y % 32 <= 16)
		{
			bmp_pixel_init (td->pxl, 48, 48, 48);
		}
		else
		{
			bmp_pixel_init (td->pxl, 32, 32, 32);
		}
	}
	
	return 0;
}

char texture_gen_stonetilesb (obj_texturedata *td)
{
	if (td->type == 0)
	{
		if (td->x % 16 == 0 || td->z % 16 == 0 || rand () % 100 == 0)
		{
			bmp_pixel_init (td->pxl, 16, 16, 16);
		}
		else if (td->x % 32 <= 16 && td->z % 32 <= 16)
		{
			bmp_pixel_init (td->pxl, 48, 48, 48);
		}
		else
		{
			bmp_pixel_init (td->pxl, 32, 32, 32);
		}
	}
	
	return 0;
}

/* Glass */
char texture_gen_glasstilesx (obj_texturedata *td)
{
	if (td->type == 0)
	{
		if (td->x%64 == 0 || td->z%64 == 0)
		{
			bmp_pixel_init (td->pxl, td->pxl->red+40, td->pxl->green+40, td->pxl->blue+40);
		}
		else
		{
			bmp_pixel_init (td->pxl, td->pxl->red+10, td->pxl->green+10, td->pxl->blue+10);
		}
	}
	
	return 0;
}

char texture_gen_glasstilesy (obj_texturedata *td)
{
	if (td->type == 0)
	{
		if (td->y%64 == 0 || td->z%64 == 0)
		{
			bmp_pixel_init (td->pxl, td->pxl->red+40, td->pxl->green+40, td->pxl->blue+40);
		}
		else
		{
			bmp_pixel_init (td->pxl, td->pxl->red+10, td->pxl->green+10, td->pxl->blue+10);
		}
	}
	
	return 0;
}

/* Nature */
char texture_gen_rndgrass (obj_texturedata *td)
{
	int r;
	
	if (td->type == 0)
	{
		r = rand () % 16;
		bmp_pixel_init (td->pxl, 16+r, 32+r, 16+r);
	}
	
	return 0;
}

char texture_gen_rndsand (obj_texturedata *td)
{
	int r;
	
	if (td->type == 0)
	{
		r = rand () % 16;
	
		if (rand () % 128 == 0)
		{
			bmp_pixel_init (td->pxl, 64+r, 64+r, 64+r);
		}
		else
		{
			bmp_pixel_init (td->pxl, 128+r, 100+r, 16+r);
		}
	}
	
	return 0;
}

/* +------------------------------------+
   |		 MODELS 		|
   +------------------------------------+*/

static void r20_models_free (obj_model *models, unsigned int models_amnt)
{
	unsigned int i;
	
	for (i = 0; i < models_amnt; i++)
	{
		free (models[i].planes);
	}
}

/* Plane */
static void r20_model_plane_init (obj_model *model, shader_material *mat, unsigned int m_width, unsigned int m_height, float x, float y, float z, char rot)
{
	model->id = MODEL_PLANE;
	model->amnt = 1;
	model->planes = (obj_plane*) malloc (sizeof (obj_plane) * model->amnt);
	
	obj_plane_init (&model->planes[0], mat, m_width, m_height, rot, x, y, z);
}

static void r20_model_plane_render (obj_model *model, obj_model *models, unsigned int models_amnt, obj_light *lights, unsigned int lights_amnt, bmp_pixel **pxls, int width, int height, vectorf *cam, char texture_gen (obj_texturedata*))
{
	if (model->id == MODEL_PLANE)
	{
		obj_plane_render (&model->planes[0], models, models_amnt, lights, lights_amnt, pxls, width, height, cam, texture_gen);
	}
}

/* Cube */
static void r20_model_cube_init (obj_model *model, shader_material *mats, unsigned int m_width, unsigned int m_height, float x, float y, float z)
{
	model->id = MODEL_CUBE;
	model->amnt = 6;
	model->planes = (obj_plane*) malloc (sizeof (obj_plane) * model->amnt);
	
	/* Bottom */
	obj_plane_init (&model->planes[0], &mats[0], m_width, m_height, ROT_NONE, x, y, z);
	
	/* Back */
	obj_plane_init (&model->planes[1], &mats[0], m_width, m_height, ROT_A, z, x, y+m_height);
	
	/* Left */
	obj_plane_init (&model->planes[2], &mats[0], m_width, m_height, ROT_B, z, y, x);
	
	/* Right */
	obj_plane_init (&model->planes[3], &mats[0], m_width, m_height, ROT_B, z, y, x+m_width);
	
	/* Front */
	obj_plane_init (&model->planes[4], &mats[0], m_width, m_height, ROT_A, z, x, y);
	
	/* Top */
	obj_plane_init (&model->planes[5], &mats[0], m_width, m_height, ROT_NONE, x, y, z+m_height-1);
}

static void r20_model_cube_render (obj_model *model, obj_model *models, unsigned int models_amnt, obj_light *lights, unsigned int lights_amnt, bmp_pixel **pxls, int width, int height, vectorf *cam)
{
	if (model->id == MODEL_CUBE)
	{
		obj_plane_render (&model->planes[0], models, models_amnt, lights, lights_amnt, pxls, width, height, cam, texture_gen_stonetilesb);
		obj_plane_render (&model->planes[1], models, models_amnt, lights, lights_amnt, pxls, width, height, cam, texture_gen_stonetilesb);
		obj_plane_render (&model->planes[2], models, models_amnt, lights, lights_amnt, pxls, width, height, cam, texture_gen_stonetilesb);
		obj_plane_render (&model->planes[3], models, models_amnt, lights, lights_amnt, pxls, width, height, cam, texture_gen_stonetilesb);
		obj_plane_render (&model->planes[4], models, models_amnt, lights, lights_amnt, pxls, width, height, cam, texture_gen_stonetilesb);
		obj_plane_render (&model->planes[5], models, models_amnt, lights, lights_amnt, pxls, width, height, cam, texture_gen_stonetilesb);
	}
}

/* Fence */
static void r20_model_fence_init (obj_model *model, shader_material *mats, unsigned int m_width, unsigned int m_height, float x, float y, float z, char rot, int thigness)
{
	model->id = MODEL_FENCE;
	model->amnt = 3;
	model->planes = (obj_plane*) malloc (sizeof (obj_plane) * model->amnt);
	
	obj_plane_init (&model->planes[0], &mats[0], m_height, m_width, rot, z, x, y);
	obj_plane_init (&model->planes[1], &mats[0], m_height, m_width, rot, z, x, y+thigness);
	obj_plane_init (&model->planes[2], &mats[0], (rot == ROT_A ? m_width : thigness), (rot == ROT_B ? m_width : thigness), ROT_NONE, (rot == ROT_A ? x : y), (rot == ROT_A ? y : x), z+m_height);
}

static void r20_model_fence_render (obj_model *model, obj_model *models, unsigned int models_amnt, obj_light *lights, unsigned int lights_amnt, bmp_pixel **pxls, int width, int height, vectorf *cam)
{
	if (model->id == MODEL_FENCE)
	{
		obj_plane_render (&model->planes[0], models, models_amnt, lights, lights_amnt, pxls, width, height, cam, (model->planes[0].rotation == ROT_A ? texture_gen_woodenplanksx : texture_gen_woodenplanksy));
		obj_plane_render (&model->planes[1], models, models_amnt, lights, lights_amnt, pxls, width, height, cam, (model->planes[1].rotation == ROT_A ? texture_gen_glasstilesx : texture_gen_glasstilesy));
		obj_plane_render (&model->planes[2], models, models_amnt, lights, lights_amnt, pxls, width, height, cam, texture_gen_stonetiles);
	}
}

/* Path */
static void r20_model_path_init (obj_model *model, shader_material *mats, unsigned int m_width, unsigned int m_height, float x, float y, float z, char rot, int thigness)
{
	model->id = MODEL_PATH;
	model->amnt = 7;
	model->planes = (obj_plane*) malloc (sizeof (obj_plane) * model->amnt);
	
	obj_plane_init (&model->planes[0], &mats[0], (rot == ROT_A ? m_height : m_width), (rot == ROT_B ? m_height : m_width), ROT_NONE, (rot == ROT_A ? x : y), (rot == ROT_A ? y : x), z);
	
	obj_plane_init (&model->planes[1], &mats[1], FENCE_HEIGHT, m_height, rot, z, x, y+m_width);
	obj_plane_init (&model->planes[2], &mats[1], FENCE_HEIGHT, m_height, rot, z, x, y+thigness+m_width);
	obj_plane_init (&model->planes[3], &mats[0], (rot == ROT_A ? m_height : thigness), (rot == ROT_B ? m_height : thigness), ROT_NONE, (rot == ROT_A ? x : y+m_width), (rot == ROT_A ? y+m_width : x), z+FENCE_HEIGHT);
	
	obj_plane_init (&model->planes[4], &mats[1], FENCE_HEIGHT, m_height, rot, z, x, y);
	obj_plane_init (&model->planes[5], &mats[1], FENCE_HEIGHT, m_height, rot, z, x, y+thigness);
	obj_plane_init (&model->planes[6], &mats[0], (rot == ROT_A ? m_height : thigness), (rot == ROT_B ? m_height : thigness), ROT_NONE, (rot == ROT_A ? x : y), (rot == ROT_A ? y : x), z+FENCE_HEIGHT);
}

static void r20_model_path_render (obj_model *model, obj_model *models, unsigned int models_amnt, obj_light *lights, unsigned int lights_amnt, bmp_pixel **pxls, int width, int height, vectorf *cam)
{
	if (model->id == MODEL_PATH)
	{
		obj_plane_render (&model->planes[0], models, models_amnt, lights, lights_amnt, pxls, width, height, cam, texture_gen_stonetiles);
		
		obj_plane_render (&model->planes[1], models, models_amnt, lights, lights_amnt, pxls, width, height, cam, (model->planes[1].rotation == ROT_A ? texture_gen_woodenplanksx : texture_gen_woodenplanksy));
		obj_plane_render (&model->planes[2], models, models_amnt, lights, lights_amnt, pxls, width, height, cam, (model->planes[2].rotation == ROT_A ? texture_gen_woodenplanksx : texture_gen_woodenplanksy));
		obj_plane_render (&model->planes[3], models, models_amnt, lights, lights_amnt, pxls, width, height, cam, (model->planes[5].rotation == ROT_A ? texture_gen_woodenplanksx : texture_gen_woodenplanksy));
		
		obj_plane_render (&model->planes[4], models, models_amnt, lights, lights_amnt, pxls, width, height, cam, (model->planes[4].rotation == ROT_A ? texture_gen_woodenplanksx : texture_gen_woodenplanksy));
		obj_plane_render (&model->planes[5], models, models_amnt, lights, lights_amnt, pxls, width, height, cam, (model->planes[5].rotation == ROT_A ? texture_gen_woodenplanksx : texture_gen_woodenplanksy));
		obj_plane_render (&model->planes[6], models, models_amnt, lights, lights_amnt, pxls, width, height, cam, (model->planes[5].rotation == ROT_A ? texture_gen_woodenplanksx : texture_gen_woodenplanksy));
	}
}

/* +------------------------------------+
   |		 RENDER 		|
   +------------------------------------+*/

static void r20_tst_space (int width, int height)
{
	unsigned int x, y;
	char color;
	bmp_img img;
	vectorf cam;
	shader_material mats[MATS_AMNT];
	obj_light *lights;
	obj_model models[MODELS_AMNT];
	
	srand (time (NULL));
	
	bmp_img_init_df (&img, width, -height);
	
	color = 0;
	
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			if (((x*x)+(y*y))%(800*800) == 0)
			{
				color = (color + 1)%200;
			}
			
			if (rand () % 256 == 0)
			{
				bmp_pixel_init (&img.img_pixels[y][x], 128, 100, 16);
			}
			else
			{
				bmp_pixel_init (&img.img_pixels[y][x], 10+color, 10+color, 30+color);
			}
		}
	}
	
	vectorf_init (&cam, 1.0, 1.0, 1.0);
	
	/* Lights */
	lights = (obj_light*) malloc (sizeof (obj_light) * LIGHTS_AMNT);
	
	obj_light_init (&lights[0], 50.0, 1.0, 1.0, 1.0, 1.0, 512.0, 512.0, 512.0);
	obj_light_init (&lights[1], 1.0, 0.0, 1.0, 1.0, 0.7, 256.0, 512.0, 51.0);
	obj_light_init (&lights[2], 1.0, 0.0, 0.7, 0.5, 0.7, 1512.0, 512.0, 51.0);
	obj_light_init (&lights[3], 1.0, 0.0, 0.4, 0.7, 1.0, 1024.0, 512.0, 51.0);
	
	/* Materials */
	shader_material_init (&mats[0], 0.5, 0.20, 0.50, 1.0);
	shader_material_init (&mats[1], 0.5, 0.70, 0.10, 1.0);
	
	/* Base */
	r20_model_plane_init (&models[0], &mats[0], 462, height, 0.0, 0.0, 1.0, ROT_NONE);
	r20_model_plane_init (&models[1], &mats[0], width-462, height, 462.0, 0.0, 1.0, ROT_NONE);
	
	/* Fences */
	r20_model_fence_init (&models[2], mats, width, 512, 0.0, height, 1.0, ROT_A, 5);
	r20_model_fence_init (&models[3], mats, width, 512, 0.0, height, 1.0, ROT_B, 5);
	
	/* Cubes */
	r20_model_cube_init (&models[4], mats, 100, 100, 1000.0, 1536, 200.0);
	r20_model_cube_init (&models[5], mats, 100, 100, 850.0, 1536, 150.0);
	r20_model_cube_init (&models[6], mats, 100, 100, 700.0, 1536, 100.0);
	
	/* Paths */
	r20_model_path_init (&models[7], mats, 100, width-512, 462.0, 462.0, 1.0, ROT_B, 5);
	r20_model_path_init (&models[8], mats, 100, height-562, 562.0, 462.0, 1.0, ROT_A, 5);
	r20_model_path_init (&models[9], mats, 100, 462, 0.0, 462.0, 1.0, ROT_B, 5);
	
	/* Rendering */
	
	/* TODO: Maybe make it possible to render this using the loop! */
	r20_model_plane_render (&models[0], models, MODELS_AMNT, lights, LIGHTS_AMNT, img.img_pixels, width, height, &cam, texture_gen_rndsand);
	r20_model_plane_render (&models[1], models, MODELS_AMNT, lights, LIGHTS_AMNT, img.img_pixels, width, height, &cam, texture_gen_rndgrass);
	
	for (x = 2; x < MODELS_AMNT; x++)
	{
		switch (models[x].id)
		{
			case MODEL_CUBE:
				r20_model_cube_render (&models[x], models, MODELS_AMNT, lights, LIGHTS_AMNT, img.img_pixels, width, height, &cam);
				break;
			case MODEL_PATH:
				r20_model_path_render (&models[x], models, MODELS_AMNT, lights, LIGHTS_AMNT, img.img_pixels, width, height, &cam);
				break;
			case MODEL_FENCE:
				r20_model_fence_render (&models[x], models, MODELS_AMNT, lights, LIGHTS_AMNT, img.img_pixels, width, height, &cam);
				break;
			default:
				printf ("ERROR: Model unknown (%i)!\n", models[x].id);
				break;
		}
	}
	
	/* Write the image file */
	bmp_img_write (&img, "test.bmp");
	bmp_img_free (&img);

	/* Cleaning */
	r20_models_free (models, MODELS_AMNT);
	free (lights);
}

int main (int argc, char *argv[])
{
	printf ("R20 v. 0.0.1 A (c) 2016 Marc Volker Dickmann\n");
	
	r20_tst_space (2048, 2048);
	
	return 0;
}

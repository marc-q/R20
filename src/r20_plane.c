/* Copyright 2016 Marc Volker Dickmann */
#include <stdio.h>
#include <stdbool.h>
#include "r20_math.h"
#include "r20_bmp.h"
#include "r20_shader.h"
#include "r20_plane.h"

void obj_texturedata_init (obj_texturedata *td, bmp_pixel *pxl, int x, int y, int z, char type)
{
	td->pxl = pxl;
	td->x = x;
	td->y = y;
	td->z = z;
	td->type = type;
}

bool obj_model_check_shadow (obj_model *models, unsigned int models_amnt, vectorf *opos)
{
	unsigned int i, j;
	
	/* TODO: Use vector math for that! */	
	for (i = 0; i < models_amnt; i++)
	{
		for (j = 0; j < models[i].amnt; j++)
		{
			if (models[i].planes[j].rotation == ROT_NONE &&
			    opos->z < models[i].planes[j].pos.z && 
			    opos->x >= models[i].planes[j].pos.x && opos->x <= models[i].planes[j].pos.x+models[i].planes[j].width &&
			    opos->y >= models[i].planes[j].pos.y && opos->y <= models[i].planes[j].pos.y+models[i].planes[j].height)
			{
				return true;
			}
		}
	}
	
	return false;
}

void obj_plane_init (obj_plane *p, shader_material *mat, int width, int height, char rotation, float x, float y, float z)
{
	p->mat = mat;
	p->width = width;
	p->height = height;
	p->rotation = rotation;
	
	vectorf_init (&p->pos, x, y, z);
}

void obj_plane_render (obj_plane *p, obj_model *models, unsigned int models_amnt, obj_light *lights, unsigned int lights_amnt, bmp_pixel **pxls, int width, int height, vectorf *cam, char texture_gen (obj_texturedata*))
{
	unsigned int x, y;
	vectorf pos, t;
	obj_texturedata td;
	
	for (y = p->pos.y; y < p->pos.y+p->height; y++)
	{
		for (x = p->pos.x; x < p->pos.x+p->width; x++)
		{
			switch (p->rotation)
			{
				case ROT_A:
					vectorf_init (&t, y, p->pos.z, x);
					break;
				case ROT_B:
					vectorf_init (&t, p->pos.z, y, x);
					break;
				case ROT_NONE:
				default:
					vectorf_init (&t, x, y, p->pos.z);
					break;
			}
			
			obj_texturedata_init (&td, &pxls[(int)pos.y][(int)pos.x], (int)t.x, (int)t.y, (int)t.z, 1);
			texture_gen (&td);
			
			vectorf_init (&t, td.x, td.y, td.z);
			
			pos = vectorf_to_twod (*cam, t, width, height);
			
			if (pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height)
			{
				obj_texturedata_init (&td, &pxls[(int)pos.y][(int)pos.x], (int)t.x, (int)t.y, (int)t.z, 0);
				
				if (texture_gen (&td) == 0 && obj_model_check_shadow (models, models_amnt, &t) == false)
				{
					vectorf_init (&t, td.x, td.y, td.z);
					obj_lights_render (lights, lights_amnt, p->mat, cam, &t, &pxls[(int)pos.y][(int)pos.x]);
				}
			}	
		}
	}
}

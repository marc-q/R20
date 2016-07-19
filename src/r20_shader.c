/* Copyright 2016 Marc Volker Dickmann */
#include <stdio.h>
#include <math.h>
#include "r20_math.h"
#include "r20_bmp.h"
#include "r20_shader.h"

/* Light */
void shader_color_init (shader_color *scolor, float red, float green, float blue)
{
	scolor->red = red;
	scolor->green = green;
	scolor->blue = blue;
}

void shader_material_init (shader_material *mat, float kambient, float kdiffus, float kspecular)
{
	mat->kambient = kambient;
	mat->kdiffus = kdiffus;
	mat->kspecular = kspecular;
}

/* Shader - Phong */
double shader_phong (obj_light *light, shader_material *mat, vectorf *cam, vectorf *pos)
{
	double iambient, idiffus, ispecular, n;
	vectorf nv, lv, hv;
	
	n = 1.0;
	vectorf_init (&nv, 0.0, 0.0, 1.0);
	vectorf_init (&hv, 0.0, 0.0, 0.0);
	
	/* Ambient */
	iambient = light->ambient * mat->kambient;
	
	/* Diffus */
	lv = vectorf_sub (&light->pos, pos);
	lv = vectorf_unit (&lv);
	
	idiffus = light->intensity * mat->kdiffus * vectorf_scalar (&lv, &nv);
	
	/* Specular */
	ispecular = light->intensity * mat->kspecular * ((n + 2.0) / (2.0 * M_PI)) * powf (vectorf_scalar (&hv, &nv), n);
	
	return iambient + idiffus + ispecular;
}

void obj_light_init (obj_light *light, float intensity, float ambient, float red, float green, float blue, float x, float y, float z)
{
	light->intensity = intensity;
	light->ambient = ambient;
	
	shader_color_init (&light->scolor, red, green, blue);
	vectorf_init (&light->pos, x, y, z);
}

void obj_lights_render (obj_light *lights, unsigned int lights_amnt, shader_material *mat, vectorf *cam, vectorf *pos, bmp_pixel *pxl)
{
	unsigned int i;
	double l;
	shader_color scolor;

	shader_color_init (&scolor, 0.0, 0.0, 0.0);

	for (i = 0; i < lights_amnt; i++)
	{
		if (lights[i].pos.z > pos->z)
		{
			l = shader_phong (&lights[i], mat, cam, pos);
		
			scolor.red += l * lights[i].scolor.red;
			scolor.green += l * lights[i].scolor.green;
			scolor.blue += l * lights[i].scolor.blue;
		}
	}
	
	scolor.red /= lights_amnt;
	scolor.green /= lights_amnt;
	scolor.blue /= lights_amnt;
	
	pxl->red = ((pxl->red * scolor.red) >= 250 ? 250 : (pxl->red * scolor.red));
	pxl->green = ((pxl->green * scolor.green) >= 250 ? 250 : (pxl->green * scolor.green));
	pxl->blue = ((pxl->blue * scolor.blue) >= 250 ? 250 : (pxl->blue * scolor.blue));
}

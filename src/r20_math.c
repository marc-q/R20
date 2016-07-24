/* Copyright 2016 Marc Volker Dickmann */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "r20_math.h"

/* Vectors - Float */

void vectorf_init (vectorf *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = 1.0;
}

vectorf vectorf_add (vectorf *a, vectorf *b)
{
	vectorf r;
	
	vectorf_init (&r, a->x+b->x, a->y+b->y, a->z+b->z);
	
	return r;
}

vectorf vectorf_sub (vectorf *a, vectorf *b)
{
	vectorf r;
	
	vectorf_init (&r, a->x-b->x, a->y-b->y, a->z-b->z);
	
	return r;
}

float vectorf_scalar (vectorf *a, vectorf *b)
{
	return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

vectorf vectorf_cross (vectorf *a, vectorf *b)
{
	vectorf r;
	
	vectorf_init (&r, (a->y * b->z) - (a->z * b->y), (a->z * b->x) - (a->x * b->z), (a->x * b->y) - (a->y * b->x));
	
	return r;
}

float vectorf_length (vectorf *a)
{
	return sqrtf (vectorf_scalar (a, a));	
}

vectorf vectorf_unit (vectorf *a)
{
	float l;
	vectorf r;
	
	l = vectorf_length (a);
	
	vectorf_init (&r, a->x / l, a->y / l, a->z / l);
	
	return r;
}

vectorf vectorf_to_twod (vectorf cam, vectorf pos, int width, int height)
{
	double d;
	vectorf r, h, n;
	
	cam.z = (width * 1.58);
	
	vectorf_init (&pos, pos.x, pos.z+(pos.y/4), pos.y);
	vectorf_init (&h, cam.x, cam.y, -1);
	
	n = vectorf_sub (&h, &cam);
	d = vectorf_length (&n);
	n = vectorf_unit (&n);
	
	r = vectorf_sub (&pos, &h);
	
	r.x = r.x * 1.0;
	r.y = r.y * 1.0;
	r.z = r.z * n.z;
	
	d = 1.0 - r.z / d;
	
	r.x = r.x / d;
	r.y = r.y / d;
	r.z = pos.z;
	
	return r;
}

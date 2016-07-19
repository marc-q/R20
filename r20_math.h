#ifndef __R20_MATH_H__
#define __R20_MATH_H__

struct _vectorf
{
	float x;
	float y;
	float z;
	float w;
};

typedef struct _vectorf vectorf;

void vectorf_init (vectorf*, float, float, float);
vectorf vectorf_add (vectorf*, vectorf*);
vectorf vectorf_sub (vectorf*, vectorf*);
float vectorf_scalar (vectorf*, vectorf*);
vectorf vectorf_cross (vectorf*, vectorf*);
float vectorf_length (vectorf*);
vectorf vectorf_unit (vectorf*);

vectorf vectorf_to_twod (vectorf, vectorf, int, int);

#endif /* __R20_MATH_H__ */

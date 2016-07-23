#ifndef __R20_PLANE_H__
#define __R20_PLANE_H__

#define ROT_NONE 0
#define ROT_A 1
#define ROT_B 2

struct _obj_texturedata
{
	bmp_pixel *pxl;
	int x;
	int y;
	int z;
	char type;
};

typedef struct _obj_texturedata obj_texturedata;

struct _obj_plane
{
	int width;
	int height;
	char rotation;
	vectorf pos;
	shader_material *mat;
};

typedef struct _obj_plane obj_plane;

struct _obj_model
{
	int id;
	unsigned int amnt;
	obj_plane *planes;
};

typedef struct _obj_model obj_model;

void obj_texturedata_init (obj_texturedata*, bmp_pixel*, int, int, int, char);

bool obj_model_check_shadow (obj_model*, unsigned int, vectorf*);

void obj_plane_init (obj_plane*, shader_material*, int, int, char, float, float, float);
void obj_plane_render (obj_plane*, obj_model*, unsigned int, obj_light*, unsigned int, bmp_pixel**, int, int, vectorf*, char texture_gen (obj_texturedata*));

#endif /* __R20_PLANE_H__ */

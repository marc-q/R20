#ifndef __R20_SHADER_H__
#define __R20_SHADER_H__

struct _shader_color
{
	float red;
	float green;
	float blue;
};

typedef struct _shader_color shader_color;

struct _shader_material
{
	float kambient;
	float kdiffus;
	float kspecular;
	float n;
};

typedef struct _shader_material shader_material;

struct _obj_light
{
	float intensity;
	float ambient;
	vectorf pos;
	shader_color scolor;
};

typedef struct _obj_light obj_light;

void shader_color_init (shader_color*, float, float, float);
void shader_material_init (shader_material*, float, float, float, float);

double shader_phong (obj_light*, shader_material*, vectorf*, vectorf*);

void obj_light_init (obj_light*, float, float, float, float, float, float, float, float);
void obj_lights_render (obj_light*, unsigned int, shader_material*, vectorf*, vectorf*, bmp_pixel*);

#endif /* __R20_SHADER_H__ */

#include "minirt_bonus.h"

/*
** clamps to valid range
*/
static int	clamp_int(int val, int min, int max)
{
	if (val < min)
		return (min);
	if (val > max)
		return (max);
	return (val);
}

/*
** extracts RGB color from MLX image data at pixel position (x, y).
** calculates memory offset and decodes the 32-bit ARGB pixel value.
** returns color with R, G, B components (0-255).
*/
static t_color get_pixel_color(char *img_data, int x, int y, t_material *mat)
{
	int		offset;
	int		pixel;
	t_color	color;

	offset = (y * mat->img.line_length) + (x * (mat->img.bits_per_pixel / 8));
	pixel = *(int *)(img_data + offset);
	color.r = (pixel >> 16) & 0xFF;
	color.g = (pixel >> 8) & 0xFF;
	color.b = pixel & 0xFF;
	return (color);
}

/*
** samples texture color at hit point's UV coordinates.
** converts UV (0.0-1.0) to pixel coordinates, clamps to valid range,
** and returns the color from the XPM texture image.
*/
t_color	sample_xpm_texture(t_hit *hit)
{
	t_material	mat;
	int			x;
	int			y;

	mat = hit->object->material;
	x = (int)(hit->uv.u * (mat.img.width - 1));
	y = (int)(hit->uv.v * (mat.img.height - 1));
	x = clamp_int(x, 0, mat.img.width - 1);
    y = clamp_int(y, 0, mat.img.height - 1);
	return (get_pixel_color(mat.img.img_data, x, y, &mat));
}

/*
** convert 3d hit point on the surface of sphere into 2d coordinates
** get vector from sphere center to hit point
** normalize to unit sphere
** convert to spherical coordinates:
**    - u: azimuthal angle (horizontal wrap around sphere)
**    - v: polar angle (vertical from top to bottom)
*/

static t_uv	sphere_uv(t_vec3 point, t_sphere sphere)
{
	t_uv	uv;
	t_vec3	p;

	p = vec_sub(point, sphere.center);
	p = vec_normalize(p);
	uv.u = 0.5 + atan2(p.z, p.x) / (2 * M_PI);
	uv.v = 0.5 - asin(p.y) / M_PI;
	return (uv);
}

/*
** convert 3d hit point to 2d texture coordinates
*/
t_uv	calculate_uv(t_hit *hit)
{
	t_uv	uv;

	uv.u = 0.0;
	uv.v = 0.0;
	if (hit->object->material.texture != TEXTURE_XPM)
		return (uv);
	if (hit->object->type == OBJ_SPHERE)
		return	(sphere_uv(hit->point, hit->object->u_data.sphere));
	return (uv);
}

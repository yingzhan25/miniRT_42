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
static t_color	get_pixel_color(char *img_data, int x, int y, t_material *mat)
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
** For plane:
** 1. use scale to change size (the smaller, the more times repeat)
** 2. use floor to convert UV to (0.0-1.0);
** 3. revert direction of u,v
*/
t_color	sample_xpm_texture(t_hit *hit)
{
	t_material	mat;
	int			x;
	int			y;

	mat = hit->object->material;
	if (hit->object->type == OBJ_PLANE)
	{
		hit->uv.u *= SCALE_XL;
		hit->uv.v *= SCALE_XL;
		hit->uv.u -= floor(hit->uv.u);
		hit->uv.v -= floor(hit->uv.v);
		hit->uv.u = 1.0 - hit->uv.u;
		hit->uv.v = 1.0 - hit->uv.v;
	}
	x = (int)(hit->uv.u * (mat.img.width - 1));
	y = (int)(hit->uv.v * (mat.img.height - 1));
	x = clamp_int(x, 0, mat.img.width - 1);
	y = clamp_int(y, 0, mat.img.height - 1);
	return (get_pixel_color(mat.img.img_data, x, y, &mat));
}

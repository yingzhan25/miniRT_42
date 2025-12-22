#include "minirt.h"

/**
 * Calculate color of object with ambient
 */
void	calculate_ambient(t_color *color, t_hit *hit, t_scene *scene)
{
	color->r = hit->color.r * scene->ambient.color.r * scene->ambient.ratio / 255;
	color->g = hit->color.g * scene->ambient.color.g * scene->ambient.ratio / 255;
	color->b = hit->color.b * scene->ambient.color.b * scene->ambient.ratio / 255;
}
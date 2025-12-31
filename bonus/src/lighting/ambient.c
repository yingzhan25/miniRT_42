#include "minirt_bonus.h"
/**
 * Calculate color of object with ambient
 */
void	calculate_ambient(t_color *color, t_color base, t_scene *scene)
{
	color->r = base.r * scene->ambient.color.r * \
	scene->ambient.ratio / 255;
	color->g = base.g * scene->ambient.color.g * \
	scene->ambient.ratio / 255;
	color->b = base.b * scene->ambient.color.b * \
	scene->ambient.ratio / 255;
}

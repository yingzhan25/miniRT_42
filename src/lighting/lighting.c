#include "minirt.h"

/**
 * Calculate color of object with Phong reflection model:
 * ambient, diffuse, specular(bonus)
 */
t_color	calculate_color(t_hit *hit, t_scene *scene)
{
	t_color	color;
	t_vec3	hit_to_light;

	calculate_ambient(&color, hit, scene);
	hit_to_light = vec_normalize(vec_sub(scene->light.position, hit->point));
	//Check whether is in shadow later
	calculate_diffuse(&color, hit_to_light, hit, scene);
	color.r = fmin(fmax(color.r, 0), 255);
	color.g = fmin(fmax(color.g, 0), 255);
	color.b = fmin(fmax(color.b, 0), 255);
	return (color);
}
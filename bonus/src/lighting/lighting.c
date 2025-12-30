#include "minirt.h"

/**
 * dot_product: cosine between 2 vectors;
 * cos(0) = 1; cos(pi/2) = 0; cos(pi) = -1;
 * flip plane normal when hit_to_ray and plane normal in opposite direction
 */
static double	check_light_visible(t_vec3 hit_to_light, t_hit *hit)
{
	if (hit->object->type == OBJ_PLANE && \
		dot_product(hit_to_light, hit->normal) < 0)
		hit->normal = vec_scale(hit->normal, -1.0);
	return (dot_product(hit_to_light, hit->normal));
}

/**
 * Calculate color of object with Phong reflection model:
 * ambient, diffuse, specular(bonus)
 * if is in shadow or light_dot_normal is negative, then only ambient, no diffuse or specular
 */
t_color	calculate_color(t_hit *hit, t_scene *scene)
{
	t_color	color;
	t_vec3	hit_to_light;
	double	light_dot_normal;

	calculate_ambient(&color, hit, scene);
	hit_to_light = vec_normalize(vec_sub(scene->light.position, hit->point));
	light_dot_normal = check_light_visible(hit_to_light, hit);
	if (!in_shadow(hit_to_light, scene, hit) || light_dot_normal >= 0)
	{
		add_diffuse(&color, light_dot_normal, hit, scene);
		add_specular(&color, light_dot_normal, hit, scene);
	}
	color.r = fmin(fmax(color.r, 0), 255);
	color.g = fmin(fmax(color.g, 0), 255);
	color.b = fmin(fmax(color.b, 0), 255);
	return (color);
}

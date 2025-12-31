#include "minirt_bonus.h"

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
 * No texture: base color is hit object color;
 * checkerborad: base color is one of the checker colors;
 * bump texture:/
 */
static t_color	check_base_color(t_hit *hit, t_scene *scene)
{
	if (hit->object->material.texture == 0)
		return (hit->color);
	else if (hit->object->material.texture == 1)
		return (get_texture_color(hit));
}
/**
 * Restrict the range of color to: 0-255
 */
static t_color	clamp_color(t_color color)
{
	t_color	valid;

	valid.r = fmin(fmax(color.r, 0), 255);
	valid.g = fmin(fmax(color.g, 0), 255);
	valid.b = fmin(fmax(color.b, 0), 255);
	return (valid);
}

/**
 * Calculate color of object with Phong reflection model:
 * ambient, diffuse, specular(bonus)
 * ambient not rely on light;
 * go through all the light sources to calculate diffuse and specular,
 * add all to get the final color
 * if is in shadow or light_dot_normal is negative, then only ambient, no diffuse or specular
 */
t_color	calculate_color(t_hit *hit, t_scene *scene)
{
	t_color	color;
	t_light	*current;
	t_color base_color;
	t_vec3	hit_to_light;
	double	light_dot_normal;
	double	specular_intense;

	base_color = check_base_color(hit, scene);
	calculate_ambient(&color, base_color, scene);
	current = scene->lights;
	while (current)
	{
		hit_to_light = vec_normalize(vec_sub(current->position, hit->point));
		light_dot_normal = check_light_visible(hit_to_light, hit);
		if (!in_shadow(hit_to_light, scene, hit, current) && light_dot_normal >= 0)
		{
			add_diffuse(&color, light_dot_normal, base_color, current);
			specular_intense= calc_intensity(light_dot_normal, hit, hit_to_light, scene);
			add_specular(&color, current, hit, specular_intense);
		}
		current = current->next;
	}
	return (clamp_color(color));
}

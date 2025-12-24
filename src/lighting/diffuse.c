#include "minirt.h"

/**
 * Calculate color of object with both ambient and diffuse;
 * dot_product: cosine between 2 vectors;
 * cos(0) = 1; cos(pi/2) = 0; cos(pi) = -1;
 * flip plane normal when hit_to_ray and plane normal in opposite direction
 */
void	calculate_diffuse(t_color *color, t_vec3 hit_to_light, t_hit *hit, t_scene *scene)
{
	double	light_dot_normal;

	if (hit->object->type == OBJ_PLANE && dot_product(hit_to_light, hit->normal) < 0)
		hit->normal = vec_scale(hit->normal, -1.0);
	light_dot_normal = dot_product(hit_to_light, hit->normal);
	if (light_dot_normal < 0)
		light_dot_normal = 0;
	color->r += hit->color.r * scene->light.color.r * scene->light.brightness * light_dot_normal / 255;
	color->g += hit->color.g * scene->light.color.g * scene->light.brightness * light_dot_normal / 255;
	color->b += hit->color.b * scene->light.color.b * scene->light.brightness * light_dot_normal / 255;
}
#include "minirt.h"

/**
 * Calculate color of object with both ambient and diffuse;
 * dot_product: cosine between 2 vectors;
 * cos(0) = 1; cos(pi/2) = 0; cos(pi) = -1;
 * flip plane normal when hit_to_ray and plane normal in opposite direction
 */
void	calculate_diffuse(t_color *c, t_vec3 hit_to_light, t_hit *h, t_scene *s)
{
	double	light_dot_normal;

	if (h->object->type == OBJ_PLANE && \
		dot_product(hit_to_light, h->normal) < 0)
		h->normal = vec_scale(h->normal, -1.0);
	light_dot_normal = dot_product(hit_to_light, h->normal);
	if (light_dot_normal < 0)
		light_dot_normal = 0;
	c->r += h->color.r * s->light.color.r * s->light.brightness * \
			light_dot_normal / 255;
	c->g += h->color.g * s->light.color.g * s->light.brightness * \
			light_dot_normal / 255;
	c->b += h->color.b * s->light.color.b * s->light.brightness * \
			light_dot_normal / 255;
}

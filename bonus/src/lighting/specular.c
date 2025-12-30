#include "../../includes/minirt_bonus.h"

/**
 * Reflective rule: R = 2 * (N·L) * N - L;
 * First calculate reflective light;
 * then calculate hit_to_eye;
 * if cosine is negative, then the reflective light cannot reach eye;
 * otherwise calculate specular intensity;
 * the larger the shininess, the more concentrated the specular
 */
void	calculate_specular(t_color *c, double cosine, t_hit *h, t_scene *s)
{
	t_vec3	reflect_light;

	reflect_light = vec_normalize(vec_sub(vec_scale(h->normal, 2 * cosine), ))

	c->r += h->color.r * s->light.color.r * s->light.brightness * \
			light_dot_normal / 255;
	c->g += h->color.g * s->light.color.g * s->light.brightness * \
			light_dot_normal / 255;
	c->b += h->color.b * s->light.color.b * s->light.brightness * \
			light_dot_normal / 255;
}
#include "minirt.h"

/**
 * Calculate color of object with both ambient and diffuse;
 */
void	add_diffuse(t_color *c, double cosine, t_hit *h, t_scene *s)
{
	c->r += h->color.r * s->light.color.r * s->light.brightness * \
			cosine / 255;
	c->g += h->color.g * s->light.color.g * s->light.brightness * \
			cosine / 255;
	c->b += h->color.b * s->light.color.b * s->light.brightness * \
			cosine / 255;
}

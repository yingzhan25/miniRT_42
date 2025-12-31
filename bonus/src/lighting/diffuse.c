#include "minirt_bonus.h"

/**
 * Calculate color of object with both ambient and diffuse;
 */
void	add_diffuse(t_color *c, double cosine, t_hit *h, t_light *l)
{
	c->r += h->color.r * l->color.r * l->brightness * \
			cosine / 255;
	c->g += h->color.g * l->color.g * l->brightness * \
			cosine / 255;
	c->b += h->color.b * l->color.b * l->brightness * \
			cosine / 255;
}

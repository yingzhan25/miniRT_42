#include "minirt_bonus.h"

/**
 * Calculate color of object with both ambient and diffuse;
 */
void	add_diffuse(t_color *c, double cosine, t_color base, t_light *l)
{
	c->r += base.r * l->color.r * l->brightness * \
			cosine / 255;
	c->g += base.g * l->color.g * l->brightness * \
			cosine / 255;
	c->b += base.b * l->color.b * l->brightness * \
			cosine / 255;
}

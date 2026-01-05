#include "minirt_bonus.h"

/**
 * Calculate color of object with both ambient and diffuse;
 */
void	add_diffuse(t_color *c, double cosine, t_light *l)
{
	c->r += c->r * l->color.r * l->brightness * cosine / 255;
	c->g += c->g * l->color.g * l->brightness * cosine / 255;
	c->b += c->b * l->color.b * l->brightness * cosine / 255;
}

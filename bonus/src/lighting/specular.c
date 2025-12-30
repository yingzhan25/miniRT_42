#include "minirt_bonus.h"

/**
 * Reflective rule: R = 2 * (N·L) * N - L;
 * First calculate reflective light;
 * then calculate hit_to_eye;
 * if cosine is negative, then the reflective light cannot reach eye;
 * otherwise calculate specular intensity;
 * the larger the shininess, the more concentrated the specular
 */
double	calc_intensity(double cosine, t_hit *h, t_vec3 hit_to_light, t_scene *s)
{
	t_vec3	reflect_light;
	t_vec3	hit_to_eye;
	double	reflect_dot_eye;

	reflect_light = vec_normalize(vec_sub(vec_scale(h->normal, 2 * cosine), hit_to_light));
	hit_to_eye = vec_normalize(vec_sub(s->camera.position, h->point));
	reflect_dot_eye = dot_product(reflect_light, hit_to_eye);
	if (reflect_dot_eye < 0)
		return (0);
	return (pow(reflect_dot_eye, h->object->material.shineness));
}

/**
 * Specular reflects the color of light instead of object
 */
void	add_specular(t_color *c, t_scene *s, t_hit *h, double intensity)
{
	c->r += s->light.color.r * h->object->material.specular * intensity;
	c->g += s->light.color.g * h->object->material.specular * intensity;
	c->b += s->light.color.b * h->object->material.specular * intensity;
}

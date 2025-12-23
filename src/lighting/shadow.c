#include "minirt.h"

/**
 * Generate a shadow ray from hit point to light position;
 * calculate the length of shadow ray;
 * if shadow ray is intersected with other object and distance is shorter than length,
 * then it is in the shadow;
 * offset origin of shadow ray with epsilon to avoid self-intersection
 */
int	in_shadow(t_vec3 hit_to_light, t_scene *scene, t_hit* hit)
{
	t_ray	shadow_ray;
	double	shadow_ray_length;
	t_hit	shadow_hit = {0};
	t_object	*current;

	shadow_ray.origin = vec_add(hit->point, vec_scale(hit->normal, EPSILON));
	shadow_ray.direction = hit_to_light;
	shadow_ray_length = vec_length(vec_sub(scene->light.position, hit->point));
	current = scene->objects;
	object_loop(current, &shadow_hit, &shadow_ray);
	return (shadow_hit.hit == 1 && shadow_hit.t < shadow_ray_length - EPSILON && shadow_hit.object != hit->object);
}
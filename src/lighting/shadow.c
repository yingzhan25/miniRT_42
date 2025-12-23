#include "minirt.h"

int	in_shadow(t_vec3 hit_to_light, t_scene *scene, t_hit* hit)
{
	t_ray	shadow_ray;
	double	shadow_ray_length;
	t_hit	shadow_hit;

	shadow_ray.origin = vec_add(hit->point, vec_scale(hit->normal, EPSILON));
	shadow_ray.direction = hit_to_light;
	shadow_ray_length = vec_length(vec_sub(scene->light.position, hit->point));
	


}
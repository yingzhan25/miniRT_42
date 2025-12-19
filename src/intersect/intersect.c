#include "../../includes/minirt.h"

t_vec3	position(t_ray ray, double t)
{
	return (vec_add(ray.origin, vec_scale(ray.direction, t)));
}

t_hit intersect_object(t_ray ray, t_object *obj)
{
	t_hit	hit_point;
	double	intersect;
	t_object	*current;
	t_object	*found;

	current = obj;
	while (current)
	{
		if (current->type == OBJ_SPHERE)
		{
			intersect = ray_sphere_intersection(ray, current->data.sphere);
			hit_point.object = &current->data.sphere;
		}
		if (current->type == OBJ_CYLINDER)
		{
			
		}
		if (current->type == OBJ_PLANE)
		{
			
		}
		current = obj->next;
	}
	if (intersect)
	{
		hit_point.hit = 1;
		hit_point.t = intersect;
		hit_point.color = hit_point.object->color;
		hit_point.point = position(ray, intersect);
		hit_point.normal = vec_normalize(vec_sub(hit_point.point, hit_point.object->data.sphere.center));
	}
	else
	{
		hit_point.hit = 0;
	}
	return (hit_point);
}

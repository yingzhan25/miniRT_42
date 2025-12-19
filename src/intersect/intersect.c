#include "../../includes/minirt.h"

t_vec3	position(t_ray ray, double t)
{
	return (vec_add(ray.origin, vec_scale(ray.direction, t)));
}

t_hit intersect_object(t_ray ray, t_object *obj)
{
	if (obj->type == OBJ_SPHERE)
	{

	}
	if (obj->type == OBJ_CYLINDER)
	{
		
	}
	if (obj->type == OBJ_PLANE)
	{
		
	}
}

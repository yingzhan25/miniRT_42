#include "../../includes/minirt.h"

t_vec3	position(t_ray ray, double t)
{
	return (vec_add(ray.origin, vec_scale(ray.direction, t)));
}

void	object_loop(t_object *current, t_hit *hit_point, t_ray *ray)
{
	double	t;

	(*hit_point).t = INFINITY;
	while (current)
	{
		if (current->type == OBJ_SPHERE)
		{
			(*hit_point).intersection_points = ray_sphere_intersection(*ray, current->data.sphere);
			if ((*hit_point).intersection_points.valid)
			{
				t = define_valid_t_for_sphere((*hit_point).intersection_points.t1, (*hit_point).intersection_points.t2);
				if (!isnan(t) && t < (*hit_point).t)
				{
					(*hit_point).t = t;
					(*hit_point).hit = 1;
					(*hit_point).object = current;
				}
			}
		}
		if (current->type == OBJ_PLANE)
		{
			(*hit_point).intersection_points = ray_plane_intersection(*ray, current->data.plane);
			if ((*hit_point).intersection_points.valid)
			{
				t = (*hit_point).intersection_points.t1;
				if (t > EPSILON && t < (*hit_point).t)
				{
					(*hit_point).t = t;
					(*hit_point).hit = 1;
					(*hit_point).object = current;
				}
			}
		}		
		current = current->next;
	}
}


t_hit intersect_object(t_ray ray, t_object *obj)
{
	t_hit	hit_point = {0};
	t_object	*current;

	current = obj;
	object_loop(current, &hit_point, &ray);
	if (hit_point.hit)
	{
		hit_point.color = hit_point.object->color;
		hit_point.point = position(ray, hit_point.t);
		if (hit_point.object->type == OBJ_PLANE)
		{
			hit_point.normal = hit_point.object->data.plane.normal;	
		}
		else
			hit_point.normal = vec_normalize(vec_sub(hit_point.point, hit_point.object->data.sphere.center));
	}
	return (hit_point);
}

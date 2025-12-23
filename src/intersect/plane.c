#include "../../includes/minirt.h"

t_intersection	ray_plane_intersection(t_ray ray, t_plane plane)
{
	t_intersection intersect;
	t_vec3		plane_to_ray;

	plane_to_ray = vec_sub(plane.point, ray.origin);
	double denominator = dot_product(ray.direction, plane.normal);
	if (fabs(denominator) < EPSILON)
	{
		intersect.valid = 0;
		return (intersect);
	}
	else
	{
		intersect.valid = 1;
		intersect.t1 = dot_product(plane_to_ray, plane.normal) / dot_product(ray.direction, plane.normal);
	}
	return (intersect);
}

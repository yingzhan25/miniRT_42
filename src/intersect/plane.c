#include "../../includes/minirt.h"

t_intersection	ray_plane_intersection(t_ray ray)
{
	t_intersection intersect;

	if (fabs(ray.direction.y) < EPSILON)
	{
		intersect.valid = 0;
		return (intersect);	
	}
	else
	{
		intersect.t1 = -ray.origin.y / ray.direction.y;
	}
	return (intersect);
}

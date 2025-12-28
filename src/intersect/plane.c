#include "../../includes/minirt.h"

/*
** Function to compute the intersection of a ray with a plane.
** The plane is defined by a point on the plane and a normal vector.
** The function returns a t_intersection struct containing the intersection 
** validity and t value.
** If the ray is parallel to the plane (denominator close to zero), 
** no intersection occurs.
** Otherwise, the intersection t value is calculated using the plane equation.
** plane_to_ray is the vector from the ray origin to the plane point.
** denominator is the dot product of the ray direction and the plane normal, 
** used to determine parallelism.
** If the absolute value of the denominator is less than EPSILON, the ray is 
** considered parallel to the plane.
** If not parallel, the intersection t value is computed and marked as valid.
** The intersection t value represents the distance along the ray to 
** the intersection point.
*/
t_intersection	ray_plane_intersection(t_ray ray, t_plane plane)
{
	t_intersection	intersect;
	double			denominator;
	t_vec3			plane_to_ray;

	plane_to_ray = vec_sub(plane.point, ray.origin);
	denominator = dot_product(ray.direction, plane.normal);
	if (fabs(denominator) < EPSILON)
	{
		intersect.valid = 0;
		return (intersect);
	}
	else
	{
		intersect.t1 = dot_product(plane_to_ray, plane.normal) / denominator;
		if (intersect.t1 > EPSILON)
			intersect.valid = 1;
		else
			intersect.valid = 0;
	}
	return (intersect);
}

 #include "../../includes/minirt.h"

/*
** Function to compute the intersection of a ray with an infinite cylinder aligned along the y-axis.
** The cylinder is defined by its center, axis (normalized), radius, and height.
** The function returns a t_intersection struct containing the intersection validity and t values.
** The normal at the intersection point is computed separately.
** oc_x and oc_z are the differences in x and z coordinates between the ray origin and cylinder center.
** a, b, and c are coefficients of the quadratic equation derived from substituting the ray equation into the cylinder equation.
** The discriminant determines the nature of the intersections (real and distinct, real and equal, or complex).
** If the discriminant is non-negative, the function calculates the two intersection t values and marks the intersection as valid.
*/

t_intersection	ray_cylinder_intersect(t_ray ray, t_cylinder cylinder)
{
	t_intersection intersect = {0};
	double	discriminant;
	double	a;
	double	b;
	double	c;
	double	oc_x;
	double	oc_z;

	oc_x = ray.origin.x - cylinder.center.x;
	oc_z = ray.origin.z - cylinder.center.z;
	a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
	if (a < EPSILON)
		return (intersect);
	b = 2 * (oc_x * ray.direction.x + oc_z * ray.direction.z);
	c = oc_x * oc_x + oc_z * oc_z - cylinder.radius * cylinder.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < EPSILON)
		return (intersect);
	else
	{
		intersect.valid = 1;
		intersect.t1 = ((-1) * b - sqrt(discriminant)) / (2 * a);
		intersect.t2 = ((-1) * b + sqrt(discriminant)) / (2 * a);	
	}
	return (intersect);
}

/*
** Function to compute the normal vector at a point on the surface of a cylinder.
** The normal is calculated by projecting the vector from the cylinder center to the point onto the cylinder axis,
** and then subtracting this projection from the original vector to get the perpendicular component.
** The resulting normal vector is then normalized.
** center_to_point is the vector from the cylinder center to the intersection point.
** projection is the projection of center_to_point onto the cylinder axis.
** normal is the vector perpendicular to the cylinder surface at the intersection point.
*/

t_vec3 cylinder_normal(t_vec3 point, t_cylinder cylinder)
{
    t_vec3 normal;
    t_vec3 center_to_point;
    t_vec3 projection;
	double proj_length; 

	center_to_point = vec_sub(point, cylinder.center);
	proj_length = dot_product(center_to_point, cylinder.axis);
	projection = vec_scale(cylinder.axis, proj_length);
	normal = vec_sub(center_to_point, projection);
	normal = vec_normalize(normal);
    return normal;
}

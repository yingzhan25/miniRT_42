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
	t_vec3	oc;
	double	t1, t2;
	double	y_max, y_min;

	oc = vec_sub(ray.origin, cylinder.center);
	a = dot_product(ray.direction, ray.direction) - pow(dot_product(ray.direction, cylinder.axis), 2);
	if (a < EPSILON)
		return (intersect);
	b = 2.0 * (dot_product(oc, ray.direction) - dot_product(ray.direction, cylinder.axis) * dot_product(oc, cylinder.axis));
	c = dot_product(oc, oc) - pow(dot_product(oc, cylinder.axis), 2) - cylinder.radius * cylinder.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < EPSILON)
		return (intersect);
	else
	{
		t1 = ((-1) * b - sqrt(discriminant)) / (2 * a);
		t2 = ((-1) * b + sqrt(discriminant)) / (2 * a);
		y_max = cylinder.center.y + cylinder.height / 2;
		y_min = cylinder.center.y - cylinder.height / 2;
		t_vec3	t1_point = position(ray, t1);
		double	proj_1 = dot_product(vec_sub(t1_point, cylinder.center), cylinder.axis);
		t_vec3	t2_point = position(ray, t2);
		double	proj_2 = dot_product(vec_sub(t2_point, cylinder.center), cylinder.axis);
		if (proj_1 <= y_max && proj_1 >= y_min)
		{
			intersect.valid = 1;
			intersect.t1 = t1;
		}
		else
			intersect.t1 = -1;
		if (proj_2 <= y_max && proj_2 >= y_min)
		{
			intersect.valid = 1;
			intersect.t2 = t2;
		}
		else
			intersect.t2 = -1;
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
    return (normal);
}

 #include "../../includes/minirt.h"

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

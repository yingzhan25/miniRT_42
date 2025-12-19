#include "../../includes/minirt.h"

double  ray_sphere_intersection(t_ray ray, t_sphere sphere)
{
	t_intersection intersect;
	double	discriminant;
	double	a;
	double	b;
	double	c;
	t_vec3	sphere_to_ray;

	sphere_to_ray = vec_sub(ray.origin, ZERO_VECTOR);
	a = dot_product(ray.direction, ray.direction);
	b = 2 * dot_product(ray.direction, sphere_to_ray);
	c = dot_product(sphere_to_ray, sphere_to_ray) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		intersect.t1 = NAN;
		intersect.t2 = NAN;
		return (NAN);
	}
	else
	{
		intersect.t1 = ((-1) * b - sqrt(discriminant)) / (2 * a);
		intersect.t2 = ((-1) * b + sqrt(discriminant)) / (2 * a);
	}
	if (intersect.t1 > 0 && intersect.t2 > 0)
        return (fmin(intersect.t1, intersect.t2));
    else if (intersect.t1 > 0)
        return (intersect.t1);
    else if (intersect.t2 > 0)
        return (intersect.t2);
	return (NAN);
}

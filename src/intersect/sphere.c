#include "../../includes/minirt.h"

/*
** Ray-Sphere Intersection
** This function calculates the intersection of a ray with a sphere.
** It returns a t_intersection struct containing 
** the intersection points t1 and t2.
** If there is no intersection, the valid field is set to 0.
** If there is an intersection, valid is set to 1 and t1, t2 
** are the intersection distances.
*/
t_intersection	ray_sphere_intersection(t_ray ray, t_sphere sphere)
{
	t_intersection intersect;
	double	discriminant;
	double	a;
	double	b;
	double	c;
	t_vec3	sphere_to_ray;

	sphere_to_ray = vec_sub(ray.origin, sphere.center);
	a = dot_product(ray.direction, ray.direction);
	b = 2 * dot_product(ray.direction, sphere_to_ray);
	c = dot_product(sphere_to_ray, sphere_to_ray) - 
		sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		intersect.valid = 0;
		return (intersect);
	}
	else
	{
		intersect.valid = 1;
		intersect.t1 = ((-1) * b - sqrt(discriminant)) / (2 * a);
		intersect.t2 = ((-1) * b + sqrt(discriminant)) / (2 * a);
	}
	return (intersect);
}

/*
** Define Valid t for Sphere Intersection
** This function takes two intersection distances t1 and t2
** and returns the smallest positive t value.
** If both t1 and t2 are negative, it returns NAN.
** If only one is positive, it returns that one.
*/
double	define_valid_t_for_sphere(double t1, double t2)
{
	if (t1 > 0 && t2 > 0)
        return (fmin(t1, t2));
    else if (t1 > 0)
        return (t1);
    else if (t2 > 0)
        return (t2);
	else
		return (NAN);
}

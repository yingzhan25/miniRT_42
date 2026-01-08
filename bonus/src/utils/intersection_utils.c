#include "minirt_bonus.h"

/*
** cap_intersect: Computes the intersection of a ray with a cylinder cap.
** It calculates the intersection point with the plane of the cap
** and checks if it lies within the cap's radius.
** Returns the t value of the intersection if valid, -1.0 otherwise.
*/
static double	cap_intersect(t_ray ray, t_vec3 cap_center,
		t_vec3 axis, double radius)
{
	double	denom;
	double	t;
	t_vec3	p;
	t_vec3	v;

	denom = dot_product(ray.direction, axis);
	if (fabs(denom) < EPSILON)
		return (-1.0);
	v = vec_sub(cap_center, ray. origin);
	t = dot_product(v, axis) / denom;
	if (t <= EPSILON)
		return (-1.0);
	p = position(ray, t);
	v = vec_sub(p, cap_center);
	if (dot_product(v, v) > radius * radius)
		return (-1.0);
	return (t);
}

// Helper function to avoid code duplication
static void	update_intersection(t_intersection *intersect, double t)
{
	if (!intersect->valid || t < intersect->t1)
	{
		intersect->t2 = intersect->t1;
		intersect->t1 = t;
		intersect->valid = 1;
	}
	else if (isnan(intersect->t2) || t < intersect->t2)
		intersect->t2 = t;
}

/*
** check_caps: Checks for intersections with the cylinder's caps.
** Updates the intersection structure with valid t values if intersections occur.
** bottom_center and top_center are the centers of the bottom and top caps.
** half_h is half the height of the cylinder.
** If an intersection is found and is closer than existing t values,
** it updates the intersection structure accordingly.
*/
void	check_caps(t_cyl_work *w, t_intersection *intersect)
{
	t_vec3	axis_scaled;
	t_vec3	bottom_center;
	t_vec3	top_center;
	double	t_bottom;
	double	t_top;

	axis_scaled = vec_scale(w->cy.axis, w->half_h);
	bottom_center = vec_sub(w->cy.center, axis_scaled);
	top_center = vec_add(w->cy.center, axis_scaled);
	t_bottom = cap_intersect(w->ray, bottom_center, w->cy.axis, w->cy.radius);
	if (t_bottom > EPSILON)
		update_intersection(intersect, t_bottom);
	t_top = cap_intersect(w->ray, top_center, w->cy.axis, w->cy.radius);
	if (t_top > EPSILON)
		update_intersection(intersect, t_top);
}

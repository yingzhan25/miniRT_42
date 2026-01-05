#include "minirt_bonus.h"

/*
** cyl_init: Initializes the cylinder intersection work structure.
** It computes the necessary coefficients for the quadratic equation
** based on the ray and cylinder parameters.
** Returns 1 if initialization is successful, 0 otherwise.
*/
static int	cyl_init(t_cyl_work *w, t_ray ray, t_cylinder cy)
{
	w->ray = ray;
	w->cy = cy;
	w->half_h = cy.height * 0.5;
	w->oc = vec_sub(ray.origin, cy.center);
	w->a = dot_product(ray.direction, ray.direction)
		- pow(dot_product(ray.direction, cy.axis), 2);
	if (w->a < EPSILON)
		return (0);
	w->b = 2.0 * (dot_product(w->oc, ray.direction) - \
			dot_product(ray.direction, cy.axis) * dot_product(w->oc, cy.axis));
	w->c = dot_product(w->oc, w->oc) - \
		pow(dot_product(w->oc, cy.axis), 2) - \
		cy.radius * cy.radius;
	return (1);
}

/*
** cyl_solve: Solves the quadratic equation for cylinder intersection.
** It calculates the discriminant and determines the intersection
** points t1 and t2.
** Returns 1 if there are real solutions (intersections), 0 otherwise.
*/
static int	cyl_solve(t_cyl_work *w)
{
	double	d;

	d = w->b * w->b - 4.0 * w->a * w->c;
	if (d < EPSILON)
		return (0);
	w->t1 = ((-1) * (w->b) - sqrt(d)) / (2.0 * w->a);
	w->t2 = ((-1) * (w->b) + sqrt(d)) / (2.0 * w->a);
	return (1);
}

/*
** cyl_in_height: Checks if the intersection point at distance t
** lies within the height bounds of the cylinder.
** It computes the projection of the intersection point onto the cylinder axis
** and verifies if it falls within the half-height limits.
** Returns 1 if the point is within height bounds, 0 otherwise.
**      +half_h  ←── top point
**         |
**         |  ← projection of point onto axis must be between these
**         |
**      -half_h  ←── bottom point
*/
static int	cyl_in_height(t_cyl_work *w, double t)
{
	t_vec3	p;
	double	proj;

	if (t <= EPSILON)
		return (0);
	p = position(w->ray, t);
	proj = dot_product(vec_sub(p, w->cy.center), w->cy.axis);
	return (proj >= ((-1) * (w->half_h)) && proj <= w->half_h);
}

/*
** ray_cylinder_intersect: Computes the intersection of a ray with a cylinder.
** It initializes the cylinder work structure, solves the quadratic equation,
** and checks if the intersection points are within the cylinder's height.
** Returns a t_intersection struct containing
** the intersection validity and t values.
** If there are valid intersections, the valid field is set
** to 1 and t1, t2 are the intersection distances.
** If there are no valid intersections, valid is set to 0.
*/
t_intersection	ray_cylinder_intersect(t_ray ray, t_cylinder cylinder)
{
	t_intersection	intersect;
	t_cyl_work		cyl;

	intersect.valid = 0;
	intersect.t1 = NAN;
	intersect.t2 = NAN;
	if (!cyl_init(&cyl, ray, cylinder))
		return (intersect);
	if (!cyl_solve(&cyl))
		return (intersect);
	if (cyl_in_height(&cyl, cyl.t1))
	{
		intersect.valid = 1;
		intersect.t1 = cyl.t1;
	}
	if (cyl_in_height(&cyl, cyl.t2))
	{
		intersect.valid = 1;
		intersect.t2 = cyl.t2;
	}
	check_caps(&cyl, &intersect);
	return (intersect);
}

/*
** cylinder_normal: Computes the normal vector at a point on the cylinder surface.
** It calculates the vector from the cylinder center to the point,
** projects it onto the cylinder axis, and derives the normal.
** Returns the normalized normal vector.
** If the point is on the caps, returns the cap normal.
** (Normal vektor - yuzaga perpendikulyar vektor.) 
** (Yorug'lik qanday aks etishini hisoblash uchun kerak.)
*/

t_vec3	cylinder_normal(t_vec3 point, t_cylinder cylinder)
{
	t_vec3	center_to_point;
	t_vec3	projection;
	double	proj_length;
	double	half_h;

    half_h = cylinder. height * 0.5;
	center_to_point = vec_sub(point, cylinder.center);
	proj_length = dot_product(center_to_point, cylinder.axis);
	projection = vec_scale(cylinder.axis, proj_length);
    if (fabs(proj_length - half_h) < EPSILON)
		return (cylinder.axis);
	if (fabs(proj_length + half_h) < EPSILON)
		return (vec_scale(cylinder.axis, -1.0));
	return (vec_normalize(vec_sub(center_to_point, projection)));
}

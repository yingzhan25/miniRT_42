/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:02:17 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/08 12:02:18 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/*
** cone_init: Initializes the cone intersection work structure.
** It computes the necessary coefficients for the quadratic equation
** based on the ray and cone parameters.
** Returns 1 if initialization is successful, 0 otherwise.
// KONUS:    a = (D·A)² * sin²θ - |D|² * cos²θ  (yoki soddaroq variant)
*/
int	cone_init(t_cone_work *w, t_ray ray, t_cone cone)
{
	double	d_dot_a;
	double	oc_dot_a;
	double	d_dot_oc;
	double	angle;

	w->ray = ray;
	w->cone = cone;
	angle = cone.radius / cone.height;
	w->cos2 = cos(angle) * cos(angle);
	w->sin2 = sin(angle) * sin(angle);
	w->oc = vec_sub(ray.origin, cone.apex);
	d_dot_a = dot_product(ray.direction, cone.axis);
	oc_dot_a = dot_product(w->oc, cone.axis);
	d_dot_oc = dot_product(ray.direction, w->oc);
	w->a = d_dot_a * d_dot_a - w->cos2;
	w->b = 2.0 * (d_dot_a * oc_dot_a - d_dot_oc * w->cos2);
	w->c = oc_dot_a * oc_dot_a - dot_product(w->oc, w->oc) * w->cos2;
	if (fabs(w->a) < EPSILON)
		return (0);
	return (1);
}

/*
** cone_solve: Solves the quadratic equation for cone intersection.
** It calculates the discriminant and determines the intersection
** points t1 and t2.
** Returns 1 if there are real solutions (intersections), 0 otherwise.
*/
int	cone_solve(t_cone_work *w)
{
	double	d;

	d = w->b * w->b - 4.0 * w->a * w->c;
	if (d < 0)
		return (0);
	w->t1 = (-w->b - sqrt(d)) / (2.0 * w->a);
	w->t2 = (-w->b + sqrt(d)) / (2.0 * w->a);
	return (1);
}

/*
** cone_in_height: Checks if the intersection point at distance t
** lies within the height bounds of the cone.
** It computes the projection of the intersection point onto the cone axis
** and verifies if it falls within the height limits.
** Returns 1 if the point is within height bounds, 0 otherwise.
**      height
**      ↑
**      |  ← projection of point onto axis must be between these
**      |
**      0
*/
static int	cone_in_height(t_cone_work *w, double t)
{
	t_vec3	p;
	double	proj;

	if (t <= EPSILON)
		return (0);
	p = position(w->ray, t);
	proj = dot_product(vec_sub(p, w->cone.apex), w->cone.axis);
	return (proj >= 0 && proj <= w->cone.height);
}

/*
** ray_cone_intersect: Computes the intersection of a ray with a cone.
** It initializes the cone work structure, solves the quadratic equation,
** and checks if the intersection points are within the cone's height.
** Returns a t_intersection struct containing
** the intersection validity and t values.
*/
t_intersection	ray_cone_intersect(t_ray ray, t_cone cone)
{
	t_intersection	intersect;
	t_cone_work		w;

	intersect.valid = 0;
	intersect.t1 = NAN;
	intersect.t2 = NAN;
	if (!cone_init(&w, ray, cone))
		return (intersect);
	if (!cone_solve(&w))
		return (intersect);
	if (cone_in_height(&w, w.t1))
	{
		intersect.valid = 1;
		intersect.t1 = w.t1;
	}
	if (cone_in_height(&w, w.t2))
	{
		intersect.valid = 1;
		intersect.t2 = w.t2;
	}
	return (intersect);
}

/*
** cone_normal: Computes the normal vector at a point on the cone surface.
// Normal = (P - apex) - (1 + k²) · proj · axis
*/
t_vec3	cone_normal(t_vec3 point, t_cone cone)
{
	t_vec3	apex_to_point;
	double	proj;
	double	k2;
	double	angle;

	angle = cone.radius / cone.height;
	apex_to_point = vec_sub(point, cone.apex);
	proj = dot_product(apex_to_point, cone.axis);
	k2 = tan(angle) * tan(angle);
	return (vec_normalize(vec_sub(apex_to_point,
				vec_scale(cone.axis, (1.0 + k2) * proj))));
}

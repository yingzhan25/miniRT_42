/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:02:37 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/08 12:02:38 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/*
** Ray-Plane Intersection
** This function calculates the intersection of a ray with a plane.
** It returns a t_intersection struct containing
** the intersection point t1.
** If there is no intersection, the valid field is set to 0.
** If there is an intersection, valid is set to 1 and t1 is
** the intersection distance.
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

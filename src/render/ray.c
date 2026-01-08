/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:32:04 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/08 12:32:05 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray_create(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

/*
 * Generate a ray from the camera through the specified pixel
 * i: pixel x coordinate
 * j: pixel y coordinate
 * u: horizontal offset in viewport space
 * v: vertical offset in viewport space
 * viewport_point: point on the viewport corresponding to pixel (i, j)
 */
t_ray	generate_ray(t_camera *cam, int i, int j)
{
	t_ray	ray;
	t_vec3	viewport_point;
	double	u;
	double	v;

	u = (i + 0.5) / WIN_WIDTH - 0.5;
	v = (j + 0.5) / WIN_HEIGHT - 0.5;
	u *= cam->viewport_width;
	v *= -cam->viewport_height;
	ray.origin = cam->position;
	viewport_point = vec_add(
			vec_add(cam->orientation, vec_scale(cam->right, u)),
			vec_scale(cam->up, v));
	ray.direction = vec_normalize(viewport_point);
	return (ray);
}

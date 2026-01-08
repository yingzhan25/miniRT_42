/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:31:59 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/08 12:32:00 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Check whether forward is close to y-axis;
 * fabs(): float absolute
 * if yes, use z-axis, otherwise use y-axis as world-up, x-axis as backup
 */
void	setup_camera(t_camera *cam)
{
	t_vec3	forward;
	t_vec3	world_up;

	forward = cam->orientation;
	if (fabs(forward.y) > 1.0 - EPSILON)
		world_up = (t_vec3){0, 0, 1};
	else
		world_up = (t_vec3){0, 1, 0};
	cam->right = vec_normalize(vec_cross(world_up, forward));
	if (is_zero_vec(&cam->right))
	{
		world_up = (t_vec3){1, 0, 0};
		cam->right = vec_normalize(vec_cross(world_up, forward));
	}
	cam->up = vec_normalize(vec_cross(forward, cam->right));
}

/**
 * Convert degree of fov to radian;
 * as fov is horizontal, calculate width first, and then height
 */
void	setup_viewport(t_camera *cam)
{
	double	aspect;
	double	half_width;
	double	half_height;
	double	fov_radian;

	aspect = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	fov_radian = cam->fov * M_PI / 180.0;
	half_width = tan(fov_radian / 2.0);
	half_height = half_width / aspect;
	cam->viewport_width = 2.0 * half_width;
	cam->viewport_height = 2.0 * half_height;
}

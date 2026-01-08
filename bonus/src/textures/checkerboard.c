/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:05:26 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/08 12:23:22 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * Calculate checkered texture for objects;
 * i, j: index of checkerboard;
 * using floor() to find the small roundup index after divide scale;
 * decide the color of checker with (i + j) % 2
 * the scale of plane should be larger than sphere,
 * because plane uv is not normalized
 */
t_color	get_cb_color(t_hit *hit)
{
	int		i;
	int		j;

	if (hit->object->type == OBJ_PLANE)
	{
		i = (int)floor(hit->uv.u / SCALE_S);
		j = (int)floor(hit->uv.v / SCALE_S);
		if ((i + j) % 2)
			return ((t_color){255, 0, 0});
		return ((t_color){0, 0, 255});
	}
	else
	{
		i = (int)floor(hit->uv.u / SCALE_L);
		j = (int)floor(hit->uv.v / SCALE_L);
		if ((i + j) % 2)
			return ((t_color){0, 0, 0});
		return ((t_color){255, 255, 255});
	}
}

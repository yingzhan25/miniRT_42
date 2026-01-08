/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:30:14 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/08 12:30:15 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Calculate color of object with ambient
 */
void	calculate_ambient(t_color *color, t_hit *hit, t_scene *scene)
{
	color->r = hit->color.r * scene->ambient.color.r * \
	scene->ambient.ratio / 255;
	color->g = hit->color.g * scene->ambient.color.g * \
	scene->ambient.ratio / 255;
	color->b = hit->color.b * scene->ambient.color.b * \
	scene->ambient.ratio / 255;
}

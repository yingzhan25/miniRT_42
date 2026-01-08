/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:02:50 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/08 12:02:51 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
/**
 * Calculate color of object with ambient
 */
void	calculate_ambient(t_color *color, t_scene *scene)
{
	color->r = color->r * scene->ambient.color.r * \
	scene->ambient.ratio / 255;
	color->g = color->g * scene->ambient.color.g * \
	scene->ambient.ratio / 255;
	color->b = color->b * scene->ambient.color.b * \
	scene->ambient.ratio / 255;
}

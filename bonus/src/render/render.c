/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:05:13 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/08 12:05:14 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * Set background color as black;
 */
static t_color	set_bg_color(void)
{
	t_color	color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	return (color);
}

/**
 * Generating ray to calculate intersection wth objects;
 * find the color according to the intersection;
 * render loop to render each pixel of image with correct color;
 * put image to window at once to avoid flickering;
 */
void	render_scene(t_mlx_data *data)
{
	int		i;
	int		j;
	t_color	color;
	t_ray	ray;
	t_hit	hit;

	j = 0;
	while (j < WIN_HEIGHT)
	{
		i = 0;
		while (i < WIN_WIDTH)
		{
			ray = generate_ray(&data->scene->camera, i, j);
			hit = intersect_object(ray, data->scene->objects);
			if (hit.hit == 1)
				color = calculate_color(&hit, data->scene);
			else
				color = set_bg_color();
			mlx_put_color_to_image(data, color, i, j);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
}

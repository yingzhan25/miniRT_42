/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:05:13 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/09 12:46:08 by yingzhan         ###   ########.fr       */
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
 * Display the progress of render;
 * display percentage after rendering every 10 lines of pixels;
 * \r: move to the start of line to rewrite
 * fflush(): output immediately without delay
 */
static void	display_progress(int j)
{
	int	progress;

	if (!j)
	{
		printf("Start rendering");
	}
	else if (j % 10 == 0 && j < WIN_HEIGHT - 1)
	{
		progress = j * 100 / WIN_HEIGHT;
		printf("\rRender progress: %d%%", progress);
		fflush(stdout);
	}
	else if (j == WIN_HEIGHT - 1)
	{
		printf("\rRender progress: 100%%");
		fflush(stdout);
		printf("\n");
	}
	return ;
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
		display_progress(j);
		j++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
}

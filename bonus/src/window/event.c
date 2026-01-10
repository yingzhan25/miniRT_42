/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:10:02 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/10 19:01:29 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * Click cross to close the window
 */
static int	handle_close(t_mlx_data *data)
{
	t_object	*obj;
	obj = data->scene->objects;
	if (data->image)
		mlx_destroy_image(data->mlx, data->image);
	if (data->window)
	{
		mlx_destroy_window(data->mlx, data->window);
		data->window = NULL;
	}
	if (data->scene)
	{
		while (obj)
		{
			if (data->scene->objects->material.texture == TEXTURE_XPM)
				mlx_destroy_image(data->mlx, obj->material.img.xpm_img);
			obj = obj->next;
		}
		free_scene(data->scene);
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
	free(data);
	exit (0);
	return (0);
}

/**
 * Press ESC to close the window;
 * Use keys to transform camera
 */
static int	handle_keypress(int keycode, t_mlx_data *data)
{
	if (keycode == KEY_ESC)
		handle_close(data);
	return (0);
}

void	handle_events(t_mlx_data *data)
{
	mlx_hook(data->window, KeyPress, KeyPressMask, handle_keypress, data);
	mlx_hook(data->window, DestroyNotify, 0, handle_close, data);
	mlx_loop(data->mlx);
}

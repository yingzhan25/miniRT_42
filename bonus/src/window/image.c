/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:10:08 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/08 12:10:09 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * Render each pixel of the image with corresponding color
 */
void	mlx_put_color_to_image(t_mlx_data *data, t_color color, int x, int y)
{
	char	*dst_pixel;
	int		offset;

	offset = (y * data->line_length) + (x * (data->bits_per_pixel / 8));
	dst_pixel = data->addr + offset;
	*(unsigned int *)dst_pixel = (color.r << 16) | (color.g << 8) | color.b;
}

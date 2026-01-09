/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:02:56 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/08 12:02:57 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * Calculate color of object with both ambient and diffuse;
 */
void	add_diffuse(t_color *c, double cosine, t_light *l)
{
	c->r += c->r * l->color.r * l->brightness * cosine / 255;
	c->g += c->g * l->color.g * l->brightness * cosine / 255;
	c->b += c->b * l->color.b * l->brightness * cosine / 255;
}

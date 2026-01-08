/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:09:55 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/08 12:09:56 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * Check whether all the parsing is valid or not
 */
int	validate_scene(t_scene *scene)
{
	if (scene->num_a != 1 || scene->num_c != 1 || scene->num_l != 1)
		return (error(LACK_ELEMENT), 1);
	if (scene->obj_count == 0)
		return (error(UNDEFINE_OBJS), 1);
	if (scene->fail_to_parse)
		return (1);
	return (0);
}

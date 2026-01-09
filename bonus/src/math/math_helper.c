/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:03:22 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/08 12:03:23 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector.h"

/*
** is_zero_vec: check whether the vector is a zero vector
*/
int	is_zero_vec(t_vec3 *vec)
{
	if ((*vec).x * (*vec).x + (*vec).y * (*vec).y + (*vec).z * \
		(*vec).z < EPSILON * EPSILON)
		return (1);
	return (0);
}

t_vec3	vec_zero(void)
{
	t_vec3	v;

	v.x = 0;
	v.y = 0;
	v.z = 0;
	return (v);
}

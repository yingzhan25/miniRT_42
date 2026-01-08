/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:03:51 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/08 12:03:52 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector.h"

/**
** Computes the dot product of two 3D vectors a and b.
** The dot product is a scalar value that represents the cosine of the angle
** between the two vectors multiplied by their magnitudes.
*/
double	dot_product(t_vec3 a, t_vec3 b)
{
	double	product;

	product = a.x * b.x + a.y * b.y + a.z * b.z;
	return (product);
}

/*
** Computes the cross product of two 3D vectors a and b.
** The cross product is a vector that is perpendicular to both a and b.
*/
t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	tmp;

	tmp.x = a.y * b.z - a.z * b.y;
	tmp.y = a.z * b.x - a.x * b.z;
	tmp.z = a.x * b.y - a.y * b.x;
	return (tmp);
}

/*
* Computes the length (magnitude) of a 3D vector v.
* The length is calculated using the Euclidean norm.
*/
double	vec_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/*
** normalize a 3d vector if magnitude of vector is zero then return the zero vec
*/
t_vec3	vec_normalize(t_vec3 v)
{
	double	m;
	t_vec3	tmp;

	m = vec_length(v);
	if (m < EPSILON)
		tmp = vec_zero();
	else
	{
		tmp.x = v.x / m;
		tmp.y = v.y / m;
		tmp.z = v.z / m;
	}
	return (tmp);
}

/*
** this function will negate vector
*/
t_vec3	vec_negate(t_vec3 v)
{
	t_vec3	tmp;

	tmp.x = v.x * (-1);
	tmp.y = v.y * (-1);
	tmp.z = v.z * (-1);
	return (tmp);
}

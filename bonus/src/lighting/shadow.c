/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:03:10 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/08 12:03:11 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * Generate a shadow ray from hit point to light position;
 * calculate the length of shadow ray;
 * if shadow ray is intersected with other object
 * and distance is shorter than length,
 * then it is in the shadow;
 * offset origin of shadow ray with epsilon to avoid self-intersection
 */
int	in_shadow(t_vec3 hit_to_light, t_scene *scene, t_hit *hit, t_light *l)
{
	t_ray		shadow_ray;
	double		shadow_ray_length;
	t_hit		shadow_hit;
	t_object	*current;

	ft_memset(&shadow_hit, 0, sizeof(t_hit));
	shadow_ray.origin = vec_add(hit->point, vec_scale(hit->normal, EPSILON));
	shadow_ray.direction = hit_to_light;
	shadow_ray_length = vec_length(vec_sub(l->position, hit->point));
	current = scene->objects;
	object_loop(current, &shadow_hit, &shadow_ray);
	return (shadow_hit.hit == 1 && shadow_hit.t < shadow_ray_length - EPSILON \
			&& shadow_hit.object != hit->object);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:37:14 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/08 12:37:15 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char *argv[])
{
	t_scene		*scene;
	t_mlx_data	*data;

	scene = parse_scene(argc, argv);
	if (!scene)
		return (1);
	data = malloc(sizeof(t_mlx_data));
	if (!data)
		return (error(FAIL_MEM_ALLOC), 1);
	mlx_data_init(data, scene);
	setup_camera(&data->scene->camera);
	setup_viewport(&data->scene->camera);
	render_scene(data);
	handle_events(data);
	return (0);
}

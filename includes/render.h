/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:29:01 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/08 12:29:02 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "scene.h"
# include <math.h>
# include "/usr/local/include/mlx.h"
// # include "mlx/mlx.h"
# include <X11/X.h>

// Number of pixels, can be changed to 1920*1080
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define M_PI 3.14159265358979323846
# define KEY_ESC 65307
// Ray definition
typedef struct s_ray {
	t_vec3	origin;
	t_vec3	direction;
}			t_ray;

// Window and image data
typedef struct s_mlx_data {
	void	*mlx;
	void	*window;
	void	*image;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_scene	*scene;
}	t_mlx_data;

void	setup_camera(t_camera *cam);
void	setup_viewport(t_camera *cam);
void	render_scene(t_mlx_data *data);
t_ray	generate_ray(t_camera *cam, int i, int j);

// Window management
void	mlx_data_init(t_mlx_data *data, t_scene *scene);
void	mlx_put_color_to_image(t_mlx_data *data, t_color color, int x, int y);
void	handle_events(t_mlx_data *data);

#endif

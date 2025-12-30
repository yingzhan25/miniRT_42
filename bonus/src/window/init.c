#include "minirt_bonus.h"

/**
 * Initialise all the members inside mlx struct
 */
void	mlx_data_init(t_mlx_data *data, t_scene *scene)
{
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "./miniRT");
	data->image = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->addr = mlx_get_data_addr(data->image, &data->bits_per_pixel, \
									&data->line_length, &data->endian);
	data->scene = scene;
}

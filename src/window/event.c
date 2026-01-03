#include "minirt.h"

/**
 * Click cross to close the window
 */
static int	handle_close(void *param)
{
	t_mlx_data *data = (t_mlx_data *)param;
	
	if (data->image)
		mlx_destroy_image(data->mlx, data->image);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->scene)
		free_scene(data->scene);
	free(data);
	exit(0);
	return (0);
}

/**
 * Press ESC to close the window;
 * Use keys to transform camera
 */
static int	handle_keypress(int keycode, void *param)
{
	t_mlx_data *data = (t_mlx_data *)param;
	
	if (keycode == KEY_ESC)
		handle_close(data);
	return (0);
}

void	handle_events(t_mlx_data *data)
{
	mlx_key_hook(data->window, handle_keypress, data);
	mlx_loop(data->mlx);
}

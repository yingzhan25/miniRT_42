# include "render.h"

// Click cross to close the window
static int	handle_close(t_mlx_data *data)
{
	if (data->image)
		mlx_destroy_image(data->mlx, data->image);
	if (data->window)
	{
		mlx_destroy_window(data->mlx, data->window);
		data->window = NULL;
	}
	if (data->scene)
		free_scene(data->scene);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
	free(data);
	exit (0);
	return (0);
}

// Press ESC to close the window
// Use keys to transform camera
static int	handle_keypress(int keycode, t_mlx_data *data)
{
	if (keycode == KEY_ESC)
		handle_close(data);
	return (0);
}

void	handle_events(t_mlx_data *data)
{
	mlx_hook(data->window, KeyPress, KeyPressMask, handle_keypress, data);
	mlx_hook(data->window, DestroyNotify, 0, handle_close, data);
	mlx_loop(data->mlx);
}
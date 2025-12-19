# include "render.h"

static void	mlx_put_color_to_image(t_mlx_data *data, t_color color, int x, int y)
{
	char	*dst_pixel;
	int		offset;

	offset = (y * data->line_length) + (x * (data->bits_per_pixel / 8));
	dst_pixel = data->addr + offset;
	*(unsigned int *)dst_pixel = (color.b << 16) | (color.g << 8) | color.r;
}

// Render loop
void	render_scene(t_mlx_data *data)
{
	int		i;
	int		j;
	t_color	color;
	t_ray	ray;

	j = 0;
	while (j < WIN_HEIGHT)
	{
		i = 0;
		while (i < WIN_WIDTH)
		{
			ray = generate_ray(&data->scene->camera, i, j);
			//Calculate intersection and find color;
			//following is for test:
			color.r = 0;
			color.g = 0;
			color.b = 255;
			mlx_put_color_to_image(data, color, i, j);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
}
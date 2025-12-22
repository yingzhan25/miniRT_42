# include "render.h"
# include "intersection.h"

/**
 * Generating ray to calculate intersection wth objects;
 * find the color according to the intersection;
 * render loop to render each pixel of image with correct color;
 * put image to window at once to avoid flickering;
 */
void	render_scene(t_mlx_data *data)
{
	int		i;
	int		j;
	t_color	color;
	t_ray	ray;
	t_hit	hit;

	j = 0;
	while (j < WIN_HEIGHT)
	{
		i = 0;
		while (i < WIN_WIDTH)
		{
			ray = generate_ray(&data->scene->camera, i, j);
			hit = intersect_object(ray, data->scene->objects);
			color = calculate_color(&hit, data->scene);
			mlx_put_color_to_image(data, color, i, j);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
}

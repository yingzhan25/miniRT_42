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
	t_intersection	hit;

	j = 0;
	while (j < WIN_HEIGHT)
	{
		i = 0;
		while (i < WIN_WIDTH)
		{
			ray = generate_ray(&data->scene->camera, i, j);
			//Calculate intersection and find color;
			//following is a silhouette of the sphere
			hit = ray_sphere_intersection(ray, data->scene->objects->data.sphere);
			if (!isnan(hit.t1) && !isnan(hit.t2) && (hit.t1 > 0 || hit.t2 > 0))
				color = data->scene->objects->color;//Sphere color
			else
				color = (t_color) {0, 0, 0};//Background color: black
			mlx_put_color_to_image(data, color, i, j);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
}

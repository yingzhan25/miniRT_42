#include "minirt_bonus.h"

void	load_texture_for_material(t_material *material, void *mlx)
{
	int	bpp;
	int	line_len;
	int	endian;

	material->img.xpm_img = mlx_xpm_file_to_image(mlx, material->xpm_path, \
		&material->img.width, &material->img.height);
	material->img.img_data = mlx_get_data_addr(material->img.xpm_img, &bpp, \
		&line_len, &endian);
	material->img.bits_per_pixel = bpp;
	material->img.line_length = line_len;
	material->img.endian = endian;
}

void	load_all_textures(t_scene *scene, void *mlx)
{
	t_object	*obj;

	obj = scene->objects;
	while (obj)
	{
		if (obj->material.texture == TEXTURE_XPM && obj->material.xpm_path)
			load_texture_for_material(&obj->material, mlx);
		obj = obj->next;
	}
}

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
	load_all_textures(scene, data->mlx);
	data->scene = scene;
}

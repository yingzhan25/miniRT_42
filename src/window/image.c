# include "render.h"

// Render each pixel of the image with corresponding color
void	mlx_put_color_to_image(t_mlx_data *data, t_color color, int x, int y)
{
	char	*dst_pixel;
	int		offset;

	offset = (y * data->line_length) + (x * (data->bits_per_pixel / 8));
	dst_pixel = data->addr + offset;
	*(unsigned int *)dst_pixel = (color.b << 16) | (color.g << 8) | color.r;
}
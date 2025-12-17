#ifndef RENDER_H
# define RENDER_H

# include "scene.h"
# include <math.h>

// Number of pixels, can be changed to 1920*1080
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define M_PI 3.14159265358979323846

// Ray definition
typedef struct s_ray {
	t_vec3 origin;
	t_vec3 direction;    // Must be normalized
} t_ray;

// Window and image data
typedef struct s_mlx_data {
	void	*mlx;      // MLX instance
	void	*window;	// Window pointer
	void	*image;	// Image buffer
	char	*addr;	    // Image pixel data address
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_scene	*scene;
} t_mlx_data;

#endif
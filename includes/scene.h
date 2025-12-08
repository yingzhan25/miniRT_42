
#include "../libft/includes/libft.h"
#include "../libft/includes/get_next_line.h"

#define	RATIO_MIN 0.0
#define	RATIO_MAX 1.0
#define	RGB_MIN 0
#define	RGB_MAX 255

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

/**
 *Struct of 3 elements
 */
typedef struct s_ambient
{
	double	ratio;
	t_vec3	color;
}	t_ambient;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	orientation;
	double	fov;
}	t_camera;

typedef struct s_light
{
	t_vec3	position;
	double	brightness;
	t_vec3	color;
}	t_light;

/**
 *Struct of 3 objects
 */

typedef	struct s_scene
{
	t_ambient	ambient;
	int			num_a;
	t_camera	camera;
	int			num_c;
	t_light		light;
	int			num_l;
	//Objects
}	t_scene;

int		parse_ambient(char **array, t_scene *scene);
int		parse_double(char *s, t_scene *scene);

//Utility functions
void	clean_array(char **arr);
int		count_dot(char *s);
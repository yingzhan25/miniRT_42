
#include "../libft/includes/libft.h"
#include "../libft/includes/get_next_line.h"
#include "vector.h"

#define	RATIO_MIN 0.0
#define	RATIO_MAX 1.0
#define	RGB_MAX 255

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
	int			fail_to_parse;
	t_ambient	ambient;
	int			num_a;
	t_camera	camera;
	int			num_c;
	t_light		light;
	int			num_l;
	//Objects
}	t_scene;

t_scene	*parse_scene(int ac, char *av[]);
int		parse_ambient(char **array, t_scene *scene);
int		parse_doubles(char *s, t_scene *scene);
int		parse_colors(char *s, t_scene *scene);

//Utility functions
int		count_array_element(char **array);
void	clean_array(char **arr);
int		check_dot(char *s);
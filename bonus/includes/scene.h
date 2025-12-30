#ifndef SCENE_H
# define SCENE_H

# include "../../libft/includes/libft.h"
# include "../../libft/includes/get_next_line.h"
# include "vector.h"
# include "error.h"
# include "stdio.h"

// function macros
# define P_VEC		parse_vector
# define P_ORI		parse_orientation
# define P_DIAM		parse_diametr
# define P_RAT		parse_ratio
# define P_FOV		parse_fov
# define P_COL		parse_colors
# define CH_A_D		check_array_double
# define C_A_E		count_array_element
# define P_SI		parse_single_obj
# define P_MLH		parse_material_light

# define RATIO_MIN 0.0
# define RATIO_MAX 1.0
# define RGB_MAX 255
# define FOV_MIN 0
# define FOV_MAX 180

/**
 * RGB color (0-255 range)
 */
typedef struct s_color {
	int	r;
	int	g;
	int	b;
}	t_color;

/**
 * Ambient light (singleton)
 */
typedef struct s_ambient {
	double	ratio;
	t_color	color;
}	t_ambient;

/**
 * Camera (singleton)
 */
typedef struct s_camera {
	t_vec3	position;
	t_vec3	orientation;
	double	fov;
	t_vec3	right;
	t_vec3	up;
	double	viewport_width;
	double	viewport_height;
}	t_camera;

/**
 * Light source (singleton in mandatory, multiple in bonus)
 */
typedef struct s_light {
	t_vec3			position;
	double			brightness;
	t_color			color;
	struct s_light	*next;
}	t_light;

typedef enum	e_texture_type {
	TEXTURE_NONE,
	TEXTURE_CHECKER,
	TEXTURE_XPM
}	t_texture_type;

typedef struct s_material {
	double			specular;
	double			shineness;
	t_texture_type	texture;
	double			checker_scale;
	char			*xpm_path;
}		t_material;

/**
 * Object type enumeration
 */
typedef enum e_obj_type {
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_obj_type;

/**
 * Sphere-specific data
 */
typedef struct s_sphere {
	t_vec3		center;
	double		diameter;
	double		radius;
	t_material	material;
}	t_sphere;

/**
 * Plane-specific data
 */
typedef struct s_plane {
	t_vec3		point;
	t_vec3		normal;
	t_material	material;
}	t_plane;

/**
 * Cylinder-specific data
 */
typedef struct s_cylinder {
	t_vec3		center;
	t_vec3		axis;
	double		diameter;
	double		radius;
	double		height;
	t_material	material;
}	t_cylinder;

/**
 * Generic object (linked list node)
 */
typedef struct s_object {
	t_obj_type		type;
	t_color			color;
	union {
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	} u_data;
	struct s_object	*next;
}	t_object;

/**
 * Complete scene
 */
typedef struct s_scene {
	int			fail_to_parse;
	t_ambient	ambient;
	int			num_a;
	t_camera	camera;
	int			num_c;
	t_light		light;
	int			num_l;
	t_object	*objects;
	int			obj_count;
}	t_scene;

/**
 * Parsing elements
 */
t_scene		*parse_scene(int ac, char *av[]);
int			parse_ambient(char **array, t_scene *scene);
int			parse_camera(char **array, t_scene *scene);
int			parse_light(char **array, t_scene *scene);
int			parse_objects(char	**array, t_scene *scene);
int			validate_scene(t_scene *scene);

/**
 * Utility functions
 */
int			parse_ratio(char *s, double *ratio);
int			parse_colors(char *s, t_color *color);
int			parse_fov(char *s, double *fov);
int			count_array_element(char **array);
void		clean_array(char **arr);
int			check_dot(char *s);
int			check_extension(char *s1, char *s2);
double		ft_atof(const char *str);
int			check_int(char *s);
int			check_double(char *s);
void		error(char *msg);
void		free_scene(t_scene *scene);

/**
 * Parsing objects
 */
int			check_array_double(char	**array, int (*f)(char *));
int			parse_vector(char *str, t_vec3	*vec);
int			is_zero_vec(t_vec3 *vec);
int			parse_orientation(char	*str, t_vec3 *vec);
int			is_object(char *str);
t_object	*create_cylinder(t_vec3 p, t_vec3 n, double *dm, t_color cl);
int			parse_cylinder(char **a, t_scene *scene);
t_object	*create_plane(t_vec3 point, t_vec3 normal, t_color color);
int			parse_plane(char **a, t_scene *scene);
t_object	*create_sphere(t_vec3 point, double diametr, t_color color);
int			parse_sphere(char **a, t_scene *scene);
int			parse_diametr(char *s, double *diametr);
void		parse_single_obj(t_scene *scene, t_object *obj);
void		print_scene(t_scene *scene);
int			parse_material(char	*str, t_material *ml);

#endif
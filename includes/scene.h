#ifndef SCENE_H
# define SCENE_H

#include "../libft/includes/libft.h"
#include "../libft/includes/get_next_line.h"
#include "vector.h"
#include "stdio.h"

#define	RATIO_MIN 0.0
#define	RATIO_MAX 1.0
#define	RGB_MAX 255

// RGB color (0-255 range)
typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;

// Ambient light (singleton)
typedef struct s_ambient {
    double ratio;        // 0.0 to 1.0
    t_color color;
} t_ambient;

// Camera (singleton)
typedef struct s_camera {
    t_vec3 position;
    t_vec3 orientation;  // Normalized direction vector
    double fov;          // Field of view in degrees (0-180)
    // Computed values for ray generation:
    t_vec3 right;        // Camera right vector
    t_vec3 up;           // Camera up vector
    double viewport_width;
    double viewport_height;
} t_camera;

// Light source (singleton in mandatory, multiple in bonus)
typedef struct s_light {
    t_vec3 position;
    double brightness;   // 0.0 to 1.0
    t_color color;       // Parsed but unused in mandatory
} t_light;

// Object type enumeration
typedef enum e_obj_type {
    OBJ_SPHERE,
    OBJ_PLANE,
    OBJ_CYLINDER
} t_obj_type;

// Sphere-specific data
typedef struct s_sphere {
    t_vec3 center;
    double diameter;
    double radius;       // Computed: diameter / 2
} t_sphere;

// Plane-specific data
typedef struct s_plane {
    t_vec3 point;
    t_vec3 normal;       // Normalized
} t_plane;

// Cylinder-specific data
typedef struct s_cylinder {
    t_vec3 center;
    t_vec3 axis;         // Normalized
    double diameter;
    double radius;       // Computed: diameter / 2
    double height;
} t_cylinder;

// Generic object (linked list node)
typedef struct s_object {
    t_obj_type type;
    t_color color;
    union {
        t_sphere sphere;
        t_plane plane;
        t_cylinder cylinder;
    } data;
    struct s_object *next;
} t_object;

// Complete scene
typedef struct s_scene {
    int			fail_to_parse;
	t_ambient	ambient;
	int			num_a;
	t_camera	camera;
	int			num_c;
	t_light		light;
	int			num_l;
    t_object *objects;   // Linked list of all objects
    int obj_count;
} t_scene;

t_scene	*parse_scene(int ac, char *av[]);
int		parse_ambient(char **array, t_scene *scene, char *name);
int		parse_ratio(char *s, t_scene *scene, char *name, char *sub_name);
int		parse_colors(char *s, t_scene *scene, char *name, char *sub_name);
int		parse_tuples(char *s, t_scene *scene, char *name, char *sub_name);
int		parse_objects(char	**array, t_scene *scene);

//Utility functions
int		count_array_element(char **array);
void	clean_array(char **arr);
int		check_dot(char *s);
int 	check_extension(char *s1, char *s2);
double	ft_atof(const char *str);
int		check_int(char *s, char *name, char *sub_name);
int		check_double(char *s, char *name, char *sub_name);
void	error(char *name, char *sub_name, char *msg);

// Utility functions for parsing the objects
int		is_object(char *str);
int		check_array_double(char	**array);
int		parse_vector(char *str, t_vec3	*vec);
int		is_zero_vec(t_vec3 *vec);
int		parse_orientation(char	*str, t_vec3 *vec);


#endif
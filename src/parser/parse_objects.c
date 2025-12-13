#include "../../includes/minirt.h"

/*
** check_array_double: check whether all strings in the array are valid doubles
*/
int	check_array_double(char	**array, int (*f)(char *))
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (f(array[i]))
			return (1);
		i++;
	}
	return (0);
}

/*
** parse_vector: parse a string into a t_vec3 structure
*/
int	parse_vector(char *str, t_vec3	*vec)
{
    char	**split;

    split = ft_split(str, ',');
    if (!split || count_array_element(split) != 3
		||	check_array_double(split, check_double))
        return (1);
    (*vec).x = ft_atof(split[0]);
    (*vec).y = ft_atof(split[1]);
    (*vec).z = ft_atof(split[2]);

    return (clean_array(split), 0);
}

/*
** is_zero_vec: check whether the vector is a zero vector
*/
int	is_zero_vec(t_vec3 *vec)
{
	if ((*vec).x == 0 && (*vec).y == 0 && (*vec).z == 0)
        return (1);
	return (0);
}

/*
** parse_orientation: parse and normalize an orientation vector
*/
int	parse_orientation(char	*str, t_vec3 *vec)
{
	if (parse_vector(str, vec))
		return (1);
	*vec = vec_normalize(*vec);
	return (0);
}

/*
** parse_color: parse a string into a t_color structure
*/
int	parse_color(char *str, t_color *color)
{
	char	**split;

    split = ft_split(str, ',');
	if (!split || count_array_element(split) != 3
		||	check_array_double(split, check_int))
        return (1);
	(*color).r = ft_atof(split[0]);
    (*color).g = ft_atof(split[1]);
    (*color).b = ft_atof(split[2]);
	if ((*color).r > RGB_MAX || (*color).g > RGB_MAX || (*color).b > RGB_MAX)
		return (error(A_INVL_COLOR), clean_array(split), 1);
	return (clean_array(split), 0);
}

/*
* parse_single_obj: add a single object to the scene's object list
*/
void	parse_single_obj(t_scene *scene, t_object *obj)
{
	t_object	*current;

	if (!scene->objects)
		scene->objects = obj;
	else
	{
		current = scene->objects;
		while (current->next)
			current = current->next;
		current->next = obj;
	}
}

/*
** create_plane: create a new plane object
*/
t_object* create_plane(t_vec3 point, t_vec3 normal, t_color color)
{
	t_object *obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return NULL;
	obj->type = OBJ_PLANE;
	obj->color = color;
	obj->data.plane.point = point;
	obj->data.plane.normal = normal;
	obj->next = NULL;
	return (obj);
}

int	parse_plane(char **array, t_scene *scene)
{
	t_object	*plane;
	t_vec3		vec_coor;
	t_vec3		vec_norm;
	t_color		color;

	if (!array[0] || count_array_element(array) != 3)
		return (1);
	if (parse_vector(array[0], &vec_coor) && is_zero_vec(&vec_coor))
		return (1);
	if (parse_orientation(array[1], &vec_norm))
		return (1);
	if (parse_color(array[2], &color))
		return (1);
	plane = create_plane(vec_coor, vec_norm, color);
	if (!plane)
		return (1);
	parse_single_obj(scene, plane);
	return (0);
}

int	parse_diametr(char *s, double *diametr)
{
	if (check_double(s))
		return (1);
	*diametr = ft_atof(s);
	return (0);
}

t_object* create_sphere(t_vec3 point, double diametr, t_color color)
{
	t_object *obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return NULL;
	obj->type = OBJ_SPHERE;
	obj->color = color;
	obj->data.sphere.center = point;
	obj->data.sphere.diameter = diametr;
	obj->data.sphere.radius = diametr / 2;
	obj->next = NULL;
	return (obj);
}

int	parse_sphere(char **array, t_scene *scene)
{
	t_object	*sphere;
	t_vec3		vec_coor;
	t_color		color;
	double		diametr;

	if (!array[0] || count_array_element(array) != 3)
		return (1);
	if (parse_vector(array[0], &vec_coor) && is_zero_vec(&vec_coor))
		return (1);
	if (parse_diametr(array[1], &diametr))
		return (1);
	if (parse_color(array[2], &color))
		return (1);
	sphere = create_sphere(vec_coor, diametr, color);
	if (!sphere)
		return (1);
	parse_single_obj(scene, sphere);
	return (0);
}

t_object* create_cylinder(t_vec3 point, t_vec3 normal, double diametr, double height, t_color color)
{
	t_object *obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return NULL;
	obj->type = OBJ_CYLINDER;
	obj->color = color;
	obj->data.cylinder.center = point;
	obj->data.cylinder.axis = normal;
	obj->data.cylinder.diameter = diametr;
	obj->data.cylinder.height = height;
	obj->data.cylinder.radius = diametr / 2;
	obj->next = NULL;
	return (obj);
}

int	parse_cylinder(char **array, t_scene *scene)
{
	t_object	*cylinder;
	t_vec3		vec_coor;
	t_vec3		vec_norm;
	t_color		color;
	double		diametr;
	double		height;

	if (!array[0] || count_array_element(array) != 5)
		return (1);
	if (parse_vector(array[0], &vec_coor) && is_zero_vec(&vec_coor))
		return (1);
	if (parse_orientation(array[1], &vec_norm))
		return (1);
	if (parse_diametr(array[2], &diametr))
		return (1);
	if (parse_diametr(array[3], &height))
		return (1);
	if (parse_color(array[4], &color))
		return (1);
	cylinder = create_cylinder(vec_coor, vec_norm, diametr, height, color);
	if (!cylinder)
		return (1);
	parse_single_obj(scene, cylinder);
	return (0);
}

int	parse_objects(char	**array, t_scene *scene)
{
	if (!ft_strcmp(array[0], "pl"))
		return (parse_plane(++array, scene));
	if (!ft_strcmp(array[0], "sp"))
		return (parse_sphere(++array, scene));
	if (!ft_strcmp(array[0], "cy"))
		return (parse_cylinder(++array, scene));
	return (0);
}

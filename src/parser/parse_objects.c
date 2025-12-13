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
	if (is_zero_vec(vec))
		return (1);
	return (0);
}

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

int	parse_plane(char **array, t_scene *scene)
{
	t_object	*plane;
	t_vec3		vec_coor;
	t_vec3		vec_norm;
	t_color		color;

	if (!array[0] || count_array_element(array) != 3)
		return (1);
	if (parse_orientation(array[0], &vec_coor))
		return (1);
	if (parse_orientation(array[1], &vec_norm))
		return (1);
	if (parse_color(array[2], &color))
		return (1);
	plane = malloc(sizeof(t_object));
	if (!plane)
		return (1);
	plane->type = OBJ_PLANE;
	plane->color = color;
	plane->data.plane.point = vec_coor;
	plane->data.plane.normal = vec_norm;
	plane->next = NULL;
	scene->objects = plane;
	return (0);
}

int	parse_objects(char	**array, t_scene *scene)
{
	printf("surprise1");
	if (!ft_strcmp(array[0], "pl"))
		return (parse_plane(++array, scene));
	return (0);
}

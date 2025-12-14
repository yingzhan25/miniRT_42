#include "../../includes/minirt.h"

/*
** parse_vector: parse a string into a t_vec3 structure
*/
int	parse_vector(char *str, t_vec3	*vec)
{
    char	**split;

    split = ft_split(str, ',');
    if (!split || count_array_element(split) != 3
		||	check_array_double(split, check_double))
        return (error(O_INVL_ARG), 1);
    (*vec).x = ft_atof(split[0]);
    (*vec).y = ft_atof(split[1]);
    (*vec).z = ft_atof(split[2]);

    return (clean_array(split), 0);
}

/*
** parse_orientation: parse and normalize an orientation vector
*/
int	parse_orientation(char	*str, t_vec3 *vec)
{
	if (parse_vector(str, vec))
		return (error(O_INVL_ORT), 1);
	*vec = vec_normalize(*vec);
	return (0);
}

/*
** parse_color: parse a string into a t_color structure
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
*/

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
** parse_objects: determine object type and parse accordingly
*/
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

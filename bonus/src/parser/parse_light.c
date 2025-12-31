#include "minirt_bonus.h"

/**
 * Create a new light
 */
t_light	*create_light(t_vec3 pos, double bright, t_color color)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		return (error(FAIL_MEM_ALLOC), NULL);
	light->position = pos;
	light->brightness = bright;
	light->color = color;
	light->next = NULL;
	return (light);
}
/**
 * Add a single light to light lists
 */
void	link_single_light(t_scene *scene, t_light *light)
{
	t_light	*current;

	if (!scene->lights)
		scene->lights = light;
	else
	{
		current = scene->lights;
		while (current->next)
			current = current->next;
		current->next = light;
	}
}

/**
 * Multiple lights are required in bonus part;
 * check whether the position is valid;
 * check whether the color is valid;
 * check whether the brightness is valid;
 * allocate memory for each light and add it to linked list
 */
int	parse_light(char **array, t_scene *scene)
{
	t_vec3	pos;
	double	bright;
	t_color	color;
	t_light	*light;

	scene->num_l = 1;
	if (!array || C_A_E(array) != 4 || \
		!array[0] || !array[1] || !array[2] || !array[3])
		return (error(L_INVL_ARG), 1);
	if (P_VEC(array[1], &pos))
		return (error(L_INVL_POS), 1);
	if (P_RAT(array[2], &bright))
		return (error(L_INVL_BRIGHT), 1);
	if (P_COL(array[3], &color))
		return (error(L_INVL_COLOR), 1);
	light = create_light(pos, bright, color);
	if (!light)
		return (1);
	return (link_single_light(scene, light), 0);
}

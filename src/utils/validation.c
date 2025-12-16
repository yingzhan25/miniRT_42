#include "scene.h"

/**
 * Check whether all the parsing is valid or not
 */
int	validate_scene(t_scene *scene)
{
	if (scene->num_a != 1 || scene->num_c != 1 || scene->num_l != 1)
		return (error(LACK_ELEMENT), 1);
	if (scene->obj_count == 0)
		return (error(UNDEFINE_OBJS), 1);
	if (scene->fail_to_parse)
		return (1);
	return (0);
}
#include "../../includes/minirt.h"

/*
** create_plane: create a new plane object
*/
t_object* create_plane(t_vec3 point, t_vec3 normal, t_color color)
{
	t_object *obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return (error(FAIL_MEM_ALLOC), NULL);
	obj->type = OBJ_PLANE;
	obj->color = color;
	obj->data.plane.point = point;
	obj->data.plane.normal = normal;
	obj->next = NULL;
	return (obj);
}

/*
** parse_plane: parse a plane object from input array
*/
int	parse_plane(char **a, t_scene *scene)
{
	t_vec3		co;
	t_vec3		no;
	t_color		cl;
	t_object	*pl;

	if (! a[0] || count_array_element(a) != 3)
		return (error(O_INVL_ARG), 1);
	if (P_VEC(a[0], &co) || is_zero_vec(&co) || P_ORI(a[1], &no)
		 || P_COL(a[2], &cl))
		return (1);
	pl = create_plane(co, no, cl);
	return (!pl || (parse_single_obj(scene, pl), 0));
}

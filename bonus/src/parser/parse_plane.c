#include "minirt_bonus.h"

/*
** create_plane: create a new plane object
*/
t_object	*create_plane(t_vec3 point, t_vec3 normal, t_color color)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return (error(FAIL_MEM_ALLOC), NULL);
	obj->type = OBJ_PLANE;
	obj->color = color;
	obj->u_data.plane.point = point;
	obj->u_data.plane.normal = normal;
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
	t_material	ml;
	t_object	*pl;

	if (! a[0] || C_A_E(a) != 6)
		return (error(O_INVL_ARG), 1);
	if (P_VEC(a[0], &co))
		return (error(O_INVL_POS), 1);
	if (P_ORI(a[1], &no))
		return (error(O_INVL_ORT), 1);
	if (P_COL(a[2], &cl))
		return (error(O_INVL_COL), 1);
	pl = create_plane(co, no, cl);
	return (!pl || (P_SI(scene, pl), scene->obj_count++, 0));
}

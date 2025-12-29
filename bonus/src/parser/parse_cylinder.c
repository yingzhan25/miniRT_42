#include "minirt.h"

/*
** create_cylinder: create a new cylinder object
*/
t_object	*create_cylinder(t_vec3 p, t_vec3 n, double *dm, t_color cl)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return (error(FAIL_MEM_ALLOC), NULL);
	obj->type = OBJ_CYLINDER;
	obj->color = cl;
	obj->u_data.cylinder.center = p;
	obj->u_data.cylinder.axis = n;
	obj->u_data.cylinder.diameter = dm[0];
	obj->u_data.cylinder.height = dm[1];
	obj->u_data.cylinder.radius = dm[0] / 2;
	obj->next = NULL;
	return (obj);
}

/*
** parse_cylinder: parse a cylinder object from input array
*/
int	parse_cylinder(char **a, t_scene *scene)
{
	t_vec3		co;
	t_vec3		no;
	t_color		cl;
	double		dm[2];
	t_object	*cy;

	if (!a[0] || C_A_E(a) != 5)
		return (error(O_INVL_ARG), 1);
	if (P_VEC(a[0], &co))
		return (error(O_INVL_POS), 1);
	if (P_ORI(a[1], &no))
		return (error(O_INVL_ORT), 1);
	if (P_DIAM(a[2], &dm[0]) || dm[0] <= 0)
		return (error(O_INVL_DIAM), 1);
	if (P_DIAM(a[3], &dm[1]) || dm[1] <= 0)
		return (error(O_INVL_HEIGHT), 1);
	if (P_COL(a[4], &cl))
		return (error(O_INVL_COL), 1);
	cy = create_cylinder(co, no, dm, cl);
	return (!cy || (P_SI(scene, cy), scene->obj_count++, 0));
}

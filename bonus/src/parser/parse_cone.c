#include "minirt_bonus.h"

/*
** create_cone: create a new cone object
*/
t_object	*create_cone(t_vec3 p, t_vec3 n, double *dm, t_material ml)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return (error(FAIL_MEM_ALLOC), NULL);
	obj->type = OBJ_CONE;
	obj->material = ml;
	obj->u_data.cone.apex = p;
	obj->u_data.cone.axis = n;
	obj->u_data.cone.diameter = dm[0];
	obj->u_data.cone.height = dm[1];
	obj->u_data.cone.radius = dm[0] / 2;
	obj->next = NULL;
	return (obj);
}

/*
** parse_cone: parse a cone object from input array
*/
int	parse_cone(char **a, t_scene *scene)
{
	t_vec3		ap;
	t_vec3		no;
	double		dm[2];
	t_object	*cone;
	t_material	ml;

	if (!a[0] || C_A_E(a) != 9)
		return (error(O_INVL_ARG), 1);
	if (P_VEC(a[0], &ap))
		return (error(O_INVL_POS), 1);
	if (P_ORI(a[1], &no))
		return (error(O_INVL_ORT), 1);
	if (P_DIAM(a[2], &dm[0]) || dm[0] <= 0)
		return (error(O_INVL_DIAM), 1);
	if (P_DIAM(a[3], &dm[1]) || dm[1] <= 0)
		return (error(O_INVL_HEIGHT), 1);
	if (P_COL(a[4], &(ml.color)))
		return (error(O_INVL_COL), 1);
	if (parse_ratio(a[5], &(ml.specular)))
		return (error(MAT_INVL_VAL), 1);
	if (parse_shineness(a[6], &(ml.shineness)))
		return (error(MAT_INVL_VAL), 1);
	if (parse_texture_type(a[7], &(ml.texture)))
		return (error(MAT_INVL_VAL), 1);
	if (parse_texture_path(a[8], &(ml)))
		return (error(MAT_INVL_VAL), 1);
	cone = create_cone(ap, no, dm, ml);
	return (!cone || (P_SI(scene, cone), scene->obj_count++, 0));
}

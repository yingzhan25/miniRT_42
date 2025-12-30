#include "minirt_bonus.h"

/*
** create_sphere: create a new sphere object
*/
t_object	*create_sphere(t_vec3 point, double diametr, t_material ml)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return (error(FAIL_MEM_ALLOC), NULL);
	obj->type = OBJ_SPHERE;
	obj->material = ml;
	obj->u_data.sphere.center = point;
	obj->u_data.sphere.diameter = diametr;
	obj->u_data.sphere.radius = diametr / 2;
	obj->next = NULL;
	return (obj);
}

/*
** parse_sphere: parse a sphere object from input array
*/
int	parse_sphere(char **a, t_scene *scene)
{
	t_vec3		co;
	double		dm;
	t_object	*sp;
	t_material	ml;

	if (!a[0] || C_A_E(a) != 7)
		return (error(O_INVL_ARG), 1);
	if (P_VEC(a[0], &co))
		return (error(O_INVL_ORT), 1);
	if (P_DIAM(a[1], &dm) || dm <= 0)
		return (error(O_INVL_DIAM), 1);
	if (P_COL(a[2], &(ml.color)))
		return (error(O_INVL_COL), 1);
	if (parse_ratio(a[3], &(ml.specular)))
		return (error(MAT_INVL_VAL), 1);
	if (parse_shineness(a[4], &(ml.shineness)))
		return (error(MAT_INVL_VAL), 1);
	if (parse_texture_type(a[5], &(ml.texture)))
		return (error(MAT_INVL_VAL), 1);
	if (parse_texture_path(a[6], &(ml)))
		return (error(MAT_INVL_VAL), 1);
	sp = create_sphere(co, dm, ml);
	return (!sp || (P_SI(scene, sp), scene->obj_count++, 0));
}

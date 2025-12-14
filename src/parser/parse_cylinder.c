#include "../../includes/minirt.h"

/*
** create_cylinder: create a new cylinder object
*/
t_object* create_cylinder(t_vec3 p, t_vec3 n, double dm, double ht, t_color cl)
{
	t_object *obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return (error(FAIL_MEM_ALLOC), NULL);
	obj->type = OBJ_CYLINDER;
	obj->color = cl;
	obj->data.cylinder.center = p;
	obj->data.cylinder.axis = n;
	obj->data.cylinder.diameter = dm;
	obj->data.cylinder.height = ht;
	obj->data.cylinder.radius = dm / 2;
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

	if (!a[0] || count_array_element(a) != 5)
		return (error(O_INVL_ARG), 1);
	if (P_VEC(a[0], &co) || is_zero_vec(&co) || P_ORI(a[1], &no)
		|| P_DIAM(a[2], &dm[0]) || P_DIAM(a[3], &dm[1]) || P_COL(a[4], &cl))
		return (1);
	cy = create_cylinder(co, no, dm[0], dm[1], cl);
	return (!cy || (parse_single_obj(scene, cy), 0));
}

#include "../../includes/minirt.h"

/*
** create_sphere: create a new sphere object
*/
t_object* create_sphere(t_vec3 point, double diametr, t_color color)
{
	t_object *obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return (error(FAIL_MEM_ALLOC), NULL);
	obj->type = OBJ_SPHERE;
	obj->color = color;
	obj->data.sphere.center = point;
	obj->data.sphere.diameter = diametr;
	obj->data.sphere.radius = diametr / 2;
	obj->next = NULL;
	return (obj);
}

/*
** parse_sphere: parse a sphere object from input array
*/
int	parse_sphere(char **a, t_scene *scene)
{
	t_vec3		co;
	t_color		cl;
	double		dm;
	t_object	*sp;

	if (!a[0] || count_array_element(a) != 3)
		return (error(O_INVL_ARG), 1);
	if (P_VEC(a[0], &co) || is_zero_vec(&co) || P_DIAM(a[1], &dm) 
		|| P_COL(a[2], &cl))
		return (1);
	sp = create_sphere(co, dm, cl);
	return (!sp || (parse_single_obj(scene, sp), 0));
}

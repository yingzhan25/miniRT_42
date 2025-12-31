#include "minirt_bonus.h"

static void	print_texture_type(t_texture_type texture)
{
	if (texture == TEXTURE_NONE)
		printf("texture: NONE\n");
	else if (texture == TEXTURE_CHECKER)
		printf("texture: CHECKER\n");
	else if (texture == TEXTURE_XPM)
		printf("texture: XPM\n");
}

static void	print_material(const t_material *mat)
{
	printf("--Material--\n");
	printf("specular: %f\n", mat->specular);
	printf("shineness: %f\n", mat->shineness);
	print_texture_type(mat->texture);
	if (mat->xpm_path)
		printf("xpm_path: %s\n", mat->xpm_path);
	else
		printf("xpm_path: (null)\n");
	printf("--Color--\n");
	printf("r: %d\n", mat->color.r);
	printf("g: %d\n", mat->color.g);
	printf("b: %d\n", mat->color.b);
}

static void	print_object(const t_object *obj)
{
	if (obj->type == OBJ_PLANE)
	{
		printf("========Plane========\n");
		printf("x: %f\n", obj->u_data.plane.point.x);
		printf("y: %f\n", obj->u_data.plane.point.y);
		printf("z: %f\n", obj->u_data.plane.point.z);
		printf("nx: %f\n", obj->u_data.plane.normal.x);
		printf("ny: %f\n", obj->u_data.plane.normal.y);
		printf("nz: %f\n", obj->u_data.plane.normal.z);
	}
	else if (obj->type == OBJ_SPHERE)
	{
		printf("========Sphere========\n");
		printf("x: %f\n", obj->u_data.sphere.center.x);
		printf("y: %f\n", obj->u_data.sphere.center.y);
		printf("z: %f\n", obj->u_data.sphere.center.z);
		printf("diameter: %f\n", obj->u_data.sphere.diameter);
	}
	else if (obj->type == OBJ_CYLINDER)
	{
		printf("========Cylinder========\n");
		printf("x: %f\n", obj->u_data.cylinder.center.x);
		printf("y: %f\n", obj->u_data.cylinder.center.y);
		printf("z: %f\n", obj->u_data.cylinder.center.z);
		printf("nx: %f\n", obj->u_data.cylinder.axis.x);
		printf("ny: %f\n", obj->u_data.cylinder.axis.y);
		printf("nz: %f\n", obj->u_data.cylinder.axis.z);
		printf("diameter: %f\n", obj->u_data.cylinder.diameter);
		printf("height: %f\n", obj->u_data.cylinder.height);
	}
	else if (obj->type == OBJ_CONE)
	{
		printf("========Cylinder========\n");
		printf("x: %f\n", obj->u_data.cone.apex.x);
		printf("y: %f\n", obj->u_data.cone.apex.y);
		printf("z: %f\n", obj->u_data.cone.apex.z);
		printf("nx: %f\n", obj->u_data.cone.axis.x);
		printf("ny: %f\n", obj->u_data.cone.axis.y);
		printf("nz: %f\n", obj->u_data.cone.axis.z);
		printf("diameter: %f\n", obj->u_data.cone.diameter);
		printf("height: %f\n", obj->u_data.cone.height);
	}
	print_material(&obj->material);
}

static void	print_light(const t_light *light)
{
	printf("========Light========\n");
	printf("x: %f\n", light->position.x);
	printf("y: %f\n", light->position.y);
	printf("z: %f\n", light->position.z);
	printf("r: %d\n", light->color.r);
	printf("g: %d\n", light->color.g);
	printf("b: %d\n", light->color.b);
	printf("brightness: %f\n", light->brightness);
}

void	print_scene(t_scene *scene)
{
	t_object	*obj;
	t_light		*light;

	printf("========Ambient========\n");
	printf("ratio: %f\n", scene->ambient.ratio);
	printf("r: %d\n", scene->ambient.color.r);
	printf("g: %d\n", scene->ambient.color.g);
	printf("b: %d\n", scene->ambient.color.b);
	printf("========Camera========\n");
	printf("x: %f\n", scene->camera.position.x);
	printf("y: %f\n", scene->camera.position.y);
	printf("z: %f\n", scene->camera.position.z);
	printf("nx: %f\n", scene->camera.orientation.x);
	printf("ny: %f\n", scene->camera.orientation.y);
	printf("nz: %f\n", scene->camera.orientation.z);
	printf("fov: %f\n", scene->camera.fov);
	light = scene->lights;
	while (light)
	{
		print_light(light);
		light = light->next;
	}
	obj = scene->objects;
	while (obj)
	{
		print_object(obj);
		obj = obj->next;
	}
}

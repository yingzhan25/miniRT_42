#include "render.h"

/**
 * Check whether forward is close to y-axis;
 * if yes, use z-axis, otherwise use y-axis as world-up, x-axis as backup
 */
void	setup_camera(t_camera *cam)
{
	t_vec3	forward;
	t_vec3	world_up;

	forward = cam->orientation;
	if (fabs(forward.y) > 1.0 - EPSILON)
		world_up = (t_vec3){0, 0, 1};
	else
		world_up = (t_vec3){0, 1, 0};
	cam->right = vec_normalize(vec_cross(world_up, forward));
	if (is_zero_vec(&cam->right))
	{
		world_up = (t_vec3){1, 0, 0};
		cam->right = vec_normalize(vec_cross(world_up, forward));
	}
	cam->up = vec_normalize(vec_cross(forward, cam->right));
}
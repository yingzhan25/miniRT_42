// 3. Sub-problem (Canvas and Viewport)
// Requirement: to initialize viewport and convert canvas to viewport
//     Input: Pixel coordinates (x, y) on canvas
//     Output: 3D direction vector for the ray
//     Process:
//         Normalize pixel coordinates to [-1, 1] range
//         Scale to viewport dimensions
//         Create direction vector from camera to viewport point

#include "vector3D.h"

#define CANVAS_WIDTH 800
#define CANVAS_HEIGHT 600
#define VIEWPORT_WIDTH 4
#define VIEWPORT_HEIGHT 3
#define DISTANCE 1

typedef	struct s_pixel
{
	float	x;
	float	y;
}	t_pixel;

t_pixel		normalized_canvas(t_pixel pixel)
{
	t_pixel	new_pixel;

	new_pixel.x = (2.0f * pixel.x / CANVAS_WIDTH) -1.0f;
	new_pixel.y = 1.0f - (2.0f * pixel.y / CANVAS_HEIGHT);
	return (new_pixel);
}

t_vector	canvas_to_viewport(t_pixel pixel)
{
	t_pixel	normalized_pixel;
	t_vector	direction;

	normalized_pixel = normalized_canvas(pixel);
	direction.x = normalized_pixel.x * (VIEWPORT_WIDTH / 2.0f);
	direction.y = normalized_pixel.y * (VIEWPORT_HEIGHT / 2.0f);
	direction.z = DISTANCE;
	direction = normalization(direction);
	return (direction);
}
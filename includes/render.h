#ifndef RENDER_H
# define RENDER_H

# include "scene.h"
# include <math.h>

// Ray definition
typedef struct s_ray {
	t_vec3 origin;
	t_vec3 direction;    // Must be normalized
} t_ray;

#endif
#ifndef ERROR_H
# define ERROR_H

# define INVALID_ARG_NUM "Usage: ./minirt <scene.rt>"
# define FAIL_OPEN_FILE "Cannot open file"
# define FAIL_MEM_ALLOC "Memory allocation failed"
# define UNDEFINE_OBJS "Undefined element/object type"

# define A_MULTIPLE_DEF "Ambient: More than 1 definition"
# define INVALID_A_ARG "Ambient: Usage: A ratio [r,g,b]"
// # define INVALID_L_ARG "Usage: A ratio [r,g,b]"
# define A_INVL_RATIO "Ambient: Ratio: Invalid input"
# define A_EXCD_RATIO "Ambient: Ratio: Exceed valid range"
# define A_INVL_COLOR "Ambient: Color: Invalid input"
# define A_EXCD_COLOR "Ambient: Color: Exceed valid range"

# define C_MULTIPLE_DEF "Camera: More than 1 definition"
# define INVALID_C_ARG "Usage: C [x,y,z] [nx,ny,nz] fov"
# define C_INVL_POS "Camera: Position: Invalid input"
# define C_INVL_ORT "Camera: Orientation: Invalid input"
# define C_EXCD_ORT "Camera: Orientation: Not a vector"
# define C_INVL_FOV "Camera: FOV: Invalid input"
# define C_EXCD_FOV "Camera: FOV: Exceed valid range"

#endif
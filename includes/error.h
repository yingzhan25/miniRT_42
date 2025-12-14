#ifndef ERROR_H
# define ERROR_H

# define INVALID_ARG_NUM "Usage: ./minirt <scene.rt>"
# define FAIL_OPEN_FILE "Cannot open file"
# define FAIL_MEM_ALLOC "Memory allocation failed"
# define UNDEFINE_OBJS "Undefined element/object type"

# define A_MULTIPLE_DEF "Ambient: More than 1 definition"
# define A_INVL_ARG "Ambient: Usage: A ratio [r,g,b]"
# define A_INVL_RATIO "Ambient: Ratio: Invalid input"
# define A_INVL_COLOR "Ambient: Color: Invalid input"

# define C_MULTIPLE_DEF "Camera: More than 1 definition"
# define C_INVL_ARG "Usage: C [x,y,z] [nx,ny,nz] fov"
# define C_INVL_POS "Camera: Position: Invalid input"
# define C_INVL_ORT "Camera: Orientation: Invalid input"
# define C_INVL_FOV "Camera: FOV: Invalid input"

# define L_MULTIPLE_DEF "Light: More than 1 definition"
# define L_INVL_ARG "Usage: L [x,y,z] brightness [r, g, b]"
# define L_INVL_POS "Light: Position: Invalid input"
# define L_INVL_BRIGHT "Light: Brightness: Invalid input"
# define L_INVL_COLOR "Light: Color: Invalid input"

# define O_INVL_CHAR "Object: Invalid character in input"
# define O_INVL_ARG "Object: Invalid number of arguments"
# define O_INVL_POS "Object: Position: Invalid input"
# define O_INVL_ORT "Object: Orientation: Invalid input"
# define O_INVL_DIAM "Object: Diameter: Invalid input"
# define O_INVL_HEIGHT "Object: Height: Invalid input"

#endif
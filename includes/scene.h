#ifndef SCENE_H
# define SCENE_H

// Core vector type for 3D coordinates, directions, and colors
typedef struct s_vec3 {
    double x;
    double y;
    double z;
} t_vec3;

// RGB color (0-255 range)
typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;

// Ambient light (singleton)
typedef struct s_ambient {
    double ratio;        // 0.0 to 1.0
    t_color color;
} t_ambient;

// Camera (singleton)
typedef struct s_camera {
    t_vec3 position;
    t_vec3 orientation;  // Normalized direction vector
    double fov;          // Field of view in degrees (0-180)
    // Computed values for ray generation:
    t_vec3 right;        // Camera right vector
    t_vec3 up;           // Camera up vector
    double viewport_width;
    double viewport_height;
} t_camera;

// Light source (singleton in mandatory, multiple in bonus)
typedef struct s_light {
    t_vec3 position;
    double brightness;   // 0.0 to 1.0
    t_color color;       // Parsed but unused in mandatory
} t_light;

// Object type enumeration
typedef enum e_obj_type {
    OBJ_SPHERE,
    OBJ_PLANE,
    OBJ_CYLINDER
} t_obj_type;

// Sphere-specific data
typedef struct s_sphere {
    t_vec3 center;
    double diameter;
    double radius;       // Computed: diameter / 2
} t_sphere;

// Plane-specific data
typedef struct s_plane {
    t_vec3 point;
    t_vec3 normal;       // Normalized
} t_plane;

// Cylinder-specific data
typedef struct s_cylinder {
    t_vec3 center;
    t_vec3 axis;         // Normalized
    double diameter;
    double radius;       // Computed: diameter / 2
    double height;
} t_cylinder;

// Generic object (linked list node)
typedef struct s_object {
    t_obj_type type;
    t_color color;
    union {
        t_sphere sphere;
        t_plane plane;
        t_cylinder cylinder;
    } data;
    struct s_object *next;
} t_object;

// Complete scene
typedef struct s_scene {
    t_ambient ambient;
    t_camera camera;
    t_light light;
    t_object *objects;   // Linked list of all objects
    int obj_count;
} t_scene;

#endif
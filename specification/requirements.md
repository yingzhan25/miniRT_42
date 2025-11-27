# Requirements Document

## Introduction

The miniRT project is a minimal ray tracer implementation in C that uses the MiniLibX graphics library. The system will parse scene description files (.rt format), perform ray tracing calculations to render 3D scenes with geometric objects (spheres, planes, cylinders), and display the resulting images with proper lighting and shading. The project emphasizes mathematical precision, memory safety, and adherence to the 42 coding standards.

## Glossary

- **Ray Tracer**: The complete system that generates 2D images from 3D scene descriptions using ray tracing algorithms
- **MiniLibX**: The graphics library used for window management and image display
- **Scene Parser**: The component that reads and validates .rt scene description files
- **Renderer**: The component that performs ray casting, intersection calculations, and pixel color computation
- **Geometric Object**: Any renderable 3D shape (sphere, plane, or cylinder) in the scene
- **Intersection Handler**: The component that calculates ray-object intersection points
- **Lighting Engine**: The component that computes ambient, diffuse, and shadow effects
- **Window Manager**: The component that handles user input and window lifecycle events

## Requirements

### Requirement 1: Scene File Parsing

**User Story:** As a user, I want to provide a .rt scene file as input, so that the ray tracer can render the described 3D scene

#### Acceptance Criteria

1. WHEN the Ray Tracer receives a command-line argument, THE Scene Parser SHALL validate that exactly one argument is provided and it has a .rt extension
2. WHEN the Scene Parser reads a .rt file, THE Scene Parser SHALL accept scene elements in any order with arbitrary whitespace and empty lines
3. WHEN the Scene Parser encounters an ambient light element (A), THE Scene Parser SHALL parse the lighting ratio (0.0-1.0) and RGB color values (0-255)
4. WHEN the Scene Parser encounters a camera element (C), THE Scene Parser SHALL parse the position coordinates, normalized orientation vector, and field of view (0-180 degrees)
5. WHEN the Scene Parser encounters a light source element (L), THE Scene Parser SHALL parse the position coordinates, brightness ratio (0.0-1.0), and RGB color values
6. WHEN the Scene Parser encounters a sphere element (sp), THE Scene Parser SHALL parse the center coordinates, diameter, and RGB color values
7. WHEN the Scene Parser encounters a plane element (pl), THE Scene Parser SHALL parse a point on the plane, the normalized normal vector, and RGB color values
8. WHEN the Scene Parser encounters a cylinder element (cy), THE Scene Parser SHALL parse the center coordinates, normalized axis vector, diameter, height, and RGB color values
9. IF the Scene Parser detects any format violation or invalid value, THEN THE Scene Parser SHALL output "Error\n" followed by a descriptive message and terminate the program with a clean exit
10. WHEN the Scene Parser completes validation, THE Scene Parser SHALL ensure exactly one ambient light element (A), exactly one camera element (C), and exactly one light element (L) are present in the mandatory part
11. WHEN the Scene Parser reads element fields, THE Scene Parser SHALL enforce strict field ordering (identifier token first, then parameters in documented order) and accept tolerant whitespace including spaces around commas in coordinate triplets
12. WHEN the Scene Parser validates orientation or normal vectors, THE Scene Parser SHALL verify they are normalized or normalize them automatically, and report malformed vectors as errors
13. WHEN the Scene Parser encounters a light element (L) with RGB color, THE Scene Parser SHALL parse the color values but may ignore them for mandatory rendering (color is reserved for bonus features)

### Requirement 2: Geometric Object Rendering

**User Story:** As a user, I want the ray tracer to render spheres, planes, and cylinders accurately, so that I can visualize complex 3D scenes

#### Acceptance Criteria

1. WHEN the Renderer processes a ray, THE Intersection Handler SHALL compute intersection points with all sphere objects using quadratic equation solving
2. WHEN the Renderer processes a ray, THE Intersection Handler SHALL compute intersection points with all plane objects using ray-plane intersection formulas
3. WHEN the Renderer processes a ray, THE Intersection Handler SHALL compute intersection points with all cylinder objects including both caps and curved surface
4. WHEN a Geometric Object is defined with translation parameters, THE Renderer SHALL position the object at the specified coordinates in 3D space
5. WHEN a Geometric Object (excluding spheres and lights) is defined with rotation parameters, THE Renderer SHALL orient the object according to the specified normal or axis vector (planes and cylinders support rotation; spheres and lights do not)
6. WHEN a sphere is defined with size parameters, THE Renderer SHALL scale the sphere according to the specified diameter value
7. WHEN a cylinder is defined with size parameters, THE Renderer SHALL scale the cylinder according to the specified diameter and height values
8. WHEN multiple intersection points exist for a ray, THE Intersection Handler SHALL select the closest positive intersection point along the ray direction
9. WHEN a ray originates inside a Geometric Object, THE Intersection Handler SHALL correctly compute intersections and orient surface normals (flipping as needed) so that shading remains correct for interior hits
10. WHEN the Intersection Handler processes any object, THE Intersection Handler SHALL handle all possible intersections including edge cases such as rays tangent to surfaces and intersections with cylinder caps

### Requirement 3: Lighting and Shading

**User Story:** As a user, I want realistic lighting with ambient light, diffuse shading, and shadows, so that rendered scenes have depth and visual clarity

#### Acceptance Criteria

1. WHEN the Lighting Engine computes pixel color, THE Lighting Engine SHALL apply ambient lighting to all visible surfaces using the ambient light ratio and color
2. WHEN the Lighting Engine computes pixel color for a surface point, THE Lighting Engine SHALL calculate diffuse lighting using the Lambertian reflection model with the light source brightness and angle
3. WHEN the Lighting Engine evaluates a surface point, THE Lighting Engine SHALL cast shadow rays toward each light source to determine occlusion
4. IF a shadow ray intersects any Geometric Object before reaching the light source, THEN THE Lighting Engine SHALL exclude diffuse contribution from that light source for the surface point
5. WHEN the Lighting Engine computes final pixel color, THE Lighting Engine SHALL ensure that no surface appears completely black by combining ambient and diffuse components
6. WHEN the Lighting Engine calculates color values, THE Lighting Engine SHALL clamp RGB components to the valid range (0-255) before display

### Requirement 4: Window Management and User Interaction

**User Story:** As a user, I want a responsive window with proper event handling, so that I can view rendered images and close the application cleanly

#### Acceptance Criteria

1. WHEN the Ray Tracer starts, THE Window Manager SHALL create a display window using MiniLibX with appropriate dimensions
2. WHEN the Renderer completes image generation, THE Window Manager SHALL display the rendered image in the window without lag or freezing
3. WHEN the user presses the ESC key, THE Window Manager SHALL close the window and terminate the program with proper cleanup
4. WHEN the user clicks the window close button (red cross), THE Window Manager SHALL close the window and terminate the program with proper cleanup
5. WHILE the window is open, THE Window Manager SHALL maintain smooth responsiveness to user input events
6. WHILE rendering or processing, THE Window Manager SHALL process OS events promptly without blocking the event loop so that window minimization, switching, and interaction remain fluid

### Requirement 5: Memory Management and Error Handling

**User Story:** As a developer, I want robust memory management and error handling, so that the program runs reliably without leaks or crashes

#### Acceptance Criteria

1. WHEN the Ray Tracer allocates memory using malloc, THE Ray Tracer SHALL track all allocations for proper deallocation
2. WHEN the Ray Tracer terminates (normally or due to error), THE Ray Tracer SHALL free all dynamically allocated memory before exit
3. IF any runtime error occurs, THEN THE Ray Tracer SHALL output "Error\n" followed by a descriptive message and exit cleanly without memory leaks
4. WHEN the Ray Tracer executes, THE Ray Tracer SHALL prevent all segmentation faults, bus errors, and undefined behavior
5. WHEN the Ray Tracer processes scene data, THE Ray Tracer SHALL validate all numerical inputs to prevent division by zero, degenerate normals, and invalid mathematical operations
6. WHEN the Ray Tracer outputs error messages, THE Ray Tracer SHALL print exactly "Error\n" (with newline) followed by a descriptive message on the next line

### Requirement 6: Build System and Code Standards

**User Story:** As a developer, I want a proper build system following 42 standards, so that the project compiles correctly and meets evaluation criteria

#### Acceptance Criteria

1. WHEN the developer runs make, THE build system SHALL compile all source files with flags -Wall -Wextra -Werror and produce the miniRT executable
2. WHEN the developer runs make clean, THE build system SHALL remove all object files (.o)
3. WHEN the developer runs make fclean, THE build system SHALL remove all object files and the miniRT executable
4. WHEN the developer runs make re, THE build system SHALL perform fclean followed by a complete rebuild
4.5. WHEN the developer runs make on an already-built project, THE build system SHALL avoid unnecessary relinking if object files are up-to-date
5. WHERE the project includes libft, THE build system SHALL compile libft from source and link it with the miniRT executable
6. WHEN the build system compiles source files, THE build system SHALL ensure all code adheres to the 42 Norm coding standards
7. WHEN the build system links the executable, THE build system SHALL include only allowed external functions (open, close, read, write, printf, malloc, free, perror, strerror, exit, math library functions, MiniLibX functions, gettimeofday) and link with -lm for math functions

### Requirement 7: Scene Element Multiplicity

**User Story:** As a user, I want to define multiple geometric objects in a scene, so that I can create complex compositions

#### Acceptance Criteria

1. WHEN the Scene Parser reads a .rt file, THE Scene Parser SHALL accept multiple sphere elements (sp) to allow multiple spheres in the scene
2. WHEN the Scene Parser reads a .rt file, THE Scene Parser SHALL accept multiple plane elements (pl) to allow multiple planes in the scene
3. WHEN the Scene Parser reads a .rt file, THE Scene Parser SHALL accept multiple cylinder elements (cy) to allow multiple cylinders in the scene
4. WHEN the Scene Parser encounters capital-letter elements (A, C, L), THE Scene Parser SHALL enforce that each appears exactly once in the mandatory part
5. WHERE bonus features are implemented, THE Scene Parser MAY accept multiple light elements (L) if explicitly documented as a bonus extension

### Requirement 8: Ray Casting and Camera Model

**User Story:** As a user, I want accurate perspective projection from the camera, so that rendered scenes have correct geometric perspective

#### Acceptance Criteria

1. WHEN the Renderer initializes, THE Renderer SHALL construct a camera coordinate system from the camera position, orientation vector, and field of view
2. WHEN the Renderer generates rays, THE Renderer SHALL compute one ray per pixel passing through the camera position and the corresponding point on the view plane
3. WHEN the Renderer calculates ray directions, THE Renderer SHALL apply the field of view angle to determine the view plane dimensions
4. WHEN the Renderer traces a ray, THE Renderer SHALL normalize the ray direction vector before intersection calculations
5. WHEN the Renderer processes all pixels, THE Renderer SHALL generate rays for the complete image resolution defined by the window dimensions
6. WHEN the camera is defined with an orientation vector, THE Renderer SHALL apply rotation to orient the camera view direction (cameras support rotation unlike spheres and lights)
7. WHEN the Renderer uses MiniLibX for image creation, THE Renderer SHALL use MiniLibX image buffers (strongly recommended) to ensure efficient pixel manipulation and display

### Requirement 9: Testing and Evaluation

**User Story:** As a developer, I want comprehensive test scenes and validation tools, so that I can verify correctness during development and peer evaluation

#### Acceptance Criteria

1. WHEN the project is submitted, THE Ray Tracer SHALL include a set of test scene files (.rt) demonstrating all mandatory features
2. WHEN test scenes are provided, THE test scenes SHALL cover edge cases including object intersections, shadow boundaries, and camera orientations
3. WHEN the project undergoes peer evaluation, THE developers SHALL demonstrate understanding of all implemented algorithms and code structure
4. WHEN the mandatory part is evaluated, THE Ray Tracer SHALL pass all correctness tests without crashes or memory leaks before bonus features are considered
5. WHERE bonus features are implemented, THE Ray Tracer SHALL document all extensions to the .rt format with logical justification

### Requirement 10: Bonus Features

**User Story:** As a user, I want optional advanced rendering features, so that I can create more visually impressive scenes after the mandatory part is complete

#### Acceptance Criteria

1. WHEN bonus features are evaluated, THE evaluation SHALL proceed only after the mandatory part is fully correct, memory-safe, and passes all tests
2. WHERE specular reflection is implemented, THE Renderer SHALL compute Phong specular highlights based on view direction and light reflection
3. WHERE checkerboard patterns are implemented, THE Renderer SHALL apply procedural texture patterns to object surfaces
4. WHERE multiple colored lights are implemented, THE Scene Parser SHALL accept multiple light elements (L) and THE Lighting Engine SHALL accumulate contributions from all lights
5. WHERE additional geometric shapes are implemented (e.g., cones), THE Intersection Handler SHALL compute correct intersections and THE Scene Parser SHALL accept corresponding element definitions
6. WHERE bump mapping is implemented, THE Renderer SHALL perturb surface normals based on texture data to simulate surface detail

# Implementation Plan

This implementation plan provides a sequential approach to building the miniRT ray tracer from the ground up. Tasks are organized to build incrementally, with each phase establishing foundations for the next.

## Phase 1: Project Setup and Core Infrastructure

- [ ] 1. Set up project structure and build system
  - Create directory structure (src/, includes/, scenes/)
  - Write Makefile with all required targets (all, clean, fclean, re)
  - Add compilation flags: -Wall -Wextra -Werror
  - Add MiniLibX linking (-lmlx -framework OpenGL -framework AppKit on macOS)
  - _Requirements: 6.1, 6.2, 6.3, 6.4, 6.5, 6.7_

- [ ] 2. Create core header files and data structures
  - Define all structures in includes/minirt.h (t_vec3, t_color, t_scene, t_object, etc.)
  - Create includes/vector.h with vector operation prototypes
  - Add include guards and proper organization
  - _Requirements: 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 2.1, 2.2, 2.3_

- [ ] 3. Implement error handling and memory management utilities
  - Write src/utils/error.c with error_exit() function
  - Implement proper "Error\n" message formatting
  - Write cleanup function to free all allocated memory
  - Add validation helpers (in_range, is_normalized, etc.)
  - _Requirements: 5.3, 5.6, 1.9_

## Phase 2: Math Library Implementation

- [ ] 4. Implement basic vector operations
  - Write src/math/vector_ops.c
  - Implement vec_new(), vec_add(), vec_sub()
  - Implement vec_scale(), vec_divide()
  - Implement vec_negate()
  - Add proper handling of edge cases
  - _Requirements: 8.4_

- [ ] 5. Implement vector math utilities
  - Write src/math/vector_utils.c
  - Implement vec_dot() for dot product
  - Implement vec_cross() for cross product
  - Implement vec_length() and vec_length_squared()
  - Implement vec_normalize() with zero-vector check
  - Add epsilon-based comparisons for floating-point
  - _Requirements: 5.5, 8.1, 8.4_

## Phase 3: Scene File Parsing

- [ ] 6. Implement parsing utilities
  - Write src/parser/parse_utils.c with string tokenization
  - Implement parse_double() with error checking
  - Implement parse_vec3() for "x,y,z" format
  - Implement parse_color() for "R,G,B" format
  - Add whitespace handling and validation
  - _Requirements: 1.2, 1.11_

- [ ] 7. Implement scene element parsers (A, C, L)
  - Write src/parser/parse_elements.c
  - Implement parse_ambient() for ambient light
  - Implement parse_camera() for camera with FOV validation
  - Implement parse_light() for light source
  - Validate ranges (ratio 0.0-1.0, FOV 0-180, RGB 0-255)
  - _Requirements: 1.3, 1.4, 1.5, 1.13_

- [ ] 8. Implement object parsers (sp, pl, cy)
  - Write src/parser/parse_objects.c
  - Implement parse_sphere() with center, diameter, color
  - Implement parse_plane() with point, normal, color
  - Implement parse_cylinder() with center, axis, diameter, height, color
  - Compute derived values (radius = diameter / 2)
  - _Requirements: 1.6, 1.7, 1.8_

- [ ] 9. Implement main scene parser and validator
  - Write src/parser/parse_scene.c with file reading
  - Implement line-by-line parsing with element dispatch
  - Write src/parser/validate.c for scene validation
  - Ensure exactly one A, C, L element
  - Validate vector normalization (or normalize automatically)
  - Handle parse errors with descriptive messages
  - _Requirements: 1.1, 1.2, 1.9, 1.10, 1.12_

## Phase 4: Camera and Ray Generation

- [ ] 10. Implement camera coordinate system setup
  - Write src/render/camera.c
  - Implement camera_init() to compute right and up vectors
  - Handle edge case: orientation parallel to world up
  - Compute viewport dimensions from FOV
  - Store computed values in camera structure
  - _Requirements: 8.1, 8.6_

- [ ] 11. Implement ray generation
  - Write src/render/ray.c
  - Implement ray_create() function
  - Implement ray_primary() to generate camera rays per pixel
  - Map pixel coordinates to viewport space
  - Normalize ray directions
  - _Requirements: 8.2, 8.3, 8.5_

## Phase 5: Intersection Algorithms

- [ ] 12. Implement sphere intersection
  - Write src/intersect/sphere.c
  - Implement quadratic equation solver
  - Calculate discriminant and handle no-intersection case
  - Return closest positive t value
  - Compute hit point and normal
  - Handle inside-sphere case (flip normal if needed)
  - _Requirements: 2.1, 2.8, 2.9_

- [ ] 13. Implement plane intersection
  - Write src/intersect/plane.c
  - Check for ray parallel to plane (dot product ≈ 0)
  - Calculate t value using dot product formula
  - Return intersection only if t > epsilon
  - Set normal (constant for planes)
  - _Requirements: 2.2_

- [ ] 14. Implement cylinder intersection
  - Write src/intersect/cylinder.c
  - Implement infinite cylinder intersection (quadratic)
  - Check height bounds for body intersections
  - Implement cap intersection tests (two planes)
  - Verify cap hits are within radius
  - Compute normals for body and caps
  - Return closest valid intersection
  - _Requirements: 2.3, 2.10_

- [ ] 15. Implement main intersection dispatcher
  - Write src/intersect/intersect.c
  - Implement intersect_object() that dispatches by type
  - Implement find_closest_hit() to test all objects
  - Return closest intersection with t > epsilon
  - Handle no-intersection case
  - _Requirements: 2.7, 2.8_

## Phase 6: Lighting and Shading

- [ ] 16. Implement color operations
  - Write src/lighting/color.c
  - Implement color_scale() for intensity multiplication
  - Implement color_add() for combining contributions
  - Implement color_multiply() for component-wise multiplication
  - Implement color_clamp() to ensure RGB in [0, 255]
  - _Requirements: 3.6_

- [ ] 17. Implement ambient lighting
  - Write src/lighting/lighting.c with ambient calculation
  - Apply ambient ratio to ambient color
  - Multiply by object color
  - _Requirements: 3.1, 3.5_

- [ ] 18. Implement diffuse lighting
  - Add diffuse calculation to src/lighting/diffuse.c
  - Compute light direction from hit point to light
  - Calculate Lambertian cosine (dot product with normal)
  - Apply light brightness
  - Multiply by object color
  - _Requirements: 3.2, 3.5_

- [ ] 19. Implement shadow ray casting
  - Write src/lighting/shadow.c
  - Create shadow ray from hit point (with epsilon offset) to light
  - Test intersection with all objects
  - Check if intersection t < light distance
  - Return true if occluded, false otherwise
  - _Requirements: 3.3, 3.4_

- [ ] 20. Integrate lighting components
  - Combine ambient, diffuse, and shadow in lighting.c
  - Implement compute_lighting() function
  - Skip diffuse contribution if light is occluded
  - Ensure objects are never fully black
  - Clamp final color to valid range
  - _Requirements: 3.5, 3.6_

## Phase 7: Window Management and Display

- [ ] 21. Implement window creation and management
  - Write src/window/window.c with MLX initialization
  - Create window with mlx_new_window()
  - Implement window close handler (red cross button)
  - Add proper cleanup for MLX resources
  - _Requirements: 4.1, 4.4_

- [ ] 22. Implement MLX image buffer operations
  - Write src/window/image.c
  - Create image buffer with mlx_new_image()
  - Implement put_pixel() function for writing pixels
  - Implement encode_color() to convert t_color to int
  - Add mlx_put_image_to_window() call
  - _Requirements: 4.2, 8.7_

- [ ] 23. Implement event handling
  - Write src/window/events.c
  - Add ESC key handler (keycode 53 on macOS, 65307 on Linux)
  - Add window close button handler (mlx_hook with event 17)
  - Ensure clean exit with memory cleanup
  - Test window responsiveness
  - _Requirements: 4.3, 4.4, 4.5, 4.6_

## Phase 8: Main Rendering Loop and Integration

- [ ] 24. Implement main render function
  - Write src/render/render.c
  - Implement render() function with pixel loop
  - For each pixel: generate ray, find intersection, compute lighting
  - Handle background color for misses (black)
  - Write pixel color to image buffer
  - _Requirements: 4.2_

- [ ] 25. Implement main program flow
  - Write src/main.c with entry point
  - Validate command-line arguments (exactly one .rt file)
  - Call scene parser
  - Initialize rendering context
  - Call renderer
  - Display image and enter event loop
  - Handle errors and cleanup
  - _Requirements: 1.1, 5.4_

- [ ] 26. End-to-end integration testing
  - Test complete pipeline: parse → render → display
  - Verify all scene files render correctly
  - Test error handling for invalid scenes
  - Run memory leak checks with valgrind
  - Fix integration issues
  - _Requirements: 5.1, 5.2, 9.3_

- [ ]* 27. Create test scene files
  - Create scenes/simple_sphere.rt with one sphere
  - Create scenes/multiple_objects.rt with sp, pl, cy
  - Create scenes/shadow_test.rt for shadow verification
  - Create scenes/edge_cases/ directory with test cases
  - Document expected output for each scene
  - _Requirements: 9.1, 9.2_

- [ ]* 28. Final polish and documentation
  - Add code comments for complex sections
  - Create README with compilation and usage instructions
  - Document .rt file format
  - Add example scenes with descriptions
  - Prepare for peer evaluation
  - _Requirements: 9.3, 9.4_

## Bonus Features (After Mandatory Completion)

- [ ]* B1. Implement specular reflection (Phong)
  - Add material properties to objects
  - Implement Phong specular calculation
  - Add specular parameters to .rt format
  - _Requirements: 10.2_

- [ ]* B2. Implement checkerboard patterns
  - Add pattern flag to object structure
  - Implement pattern calculation in color computation
  - Add pattern parameters to .rt format
  - _Requirements: 10.3_

- [ ]* B3. Implement multiple lights support
  - Modify parser to accept multiple L elements
  - Store lights in array or linked list
  - Update lighting loop to iterate all lights
  - _Requirements: 10.4_

- [ ]* B4. Implement cone intersection
  - Write cone intersection algorithm
  - Add cone parser
  - Add cone to .rt format
  - _Requirements: 10.5_

- [ ]* B5. Implement bump mapping
  - Add texture/normal map support
  - Perturb normals based on texture
  - Add bump map parameters to .rt format
  - _Requirements: 10.6_

---

## Notes

- Tasks marked with * are optional (testing, documentation, optimization, bonuses)
- Each task builds incrementally on previous tasks
- Focus on correctness first, optimization later
- Test each component before moving to the next phase

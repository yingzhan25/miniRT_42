# miniRT Project Summary (Paraphrased)

## Introduction

Ray tracing and rasterization are two primary techniques for generating
3D computer graphics. While rasterization is widely used for real-time
rendering due to its speed, ray tracing produces more realistic visuals
by simulating light behavior, though at a higher computational cost.\
The miniRT project introduces you to building a minimal ray tracer in C
using MiniLibX. Its purpose is to help you implement mathematical and
physical formulas without requiring deep mathematical expertise.

------------------------------------------------------------------------

## Common Instructions

-   Write the project in **C**, following the **42 Norm**. Bonus files
    are checked as well.
-   Your program must not crash unexpectedly (segfaults, double frees,
    etc.).
-   Free all allocated memory; **no leaks** allowed.
-   Provide a Makefile with: `$(NAME)`, `all`, `clean`, `fclean`, `re`.
    -   Use `-Wall -Wextra -Werror` with `cc`.\
    -   No unnecessary relinking.
-   A `bonus` rule is required if you submit bonus features.
-   If libft is allowed, include its full source and Makefile in a
    *libft* folder.
-   Testing your project is encouraged, especially for defense.
-   Only the code pushed to the Git repository will be evaluated.
    Deepthought stops at the first error.

------------------------------------------------------------------------

## AI Instructions

### Context

AI tools can support your learning and coding tasks, but outputs must
always be verified. Peers remain essential for maintaining accuracy and
avoiding misunderstandings.

### Guidelines

-   Use AI to **speed up repetitive tasks**.
-   Develop strong prompting habits.
-   Learn how AI systems behave to avoid bias and errors.
-   Always validate AI-generated results and rely on peer review.
-   Only use code or explanations you fully understand and can defend.

### Good vs Bad Practices

**Good:** Using AI to brainstorm tests or help design logic, then
reviewing it with classmates.\
**Bad:** Copy-pasting AI-generated code without understanding it ---
this leads to failure in evaluations.

------------------------------------------------------------------------

## Mandatory Part -- miniRT

### Overview

**Program name:** `miniRT`\
**Input:** A `.rt` scene description file\
**Goal:** Render a scene using basic ray-tracing concepts including
lights, materials, and 3D objects.

### Allowed External Functions

-   Standard C I/O & syscalls: `open`, `close`, `read`, `write`,
    `printf`, `malloc`, `free`, etc.
-   Math library functions (`-lm`)
-   MiniLibX
-   `gettimeofday()`
-   **libft is allowed**

### General Requirements

-   Use MiniLibX (system version or compiled from source).
-   Window behavior must remain smooth (switching focus, minimizing,
    etc.).
-   Program must display an image in a window.
-   Exit cleanly on:
    -   ESC key press
    -   Clicking window close button
-   Images should be created using MiniLibX.

### Supported Objects

You must implement at least: - **Plane** - **Sphere** - **Cylinder**

Correct handling of: - All intersections - Object interiors - Object
transformations (translation & rotation) - Spheres and lights **cannot**
rotate

### Lighting Requirements

-   Ambient light
-   Diffuse light
-   Hard shadows\
    Objects should never be fully black.

------------------------------------------------------------------------

## Scene File Format (`.rt`)

-   Accept a single scene file as argument.
-   Elements may appear in any order, separated by any number of spaces
    or newlines.
-   Capital-letter elements may appear only once.
-   First token is a type identifier; format must strictly follow
    ordering.

### Elements

#### Ambient Light

    A <ratio> <R,G,B>

-   Ratio: `0.0–1.0`
-   Colors: `0–255`

#### Camera

    C <x,y,z> <orientation> <FOV>

-   Normalized orientation vector: each component in `[-1,1]`
-   FOV: degrees `0–180`

#### Light

    L <x,y,z> <brightness> <R,G,B>

-   Brightness ratio `0.0–1.0`
-   RGB color is ignored in mandatory part

#### Sphere

    sp <x,y,z> <diameter> <R,G,B>

#### Plane

    pl <x,y,z> <normal> <R,G,B>

-   Normal vector normalized

#### Cylinder

    cy <x,y,z> <axis> <diameter> <height> <R,G,B>

### Example Scene

    A 0.2 255,255,255
    C -50,0,20 0,0,1 70
    L -40,0,30 0.7 255,255,255

    pl 0,0,0 0,1,0 255,0,225
    sp 0,0,20 20 255,0,0
    cy 50,0,20.6 0,0,1 14.2 21.42 10,0,255

### Error Handling

-   On any parsing or scene configuration error:
    -   Print `Error`
    -   Follow with a descriptive error message
    -   Exit cleanly

------------------------------------------------------------------------

## Bonus Part

Bonuses are evaluated **only if the mandatory part is perfect** (all
points).

Suggested bonus features: - Specular reflection (Phong model) -
Checkerboard surface pattern - Multiple lights and colored lights -
Additional quadratic object (cone, paraboloid, hyperboloid...) - Bump
mapping textures

You may: - Extend the `.rt` format - Add functions and features as
needed\
--- but you must justify everything during the defense.

------------------------------------------------------------------------

## Submission & Evaluation

-   Submit your project in the assigned Git repository.
-   Evaluators may ask you to:
    -   Modify a small piece of code
    -   Adjust behavior
    -   Add a simple feature\
        These tasks must be completed quickly and demonstrate your
        understanding.

Evaluation rules may vary; always be prepared.

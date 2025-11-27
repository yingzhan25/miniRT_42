# miniRT Project — Structured Sections for Kiro

---

## SECTION 1 — Project Overview
Purpose: Build a minimal ray tracer in C using MiniLibX.  
Core Goal: Implement basic ray tracing (ray casting, intersections, lighting, shading).  
Outcome: Produce images from a `.rt` scene description while practicing mathematical implementation.

---

## SECTION 2 — Technical Rules & Constraints
- Written in C following the 42 Norm.
- No crashes or memory leaks.
- Makefile must include: `all`, `clean`, `fclean`, `re`, `bonus`.
- Use flags: `-Wall -Wextra -Werror`.
- Only allowed functions: system I/O, math library, MiniLibX, gettimeofday, malloc/free, etc.
- Libft allowed (must include full source).
- Deepthought stops on first error.

---

## SECTION 3 — Mandatory Features
### Rendering & Window Management
- Use MiniLibX for image display.
- Window must respond smoothly.
- Close on ESC or window red cross.

### Required Objects
- Plane  
- Sphere  
- Cylinder  
All must support:
- Intersection handling  
- Translation (all)  
- Rotation (all except spheres and lights)  
- Size changes (diameter, height)

### Lighting Features
- Ambient light  
- Diffuse light  
- Hard shadows  
- Objects must not be fully black.

### Input Handling
Argument: `.rt` scene file  
Rules:
- Any order of elements
- Spaces and empty lines allowed
- Capital-letter elements appear once
- Strict format required

### Error Handling
Print:
```
Error
<message>
```
Exit cleanly on any misconfiguration.

---

## SECTION 4 — Scene File Format Specification

### Ambient Light
```
A <ratio> <R,G,B>
```

### Camera
```
C <x,y,z> <norm_vector> <FOV>
```

### Light
```
L <x,y,z> <brightness> <R,G,B>
```

### Sphere
```
sp <x,y,z> <diameter> <R,G,B>
```

### Plane
```
pl <x,y,z> <normal_vector> <R,G,B>
```

### Cylinder
```
cy <x,y,z> <axis_vector> <diameter> <height> <R,G,B>
```

### Example
```
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,0,30 0.7 255,255,255

pl 0,0,0 0,1,0 255,0,225
sp 0,0,20 20 255,0,0
cy 50,0,20.6 0,0,1 14.2 21.42 10,0,255
```

---

## SECTION 5 — Bonus Features
Only evaluated if mandatory part is perfect.

Suggested bonuses:
- Specular reflection (Phong)
- Checkerboard pattern
- Multiple colored lights
- Additional quadratic shapes (e.g., cone)
- Bump mapping

Extensions to `.rt` format allowed if logically justified.

---

## SECTION 6 — Submission & Evaluation
- Push to Git repository.
- Evaluation may require quick code changes.
- Must demonstrate full understanding of project.

---

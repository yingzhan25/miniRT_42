# miniRT - First RayTracer with miniLibX

![miniRT Logo](https://img.shields.io/badge/42-School-blue)
![C Language](https://img.shields.io/badge/language-C-orange)

## 📖 Introduction

### Project Overview
**miniRT** is a minimalist ray tracing engine developed as part of the 42 school curriculum. This project introduces the beautiful world of computer graphics by implementing a ray tracer from scratch using the miniLibX graphics library.

### What is a Ray Tracer?
Ray tracing is a rendering technique that simulates the physical behavior of light to generate photorealistic images. The algorithm traces the path of light rays as they travel from a camera through each pixel in an image plane and calculates how these rays interact with objects in a 3D scene.  By simulating reflection, refraction, shadows, and lighting, ray tracing produces images with realistic lighting and shadows.

The basic ray tracing algorithm works as follows:
1. **Cast rays** from the camera through each pixel of the viewport
2. **Detect intersections** between rays and scene objects
3. **Calculate lighting** using ambient light, diffuse reflection, and shadows
4. **Render the final color** for each pixel based on material properties and lighting

### Key Features

**Mandatory Features:**
- 3D vector mathematics implementation
- Ray-object intersection algorithms for spheres, planes, and cylinders
- Phong lighting model with ambient and diffuse components
- Shadow casting for realistic lighting
- Scene file parsing (. rt format)
- Real-time rendering using miniLibX

**Bonus Features:**
- **(Bonus) Cone object** - Additional geometric primitive with apex-based intersection
- **(Bonus) Texture mapping** - Support for multiple texture types: 
  - Procedural checkerboard patterns
  - XPM image texture mapping (e.g., Earth and Jupiter textures)
  - UV coordinate mapping for spherical objects
- **(Bonus) Specular reflection** - Phong specular highlights for shiny surfaces
- **(Bonus) Adjustable shininess** - Configurable material shininess (2.0 - 200.0)
- **(Bonus) Multiple lights** - Support for multiple point light sources in a single scene

---

## 🖼️ Output Gallery

<img width="1440" height="847" alt="Screenshot 2026-01-11 at 20 22 00" src="https://github.com/user-attachments/assets/45b464e7-082c-4cbe-9a29-bc139287b69c" />
<p align="center"><i>Snowman before xpm plane demonstrating specular highlights and multiple light sources</i></p>

<img width="1440" height="847" alt="Screenshot 2026-01-11 at 20 32 21" src="https://github.com/user-attachments/assets/723bab0f-9ab6-4b97-8834-adbc34f8dd9a" />
<p align="center"><i>Snowman before checkerboard plane demonstrating specular highlights and multiple light sources</i></p>

<img width="1440" height="845" alt="Screenshot 2026-01-11 at 20 28 54" src="https://github.com/user-attachments/assets/8c5d8a7f-8ea1-4349-b8f6-4b504b8d1533" />
<p align="center"><i>Colorful stickman with checkerboard pattern and xpm background on plane surface</i></p>

<img width="1440" height="846" alt="Screenshot 2026-01-11 at 20 24 05" src="https://github.com/user-attachments/assets/2d358c90-7b10-4e6c-9446-fd2f1209f5f3" />
<p align="center"><i>Complex scene featuring cylinders, spheres, and realistic shadow casting</i></p>

<img width="1440" height="848" alt="Screenshot 2026-01-11 at 20 33 06" src="https://github.com/user-attachments/assets/210a4d45-c201-4a4d-a7bb-b939376dd997" />
<p align="center"><i>Multiple spheres and cylinders with varying textures and lighting effects</i></p>

<img width="1440" height="848" alt="Screenshot 2026-01-11 at 20 39 27" src="https://github.com/user-attachments/assets/9be65ea8-88d7-4be1-8fe5-f6162bf89dfe" />
<p align="center"><i>Geometric composition with cones and cylinders demonstrating ray-object intersections</i></p>

<img width="1440" height="847" alt="Screenshot 2026-01-11 at 20 18 55" src="https://github.com/user-attachments/assets/dadcf7b3-4fa3-428c-8f80-1bbb59b9116f" />
<p align="center"><i>Sphere and plane showcasing procedural checkerboard pattern</i></p>

---

## 🚀 Installation

### Clone the Repository

```bash
# Clone the project
git clone https://github.com/yingzhan25/miniRT_42.git

# Navigate to the project directory
cd miniRT_42
```

### Installation on Linux

```bash
# Install required dependencies
sudo apt-get update
sudo apt-get install gcc make xorg libxext-dev libbsd-dev

# Compile the project
make

# Run with a scene file
./minirt scenes/example.rt
```

### Installation on macOS

```bash
# Install Xcode Command Line Tools if not already installed
xcode-select --install

# Compile the project
make

# Run with a scene file
./minirt scenes/example.rt
```

### Using the miniLibX Library

The miniLibX (mlx) is a simple graphics library used for this project. It provides basic functionality for creating windows, handling events, and drawing images.

**Important Notes:**
- The library is already included or linked in the Makefile
- On Linux, mlx uses the X11 window system
- On macOS, mlx uses the native Cocoa framework
- Make sure the mlx header path in `includes/render.h` matches your system: 
  - macOS: `#include <mlx. h>`
  - Linux: `#include </usr/local/include/mlx.h>`

### Compilation

```bash
# Compile mandatory part
make

# Compile with bonus features (if implemented)
make bonus

# Clean object files
make clean

# Clean everything including executables
make fclean

# Recompile
make re
```

### Running the Program

```bash
# Basic usage
./minirt <scene_file. rt>

# Example
./minirt scenes/example.rt
```

### Controls
- **ESC**: Exit the program
- **Close window (X button)**: Exit the program

## 📝 Scene File Format

Scene files use the `.rt` extension and follow this format:

### Mandatory Format

```
# Ambient lighting
A 0.2 255,255,255

# Camera
C 0,0,0 0,0,1 70

# Light source
L -40,50,0 0.6 255,255,255

# Sphere
sp 0,0,20 20 255,0,0

# Plane
pl 0,-10,0 0,1,0 0,255,0

# Cylinder
cy 0,0,30 0,1,0 10 40 0,0,255
```

### Bonus Format

```
# Scene with multiple lights and textures
A 0.1 255,255,255
C -50,0,20 0,0,1 70

# Multiple light sources
L -40,50,0 0.6 255,255,255
L 40,30,20 0.4 255,200,150

# Textured sphere (Earth)
sp 0,0,20 20 255,255,255 0.8 100 2 imgs/earthmap1k. xpm

# Checkerboard plane
pl 0,-10,0 0,1,0 255,255,255 0.3 50 1 -

# Shiny cylinder
cy 20,0,0 0,1,0 14 21 200,50,50 0.9 150 0 -

# Cone with material
co -20,0,10 0,1,0 15 30 100,200,100 0.7 80 0 -
```

### Element Format Specifications

#### Mandatory Elements

| Identifier | Format | Parameters | Description |
|------------|--------|------------|-------------|
| **A** | `A ratio R,G,B` | **ratio**: `[0.0 - 1.0]` Ambient light ratio<br>**R,G,B**:  `[0 - 255]` Color values | Ambient lighting |
| **C** | `C x,y,z nx,ny,nz fov` | **x,y,z**:  3D position coordinates<br>**nx,ny,nz**:  `[-1.0 - 1.0]` Normalized orientation vector<br>**fov**:  `[0 - 180]` Field of view in degrees | Camera position, orientation, field of view |
| **L** | `L x,y,z brightness R,G,B` | **x,y,z**: 3D position coordinates<br>**brightness**: `[0.0 - 1.0]` Light brightness<br>**R,G,B**:  `[0 - 255]` Color values | Light source |
| **sp** | `sp x,y,z diameter R,G,B` | **x,y,z**: 3D center position<br>**diameter**:  Positive value<br>**R,G,B**: `[0 - 255]` Color values | Sphere |
| **pl** | `pl x,y,z nx,ny,nz R,G,B` | **x,y,z**: Point on the plane<br>**nx,ny,nz**: `[-1.0 - 1.0]` Normalized normal vector<br>**R,G,B**: `[0 - 255]` Color values | Plane |
| **cy** | `cy x,y,z nx,ny,nz diameter height R,G,B` | **x,y,z**:  3D center position<br>**nx,ny,nz**:  `[-1.0 - 1.0]` Normalized axis vector<br>**diameter**:  Positive value<br>**height**:  Positive value<br>**R,G,B**: `[0 - 255]` Color values | Cylinder |

#### Bonus Elements

| Identifier | Format | Parameters | Description |
|------------|--------|------------|-------------|
| **co** | `co x,y,z nx,ny,nz diameter height R,G,B [specular shininess] [texture]` | **x,y,z**:  3D apex position<br>**nx,ny,nz**:  `[-1.0 - 1.0]` Normalized axis vector<br>**diameter**:  Positive value (base diameter)<br>**height**: Positive value<br>**R,G,B**:  `[0 - 255]` Color values<br>**specular**: `[0.0 - 1.0]` (optional)<br>**shininess**: `[2.0 - 200.0]` (optional)<br>**texture**: `checker` or `xpm path` (optional) | **(Bonus)** Cone |

#### Bonus Material Properties

**(Bonus)** All objects (sp, pl, cy, co) can be extended with optional material properties:

| Property | Format | Range/Options | Description |
|----------|--------|---------------|-------------|
| **specular** | Add after color:  `R,G,B specular` | `[0.0 - 1.0]` | Specular reflection coefficient for shiny surfaces |
| **shininess** | Add after specular: `specular shininess` | `[2.0 - 200.0]` | Material shininess/glossiness (higher = shinier) |
| **texture** | Add at end:  `[texture_type] [path]` | `checker` or `xpm path/to/file.xpm` | Texture mapping (procedural or image-based) |

### Format Rules

**General Rules:**
- Each element is defined on a separate line
- Elements start with an identifier (A, C, L, sp, pl, cy, co)
- Parameters are separated by spaces
- 3D coordinates and colors use comma-separated values (no spaces)
- Comments start with `#`
- Empty lines are ignored

---

## 📚 References

- **Fundamentals of Ray Tracing** - The foundational text used for understanding ray tracing concepts and implementation techniques
- [miniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - Guide for the miniLibX library
- Visual animation for generating the ray https://claude.ai/public/artifacts/9c66201f-f915-46f4-a275-1c15b46081c3
- Visual animation for finding the intersection https://claude.ai/public/artifacts/9a98ee8d-0056-45fb-8a9f-25c53b96a221
- Visual animation for Phong Lighting Model https://claude.ai/public/artifacts/4e5f22a4-4fe9-4c9e-89ce-4a4e0c9fe035
- Visual animation for shadow detection https://claude.ai/public/artifacts/dda2cb4b-fab1-4b81-8309-8f6b67a89b0f
- Visual animation for Ray-Cylinder Intersection https://claude.ai/public/artifacts/c0426c6d-ff08-432c-8cf2-d92d60f42afa
- Visual animation for texture uv-mapping https://claude.ai/public/artifacts/c9bd67d6-99ea-4e29-a04b-e2bc8c342439

---

## 🏫 42 School Project

This project is part of the 42 school curriculum, focusing on:
- Computer graphics fundamentals
- Mathematical concepts (vectors, matrices, intersections)
- Algorithm optimization
- Scene parsing and validation
- Memory management in C

---

## 📄 License

This is an educational project developed as part of the 42 school curriculum. 

---

**Made with ☕ and determination at 42 Berlin**

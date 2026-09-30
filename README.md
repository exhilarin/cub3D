# 🎮 cub3D

![42 Project](https://img.shields.io/badge/42%20Network-cub3D-blue?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge)
![Concepts](https://img.shields.io/badge/Concepts-Raycasting%20%26%20Graphics-yellowgreen?style=for-the-badge)

## 📚 Project Summary

**cub3D** is a 42 curriculum project inspired by the legendary *Wolfenstein 3D*. The goal is to build a first-person 3D view of a maze from a 2D map using the **raycasting** technique and the **MiniLibX** graphics library.

Through this project, I learned how a 3D scene can be rendered from a simple 2D grid, how to parse and validate a scene description file, and how to handle real-time input and rendering in C.

My version goes beyond the mandatory part with a **Pokémon-themed bonus**: animated Pokémon sprites, doors, a minimap, mouse rotation and more.

---

## 🧠 What I Learned in cub3D

### 🔹 Raycasting and the DDA Algorithm
* Casting one ray per screen column and computing its direction from the player's direction and **camera plane (FOV)**
* Using the **DDA (Digital Differential Analyzer)** algorithm to find the first wall a ray hits
* Computing the perpendicular wall distance to avoid the fisheye effect
* Selecting the correct **wall texture** (North, South, East, West) depending on the hit side

### 🔹 Graphics with MiniLibX
* Creating windows and images, and drawing pixels directly into an image buffer
* Loading **XPM textures** and mapping them onto wall slices
* Handling **keyboard events** (press/release) and window close events with `mlx_hook`
* Keeping movement smooth by tracking key states instead of reacting to single events

### 🔹 Parsing and Map Validation
* Parsing a `.cub` scene file: texture paths (`NO`, `SO`, `WE`, `EA`), floor/ceiling colors (`F`, `C`) and the map
* Validating RGB values, missing or duplicated elements and unknown characters
* Checking that the map is **closed/surrounded by walls** and has exactly one player start position
* Reporting clear error messages for invalid input

### 🔹 Bonus Features
* Drawing a **minimap** with the player position and direction
* **Collision detection** for walls and doors
* **Doors** that open and close with an animation
* **Mouse rotation** to look around
* **Animated sprites** (Pokémon, Pokéball effects, hand animation) and an intro screen

### 🔹 Clean and Safe C Code
* Following **Norminette** rules and splitting code into small modules
* Freeing every allocation, including images, textures and sprite frames
* Collaborating through Git on a shared codebase

---

## 📁 Project Structure

```bash
cub3D/
├── src/                    # Mandatory part
│   ├── main.c
│   ├── parsing/            # .cub file parsing and map validation
│   ├── game/
│   │   ├── player/         # Player init and movement
│   │   ├── raycasting/     # DDA, wall drawing, pixel drawing
│   │   └── render/         # Frame rendering
│   └── utils/              # Errors, free, init helpers
├── bonus/                  # Bonus part
│   ├── collision/
│   ├── core/
│   ├── door/
│   ├── minimap/
│   ├── mouse/
│   ├── sprite/
│   └── include/
├── include/                # Headers and configuration
├── assets/                 # XPM textures and sprites
├── maps/                   # Example .cub maps
├── library/                # libft, get_next_line, minilibx-linux
└── Makefile
```

---

## ⚙️ Features Implemented

### Mandatory
* Raycasting engine with **textured walls** (different texture per wall direction)
* Configurable **floor and ceiling colors**
* Move with `W` `A` `S` `D`, rotate with `←` `→`, quit with `ESC` or the window's close button
* Full validation of the scene file and the map

### Bonus
* Minimap
* Wall collisions
* Interactive doors (`E`)
* Mouse camera rotation
* Sprint with `Shift`
* Animated Pokémon sprites and Pokéball animation
* Intro screen (`Space` to start)

---

## 🚀 How to Run

```bash
git clone https://github.com/exhilarin/cub3D.git
cd cub3D

make              # mandatory part
./cub3D maps/subject.cub

make re_bonus     # bonus part
./cub3D maps/test_all_pokemon.cub
```

> Requires a Linux environment with `X11`, `Xext`, `libm` and `libbsd` (used by MiniLibX).

### Map Format

```text
NO ./assets/textures/north.xpm
SO ./assets/textures/south.xpm
WE ./assets/textures/west.xpm
EA ./assets/textures/east.xpm

F 79,127,31
C 109,182,232

1111111
1000001
10N0001
1111111
```

`1` is a wall, `0` is an empty space, and `N` / `S` / `E` / `W` is the player's start position and direction.

---

## 🧩 Technical Highlights

* Pure **C** with the **MiniLibX** library and no external rendering libraries
* Separate builds for mandatory and bonus parts, sharing the same raycasting core
* Error handling for invalid maps and missing assets

---

## 🚀 Key Takeaways

cub3D showed me that a convincing 3D world can come from a little math and a 2D grid.  
Building the raycaster and then turning it into a small Pokémon game was a great way to combine math, graphics and C.

---

> _“Every wall on the screen is just a single ray asking: how far is the nearest obstacle?”_

# Tiny Physics Engine

2D physics engine  in C to understand how game and simulation engines actually work under the hood.
The project implements a deterministic physics update loop, collision detection and rigid body dynamics from scratch without relying on external physics libraries.

Right now it supports:

- Gravity
- Delta-time based physics
- Basic vector math
- Ground collision with bounce
- Wall collision
- Simple AABB (Axis-Aligned Bounding Box) collision detection
- Basic body-body collision response using velocity exchange


---

## Built With

- C
- SDL2
- GCC (MSYS2 MinGW64)

---

## How to Run

### 1. Install SDL2 (MSYS2)

```bash
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-SDL2
```

### 2. Compile

```bash
gcc main.c vector.c collision.c -lmingw32 -lSDL2main -lSDL2 -o engine
```

### 3. Run

```bash
./engine
```


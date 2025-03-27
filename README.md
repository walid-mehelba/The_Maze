# The Maze

## Overview
**The Maze** is a **3D maze game** built using **C** and **SDL2**. It features a first-person view, raycasting-based rendering, enemy interactions, and weapon mechanics.

## Features
- 🏰 **Raycasting Engine** for 3D rendering.
- 🎯 **Player Movement** with collision detection.
- 👾 **Enemy AI** with attack mechanics.
- 🔫 **Weapon System** with recoil and shooting effects.
- 🌄 **Textures** for walls, sky, and ground.
- 🔊 **Sound Effects** for shooting and taking damage.
- 🛑 **Pause Functionality** with on-screen UI.

## Prerequisites
Ensure you have the following installed:
- **C Compiler** (e.g., GCC)
- **SDL2** (`libsdl2-dev`)
- **SDL2 Image** (`libsdl2-image-dev`)
- **SDL2 Mixer** (`libsdl2-mixer-dev`)
- **SDL2 TTF** (`libsdl2-ttf-dev`)

## Installation
1. **Clone the repository:**
   ```sh
   git clone https://github.com/yourusername/the-maze.git
   cd the-maze
   ```
2. **Compile the project:**
   ```sh
<<<<<<< HEAD
   make clean
=======
>>>>>>> Walid_testing
   make
   ```
3. **Run the game:**
   ```sh
<<<<<<< HEAD
   ./the_maze
=======
   ./maze
>>>>>>> Walid_testing
   ```

## Controls
- `WASD` - Move Forward, Backward, Strafe Left/Right
- `Arrow Keys` - Rotate Left/Right
- `Mouse` - Look Around
- `Left Click` - Fire Weapon
- `P` - Pause Game
- `ESC` - Quit Game

## File Structure
```
├── src/
│   ├── main.c          # Main game loop
│   ├── map.c           # Map generation
│   ├── player.c        # Player movement & shooting
│   ├── raycasting.c    # 3D rendering logic
│   ├── sdl_utils.c     # SDL initialization
│   ├── textures.c      # Texture management
│
├── inc/
│   ├── map.h           # Map definitions
│   ├── raycasting.h    # Raycasting & game logic
│   ├── sdl_utils.h     # SDL helper functions
│   ├── textures.h      # Texture loading
│
├── assets/
│   ├── sounds/         # Sound effects
│   ├── textures/       # Game textures
│
├── Makefile            # Build instructions
└── README.md           # Project documentation
```

## Credits
- **Developers:** Walid Mehelba & Laila Mohamed
- **Technologies:** C, SDL2, SDL_mixer, SDL_ttf, SDL_image
<<<<<<< HEAD
=======


>>>>>>> Walid_testing

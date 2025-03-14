#include <SDL2/SDL.h>
#include <stdio.h>
#include "raycasting.h"
#include "textures.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() {
    // Initialize SDL
    if (!init_sdl()) {
        fprintf(stderr, "Failed to initialize SDL!\n");
        return 1;
    }

    // Load textures
    SDL_Texture *wallTexture = loadTexture(renderer, "assets/jungle_texture.png");
    if (!wallTexture) {
        fprintf(stderr, "Failed to load wall texture!\n");
        close_sdl();
        return 1;
    }

    // Start the game loop
    game_loop(renderer, wallTexture);

    // Clean up
    SDL_DestroyTexture(wallTexture);
    close_sdl();
    return 0;
}

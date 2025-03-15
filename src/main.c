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
    SDL_Texture *skyTexture = loadTexture(renderer, "assets/sky_texture.png");
    if (!wallTexture || !skyTexture) {
        fprintf(stderr, "Failed to load textures!\n");
        close_sdl();
        return 1;
    }

    // Start the game loop
    game_loop(renderer, wallTexture, skyTexture);

    // Clean up
    SDL_DestroyTexture(wallTexture);
    SDL_DestroyTexture(skyTexture);
    close_sdl();
    return 0;
}

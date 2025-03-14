#include "textures.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

// Global texture variable
SDL_Texture* wall_texture = NULL;

bool load_textures(SDL_Renderer* renderer) {
    // Load the wall texture
    wall_texture = IMG_LoadTexture(renderer, "assets/jungle_texture.png");
    if (!wall_texture) {
        printf("Failed to load wall texture! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void free_textures() {
    // Free the wall texture if it exists
    if (wall_texture) {
        SDL_DestroyTexture(wall_texture);
        wall_texture = NULL; // Set to NULL to avoid dangling pointers
    }
}

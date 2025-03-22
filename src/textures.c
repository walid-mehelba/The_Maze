#include "../inc/textures.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

// Global texture variables (loaded and freed here)
SDL_Texture *wall_texture = NULL;    // Wall texture
SDL_Texture *sky_texture = NULL;     // Sky texture
SDL_Texture *ground_texture = NULL;  // Ground texture

// Load all textures into memory
bool load_textures(SDL_Renderer *renderer) {
    // Load wall texture
    wall_texture = IMG_LoadTexture(renderer, "assets/jungle_texture.png");
    if (!wall_texture) {
        fprintf(stderr, "Failed to load wall texture! SDL_Error: %s\n", IMG_GetError());
        return false;
    }

    // Load sky texture
    sky_texture = IMG_LoadTexture(renderer, "assets/sky_texture.png");
    if (!sky_texture) {
        fprintf(stderr, "Failed to load sky texture! SDL_Error: %s\n", IMG_GetError());
        return false;
    }

    // Load ground texture
    ground_texture = IMG_LoadTexture(renderer, "assets/ground_texture.png");
    if (!ground_texture) {
        fprintf(stderr, "Failed to load ground texture! SDL_Error: %s\n", IMG_GetError());
        return false;
    }

    return true; // Success
}

// Free all loaded textures
void free_textures() {
    if (wall_texture) {
        SDL_DestroyTexture(wall_texture); // Free wall texture
        wall_texture = NULL;
    }
    if (sky_texture) {
        SDL_DestroyTexture(sky_texture); // Free sky texture
        sky_texture = NULL;
    }
    if (ground_texture) {
        SDL_DestroyTexture(ground_texture); // Free ground texture
        ground_texture = NULL;
    }
}

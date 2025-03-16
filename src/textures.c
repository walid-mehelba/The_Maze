#include "textures.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

// Global texture variables
SDL_Texture *wall_texture = NULL;
SDL_Texture *sky_texture = NULL; // Add sky texture
SDL_Texture *ground_texture = NULL; // adding ground texture
/**
 * Loads all textures (e.g., wall texture and sky texture) into memory.
 * Returns true on success, false on failure.
 */
bool load_textures(SDL_Renderer *renderer) {
    // Load the wall texture
    wall_texture = IMG_LoadTexture(renderer, "assets/jungle_texture.png");
    if (!wall_texture) {
        fprintf(stderr, "Failed to load wall texture! SDL_Error: %s\n", IMG_GetError());
        return false;
    }

    // Load the sky texture
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
     // Load weapon texture
    weapon_texture = IMG_LoadTexture(renderer, "assets/weapons/weapon_texture.png");
    if (!weapon_texture) {
        fprintf(stderr, "Failed to load weapon texture! SDL_Error: %s\n", IMG_GetError());
        return false;
    }


    return true;
}

/**
 * Frees all loaded textures.
 */
void free_textures() {
    if (wall_texture) {
        SDL_DestroyTexture(wall_texture);
        wall_texture = NULL;
    }
    if (sky_texture) {
        SDL_DestroyTexture(sky_texture);
        sky_texture = NULL;
    }
     if (ground_texture) {
        SDL_DestroyTexture(ground_texture);

    }
      if (weapon_texture) {
        SDL_DestroyTexture(weapon_texture);
        weapon_texture = NULL;
    }
   }

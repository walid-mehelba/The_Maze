#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

// Global texture variable
extern SDL_Texture *wall_texture;
extern SDL_Texture *sky_texture;
extern SDL_Texture *weapon_texture;
/**
 * Loads all textures (e.g., wall texture) into memory.
 * Returns true on success, false on failure.
 */
bool load_textures(SDL_Renderer *renderer);

/**
 * Frees all loaded textures.
 */
void free_textures();

#endif /* TEXTURES_H */

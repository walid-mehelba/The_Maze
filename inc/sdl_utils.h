#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include </opt/homebrew/include/SDL2/SDL.h>
#include </opt/homebrew/include/SDL2/SDL_image.h>
#include <stdio.h>

// Function prototypes

/**
 * Initializes SDL2 and creates a window and renderer.
 * Returns 1 on success, 0 on failure.
 */
int init_sdl(void);

/**
 * Returns the SDL renderer.
 */
SDL_Renderer *get_renderer(void);

/**
 * Loads a texture from a file.
 * Returns the texture on success, NULL on failure.
 */
SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *file_path);

/**
 * Cleans up SDL2 resources.
 */
void close_sdl(void);

#endif /* SDL_UTILS_H */

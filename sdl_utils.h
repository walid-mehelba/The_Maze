#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *file_path);
#endif /* SDL_UTILS_H */

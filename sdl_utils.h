#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

SDL_Texture *loadTexture(const char *path, SDL_Renderer *renderer);

#endif /* SDL_UTILS_H */

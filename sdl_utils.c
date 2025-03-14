#include "raycasting.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
Player player = {3.5, 3.5, M_PI / 4}; // Initial player position

int init_sdl()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 0;
    }

    window = SDL_CreateWindow("Raycasting with SDL2", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    return 1;
}

SDL_Renderer *get_renderer()
{
    return renderer;
}

SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *file_path)
{
    SDL_Surface *loadedSurface = IMG_Load(file_path);
    if (!loadedSurface)
    {
        fprintf(stderr, "Unable to load image %s! SDL_image Error: %s\n", file_path, IMG_GetError());
        return NULL;
    }

    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if (!newTexture)
    {
        fprintf(stderr, "Unable to create texture from %s! SDL Error: %s\n", file_path, SDL_GetError());
    }

    return newTexture;
}

void close_sdl()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

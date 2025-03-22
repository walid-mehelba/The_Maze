#include "../inc/sdl_utils.h"
#include "../inc/raycasting.h"
#include <SDL2/SDL.h>
#include <stdio.h>

// Global variables for window and renderer
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

/**
 * Initializes SDL, creates a window, and sets up the renderer.
 * Returns 1 on success, 0 on failure.
 */
int init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // Initialize SDL_image for loading textures
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 0;
    }

    // Create the window
    window = SDL_CreateWindow("Jungle Raycasting", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    // Create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    // Enable relative mouse mode (optional, for mouse rotation)
    SDL_SetRelativeMouseMode(SDL_TRUE);

    return 1;
}

/**
 * Returns the SDL renderer.
 */
SDL_Renderer *get_renderer() {
    return renderer;
}

/**
 * Loads a texture from a file.
 * Returns the texture on success, NULL on failure.
 */
SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *file_path) {
    SDL_Surface *loadedSurface = IMG_Load(file_path);
    if (!loadedSurface) {
        fprintf(stderr, "Unable to load image %s! SDL_image Error: %s\n", file_path, IMG_GetError());
        return NULL;
    }

    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if (!newTexture) {
        fprintf(stderr, "Unable to create texture from %s! SDL Error: %s\n", file_path, SDL_GetError());
    }

    return newTexture;
}

/**
 * Cleans up SDL resources.
 */
void close_sdl() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    IMG_Quit();
    SDL_Quit();
}

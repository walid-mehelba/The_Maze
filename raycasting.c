#include "raycasting.h"

int main(void)
{
    if (!init_sdl())
        return 1;

    SDL_Renderer *renderer = get_renderer();
    if (!renderer)
    {
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Texture *j_texture = loadTexture("raycasting.png", renderer);
    if (!j_texture)
    {
        fprintf(stderr, "Failed to load texture: %s\n", SDL_GetError());
        return 1;
    }

    int running = 1; // Ensure this variable exists
    while (running)
    {
        handle_events(&running);  // Correct: Pass int *running
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, j_texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(j_texture);
    close_sdl();

    return 0;
}

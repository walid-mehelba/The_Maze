#include "raycasting.h"

int main()
{
    if (!init_sdl())
        return 1;

    int running = 1;
    while (running)
    {
        handle_events(&running);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw_walls();
        SDL_RenderPresent(renderer);
    }

    close_sdl();
    return 0;
}

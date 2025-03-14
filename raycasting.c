#include "raycasting.h"

int main()
{
	SDL_Texture *jungleTexture = loadTexture("jungle_texture.png", renderer);
if (!jungleTexture)
{
    SDL_Log("Failed to load texture: %s", SDL_GetError());
    return (1);
}

    if (!init_sdl())
        return 1;

    int running = 1;
    while (running)
    {
        handle_events(&running);
        
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
	draw_walls(renderer, jungleTexture, x, y, wall_width, wall_height);

    }

    close_sdl();
    return 0;
}

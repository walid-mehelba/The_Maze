#include "raycasting.h"
#include "sdl_utils.h"

int main(void)
{
    if (!init_sdl())
        return 1;

    SDL_Renderer *renderer = get_renderer(); // Ensure this function is declared in raycasting.h

    SDL_Texture *jungleTexture = loadTexture("path/to/your/jungle_texture.png", renderer);
    if (!jungleTexture)
    {
        fprintf(stderr, "Failed to load texture: %s", SDL_GetError());
        close_sdl(); // Ensure to close SDL properly before returning
        return 1;
    }
    
    int x = 100;
    int y = 100;
    int wall_width = 50;
    int wall_height = 100;

    while (1) // Replace with actual condition to control the loop
    {
	SDL_Event event;
        handle_events(&event);
        
        SDL_RenderClear(renderer);
        draw_walls(renderer, jungleTexture, x, y, wall_width, wall_height);
        SDL_RenderPresent(renderer);
    }
    
    close_sdl();
    return 0;
    }

#include "raycasting.h"

void handle_events(int *running)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            *running = 0; // Stop the game loop
        }
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                *running = 0; // Quit if ESC is pressed
            }
        }
    }
}


void move_player(float dx, float dy)
{
    int new_x = (int)(player.x + dx);
    int new_y = (int)(player.y + dy);

    if (map[new_y][new_x] == 0) // Prevent walking into walls
    {
        player.x += dx;
        player.y += dy;
    }
}

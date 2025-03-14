#include "raycasting.h"

void handle_events(int *running)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            *running = 0;
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_LEFT:
                    player.angle -= 0.1;
                    break;
                case SDLK_RIGHT:
                    player.angle += 0.1;
                    break;
                case SDLK_w:
                    move_player(cos(player.angle) * 0.1, sin(player.angle) * 0.1);
                    break;
                case SDLK_s:
                    move_player(-cos(player.angle) * 0.1, -sin(player.angle) * 0.1);
                    break;
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

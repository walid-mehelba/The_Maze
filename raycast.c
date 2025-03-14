#include "raycasting.h"

void draw_walls(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h)
{
	(void)y;
    	(void)h;
    for (int i = 0; i < NUM_RAYS; i++) {
        float ray_angle = player.angle - (FOV / 2) + (FOV * i / NUM_RAYS);
        float ray_x = player.x, ray_y = player.y;
        float step_x = cos(ray_angle) * 0.01;
        float step_y = sin(ray_angle) * 0.01;

        while (map[(int)ray_y][(int)ray_x] == 0) {
            ray_x += step_x;
            ray_y += step_y;
        }

        float distance = sqrt((ray_x - player.x) * (ray_x - player.x) +
                              (ray_y - player.y) * (ray_y - player.y));
        distance *= cos(ray_angle - player.angle); // Fix fisheye effect

        int wall_height = (int)(SCREEN_HEIGHT / distance);
        int line_y_start = (SCREEN_HEIGHT - wall_height) / 2;

        SDL_Rect wallRect = {x, line_y_start, w, wall_height}; // Use calculated values
        SDL_RenderCopy(renderer, texture, NULL, &wallRect);
    }
}

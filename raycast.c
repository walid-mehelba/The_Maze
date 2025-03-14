#include "raycasting.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Draw walls with texture mapping
void draw_walls(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h, float wall_hit_x) {
    SDL_Rect srcRect, dstRect;

    // Texture width and height
    int texWidth, texHeight;
    SDL_QueryTexture(texture, NULL, NULL, &texWidth, &texHeight);

    // Determine the x coordinate to sample from the texture
    srcRect.x = (int)(wall_hit_x * texWidth) % texWidth;
    srcRect.y = 0;
    srcRect.w = 1; // Sample a single vertical slice
    srcRect.h = texHeight;

    // Destination rectangle (where to draw the wall slice)
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = w;
    dstRect.h = h;

    // Render the textured wall slice
    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}

// Raycasting function
void cast_rays(SDL_Renderer *renderer, SDL_Texture *texture) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        float rayAngle = player.angle - (FOV / 2) + (x * FOV / SCREEN_WIDTH);
        float rayDirX = cos(rayAngle);
        float rayDirY = sin(rayAngle);

        float distanceToWall = 0;
        int hit = 0;
        int mapX = (int)player.x;
        int mapY = (int)player.y;

        float deltaDistX = fabs(1 / rayDirX);
        float deltaDistY = fabs(1 / rayDirY);
        float sideDistX, sideDistY;
        int stepX, stepY;
        int hitVertical = 0;

        // Calculate step direction and initial side distances
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (player.x - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player.x) * deltaDistX;
        }

        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (player.y - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player.y) * deltaDistY;
        }

        // DDA algorithm (Digital Differential Analyzer) to find the wall hit
        while (!hit) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                hitVertical = 1;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                hitVertical = 0;
            }

            if (map[mapY][mapX] > 0) {
                hit = 1;
            }
        }

        // Calculate distance to the wall
        if (hitVertical)
            distanceToWall = (mapX - player.x + (1 - stepX) / 2) / rayDirX;
        else
            distanceToWall = (mapY - player.y + (1 - stepY) / 2) / rayDirY;

        // Calculate wall height and position
        int wallHeight = (int)(SCREEN_HEIGHT / distanceToWall);
        int wallTop = (SCREEN_HEIGHT / 2) - (wallHeight / 2);


        // Get wall hit texture coordinate
        float wallHitX;
        if (hitVertical)
            wallHitX = player.y + distanceToWall * rayDirY;
        else
            wallHitX = player.x + distanceToWall * rayDirX;
        wallHitX -= floor(wallHitX); // Get fractional part only

        // Draw the wall with texture mapping
        draw_walls(renderer, texture, x, wallTop, 1, wallHeight, wallHitX);
    }
}

// Game loop
void game_loop(SDL_Renderer *renderer, SDL_Texture *texture) {
    int running = 1;
    while (running) {
        handle_events(&running);
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        cast_rays(renderer, texture);

        SDL_RenderPresent(renderer);
    }
}

// Main function
int main() {
    if (!init_sdl()) return 1;

    SDL_Texture *wallTexture = loadTexture(renderer, "wall_texture.png");
    if (!wallTexture) return 1;

    game_loop(renderer, wallTexture);

    SDL_DestroyTexture(wallTexture);
    close_sdl();
    return 0;
}

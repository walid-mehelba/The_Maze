#include "raycasting.h"

// Function to render a wall slice with texture mapping
void draw_walls(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h, float wall_hit_x) {
    SDL_Rect srcRect, dstRect;

    // Get texture width & height
    int texWidth, texHeight;
    SDL_QueryTexture(texture, NULL, NULL, &texWidth, &texHeight);

    // Select the correct texture column
    srcRect.x = (int)(wall_hit_x * texWidth) % texWidth;
    srcRect.y = 0;
    srcRect.w = 1;
    srcRect.h = texHeight;

    // Set destination rectangle
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = w;
    dstRect.h = h;

    // Render the textured wall slice
    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}

// Function to render the sky
void draw_sky(SDL_Renderer *renderer, SDL_Texture *sky_texture) {
    // Set the destination rectangle for the sky (top half of the screen)
    SDL_Rect sky_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2};

    // Render the sky texture
    SDL_RenderCopy(renderer, sky_texture, NULL, &sky_rect);
}

// Function to render the ground with scrolling effect
void draw_ground(SDL_Renderer *renderer, SDL_Texture *ground_texture) {
    // Calculate the offset based on the player's position
    float offsetX = player.x * 10; // Adjust the multiplier for the desired effect
    float offsetY = player.y * 10; // Adjust the multiplier for the desired effect

    // Get the texture dimensions
    int texWidth, texHeight;
    SDL_QueryTexture(ground_texture, NULL, NULL, &texWidth, &texHeight);

    // Create a source rectangle for the ground texture
    SDL_Rect srcRect = {
        (int)offsetX % texWidth, // Offset X
        (int)offsetY % texHeight, // Offset Y
        SCREEN_WIDTH, // Width of the ground texture to render
        SCREEN_HEIGHT / 2 // Height of the ground texture to render
    };

    // Create a destination rectangle for the ground texture
    SDL_Rect dstRect = {
        0, // X position (top-left corner)
        SCREEN_HEIGHT / 2, // Y position (bottom half of the screen)
        SCREEN_WIDTH, // Width of the ground texture to render
        SCREEN_HEIGHT / 2 // Height of the ground texture to render
    };

    // Render the ground texture
    SDL_RenderCopy(renderer, ground_texture, &srcRect, &dstRect);
}

// Function to render the weapon on the screen
void draw_weapon(SDL_Renderer *renderer, SDL_Texture *weapon_texture) {
    // Define the position and size of the weapon on the screen
    int weapon_width = SCREEN_WIDTH / 4; // Adjust size as needed
    int weapon_height = SCREEN_HEIGHT / 3; // Adjust size as needed
    int weapon_x = (SCREEN_WIDTH - weapon_width) / 2; // Center horizontally
    int weapon_y = SCREEN_HEIGHT - weapon_height; // Place at the bottom

    // Add recoil effect
    if (recoil_offset > 0) {
        weapon_y -= recoil_offset;
        recoil_offset -= 2; // Gradually reduce recoil
    }

    SDL_Rect weapon_rect = {weapon_x, weapon_y, weapon_width, weapon_height};
    SDL_RenderCopy(renderer, weapon_texture, NULL, &weapon_rect);
}

// Raycasting function
void raycasting(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *sky_texture, SDL_Texture *ground_texture) {
    // Draw the sky
    draw_sky(renderer, sky_texture);

    // Draw the ground
    draw_ground(renderer, ground_texture);

    // Cast rays and render walls
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

        // Calculate step direction and side distances
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

        // DDA algorithm
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

        // Wall height
        int wallHeight = (int)(SCREEN_HEIGHT / distanceToWall);
        int wallTop = (SCREEN_HEIGHT / 2) - (wallHeight / 2);

        // Compute texture mapping
        float wallHitX;
        if (hitVertical)
            wallHitX = player.y + distanceToWall * rayDirY;
        else
            wallHitX = player.x + distanceToWall * rayDirX;
        wallHitX -= floor(wallHitX);

        // Draw wall slice
        draw_walls(renderer, texture, x, wallTop, 1, wallHeight, wallHitX);
    }
}

// Game loop
void game_loop(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *sky_texture, SDL_Texture *ground_texture, SDL_Texture *weapon_texture) {
    int running = 1;
    while (running) {
        handle_events(&running); // Handle events (keyboard and mouse input)
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        // Draw the sky
        draw_sky(renderer, sky_texture);

        // Draw the ground
        draw_ground(renderer, ground_texture);

        // Cast rays and render walls
        raycasting(renderer, texture, sky_texture, ground_texture);

        // Draw the weapon
        draw_weapon(renderer, weapon_texture);

        SDL_RenderPresent(renderer);
    }
}

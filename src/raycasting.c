#include "../inc/raycasting.h"

// Global flag for damage flash effect
bool show_damage_flash = false;
static Uint32 flash_start_time = 0;

// Global flag for fire effect
bool show_fire_effect = false;
Uint32 fire_start_time = 0; // Moved from player.c

// Font for text rendering
TTF_Font *font = NULL;

// Render a wall slice with texture mapping
void draw_walls(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h, float wall_hit_x) {
    SDL_Rect srcRect, dstRect;
    int texWidth, texHeight;
    SDL_QueryTexture(texture, NULL, NULL, &texWidth, &texHeight);

    srcRect.x = (int)(wall_hit_x * texWidth) % texWidth;
    srcRect.y = 0;
    srcRect.w = 1;
    srcRect.h = texHeight;

    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = w;
    dstRect.h = h;

    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}

// Render the sky background
void draw_sky(SDL_Renderer *renderer, SDL_Texture *sky_texture) {
    SDL_Rect sky_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
    SDL_RenderCopy(renderer, sky_texture, NULL, &sky_rect);
}

// Render the ground with scrolling effect
void draw_ground(SDL_Renderer *renderer, SDL_Texture *ground_texture) {
    float offsetX = player.x * 10;
    float offsetY = player.y * 10;
    int texWidth, texHeight;
    SDL_QueryTexture(ground_texture, NULL, NULL, &texWidth, &texHeight);

    SDL_Rect srcRect = {(int)offsetX % texWidth, (int)offsetY % texHeight, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
    SDL_Rect dstRect = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2};

    SDL_RenderCopy(renderer, ground_texture, &srcRect, &dstRect);
}

// Render the weapon overlay with recoil animation
void draw_weapon(SDL_Renderer *renderer, SDL_Texture *weapon_texture) {
    int weapon_width = SCREEN_WIDTH / 3;
    int weapon_height = SCREEN_HEIGHT / 2;
    int weapon_x = (SCREEN_WIDTH - weapon_width) / 2;
    int weapon_y = SCREEN_HEIGHT - weapon_height;

    if (recoil_offset > 0) {
        weapon_y -= recoil_offset;
        recoil_offset -= 2;
    }

    SDL_Rect weapon_rect = {weapon_x, weapon_y, weapon_width, weapon_height};
    SDL_RenderCopy(renderer, weapon_texture, NULL, &weapon_rect);
}

// Spawn an enemy with a slower random speed between 0.01 and 0.03
void spawn_enemy(float x, float y, SDL_Texture *texture) {
    if (num_enemies < MAX_ENEMIES && map[(int)y][(int)x] == 0) {
        float speed = 0.01 + (rand() % 3) * 0.01; // Slower range: 0.01 to 0.03
        enemies[num_enemies] = (Enemy){x, y, texture, true, speed};
        num_enemies++;
    }
}

// Render all active enemies in the scene
void render_enemies(SDL_Renderer *renderer) {
    for (int i = 0; i < num_enemies; i++) {
        if (!enemies[i].alive) continue;

        float dx = enemies[i].x - player.x;
        float dy = enemies[i].y - player.y;
        float distance = sqrt(dx * dx + dy * dy);
        float enemy_angle = atan2(dy, dx) - player.angle;
        if (enemy_angle < -M_PI) enemy_angle += 2 * M_PI;
        if (enemy_angle > M_PI) enemy_angle -= 2 * M_PI;

        if (fabs(enemy_angle) < FOV / 2) {
            int screen_x = (int)((SCREEN_WIDTH / 2) + (enemy_angle / (FOV / 2)) * (SCREEN_WIDTH / 2));
            int enemy_size = (int)(SCREEN_HEIGHT / distance);
            int enemy_y = (SCREEN_HEIGHT - enemy_size) / 2;

            if (screen_x >= 0 && screen_x < SCREEN_WIDTH) {
                SDL_Rect enemy_rect = {screen_x - enemy_size / 2, enemy_y, enemy_size, enemy_size};
                SDL_RenderCopy(renderer, enemies[i].texture, NULL, &enemy_rect);
            }
        }
    }
}

// Move enemies toward the player, avoiding walls and other enemies
void move_enemies(void) {
    for (int i = 0; i < num_enemies; i++) {
        if (!enemies[i].alive) continue;

        float dx = player.x - enemies[i].x;
        float dy = player.y - enemies[i].y;
        float distance = sqrt(dx * dx + dy * dy);
        if (distance < 0.1) continue;

        float moveX = (dx / distance) * enemies[i].speed;
        float moveY = (dy / distance) * enemies[i].speed;

        float newX = enemies[i].x + moveX;
        float newY = enemies[i].y + moveY;

        int mapX = (int)newX;
        int mapY = (int)newY;
        bool canMove = (map[mapY][mapX] == 0);

        if (canMove) {
            for (int j = 0; j < num_enemies; j++) {
                if (j == i || !enemies[j].alive) continue;
                float enemyDx = newX - enemies[j].x;
                float enemyDy = newY - enemies[j].y;
                if (sqrt(enemyDx * enemyDx + enemyDy * enemyDy) < 0.5) {
                    canMove = false;
                    break;
                }
            }
        }

        if (canMove) {
            enemies[i].x = newX;
            enemies[i].y = newY;
        } else {
            newX = enemies[i].x + moveX;
            newY = enemies[i].y;
            mapX = (int)newX;
            mapY = (int)newY;
            canMove = (map[mapY][mapX] == 0);
            if (canMove) {
                for (int j = 0; j < num_enemies; j++) {
                    if (j == i || !enemies[j].alive) continue;
                    float enemyDx = newX - enemies[j].x;
                    float enemyDy = newY - enemies[j].y;
                    if (sqrt(enemyDx * enemyDx + enemyDy * enemyDy) < 0.5) {
                        canMove = false;
                        break;
                    }
                }
                if (canMove) enemies[i].x = newX;
            }

            newX = enemies[i].x;
            newY = enemies[i].y + moveY;
            mapX = (int)newX;
            mapY = (int)newY;
            canMove = (map[mapY][mapX] == 0);
            if (canMove) {
                for (int j = 0; j < num_enemies; j++) {
                    if (j == i || !enemies[j].alive) continue;
                    float enemyDx = newX - enemies[j].x;
                    float enemyDy = newY - enemies[j].y;
                    if (sqrt(enemyDx * enemyDx + enemyDy * enemyDy) < 0.5) {
                        canMove = false;
                        break;
                    }
                }
                if (canMove) enemies[i].y = newY;
            }
        }
    }
}

// Enemy attack logic: Reduce player health, play sound, and trigger flash
void enemy_attack(void) {
    static Uint32 last_attack_time = 0;
    Uint32 current_time = SDL_GetTicks();

    if (current_time - last_attack_time < 1000) return;

    for (int i = 0; i < num_enemies; i++) {
        if (!enemies[i].alive) continue;

        float dx = player.x - enemies[i].x;
        float dy = player.y - enemies[i].y;
        float distance = sqrt(dx * dx + dy * dy);

        if (distance < 1.0) {
            player_health -= 10;
            printf("Enemy %d attacked! Player health: %d\n", i, player_health);

            if (damage_sound) {
                if (Mix_PlayChannel(-1, damage_sound, 0) == -1) {
                    fprintf(stderr, "Failed to play damage sound! SDL_mixer Error: %s\n", Mix_GetError());
                }
            }

            show_damage_flash = true;
            flash_start_time = current_time;

            last_attack_time = current_time;
            break;
        }
    }
}

// Initialize SDL_ttf and load font
bool init_ttf(void) {
    if (TTF_Init() == -1) {
        fprintf(stderr, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    font = TTF_OpenFont("assets/arial.ttf", 24);
    if (!font) {
        fprintf(stderr, "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    return true;
}

// Render player health on screen
void render_health(SDL_Renderer *renderer) {
    if (!font) return;

    char health_text[32];
    snprintf(health_text, sizeof(health_text), "Health: %d", player_health);

    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, health_text, color);
    if (!surface) {
        fprintf(stderr, "Failed to render health text! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        fprintf(stderr, "Failed to create health texture! SDL_Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect rect = {10, 10, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

// Cleanup TTF resources
void cleanup_ttf(void) {
    if (font) {
        TTF_CloseFont(font);
        font = NULL;
    }
    TTF_Quit();
}

// Perform raycasting to render the 3D scene
void raycasting(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *sky_texture, SDL_Texture *ground_texture) {
    draw_sky(renderer, sky_texture);
    draw_ground(renderer, ground_texture);

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
            if (map[mapY][mapX] > 0) hit = 1;
        }

        if (hitVertical)
            distanceToWall = (mapX - player.x + (1 - stepX) / 2) / rayDirX;
        else
            distanceToWall = (mapY - player.y + (1 - stepY) / 2) / rayDirY;

        int wallHeight = (int)(SCREEN_HEIGHT / distanceToWall);
        int wallTop = (SCREEN_HEIGHT / 2) - (wallHeight / 2);
        float wallHitX = hitVertical ? player.y + distanceToWall * rayDirY : player.x + distanceToWall * rayDirX;
        wallHitX -= floor(wallHitX);

        draw_walls(renderer, texture, x, wallTop, 1, wallHeight, wallHitX);
    }

    render_enemies(renderer);
}

// Main game loop with cursor, fire effect, and health display
void game_loop(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *sky_texture, SDL_Texture *ground_texture, SDL_Texture *weapon_texture) {
    int running = 1;
    SDL_ShowCursor(SDL_DISABLE);

    while (running) {
        handle_events(&running);
        move_enemies();
        enemy_attack();
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        raycasting(renderer, texture, sky_texture, ground_texture);
        draw_weapon(renderer, weapon_texture);

        // Render damage flash
        if (show_damage_flash) {
            Uint32 current_time = SDL_GetTicks();
            if (current_time - flash_start_time < 200) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
                SDL_Rect flash_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
                SDL_RenderFillRect(renderer, &flash_rect);
            } else {
                show_damage_flash = false;
            }
        }

        // Render fire effect (yellow flash at weapon tip)
        if (show_fire_effect) {
            Uint32 current_time = SDL_GetTicks();
            if (current_time - fire_start_time < 100) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 150);
                SDL_Rect fire_rect = {SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT - 100, 20, 20};
                SDL_RenderFillRect(renderer, &fire_rect);
            } else {
                show_fire_effect = false;
            }
        }

        // Render weapon cursor (crosshair)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 + 10, SCREEN_HEIGHT / 2);
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 10, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 10);

        // Render health
        render_health(renderer);

        SDL_RenderPresent(renderer);
    }
}

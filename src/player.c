#include "../inc/raycasting.h"
#include <stdbool.h>
#include <SDL2/SDL_mixer.h>

// Player instance with initial position and angle
Player player = {3.5, 3.5, M_PI / 4};

// Weapon-related globals
int recoil_offset = 0;
SDL_Texture *weapon_texture = NULL;
Mix_Chunk *gunshot_sound = NULL;
Mix_Chunk *damage_sound = NULL;


// Player health
int player_health = 100;

// Sound effect for taking damage
Mix_Chunk *damageSound = NULL;

// Enemy array and counter
Enemy enemies[MAX_ENEMIES];
int num_enemies = 0;

// Handle keyboard and mouse input events
void handle_events(int *running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *running = 0;
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                *running = 0;
<<<<<<< HEAD
            } else if (event.key.keysym.sym == SDLK_w) {
                move_player(0.1 * cos(player.angle), 0.1 * sin(player.angle));
            } else if (event.key.keysym.sym == SDLK_s) {
                move_player(-0.1 * cos(player.angle), -0.1 * sin(player.angle)); // Move backward
            } else if (event.key.keysym.sym == SDLK_d) {
                // Strafe left
                move_player(-0.1 * sin(player.angle), 0.1 * cos(player.angle));
            } else if (event.key.keysym.sym == SDLK_a) {
                // Strafe right
                move_player(-0.1 * cos(player.angle), -0.1 * sin(player.angle));
            } else if (event.key.keysym.sym == SDLK_d) {
                move_player(-0.1 * sin(player.angle), 0.1 * cos(player.angle));
            } else if (event.key.keysym.sym == SDLK_a) {

                move_player(0.1 * sin(player.angle), -0.1 * cos(player.angle));
            } else if (event.key.keysym.sym == SDLK_LEFT) {
                player.angle -= 0.1;
            } else if (event.key.keysym.sym == SDLK_RIGHT) {
                player.angle += 0.1;
=======
            } else if (event.key.keysym.sym == SDLK_p) { // Toggle pause with 'P'
                paused = !paused;
            } else if (!paused) { // Only process movement/fire when not paused
                if (event.key.keysym.sym == SDLK_w) {
                    move_player(0.1 * cos(player.angle), 0.1 * sin(player.angle));
                } else if (event.key.keysym.sym == SDLK_s) {
                    move_player(-0.1 * cos(player.angle), -0.1 * sin(player.angle));
                } else if (event.key.keysym.sym == SDLK_d) {
                    move_player(-0.1 * sin(player.angle), 0.1 * cos(player.angle));
                } else if (event.key.keysym.sym == SDLK_a) {
                    move_player(0.1 * sin(player.angle), -0.1 * cos(player.angle));
                } else if (event.key.keysym.sym == SDLK_LEFT) {
                    player.angle -= 0.1;
                } else if (event.key.keysym.sym == SDLK_RIGHT) {
                    player.angle += 0.1;
                }
>>>>>>> Walid_testing
            }
        } else if (event.type == SDL_MOUSEBUTTONDOWN && !paused) { // Fire only when not paused
            if (event.button.button == SDL_BUTTON_LEFT) {
                fire_weapon();
            }
        } else if (event.type == SDL_MOUSEMOTION && !paused) { // Mouse rotation only when not paused
            int mouse_x = event.motion.x;
            int delta_x = mouse_x - (SCREEN_WIDTH / 2);
            player.angle += delta_x * 0.005;
            SDL_WarpMouseInWindow(window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        }
    }

    if (player_health <= 0) {
        *running = 0;
        printf("Player died!\n");
    }
}

// Move the player, checking for wall collisions
void move_player(float dx, float dy) {
    int new_x = (int)(player.x + dx);
    int new_y = (int)(player.y + dy);

    if (map[new_y][new_x] == 0) {
        player.x += dx;
        player.y += dy;
    }
}

void fire_weapon(void) {
    if (gunshot_sound) {
        Mix_HaltChannel(-1); // Stop all currently playing sounds
        if (Mix_PlayChannel(-1, gunshot_sound, 0) == -1) {
            fprintf(stderr, "Failed to play gunshot sound! SDL_mixer Error: %s\n", Mix_GetError());
        }
    }
    recoil_offset = 20;
    show_fire_effect = true;
    fire_start_time = SDL_GetTicks();
<<<<<<< HEAD

=======
>>>>>>> Walid_testing

    float rayDirX = cos(player.angle);
    float rayDirY = sin(player.angle);
    float rayX = player.x;
    float rayY = player.y;
    float distance = 0;

    while (distance < 10) {
        rayX += rayDirX * 0.1;
        rayY += rayDirY * 0.1;
        distance += 0.1;

        if (map[(int)rayY][(int)rayX] > 0) break;

        for (int i = 0; i < num_enemies; i++) {
            if (!enemies[i].alive) continue;
            float dx = enemies[i].x - rayX;
            float dy = enemies[i].y - rayY;
            if (sqrt(dx * dx + dy * dy) < 0.5) {
                enemies[i].alive = false;
                break;
            }
        }
    }

}
bool load_sounds(void) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    // Allocate more mixing channels
    Mix_AllocateChannels(16);  // Default is 8, increase to 16

    gunshot_sound = Mix_LoadWAV("assets/sounds/final_shot.wav");
    if (!gunshot_sound) {
        fprintf(stderr, "Failed to load gunshot sound! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    damage_sound = Mix_LoadWAV("assets/sounds/damage.wav");
    if (!damage_sound) {
        fprintf(stderr, "Failed to load damage sound! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    return true;
}

// Free loaded sound resources
void free_sounds(void) {
    if (gunshot_sound) {
        Mix_FreeChunk(gunshot_sound);
        gunshot_sound = NULL;
    }
    if (damage_sound) {
        Mix_FreeChunk(damage_sound);
        damage_sound = NULL;
    }
    Mix_CloseAudio();
}

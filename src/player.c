#include "raycasting.h"

// Define the player variable
Player player = {3.5, 3.5, M_PI / 4}; // Initial position and angle

// Define global variables for weapon state
int recoil_offset = 0; // Recoil effect for the weapon
SDL_Texture *weapon_texture = NULL; // Texture for the weapon
Mix_Chunk *gunshot_sound = NULL; // Sound effect for firing

// Function to handle events (keyboard and mouse input)
void handle_events(int *running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *running = 0; // Stop the game loop
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                *running = 0; // Quit if ESC is pressed
            } else if (event.key.keysym.sym == SDLK_w) {
                move_player(0.1 * cos(player.angle), 0.1 * sin(player.angle)); // Move forward
            } else if (event.key.keysym.sym == SDLK_s) {
                move_player(-0.1 * cos(player.angle), -0.1 * sin(player.angle)); // Move backward
            } else if (event.key.keysym.sym == SDLK_a) {
                // Strafe left
                move_player(-0.1 * sin(player.angle), 0.1 * cos(player.angle));
            } else if (event.key.keysym.sym == SDLK_d) {
                // Strafe right
                move_player(0.1 * sin(player.angle), -0.1 * cos(player.angle));
            } else if (event.key.keysym.sym == SDLK_LEFT) {
                player.angle -= 0.1; // Rotate left (arrow key)
            } else if (event.key.keysym.sym == SDLK_RIGHT) {
                player.angle += 0.1; // Rotate right (arrow key)
            }
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                // Fire the weapon when the left mouse button is pressed
                fire_weapon();
            }
        } else if (event.type == SDL_MOUSEMOTION) {
            // Rotate based on mouse movement
            int mouse_x = event.motion.x;
            int delta_x = mouse_x - (SCREEN_WIDTH / 2);
            player.angle += delta_x * 0.005; // Adjust sensitivity as needed

            // Lock mouse to the center of the screen (optional)
            SDL_WarpMouseInWindow(window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        }
    }
}

// Function to move the player
void move_player(float dx, float dy) {
    int new_x = (int)(player.x + dx);
    int new_y = (int)(player.y + dy);

    if (map[new_y][new_x] == 0) { // Prevent walking into walls
        player.x += dx;
        player.y += dy;
    }
}

// Function to fire the weapon
void fire_weapon(void) {
    printf("Weapon fired!\n");

    // Play gunshot sound if loaded
    if (gunshot_sound) {
        Mix_PlayChannel(-1, gunshot_sound, 0);
    }

    // Add recoil effect
    recoil_offset = 20; // Adjust the recoil distance
}

// Function to load weapon sound effects
bool load_sounds(void) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    gunshot_sound = Mix_LoadWAV("assets/weapons/gunshot.wav");
    if (!gunshot_sound) {
        fprintf(stderr, "Failed to load gunshot sound! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    return true;
}

// Function to clean up sound resources
void free_sounds(void) {
    if (gunshot_sound) {
        Mix_FreeChunk(gunshot_sound);
        gunshot_sound = NULL;
    }
    Mix_CloseAudio();
}

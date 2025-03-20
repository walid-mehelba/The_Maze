#include </opt/homebrew/include/SDL2/SDL.h>
#include <stdio.h>
#include "../inc/map.h"
#include "../inc/raycasting.h"
#include "../inc/textures.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Main entry point of the program
int main() {
    srand(time(NULL));

    if (!init_sdl()) {
        fprintf(stderr, "Failed to initialize SDL!\n");
        return 1;
    }

    if (!init_ttf()) { // Initialize SDL_ttf
        fprintf(stderr, "Failed to initialize TTF!\n");
        close_sdl();
        return 1;
    }

    // Load game textures
    SDL_Texture *wallTexture = loadTexture(renderer, "assets/jungle_texture.png");
    SDL_Texture *skyTexture = loadTexture(renderer, "assets/sky_texture.png");
    SDL_Texture *groundTexture = loadTexture(renderer, "assets/ground_texture.png");
    SDL_Texture *weaponTexture = loadTexture(renderer, "assets/weapons/weapon_texture.png");
    SDL_Texture *enemyTexture = loadTexture(renderer, "assets/enemy_texture.png");

    if (!wallTexture || !skyTexture || !groundTexture || !weaponTexture || !enemyTexture) {
        fprintf(stderr, "Failed to load textures!\n");
        cleanup_ttf();
        close_sdl();
        return 1;
    }

    if (!load_sounds()) {
        fprintf(stderr, "Failed to load sounds!\n");
        cleanup_ttf();
        close_sdl();
        return 1;
    }

    // Spawn enemies
    spawn_enemy(2.5, 2.5, enemyTexture);
    spawn_enemy(5.5, 4.5, enemyTexture);
    spawn_enemy(1.5, 5.5, enemyTexture);
    spawn_enemy(3.5, 1.5, enemyTexture);
    spawn_enemy(4.5, 6.5, enemyTexture);
    spawn_enemy(6.5, 2.5, enemyTexture);

    game_loop(renderer, wallTexture, skyTexture, groundTexture, weaponTexture);

    // Cleanup
    SDL_DestroyTexture(wallTexture);
    SDL_DestroyTexture(skyTexture);
    SDL_DestroyTexture(groundTexture);
    SDL_DestroyTexture(weaponTexture);
    SDL_DestroyTexture(enemyTexture);
    free_sounds();
    cleanup_ttf(); // Cleanup TTF resources
    close_sdl();

    return 0;
}

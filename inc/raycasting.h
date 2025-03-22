#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "sdl_utils.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Window and map dimensions
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define FOV 60 * (M_PI / 180)
#define NUM_RAYS SCREEN_WIDTH

// Player structure: Represents the player's position and orientation
typedef struct {
    float x, y;     // Player's X and Y coordinates in the map
    float angle;    // Player's facing angle in radians
} Player;

// Enemy structure: Represents an enemy with position, texture, state, and speed
typedef struct {
    float x, y;     // Enemy's X and Y coordinates in the map
    SDL_Texture *texture; // Texture for rendering the enemy
    bool alive;     // Whether the enemy is alive or defeated
    float speed;    // Movement speed of the enemy (units per frame)
} Enemy;

// Global variables (defined in other source files)
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern int map[MAP_HEIGHT][MAP_WIDTH];
extern Player player;
extern int recoil_offset;
extern SDL_Texture *weapon_texture;
extern Mix_Chunk *gunshot_sound;
extern int player_health;
extern Mix_Chunk *damage_sound;
extern bool show_damage_flash;
extern TTF_Font *font;
extern bool show_fire_effect;       // Flag for fire effect when shooting
extern Uint32 fire_start_time;
extern Mix_Chunk *damage_sound;

// Time when fire effect started

#define MAX_ENEMIES 20
extern Enemy enemies[MAX_ENEMIES];
extern int num_enemies;

// Function prototypes
void draw_walls(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h, float wall_hit_x);
void draw_sky(SDL_Renderer *renderer, SDL_Texture *sky_texture);
void draw_ground(SDL_Renderer *renderer, SDL_Texture *ground_texture);
void draw_weapon(SDL_Renderer *renderer, SDL_Texture *weapon_texture);
void handle_events(int *running);
void move_player(float dx, float dy);
void raycasting(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *sky_texture, SDL_Texture *ground_texture);
void game_loop(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *sky_texture, SDL_Texture *ground_texture, SDL_Texture *weapon_texture);
void fire_weapon(void);
bool load_sounds(void);
void free_sounds(void);
void spawn_enemy(float x, float y, SDL_Texture *texture);
void render_enemies(SDL_Renderer *renderer);
void move_enemies(void);
void enemy_attack(void);
bool init_ttf(void);
void render_health(SDL_Renderer *renderer);
void cleanup_ttf(void);

#endif

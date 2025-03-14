#ifndef RAYCASTING_H
#define RAYCASTING_H

#include "sdl_utils.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Window dimensions
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Map dimensions
#define MAP_WIDTH 8
#define MAP_HEIGHT 8

// Field of View and number of rays
#define FOV 60 * (M_PI / 180) // Convert degrees to radians
#define NUM_RAYS SCREEN_WIDTH // One ray per column

// Player structure
typedef struct {
    float x, y;     // Player position
    float angle;    // Player viewing angle
} Player;

// Global variables
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern int map[MAP_HEIGHT][MAP_WIDTH];
extern Player player;

// Function prototypes
void raycasting(SDL_Renderer *renderer, SDL_Texture *texture);
/**
 * Draws a wall slice with texture mapping.
 */
void draw_walls(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h, float wall_hit_x);

/**
 * Handles SDL events (e.g., keyboard input, window close).
 */
void handle_events(int *running);

/**
 * Moves the player by (dx, dy) if the new position is not a wall.
 */
void move_player(float dx, float dy);

/**
 * Casts rays and renders the walls.
 */
void cast_rays(SDL_Renderer *renderer, SDL_Texture *texture);

/**
 * Main game loop.
 */
void game_loop(SDL_Renderer *renderer, SDL_Texture *texture);

#endif /* RAYCASTING_H */

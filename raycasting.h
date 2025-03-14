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
    float x, y;
    float angle;
} Player;

// Global variables
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern int map[MAP_HEIGHT][MAP_WIDTH];
extern Player player;

// Function prototypes
// Add function prototype
SDL_Renderer *get_renderer();
void draw_walls(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h);
void handle_events(SDL_Event *event); // Ensure correct parameter


int init_sdl();
void close_sdl();
void move_player(float dx, float dy);
SDL_Texture *loadTexture(const char *path, SDL_Renderer *renderer);
#endif /* RAYCASTING_H */

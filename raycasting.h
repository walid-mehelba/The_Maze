#ifndef RAYCASTING_H
#define RAYCASTING_H

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
int init_sdl();
void close_sdl();
void draw_walls();
void handle_events(int *running);
void move_player(float dx, float dy);
void draw_walls();
#endif /* RAYCASTING_H */

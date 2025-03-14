#include "raycasting.h"

// Define the player variable
Player player = {3.5, 3.5, M_PI / 4}; // Initial position and angle

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
                player.angle -= 0.1; // Rotate left
            } else if (event.key.keysym.sym == SDLK_d) {
                player.angle += 0.1; // Rotate right
            } else if (event.key.keysym.sym == SDLK_LEFT) {
                player.angle -= 0.1; // Rotate left (arrow key)
            } else if (event.key.keysym.sym == SDLK_RIGHT) {
                player.angle += 0.1; // Rotate right (arrow key)
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

void move_player(float dx, float dy) {
    int new_x = (int)(player.x + dx);
    int new_y = (int)(player.y + dy);

    if (map[new_y][new_x] == 0) { // Prevent walking into walls
        player.x += dx;
        player.y += dy;
    }
}

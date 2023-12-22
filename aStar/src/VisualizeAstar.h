#ifndef VISUALIZE_ASTAR
#include <SDL2/SDL.h>

#define VISUALIZE_ASTAR
#define GRID_ROWS 40
#define GRID_COLS 40
#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800
#define CELL_HEIGHT (WINDOW_HEIGHT / GRID_ROWS)
#define CELL_WIDTH (WINDOW_WIDTH / GRID_COLS)

// Function declaration
void initSDL(SDL_Window **window, SDL_Renderer **renderer);
void cleanUpSDL(SDL_Window *window, SDL_Renderer *renderer);
void initGrid(int grid[GRID_ROWS][GRID_COLS]);
void renderGridLines(SDL_Window *window, SDL_Renderer *renderer);
void renderGrid(SDL_Window *window, SDL_Renderer *renderer,
                const int grid[GRID_ROWS][GRID_COLS]);

#endif

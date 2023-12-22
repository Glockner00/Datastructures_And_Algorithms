
#include "VisualizeAstar.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

void initSDL(SDL_Window **window, SDL_Renderer **renderer) {
    *window = SDL_CreateWindow("A-Star Visualization", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    *renderer = SDL_CreateRenderer(
        *window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void cleanUpSDL(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void initGrid(int grid[GRID_ROWS][GRID_COLS]) {
    for (int i = 0; i < GRID_ROWS; ++i) {
        for (int j = 0; j < GRID_COLS; ++j) {
            grid[i][j] = 0;
        }
    }
}

void renderGridLines(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (int i = 0; i <= GRID_ROWS; ++i) {
        SDL_RenderDrawLine(renderer, 0, i * CELL_HEIGHT, WINDOW_WIDTH,
                            i * CELL_HEIGHT);
    }
    for (int j = 0; j <= GRID_COLS; ++j) {
        SDL_RenderDrawLine(renderer, j * CELL_WIDTH, 0, j * CELL_WIDTH,
                            WINDOW_HEIGHT);
    }
}

void renderGrid(SDL_Window *window, SDL_Renderer *renderer,
                const int grid[GRID_ROWS][GRID_COLS]) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < GRID_ROWS; ++i) {
        for (int j = 0; j < GRID_COLS; ++j) {
            SDL_Rect rect = {(i * CELL_WIDTH), (j * CELL_HEIGHT), CELL_WIDTH,
                            CELL_HEIGHT};

            if (grid[i][j] == 1) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black for obstacles
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255,
                                    255); // white for open cells
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    renderGridLines(window, renderer);
    SDL_RenderPresent(renderer);
}

int main() {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    initSDL(&window, &renderer);
    int grid[GRID_ROWS][GRID_ROWS];
    initGrid(grid);

    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
        renderGrid(window, renderer, grid);
    }
    cleanUpSDL(window, renderer);
    return 0;
}


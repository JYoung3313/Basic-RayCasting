#pragma once
#include <SDL2/SDL.h>

extern int WIDTH;
extern int HEIGHT;

struct Window {
    SDL_Window *pwindow = SDL_CreateWindow("Raycaster Tester",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
};

Window createWindow();
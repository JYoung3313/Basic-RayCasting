#pragma once
#include <SDL2/SDL.h>

#define CELL_SIZE 50

void initMap(int (*arr)[5]);
//int map[5][5];

void drawMap(SDL_Renderer* prenderer, int map[5][5]);
#pragma once
#include <SDL2/SDL.h>

// globals for map sizing
#define MAP_WIDTH 18
#define MAP_HEIGHT 12
#define CELL_SIZE 50

void initMap(int map[MAP_HEIGHT][MAP_WIDTH]);
//int map[5][5];

void drawMap(SDL_Renderer* prenderer, int map[MAP_HEIGHT][MAP_WIDTH]);
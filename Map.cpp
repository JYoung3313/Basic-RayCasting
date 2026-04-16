#include "Map.h"
#include <algorithm> // for std::copy
#include <iterator>  // Essential for std::begin and std::end

// ----------------------- DO Not Use -----------------------
// void initMap(int (*arr)[5]) {
    // int data[25] = {
    //     {0, 0, 0, 1, 0},
    //     {0, 0, 1, 1, 0},
    //     {1, 0, 0, 1, 1},
    //     {1, 0, 0, 0, 0},
    //     {1, 1, 1, 0, 1}
    // };
    // int data[25] = { 0,0,0,1,0, 0,0,1,1,0, 1,0,0,1,1,
    //     1,0,0,0,0, 1,1,1,0,1 };

    // std::copy(std::begin(data), std::end(data), &arr[0][0]);
// }

// New Updated initMap function
// It draws out the map using the dimentions:
// MAP_HEIGHT and MAP_WIDTH globals
void initMap(int map[MAP_HEIGHT][MAP_WIDTH]) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            // If it's the top, bottom, left, or right edge, make it a wall (1)  
            if (x == 0 || y == 0 || x == MAP_WIDTH - 1 || y == MAP_HEIGHT - 1) {
                map[y][x] = 1;
            } else {
                map[y][x] = 0; // empty space inside if 0
            }
            // Optional: throws in a couple of random pillars in the middle to test the rays!
            if (x == 5 && y == 5) map[y][x] = 1;
            if (x == 10 && y == 8) map[y][x] = 1;
        }
    } 
}

// Draws the map blocks Using the globals
void drawMap(SDL_Renderer* prenderer, int map[MAP_HEIGHT][MAP_WIDTH]) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            // If the array has a 1 (or greater), it's a wall
            if (map[y][x] > 0) {
                // Calculate the pixel position by multiplying by CELL_SIZE
                SDL_Rect wall_rect = {
                    x * CELL_SIZE,
                    y * CELL_SIZE,
                    CELL_SIZE,  // Width
                    CELL_SIZE   // Height
                };

                // Set color to Gray for the walls
                SDL_SetRenderDrawColor(prenderer, 100, 100, 100, 255);
                SDL_RenderFillRect(prenderer, &wall_rect);

                // Optional: Draw a slightly darker outline
                // so you can see individual blocks
                // Im doing this Mostly for testing
                SDL_SetRenderDrawColor(prenderer, 50, 50, 50, 255);
                SDL_RenderDrawRect(prenderer, &wall_rect);
            }
        }
    }
}
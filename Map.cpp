#include "Map.h"
#include <algorithm> // for std::copy
#include <iterator>  // Essential for std::begin and std::end


void initMap(int (*arr)[5]) {
    // int data[25] = {
    //     {0, 0, 0, 1, 0},
    //     {0, 0, 1, 1, 0},
    //     {1, 0, 0, 1, 1},
    //     {1, 0, 0, 0, 0},
    //     {1, 1, 1, 0, 1}
    // };
    int data[25] = { 0,0,0,1,0, 0,0,1,1,0, 1,0,0,1,1,
        1,0,0,0,0, 1,1,1,0,1 };

    std::copy(std::begin(data), std::end(data), &arr[0][0]);
}

// Draws the map blocks
void drawMap(SDL_Renderer* prenderer, int map[5][5]) {
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            // If the array has a 1 (or greater), it's a wall
            if (map[y][x] > 0) {
                
            }
        }
    }
}
// Copyright [2026] <Justin J. Young>
// Used tutorial from @HirschDaniel from Youtube.
#include <SDL2/SDL.h>
#include "Map.h"    // This initializes the map and does a few other things
#include "Player.h"
#include "Color.h"
#include "Ray.h"
#include "Vec.h"
#include "Intersection.h"

// Window dimentions
#define WIDTH 900
#define HEIGHT 600

// Global for player_pov
// #define PLAYER_POV 60
 
// Globals for Color
// Global for cells
// #define CELL_SIZE 50 -> moved to map.h
// actual global vars
bool app_running = true;
// int map[5][5]; -> updated to something less hardCoded
// eventually if i want to design complex mazes without coding them in C++,
// the standard trick is to write a helper function that reads a .txt file
// line by line (using std::ifstream). I can literally "draw" your maze in
// a text file using Notepad (with 1s and 0s) and have my program load it!
int map[MAP_HEIGHT][MAP_WIDTH];

// Player player = { 0, 0 };
Player player = { {1.5f * 5, 1.5f}, 45.0f };

void checkEvents(SDL_Event event) {
    while (SDL_PollEvent(&event)) { // loop for events
        switch(event.type) {
            case SDL_QUIT:
                app_running = false;
                break;
        }
    }
}

void drawPlayer(SDL_Renderer *prenderer, Player player) {
    // Multiply grid position by CELL_SIZE to get screen pixels
    SDL_Rect player_rect = {
        (int)(player.position.x * CELL_SIZE),
        (int)(player.position.y * CELL_SIZE),
        10, 10
    };
    
    // Set color to PLAYER_COLOR (Hex 0xEFBF04 -> RGB: 239, 191, 4)
    SDL_SetRenderDrawColor(prenderer, 239, 191, 4, 255); // PLAYER_COLOR
    SDL_RenderFillRect(prenderer, &player_rect);
}

// helper for mainloop that renders the graphics in 3d
void render3D(SDL_Renderer* prenderer, Ray& ray, Player& p,
    int map[MAP_HEIGHT][MAP_WIDTH]) {
    float fov = 60.0f;      // init fov
    int numRays  = WIDTH;   // init number of Rays
    float angleStep = fov / (float)numRays;     // Makes steps for angle
    float startAngle = p.angle - (fov / 2.0f);  // Takes starting angle
    
    // Loops through every ray applying math and physics to 
    // render 3d Graphics 
    for (int i = 0; i < numRays; i++) {
        float currentAngle = startAngle + (i * angleStep);
        HitInfo hit = getDDAIntersection(ray, currentAngle, map);

        // CHecks if ray hits
        if (hit.hit) {
            // Fixes fish-eye effect
            float relativeAngle = (currentAngle - p.angle) * (M_PI / 180.0f);
            float correctedDist = hit.distance * SDL_cos(relativeAngle);

            // Calculate height (The '50' scales it based on your grid)
            int lineHight = (int)(HEIGHT / correctedDist);

            // Clamps the drawing points so they don't go off-screen
            int drawStart = -lineHight / 2 + HEIGHT / 2;
            if (drawStart < 0) drawStart = 0;
            int drawEnd = lineHight / 2 + HEIGHT / 2;
            if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

            // Simple Shading: side 0 is North/South, side 1 is east/west
            if (hit.side == 1) {
                SDL_SetRenderDrawColor(prenderer, 140, 140, 140, 255);
            } else {
                SDL_SetRenderDrawColor(prenderer, 100, 100, 100, 255);
            }
            SDL_RenderDrawLine(prenderer, i, drawStart, i, drawEnd);
        }
    }
}

// Main loop for main function that runs and updates everything
void mainLoop(SDL_Renderer *prenderer, SDL_Window *pwindow, Ray& ray, Player& player) {
    // Counter to create more Shapes or objects    
    while (app_running) {   // Main loop for running GUI
        SDL_Event event;
        checkEvents(event);
        //SDL_Rect rect = { WIDTH/2, HEIGHT/2, 100 + counter++, 100 + counter };    // creates rectangle
        //SDL_FillRect(psurface, &rect, COLOR_WHITE);     // files in rect or retangle

        // Clear the screen (Paint it black to erase the previous frame)
        SDL_SetRenderDrawColor(prenderer, 0, 0, 0, 255);
        SDL_RenderClear(prenderer);

        ray.update(player);

        // Draw Ceiling (Top half of screen)
        SDL_SetRenderDrawColor(prenderer, 50, 50, 150, 255); // Blue-ish
        SDL_Rect ceiling = {0, 0, WIDTH, HEIGHT / 2};
        SDL_RenderFillRect(prenderer, &ceiling);

        // Draw Floor (Bottom half of screen)
        SDL_SetRenderDrawColor(prenderer, 30, 30, 30, 255); // Dark Gray
        SDL_Rect floor = {0, HEIGHT / 2, WIDTH, HEIGHT / 2};
        SDL_RenderFillRect(prenderer, &floor);

        render3D(prenderer, ray, player, map);

        // Draws map
        // drawMap(prenderer, map);

        // Draw the Player
        // drawPlayer(prenderer, player);

        // update the ray's starting Pos to match the player
        // ray.update(player);

        // Calculate the DDA Intersection
        // This uses the global 'map' array defined at the top of raycaster.cpp
        // HitInfo hit = getDDAIntersection(ray, player.angle, map);   // getting hit record

        // Draw the Ray Line
        // if (hit.hit) {
        //     SDL_SetRenderDrawColor(prenderer, 255, 255, 255, 255);

        //     // Draw from the ray's origin to the exact hitPoint calculated in DDA
        //     SDL_RenderDrawLineF(prenderer,
        //         ray.x * CELL_SIZE,
        //         ray.y * CELL_SIZE,
        //         hit.hitPoint.x * CELL_SIZE,
        //         hit.hitPoint.y * CELL_SIZE
        //     );
        // }
        
        // ^ left off here 50:11 for vid
        SDL_RenderPresent(prenderer);   // updates surface/window
        SDL_Delay(10);   // delays before loop again
    }
    //SDL_Delay(3000);         // Delays window from closing 
}

// Main function where all the magic happens.
int main(int argc, char* argv[]) {
    initMap(map);

    Ray ray; // Init ray

    // Initilizing window
    SDL_Init(SDL_INIT_VIDEO);   // Initialises state for sdl
    SDL_Window *pwindow = SDL_CreateWindow("Raycaster Tester",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);  // Creates window
    // SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);  // Creates a surface for window
    SDL_Renderer *prenderer = SDL_CreateRenderer(pwindow, -1, SDL_RENDERER_ACCELERATED);
    // calls main loop function allowing to free up space in main function
    mainLoop(prenderer, pwindow, ray, player);

    //SDL_Delay(3000);         // Delays window from closing 
    return 0;
}
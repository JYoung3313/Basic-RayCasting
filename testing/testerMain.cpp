// Tester for math
#include <SDL2/SDL.h>
#include "Map.h"    // This initializes the map and does a few other things
#include "Player.h"
#include "Color.h"
#include "Ray.h"
#include "Vec.h"
#include <iostream>

// Finding the mangitue of the Ray
float testMag(Ray& r) {
    float magn = r.magnitiude();
    return magn;
}

void testing_magn(float test1) {
    // test part for magn
    std::cout << "Ray 1: testing magnitiude..." << std::endl;
    std::cout << "\nRay1 Magnitiude = \n" << test1 << std::endl; 
}

void testing_dir(SDL_FPoint dir1) {
    std::cout << "\nDirection X: " << dir1.x <<
    " Y: " << dir1.y << std::endl;
}

int main(int argc, char* argv[]) {
    Ray r;
    Player player;
    player.position.x = 0.5;
    player.position.y = 1.5;
    //player.angle = 45.0f;
    // SDL_FPoint dir1 = r.vecFromAngle(player);
    
    r.update(player);

    // test for magn
    float test1 = testMag(r);
    testing_magn(test1);

    player.angle = 45.0f;
    SDL_FPoint dir1 = r.vecFromAngle(player);

    // test for dir
    testing_dir(dir1);
    return 0;
}

    
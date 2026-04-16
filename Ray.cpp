// Copyright [2026] <Justin J. Young>
#include "Ray.h"
#include <cmath>

// Update the ray's inherited coordinates to match the player
void Ray::update(const Player& p) {
    this->x = p.position.x;
    this->y = p.position.y;
    // this->z = p.position.z;
}

// Calculates the magnitude (length) of a ray
float Ray::magnitiude() {
    return std::hypot(this->x, this->y);
}

// Calculate a direction vector based on player position
// Convert degrees to radians: (degrees * PI / 180)
// SDL_FPoint Ray::direction(const Player& p) {
//     const float PI = 3.1415926535f; // const for pi
//     SDL_FPoint dir;
//     float rads = p.angle * (PI / 180.0f);   // Convert deg to rads

//     float mag = this->magnitiude();  // calc magnititude

//     // Calcualting the direction using:
//     // cos(rads) and sin(rads) and multipling both by mag
//     // to get the direction vec of player.x and player.y
//     dir.x = SDL_cos(rads) * mag;
//     dir.y = SDL_sin(rads) * mag;

//     return dir;
// }

// Distance the ray has to travel to go from 1 x-side to next x-side
// Vec2D Ray::deltaDist(SDL_FPoint dir) {
//     Vec2D deltaPos;
//     float deltaDistX = (dir.x == 0) ? 1e30 : SDL_abs(1.0f / dir.x);
//     float deltaDistY = (dir.y == 0) ? 1e30 : SDL_abs(1.0f / dir.x);

//     deltaPos.x = deltaDistX;
//     deltaPos.y = deltaDistY;

//     return deltaPos;
// }

void Ray::calcuateMath(float angle) {
    const float PI = 3.1415926535f; // const for pi
    float rads = angle * (PI / 180.0f);   // Convert deg to rads

    // Set Direction
    this->dir.x = SDL_cos(rads);
    this->dir.y = SDL_sin(rads);

    // Set Delta Distaances
    this->deltaDist.x = (dir.x == 0) ? 1e30 : SDL_abs(1.0f / dir.x);
    this->deltaDist.y = (dir.y == 0) ? 1e30 : SDL_abs(1.0f / dir.y);
}



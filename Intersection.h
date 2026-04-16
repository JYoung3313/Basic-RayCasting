// Copyright [2026] <Justin J. Young>
#pragma once
#include "Vec.h"
#include "Ray.h"
#include "Map.h"
#include <SDL2/SDL.h>

struct HitInfo {
    bool hit;
    float distance;
    SDL_Point mapPos;   // Which grid cell did we hit?
    int side;       // 0 for East/West hit, 1 for North/South (useful for shading)
    Vec2D hitPoint; // The exact world cordinates of the hit
};

// GetIntersetion prototype
HitInfo getDDAIntersection(Ray& ray, float angle, int map[MAP_HEIGHT][MAP_WIDTH]);
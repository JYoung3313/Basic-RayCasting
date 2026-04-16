// Copyright [2026] <Justin J. Young>
#pragma once
#include <SDL2/SDL.h>
#include "Player.h"
#include "Vec.h"

struct Ray : Vec2D {
    Vec2D origin;
    Vec2D dir;
    Vec2D deltaDist;
    
    void update(const Player& p);
    // Calculates the magnitiude of the ray
    float magnitiude();
    //Vec2D vector_from_angle( angle, double magnitude)

    void calcuateMath(float angle);
};


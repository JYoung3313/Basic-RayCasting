// Copyright [2026] <Justin J. Young>
// Vector class that creates 2 and 3D vectors
#pragma once

struct Vec2D {
    float x, y;
    Vec2D(float _x = 0, float _y = 0) : x(_x), y(_y) {}
};

struct Vec3D : Vec2D {
    float z;
    Vec3D(float _x = 0, float _y = 0, float _z = 0) 
        : Vec2D(_x, _y), z(_z) {}
};
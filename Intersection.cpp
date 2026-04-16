// Copyright [2026] <Justin J. Young>
#include "Intersection.h"
#include "Ray.h"
#include "Vec.h"
#include <cmath>
#include <algorithm>

// Helper to determine initial step and side distances
void initStep(const Ray& ray, int& stepX, int& stepY,
    Vec2D& sideDist, int mapX, int mapY) {
    if (ray.dir.x < 0) {
        stepX = -1;
        sideDist.x = (ray.x - mapX) * ray.deltaDist.x;
    } else {
        stepX = 1;
        sideDist.x = (mapX + 1.0f - ray.x) * ray.deltaDist.x;
    }

    if (ray.dir.y < 0) {
        stepY = -1;
        sideDist.y = (ray.y - mapY) * ray.deltaDist.y;
    } else {
        stepY = 1;
        sideDist.y = (mapY + 1.0f - ray.y) * ray.deltaDist.y;
    }
    
}

Vec2D map_Pos(Ray& ray) {
    Vec2D mapPos;
    int mapX = int(ray.x);
    int mapY = int(ray.y);
    mapPos.x = (float)mapX;
    mapPos.y = (float)mapY;

    return mapPos;
}

// Simple DDA Loop
void mainLoop(HitInfo& info, Vec2D& sideDist, Ray& ray, int& stepX,
    int& stepY, int& mapX, int& mapY, int map[5][5]) {
    
    while (!info.hit) {
        if (sideDist.x < sideDist.y) {
            sideDist.x += ray.deltaDist.x;
            mapX += stepX;
            info.side = 0;
        } else {
            sideDist.y += ray.deltaDist.y;
            mapY += stepY;
            info.side = 1;
        }

        // Bounds check and wall hit
        if (mapX < 0 || mapX >= 5 || mapY < 0 || mapY >= 5) return;
        if (map[mapY][mapX] > 0) {
            info.hit = true;
            info.mapPos = {mapX, mapY};

            // Perpendicular distance calculation
            info.distance = 
                (info.side == 0) ? (sideDist.x - ray.deltaDist.x) :
                                    (sideDist.y - ray.deltaDist.y);
            // Calcuates and stores the exact hit points
            // Start point + (direction * distance)
            info.hitPoint.x = ray.x + (ray.dir.x * info.distance);
            info.hitPoint.y = ray.y + (ray.dir.y * info.distance);
        }
    }
}

HitInfo getDDAIntersection(Ray& ray, float angle, int map[5][5]) {
    // init HitInfo
    HitInfo info = {false, 0.0f, {0, 0}, 0};
    
    // Preping Ray Math
    ray.calcuateMath(angle);

    // Setup For the girl Positions using the helper
    Vec2D mPos = map_Pos(ray);
    int mapX = (int)mPos.x;
    int mapY = (int)mPos.y;
    
    Vec2D sideDist;
    int stepX, stepY;

    initStep(ray, stepX, stepY, sideDist, mapX, mapY);

    // Class the main loop
    mainLoop(info, sideDist, ray, stepX, stepY, mapX, mapY, map);

    return info;
}


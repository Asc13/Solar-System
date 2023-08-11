#include "../../include/Shared/Vec2.h"

Vec2::Vec2(float x, float y) {
    _x = x;
    _y = y;
}

float Vec2::getX() const {
    return _x;
}

float Vec2::getY() const {
    return _y;
}
#include "../../../include/Engine/Transformation/RotateTime.h"

RotateTime::RotateTime(float time, float x, float y, float z) {
    _time = time;
    _x = x;
    _y = y;
    _z = z;
}

float RotateTime::getTime() {
    return _time;
}

float RotateTime::getX() {
    return _x;
}

float RotateTime::getY() {
    return _y;
}

float RotateTime::getZ() {
    return _z;
}
TransformationType RotateTime::getTransformationType(){
    return ROTATETIME;
}


#include "../../../include/Engine/Transformation/Rotate.h"

Rotate::Rotate(float angle, float x, float y, float z) {
    _angle = angle;
    _x = x;
    _y = y;
    _z = z;
}

float Rotate::getAngle() {
    return _angle;
}

float Rotate::getX() {
    return _x;
}

float Rotate::getY() {
    return _y;
}

float Rotate::getZ() {
    return _z;
}

TransformationType Rotate::getTransformationType() {
    return ROTATE;
}

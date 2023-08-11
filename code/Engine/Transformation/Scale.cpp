#include "../../../include/Engine/Transformation/Scale.h"

Scale::Scale(float x, float y, float z) {
    _x = x;
    _y = y;
    _z = z;
}

float Scale::getX() {
    return _x;
}

float Scale::getY() {
    return _y;
}

float Scale::getZ() {
    return _z;
}

TransformationType Scale::getTransformationType() {
    return SCALE;
}

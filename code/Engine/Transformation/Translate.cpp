#include "../../../include/Engine/Transformation/Translate.h"

Translate::Translate(float x, float y, float z) {
    _x = x;
    _y = y;
    _z = z;
}

float Translate::getX() {
    return _x;
}

float Translate::getY() {
    return _y;
}

float Translate::getZ() {
    return _z;
}
TransformationType  Translate::getTransformationType(){
    return TRANSLATE;
}

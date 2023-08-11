#ifndef ENGINE_SCALE_H
#define ENGINE_SCALE_H

#include "Transformation.h"

class Scale : public Transformation {
private:
    float _x, _y, _z;
public:
    Scale(float, float, float);
    float getX();
    float getY();
    float getZ();
    TransformationType getTransformationType();
};

#endif //ENGINE_SCALE_H

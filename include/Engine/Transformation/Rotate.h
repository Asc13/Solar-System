#ifndef ENGINE_ROTATE_H
#define ENGINE_ROTATE_H

#include "Transformation.h"

class Rotate : public Transformation {
    private:
        float _angle, _x, _y, _z;
    public:
        Rotate(float, float, float, float);
        float getAngle();
        float getX();
        float getY();
        float getZ();
        TransformationType getTransformationType();
};

#endif //ENGINE_ROTATE_H

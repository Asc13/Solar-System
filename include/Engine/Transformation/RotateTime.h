#ifndef ENGINE_ROTATETIME_H
#define ENGINE_ROTATETIME_H

#include "Transformation.h"

class RotateTime : public Transformation {
    private:
        float _time, _x, _y, _z;
    public:
        RotateTime(float, float, float, float);
        float getTime();
        float getX();
        float getY();
        float getZ();
        TransformationType getTransformationType();
};

#endif //ENGINE_ROTATETIME_H

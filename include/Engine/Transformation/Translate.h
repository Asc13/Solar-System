#ifndef ENGINE_TRANSLATE_H
#define ENGINE_TRANSLATE_H

#include "Transformation.h"

class Translate : public Transformation {
private:
    float _x, _y, _z;
public:
    Translate(float, float, float);
    float getX();
    float getY();
    float getZ();
    TransformationType getTransformationType();
};


#endif //ENGINE_TRANSLATE_H

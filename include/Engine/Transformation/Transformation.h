#ifndef ENGINE_TRANSFORMATION_H
#define ENGINE_TRANSFORMATION_H

enum TransformationType{
    INVALID,
    TRANSLATE,
    ROTATE,
    SCALE,
    TRANSLATETIME,
    ROTATETIME
};

class Transformation {
public:
    Transformation();

    virtual TransformationType getTransformationType();
};

#endif

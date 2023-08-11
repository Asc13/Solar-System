#ifndef ENGINE_TRANSLATETIME_H
#define ENGINE_TRANSLATETIME_H

#include "../../Shared/Point.h"
#include "Transformation.h"
#include "../CatmullRom.h"

class TranslateTime : public Transformation {
private:
    float _time;
    std::vector<Point> _pontos;
    CatmullRom *_catmullRom;
    std::vector<float> _y{0.0f,1.0f,0.0f};
public:
    TranslateTime(float, std::vector<Point>);
    float getTime();
    CatmullRom *getCatullRom();
    std::vector<Point> getPoints();
    TransformationType getTransformationType();
    std::vector<float> getYVec();
    void setYVec(std::vector<float>);
};

#endif //ENGINE_TRANSLATETIME_H

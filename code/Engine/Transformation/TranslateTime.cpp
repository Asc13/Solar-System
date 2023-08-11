#include "../../../include/Engine/Transformation/TranslateTime.h"

#include <utility>

TranslateTime::TranslateTime(float time, std::vector<Point> pontos) {
    _time = time;
    _pontos = pontos;
    _catmullRom = new CatmullRom(pontos);
}

float TranslateTime::getTime() {
    return _time;
}

CatmullRom *TranslateTime::getCatullRom(){
  return _catmullRom;
}

std::vector<Point> TranslateTime::getPoints() {
    return _pontos;
}

TransformationType TranslateTime::getTransformationType(){
    return TRANSLATETIME;
}

std::vector<float> TranslateTime::getYVec(){
    return _y;
}

void TranslateTime::setYVec(std::vector<float> vec) {
    _y = std::move(vec);
}


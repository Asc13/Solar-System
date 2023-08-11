#ifndef GENERATOR_BOX_H
#define GENERATOR_BOX_H

#include <cmath>
#include <cstring>
#include <cstring>
#include <fstream>
#include "../Shared/Point.h"
#include "../Shared/Vec2.h"

using namespace std;

class Box {
    private:
        float _length;
        float _width;
        float _height;
        int _dpe;

    public:
        Box(float length, float width, float height, int dpe);
        void generatePoints(vector<Point> & pontos, vector<Point> & normais, vector<Vec2> & textures) const;
};

#endif
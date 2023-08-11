#ifndef GENERATOR_CONE_H
#define GENERATOR_CONE_H

#include <cmath>
#include <cstring>
#include <fstream>
#include "../../include/Shared/Point.h"
#include "../Shared/Vec2.h"

using namespace std;

class Cone {
    protected:
        float _base_radius;
        float _height;
        int _slices;
        int _stacks;

    public:
        Cone(float base_radius, float height, int slices, int stacks);
        float getBaseRadius() const;
        float getHeight() const;
        int getSlices() const;
        int getStacks() const;
        virtual void generatePoints(vector<Point> &, vector<Point> &, vector<Vec2> &);
};
#endif
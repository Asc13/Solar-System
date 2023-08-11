#ifndef GENERATOR_CYLINDER_H
#define GENERATOR_CYLINDER_H
#include <cmath>
#include <cstring>
#include <cstring>
#include <fstream>
#include "../Shared/Point.h"
#include "../Shared/Vec2.h"

using namespace std;

class Cylinder {
    protected:
        float _base_radius;
        float _height;
        int _slices;
        int _stacks;

    public:
        Cylinder(float base_radius, float height, int slices, int stacks);
        void generatePoints(vector<Point> &, vector<Point> &, vector<Vec2> &) const;
};

#endif

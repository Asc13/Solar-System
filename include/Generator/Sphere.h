#ifndef GENERATOR_SPHERE_H
#define GENERATOR_SPHERE_H

#include <cmath>
#include <cstring>
#include <cstring>
#include <fstream>
#include "../Shared/Point.h"
#include "../Shared/Vec2.h"

using namespace std;

class Sphere {
    private:
        float _radius;
        int _slices;
        int _stacks;
    public:
        Sphere(float radius, int slices, int stacks);
        void generatePoints(vector<Point> &, vector<Point> &, vector<Vec2> &) const;
};

#endif //GENERATOR_SPHERE_H

#ifndef GENERATOR_TORUS_H
#define GENERATOR_TORUS_H

#include <cmath>
#include <cstring>
#include <fstream>
#include "../Shared/Point.h"
#include "../Shared/Vec2.h"

class Torus {
    private:
        float _outer_radius;
        float _inner_radius;
        int _slices;
        int _stacks;
    public:
        Torus(float radius, float size, int slices, int stacks);
        void generatePoints(std::vector<Point>&, std::vector<Point>&,std::vector<Vec2>&) const;
};


#endif //GENERATOR_TORUS_H

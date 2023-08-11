
#ifndef ENGINE_TUBE_H
#include "Cylinder.h"
#define ENGINE_TUBE_H
#include "../Shared/Point.h"
#include "../Shared/Vec2.h"

class Tube : public Cylinder {
    private:
        float _inner_radius;
    public:
        Tube(float baseRadius, float innerRadius, float height, int slices, int stacks);
        void generatePoints(std::vector<Point>&, std::vector<Point>&, std::vector<Vec2>&);
};


#endif //ENGINE_TUBE_H

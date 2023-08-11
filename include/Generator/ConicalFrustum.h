
#ifndef ENGINE_CONICALFRUSTRUM_H
#include "Cone.h"
#include "../Shared/Point.h"
#define ENGINE_CONICALFRUSTRUM_H


class ConicalFrustum : public Cone{
    private:
        float _height_cut;
    public:
        ConicalFrustum(float, float, float, int, int);
        void generatePoints(std::vector<Point>&, std::vector<Point>&, std::vector<Vec2>&);
};

#endif //ENGINE_CONICALFRUSTRUM_H



#ifndef ENGINE_SPHEREBOUNDINGVOLUME_H
#define ENGINE_SPHEREBOUNDINGVOLUME_H


#include <vector>
#include "../Shared/Point.h"
#include "BoundingVolume.h"

class SphereBoundingVolume : public BoundingVolume {
    public:
        SphereBoundingVolume(std::vector<Point>&);
};


#endif //ENGINE_SPHEREBOUNDINGVOLUME_H

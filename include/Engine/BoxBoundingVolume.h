
#ifndef ENGINE_BOXBOUNDINGVOLUME_H
#define ENGINE_BOXBOUNDINGVOLUME_H


#include "BoundingVolume.h"

class BoxBoundingVolume : public BoundingVolume{
    public:
        BoxBoundingVolume(std::vector<Point> &modelPoints);
        bool isInsideFrustum() override;

};


#endif //ENGINE_BOXBOUNDINGVOLUME_H

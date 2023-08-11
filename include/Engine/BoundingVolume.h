
#ifndef ENGINE_BOUNDINGVOLUME_H
#define ENGINE_BOUNDINGVOLUME_H


#include <vector>
#include "../Shared/Point.h"

class BoundingVolume {
    private:
        std::vector<Point> _points;
    public:
        BoundingVolume();
        BoundingVolume(BoundingVolume&);
        std::vector<Point> getPoints();
        void setPoints(std::vector<Point>&);
        virtual bool isInsideFrustum();

};


#endif //ENGINE_BOUNDINGVOLUME_H

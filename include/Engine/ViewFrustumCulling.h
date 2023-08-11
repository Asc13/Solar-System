#ifndef CG_TP_VIEWFRUSTUMCULLING_H
#define CG_TP_VIEWFRUSTUMCULLING_H

#include "../Shared/Point.h"
#include "Model.h"
#include <vector>
#include <tuple>

using namespace std;

class ViewFrustumCulling {

    private:
        float _fov;
        float _ratio;
        float _near;
        float _far;

        float _heightNear;
        float _widthNear;

        float _heightFar;
        float _widthFar;

        // 0 - Near  1 - Far  2 - Right  3 - Left   4 - Top   5 - Bottom  (tuple(ponto e normal para criar o plano))
        vector<tuple<vector<float>, vector<float>>> _planes;
        vector<float> _planesConst;

    public:
        ViewFrustumCulling(float, float, float, float);

        float getFOV() const;
        float getNear() const;
        float getFar() const;
        float getRatio() const;

        void setupPlanes(Point p, Point up, Point d, Point r);
        void planesConstCalc(vector<float> &planesConst, int planeIndex);
        float pointDistToPlane(Point point, int planeIndex);
        bool insideFrustum(vector<Point> &boundingVolumeModels);
        void boxesSetup(vector<Model> & models, vector<vector<Point>> & boundingVolumeModels);
        void boxesUpdate(float *transMatrix, vector<bool> & flagIndexes, vector<vector<Point>> & boundingVolumeModels);
};

#endif //CG_TP_VIEWFRUSTUMCULLING_H
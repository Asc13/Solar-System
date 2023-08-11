#include "../../include/Engine/ViewFrustumCulling.h"
#include "../../include/Shared/Maths.h"
#include "../../include/Engine/BoxBoundingVolume.h"
#include "../../include/Engine/SphereBoundingVolume.h"


ViewFrustumCulling::ViewFrustumCulling(float fov, float ratio, float near, float far) {
    _fov = fov;
    _ratio = ratio;
    _near = near;
    _far = far;

    _heightFar = 2 * tan(fov / 2) * _far;
    _widthFar = _heightFar * _ratio;
    _heightNear = 2 * tan(fov / 2) * _near;
    _widthNear = _ratio;
}


float ViewFrustumCulling::getFOV() const {
    return _fov;
}


float ViewFrustumCulling::getNear() const {
    return _near;
}

float ViewFrustumCulling::getFar() const {
    return _far;
}

float ViewFrustumCulling::getRatio() const {
    return _ratio;
}

void ViewFrustumCulling::setupPlanes(Point p, Point up, Point d, Point r) {

    vector<float> pVec = p.pointAsVector();
    vector<float> dVec = Maths::normalize(d.pointAsVector());
    vector<float> upVec = Maths::normalize(up.pointAsVector());
    vector<float> rVec = Maths::normalize(r.pointAsVector());

    // Plane Points
    vector<float> nearPointCenter = Maths::add(pVec, Maths::multiply(dVec, _near));
    vector<float> farPointCenter = Maths::add(pVec, Maths::multiply(dVec, _far));

    vector<float> nearPoint1 = Maths::sub(Maths::add(nearPointCenter, Maths::multiply(upVec, _heightNear/2.0f)), Maths::multiply(rVec, _widthNear/2.0f));
    vector<float> nearPoint2 = Maths::add(Maths::add(nearPointCenter, Maths::multiply(upVec, _heightNear/2.0f)), Maths::multiply(rVec, _widthNear/2.0f));
    vector<float> nearPoint3 = Maths::add(Maths::sub(nearPointCenter, Maths::multiply(upVec, _heightNear/2.0f)), Maths::multiply(rVec, _widthNear/2.0f));

    vector<float> farPoint1 = Maths::sub(Maths::add(farPointCenter, Maths::multiply(upVec, _heightFar/2.0f)), Maths::multiply(rVec, _widthFar/2.0f));
    vector<float> farPoint2 = Maths::add(Maths::add(farPointCenter, Maths::multiply(upVec, _heightFar/2.0f)), Maths::multiply(rVec, _widthFar/2.0f));
    vector<float> farPoint3 = Maths::add(Maths::sub(farPointCenter, Maths::multiply(upVec, _heightFar/2.0f)), Maths::multiply(rVec, _widthFar/2.0f));
    vector<float> farPoint4 = Maths::sub(Maths::sub(farPointCenter, Maths::multiply(upVec, _heightFar/2.0f)), Maths::multiply(rVec, _widthFar/2.0f));

    // Near Plane
    _planes.emplace_back(nearPointCenter, dVec);

    // Far Plane
    _planes.emplace_back(farPointCenter, Maths::inverse(dVec));

    // Right Plane
    _planes.emplace_back(farPoint2, Maths::normalize(Maths::cross(Maths::sub(farPoint2, farPoint3), Maths::sub(farPoint2, nearPoint2))));

    // Left Plane
    _planes.emplace_back(farPoint1, Maths::normalize(Maths::cross(Maths::sub(farPoint1, nearPoint1), Maths::sub(farPoint1, farPoint4))));

    // Top Plane
    _planes.emplace_back(farPoint2, Maths::normalize(Maths::cross(Maths::sub(farPoint2, nearPoint2), Maths::sub(farPoint2, farPoint1))));

    // Bottom Plane
    _planes.emplace_back(farPoint3, Maths::normalize(Maths::cross(Maths::sub(farPoint3, farPoint4), Maths::sub(farPoint3, nearPoint3))));

    for(int i = 0; i < 6; ++i) planesConstCalc(_planesConst, i);
}


void ViewFrustumCulling::planesConstCalc(vector<float> & planesConst, int planeIndex) {
    planesConst.push_back(-((get<1>(_planes[planeIndex]))[0] * (get<0>(_planes[planeIndex]))[0] +
                            (get<1>(_planes[planeIndex]))[1] * (get<0>(_planes[planeIndex]))[1] +
                            (get<1>(_planes[planeIndex]))[2] * (get<0>(_planes[planeIndex]))[2]));
}


float ViewFrustumCulling::pointDistToPlane(Point point, int planeIndex) {
    return ((get<1>(_planes[planeIndex]))[0] * point.getX() +
             (get<1>(_planes[planeIndex]))[1] * point.getY() +
             (get<1>(_planes[planeIndex]))[2] * point.getZ() +
             _planesConst[planeIndex]);
}


bool ViewFrustumCulling::insideFrustum(vector<Point> & boundingVolumeModel) {
    vector<bool> flags = {true, true, true, true, true, true};

    for(Point p : boundingVolumeModel)
        for(int i = 0; i < 6; ++i)
            if (pointDistToPlane(p, i) < 0.0f)
                flags[i] = false;

    for(bool b : flags) if(b) return true;
    return false;
}


void dimCalc(Model & model, vector<float> & minMax) {

    float minAuxX = MAXFLOAT, maxAuxX = -MAXFLOAT;
    float minAuxY = MAXFLOAT, maxAuxY = -MAXFLOAT;
    float minAuxZ = MAXFLOAT, maxAuxZ = -MAXFLOAT;

    model.getMinMax(minAuxX, maxAuxX, minAuxY, maxAuxY, minAuxZ, maxAuxZ);

    minMax.push_back(minAuxX);
    minMax.push_back(maxAuxX);

    minMax.push_back(minAuxY);
    minMax.push_back(maxAuxY);

    minMax.push_back(minAuxZ);
    minMax.push_back(maxAuxZ);
}


void applyTranfs(float* transMatrix, vector<Point>& box) {
    for(Point p : box) p.applyTransfPoint(transMatrix);
}


void ViewFrustumCulling::boxesUpdate(float *transMatrix, vector<bool> & flagIndexes, vector<vector<Point>> & boundingVolumeModels) {
    for(vector<Point> box : boundingVolumeModels) {
        applyTranfs(transMatrix, box);
        flagIndexes.push_back(insideFrustum(box));
    }
}


void ViewFrustumCulling::boxesSetup(vector<Model> & models, vector<vector<Point>> & boundingVolumeModels) {

    // Min e Max     0 e 1 -> X    2 e 3 -> Y    4 e 5 -> Z
    vector<float> minMax;

    for(Model & m : models) {
        dimCalc(m, minMax);
        vector<Point> box;

        // p0
        box.emplace_back(minMax[0], minMax[3], minMax[5]);

        // p1
        box.emplace_back(minMax[1], minMax[3], minMax[5]);

        // p2
        box.emplace_back(minMax[0], minMax[3], minMax[4]);

        // p3
        box.emplace_back(minMax[1], minMax[3], minMax[4]);

        // p4
        box.emplace_back(minMax[0], minMax[2], minMax[5]);

        // p5
        box.emplace_back(minMax[1], minMax[2], minMax[5]);

        // p6
        box.emplace_back(minMax[0], minMax[2], minMax[4]);

        // p7
        box.emplace_back(minMax[1], minMax[2], minMax[4]);

        boundingVolumeModels.push_back(box);
    }

}
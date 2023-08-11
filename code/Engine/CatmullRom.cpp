#include "../../include/Engine/CatmullRom.h"

CatmullRom::CatmullRom(std::vector<Point> pontos) {
    _pontos = pontos;
}

void CatmullRom::buildRotMatrix(std::vector<float>& x, std::vector<float>& y, std::vector<float>& z, float*m) {

    m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
    m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
    m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void CatmullRom::getCatmullRomPoint(float t, std::vector<float>& p0, std::vector<float>& p1, std::vector<float>& p2, std::vector<float>& p3, std::vector<float>& pos, std::vector<float>& deriv) {
    float a[4];
    // catmull-rom matrix
    float temp[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
                         { 1.0f, -2.5f,  2.0f, -0.5f},
                         {-0.5f,  0.0f,  0.5f,  0.0f},
                         { 0.0f,  1.0f,  0.0f,  0.0f}};

    float tv[4] = {t*t*t,t*t,t,1};

    float tderiv[4] = {3*t*t,2*t,1,0};

    for(int i = 0; i < 3; i++) {

        float pvector [4] = {p0[i], p1[i], p2[i], p3[i]};

        Maths::multiplyMatrixVector(reinterpret_cast<float *>(temp), 4, 4, pvector, 4, a);

        pos.push_back(Maths::multiplyVectorVector(tv, a, 4));

        deriv.push_back(Maths::multiplyVectorVector(tderiv, a, 4));
    }

}

void CatmullRom::getGlobalCatmullRomPoint(float gt, std::vector<float>& pos, std::vector<float>& deriv) {

    float t = gt * _pontos.size(); // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within  the segment

    // indices store the points
    int indices[4];
    indices[0] = (index + _pontos.size()-1)%_pontos.size();
    indices[1] = (indices[0]+1)%_pontos.size();
    indices[2] = (indices[1]+1)%_pontos.size();
    indices[3] = (indices[2]+1)%_pontos.size();
    std::vector<float> p0 = _pontos[indices[0]].pointAsVector();
    std::vector<float> p1 = _pontos[indices[1]].pointAsVector();
    std::vector<float> p2 = _pontos[indices[2]].pointAsVector();
    std::vector<float> p3 = _pontos[indices[3]].pointAsVector();
    getCatmullRomPoint(t, p0, p1, p2, p3, pos, deriv);
}





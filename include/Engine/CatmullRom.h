#ifndef CG_TP_CATMULLROM_H
#define CG_TP_CATMULLROM_H


#include "../Shared/Point.h"
#include "../Shared/Maths.h"

class CatmullRom {
    private:
        std::vector<Point> _pontos;
    public:
        CatmullRom(std::vector<Point>);
        void getCatmullRomPoint(float t, std::vector<float>& p0, std::vector<float>& p1, std::vector<float>& p2, std::vector<float>& p3, std::vector<float>& pos, std::vector<float>& deriv);
        void getGlobalCatmullRomPoint(float gt, std::vector<float>& pos, std::vector<float>& deriv);
        void static buildRotMatrix(std::vector<float>& x, std::vector<float>& y, std::vector<float>& z, float*);
};


#endif //CG_TP_CATMULLROM_H

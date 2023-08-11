#ifndef CG_TP_TEAPOT_H
#define CG_TP_TEAPOT_H

#include <cmath>
#include <cstring>
#include <cstring>
#include <fstream>
#include "../Shared/Point.h"
#include "../Shared/Vec2.h"

using namespace std;

class Teapot {
    private:
        int _nrIndexes{};
        int _nrControlPoints{};
        float _xDelta{}, _yDelta{};
        int _tesselation;
        std::vector<std::vector<int>> _indexes;
        std::vector<Point> _controlPoints;

    public:
        Teapot(int tesselation, char *path);
        void generatePoints(vector<Point> & pontos, vector<Point> & normais, vector<Vec2> & texturas);
        void pointsFromPatch(vector<Point> & cp, vector<Point> & pontos, vector<Point> & normais, vector<Vec2> & texturas) const;
};


#endif //CG_TP_TEAPOT_H

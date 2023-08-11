#ifndef ENGINE_ICOSAHEDRON_H
#define ENGINE_ICOSAHEDRON_H

#include "../Shared/Point.h"
#include "../Shared/Vec2.h"
#include <cmath>
#include <cstring>
#include <cstring>
#include <fstream>

using namespace std;

class Icosahedron {
    private:
        float _length;
        float _width;
        int _dpe;

    public:
        Icosahedron(float length, float width, int dpe);
        void generatePoints(vector<Point> & pontos, vector<Point> & normais, vector<Vec2> & texturas) const;
        void geodesicTriangles(Point p1, Point p2, Point p3, vector<Point> & pontos, vector<Point> & normais, vector<Vec2> & texturas, float deltaW, float deltaH) const;
};

#endif //ENGINE_ICOSAHEDRON_H

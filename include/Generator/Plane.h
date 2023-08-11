#ifndef GENERATOR_PLANE_H
#define GENERATOR_PLANE_H

#include <cmath>
#include <cstring>
#include <cstring>
#include <fstream>
#include "../Shared/Point.h"
#include "../Shared/Vec2.h"

class Plane {
	private:
        float _width;
        float _length;
        int _divisions;

	public:
		Plane(float width, float length, int divisions);
		void generatePoints(std::vector<Point> &, std::vector<Point> &, std::vector<Vec2> &) const;
};

#endif //GENERATOR_PLANE_H

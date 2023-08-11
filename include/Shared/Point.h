#ifndef SHARED_POINT_H
#define SHARED_POINT_H

#include <cstring>
#include <math.h>
#include <fstream>
#include <list>
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>

class Point {

	private:
        float _x;
		float _y;
		float _z;

	public:
		Point(float, float, float);
        Point(std::vector<float>);
		Point();
		Point(std::string);

		float getX() const;
		float getZ() const;
		float getY() const;
		void setX(float);
        void setY(float);
        void setZ(float);
		void normalize();
		Point sub(Point p) const;
		Point add(Point p) const;
		void cross(Point a, Point b);
        void multiply(Point p, float multiplier, int signal);
        void applyTransfPoint(const float *m);
        std::vector<float> pointAsVector();
};

#endif
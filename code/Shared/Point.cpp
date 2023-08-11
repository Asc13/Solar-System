#include "../../include/Shared/Point.h"

/**
 *
 * Construtor parametrizado de um ponto
 * @param x
 * @param y
 * @param z
 * x y z (coordenadas do ponto)
 */

Point::Point(std::vector<float> point) {
    _x = point[0];
    _y = point[1];
    _z = point[2];
}

Point::Point(float x, float y, float z) {
	_x = x;
	_y = y;
	_z = z;
}

Point::Point() {
    _x = 0;
    _y = 0;
    _z = 0;
}

Point::Point(std::string line) {
    std::stringstream str(line);
    std::string elem;
    std::vector<float> coordinates;
    while(std::getline(str,elem,' ')){
        coordinates.push_back(stof(elem));
    }
    _x = coordinates.at(0);
    _y = coordinates.at(1);
    _z = coordinates.at(2);
}

/**
 *
 * Função que devolve a coordenada x
 * @return x (coordenada)
 */
float Point::getX() const {
    return _x;
}

/**
 *
 * Função que devolve a coordenada y
 * @return y (coordenada)
 */
float Point::getY() const{
    return _y;
}

/**
 *
 * Função que devolve a coordenada z
 * @return z (coordenada)
 */

float Point::getZ() const{
    return _z;
}


void Point::setX(float x)  {
    _x = x;
}


void Point::setY(float y) {
    _y = y;
}

void Point::setZ(float z) {
    _z = z;
}

// Funções de vetores

void Point::normalize() {
    double factor = sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2));
    _x /= (float) factor;
    _y /= (float) factor;
    _z /= (float) factor;
}


Point Point::sub(Point p) const {
    return {_x - p.getX(), _y - p.getY(), _z - p.getZ()};
}


Point Point::add(Point p) const {
    return {_x + p.getX(), _y + p.getY(), _z + p.getZ()};
}


void Point::multiply(Point p, float multiplier, int signal) {

    if(signal == 1) {
        _x += p.getX() * multiplier;
        _y += p.getY() * multiplier;
        _z += p.getZ() * multiplier;
    }
    else if (signal == 0) {
        _x -= p.getX() * multiplier;
        _y -= p.getY() * multiplier;
        _z -= p.getZ() * multiplier;
    }
}


void Point::cross(Point a, Point b) {
    _x = a.getY() * b.getZ() - a.getZ() * b.getY();
    _y = a.getX() * b.getZ() - a.getZ() * b.getX();
    _z = a.getX() * b.getY() - a.getY() * b.getX();
}


void Point::applyTransfPoint(const float* m) {
    float x = _x, y = _y, z = _z, w = 1.0f;

    _x = x * m[0] + y * m[4] + z * m[8] + w * m[12];
    _y = x * m[1] + y * m[5] + z * m[9] + w * m[13];
    _z = x * m[2] + y * m[6] + z * m[10] + w * m[14];
}

std::vector<float> Point::pointAsVector() {
    return std::vector<float>({_x,_y,_z});

}


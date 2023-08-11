#include "../../include/Engine/CameraFPS.h"
const float yawI = -90.0f;
const float pitchI =  0.0f;
const float senseI =  0.1f;

CameraFPS::CameraFPS(Point position) {
    _position = Point(position);
    _right = Point(0.0f, 0.0f, 0.0f);
    _up = Point(0.0f, 1.0f, 0.0f);
    _front = Point(0.0f, 0.0f, -1.0f);

    _yaw = yawI;
    _pitch = pitchI;

    _speed = 50;
    _sense = senseI;

    _lastX = 0;
    _lastY = 0;
    _firstmove = true;

    update();
}

CameraFPS::CameraFPS(float px, float py, float pz){
    _position = Point(px,py,pz);
    _right = Point(0.0f, 0.0f, 0.0f);
    _up = Point(0.0f, 1.0f, 0.0f);
    _front = Point(0.0f, 0.0f, -1.0f);
    _yaw = yawI;
    _pitch = pitchI;

    _speed = 50;
    _sense = senseI;

    _lastX = 0;
    _lastY = 0;
    _firstmove = true;

    update();
}

void CameraFPS::setP(float x, float y, float z){
    _position = Point(x,y,z);
}

float CameraFPS::getPx() {
    return _position.getX();
}

float CameraFPS::getPy() {
    return _position.getY();
}

float CameraFPS::getPz() {
    return _position.getZ();
}

Point CameraFPS::getP() {
    return _position;
}


float CameraFPS::getDx() {
    return _position.getX() + _front.getX();
}

float CameraFPS::getDy() {
    return _position.getY() + _front.getY();
}

float CameraFPS::getDz() {
    return _position.getZ() + _front.getZ();
}

float CameraFPS::getFrontX() {
    return _front.getX();
}

float CameraFPS::getFrontY() {
    return _front.getY();
}

float CameraFPS::getFrontZ() {
    return _front.getZ();
}

Point CameraFPS::getD() {
    return _front;
}



float CameraFPS::getUx() {
    return _up.getX();
}

float CameraFPS::getUy() {
    return _up.getY();
}

float CameraFPS::getUz() {
    return _up.getZ();
}

Point CameraFPS::getU() {
    return _up;
}

Point CameraFPS::getR() {
    return _right;
}


void CameraFPS::update() {
    _front = Point(cos(radians(_yaw)) * cos(radians(_pitch)),
                   -sin(radians(_pitch)),
                   sin(radians(_yaw)) * cos(radians(_pitch)));
    _front.normalize();

    _right.cross(_front, _up);
    _right.normalize();
}

void CameraFPS::keyboardEvent(const char *moveType) {

    if(strcmp(moveType, "FRONT") == 0) _position.multiply(_front, _speed, 1);
    else if(strcmp(moveType, "BACK") == 0) _position.multiply(_front, _speed, 0);
    else if(strcmp(moveType, "LEFT") == 0) _position.multiply(_right, _speed, 0);
    else if(strcmp(moveType, "RIGHT") == 0) _position.multiply(_right, _speed, 1);
}


void CameraFPS::mouseEvent(float x, float y) {

    if(_firstmove){
        _lastX = x;
        _lastY = y;
        _firstmove = false;
    }


    float xdiff = x - _lastX;
    float ydiff = y - _lastY;
    _lastX = x;
    _lastY = y;

    //xdiff *= _sense;
    //ydiff *= _sense;

    _yaw += xdiff;
    _pitch += ydiff;

    if(_pitch > 89.0f) _pitch = 89.0f;
    if(_pitch < -89.0f) _pitch = -89.0f;

    update();
}

void CameraFPS::speedChanger(int flag) {
    if(flag) _speed *= 2;
    else _speed /= 2;
}

float CameraFPS::radians(float degrees) {
    return (float) (M_PI * degrees) / 180;
}

void CameraFPS::setNewPosition(float px, float py, float pz, float fx, float fy, float fz) {
    _position = Point(px, py, pz);
    _front = Point(fx, fy, fz);
    _front.normalize();

    _pitch = (float) (asin(-_front.getY()) * 180 / M_PI);
    _yaw = (float) (asin(_front.getZ() / cos(radians(_pitch))) * 180 / M_PI);

}

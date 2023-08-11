#include "../../include/Engine/CameraExplorer.h"
#include <cstring>
#include <math.h>

CameraExplorer::CameraExplorer(float px, float py, float pz){
    _position = Point(px,py,pz);
    _alpha = M_PI/2;
    _newOrigin = Point(0.0f,0.0f,0.0f);
    _speed = 0;
    _beta = M_PI/2;
    _radius = 2000.0f;
}

CameraExplorer::CameraExplorer(){
    _position = Point(10.0f,10.0f,10.0f);
    _newOrigin = Point(0.0f,0.0f,0.0f);
    _alpha = M_PI/2;
    _speed = 0;
    _beta = M_PI/2;
    _radius = 2000.0f;
}

void CameraExplorer::keyboardEvent(const char* s) {
    if(!strcmp(s,"FRONT")){
        _beta += M_PI / 90 + _speed;
        if(_beta > 1.5f) _beta = 1.5f;
    }
    else if(!strcmp(s,"BACK")){
        _beta -= M_PI / 90 + _speed;
        if(_beta < - 1.5f) _beta = - 1.5f;
    }
    else if(!strcmp(s,"LEFT")) {
        _alpha -= M_PI / 90 + _speed;
    }
    else if(!strcmp(s,"RIGHT")){
        _alpha += M_PI / 90 + _speed;
    }
    update();
}

void CameraExplorer::setNewPos(float x, float y, float z, float frX, float frY, float frZ){
    _position = Point(x,y,z);
    _newOrigin = Point(x+frX*2000,y+frY*2000,z+frZ*2000);
    _speed = 0;

    _beta =  asin((_position.getY() - _newOrigin.getY())/_radius);
    _alpha = asin((_position.getX() - _newOrigin.getX())/(_radius * cos(_beta)));
}

void CameraExplorer::update(){
    _position = Point(_newOrigin.getX() + _radius * sin(_alpha) * cos(_beta),
                      (_newOrigin.getY() + _radius * sin(_beta)),
                      _newOrigin.getZ() + _radius * cos(_alpha) * cos(_beta));
}


float CameraExplorer::getPx() {
    return _position.getX();
}

float CameraExplorer::getPy() {
    return _position.getY();
}

float CameraExplorer::getPz() {
    return _position.getZ();
}

Point CameraExplorer::getP() {
    return _position;
}


float CameraExplorer::getDx() {
    return _newOrigin.getX();
}

float CameraExplorer::getDy() {
    return _newOrigin.getY();
}

float CameraExplorer::getDz() {
    return _newOrigin.getZ();
}

Point CameraExplorer::getD() {
    return _newOrigin;
}


float CameraExplorer::getUx() {
    return 0.0f;
}

float CameraExplorer::getUy() {
    return 1.0f;
}

float CameraExplorer::getUz() {
    return 0.0f;
}

Point CameraExplorer::getU() {
    return {0.0f, 1.0f, 0.0f};
}

Point CameraExplorer::getR() {
    Point right;
    right.cross(_newOrigin, getU());
    return right;
}

void CameraExplorer::speedChanger(int flag) {
    if(flag && _speed < 10) _speed += 1;
    else {
        if(_speed > 0) _speed -= 1;
    }
}

void CameraExplorer::setRadius(float r){
    _radius = r;
}

void CameraExplorer::setRadiusToOrigin(){
    _radius = sqrt(pow(sqrt(pow(_position.getX(),2) + pow(_position.getZ(),2)),2) + pow(_position.getY(),2));
}
void CameraExplorer::increaseRadius(){
    _radius += 10;
}
void CameraExplorer::decreaseRadius(){
    _radius -=10;
}
void CameraExplorer::resetRadius(){
    _radius = 20.0f;
}

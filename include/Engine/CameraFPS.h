
#ifndef CG_TP_CAMERAFPS_H
#define CG_TP_CAMERAFPS_H
#include "../Shared/Point.h"

class CameraFPS {
    private:

        Point _position;
        Point _up;
        Point _front;
        Point _right;

        float _yaw;
        float _pitch;

        float _speed;
        float _sense;

        float _lastX;
        float _lastY;
        bool _firstmove;

    public:

        CameraFPS(Point position);
        CameraFPS(float,float,float);
        void setP(float,float,float);
        float getPx();
        float getPy();
        float getPz();
        Point getP();

        float getFrontX();
        float getFrontY();
        float getFrontZ();

        float getDx();
        float getDy();
        float getDz();
        Point getD();

        float getUx();
        float getUy();
        float getUz();
        Point getU();

        Point getR();

        void update();
        static float radians(float degrees);
        void keyboardEvent(const char *moveType);
        void mouseEvent(float x, float y);
        void speedChanger(int flag);
        void setNewPosition(float, float, float, float, float, float);
};



#endif //CG_TP_CAMERAFPS_H

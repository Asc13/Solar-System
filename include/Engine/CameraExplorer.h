#ifndef CG_TP_CAMERAEXPLORER_H
#define CG_TP_CAMERAEXPLORER_H
#include <string>
#include "../Shared/Point.h"

class CameraExplorer{
    private:
        float _alpha, _beta, _radius, _speed;
        Point _position, _newOrigin;

    public:
        CameraExplorer(float, float, float);
        CameraExplorer();
        float getPx();
        float getPy();
        float getPz();
        Point getP();

        float getDx();
        float getDy();
        float getDz();
        Point getD();

        static float getUx();
        static float getUy();
        static float getUz();
        static Point getU();

        Point getR();

        void update();
        void keyboardEvent(const char *moveType);
        void speedChanger(int flag);
        void increaseRadius();
        void decreaseRadius();
        void resetRadius();

        void setNewPos(float, float, float, float, float, float);
        void setRadiusToOrigin();
        void setRadius(float);

};


#endif //CG_TP_CAMERAEXPLORER_H

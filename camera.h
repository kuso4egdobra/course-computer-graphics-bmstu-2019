#ifndef CAMERA_H
#define CAMERA_H

class Angle;

class Camera
{
    Angle *angle = nullptr;
    double moveX, moveY, moveZ;
    double kxy;

public:
    Camera();
    Camera(double moveX, double moveY, double moveZ, double angleX, double angleY, double angleZ);
    double getMoveX();
    double getMoveY();
    double getMoveZ();
    double getAngleX();
    double getAngleY();
    double getAngleZ();
    double getKxy();
    void addAngleX();
    void decAngleX();
    void addAngleY();
    void decAngleY();
    void addKxy();
    void decKxy();
};

#endif // CAMERA_H

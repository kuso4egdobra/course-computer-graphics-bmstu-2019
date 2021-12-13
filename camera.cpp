#include "camera.h"
#include "angle.h"

Camera::Camera()
{

}

Camera::Camera(double moveX, double moveY, double moveZ, double angleX, double angleY, double angleZ)
{
    this->moveX = moveX;
    this->moveY = moveY;
    this->moveZ = moveZ;

    kxy = 1;

    angle = new Angle(angleX, angleY, angleZ);
}

double Camera::getMoveX()
{
    return moveX;
}

double Camera::getMoveY()
{
    return moveY;
}

double Camera::getMoveZ()
{
    return moveZ;
}

double Camera::getAngleX()
{
    return angle->getAngleX();
}

double Camera::getAngleY()
{
    return angle->getAngleY();
}

double Camera::getAngleZ()
{
    return angle->getAngleZ();
}

double Camera::getKxy()
{
    return kxy;
}

void Camera::addAngleX()
{
    angle->addAngleX(10);
}

void Camera::decAngleX()
{
    angle->addAngleX(-10);
}

void Camera::addAngleY()
{
    angle->addAngleY(10);
}

void Camera::decAngleY()
{
    angle->addAngleY(-10);
}

void Camera::addKxy()
{
    kxy += 0.1;
}

void Camera::decKxy()
{
    kxy -= 0.1;
}



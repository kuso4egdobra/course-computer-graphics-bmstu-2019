#include "angle.h"
#include <math.h>

#include "defines.h"

Angle::Angle(double x, double y, double z)
{
    angleX = x;
    angleY = y;
    angleZ = z;

    angleX = modDegree(angleX);
    angleY = modDegree(angleY);
    angleZ = modDegree(angleZ);
}

double Angle::getAngleX()
{
    return angleX;
}

double Angle::getAngleY()
{
    return angleY;
}

double Angle::getAngleZ()
{
    return angleZ;
}

void Angle::addAngleX(double dx)
{
    angleX += dx;
    angleX = modDegree(angleX);
}

void Angle::addAngleY(double dy)
{
    angleY += dy;
    angleY = modDegree(angleY);
}

void Angle::addAngleZ(double dz)
{
    angleZ += dz;
    angleZ = modDegree(angleZ);
}

void Angle::addAngles(double dx, double dy, double dz)
{
    angleX += dx;
    angleY += dy;
    angleZ += dz;

    angleX = modDegree(angleX);
    angleY = modDegree(angleY);
    angleZ = modDegree(angleZ);
}

void Angle::setAngleX(double x)
{
    angleX = x;
    angleX = modDegree(angleX);
}

void Angle::setAngleY(double y)
{
    angleY = y;
    angleY = modDegree(angleY);
}

void Angle::setAngleZ(double z)
{
    angleZ = z;
    angleZ = modDegree(angleZ);
}

void Angle::setAll(double x, double y, double z)
{
    angleX = x;
    angleY = y;
    angleZ = z;

    angleX = modDegree(angleX);
    angleY = modDegree(angleY);
    angleZ = modDegree(angleZ);
}

void Angle::setAnglesZero()
{
    angleX = 0;
    angleY = 0;
    angleZ = 0;
}

bool Angle::isZero()
{
    if (fabs(angleX) > EPS || fabs(angleY) > EPS || fabs(angleZ) > EPS)
        return false;
    return true;
}

double Angle::modDegree(double angle)
{
    angle = fmod(angle, 360);
    if (angle < 0)
        angle += 360;

    return angle;
}



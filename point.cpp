#include "point.h"

#include "defines.h"
#include <cmath>

Point::Point()
{

}

Point::Point(const Point &pt, double xCentr, double yCentr, double zCentr)
{
    this->x = pt.x + xCentr;
    this->y = pt.y + yCentr;
    this->z = pt.z + zCentr;
}

Point::Point(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::Point(const Point &pt)
{
    x = pt.x;
    y = pt.y;
    z = pt.z;
}

Point::Point(const Point *pt)
{
    x = pt->x;
    y = pt->y;
    z = pt->z;
}

double Point::getX()
{
    return x;
}

double Point::getY()
{
    return y;
}

double Point::getZ()
{
    return z;
}

void Point::addX(double dx)
{
    x += dx;
}

void Point::addY(double dy)
{
    y += dy;
}

void Point::addZ(double dz)
{
    z += dz;
}

void Point::add(double dx, double dy, double dz)
{
    x += dx;
    y += dy;
    z += dz;
}

void Point::setX(double x)
{
    this->x = x;
}

void Point::setY(double y)
{
    this->y = y;
}

void Point::setZ(double z)
{
    this->z = z;
}

void Point::setAll(Point *pt)
{
    x = pt->x;
    y = pt->y;
    z = pt->z;
}

void Point::setAll(double newX, double newY, double newZ)
{
    x = newX;
    y = newY;
    z = newZ;
}

double Point::sum()
{
    return x + y + z;
}

double Point::sumSquare()
{
    return x*x + y*y + z*z;
}

double Point::skalMul(Point *pt)
{
    double sumVec = x * pt->x + y * pt->y + z * pt->z;
    double skalVec = sumVec/(sqrt(pt->sumSquare()) * sqrt(sumSquare()));

    return skalVec;
}

double d_cos(double angle)
{
    return cos(angle * 0.017453);
}

double d_sin(double angle)
{
    return sin(angle * 0.017453);
}

void Point::turn(double x, double y, double z, double angleX, double angleY, double angleZ)
{
    if (fabs(angleX) > EPS)
        turnX(y, z, angleX);
    if (fabs(angleY) > EPS)
        turnY(x, z, angleY);
    if (fabs(angleZ) > EPS)
        turnZ(x, y, angleZ);
}

void Point::turnX(double yCtr, double zCtr, double angleX)
{
    double dCosX = d_cos(angleX);
    double dSinX = d_sin(angleX);
    double resY = y - yCtr;
    double resZ = z - zCtr;

    double newY = yCtr + resY * dCosX + resZ * dSinX;
    double newZ = zCtr - resY * dSinX + resZ * dCosX;

    y = newY;
    z = newZ;
}

void Point::turnY(double xCtr, double zCtr, double angleY)
{
    double dCosY = d_cos(angleY);
    double dSinY = d_sin(angleY);
    double resX = x - xCtr;
    double resZ = z - zCtr;

    double newX = xCtr + resX * dCosY + resZ * dSinY;
    double newZ = zCtr - resX * dSinY + resZ * dCosY;

    x = newX;
    z = newZ;
}

void Point::turnZ(double xCtr, double yCtr, double angleZ)
{
    double dCosZ = d_cos(angleZ);
    double dSinZ = d_sin(angleZ);
    double resX = x - xCtr;
    double resY = y - yCtr;

    double newX = xCtr + resX * dCosZ - resY * dSinZ;
    double newY = yCtr - resX * dSinZ + resY * dCosZ;

    x = newX;
    y = newY;
}

//Point Point::operator =(Point &point)
//{
//    x = point.x;
//    y = point.y;
//    z = point.z;

//    return *this;
//}

bool Point::operator <(Point &point)
{
    if (y > point.y)
        return true;
    else if (x < point.x)
        return true;

    return false;

}

Point Point::operator -(const Point &pt)
{
    return Point(x - pt.x, y - pt.y, y - pt.y);
}

Point Point::operator +(const Point &pt)
{
    return Point(x + pt.x, y + pt.y, y + pt.y);
}

Point Point::operator *(double f)
{
    return Point(x * f, y * f, z * f);
}

Point Point::operator /(double f)
{
    return Point(x/f, y/f, z/f);
}

void Point::swap(Point &pt)
{
       Point temp = pt;
       pt = *this;
       *this = temp;
}

void Point::div(double f)
{
    x /= f;
    y /= f;
    z /= f;
}

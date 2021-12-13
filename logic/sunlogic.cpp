#include "sunlogic.h"

#include "infoobject.h"
#include <cmath>
#include <QDebug>

SunLogic::SunLogic(double x, double y, double z, double dAngle, double radius)
{
    curAngle = 0;
    dFi = dAngle;
    xc = x;
    yc = y;
    this->z = z;
    zc = z;
    r = radius;
}

void SunLogic::active()
{
    if (curAngle > 360 || curAngle < -360)
        curAngle = 0;
    x = round(r * cos(double(curAngle) * M_PI / 180)) + xc;
    y = round(r * sin(double(curAngle) * M_PI / 180)) + yc;
}

QVector<infoObject> SunLogic::getInfoObject()
{
    QVector<infoObject> listInfoObject;
    infoObject object = infoObject(id, typeObject::SUN, x, y, z, width, length, height);
    listInfoObject.push_back(object);

    return listInfoObject;
}

double SunLogic::getWidth()
{
    return 0;
}

void SunLogic::setCurAngle(double angle)
{
    curAngle = angle;
    active();
}

#ifndef SUNLOGIC_H
#define SUNLOGIC_H

#include "worldobject.h"

class SunLogic : public WorldObject
{
    double curAngle;
    double dFi;
    double r;
    double xc, yc, zc;
public:
    SunLogic(double x, double y, double z, double dAngle, double radius);
    void active() override;
    QVector<infoObject> getInfoObject() override;
    double getWidth() override;
    void setCurAngle(double angle);
};

#endif // SUNLOGIC_H

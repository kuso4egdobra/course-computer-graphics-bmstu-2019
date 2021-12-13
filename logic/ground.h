#ifndef GROUND_H
#define GROUND_H

#include "worldobject.h"

class Ground : public WorldObject
{
public:
    Ground(double x, double y, double z, double length, double width, double height);
    void active() override;
    double getWidth() override;
    QVector<infoObject> getInfoObject() override;
};

#endif // GROUND_H

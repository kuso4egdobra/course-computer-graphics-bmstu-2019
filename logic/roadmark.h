#ifndef ROADMARK_H
#define ROADMARK_H

#include "worldobject.h"

class RoadMark : public WorldObject
{
public:
    RoadMark();
    RoadMark(double x, double y, double z, double length, double width, double height);
    QVector<infoObject> getInfoObject() override;
    double getWidth() override;
    void active() override;
};

#endif // ROADMARK_H

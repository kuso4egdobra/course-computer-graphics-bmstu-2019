#ifndef ROAD_H
#define ROAD_H

#include <QVector>
#include "worldobject.h"

class RoadLine;
struct infoObject;

class Road: public WorldObject
{
    QVector<RoadLine *> roadLines;

public:
    Road();
    Road(double x, double z, double length);
    void addRoadLine(RoadLine *roadLine);
    void deleteRoadLine(RoadLine *roadLine);
    void active() override;
    RoadLine* findSibling(RoadLine* roadLine);
    double getWidth() override;
    double getWidthRight();
    double getWidthLeft();
    QVector<infoObject> getInfoObject() override;
    QVector<RoadLine *> getRoadLines();
    QVector<infoObject> getDeletedObj() override;
};

#endif // ROAD_H

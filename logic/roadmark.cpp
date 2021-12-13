#include "roadmark.h"
#include "infoobject.h"

RoadMark::RoadMark()
{

}

RoadMark::RoadMark(double x, double y, double z, double length, double width, double height)
    : WorldObject (x, y, z, length, width, height)
{

}

QVector<infoObject> RoadMark::getInfoObject()
{
    infoObject object = infoObject(id, typeObject::ROADMARK, x, y, z, width, length, height);
    QVector<infoObject> list;
    list.push_back(object);

    return list;
}

double RoadMark::getWidth()
{
    return width;
}

void RoadMark::active()
{

}

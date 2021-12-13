#include "ground.h"

#include "infoobject.h"

Ground::Ground(double x, double y, double z, double length, double width, double height)
    : WorldObject (x, y, z, length, width, height)
{

}

void Ground::active()
{

}

double Ground::getWidth()
{
    return width;
}

QVector<infoObject> Ground::getInfoObject()
{
    infoObject object = infoObject(id, typeObject::GROUND, x, y, z, width, length, height);
    QVector<infoObject> list;
    list.push_back(object);

    return list;
}

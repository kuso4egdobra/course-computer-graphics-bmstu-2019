#include "worldobject.h"

#include "infoobject.h"

int WorldObject::autoId = 0;

WorldObject::WorldObject()
{
    id = ++autoId;

    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->length = 0;
    this->width = 0;
    this->height = 0;
}

WorldObject::WorldObject(double x, double y, double z, double length, double width, double height)
{
    id = ++autoId;

    this->x = x;
    this->y = y;
    this->z = z;
    this->length = length;
    this->width = width;
    this->height = height;
}

WorldObject::~WorldObject()
{

}

bool WorldObject::operator == (WorldObject &object)
{
    if (id == object.id)
        return true;

    return false;
}

double WorldObject::getX()
{
    return x;
}

double WorldObject::getY()
{
    return y;
}

double WorldObject::getZ()
{
    return z;
}

double WorldObject::getLength()
{
    return length;
}

double WorldObject::getHeight()
{
    return height;
}

void WorldObject::setX(double newX)
{
    x = newX;
}

void WorldObject::setY(double newY)
{
    y = newY;
}

void WorldObject::setZ(double newZ)
{
    z = newZ;
}

QVector<infoObject> WorldObject::getDeletedObj()
{
    return QVector<infoObject>();
}

void WorldObject::setLength(double length)
{
    this->length = length;
}

int WorldObject::getId()
{
    return id;
}





#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QVector>

struct infoObject;

class WorldObject
{
public:
    WorldObject();
    WorldObject(double x, double y, double z, double length, double width, double height);
    virtual ~WorldObject();
    bool operator == (WorldObject &object);
    virtual void active() = 0;
    double getX();
    double getY();
    double getZ();
    virtual double getLength();
    virtual double getHeight();
    virtual double getWidth() = 0;
    void setX(double newX);
    void setY(double newY);
    void setZ(double newZ);
    virtual QVector<infoObject> getInfoObject() = 0;
    virtual QVector<infoObject> getDeletedObj();
    void setLength(double length);
    int getId();

protected:
    double x, y, z;
    double length, width, height;
    int id;
    static int autoId;
};

#endif // WORLDOBJECT_H

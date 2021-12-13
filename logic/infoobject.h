#ifndef INFOOBJECT_H
#define INFOOBJECT_H

enum class typeObject
{
    ROADLINE, TREE, CAR2LEFT, CAR2RIGHT, SUN, ROADMARK, GROUND
};

struct infoObject
{
    int id;
    typeObject type;
    double x, y, z;
    double width, length, height;

    infoObject()
    {

    }

    infoObject(int id, typeObject type, double x, double y, double z, double width, double length, double height)
    {
        this->id = id;
        this->type = type;
        this->x = x;
        this->y = y;
        this->z = z;
        this->width = width;
        this->length = length;
        this->height = height;
    }
};

#endif // INFOOBJECT_H

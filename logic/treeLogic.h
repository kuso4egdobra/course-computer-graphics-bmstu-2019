#ifndef TREELOGIC_H
#define TREELOGIC_H

#include "worldobject.h"

struct infoObject;

class TreeLogic : public WorldObject
{
public:
    TreeLogic(double x, double y, double z, double length, double width, double height);
    void active() override;
    double getWidth() override;
    QVector<infoObject> getInfoObject() override;
};

#endif // TREELOGIC_H

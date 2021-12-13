#include "treeLogic.h"
#include "infoobject.h"

TreeLogic::TreeLogic(double x, double y, double z, double length, double width, double height):
    WorldObject (x, y, z, length, width, height)
{

}

void TreeLogic::active()
{

}

double TreeLogic::getWidth()
{
    return width;
}

QVector<infoObject> TreeLogic::getInfoObject()
{
    QVector<infoObject> listInfoObject;
    infoObject object(id, typeObject::TREE, x, y, z, width, length, height);
    listInfoObject.push_back(object);

    return listInfoObject;
}

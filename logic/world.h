#ifndef WORLD_H
#define WORLD_H

#include <QVector>

class WorldObject;
struct infoObject;

class World
{
    QVector<WorldObject*> objects;
    double sizeX, sizeY, sizeZ;

public:
    World();
    World(double sizeX, double sizeY, double sizeZ);
    void action();
    void createWorld();
    QVector<infoObject> getListInfoObjects(); // только изменившиеся объекты, парараметр для запроса изм. или все объеты
    QVector<infoObject> getListObjToDelete();

private:
    void addObject(WorldObject *object);
};

#endif // WORLD_H

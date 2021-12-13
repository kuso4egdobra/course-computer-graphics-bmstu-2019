#include "world.h"
#include "worldobject.h"
#include "road.h"
#include "roadline.h"
#include "treeLogic.h"
#include "infoobject.h"
#include "roadmark.h"
#include "defines.h"
#include "ground.h"


World::World()
{

}


World::World(double x,double y,double z)
{
    sizeX = x;
    sizeY = y;
    sizeZ = z;
}

void World::addObject(WorldObject *object)
{
    objects.push_back(object);
}

void World::action()
{
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->active();
    }
}

void World::createWorld()
{
    Ground *ground = new Ground(0, -0.5, 0, 500, 500, 0);
    addObject(ground);

    Road *newRoad = new Road(0, 0, 500);
    addObject(newRoad);

    RoadLine *newLeftRoadLine1 = new RoadLine(50, Direction::LEFT2RIGHT, 0, 0);
    RoadLine *newLeftRoadLine2 = new RoadLine(50, Direction::LEFT2RIGHT, 0, 0);
    RoadLine *newRightRoadLine1 = new RoadLine(50, Direction::RIGHT2LEFT, 0, 0);
//    RoadLine *newRightRoadLine2 = new RoadLine(50, Direction::RIGHT2LEFT, 0, 0);

//    newRoad->addRoadLine(newRightRoadLine2);
    newRoad->addRoadLine(newRightRoadLine1);
    newRoad->addRoadLine(newLeftRoadLine2);
    newRoad->addRoadLine(newLeftRoadLine1);


    double zTreeRight = - newRoad->getWidthRight() + newRoad->getZ() - 20;
    double zTreeLeft = newRoad->getWidthLeft() + newRoad->getZ() + 20;
    for (double i = newRoad->getX() - newRoad->getLength()/2 + 50; i < newRoad->getX() + newRoad->getLength()/2; i += 100)
    {
        addObject(new TreeLogic(i, 20, zTreeRight, 20, 20, 20));
        addObject(new TreeLogic(i, 20, zTreeLeft, 20, 20, 20));
    }

    QVector<RoadLine*> roadlines = newRoad->getRoadLines();
    for (int i = 0; i < roadlines.size() - 1; i++)
    {
        double rLineX = roadlines[i]->getX(),
               rLineY = roadlines[i]->getY(),
               rLineZ = roadlines[i]->getZ(),
               rWid = roadlines[i]->getWidth(),
               rLen = roadlines[i]->getLength();
        if (roadlines[i]->getDirection() != roadlines[i+1]->getDirection())
        {
            addObject(new RoadMark(rLineX, rLineY + 0.01, rLineZ - rWid/2, rLen, WIDTH_ROAD_MARK, 0));
        }
        else
        {
            for (double j = rLineX - rLen/2 + rLen/(NUM_MARKS*2); j < rLineX + rLen/2; j += rLen/NUM_MARKS)
                addObject(new RoadMark(j, rLineY + 0.01, rLineZ - rWid/2, rLen/(NUM_MARKS*2), WIDTH_ROAD_MARK, 0));
        }
    }
}

QVector<infoObject> World::getListInfoObjects()
{
    QVector<infoObject> listInfoObjects;
    for (int i = 0; i < objects.size(); i++)
    {
        QVector<infoObject> listInfoObjectIter = objects[i]->getInfoObject();
        for (int j = 0; j < listInfoObjectIter.size(); j++)
        {
            infoObject temp = listInfoObjectIter[j];
            listInfoObjects.push_back(temp);
        }
    }

    return listInfoObjects;
}

QVector<infoObject> World::getListObjToDelete()
{
    QVector<infoObject> listDelObjects;
    for (int i = 0; i < objects.size(); i++)
    {
        QVector<infoObject> listInfoObjectIter = objects[i]->getDeletedObj();
        for (int j = 0; j < listInfoObjectIter.size(); j++)
        {
            infoObject temp = listInfoObjectIter[j];
            listDelObjects.push_back(temp);
        }
    }

    return listDelObjects;
}

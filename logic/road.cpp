#include "road.h"
#include "roadline.h"
#include "carLogic.h"
#include "infoobject.h"

Road::Road()
{

}

Road::Road(double x, double z, double length):WorldObject(x, 1, z, length, 0, 0)
{

}

void Road::addRoadLine(RoadLine *roadLine)
{
    roadLine->setRoad(this);
    roadLine->setX(getX());
    roadLine->setLength(getLength());

    if (roadLine->getDirection() == Direction::LEFT2RIGHT)
    {
        double z = getZ() - roadLine->getLeftGap() - roadLine->getWidth()/2;
        for (int i = 0; i < roadLines.size(); i++)
            if (roadLines[i]->getDirection() == Direction::LEFT2RIGHT)
                z -= roadLines[i]->getSumGaps() + roadLines[i]->getWidth();
        roadLine->setZ(z);
    }
    else
    {
        double z = getZ() + roadLine->getRightGap() + roadLine->getWidth()/2;
        for (int i = 0; i < roadLines.size(); i++)
            if (roadLines[i]->getDirection() == Direction::RIGHT2LEFT)
                z += roadLines[i]->getSumGaps() + roadLines[i]->getWidth();
        roadLine->setZ(z);
    }

    roadLines.push_back(roadLine);
}

void Road::deleteRoadLine(RoadLine *roadLine)
{
    for (auto it = roadLines.begin(); it != roadLines.end(); it++)
    {
        if (*it == roadLine)
        {
            roadLines.erase(it);
            break;
        }
    }
}

void Road::active()
{
    int randomChoice = rand() % roadLines.size();

    if (roadLines[randomChoice]->startColision() == false && rand() % 10 == 1)
    {
        Car* newCar = new Car();
        newCar->setRoadLine(roadLines[randomChoice]);
        roadLines[randomChoice]->addObject(newCar);
    }

    for (int i = 0; i < roadLines.size(); i++)
        roadLines[i]->active();
}

RoadLine* Road::findSibling(RoadLine* roadLine)
{
    for (int i = 1; i < roadLines.size() - 1; i++)
    {
        if (roadLines[i]->getId() == roadLine->getId())
        {
            if (roadLine->getDirection() == Direction::LEFT2RIGHT)
                return roadLines[i+1];
            else
                return roadLines[i-1];
        }
    }
    return nullptr;
}

double Road::getWidth()
{
    double sumWidth = 0;
    for (int i = 0; i < roadLines.size(); i++)
        sumWidth += roadLines[i]->getWidth() + roadLines[i]->getSumGaps();

    return sumWidth;
}

double Road::getWidthRight()
{
    double sum = 0;
    for (int i = 0; i < roadLines.size(); i++)
        if (roadLines[i]->getDirection() == Direction::LEFT2RIGHT)
            sum += roadLines[i]->getSumGaps() + roadLines[i]->getWidth();

    return sum;
}

double Road::getWidthLeft()
{
    double sum = 0;
    for (int i = 0; i < roadLines.size(); i++)
        if (roadLines[i]->getDirection() == Direction::RIGHT2LEFT)
            sum += roadLines[i]->getSumGaps() + roadLines[i]->getWidth();

    return sum;
}

QVector<infoObject> Road::getInfoObject()
{
    QVector<infoObject> listInfoObjects;
    for (int i = 0; i < roadLines.size(); i++)
    {
        QVector<infoObject> listInfoObjectIter = roadLines[i]->getInfoObject();
        for (int j = 0; j < listInfoObjectIter.size(); j++)
        {
            infoObject temp = listInfoObjectIter[j];
            listInfoObjects.push_back(temp);
        }
    }

    return listInfoObjects;
}

QVector<RoadLine *> Road::getRoadLines()
{
    return roadLines;
}

QVector<infoObject> Road::getDeletedObj()
{
    QVector<infoObject> listInfoObjects;
    for (int i = 0; i < roadLines.size(); i++)
    {
        QVector<infoObject> listInfoObjectIter = roadLines[i]->getDeletedObj();
        for (int j = 0; j < listInfoObjectIter.size(); j++)
        {
            infoObject temp = listInfoObjectIter[j];
            listInfoObjects.push_back(temp);
        }
    }

    return listInfoObjects;
}

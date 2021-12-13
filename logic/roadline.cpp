#include "roadline.h"
#include "road.h"
#include "infoobject.h"
#include "carLogic.h"

RoadLine::RoadLine()
{

}

RoadLine::RoadLine(double widthRoad, Direction direction, double gapRight, double gapLeft)
    :WorldObject(0,0,0,widthRoad, 0, 0)
{
    this->direction = direction;
    this->gapLeft = gapLeft;
    this->gapRight = gapRight;
    this->width = widthRoad;
}

void RoadLine::addObject(Car *object)
{
    objects.push_back(object);
}

void RoadLine::deleteObject(Car *car)
{
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        Car *newObj = *it;
        if (newObj == car)
        {
            objects.erase(it);
            break;
        }
    }
}

bool RoadLine::operator == (RoadLine &roadLine)
{
    if (this->id == roadLine.id)
        return true;

    return false;
}

RoadLine* RoadLine::getRightSibling()
{
    return  this->road->findSibling(this);
}

int RoadLine::getId()
{
    return id;
}

Direction RoadLine::getDirection()
 {
    return direction;
 }

bool RoadLine::colision(double newX, double length, Car *car)
{
    Car* nextObject = this->getNextObject(newX);
    if (nextObject == nullptr || car == nextObject)
        return false;

    double backNextCar = nextObject->getX();
    double topThisCar = newX;

    if (getDirection() == Direction::LEFT2RIGHT)
    {
        backNextCar -= nextObject->getLength();
        topThisCar += length;
        if (topThisCar >= backNextCar)
            return true;
        else
            return false;
    }
    else
    {
        backNextCar += nextObject->getLength()/2;
        topThisCar -= length;
        if (topThisCar <= backNextCar)
            return true;
        else
            return false;
    }
}

bool RoadLine::colisionBack(double newX, double length, Car *car)
{
    Car* prevObject = this->getPrevObject(newX);
    if (prevObject == nullptr || car == prevObject)
        return false;

    double topPrevCar = prevObject->getX();
    double backThisCar = newX;

    if (getDirection() == Direction::LEFT2RIGHT)
    {
        topPrevCar += prevObject->getLength();
        backThisCar -= length;
        if (backThisCar <= topPrevCar)
            return true;
        else
            return false;
    }
    else
    {
        topPrevCar -= prevObject->getLength();
        backThisCar += length;
        if (backThisCar >= topPrevCar)
            return true;
        else
            return false;
    }
}

Car* RoadLine::getNextObject(Car* object)
{
    if(objects.size() <= 1)
    {
        return nullptr;
    }
    Car* nextObject = objects[0];
    for (int i = 1; i < objects.size() - 1; i++)
    {
        if (getDirection() == Direction::LEFT2RIGHT)
        {
            if (objects[i]->getX() > object->getX() && objects[i]->getX() < nextObject->getX())
                nextObject = objects[i];
        }
        else if (getDirection() == Direction::RIGHT2LEFT)
        {
            if (objects[i]->getX() < object->getX() && objects[i]->getX() > nextObject->getX())
                nextObject = objects[i];
        }
    }
    return nextObject;
}

Car* RoadLine::getNextObject(double newX)
{
    if (objects.size() < 1)
    {
        return nullptr;
    }
    Car* nextObject = objects[0];
    for (int i = 1; i < objects.size(); i++)
    {
        if (getDirection() == Direction::LEFT2RIGHT)
        {
            if (objects[i]->getX() > newX && objects[i]->getX() < nextObject->getX())
                nextObject = objects[i];
        }
        else if (getDirection() == Direction::RIGHT2LEFT)
        {
            if (objects[i]->getX() < newX && objects[i]->getX() > nextObject->getX())
                nextObject = objects[i];
        }
    }
    if (getDirection() == Direction::LEFT2RIGHT && nextObject->getX() <= newX)
        nextObject = nullptr;
    if (getDirection() == Direction::RIGHT2LEFT && nextObject->getX() >= newX)
        nextObject = nullptr;

    return nextObject;
}

Car* RoadLine::getPrevObject(double newX)
{
    if (objects.size() < 1)
    {
        return nullptr;
    }
    Car* prevObject = objects[0];
    for (int i = 1; i < objects.size(); i++)
    {
        if (getDirection() == Direction::LEFT2RIGHT)
        {
            if (objects[i]->getX() < newX && objects[i]->getX() > prevObject->getX())
                prevObject = objects[i];
        }
        else if (getDirection() == Direction::RIGHT2LEFT)
        {
            if (objects[i]->getX() > newX && objects[i]->getX() < prevObject->getX())
                prevObject = objects[i];
        }
    }
//    if (getDirection() == Direction::LEFT2RIGHT && prevObject->getX() >= newX)
//        prevObject = nullptr;
//    if (getDirection() == Direction::RIGHT2LEFT && prevObject->getX() <= newX)
//        prevObject = nullptr;

    return prevObject;
}

bool RoadLine::startColision()
{
    bool result = false;
    if (direction == Direction::LEFT2RIGHT)
    {
        Car *firstObject = getNextObject(getX() - getLength()*2);
        if (firstObject)
        {
            if ((firstObject->getX() - firstObject->getLength() - 30) <= (getX() - getLength()/2))
                result = true;
        }
        else
            result = false;
    }
//        result = colision(road->getX() - road->getLength()/2, 80, nullptr);
    else
        result = colision(road->getX() + road->getLength()/2, 80, nullptr);

    return result;
}

void RoadLine::active()
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->getRoadLineToChange() != this)
            objects[i]->active();
    }
}

double RoadLine::getLength()
{
    return this->road->getLength();
}

double RoadLine::getWidth()
{
    return width;
}

double RoadLine::getSumGaps()
{
    return gapLeft + gapRight;
}

void RoadLine::setRoad(Road *road)
{
    this->road = road;
}

double RoadLine::getLeftGap()
{
    return gapRight;
}

double RoadLine::getRightGap()
{
    return gapRight;
}

QVector<infoObject> RoadLine::getInfoObject()
{
    QVector<infoObject> listInfoObject;
    for (int i = 0; i < objects.size(); i++)
    {
        QVector<infoObject> listInfoObjectIter = objects[i]->getInfoObject();
        for (int j = 0; j < listInfoObjectIter.size(); j++)
        {
            infoObject temp = listInfoObjectIter[j];
            listInfoObject.push_back(temp);
        }
    }
    infoObject object(id, typeObject::ROADLINE, x, y, z, width, length, height);
    listInfoObject.push_back(object);

    return listInfoObject;
}

void RoadLine::addDelObject(Car *car)
{
    infoObject object;
    if (direction == Direction::LEFT2RIGHT)
        object = infoObject(car->getId(), typeObject::CAR2RIGHT,
                            car->getX(), car->getY(), car->getZ(),
                            car->getWidth(), car->getLength(), car->getHeight());
    else
        object = infoObject(car->getId(), typeObject::CAR2LEFT,
                            car->getX(), car->getY(), car->getZ(),
                            car->getWidth(), car->getLength(), car->getHeight());
    deletedObjs.append(object);
}

QVector<infoObject> RoadLine::getDeletedObj()
{
    QVector<infoObject> temp = deletedObjs;
    deletedObjs.clear();
    return temp;
}


#include <QDebug>
#include "carLogic.h"
#include "roadline.h"
#include "infoobject.h"

Color Car::masColors[] = {Color::RED, Color::BLUE, Color::GREY, Color::GREEN};
double Car::maxSpeed = 6;

Car::Car()
{
    speed = rand() % 10 + 1;
    color = masColors[rand() % 4];
    length = 80;
    width = rand() % 50 + 10;
    height = rand() % 50 + 10;
    x = 0;
    y = 0;
    z = 0;
}

Car::Car(RoadLine* roadLine):Car()
{
    this->roadLine = roadLine;

    x = roadLine->getX();
    y = 0;
    z = roadLine->getZ();

    if (roadLine->getDirection() == Direction::LEFT2RIGHT)
        x -= roadLine->getLength()/2;
    else
        x += roadLine->getLength()/2;
}

Car::Car(double x, double z, double speed, Color color, double length, double width, double height):
    WorldObject(x, 0, z, length, width, height)
{
    this->speed = speed;
    this->color = color;
}

Car::Car(double speed, Color color, double length, double width, double height):WorldObject (0,0,0,length,width,height)
{
    this->speed = speed;
    this->color = color;
}

void Car::active()
{
    Direction direction = roadLine->getDirection();

    if (direction == Direction::LEFT2RIGHT)
    {
        if (x >= roadLine->getX() + roadLine->getLength()/2)
        {
            roadLine->deleteObject(this);
            if (roadLineToChange)
                roadLineToChange->deleteObject(this);
            roadLine->addDelObject(this);
            delete this;
            return;
        }
    }
    else if (direction == Direction::RIGHT2LEFT)
    {
        if (x <= roadLine->getX() - roadLine->getLength()/2)
        {
            roadLine->deleteObject(this);
            if (roadLineToChange)
                roadLineToChange->deleteObject(this);
            roadLine->addDelObject(this);
            delete this;
            return;
        }
    }

    double newX = x;
    double newZ = z;

    if (direction == Direction::LEFT2RIGHT)
    {
        newX += speed;

       if (changeLine)
       {
           newZ -= speed;
           if (newZ < roadLineToChange->getZ())
           {
               changeLine = false;
               newZ = roadLineToChange->getZ();
               roadLine->deleteObject(this);
               roadLine = roadLineToChange;
               roadLineToChange = nullptr;
           }
       }
    }
    else if (direction == Direction::RIGHT2LEFT)
    {
        newX -= speed;

        if (changeLine)
            newZ += speed;
    }

    RoadLine* rightRoadLine = roadLine->getRightSibling();
    if (rightRoadLine && getX() > (roadLine->getX() - roadLine->getLength()/4))
    {
        bool colision1 = rightRoadLine->colision(newX, length, this);
        bool colision2 = rightRoadLine->colisionBack(newX, length, this);
        if (!colision1 && !colision2)
        {
//            if (rand() % 13 == 0)
            {
                changeLine = true;
                if (roadLineToChange == nullptr)
                {
                    roadLineToChange = rightRoadLine;
                    roadLineToChange->addObject(this);
                }
            }

        }
        else //if (roadLineToChange && colision)
        {
            WorldObject* nextObject = rightRoadLine->getNextObject(newX);
            Car* nextСar = dynamic_cast<Car*>(nextObject);

            if (nextСar && nextСar->speed <= speed)
                speed = nextСar->speed;
            else
                speed += 0.1;

//            return;
        }

    }
    else
    {
//        changeLine = false;
        bool colision = roadLine->colision(newX, length, this);
        if (colision)
        {
            WorldObject* nextObject = roadLine->getNextObject(newX);
            Car* nextСar = dynamic_cast<Car*>(nextObject);

            if (nextСar && nextСar->speed <= speed)
                speed = nextСar->speed;
            else
                speed += 0.1;

//            return;
        }
        else
        {
            if (speed < maxSpeed && !roadLine->getNextObject(newX)
                                 && getX() > roadLine->getX() + roadLine->getLength()/3)
                speed += 0.1;
        }

    }
    this->x = newX;
    this->z = newZ;
}

void Car::setRoadLine(RoadLine *roadLine)
{
    this->roadLine = roadLine;
    width = roadLine->getWidth() + rand() % 30 - 40;

    x = roadLine->getX();
    y = 0;
    z = roadLine->getZ();

    if (roadLine->getDirection() == Direction::LEFT2RIGHT)
        x -= roadLine->getLength()/2;
    else
        x += roadLine->getLength()/2;
}

double Car::getWidth()
{
    return width;
}

QVector<infoObject> Car::getInfoObject()
{
    QVector<infoObject> listInfoObject;
    infoObject object;
    if (roadLine->getDirection() == Direction::LEFT2RIGHT)
        object = infoObject(id, typeObject::CAR2RIGHT, x, y, z, width, length, height);
    else
        object = infoObject(id, typeObject::CAR2LEFT, x, y, z, width, length, height);

    listInfoObject.push_back(object);

    return listInfoObject;
}

RoadLine *Car::getRoadLineToChange()
{
    return roadLineToChange;
}

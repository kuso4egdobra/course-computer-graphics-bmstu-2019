#ifndef ROADLINE_H
#define ROADLINE_H

#include <QVector>
#include "worldobject.h"

class Road;
class Car;
struct infoObject;

enum class Direction
{
    LEFT2RIGHT, RIGHT2LEFT
};

class RoadLine: public WorldObject
{
    double gapRight, gapLeft;
    QVector<Car*> objects;
    Direction direction;
    Road* road = nullptr;
    QVector<infoObject> deletedObjs;

public:
    RoadLine();
    RoadLine(double widthRoad, Direction direction, double gapRight, double gapLeft);
    void addObject(Car *object);
    void deleteObject(Car *object);

    int getId();
    RoadLine* getRightSibling();
    Car* getNextObject(Car* object);
    Car* getNextObject(double newX);
    Car* getPrevObject(double newX);
    Direction getDirection();
    double getLeftGap();
    double getRightGap();
    double getLength() override;
    double getWidth() override;
    double getSumGaps();

    void setRoad(Road *road);
    bool colision(double newX, double length, Car *car);
    bool colisionBack(double newX, double length, Car *car);
    bool startColision();
    void active() override;
    QVector<infoObject> getInfoObject() override;
    QVector<infoObject> getDeletedObj() override;
    void addDelObject(Car *car);

    bool operator == (RoadLine &roadLine);
};

#endif // ROADLINE_H

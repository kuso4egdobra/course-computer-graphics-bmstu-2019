#ifndef CAR_H
#define CAR_H

#include "worldobject.h"

class RoadLine;
struct infoObject;

enum class Color
{
    RED, GREEN, BLUE, GREY
};

class Car: public WorldObject
{
    Color color;
    static Color masColors[4];
    double speed;
    RoadLine *roadLine, *roadLineToChange = nullptr;
    bool changeLine = false;
    static double maxSpeed;
public:
    Car();
    Car(RoadLine* roadLine);
    Car(double x, double z, double speed, Color color, double length, double width, double height);
    Car(double speed, Color color, double length, double width, double height);
    void active() override;
    void setRoadLine(RoadLine *roadLine);
    double getWidth() override;
    QVector<infoObject> getInfoObject() override;
    RoadLine* getRoadLineToChange();
    void deleteCarFromScene();
};

#endif // CAR_H

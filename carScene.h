#ifndef CARSCENE_H
#define CARSCENE_H

#include "figure.h"

class Cylinder;
class Rectangle;

class CarScene : public Figure
{
public:
    CarScene(double x, double y, double z,
        double angleX, double angleY, double angleZ, QColor color = Qt::black);
};

#endif // CARSCENE_H

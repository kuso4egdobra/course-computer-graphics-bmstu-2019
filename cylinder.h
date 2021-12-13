#ifndef CYLINDER_H
#define CYLINDER_H

#include "figure.h"

class Cylinder : public Figure
{
public:
    Cylinder(double xCentre, double yCentre, double zCentre, double radius,
             double height, double turnX, double turnY, double turnZ);
};

#endif // CYLINDER_H

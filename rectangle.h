#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figure.h"

class Rectangle : public Figure
{
public:
    Rectangle(double x, double y, double z, double lenX, double lenY, double lenZ,
              double turnX, double turnY, double turnZ, QColor color = Qt::black);
};

#endif // RECTANGLE_H

#include "size.h"

Size::Size(double lenX, double lenY, double lenZ)
{
    this->lenX = lenX;
    this->lenY = lenY;
    this->lenZ = lenZ;
}

double Size::getLenX()
{
    return lenX;
}

double Size::getLenY()
{
    return lenX;
}

double Size::getLenZ()
{
    return lenX;
}

Size& Size::operator = (Size &size)
{
    lenX = size.lenX;
    lenY = size.lenY;
    lenZ = size.lenZ;

    return *this;
}

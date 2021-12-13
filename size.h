#ifndef SIZE_H
#define SIZE_H

class Size
{
    double lenX;
    double lenY;
    double lenZ;

public:
    Size(double lenX, double lenY, double lenZ);
    double getLenX();
    double getLenY();
    double getLenZ();
    Size& operator = (Size &size);
};

#endif // SIZE_H

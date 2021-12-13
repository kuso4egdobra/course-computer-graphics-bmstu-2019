#ifndef TREE_H
#define TREE_H

#include "figure.h"

class Rectangle;

class Tree : public Figure
{
public:
    Tree(double x, double y, double z,
         double height, double widthWood, double widthLeaves,
         double angleX, double angleY, double angleZ);
};

#endif // TREE_H

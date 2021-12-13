#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QVector>
#include <QColor>

class Point;
class Camera;

#include "figure.h"

class Triangle
{
    Point* pt1;
    Point* pt2;
    Point* pt3;
    QColor color;
    Point* normal = nullptr;
    bool needToDraw;

public:
    Triangle();
    Triangle(Point *point1, Point *point2, Point *point3, QColor color = Qt::black);
    Triangle(Point *point1, Point *point2, Point *point3, Point *normal, QColor color = Qt::black);
    ~Triangle();

    void alignPoints(); // перестановка точек
    double round(double value);
    void barycentric(double &barCoord1, double &barCoord2, double &barCoord3, Point *A, Point *B, Point *C, int x, int y);
    void fillMtx(Point *sunVec, Camera *cam, Angle* angle2Turn, typeFigure type);
    bool isLine();
    Point* getNormal();
    QColor getColor();
};

#endif // TRIANGLE_H

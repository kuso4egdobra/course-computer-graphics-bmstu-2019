#ifndef POINT_H
#define POINT_H

class Point
{
    double x;
    double y;
    double z;

public:
    Point(Point const &pt, double xCentr, double yCentr, double zCentr);
    Point(double x, double y, double z);
    Point(Point const &pt);
    Point(Point const *pt);
    Point();
    double getX();
    double getY();
    double getZ();

    void addX(double dx);
    void addY(double dy);
    void addZ(double dz);
    void add(double dx, double dy, double dz);

    void setX(double x);
    void setY(double x);
    void setZ(double x);
    void setAll(Point *pt);
    void setAll(double newX, double newY, double newZ);
    double sum();
    double sumSquare();
    double skalMul(Point* pt);

    void turn(double x, double y, double z, double angleX, double angleY, double angleZ);


//    Point operator = (Point &point);
//    Point& operator = (Point &point);
    bool operator < (Point &point);
    bool operator == (Point &point);
    Point operator -(const Point &pt);
    Point operator +(const Point &pt);
    Point operator *(double f);
    Point operator /(double f);
    void swap(Point &pt);
    void div(double f);
private:
    void turnX(double yCtr, double zCtr, double angleX);
    void turnY(double xCtr, double zCtr, double angleY);
    void turnZ(double xCtr, double yCtr, double angleZ);
};

#endif // POINT_H

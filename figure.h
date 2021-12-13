#ifndef FIGURE_H
#define FIGURE_H

#include <QVector>
#include <QColor>
#include <algorithm>
#include <QMap>
#include <cmath>
#include <thread>

class Scene;
class Size;
class Point;
class Angle;
class Triangle;

enum class typeFigure
{
    TREE, RECTANGLE, CYLINDER, SUN, CAR, NOT_GROUND, GROUND
};   

class Figure
{
protected:
    QVector<Point*> points;
    QVector<Point*> normals;
    QVector<Point*> primaryPoints;
    QVector<Point*> primaryNormals;
    QVector<Triangle> triangls;
    Angle* angle;
    typeFigure type = typeFigure::NOT_GROUND;

private:
    int id;
    Size* size;
    Point* position;
    Point* primaryPosition;
    Scene* scene;

public:
    Figure();
    Figure(double x, double y, double z,
           double lenX, double lenY, double lenZ,
           double angleX, double angleY, double angleZ);
    virtual void setScene(Scene *scene);
    virtual void drawFigure();
    Size* getSize();
    Point* getPosition();
    virtual void moveX(double x);
    virtual void moveY(double y);
    virtual void moveZ(double z);
    virtual void move(double x, double y, double z);
    virtual void addAngles(double dx, double dy, double dz);
    virtual void turnPoints(double x, double y, double z);
    void turnPoints(double x, double y, double z, double angleX, double angleY, double angleZ);
    int getId();
    void setId(int id);
    void skaleFigure(double kxy);
    void setPosition(double x, double y, double z);
    static Figure* createFigure(int id, typeFigure type, double x, double y, double z,
                                                 double lenX, double lenY, double lenZ,
                                                 double angleX, double angleY, double angleZ, QColor color = Qt::black);
    ~Figure();

private:
    void fillTriangMtx(int start, int step);

};

#endif // FIGURE_H

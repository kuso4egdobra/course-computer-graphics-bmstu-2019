#include "figure.h"
#include "defines.h"

#include "scene.h"
#include "size.h"
#include "angle.h"
#include "triangle.h"
#include "point.h"
#include "rectangle.h"
#include "cylinder.h"
#include "tree.h"
#include "carScene.h"
#include "camera.h"

#include <math.h>
#include <QList>
#include <thread>

Figure::Figure()
{

}

Figure::Figure(double x, double y, double z,
               double lenX, double lenY, double lenZ,
               double angleX, double angleY, double angleZ)
{
    position = new Point(x, y, z);
    primaryPosition = new Point(x, y, z);
    size = new Size(lenX, lenY, lenZ);
    angle = new Angle(angleX, angleY, angleZ);
}

void Figure::setScene(Scene *scene)
{
    this->scene = scene;
}

void Figure::fillTriangMtx(int start, int step)
{
    int size = triangls.size();
    for (int i = start; i < size; i += step)
        triangls[i].fillMtx(scene->getSunVec(), scene->getCurCam(), scene->getAngleBtwSunAndEyes(), type);
}

void Figure::drawFigure()
{
    int numThreads = Scene::numThreads;
    std::thread ths[numThreads];
    for(int i = 0; i < numThreads; i++)
        ths[i] = std::thread(&Figure::fillTriangMtx, this, i, numThreads);

    for (int i = 0; i < numThreads; i++)
        ths[i].join();
}

Size* Figure::getSize()
{
    return size;
}

Point* Figure::getPosition()
{
    return position;
}

void Figure::moveX(double dx)
{
    for (int i = 0; i < points.size(); i++)
        points[i]->addX(dx);
}

void Figure::moveY(double dy)
{
    for (int i = 0; i < points.size(); i++)
        points[i]->addY(dy);
}

void Figure::moveZ(double dz)
{
    for (int i = 0; i < points.size(); i++)
        points[i]->addZ(dz);
}

void Figure::move(double x, double y, double z)
{
    for (int i = 0; i < points.size(); i++)
        points[i]->add(x, y, z);
}

Figure *Figure::createFigure(int id, typeFigure type, double x, double y, double z,
                             double lenX, double lenY, double lenZ,
                             double angleX, double angleY, double angleZ, QColor color)
{
    Figure *figure = nullptr;
    switch(type)
    {
    case typeFigure::RECTANGLE:
        figure = new Rectangle(x, y, z, lenX, lenY, lenZ, angleX, angleY, angleZ, color);
        break;
    case typeFigure::CAR:
        figure = new CarScene(x, y, z, angleX, angleY, angleZ, color);
        break;
    case typeFigure::CYLINDER:
        figure = new Cylinder(x, y, z, lenX/2, lenZ, angleX, angleY, angleZ);
        break;
    case typeFigure::TREE:
        figure = new Tree(x, y, z, lenZ, lenX, lenX, angleX, angleY, angleZ);
        break;
    default:
        figure = new Rectangle(x, y, z, lenX, lenY, lenZ, angleX, angleY, angleZ);
        break;
    }
    figure->id = id;

    return figure;
}

Figure::~Figure()
{
    for (int i = 0; i < points.size(); i++)
        delete points[i];

    delete size;
    delete position;
    delete angle;
}

void Figure::addAngles(double dx, double dy, double dz)
{
    angle->addAngles(dx, dy, dz);
}

void Figure::turnPoints(double x, double y, double z)
{
    position->setAll(primaryPosition);
    for (int i = 0; i < primaryPoints.size(); i++)
        points[i]->setAll(primaryPoints[i]);

    for (int i = 0; i < primaryNormals.size(); i++)
        normals[i]->setAll(primaryNormals[i]);


    double angleX = angle->getAngleX(),
           angleY = angle->getAngleY(),
           angleZ = angle->getAngleZ();

    if (abs(angleX) > EPS || abs(angleY) > EPS || abs(angleZ) > EPS)
    {
        position->turn(x, y, z, angleX, angleY, angleZ);
        for (int i = 0; i < points.size(); i++)
            points[i]->turn(x, y, z, angleX, angleY, angleZ);
        for (int i = 0; i < normals.size(); i++)
            normals[i]->turn(0, 0, 0, angleX, angleY, angleZ);
    }

    angle->setAnglesZero();
}

void Figure::turnPoints(double x, double y, double z, double angleX, double angleY, double angleZ)
{
    angle->addAngles(angleX, angleY, angleZ);

    turnPoints(x, y, z);
}

int Figure::getId()
{
    return id;
}

void Figure::setId(int id)
{
    this->id = id;
}

void Figure::skaleFigure(double kxy)
{
    for (int i = 0; i < points.size(); i++)
    {
        points[i]->setX(points[i]->getX() * kxy);
        points[i]->setY(points[i]->getY() * kxy);
    }
}

void Figure::setPosition(double x, double y, double z)
{
    // перестановка исходных точек (вносят вклад при повороте)
    double subPrCurNewX = x - primaryPosition->getX(),
           subPrCurNewY = y - primaryPosition->getY(),
           subPrCurNewZ = z - primaryPosition->getZ();
    for (auto i = primaryPoints.begin(); i != primaryPoints.end(); i++)
        (*i)->add(subPrCurNewX, subPrCurNewY, subPrCurNewZ);

    primaryPosition->setAll(x, y, z);

    // перестановка текущих точек
    auto cam = scene->getCurCam();
    Point tmpPoint(x, y, z);
    tmpPoint.turn(0, 0, 0, cam->getAngleX(), cam->getAngleY(), cam->getAngleZ());

    double newX_turned = tmpPoint.getX(),
           newY_turned = tmpPoint.getY(),
           newZ_turned = tmpPoint.getZ();
    double subCurNewX = newX_turned - position->getX(),
           subCurNewY = newY_turned - position->getY(),
           subCurNewZ = newZ_turned - position->getZ();

    for (auto i = points.begin(); i != points.end(); i++)
        (*i)->add(subCurNewX, subCurNewY, subCurNewZ);

    position->setAll(newX_turned, newY_turned, newZ_turned);
}

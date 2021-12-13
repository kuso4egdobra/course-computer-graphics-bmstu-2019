#include "triangle.h"
#include "defines.h"

#include "point.h"
#include "zbuffer.h"

#include <cmath>
#include <mutex>

#include<QDebug>
#include "scene.h"
#include "camera.h"
#include "angle.h"

//std::mutex mt;

Triangle::Triangle()
{
    pt1 = nullptr;
    pt2 = nullptr;
    pt3 = nullptr;
}

Triangle::Triangle(Point *point1, Point *point2, Point *point3, QColor color)
{
    pt1 = point1;
    pt2 = point2;
    pt3 = point3;
    normal = new Point(0,0,0);
    this->color = color;
    needToDraw = 1;
}

Triangle::Triangle(Point *point1, Point *point2, Point *point3, Point *normal, QColor color)
{
    pt1 = point1;
    pt2 = point2;
    pt3 = point3;
    this->normal = normal;
    this->color = color;
    needToDraw = 1;

}

Triangle::~Triangle()
{

}

void Triangle::alignPoints()
{

}

// начало функция округления
double Triangle::round(double value)
{
   return floor(value + 0.5);
}


void Triangle::barycentric(double &barCoord1, double &barCoord2, double &barCoord3,
                           Point *A, Point *B, Point *C, int x, int y)
{
    double aX = A->getX();
    double aY = A->getY();
    double cX = C->getX();
    double cY = C->getY();

    double bXminCX = B->getX() - cX;
    double cXminAX = cX - aX;
    double bYmincY = B->getY() - cY;
    double aYminCY = aY - cY;

    double square = aYminCY * bXminCX + bYmincY * cXminAX;
    if (square > 1 || square < -1)
    {
        barCoord1 = (y - cY) * bXminCX + bYmincY * (cX - x);
        barCoord1 /= square;
        barCoord2 = (y - aY) * cXminAX + (-aYminCY) * (aX - x);
        barCoord2 /= square;
        barCoord3 = 1 - barCoord1 - barCoord2;
    }
    else
    {
        barCoord1 = -1;
    }
}

void Triangle::fillMtx(Point *sun, Camera *cam, Angle* angle2Turn, typeFigure type)
{
    double barCoord1 = 0, barCoord2 = 0, barCoord3 = 0;

    double minX, maxX, minY, maxY;
    minX = std::min(std::min(pt1->getX(), pt2->getX()), pt3->getX());
    minY = std::min(std::min(pt1->getY(), pt2->getY()), pt3->getY());
    maxX = std::max(std::max(pt1->getX(), pt2->getX()), pt3->getX());
    maxY = std::max(std::max(pt1->getY(), pt2->getY()), pt3->getY());

    int sizeX = ZBuffer::getNumRows();
    int sizeY = ZBuffer::getNumCols();

    QColor skalColor;
    if (Scene::isShadow)
    {
        if (abs(sun->getX()) < EPS && abs(sun->getY() - 1) < EPS && abs(sun->getZ() - 1) < EPS)
            skalColor = QColor(int(color.red() * 0.15),
                               int(color.green() * 0.15),
                               int(color.blue() * 0.15));
        else{
            double sumVec = sun->getX() * normal->getX() +
                    sun->getY() * normal->getY() +
                    sun->getZ() * normal->getZ();
            double skalVec = sumVec/(sqrt(normal->sumSquare()) * sqrt(sun->sumSquare()));

            if ((abs(normal->getX()) > EPS || abs(normal->getY()) > EPS || abs(normal->getZ()) > 0) &&
                    skalVec >= 0 && skalVec <= 1)
                skalColor = QColor(int(color.red() * skalVec),
                                   int(color.green() * skalVec),
                                   int(color.blue() * skalVec));
            else if (skalVec <= 0)
                skalColor = Qt::black;
            else
                skalColor = color;
        }
    }
    else
        skalColor = color;


    double angle2TurnX = angle2Turn->getAngleX(), angle2TurnY = angle2Turn->getAngleY(),  angle2TurnZ = angle2Turn->getAngleZ();
    double angleX = -cam->getAngleX(), angleY = -cam->getAngleY(), angleZ = -cam->getAngleZ();
    for (int i = int(minX - PIX_GAP); i < maxX + PIX_GAP; i++)
        for (int j = int(minY - PIX_GAP); j < maxY + PIX_GAP; j++)
        {
            int tempI = i + sizeX/2,
                tempJ = j + sizeY/2;
            if (tempI > 0 && tempJ > 0 && tempI < sizeX && tempJ < sizeY)
            {
                barycentric(barCoord1, barCoord2, barCoord3, pt1, pt2, pt3, i, j);
                if (barCoord1 >= 0)
                    if (barCoord2 >= 0 && barCoord3 >= 0)
                    {
                        double curZ = barCoord1 * pt1->getZ() + barCoord2 * pt2->getZ() + barCoord3 * pt3->getZ();
                        ZBuffer::setZ(tempI, tempJ, curZ, skalColor);

                        if (Scene::isShadow)
                        {
                            Point tempPt(i, j, curZ);

                            if (type != typeFigure::GROUND)
                            {
                                tempPt.turn(0, 0, 0, 0, 0, -angleZ);
                                tempPt.turn(0, 0, 0, 0, angleY, 0);
                                tempPt.turn(0, 0, 0, angleX, 0, 0);
                                tempPt.turn(0, 0, 0, angle2TurnX, angle2TurnY, angle2TurnZ);

                                if (tempPt.getX() > -320 && tempPt.getY() > -320 && tempPt.getX() < 320 && tempPt.getY() < 320)
                                {
                                    ZBuffer::setZShadow(int(0.3 + 0.7*(tempPt.getX() + 43.34 + 320)),
                                                        int(0.3 + 0.7*(tempPt.getY() + 43.34 + 320)),
                                                        tempPt.getZ());
                                }
                            }
                        }
                    }
            }
        }
}

//TODO
bool Triangle::isLine()
{
    if ((abs(pt1->getX() - pt2->getX()) < EPS && abs(pt1->getY() - pt2->getY()) < EPS) ||
        (abs(pt1->getX() - pt3->getX()) < EPS && abs(pt1->getY() - pt3->getY()) < EPS) ||
        (abs(pt2->getX() - pt3->getX()) < EPS && abs(pt2->getY() - pt3->getY()) < EPS))
        return true;

    return false;
}

Point *Triangle::getNormal()
{
    return normal;
}

QColor Triangle::getColor()
{
    return color;
}

#include "scene.h"
#include "point.h"
#include "figure.h"
#include "size.h"
#include "point.h"
#include "rectangle.h"

#include "tree.h"
#include "carScene.h"
#include "camera.h"
#include "objfigure.h"
#include "zbuffer.h"
#include "defines.h"
#include "angle.h"

#include <QDebug>
#include <QPointer>
#include <QGraphicsPixmapItem>
#include <cmath>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;

static bool isNewCam = true;
bool Scene::isShadow = true;
int Scene::numThreads = 4;
QVector<Camera> Scene::cameras = QVector<Camera>();
int Scene::curCam = 0;

Scene::Scene(QGraphicsScene *scene, double sizeX, double sizeY, double sizeZ)
{
    this->scene = scene;
    size = new Size(sizeX, sizeY, sizeZ);
    image = new QImage(size->getLenX(), size->getLenY(), QImage::Format_ARGB32);
    ZBuffer::initZBuffer(size->getLenX(), size->getLenY());
    ObjFigure::init();
    sunVec = new Point(0, 0, 0);
    angleBtwSunAndEyes = new Angle(0, 0, 0);
    posSun = new Point(0,0,0);
}

Scene::~Scene()
{

}

void Scene::addFigure(Figure *newFigure)
{
    if (newFigure)
    {
        if (abs(cameras[curCam].getAngleX()) > EPS || abs(cameras[curCam].getAngleY()) > EPS || abs(cameras[curCam].getAngleZ()) > EPS)
            newFigure->turnPoints(0, 0, 0, cameras[curCam].getAngleX(), cameras[curCam].getAngleY(), cameras[curCam].getAngleZ());

        newFigure->setScene(this);
        figures.push_back(newFigure);
    }
}


void Scene::clearScene()
{
    image->fill(QColor(0,0,0,0));

    auto point = scene->items();
    for (int i = 0; i < point.size(); i++)
    {
        scene->removeItem(point[i]);
        delete point[i];
    }

    scene->clear();
}


void Scene::updateScene()
{
    drawingFigures();
}

void Scene::turnAllFigures(double x, double y, double z, double angleX, double angleY, double angleZ)
{
        for (int i = 0; i < figures.size(); i++)
        {
            figures[i]->addAngles(angleX, angleY, angleZ);
            figures[i]->turnPoints(x, y, z);
        }
}

void Scene::addLine(Point *point1, Point *point2, QColor color)
{

}

void Scene::createScene()
{

}


void Scene::drawFigure(int start, int step)
{
    int size = figures.size();
    for (int i = start; i < size; i += step)
        figures[i]->drawFigure();
}

void Scene::skaleFigures()
{
    double kxy = cameras[curCam].getKxy();
    for (int i = 0; i < figures.size(); i++)
    {
        figures[i]->skaleFigure(kxy);
    }
}

void Scene::drawingFigures()
{
    QColor orange(255, 140, 0), black = Qt::black;
    double nOrange, nBlack;
    getColorAndN(nOrange, nBlack);

    if (isNewCam)
    {
        turnAllFigures(0, 0, 0, cameras[curCam].getAngleX(), cameras[curCam].getAngleY(), cameras[curCam].getAngleZ());
        skaleFigures();
        isNewCam = false;
    }

    ZBuffer::setDefaultValue();

    for (int i = 0; i < figures.size(); i++)
        figures[i]->drawFigure();

    double** zBuf = ZBuffer::getZBuffer();
    QColor** zBufColor = ZBuffer::getZBufferColor();
    double** zBufShadow = ZBuffer::getZBufferShadow();
    auto cam = getCurCam();
    double angleX = -cam->getAngleX(),
           angleY = -cam->getAngleY(),
           angleZ = -cam->getAngleZ();

    auto angle2Turn = getAngleBtwSunAndEyes();
    double angle2TurnX = angle2Turn->getAngleX(), angle2TurnY = angle2Turn->getAngleY(),  angle2TurnZ = angle2Turn->getAngleZ();

    bool shadowMap[int(size->getLenX())][int(size->getLenY())];
    QColor colorMap[int(size->getLenX())][int(size->getLenY())];

    for (int i = 0; i < size->getLenX(); i++)
        for (int j = 0; j < size->getLenY(); j++)
            shadowMap[i][j] = false;


    for (int i = 0; i < size->getLenX(); i++)
        for (int j = 0; j < size->getLenY(); j++)
        {
            if (isShadow)
            {
                Point tempPt(i - 320, j - 320, zBuf[i][j]);
                tempPt.turn(0, 0, 0, 0, 0, -angleZ);
                tempPt.turn(0, 0, 0, 0, angleY, 0);
                tempPt.turn(0, 0, 0, angleX, 0, 0);
                if (tempPt.getY() >= -1)
                {
                    double eps = 5;

                    tempPt.turn(0, 0, 0, angle2TurnX, angle2TurnY, angle2TurnZ);

                    if (tempPt.getX() > -320 && tempPt.getY() > -320 && tempPt.getX() < 319 && tempPt.getY() < 319)
                    {
                        if (tempPt.getZ() + eps < zBufShadow[int(0.3 + 0.7*(tempPt.getX() + 43.34 + 320))][int(0.3 + 0.7*(tempPt.getY() + 43.34 + 320))] && nBlack == INT_MAX)
                        {
                            shadowMap[i][j] = true;
                        }
                    }
                }
                colorMap[i][j] = zBufColor[i][j];
            }
            else
                colorMap[i][j] = zBufColor[i][j];
        }

//    добавление теней
    if (isShadow)
    {
        for (int k = 0; k < 3; k++)
            for (int i = 3; i < size->getLenX() - 3; i++)
                for (int j = 3; j < size->getLenY() - 3; j++)
                {
                    if ((shadowMap[i][j - 1] && shadowMap[i][j + 1]) ||
                            (shadowMap[i - 1][j] && shadowMap[i + 1][j]) ||
                            (shadowMap[i - 1][j - 1] && shadowMap[i + 1][j + 1]) ||
                            (shadowMap[i + 1][j - 1] && shadowMap[i - 1][j + 1]) ||
                            (shadowMap[i + 2][j - 2] && shadowMap[i - 2][j + 2]) ||
                            (shadowMap[i][j - 2] && shadowMap[i][j + 2]) ||
                            (shadowMap[i - 2][j] && shadowMap[i + 2][j]) ||
                            (shadowMap[i - 2][j - 2] && shadowMap[i + 2][j + 2]) ||
                            (shadowMap[i + 3][j - 3] && shadowMap[i - 3][j + 3]) ||
                            (shadowMap[i][j - 3] && shadowMap[i][j + 3]) ||
                            (shadowMap[i - 3][j] && shadowMap[i + 3][j]) ||
                            (shadowMap[i - 3][j - 3] && shadowMap[i + 3][j + 3]))
                    {
                        shadowMap[i][j] = true;
                    }
                }
    }

    for (int i = 0; i < size->getLenX(); i++)
        for (int j = 0; j < size->getLenY(); j++)
        {
            if (shadowMap[i][j] && colorMap[i][j] != DFT_COLOR)
                colorMap[i][j] = QColor(int(colorMap[i][j].red() * 0.3),
                                        int(colorMap[i][j].green() * 0.3),
                                        int(colorMap[i][j].blue() * 0.3));


            int red = colorMap[i][j].red(),
                green = colorMap[i][j].green(),
                blue = colorMap[i][j].blue();

            if (nOrange < INT_MAX)
            {
                red = red + (orange.red() - red)/nOrange;
                green = green + (orange.green() - green)/nOrange;
                blue = blue + (orange.blue() - blue)/nOrange;
            }

            if (nBlack < INT_MAX)
            {
                red = red + (black.red() - red)/nBlack;
                green = green + (black.green() - green)/nBlack;
                blue = blue + (black.blue() - blue)/nBlack;
            }
            colorMap[i][j] = QColor(red, green, blue);
        }

    for (int i = 0; i < size->getLenX(); i++)
        for (int j = 0; j < size->getLenY(); j++)
            image->setPixelColor(i, j, colorMap[i][j]);//}

    scene->addPixmap(QPixmap::fromImage(*image));
}

void Scene::getColorAndN(double &nOrange, double &nBlack)
{
    QColor globalColor;
    Point vecXY(posSun->getX(), posSun->getY(), 0);
    Point vecX(posSun->getX() + 0.01, 0, 0);
    double angleX = acos(vecXY.skalMul(&vecX)) * 180 / M_PI;
    angleX = isnan(angleX) ? 0: angleX;

    if (posSun->getY() < 0)
        angleX = -angleX;

    angleX = -angleX;

    if (abs(angleX) < 45 && posSun->getY() >= 0)
    {
        // orange
        nOrange = 10*abs(angleX)/45 + 6;
        nBlack = INT_MAX;

    }
    else if (abs(angleX) > 0 && abs(angleX) < 45 && posSun->getY() <= 0)
    {
        nOrange = 10 * abs(angleX)/45 + 6;
        nBlack = 10 + 6 - nOrange + 6;
        sunVec->setAll(0, 1, 1);
    }
    else if (abs(angleX) >= 45 && posSun->getY() <= 0)
    {
        nOrange = INT_MAX;
        nBlack = 12 - 10 * abs(angleX)/90;
        sunVec->setAll(0, 1, 1);
    }
    else
    {
        nOrange = INT_MAX;
        nBlack = INT_MAX;
    }
}

Size* Scene::getSize()
{
    return size;
}

void Scene::addCamera(Camera &newCam)
{
    cameras.push_back(newCam);
}

void Scene::setCurCam(int index)
{
    if (index != curCam)
    {
        curCam = index;
        isNewCam = true;
    }
}

Point* Scene::getSunVec()
{
    return sunVec;
}

void Scene::setSun(double x, double y, double z)
{
    posSun->setAll(x, y, z);
    x = -x;
    y = -y;
    z = -z;
    sunVec->setAll(-x, y, z);

    Point vecEye(0, 0, -1);
//    Point vecX(1, 0, 0);
//    Point vecY(0, 1, 0);
//    Point vecZ(0, 0, 1);
    Point vecXY(x, y, 0);
    Point vecYZ(0, y, z);
    Point vecXZ(x, 0, z);

    Point vecZero(0, 0, 0);
//    double angleX = acos(vecYZ.skalMul(&vecZ)) * 180 / M_PI;
//    double angleY = acos(vecXZ.skalMul(&vecZ)) * 180 / M_PI;
//    double angleZ = acos(vecXY.skalMul(&vecY)) * 180 / M_PI;
    double angleX = acos(vecEye.skalMul(&vecYZ)) * 180 / M_PI;
    double angleY = acos(vecEye.skalMul(&vecXZ)) * 180 / M_PI;
    double angleZ = acos(vecEye.skalMul(&vecXY)) * 180 / M_PI;

    angleX = isnan(angleX) ? 0: angleX;
    angleY = isnan(angleY) ? 0: angleY;
    angleZ = isnan(angleZ) ? 0: angleZ;

    if (x < 0)
        angleY = -angleY;
    if (y < 0)
        angleX = -angleX;

    auto cam = getCurCam();
    angleBtwSunAndEyes->setAll(angleX, angleY, 180 + angleZ);
    sunVec->turn(0, 0, 0, cam->getAngleX() + 180, cam->getAngleY(), cam->getAngleZ());
}

Angle *Scene::getAngleBtwSunAndEyes()
{
    return angleBtwSunAndEyes;
}

void Scene::moveAllFigures(double moveX, double moveY, double moveZ)
{
    for (int i = 0; i < figures.size(); i++)
        figures[i]->move(moveX, moveY, moveZ);
}

void Scene::plusAngleX()
{
    isNewCam = true;
//    if (cameras[curCam].getAngleX() < 350)
        cameras[curCam].addAngleX();
}

void Scene::decAngleX()
{
    isNewCam = true;
//    if (cameras[curCam].getAngleX() > 190)
        cameras[curCam].decAngleX();
}

void Scene::plusAngleY()
{
    isNewCam = true;
//    if (cameras[curCam].getAngleY() < 80 || cameras[curCam].getAngleY() > 270)
        cameras[curCam].addAngleY();
}

void Scene::decAngleY()
{
    isNewCam = true;
//    if (cameras[curCam].getAngleY() > 280 || cameras[curCam].getAngleY() >= 0 && cameras[curCam].getAngleY() < 180)
        cameras[curCam].decAngleY();
}

void Scene::deleteFigure(int id)
{
    for (auto i = figures.begin(); i != figures.end(); i++)
    {
        if ((*i)->getId() == id)
        {
            figures.erase(i);
            break;
        }
    }
}

QList<Figure *> *Scene::getFigures()
{
    return &figures;
}

void Scene::pushCar2Right(Figure* figure)
{
    poolFigures2Right.push(figure);
}

void Scene::pushCar2Left(Figure* figure)
{
    poolFigures2Left.push(figure);
}

Figure *Scene::popCar2Right()
{
    if (poolFigures2Right.isEmpty())
        return nullptr;

    return poolFigures2Right.pop();
}

Figure *Scene::popCar2Left()
{
    if (poolFigures2Left.isEmpty())
        return nullptr;

    return poolFigures2Left.pop();
}

void Scene::setIsShadow(bool flag)
{
    isShadow = flag;
}

Camera *Scene::getCurCam()
{
    return &cameras[curCam];
}

void Scene::addKxy()
{
    cameras[curCam].addKxy();
    isNewCam = 1;
}

void Scene::decKxy()
{
    cameras[curCam].decKxy();
    isNewCam = 1;
}

int sign(double x)
{
    if (x < 0)
        return -1;
    else if (x > 0)
        return 1;
    return 0;
}

void dswap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

#include "controller.h"
#include "defines.h"

#include "logic/world.h"
#include "logic/infoobject.h"
#include "scene.h"
#include "figure.h"
#include "camera.h"
#include "logic/sunlogic.h"


Controller::Controller(Scene *scene, World *world, QObject *parent) : QObject (parent)
{
    this->scene = scene;
    this->world = world;

    timer.setInterval(int(200));
    timer.start();
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(update()));

    sun = new SunLogic(0, 0, 200, 2, 200);
}

void Controller::update()
{
    world->action();
    scene->clearScene();
    mapWorldOnScene();
    scene->updateScene();

    timer.start();
}

void Controller::generateWorld()
{
    world->createWorld();
    scene->createScene();
}

void Controller::mapWorldOnScene()
{
    scene->setSun(sun->getX(), sun->getY(), sun->getZ());
    static QColor colorsCAr[3] = {QColor(165, 42, 42), QColor(250, 240, 230), QColor(255, 215, 0)};

    QVector<infoObject> listInfoObject = world->getListInfoObjects();
    auto figures = scene->getFigures();

    for (int i = 0; i < listInfoObject.size(); i++)
    {
        Figure *figure = nullptr;

        bool isFound = 0;
        for (auto j = figures->begin(); j != figures->end(); j++)
            if ((*j)->getId() == listInfoObject[i].id)
            {
                if (listInfoObject[i].type == typeObject::CAR2LEFT || listInfoObject[i].type == typeObject::CAR2RIGHT)
                    (*j)->setPosition(listInfoObject[i].x, listInfoObject[i].y, listInfoObject[i].z);

                isFound = 1;
                break;
            }

        if (!isFound)
        {
            switch (listInfoObject[i].type)
            {
            case typeObject::CAR2RIGHT:
            {
                Figure* newFigure = scene->popCar2Right();
                if (newFigure)
                {
                    figure = newFigure;
                    figure->setId(listInfoObject[i].id);
                    figure->setPosition(listInfoObject[i].x, listInfoObject[i].y, listInfoObject[i].z);
                }
                else
                {
                    int chooseColor = rand() % 3;
                    figure = Figure::createFigure(listInfoObject[i].id, typeFigure::CAR,
                                                  listInfoObject[i].x, listInfoObject[i].y, listInfoObject[i].z,
                                                  listInfoObject[i].length, listInfoObject[i].height, listInfoObject[i].width,
                                                  0, 0, 0,
                                                  colorsCAr[chooseColor]);
                }
                break;
            }
            case typeObject::CAR2LEFT:
            {
                Figure* newFigure = scene->popCar2Left();
                if (newFigure)
                {
                    figure = newFigure;
                    figure->setId(listInfoObject[i].id);
                    figure->setPosition(listInfoObject[i].x, listInfoObject[i].y, listInfoObject[i].z);
                }
                else
                {
                    int chooseColor = rand() % 3;
                    figure = Figure::createFigure(listInfoObject[i].id, typeFigure::CAR,
                                                  listInfoObject[i].x, listInfoObject[i].y, listInfoObject[i].z,
                                                  listInfoObject[i].length, listInfoObject[i].height, listInfoObject[i].width,
                                                  0, 180, 0,
                                                  colorsCAr[chooseColor]);
                }
                break;
            }
            case typeObject::SUN:
                scene->setSun(listInfoObject[i].x, listInfoObject[i].y, listInfoObject[i].z);
                break;

            case typeObject::TREE:
                figure = Figure::createFigure(listInfoObject[i].id, typeFigure::TREE,
                                              listInfoObject[i].x, listInfoObject[i].y, listInfoObject[i].z,
                                              listInfoObject[i].length, listInfoObject[i].height, listInfoObject[i].width,
                                              0, 0, 0);
                break;
            case typeObject::ROADLINE:
                figure = Figure::createFigure(listInfoObject[i].id, typeFigure::RECTANGLE,
                                              listInfoObject[i].x, listInfoObject[i].y, listInfoObject[i].z,
                                              listInfoObject[i].length, listInfoObject[i].height, listInfoObject[i].width,
                                              0, 0, 0,
                                              Qt::darkGray);
                break;
            case typeObject::ROADMARK:
                figure = Figure::createFigure(listInfoObject[i].id, typeFigure::RECTANGLE,
                                              listInfoObject[i].x, listInfoObject[i].y, listInfoObject[i].z,
                                              listInfoObject[i].length, listInfoObject[i].height, listInfoObject[i].width,
                                              0, 0, 0,
                                              Qt::white);
                break;
            case typeObject::GROUND:
                figure = Figure::createFigure(listInfoObject[i].id, typeFigure::RECTANGLE,
                                              listInfoObject[i].x, listInfoObject[i].y - 10, listInfoObject[i].z,
                                              listInfoObject[i].length, listInfoObject[i].height + 20, listInfoObject[i].width,
                                              0, 0, 0,
                                              QColor(107, 142, 35));
                break;
            default:
                figure = Figure::createFigure(listInfoObject[i].id, typeFigure::RECTANGLE,
                                              listInfoObject[i].x, listInfoObject[i].y, listInfoObject[i].z,
                                              listInfoObject[i].length, listInfoObject[i].height, listInfoObject[i].width,
                                              0, 0, 0);
            }
            scene->addFigure(figure);
        }
    }

    // проверка зомби-фигур
    auto delLogicObj = world->getListObjToDelete();
    for (int i = 0; i < delLogicObj.size(); i++)
        for (auto j = figures->begin(); j != figures->end(); j++)
        {
            if ((*j)->getId() == delLogicObj[i].id)
            {
                auto tmp = *j;
                figures->erase(j);
                if (delLogicObj[i].type == typeObject::CAR2RIGHT)
                    scene->pushCar2Right(tmp);
                else if (delLogicObj[i].type == typeObject::CAR2LEFT)
                    scene->pushCar2Left(tmp);
                else
                    delete tmp;
                break;
            }
        }
}

void Controller::setCurCam(int index)
{
    scene->setCurCam(index);
}

void Controller::plusAngleX()
{
    scene->plusAngleX();
}

void Controller::minusAngleX()
{
    scene->decAngleX();
}

void Controller::plusAngleY()
{
    scene->plusAngleY();
}

void Controller::minusAngleY()
{
    scene->decAngleY();
}

void Controller::setCurSunAngle(double angle)
{
    sun->setCurAngle(angle);
}

void Controller::addKxy()
{
    scene->addKxy();
}

void Controller::decKxy()
{
    scene->decKxy();
}

void Controller::setIsShadow(bool flag)
{
    scene->setIsShadow(flag);
}

void Controller::setNumThreads(int num)
{
    Scene::numThreads = num;
}

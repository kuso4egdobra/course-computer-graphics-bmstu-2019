#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>

class Scene;
class World;
class SunLogic;

class Controller : public QObject
{
    Q_OBJECT

    Scene *scene;
    World *world;
    QTimer timer;
    SunLogic *sun = nullptr;

public:
    Controller(Scene *scene, World *world, QObject *parent = nullptr);
    void generateWorld();
    void mapWorldOnScene();
    void setCurCam(int index);
    void plusAngleX();
    void minusAngleX();
    void plusAngleY();
    void minusAngleY();
    void setCurSunAngle(double angle);
    void addKxy();
    void decKxy();
    void setIsShadow(bool flag);
    void setNumThreads(int num);

private slots:
    void update();
};

#endif

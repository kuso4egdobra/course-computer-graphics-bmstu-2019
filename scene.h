#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QVector>
#include <QStack>

class Shadow;
class Figure;
class Point;
class Size;
class Camera;
class Angle;

class Scene
{
    QGraphicsScene* scene;
    Size* size;
    QList<Figure*> figures;
    QImage* image;
    static QVector<Camera> cameras;
    QStack<Figure*> poolFigures2Right;
    QStack<Figure*> poolFigures2Left;
    static int curCam;
    Point *posSun = nullptr;
    Point *sunVec = nullptr;
    Angle *angleBtwSunAndEyes = nullptr;

public:
    Scene(QGraphicsScene* scene, double sizeX, double sizeY, double sizeZ);
    ~Scene();
    void addFigure(Figure* newFigure);
    void clearScene();
    void addLine(Point* point1, Point* point2, QColor color = Qt::black);
    void createScene();
    void updateScene();
    void turnAllFigures(double x, double y, double z, double angleX, double angleY, double angleZ);
    void fillArea(QVector<Point*> &points);
    void brezLine(QImage *image, int x0, int y0, int x1, int y1, QColor color, double width, double height);
    Size* getSize();
    static bool isShadow;
    static int numThreads;
    void moveAllFigures(double moveX, double moveY, double moveZ);
    void deleteFigure(int id);
    QList<Figure*> *getFigures();
    void pushCar2Right(Figure* figure);
    void pushCar2Left(Figure* figure);
    Figure* popCar2Right();
    Figure* popCar2Left();
    void setIsShadow(bool flag);

    Camera* getCurCam();
    void plusAngleX();
    void decAngleX();
    void plusAngleY();
    void decAngleY();
    void addCamera(Camera &newCam);
    void setCurCam(int index);
    Point* getSunVec();
    void setSun(double x, double y, double z);
    Angle* getAngleBtwSunAndEyes();
    void addKxy();
    void decKxy();

private:
    void drawingFigures(); // for figures and shadows
    void getColorAndN(double &nOrange, double &nBlack);
    void drawFigure(int start, int step);
    void skaleFigures();
};

#endif // SCENE_H

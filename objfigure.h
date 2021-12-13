#ifndef OBJFIGURE_H
#define OBJFIGURE_H

#include <QVector>
#include <QColor>

class Point;

class ObjFigure
{
    static bool loadModel;

public:
    static QVector<QVector<QVector <Point>>> trianglesCarModels;
    static QVector<QVector<QColor>> colorCarModels;
    static QVector<QVector<Point>> normalsCarModels;

    static QVector<QVector<QVector <Point>>> trianglesTreeModels;
    static QVector<QVector<QColor>> colorTreeModels;
    static QVector<QVector<Point>> normalsTreeModels;


    ObjFigure();
    static void init();
    static void importObj(char* fileName);
};

#endif // OBJFIGURE_H

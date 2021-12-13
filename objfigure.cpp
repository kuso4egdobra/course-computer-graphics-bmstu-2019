#include "objfigure.h"

#include "rectangle.h"
#include "cylinder.h"
#include "point.h"
#include "triangle.h"
#include "defines.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <string.h>

bool ObjFigure::loadModel = false;
QVector<QVector<QVector <Point>>> ObjFigure::trianglesCarModels = QVector<QVector<QVector <Point>>>();
QVector<QVector<QColor>> ObjFigure::colorCarModels = QVector<QVector<QColor>>();
QVector<QVector<QVector <Point>>> ObjFigure::trianglesTreeModels = QVector<QVector<QVector <Point>>>();
QVector<QVector<QColor>> ObjFigure::colorTreeModels = QVector<QVector<QColor>>();
QVector<QVector<Point>> ObjFigure::normalsCarModels = QVector<QVector<Point>>();
QVector<QVector<Point>> ObjFigure::normalsTreeModels = QVector<QVector<Point>>();

ObjFigure::ObjFigure()
{

}

void ObjFigure::init()
{
    if (loadModel)
        return;

    loadModel = true;
    char fileName1[]= "lowpolytree.obj";
    importObj(fileName1);
    char fileName2[]= "Dodge_ChallengerCar.obj";
    importObj(fileName2);
}

struct Edge
{
    QVector<int> points;
    QColor color;
    int normal;
};

void ObjFigure::importObj(char *fileName)
{
    QVector<Point> pts;
    QVector<Point> normals;
    QVector<QVector<Point>> ptsModels;
    QVector<QVector<Edge>> edgesModels;
    QVector<Edge> edges;
    QColor color = Qt::black;

    std::string line, line1;
    std::ifstream in(fileName); // окрываем файл для чтения
    if (in.is_open())
    {
        char c[100];
        double num1, num2, num3;
        char *str = new char[100];
        while (getline(in, line))
        {
            if (sscanf(line.data(),"%s %s", c, str) == 2)
            {
                if (str[0] == 'w' && str[1] == 'h' && str[2] == 'e')
                    color = Qt::black;
                else if (str[0] == 'c' && str[1] == 'a' && str[2] == 'r' && line1[2] != 'w')
                    color = QColor(255, 99, 71);
                else if (str[0] == 'g' && str[1] == 'l' && str[2] == 'a')
                    color = QColor(173, 216, 230);
                else if (str[0] == 'h' && str[1] == 'e' && str[2] == 'a')
                    color = Qt::yellow;
                else if (str[0] == 'r' && str[1] == 'e' && str[2] == 'a')
                    color = Qt::red;
                else if (str[0] == 'L' && str[1] == 'e')
                    color = Qt::darkGreen;
                else if (str[0] == 'B' && str[1] == 'a' && str[2] == 'r')
                    color = Qt::darkRed;
                else if (str[0] == 'L' && str[1] == 'i' && str[2] == 'g')
                    color = Qt::red;
                else if (str[0] == 'B' && str[1] == 'o' && str[2] == 't')
                    color = Qt::lightGray;
                else if (str[0] == 'E' && str[1] == 'x' && str[2] == 'h')
                    color = Qt::darkMagenta;
                else if (str[0] == 'W' && str[1] == 'h' && str[2] == 'i')
                    color = Qt::lightGray;
                else if (str[0] == 'G' && str[1] == 'r' && str[2] == 'i')
                    color = Qt::darkRed;
                else if (str[0] == 'R' && str[1] == 'i' && str[2] == 'm')
                    color = Qt::black;
                else if (str[0] == 'T' && str[1] == 'i' && str[2] == 'r')
                    color = Qt::black;
                else if (str[0] == 'B' && str[1] == 'r' && str[2] == 'a')
                    color = Qt::red;
            }

            if (sscanf(line.data(),"%s", c) == 1)
            {
                if (!std::strcmp(c, "v"))
                {
                    if (sscanf(line.data(),"%s %lf %lf %lf\n", c, &num1, &num2, &num3) == 4)
                    {
                        Point newPnt(num1, num2, num3);
                        pts.push_back(newPnt);
                    }
                }
                else if (!std::strcmp(c, "vn"))
                {
                    if (sscanf(line.data(),"%s %lf %lf %lf\n", c, &num1, &num2, &num3) == 4)
                    {
                        Point newPnt(num1, num2, num3);
                        normals.push_back(newPnt);
                    }
                }
                else if (!std::strcmp(c, "f"))
                {
                    int num4, num5, num6, num7, num8, num9, num10, numTrash;
                    if (sscanf(line.data(),"%s %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
                               c, &num4, &numTrash, &num8, &num5, &numTrash, &numTrash,
                               &num6, &numTrash, &numTrash, &num7, &numTrash, &numTrash) == 13)
                    {
                        Edge newEdge;
                        newEdge.points.push_back(num4 - 1);
                        newEdge.points.push_back(num5 - 1);
                        newEdge.points.push_back(num6 - 1);
                        newEdge.points.push_back(num7 - 1);
                        newEdge.color = color;
                        newEdge.normal = num8 - 1;

                        edges.push_back(newEdge);
                    }
                    else if (sscanf(line.data(),"%s %d/%d/%d %d/%d/%d %d/%d/%d\n",
                               c, &num4, &numTrash, &num8, &num5, &numTrash, &numTrash,
                               &num6, &numTrash, &numTrash) == 10)
                    {
                        Edge newEdge;
                        newEdge.points.push_back(num4 - 1);
                        newEdge.points.push_back(num5 - 1);
                        newEdge.points.push_back(num6 - 1);
                        newEdge.color = color;
                        newEdge.normal = num8 - 1;

                        edges.push_back(newEdge);
                    }
                    else if (sscanf(line.data(),"%s %d/%d %d/%d %d/%d %d/%d\n",
                               c, &num4, &num8, &num5, &numTrash, &num6, &numTrash,
                               &num7, &numTrash) == 9)
                    {
                        Edge newEdge;
                        newEdge.points.push_back(num4 - 1);
                        newEdge.points.push_back(num5 - 1);
                        newEdge.points.push_back(num6 - 1);
                        newEdge.points.push_back(num7 - 1);
                        newEdge.color = color;
                        newEdge.normal = num8 - 1;

                        edges.push_back(newEdge);
                    }
                    else if (sscanf(line.data(),"%s %d/%d %d/%d %d/%d\n",
                                    c, &num4, &num8, &num5, &numTrash, &num6, &numTrash) == 7)
                    {
                        Edge newEdge;
                        newEdge.points.push_back(num4 - 1);
                        newEdge.points.push_back(num5 - 1);
                        newEdge.points.push_back(num6 - 1);
                        newEdge.color = color;
                        newEdge.normal = num8 - 1;

                        edges.push_back(newEdge);
                    }
                }
            }
            line1 = line;
        }
    }
    in.close();

    ptsModels.push_back(pts);
    edgesModels.push_back(edges);

    QVector<QVector<QVector <Point>>> *ptrModel = nullptr;
    QVector<QVector<QColor>> *ptrColor = nullptr;
    QVector<QVector<Point>> *ptrNormal = nullptr;
    bool isCar = 0;
    if (strstr(fileName, "Car"))
    {
        trianglesCarModels.push_back(QVector<QVector<Point>>());
        colorCarModels.push_back(QVector<QColor>());
        normalsCarModels.push_back(QVector<Point>());
        ptrModel = &trianglesCarModels;
        ptrColor = &colorCarModels;
        ptrNormal = &normalsCarModels;
        isCar = 1;
    }
    else if (strstr(fileName, "tree"))
    {
        trianglesTreeModels.push_back(QVector<QVector<Point>>());
        colorTreeModels.push_back(QVector<QColor>());
        normalsTreeModels.push_back(QVector<Point>());
        ptrModel = &trianglesTreeModels;
        ptrColor = &colorTreeModels;
        ptrNormal = &normalsTreeModels;
    }

    for (int i = 0; i < edgesModels.last().size(); i++)
    {
        QVector<int> edge = edgesModels.last()[i].points;
        QColor colorCar = edgesModels.last()[i].color;
        int normal = edgesModels.last()[i].normal;

        Point *screen_coords[4];
        for (int j = 0; j < edge.size(); j++)
        {
            Point world_coords = ptsModels.last()[edge[j]];
            screen_coords[j] = new Point(world_coords.getX(), world_coords.getY(), world_coords.getZ());
        }
        if (isCar)
        {
            for (int j = 0; j < edge.size(); j++)
            {
                screen_coords[j]->div(DIV_COEF);
            }
        }

        ptrModel->last().push_back({screen_coords[0], screen_coords[1], screen_coords[2]});
        ptrColor->last().push_back(colorCar);
        ptrNormal->last().push_back(normals[normal]);

        if (edge.size() == 4)
        {
            ptrModel->last().push_back({screen_coords[2], screen_coords[3], screen_coords[0]});
            ptrColor->last().push_back(colorCar);
            ptrNormal->last().push_back(normals[normal]);
        }
    }
}

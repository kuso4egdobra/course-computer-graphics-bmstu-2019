#include "carScene.h"

#include "point.h"
#include "triangle.h"
#include "objfigure.h"
#include "angle.h"

CarScene::CarScene(double x, double y, double z,
         double angleX, double angleY, double angleZ, QColor color) :
    Figure(x, y, z, 0, 0, 0, angleX + 90, angleY + 90, angleZ)
{
    auto trianglesModels = ObjFigure::trianglesCarModels;
    auto colorModels = ObjFigure::colorCarModels;
    auto normalModels = ObjFigure::normalsCarModels;
    int randCar = rand() % trianglesModels.size();

     // !!! лишние точки
    auto curTriangModel = trianglesModels[randCar];
    auto curColorModel = colorModels[randCar];
    auto curNormalModel = normalModels[randCar];

    int sizeList = curTriangModel.size();
    for (int i = 0; i < sizeList; i++)
    {
        QColor curColor = curColorModel[i];
        auto curTriang = curTriangModel[i];
        auto curNormal = new Point(curNormalModel[i]);
        Point *pt1 = new Point(curTriang[0], x, y - 4, z);
        Point *pt2 = new Point(curTriang[1], x, y - 4, z);
        Point *pt3 = new Point(curTriang[2], x, y - 4, z);

        if (curColor == QColor(255, 99, 71))
            curColor = color;

        triangls.push_back(Triangle(pt1, pt2, pt3, curNormal, curColor));
        points.append({pt1, pt2, pt3});
        normals.append(curNormal);
    }
    turnPoints(x,y,z);

    for (int i = 0; i < points.size(); i++)
        primaryPoints.append(new Point(points[i]));

    for (int i = 0; i < normals.size(); i++)
        primaryNormals.append(new Point(normals[i]));
}

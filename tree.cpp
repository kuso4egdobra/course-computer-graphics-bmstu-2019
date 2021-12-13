#include "tree.h"

#include "point.h"
#include "triangle.h"
#include "objfigure.h"

Tree::Tree(double x, double y, double z,
           double height, double widthWood, double widthLeaves,
           double angleX, double angleY, double angleZ):
    Figure(x, y, z, widthLeaves, height, widthLeaves, angleX, angleY, angleZ)
{
    auto trianglesModels = ObjFigure::trianglesTreeModels;
    auto colorModels = ObjFigure::colorTreeModels;
    auto normalModels = ObjFigure::normalsTreeModels;
    int randNum = rand() % trianglesModels.size();
    y += 12;

     // !!! лишние точки
    auto curTriangModel = trianglesModels[randNum];
    auto curColorModel = colorModels[randNum];
    auto curNormalModel = normalModels[randNum];

    int sizeList = curTriangModel.size();
    for (int i = 0; i < sizeList; i++)
    {
        QColor curColor = curColorModel[i];
        auto curTriang = curTriangModel[i];
        auto curNormal = new Point(curNormalModel[i]);
        Point *pt1 = new Point(curTriang[0]*17, x, y, z);
        Point *pt2 = new Point(curTriang[1]*17, x, y, z);
        Point *pt3 = new Point(curTriang[2]*17, x, y, z);

        triangls.push_back(Triangle(pt1, pt2, pt3, curNormal, curColor));
        points.append({pt1, pt2, pt3});
        normals.append(curNormal);
    }

    for (int i = 0; i < points.size(); i++)
        primaryPoints.append(new Point(points[i]));

    for (int i = 0; i < normals.size(); i++)
        primaryNormals.append(new Point(normals[i]));
}

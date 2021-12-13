#include "rectangle.h"
#include "point.h"
#include "triangle.h"

Rectangle::Rectangle(double x, double y, double z, double lenX, double lenY, double lenZ,
                     double turnX, double turnY, double turnZ, QColor color):
    Figure(x, y, z, lenX, lenY, lenZ, turnX, turnY, turnZ)
{
    type = typeFigure::GROUND;
    Point *point1 = new Point(x + lenX/2, y + lenY/2, z + lenZ/2);
    Point *point2 = new Point(x + lenX/2, y + lenY/2, z - lenZ/2);
    Point *point3 = new Point(x + lenX/2, y - lenY/2, z + lenZ/2);
    Point *point4 = new Point(x + lenX/2, y - lenY/2, z - lenZ/2);
    Point *point5 = new Point(x - lenX/2, y + lenY/2, z + lenZ/2);
    Point *point6 = new Point(x - lenX/2, y + lenY/2, z - lenZ/2);
    Point *point7 = new Point(x - lenX/2, y - lenY/2, z + lenZ/2);
    Point *point8 = new Point(x - lenX/2, y - lenY/2, z - lenZ/2);

    points.push_back(point1);
    points.push_back(point2);
    points.push_back(point3);
    points.push_back(point4);
    points.push_back(point5);
    points.push_back(point6);
    points.push_back(point7);
    points.push_back(point8);

    Point *normRight = new Point(1, 0, 0);
    Point *normUp = new Point(0, 1, 1);
    Point *normToUs = new Point(0, 0, 1); //?
    Point *normLeft = new Point(-1, 0, 0);
    Point *normDown = new Point(0, -1, 0);
    Point *normFromUs = new Point(0, 0, -1); //?

    normals.append({normRight, normUp, normToUs, normLeft, normDown, normFromUs});
    for (int i = 0; i < normals.size(); i++)
        primaryNormals.append(new Point(normals[i]));


    triangls.append(Triangle(point1, point2, point4, normUp, color));
    triangls.append(Triangle(point4, point3, point1, normUp, color));

    triangls.append(Triangle(point5, point6, point8, normUp, color));
    triangls.append(Triangle(point8, point7, point5, normUp, color));

    triangls.append(Triangle(point1, point3, point7, normUp, color));
    triangls.append(Triangle(point7, point5, point1, normUp, color));

    triangls.append(Triangle(point2, point4, point8, normUp, color));
    triangls.append(Triangle(point8, point6, point2, normUp, color));

    triangls.append(Triangle(point1, point2, point6, normUp, color));
    triangls.append(Triangle(point6, point5, point1, normUp, color));

    triangls.append(Triangle(point3, point4, point8, normUp, color));
    triangls.append(Triangle(point8, point7, point3, normUp, color));

    for (int i = 0; i < points.size(); i++)
        primaryPoints.append(new Point(points[i]));
}

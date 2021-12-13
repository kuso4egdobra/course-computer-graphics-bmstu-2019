#include "cylinder.h"
#include "point.h"

Cylinder::Cylinder(double xCentre, double yCentre, double zCentre, double radius, double height, double turnX, double turnY, double turnZ):
    Figure (xCentre, yCentre, zCentre, radius*2, height, radius*2, turnX, turnY, turnZ)
{
    int i = 0;
    double x = 0;
    double y = radius;
    double di = 2 - 2 * radius;
    Point *pnt1 = nullptr, *pnt2 = nullptr, *pnt3 = nullptr, *pnt4 = nullptr,
          *pnt5 = nullptr, *pnt6 = nullptr, *pnt7 = nullptr, *pnt8 = nullptr;
    while (y >= 0)
    {
        //            win.image.setPixel(cx + x, cy + y, win.color_line.rgb())
        //            win.image.setPixel(cx + x, cy - y, win.color_line.rgb())
        //            win.image.setPixel(cx - x, cy + y, win.color_line.rgb())
        //            win.image.setPixel(cx - x, cy - y, win.color_line.rgb())
        if (i == 0)
        {
            pnt1 = new Point(xCentre + x, yCentre + y, zCentre + height/2);
            pnt2 = new Point(xCentre + x, yCentre - y, zCentre + height/2);
            pnt3 = new Point(xCentre - x, yCentre + y, zCentre + height/2);
            pnt4 = new Point(xCentre - x, yCentre - y, zCentre + height/2);
            pnt5 = new Point(xCentre + x, yCentre + y, zCentre - height/2);
            pnt6 = new Point(xCentre + x, yCentre - y, zCentre - height/2);
            pnt7 = new Point(xCentre - x, yCentre + y, zCentre - height/2);
            pnt8 = new Point(xCentre - x, yCentre - y, zCentre - height/2);

            points.push_back(pnt1);
            points.push_back(pnt2);
            points.push_back(pnt3);
            points.push_back(pnt4);
            points.push_back(pnt5);
            points.push_back(pnt6);
            points.push_back(pnt7);
            points.push_back(pnt8);


            if (points.size() > 16)
            {
//                окружность
                QPair<Point*, Point*> connection9(pnt1, points[points.size() - 16]);
                QPair<Point*, Point*> connection10(pnt2, points[points.size() - 15]);
                QPair<Point*, Point*> connection11(pnt3, points[points.size() - 14]);
                QPair<Point*, Point*> connection12(pnt4, points[points.size() - 13]);
                QPair<Point*, Point*> connection13(pnt5, points[points.size() - 12]);
                QPair<Point*, Point*> connection14(pnt6, points[points.size() - 11]);
                QPair<Point*, Point*> connection15(pnt7, points[points.size() - 10]);
                QPair<Point*, Point*> connection16(pnt8, points[points.size() - 9]);
            }

            i++;
        }
        else if (i == 5)
            i = 0;
        else
            i++;

        if (di <= 0)
        {
            double buf = 2 * (di + y) - 1;
            x += 1;

            if (buf <= 0)
                di = di + 2 * x + 1;
            else
            {
                y -= 1;
                di = di + 2 * (x - y + 1);
            }
        }

        else
        {
            double buf = 2 * (di - x) - 1;
            y -= 1;

            if (buf > 0)
                di = di - 2 * y + 1;
            else
            {
                x += 1;
                di = di + 2 * (x - y + 1);
            }
        }
    }
}

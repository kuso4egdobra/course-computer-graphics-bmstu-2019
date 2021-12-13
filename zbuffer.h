#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <QColor>

class Point;

class ZBuffer
{
    static double **zBuffer;
    static double **zBufferShadow;
    static QColor **zBufferColor;
    static int rows, colums;
public:
    ZBuffer();
    ~ZBuffer();
    static void initZBuffer(int rowNum, int colNum);
    static void setDefaultValue();
    static void setZ(int i, int j, double z, QColor color);
    static void setZShadow(int i, int j, double z);
    static double** getZBuffer();
    static double** getZBufferShadow();
    static QColor** getZBufferColor();
    static int getNumRows();
    static int getNumCols();

protected:
    static QColor **createZBufferColor();
    static double **createZBuffer();
};

#endif // ZBUFFER_H




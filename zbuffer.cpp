#include "zbuffer.h"

#include <mutex>
#include "defines.h"

double** ZBuffer::zBuffer = nullptr;
double** ZBuffer::zBufferShadow = nullptr;
QColor** ZBuffer::zBufferColor = nullptr;
int ZBuffer::rows = 0;
int ZBuffer::colums = 0;

//std::mutex mt;


double** ZBuffer::createZBuffer()
{
    double **ptr = new double* [rows];
    for (int i = 0; i < rows; i++)
        ptr[i] = new double [colums];

    return ptr;
}



QColor** ZBuffer::createZBufferColor()
{
    QColor **ptr = new QColor* [rows];
    for (int i = 0; i < rows; i++)
        ptr[i] = new QColor [colums];

    return ptr;
}

ZBuffer::ZBuffer()
{

}

ZBuffer::~ZBuffer()
{
    delete[] zBuffer;
    delete[] zBufferColor;
    delete[] zBufferShadow;
}

void ZBuffer::initZBuffer(int rowNum, int colNum)
{
    rows = rowNum;
    colums = colNum;
    zBuffer = createZBuffer();
    zBufferColor = createZBufferColor();
    zBufferShadow = createZBuffer();
}

void ZBuffer::setDefaultValue()
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < colums; j++)
        {
            zBuffer[i][j] = DEPTH_ZB;
            zBufferColor[i][j] = DFT_COLOR;
            zBufferShadow[i][j] = DEPTH_ZB;
        }
}

void ZBuffer::setZ(int i, int j, double z, QColor color)
{
//    mt.lock();
    if (zBuffer[i][j] < z)
    {
        zBuffer[i][j] = z;
        zBufferColor[i][j] = color;
    }
//     mt.unlock();
}

void ZBuffer::setZShadow(int i, int j, double z)
{
//    mt.lock();
    if (zBufferShadow[i][j] < z)
        zBufferShadow[i][j] = z;
//     mt.unlock();
}

double** ZBuffer::getZBuffer()
{
    return zBuffer;
}

double** ZBuffer::getZBufferShadow()
{
    return zBufferShadow;
}

QColor **ZBuffer::getZBufferColor()
{
    return zBufferColor;
}

int ZBuffer::getNumRows()
{
    return rows;
}

int ZBuffer::getNumCols()
{
    return colums;
}

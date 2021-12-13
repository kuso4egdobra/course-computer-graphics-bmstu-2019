#ifndef ANGLE_H
#define ANGLE_H

class Angle
{
    double angleX, angleY, angleZ;
public:
    Angle(double x, double y, double z);
    double getAngleX();
    double getAngleY();
    double getAngleZ();

    void addAngleX(double dx);
    void addAngleY(double dy);
    void addAngleZ(double dz);
    void addAngles(double dx, double dy, double dz);

    void setAngleX(double x);
    void setAngleY(double y);
    void setAngleZ(double z);
    void setAll(double x, double y, double z);

    void setAnglesZero();
    bool isZero();

private:
    double modDegree(double angle);
};

#endif // ANGLE_H

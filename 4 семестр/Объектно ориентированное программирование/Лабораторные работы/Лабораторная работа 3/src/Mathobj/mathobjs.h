#ifndef MATHOBJS_H
#define MATHOBJS_H


class ScaleCoef
{
private:
    double kx, ky, kz;
public:
    ScaleCoef() = default;
    ScaleCoef(double x, double y, double z) {kx = x; ky = y; kz = z;};

    double get_kx() const {return kx; };
    double get_ky() const {return ky; };
    double get_kz() const {return kz; };
};

class Angle
{
private:
    double xy, yz, xz;
public:
    Angle() = default;
    Angle(double x, double y, double z) {xy = x; yz = y; yz = z;};

    double get_xy() const {return xy; };
    double get_yz() const {return yz; };
    double get_xz() const {return xz; };
};

#endif // MATHOBJS_H

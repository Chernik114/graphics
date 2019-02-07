#ifndef REGPOLYGON_H
#define REGPOLYGON_H

#include <functional>
#include <QtGlobal>
#include <cmath>

class RegPolygon
{
public:
    typedef std::function<void(double,double,double,double)> LineDrawer;

    const double PI;

    RegPolygon();

    RegPolygon& setCenter(double x, double y);
    RegPolygon& setLineDrawer(const LineDrawer& drawer);
    RegPolygon& setSide(double s);
    RegPolygon& setOuterRadius(double s);
    RegPolygon& setInnerRadius(double s);
    RegPolygon& setAmountSides(int k);
    RegPolygon& setRotation(double a);

    void draw();
    bool isContains(double x, double y);

    double getX() const;
    double getY() const;
    double getSide() const;
    double getOuter() const;
    double getInner() const;
    int getK() const;
    const LineDrawer& getDrawer() const;
    double getA() const;

private:
    double x, y, side, outer, inner, a;
    int k;
    LineDrawer drawer;
};

#endif // REGPOLYGON_H

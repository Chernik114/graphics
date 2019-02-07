#include "regpolygon.h"

RegPolygon::RegPolygon():
    PI(acos(-1.0)),
    x(0), y(0), side(0), outer(0), inner(0), a(0),
    k(1),
    drawer([](double,double,double,double){})
{}

RegPolygon &RegPolygon::setCenter(double x, double y)
{
    this->x = x;
    this->y = y;
    return *this;
}

RegPolygon &RegPolygon::setLineDrawer(const RegPolygon::LineDrawer &drawer)
{
    this->drawer = drawer;
    return *this;
}

RegPolygon &RegPolygon::setSide(double s)
{
    this->side = s;
    this->inner = s / 2 / tan(PI / k);
    this->outer = s / 2 / sin(PI / k);
    return *this;
}

RegPolygon &RegPolygon::setOuterRadius(double s)
{
    this->side = s * sin(PI / k) * 2;
    this->inner = s * cos(PI / k);
    this->outer = s;
    return *this;
}

RegPolygon &RegPolygon::setInnerRadius(double s)
{
    this->side = s * tan(PI / k) * 2;
    this->inner = s;
    this->outer = s / cos(PI / k);
    return *this;
}

RegPolygon &RegPolygon::setAmountSides(int k)
{
    this->k = k;
    setOuterRadius(outer);
    return *this;
}

RegPolygon &RegPolygon::setRotation(double a)
{
    this->a = a;
    return *this;
}

void RegPolygon::draw()
{
    double x1, y1, x2, y2;
    for(int i = 0; i <= k; i++){
        y2 = PI * 2 * i / k + a;
        x2 = cos(y2) * outer + x;
        y2 = sin(y2) * outer + y;
        if(i > 0){
            drawer(x1, y1, x2, y2);
        }
        x1 = x2;
        y1 = y2;
    }
}

double RegPolygon::getX() const
{
    return x;
}

double RegPolygon::getY() const
{
    return y;
}

double RegPolygon::getSide() const
{
    return side;
}

double RegPolygon::getOuter() const
{
    return outer;
}

double RegPolygon::getInner() const
{
    return inner;
}

int RegPolygon::getK() const
{
    return k;
}

const RegPolygon::LineDrawer& RegPolygon::getDrawer() const
{
    return drawer;
}

double RegPolygon::getA() const
{
    return a;
}

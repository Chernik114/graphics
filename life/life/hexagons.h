#ifndef HEXAGONS_H
#define HEXAGONS_H

#include "pixdrawer.h"
#include "tableview.h"
#include "regpolygon.h"

class Hexagons
{
public:
    Hexagons();

    void draw(PixDrawer& drw);

private:
    TableView view;

    class LineDrawer : public RegPolygon::LineDrawer {
    public:
        LineDrawer(PixDrawer &drw, ulong color);
        void operator() (double x1, double y1, double x2, double y2);
    private:
        PixDrawer &drw;
        ulong color;
    };
};

#endif // HEXAGONS_H

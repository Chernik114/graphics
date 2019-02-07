#ifndef HEXAGONS_H
#define HEXAGONS_H

#include <QDebug>

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

    class LineDrawer {
    public:
        LineDrawer(PixDrawer &drw, ulong color);
        operator RegPolygon::LineDrawer();
    private:
        PixDrawer &drw;
        ulong color;
    };
};

#endif // HEXAGONS_H

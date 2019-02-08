#ifndef HEXAGONS_H
#define HEXAGONS_H

#include "pixdrawer.h"
#include "tableview.h"
#include "regpolygon.h"

class Hexagons
{
public:
    Hexagons(IGameView* view);

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

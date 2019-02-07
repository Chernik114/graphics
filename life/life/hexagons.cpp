#include "hexagons.h"

Hexagons::Hexagons()
{

}

void Hexagons::draw(PixDrawer &drw)
{
    RegPolygon p;
    p
            .setRotation(p.PI / 12)
            .setAmountSides(6)
            .setOuterRadius(view.getSizeCell())
            .setLineDrawer(LineDrawer(drw, view.getBorderColor()));

    for(int x = 0; x < view.getCellsX(); x++){
        for(int y = 0; y < view.getCellsY(); y++){
            if(!view.isCellShowed(x, y)){
                continue;
            }
            p
                    .setCenter(
                        p.getInner() * ((x % 2) + 2 * x),
                        (p.getOuter() + p.getSide() / 2) * y)
                    .draw();
            drw.fillSpace(p.getX(), p.getY(), view.getCellColor(x, y));
            drw.drawText(view.getCellText(x, y), p.getX(), p.getY(), view.getTextSize(), view.getTextColor());
        }
    }
}

Hexagons::LineDrawer::LineDrawer(PixDrawer &drw, ulong color):
    drw(drw), color(color)
{}

void Hexagons::LineDrawer::operator()(double x1, double y1, double x2, double y2)
{
    drw.drawLine(x1, y1, x2, y2, color);
}

#include "hexagons.h"

Hexagons::Hexagons()
{

}

void Hexagons::draw(PixDrawer &drw)
{
    RegPolygon p;
    p
            .setRotation(p.PI / 6)
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
                        p.getInner() * ((y % 2) + 2 * x + 1),
                        (p.getOuter() + p.getSide() / 2) * y + p.getOuter())
                    .draw();
            drw.fillSpace(p.getX(), p.getY(), view.getCellColor(x, y));
            drw.drawText(view.getCellText(x, y), p.getX(), p.getY(), view.getTextSize(), view.getTextColor());
        }
    }
}

Hexagons::LineDrawer::LineDrawer(PixDrawer &drw, ulong color):
    drw(drw), color(color)
{}

Hexagons::LineDrawer::operator RegPolygon::LineDrawer()
{
    return [=](double x1, double y1, double x2, double y2){
        this->drw.drawLine(round(x1), round(y1), round(x2), round(y2), color);
    };
}
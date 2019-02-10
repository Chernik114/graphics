#include "hexagons.h"

Hexagons::Hexagons(IGameView& view):
    view(view)
{}

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
            drw.fillSpace(
                        p.getX(), p.getY(),
                        view.getCellColor(x, y)
            );
            if(view.getSizeCell() >= 7 && view.getTextColor() != 0){
                drw.drawText(
                            view.getCellText(x, y),
                            p.getX(), p.getY(),
                            view.getTextSize(),
                            view.getTextColor()
                );
            }
        }
    }
}

void Hexagons::mouseClick(int px, int py, IGameView::Mouse state)
{
    RegPolygon p;
    p
            .setRotation(p.PI / 6)
            .setAmountSides(6)
            .setOuterRadius(view.getSizeCell());
    for(int x = 0; x < view.getCellsX(); x++){
        for(int y = 0; y < view.getCellsY(); y++){
            p.setCenter(
                    p.getInner() * ((y % 2) + 2 * x + 1),
                    (p.getOuter() + p.getSide() / 2) * y + p.getOuter());
            if(p.isContains(px, py)){
                view.mouseClick(x, y, state);
                return;
            }
        }
    }
    view.mouseClick(-1, -1, state);
}

int Hexagons::getSizeX()
{
    RegPolygon p;
    p
            .setAmountSides(6)
            .setOuterRadius(view.getSizeCell());
    return p.getInner() * (1 + 2 * view.getCellsX()) + 5;
}

int Hexagons::getSizeY()
{
    RegPolygon p;
    p
            .setAmountSides(6)
            .setOuterRadius(view.getSizeCell());
    return (p.getOuter() + p.getSide() / 2) * view.getCellsY() + p.getOuter() - p.getSide() / 2 + 5;
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

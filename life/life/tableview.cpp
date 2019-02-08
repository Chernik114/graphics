#include "tableview.h"

TableView::TableView(IGameView* view):
    animator(),
    sizeCell    (new Animator::Value<int>(animator, 20)),
    borderColor (new Animator::Value<ulong>(animator, 0xFF000000)),
    textColor   (new Animator::Value<ulong>(animator, 0xFF0000FF)),
    deadColor   (new Animator::Value<ulong>(animator, 0xFFFFFFFF)),
    aliveColor  (new Animator::Value<ulong>(animator, 0xFF00FF00)),
    view(view)
{}

int TableView::getSizeCell()
{
    return sizeCell->g();
}

int TableView::getTextSize()
{
    return getSizeCell() * 3 / 5;
}

ulong TableView::getBorderColor()
{
    return borderColor->g();
}

ulong TableView::getCellColor(int x, int y)
{
    switch(view->getCellState(x, y)){
    case IGameView::DEAD:
    case IGameView::NO_SHOWED:
        return deadColor->g();
    case IGameView::ALIVE:
        return aliveColor->g();
    }
}

ulong TableView::getTextColor()
{
    return textColor->g();
}

int TableView::getCellsX()
{
    return view->getCellsX();
}

int TableView::getCellsY()
{
    return view->getCellsY();
}

bool TableView::isCellShowed(int x, int y)
{
    return view->getCellState(x, y) != IGameView::NO_SHOWED;
}

QString TableView::getCellText(int x, int y)
{
    return view->getCellText(x, y);
}

void TableView::setSizeCell(int s)
{
    sizeCell->s(s);
}

void TableView::setBorderColor(ulong c)
{
    borderColor->s(c);
}

void TableView::setTextColor(ulong c)
{
    textColor->s(c);
}

#include "tableview.h"

TableView::TableView(IGameView& view):
    animator([&view](){view.repaint();}),
    sizeCell(*animator.createValue(20)),
    borderColor (*animator.createARGBValue(0xFF000000)),
    textColor   (*animator.createARGBValue(0xFF0000FF)),
    deadColor   (*animator.createARGBValue(0xFFFFFFFF)),
    aliveColor  (*animator.createARGBValue(0xFF00FF00)),
    cells(view.getCellsX() * view.getCellsY()),
    view(view)
{
    for(auto i = 0ull; i < cells.size(); i++){
        cells[i] = animator.createARGBValue(
                    MathCellColor(i % view.getCellsX(), i / view.getCellsX())
        );
    }
}

int TableView::getSizeCell()
{
    return sizeCell.g();
}

int TableView::getTextSize()
{
    return getSizeCell() * 3 / 5;
}

ulong TableView::getBorderColor()
{
    return borderColor.g();
}

ulong TableView::getCellColor(int x, int y)
{
    auto& cell = *cells[x + y * view.getCellsX()];
    cell.s(MathCellColor(x, y));
    return cell.g();
}

ulong TableView::getTextColor()
{
    return textColor.g();
}

int TableView::getCellsX()
{
    return view.getCellsX();
}

int TableView::getCellsY()
{
    return view.getCellsY();
}

bool TableView::isCellShowed(int x, int y)
{
    return view.getCellState(x, y) != IGameView::NO_SHOWED;
}

QString TableView::getCellText(int x, int y)
{
    return view.getCellText(x, y);
}

void TableView::setSizeCell(int s)
{
    sizeCell.s(s);
}

void TableView::setBorderColor(ulong c)
{
    borderColor.s(c);
}

void TableView::setTextColor(ulong c)
{
    textColor.s(c);
}

void TableView::mouseClick(int x, int y, IGameView::Mouse state)
{
    view.mouseClick(x, y, state);
}

ulong TableView::MathCellColor(int x, int y)
{
    switch(view.getCellState(x, y)){
    case IGameView::DEAD:
    case IGameView::NO_SHOWED:
        return deadColor.g();
    case IGameView::ALIVE:
        return aliveColor.g();
    }
}

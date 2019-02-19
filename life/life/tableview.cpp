#include "tableview.h"

TableView::TableView(IGameView& view):
    animator([&view](){view.repaint();}),
    realTextColor(0xFFFF00FF),
    sizeCell(*animator.createValue(20)),
    borderColor (*animator.createARGBValue(0xFF000000)),
    textColor   (*animator.createARGBValue(0x00000000)),
    deadColor   (*animator.createARGBValue(0xFFFFFFFF)),
    aliveColor  (*animator.createARGBValue(0xFFFF0000)),
    nDeadColor  (*animator.createARGBValue(0xFFDDDDDD)),
    nAliveColor (*animator.createARGBValue(0xFFDD0000)),
    cells(0),
    view(view)
{
    getVCell(1, 1);
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
    auto& cell = getVCell(x, y);
    cell.s(mathCellColor(x, y));
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
    if(s <= 0){
        return;
    }
    sizeCell.s(s);
}

void TableView::setBorderColor(ulong c)
{
    borderColor.s(c);
}

void TableView::setTextColor(ulong c)
{
    realTextColor = c;
    if(isShowText){
        textColor.s(c);
    }
}

ulong TableView::getDeadColor()
{
    return deadColor.g();
}

ulong TableView::getNDeadColor()
{
    return nDeadColor.g();
}

ulong TableView::getAliveColor()
{
    return aliveColor.g();
}

ulong TableView::getNAliveColor()
{
    return nAliveColor.g();
}

void TableView::setDeadColor(ulong c)
{
    deadColor.s(c);
}

void TableView::setNDeadColor(ulong c)
{
    nDeadColor.s(c);
}

void TableView::setAliveColor(ulong c)
{
    aliveColor.s(c);
}

void TableView::setNAliveColor(ulong c)
{
    nAliveColor.s(c);
}

void TableView::setAnimInterval(int t)
{
    animator.setInterval(t);
}

void TableView::setIsShowText(bool state)
{
    isShowText = state;
    if(state){
        textColor.s(realTextColor);
    } else {
        textColor.s(0);
    }
}

ulong TableView::getRealTextColor()
{
    return realTextColor;
}

void TableView::setMsAnimation(int t)
{
    animator.setMsAnimation(t);
}

int TableView::getMsAnimation()
{
    return animator.getMsAnimation();
}

void TableView::mouseClick(int x, int y, IGameView::Mouse state)
{
    view.mouseClick(x, y, state);
}

ulong TableView::mathCellColor(int x, int y)
{
    switch(view.getCellState(x, y)){
    case IGameView::DEAD:
    case IGameView::NO_SHOWED:
        return deadColor.g();
    case IGameView::NEW_DEAD:
        return nDeadColor.g();
    case IGameView::ALIVE:
        return aliveColor.g();
    case IGameView::NEW_ALIVE:
        return nAliveColor.g();
    }
    return 0;
}

Value<ulong> &TableView::getVCell(int x, int y)
{
    auto pos = 0ull + x + y * view.getCellsX();
    if(pos >= cells.size()){
        auto newPos = 1ull * view.getCellsX() * view.getCellsY();
        auto oldPos = cells.size();
        cells.resize(newPos);
        for(auto i = oldPos; i < newPos; i++){
            cells[i] = animator.createARGBValue(
                        mathCellColor(i % view.getCellsX(), i / view.getCellsX())
            );
        }
    }
    return *cells[pos];
}

#include "tableview.h"

TableView::TableView()
{

}

int TableView::getSizeCell()
{
    return 20;
}

int TableView::getTextSize()
{
    return getSizeCell() * 3 / 5;
}

ulong TableView::getBorderColor()
{
    return 0xFF000000;
}

ulong TableView::getCellColor(int x, int y)
{
    return 0xFF00FF00;
}

ulong TableView::getTextColor()
{
    return 0xFF0000FF;
}

int TableView::getCellsX()
{
    return 10;
}

int TableView::getCellsY()
{
    return 10;
}

bool TableView::isCellShowed(int x, int y)
{
    return !((y % 2) == 1 && x == getCellsX() - 1);
}

QString TableView::getCellText(int x, int y)
{
    return (x % 2) ?  "0.0" : "3";
}

#include "tableview.h"

TableView::TableView()
{

}

int TableView::getSizeCell()
{
    return 15;
}

int TableView::getTextSize()
{
    return 7;
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
    return 5;
}

int TableView::getCellsY()
{
    return 5;
}

bool TableView::isCellShowed(int x, int y)
{
    return true;
}

QString TableView::getCellText(int x, int y)
{
    return "QQ";
}

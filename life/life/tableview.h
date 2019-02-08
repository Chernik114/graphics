#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QtGlobal>
#include <QString>
#include <memory>

#include "animator.h"
#include "igameview.h"

class TableView
{
public:
    TableView(IGameView& view);

    int getSizeCell();
    int getTextSize();

    ulong getBorderColor();
    ulong getCellColor(int x, int y);
    ulong getTextColor();

    int getCellsX();
    int getCellsY();

    bool isCellShowed(int x, int y);
    QString getCellText(int x, int y);

    void setSizeCell(int s);
    void setBorderColor(ulong c);
    void setTextColor(ulong c);
    void setAnimInterval(int t);

    void mouseClick(int x, int y, IGameView::Mouse state);

private:
    ulong MathCellColor(int x, int y);
    Animator animator;

    Value<int> &sizeCell;
    Value<ulong> &borderColor, &textColor;
    Value<ulong> &deadColor, &aliveColor;

    std::vector<Value<ulong>*> cells;

    IGameView& view;
};

#endif // TABLEVIEW_H

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
    TableView(IGameView* view);

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

private:
    Animator animator;
    std::shared_ptr<Value<int>> sizeCell;
    std::shared_ptr<Value<ulong>> borderColor, textColor;
    std::shared_ptr<Value<ulong>> deadColor, aliveColor;

    IGameView* view;
};

#endif // TABLEVIEW_H

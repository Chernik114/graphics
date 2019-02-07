#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QtGlobal>
#include <QString>

class TableView
{
public:
    TableView();

    int getSizeCell();
    int getTextSize();

    ulong getBorderColor();
    ulong getCellColor(int x, int y);
    ulong getTextColor();

    int getCellsX();
    int getCellsY();

    bool isCellShowed(int x, int y);
    QString getCellText(int x, int y);

};

#endif // TABLEVIEW_H

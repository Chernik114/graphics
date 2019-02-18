#ifndef SETTINGSDRIVER_H
#define SETTINGSDRIVER_H

#include "gameview.h"
#include "tableview.h"
#include <QTimer>

class SettingsDriver
{
public:
    SettingsDriver(GameView &gv, TableView &tv, QTimer &tm);
    GameView &gv;
    TableView &tv;
    QTimer &tm;
};

#endif // SETTINGSDRIVER_H

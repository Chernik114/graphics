#ifndef IGAMEVIEW_H
#define IGAMEVIEW_H

#include <QString>
#include <QDebug>

class IGameView
{
public:
    enum State {
        NO_SHOWED,
        ALIVE,
        DEAD,
        NEW_ALIVE,
        NEW_DEAD
    };

    typedef uchar Mouse;

    enum MouseState {
        LEFT = 0x01,
        RIGHT = 0x02,
        NONE = 0x00,
        DOWN = 0x04,
        UP = 0x08,
        MOVE = 0x10
    };

    virtual int getCellsX() = 0;
    virtual int getCellsY() = 0;
    virtual QString getCellText(int, int) = 0;
    virtual State getCellState(int, int) = 0;
    virtual void mouseClick(int, int, Mouse) = 0;
    virtual void repaint() = 0;
    virtual ~IGameView(){}
};

#endif // IGAMEVIEW_H

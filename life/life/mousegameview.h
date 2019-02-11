#ifndef MOUSEGAMEVIEW_H
#define MOUSEGAMEVIEW_H

#include "gameview.h"

class MouseGameView : public GameView
{
public:
    enum FillState {
        REPLACE,
        XOR,
        NONE
    };

    MouseGameView();

    void mouseClick(int x, int y, IGameView::Mouse state);

    void setFillState(FillState state);
    FillState getFillState();

private:


    int lastX, lastY;
    FillState fillState;
    State lastState;
    MouseState mouseState;

};

#endif // MOUSEGAMEVIEW_H

#include "mousegameview.h"

MouseGameView::MouseGameView():
    fillState(REPLACE)
{

}

void MouseGameView::mouseClick(int x, int y, IGameView::Mouse state)
{
    if(state & UP){ // No capture up
        return;
    }
    if(fillState == NONE){
        return;
    }
    if(getCellState(x, y) == NO_SHOWED){ // Skip invalid
        return;
    }
    bool cell = isCellAlive(x, y);
    if(state & DOWN){ // Save state
        lastX = x;
        lastY = y;
        lastState = cell;
        mouseState = IGameView::NONE;
        if(state & LEFT){
            mouseState = LEFT;
        }
        if(state & RIGHT){
            mouseState = RIGHT;
        }
    }
    if(state == IGameView::MOVE){
        if(lastX == x && lastY == y){ // Do not repeat
            return;
        }
        lastX = x; // Resave
        lastY = y;
    }
    if(fillState == REPLACE){
        if(cell == (mouseState != LEFT)){
            setCellState(x, y, (mouseState == LEFT) ? ALIVE : DEAD);
            repaint();
        }
    }
    if(fillState == XOR){
        if(state == MOVE){
            if(cell != lastState){
                return;
            }
        }
        setCellState(x, y, cell ? DEAD : ALIVE);
        repaint();
    }
}

void MouseGameView::setFillState(MouseGameView::FillState state)
{
    fillState = state;
}

MouseGameView::FillState MouseGameView::getFillState()
{
    return fillState;
}

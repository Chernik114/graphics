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
    State cell = getCellState(x, y); // Get last state
    if(cell == NO_SHOWED){ // Skip invalid
        return;
    }
    if(cell == NEW_ALIVE){ // Normalize
        cell = ALIVE;
    }
    if(cell == NEW_DEAD){
        cell = DEAD;
    }
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
        if(cell == ((mouseState == LEFT) ? DEAD : ALIVE)){
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
        if(cell == DEAD){
            setCellState(x, y, ALIVE);
        } else {
            setCellState(x, y, DEAD);
        }
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

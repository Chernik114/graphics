#ifndef IGAMEVIEW_H
#define IGAMEVIEW_H

#include <QString>

class IGameView
{
public:
    enum State {
        NO_SHOWED,
        ALIVE,
        DEAD
    };

    virtual int getCellsX() = 0;
    virtual int getCellsY() = 0;
    virtual QString getCellText(int, int) = 0;
    virtual State getCellState(int, int) = 0;
    virtual ~IGameView(){}
};

class SimpleGameView : public IGameView {
public:
    int getCellsX(){
        return 10;
    }
    int getCellsY(){
        return 10;
    }
    QString getCellText(int x, int y){
        return (x % 2) ?  "0.0" : "3";
    }
    State getCellState(int x, int y){
        if((y % 2) == 1 && x == getCellsX() - 1){
            return NO_SHOWED;
        }
        return ALIVE;
    }
};

#endif // IGAMEVIEW_H

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
        DEAD
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

class SimpleGameView : public IGameView {
public:
    bool ss = false;
    std::function<void()> f = [](){};
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
        if(x == 0 && y == 0){
            return ss ? ALIVE : DEAD;
        }
        return ALIVE;
    }
    void mouseClick(int x, int y, Mouse state){
        if(x == 0 && y == 0){
            ss = !ss;
            repaint();
        }
        qDebug() << x << y;
        qDebug() << (state & LEFT) << (state & RIGHT) << (state & DOWN);
    }
    void repaint(){
        qDebug() << "REDRAW";
        f();
    }
};

#endif // IGAMEVIEW_H

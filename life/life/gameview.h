#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <cmath>

#include "igameview.h"

class GameView : public IGameView
{
public:
    enum GameState {
        NORMAL,
        TOROIDAL
    };

    GameView();

    int getCellsX();
    int getCellsY();
    QString getCellText(int x, int y);
    State getCellState(int x, int y);
    bool isCellAlive(int x, int y);
    void mouseClick(int, int, Mouse){}
    void repaint(){}

    void setFieldSize(int x, int y);
    void clear();
    void setCellState(int x, int y, State state);
    void setCellStates(std::vector<std::pair<int, int>>& coors, State state);

    void stepForward();
    void setGameState(GameState state);

private:
    inline double roundImpact(int x, int y);
    inline double getCellImpact(int x, int y);
    inline State& cellState(int x, int y);
    inline State roundState(int x, int y);
    inline State& cellState(std::vector<State> &cells, int x, int y, int xSize);
    inline bool isEdge(int x, int y);
    inline bool isEdge(int xSize, int x, int y);

    GameState gameState;
    int xSize, ySize;
    double fstImpact, sndImpact;
    double liveBegin, liveEnd;
    double birthBegin, birthEnd;
    std::vector<State> cells;
};

#endif // GAMEVIEW_H

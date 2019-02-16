#include "gameview.h"

GameView::GameView():
    gameState(NORMAL),
    xSize(15), ySize(14),
    fstImpact(1.0), sndImpact(0.3),
    liveBegin(2.0), liveEnd(3.3),
    birthBegin(2.3), birthEnd(2.9),
    cells(xSize * ySize)
{
    clear();
}

int GameView::getCellsX()
{
    return xSize;
}

int GameView::getCellsY()
{
    return ySize;
}

QString GameView::getCellText(int x, int y)
{
    int impact = round(getCellImpact(x, y) * 10);
    if((impact % 10) == 0){
        return QString("%1").arg(impact / 10);
    } else {
        return QString("%1").arg(0.1 * impact, 0, 'f', 1);
    }
}

IGameView::State GameView::getCellState(int x, int y)
{
    return cellState(x, y);
}

bool GameView::isCellAlive(int x, int y)
{
    State state = getCellState(x, y);
    return state == ALIVE || state == NEW_ALIVE;
}

void GameView::setFieldSize(int x, int y)
{
    if(x == xSize && y == ySize){
        return;
    }
    std::vector<State> nw(x * y);
    for(int xx = 0; xx < x; xx++){
        for(int yy = 0; yy < y; yy++){
            if(isEdge(x, xx, yy)){
                cellState(nw, xx, yy, x) = NO_SHOWED;
                continue;
            }
            if(xx >= xSize || yy >= ySize){
                cellState(nw, xx, yy, x) = DEAD;
                continue;
            }
            if(cellState(xx, yy) == NO_SHOWED){
                cellState(nw, xx, yy, x) = DEAD;
                continue;
            }
            cellState(nw, xx, yy, x) = cellState(xx, yy);
        }
    }
    xSize = x;
    ySize = y;
    cells = nw;
    repaint();
}

void GameView::clear()
{
    for(int x = 0; x < xSize; x++){
        for(int y = 0; y < ySize; y++){
            if(isEdge(x, y)){
                cellState(x, y) = NO_SHOWED;
                continue;
            }
            cellState(x, y) = DEAD;
        }
    }
    repaint();
}

void GameView::setCellState(int x, int y, IGameView::State state)
{
    if(cellState(x, y) == NO_SHOWED || state == cellState(x, y)){
        return;
    }
    cellState(x, y) = state;
    repaint();
}

void GameView::setCellStates(std::vector<std::pair<int, int> >& coors, IGameView::State state)
{
    for(auto &coor: coors){
        cellState(coor.first, coor.second) = state;
    }
    repaint();
}

void GameView::stepForward()
{
    bool isChanged = false;
    std::vector<State> news = cells;
    for(int x = 0; x < xSize; x++){
        for(int y = 0; y < ySize; y++){
            if(cellState(x, y) == NO_SHOWED){
                continue;
            }
            double impact = getCellImpact(x, y);
            State lastState = cellState(x, y);
            State newState = NO_SHOWED;
            if(impact < liveBegin || impact > liveEnd){
                newState = DEAD;
            }
            else if(impact >= birthBegin && impact <= birthEnd){
                newState = ALIVE;
            }
            if(lastState == DEAD && newState == ALIVE){
                newState = NEW_ALIVE;
            }
            if(lastState == NEW_ALIVE){
                if(newState == DEAD){
                    newState = NEW_DEAD;
                } else {
                    newState = ALIVE;
                }
            }
            if(lastState == ALIVE && newState == DEAD){
                newState = NEW_DEAD;
            }
            if(lastState == NEW_DEAD){
                if(newState == ALIVE){
                    newState = NEW_ALIVE;
                } else {
                    newState = DEAD;
                }
            }
            if(newState == NO_SHOWED){
                newState = lastState;
            }
            if(newState == lastState){
                continue;
            }
            cellState(news, x, y, xSize) = newState;
            isChanged = true;
        }
    }
    if(isChanged){
        cells = news;
        repaint();
    }
}

void GameView::setGameState(GameView::GameState state)
{
    if(state == gameState){
        return;
    }
    for(int y = 1; y < ySize; y += 2){
        if(state == NORMAL){
            cellState(xSize - 1, y) = NO_SHOWED;
        } else {
            cellState(xSize - 1, y) = DEAD;
        }
    }
    gameState = state;
    repaint();
}

double GameView::roundImpact(int x, int y)
{
    State s = roundState(x, y);
    if(s == ALIVE || s == NEW_ALIVE){
        return 1;
    }
    return 0;
}

double GameView::getCellImpact(int x, int y)
{
    if((y % 2) == 1){
        return fstImpact * (
                    roundImpact(x+1, y-1) + //
                    roundImpact(x+0, y-1) +
                    roundImpact(x-1, y+0) +
                    roundImpact(x+1, y+0) +
                    roundImpact(x+1, y+1) + //
                    roundImpact(x+0, y+1)
         ) + sndImpact * (
                    roundImpact(x+0, y-2) +
                    roundImpact(x+2, y-1) + //
                    roundImpact(x-1, y-1) + //
                    roundImpact(x+2, y+1) + //
                    roundImpact(x-1, y+1) + //
                    roundImpact(x+0, y+2)
        );
    } else {
        return fstImpact * (
                    roundImpact(x-1, y-1) +
                    roundImpact(x+0, y-1) +
                    roundImpact(x-1, y+0) +
                    roundImpact(x+1, y+0) +
                    roundImpact(x-1, y+1) +
                    roundImpact(x+0, y+1)
         ) + sndImpact * (
                    roundImpact(x+0, y-2) +
                    roundImpact(x-2, y-1) +
                    roundImpact(x+1, y-1) +
                    roundImpact(x-2, y+1) +
                    roundImpact(x+1, y+1) +
                    roundImpact(x+0, y+2)
        );
    }
}

IGameView::State &GameView::cellState(int x, int y)
{
    return cellState(cells, x, y, xSize);
}

IGameView::State GameView::roundState(int x, int y)
{
    if(x >= 0 && y >= 0 && x < xSize && y < ySize){
        return cellState(x, y);
    }
    if(gameState == NORMAL){
        return DEAD;
    }
    x %= xSize;
    if(x < 0){
        x += xSize;
    }
    y %= ySize;
    if(y < 0){
        y += ySize;
    }
    return cellState(x, y);
}

IGameView::State &GameView::cellState(std::vector<IGameView::State> &cells, int x, int y, int xSize)
{
    return cells[x + y * xSize];
}

bool GameView::isEdge(int x, int y)
{
    return isEdge(xSize, x, y);
}

bool GameView::isEdge(int xSize, int x, int y)
{
    return gameState == NORMAL && (y % 2) == 1 && x == xSize - 1;
}

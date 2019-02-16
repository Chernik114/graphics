#include "filedriver.h"

FileDriver::FileDriver(TableView &tv, GameView &gv):
    tv(tv),
    gv(gv)
{}

QTextStream &operator<<(QTextStream & s, FileDriver & fd)
{
    s << fd.tv.getSizeCell() << '\n';
    s << "1\n";
    std::vector<std::pair<int, int>> cells;
    for(int i = 0; i < fd.gv.getCellsX(); i++){
        for(int j = 0; j < fd.gv.getCellsY(); j++){
            auto cell = fd.gv.getCellState(i, j);
            if(cell == IGameView::ALIVE || cell == IGameView::NEW_ALIVE){
                cells.push_back({i, j});
            }
        }
    }
    s << cells.size() << '\n';
    for(auto &cell: cells){
        s << cell.first << ' ' << cell.second << '\n';
    }

}

QTextStream &operator>>(QTextStream &s, FileDriver &fd)
{
    int x, y;
    s >> x;
    s.readLine();
    s >> y;
    s.readLine();
    fd.tv.setSizeCell(x);
    auto size = 0ull;
    s >> size;
    s.readLine();
    fd.gv.clear();
    for(; size > 0; size--){
        s >> x >> y;
        s.readLine();
        fd.gv.setCellState(x, y, IGameView::ALIVE);
    }
}


#include "filedriver.h"

FileDriver::FileDriver(TableView &tv, GameView &gv):
    tv(tv),
    gv(gv)
{}

QTextStream &operator<<(QTextStream & s, FileDriver & fd)
{
    s << fd.gv.getCellsX() << ' ' << fd.gv.getCellsY() << '\n';
    s << "1\n";
    s << fd.tv.getSizeCell() << '\n';
    std::vector<std::pair<int, int>> cells;
    for(int i = 0; i < fd.gv.getCellsX(); i++){
        for(int j = 0; j < fd.gv.getCellsY(); j++){
            if(fd.gv.isCellAlive(i, j)){
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
    int x = 0, y = 0;
    s >> x >> y;
    s.readLine();
    fd.gv.setFieldSize(x, y);
    s >> x;
    s.readLine();
    s >> y;
    s.readLine();
    fd.tv.setSizeCell(y);
    auto size = 0ull;
    s >> size;
    s.readLine();
    fd.gv.clear();
    std::vector<std::pair<int, int>> coors(size);
    for(auto &coor: coors){
        s >> x >> y;
        s.readLine();
        coor = {x, y};
    }
    fd.gv.setCellStates(coors, IGameView::ALIVE);
}


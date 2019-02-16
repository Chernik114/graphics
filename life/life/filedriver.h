#ifndef FILEDRIVER_H
#define FILEDRIVER_H

#include <tableview.h>
#include <gameview.h>

#include <QTextStream>
#include <QTime>

class FileDriver
{
public:
    FileDriver(TableView& tv, GameView& gv);

private:
    friend QTextStream& operator<<(QTextStream&, FileDriver&);
    friend QTextStream& operator>>(QTextStream&, FileDriver&);

    TableView& tv;
    GameView& gv;
};

QTextStream& operator<<(QTextStream& s, FileDriver& fd);
QTextStream& operator>>(QTextStream& s, FileDriver& fd);

#endif // FILEDRIVER_H

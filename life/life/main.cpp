#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qDebug() << (-2 + 6 * 3) / 3 << -2 / 3 + 6;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

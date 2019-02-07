#ifndef PIXDRAWER_H
#define PIXDRAWER_H

#include <QWidget>
#include <QPainter>
#include <QImage>

class PixDrawer
{
public:
    PixDrawer(QWidget* w);

    void drawPaint(int x, int y, ulong color);

    virtual ~PixDrawer();

private:
    int w, h;
    QPainter p;
    QImage im;
    ulong* bits;

    inline ulong& ii(int x, int y);
};

#endif // PIXDRAWER_H

#ifndef PIXDRAWER_H
#define PIXDRAWER_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <algorithm>
#include <cmath>

class PixDrawer
{
public:
    PixDrawer(QWidget* widget);

    void drawPaint(int x, int y, ulong color);
    void drawLine(int x1, int y1, int x2, int y2, ulong color);
    void fillSpace(int x, int y, ulong color);
    void drawText(const QString& text, int x, int y, int s, ulong color);
    void clear();

    virtual ~PixDrawer();

private:

    typedef struct {
        int l, r, y;
    } Span;

    int w, h;
    QPainter p;
    QImage im;
    ulong* bits;

    inline ulong& ii(int x, int y);
};

#endif // PIXDRAWER_H

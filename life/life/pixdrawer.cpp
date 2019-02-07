#include "pixdrawer.h"

PixDrawer::PixDrawer(QWidget* widget):
    w(widget->width()),
    h(widget->height()),
    p(widget),
    im(w, h, QImage::Format_ARGB32),
    bits(reinterpret_cast<ulong*>(im.bits()))
{

}

void PixDrawer::drawPaint(int x, int y, ulong color)
{
    this->ii(x, y) = color;
}

PixDrawer::~PixDrawer()
{
    p.drawImage(0, 0, im);
    p.end();
}

ulong &PixDrawer::ii(int x, int y)
{
    return bits[x + y * w];
}

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

void PixDrawer::drawLine(int x1, int y1, int x2, int y2, ulong color)
{
    if(x2 < x1){
        drawLine(x2, y2, x1, y1, color);
        return;
    }
    if((y2 - y1) <= (x2 - x1)){
        double k = 1.0 * (y2 - y1) / (x2 - x1);
        for(int i = 0; i < x2 - x1; i++){
            int v = static_cast<int>(round(k * (x1 + i) + y1)); // TODO: normalize round
            ii(i, v) = color;
        }
    } else {
        double k = 1.0 * (x2 - x1) / (y2 - y1);
        for(int i = 0; i < y2 - y1; i++){
            int v = static_cast<int>(round(k * (y1 + i) + x1)); // TODO: normalize round
            ii(v, i) = color;
        }
    }
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

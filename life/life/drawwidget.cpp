#include "drawwidget.h"

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{

}

void DrawWidget::setSize(const QSize &s)
{
    setMaximumSize(s);
    setMinimumSize(s);
}

void DrawWidget::paintEvent(QPaintEvent *)
{
    PixDrawer drw(this);
    drw.clear();
    int w = width() / 2;
    int h = height();

    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            drw.drawPaint(i, j, (i * i + j * j < w * w) ? 0xFF00FF00 : 0x00000000);
        }
    }

    for(int i = 0; i < h; i += 10){
        drw.drawLine(0, 0, w - 1, i, 0xFF0000FF);
    }
    for(int i = 0; i < w; i += 10){
        drw.drawLine(i, h - 1, 0, 0, 0xFF0000FF);
    }

    drw.fillSpace(w - 15, h - 1, 0xFFFF0000);
}

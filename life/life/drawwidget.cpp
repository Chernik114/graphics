#include "drawwidget.h"

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{

}

void DrawWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QImage im(width(), height(), QImage::Format_ARGB32);
    uchar* bits = im.bits();
    int w = width();
    int h = height();
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            for(int k = 0; k < 4; k++){
                bits[k + i * 4 + j * 4 * w] =
                        (i * i + j * j < w * w) ? 0xFF : 0x00;
            }
        }
    }
    p.drawImage(0, 0, im);
    p.end();
}

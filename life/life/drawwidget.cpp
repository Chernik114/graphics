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
    int w = width() / 4;
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

    drw.fillSpace(35, h - 1, 0xFFFF0000);

    RegPolygon pg;
    pg
            .setOuterRadius(10)
            .setLineDrawer([&](double x1, double y1, double x2, double y2){
                drw.drawLine(x1, y1, x2, y2, 0xFF0000FF);
            });
    for(int i = 0; i < 9; i++){
        pg
                .setAmountSides(i + 3)
                .setCenter(w + 10 + i * 22, 20)
                .draw();

        drw.drawText("O", w + 10 + i * 22, 20, 7, 0xFF000000);
        drw.fillSpace(w + 10 + i * 22, 20, 0xFFFFFF00);
    }
}

void DrawWidget::mousePressEvent(QMouseEvent *e)
{
    RegPolygon pg;
    pg
            .setOuterRadius(10);
    for(int i = 0; i < 9; i++){
        pg
                .setAmountSides(i + 3)
                .setCenter(width() / 4 + 10 + i * 22, 20);
        qDebug() << "CLICK";
        int xx = e->x();
        int yy = e->y();
        if(pg.isContains(xx, yy)){
            qDebug() << i;
        }
    }
}

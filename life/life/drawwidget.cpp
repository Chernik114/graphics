#include "drawwidget.h"

DrawWidget::DrawWidget(QWidget *parent) :
    QWidget(parent),
    hs(nullptr)
{

}

void DrawWidget::setSize(const QSize &s)
{
    setMaximumSize(s);
    setMinimumSize(s);
}

void DrawWidget::setIView(IGameView *view)
{
    hs = std::make_shared<Hexagons>(view);
}

void DrawWidget::paintEvent(QPaintEvent *)
{
    PixDrawer drw(this);
    hs->draw(drw);
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

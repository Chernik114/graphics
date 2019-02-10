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

void DrawWidget::setIView(IGameView &view)
{
    hs = std::make_shared<Hexagons>(view);
}

TableView &DrawWidget::getTableView()
{
    return hs->view;
}

void DrawWidget::paintEvent(QPaintEvent *)
{
    QSize s = size();
    int sx = s.width(), sy = s.height();
    int rx = hs->getSizeX(), ry = hs->getSizeY();
    while(sx < rx) sx += 20;
    while(sx > rx + 20) sx -= 20;
    while(sy < ry) sy += 20;
    while(sy > ry + 20) sy -= 20;
    if(s.width() != sx || s.height() != sy){
        setSize(QSize(sx, sy));
    }
    PixDrawer drw(this);
    hs->draw(drw);
}

void DrawWidget::mousePressEvent(QMouseEvent *e)
{
    hs->mouseClick(e->x(), e->y(), parseEvent(e) | IGameView::DOWN);
}

IGameView::Mouse DrawWidget::parseEvent(QMouseEvent *e)
{
    IGameView::Mouse state = IGameView::NONE;
    if(e->button() == Qt::MouseButton::LeftButton){
        state |= IGameView::LEFT;
    }
    if(e->button() == Qt::MouseButton::RightButton){
        state |= IGameView::RIGHT;
    }
    return state;
}

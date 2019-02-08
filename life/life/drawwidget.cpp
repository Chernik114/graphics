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
    ((SimpleGameView&)view).f = [=](){
        this->repaint();
    };
}

void DrawWidget::paintEvent(QPaintEvent *)
{
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

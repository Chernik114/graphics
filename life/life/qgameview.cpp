#include "qgameview.h"

QGameView::HView::HView(QGameView &view):
    view(view)
{

}

void QGameView::HView::repaint()
{
    view.repaint();
}


QGameView::QGameView():
    view(*this)
{

}

MouseGameView &QGameView::v()
{
    return view;
}

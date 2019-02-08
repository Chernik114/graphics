#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <memory>

#include "pixdrawer.h"
#include "regpolygon.h"
#include "hexagons.h"

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = nullptr);
    void setSize(const QSize& s);
    void setIView(IGameView& view);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* e);

private:
    IGameView::Mouse parseEvent(QMouseEvent* e);
    std::shared_ptr<Hexagons> hs;
};

#endif // DRAWWIDGET_H

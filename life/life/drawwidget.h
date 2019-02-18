#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <memory>
#include <QTime>

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
    TableView& getTableView();

signals:
    void click();

public slots:

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

private:
    IGameView::Mouse parseEvent(QMouseEvent* e);
    std::shared_ptr<Hexagons> hs;
};

#endif // DRAWWIDGET_H

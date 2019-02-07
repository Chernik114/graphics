#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

#include "pixdrawer.h"
#include "regpolygon.h"
#include "hexagons.h"

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = nullptr);
    void setSize(const QSize& s);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* e);

private:
    Hexagons hs;
};

#endif // DRAWWIDGET_H

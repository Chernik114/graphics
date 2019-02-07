#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QPainter>

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = nullptr);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent*);
};

#endif // DRAWWIDGET_H

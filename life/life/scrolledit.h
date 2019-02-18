#ifndef SCROLLEDIT_H
#define SCROLLEDIT_H

#include <QLineEdit>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QPainter>

class ScrollEdit : public QLineEdit
{
public:
    ScrollEdit(QWidget* parent);

    void setMinimum(double v);
    void setMaximum(double v);
    void setPosition(double v);

    void setBgColor(QColor c);
    QColor getBgColor();
    void setProgressColor(QColor c);
    QColor getProgressColor();
    void setPrec(int prec);
    int getPrec();
    double getValue();
    void setKoef(double koef);
    double getKoef();
    void setRange(double min, double max);

signals:
    void changeValue(double);

protected:
    void paintEvent(QPaintEvent* e);
    void keyPressEvent(QKeyEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

private:
    inline void retext();

    double min, max, pos, koef; // Value
    QColor bgColor, progressColor;
    int lastX, lastY;
    bool isMouse;
    int prec;
};

#endif // SCROLLEDIT_H

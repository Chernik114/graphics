#ifndef QGAMEVIEW_H
#define QGAMEVIEW_H

#include <mousegameview.h>
#include <QObject>

class QGameView : public QObject
{
    Q_OBJECT
private:
    class HView : public MouseGameView {
    private:
        QGameView& view;
    public:
        HView(QGameView& view);
        void repaint();
    };

    HView view;
public:
    QGameView();
    MouseGameView& v();

signals:
    void repaint();
};

#endif // QGAMEVIEW_H

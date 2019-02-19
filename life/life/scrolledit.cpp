#include "scrolledit.h"

ScrollEdit::ScrollEdit(QWidget *parent):
    QLineEdit (parent),
    min(0), max(1), pos(0.5), koef(0.01),
    bgColor(0xFFFFFFFF), progressColor(0xFFFFBBBB),
    isMouse(false),
    prec(3)
{
    setStyleSheet("*{background-color: rgba(0,0,0,0)}");
    retext();
}

void ScrollEdit::setMinimum(double v)
{
    if(v > max){
        setMaximum(v);
    } else {
        min = v;
        if(v < min){
            v = min;
        }
        retext();
    }
}

void ScrollEdit::setMaximum(double v)
{
    if(v < min){
        setMinimum(v);
    } else {
        max = v;
        if(v > max){
            v = max;
        }
        retext();
    }
}

void ScrollEdit::setPosition(double v)
{
    if(v < min){
        min = v;
    }
    if(v > max){
        max = v;
    }
    pos = v;
    retext();
}

void ScrollEdit::setBgColor(QColor c)
{
    bgColor = c;
    repaint();
}

QColor ScrollEdit::getBgColor()
{
    return bgColor;
}

void ScrollEdit::setProgressColor(QColor c)
{
    progressColor = c;
    repaint();
}

QColor ScrollEdit::getProgressColor()
{
    return progressColor;
}

void ScrollEdit::setPrec(int prec)
{
    if(prec < 0){
        return;
    }
    this->prec = prec;
    retext();
}

int ScrollEdit::getPrec()
{
    return prec;
}

double ScrollEdit::getValue()
{
    return pos;
}

void ScrollEdit::setKoef(double koef)
{
    this->koef = koef;
    retext();
}

double ScrollEdit::getKoef()
{
    return koef;
}

void ScrollEdit::setRange(double min, double max)
{
    if(min > max){
        double a = min;
        min = max;
        max = a;
    }
    this->min = min;
    this->max = max;
    retext();
}

void ScrollEdit::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    QPainterPath path;
    double k = (pos - min) / (max - min);
    path.addRect(0, 0, k * width(), height());
    p.fillPath(path, progressColor);
    path = QPainterPath();
    path.addRect(k * width(), 0, width(), height());
    p.fillPath(path, bgColor);
    p.end();
    QLineEdit::paintEvent(e);
}

void ScrollEdit::keyPressEvent(QKeyEvent *e){
    if(!((e->key() >= Qt::Key_0 && e->key() <= Qt::Key_9) || e->key() == Qt::Key_Period || e->key() == Qt::Key_Delete || e->key() == Qt::Key_Backspace)){
        return;
    }
    QString oldTxt = text();
    QLineEdit::keyPressEvent(e);
    QString newTxt = text();
    if(newTxt == ""){
        return;
    }
    bool ok;
    double val = newTxt.toDouble(&ok);
    if(!ok || val < min || val > max){
        if(val < min){
            return;
        }
        setText(oldTxt);
        return;
    }
    pos = val;
    repaint();
    changeValue(pos);
}

void ScrollEdit::mousePressEvent(QMouseEvent *e)
{
    isMouse = true;
    lastX = e->x();
    lastY = e->y();
    QLineEdit::mousePressEvent(e);
}

void ScrollEdit::mouseMoveEvent(QMouseEvent *e)
{
    if(isMouse){
        double val = (e->x() - lastX) * koef * (max - min);
        val += pos;
        if(val < min){
            val = min;
        }
        if(val > max){
            val = max;
        }
        pos = val;
        lastX = e->x();
        lastY = e->y();
        retext();
        changeValue(pos);
    }
    QLineEdit::mouseMoveEvent(e);
}

void ScrollEdit::mouseReleaseEvent(QMouseEvent *e)
{
    isMouse = false;
    QLineEdit::mouseReleaseEvent(e);
}

void ScrollEdit::retext()
{
    setText(QString("%1").arg(pos, 0, 'f', prec));
}

void ScrollEdit::changeValue(double){};

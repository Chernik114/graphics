#include "pixdrawer.h"

PixDrawer::PixDrawer(QWidget* widget):
    w(widget->width()),
    h(widget->height()),
    p(widget),
    pbuf(nullptr),
    im(w, h, QImage::Format_ARGB32),
    bits(reinterpret_cast<ulong*>(im.bits()))
{
    clear();
}

void PixDrawer::drawPaint(int x, int y, ulong color)
{
    finishBufP();
    this->ii(x, y) = color;
}

void PixDrawer::drawLine(int x1, int y1, int x2, int y2, ulong color)
{
    finishBufP();
    if(std::abs(y2 - y1) <= std::abs(x2 - x1)){ // horisontal
        if(x1 == x2){
            ii(x1, y1) = color;
            return;
        }
        if(x1 > x2){ // order for X
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        int dx = x2 - x1, dy = y2 - y1;
        for(int i = x1; i <= x2; i++){
            int m = (i - x1) * dy;
            int err = m % dx;
            m = (m + y1 * dx) / dx;
            if(err < 0){
                err += dx;
            }
            if(err >= dx / 2){
                m++;
            }
            ii(i, m) = color;
        }
    } else { // vertical
        if(y1 > y2){ // order for Y
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        int dx = x2 - x1, dy = y2 - y1;
        for(int i = y1; i <= y2; i++){
            int m = (i - y1) * dx;
            int err = m % dy;
            m = (m + x1 * dy) / dy;
            if(err < 0){
                err += dx;
            }
            if(err >= dy / 2){
                m++;
            }
            ii(m, i) = color;
        }
    }
}

void PixDrawer::fillSpace(int x, int y, ulong color)
{
    finishBufP();
    ulong old = ii(x, y);
    if(old == color){
        return;
    }
    std::vector<Span> stack; // # TODO: stack?
    int l, r;
    for(l = x; l >= 0 && ii(l, y) == old; l--); // find left edge
    for(r = x; r <  w && ii(r, y) == old; r++); // find right edge
    stack.push_back({l + 1, r - 1, y}); // push
    l = r = -1;
    while(stack.size() > 0){
        Span cur = stack.back(); // pop
        stack.pop_back();
        for(int i = cur.l; i <= cur.r; i++){ // run
            ii(i, cur.y) = color; // fill
            if(cur.y > 0){ // upper line exist
                if(l < 0 && ii(i, cur.y - 1) == old){ // start upper span
                    l = i; // save pos
                    if(i == cur.l){ // expand left edge
                        for(; l >= 0 && ii(l, cur.y - 1) == old; l--);
                        l++;
                    }
                }
                if(l >= 0 && ii(i, cur.y - 1) != old){ // stop upper span
                    stack.push_back({l, i - 1, cur.y - 1}); // push
                    l = -1; // reset pos
                }
            }
            if(cur.y < h - 1){ // lower line exist
                if(r < 0 && ii(i, cur.y + 1) == old){ // start lower span
                    r = i; // save pos
                    if(i == cur.l){ // expand left edge
                        for(; r >= 0 && ii(r, cur.y + 1) == old; r--);
                        r++;
                    }
                }
                if(r >= 0 && ii(i, cur.y + 1) != old){ // stop lower span
                    stack.push_back({r, i - 1, cur.y + 1}); // push
                    r = -1; // reset pos
                }
            }
        }
        if(l >= 0){ // unclosed upper span
            int i;
            for(i = cur.r + 1; i < w && ii(i, cur.y - 1) == old; i++); // expand right edge
            stack.push_back({l, i - 1, cur.y - 1}); // push
            l = -1;
        }
        if(r >= 0){ // unclosed lower span
            int i;
            for(i = cur.r + 1; i < w && ii(i, cur.y + 1) == old; i++); // expand right edge
            stack.push_back({r, i - 1, cur.y + 1}); // push
            r = -1;
        }
    }
}

void PixDrawer::drawText(const QString& text, int x, int y, int s, ulong color)
{
    QPainter &p = startBufP();
    p.setPen(QColor(
                 (color >> 16) & 0xFF,
                 (color >>  8) & 0xFF,
                 (color >>  0) & 0xFF,
                 (color >> 24) & 0xFF
    ));
    p.setFont(QFont("Times", s, QFont::Bold));
    p.drawText(x - text.size() * s + 2, y - s, text.size() * 2 * s, 2 * s, Qt::AlignCenter | Qt::AlignHCenter, text);
}

void PixDrawer::clear()
{
    finishBufP();
    std::fill(bits, bits + w * h, 0);
}

PixDrawer::~PixDrawer()
{
    finishBufP();
    p.drawImage(0, 0, im);
    p.end();
}

ulong &PixDrawer::ii(int x, int y)
{
    return bits[x + y * w];
}

QPainter &PixDrawer::startBufP()
{
    if(pbuf == nullptr){
        pbuf = new QPainter();
        pbuf->begin(&im);
    }
    return *pbuf;
}

void PixDrawer::finishBufP()
{
    if(pbuf == nullptr){
        return;
    }
    pbuf->end();
    delete pbuf;
    pbuf = nullptr;
    return;
}

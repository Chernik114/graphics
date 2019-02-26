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
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    if(dy <= dx){ // horisontal
        if(x1 == x2){
            ii(x1, y1) = color;
            return;
        }
        if(x1 > x2){ // order for X
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        int err = 0, y = y1, sy = y2 - y1;
        if(sy < 0){
            sy = -w;
        }
        if(sy > 0){
            sy = w;
        }
        ulong *px = &ii(x1, y);
        for(int x = x1; x <= x2; x++){
            *px++ = color;
            err += dy;
            if(err + err >= dx){
                px += sy;
                err -= dx;
            }
        }
    } else { // vertical
        if(y1 > y2){ // order for Y
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        int err = 0, x = x1, sx = x2 - x1;
        if(sx < 0){
            sx = -1;
        }
        if(sx > 0){
            sx = 1;
        }
        ulong *px = &ii(x, y1);
        for(int y = y1; y <= y2; y++){
            *px = color;
            px += w;
            err += dx;
            if(err + err >= dy){
                px += sx;
                err -= dy;
            }
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
        ulong *pm = &ii(cur.l, cur.y);
        ulong *pu = pm - w;
        ulong *pd = pm + w;
        for(int i = cur.l; i <= cur.r; i++){ // run
            *pm = color; // fill
            if(cur.y > 0){ // upper line exist
                if(l < 0 && *pu == old){ // start upper span
                    l = i; // save pos
                    if(i == cur.l){ // expand left edge
                        ulong *pb = pu;
                        for(; l >= 0 && *pb == old; l--, pb--);
                        l++;
                    }
                }
                if(l >= 0 && *pu != old){ // stop upper span
                    stack.push_back({l, i - 1, cur.y - 1}); // push
                    l = -1; // reset pos
                }
            }
            if(cur.y < h - 1){ // lower line exist
                if(r < 0 && *pd == old){ // start lower span
                    r = i; // save pos
                    if(i == cur.l){ // expand left edge
                        ulong *pb = pd;
                        for(; r >= 0 && *pb == old; r--, pb--);
                        r++;
                    }
                }
                if(r >= 0 && *pd != old){ // stop lower span
                    stack.push_back({r, i - 1, cur.y + 1}); // push
                    r = -1; // reset pos
                }
            }
            pm++; pu++; pd++;
        }
        if(l >= 0){ // unclosed upper span
            int i;
            ulong *pb = &ii(cur.r + 1, cur.y - 1);
            for(i = cur.r + 1; i < w && *pb == old; i++, pb++); // expand right edge
            stack.push_back({l, i - 1, cur.y - 1}); // push
            l = -1;
        }
        if(r >= 0){ // unclosed lower span
            int i;
            ulong *pb = &ii(cur.r + 1, cur.y + 1);
            for(i = cur.r + 1; i < w && *pb == old; i++, pb++); // expand right edge
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

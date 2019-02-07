#include "pixdrawer.h"

PixDrawer::PixDrawer(QWidget* widget):
    w(widget->width()),
    h(widget->height()),
    p(widget),
    im(w, h, QImage::Format_ARGB32),
    bits(reinterpret_cast<ulong*>(im.bits()))
{}

void PixDrawer::drawPaint(int x, int y, ulong color)
{
    this->ii(x, y) = color;
}

void PixDrawer::drawLine(int x1, int y1, int x2, int y2, ulong color)
{
    if(std::abs(y2 - y1) <= std::abs(x2 - x1)){ // horisontal
        if(x1 > x2){ // order for X
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        double k = 1.0 * (y2 - y1) / (x2 - x1); // straight K
        for(int i = 0; i <= x2 - x1; i++){ // for X pixels
            int v = static_cast<int>(round(k * (x1 + i) + y1)); // nearest Y
            ii(i, v) = color; // draw
        }
    } else { // vertical
        if(y1 > y2){ // order for Y
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        double k = 1.0 * (x2 - x1) / (y2 - y1); // straight K
        for(int i = 0; i <= y2 - y1; i++){ // for Y pixels
            int v = static_cast<int>(round(k * (y1 + i) + x1)); // nearest X
            ii(v, i) = color; // draw
        }
    }
}

void PixDrawer::fillSpace(int x, int y, ulong color)
{
    ulong old = ii(x, y);
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

PixDrawer::~PixDrawer()
{
    p.drawImage(0, 0, im);
    p.end();
}

ulong &PixDrawer::ii(int x, int y)
{
    return bits[x + y * w];
}

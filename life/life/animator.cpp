#include "animator.h"

void Animator::TimValue::valueToAnim(TimValue &v, Animator &animator)
{
    animator.values.push_back(&v);
    if(!animator.isActive()){
        animator.start();
    }
}

Animator::Animator():
    Animator([](){})
{}

Animator::Animator(std::function<void ()> onTimer):
    msAnim(100),
    onTimer(onTimer)
{
    setInterval(20);
}

Animator::ARGBValue *Animator::createARGBValue(const ulong &v)
{
    ARGBValue* res = new ARGBValue(*this, v);
    all.push_back(res);
    return res;
}

void Animator::setMsAnimation(int ms)
{
    msAnim = ms;
}

int Animator::getMsAnimation()
{
    return msAnim;
}

Animator::~Animator()
{
    for(auto i = 0ull; i < all.size(); i++){
        delete all[i];
    }
}

void Animator::timerEvent(QTimerEvent *)
{
    if(values.size() == 0){
        this->stop();
    }
    std::vector<TimValue*> ge;
    for(auto i = 0ull; i < values.size(); i++){
        if(!values[i]->onTimer()){
            ge.push_back(values[i]);
        }
    }
    values = ge;
    onTimer();
}

ulong Animator::ARGBValue::g()
{
    return
            ((0ul + A.g()) << 24) |
            ((0ul + R.g()) << 16) |
            ((0ul + G.g()) <<  8) |
            ((0ul + B.g()) <<  0);
}

void Animator::ARGBValue::s(const ulong &v)
{
    A.s((v >> 24) & 0xFF);
    R.s((v >> 16) & 0xFF);
    G.s((v >>  8) & 0xFF);
    B.s((v >>  0) & 0xFF);
}

Animator::ARGBValue::ARGBValue(Animator &animator, const ulong &v):
    Value<ulong> (animator, 0),
    A(animator, (v >> 24) & 0xFF),
    R(animator, (v >> 16) & 0xFF),
    G(animator, (v >> 8) & 0xFF),
    B(animator, (v >> 0) & 0xFF)
{}


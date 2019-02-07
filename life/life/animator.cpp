#include "animator.h"

void Animator::TimValue::addValue(Animator::TimValue &v, Animator &animator)
{
    animator.values.push_back(&v);
}

template<typename T>
T Animator::Value<T>::g()
{
    return cur;
}

template<typename T>
void Animator::Value<T>::s(const T &v)
{
    aim = v;
    msLeft = msFull;
    if(!isAnimNow){
        isAnimNow = true;
        addValue(*this, animator);
    }
}

template<typename T>
Animator::Value<T>::Value(Animator &animator, const T &v):
    animator(animator),
    cur(v), aim(v),
    msLeft(0), msFull(animator.msAnim),
    isAnimNow(false)
{}

template<typename T>
bool Animator::Value<T>::onTimer()
{
    // TODO: done that
    return true;
}

Animator::Animator():
    msAnim(50)
{}

void Animator::setMsAnimation(int ms)
{
    msAnim = ms;
}

int Animator::getMsAnimation()
{
    return msAnim;
}

void Animator::timerEvent(QTimerEvent *)
{
    if(values.size() == 0){
        this->stop();
    }
    std::vector<TimValue*> ge;
    for(unsigned long long i = 0; i < values.size(); i++){
        if(!values[i]->onTimer()){
            ge.push_back(values[i]);
        }
    }
    values = ge;
}

template<typename T>
Animator::Value<T> Animator::createValue(const T &v)
{
    return Value<T>(*this, v);
}

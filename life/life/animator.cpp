#include "animator.h"

void Animator::TimValue::addValue(Animator::TimValue &v, Animator &animator)
{
    animator.values.push_back(&v);
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

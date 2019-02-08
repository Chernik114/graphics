#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <QTimer>
#include <memory>

template <class T>
class Value { // Usable interface
public:
    virtual T g() = 0; // Get value
    virtual void s(const T&) = 0; // Set value
};

class Animator : public QTimer
{
    Q_OBJECT
private:
    class TimValue { // Interface for vector<>
    public:
        virtual bool onTimer() = 0; // Time event, true if end enimation
        virtual ~TimValue(){} // TODO: need realization))

        static void addValue(TimValue& v, Animator& animator); // Start animation
    };
    friend class TimValue; // For addValue

public:
    template <class T>
    class Value : public ::Value<T>, private TimValue { // Animated value
    public:
        Value(Animator& animator, T v):
            animator(animator),
            cur(v), aim(v),
            msLeft(0), msFull(animator.msAnim),
            isAnimNow(false)
        {}

        T g() {
            return cur;
        }

        void s(const T& v){
            aim = v;
            msLeft = msFull;
            if(!isAnimNow){
                isAnimNow = true;
                addValue(*this, animator);
            }
        }

    private:
        bool onTimer(){
            // TODO: done that
            return true;
        }

        Animator& animator;
        T cur, aim;
        int msLeft, msFull;
        bool isAnimNow;
    };

    Animator();

    template <class T> Value<T> createValue(const T& v){
        return Value<T>(*this, v);
    }

    void setMsAnimation(int ms);
    int getMsAnimation();

protected:
    void timerEvent(QTimerEvent*);

private:
    std::vector<TimValue*> values;
    int msAnim;
};

#endif // ANIMATOR_H

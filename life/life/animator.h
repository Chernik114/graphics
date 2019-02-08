#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <QTimer>
#include <functional>
#include <QDebug>

// ------------------------- Base interface for parameters
template <class T>
class Value { // Usable interface
public:
    virtual T g() = 0; // Get value
    virtual void s(const T&) = 0; // Set value
    virtual ~Value(){}
};

// --------------------------------- Animator
class Animator : public QTimer
{
    Q_OBJECT
private:

    // ------------------------------------- Interface with timer event and callback
    class TimValue { // Interface for vector<>
    public:
        virtual bool onTimer() = 0; // Time event, true if end enimation
        virtual ~TimValue(){}

        static void valueToAnim(TimValue& v, Animator& animator); // On start animation
    };
    friend class TimValue; // For onSetValue

public:

    // ---------------------- Universal animated value
    template <class T>
    class Value : public ::Value<T>, private TimValue {
    public:
        T g() { // Getter
            return cur;
        }
        void s(const T& v){ // Setter
            if(v == aim){
                return;
            }
            aim = v;
            msLeft = msFull;
            if(!isAnimNow){
                isAnimNow = true;
                valueToAnim(*this, animator);
            }
        }
    protected:
        bool onTimer() { // On timer event
            qDebug() << "TIMER";
            cur = aim;
            isAnimNow = false;
            return true;
        }
        Animator& animator; // Loopback
        bool isAnimNow; // We animated now
        int msLeft, msFull;
        T cur, aim;
    private:
        Value(Animator& animator, T v):
            animator(animator),
            isAnimNow(false),
            msLeft(0), msFull(animator.msAnim),
            cur(v), aim(v)
        {}
        friend class Animator; // For constructor
    };

    // ---------------------------------- For ARGB color animation
    class ARGBValue : public Value<ulong> {
    public:
        ulong g();
        void s(const ulong& v);
    private:
        ARGBValue(Animator& animator, const ulong& v);
        Value<uchar> A, R, G, B;
        friend class Animator;
    };

    Animator();
    Animator(std::function<void()> onTimer);

    // -------------------------------------------- Fabrics
    template <class T> ::Value<T>* createValue(const T& v){
        Value<T> *res = new Value<T>(*this, v);
        all.push_back(res);
        return res;
    }
    ARGBValue* createARGBValue(const ulong& v);

    void setMsAnimation(int ms);
    int getMsAnimation();

    virtual ~Animator();

protected:
    void timerEvent(QTimerEvent*);

private:
    std::vector<TimValue*> values, all;
    int msAnim;
    std::function<void()> onTimer;
};

#endif // ANIMATOR_H

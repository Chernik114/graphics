#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <QTimer>

template <typename T>
class Value { // Usable interface
public:
    virtual T g(); // Get value
    virtual void s(const T&); // Set value
};

class Animator : public QTimer
{
    Q_OBJECT
private:
    class TimValue { // Interface for vector<>
    public:
        virtual bool onTimer(); // Time event, true if end enimation
        virtual ~TimValue();

        static void addValue(TimValue& v, Animator& animator); // Start animation
    };
    friend class TimValue; // For addValue

public:
    template <typename T>
    class Value : public ::Value<T>, private TimValue { // Animated value
    public:
        T g();
        void s(const T& v);

    private:
        friend class Animator; // For constructor

        Value(Animator& animator, const T& v);
        bool onTimer();

        Animator& animator;
        T cur, aim;
        int msLeft, msFull;
        bool isAnimNow;
    };

    Animator();
    template <typename T> Value<T> createValue(const T& v);
    void setMsAnimation(int ms);
    int getMsAnimation();

protected:
    void timerEvent(QTimerEvent*);

private:
    std::vector<TimValue*> values;
    int msAnim;
};

#endif // ANIMATOR_H

#ifndef TIMER_H
#define TIMER_H

#include <QtWidgets>

class Timer : public QGraphicsObject
{
    Q_OBJECT
public:
    Timer(int s);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void stop(bool st);
    void reset();
    int getTime();

private:
    int size;
    int seconds;
    bool stopped;

public slots:
    void run();
};

#endif // TIMER_H

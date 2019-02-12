#include "timer.h"

Timer::Timer(int s) : QGraphicsObject(), size(s), seconds(0), stopped(true)
{}

QRectF Timer::boundingRect() const
{
    return QRect(0, 0, size*4, size);
}

void Timer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::darkRed, 3));
    painter->drawRect(boundingRect());
    painter->setFont(QFont("Times", static_cast<int>(size/1.7), QFont::Normal));
    QString time;
    time += QString::number(seconds/360000);
    time += QString::number((seconds/36000)%10);
    time += ":";
    time += QString::number(((seconds/600)%60)/10);
    time += QString::number((seconds/600)%10);
    time += ":";
    time += QString::number(((seconds/10)%60)/10);
    time += QString::number((seconds/10)%10);
    painter->drawText(boundingRect(), Qt::AlignCenter, time);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Timer::run()
{
    seconds++;
    update(boundingRect());
    if(!stopped)
        QTimer::singleShot(100, this, SLOT(run()));
}

void Timer::stop(bool st)
{
    stopped = st;
}

void Timer::reset()
{
    seconds = 0;
    update(boundingRect());
}

int Timer::getTime()
{
    return seconds/10;
}

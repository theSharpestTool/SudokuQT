#ifndef CIRCLE_H
#define CIRCLE_H

#include <QtWidgets>
#include "cell.h"

class Circle : public Cell
{
public:
    Circle(int s);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CIRCLE_H

#include "circle.h"
#include "widget.h"

extern Widget* widget;

Circle::Circle(int s) : Cell(s)
{}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::white, 0));
    painter->setBrush(QBrush(Qt::darkRed));
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawEllipse(boundingRect());
    painter->setFont(QFont("Times", size/2.5, QFont::Normal));
    painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(value));
    setOpacity(0.85);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Circle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   widget->writeValue(value);
   Q_UNUSED(event);
}

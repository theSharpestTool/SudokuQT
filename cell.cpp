#include "cell.h"
#include "widget.h"
#include <QDebug>

extern Widget* widget;

Cell::Cell(int s) : QGraphicsItem(), value(0), size(s), editable(true), red(false)
{}

QRectF Cell::boundingRect() const
{
    return QRect(0, 0, size, size);
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 1));
    if(red)
        painter->setBrush(QBrush(Qt::darkRed));

    painter->drawRect(boundingRect());

    if (value != 0)
    {
        if(editable)
            painter->setPen(QPen(Qt::darkRed, 1));
        painter->setFont(QFont("Times", size/2.5, QFont::Normal));
        painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(value));
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!widget->variantsAreShown() && editable)
    {
        if(value == 0)
            widget->showVariants(scenePos());
        else
            setValue(0);
    }
    else if(widget->variantsAreShown())
        widget->moveBack();
    Q_UNUSED(event);
}

void Cell::setValue(int n)
{
    value = n;
    update(boundingRect());
}

int Cell::getValue()
{
    return value;
}

void Cell::setEditable(bool condition)
{
    editable = condition;
}

bool Cell::isEditable()
{
    return editable;
}

int Cell::getSize()
{
    return size;
}

void Cell::setRed()
{
    if(red == true)
        red = false;
    else
        red = true;
    update();
}

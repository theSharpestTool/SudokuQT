#include "button.h"
#include "widget.h"

extern Widget* widget;

Button::Button(int w, int h) : QGraphicsItem(), width(w), height(h), text(""), left(true)
{}

QRectF Button::boundingRect() const
{
    return QRect(0, 0, width, height);
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(text == "")
    {
        painter->setPen(QPen(Qt::darkRed, 4));
        painter->setRenderHint(QPainter::Antialiasing, true);
        QPolygonF triangle;
        if(left)
            triangle << QPointF(width, 0) << QPointF(width, height) << QPointF(0, height/2);
        else
            triangle << QPointF(0, 0) << QPointF(0, height) << QPointF(width, height/2);
        painter->drawPolygon(triangle);
    }
    else
    {
        if(text == "EASY")
            painter->setBrush(QBrush(QColor(Qt::red).darker(75)));
        else if(text == "MEDIUM")
            painter->setBrush(QBrush(QColor(Qt::red).darker(120)));
        else if(text == "HARD")
            painter->setBrush(QBrush(QColor(Qt::red).darker(180)));
        else if(text == "START" || text == "CLOSE" || text == "RECORDS"
                || text == "BACK" || text == "CONNECTION ERROR")
            painter->setBrush(QBrush(Qt::darkRed));

        painter->setPen(QPen(Qt::white, 1));
        if(text == " EASY " || text == " MEDIUM " || text == " HARD " || text == "RECONNECT")
            painter->setPen(QPen(Qt::darkRed, 7));
        painter->drawRect(boundingRect());
        painter->setFont(QFont("Times", height/2.5, QFont::Normal));
        if(text == "RECORDS" || text == " EASY " || text == " MEDIUM " || text == " HARD ")
            painter->setFont(QFont("Times", height/1.9, QFont::Normal));
        if(text == "CONNECTION ERROR")
            painter->setFont(QFont("Times", height/3.5, QFont::Normal));
        painter->drawText(boundingRect(), Qt::AlignCenter, text);
    }
    if(text == "EASY" || text == "MEDIUM" || text == "HARD")
        setOpacity(0.9);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(text == "START")
        widget->showDifficulties();
    else if(text == "CLOSE")
        widget->moveBack();
    else if(text == "EASY")
        widget->startGame(3);
    else if(text == "MEDIUM")
        widget->startGame(2);
    else if(text == "HARD")
        widget->startGame(1);
    else if(text == "RECORDS")
        widget->showRecords();
    else if(text == "BACK")
        widget->backToMainScene();

    else if(text == "")
    {
        if(left)
            widget->goLeft();
        else
            widget->goRight();
    }
    Q_UNUSED(event);
}

void Button::setText(QString txt)
{
    text = txt;
    update();
}

void Button::setLeft(bool l)
{
    left = l;
}

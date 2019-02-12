#ifndef BUTTON_H
#define BUTTON_H

#include <QtWidgets>

class Button : public QGraphicsItem
{
public:
    Button(int w, int h);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setText(QString txt);
    void setLeft(bool l);

private:
    int width;
    int height;
    bool left;
    QString text;
};

#endif // BUTTON_H

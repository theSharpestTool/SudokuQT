#ifndef CELL_H
#define CELL_H

#include <QtWidgets>

class Cell : public QGraphicsItem
{
public:
    Cell(int s);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setValue(int n);
    int getValue();
    void setEditable(bool condition);
    bool isEditable();
    int getSize();
    void setRed();

private:
    bool editable;
    bool red;

protected:
    int size;
    int value;
};

#endif // CELL_H

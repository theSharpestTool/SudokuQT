#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include "cell.h"
#include "circle.h"
#include "QDebug"
#include "button.h"
#include "timer.h"
#include "records.h"
#include "client.h"
#include "generator.h"

class Widget : public QGraphicsView
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    void showVariants(QPointF p);
    void showMiddleV(QPointF p);
    void showSideV(QPointF p);
    bool variantsAreShown();
    void writeValue(int value);
    void showDifficulties();
    void startGame(int difficulty);
    void update();
    void showRecords();
    void backToMainScene();
    void goLeft();
    void goRight();
    void sendToServer(QString request);
    void setRecords(QString rec);
    void errorConnection(bool er);
    void moveBack();

private:
    QGraphicsScene* scene;
    Records* records;
    QVector<Cell*> cell;
    QVector<Circle*> circle;
    Circle* chosenCircle;
    Generator* generator;
    QPoint* chosenCell;
    Button* buttonStart;
    Button* buttonRecords;
    QVector<Button*> difficulties;
    Button* window;
    int** numbers;
    Timer* timer;
    Client* client;
    int currentDifficulty;
    QPointF mistakeCell;
    QVector<QPointF> startPositions;
    QVector<QPointF> curPositions;
    QVector<QPointF> finPositions;
    int counter;
    int cellSize;

public slots:
    void recievePuzzle(int** numbrs);
    void setRedCell();
    void moveCircles();
    void removeVariants();
    void moveDifficulties();
    void removeDifficulties();
};

#endif // WIDGET_H

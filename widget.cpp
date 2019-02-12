#include "widget.h"

Widget::Widget(QWidget *parent)
    : QGraphicsView (parent)
{
    scene = new QGraphicsScene;
    records = new Records;
    client = new Client("localhost", 2323);
    //setFixedSize(540, 930);
    //scene->setSceneRect(0, 0, 540, 930);
    setFixedSize(423, 693);
    scene->setSceneRect(0, 0, 423, 693);
    //192.168.43.129

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(scene);

    chosenCircle = nullptr;
    setMouseTracking(true);
    chosenCell = nullptr;
    mistakeCell = QPointF();
    generator = new Generator();

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            QGraphicsRectItem* square = new QGraphicsRectItem;
            square->setRect(0, 0, scene->width()/3, scene->width()/3);
            square->setPen(QPen(Qt::black, 4));
            square->setPos(i*scene->width()/3, scene->height()/2-((scene->width()/3)*1.5)+j*scene->width()/3);
            scene->addItem(square);
        }

    cellSize = static_cast<int>(scene->width()/9);
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
        {
            cell << new Cell(cellSize);
            cell[(i*9)+j]->setPos(j*cellSize, scene->height()/2-((scene->width()/3)*1.5)+i*cellSize);
            cell[(i*9)+j]->setEditable(false);
            scene->addItem(cell[(i*9)+j]);
        }

    buttonStart = new Button(static_cast<int>(scene->width()), static_cast<int>(scene->height()/9));
    buttonStart->setText("START");
    buttonStart->setPos(0, 8*scene->height()/9);
    scene->addItem(buttonStart);

    buttonRecords = new Button(4*cellSize, cellSize+2);
    buttonRecords->setText("RECORDS");
    buttonRecords->setPos(5*cellSize, 0);
    scene->addItem(buttonRecords);

    timer = new Timer(cellSize);
    timer->setPos(0, 0);
    scene->addItem(timer);

    numbers = new int* [9];
    for(int i = 0; i < 9; i++)
        numbers[i] = new int [9];

    counter = 0;
}

void Widget::showVariants(QPointF p)
{
    if(static_cast<int>(p.x()) == 0 || static_cast<int>(p.x()) == static_cast<int>(8*scene->width()/9))
        showSideV(p);
    else
        showMiddleV(p);
    int x, y;
    x = static_cast<int>(p.x()/(cellSize));
    y = static_cast<int>(p.y()/(cellSize))-2;
    chosenCell = new QPoint(x,y);
}

void Widget::showMiddleV(QPointF p)
{
    for(int i = 0; i < 9; i++)
    {
        double x, y;
        circle << new Circle(cellSize);
        circle[i]->setValue(i+1);
        if(i < 5)
        {
            x = p.x()-circle[i]->getSize();
            y = p.y()+(i-2)*circle[i]->getSize();
        }
        else
        {
            x = p.x()+circle[i]->getSize();
            y = p.y()+(i-6.5)*circle[i]->getSize();
        }
        finPositions << QPointF(x, y);
        curPositions << QPointF(p);
        startPositions << QPointF(p);
        scene->addItem(circle[i]);
    }
    moveCircles();
}

void Widget::showSideV(QPointF p)
{
    double x, y;
    for(int i = 0; i < 9; i++)
    {
        circle << new Circle(cellSize);
        circle[i]->setValue(i+1);
        if (static_cast<int>(p.x()) == 0)
        {
            if(i < 5)
            {
                x = p.x()+circle[i]->getSize();
                y = p.y()+(i-2)*circle[i]->getSize();
            }
            else
            {
                x = p.x()+2*circle[i]->getSize();
                y = p.y()+(i-6.5)*circle[i]->getSize();
            }
        }
        else
        {
            if(i < 5)
            {
                x = p.x()-2*circle[i]->getSize();
                y = p.y()+(i-2)*circle[i]->getSize();
            }
            else
            {
                x = p.x()-circle[i]->getSize();
                y = p.y()+(i-6.5)*circle[i]->getSize();
            }
        }
        finPositions << QPointF(x, y);
        curPositions << QPointF(p);
        startPositions << QPointF(p);
        scene->addItem(circle[i]);
    }
    moveCircles();
}

bool Widget::variantsAreShown()
{
    return chosenCell;
}

void Widget::removeVariants()
{
    for(int i = 0; i < 9; i++)
        scene->removeItem(circle[i]);
    circle.clear();
    delete chosenCell;
    chosenCell = nullptr;
    startPositions.clear();
    curPositions.clear();
    finPositions.clear();
}

void Widget::moveDifficulties()
{
    for(int i = 0; i < difficulties.size(); i++)
    {
        curPositions[i].setX(startPositions[i].x()+(counter*(finPositions[i].x()-startPositions[i].x())/13));
        curPositions[i].setY(startPositions[i].y()+(counter*(finPositions[i].y()-startPositions[i].y())/13));
        difficulties[i]->setPos(curPositions[i]);
    }
    counter++;
    if(counter <= 13)
        QTimer::singleShot(10, this, SLOT(moveDifficulties()));
    else
        counter = 0;
}

void Widget::writeValue(int value)
{
    bool mistake = false;
    int x = chosenCell->x();
    int y = chosenCell->y();
    int buffer = numbers[y][x];
    numbers[y][x] = value;
    for(int i = 0; i < 9; i++)
        if(i != y && numbers[i][x] == numbers[y][x])
        {
            mistakeCell.setY(i);
            mistakeCell.setX(x);
            mistake = true;
        }
    for(int j = 0; j < 9; j++)
        if(j != x && numbers[y][j] == numbers[y][x])
        {
            mistakeCell.setY(y);
            mistakeCell.setX(j);
            mistake = true;
        }
    for(int i = y-(y%3); i < (y/3)*3+3; i++)
        for(int j = x-(x%3); j < (x/3)*3+3; j++)
            if(i != y && j != x && numbers[i][j] == numbers[y][x])
            {
                mistakeCell.setY(i);
                mistakeCell.setX(j);
                mistake = true;
            }
    if(!mistake)
        cell[y*9+x]->setValue(value);
    else
    {
        setRedCell();
        QTimer::singleShot(1000, this, SLOT(setRedCell()));
        numbers[y][x] = buffer;
    }
    removeVariants();
    update();
}

void Widget::showDifficulties()
{
    if(chosenCell)
        removeVariants();
    buttonStart->setText("CLOSE");
    for(int i = 0; i < 3; i++)
        difficulties << new Button(static_cast<int>(scene->width()), static_cast<int>(scene->height()/9));
    difficulties[0]->setText("EASY");
    difficulties[1]->setText("MEDIUM");
    difficulties[2]->setText("HARD");
    for(int i = 0; i < 3; i++)
    {
        startPositions << QPointF(0, 8*scene->height()/9);
        curPositions = startPositions;
        finPositions << QPointF(0, (7-i)*scene->height()/9);
        scene->addItem(difficulties[i]);
    }
    moveDifficulties();
}

void Widget::removeDifficulties()
{
    for(int i = 0; i < difficulties.size(); i++)
        scene->removeItem(difficulties[i]);
    difficulties.clear();
    startPositions.clear();
    curPositions.clear();
    finPositions.clear();
    buttonStart->setText("START");
}

void Widget::startGame(int difficulty)
{
    currentDifficulty = difficulty;
    removeDifficulties();
    scene->removeItem(timer);
    delete timer;
    timer = new Timer(static_cast<int>(scene->width()/9));
    timer->setPos(0, 0);
    scene->addItem(timer);
    generator->recieveDifficulty(difficulty);
}

void Widget::recievePuzzle(int** numbrs)
{
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
        {
            numbers[i][j] = numbrs[i][j];
            if(numbers[i][j] != 0)
                cell[(i*9)+j]->setEditable(false);
            else
                cell[(i*9)+j]->setEditable(true);
            cell[(i*9)+j]->setValue(numbers[i][j]);
        }
    timer->stop(false);
    timer->run();
}

void Widget::setRedCell()
{
    cell[static_cast<int>(mistakeCell.y()*9+mistakeCell.x())]->setRed();
}

void Widget::moveCircles()
{
    for(int i = 0; i < circle.size(); i++)
    {
        curPositions[i].setX(startPositions[i].x()+(counter*(finPositions[i].x()-startPositions[i].x())/13));
        curPositions[i].setY(startPositions[i].y()+(counter*(finPositions[i].y()-startPositions[i].y())/13));
        circle[i]->setPos(curPositions[i]);
    }
    counter++;
    if(counter <= 13)
        QTimer::singleShot(10, this, SLOT(moveCircles()));
    else
        counter = 0;
}

void Widget::moveBack()
{
    QVector<QPointF> buffer;
    buffer = startPositions;
    startPositions = finPositions;
    curPositions = startPositions;
    finPositions = buffer;
    if(chosenCell)
    {
        moveCircles();
        QTimer::singleShot(210, this, SLOT(removeVariants()));
    }
    else
    {
        moveDifficulties();
        QTimer::singleShot(150, this, SLOT(removeDifficulties()));
    }
}

void Widget::update()
{
    bool isFull = true;
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
        {
            numbers[i][j] = cell[(i*9)+j]->getValue();
            if(numbers[i][j] == 0)
                isFull = false;
        }
    if(isFull)
    {
        timer->stop(true);
        QString difficulty;
        if(currentDifficulty == 3)
            difficulty = "easy";
        else if(currentDifficulty == 2)
            difficulty = "medium";
        else if(currentDifficulty == 1)
            difficulty = "hard";
        sendToServer(difficulty + "," + QString::number(timer->getTime()));
    }
}

void Widget::showRecords()
{
    records->build();
    setScene(records);
}

void Widget::backToMainScene()
{
    setScene(scene);
}

void Widget::goLeft()
{
    records->goLeft();
}

void Widget::goRight()
{
    records->goRight();
}

void Widget::sendToServer(QString request)
{
    client->sendToServer(request);
}

void Widget::setRecords(QString rec)
{
    records->setRecords(rec);
}

void Widget::errorConnection(bool er)
{
    records->errorConnection(er);
}

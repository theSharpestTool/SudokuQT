#include "records.h"
#include "widget.h"

extern Widget* widget;

Records::Records() : QGraphicsScene(), difficulty(0), error(false)
{
    //setSceneRect(0, 0, 540, 930);
    setSceneRect(0, 0, 423, 693);
}

void Records::build()
{
    widget->sendToServer(QString::number(difficulty));

    bannerDifficulty = new Button(static_cast<int>(width()), static_cast<int>(height()/9));
    if(difficulty == 0)
        bannerDifficulty->setText(" EASY ");
    else if(difficulty == 1)
        bannerDifficulty->setText(" MEDIUM ");
    else if(difficulty == 2)
        bannerDifficulty->setText(" HARD ");
    bannerDifficulty->setPos(0, 0);
    addItem(bannerDifficulty);

    buttonBack = new Button(static_cast<int>(4*width()/6), static_cast<int>(height()/9));
    buttonBack->setText("BACK");
    buttonBack->setPos(width()/6, 8*height()/9);
    addItem(buttonBack);

    toggleLeft = new Button(static_cast<int>(width()/6), static_cast<int>(height()/9));
    toggleRight = new Button(static_cast<int>(width()/6), static_cast<int>(height()/9));
    toggleRight->setLeft(false);
    toggleLeft->setPos(0, 8*height()/9);
    toggleRight->setPos(5*width()/6, 8*height()/9);
    addItem(toggleLeft);
    addItem(toggleRight);

    if(error)
    {
        bannerError = new Button(static_cast<int>(width()), static_cast<int>(height()/9));
        bannerError->setText("CONNECTION ERROR");
        bannerError->setPos(0, height()/2 - height()/18);
        addItem(bannerError);
    }
    else
    {
        textEdit = new QTextEdit;
        textEdit->setReadOnly(true);
        textEdit->setFixedSize(static_cast<int>(width()), static_cast<int>(7*height()/9));
        textEdit->setFont(QFont("Times", static_cast<int>(height()/25), QFont::Normal));
        textEdit->append(records);
        QGraphicsProxyWidget* proxyWidget = addWidget(textEdit);
        proxyWidget->setPos(0, height()/9);
    }
}

void Records::goLeft()
{
    if(difficulty > 0)
        difficulty--;
    else if(difficulty == 0)
        difficulty = 2;
    clear();
    build();
}

void Records::goRight()
{
    if(difficulty < 2)
        difficulty++;
    else if(difficulty == 2)
        difficulty = 0;
    clear();
    build();
}

void Records::setRecords(QString rec)
{
    records = rec;
    clear();
    build();
}

void Records::errorConnection(bool er)
{
   error = er;
   clear();
   build();
}

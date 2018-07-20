#ifndef RECORDS_H
#define RECORDS_H

#include <QtWidgets>
#include "button.h"

class Records : public QGraphicsScene
{
public:
    Records();
    void build();
    void goLeft();
    void goRight();
    void setRecords(QString rec);
    void errorConnection(bool er);

private:
    Button* buttonBack;
    Button* bannerDifficulty;
    Button* toggleLeft;
    Button* toggleRight;
    Button* bannerError;
    QTextEdit* textEdit;
    int difficulty;
    QString records;
    bool error;

signals:

public slots:
};

#endif // RECORDS_H

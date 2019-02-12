#include "widget.h"
#include "generator.h"
#include <QApplication>

Widget* widget;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    widget = new Widget();
    widget->show();
    return a.exec();
}

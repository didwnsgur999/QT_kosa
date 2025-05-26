#include "widget.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLabel*hello = new QLabel("Hello Qt!",0,Qt::FramelessWindowHint);
    hello->setCursor(QCursor(Qt::ClosedHandCursor));
    hello->showMaximized();
    return a.exec();
}

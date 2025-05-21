#include "qteditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qteditor w;
    w.show();
    return a.exec();
}

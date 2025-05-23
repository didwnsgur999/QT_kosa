#include "widget.h"

#include <QtWidgets>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString lang= QLocale::system().uiLanguages().first();

    QTranslator translator;
    if(translator.load("hello_"+lang.left(2)))
        a.installTranslator(&translator);
    QPushButton hello(QObject::tr("Hello world"));
    QPushButton hello2(QObject::tr("Hi world"));
    hello.resize(100,30);
    hello.show();
    hello2.show();

    return a.exec();
}

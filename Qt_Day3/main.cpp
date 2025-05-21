#include "widget.h"

#include <QApplication>
#include <QToolBox>
#include <QDial>
#include <QCalendarWidget>
#include <QTextEdit>
#include <QGroupBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if Toolboxwid
    QGroupBox groupbox;
    QToolBox toolbox(&groupbox);
    groupbox.resize(360,420);
    toolbox.resize(300,380);
    groupbox.show();
    QDial dial(&toolbox);
    QCalendarWidget calendarWidget(&toolbox);
    QTextEdit textEdit("hello3",&toolbox);
    toolbox.addItem(&dial,"Page &1");
    toolbox.addItem(&calendarWidget,"Page &2");
    toolbox.addItem(&textEdit,"Page &3");

#endif
    Widget w;
    w.show();

    return a.exec();
}

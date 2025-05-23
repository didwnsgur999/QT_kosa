#include "widget.h"
#include <QCloseEvent>
#include <QTextEdit>


Widget::Widget(QWidget *parent)
    : QTextEdit(parent)
{
    //setText(tr("Hello World"));
    //resize(100,30);
}

Widget::~Widget() {}
//윈도우가 이동될때
// void Widget::moveEvent(QMoveEvent*) {
//     setText(QString("X:%1,Y:%2").arg(x()).arg(y()));
// }
// void Widget::closeEvent(QCloseEvent* event){
//     event->ignore();
// }

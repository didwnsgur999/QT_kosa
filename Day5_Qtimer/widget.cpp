#include "widget.h"

#include <QTimer>
#include <QTime>
Widget::Widget(QWidget *parent)
    : QLabel(parent)
{
    QTimer *timer=new QTimer(this);
    displayClock();
    connect(timer,SIGNAL(timeout()),SLOT(displayClock()));
    timer->start(1000);
    resize(90,40);
}

void Widget::displayClock(){
    static int cnt=0;
    setText(QTime::currentTime().toString()+"\n"+QString::number(cnt++));
}
Widget::~Widget() {}

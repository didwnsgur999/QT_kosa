#include "widget.h"
#include "thread.h"
#include <QtGui>
#include <QtWidgets>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLabel* label=new QLabel(this);
    QPushButton* button=new QPushButton("Pause",this);
    button->setCheckable(true);
    thread = new Thread(label);
    QHBoxLayout* hBoxLayout=new QHBoxLayout(this);
    hBoxLayout->addWidget(label);
    hBoxLayout->addWidget(button);
    hBoxLayout->setSpacing(10);
    connect(button,SIGNAL(toggled(bool)),SLOT(threadControl(bool)));
    //thread가 1초마다 signal을 보내면, setText처리한다.
    connect(thread,SIGNAL(setLabeled(QString)),label,SLOT(setText(QString)));
    thread->start();
}

Widget::~Widget() {}

void Widget::threadControl(bool flag){
    QPushButton* button = (QPushButton*)(sender());
    button->setText((flag)?"Resume":"Stop");
    (flag)?thread->stopThread():thread->resumeThread();
}

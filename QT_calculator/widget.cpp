#include "widget.h"
#include <QLabel>
#include <QPushButton>
Widget::Widget(QWidget *parent)
    : QWidget(parent),m_isFirst(true)//first인 상태 확인
{
    m_label=new QLabel("0",this);
    m_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    m_label->setGeometry(10,5,230,40);
    const char ButtonChar[16][2]={
        "7","8","9","/",
        "4","5","6","*",
        "1","2","3","-",
        "0","c","=","+"
    };
    for(int y=0; y<WIDTH; y++){
        for(int x=0; x<WIDTH; x++){
            m_buttons.append(new QPushButton(ButtonChar[x+y*WIDTH],this));
            m_buttons.at(x+y*WIDTH)->setGeometry(5+60*x,50+60*y,60,60);
        }
    }
    for(int i=0; i<12; i++){
        connect(m_buttons.at(i),SIGNAL(clicked()),SLOT(setNum()));
    }
    connect(m_buttons.at(1),SIGNAL(clicked()),SLOT(setNum()));
    connect(m_buttons.at(2),SIGNAL(clicked()),SLOT(setNum()));
    connect(m_buttons.at(4),SIGNAL(clicked()),SLOT(setNum()));
    connect(m_buttons.at(5),SIGNAL(clicked()),SLOT(setNum()));
    connect(m_buttons.at(6),SIGNAL(clicked()),SLOT(setNum()));
    connect(m_buttons.at(8),SIGNAL(clicked()),SLOT(setNum()));
    connect(m_buttons.at(9),SIGNAL(clicked()),SLOT(setNum()));
    connect(m_buttons.at(10),SIGNAL(clicked()),SLOT(setNum()));
    connect(m_buttons.at(12),SIGNAL(clicked()),SLOT(setNum()));
}

Widget::~Widget() {}

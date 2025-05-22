#include "widget.h"
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QButtonGroup>

Widget::Widget(QWidget *parent)
    : QWidget(parent),m_isFirst(true)//first인 상태 확인
{
    buttonGroup=new QButtonGroup(this);
    QVBoxLayout* vBoxLayout=new QVBoxLayout(this);
    QGridLayout* gridLayout=new QGridLayout();

    m_label=new QLabel("0",this);
    m_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    m_label->setMaximumHeight(30);
    m_label->setFrameShape(QFrame::Box);
    vBoxLayout->addWidget(m_label);
    vBoxLayout->addLayout(gridLayout);
    const char ButtonChar[16][2]={
        "7","8","9","/",
        "4","5","6","*",
        "1","2","3","-",
        "0","c","=","+"
    };
    //buttonGroup에 addbutton(button주소, id 넣기) + 위치지정 + gridlayout에 넣기.
    for(int y=0; y<WIDTH; y++){
        for(int x=0; x<WIDTH; x++){
            QPushButton* btn=new QPushButton(ButtonChar[x+y*WIDTH],this);
            buttonGroup->addButton(btn,x+y*WIDTH);
            gridLayout->addWidget(btn,y,x);
        }
    }
    //click()에서 한번에 처리.
    for(int i=0; i<16; i++){
        connect(buttonGroup->button(i),&QAbstractButton::clicked,[=](){Widget::click(i);});
    }

    setWindowTitle("Calculator");
    setLayout(vBoxLayout);
}

Widget::~Widget() {
    delete m_label;
    Q_FOREACH(auto b, buttonGroup->buttons()) delete b;
}

void Widget::click(int id){
    //clear -> 전체초기화 아니라 일부초기화
    if(id==13){
        m_isFirst=true;
        m_label->setText("0");
        m_op="0";
        m_num1="0";
        return;
    }
    //equal
    else if(id==14){
        if(m_num1=="0"){
            m_op="0";
            m_label->setText("0");
            m_isFirst=true;
            return;
        }
        if(m_op=="0"){
            m_op="0";
            m_label->setText("0");
            m_isFirst=true;
            return;
        }
        double res;
        if(m_op=="+"){
            res=m_num1.toDouble()+m_label->text().toDouble();
        }
        else if(m_op=="-"){
            res=m_num1.toDouble()-m_label->text().toDouble();
        }
        else if(m_op=="*"){
            res=m_num1.toDouble()*m_label->text().toDouble();
        }
        else if(m_op=="/"){
            if(m_label->text().toDouble()==0) return;
            res=m_num1.toDouble()/m_label->text().toDouble();
        }
        m_label->setText(QString::number(res));
        return;
    }
    QPushButton *btn=(QPushButton*)buttonGroup->button(id);

    QString bStr;
    if(btn!=nullptr) bStr=btn->text();
    //ops
    if(id%4==3){
        if(m_label!=nullptr){
            m_num1=m_label->text();
            m_label->setText(btn->text());
        }
        m_op=bStr;
        m_isFirst=true;
    }
    else{
        if(m_label!=nullptr){
            QString lStr=m_label->text();
            m_label->setText((lStr=="0"|m_isFirst)?bStr:lStr+bStr);
            m_isFirst=false;
        }
    }
}

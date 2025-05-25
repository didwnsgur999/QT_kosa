#include "widget.h"
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QButtonGroup>

Widget::Widget(QWidget *parent)
    : QWidget(parent),m_num1("0"),m_op("0"),m_isFirst(true)//setting private variable
{
    //setting buttonGroup, vertical layout, grid layout
    buttonGroup=new QButtonGroup(this);
    QVBoxLayout* vBoxLayout=new QVBoxLayout(this);
    QGridLayout* gridLayout=new QGridLayout();

    //label setting
    m_label=new QLabel("0",this);
    m_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    m_label->setMaximumHeight(30);
    m_label->setFrameShape(QFrame::Box);
    //add widget, layout to vBox layout
    vBoxLayout->addWidget(m_label);
    vBoxLayout->addLayout(gridLayout);
    const char ButtonChar[16][2]={
        "7","8","9","/",
        "4","5","6","*",
        "1","2","3","-",
        "0","c","=","+"
    };
    //buttonGroup's addbutton(button id) + setting point + gridlayout.
    for(int y=0; y<WIDTH; y++){
        for(int x=0; x<WIDTH; x++){
            QPushButton* btn=new QPushButton(ButtonChar[x+y*WIDTH],this);
            buttonGroup->addButton(btn,x+y*WIDTH);
            gridLayout->addWidget(btn,y,x);
        }
    }
    //click()-> button action set.
    for(int i=0; i<16; i++){
        connect(buttonGroup->button(i),&QAbstractButton::clicked,this,[=](){Widget::click(i);});
    }

    setWindowTitle("Calculator");
    //show layout
    setLayout(vBoxLayout);
}

Widget::~Widget() {
    //delete heap obj
    delete m_label;
    Q_FOREACH(auto b, buttonGroup->buttons()) delete b;
}

void Widget::click(int id){
    //error-> next label 0
    if(m_label->text()=="Error") m_label->setText("0");
    //clear -> all setting clear C
    if(id==13){
        m_isFirst=true;
        m_label->setText("0");
        m_op="0";
        m_num1="0";
        return;
    }
    //equal =
    else if(id==14){
        //op == 0 -> op is not set -> op has to be set
        if(m_op=="0"){
            QString labelText = m_label->text();
            m_label->setText(labelText);
            m_num1=labelText;
            m_isFirst=true;
            return;
        } else { //op set
            QString labelText = m_label->text();
            //num2 is not set
            if((labelText=="*"||labelText=="+"||labelText=="-"||labelText=="/")) return;
            double res;
            //if op set-> num2 is not called->auto 0 call
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
                // div by zero
                if(m_label->text().toDouble()==0) {
                    m_label->setText("Error");
                    m_op="0";
                    m_num1="0";
                    return;
                }
                res=m_num1.toDouble()/m_label->text().toDouble();
            }
            m_label->setText(QString::number(res));
            m_num1=QString::number(res);
            m_op="0";
            m_isFirst=true;
        }
        return;
    }
    //ops, number sets in here
    QPushButton *btn=(QPushButton*)buttonGroup->button(id);

    QString bStr;
    if(btn!=nullptr) bStr=btn->text();
    //id%4==3 -> ops -> num1 setting
    if(id%4==3){
        if(m_label!=nullptr){
            QString labelText = m_label->text();
            //label->ops->dont change m_num1
            if(!(labelText=="*"||labelText=="+"||labelText=="-"||labelText=="/"))m_num1=labelText;
            m_label->setText(btn->text());
        }
        m_op=bStr;
        m_isFirst=true;
    }
    // number select-> check isfirst-> label set new num/add bStr in end
    else{
        if(m_label!=nullptr){
            QString lStr=m_label->text();
            m_label->setText((lStr=="0"|m_isFirst)?bStr:lStr+bStr);
            m_isFirst=false;
        }
    }
}

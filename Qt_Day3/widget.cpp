#include "widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDebug>
#include <QDial>
#include <QCalendarWidget>
#include <QTextEdit>
#include <QStackedLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QtWidgets>
#include <QLabel>
#include <QSplitter>
#include <QPushButton>
#include <QTabWidget>
#include <QToolBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
#if horizontal_box
    QPushButton *pushButton1=new QPushButton();
    pushButton1->setText("Button1");
    QPushButton *pushButton2=new QPushButton("Button2");
    QPushButton *pushButton3=new QPushButton("Button3",this);
    QHBoxLayout *hBoxLayout=new QHBoxLayout;
    hBoxLayout->setContentsMargins(10,10,10,10);
    hBoxLayout->addWidget(pushButton1);
    hBoxLayout->addWidget(pushButton2);
    hBoxLayout->addWidget(pushButton3);
    setLayout(hBoxLayout);
#endif
#if vertical_box
    //객체이름, 부모 위젯 포인터
    QPushButton *pushButton1=new QPushButton();
    pushButton1->setText("Button1");
    QPushButton *pushButton2=new QPushButton("Button2");
    QPushButton *pushButton3=new QPushButton("Button3",this);
    //()안에는 부모 위젯 포인터가 들어
    QVBoxLayout *vBoxLayout=new QVBoxLayout(this);
    //widget 추가
    vBoxLayout->setSpacing(6);
    vBoxLayout->addWidget(pushButton1);
    vBoxLayout->addWidget(pushButton2);
    vBoxLayout->addWidget(pushButton3);
    setLayout(vBoxLayout);
#endif
#if gridlayout
#define NO_OF_ROW 3
    QGridLayout*gridLayout=new QGridLayout(this);
    QPushButton *pushButton[NO_OF_ROW*NO_OF_ROW];
    for(int y=0; y<NO_OF_ROW; y++){
        for(int x=0; x<NO_OF_ROW; x++){
            int p = x+y*NO_OF_ROW;
            QString str=QString("Button%1").arg(p+1);
            pushButton[p]=new QPushButton(str,this);
            gridLayout->addWidget(pushButton[p],x,y);
        }
    }
    setLayout(gridLayout);
#endif
#if stacklayout
    QDial *dial=new QDial(this);
    dial->setRange(0,3);

    QLabel *label=new QLabel("1",this);
    QCalendarWidget* calendarWidget=new QCalendarWidget(this);
    QTextEdit *textEdit=new QTextEdit("hello3",this);

    QStackedLayout *stackedLayout=new QStackedLayout();
    qDebug()<<stackedLayout->addWidget(label);
    qDebug()<<stackedLayout->addWidget(calendarWidget);
    qDebug()<<stackedLayout->addWidget(textEdit);
    connect(dial,SIGNAL(valueChanged(int)),stackedLayout,SLOT(setCurrentIndex(int)));
    QHBoxLayout *hBoxLayout = new QHBoxLayout(this);
    hBoxLayout->addWidget(dial);
    hBoxLayout->addLayout(stackedLayout);
    setLayout(hBoxLayout);
#endif
#if QGroupboxwid
    QStringList labels;
    labels<<"&Ip Address"<<"&Mac Address"<<"&Date";
    QLineEdit* lineEdit[3];
    QFormLayout* formLayout=new QFormLayout();
    for(int i=0; i<3; i++){
        lineEdit[i]=new QLineEdit(this);
        formLayout->addRow(labels.at(i),lineEdit[i]);
    }
    QGroupBox *groupBox=new QGroupBox("&Widget Group",this);
    groupBox->move(5,5);
    groupBox->setLayout(formLayout);

    resize(groupBox->sizeHint().width()+10,groupBox->sizeHint().height()+10);
#endif
#if tabwid
    QDial *dial=new QDial(this);
    dial->setRange(0,2);
    QCalendarWidget* calendarWidget=new QCalendarWidget(this);
    QTextEdit *textEdit=new QTextEdit("hello3",this);

    QTabWidget* tabWidget=new QTabWidget(this);
    tabWidget->addTab(dial,"Tab &1");
    tabWidget->addTab(calendarWidget,"Tab &2");
    tabWidget->addTab(textEdit,"Tab &2");
    resize(tabWidget->sizeHint());
#endif
#if splitter
    QLabel* label=new QLabel("&value",this);
    QDial* dial1=new QDial(this);
    QDial* dial2=new QDial(this);
    label->setBuddy(dial2);

    QSplitter* splitter=new QSplitter(this);
    splitter->addWidget(label);
    splitter->addWidget(dial1);
    splitter->addWidget(dial2);
    resize(splitter->sizeHint());
#endif

}
Widget::~Widget()
{

}

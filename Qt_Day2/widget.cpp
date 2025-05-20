#include "widget.h"
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QButtonGroup>

#if checkbox
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(140,110);
    buttonGroup=new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    //connect(buttonGroup,SIGNAL(idClicked(int)),SLOT(selectButton(int)));
    QLabel* label=new QLabel("0",this);
    label->move(10,10);
    connect(buttonGroup,&QButtonGroup::idClicked,[=](int id)mutable{label->setText(QString::number(id+1));});
    for(int i=0; i<4; i++){
        QString str=QString("checkBox%1").arg(1+i);
        checkBox[i]=new QCheckBox(str,this);
        checkBox[i]->move(10,10+20*i);
        buttonGroup->addButton(checkBox[i],i);
    }
}
void Widget::selectButton(int id){
    QButtonGroup *buttonGroup=dynamic_cast<QButtonGroup*>(sender());
    QCheckBox*button = dynamic_cast<QCheckBox*>(buttonGroup->button(id));
    qDebug("CheckBox%d is selected (%s)",id+1,(button->isChecked())?"On":"Off");
}
#endif
#if !next
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QValidator>
#include <QMessageBox>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QDoubleValidator*doubleValidator=new QDoubleValidator(this);
    doubleValidator->setRange(10.0,100.0,3);
    QIntValidator* intValidator=new QIntValidator(this);
    //intValidator->setRange(13,19);
    intValidator->setBottom(13);
    intValidator->setTop(19);
    //QRegularExpression re("^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$");
    QRegularExpression re("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    QRegularExpressionValidator* regExpValidator= new QRegularExpressionValidator(re,this);

    QLineEdit *lineEditDouble = new QLineEdit(this);
    lineEditDouble->setValidator(doubleValidator);
    QLineEdit *lineEditInt = new QLineEdit(this);
    lineEditInt->setValidator(intValidator);
    QLineEdit *lineEditRegExp = new QLineEdit(this);
    lineEditRegExp->setValidator(regExpValidator);
    QPushButton* dummyBtn = new QPushButton("Submit", this);

    QFormLayout* formLayout = new QFormLayout(this);
    formLayout->addRow(dummyBtn);
    formLayout->addRow("&Double",lineEditDouble);
    formLayout->addRow("&Int",lineEditInt);
    formLayout->addRow("&Regular Expression",lineEditRegExp);
    connect(lineEditInt, &QLineEdit::editingFinished, this, [=]() {
        qDebug() << "[DEBUG] editingFinished called";
        bool ok;
        int val = lineEditInt->text().toInt(&ok);
        qDebug("%d",val);
        if (!ok || val < 13 || val > 19) {
            qDebug() << "invalid input" << lineEditInt->text();
            lineEditInt->clear();
            lineEditInt->setText("");
        } else {
            qDebug() << "valid input:" << val;
        }
    });
    setWindowTitle("Validator");
}
#endif
Widget::~Widget() {}

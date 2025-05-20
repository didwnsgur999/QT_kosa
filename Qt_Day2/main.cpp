#include "widget.h"
#include <QSlider>
#include <QStyleFactory>
#include <QProgressBar>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);
//     Widget w;
//     w.show();
//     return a.exec();
// }
#if qtbutton
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPushButton quit("Quit",0);
    QLabel hello("<font color=blue>"
                 "Hello <i>Qt!</i> </font>",nullptr);
    quit.resize(75,35);
    hello.resize(1200,800);
    //속성설정이 끝난 이후에 show 사용하기.
    hello.show();
    quit.show();
    return a.exec();
}
#endif
#if qtbutton
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;
    QLabel hello("<font color=blue>"
                 "Hello <i>Qt!</i> </font>",&w);
    QPushButton quit("Quit",&w);
    quit.move(10,40);
    quit.resize(75,35);
    QObject::connect(&quit,&QPushButton::clicked,&hello,[&](){hello.setText("<b>HI</b>");});
    w.show();

    return a.exec();
}
#endif
#if usingwidget
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QLabel *label=new QLabel("<font size=20>Hello World!</font>",&w);
    QObject::connect(&w,SIGNAL(clicked()),&a,SLOT(quit()));
    label->setGeometry(10,90,75,35);
    w.show();

    return a.exec();
}
#endif
#if lcdnumber
#include <QLCDNumber>
int main(int argc, char*argv[]){
    QApplication a(argc, argv);
    QLCDNumber *lcd = new QLCDNumber();

    lcd->setSegmentStyle(QLCDNumber::Flat);
    //binary 너무 길어서 안나온다.
    lcd->setBinMode();
    lcd->display(2002);
    lcd->setDigitCount(32);
    lcd->show();
    return a.exec();
}
#endif
#if progressbarwid
#include <QProgressBar>
#include <QTimer>
int main(int argc, char*argv[]){
    QApplication a(argc, argv);
    QProgressBar *progBar=new QProgressBar();
    progBar->setOrientation(Qt::Vertical);
    QTimer timer;
    progBar->show();
    int n=0;
    QObject::connect(&timer,&QTimer::timeout,[&](){progBar->setValue(++n%101);});
    timer.start(10);
    return a.exec();
}
#endif
#if QtextBrowser
#include <QTextBrowser>
#include <QUrl>
int main(int argc, char* argv[]){
    QApplication a(argc,argv);

    QTextBrowser*tb=new QTextBrowser();
    tb->setSource(QUrl("index.html"));
    tb->show();

    return a.exec();
}
#endif
#if qpushbuttonwid
int main(int argc, char* argv[]){
    QApplication a(argc,argv);

    QPushButton *pushButton=new QPushButton("Push&button",nullptr);
    pushButton->setCheckable(true);
    QObject::connect(pushButton,&QPushButton::toggled,[&](bool flag){qDebug()<<"toggled";if(!flag) a.quit();});
    pushButton->show();

    return a.exec();
}
#endif
#if Qslider
int main(int argc, char* argv[]){
    QApplication a(argc,argv);

    QWidget w;

    QProgressBar bar(&w);
    bar.setGeometry(10,10,150,20);

    QSlider slider(&w);
    slider.setOrientation(Qt::Horizontal);
    slider.setTickPosition(QSlider::TicksAbove);
    slider.setStyle(QStyleFactory::create("Fusion"));
    //valuechanged가 int형을 넘기는걸 slot이 받아서 사용한다.
    QObject::connect(&slider,SIGNAL(valueChanged(int)),&bar,SLOT(setValue(int)));
    w.show();

    return a.exec();
}
#endif
#if Qscrollbar
#include <QScrollArea>
#include <QScrollBar>

int main(int argc, char* argv[]){
    QApplication a(argc,argv);
    QLabel*label=new QLabel("adnlknlnflkngdklsgnsaklgndsajgasnglsnaglsanglkasnglkas");
    QScrollArea* scrollArea=new QScrollArea();
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(label);
    scrollArea->resize(60,30);
    scrollArea->show();
    QScrollBar*scrollBar=scrollArea->horizontalScrollBar();
    scrollBar->setValue(scrollBar->minimum());
    return a.exec();
}
#endif

#if QDial
#include <QDial>

int main(int argc, char* argv[]){
    QApplication a(argc,argv);
    QDial*dial=new QDial();
    dial->setWrapping(true);
    dial->setNotchesVisible(true);
    dial->setNotchTarget(10);
    dial->show();
    return a.exec();
}
#endif
#if QSpinBox
#include <QSpinBox>

int main(int argc, char* argv[]){
    QApplication a(argc,argv);
    QSpinBox* spinBox=new QSpinBox();
    spinBox->setRange(0,10);
    spinBox->setSuffix("%");
    spinBox->setWrapping(true);
    //0을 대체한다.
    spinBox->setSpecialValueText("Percent");
    spinBox->show();

    return a.exec();
}
#endif
#if onlyw
int main(int argc, char* argv[]){
    QApplication a(argc,argv);



    return a.exec();
}
#endif
#if miniproject_//내가 해야됨.
#include <QSpinBox>
#include <QDial>

int main(int argc, char* argv[]){
    QApplication a(argc,argv);
    QWidget w;

    QSpinBox spinBox(&w);
    QDial dial(&w);

    spinBox.setRange(0,359);
    spinBox.setSuffix("`");
    spinBox.setWrapping(true);
    QObject::connect(&)


    return a.exec();
}
#endif
#if QDateTime
#include <QTime>
#include <QTimeEdit>
int main(int argc, char* argv[]){
    QApplication a(argc,argv);

    QTimeEdit* timeEdit=new QTimeEdit();
    timeEdit->move(500,300);
    timeEdit->setTime(QTime::currentTime());
    timeEdit->show();
    QDateEdit* dateEdit=new QDateEdit(QDate::currentDate(),0);
    dateEdit->setCalendarPopup(true);
    dateEdit->show();
    return a.exec();
}
#endif
#if QLineEditwid
#include <QLineEdit>
#include <QCompleter>
int main(int argc, char*argv[]){
    QApplication a(argc,argv);

    QLineEdit* lineEdit=new QLineEdit();

    //lineEdit->setInputMask("000");
    //lineEdit->setPlaceholderText("input teh number");
    lineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    // QStringList CompletionList;
    // CompletionList<<"Bryan"<<"Bryan"<<"Bryan"<<"Bryan"<<"Bryan";
    // QCompleter* stringCompleter=new QCompleter(CompletionList,lineEdit);
    // stringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    // lineEdit->setCompleter(stringCompleter);
    lineEdit->show();
    return a.exec();
}
#endif
#if QCombowidg
#include <QComboBox>
int main(int argc, char*argv[]){
    QApplication a(argc,argv);

    QComboBox*comboBox=new QComboBox();
    comboBox->addItem("KDE");
    comboBox->addItem("Gnome");
    comboBox->addItem("FVWM");
    comboBox->addItem("CDE");
    comboBox->setEditable(true);
    comboBox->show();

    return a.exec();
}
#endif
#if !Qvalidator

int main(int argc, char*argv[]){
    QApplication a(argc,argv);

    Widget w;
    w.resize(300,300);
    w.show();

    return a.exec();
}
#endif

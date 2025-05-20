#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#if radiobutton
class QRadioButton;
class QButtonGroup;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
#if c
public slots:
    void slotQuit();
signals:
    void clicked();
#endif
private:
    QRadioButton *radioButton[4];
    QButtonGroup *buttonGroup;
};
#endif//radiobutton
#if checkbox
class QCheckBox;
class QButtonGroup;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QCheckBox *checkBox[4];
    QButtonGroup *buttonGroup;
public slots:
    void selectButton(int id);
};
#endif
#if !scrool
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif
#endif // WIDGET_H

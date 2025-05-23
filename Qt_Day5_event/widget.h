#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextEdit>

class Widget : public QTextEdit
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    //void moveEvent(QMoveEvent*) override;
    //void closeEvent(QCloseEvent*) override;
};
#endif // WIDGET_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVector>
class QLabel;
class QPushButton;
class QButtonGroup;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    //private member variable
    QButtonGroup * buttonGroup;
    //cal label
    QLabel *m_label;
    //m_num1=saved num, m_op=saved op
    QString m_num1,m_op;
    //
    bool m_isFirst;
    const qint32 WIDTH =4;

public slots:
    void click(int);
};
#endif // WIDGET_H

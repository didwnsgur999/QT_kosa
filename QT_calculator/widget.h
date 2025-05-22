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
    QButtonGroup * buttonGroup;
    QLabel *m_label;
    QString m_num1,m_op;
    bool m_isFirst;
    const qint32 WIDTH =4;

public slots:
    void click(int);
};
#endif // WIDGET_H

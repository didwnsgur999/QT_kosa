#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QWidget>
#include <QTimer>

class CustomButton : public QWidget
{
    Q_OBJECT

public:
    CustomButton(QWidget *parent = nullptr);
    ~CustomButton();
protected:
    void paintEvent(QPaintEvent*) override;
    void enterEvent(QEnterEvent*) override;
    void leaveEvent(QEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
private:
    bool m_isEntered;
    bool m_isHighlighted;
    QTimer m_timer;
signals:
    void clicked();

};
#endif // CUSTOMBUTTON_H

#ifndef PADDLE_H
#define PADDLE_H

#include <QWidget>

class Paddle : public QWidget
{
public:
    Paddle(QWidget *parent=0);
private:
    void paintEvent(QPaintEvent*) override;
};

#endif // PADDLE_H

#ifndef BALL_H
#define BALL_H

#include <QWidget>

class Ball : public QWidget
{
public:
    Ball(QWidget*parent=0);
private:
    void paintEvent(QPaintEvent*) override;
};

#endif // BALL_H

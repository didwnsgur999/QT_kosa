#include <QPainter>
#include "ball.h"

#define RADIUS 10
Ball::Ball(QWidget *parent)
    : QWidget{parent}
{
    resize(RADIUS,RADIUS);
    setStyleSheet("background-color: rgba(0,0,0,0)");
    //setPixmap(QPixmap("./images/ball.png").scaled(RADIUS,RADIUS));
}
void Ball::paintEvent(QPaintEvent*){
    QPainter p(this);
    p.setPen(QColor(Qt::transparent));
    p.setBrush(QColor(Qt::red));
    p.drawEllipse(0,0,RADIUS,RADIUS);
}

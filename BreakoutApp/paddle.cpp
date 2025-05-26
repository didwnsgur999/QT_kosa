#include <QPainter>

#include "paddle.h"

#define WIDTH 50
#define HEIGHT 12
Paddle::Paddle(QWidget *parent)
    : QWidget{parent}
{
    resize(WIDTH,HEIGHT);
    //배경색.
    setStyleSheet("background-color: rgba(0,0,0,0)");
    //setPixmap(QPixmap("./images/paddle.png").scaled(WIDTH,HEIGHT));
}
void Paddle::paintEvent(QPaintEvent*){
    QPainter p(this);
    p.setPen(QColor(Qt::transparent));
    p.setBrush(QColor(Qt::blue));
    p.drawRoundedRect(0,0,WIDTH,HEIGHT,5,5);
}

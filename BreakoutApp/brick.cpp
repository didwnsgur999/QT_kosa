#include <QPainter>
#include "brick.h"
#include <QRandomGenerator>
#define WIDTH 50
#define HEIGHT 12
Brick::Brick(QWidget *parent)
    : QLabel{parent}
{
    resize(WIDTH,HEIGHT);
    setStyleSheet("background-color: rgba(0,0,0,0)");
    //setPixmap(QPixmap(QString("./images/brick%1.png").arg(QRandomGenerator::global()->bounded(1,6))).scaled(WIDTH,HEIGHT));
}
void Brick::paintEvent(QPaintEvent*){
    QPainter p(this);
    p.setPen(QColor(Qt::transparent));
    p.setBrush(QColor(Qt::cyan));
    p.drawRoundedRect(0,0,WIDTH,HEIGHT,5,5);
}

#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMediaplayer>
#include "brick.h"
#include "ball.h"
#include "paddle.h"

class QLabel;

class Breakout : public QWidget
{
    Q_OBJECT
private:
    static const int NO_OF_BRICKS=30;
    QMediaPlayer *bgPlayer;
    QMediaPlayer *effectPlayer;
    QLabel *scoreLab;
    Ball* ball;
    Paddle* paddle;
    Brick* bricks[NO_OF_BRICKS];
    //QLabel *ball;
    //QLabel *paddle;
    //QLabel *bricks[NO_OF_BRICKS];
    QLabel *lifeLab;
    QPixmap heartPixmap;
    int timerId;
    int xDir,yDir;
    int score,life;
protected:
    void keyPressEvent(QKeyEvent*) override;
    void mouseMoveEvent(QMouseEvent*e) override;
    void timerEvent(QTimerEvent*) override;
    void moveObjects();
    void checkCollision();
    int MOVE_SPEED;

public:
    Breakout(QWidget *parent = nullptr);
    ~Breakout();

};
#endif // BREAKOUT_H

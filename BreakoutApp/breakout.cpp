#include "breakout.h"
#include <QLabel>
#include <QApplication>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QtMultimedia>
#define WIDTH 50
#define HEIGHT 12
#define SCR_WIDTH 300
#define SCR_HEIGHT 400

Breakout::Breakout(QWidget *parent)
    : QWidget(parent),heartPixmap("heart.png"),xDir(1),yDir(-1),score(0),life(3),MOVE_SPEED(3)
{
    //SCORE LABEL
    scoreLab=new QLabel(this);
    scoreLab->setStyleSheet("QLabel{color: rgb(6,126,219); font: bold large;}");
    scoreLab->setGeometry(SCR_WIDTH*0.4,SCR_HEIGHT*0.5,120,70);
    scoreLab->setText(QString("SCORE=%1").arg(score));
    //LIFE SYSTEM DEVELOPING
    lifeLab=new QLabel(this);
    QPixmap scaledPixmap=heartPixmap.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    lifeLab->setGeometry(SCR_WIDTH*0.4,SCR_HEIGHT*0.45,20,20);
    lifeLab->setPixmap(scaledPixmap);

    //BALL LABEL
    ball=new Ball(this);
    ball->setGeometry(SCR_WIDTH*0.8,SCR_HEIGHT*0.875,10,10);
    // ball=new QLabel(this);
    // ball->setGeometry(SCR_WIDTH*0.8,SCR_HEIGHT*0.875,10,10);
    // ball->setStyleSheet("QLabel{background-color:red; border-radius: 5px;}");
    // PADDLE LABEL
    paddle=new Paddle(this);
    paddle->setGeometry(SCR_WIDTH*0.7,SCR_HEIGHT*0.9,WIDTH,HEIGHT);
    // paddle=new QLabel(this);
    // paddle->setGeometry(SCR_WIDTH*0.7,SCR_HEIGHT*0.9,WIDTH,HEIGHT);
    //paddle->setStyleSheet("QLabel{background-color:rgb(6,126,219); border:2px solid rgb(0,51,255)}");

    //Brick LABEL
    for(int y=0,i=0;y<5; y++){
        for(int x=0;x<6; x++,i++){
            bricks[i]=new Brick(this);
            bricks[i]->setGeometry(x*WIDTH,y*HEIGHT+30,WIDTH,HEIGHT);
            // bricks[i]=new QLabel(this);
            // bricks[i]->setGeometry(x*WIDTH,y*HEIGHT+30,WIDTH,HEIGHT);
            // bricks[i]->setStyleSheet("QLabel{background-color:rgb(13,238,201); border:1px solid rgb(17,159,138);}");
        }
    }
    resize(SCR_WIDTH,SCR_HEIGHT);

    setMouseTracking(true);

    QAudioOutput *bgAudioOutput = new QAudioOutput;
    bgAudioOutput->setVolume(5);

    bgPlayer=new QMediaPlayer();
    bgPlayer->setAudioOutput(bgAudioOutput);
    bgPlayer->setLoops(QMediaPlayer::Infinite);
    bgPlayer->setSource(QUrl::fromLocalFile(QFileInfo("The_Cheetahmen.mp3").absoluteFilePath()));
    bgPlayer->play();

    QAudioOutput *bgEffecOutput = new QAudioOutput;
    bgEffecOutput->setVolume(100);
    effectPlayer=new QMediaPlayer();
    effectPlayer->setAudioOutput(bgEffecOutput);
    effectPlayer->setLoops(QMediaPlayer::Once);
    effectPlayer->setSource(QUrl::fromLocalFile(QFileInfo("collision.wav").absoluteFilePath()));

    timerId = startTimer(10);
}

Breakout::~Breakout() {
    delete ball;
    delete paddle;
    for(int i=0; i<NO_OF_BRICKS; i++){
        delete bricks[i];
    }
}
void Breakout::keyPressEvent(QKeyEvent*e){
    switch(e->key()){
    case Qt::Key_Left:
        if(paddle->x()-MOVE_SPEED>=0)paddle->move(paddle->x()-MOVE_SPEED,paddle->y());
        break;
    case Qt::Key_Right:
        if(paddle->x()+MOVE_SPEED<=SCR_WIDTH-WIDTH) paddle->move(paddle->x()+MOVE_SPEED,paddle->y());
        break;
    case Qt::Key_Escape:
        qApp->exit();
        break;
    default:
        QWidget::keyPressEvent(e);
    }
}
void Breakout::mouseMoveEvent(QMouseEvent*e){
    int x=e->pos().x();
    x=(x<0)?25:(x+WIDTH>width())?width()-WIDTH:x;
    paddle->move(x,paddle->y());
}
void Breakout::timerEvent(QTimerEvent*){
    moveObjects();
    checkCollision();
}
void Breakout::moveObjects(){
    ball->move(ball->x()+xDir,ball->y()+yDir);
    if(ball->x()<=0||ball->x()+10>=SCR_WIDTH){
        xDir*=-1;
    }
    if(ball->y()<=0) yDir=1;
}
void Breakout::checkCollision(){
    if(ball->geometry().bottom()>height()){
        killTimer(timerId);
        QMessageBox::information(this,"game lose",QString("GAME LOSE!\nscore = %1").arg(score),QMessageBox::Ok);
    }
    int j=0;
    for(int i=0; i<NO_OF_BRICKS; i++){
        if(bricks[i]->isHidden())j++;
    }
    if(j==NO_OF_BRICKS){
        killTimer(timerId);
        QMessageBox::information(this,"game win","GAME WIN!",QMessageBox::Ok);
    }
    if((ball->geometry()).intersects((paddle->geometry()))){
        int paddleLpos=paddle->geometry().left();
        int ballLpos=ball->geometry().left();
        int first = paddleLpos+8;
        int second = paddleLpos+16;
        int third = paddleLpos+24;
        int fourth =  paddleLpos+32;
        if(ballLpos<first) {xDir=-1;yDir=-1;}
        if(ballLpos>=first&&ballLpos<second){xDir=-1;yDir*=-1;}
        if(ballLpos>=second&&ballLpos<third){xDir=0;yDir=-1;}
        if(ballLpos>=third&&ballLpos<fourth){xDir=1;yDir*=-1;}
        if(ballLpos>fourth) {xDir=1;yDir=-1;}
        effectPlayer->stop();
        effectPlayer->play();
    }
    for(int i=0; i<NO_OF_BRICKS; i++){
        if((ball->geometry()).intersects(bricks[i]->geometry())){
            if(bricks[i]->isHidden()) continue;
            int ballLeft=ball->geometry().left();
            int ballHeight=ball->geometry().height();
            int ballwidth=ball->geometry().width();
            int ballTop=ball->geometry().top();
            QPoint pointRight(ballLeft+ballwidth+1,ballTop);
            QPoint pointLeft(ballLeft-1,ballTop);
            QPoint pointTop(ballLeft,ballTop-1);
            QPoint pointBottom(ballLeft,ballTop+ballHeight+1);
            if(bricks[i]->geometry().contains(pointRight)) xDir=-1;
            else if(bricks[i]->geometry().contains(pointLeft)) xDir=1;
            if(bricks[i]->geometry().contains(pointTop))yDir=1;
            else if(bricks[i]->geometry().contains(pointBottom))yDir=-1;
            bricks[i]->setHidden(true);
            effectPlayer->stop();
            effectPlayer->play();
            score++;
            if((score+1)%4==0)MOVE_SPEED+=100;
            scoreLab->setText(QString("SCORE=%1").arg(score));
        }
    }
}

#ifndef BRICK_H
#define BRICK_H

#include <QLabel>

class Brick : public QLabel
{
public:
    Brick(QWidget*parent=0);
private:
    void paintEvent(QPaintEvent*) override;
};

#endif // BRICK_H

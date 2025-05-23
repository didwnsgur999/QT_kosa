#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

class Application : public QApplication
{
public:
    Application(int&,char**);
    virtual bool notify(QObject *receiver, QEvent *e) override;
};

#endif // APPLICATION_H

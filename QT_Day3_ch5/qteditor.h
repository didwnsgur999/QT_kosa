#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QMainWindow>
#include <QTextEdit>
#include <QStatusBar>
class QAction;

class qteditor : public QMainWindow
{
    Q_OBJECT

public:
    qteditor(QWidget *parent = nullptr);
    ~qteditor();
private:
    //template <typename T>
    //QAction* makeAction(QString icon, QString text,T shortCut,QString toolTip,QObject*recv,const char* slot);
    template <typename T,typename R>
    QAction* makeAction(R icon, QString text,T shortCut,QString toolTip,QObject*recv,const char* slot);
    template <>
    QAction *makeAction(QString icon, QString text, \
                        const char* shortCut, QString toolTip, \
                        QObject* recv, const char* slot);
    template <typename T,typename Functor>
    QAction* makeAction(QString icon, QString text,T shortCut,QString toolTip,Functor lambda);

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveasFile();
    void printFile();
};
#endif // QTEDITOR_H

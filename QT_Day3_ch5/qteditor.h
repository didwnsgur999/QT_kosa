#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QMainWindow>
#include <QTextEdit>
#include <QStatusBar>
#include <QDialog>
#include <QHash>
#include <QFontComboBox>
#include <QDoubleSpinBox>
class QAction;
class QTextEdit;
class QMdiArea;
class qteditor : public QMainWindow
{
    Q_OBJECT

public:
    qteditor(QWidget *parent = nullptr);
    ~qteditor();
private:
    QMenu *windowMenu;

    QHash<QAction*,QWidget*> windowHash;
    QMdiArea *mdiArea;
    QFontComboBox *fontComboBox;
    QDoubleSpinBox *sizeSpinBox;
    //QTextEdit *textEdit;
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
    QTextEdit *newFile();
    void openFile();
    void saveFile();
    void saveasFile();
    void printFile();
    void setColor();
    void setFont();
    void Help();
    //void setFontWidget();
};
#endif // QTEDITOR_H

#include "qteditor.h"
#include <QTextEdit>
#include <QLabel>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStyle>
#include <QKeySequence>
#include <QApplication>
#include <QToolBar>
#include <QFontComboBox>
#include <QDoubleSpinBox>
#include <QStatusBar>
qteditor::qteditor(QWidget *parent)
    : QMainWindow(parent)
{
#if !textedit
    QTextEdit* textEdit=new QTextEdit(this);
    setCentralWidget(textEdit);
#endif
#if !menubar
    QMenuBar* menuBar=new QMenuBar(this);
    setMenuBar(menuBar);
#endif
#if action
    QIcon icon=style()->standardIcon(QStyle::SP_DialogSaveButton);
    QAction *newAct=new QAction(icon,"&New",this);
    //QAction *newAct=new QAction(QIcon("new.png"),"&New",this);
    newAct->setShortcut(tr("Ctrl+N"));
    newAct->setStatusTip(tr("make new file"));
    connect(newAct,SIGNAL(triggered()),SLOT(newFile()));
#endif
#if !actionusing_tem
    //QAction *fileAct=makeAction("new.png","&New",tr("Ctrl+N"),tr("make new file"),this,SLOT(newFile()));
    QAction *fileAct=makeAction(style()->standardIcon(QStyle::SP_DialogSaveButton),"&New",tr("Ctrl+N"),tr("make new file"),this,SLOT(newFile()));
    QAction *openAct=makeAction("open.png","&Open",tr("Ctrl+O"),tr("open file"),this,SLOT(openFile()));
    QAction *saveAct=makeAction("save.png","&Save",tr("Ctrl+S"),tr("save file"),this,SLOT(saveFile()));
    QAction *saveasAct=makeAction("saveas.png","&Save As",tr("Ctrl+A"),tr("save as other file"),this,SLOT(saveasFile()));
    QAction *printAct=makeAction("print.png","&Print",tr("Ctrl+P"),tr("print file"),this,SLOT(printFile()));
    //QAction *quitAct=makeAction("quit.png","&Quit",tr("Ctrl+Q"),tr("quit file"),qApp,SLOT(quit()));
    QAction *quitAct=makeAction("quit.png","&Quit",tr("Ctrl+Q"),tr("quit file"),[=](){qApp->quit();});
#endif
#if !menu
    QMenu *fileMenu=menuBar->addMenu("&file");
    fileMenu->addAction(fileAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveasAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);
#endif
#if !actioneditusing_tem
    QAction *undoAct=makeAction("undo.png","&Undo",tr("Ctrl+Z"),tr("undo"),textEdit,SLOT(undo()));
    QAction *redoAct=makeAction("redo.png","&redo",tr("Ctrl+R"),tr("redo"),textEdit,SLOT(redo()));
    QAction *copyAct=makeAction("copy.png","&copy",tr("Ctrl+C"),tr("copy"),textEdit,SLOT(copy()));
    QAction *cutAct=makeAction("cut.png","&cut",tr("Ctrl+X"),tr("cut"),textEdit,SLOT(cut()));
    QAction *pasteAct=makeAction("paste.png","&paste",tr("Ctrl+V"),tr("paste"),textEdit,SLOT(paste()));
    QAction *zoomInAct=makeAction("zoomIn.png","&zoomIn",tr("Ctrl+I"),tr("zoomIn"),textEdit,SLOT(zoomIn()));
    QAction *zoomOutAct=makeAction("zoomOut.png","&zoomOut",tr("Ctrl+Alt+I"),tr("zoomOut"),textEdit,SLOT(zoomOut()));
#endif
#if !editmenu
    QMenu*editMenu=menuBar->addMenu("&edit");
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(copyAct);
    editMenu->addAction(cutAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();
    editMenu->addAction(zoomInAct);
    editMenu->addAction(zoomOutAct);
#endif
#if !formatMenu+action
    QMenu*formatMenu=menuBar->addMenu("&Format");
    QMenu*alignMenu=formatMenu->addMenu("&Align");
    //page 40 triggered자체의 넘겨주는 인자가 없기때문에 Qt::AlignCenter를 넘겨줄 방법이 없어서 align방식을 변경할 수 없다.
    //SIGNAL SLOT 사용하려면 사용자 slot필요.
    QAction *leftAct=makeAction("left.png","&Left",tr("Ctrl+1"),tr("Left"),[=]{textEdit->setAlignment(Qt::AlignLeft);});
    QAction *centerAct=makeAction("center.png","&Center",tr("Ctrl+2"),tr("Center"),[=]{textEdit->setAlignment(Qt::AlignCenter);});
    QAction *rightAct=makeAction("right.png","&Right",tr("Ctrl+3"),tr("Right"),[=]{textEdit->setAlignment(Qt::AlignRight);});
    QAction *justifyAct=makeAction("justify.png","&Justify",tr("Ctrl+4"),tr("justify"),[=]{textEdit->setAlignment(Qt::AlignJustify);});
    alignMenu->addAction(leftAct);
    alignMenu->addAction(centerAct);
    alignMenu->addAction(rightAct);
    alignMenu->addAction(justifyAct);
#endif
#if !toolbar+windowmenu
    QToolBar* fileToolBar=addToolBar("&file");
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    fileToolBar->addAction(fileAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(quitAct);

    QMenu *windowMenu=menuBar->addMenu("&Window");
    QMenu *toolbarMenu=windowMenu->addMenu("&Toolbar");
    toolbarMenu->addAction(fileToolBar->toggleViewAction());

    QFontComboBox *fontComboBox=new QFontComboBox(this);
    connect(fontComboBox,SIGNAL(currentFontChanged(QFont)),textEdit,SLOT(setCurrentFont(QFont)));
    QDoubleSpinBox *sizeSpinBox=new QDoubleSpinBox(this);
    connect(sizeSpinBox,SIGNAL(valueChanged(double)),textEdit,SLOT(setFontPointSize(qreal)));
    addToolBarBreak();
    QToolBar *formatToolBar= addToolBar("&Format");
    formatToolBar->addSeparator();
    formatToolBar->addWidget(fontComboBox);
    formatToolBar->addWidget(sizeSpinBox);
#endif
#if !statusBar
    QStatusBar* statusbar=statusBar();
    QLabel * statusLabel = new QLabel("Qt Editor",statusbar);
    statusLabel->setObjectName("Status name");
    statusbar->addPermanentWidget(statusLabel);
    statusbar->showMessage("started",1500);

#endif

}
void qteditor::newFile(){
    qDebug("Make new File");
}
void qteditor::openFile(){
    qDebug("open File");
}
void qteditor::saveFile(){
    qDebug("save File");
}
void qteditor::saveasFile(){
    qDebug("save as File");
}
void qteditor::printFile(){
    qDebug("print File");
}
// template<typename T>
// QAction *qteditor::makeAction(QString icon, QString text,T shortCut,QString toolTip,QObject*recv,const char* slot){
//     QAction *newAct=new QAction(QIcon(icon),text,this);
//     newAct->setShortcut(shortCut);
//     newAct->setStatusTip(toolTip);
//     connect(newAct,SIGNAL(triggered()),recv,slot);
//     return newAct;
// }
template <typename T,typename R>
QAction* qteditor::makeAction(R icon, QString text,T shortCut,QString toolTip,QObject*recv,const char* slot){
    R icon2=icon;
    QAction *newAct=new QAction(QIcon(icon2),text,this);
    newAct->setShortcut(QString(shortCut));
    newAct->setStatusTip(toolTip);
    connect(newAct,SIGNAL(triggered()),recv,slot);
    return newAct;
}
template<>
QAction *qteditor::makeAction(QString icon, QString text,const char* shortCut,QString toolTip,QObject*recv,const char* slot){
    QAction *newAct=new QAction(QIcon(icon),text,this);
    newAct->setShortcut(QString(shortCut));
    newAct->setStatusTip(toolTip);
    connect(newAct,SIGNAL(triggered()),recv,slot);
    return newAct;
}
template <typename T,typename Functor>
QAction* qteditor::makeAction(QString icon, QString text,T shortCut,QString toolTip,Functor lambda){
    QAction *newAct=new QAction(QIcon(icon),text,this);
    QKeySequence keySequence(shortCut);
    newAct->setShortcut(keySequence);
    newAct->setStatusTip(toolTip);
    connect(newAct,&QAction::triggered,this,lambda);
    return newAct;
}
qteditor::~qteditor() {

}

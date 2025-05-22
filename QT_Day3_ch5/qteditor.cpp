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
#include <QDockWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QColorDialog>
#include <QFontDialog>
#include <QPrintDialog>
#include <QPrinter>
#include <QHash>
qteditor::qteditor(QWidget *parent)
    : QMainWindow(parent)
{
//다른 위젯들을 담는 dock
#if !dockwidget
    QWidget *w = new QWidget(this);
    QLabel *label=new QLabel("Dock Widget",w);
    label->setAlignment(Qt::AlignCenter);
    QDockWidget *dock=new QDockWidget("Dock Widget",this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea,dock);
    dock->setWidget(w);
#endif

#if !menubar
    QMenuBar* menuBar=new QMenuBar(this);
    setMenuBar(menuBar);
#endif //menubar

#if !windowmenu
    windowMenu=menuBar->addMenu("&Window");
#endif //windowmenu

    //초기값 설정.
    mdiArea=new QMdiArea(this);
    setCentralWidget(mdiArea);
    QTextEdit* textEdit=newFile();

#if action_single
    QIcon icon=style()->standardIcon(QStyle::SP_DialogSaveButton);
    QAction *newAct=new QAction(icon,"&New",this);
    //QAction *newAct=new QAction(QIcon("new.png"),"&New",this);
    newAct->setShortcut(tr("Ctrl+N"));
    newAct->setStatusTip(tr("make new file"));
    connect(newAct,SIGNAL(triggered()),SLOT(_newFile()));
#endif //actionsingle

#if !actionusing_template
#if SDI
    //QAction *fileAct=makeAction(":/images/new.png","&New",tr("Ctrl+N"),tr("make new file"),this,SLOT(_newFile()));
    //QAction *fileAct=makeAction(style()->standardIcon(QStyle::SP_DialogSaveButton),"&New",tr("Ctrl+N"),tr("make new file"),this,SLOT(_newFile()));
#else //MDI
    QAction *fileAct=makeAction(":/images/new.png","&New",tr("Ctrl+N"),tr("make new file"),[&](){textEdit=newFile();});
#endif
    QAction *openAct=makeAction(":/images/open.png","&Open",tr("Ctrl+O"),tr("open file"),this,SLOT(openFile()));
    QAction *saveAct=makeAction(":/images/save.png","&Save",tr("Ctrl+S"),tr("save file"),this,SLOT(saveFile()));
    QAction *saveasAct=makeAction(":/images/saveas.png","&Save As",tr("Ctrl+A"),tr("save as other file"),this,SLOT(saveasFile()));
    QAction *printAct=makeAction(":/images/print.png","&Print",tr("Ctrl+P"),tr("print file"),this,SLOT(printFile()));
    //QAction *quitAct=makeAction(":/images/quit.png","&Quit",tr("Ctrl+Q"),tr("quit file"),qApp,SLOT(quit()));
    QAction *quitAct=makeAction(":/images/quit.png","&Quit",tr("Ctrl+Q"),tr("quit file"),[=](){qApp->quit();});
#endif//actionusing template, fileACT

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
#endif//filemenu

#if actioneditusing_tem_SDI
    QAction *undoAct=makeAction(":/images/undo.png","&Undo",tr("Ctrl+Z"),tr("undo"),\
                                  [=]{QMdiSubWindow *mdiSubWindow=mdiArea->currentSubWindow();
                                        if(mdiSubWindow){QTextEdit *textEdit=dynamic_cast<QTextEdit*>(mdiSubWindow->widget());
                                        textEdit->undo();}});
    //QAction *undoAct=makeAction(":/images/undo.png","&Undo",tr("Ctrl+Z"),tr("undo"),textEdit,SLOT(undo()));
    QAction *redoAct=makeAction(":/images/redo.png","&redo",tr("Ctrl+R"),tr("redo"),textEdit,SLOT(redo()));
    QAction *copyAct=makeAction(":/images/copy.png","&copy",tr("Ctrl+C"),tr("copy"),textEdit,SLOT(copy()));
    QAction *cutAct=makeAction(":/images/cut.png","&cut",tr("Ctrl+X"),tr("cut"),textEdit,SLOT(cut()));
    QAction *pasteAct=makeAction(":/images/paste.png","&paste",tr("Ctrl+V"),tr("paste"),textEdit,SLOT(paste()));
    QAction *zoomInAct=makeAction(":/images/zoomIn.png","zoom&In",tr("Ctrl+I"),tr("zoomIn"),textEdit,SLOT(zoomIn()));
    QAction *zoomOutAct=makeAction(":/images/zoomOut.png","zoom&Out",tr("Ctrl+Alt+I"),tr("zoomOut"),textEdit,SLOT(zoomOut()));
#else
    QAction *undoAct=makeAction(":/images/undo.png","&Undo",tr("Ctrl+Z"),tr("undo"),\
                                  [=]{QMdiSubWindow *mdiSubWindow=mdiArea->currentSubWindow();
                                        if(mdiSubWindow){QTextEdit *textEdit=dynamic_cast<QTextEdit*>(mdiSubWindow->widget());
                                        textEdit->undo();}});
    QAction *redoAct=makeAction(":/images/redo.png","&Redo",tr("Ctrl+R"),tr("redo"),\
                                  [=]{QMdiSubWindow *mdiSubWindow=mdiArea->currentSubWindow();
                                        if(mdiSubWindow){QTextEdit *textEdit=dynamic_cast<QTextEdit*>(mdiSubWindow->widget());
                                        textEdit->redo();}});
    QAction *copyAct=makeAction(":/images/copy.png","&Copy",tr("Ctrl+C"),tr("copy"),\
                                  [=]{QMdiSubWindow *mdiSubWindow=mdiArea->currentSubWindow();
                                        if(mdiSubWindow){QTextEdit *textEdit=dynamic_cast<QTextEdit*>(mdiSubWindow->widget());
                                        textEdit->copy();}});
    QAction *cutAct=makeAction(":/images/cut.png","&Cut",tr("Ctrl+X"),tr("cut"),\
                                  [=]{QMdiSubWindow *mdiSubWindow=mdiArea->currentSubWindow();
                                        if(mdiSubWindow){QTextEdit *textEdit=dynamic_cast<QTextEdit*>(mdiSubWindow->widget());
                                        textEdit->cut();}});
    QAction *pasteAct=makeAction(":/images/paste.png","&Paste",tr("Ctrl+V"),tr("paste"),\
                                  [=]{QMdiSubWindow *mdiSubWindow=mdiArea->currentSubWindow();
                                        if(mdiSubWindow){QTextEdit *textEdit=dynamic_cast<QTextEdit*>(mdiSubWindow->widget());
                                        textEdit->paste();}});
    QAction *zoomInAct=makeAction(":/images/zoomIn.png","zoom&In",tr("Ctrl+I"),tr("zoomIn"),\
                                  [=]{QMdiSubWindow *mdiSubWindow=mdiArea->currentSubWindow();
                                        if(mdiSubWindow){QTextEdit *textEdit=dynamic_cast<QTextEdit*>(mdiSubWindow->widget());
                                        textEdit->zoomIn();}});
    QAction *zoomOutAct=makeAction(":/images/zoomOut.png","zoom&Out",tr("Ctrl+Alt+I"),tr("zoomOut"),\
                                    [=]{QMdiSubWindow *mdiSubWindow=mdiArea->currentSubWindow();
                                        if(mdiSubWindow){QTextEdit *textEdit=dynamic_cast<QTextEdit*>(mdiSubWindow->widget());
                                        textEdit->zoomOut();}});
    QAction *prevWinAct=makeAction(":/images/prev.png","&Prev",tr("Ctrl+6"),tr("Prev"),[=]{mdiArea->activatePreviousSubWindow();});
    QAction *nextWinAct=makeAction(":/images/next.png","&Next",tr("Ctrl+7"),tr("Next"),[=]{mdiArea->activateNextSubWindow();});
    QAction *cascadeWinAct=makeAction(":/images/cascade.png","&Cascade",tr("Ctrl+8"),tr("Cascade"),[=]{mdiArea->cascadeSubWindows();});
    QAction *tileWinAct=makeAction(":/images/tile.png","&Tile",tr("Ctrl+9"),tr("Tile"),[=]{mdiArea->tileSubWindows();});
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
    editMenu->addSeparator();
    editMenu->addAction(prevWinAct);
    editMenu->addAction(nextWinAct);
    editMenu->addAction(cascadeWinAct);
    editMenu->addAction(tileWinAct);
#endif //editmenu

#if !formatMenu+action
    QMenu*formatMenu=menuBar->addMenu("&Format");
    QMenu*alignMenu=formatMenu->addMenu("&Align");
#if SDI
    QAction *fontAct=makeAction(":/images/font.png","&font",tr("Ctrl+F"),tr("Font"),[=]{textEdit->setCurrentFont(QFont("Arial", 12));});
    QAction *colorAct=makeAction(":/images/color.png","&color",tr("Ctrl+G"),tr("Color"),[=]{textEdit->setTextColor(QColor("Blue"));});
    QAction *leftAct=makeAction(":/images/left.png","&Left",tr("Ctrl+1"),tr("Left"),[=]{textEdit->setAlignment(Qt::AlignLeft);});
    QAction *centerAct=makeAction(":/images/center.png","&Center",tr("Ctrl+2"),tr("Center"),[=]{textEdit->setAlignment(Qt::AlignCenter);});
    QAction *rightAct=makeAction(":/images/right.png","&Right",tr("Ctrl+3"),tr("Right"),[=]{textEdit->setAlignment(Qt::AlignRight);});
    QAction *justifyAct=makeAction(":/images/justify.png","&Justify",tr("Ctrl+4"),tr("justify"),[=]{textEdit->setAlignment(Qt::AlignJustify);});
#else
    //page 40 triggered자체의 넘겨주는 인자가 없기때문에 Qt::AlignCenter를 넘겨줄 방법이 없어서 align방식을 변경할 수 없다.
    //SIGNAL SLOT 사용하려면 사용자 slot필요.
    QAction *fontAct=makeAction(":/images/font.png","&font",tr("Ctrl+F"),tr("Font"),this,SLOT(setFont()));
    QAction *colorAct=makeAction(":/images/color.png","&color",tr("Ctrl+G"),tr("Color"),this,SLOT(setColor()));
    // QAction *fontAct=makeAction(":/images/font.png","&font",tr("Ctrl+F"),tr("Font"),\
    //                               [=]{QMdiSubWindow *mdiSubWindow=mdiArea->currentSubWindow();
    //                                     if(mdiSubWindow){QTextEdit *textEdit=dynamic_cast<QTextEdit*>(mdiSubWindow->widget());
    //                                     textEdit->setCurrentFont(QFont("Arial", 12));}});
    // QAction *colorAct=makeAction(":/images/color.png","&color",tr("Ctrl+G"),tr("Color"),\
    //                                 [=]{QMdiSubWindow *mdiSubWindow=mdiArea->currentSubWindow();
    //                                     if(mdiSubWindow){QTextEdit *textEdit=dynamic_cast<QTextEdit*>(mdiSubWindow->widget());
    //                                     textEdit->setTextColor(QColor("Blue"));}});
    QAction *leftAct=makeAction(":/images/left.png","&Left",tr("Ctrl+1"),tr("Left"),\
                                    [=]{QMdiSubWindow *mdiSubWindow=mdiArea->currentSubWindow();
                                        if(mdiSubWindow){QTextEdit *textEdit=dynamic_cast<QTextEdit*>(mdiSubWindow->widget());
                                        textEdit->setAlignment(Qt::AlignLeft);}});
    QAction *centerAct=makeAction(":/images/center.png","&Center",tr("Ctrl+2"),tr("Center"),\
                                    [=]{QMdiSubWindow *mdiSubWindow=mdiArea->currentSubWindow();
                                        if(mdiSubWindow){QTextEdit *textEdit=dynamic_cast<QTextEdit*>(mdiSubWindow->widget());
                                        textEdit->setAlignment(Qt::AlignCenter);}});
    QAction *rightAct=makeAction(":/images/right.png","&Right",tr("Ctrl+3"),tr("Right"),\
                                   [=]{QMdiSubWindow *mdiSubWindow=mdiArea->currentSubWindow();
                                        if(mdiSubWindow){QTextEdit *textEdit=dynamic_cast<QTextEdit*>(mdiSubWindow->widget());
                                        textEdit->setAlignment(Qt::AlignRight);}});
    QAction *justifyAct=makeAction(":/images/justify.png","&Justify",tr("Ctrl+4"),tr("justify"),\
                                     [=]{QMdiSubWindow *mdiSubWindow=mdiArea->currentSubWindow();
                                        if(mdiSubWindow){QTextEdit *textEdit=dynamic_cast<QTextEdit*>(mdiSubWindow->widget());
                                        textEdit->setAlignment(Qt::AlignJustify);}});
#endif
    alignMenu->addAction(fontAct);
    alignMenu->addAction(colorAct);
    alignMenu->addAction(leftAct);
    alignMenu->addAction(centerAct);
    alignMenu->addAction(rightAct);
    alignMenu->addAction(justifyAct);
#endif

#if !toolbar
    QToolBar* fileToolBar=addToolBar("&file");
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    fileToolBar->addAction(fileAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(quitAct);

    QMenu *toolbarMenu=windowMenu->addMenu("&Toolbar");
    toolbarMenu->addAction(fileToolBar->toggleViewAction());
    fontComboBox=new QFontComboBox(this);
    sizeSpinBox=new QDoubleSpinBox(this);
#if SDI
    connect(fontComboBox,SIGNAL(currentFontChanged(QFont)),textEdit,SLOT(setCurrentFont(QFont)));
    connect(sizeSpinBox,SIGNAL(valueChanged(double)),textEdit,SLOT(setFontPointSize(qreal)));
#else
    connect(fontComboBox,&QFontComboBox::currentFontChanged,\
                                    [=](QFont Font){QMdiSubWindow *mdiSubWindow=mdiArea->currentSubWindow();
                                        if(mdiSubWindow){QTextEdit *textEdit=dynamic_cast<QTextEdit*>(mdiSubWindow->widget());
                                        textEdit->setCurrentFont(Font);}});
    connect(sizeSpinBox,&QDoubleSpinBox::valueChanged,\
                                    [=](double dou){QMdiSubWindow *mdiSubWindow=mdiArea->currentSubWindow();
                                        if(mdiSubWindow){QTextEdit *textEdit=dynamic_cast<QTextEdit*>(mdiSubWindow->widget());
                                        textEdit->setFontPointSize(static_cast<qreal>(dou));}});
#endif //SDI
    addToolBarBreak();
    QToolBar *formatToolBar= addToolBar("&Format");
    formatToolBar->addSeparator();
    formatToolBar->addWidget(fontComboBox);
    formatToolBar->addWidget(sizeSpinBox);
#endif //Toolbar

#if !Helpmenu
    QMenu*helpMenu=menuBar->addMenu("&Help");
    QAction *helpAct=makeAction(":/images/help.png","&help",tr("Ctrl+Alt+H"),tr("help file"),this,SLOT(Help()));
    helpMenu->addAction(helpAct);
#endif //helpmenu

#if !statusBar
    QStatusBar* statusbar=statusBar();
    QLabel * statusLabel = new QLabel("Qt Editor",statusbar);
    statusLabel->setObjectName("Status name");
    statusbar->addPermanentWidget(statusLabel);
    statusbar->showMessage("started",1500);
#endif //statusbar

#if !dockshow
    toolbarMenu->addAction(dock->toggleViewAction());
#endif //dock show
} //end ofqteditor


QTextEdit* qteditor::newFile(){
    qDebug("Make new File");
    QAction *windowAct=new QAction("NewFile",this);
    windowMenu->addAction(windowAct);
    QTextEdit *textEdit=new QTextEdit();

    connect(windowAct,SIGNAL(triggered()),textEdit,SLOT(setFocus()));
    connect(textEdit,SIGNAL(destroyed(QObject*)),textEdit,SLOT(deleteLater()));
    connect(textEdit,SIGNAL(destroyed(QObject*)),windowAct,SLOT(deleteLater()));
    mdiArea->addSubWindow(textEdit);
    textEdit->show();
    windowHash[windowAct]=textEdit;
    return textEdit;
}
void qteditor::openFile(){
    qDebug("Open a File");

    QString filename = QFileDialog::getOpenFileName(this,"Select file to open",QDir::home().dirName(),"Text File(*.txt *.html *.c *.cpp *.h)");
    if(!filename.length()) return;

    QFileInfo fileInfo(filename);
    if(fileInfo.isReadable()){
        QFile file(filename);
        file.open(QIODevice::ReadOnly|QIODevice::Text);
        QByteArray msg=file.readAll();
        file.close();

        QTextEdit *textEdit=newFile();
        textEdit->setWindowTitle(filename);
        windowHash.key(textEdit)->setText(filename);

        if(fileInfo.suffix()=="htm"||fileInfo.suffix()=="html")
            textEdit->setHtml(msg);
        else
            textEdit->setPlainText(msg);
    }else QMessageBox::warning(this,"error","Can't read the file",QMessageBox::Ok);
    qDebug()<<filename;
}
void qteditor::saveFile(){
    QMdiSubWindow *window=mdiArea->currentSubWindow();
    if(window!=nullptr){
        QTextEdit *textEdit = (QTextEdit*)(window->widget());
        QString filename = QFileDialog::getSaveFileName(this,"Select file to save",".","Text File(*.txt *.html *.c *.cpp *.h)");
        if(!filename.length()){
            filename=QFileDialog::getSaveFileName(this,"Select a file to save",".","Text File(*.txt *.html *.c *.cpp *.h)");
            if(!filename.length()) return;
            textEdit->setWindowTitle(filename);
            windowHash.key(textEdit)->setText(filename);
        }
        QFile file(filename);
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        QFileInfo fileInfo(filename);
        if(fileInfo.isWritable()){
            QByteArray msg=(fileInfo.suffix()=="htm"||fileInfo.suffix()=="html")?\
                            textEdit->toHtml().toUtf8():textEdit->toPlainText().toUtf8();
            file.write(msg);
        }else QMessageBox::warning(this,"error","Can't save the file",QMessageBox::Ok);
        file.close();
    }
}
void qteditor::saveasFile(){
    QMdiSubWindow *window=mdiArea->currentSubWindow();
    if(window!=nullptr){
        QTextEdit *textEdit = (QTextEdit*)(window->widget());
        QString filename = QFileDialog::getSaveFileName(this,"Select file to save",".","Text File(*.txt *.html *.c *.cpp *.h)");
        if(!filename.length()) return;
        QFile* file=new QFile(filename);
        file->open(QIODevice::WriteOnly|QIODevice::Text);
        QFileInfo fileInfo(filename);
        if(fileInfo.isWritable()){
            QByteArray msg=(fileInfo.suffix()=="htm"||fileInfo.suffix()=="html")?\
                            textEdit->toHtml().toUtf8():textEdit->toPlainText().toUtf8();
            file->write(msg);
        }else QMessageBox::warning(this,"error","Can't save the file",QMessageBox::Ok);
        file->close();
    }
}
void qteditor::printFile(){
    QPrinter printer(QPrinter::HighResolution);
    printer.setFullPage(true);
    QPrintDialog printDialog(&printer,this);
    if(printDialog.exec()==QDialog::Accepted){
        QTextEdit *textEdit=(QTextEdit*)mdiArea->currentSubWindow()->widget();
        textEdit->print(&printer);
    }
}
void qteditor::Help(){
    QMessageBox::information(this, tr("Aboutqt"),tr("Made by Yang\nVersion: 2025.05.22\nThank you for using this program."));
    //QApplication::aboutQt();
}
void qteditor::setColor(){
    QTextEdit *textEdit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QColor color = QColorDialog::getColor(textEdit->textColor(),this);
    if(color.isValid())textEdit->setTextColor(color);
}
void qteditor::setFont(){
    bool ok;
    QTextEdit *textEdit=(QTextEdit*)mdiArea->currentSubWindow()->widget();
    QFont font= QFontDialog::getFont(&ok,textEdit->currentFont(),this);
    if(ok)textEdit->setCurrentFont(font);
}
// void qteditor::setFontWidget(){
//     QTextEdit* textedit=(QTextEdit*)mdiArea->currentSubWindow()->widget();
//     QFont font = textedit->currentFont();
//     fontComboBox->blockSignals(true);
//     sizeSpinBox->blockSignals(true);
//     fontComboBox->setCurrentFont(font);
//     sizeSpinBox->setValue(font.pointSizeF());
//     fontComboBox->blockSignals(false);
//     sizeSpinBox->blockSignals(false);
// }
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

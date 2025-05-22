#include "dialog.h"
#include <QMessageBox>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
#if !messagebox
    QMessageBox *messageBox=new QMessageBox();
    messageBox=QMessageBox::information(this,"QMessageBox::showHelp()","information",QMessageBox::aboutQt(this));


#endif

}

Dialog::~Dialog() {}

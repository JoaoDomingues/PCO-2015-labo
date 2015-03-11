#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QList>

#include "mythread.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    
private:
    QList<QFuture> threadList;
    Ui::Dialog *ui;

private slots:
    void startThreads();
};

#endif // DIALOG_H

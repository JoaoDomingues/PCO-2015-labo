#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QElapsedTimer>
#include <QTimer>
#include <QRegExp>
#include <QtCore>

#include "threadmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    static const QString validChars;

    Ui::MainWindow  *ui;
    ThreadManager   *threadManager;

    QElapsedTimer   chronometer;
    QRegExp         hashValidationRegExp;

    QFuture<QString>        hackingAsync;
    QFutureWatcher<QString> hackingWatcher;

    double  progress;
    bool    isHacking;

public:
    explicit MainWindow(QWidget *parent = 0);

signals:
    
public slots:
    void prepareHacking();
    void endHacking();
    void incrementProgressBar(double percent);
};

#endif // MAINWINDOW_H

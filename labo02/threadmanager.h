#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <QObject>
#include <QString>
#include "hackthread.h"

class ThreadManager: public QObject
{
    Q_OBJECT
private:
    QString answer;
    hackThread[] *thread;

public:
    ThreadManager(QObject *parent);
    QString startHacking(
            QString charset,
            QString salt,
            QString hash,
            unsigned int nbChars,
            unsigned int nbThreads
    );

public slots:
    void iFoundIt(QString answer);
    /*
     * Reçoit la progression depuis hackthread
     */
    void incrementPBar(double percent);

signals:
    /*
     * Permet de retransmettre le signal de progression reçu depuis hacktread à mainwindow
     */
    void incrementPercentComputed(double percent);

};

#endif // THREADMANAGER_H

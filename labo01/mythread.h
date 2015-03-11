#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QtConcurrent/QtConcurrent>
#include <QThread>


class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(long unsigned int paramNbIterations,QObject *parent = 0);
    static unsigned long compteur;
signals:
    
public slots:

protected:
    void run();

private:
    long unsigned int nbIterations;

};

#endif // MYTHREAD_H

#ifndef HACKTHREAD_H
#define HACKTHREAD_H

#include <QtConcurrent/QtConcurrent>
#include <QThread>

class hackThread : public QThread
{
    Q_OBJECT
public:
    explicit hackThread(QString charset, QString salt, QString hash, unsigned int nbChars, long long unsigned int nbToCompute, long long unsigned int borneDepart,QObject *parent = 0);
signals:

public slots:

protected:
    void run();

private:
    QString charset;

    QString salt;
    QString hash;

    unsigned int nbChars;
    long long unsigned int nbToCompute;

    long long unsigned int borneDepart;

    QString currentPasswordString;

signals:
    void incrementPBar(double percentComputed);
    void iFoundIt(QString answer);
};

#endif // HACKTHREAD_H

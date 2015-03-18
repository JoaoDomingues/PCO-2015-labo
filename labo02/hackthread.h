/*
 * Bastien Rouiller & Stéphane Donnet
 * Lab02
 * PCO
 */

#ifndef HACKTHREAD_H
#define HACKTHREAD_H

#include <QtConcurrent/QtConcurrent>
#include <QThread>

class hackThread : public QThread
{
    Q_OBJECT
public:
    explicit hackThread(QString charset, QString salt, QString hash, unsigned int nbChars, long long unsigned int nbToCompute, long long unsigned int borneDepart, long long unsigned int nbPossibilite, QObject *parent = 0);
    void stop();
signals:

public slots:

protected:
    void run();

private:
    QString charset;

    long long unsigned int nbPossibilite;
    QString salt;
    QString hash;
    bool isRunning;

    unsigned int nbChars;
    long long unsigned int nbToCompute;

    long long unsigned int borneDepart;

    QString currentPasswordString;

signals:
    void incrementBar(double percentComputed);
    void iFoundIt(QString answer);
};

#endif // HACKTHREAD_H

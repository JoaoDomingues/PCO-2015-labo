#include "mythread.h"

unsigned long int MyThread::compteur;

MyThread::MyThread(long unsigned int paramNbIterations, QObject *parent) :
    QThread(parent)
{
    nbIterations = paramNbIterations;
}

void MyThread::run()
{
    long unsigned int i = 0;
    while (i < nbIterations)
    {
        compteur++;
        i++;
    }
}

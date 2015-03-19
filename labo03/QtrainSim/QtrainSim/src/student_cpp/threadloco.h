#ifndef THREADLOCO_H
#define THREADLOCO_H

#include <QThread>
#include <QList>

#include "locomotive.h"
#include "ctrain_handler.h"

class ThreadLoco: public QThread
{
    Q_OBJECT
public:
    ThreadLoco();
    ThreadLoco(int numero, int vitesse, int position1, int position2, QList<int> parcours);
    void setNumero(int numero);
    void setVitesse(int vitesse);
    void setPosition(int position1, int position2);
    void setPosition1(int position1);
    void setPosition2(int position2);
    void setParcours(QList<int> parcours);
    virtual void run(); Q_DECL_OVERRIDE
    void arreter();
    ~ThreadLoco();
private:
    Locomotive locomotive;
    int numero;
    int vitesse;
    int position1;
    int position2;
    QList<int> parcours;
};

#endif // THREADLOCO_H

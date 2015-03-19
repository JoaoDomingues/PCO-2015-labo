#include "threadloco.h"

ThreadLoco::ThreadLoco()
{

}

ThreadLoco::ThreadLoco(int numero, int vitesse, int position1, int position2, QList<int> parcours):
    numero(numero), vitesse(vitesse), position1(position1), position2(position2), parcours(parcours){
}

void ThreadLoco::setNumero(int numero){
    this->numero = numero;
}

void ThreadLoco::setVitesse(int vitesse){
    this->vitesse = vitesse;
}

void ThreadLoco::setPosition(int position1, int position2){
    this->position1 = position1;
    this->position2 = position2;
}

void ThreadLoco::setPosition1(int position1){
    this->position1 = position1;
}

void ThreadLoco::setPosition2(int position2){
    this->position2 = position2;
}

void ThreadLoco::setParcours(QList<int> parcours){
    this->parcours = parcours;
}

void ThreadLoco::run(){

    //Initialisation de la locomotive
    locomotive.fixerNumero(numero);
    locomotive.fixerVitesse(vitesse);
    locomotive.fixerPosition(position1, position2);
    locomotive.allumerPhares();
    locomotive.demarrer();
    locomotive.afficherMessage("Ready!");

    //Attente du passage sur les contacts
    for (int i = 0; i < parcours.size(); i++) {
        attendre_contact(parcours.at(i));
        afficher_message(qPrintable(QString("The engine no. %1 has reached contact no. %2.").arg(locomotive.numero()).arg(parcours.at(i))));
        locomotive.afficherMessage(QString("I've reached contact no. %1.").arg(parcours.at(i)));
    }

    //Arreter la locomotive
    locomotive.arreter();
    locomotive.afficherMessage("Yeah, piece of cake!");

    return;
}

void ThreadLoco::arreter(){
    locomotive.arreter();
}

ThreadLoco::~ThreadLoco()
{

}


#include "ctrain_handler.h"
#include "locomotive.h"
#include "threadloco.h"

#include <QList>

//Creation des locomotive
static ThreadLoco locomotive1;
static ThreadLoco locomotive2;

//Arret d'urgence
void emergency_stop()
{
    locomotive1.arreter();
    locomotive2.arreter();
    afficher_message("\nSTHAP!");
}

//Fonction principale
int cmain()
{
    afficher_message("Hit play to start the simulation...");

    //Choix de la maquette
    selection_maquette(MAQUETTE_A);

    //Initialisation des parcours
    QList<int> parcours1;
    QList<int> parcours2;

    parcours1 << 15 << 14 <<  7 << 6 << 5 << 34 << 33 << 32 << 25 << 24;
    parcours2 << 12 << 11 << 10 << 4 << 3 <<  2 <<  1 << 31 << 30 << 29 << 28 << 22 << 21;

    //Initialisation des aiguillages pour la première locomotive
    diriger_aiguillage(8,  DEVIE,       0);
    diriger_aiguillage(2,  DEVIE,       0);
    diriger_aiguillage(20, DEVIE,       0);
    diriger_aiguillage(14, DEVIE,       0);
    diriger_aiguillage(11, TOUT_DROIT,  0);
    diriger_aiguillage(17, TOUT_DROIT,  0);
    diriger_aiguillage(23, TOUT_DROIT,  0);

    //Initialisation des aiguillages pour la deuxième locomotive
    diriger_aiguillage(10, TOUT_DROIT,  0);
    diriger_aiguillage(7,  TOUT_DROIT,  0);
    diriger_aiguillage(4,  TOUT_DROIT,  0);
    diriger_aiguillage(1,  TOUT_DROIT,  0);
    diriger_aiguillage(22, TOUT_DROIT,  0);
    diriger_aiguillage(19, TOUT_DROIT,  0);
    diriger_aiguillage(16, TOUT_DROIT,  0);
    diriger_aiguillage(13, TOUT_DROIT,  0);

    //Initialisation de la première locomotive
    locomotive1.setNumero(1);
    locomotive1.setVitesse(12);
    locomotive1.setPosition(16,23);
    locomotive1.setParcours(parcours1);

    //Initialisation de la deuxième locomotive
    locomotive2.setNumero(2);
    locomotive2.setVitesse(14);
    locomotive2.setPosition(13,19);
    locomotive2.setParcours(parcours2);

    //Lancement des locomotive
    locomotive1.start();
    locomotive2.start();
    locomotive1.wait();
    locomotive2.wait();


    //Fin de la simulation
    mettre_maquette_hors_service();

    //Exemple de commande
    afficher_message("Enter a command in the input field at the top of the window.");
    QString commande = getCommand();
    afficher_message(qPrintable(QString("Your command is: ") + commande));

    return EXIT_SUCCESS;
}

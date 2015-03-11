#include <QCryptographicHash>
#include <QVector>

#include "threadmanager.h"


ThreadManager::ThreadManager(QObject *parent) :
    QObject(parent)
{

}

/*
 * Cette fonction est appelée lorsqu'un thread a trouvé la solution.
 * Elle tue, gentillement, les threads
 */
void ThreadManager::iFoundIt(QString answer)
{
    this->answer = answer;
}

/*
 * Cette fonction est appelée lorsqu'un thread a avancé dans sa progression.
 * Retransmet l'inforamtion à mainWindow
 */
void ThreadManager::incrementPBar(double percent){

}

/*
 * Permet de retransmettre le signal de progression reçu depuis hacktread à mainwindow
 */
void incrementPercentComputed(double percent){

}


/*
 * Les paramètres sont les suivants:
 *
 * - charset:   QString contenant tous les caractères possibles du mot de passe
 * - salt:      le sel à concaténer au début du mot de passe avant de le hasher
 * - hash:      le hash dont on doit retrouver la préimage
 * - nbChars:   le nombre de caractères du mot de passe à bruteforcer
 * - nbThreads: le nombre de threads à lancer
 *
 * Cette fonction doit retourner le mot de passe correspondant au hash, ou une
 * chaine vide si non trouvé.
 */
QString ThreadManager::startHacking(
        QString charset,
        QString salt,
        QString hash,
        unsigned int nbChars,
        unsigned int nbThreads
)
{
    long long unsigned int nbPossibilite = pow(nbChars, 62.);
    int interval = nbPossibilite/nbThreads;
    for(int i = 0; i < nbThreads; i++)
    {
        thread[i]= new hackThread(charset, salt, hash, nbChars, interval, i*interval ,0);
        thread[i]->wait();
        delete thread[i];
    }
    //thread = new hackThread(charset, salt, hash, nbChars, interval ,0);
    return answer;
}

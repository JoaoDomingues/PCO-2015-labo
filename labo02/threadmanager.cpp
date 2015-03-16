#include <QCryptographicHash>
#include <QVector>

#include "threadmanager.h"

/*
 * std::pow pour les long long unsigned int
 */
long long unsigned int intPow (
        long long unsigned int number,
        long long unsigned int index)
{
    long long unsigned int i;

    if (index == 0)
        return 1;

    long long unsigned int num = number;

    for (i = 1; i < index; i++)
        number *= num;

    return number;
}

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
    for(unsigned int i = 0; i < threadList.length(); i++){
        threadList.at(i)->stop();
    }
}

/*
 * Cette fonction est appelée lorsqu'un thread a avancé dans sa progression.
 * Retransmet l'inforamtion à mainWindow
 */
void ThreadManager::incrementPBar(double percent){
    emit incrementPercentComputed(percent);
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

    long long unsigned int nbPossibilite = intPow(charset.length(),nbChars);
    int interval = nbPossibilite/nbThreads;
    hackThread *currentThread;

    /* Créé les threads, on ajoutant leur pointeur à la liste.
     * Un appel à la méthode start() apellera la méthode run() de la classe MyThread */
    for (unsigned int i=0; i<nbThreads; i++)
    {
        currentThread = new hackThread(charset, salt, hash, nbChars, interval, i*interval ,0);
        threadList.append(currentThread);

        connect(
                    currentThread,
                    SIGNAL(iFoundIt(QString)),
                    this,
                    SLOT(iFoundIt(QString)));
        connect(
                    currentThread,
                    SIGNAL(incrementBar(double)),
                    this,
                    SLOT(incrementPBar(double)));

        currentThread->start();
    }

    for(unsigned int i = 0; i < threadList.length(); i++){
        threadList.at(i)->wait();
    }

    return answer;
}

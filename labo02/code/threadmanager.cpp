#include <QCryptographicHash>
#include <QVector>

#include "threadmanager.h"

QObject *lol;

ThreadManager::ThreadManager(QObject *parent) :
    QObject(parent)
{
    lol = parent;
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
 * Propage le signal de progression à mainwindow
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
    thread = new hackThread(charset, salt, hash, nbChars, 100000, 0);
    thread->wait();
    delete thread;
    return answer;
}

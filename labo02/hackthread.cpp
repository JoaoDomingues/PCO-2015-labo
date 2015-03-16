#include "hackthread.h"

void incrementBar(double percentComputed){

}

hackThread::hackThread(QString charset, QString salt, QString hash, unsigned int nbChars, long long unsigned int nbToCompute, long long unsigned int borneDepart, QObject *parent) :
    QThread(parent)
{
    this->charset = charset;
    this->salt = salt;
    this->hash = hash;
    this->nbChars = nbChars;
    this->nbToCompute = nbToCompute;
    this->borneDepart = borneDepart;
    isRunning = true;
}

void hackThread::stop(){
    isRunning = false;
}

void hackThread::run()
{
    unsigned int i;

    long long unsigned int nbComputed;

    /*
     * Nombre de caractères différents pouvant composer le mot de passe
     */
    unsigned int nbValidChars;

    /*
     * Tableau contenant les index dans la chaine charset des caractères de
     * currentPasswordString
     */
    QVector<unsigned int> currentPasswordArray(nbChars);

    /*
     * Hash du mot de passe à tester courant
     */
    QString currentHash;

    /*
     * Object QCryptographicHash servant à générer des md5
     */
    QCryptographicHash md5(QCryptographicHash::Md5);

    /*
     * Calcul du nombre de hash à générer
     */
    nbComputed         = 0;

    /*
     * Nombre de caractères différents pouvant composer le mot de passe
     */
    nbValidChars       = charset.length();


    /*
     * On initialise le premier mot de passe avec le mot de passe correspondant
     * à la borne de départ
     */
    int arrayIndex = 0;
    while(borneDepart != 0){
        currentPasswordArray[arrayIndex] = borneDepart % nbValidChars;
        borneDepart -= currentPasswordArray[arrayIndex];
        borneDepart /= nbValidChars;
        arrayIndex++;
    }
    for (i=0;i<nbChars;i++){
        currentPasswordString[i]  = charset.at(currentPasswordArray.at(i));
    }

    /*
     * Tant qu'on a pas tout essayé...
     */
    while (nbComputed < nbToCompute && isRunning) {
        /* On vide les données déjà ajoutées au générateur */
        md5.reset();
        /* On préfixe le mot de passe avec le sel */
        md5.addData(salt.toLatin1());
        md5.addData(currentPasswordString.toLatin1());
        /* On calcul le hash */
        currentHash = md5.result().toHex();

        /*
         * Si on a trouvé, on retourne le mot de passe courant (sans le sel)
         */
        if (currentHash == hash){
            emit iFoundIt(currentPasswordString);
            return;
        }

        /*
         * Tous les 1000 hash calculés, on notifie qui veut bien entendre
         * de l'état de notre avancement (pour la barre de progression)
         */
        if (!(nbComputed % 1000))
            emit incrementBar((double)1000/nbToCompute);

        /*
         * On récupère le mot de pass à tester suivant.
         *
         * L'opération se résume à incrémenter currentPasswordArra" comme si
         * chaque élément de ce vecteur représentait un digit d'un nombre en
         * base nbValidChars.
         *
         * Le digit de poids faible étant en position 0
         */
        i = 0;

        while (i < (unsigned int)currentPasswordArray.size()) {
            currentPasswordArray[i]++;

            if (currentPasswordArray[i] >= nbValidChars) {
                currentPasswordArray[i] = 0;
                i++;
            } else
                break;
        }

        /*
         * On traduit les index présents dans currentPasswordArray en
         * caractères
         */
        for (i=0;i<nbChars;i++)
            currentPasswordString[i]  = charset.at(currentPasswordArray.at(i));

        nbComputed++;
    }
    /*
     * Si on arrive ici, cela signifie que tous les mot de passe possibles ont
     * été testés, et qu'aucun n'est la préimage de ce hash.
     */
    return;
}

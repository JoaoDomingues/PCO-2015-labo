#include "hackthread.h"

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

hackThread::hackThread(QString charset, QString salt, QString hash, unsigned int nbChars, long long unsigned int nbToCompute, long long unsigned int borneDepart,QObject *parent) :
    QThread(parent)
{
    this->charset = charset;
    this->salt = salt;
    this->hash = hash;
    this->nbChars = nbChars;
    this->nbToCompute = nbToCompute;
    this->borneDepart = borneDepart;
}

void hackThread::run()
{

    emit iFoundIt("LOL");

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
    QVector<unsigned int> currentPasswordArray;

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
    nbToCompute        = intPow(charset.length(),nbChars);
    nbComputed         = 0;

    /*
     * Nombre de caractères différents pouvant composer le mot de passe
     */
    nbValidChars       = charset.length();

    /*
     * On initialise le premier mot de passe à tester courant en le remplissant
     * de nbChars fois du premir carcatère de charset
     */
    currentPasswordString.fill(charset.at(0),nbChars);
    currentPasswordArray.fill(0,nbChars);

    /*
     * Tant qu'on a pas tout essayé...
     */
    while (nbComputed < nbToCompute) {
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
        if (currentHash == hash)
            emit iFoundIt(currentPasswordString);
            return;

        /*
         * Tous les 1000 hash calculés, on notifie qui veut bien entendre
         * de l'état de notre avancement (pour la barre de progression)
         */
        if (!(nbComputed % 1000))
            emit incrementPBar((double)1000/nbToCompute);

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

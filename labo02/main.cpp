/*
 * Bastien Rouiller & Stéphane Donnet
 * Lab02
 * PCO
 */

#include "mainwindow.h"
#include <QApplication>

/*
    #### Documentation et analyse ####
    Afin de répartir la charge entre les thread, nous avons tout simplement décidé de calculer le nombre de combinaisons possibles
    et ensuite répartir ce nombre équitablement entre chaque thread.
    Par exemple avec deux threads et 1000 possibilités, le premier thread se chargera de la combinaison 1 à la combinaison à
    la 500 quant au second thread de la 501 à la 1'000. Dans ce laboratoire, il y a 62 caractères possibles donc pour un
    mot de 5 lettres cracker avec n threads. Chaque thread aura 62^5/n combinaisons à tester.

    Une telle répartition nous paraît la plus simple et la moins gourmande en ressources: On fait tous nos calcules d'abord,
    puis on itère l'ensemble des solutions. Une fois la borne déterminée, les threads calcules d'abord
    la solution correspondant au numéro de solution etfont de simple itérations jusqu'à ce que la solution soit trouvée.
    Cette méthode est facilement extensible pour un jeu de caractères plus grand.

    Le threadmanager est chargé de lancer les threads depuis la fonction starthacking et leur indiquer leur borne de départ ainsi
    que le nombre combinaisons à tester depuis cette borne.

    Ensuite, chaque thread se charge de "traduire" ces positions de bornes en termes de combinaison par exemple pour un mot à 4 lettres avec
    une borne valant 1 => aaaa. Et effectuer le nombre d'itérations attribués à ce même thread.
    Enfin, le thread ayant trouvé un "match" envoye un signal "iFoundIt" au threadmanager accompagné du mot de passe cracké.
    Ce dernier, tueras tous les threads actifs et informera la fenêtre principale qui affichera le résultat à l'utilisateur.
    Afin de les "tuer proprement", nous avons choisi de mettre une variable bool dans chacque thread qui est testé à chaque itération.
    Cette variable est passée à false lors de l'appel à la méthode stop();

    #### BenchMark ####
    ------------------------------------------------
    Processeur :	Intel Core i7-3610QM CPU @ 2.30GHz, 2301 MHz, 4 coeur(s), 8 processeur(s) logique(s)

    ---------------------------------------------------------
    |     Mdp    | Taille | Nb Thread |      Temps (ms)     |
    ---------------------------------------------------------
    |   Md5          3          1         660, 662          |
    |                           2         299, 284          |
    |                           3         147, 145          |
    |                           4         114, 115          |
    |                           5		  62, 53            |
    |                           6		  25, 25            |
    |                           7		  158, 150          |
    |                           8		  125, 124          |
    |                           9		  90, 110           |
    |                           10		  62, 105           |
    |                           11		  41, 41            |
    |                           12		  28, 54            |
    |-------------------------------------------------------|
    |   2Day          4         1         19'155, 19'213    |
    |                           2         20'136, 19'691    |
    |                           3         1'688, 1'639      |
    |                           4         7'159, 6'690      |
    |							5		  10'601, 10'773    |
    |                           6		  2'272, 2'372      |
    |                           7		  6'212, 6'087      |
    |                           8		  9'714, 9'496      |
    |                           9		  2'555, 2'724      |
    |                           10		  6'813, 6'752      |
    |                           11		  12, 11			|   !!!! meilleur temps
    |                           12		  3'696,3'724       |
    |-------------------------------------------------------|
    |	Lov3U					1		  2'576'950         |   OVER NINE THOUSANDDDD
    |                           2         769'645,          |
    |                           3         157'987,          |
    |                           4         863'819           |
    |                           5         661'129           |
    |                           6         211'006           |
    |                           7         789'620           |
    |                           8         653'955           |
    ---------------------------------------------------------

    1er test : md5
    Pour ce premier test, on peut voir que le temps nécessaire pour cracker ce mdp est décroissant jusqu'à 6 threads ensuite le temps augmente à nouveau.
    Pour le second test (2Day) on constate que les nombres de threads multiples de 3 ont un temps inférieurs aux autres. Ceci est sans doute dû au découpage
    des intervalles pour les différents threads. Avec 11 thread on a un temps extrêmement bas, 11ms. Sans doute un des threads ayant une borne très proche
    de la solution.
    Pour le dernier test effectués (Lov3U), il y a un gain drastique entre avec 2 threads puis 3 threads ensuite le temps nécessaires varie.

    A noter que ces tests ont été effectués sur une machine standard avec windows installée, il se peut que des threads en tâche de fond s'exécute et donc
    les résultats ne sont pas toujours prédictibles.

    Nous avons testé sur une machine Debian embaraquant un Intel® Core™ i7-3520M CPU @ 2.90GHz × 4. Les temps de recherche étaient quasiment divisé par 2.
    Nous avons pu remarquer sur ce système qu'il était intéressant d'avoir jusqu'à 16 threads, 32 threads augmentant les temps de calcul. Cela est dû qu'il y a
    beaucoup trop de thread par rapport au nombre de coeur disponible pour effectuer du vrai parallèlisme et donc que les changements de contextes sont trop
    pénalisant.

    Conclusion :
    Le temps pour cracker un mdp dépend non seulement du nombre de thread assignés au crackage mais également du découpage répartissant les combinaisons
    entre les threads.
    Par exemple pour 1'000 combinaisons possibles, avec 2 threads le mot de passe numéro 501 sera trouvé instatanément du à la répartition entre T1 et T2
    alors qu'avec T3 on aurait eu un temps plus grand.
*/

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();

}

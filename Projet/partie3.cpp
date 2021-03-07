
// Partie 3 du projet : poursuite de robots

#include <iostream>
#include <algorithm>
#include <vector>
#include "Labyrinthe.h"

using namespace std;

// Attend que duree (en secondes) se soit écoulée depuis le dernier appel.
void synchro(double duree)
{
    static clock_t jalon = clock();
    jalon = jalon + (clock_t)(duree * CLOCKS_PER_SEC);;
    while(clock()<jalon);
}

///============================================================================
/// Vous devez compléter l'implémentation de cette classe qui hérite de
/// La classe Labyrinthe. Toutes les méthodes publiques de Labyrinthe sont
/// disponibles. Vous pouvez ajouter des attributs et des méthodes.
///============================================================================

class Laby : public Labyrinthe
{
private:
    // Positions des robots
    int idRobotA;
    int idRobotB;

    // ------- Ajoutez ici des attributs supplémentaires si applicable --------
    int savesrand;
    // ------------------------------------------------------------------------
public:
    // Produit un labyrinthe avec une densité de cases blanches égale à density.
    // Les positions initiale des deux robots sont situées dans les coins supérieur gauche
    // et inférieur droit. Les codes des robots ne sont pas placés dans le grilles, dont
    // toutes les cases vides sont initialisées à 0.
    Laby(int nLignes, int nColonnes, double density);

    // Construit un labyrinthe d'après un descripteur.
    Laby(char* descr);

    int getIdRobotA() {return idRobotA;}
    int getIdRobotB() {return idRobotB;}    
    void setIdRobotA(int id) {idRobotA = id;}
    void setIdRobotB(int id) {idRobotB = id;}

    // Produit un identifiant aléatoire de case vide (PAS un mur)/
    int caseRandom();

    int getUpID(int id);
    int getDownID(int id);
    int getLeftID(int id);
    int getRightID(int id);

    // Réalise un mouvemement du robot prédateur. La grille ne doit contenir que des cases 
    // vides et des murs.
    // L'attribut idRobotA est modifié. La grille n'est pas modifiée.
    // Retourne false si les robots sont en contact (dans ce cas A n'est pas déplacé),
    // et true si les robots n'étaient pas en contact avant le déplacement de A.
    // Au moins un algorithme de déplacement doit être implémenté. Les algorithmes
    // implémentés doivent être numéroté à partir de 1. Par exemple, si deux algorithmes sont
    // implémentés, ils sont numérotés 1 et 2. Le paramètre algo désigne l'algorithme à
    // utiliser. Si un seul algorithme est utilisé, sa valuer doit être 1.
    bool deplaceRobotA(int algo);
    
    // Réalise un mouvemement du robot proie. Mêmes convension que deplaceRobotB.
    bool deplaceRobotB(int algo);

    // Place les robots (identifiés par les valeurs 2 et 3) dans la grille. Efface l'écran.
    // Affiche la grille. Enlève les robots de lagrille (pour ne pas perturber distMin).
    void visualisation();

    // Lance une poursuite dans le labyrinthe courant. Si silent == true, aucun affichage n'est
    // réalisé, sinon il y a affichage de chaque étape.
    // Une étape = un mouvement de chaque robot. Si le nombre d'étape atteint timeout, la
    // valeur timeout+1 est retournée, sinon le nombre d'étape avant contact des robots est 
    // retourné. Si random == true, les position initiales des robots sont aléatoires, sinon ce 
    // sont les coins supérieur gauche et inféieur droit.
    // Les paramètres algoA et algoB indiquent le algorithmes utilisé pour les robots.
    int course(int timeout, bool silent, bool random, int algoA, int algoB);

    // Réalise nCourses courses et retourne la médiane des valeurs retournées par les
    // appels à la méthode courses. Le apramètres algoA et algoB donnent les algorithmes
    // à utiliser pour les robots A et B.
    int evalue(int nCourses, int timeOut, int algoA, int algoB);
};

// Constructeur fourni par O. Bailleux. Peut être complété si nécessaire.
Laby::Laby(int nLignes, int nColonnes, double density) : Labyrinthe(nLignes, nColonnes)
{
    setAff(" XAB.");
    idRobotA = getID(0,0);
    idRobotB = getID(getNbLignes()-1, getNbColonnes()-1);
    genLaby((int)(density * getNbColonnes() * getNbLignes()));
    // Ajouter les initialisations supplémentaire nécessaires, si applicable
}

// Constructeur fourni gracieusement par O. Bailleux. Peut être complété si nécessaire.
Laby::Laby(char* descr) : Labyrinthe(descr)
{
    setAff(" XAB.");
    idRobotA = getID(0,0);
    idRobotB = getID(getNbLignes()-1, getNbColonnes()-1);
    // Ajouter les initialisations supplémentaire nécessaires, si applicable
}

// Méthode fournie par O. Bailleux
void Laby::visualisation()
{
    // Les robots sont placés dans la grille avant l'affichage
    modifie(getIdRobotA(),2);
    modifie(getIdRobotB(),3);

    system("clear");
    affiche();

    // Les robots sont retirés de la grille pour ne pas perturber la recherche de chemins
    // optimaux par la méthode distMin.
    modifie(getIdRobotA(),0);
    modifie(getIdRobotB(),0);
}

// Méthode fournie par O. Bailleux
int Laby::course(int timeout, bool silent, bool random, int algoA, int algoB)
{
    if(random)
    {// Course avec positions initiales des robots aléatoire
        idRobotB = caseRandom();
        idRobotA = caseRandom();
    }
    else
    {// Course avec départ dans les coins opposés.
        idRobotA = getID(0,0);
        idRobotB = getID(getNbLignes()-1, getNbColonnes()-1);
    }
    
    int nEtapes = 0;
    bool contact = false;

    // Arret quand les robots se touchent ou de nombre maxi d'étapes atteint
    while(!contact && nEtapes<timeout)
    {
        // On déplace le robot A
        contact = !deplaceRobotA(algoA);

        // On déplace le robot B sauf s'il est en contact avec A
        if (!contact) contact = !deplaceRobotB(algoB);

        nEtapes++;
        if(!silent) 
        {// Délai et affichage seulement si on est pas en mode silencieux
            synchro(0.1);
            visualisation();
        }
    }

    if(contact) return nEtapes;
    else return timeout+1;
}

// Méthode fournie par O. Bailleux
int Laby::evalue(int nCourses, int timeout, int algoA, int algoB)
{
    std::vector<int> tab;
    //int* tab = new int[nCourses]; // Tableau des scores

    for(int i=0; i<nCourses; i++)
    {// On lance une course et récupère le score
        cout << i << " / " << nCourses;
        int score = course(timeout, true, true, algoA, algoB);
        tab.push_back(score);
        cout << " --> " << score << endl;
    }

    // Tri du tableau de score pour calcul de la médiane.
    sort(tab.begin(), tab.end());
    return tab[nCourses/2];
}

///============================================================================
/// Méthodes à compléter. Vous pouvez ajouter les méthodes supplémentaires
/// pour simplifier votre programme et le rendre plus lisible.
///============================================================================

int Laby::caseRandom()
{
    //  A COMPLETER
    int shouldContinue = 1;
    if(this->savesrand!=0){
        this->savesrand+=13;    
    }else{  
        this->savesrand = time(NULL);
    }
    int random = 0;
    int maxRecursion = this->getNbColonnes()*this->getNbLignes()*10;
    int recursion = 0;
    do
    {
        recursion++;
        this->savesrand+=1;
        srand(this->savesrand);
        random = ((double) rand())/RAND_MAX*(this->getNbColonnes()*this->getNbLignes()-1)+1;
        if(this->lit(random)==0)
        {
            shouldContinue=0;
        }
    }while(shouldContinue && recursion<=maxRecursion);

    return random;
}

int Laby::getUpID(int id)
{
  if(id-this->getNbColonnes()>=0)
  {
    return id-this->getNbColonnes();
  }else
  {
    return -1;
  }
}

int Laby::getDownID(int id)
{
  if((id+this->getNbColonnes())<=this->getNbColonnes()*this->getNbLignes()-1)
  {
    return id+this->getNbColonnes();
  }else
  {
    return -1;
  }
}

int Laby::getLeftID(int id)
{
  if(this->getLigne(id-1)==this->getLigne(id))
  {
    return id-1;
  }else
  {
    return -1;
  }
}

int Laby::getRightID(int id)
{
  if(this->getLigne(id+1)==this->getLigne(id))
  {
    return id+1;
  }else
  {
    return -1;
  }
}

// Méthode à compléter
bool Laby::deplaceRobotA(int algo)
{
    // A COMPLETER AVEC AU MOINS UN ALGORITHME DE POURSUITE PREDATEUR
    int* dist = new int[4] {-1,-1,-1,-1};

    int id_up = this->getUpID(this->getIdRobotA());
    int id_down = this->getDownID(this->getIdRobotA());
    int id_left = this->getLeftID(this->getIdRobotA());
    int id_right = this->getRightID(this->getIdRobotA());

    if(id_up!=-1 && this->lit(id_up)==0){
        dist[0] = this->distMin(id_up,this->getIdRobotB());
    }

    if(id_down!=-1 && this->lit(id_down)==0){
        dist[1] = this->distMin(id_down,this->getIdRobotB());
    }

    if(id_left!=-1 && this->lit(id_left)==0){
        dist[2] = this->distMin(id_left,this->getIdRobotB());
    }
    
    if(id_right!=-1 && this->lit(id_right)==0){
        dist[3] = this->distMin(id_right,this->getIdRobotB());
    }

    int availableDistLength = 0;
    int currentDist = this->distMin(this->getIdRobotA(),this->getIdRobotB());
    for(int x=0;x<4;x++){
        if(dist[x]!=-1 && dist[x]<currentDist){
            availableDistLength+=1;
        }else{
            dist[x]=-1;
        }
    }

    if(availableDistLength==0){
        delete[] dist;
        return true;
    }else{ 
        int* availableDist = new int[availableDistLength];
        int availableDistIndex = 0;

        if(dist[0]!=-1){
            availableDist[availableDistIndex]=id_up;
            availableDistIndex+=1;
        }

        if(dist[1]!=-1){
            availableDist[availableDistIndex]=id_down;
            availableDistIndex+=1;
        }

        if(dist[2]!=-1){
            availableDist[availableDistIndex]=id_left;
            availableDistIndex+=1;
        }

        if(dist[3]!=-1){
            availableDist[availableDistIndex]=id_right;
            availableDistIndex+=1;
        }

        int random = ((double) rand())/RAND_MAX*(availableDistLength)-1;
        int newPosition = availableDist[random];

        delete[] dist;
        delete[] availableDist;

        if(newPosition!=this->getIdRobotB()){
            this->idRobotA=newPosition;
            return true;
        }else{
            return false;
        }
    }
}

bool Laby::deplaceRobotB(int algo)
{
    // A COMPLETER AVEC AU MOINS UN ALGORITHME DE POURSUITE PROIE
    int* dist = new int[4] {-1,-1,-1,-1};

    int id_up = this->getUpID(this->getIdRobotB());
    int id_down = this->getDownID(this->getIdRobotB());
    int id_left = this->getLeftID(this->getIdRobotB());
    int id_right = this->getRightID(this->getIdRobotB());

    if(id_up!=-1 && this->lit(id_up)==0){
        dist[0] = this->distMin(id_up,this->getIdRobotA());
    }

    if(id_down!=-1 && this->lit(id_down)==0){
        dist[1] = this->distMin(id_down,this->getIdRobotA());
    }

    if(id_left!=-1 && this->lit(id_left)==0){
        dist[2] = this->distMin(id_left,this->getIdRobotA());
    }
    
    if(id_right!=-1 && this->lit(id_right)==0){
        dist[3] = this->distMin(id_right,this->getIdRobotA());
    }

    int availableDistLength = 0;
    int currentDist = this->distMin(this->getIdRobotA(),this->getIdRobotB());
    for(int x=0;x<4;x++){
        if(dist[x]!=-1 && dist[x]>currentDist){
            availableDistLength+=1;
        }else{
            dist[x]=-1;
        }
    }

    if(availableDistLength==0){
        delete[] dist;
        return true;
    }else{ 
        int* availableDist = new int[availableDistLength];
        int availableDistIndex = 0;

        if(dist[0]!=-1){
            availableDist[availableDistIndex]=id_up;
            availableDistIndex+=1;
        }

        if(dist[1]!=-1){
            availableDist[availableDistIndex]=id_down;
            availableDistIndex+=1;
        }

        if(dist[2]!=-1){
            availableDist[availableDistIndex]=id_left;
            availableDistIndex+=1;
        }

        if(dist[3]!=-1){
            availableDist[availableDistIndex]=id_right;
            availableDistIndex+=1;
        }

        int random = ((double) rand())/RAND_MAX*(availableDistLength)-1;
        int newPosition = availableDist[random];

        delete[] dist;
        delete[] availableDist;

        if(newPosition!=this->getIdRobotA()){
            this->idRobotB=newPosition;
            return true;
        }else{
            return false;
        }
    }
}

///============================================================================
/// Quelques descripteurs qui seront utilisés pour évaluer les algos de poursuite
///============================================================================

// Gille de 20 lignes et 30 colonnes densité de cases vides 0.8
char descripteur1[] = 
{ 20, 30,
0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 
0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 
0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 
0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 
0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 
1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
};

// Gille de 20 lignes et 30 colonnes sans murs
char descripteur2[] = 
{ 20, 30,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

// Gille de 20 lignes et 30 colonnes densité de cases vides 0.9
char descripteur3[] = 
{ 20, 30,
0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

// Gille de 20 lignes et 30 colonnes densité de cases vides 0.7
char descripteur4[] =
{ 20, 30,
0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 
0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 
0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 
0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 
0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 
1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 
1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 
1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 
1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 
1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 
0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 
0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 
0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 
0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 
0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 
1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 
0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
};

///============================================================================
/// Exemple d'utilisation.
///============================================================================

void testPoursuite()
{
    int dureeMax = 300;
    Laby laby(30, 60, 0.9);

    int duree = laby.course(dureeMax, false, true, 1, 1);

    if(duree > dureeMax)
    {
        cout << "Echec apres " << dureeMax << " etapes" << endl;
    }
    else
    {
        cout << "Succes apres " << duree << " etapes" << endl;
    }
}

void testEval()
{
    Laby laby(descripteur2);

    int score = laby.evalue(100, 100, 1, 2);
 
    cout << "Mediane : " << score << endl;
}

int main(int argc, const char * argv[])
{
    srand((unsigned)time(NULL));
    //testPoursuite();
    testEval();
    return 0;
}
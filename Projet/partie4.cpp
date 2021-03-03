class Labyrinthe{
  private:
    char* grille[];
    int lignes;
    int colonnes;

  public:
    Labyrinthe(int lignes, int colonnes){
      *this->grille = new char[lignes*colonnes];
      this->lignes = lignes;
      this->colonnes = colonnes;
    };

    Labyrinthe(char data[]){
      int index = 0;
      int shouldContinue = 1;
      do{
        shouldContinue = data[index]==0;
        index+=1;
      }while(shouldContinue);
      index-=1;

      *this->grille = new char[index];
      for(int x=0;x<index;x++){
        *this->grille[x] = data[x];
      }
    };

    int getID(int ligne, int colonne){
      return 0;
    };

    int getLigne(int id){
      return 0;
    };

    int getCol(int id){
      return 0;
    };

    void modifie(int ligne, int colonne, char x){
    };

    void setAff(const char* motifs){

    };

    void affiche(){

    };

    char lit(int ligne, int colonne){
      return 'a';
    };

    bool connexe(){
      return 0;
    };

    void genLaby(int nb){

    };

    int distMin(int id1, int id2){
      return 0;
    };

    void chemin(int id1, int id2){

    };

    void afficheDescr(){

    };

    static void demo(){

    };
};
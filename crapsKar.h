//KAROUIA Alaedine 21611332







typedef struct De {
	int valeur;
}De;

struct Mise {
	int choix; 
	int somme;
};

typedef struct Joueur {
	char* nom;
	int argent;
	struct Mise mise;
}Joueur;



Joueur* joueurs;

De de[2];
int nombreDeJoueurs, jouer, numeroDeSuspension;



/*SAVES*/


/*PARTIE*/
void initialise(int nbJoueurs);
void afficherJoueurs();
void creerJoueurs();
void choisirMise();
int joueurSuivant(int joueurActuel);
void reset();

/*MISES*/
void passWin();
void passLoose();
void dontPassWin();
void dontPassLoose();
void recharge();

/*DES*/

int finJeu();
void LancerDe(int joueurID);

void highscore();
void Affhighscore();
int finJeu();
void recharge();


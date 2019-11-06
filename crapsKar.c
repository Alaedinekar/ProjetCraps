//KAROUIA Alaedine 21611332

#include "crapsKar.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


/*PARTIE*/
void initialise(int nbJoueurs) {
	//On alloue notre tableau de joueurs
	joueurs = (Joueur*)malloc(nbJoueurs * sizeof(Joueur));
	//On met la variable jouer à 1 pour pouvoir boucler (utulisé dans le main.c, boucle principale)
	jouer = 1;
	numeroDeSuspension = 0;
	nombreDeJoueurs = nbJoueurs;
}



void creerJoueurs() {
	//varible qui nous sert à renseigner le nom du Ième joueur 
	char tmp[50];
	int i;

	for (i = 0; i < nombreDeJoueurs; i++) {
		printf("Veuillez rentrer votre nom:\n");
		scanf("%s", &tmp);

		//On alloue le char* du joueur pour pouvoir copier son nom
		joueurs[i].nom = (char*)malloc((strlen(tmp) + 1) * sizeof(char));
		//On copie le nom
		strcpy(joueurs[i].nom, tmp);
		//On initialise les différentes variables
		joueurs[i].argent = 100;
		joueurs[i].mise.choix = 0;
		joueurs[i].mise.somme = 0;
	}

}

void reset() {
	//On remet à 0 la mise des joueurs
	int i;
	for (i = 0; i < nombreDeJoueurs; i++) {
		joueurs[i].mise.somme = 0;
		joueurs[i].mise.choix = 0;
	}
}

void choisirMise() {
	int i;
	for (i = 0; i < nombreDeJoueurs; i++) {
		if (joueurs[i].argent >= 0) {
			printf("\nA votre tour, %s\n", joueurs[i].nom);
			if (joueurs[i].mise.choix == 1 && numeroDeSuspension == 0) {
				printf("Vous pouvez augmenter votre mise ou ne rien faire \n (entrez %d votre ancienne mise pour ne rien faire) \n", joueurs[i].mise.somme);
			}
			else if (joueurs[i].mise.choix == 2 && numeroDeSuspension == 0) {
				printf("Vous pouvez diminuer, retirer ou ne rien faire\n");
				printf("\nEntrez un nombre negatif pour diminuer votre mise.\n");
			}
			else if(numeroDeSuspension == 0) {
				printf("Sur quoi allez vous pariez %s !\nEcrivez '1' pour Pass\nEcrivez '2' pour Don't Pass\n", joueurs[i].nom);
				int choice = 0;
				scanf("%d", &choice);
				joueurs[i].mise.choix = choice;
			}
			
			int mise = 0, Amiser = 0;
			do {

				//Si on est pas en suspention
				if (numeroDeSuspension == 0) {

					if (joueurs[i].mise.somme > 0) {
						printf("Votre mise etant de : %d euros !\n", joueurs[i].mise.somme);
					}

					//Pour la 2ieme phase, si le joueur à misé sur "Don't pass", il peut réduire ou annuler sa mise
					if (joueurs[i].mise.somme > 0 && joueurs[i].mise.choix == 2) {
						printf("Entrez 0 pour annuler votre precedente mise\n");
					}

					printf("Combien voulez vous miser d'argent ?\n");
					scanf("%d", &mise);
								
					if (mise < 0 && joueurs[i].mise.choix == 1) {
						//Pour la 2ieme, si le joueur à misé sur "Pass", il ne peut qu'augmenter sa mise
						printf("Vous pouvez uniquement augmenter votre mise ou ne rien faire!\n");
						//continue;
					}else if (mise <= 0 && joueurs[i].mise.somme == 0) {
						//Pour la 1ere phase, si le joueur à rentré une mise <= 0, on l'averti 
						printf("Votre mise doit être superieure a 0 euros !\n");
					}
					else if (mise == joueurs[i].mise.somme && joueurs[i].mise.choix == 1) {
						printf("Votre mise n'a pas ete modifie!\n");
						Amiser = 1;
					}
					else if (mise > joueurs[i].mise.somme && joueurs[i].mise.choix == 2 && joueurs[i].mise.somme > 0) {
						do {
							printf("Vous ne pouvez pas augmenter votre mise !\n");
							printf("Combien voulez vous miser d'argent ?\n");
							scanf("%d", &mise);
						} while (mise > joueurs[i].mise.somme);

						printf("Votre mise a ete diminue !\n");
						joueurs[i].argent = joueurs[i].argent + mise;
						joueurs[i].mise.somme = joueurs[i].mise.somme - mise;
						Amiser = 1;
					}
					else if (mise == 0 && joueurs[i].mise.choix == 2 && joueurs[i].mise.somme > 0) {
						//Pour la 2ieme phase, si le joueur à misé sur "Don't pass", il peut annuler sa mise
						printf("Votre mise a ete supprimee !\n");
						joueurs[i].argent = joueurs[i].argent + joueurs[i].mise.somme;
						joueurs[i].mise.somme = 0;
						Amiser = 1;
					}
					else if (mise < 0 && joueurs[i].mise.choix == 2 && joueurs[i].mise.somme > 0) {
						//Pour la 2ieme phase, si le joueur à misé sur "Don't pass", il peut diminuer sa mise
						while (joueurs[i].mise.somme + mise < 0) { //Si la diminution est trop grande (et donc que sa mise finale est < 0)
							printf("Vous avez trop diminue votre mise !\nDe combien voulez vous diminuer votre argent?\n");
							scanf("%d", mise);
						}

						printf("Votre mise a ete diminue !\n");
						joueurs[i].argent = joueurs[i].argent - mise;
						joueurs[i].mise.somme = joueurs[i].mise.somme + mise;
						Amiser = 1;
					}
					else if (mise > 0 && joueurs[i].argent - mise < 0) {
						printf("Vous n'avez pas assez d'argent ! il vous reste: %d euros.\n", joueurs[i].argent);
						
					}	
					else if (mise > 0 && joueurs[i].argent - mise >= 0) {
						joueurs[i].mise.somme = joueurs[i].mise.somme + mise;
						joueurs[i].argent = joueurs[i].argent - mise;
						Amiser = 1;
						mise = 0;
					}					
				}
				else if (numeroDeSuspension == 1) {
					//Premiere suspension
					//On peut que doubler sa mise				
					int choixDoublerMise = 0;
				
					printf("Premiere suspension. voulez vous doubler votre mise ?\nEntrez '1' pour la doubler\nEntrez '2' pour ne rien faire\n");
					scanf("%d", &choixDoublerMise);
					
					
					if (joueurs[i].argent >= joueurs[i].mise.somme) {
						if (choixDoublerMise == 1) {
							joueurs[i].argent = joueurs[i].argent - joueurs[i].mise.somme;
							joueurs[i].mise.somme = 2 * joueurs[i].mise.somme;
						}
					}
					else {
						printf("Vous n'avez pas assez d'argent ! \n");
						recharge();
					}
					Amiser = 1;
				}
				else {					
					//Suspension suivantes: on peut diminuer par facteur de 2 sa mise				
					int choixDiviserMise = 0;
				
					printf("%dieme Suspension, Vous pouvez diminuer par facteur de 2 votre mise ?\nEntrez '1' pour la diviser par 2\nEntrez '2' pour ne rien faire\n",numeroDeSuspension );
					scanf("%d", &choixDiviserMise);

					if (choixDiviserMise == 1) {
						joueurs[i].argent = joueurs[i].argent + joueurs[i].mise.somme / 2;
						joueurs[i].mise.somme = joueurs[i].mise.somme / 2;			
					}
					Amiser = 1;
				}
			} while (!Amiser);
		}
		else {
			printf("%s, Vous n'avez plus d'argent", joueurs[i].nom);
			recharge();
		}
	}
}

void afficherJoueurs() {
	printf("\nListe des joueurs:\n");
	int i;
	for (i = 0; i < nombreDeJoueurs; i++) {
		printf("%s : %d euros\n", joueurs[i].nom, joueurs[i].argent);
	}
	printf("\n");
}

int joueurSuivant(int numeroDuLanceur) {
	//Fonction qui renvoie l'index du joueur suivant (index du tableau de joueur)

	//Si le numero actuel du lanceur est égale au nombre de joueur -1, il s'agit du dernier joueur
	//On a donc fait un tour complet, on revient au premier joueur, donc le joueur n°0
	if (numeroDuLanceur == nombreDeJoueurs - 1) {
		return 0;
	}
	else {
		//Sinon le tour est au prochain joueur
		return numeroDuLanceur + 1;
	}

}







void LancerDe(int numeroDuJoueur) {
	
	printf("\nC'est a %s de lancer les des !\n", joueurs[numeroDuJoueur].nom);

	srand(time(NULL));

	de[0].valeur = rand() % (1 - 7) + 1; //[1; 7[
	de[1].valeur = rand() % (1 - 7) + 1; //[1; 7[

	printf("\nDes: %d + %d = %d\n\n", de[0].valeur, de[1].valeur, de[0].valeur + de[1].valeur);
	sleep(1);
}


/*MISES*/
void passWin() {
	//Tous les joueurs ayant misé sur PASS ont gagné
	int i;
	for (i = 0; i < nombreDeJoueurs; i++) {
		//Si le Ième joueur à misé sur 1
		if (joueurs[i].mise.choix == 1) {
			int x = joueurs[i].mise.somme;
			printf("Le joueur '%s' a gagne: %d euros !\n", joueurs[i].nom, x);

		 

			//Le joueur récupère son argent (qui correspont à sa mise) et gagne le montant de sa mise (donc mise + mise)
			joueurs[i].argent = joueurs[i].argent + 2 * x;
			joueurs[i].mise.somme = 0;
		}
	}
}

void passLoose() {
	//Les joueurs ayant misé sur PASS ont perdu
	int i;
	for (i = 0; i < nombreDeJoueurs; i++) {
		if (joueurs[i].mise.choix == 1) {
			//Comme son compte à déjà été débité, on à juste a mettre sa mise à O
			int tmp = joueurs[i].mise.somme;
			printf("Le joueur '%s' a perdu: %d euros !\n", joueurs[i].nom, tmp);
			joueurs[i].mise.somme = 0;
		}
	}
}

void dontPassWin() {
	//Les joueurs qui ont misé sur DONT PASS ont gagné
	int i;
	for (i = 0; i < nombreDeJoueurs; i++) {
		if (joueurs[i].mise.choix == 2) {
			//même principe que pour 1ersWin()
			int tmp = joueurs[i].mise.somme;
			printf("Le joueur '%s' à gagne: %d euros !\n", joueurs[i].nom, tmp);

			

			joueurs[i].argent = joueurs[i].argent + 2 * tmp;
			joueurs[i].mise.somme = 0;
		}
	}
}

void dontPassLoose() {
	
	int i;
	for (i = 0; i < nombreDeJoueurs; i++) {
		if (joueurs[i].mise.choix == 2) {
			//même principe que pour 1ersLoose()
			int tmp = joueurs[i].mise.somme;
			printf("Le joueur '%s' a perdu: %d euros !\n", joueurs[i].nom, tmp);
			joueurs[i].mise.somme = 0;
		}
	}
}







void highscore(){
	FILE* scoremax = fopen("HIGHSCORE_CRAPS.txt","w+");
	char chaine[255] ;
      
    int i;
    	
	fgets(chaine,255,scoremax);		
    	
    for (i=0; i<nombreDeJoueurs;i++)
{
	if (joueurs[i].argent>atoi(chaine)){
	
	fseek(scoremax,0,SEEK_SET);
	fprintf(scoremax,"%d\n", joueurs[i].argent); // On l'affiche
	        
}

}
   fclose(scoremax); 

}

void Affhighscore(){

FILE* scoremax = fopen("HIGHSCORE_CRAPS.txt","r");

char caractereActuel ;
if (scoremax != NULL){
	
  
	 do
        {
            caractereActuel = fgetc(scoremax); // On lit le caractère
            printf("%c", caractereActuel); // On l'affiche
        } while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)	   
}
else {
	printf("Pas encore defini\n");
}
fclose(scoremax);
}


void recharge() {
int choix ;
int somme;
int i;
for (i=0;i<nombreDeJoueurs;i++){
if (joueurs[i].argent == 0 ){

printf("\nSouhaitez vous recharger votre portemonnaie afin de continuer la partie?(0/1)\n")	;
scanf("%d",&choix);
if (choix == 1) {
	printf("De combien?\n");
	scanf("%d",&somme);
	joueurs[i].argent = joueurs[i].argent + somme;
}
}
}
}

int finJeu(){
	char boo[50] ;
	printf("\nTaper continuer pour pour poursuivre sur cette table ou autre pour quitter.\n");
	scanf("%s",&boo);
	if (strcmp (boo, "continuer")){		
		jouer = 0;
		return 0;
	}

	}

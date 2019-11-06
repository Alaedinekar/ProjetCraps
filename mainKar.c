//KAROUIA Alaedine 21611332
#include <stdio.h>
#include <stdlib.h>
#include "crapsKar.h"


//SUSPENSION CHECK

int main(void) {
	srand(time(NULL));



	printf("\tCRAPS SIMULATOR KAROUIA \n\n\n");
	
	
	
	jouer = 1;
	int numeroDuJoueur = 0; //Randomize ?
	
	
		printf("Bienvenue dans le jeu CRAPS\nQuel est  le nombre de participants au jeu: ");
		scanf("%d", &nombreDeJoueurs);
		
		if (nombreDeJoueurs == 0){
			printf("\nVous devez au moins etre 1 pour jouer!!\n");
			
			return 0;
		}
		
		
				
			
	
	
		//On alloue la mémoire et initialise certaines variables
		initialise(nombreDeJoueurs);
		//On créer les joeuurs
		creerJoueurs();
		
		
	    
	    
	    printf("\n\nLe highscore etant de:\t ");
	    Affhighscore();
	    printf("\nvous commencerez la partie avec 100euros\n");

	//Boucle principale
	do {
		//On affiche les joueurs
		afficherJoueurs();
		//On affiche le classement des gains
	
		//On demande à chaques joueurs leur mise
		choisirMise();	
			
		//On lance les dés (résultat aléatoire)
		LancerDe(numeroDuJoueur);

		//Si on à un CRAPS (2 ou 12)
		if (de[0].valeur + de[1].valeur == 2 ||de[0].valeur + de[1].valeur == 12) {
			printf("Cest un CRAPS !\n");
			//Les joueurs ayant voté sur 'PASS' ont perdu
			passLoose();
			//Si le CRAPS = 2
			if (de[0].valeur + de[1].valeur == 2) {
				//Les joueurs ayant voté sur 'DONT PASS' ont gagné
				dontPassWin();				
			}
			else if (de[0].valeur + de[1].valeur  == 12) {
				//Sinon, si le CRAPS = 12, le coup est nul
				printf("Le coup est nul. La manche recommence. \n");				
			}
		} else if(de[0].valeur + de[1].valeur == 7) {
			//Sinon, si on la somme des dés est égal à 7, les joueurs ayant misé sur PASS ont gagné
			passWin();	
			//..Don't pass ont perdu
			dontPassLoose();
			//On remet les mises et les choix des joueurs à 0
			reset();
		}else {
			//debut seconde phase
			int valeurDuPoint = de[0].valeur + de[1].valeur;
			printf("La valeur a refaire est: %d\n", valeurDuPoint);

			int Ajouer = 0;
			do {
				//demander augmentation de la mise sur pass
				//demander diminution / suppression sur dont pass
				//if mise == PASS ||
				//mise < anciene mise
				//si annule mise => perdu
				printf("\nVous pouvez modifier votre mise !\n");
				choisirMise();

				LancerDe(numeroDuJoueur);

				//SI il refait le point, les joueurs ayant misé sur:
				//Pass => gagné
				//Don't pass => perdu
				if (de[0].valeur + de[1].valeur == valeurDuPoint) {					
					passWin();
					dontPassLoose();
					Ajouer = 1;
				}
				else if (de[0].valeur + de[1].valeur == 7 ) {
					//Il fait 7, il perd et les joueurs ayant voté:
					//Pass => perdu
					//D'ont pass => gagné
					passLoose();
					dontPassWin();
					//C'est au prochain joueur de lancer les dés (sens des aiguilles d'une montre)
					numeroDuJoueur = joueurSuivant(numeroDuJoueur);
					Ajouer = 1;
				}
				else if (de[0].valeur + de[1].valeur != valeurDuPoint || de[0].valeur + de[1].valeur != 7){
					//Si il fait ni "le point" ni 7, on est en suspension
					numeroDeSuspension++;
				}

			} while (!Ajouer);			
		}
		printf("\n\nNouvelle Partie! \n\n");
		afficherJoueurs();
        finJeu();
		
		
		reset();
		
		numeroDeSuspension = 0;
		highscore();
	} while (jouer == 1);
	
    
	return 0;
}

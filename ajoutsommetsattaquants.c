#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
//./a.out nomfichier.txt 
//changer nb pages et de liens
//pertinence : 
//forte : Page 280545 9.96199e-05
//moyenne : Page 281466 7.53954e-06
//faible : Page 281574 6.05222e-07
//Staford de base : 281903 2312497
			
void ajoutsommetseul (int nbajout, char* nom, int nbpages, int nbliens, int perticible) {
	int degre = 1;
	int i;
	int cible = 0;
	//affectation de la cible
	if (perticible == 1) { cible = 280545; }
	else if (perticible == 2) { cible = 281466; }
	else if (perticible == 3) { cible = 281574; }
	else { cible = perticible; }
	
	// Ecriture du nouveau sommet seul à la fin du fichier web
	FILE *g = fopen(nom,"a");
	for (i = 1; i < nbajout + 1; i++) {
		fprintf(g, "%d %d %d 1.000000\n", nbpages+i, degre, cible);
	}
	fclose(g);
	
	// Ecriture du nouveau nombre de pages et nombre de liens.
	FILE *h = fopen(nom,"r+");
	fprintf(h, "%d %d", nbpages+nbajout, nbliens+nbajout);
	fclose(h);
}

void ajoutanneau (int nbajout, char* nom, int nbpages, int nbliens, int perticible, int nbstructure) {
	//initialisation
	int degre = 2;
	int i;
	int cible = 0;
	
	//Choix de la cible aléatoirement ou non et en fonction de ce qu'a entré l'utilisateur
	if (perticible == 1) { cible = 280545; }
	else if (perticible == 2) { cible = 281466; }
	else if (perticible == 3) { cible = 281574; }
	else { cible = perticible; }

	// Ecriture d'un anneau à la fin du fichier web,
	//Le (y*nbajout) est la pour incrémenter le num de page a chaque itération du nb de structure a ajouter
	FILE *g = fopen(nom,"a");
	for (int y = 0; y < nbstructure; y++) {
		for (i = 1; i < nbajout; i++) {
			fprintf(g, "%d %d %d 0.500000 %d 0.500000\n", nbpages+i+(y*nbajout), degre, nbpages+i+1+(y*nbajout), cible);
		}
		//ecriture du dernier sommet qui se relie au premier sommet de l'anneau
		fprintf(g, "%d %d %d 0.500000 %d 0.500000\n", nbpages+i+(y*nbajout), degre, nbpages+1+(y*nbajout), cible);

	}
	fclose(g);

	// Ecriture du nouveau nombre de pages et nombre de liens.
	FILE *h = fopen(nom,"r+");
	fprintf(h, "%d %d", nbpages+(nbajout*nbstructure), nbliens+(nbajout*nbstructure)*2);
	fclose(h);
}

void ajoutcomplet (int nbajout, char* nom, int nbpages, int nbliens, int perticible, int nbstructure) {
	//initialisation
	int degre = nbajout;
	int i;
	int j;
	//Ici on utilise des float pour la valeur avec laquelle on pointe sur les autres sommets
	float z = nbajout;
	float x = 1/z;
	int cible = 0;
	
	//Choix de la cible aléatoirement ou non et en fonction de ce qu'a entré l'utilisateur
	if (perticible == 1) { cible = 280545; }
	else if (perticible == 2) { cible = 281466; }
	else if (perticible == 3) { cible = 281574; }
	else { cible = perticible; }
	
	// Ecriture du graphe complet à la fin du fichier web.
	FILE *g = fopen(nom,"a");
	// Ici on ecrit d'abord le degré et le while (2nd for) va ecrire les liens 
	// vers les autres pages. 
	for (int y = 0; y < nbstructure; y++) {
		for (i = 1; i < nbajout + 1; i++) {
			/////// j = 1;
			fprintf(g, "%d %d", nbpages+i+(y*nbajout), degre);
			for(j = 1; j < nbajout + 1; j++){
			///////  while (j != nbajout + 1){
				// Cette condition permet de savoir si on est pas sur 
				// la page que l'on ecrit. Pour ne pas faire un lien d'une 
				// page sur elle même.
				if (nbpages+j == nbpages+i) {} // if vide !
				else {
					fprintf(g, " %d %f", nbpages+j+(y*nbajout), x);}
				/////// j++;
			}
			fprintf(g, " %d %f\n", cible, x);
			//~ fprintf(g, "\n");
		}
		// Ecriture de la derniere page
		//~ x = 1/z;
		//~ fprintf(g, "%d %d", nbpages+i+(y*nbajout), degre + 1);
		//~ for(j = 1; j < nbajout + 1; j++){
		//~ /////// j = 1;
		//~ /////// while (j != nbajout + 1){
			//~ if (nbpages+j == nbpages+i) {} // if vide !
			//~ else {
				//~ fprintf(g, " %d %f", nbpages+j+(y*nbajout), x);
			//~ }
			//~ /////// j++;
		//~ }
		//~ fprintf(g, " %d %f\n", cible, x);
	}
	fclose(g);
	
	// Ecriture du nouveau nombre de pages et nombre de liens.
	FILE *h = fopen(nom,"r+");
	fprintf(h, "%d %d", nbpages+(nbajout*nbstructure), nbliens+(nbajout*nbstructure)*nbajout);
	fclose(h);
}

void ajoutarbre(int nbajout, char* nom, int nbpages, int nbliens, int perticible, int nbstructure) {
// L'arbre va être construit dans cet ordre : 1 pointe vers la cible, 2 et 3 pointe 
// vers 1 et la cible, 4 et 5 vers 2 et la cible, 6 et 7 vers 3 et la cible etc ...
	//initialisation
	int degre = 2;
	int i;
	int compteur = 0; // Distance par rapport à la racine
	int cible = 0;
	int racine = 0;
	
	//Choix de la cible aléatoirement ou non et en fonction de ce qu'a entré l'utilisateur
	if (perticible == 1) { cible = 280545; }
	else if (perticible == 2) { cible = 281466; }
	else if (perticible == 3) { cible = 281574; }
	else { cible = perticible; }

	// Ecriture de l'arbre à la fin du fichier web.
	FILE *g = fopen(nom,"a");
	
	for (int y = 0; y < nbstructure; y++) {
		// Initialisation du sommet racine
		racine = nbpages + 1+(y*nbajout);
		fprintf(g, "%d %d %d 1.000000\n", racine, 1, cible);
		// Sommets 2 à 2 (arbre binaire) et on pointe vers le sommet père 
		// lui meme calculé par sa distance à la racine	
		for (i = 1; i < nbajout - 1; i+=2) {
			fprintf(g, "%d %d %d 0.500000 %d 0.500000\n", racine+i, degre, racine + compteur, cible);	
			fprintf(g, "%d %d %d 0.500000 %d 0.500000\n", racine+i+1, degre, racine + compteur, cible);	
			compteur++;
		}
		// Le dernier sommet dans le cas d'un nombre PAIR de sommets 
		// a entrer (pair car le sommet racine est deja entré hors de la boucle)
		if (nbajout%2 == 0){ 
			fprintf(g, "%d %d %d 0.500000 %d 0.500000\n", racine+i, degre, racine + compteur, cible);
		}
		//on réinitialise le compteur car on va commencer un nouvel arbre
		compteur = 0;
	}
	fclose(g);
	
	// Ecriture du nouveau nombre de pages et nombre de liens.
	FILE *h = fopen(nom,"r+");
	fprintf(h, "%d %d", nbpages+(nbajout*nbstructure), nbliens+(nbajout*nbstructure)*2);
	fclose(h);
}

void ajoutarbre_attaquantunique(int nbajout, char* nom, int nbpages, int nbliens, int perticible, int nbstructure) {
// L'arbre va être construit dans cet ordre : 1 pointe vers la cible, 2 et 3 pointe 
// vers 1, 4 et 5 vers 2, 6 et 7 vers 3 etc ...
	//initialisation
	int degre = 1;
	int i;
	int compteur = 0; // Distance par rapport à la racine
	int cible = 0;
	int racine = 0;
	
	//Choix de la cible aléatoirement ou non et en fonction de ce qu'a entré l'utilisateur
	if (perticible == 1) { cible = 280545; }
	else if (perticible == 2) { cible = 281466; }
	else if (perticible == 3) { cible = 281574; }
	else { cible = perticible; }

	// Ecriture de l'arbre à la fin du fichier web.
	FILE *g = fopen(nom,"a");
	
	for (int y = 0; y < nbstructure; y++) {
		// Initialisation du sommet racine
		racine = nbpages + 1+(y*nbajout);
		fprintf(g, "%d %d %d 1.000000\n", racine, degre, cible);
		// Sommets 2 à 2 (arbre binaire) et on pointe vers le sommet père 
		// lui meme calculé par sa distance à la racine	
		for (i = 1; i < nbajout - 1; i+=2) {
			fprintf(g, "%d %d %d 1.000000\n", racine+i, degre, racine + compteur);	
			fprintf(g, "%d %d %d 1.000000\n", racine+i+1, degre, racine + compteur);	
			compteur++;
		}
		// Le dernier sommet dans le cas d'un nombre PAIR de sommets 
		// a entrer (pair car le sommet racine est deja entré hors de la boucle)
		if (nbajout%2 == 0){ 
			fprintf(g, "%d %d %d 1.000000\n", racine+i, degre, racine + compteur);
		}
		//on réinitialise le compteur car on va commencer un nouvel arbre
		compteur = 0;
	}
	fclose(g);
	
	// Ecriture du nouveau nombre de pages et nombre de liens.
	FILE *h = fopen(nom,"r+");
	fprintf(h, "%d %d", nbpages+(nbajout*nbstructure), nbliens+(nbajout*nbstructure));
	fclose(h);
}

void ajoutanneaualeatoire (int nbajout, char* nom, int nbpages, int nbliens, int perticible) {
	//initialisation
	int degre = 2;
	int i;
	int cible = 0;
	int nouveauliens = 0;
	int nouveausommets = 0;
	int sommetsuivant = 0;
	int nbsommetrestant = 100;
	
	//Choix de la cible en fonction de ce qu'a entré l'utilisateur (cible pré choisis ou choix manuel)
	if (perticible == 1) { cible = 280545; }
	else if (perticible == 2) { cible = 281466; }
	else if (perticible == 3) { cible = 281574; }
	else { cible = perticible; }

	FILE *g = fopen(nom,"a");

	//On boucle tant qu'il reste des sommets a ajouter (on ajoute entre 49 et 51 sommets)
	while(nbsommetrestant > 0) {
		//nbajout correspond a la taille en nombre de sommets de la structure que l'on va insérer
		//il est limité au nombre de sommet restants a ajouter
		//ainsi on se retrouvera au final avec par exemple un anneau de
		//10 sommets puis un anneau de 29 puis un de 5 puis un de 3 et un de 2 ...
		nbajout = rand()%(100-nouveausommets);
		
		//si la taille du graphe choisis est inférieure a 3 on le met a 3. Ajouter 
		//des graphes de taille 1 ou 2 correspondrait en effet a ajouter 
		//des sommets seuls
		if (nbajout <= 3) { nbajout = 3; }
		
		//on décrémente le nombre de sommet restant
		nbsommetrestant -= nbajout;
		
		for (i = 1; i < nbajout; i++) {
			fprintf(g, "%d %d %d 0.500000 %d 0.500000\n", nbpages+i+sommetsuivant, degre, nbpages+i+1+sommetsuivant, cible);
			nouveauliens+=2;
			nouveausommets++;
		}
		fprintf(g, "%d %d %d 0.500000 %d 0.500000\n", nbpages+i+sommetsuivant, 2, nbpages+1+sommetsuivant, cible);
		nouveausommets++;
		nouveauliens+=2;
		sommetsuivant += nbajout;
	}
	fclose(g);

	// Ecriture du nouveau nombre de pages et nombre de liens.
	FILE *h = fopen(nom,"r+");
	fprintf(h, "%d %d", nbpages+nouveausommets, nbliens+nouveauliens);
	fclose(h);
}

void ajoutcompletaleatoire (int nbajout, char* nom, int nbpages, int nbliens, int perticible) {
	//initialisation
	int degre = 0;
	int i,j;
	float z,x;
	int cible = 0;
	int nouveauliens = 0;
	int nouveausommets = 0;
	int sommetsuivant = 0;
	int nbsommetrestant = 100;
	
	if (perticible == 1) { cible = 280545; }
	else if (perticible == 2) { cible = 281466; }
	else if (perticible == 3) { cible = 281574; }
	else { cible = perticible; }

	FILE *g = fopen(nom,"a");

	while(nbsommetrestant > 0) {
		nbajout = rand()%(100-nouveausommets);
		if (nbajout <= 3) { nbajout = 3; }
		
		z = nbajout;
		x = 1/z;
		degre = nbajout;

		nbsommetrestant -= nbajout;
		
		for (i = 1; i < nbajout + 1; i++) {
			/////// j = 1;
			fprintf(g, "%d %d", nbpages+i+sommetsuivant, degre);
			for(j = 1; j < nbajout + 1; j++){
			///////  while (j != nbajout + 1){
				// Cette condition permet de savoir si on est pas sur 
				// la page que l'on ecrit. Pour ne pas faire un lien d'une 
				// page sur elle même.
				if (nbpages+j == nbpages+i) {} // if vide !
				else {
					fprintf(g, " %d %f", nbpages+j+1+sommetsuivant, x);
					nouveauliens++;}
				/////// j++;
			}
			fprintf(g, " %d %f\n", cible, x);
			nouveausommets++;
			nouveauliens++;
		}
		//~ x = 1/z;
		//~ fprintf(g, "%d %d", nbpages+i+sommetsuivant, degre + 1);
		//~ for(j = 1; j < nbajout + 1; j++){
			//~ if (nbpages+j == nbpages+i) {}
			//~ else {
				//~ fprintf(g, " %d %f", nbpages+j+1+sommetsuivant, x);
				//~ nouveauliens++;
			//~ }
		//~ }
		//~ fprintf(g, " %d %f\n", cible, x);
		//~ nouveauliens++;
		//~ nouveausommets++;
		sommetsuivant += nbajout;
	}
	fclose(g);

	// Ecriture du nouveau nombre de pages et nombre de liens.
	FILE *h = fopen(nom,"r+");
	//printf("new sommet : %d \n new liens : %d",nouveausommets,nouveauliens);
	fprintf(h, "%d %d", nbpages+nouveausommets, nbliens+nouveauliens);
	fclose(h);
}

void ajoutarbrealeatoire (int nbajout, char* nom, int nbpages, int nbliens, int perticible) {
	//initialisation
	int degre = 2;
	int i;
	int cible = 0;
	int nouveauliens = 0;
	int nouveausommets = 0;
	int sommetsuivant = 0;
	int nbsommetrestant = 100;
	int compteur = 0; // Distance par rapport à la racine
	int racine = 0;
	
	if (perticible == 1) { cible = 280545; }
	else if (perticible == 2) { cible = 281466; }
	else if (perticible == 3) { cible = 281574; }
	else { cible = perticible; }

	FILE *g = fopen(nom,"a");

	while(nbsommetrestant > 0) {
		nbajout = rand()%(100-nouveausommets);
		if (nbajout <= 3) { nbajout = 3; }
		
		nbsommetrestant -= nbajout;
		
		racine = nbpages+1+sommetsuivant;
		fprintf(g, "%d %d %d 1.000000\n", racine, 1, cible);
		nouveausommets++;
		nouveauliens++;
		// Sommets 2 à 2 (arbre binaire) et on pointe vers le sommet père 
		// lui meme calculé par sa distance à la racine	
		for (i = 1; i < nbajout - 1; i+=2) {
			fprintf(g, "%d %d %d 0.500000 %d 0.500000\n", racine+i, degre, racine + compteur, cible);	
			fprintf(g, "%d %d %d 0.500000 %d 0.500000\n", racine+i+1, degre, racine + compteur, cible);	
			nouveausommets+=2;
			nouveauliens+=4;	
			compteur++;
		}
		// Le dernier sommet dans le cas d'un nombre PAIR de sommets 
		// a entrer (pair car le sommet racine est deja entré hors de la boucle)
		if (nbajout%2 == 0){ 
			fprintf(g, "%d %d %d 0.500000 %d 0.500000\n", racine+i, degre, racine + compteur, cible);
			nouveausommets++;
			nouveauliens+=2;
		}
		//on réinitialise le compteur car on va commencer un nouvel arbre
		compteur = 0;
		sommetsuivant += nbajout;
	}
	fclose(g);

	// Ecriture du nouveau nombre de pages et nombre de liens.
	FILE *h = fopen(nom,"r+");
	fprintf(h, "%d %d", nbpages+nouveausommets, nbliens+nouveauliens);
	fclose(h);
}

void ajout_graphe_aleatoire(int nbajout, char* nom,int nbpages,int nbliens,int perticible,int nbstructure)
{
	//initialisation
	//On choisis un degré aléatoire pour les sommets inférieur a 99 car 100 sommets sont ajoutés
	//+ 1 car il faut aussi pointer sur la cible
	int degre = rand()%99;
	degre++;
	printf("\n Le degré choisis est : %d \n",degre);
	int i,j;
	int k = 1;
	int cible = 0;
	int sommet_aleatoire = 0;
	
	//Ici on utilise des float pour la valeur avec laquelle on pointe sur les autres sommets
	float z = degre;
	float x = 1/z;
	
	
	//Choix de la cible aléatoirement ou non et en fonction de ce qu'a entré l'utilisateur
	if (perticible == 1) { cible = 280545; }
	else if (perticible == 2) { cible = 281466; }
	else if (perticible == 3) { cible = 281574; }
	else { cible = perticible; }

	// Ecriture du graphe à la fin du fichier web,
	//Le (y*nbajout) est la pour incrémenter le num de page a chaque itération du nb de structure a ajouter
	FILE *g = fopen(nom,"a");
	for (int y = 0; y < nbstructure; y++) {
		for (i = 1; i < nbajout + 1; i++) {
			/////// j = 1;
			fprintf(g, "%d %d", nbpages+i+(y*nbajout), degre);
			sommet_aleatoire = rand()%(nbpages+100 - nbpages) + nbpages;
				while (sommet_aleatoire == nbpages+i){
					sommet_aleatoire = rand()%(nbpages+100 - nbpages) + nbpages;
				}
				printf("\n Le sommet choisis est : %d \n",sommet_aleatoire);
			k = 1;
			for(j = 0; j < degre - 1; j++){
				if (sommet_aleatoire + j > nbpages+100) {
					fprintf(g, " %d %f", sommet_aleatoire - k, x);
					k++;
					}
				else {
					fprintf(g, " %d %f", sommet_aleatoire + j, x);}
				}
			fprintf(g, " %d %f\n", cible, x);
		}
	}
			
	fclose(g);

	// Ecriture du nouveau nombre de pages et nombre de liens.
	FILE *h = fopen(nom,"r+");
	fprintf(h, "%d %d", nbpages+(nbajout*nbstructure), nbliens+(nbajout*nbstructure)*degre);
	fclose(h);
}

void ajout_graphe_aleatoire_avec_proba(int nbajout, char* nom,int nbpages,int nbliens,int perticible, int probabilite)
{
	//initialisation
	int degre = probabilite*100;
	int i,j;
	int k = 1;
	int cible = 0;
	int sommet_aleatoire = 0;
	
	//Ici on utilise des float pour la valeur avec laquelle on pointe sur les autres sommets
	float z = degre;
	float x = 1/z;
	
	//Choix de la cible aléatoirement ou non et en fonction de ce qu'a entré l'utilisateur
	if (perticible == 1) { cible = 280545; }
	else if (perticible == 2) { cible = 281466; }
	else if (perticible == 3) { cible = 281574; }
	else { cible = perticible; }

	// Ecriture du graphe à la fin du fichier web,
	FILE *g = fopen(nom,"a");
	
	for (i = 1; i < nbajout + 1; i++) {
		fprintf(g, "%d %d", nbpages+i, degre);
			sommet_aleatoire = rand()%(nbpages+100 - nbpages) + nbpages;
				while (sommet_aleatoire == nbpages+i){
					sommet_aleatoire = rand()%(nbpages+100 - nbpages) + nbpages;
				}
				printf("\n Le sommet choisis est : %d \n",sommet_aleatoire);
			k = 1;
			for(j = 0; j < degre - 1; j++){
				if (sommet_aleatoire + j > nbpages+100) {
					fprintf(g, " %d %f", sommet_aleatoire - k, x);
					k++;
					}
				else {
					fprintf(g, " %d %f", sommet_aleatoire + j, x);}
				}
			fprintf(g, " %d %f\n", cible, x);
		}
	
			
	fclose(g);

	// Ecriture du nouveau nombre de pages et nombre de liens.
	FILE *h = fopen(nom,"r+");
	fprintf(h, "%d %d", nbpages+nbajout, nbliens+(nbajout*degre));
	fclose(h);
}

void ajoutstructure(int structure, int nbstructure, int nbajout, char* nom, int nbpages, int nbliens, int cible)
{
	int i;
		if (structure == 1) { ajoutsommetseul(nbajout, nom, nbpages, nbliens, cible); }
		else if (structure == 2) { ajoutanneau(nbajout, nom, nbpages, nbliens, cible, nbstructure); }
		else if (structure == 3) { ajoutcomplet(nbajout, nom, nbpages, nbliens, cible, nbstructure); }
		else if (structure == 4) { ajoutarbre(nbajout, nom, nbpages, nbliens, cible, nbstructure); }
		else if (structure == 5) { ajoutanneaualeatoire(100, nom, nbpages, nbliens, 1); }
		else if (structure == 6) { ajoutcompletaleatoire(100, nom, nbpages, nbliens, 1); }
		else if (structure == 7) { ajoutarbrealeatoire(100, nom, nbpages, nbliens, 1); }
		else if (structure == 8) { ajoutarbre_attaquantunique(nbajout, nom, nbpages, nbliens, cible, nbstructure); }
		else if (structure == 9) { ajout_graphe_aleatoire(100, nom, nbpages, nbliens, cible, nbstructure); }
		else if (structure == 10) { ajout_graphe_aleatoire_avec_proba(100, nom, nbpages, nbliens, cible, 0.1); }
}


int main(int argc, char** argv) {
	// cible c'est le n° de page de la cible
	int structure, nbstructure, nbajout, nbpages, nbliens, cible;
	srandom(time(NULL));
	printf("Random cible si besoin : %d\n\n",rand()%281904);
	
	FILE *f = fopen(argv[1],"r");
	if (f == NULL) {
		exit(EXIT_FAILURE); }
	
	fscanf(f, "%d", &nbpages);
	fscanf(f, "%d", &nbliens);
	printf("pages : %d\n", nbpages);
	printf("lien : %d\n", nbliens);
	fclose(f);
	

	printf("Entrez la structure que vous voulez insérer : \n 1 pour un sommet seul \n 2 pour un anneau \n 3 pour un graphe complet \n 4 pour un arbre \n 5 pour un nombre d'anneaux aléatoire \n 6 pour un nombre de graphes complet aléatoire \n 7 pour un nombre d'arbres aléatoire\n 8 pour un arbre a attaquant unique\n 9 pour un graphe de 100 sommets avec un degré aléatoire\n 10 pour un graphe avec une certaine probabilité de connecter les sommets entre eux\n");
	scanf("%d", &structure);
	
	if ((structure == 5) || (structure == 6) || (structure == 7)) { }
	else { 

	if (structure != 1) {
	printf("Entrer le nombre de structure que vous voulez ajouter : \n");
	scanf("%d", &nbstructure);
	}
	
	if ((structure != 9) || (structure != 10)) {
	printf("Entrez le nombre de sommets par structure a ajouter : \n");
	scanf("%d", &nbajout);	
	}
	
	printf("Entrez la pertinence de la cible : \n 1 pour une pertinence forte \n 2 pour une pertinence moyenne \n 3 pour une pertinence faible \n 4 Pour entrer manuellement le sommet cible\n");
	scanf("%d", &cible);
	if (cible == 4) { printf("Entrez le sommet cible : "); scanf ("%d", &cible);}
	}

	ajoutstructure(structure, nbstructure, nbajout, argv[1], nbpages, nbliens, cible);	
	
	return 0;
}

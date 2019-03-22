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
	//ca on changera si on choisis des cibles alea plus tard
	if (perticible == 1) { cible = 280545; }
	if (perticible == 2) { cible = 281466; }
	if (perticible == 3) { cible = 281574; }
	
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
	int degre = 1;
	int i;
	int cible = 0;
	
	//Choix de la cible aléatoirement ou non et en fonction de ce qu'a entré l'utilisateur
	if (perticible == 1) { cible = 280545; }
	if (perticible == 2) { cible = 281466; }
	if (perticible == 3) { cible = 281574; }

	// Ecriture d'un anneau à la fin du fichier web, on relis le dernier 
	// sommet au premier de l'anneau et à la cible.
	//Le (y*nbajout) est la pour incrémenter le num de page a chaque itération du nb de structure a ajouter
	FILE *g = fopen(nom,"a");
	for (int y = 0; y < nbstructure; y++) {
		for (i = 1; i < nbajout; i++) {
			fprintf(g, "%d %d %d 1.000000\n", nbpages+i+(y*nbajout), degre, nbpages+i+1+(y*nbajout));
		}
		fprintf(g, "%d %d %d 0.500000 %d 0.500000\n", nbpages+i+(y*nbajout), 2, nbpages+1+(y*nbajout), cible);
	}
	fclose(g);

	// Ecriture du nouveau nombre de pages et nombre de liens.
	FILE *h = fopen(nom,"r+");
	fprintf(h, "%d %d", nbpages+(nbajout*nbstructure), nbliens+(nbajout+1)*nbstructure);
	fclose(h);
}

void ajoutcomplet (int nbajout, char* nom, int nbpages, int nbliens, int perticible, int nbstructure) {
	//initialisation
	int degre = nbajout - 1;
	int i;
	int j;
	//Ici on utilise des float pour la valeur avec laquelle on pointe sur les autres sommets
	float z = nbajout;
	float x = 1/(z - 1);
	int cible = 0;
	
	//Choix de la cible aléatoirement ou non et en fonction de ce qu'a entré l'utilisateur
	if (perticible == 1) { cible = 280545; }
	if (perticible == 2) { cible = 281466; }
	if (perticible == 3) { cible = 281574; }
	
	// Ecriture du graphe complet à la fin du fichier web.
	FILE *g = fopen(nom,"a");
	// Ici on ecrit d'abord le degré et le while (2nd for) va ecrire les liens 
	// vers les autres pages. 
	for (int y = 0; y < nbstructure; y++) {
		for (i = 1; i < nbajout; i++) {
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
			fprintf(g, "\n");
		}
		// Ecriture de la dernière page, celle qui pointe sur la cible
		x = 1/z;
		fprintf(g, "%d %d", nbpages+i+(y*nbajout), degre + 1);
		for(j = 1; j < nbajout + 1; j++){
		/////// j = 1;
		/////// while (j != nbajout + 1){
			if (nbpages+j == nbpages+i) {} // if vide !
			else {
				fprintf(g, " %d %f", nbpages+j+(y*nbajout), x);
			}
			/////// j++;
		}
		fprintf(g, " %d %f\n", cible, x);
	}
	fclose(g);
	
	// Ecriture du nouveau nombre de pages et nombre de liens.
	FILE *h = fopen(nom,"r+");
	fprintf(h, "%d %d", nbpages+(nbajout*nbstructure), nbliens+((nbajout * (nbajout-1)) +1)*nbstructure);
	fclose(h);
}



void ajoutarbre(int nbajout, char* nom, int nbpages, int nbliens, int perticible, int nbstructure) {
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
	if (perticible == 2) { cible = 281466; }
	if (perticible == 3) { cible = 281574; }

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
	int degre = 1;
	int i;
	int y = 0;
	int cible = 0;
	int nouveauliens = 0;
	int nouveausommets = 0;
	int sommetsuivant = 0;
	int nbsommetrestant = 50;
	//int nbstructurerestant = nbstructure;
	
	//Choix de la cible aléatoirement ou non et en fonction de ce qu'a entré l'utilisateur
	if (perticible == 1) { cible = 280545; }
	if (perticible == 2) { cible = 281466; }
	if (perticible == 3) { cible = 281574; }

	// Ecriture d'un anneau à la fin du fichier web, on relis le dernier 
	// sommet au premier de l'anneau et à la cible.
	//Le (y*nbajout) est la pour incrémenter le num de page a chaque itération du nb de structure a ajouter
	FILE *g = fopen(nom,"a");

	while(nbsommetrestant > 0) {
		//nbstructurerestant --;
		nbajout = rand()%(50-nouveausommets);
		//while (nbajout <= 0) { nbajout = rand()%(nbsommetrestant-nbstructurerestant); }
		if (nbajout <= 3) { nbajout = 3; }
		
		//if (nbajout > nbsommetrestant) { nbajout = nbsommetrestant; }
		//if (nbajout == 1) { nbajout = 2; }
		
		nbsommetrestant -= nbajout;
		//if (nbsommetrestant <=0) {return;}
		
		printf("%d \n", nbajout);
		
		for (i = 1; i < nbajout; i++) {
			fprintf(g, "%d %d %d 1.000000\n", nbpages+i+sommetsuivant, degre, nbpages+i+1+sommetsuivant);
			nouveauliens++;
			nouveausommets++;
		}
		fprintf(g, "%d %d %d 0.500000 %d 0.500000\n", nbpages+i+sommetsuivant, 2, nbpages+1+sommetsuivant, cible);
		nouveausommets++;
		nouveauliens+=2;
		sommetsuivant += nbajout;
	y++;
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
	int nbsommetrestant = 50;
	//int nbstructurerestant = nbstructure;
	int y = 0;
	
	//printf("nb struct a  creer : %d \n", nbstructure);
	
	
	//Choix de la cible aléatoirement ou non et en fonction de ce qu'a entré l'utilisateur
	if (perticible == 1) { cible = 280545; }
	if (perticible == 2) { cible = 281466; }
	if (perticible == 3) { cible = 281574; }

	// Ecriture d'un anneau à la fin du fichier web, on relis le dernier 
	// sommet au premier de l'anneau et à la cible.
	//Le (y*nbajout) est la pour incrémenter le num de page a chaque itération du nb de structure a ajouter
	FILE *g = fopen(nom,"a");

	while(nbsommetrestant > 0) {
		//nbstructurerestant --;
		nbajout = rand()%(50-nouveausommets);
		//while (nbajout <= 0) { nbajout = rand()%(nbsommetrestant-nbstructurerestant); }
		if (nbajout <= 3) { nbajout = 3; }
		z = nbajout;
		x = 1/(z - 1);
		degre = nbajout-1;
		
		//if (nbajout > nbsommetrestant) { nbajout = nbsommetrestant; }
		//if (nbajout == 1) { nbajout = 2; }
		
		nbsommetrestant -= nbajout;
		//if (nbsommetrestant >= 0) {}
		
		printf("%d \n", nbajout);
		
		for (i = 1; i < nbajout; i++) {
			/////// j = 1;
			fprintf(g, "%d %d", nbpages+i+(y*nbajout), degre);
			for(j = 1; j < nbajout + 1; j++){
			///////  while (j != nbajout + 1){
				// Cette condition permet de savoir si on est pas sur 
				// la page que l'on ecrit. Pour ne pas faire un lien d'une 
				// page sur elle même.
				if (nbpages+j == nbpages+i) {} // if vide !
				else {
					fprintf(g, " %d %f", nbpages+j+(y*nbajout), x);
					nouveauliens++;}
				/////// j++;
			}
			fprintf(g, "\n");
			nouveausommets++;
		}
		x = 1/z;
		fprintf(g, "%d %d", nbpages+i+(y*nbajout), degre + 1);
		for(j = 1; j < nbajout + 1; j++){
		/////// j = 1;
		/////// while (j != nbajout + 1){
			if (nbpages+j == nbpages+i) {} // if vide !
			else {
				fprintf(g, " %d %f", nbpages+j+(y*nbajout), x);
				nouveauliens++;
			}
			/////// j++;
		}
		fprintf(g, " %d %f\n", cible, x);
		nouveauliens++;
		nouveausommets++;
		sommetsuivant += nbajout;
		y++;
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
	int degre = 1;
	int i;
	int y = 0;
	int cible = 0;
	int nouveauliens = 0;
	int nouveausommets = 0;
	int sommetsuivant = 0;
	int nbsommetrestant = 50;
	int compteur = 0; // Distance par rapport à la racine
	int racine = 0;
	
	//Choix de la cible aléatoirement ou non et en fonction de ce qu'a entré l'utilisateur
	if (perticible == 1) { cible = 280545; }
	if (perticible == 2) { cible = 281466; }
	if (perticible == 3) { cible = 281574; }

	// Ecriture d'un anneau à la fin du fichier web, on relis le dernier 
	// sommet au premier de l'anneau et à la cible.
	//Le (y*nbajout) est la pour incrémenter le num de page a chaque itération du nb de structure a ajouter
	FILE *g = fopen(nom,"a");

	while(nbsommetrestant > 0) {
		//nbstructurerestant --;
		nbajout = rand()%(50-nouveausommets);
		//while (nbajout <= 0) { nbajout = rand()%(nbsommetrestant-nbstructurerestant); }
		if (nbajout <= 3) { nbajout = 3; }
		
		//if (nbajout > nbsommetrestant) { nbajout = nbsommetrestant; }
		//if (nbajout == 1) { nbajout = 2; }
		
		nbsommetrestant -= nbajout;
		//if (nbsommetrestant <=0) {return;}
		printf("%d \n", nbajout);
		
		racine = nbpages + 1+(y*nbajout);
		fprintf(g, "%d %d %d 1.000000\n", racine, degre, cible);
		nouveausommets++;
		nouveauliens++;
		// Sommets 2 à 2 (arbre binaire) et on pointe vers le sommet père 
		// lui meme calculé par sa distance à la racine	
		for (i = 1; i < nbajout - 1; i+=2) {
			fprintf(g, "%d %d %d 1.000000\n", racine+i, degre, racine + compteur);	
			fprintf(g, "%d %d %d 1.000000\n", racine+i+1, degre, racine + compteur);
			nouveausommets+=2;
			nouveauliens+=2;	
			compteur++;
		}
		// Le dernier sommet dans le cas d'un nombre PAIR de sommets 
		// a entrer (pair car le sommet racine est deja entré hors de la boucle)
		if (nbajout%2 == 0){ 
			fprintf(g, "%d %d %d 1.000000\n", racine+i, degre, racine + compteur);
			nouveausommets++;
			nouveauliens++;
		}
		//on réinitialise le compteur car on va commencer un nouvel arbre
		compteur = 0;
	y++;
	}
	fclose(g);

	// Ecriture du nouveau nombre de pages et nombre de liens.
	FILE *h = fopen(nom,"r+");
	fprintf(h, "%d %d", nbpages+nouveausommets, nbliens+nouveauliens);
	fclose(h);
}

void ajoutstructure(int structure, int nbstructure, int nbajout, char* nom, int nbpages, int nbliens, int cible)
{
	int i;
		if (structure == 1) { ajoutsommetseul(nbajout, nom, nbpages, nbliens, cible); }
		else if (structure == 2) { ajoutanneau(nbajout, nom, nbpages, nbliens, cible, nbstructure); }
		else if (structure == 3) { ajoutcomplet(nbajout, nom, nbpages, nbliens, cible, nbstructure); }
		else if (structure == 4) { ajoutarbre(nbajout, nom, nbpages, nbliens, cible, nbstructure); }
		else if (structure == 5) { ajoutanneaualeatoire(50, nom, nbpages, nbliens, 2); }
		else if (structure == 6) { ajoutcompletaleatoire(50, nom, nbpages, nbliens, 2); }
		else if (structure == 7) { ajoutarbrealeatoire(50, nom, nbpages, nbliens, 2); }
}


int main(int argc, char** argv) {
	// cible c'est le n° de page de la cible
	int structure, nbstructure, nbajout, nbpages, nbliens, cible;
	char c;
	int i = 0;
	//srand(time(0));
	srandom(time(NULL));
	
	FILE *f = fopen(argv[1],"r");
	if (f == NULL) {
		exit(EXIT_FAILURE); }
	
	fscanf(f, "%d", &nbpages);
	fscanf(f, "%d", &nbliens);
	printf("pages : %d\n", nbpages);
	printf("lien : %d\n", nbliens);
	fclose(f);
	

	printf("Entrez la structure que vous voulez insérer : \n 1 pour un sommet seul \n 2 pour un anneau \n 3 pour un graphe complet \n 4 pour un arbre \n 5 pour un anneau aléatoire \n 6 pour un graphe complet aléatoire \n 7 pour un arbre aléatoire\n");
	scanf("%d", &structure);
	
	if ((structure == 5) || (structure == 6) || (structure == 7)) { }
	else { 

	printf("Entrer le nombre de structure que vous voulez ajouter : \n");
	scanf("%d", &nbstructure);

	printf("Entrez le nombre de sommets par structure a ajouter : \n");
	scanf("%d", &nbajout);	
	
	printf("Entrez la pertinence de la cible : \n 1 pour une pertinence forte \n 2 pour une pertinence moyenne \n 3 pour une pertinence faible \n");
	scanf("%d", &cible);
	}

	ajoutstructure(structure, nbstructure, nbajout, argv[1], nbpages, nbliens, cible);	
	
	
	return 0;
}

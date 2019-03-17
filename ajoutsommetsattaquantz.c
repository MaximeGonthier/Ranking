#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	FILE *g = fopen(nom,"a");
	for (i = 1; i < nbajout + 1; i++) {
		fprintf(g, "%d %d %d 1.000000\n", nbpages+i, degre, cible);
	}
	fclose(g);
	
	FILE *h = fopen(nom,"r+");
	fprintf(h, "%d %d", nbpages+nbajout, nbliens+nbajout);
	fclose(h);
}

void ajoutanneau (int nbajout, char* nom, int nbpages, int nbliens, int perticible) {

	int degre = 1;
	int i;
	int cible = 0;
	if (perticible == 1) { cible = 280545; }
	if (perticible == 2) { cible = 281466; }
	if (perticible == 3) { cible = 281574; }
	FILE *g = fopen(nom,"a");
	for (i = 1; i < nbajout; i++) {
		fprintf(g, "%d %d %d 1.000000\n", nbpages+i, degre, nbpages+i+1);
	}
		fprintf(g, "%d %d %d 0.500000 %d 0.500000\n", nbpages+i, 2, nbpages+1, cible);
	fclose(g);
	
	FILE *h = fopen(nom,"r+");
	fprintf(h, "%d %d", nbpages+nbajout, nbliens+nbajout+1);
	fclose(h);
}

void ajoutcomplet (int nbajout, char* nom, int nbpages, int nbliens, int perticible) {

	int degre = nbajout - 1;
	int i;
	int j;
	float y = nbajout;
	float x = 1/(y - 1);
	int cible = 0;
	if (perticible == 1) { cible = 280545; }
	if (perticible == 2) { cible = 281466; }
	if (perticible == 3) { cible = 281574; }
	FILE *g = fopen(nom,"a");
	//ici on ecris d'abord le degré et le n° de la page puis le while va ecrire les liens vers les autres pages. 
	for (i = 1; i < nbajout; i++) {
		j = 1;
		fprintf(g, "%d %d", nbpages+i, degre);
		
		while (j != nbajout + 1){
			//ce if il sert a savoir si on est pas sur la page que l'on ecrit. Fin pour pas faire un lien d'une page sur elle meme
			if (nbpages+j == nbpages+i) {}
			else {
				fprintf(g, " %d %f", nbpages+j, x);
			}
			j++;
		}
		fprintf(g, "\n");
	}
	//la on ecris la derniere page, celle qui pointe sur la cible
    x = 1/y;
	fprintf(g, "%d %d", nbpages+i, degre + 1);
	j = 1;
	while (j != nbajout + 1){
			if (nbpages+j == nbpages+i) {}
			else {
				fprintf(g, " %d %f", nbpages+j, x);
			}
			j++;
		}
	fprintf(g, " %d %f\n",cible,x);
	fclose(g);
	
	FILE *h = fopen(nom,"r+");
	fprintf(h, "%d %d", nbpages+nbajout, nbliens+(nbajout * (nbajout-1)) +1);
	fclose(h);
}

void ajoutarbre(int nbajout, char* nom, int nbpages, int nbliens, int perticible) {
//L'arbre va etre construit ainsi : 1 pointe vers la cible, 2 et 3 pointe vers 1, 4 et 5 vers 2, 6 et 7 vers 3 etc ...


	int degre = 1;
	int i;
	//Compteur donne la distance par rapport a la racine
	int compteur = 0;
	int cible = 0;
	int racine = nbpages+1;
	if (perticible == 1) { cible = 280545; }
	if (perticible == 2) { cible = 281466; }
	if (perticible == 3) { cible = 281574; }
	FILE *g = fopen(nom,"a");
	
	//init du sommet racine
	fprintf(g, "%d %d %d 1.000000\n", racine, degre, cible);
	//on fais 2 par 2 les sommets (arbre binaire) et on pointe vers le sommet père lui meme calculé par sa distance a la racine	
	for (i = 1; i < nbajout - 1; i+=2) {
		fprintf(g, "%d %d %d 1.000000\n", racine+i, degre, racine + compteur);	
		fprintf(g, "%d %d %d 1.000000\n", racine+i+1, degre, racine + compteur);	
		compteur++;
	}
	//le dernier sommet dans le cas d'un nombre PAIR de sommets a entré. (pair car le sommet racine est deja entré hors de la boucle)
	if (nbajout%2 == 0) { fprintf(g, "%d %d %d 1.000000\n", racine+i, degre, racine + compteur); }

	
	
	fclose(g);
	
	//modif du nb de liens et de pages dans Stanford
	FILE *h = fopen(nom,"r+");
	fprintf(h, "%d %d", nbpages+nbajout, nbliens+nbajout);
	fclose(h);
}

int main(int argc, char** argv) {

	//cible c'est le n° de page de la cible
	int structure, nbajout, nbpages, nbliens, cible;
	char c;
	int i = 0;
	

	 FILE *f = fopen(argv[1],"r");

	 if (f == NULL) {
		exit(EXIT_FAILURE);
	}
	
	fscanf(f, "%d", &nbpages);
	fscanf(f, "%d", &nbliens);
	printf("pages : %d\n", nbpages);
	printf("lien : %d\n", nbliens);
	fclose(f);

	printf("Entrez la structure que vous voulez insérer : \n 1 pour un sommet seul \n 2 pour un anneau \n 3 pour un graphe complet \n 4 pour un arbre \n");
	scanf("%d", &structure);	

	printf("Entrez le nombre de sommets a ajouter : \n");
	scanf("%d", &nbajout);	
	
	printf("Entrez la pertinence de la cible : \n 1 pour une pertinence forte \n 2 pour une pertinence moyenne \n 3 pour une pertinence faible \n");
	scanf("%d", &cible);

	

	if (structure == 1) { ajoutsommetseul(nbajout,argv[1], nbpages, nbliens, cible); }
	else
	if (structure == 2) { ajoutanneau(nbajout,argv[1], nbpages, nbliens, cible); }
	else
	if (structure == 3) { ajoutcomplet(nbajout,argv[1], nbpages, nbliens, cible); }
	else
	if (structure == 4) { ajoutarbre(nbajout,argv[1], nbpages, nbliens, cible); }
	

	return 0;
}

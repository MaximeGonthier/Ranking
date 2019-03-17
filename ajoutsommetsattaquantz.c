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

	int degre = nbajout;
	int i;
	int j;
	float x = 1/(nbajout - 1);
	int cible = 0;
	if (perticible == 1) { cible = 280545; }
	if (perticible == 2) { cible = 281466; }
	if (perticible == 3) { cible = 281574; }
	FILE *g = fopen(nom,"a");
	for (i = 1; i < nbajout; i++) {
		j = 1;
		fprintf(g, "%d %d", nbpages+i, degre);
		while (nbpages+j != nbajout+nbpages+1) {
			fprintf(g, " %d %f", nbpages+i+j, x);
			j++;
		}
		j = 1;
		while (nbpages+i-j != nbpages) {
			fprintf(g, " %d %f", nbpages+i-j, x);
			j++;
		}
	}
	fclose(g);
	
	FILE *h = fopen(nom,"r+");
	fprintf(h, "%d %d", nbpages+nbajout, nbliens+((nbajout * (nbajout-1))/2) +1);
	fclose(h);
}

int main(int argc, char** argv) {

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
	

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//./a.out nomfichier.txt 
//changer nb pages et de liens

void ajoutsommetseul (int nbajout, char* nom) {

	char c;
	int nbpages, nbliens;
	FILE *f = fopen(nom,"r");
	fscanf(f, "%d\n", &nbpages);
	fscanf(f, "%d\n", &nbliens);
	FILE *g = fopen("result.txt", "w");
	fprintf(g, "%d \n", nbpages + nbajout);
	fprintf(g, "%d \n", nbliens);	//attention faudra mettre les nouveaux liens
	//~ while (c != EOF) {
		//~ fscanf(f, "%c", c);
		//~ fprintf(g, "%c", c);
	//~ }
	fprintf(g, "%d", nbpages + 1);


}

int main(int argc, char** argv) {

	int structure, nbajout;
	

	 FILE *f = fopen(argv[1],"r");

	 if (f == NULL) {
		exit(EXIT_FAILURE);
	}
	
	fclose(f);

	printf("Entrez la structure que vous voulez insérer : \n 1 pour un sommet seul \n 2 pour un anneau \n 3 pour un graphe complet \n 4 pour un arbre \n");
	scanf("%d", &structure);	

	printf("Entrez le nombre de sommets a ajouter : \n");
	scanf("%d", &nbajout);	




	if (structure = 1) { ajoutsommetseul(nbajout,argv[1]); }

	return 0;
}

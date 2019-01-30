#include <stdio.h>
#include <stdlib.h>

typedef struct triplet {
	int i; // a changer en long plus tard
	int j; 
	double proba;
} TRIPLET;



int main(int argc, char** argv) {
	int j, k, n, m;
	
    //lecture du ficher
    FILE *web = fopen("web1.txt","r");
    fscanf(web, "%d\n", &n);
    fscanf(web, "%d\n", &m);
   
	printf("%d\n", n);
	printf("%d\n", m);
	
	// allocation du tableau de triplet
	TRIPLET *st = malloc(m*sizeof(TRIPLET));
	
	// allocation des tableaux debut fin et proba
	int *deb = malloc(n*sizeof(int));
	int *fin = malloc(n*sizeof(int));
	int *proba = malloc(n*sizeof(int));
	
	// page courante, degré sortant, page suivante
	int pageC, degS, pageS;
	double prob; 
	for (k = 0; k < m;) {
		
		fscanf(web, "%d", &pageC);
		fscanf(web, "%d", &degS);
		
		for (j = 0; j < degS; j++)
		{
			fscanf(web, "%d", &pageS);
			fscanf(web, "%lf", &prob);
			st[k].i = pageC;
			st[k].j = pageS;
			st[k].proba = prob;
			k++;
		}
		
		fscanf(web, "\n");
	}
	
	// affichage temporaire
	for (k = 0; k < m; k++)
	{
		printf("%d\t %d\t %lf\n", st[k].i, st[k].j, st[k].proba);
	}
	
	fclose(web);
	
	free(st);
	
	
}

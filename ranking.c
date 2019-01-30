#include <stdio.h>
#include <stdlib.h>

typedef struct triplet {
	long i; // a changer en long plus tard
	long j; 
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
	long pageC, degreS;
	for (k = 0; k < m;) {
		
		fscanf(web, "%ld", &pageC);
		fscanf(web, "%ld", &degreS);
		
		for (j = 0; j < degreS; j++)
		{
			st[k].i = pageC;
			fscanf(web, "%ld", &st[k].j);
			fscanf(web, "%lf", &st[k].proba);
			k++;
		}
		
		fscanf(web, "\n");
	}
	
	// affichage temporaire
	for (k = 0; k < m; k++)
	{
		printf("%ld\t %ld\t %.2lf\n", st[k].i, st[k].j, st[k].proba);
	}
	
	fclose(web);
	
	free(st);
	
	
}

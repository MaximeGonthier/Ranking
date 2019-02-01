#include <stdio.h>
#include <stdlib.h>

typedef struct triplet {
	int i;
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
	double *p = malloc(n*sizeof(double));
	
	// page courante, degré sortant, page suivante
	int pageC, degreS, pageS;
	double proba;
	
	for (k = 0; k < m;) {
		
		fscanf(web, "%d", &pageC);
		fscanf(web, "%d", &degreS);
		
		deb[pageC-1] = k+1;
		
		for (j = 0; j < degreS; j++)
		{
			fscanf(web, "%d", &pageS);
			fscanf(web, "%lf", &proba);
			
			st[k].i = pageC;
			st[k].j = pageS;
			st[k].proba = proba;
			
			k++;
		}
		
		fin[pageC-1] = k;
		
		fscanf(web, "\n");
	}
	
	// affichage temporaire
	for (k = 0; k < m; k++)
	{
		printf("%d\t %d\t %.2lf\n", st[k].i, st[k].j, st[k].proba);
	}
	
	for (j = 0; j < n; j++)
	{
		printf("%d\t %d\t\n", deb[j], fin[j]);
		
		for (k = deb[j]; k <= fin[j]; k++) {
			//do something
		}
	}
	
	fclose(web);
	
	free(st);
	free(deb);
	free(fin);
	free(p);	
	
}

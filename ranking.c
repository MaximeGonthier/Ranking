#include <stdio.h>
#include <stdlib.h>

typedef struct triplet {
	int i; // a changer en long plus tard
	int j; 
	double proba;
} TRIPLET;



int main(int argc, char** argv) {
	int i, n, m;
	
    //lecture du ficher
    FILE *web = fopen("web1.txt","r");
    fscanf(web, "%d\n", &n);
    fscanf(web, "%d\n", &m);
   
	printf("%d\n", n);
	printf("%d\n", m);
	
	// allocation du tableau de triplet
	TRIPLET *st = malloc(m);
	
	int pageC, degS, pageS, proba; // page courante, degré sortant, page suivante
	for (i = 0; i < n; i++) {
		
		fscanf(web, "%d", &pageC);
		fscanf(web, "%d", &degS);
		
		for (j = 0; j < degS; j++)
		{
			fscanf(web, "%d", &pageS);
			fscanf(web, "%f", &proba);
			st[i].i = pageC;
			st[i].j = pageS;
			st[i].proba = proba;
		}
	}
	
	free(st);
	
	
}

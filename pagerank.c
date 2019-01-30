#include <stdio.h>														
#include <stdlib.h>	

typedef struct element
{
	double val;
	int i;	//lignes
	int j;	//colonnes																											
} ELEMENT;

int main() {
	
	int i,j; i = 0; j = 0;
	int degre;	//degre sortant
	int page;	//page courante
	int m;		//nb liens
	int nbp;	//nb pages
	
	FILE *f= fopen("web1.txt", "r"); 		
	
	fscanf(f, "%d\n", &nbp);
	printf("%d\n", nbp);
	fscanf(f, "%d\n", &m);
	printf("%d\n", m);
	ELEMENT *t = mal
	
	loc(m*sizeof(ELEMENT));
	int tabdebut[nbp];
	int tabfin[nbp];
	
	
	
	
	for (i = 0; i < nbp; i++){
		fscanf(f, "%d", &t[i].i);
		printf("%d	", t[i].i);
		fscanf(f, "%d", &degre);
		printf("%d	", degre);
		for (j = 0; j < degre; j++){
			fscanf(f, "%d", &t[i].j);
			
			printf("%d	", t[i].j);
			fscanf(f, "%lf", &t[i].val);
			printf("%lf\n", t[i].val);
			//tabdebut[i] = tabfin[i-1] + 1;
			//tabfin[i] = tabdebut[i] + degre - 1;
	}}
	free(t);
	return 0;
}		
			
			
			
			
			
		

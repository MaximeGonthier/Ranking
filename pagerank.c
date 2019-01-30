#include <stdio.h>														
#include <stdlib.h>	

typedef struct element
{
	double val;
	int i;	//lignes
	int j;	//colonnes																											
} ELEMENT;

int main() {
	printf("a");
	int i,j; i = 0; j = 0;
	int degre;	//degre sortant
	int page;	//page courante
	int m;		//nb liens
	int nbp;	//nb pages
	FILE *f= fopen("web1.txt", "r"); 		
	
	fscanf(f, "%d\n", &nbp);
	fscanf(f, "%d\n", &m);
	ELEMENT *t = malloc(m*sizeof(ELEMENT));
	printf("a");
	for (i = 0; i < m; i++){
		fscanf(f, "%d", NULL);
		fscanf(f, "%d", &degre);
		for (j = 0; j < degre; j++){
			fscanf(f, "%d", &t[i].j);
			fscanf(f, "%f", &t[i].val);
			
	}}
	free(t);
	return 0;
}		
			
			
			
			
			
		

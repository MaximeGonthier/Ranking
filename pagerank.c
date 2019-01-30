#include <stdio.h>														
#include <stdlib.h>	

struct element
{
	double val;
	int i;	//lignes
	int j;	//colonnes															
												
};

typedef struct element* tab;

int main() {
	int i,j; i = 0; j = 0;
	int degre;	//degre sortant
	int page;	//page courante
	int m;		//nb liens
	int nbp;	//nb pages
	FILE *f= fopen("web1.txt", "r"); 		
	tab t;
	int temp; temp = 0;
	fscanf(f, "%d\n", &nbp);
	fscanf(f, "%d\n", &m);
	t = malloc(m*(sizeof(struct element))+1);
	
	for (i = 0; i < m; i++){
		fscanf(f, "%d", &page);
		fscanf(f, "%d", &degre);
		for (j = 0; j < degre; j++){
			t[temp].i = page;
			fscanf(f, "%d", &t[temp].j);
			fscanf(f, "%lf", &t[temp].val);
			temp++;
		}
	}
	
	for(i = 0; i < m; i++){
		printf("%d %d %lf \n", t[i].i, t[i].j, t[i].val);
	}
}	

//// Fin			
			
			
		

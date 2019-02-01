#include <stdio.h>
#include <stdlib.h>

typedef struct triplet {
	int i;
	int j; 
	double proba;
	struct triplet *next; 
} TRIPLET;

TRIPLET* inserer_triplet(int pageC, int pageS, double proba, TRIPLET* next) {
	TRIPLET *t = malloc(sizeof(TRIPLET));
	t->i = pageC;
	t->j = pageS;
	t->proba = proba;
	t->next = next;
	return t;
}

void inserer_liste(TRIPLET** st, int pageC, int pageS, double proba) {
	TRIPLET *tmp  = *st;
	*st = inserer_triplet(pageC, pageS, proba, tmp);
	//printf("%p %d %d\n", (*st)->next, (*st)->i, (*st)->j);
}

void detruire_liste(TRIPLET* l) {
	if (l->next == NULL) {
		free(l);
	}
	else {
		detruire_liste(l->next);
		free(l);
	}
}

void detruire_tableau_listes(TRIPLET** st, int n) {
	int i;
	for (i = 0; i < n; i++)	detruire_liste(st[i]);
	free(st);
}

int main(int argc, char** argv) {
	int j, k, n, m;
	
    //lecture du ficher
    FILE *web = fopen("web1.txt","r");
    fscanf(web, "%d\n", &n);
    fscanf(web, "%d\n", &m);
   
	printf("%d\n", n);
	printf("%d\n", m);
	
	// allocation du tableau de pointeurs de triplets
	TRIPLET **st = calloc(n, sizeof(TRIPLET*));
	
	// allocation du tableaux proba
	double *p = malloc(n*sizeof(double));
	
	// page courante, degré sortant, page suivante
	int pageC, degreS, pageS;
	double proba;
	
	for (k = 0; k < m;) 
	{	
		fscanf(web, "%d", &pageC);
		fscanf(web, "%d", &degreS);
		
		for (j = 0; j < degreS; j++)
		{
			fscanf(web, "%d", &pageS);
			fscanf(web, "%lf", &proba);
			
			inserer_liste(&st[pageS-1], pageC, pageS, proba);
			
			k++;
		}
		
		fscanf(web, "\n");
	}
	
	// affichage temporaire
	TRIPLET *l;
	for (j = 0; j < n; j++)
	{
		l = st[j];
		
		while (l != NULL) {
			printf("%d\t%d\t%lf\n", l->j, l->i, l->proba);
			l = l->next;
		}
	}
	
	fclose(web);
	
	detruire_tableau_listes(st, n);
	free(p);	
	
}

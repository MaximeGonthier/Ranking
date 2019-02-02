#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define alpha 0.85

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

double somme(double* t, int n) {
	int i;
	double sum = 0;
	for (i = 0; i < n; i++)
	{
		sum += t[i];
	}
	return sum;
}

double valeur_absolue(double x) {
	return x < 0 ? -x : x; 
}

double difference_norme(double* p, double* old_p, int n) {
	double norme_p = somme(p, n);
	double norme_old_p = somme(old_p, n);
	return valeur_absolue(norme_p - norme_old_p);
}

void power_method(double* p, TRIPLET** H, int n) {
	int i, j;
	TRIPLET *l;
	double sum, *old_p;
	
	// initialisation des tableaux de probas
	old_p = calloc(n, sizeof(double));
	for (i = 0; i < n; i++)
	{
		p[i] = 1.0/n;		
	}

	// power method
	while (difference_norme(p, old_p, n) > 10E-2) {
		memcpy(old_p, p, n*sizeof(double));
		
		for (i = 0; i < n; i++) // somme p(j) H(j, i)
		{
			sum = 0;
			l = H[i]; // colonne i
			
			while (l != NULL) { // pour tous H(j, i) != 0
				j = l->i; // ligne j
				sum += p[j] * l->proba; // produit matriciel
				l = l->next;
			}
			
			p[i] = sum;
		}
	}	
	
	free(old_p);
}

int main(int argc, char** argv) {
	int i, j, k, n, m;
	
    // lecture du ficher
    FILE *web = fopen("web3.txt","r");
    fscanf(web, "%d\n", &n);
    fscanf(web, "%d\n", &m);
   
	printf("%d\n", n);
	printf("%d\n", m);
	
	// allocation du tableau de pointeurs de triplets
	TRIPLET **st = calloc(n, sizeof(TRIPLET*));
	
	// allocation du tableau proba
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
	power_method(p, st, n);
	
	// affichage du tableau proba après power method
	for (i = 0; i < n; i++)
	{
		printf("Page %d %lf\n",i+1 , p[i]);		
	}	
	
	
	detruire_tableau_listes(st, n);
	free(p);	
	
}

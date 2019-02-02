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
	for (i = 0; i < n; i++)	{
		if (st[i] != NULL) detruire_liste(st[i]);
	}
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
	double sum, beta, *old_p;
	
	// initialisation des tableaux de probas
	old_p = calloc(n, sizeof(double));
	for (i = 0; i < n; i++)
	{
		p[i] = 1.0/n;		
	}

	// power method
	while (difference_norme(p, old_p, n) > 10E-12) 
	{
		memcpy(old_p, p, n*sizeof(double));
		beta = 0;
		for (i = 0; i < n; i++) // p(i) = somme p(j) H(j, i)
		{
			sum = 0;
			l = H[i]; // colonne i
			
			if (l == NULL) beta += old_p[i]; // calcul beta (faux)
			
			while (l != NULL)  // pour tous H(j, i) != 0 
			{
				j = l->i; // ligne j
				sum += old_p[j-1] * l->proba; // produit matriciel
				l = l->next;
			}
			
			p[i] = sum; // p = p*H
		}
		for (i = 0; i < n; i++) // calcul de p = p*G = f(p*H) 
		{ 
			p[i] = alpha * p[i] + (1 - alpha) / n + (alpha * beta) / n; 
		}
	}	
	free(old_p);
}

void afficher_triplets(TRIPLET** st, int n) {
	int j;
	TRIPLET *l;
	for (j = 0; j < n; j++)
	{
		l = st[j];
		
		while (l != NULL) {
			printf("%d\t%d\t%lf\n", l->j, l->i, l->proba);
			l = l->next;
		}
	}	
}

int main(int argc, char** argv) {
	int i, j, k; 
	int n, m;
	
    // lecture du ficher
    FILE *web = fopen("web1.txt","r");
    fscanf(web, "%d\n", &n);
    fscanf(web, "%d\n", &m);
   
	printf("%d pages\n", n);
	printf("%d liens\n", m);
	
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
	fclose(web);
	
	//~ afficher_triplets(st, n);
	
	power_method(p, st, n);
	printf("Done!\n");
	
	// ecriture du tableau de probas après power method
	FILE *out = stdout; //fopen("output.txt","w");
	for (i = 0; i < n; i++)
	{
		fprintf(out, "Page %d %lf %le\n", i+1 , p[i], p[i]);		
	}	
	fprintf(out, "Somme probas : %lf\n", somme(p, n));	
	
	detruire_tableau_listes(st, n);
	free(p);	
	
}

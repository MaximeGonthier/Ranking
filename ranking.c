#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
	return (x < 0) ? -x : x; 
}

double difference_norme(double* t1, double* t2, int n) {
	int i;
	double sum = 0;
	for (i = 0; i < n; i++)
	{
		sum += valeur_absolue(t1[i] - t2[i]);
	}
	return sum;
}

void power_method(double* p, TRIPLET** H, int* f0,  int n) {
	int i, j, k;
	TRIPLET *l;
	double sum, beta, *old_p;
	
	// initialisation des tableaux de probas
	old_p = calloc(n, sizeof(double));
	for (i = 0; i < n; i++)
	{
		p[i] = 1.0/n;		
	}

	// power method
	k = 0;
	while (difference_norme(p, old_p, n) > 10E-12) 
	{
		k++;
		memcpy(old_p, p, n*sizeof(double));
		beta = 0;
		for (i = 0; i < n; i++) // p(i) = somme p(j) H(j, i)
		{
			sum = 0;
			l = H[i]; // colonne i
			
			beta += f0[i]*old_p[i]; // calcul beta		
			
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
	printf("%d itérations\n", k);
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

int succes_fscanf(int fsc1, int fsc2) {
	return (fsc1 == 1 && fsc2 == 1);
}

int main(int argc, char** argv) {
	int i, j, k; 
	int n, m;
	
	float temps;
	clock_t t1,t2;
	t1 = clock();
	
    // lecture du ficher
    FILE *web = fopen("web1sommetseul2.txt","r");
    
    if (web == NULL) {
		exit(EXIT_FAILURE);
	}
    
    fscanf(web, "%d\n", &n);
    fscanf(web, "%d\n", &m);
   
	printf("%d pages\n", n);
	printf("%d liens\n", m);
	
	// allocation du tableau de pointeurs de triplets
	TRIPLET **st = calloc(n, sizeof(TRIPLET*));
	
	// allocation des tableaux
	double *p = malloc(n*sizeof(double)); // probabilités
	int *f0 = malloc(n*sizeof(int)); // stocke si ligne vecteur nul	
	
	// page courante, degré sortant, page suivante
	int pageC, degreS, pageS;
	int fsc1, fsc2;
	double proba;
	
	for (k = 0, fsc1 = 1, fsc2 = 1; succes_fscanf(fsc1, fsc2);)
	{	
		fsc1 = fscanf(web, "%d", &pageC);
		fsc2 = fscanf(web, "%d", &degreS);
		
		if (!succes_fscanf(fsc1, fsc2)) continue;
		
		f0[pageC-1] = (degreS == 0) ? 1 : 0;
		
		for (j = 0; j < degreS && k < m; j++)
		{
			fscanf(web, "%d", &pageS);
			fscanf(web, "%lf", &proba);
			
			inserer_liste(&st[pageS-1], pageC, pageS, proba);
			
			k++;
		}
		
		fscanf(web, "\n");
	}
	fclose(web);
	printf("File read!\n");
	
	if (fsc1 != EOF) {
		fprintf(stderr, "Erreur: Format fichier\n");
		detruire_tableau_listes(st, n);
		free(p);
		free(f0);
		exit(EXIT_FAILURE);			
	}
	
	//~ afficher_triplets(st, n);
	
	power_method(p, st, f0, n);
	printf("Done!\n");
	
	// ecriture du tableau de probas après power method
	FILE *out = fopen("output.txt","w");
	for (i = 0; i < n; i++)
	{
		fprintf(out, "Page %d %lg\n", i+1 , p[i]);		
	}	
	fprintf(out, "Somme probas : %lg\n", somme(p, n));	
	fclose(out);
	
	// memoire
	detruire_tableau_listes(st, n);
	free(p);	
	free(f0);
	t2 = clock();
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	printf("Le temps d'executin est de : %f secondes \n", temps);
}

#ifndef RANKING_H
#define RANKING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct triplet {
	int i;
	int j; 
	double proba;
	struct triplet *next; 
} TRIPLET;

void inserer_liste(TRIPLET** st, int pageC, int pageS, double proba);
void detruire_liste(TRIPLET* l);
void detruire_tableau_listes(TRIPLET** st, int n);
double somme(double* t, int n);
double valeur_absolue(double x);
double difference_norme(double* t1, double* t2, int n);
void power_method(double* p, TRIPLET** H, int* f0,  int n);
void afficher_triplets(TRIPLET** st, int n);
int succes_fscanf(int fsc1, int fsc2);
void pagerank(int argc, char** argv);

#endif //RANKING_H
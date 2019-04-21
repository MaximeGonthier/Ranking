#ifndef AJOUTSOMMETSATTAQUANTS_H
#define AJOUTSOMMETSATTAQUANTS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

void ajoutsommetseul (int nbajout, char* nom, int nbpages, int nbliens, int perticible);
void ajoutanneau (int nbajout, char* nom, int nbpages, int nbliens, int perticible, int nbstructure);
void ajoutcomplet (int nbajout, char* nom, int nbpages, int nbliens, int perticible, int nbstructure);
void ajoutarbre(int nbajout, char* nom, int nbpages, int nbliens, int perticible, int nbstructure);
void ajoutarbre_attaquantunique(int nbajout, char* nom, int nbpages, int nbliens, int perticible, int nbstructure);
void ajoutanneaualeatoire (int nbajout, char* nom, int nbpages, int nbliens, int perticible);
void ajoutcompletaleatoire (int nbajout, char* nom, int nbpages, int nbliens, int perticible);
void ajoutarbrealeatoire (int nbajout, char* nom, int nbpages, int nbliens, int perticible);
void ajout_graphe_aleatoire(int nbajout, char* nom,int nbpages,int nbliens,int perticible,int nbstructur);
void ajout_graphe_aleatoire_avec_proba(int nbajout, char* nom,int nbpages,int nbliens,int perticible, int probabilite);
void ajoutstructure(int structure, int nbstructure, int nbajout, char* nom, int nbpages, int nbliens, int cible);
void sommetsattaquants(int argc, char** argv);


#endif //AJOUTSOMMETSATTAQUANTS_H
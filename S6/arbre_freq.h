#ifndef _ARBRE_FREQ_H_
#define _ARBRE_FREQ_H_

#include <stdio.h>
#include "arbre_binaire.h"

/* Donnee portee par un noeud: Lettre - Frequence */

typedef struct _LettreFrequence {
  char lettre;
  unsigned int nb_occ;
} LettreFrequence;

void *dupliquer_lf(const void *src);
void copier_lf(const void *src, void *dst);
void detruire_lf(void *data);
void afficher_lf(const void *data);
int comparer_lf(const void *a, const void *b);
int ecrire_lf(const void *data, FILE *f);
void * lire_lf(FILE *);


/* Fonctions permettant de manipuler les arbres de Huffman comme donnees d'une liste */


void *dupliquer_ah(const void *src);
void copier_ah(const void *src, void *dst);
void detruire_ah(void *data);
void afficher_ah(const void *data);
int comparer_ah(const void *a, const void *b);
int ecrire_ah(const void *data, FILE *f);
void * lire_ah(FILE *);

PNoeudBinaire copier_ab(PArbreBinaire pab, PNoeudBinaire pnb);

PNoeudBinaire lire_ah_rec(FILE *f);


#endif

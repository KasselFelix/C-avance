#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <stdio.h>
#include "liste.h"
#include "arbre_binaire.h"
#include "arbre_freq.h"


typedef enum _type_noeud_arbre_binaire {INTERNE, AFILSGAUCHE, AFILSDROIT, FEUILLE} TypeNoeudArbreBinaire;

typedef enum _type_chemin {RACINE, FILSGAUCHE, FILSDROIT} TypeChemin;

typedef struct _TabCode {
  char code_courant[257];
  char *code[256];
} TabCode;

int *distri_code(FILE *f);

PArbreBinaire creer_arbre_huffman(char lettre, unsigned int nb_occ);


PListe creer_liste_occ(int *);


PArbreBinaire fusion_arbres(PArbreBinaire pab1, PArbreBinaire pab2);


PArbreBinaire construire_arbre_codes(PListe plocc);


void map_ab_prefixe_chemin(PArbreBinaire pab, void (*fonction)(void *data, int prof, TypeChemin tc,
							       TypeNoeudArbreBinaire tnab, void *oa), void *optarg);

void affiche_code(void *data, int prof, TypeChemin tc, TypeNoeudArbreBinaire tnab, void *oa);


void construire_tableau_code_fonction(void *data, int prof, TypeChemin tc,
				      TypeNoeudArbreBinaire tnab, void *oa);


char **construire_tableau_code(PArbreBinaire pah);


int compresser(const char *nom_fichier_in);


int ajouter_bits(char *code, char* buffer, int ptr);


int decompresser(const char *nom_fichier_in, const char *nom_fichier_out);


void ecrire_noeud_huffman(void *data, int prof, TypeChemin tc, TypeNoeudArbreBinaire tnab, void *oa);


#endif

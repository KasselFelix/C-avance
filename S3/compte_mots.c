#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "devel.h"
#include "liste.h"
#include "fonctions_2entiers.h"
#include "fonctions_string.h"

void compte(void *data, void *optarg) {
  int longueur = strlen( ( char * ) data );
  PElement element_avec_meme_longueur = chercher_liste( optarg, & longueur );
  if ( element_avec_meme_longueur == NULL ) {
    Double_int compteur_a_rajouter = { longueur, 1 };
    inserer_place( optarg, & compteur_a_rajouter );
  }
  else
    ( ( Double_int * ) ( element_avec_meme_longueur -> data ) ) -> b += 1;
}

int main(void) {

  PListe dictionnaire;
  if ( ( dictionnaire = malloc( sizeof( Liste ) ) ) == NULL ) {
    fprintf( stderr, "Erreur lors de l'allocation du dictionnaire.\n" );
    return EXIT_FAILURE;
  }
  dictionnaire -> dupliquer = dupliquer_str;
  dictionnaire -> copier = copier_str;
  dictionnaire -> detruire = detruire_str;
  dictionnaire -> afficher = afficher_str;
  dictionnaire -> comparer = comparer_str;
  dictionnaire -> ecrire = ecrire_str;
  dictionnaire -> lire = lire_str;
  dictionnaire -> elements = NULL;
  printf( "Le programme va maintenant parcourir le contenu du dictionnaire french_za.\n" );
  printf("Il est retiré par défaut pour ne pas dépasser la taille limite du rendu.\n" );
  printf( "Veuillez patienter...\n" );
  lire_liste( dictionnaire, "french_za" );

  PListe compteur;
  if ( ( compteur = malloc( sizeof( Liste ) ) ) == NULL ) {
    fprintf( stderr, "Erreur lors de l'allocation du compteur.\n" );
    return EXIT_FAILURE;
  }
  compteur -> dupliquer = dupliquer_2int;
  compteur -> copier = copier_2int;
  compteur -> detruire = detruire_2int;
  compteur -> afficher = afficher_2int;
  compteur -> comparer = comparer_2int;
  compteur -> ecrire = ecrire_2int;
  compteur -> lire = lire_2int;
  compteur -> elements = NULL;

  printf( "Voici le nombre b de mots de longueur a :\n" );
  map( dictionnaire, compte, compteur );
  afficher_liste( compteur );

  detruire_liste( dictionnaire );
  detruire_liste( compteur );
  
  return 0;
}

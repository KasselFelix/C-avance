
#include <stdlib.h>
#include "liste.h"
#include "devel.h"
#include "fonctions_entiers.h"

void decrementer( void * data, void * oa ) {
  int * data_int = ( int * ) data;
  * data_int -= 1;
}

int main(void) {

  PListe liste_int;
  if ( ( liste_int = malloc( sizeof( Liste ) ) ) == NULL ) {
    fprintf( stderr, "Erreur lors de l'allocation de liste_int.\n" );
    return EXIT_FAILURE;
  }
  liste_int -> dupliquer = dupliquer_int;
  liste_int -> copier = copier_int;
  liste_int -> detruire = detruire_int;
  liste_int -> afficher = afficher_int;
  liste_int -> comparer = comparer_int;
  liste_int -> ecrire = ecrire_int;
  liste_int -> lire = lire_int;
  liste_int -> elements = NULL;

  printf( "Affiche 3 4.\n" );
  for( int i = 3; i < 5; i++ )
    inserer_fin( liste_int, &i );
  afficher_liste( liste_int );

  printf( "Affiche 1 3 4.\n" );
  int tmp = 1;
  inserer_debut( liste_int, &tmp );
  afficher_liste( liste_int );

  printf( "Affiche 1 2 3 4.\n" );
  tmp = 2;
  inserer_place( liste_int, &tmp );
  afficher_liste( liste_int );

  printf( "Affiche 2.\n" );
  printf( "%d\n", * ( int * ) ( chercher_liste( liste_int, &tmp )-> data ) );

  printf( "Affiche aussi 2.\n" );
  printf( "%d\n", * ( int * ) ( chercher_liste_triee( liste_int, &tmp )-> data ) );

  printf( "Maintenant, nous écrivons dans 'liste.txt'. Vérifier qu'elle contient 1 2 3 4 !\n" );
  ecrire_liste( liste_int, "liste.txt" );

  printf( "Affiche 1 2 3 4 5 6.\n" );
  tmp = 5;
  int tmp2 = 6;
  ajouter_liste( liste_int, 2, &tmp, &tmp2 );
  afficher_liste( liste_int );

  printf( "Affiche 0 1 2 3 4 5.\n" );
  map( liste_int, decrementer, NULL );
  afficher_liste( liste_int );

  printf( "Retirons et affichons la tête : 0.\n" );
  PElement tete = extraire_en_tete( liste_int );
  printf( "%d\n", * ( int * ) ( tete -> data ) );
  liste_int -> detruire( tete -> data );
  free( tete );

  printf( "Affiche le reste : 1 2 3 4 5.\n" );
  afficher_liste( liste_int );

  printf( "Enfin, on ajoute le contenu de 'liste.txt' : 1 2 3 4 5 suivi de 1 2 3 4.\n");
  lire_liste( liste_int, "liste.txt" );
  afficher_liste( liste_int );

  detruire_liste( liste_int );

  return EXIT_SUCCESS;
}

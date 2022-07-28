#include <stdlib.h>
#include "liste.h"
#include "devel.h"
#include "fonctions_string.h"

void decrementerInitiale( void * data, void * oa ) {
  char * data_char = ( char * ) data;
  * data_char -= 1;
}

int main(void) {

  PListe liste_string;
  if ( ( liste_string = malloc( sizeof( Liste ) ) ) == NULL ) {
    fprintf( stderr, "Erreur lors de l'allocation de liste_string.\n" );
    return EXIT_FAILURE;
  }
  liste_string -> dupliquer = dupliquer_str;
  liste_string -> copier = copier_str;
  liste_string -> detruire = detruire_str;
  liste_string -> afficher = afficher_str;
  liste_string -> comparer = comparer_str;
  liste_string -> ecrire = ecrire_str;
  liste_string -> lire = lire_str;
  liste_string -> elements = NULL;

  printf( "Affiche C D.\n" );
  char tmp[] = "C";
  char tmp2[] = "D";
  inserer_fin( liste_string, &tmp );
  inserer_fin( liste_string, &tmp2 );
  afficher_liste( liste_string );

  printf( "Affiche A C D.\n" );
  tmp[ 0 ] = 'A';
  inserer_debut( liste_string, &tmp );
  afficher_liste( liste_string );

  printf( "Affiche A B C D.\n" );
  tmp[ 0 ] = 'B';
  inserer_place( liste_string, &tmp );
  afficher_liste( liste_string );

  printf( "Affiche B.\n" );
  printf( "%s\n", ( char * ) ( chercher_liste( liste_string, &tmp )-> data ) );

  printf( "Affiche aussi B.\n" );
  printf( "%s\n", ( char * ) ( chercher_liste_triee( liste_string, &tmp )-> data ) );

  printf( "Maintenant, nous écrivons dans 'liste.txt'. Vérifier qu'elle contient A B C D !\n" );
  ecrire_liste( liste_string, "liste.txt" );

  printf( "Affiche A B C D E F.\n" );
  tmp[ 0 ] = 'E';
  tmp2[ 0 ] = 'F';
  ajouter_liste( liste_string, 2, &tmp, &tmp2 );
  afficher_liste( liste_string );

  printf( "Affiche @ A B C D E.\n" );
  map( liste_string, decrementerInitiale, NULL );
  afficher_liste( liste_string );

  printf( "Retirons et affichons la tête : @.\n" );
  PElement tete = extraire_en_tete( liste_string );
  printf( "%s\n", ( char * ) ( tete -> data ) );
  liste_string -> detruire( tete -> data );
  free( tete );

  printf( "Affiche le reste : A B C D E.\n" );
  afficher_liste( liste_string );

  printf( "Enfin, on ajoute le contenu de 'liste.txt' : A B C D E suivi de A B C D.\n" );
  lire_liste( liste_string, "liste.txt" );
  afficher_liste( liste_string );

  detruire_liste( liste_string );

  return EXIT_SUCCESS;
}

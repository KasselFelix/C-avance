#include <stdlib.h>
#include <stdio.h>
#include "devel.h"
#include <string.h>

#include "fonctions_2entiers.h"

int * pa( void * data ) {
  return & ( ( ( Double_int * ) data ) -> a );
}

int * pb( void * data ) {
  return & ( ( ( Double_int * ) data ) -> b );
}

void *dupliquer_2int(const void *src) {
  Double_int * dst = malloc( sizeof( Double_int ) );
  memcpy( dst, src, sizeof( Double_int ) );

  //dst -> a = * pa( ( void * ) src );
  //dst -> b = * pb( ( void * ) src );
  return dst;
}

void copier_2int(const void *src, void *dst) {
  dst = malloc( sizeof( Double_int ) );
  memcpy( dst, src, sizeof( Double_int) );
}

void detruire_2int(void *data) {
  free( data );
}

void afficher_2int(const void *data) {
  printf( "a=%d b=%d", (* pa( data )), * pb( data ) );
}

int comparer_2int(const void *a, const void *b) {
  if ( * pa( a )  < * pa( b ) ) return -1;
  if ( * pa( a ) == * pa( b ) ) return  0;
  else                          return  1;
}

int ecrire_2int(const void *data, FILE *f) {
  return fprintf( f, "a=%d b=%d\n", * pa( data ), * pb( data ) );
}

void * lire_2int(FILE *f) {
  Double_int * dst = malloc( sizeof( Double_int ) );
  if ( fscanf( f, "a=%d b=%d\n", pa( dst ), pb( dst ) ) != 2 )
    printf( "Erreur à la lecture du fichier.\n" );
  return dst;
}
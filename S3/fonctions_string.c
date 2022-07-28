#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "devel.h"

void *dupliquer_str(const void *src) {
  return strdup( src );
}

void copier_str(const void *src, void *dst) {
  strcpy( dst, src );
}

void detruire_str(void *data) {
  free( data );
}

void afficher_str(const void *data) {
  printf( "%s", ( char * ) data );
}

int comparer_str(const void *a, const void *b) {
  return strcmp( a, b );
}

int ecrire_str(const void *data, FILE *f) {
  return fprintf( f, "%s", ( char * ) data );
}

void * lire_str(FILE *f) {
  //Grand tableau temporaire pour être sûr de lire toute la chaîne.
  char luTemporaire[ 1000 ];
  if ( fscanf( f, "%s\n", luTemporaire ) == 1 )
    //On duplique dans une chaîne plus courte et ne renvoie que celle-ci pour optimiser la mémoire.
    return strdup( luTemporaire );
  else
    return NULL;
}
